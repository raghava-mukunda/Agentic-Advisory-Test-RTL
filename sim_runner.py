"""
sim_runner.py
Verilator simulation wrapper.

Handles:
  - Compilation of RTL + testbench to a Verilator binary (cached)
  - Running the binary with a test vector
  - Parsing stdout into a structured result dict
  - Timeout protection
  - VCD dump support for waveform debugging
"""

import subprocess
import os
import json
import hashlib
import time
from pathlib import Path
from typing import Optional
from dataclasses import dataclass


@dataclass
class SimConfig:
    design_file: str                   # Path to .v / .sv RTL file
    tb_file: str                       # Path to tb.cpp
    obj_dir: str = "./obj_dir"         # Verilator build output dir
    binary_name: str = "Valu_fsm"     # Verilator-generated binary name
    timeout_sec: float = 5.0           # Per-simulation timeout
    enable_vcd: bool = False           # Dump waveforms (slow — debug only)
    num_cycles: int = 6                # Clock edges to simulate per test
    verilator_flags: str = "--cc --exe --build"


class SimRunner:
    """
    Manages compilation and execution of the Verilator simulation.

    Usage
    -----
    runner = SimRunner(SimConfig(...))
    runner.compile()                         # once per design change
    result = runner.run({"a": 10, "b": 0, "op": 3})
    """

    def __init__(self, config: SimConfig):
        self.config = config
        self._binary_path = os.path.join(config.obj_dir, config.binary_name)
        self._compiled_hash: Optional[str] = None

    # ------------------------------------------------------------------
    # Compilation
    # ------------------------------------------------------------------

    def compile(self, force: bool = False) -> bool:
        """
        Compile RTL + testbench using Verilator.
        Returns True on success.
        Caches by file hash — skips recompilation if nothing changed.
        """
        current_hash = self._source_hash()
        if not force and current_hash == self._compiled_hash and self._binary_exists():
            return True

        cmd = [
            "verilator",
            "--cc", "--exe", "--build",
            "-Wall", "-Wno-UNUSEDPARAM",
            "--Mdir", self.config.obj_dir,
        ]
        if self.config.enable_vcd:
            cmd += ["--trace"]
        cmd += [self.config.design_file, self.config.tb_file]

        print(f"[SimRunner] Compiling: {' '.join(cmd)}")
        result = subprocess.run(cmd, capture_output=True, text=True)

        if result.returncode != 0:
            print("[SimRunner] Compilation FAILED:")
            print(result.stderr)
            return False

        self._compiled_hash = current_hash
        print(f"[SimRunner] Compilation OK → {self._binary_path}")
        return True

    # ------------------------------------------------------------------
    # Simulation
    # ------------------------------------------------------------------

    def run(self, vector: dict) -> dict:
        """
        Run one simulation with the given input vector.

        Returns a result dict:
          {
            "failure": bool,
            "type": str | None,       # "divide_by_zero" | "overflow" | "unknown" | None
            "outputs": dict,          # parsed output values
            "raw": str,               # raw stdout
            "cycles": int,            # cycles simulated
            "sim_time_ms": float
          }
        """
        if not self._binary_exists():
            raise RuntimeError("Binary not found. Call compile() first.")

        args = [str(v) for v in vector.values()]
        cmd = [self._binary_path] + args

        t0 = time.perf_counter()
        try:
            proc = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=self.config.timeout_sec
            )
        except subprocess.TimeoutExpired:
            return {
                "failure": True,
                "type": "timeout",
                "outputs": {},
                "raw": "",
                "cycles": 0,
                "sim_time_ms": self.config.timeout_sec * 1000,
            }
        sim_ms = (time.perf_counter() - t0) * 1000

        raw = proc.stdout.strip()
        return self._parse_output(raw, vector, sim_ms)

    # ------------------------------------------------------------------
    # Output parsing
    # ------------------------------------------------------------------

    def _parse_output(self, raw: str, vector: dict, sim_ms: float) -> dict:
        """
        Parse the simulator's stdout into a structured result.
        Expected format from tb.cpp (new):
            y=<val> err_div=<0|1> err_ovf=<0|1> err_udf=<0|1> state=<0-3> cycle=<n>
        Also handles legacy:
            y=<val> error=<0|1>
        """
        result = {
            "failure": False,
            "type": None,
            "outputs": {},
            "raw": raw,
            "cycles": self.config.num_cycles // 2,
            "sim_time_ms": round(sim_ms, 3),
        }

        if not raw:
            result["failure"] = True
            result["type"] = "empty_output"
            return result

        # Parse key=value pairs from output
        for token in raw.split():
            if '=' in token:
                k, v = token.split('=', 1)
                try:
                    result["outputs"][k] = int(v)
                except ValueError:
                    result["outputs"][k] = v

        out   = result["outputs"]
        cycle = out.get("cycle")
        if cycle is not None:
            result["cycles"] = cycle

        # New separate error signals (preferred)
        if out.get("err_div", 0):
            result["failure"] = True
            result["type"] = "divide_by_zero"
        elif out.get("err_ovf", 0):
            result["failure"] = True
            result["type"] = "overflow"
        elif out.get("err_udf", 0):
            result["failure"] = True
            result["type"] = "underflow"
        # Legacy single error signal
        elif out.get("error", 0):
            result["failure"] = True
            op = vector.get("op", -1)
            b  = vector.get("b", -1)
            if op == 3 and b == 0:
                result["type"] = "divide_by_zero"
            elif out.get("y", 0) > 200:
                result["type"] = "overflow"
            else:
                result["type"] = "unknown_error"

        return result

    # ------------------------------------------------------------------
    # Helpers
    # ------------------------------------------------------------------

    def _binary_exists(self) -> bool:
        return Path(self._binary_path).exists()

    def _source_hash(self) -> str:
        h = hashlib.md5()
        for f in [self.config.design_file, self.config.tb_file]:
            if Path(f).exists():
                h.update(Path(f).read_bytes())
        return h.hexdigest()
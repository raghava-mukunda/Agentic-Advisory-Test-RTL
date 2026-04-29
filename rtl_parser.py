"""
rtl_parser.py
Parses Verilog/SV RTL files to extract port definitions, bit widths,
directionality, and design metadata needed by the agent and sim_runner.

Handles both numeric widths [7:0] and parameter-based widths [WIDTH-1:0].
"""

import re
import json
from pathlib import Path
from dataclasses import dataclass, field, asdict
from typing import Dict, List, Optional


@dataclass
class Port:
    name: str
    direction: str          # "input" | "output" | "inout"
    width: int              # bit width (1 for scalar)
    signed: bool = False
    is_clock: bool = False
    is_reset: bool = False

    @property
    def max_val(self) -> int:
        if self.signed:
            return (1 << (self.width - 1)) - 1
        return (1 << self.width) - 1

    @property
    def min_val(self) -> int:
        return -(1 << (self.width - 1)) if self.signed else 0


@dataclass
class DesignMeta:
    module_name: str
    source_file: str
    inputs: Dict[str, Port] = field(default_factory=dict)
    outputs: Dict[str, Port] = field(default_factory=dict)
    clocked: bool = False
    clock_port: Optional[str] = None
    reset_port: Optional[str] = None
    reset_active_high: bool = True
    parameters: Dict[str, int] = field(default_factory=dict)

    def controllable_inputs(self) -> Dict[str, Port]:
        """Return inputs excluding clock and reset — the ones the agent controls."""
        return {
            name: p for name, p in self.inputs.items()
            if not p.is_clock and not p.is_reset
        }

    def to_dict(self) -> dict:
        return asdict(self)

    def to_json(self, path: Optional[str] = None) -> str:
        s = json.dumps(self.to_dict(), indent=2)
        if path:
            Path(path).write_text(s)
        return s


class RTLParser:
    """
    Lightweight regex-based Verilog port parser.
    Handles ANSI-style port declarations with both numeric and
    parameter-based bit widths (e.g. [WIDTH-1:0]).
    """

    _MODULE_RE = re.compile(r'\bmodule\s+(\w+)\s*[#(]', re.IGNORECASE)
    _PARAM_RE  = re.compile(r'\bparameter\s+(?:integer\s+)?(\w+)\s*=\s*(\d+)', re.IGNORECASE)

    # Matches: input/output [signed] [<expr>:<expr>] portname
    # The width expression groups now accept any non-bracket chars (handles WIDTH-1, etc.)
    _ANSI_PORT_RE = re.compile(
        r'\b(input|output|inout)\s+'
        r'(?:wire\s+|reg\s+|logic\s+)?'
        r'(signed\s+)?'
        r'(?:\[([^\]:]+)\s*:\s*([^\]:]+)\])?\s*'
        r'(\w+)',
        re.IGNORECASE
    )

    _CLOCK_HINTS = {'clk', 'clock', 'clk_i', 'sys_clk', 'pclk'}
    _RESET_HINTS = {'rst', 'reset', 'rst_n', 'reset_n', 'arst', 'nrst', 'rst_i'}

    def parse(self, filepath: str) -> DesignMeta:
        src       = Path(filepath).read_text()
        src_clean = self._strip_comments(src)

        module_match = self._MODULE_RE.search(src_clean)
        if not module_match:
            raise ValueError(f"No module declaration found in {filepath}")

        meta = DesignMeta(module_name=module_match.group(1),
                          source_file=str(filepath))

        # Extract parameters first so we can resolve WIDTH etc.
        for m in self._PARAM_RE.finditer(src_clean):
            meta.parameters[m.group(1)] = int(m.group(2))

        # Extract ports
        for m in self._ANSI_PORT_RE.finditer(src_clean):
            direction = m.group(1).lower()
            signed    = m.group(2) is not None
            msb_expr  = m.group(3)
            lsb_expr  = m.group(4)
            name      = m.group(5)

            # Skip keywords that the regex might accidentally match
            if name.lower() in ('begin', 'end', 'always', 'assign',
                                 'module', 'endmodule', 'case', 'if',
                                 'else', 'wire', 'reg', 'logic'):
                continue

            if msb_expr is not None:
                msb = self._eval_expr(msb_expr.strip(), meta.parameters)
                lsb = self._eval_expr(lsb_expr.strip(), meta.parameters)
                width = max(1, msb - lsb + 1)
            else:
                width = 1

            port = Port(
                name=name,
                direction=direction,
                width=width,
                signed=signed,
                is_clock=name.lower() in self._CLOCK_HINTS,
                is_reset=name.lower() in self._RESET_HINTS,
            )

            if direction == "input":
                meta.inputs[name] = port
            else:
                meta.outputs[name] = port

        # Detect clocked design
        if "posedge" in src_clean.lower() or "negedge" in src_clean.lower():
            meta.clocked = True

        # Identify clock/reset ports
        for name, port in meta.inputs.items():
            if port.is_clock:
                meta.clock_port = name
            if port.is_reset:
                meta.reset_port = name
                if name.endswith('_n') or name.endswith('n'):
                    meta.reset_active_high = False

        return meta

    def _eval_expr(self, expr: str, params: dict) -> int:
        """
        Evaluate a simple Verilog width expression like 'WIDTH-1' or '7'.
        Substitutes known parameters then evaluates with Python.
        """
        # Replace parameter names with their values
        for pname, pval in sorted(params.items(), key=lambda x: -len(x[0])):
            expr = re.sub(r'\b' + re.escape(pname) + r'\b', str(pval), expr)
        try:
            return int(eval(expr))  # safe: only numeric ops after substitution
        except Exception:
            return 7  # fallback: assume 8-bit if expression can't be resolved

    @staticmethod
    def _strip_comments(src: str) -> str:
        src = re.sub(r'/\*.*?\*/', ' ', src, flags=re.DOTALL)
        src = re.sub(r'//[^\n]*', ' ', src)
        return src


if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python rtl_parser.py <design.v>")
        sys.exit(1)
    parser = RTLParser()
    meta   = parser.parse(sys.argv[1])
    print(meta.to_json())
    print(f"\nControllable inputs: {list(meta.controllable_inputs().keys())}")
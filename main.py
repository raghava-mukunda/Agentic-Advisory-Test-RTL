"""
main.py
Entry point for the AAT-RTL framework.

Usage:
    python main.py                        # single adaptive agent run
    python main.py --compare              # 3-way: adaptive vs random vs biased
    python main.py --multiseed            # publishable: 3 agents x N seeds
    python main.py --episodes 300 --seed 42
"""

import argparse
import random
import json
import sys
import copy
import time
from pathlib import Path


import yaml
from rtl_parser import RTLParser
from agent import Agent, MutationStrategy
from sim_runner import SimRunner, SimConfig
from analyzer import Analyzer
from logger import RunLogger

DEFAULT_CONFIG = {
    "design": "sat_alu.v",
    "tb":     "tb_sat.cpp",
    "episodes": 300,
    "seed": 42,
    "seeds": [42, 123, 7, 99, 2024],
    "epsilon": 0.15,
    "mutation_delta": 8,
    "novelty_budget": 50,
    "known_failure_types": ["divide_by_zero", "overflow", "underflow"],
    "verilator": {
        "obj_dir":     "./obj_dir",
        "binary_name": "Valu_fsm",
        "timeout_sec": 5.0,
        "num_cycles":  8,
    },
    "output_dir": "./results",
}


# ── Agent factories ─────────────────────────────────────────────────────────

def make_adaptive_agent(meta, config):
    return Agent(
        meta=meta,
        epsilon=config.get("epsilon", 0.15),
        mutation_delta=config.get("mutation_delta", 8),
        novelty_budget=config.get("novelty_budget", 50),
        known_failure_types=config.get("known_failure_types", []),
    )


def make_random_agent(ports):
    class RandomAgent:
        name = "random"
        def generate(self):
            return {n: MutationStrategy.random_val(p) for n, p in ports.items()}
        def update(self, v, r): pass
        def summary(self): return {"strategy": "random"}
    return RandomAgent()


def make_biased_agent(ports):
    """
    Biased agent — human-guided heuristics, zero learning.
    Represents a skilled verification engineer's manual strategy.
    Upper bound for what domain-knowledge-free agents must beat.
    """
    class BiasedAgent:
        name = "biased"
        def generate(self):
            vec = {}
            for n, p in ports.items():
                if n.lower() == "b":
                    vec[n] = 0 if random.random() < 0.35 \
                             else random.randint(1, p.max_val)
                elif n.lower() == "op":
                    vec[n] = random.choice([2, 3, 3, 1])
                elif n.lower() == "a":
                    lo = int(p.max_val * 0.6)
                    vec[n] = random.randint(lo, p.max_val) \
                             if random.random() < 0.5 \
                             else random.randint(0, p.max_val)
                else:
                    vec[n] = MutationStrategy.random_val(p)
            return vec
        def update(self, v, r): pass
        def summary(self): return {"strategy": "biased"}
    return BiasedAgent()


# ── Core run loop ───────────────────────────────────────────────────────────

def run_one(config, agent_type, seed, runner, meta, label=None):
    random.seed(seed)
    ports       = meta.controllable_inputs()
    known_types = config.get("known_failure_types", [])
    output_dir  = Path(config["output_dir"])
    output_dir.mkdir(parents=True, exist_ok=True)

    run_label = label or f"{agent_type}_s{seed}"
    print(f"  [{agent_type:>8}] seed={seed}", end="", flush=True)

    if agent_type == "adaptive":
        agent = make_adaptive_agent(meta, config)
    elif agent_type == "biased":
        agent = make_biased_agent(ports)
    else:
        agent = make_random_agent(ports)

    analyzer = Analyzer(port_meta=ports, known_failure_types=known_types)
    logger   = RunLogger(
        run_name=run_label, config=config, seed=seed,
        db_path=str(output_dir / "runs.db"),
    )

    t0 = time.perf_counter()
    for ep in range(1, config["episodes"] + 1):
        vector = agent.generate()
        result = runner.run(vector)
        record = analyzer.process(vector, result)
        agent.update(vector, result)
        logger.log_episode({**record, "result": result})

    elapsed = time.perf_counter() - t0
    metrics = analyzer.final_metrics()
    metrics.update({
        "agent_type":    agent_type,
        "seed":          seed,
        "wall_time_sec": round(elapsed, 2),
    })
    if hasattr(agent, "summary"):
        metrics["agent_summary"] = agent.summary()

    logger.finalize(metrics)
    logger.export_json(str(output_dir / f"{run_label}.json"))

    print(f"  TTFF={str(metrics.get('time_to_first_failure','—')):>4}  "
          f"types={metrics['unique_failure_types']}  "
          f"fcov={metrics['failure_coverage']:.2f}  "
          f"div={metrics['diversity_score']:.3f}  ({elapsed:.1f}s)")
    return metrics


# ── Single-seed 3-way comparison ─────────────────────────────────────────────

def run_compare(config):
    seed   = config.get("seed", 42)
    runner = _compile(config)
    meta   = RTLParser().parse(config["design"])

    print(f"\n3-WAY COMPARISON  seed={seed}  episodes={config['episodes']}")
    print("="*72)
    results = {}
    for atype in ["random", "biased", "adaptive"]:
        results[atype] = run_one(config, atype, seed, runner, meta,
                                 label=f"{atype}_s{seed}")

    _print_3way(results)
    out = Path(config["output_dir"]) / f"compare_s{seed}.json"
    out.write_text(json.dumps(results, indent=2))
    print(f"Saved → {out}")
    return results


# ── Multi-seed publishable evaluation ────────────────────────────────────────

def run_multiseed(config):
    seeds  = config.get("seeds", [42, 123, 7, 99, 2024])
    runner = _compile(config)
    meta   = RTLParser().parse(config["design"])

    print(f"\nMULTI-SEED EVALUATION")
    print(f"Seeds: {seeds}  |  Episodes/run: {config['episodes']}  |  Total: {3*len(seeds)} runs")
    print("="*72)

    all_results = {"adaptive": [], "biased": [], "random": []}
    for seed in seeds:
        print(f"\n  -- Seed {seed} --")
        for atype in ["random", "biased", "adaptive"]:
            m = run_one(config, atype, seed, runner, meta, label=f"{atype}_s{seed}")
            all_results[atype].append(m)

    stats = _aggregate(all_results)
    out   = Path(config["output_dir"]) / "multiseed_stats.json"
    out.write_text(json.dumps(stats, indent=2))
    _print_stats(stats)
    print(f"\nStats saved → {out}")
    return stats


# ── Helpers ──────────────────────────────────────────────────────────────────

def _compile(config):
    vcfg = config.get("verilator", DEFAULT_CONFIG["verilator"])
    sim_config = SimConfig(
        design_file=config["design"],
        tb_file    =config["tb"],
        obj_dir    =vcfg.get("obj_dir",      "./obj_dir"),
        binary_name=vcfg.get("binary_name",  "Valu_fsm"),
        timeout_sec=vcfg.get("timeout_sec",  5.0),
        num_cycles =vcfg.get("num_cycles",   8),
    )
    runner = SimRunner(sim_config)
    print(f"Compiling {config['design']} ...")
    if not runner.compile():
        sys.exit("[ERROR] Compilation failed.")
    return runner


def _aggregate(all_results):
    import math
    keys = [
        "time_to_first_failure", "unique_failure_types",
        "failure_coverage", "diversity_score",
        "functional_coverage_pct", "total_failures",
        "avg_failure_depth", "failure_rate",
    ]
    stats = {}
    for atype, runs in all_results.items():
        stats[atype] = {}
        for k in keys:
            vals = [r[k] for r in runs if r.get(k) is not None]
            if not vals:
                stats[atype][k] = {"mean": None, "std": None, "n": 0}
                continue
            n    = len(vals)
            mu   = sum(vals) / n
            std  = math.sqrt(sum((v-mu)**2 for v in vals)/n) if n > 1 else 0.0
            stats[atype][k] = {"mean": round(mu,3), "std": round(std,3), "n": n}
        stats[atype]["_raw"] = all_results[atype]
    return stats


def _print_3way(results):
    keys = [
        ("TTFF (episodes)",      "time_to_first_failure"),
        ("Unique types",         "unique_failure_types"),
        ("Failure coverage",     "failure_coverage"),
        ("Diversity (entropy)",  "diversity_score"),
        ("Functional cov (%)",   "functional_coverage_pct"),
        ("Total failures",       "total_failures"),
    ]
    print(f"\n{'METRIC':<26} {'RANDOM':>12} {'BIASED':>12} {'ADAPTIVE':>12}")
    print("-"*64)
    for label, key in keys:
        rv = results.get("random",   {}).get(key, "N/A")
        bv = results.get("biased",   {}).get(key, "N/A")
        av = results.get("adaptive", {}).get(key, "N/A")
        fmt = lambda v: f"{v:.3f}" if isinstance(v, float) else str(v)
        print(f"  {label:<24} {fmt(rv):>12} {fmt(bv):>12} {fmt(av):>12}")
    print("="*64)


def _print_stats(stats):
    keys = [
        ("TTFF (episodes)",      "time_to_first_failure"),
        ("Unique types",         "unique_failure_types"),
        ("Failure coverage",     "failure_coverage"),
        ("Diversity (entropy)",  "diversity_score"),
        ("Functional cov (%)",   "functional_coverage_pct"),
    ]
    print(f"\n{'METRIC':<24} {'RANDOM (μ±σ)':>18} {'BIASED (μ±σ)':>18} {'ADAPTIVE (μ±σ)':>18}")
    print("-"*80)
    for label, key in keys:
        row = []
        for atype in ["random", "biased", "adaptive"]:
            s  = stats.get(atype, {}).get(key, {})
            mu = s.get("mean")
            sd = s.get("std")
            row.append("N/A" if mu is None else f"{mu:.2f}±{sd:.2f}")
        print(f"  {label:<22} {row[0]:>18} {row[1]:>18} {row[2]:>18}")
    print("="*80)


# ── CLI ──────────────────────────────────────────────────────────────────────

def main():
    ap = argparse.ArgumentParser(description="AAT-RTL")
    ap.add_argument("--config",    default="experiments/config.yaml")
    ap.add_argument("--compare",   action="store_true")
    ap.add_argument("--multiseed", action="store_true")
    ap.add_argument("--episodes",  type=int,   default=None)
    ap.add_argument("--seed",      type=int,   default=None)
    ap.add_argument("--epsilon",   type=float, default=None)
    args = ap.parse_args()

    cfg_path = Path(args.config)
    config   = yaml.safe_load(cfg_path.read_text()) if cfg_path.exists() \
               else copy.deepcopy(DEFAULT_CONFIG)

    if args.episodes: config["episodes"] = args.episodes
    if args.seed:     config["seed"]     = args.seed
    if args.epsilon:  config["epsilon"]  = args.epsilon

    if args.multiseed:
        run_multiseed(config)
    elif args.compare:
        run_compare(config)
    else:
        runner = _compile(config)
        meta   = RTLParser().parse(config["design"])
        run_one(config, "adaptive", config.get("seed", 42), runner, meta,
                label="adaptive_single")


if __name__ == "__main__":
    main()
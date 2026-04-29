"""
analyze_results.py
Aggregates multi-seed results from results/multiseed_stats.json and
individual run JSONs, prints a publication-ready summary table,
and runs basic statistical significance checks.

Run:
    python analyze_results.py
    python analyze_results.py --stats results/multiseed_stats.json
"""

import json
import math
import argparse
import glob
from pathlib import Path


# ── Load helpers ─────────────────────────────────────────────────────────────

def load_stats(path: str) -> dict:
    return json.loads(Path(path).read_text())


def load_individual_runs(results_dir: str, agent_type: str):
    """Load all per-seed run JSONs for a given agent type."""
    pattern = str(Path(results_dir) / f"{agent_type}_s*.json")
    files   = glob.glob(pattern)
    runs    = []
    for f in sorted(files):
        data = json.loads(Path(f).read_text())
        runs.append(data.get("metrics", data))  # handle both formats
    return runs


# ── Statistical tests ────────────────────────────────────────────────────────

def welch_t_test(a_vals, b_vals):
    """
    Welch's t-test (unequal variance).
    Returns (t_statistic, approx_p_value_string).
    Used to check if adaptive significantly outperforms random.
    Full scipy not required — uses built-in math only.
    """
    na, nb = len(a_vals), len(b_vals)
    if na < 2 or nb < 2:
        return None, "n<2"

    mean_a = sum(a_vals) / na
    mean_b = sum(b_vals) / nb
    var_a  = sum((v - mean_a)**2 for v in a_vals) / (na - 1)
    var_b  = sum((v - mean_b)**2 for v in b_vals) / (nb - 1)

    se = math.sqrt(var_a/na + var_b/nb)
    if se == 0:
        return 0.0, "se=0"

    t = (mean_a - mean_b) / se
    # Rough two-tailed p-value approximation using t-table cutoffs
    abs_t = abs(t)
    if abs_t > 3.355:  p_str = "p<0.01"
    elif abs_t > 2.015: p_str = "p<0.05"
    elif abs_t > 1.341: p_str = "p<0.20"
    else:               p_str = "p≥0.20 (NS)"

    return round(t, 3), p_str


def effect_size_d(a_vals, b_vals):
    """Cohen's d effect size."""
    na, nb = len(a_vals), len(b_vals)
    if na < 2 or nb < 2:
        return None
    mean_a = sum(a_vals) / na
    mean_b = sum(b_vals) / nb
    pooled_var = (
        (na-1) * sum((v-mean_a)**2 for v in a_vals)/(na-1) +
        (nb-1) * sum((v-mean_b)**2 for v in b_vals)/(nb-1)
    ) / (na + nb - 2)
    if pooled_var <= 0:
        return 0.0
    return round((mean_a - mean_b) / math.sqrt(pooled_var), 3)


# ── Report ───────────────────────────────────────────────────────────────────

METRICS = [
    ("time_to_first_failure",   "TTFF (episodes)",        "lower"),
    ("unique_failure_types",    "Unique failure types",   "higher"),
    ("failure_coverage",        "Failure coverage",       "higher"),
    ("diversity_score",         "Diversity (entropy)",    "higher"),
    ("functional_coverage_pct", "Functional cov (%)",     "higher"),
    ("avg_failure_depth",       "Avg failure depth",      "higher"),
    ("total_failures",          "Total failures found",   "higher"),
]


def print_full_report(stats: dict):
    agents = ["random", "biased", "adaptive"]

    print("\n" + "="*90)
    print("AAT-RTL — MULTI-SEED STATISTICAL EVALUATION REPORT")
    print("="*90)

    # Seeds used
    n_seeds = stats.get("adaptive", {}).get("failure_coverage", {}).get("n", "?")
    print(f"Seeds evaluated per agent: {n_seeds}\n")

    # Main metrics table
    print(f"{'METRIC':<26} {'RANDOM':>18} {'BIASED':>18} {'ADAPTIVE':>18}")
    print("-"*82)
    for key, label, direction in METRICS:
        row = []
        for a in agents:
            s  = stats.get(a, {}).get(key, {})
            mu = s.get("mean")
            sd = s.get("std")
            row.append("N/A" if mu is None else f"{mu:.2f} ± {sd:.2f}")
        print(f"  {label:<24} {row[0]:>18} {row[1]:>18} {row[2]:>18}")
    print("="*90)

    # Statistical significance: adaptive vs random
    print("\nSTATISTICAL SIGNIFICANCE: Adaptive vs Random (Welch t-test)")
    print("-"*70)
    print(f"  {'METRIC':<30} {'t-stat':>8} {'p-value':>14} {'Cohen d':>10} {'Winner':>10}")
    print("  " + "-"*66)

    for key, label, direction in METRICS:
        a_raw = [r.get(key) for r in stats.get("adaptive", {}).get("_raw", []) if r.get(key) is not None]
        r_raw = [r.get(key) for r in stats.get("random",   {}).get("_raw", []) if r.get(key) is not None]

        if not a_raw or not r_raw:
            continue

        t, p = welch_t_test(a_raw, r_raw)
        d    = effect_size_d(a_raw, r_raw)

        a_mean = sum(a_raw)/len(a_raw)
        r_mean = sum(r_raw)/len(r_raw)

        if direction == "higher":
            winner = "ADAPTIVE" if a_mean > r_mean else "RANDOM"
        else:
            winner = "ADAPTIVE" if a_mean < r_mean else "RANDOM"

        print(f"  {label:<30} {str(t):>8} {str(p):>14} {str(d):>10} {winner:>10}")

    print("-"*70)

    # Adaptive vs Biased
    print("\nSTATISTICAL SIGNIFICANCE: Adaptive vs Biased (Welch t-test)")
    print("-"*70)
    print(f"  {'METRIC':<30} {'t-stat':>8} {'p-value':>14} {'Cohen d':>10} {'Winner':>10}")
    print("  " + "-"*66)

    for key, label, direction in METRICS:
        a_raw = [r.get(key) for r in stats.get("adaptive", {}).get("_raw", []) if r.get(key) is not None]
        b_raw = [r.get(key) for r in stats.get("biased",   {}).get("_raw", []) if r.get(key) is not None]

        if not a_raw or not b_raw:
            continue

        t, p = welch_t_test(a_raw, b_raw)
        d    = effect_size_d(a_raw, b_raw)
        a_mean = sum(a_raw)/len(a_raw)
        b_mean = sum(b_raw)/len(b_raw)

        if direction == "higher":
            winner = "ADAPTIVE" if a_mean > b_mean else "BIASED"
        else:
            winner = "ADAPTIVE" if a_mean < b_mean else "BIASED"

        print(f"  {label:<30} {str(t):>8} {str(p):>14} {str(d):>10} {winner:>10}")

    print("="*90)

    # Key findings
    print("\nKEY FINDINGS (for paper abstract):")
    for key, label, direction in [
        ("time_to_first_failure", "TTFF", "lower"),
        ("failure_coverage",      "failure coverage", "higher"),
        ("diversity_score",       "diversity", "higher"),
    ]:
        a_s  = stats.get("adaptive", {}).get(key, {})
        r_s  = stats.get("random",   {}).get(key, {})
        a_mu = a_s.get("mean")
        r_mu = r_s.get("mean")
        if a_mu and r_mu and r_mu != 0:
            ratio = r_mu / a_mu if direction == "lower" else a_mu / r_mu
            print(f"  • {label}: adaptive is {ratio:.1f}× better than random")
    print()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--stats",   default="results/multiseed_stats.json")
    ap.add_argument("--results", default="results")
    args = ap.parse_args()

    stats_path = Path(args.stats)
    if not stats_path.exists():
        print(f"[Error] {stats_path} not found.")
        print("Run:  python main.py --multiseed   first to generate results.")
        return

    stats = load_stats(str(stats_path))
    print_full_report(stats)


if __name__ == "__main__":
    main()
"""
eval/plot_metrics.py
Generate all plots for the paper from saved run JSON files.

Produces:
  1. ttff_comparison.png       — time-to-first-failure: agent vs random
  2. failure_discovery.png     — cumulative unique failure types over episodes
  3. diversity_curve.png       — Shannon entropy of failure distribution over time
  4. coverage_curve.png        — functional coverage % over episodes
  5. strategy_pie.png          — agent strategy distribution (how often each strategy fired)
  6. summary_table.png         — final metrics comparison table (goes in paper)

Run:
    python eval/plot_metrics.py --run results/adaptive_agent_run.json \
                                --baseline results/random_baseline_run.json
"""

import argparse
import json
import sys
from pathlib import Path

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

# --- Style -------------------------------------------------------
plt.rcParams.update({
    "font.family": "serif",
    "font.size": 11,
    "axes.spines.top": False,
    "axes.spines.right": False,
    "axes.grid": True,
    "grid.alpha": 0.3,
    "figure.dpi": 150,
})

AGENT_COLOR    = "#1D9E75"
RANDOM_COLOR   = "#BA7517"
ACCENT_COLOR   = "#534AB7"

# -----------------------------------------------------------------

def load_run(path: str) -> dict:
    return json.loads(Path(path).read_text())


def episodes_to_series(run: dict, key: str):
    """Extract a per-episode time series from the run's episode log."""
    eps  = [e["episode"] for e in run["episodes"]]
    vals = [e.get(key, 0) for e in run["episodes"]]
    return eps, vals


def cumulative_unique_types(run: dict):
    seen = set()
    eps, types = [], []
    for e in run["episodes"]:
        if e.get("failure") and e.get("ftype"):
            seen.add(e["ftype"])
        eps.append(e["episode"])
        types.append(len(seen))
    return eps, types


def plot_ttff(agent_run, random_run, out_dir):
    fig, ax = plt.subplots(figsize=(7, 4))

    ttff_a = agent_run["metrics"].get("time_to_first_failure")
    ttff_r = random_run["metrics"].get("time_to_first_failure")

    bars = ax.bar(
        ["Adaptive Agent", "Random Baseline"],
        [ttff_a or 0, ttff_r or 0],
        color=[AGENT_COLOR, RANDOM_COLOR],
        width=0.45,
        edgecolor="white",
        linewidth=0.5,
    )
    for bar, val in zip(bars, [ttff_a, ttff_r]):
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 2,
                str(val), ha='center', va='bottom', fontweight='bold')

    ax.set_ylabel("Episode #")
    ax.set_title("Time to First Failure")
    speedup = (ttff_r or 0) / max(ttff_a or 1, 1)
    ax.text(0.98, 0.95, f"{speedup:.1f}× speedup", transform=ax.transAxes,
            ha='right', va='top', color=AGENT_COLOR, fontweight='bold', fontsize=10)

    fig.tight_layout()
    fig.savefig(out_dir / "ttff_comparison.png")
    print(f"  Saved ttff_comparison.png")
    plt.close(fig)


def plot_discovery_curve(agent_run, random_run, out_dir):
    fig, ax = plt.subplots(figsize=(7, 4))

    for run, color, label in [
        (agent_run,  AGENT_COLOR,  "Adaptive Agent"),
        (random_run, RANDOM_COLOR, "Random Baseline"),
    ]:
        eps, types = cumulative_unique_types(run)
        ax.plot(eps, types, color=color, label=label, linewidth=1.8)

    ax.set_xlabel("Episode")
    ax.set_ylabel("Unique Failure Types Found")
    ax.set_title("Cumulative Failure Type Discovery")
    ax.legend()
    fig.tight_layout()
    fig.savefig(out_dir / "failure_discovery.png")
    print(f"  Saved failure_discovery.png")
    plt.close(fig)


def plot_diversity(agent_run, random_run, out_dir):
    fig, ax = plt.subplots(figsize=(7, 4))

    for run, color, label in [
        (agent_run,  AGENT_COLOR,  "Adaptive Agent"),
        (random_run, RANDOM_COLOR, "Random Baseline"),
    ]:
        eps, div = episodes_to_series(run, "diversity")
        ax.plot(eps, div, color=color, label=label, linewidth=1.8)

    ax.set_xlabel("Episode")
    ax.set_ylabel("Shannon Entropy (bits)")
    ax.set_title("Failure Diversity Over Time")
    ax.legend()
    fig.tight_layout()
    fig.savefig(out_dir / "diversity_curve.png")
    print(f"  Saved diversity_curve.png")
    plt.close(fig)


def plot_coverage(agent_run, random_run, out_dir):
    fig, ax = plt.subplots(figsize=(7, 4))

    for run, color, label in [
        (agent_run,  AGENT_COLOR,  "Adaptive Agent"),
        (random_run, RANDOM_COLOR, "Random Baseline"),
    ]:
        eps, cov = episodes_to_series(run, "coverage_pct")
        ax.plot(eps, cov, color=color, label=label, linewidth=1.8)

    ax.set_ylabel("Functional Coverage (%)")
    ax.set_xlabel("Episode")
    ax.set_title("Functional Coverage Convergence")
    ax.set_ylim(0, 105)
    ax.legend()
    fig.tight_layout()
    fig.savefig(out_dir / "coverage_curve.png")
    print(f"  Saved coverage_curve.png")
    plt.close(fig)


def plot_strategy_pie(agent_run, out_dir):
    strat = agent_run["metrics"].get("agent_summary", {}).get("strategy_distribution", {})
    if not strat:
        return

    labels = list(strat.keys())
    sizes  = list(strat.values())
    colors = plt.cm.Set2(np.linspace(0, 0.8, len(labels)))

    fig, ax = plt.subplots(figsize=(6, 5))
    wedges, texts, autotexts = ax.pie(
        sizes, labels=None, autopct="%1.0f%%",
        colors=colors, startangle=140,
        wedgeprops={"edgecolor": "white", "linewidth": 1},
    )
    ax.legend(wedges, labels, loc="lower right", fontsize=9)
    ax.set_title("Agent Strategy Distribution")
    fig.tight_layout()
    fig.savefig(out_dir / "strategy_pie.png")
    print(f"  Saved strategy_pie.png")
    plt.close(fig)


def plot_summary_table(agent_run, random_run, out_dir):
    am = agent_run["metrics"]
    rm = random_run["metrics"]

    rows = [
        ("Time to first failure (ep)",  am.get("time_to_first_failure", "N/A"),
                                        rm.get("time_to_first_failure", "N/A")),
        ("Unique failure types",        am["unique_failure_types"],
                                        rm["unique_failure_types"]),
        ("Failure coverage",            f"{am['failure_coverage']:.2f}",
                                        f"{rm['failure_coverage']:.2f}"),
        ("Diversity score (entropy)",   f"{am['diversity_score']:.3f}",
                                        f"{rm['diversity_score']:.3f}"),
        ("Functional coverage (%)",     f"{am['functional_coverage_pct']:.1f}",
                                        f"{rm['functional_coverage_pct']:.1f}"),
        ("Total failures found",        am["total_failures"],
                                        rm["total_failures"]),
    ]

    fig, ax = plt.subplots(figsize=(8, 3.2))
    ax.axis('off')

    col_labels = ["Metric", "Adaptive Agent", "Random Baseline"]
    cell_text  = [[r[0], str(r[1]), str(r[2])] for r in rows]
    cell_colors = [
        ["white"] + (
            [AGENT_COLOR + "33", RANDOM_COLOR + "33"]
        )
        for _ in rows
    ]

    table = ax.table(
        cellText=cell_text,
        colLabels=col_labels,
        cellLoc='center',
        loc='center',
        cellColours=cell_colors,
    )
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1, 1.6)

    # Header styling
    for j in range(3):
        table[(0, j)].set_facecolor("#2C2C2A")
        table[(0, j)].set_text_props(color="white", fontweight="bold")

    ax.set_title("Evaluation Metrics: Adaptive Agent vs. Random Baseline",
                 fontweight="bold", pad=20)
    fig.tight_layout()
    fig.savefig(out_dir / "summary_table.png", bbox_inches="tight")
    print(f"  Saved summary_table.png")
    plt.close(fig)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--run",      required=True, help="Path to adaptive agent run JSON")
    parser.add_argument("--baseline", required=True, help="Path to random baseline run JSON")
    parser.add_argument("--out",      default="results/plots", help="Output directory")
    args = parser.parse_args()

    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    print(f"Loading runs...")
    agent_run  = load_run(args.run)
    random_run = load_run(args.baseline)

    print("Generating plots...")
    plot_ttff(agent_run, random_run, out_dir)
    plot_discovery_curve(agent_run, random_run, out_dir)
    plot_diversity(agent_run, random_run, out_dir)
    plot_coverage(agent_run, random_run, out_dir)
    plot_strategy_pie(agent_run, out_dir)
    plot_summary_table(agent_run, random_run, out_dir)

    print(f"\nAll plots saved to {out_dir}/")


if __name__ == "__main__":
    main()
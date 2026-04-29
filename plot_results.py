"""
plot_results.py
Generate all publication figures from real multi-seed result data.

Run:
    python plot_results.py                              # uses results/multiseed_stats.json
    python plot_results.py --stats results/multiseed_stats.json --out results/plots

Produces 6 figures:
    fig1_ttff_bar.png          — TTFF bar chart with error bars (Table 1 companion)
    fig2_discovery_curve.png   — cumulative unique types over episodes (per-seed lines)
    fig3_diversity_curve.png   — Shannon entropy over episodes
    fig4_coverage_curve.png    — functional coverage convergence
    fig5_strategy_pie.png      — adaptive agent strategy breakdown
    fig6_summary_table.png     — full metrics table (paper Table 1)
"""

import json
import glob
import argparse
import math
from pathlib import Path
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

# ── Style ─────────────────────────────────────────────────────────────────────
plt.rcParams.update({
    "font.family":        "serif",
    "font.size":          11,
    "axes.spines.top":    False,
    "axes.spines.right":  False,
    "axes.grid":          True,
    "grid.alpha":         0.3,
    "grid.linewidth":     0.5,
    "figure.dpi":         160,
    "savefig.dpi":        200,
    "savefig.bbox":       "tight",
})

COLORS = {
    "adaptive": "#1D9E75",
    "biased":   "#534AB7",
    "random":   "#BA7517",
}
LABELS = {
    "adaptive": "Adaptive Agent (ours)",
    "biased":   "Biased (domain knowledge)",
    "random":   "Random Baseline",
}
AGENTS = ["random", "biased", "adaptive"]


# ── Data loading ──────────────────────────────────────────────────────────────

def load_stats(path):
    return json.loads(Path(path).read_text())


def load_episode_histories(results_dir, agent_type):
    """Load per-episode time series for all seeds of a given agent."""
    pattern = str(Path(results_dir) / f"{agent_type}_s*.json")
    histories = []
    for f in sorted(glob.glob(pattern)):
        data = json.loads(Path(f).read_text())
        eps  = data.get("episodes", [])
        histories.append(eps)
    return histories


def extract_series(histories, key):
    """
    Extract a time series [key per episode] from all seed histories.
    Returns list of (episode_array, value_array) per seed.
    """
    series = []
    for eps in histories:
        x = [e["episode"] for e in eps]
        y = [e.get(key, 0) or 0 for e in eps]
        series.append((np.array(x), np.array(y)))
    return series


def mean_std_series(series):
    """Compute mean ± std arrays across seeds, aligned by episode index."""
    if not series:
        return np.array([]), np.array([]), np.array([])
    min_len = min(len(y) for _, y in series)
    mat = np.stack([y[:min_len] for _, y in series])
    x   = series[0][0][:min_len]
    return x, mat.mean(axis=0), mat.std(axis=0)


def cumulative_types_series(histories):
    """Build cumulative unique failure type count per episode for each seed."""
    series = []
    for eps in histories:
        seen = set()
        y    = []
        for e in eps:
            if e.get("failure") and e.get("ftype"):
                seen.add(e["ftype"])
            y.append(len(seen))
        series.append((np.arange(1, len(y)+1), np.array(y)))
    return series


# ── Figure 1: TTFF bar chart with error bars ─────────────────────────────────

def fig1_ttff(stats, out_dir):
    fig, ax = plt.subplots(figsize=(7, 4.5))

    agents = AGENTS
    means  = [stats[a].get("time_to_first_failure", {}).get("mean") or 0 for a in agents]
    stds   = [stats[a].get("time_to_first_failure", {}).get("std")  or 0 for a in agents]
    colors = [COLORS[a] for a in agents]
    xlabels= [LABELS[a] for a in agents]

    bars = ax.bar(xlabels, means, yerr=stds, color=colors,
                  width=0.5, capsize=6, edgecolor="white",
                  error_kw={"linewidth": 1.5, "ecolor": "black"})

    for bar, mu, sd in zip(bars, means, stds):
        ax.text(bar.get_x() + bar.get_width()/2,
                bar.get_height() + sd + 3,
                f"{mu:.0f}", ha="center", va="bottom",
                fontsize=10, fontweight="bold")

    # Speedup annotation
    r_mu = means[0]  # random
    a_mu = means[2]  # adaptive
    if a_mu and a_mu > 0:
        ax.annotate(f"{r_mu/a_mu:.1f}× faster",
                    xy=(2, a_mu), xytext=(1.5, a_mu + stds[0] + 30),
                    arrowprops=dict(arrowstyle="->", color=COLORS["adaptive"]),
                    fontsize=10, color=COLORS["adaptive"], fontweight="bold")

    ax.set_ylabel("Episode number")
    ax.set_title("Time to First Failure (TTFF)\nmean ± std across seeds", fontsize=12)
    ax.set_ylim(0, max(means) * 1.35 if max(means) > 0 else 100)
    plt.xticks(fontsize=9)
    fig.tight_layout()
    fig.savefig(out_dir / "fig1_ttff_bar.png")
    plt.close(fig)
    print("  fig1_ttff_bar.png")


# ── Figure 2: Cumulative failure type discovery ───────────────────────────────

def fig2_discovery(results_dir, out_dir):
    fig, ax = plt.subplots(figsize=(8, 4.5))

    for atype in AGENTS:
        histories = load_episode_histories(results_dir, atype)
        if not histories:
            continue
        series = cumulative_types_series(histories)
        x, mu, sd = mean_std_series(series)
        if len(x) == 0:
            continue
        ax.plot(x, mu, color=COLORS[atype], label=LABELS[atype],
                linewidth=2.0)
        ax.fill_between(x, mu - sd, mu + sd,
                        color=COLORS[atype], alpha=0.15)

    ax.set_xlabel("Episode")
    ax.set_ylabel("Cumulative unique failure types")
    ax.set_title("Failure Type Discovery Curve\n(mean ± std across seeds)")
    ax.legend(fontsize=9)
    ax.yaxis.set_major_locator(plt.MaxNLocator(integer=True))
    fig.tight_layout()
    fig.savefig(out_dir / "fig2_discovery_curve.png")
    plt.close(fig)
    print("  fig2_discovery_curve.png")


# ── Figure 3: Shannon entropy (diversity) over time ──────────────────────────

def fig3_diversity(results_dir, out_dir):
    fig, ax = plt.subplots(figsize=(8, 4.5))

    for atype in AGENTS:
        histories = load_episode_histories(results_dir, atype)
        if not histories:
            continue
        series    = extract_series(histories, "diversity")
        x, mu, sd = mean_std_series(series)
        if len(x) == 0:
            continue
        ax.plot(x, mu, color=COLORS[atype], label=LABELS[atype], linewidth=2.0)
        ax.fill_between(x, mu - sd, mu + sd, color=COLORS[atype], alpha=0.15)

    ax.set_xlabel("Episode")
    ax.set_ylabel("Shannon Entropy (bits)")
    ax.set_title("Failure Diversity Over Time\n(mean ± std across seeds)")
    ax.legend(fontsize=9)
    fig.tight_layout()
    fig.savefig(out_dir / "fig3_diversity_curve.png")
    plt.close(fig)
    print("  fig3_diversity_curve.png")


# ── Figure 4: Functional coverage convergence ─────────────────────────────────

def fig4_coverage(results_dir, out_dir):
    fig, ax = plt.subplots(figsize=(8, 4.5))

    for atype in AGENTS:
        histories  = load_episode_histories(results_dir, atype)
        if not histories:
            continue
        series     = extract_series(histories, "coverage_pct")
        x, mu, sd  = mean_std_series(series)
        if len(x) == 0:
            continue
        ax.plot(x, mu, color=COLORS[atype], label=LABELS[atype], linewidth=2.0)
        ax.fill_between(x, np.clip(mu-sd, 0, 100), np.clip(mu+sd, 0, 100),
                        color=COLORS[atype], alpha=0.15)

    ax.set_xlabel("Episode")
    ax.set_ylabel("Functional Coverage (%)")
    ax.set_title("Functional Coverage Convergence\n(mean ± std across seeds)")
    ax.set_ylim(0, 105)
    ax.legend(fontsize=9)
    fig.tight_layout()
    fig.savefig(out_dir / "fig4_coverage_curve.png")
    plt.close(fig)
    print("  fig4_coverage_curve.png")


# ── Figure 5: Strategy distribution pie ───────────────────────────────────────

def fig5_strategy(results_dir, out_dir):
    """Aggregate strategy counts across all adaptive seeds."""
    pattern = str(Path(results_dir) / "adaptive_s*.json")
    files   = glob.glob(pattern)
    if not files:
        print("  fig5_strategy_pie.png — skipped (no adaptive runs found)")
        return

    agg = defaultdict(int)
    for f in files:
        data = json.loads(Path(f).read_text())
        sd   = (data.get("metrics") or data).get("agent_summary", {}).get("strategy_distribution", {})
        for k, v in sd.items():
            agg[k] += v

    if not agg:
        print("  fig5_strategy_pie.png — skipped (no strategy data)")
        return

    # Simplify strategy labels
    simplified = defaultdict(int)
    for k, v in agg.items():
        if k.startswith("novelty:"):    simplified["Novelty forcing"] += v
        elif k.startswith("mutation:"): simplified["UCB mutation"] += v
        elif k.startswith("hypothesis:"):simplified["Hypothesis-guided"] += v
        elif k == "boundary":           simplified["Boundary sweep"] += v
        else:                           simplified["Random (ε)"] += v

    labels = list(simplified.keys())
    sizes  = list(simplified.values())
    colors = plt.cm.Set2(np.linspace(0, 0.85, len(labels)))

    fig, ax = plt.subplots(figsize=(6.5, 5))
    wedges, _, autotexts = ax.pie(
        sizes, labels=None, autopct="%1.1f%%",
        colors=colors, startangle=140,
        wedgeprops={"edgecolor": "white", "linewidth": 1.2},
        pctdistance=0.8,
    )
    for at in autotexts:
        at.set_fontsize(9)
    ax.legend(wedges, labels, loc="lower right", fontsize=9,
              framealpha=0.8)
    ax.set_title("Adaptive Agent — Strategy Distribution\n(aggregated across seeds)")
    fig.tight_layout()
    fig.savefig(out_dir / "fig5_strategy_pie.png")
    plt.close(fig)
    print("  fig5_strategy_pie.png")


# ── Figure 6: Summary metrics table ──────────────────────────────────────────

def fig6_table(stats, out_dir):
    metrics = [
        ("TTFF (episodes)",       "time_to_first_failure"),
        ("Unique failure types",  "unique_failure_types"),
        ("Failure coverage",      "failure_coverage"),
        ("Diversity (entropy)",   "diversity_score"),
        ("Functional cov (%)",    "functional_coverage_pct"),
        ("Avg failure depth",     "avg_failure_depth"),
        ("Total failures",        "total_failures"),
    ]

    col_labels = ["Metric", "Random", "Biased", "Adaptive (ours)"]
    cell_text  = []
    for label, key in metrics:
        row = [label]
        for atype in ["random", "biased", "adaptive"]:
            s  = stats.get(atype, {}).get(key, {})
            mu = s.get("mean")
            sd = s.get("std")
            row.append("N/A" if mu is None else f"{mu:.2f}\n±{sd:.2f}")
        cell_text.append(row)

    fig, ax = plt.subplots(figsize=(10, 4))
    ax.axis("off")

    tbl = ax.table(
        cellText=cell_text,
        colLabels=col_labels,
        cellLoc="center", loc="center",
    )
    tbl.auto_set_font_size(False)
    tbl.set_fontsize(9.5)
    tbl.scale(1, 1.8)

    # Header row styling
    for j in range(4):
        cell = tbl[(0, j)]
        cell.set_facecolor("#2C2C2A")
        cell.set_text_props(color="white", fontweight="bold")

    # Highlight adaptive column
    for i in range(1, len(metrics)+1):
        tbl[(i, 3)].set_facecolor("#E1F5EE")

    # Alternating rows
    for i in range(1, len(metrics)+1):
        for j in range(3):
            if i % 2 == 0:
                tbl[(i, j)].set_facecolor("#F5F5F2")

    ax.set_title(
        "Table 1 — Evaluation Metrics: Adaptive Agent vs. Baselines\n"
        f"(mean ± std, N={stats.get('adaptive',{}).get('failure_coverage',{}).get('n','?')} seeds)",
        fontweight="bold", fontsize=11, pad=20,
    )
    fig.tight_layout()
    fig.savefig(out_dir / "fig6_summary_table.png")
    plt.close(fig)
    print("  fig6_summary_table.png")


# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--stats",   default="results/multiseed_stats.json")
    ap.add_argument("--results", default="results")
    ap.add_argument("--out",     default="results/plots")
    args = ap.parse_args()

    stats_path = Path(args.stats)
    if not stats_path.exists():
        print(f"[Error] {stats_path} not found.")
        print("Run:  python main.py --multiseed   first.")
        return

    stats     = load_stats(str(stats_path))
    out_dir   = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    print(f"Generating plots → {out_dir}/")
    fig1_ttff(stats, out_dir)
    fig2_discovery(args.results, out_dir)
    fig3_diversity(args.results, out_dir)
    fig4_coverage(args.results, out_dir)
    fig5_strategy(args.results, out_dir)
    fig6_table(stats, out_dir)
    print(f"\nDone — {len(list(out_dir.glob('*.png')))} figures saved.")


if __name__ == "__main__":
    main()
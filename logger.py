"""
logger.py
SQLite-backed episode logger.

Stores every test vector + result for:
  - Post-run analysis and plotting
  - Reproducibility (seed + full log → reproduce any run)
  - Comparison across runs (random baseline vs. our agent)
"""

import sqlite3
import json
import time
import os
from pathlib import Path
from typing import Optional, List, Dict


class RunLogger:
    """
    Manages a SQLite database with schema:

    runs(id, name, config_json, start_time, end_time, seed, metrics_json)
    episodes(run_id, episode, vector_json, result_json, failure, ftype,
             coverage_pct, diversity, sim_time_ms, timestamp)
    """

    DB_PATH = "./results/runs.db"

    def __init__(self, run_name: str, config: dict, seed: Optional[int] = None,
                 db_path: Optional[str] = None):
        self.run_name = run_name
        self.config = config
        self.seed = seed
        self.db_path = db_path or self.DB_PATH
        Path(self.db_path).parent.mkdir(parents=True, exist_ok=True)

        self.conn = sqlite3.connect(self.db_path)
        self._init_schema()
        self.run_id = self._create_run()

    def _init_schema(self):
        c = self.conn.cursor()
        c.executescript("""
            CREATE TABLE IF NOT EXISTS runs (
                id          INTEGER PRIMARY KEY AUTOINCREMENT,
                name        TEXT,
                config      TEXT,
                seed        INTEGER,
                start_time  REAL,
                end_time    REAL,
                metrics     TEXT
            );
            CREATE TABLE IF NOT EXISTS episodes (
                run_id      INTEGER,
                episode     INTEGER,
                vector      TEXT,
                result      TEXT,
                failure     INTEGER,
                ftype       TEXT,
                coverage    REAL,
                diversity   REAL,
                sim_ms      REAL,
                ts          REAL,
                FOREIGN KEY(run_id) REFERENCES runs(id)
            );
        """)
        self.conn.commit()

    def _create_run(self) -> int:
        c = self.conn.cursor()
        c.execute(
            "INSERT INTO runs(name, config, seed, start_time) VALUES (?,?,?,?)",
            (self.run_name, json.dumps(self.config), self.seed, time.time())
        )
        self.conn.commit()
        return c.lastrowid

    def log_episode(self, record: dict):
        c = self.conn.cursor()
        c.execute("""
            INSERT INTO episodes
            (run_id, episode, vector, result, failure, ftype, coverage, diversity, sim_ms, ts)
            VALUES (?,?,?,?,?,?,?,?,?,?)
        """, (
            self.run_id,
            record.get("episode"),
            json.dumps(record.get("vector", {})),
            json.dumps(record.get("result", {})),
            1 if record.get("failure") else 0,
            record.get("type"),
            record.get("coverage_pct", 0),
            record.get("diversity", 0),
            record.get("sim_time_ms", 0),
            time.time(),
        ))
        self.conn.commit()

    def finalize(self, metrics: dict):
        c = self.conn.cursor()
        c.execute(
            "UPDATE runs SET end_time=?, metrics=? WHERE id=?",
            (time.time(), json.dumps(metrics), self.run_id)
        )
        self.conn.commit()
        self.conn.close()

    def export_json(self, out_path: str):
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row
        c = conn.cursor()

        run = dict(c.execute("SELECT * FROM runs WHERE id=?", (self.run_id,)).fetchone())
        episodes = [dict(r) for r in c.execute(
            "SELECT * FROM episodes WHERE run_id=? ORDER BY episode", (self.run_id,)
        ).fetchall()]

        for ep in episodes:
            ep["vector"] = json.loads(ep["vector"])
            ep["result"] = json.loads(ep["result"])

        run["config"] = json.loads(run["config"])
        run["metrics"] = json.loads(run["metrics"] or "{}")
        run["episodes"] = episodes

        Path(out_path).write_text(json.dumps(run, indent=2))
        conn.close()
        print(f"[Logger] Exported run to {out_path}")


def load_all_runs(db_path: str = RunLogger.DB_PATH) -> List[Dict]:
    """Load summary of all runs from the database — used by plot_metrics.py."""
    conn = sqlite3.connect(db_path)
    conn.row_factory = sqlite3.Row
    c = conn.cursor()
    rows = c.execute("SELECT id, name, seed, start_time, metrics FROM runs").fetchall()
    conn.close()
    result = []
    for r in rows:
        d = dict(r)
        d["metrics"] = json.loads(d.get("metrics") or "{}")
        result.append(d)
    return result
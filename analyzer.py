import math
from collections import Counter


class Analyzer:
    def __init__(self, port_meta, known_failure_types=None):
        self.port_meta = port_meta
        self.known_failure_types = known_failure_types or []

        self.total_episodes = 0
        self.total_failures = 0

        self.failure_counts = Counter()
        self.failure_types_seen = set()

        self.first_failure_time = None
        self.time_to_each_type = {}

        self.history = []

    # ---------------------------------------------------------
    # MAIN PROCESS FUNCTION
    # ---------------------------------------------------------
    def process(self, vector, result):
        self.total_episodes += 1

        failure_type = self._detect_failure(result)

        record = {
            "vector": vector,
            "result": result,
            "failure": failure_type is not None,
            "type": failure_type,
            "event": ""
        }

        if failure_type:
            self.total_failures += 1
            self.failure_counts[failure_type] += 1

            if self.first_failure_time is None:
                self.first_failure_time = self.total_episodes

            if failure_type not in self.failure_types_seen:
                self.failure_types_seen.add(failure_type)
                self.time_to_each_type[failure_type] = self.total_episodes
                record["event"] = f"NEW_TYPE:{failure_type}"

        self.history.append(record)
        return record

    # ---------------------------------------------------------
    # GENERIC FAILURE DETECTOR
    # ---------------------------------------------------------
    def _detect_failure(self, result):
        """
        Detect failures generically from result dict.
        """

        # 1. Explicit failure flag
        if result.get("failure"):
            return result.get("type", "generic_failure")

        # 2. Any signal starting with err_
        for key, val in result.items():
            if key.startswith("err_") and int(val) == 1:
                return key

        # 3. Invalid outputs (common pattern)
        if "valid" in result and int(result["valid"]) == 0:
            return "invalid_output"

        if "ready" in result and int(result["ready"]) == 0:
            return "not_ready"

        # 4. Heuristic: suspicious zero output
        if "y" in result:
            y = int(result["y"])
            if y == 0 and self.total_episodes > 10:
                return "zero_output_suspicious"

        return None

    # ---------------------------------------------------------
    # FINAL METRICS
    # ---------------------------------------------------------
    def final_metrics(self):
        unique_types = len(self.failure_types_seen)

        failure_rate = (
            self.total_failures / self.total_episodes
            if self.total_episodes > 0 else 0
        )

        # entropy (diversity)
        diversity = self._compute_entropy()

        # coverage
        coverage = (
            unique_types / max(len(self.known_failure_types), 1)
            if self.known_failure_types else unique_types
        )

        return {
            "total_episodes": self.total_episodes,
            "total_failures": self.total_failures,
            "failure_rate": round(failure_rate, 4),
            "unique_failure_types": unique_types,
            "failure_types_found": list(self.failure_types_seen),
            "time_to_first_failure": self.first_failure_time,
            "time_to_each_type": self.time_to_each_type,
            "failure_coverage": round(coverage, 4),
            "diversity_score": round(diversity, 4),
            "failure_counts": dict(self.failure_counts),
        }

    # ---------------------------------------------------------
    # ENTROPY (DIVERSITY)
    # ---------------------------------------------------------
    def _compute_entropy(self):
        total = sum(self.failure_counts.values())
        if total == 0:
            return 0

        entropy = 0
        for count in self.failure_counts.values():
            p = count / total
            entropy -= p * math.log(p + 1e-9)

        return entropy

    # ---------------------------------------------------------
    # PRINT SUMMARY
    # ---------------------------------------------------------
    def print_summary(self):
        m = self.final_metrics()

        print("\n" + "=" * 60)
        print("ANALYZER SUMMARY")
        print("=" * 60)

        for k, v in m.items():
            print(f"{k:35s} {v}")

        print("=" * 60)
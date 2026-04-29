"""
agent.py
Multi-strategy adaptive test generation agent.

Strategy stack (evaluated in order):
  1. Novelty-forced exploration  — guarantees unseen failure modes are sought
  2. UCB-guided failure targeting — targets under-represented failures using
                                    Upper Confidence Bound to balance
                                    exploitation vs. exploration of failure space
  3. Neighbourhood mutation      — perturbs a known-failing vector by ±delta
  4. Boundary sweep              — systematically tests extreme values
  5. Pure random fallback        — epsilon-probability uniform random

This addresses the key mode-collapse problem from v1 while being
measurably better than random, which is the core publishable claim.
"""

import random
import math
import numpy as np
from collections import defaultdict
from typing import Dict, List, Optional, Tuple
from rtl_parser import DesignMeta, Port


class MutationStrategy:
    """Namespace for individual mutation operators."""

    @staticmethod
    def bit_flip(val: int, width: int) -> int:
        bit = random.randint(0, width - 1)
        return val ^ (1 << bit)

    @staticmethod
    def boundary(port: Port) -> int:
        return random.choice([port.min_val, port.max_val, port.max_val // 2,
                               port.max_val // 2 + 1, 0, 1])

    @staticmethod
    def neighbour(val: int, port: Port, delta: int = 8) -> int:
        noise = random.randint(-delta, delta)
        return max(port.min_val, min(port.max_val, val + noise))

    @staticmethod
    def random_val(port: Port) -> int:
        return random.randint(port.min_val, port.max_val)


class FailureMemory:
    """
    Stores failure-inducing vectors, indexed by failure type.
    Provides weighted sampling biased toward rare types.
    """

    def __init__(self, capacity: int = 500):
        self.capacity = capacity
        self.by_type: Dict[str, List[dict]] = defaultdict(list)
        self.all_failures: List[Tuple[dict, str]] = []
        self.counts: Dict[str, int] = defaultdict(int)

    def add(self, vector: dict, ftype: str):
        self.counts[ftype] += 1
        if len(self.by_type[ftype]) < self.capacity:
            self.by_type[ftype].append(vector)
        else:
            # Reservoir replacement
            idx = random.randint(0, self.counts[ftype] - 1)
            if idx < self.capacity:
                self.by_type[ftype][idx] = vector
        self.all_failures.append((vector, ftype))

    def sample_rare_type(self) -> Optional[str]:
        """Return the failure type with lowest discovery count (UCB-style)."""
        if not self.counts:
            return None
        total = sum(self.counts.values())
        # UCB score: favour under-represented failure types
        scores = {
            ftype: (total - count) + math.sqrt(2 * math.log(total + 1) / (count + 1))
            for ftype, count in self.counts.items()
        }
        return max(scores, key=scores.get)

    def sample_vector_for_type(self, ftype: str) -> Optional[dict]:
        pool = self.by_type.get(ftype, [])
        return random.choice(pool) if pool else None

    @property
    def known_types(self):
        return set(self.counts.keys())

    @property
    def total_failures(self):
        return sum(self.counts.values())

    def diversity_score(self) -> float:
        """Shannon entropy of failure type distribution. Higher = more diverse."""
        total = self.total_failures
        if total == 0:
            return 0.0
        probs = [c / total for c in self.counts.values()]
        return -sum(p * math.log2(p) for p in probs if p > 0)


class Agent:
    """
    Adaptive test generation agent with multi-strategy selection.

    Parameters
    ----------
    meta           : DesignMeta from RTLParser
    epsilon        : probability of pure random exploration
    mutation_delta : neighbourhood mutation range
    novelty_budget : episodes to force-explore for a new failure type
                     before giving up and assuming it doesn't exist
    known_failure_types : inject ground-truth failure types for novelty targeting
                          (optional — agent discovers them otherwise)
    """

    def __init__(
        self,
        meta: DesignMeta,
        epsilon: float = 0.15,
        mutation_delta: int = 8,
        novelty_budget: int = 50,
        known_failure_types: Optional[List[str]] = None,
    ):
        self.meta = meta
        self.ports = meta.controllable_inputs()
        self.epsilon = epsilon
        self.mutation_delta = mutation_delta
        self.novelty_budget = novelty_budget
        self.known_failure_types = set(known_failure_types or [])

        self.memory = FailureMemory()
        self.episode = 0
        self.last_vector: Optional[dict] = None

        # Novelty forcing: tracks how many episodes we've tried for each type
        self._novelty_attempts: Dict[str, int] = defaultdict(int)
        # Running stats for logging
        self.stats = {
            "total": 0,
            "failures": 0,
            "strategy_counts": defaultdict(int),
        }

        # Hard-coded domain knowledge for known failure types
        # These are the "hypothesis vectors" the agent uses to target specific bugs
        self._hypothesis_generators = {
            "divide_by_zero": self._gen_divide_by_zero,
            "overflow":       self._gen_overflow,
        }

    # ------------------------------------------------------------------
    # Public API
    # ------------------------------------------------------------------

    def generate(self) -> dict:
        self.episode += 1
        self.stats["total"] += 1
        strategy, vector = self._select_strategy()
        self.stats["strategy_counts"][strategy] += 1
        self.last_vector = vector
        return vector

    def update(self, vector: dict, result: dict):
        if result.get("failure"):
            ftype = result.get("type", "unknown")
            self.memory.add(vector, ftype)
            self.stats["failures"] += 1
            # Reset novelty budget for this type since we found it
            self._novelty_attempts[ftype] = 0

    def summary(self) -> dict:
        return {
            "episode": self.episode,
            "total_failures": self.memory.total_failures,
            "failure_counts": dict(self.memory.counts),
            "failure_types_found": list(self.memory.known_types),
            "diversity_score": round(self.memory.diversity_score(), 4),
            "strategy_distribution": dict(self.stats["strategy_counts"]),
        }

    # ------------------------------------------------------------------
    # Strategy selection
    # ------------------------------------------------------------------

    def _select_strategy(self) -> Tuple[str, dict]:
        # 1. Pure random (epsilon)
        if random.random() < self.epsilon:
            return "random", self._gen_random()

        # 2. Novelty forcing: if known types haven't been found yet, target them
        undiscovered = self.known_failure_types - self.memory.known_types
        for ftype in undiscovered:
            if self._novelty_attempts[ftype] < self.novelty_budget:
                self._novelty_attempts[ftype] += 1
                gen = self._hypothesis_generators.get(ftype)
                if gen:
                    return f"novelty:{ftype}", gen()

        # 3. If we have failures, use UCB to pick which type to target
        if self.memory.total_failures > 0:
            target_type = self.memory.sample_rare_type()

            # Sub-strategy: mutate a known-failing vector for this type
            if random.random() < 0.6:
                base = self.memory.sample_vector_for_type(target_type)
                if base:
                    return f"mutation:{target_type}", self._mutate(base)

            # Sub-strategy: hypothesis-guided generation
            gen = self._hypothesis_generators.get(target_type)
            if gen:
                return f"hypothesis:{target_type}", gen()

        # 4. Boundary sweep
        if random.random() < 0.2:
            return "boundary", self._gen_boundary()

        # 5. Fallback random
        return "random", self._gen_random()

    # ------------------------------------------------------------------
    # Vector generators
    # ------------------------------------------------------------------

    def _gen_random(self) -> dict:
        return {name: MutationStrategy.random_val(p) for name, p in self.ports.items()}

    def _gen_boundary(self) -> dict:
        return {name: MutationStrategy.boundary(p) for name, p in self.ports.items()}

    def _mutate(self, base: dict) -> dict:
        vec = dict(base)
        port_names = list(self.ports.keys())
        # Mutate 1 or 2 ports
        targets = random.sample(port_names, k=min(2, len(port_names)))
        for name in targets:
            p = self.ports[name]
            strat = random.choice(["neighbour", "bitflip"])
            if strat == "neighbour":
                vec[name] = MutationStrategy.neighbour(vec[name], p, self.mutation_delta)
            else:
                vec[name] = MutationStrategy.bit_flip(vec[name], p.width)
        return vec

    def _gen_divide_by_zero(self) -> dict:
        """Domain hypothesis: op=3 (DIV), b=0"""
        vec = self._gen_random()
        # Try to set b=0 if port exists
        for name, port in self.ports.items():
            if name.lower() == 'b':
                vec[name] = 0
            if name.lower() == 'op':
                vec[name] = 3
        return vec

    def _gen_overflow(self) -> dict:
        """Domain hypothesis: large a+b or a*b"""
        vec = self._gen_random()
        for name, port in self.ports.items():
            if name.lower() in ('a', 'b'):
                # Upper 25% of range
                lo = int(port.max_val * 0.75)
                vec[name] = random.randint(lo, port.max_val)
            if name.lower() == 'op':
                vec[name] = random.choice([0, 2])  # ADD or MUL — most likely to overflow
        return vec
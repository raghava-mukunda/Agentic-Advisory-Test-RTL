# Adaptive Agent-Based RTL Testing (AAT-RTL)

An automated framework for testing RTL (Register Transfer Level) designs using an adaptive, feedback-driven agent. The system generates input vectors, runs simulations via Verilator, detects failures, and iteratively improves test generation — without requiring prior knowledge of failure conditions.

---

## Testing Strategies

| Strategy | Description |
|---|---|
| **Random** | Uniform input sampling |
| **Biased** | Heuristic-guided input generation |
| **Adaptive** | Feedback-driven agentic approach |

---

## Key Features

- Fully automated RTL testing pipeline
- Works with any Verilog design + C++ testbench
- Generic failure detection (`err_*`, validity signals)
- Multi-seed evaluation for statistical robustness
- Metrics: Time to First Failure (TTFF), Failure Coverage, Diversity (entropy), Unique failure types

---

## Project Structure

```
aat-rtl/
├── main.py                  # Entry point
├── agent.py                 # Adaptive agent logic
├── analyzer.py              # Failure detection & metrics
├── sim_runner.py            # Verilator interface
├── rtl_parser.py            # Extracts inputs from RTL
├── logger.py                # Logging results
├── alu_fsm.v                # Example RTL (sequential)
├── sat_alu.v                # Example RTL (combinational)
├── priority_encoder.v       # Example RTL
├── tb.cpp                   # Testbench
├── results/                 # Output JSON files
└── README.md
```

---

## Requirements

- Python 3.10+
- Verilator >= 5.x
- C++ compiler (clang / gcc)
- Python: `numpy`

---

## Installation

```bash
# 1. Clone
git clone https://github.com/raghava-mukunda/Agentic-Advisory-Test-RTL.git
cd aat-rtl

# 2. Virtual environment
python3 -m venv venv
source venv/bin/activate

# 3. Dependencies
pip install numpy
```

---

## How It Works

```
RTL → Parser → Agent → Simulation → Analyzer → Logger
                      ↑________feedback__________|
```

1. **RTL Parser** — extracts controllable inputs from the design
2. **Agent** — generates test vectors
3. **Simulation Runner** — executes tests via Verilator
4. **Analyzer** — detects failures from output signals
5. **Logger** — records results to JSON
6. Agent updates strategy based on feedback and repeats

---

## Running Experiments

```bash
# Single run
python main.py

# Multi-seed evaluation (recommended) — seeds: [42, 123, 7, 99, 2024], 300 episodes each
python main.py --multiseed

# Baseline comparison (Adaptive vs Random vs Biased)
python main.py --baseline
```

---

## Input Requirements

### RTL (`.v`)
- Clearly defined inputs
- Optional failure signals: `err_*`, `valid`, `ready`

### Testbench (`.cpp`)
Must read inputs from stdin and print outputs in `key=value` format:

```cpp
std::cout << "y=" << int(top->y)
          << " err_overflow=" << int(top->err_overflow)
          << std::endl;
```

---

## Output Format

Results are written to `results/*.json`:

```json
{
  "total_episodes": 300,
  "total_failures": 138,
  "unique_failure_types": 3,
  "failure_coverage": 1.0,
  "diversity_score": 1.48
}
```

---

## Metrics

| Metric | Description |
|---|---|
| TTFF | Episodes until first failure is detected |
| Coverage | Fraction of failure types discovered |
| Diversity | Entropy of failure type distribution |
| Types | Number of unique failure types found |

---

## Results

### Saturating ALU

| Metric | Random | Biased | Adaptive |
|---|---|---|---|
| TTFF | 2.40 ± 2.33 | 4.00 ± 1.79 | **1.40 ± 0.49** |
| Unique Types | 2.20 | 3.00 | **3.00** |
| Coverage | 0.73 | 1.00 | **1.00** |
| Diversity | 0.85 | 1.42 | **1.58** |

### FSM ALU
Adaptive finds all failure types; random misses rare corner-case conditions.

### Priority Encoder
All methods behave similarly due to limited failure signal observability.

---

## Key Insights

- Adaptive testing consistently outperforms random testing
- Matches or exceeds biased testing **without any prior knowledge**
- Performance scales with the richness of observable failure signals
- Exploration-exploitation balance is critical for efficiency

---

## Limitations

- Agent uses simple heuristics (not full RL)
- Evaluated on a limited number of designs
- Requires observable failure signals in the RTL

---

## Future Work

- Reinforcement learning-based agent
- Automatic failure inference from waveforms
- Larger RTL benchmark suite

---

## Author

Raghava M — RV College of Engineering, Bangalore

---

## License

MIT License
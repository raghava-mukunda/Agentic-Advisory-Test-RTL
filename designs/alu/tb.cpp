// tb.cpp
// Verilator testbench for alu_fsm
//
// Output format (one line to stdout):
//   y=<val> err_div=<0|1> err_ovf=<0|1> err_udf=<0|1> state=<0-3> cycle=<n>
//
// The Python analyzer parses these key=value tokens.
// Adding cycle= and state= lets the analyzer measure failure depth.

#include "Valu_fsm.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib>

// Clock tick helper
static void tick(Valu_fsm* top) {
    top->clk = 0; top->eval();
    top->clk = 1; top->eval();
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: Valu_fsm <a> <b> <op>\n";
        return 1;
    }

    Verilated::commandArgs(argc, argv);
    Valu_fsm* top = new Valu_fsm;

    int a  = atoi(argv[1]);
    int b  = atoi(argv[2]);
    int op = atoi(argv[3]);

    // --- Reset ---
    top->rst = 1;
    top->clk = 0;
    top->a   = 0;
    top->b   = 0;
    top->op  = 0;
    tick(top);
    tick(top);
    top->rst = 0;

    // --- Apply inputs ---
    top->a  = (uint8_t)a;
    top->b  = (uint8_t)b;
    top->op = (uint8_t)(op & 0x3);

    // Run enough cycles to traverse the 4-state FSM:
    // IDLE(0) -> LOAD(1) -> EXEC(2) -> DONE(3) -> IDLE(0)
    // = 4 full cycles = 8 clock edges
    int failure_cycle = -1;
    for (int i = 0; i < 8; i++) {
        tick(top);
        // Record first cycle where any error is raised
        if (failure_cycle < 0 &&
            (top->err_div_zero || top->err_overflow || top->err_underflow)) {
            failure_cycle = i;
        }
    }

    // Final state
    int cyc = (failure_cycle >= 0) ? failure_cycle : 8;

    std::cout
        << "y="        << (int)top->y
        << " err_div=" << (int)top->err_div_zero
        << " err_ovf=" << (int)top->err_overflow
        << " err_udf=" << (int)top->err_underflow
        << " state="   << (int)top->state_out
        << " cycle="   << cyc
        << std::endl;

    delete top;
    return 0;
}
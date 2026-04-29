#include "Vfifo_ecc.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vfifo_ecc* top = new Vfifo_ecc;

    int write_en = atoi(argv[1]);
    int read_en  = atoi(argv[2]);
    int data_in  = atoi(argv[3]);
    int burst    = atoi(argv[4]);

    top->rst = 1; top->clk = 0; top->eval();
    top->rst = 0;

    top->write_en = write_en;
    top->read_en  = read_en;
    top->data_in  = data_in;
    top->burst_len = burst;

    for (int i=0; i<10; i++) {
        top->clk = !top->clk;
        top->eval();
    }

    std::cout
        << "err_overflow=" << (int)top->err_overflow << " "
        << "err_underflow=" << (int)top->err_underflow << " "
        << "err_ecc=" << (int)top->err_ecc << " "
        << "err_ptr=" << (int)top->err_ptr
        << std::endl;

    delete top;
    return 0;
}
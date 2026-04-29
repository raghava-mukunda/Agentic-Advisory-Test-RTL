#include "Vcomb_unit.h"
#include "verilated.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vcomb_unit* top = new Vcomb_unit;

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int op = atoi(argv[3]);

    top->a = a;
    top->b = b;
    top->op = op;

    top->eval();

    std::cout
        << "err_overflow=" << (int)top->err_overflow << " "
        << "err_underflow=" << (int)top->err_underflow << " "
        << "err_div_zero=" << (int)top->err_div_zero << " "
        << "err_flag=" << (int)top->err_flag << " "
        << "err_sat=" << (int)top->err_sat
        << std::endl;

    delete top;
    return 0;
}
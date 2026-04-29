#include "Vsat_alu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vsat_alu* top = new Vsat_alu;

    int a, b, op;
    std::cin >> a >> b >> op;

    top->a = a;
    top->b = b;
    top->op = op;

    top->eval();

    std::cout << "y=" << int(top->y)
              << " err_overflow=" << int(top->err_overflow)
              << " err_div_zero=" << int(top->err_div_zero)
              << " err_saturation=" << int(top->err_saturation)
              << std::endl;

    delete top;
}
#include "Vpriority_encoder.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vpriority_encoder* top = new Vpriority_encoder;

    int in;
    std::cin >> in;

    top->in = in;
    top->eval();

    std::cout << "out=" << int(top->out)
              << " valid=" << int(top->valid)
              << " err_multiple=" << int(top->err_multiple)
              << std::endl;

    delete top;
}
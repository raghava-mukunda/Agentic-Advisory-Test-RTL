// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_ecc.h for the primary calling header

#include "Vfifo_ecc__pch.h"

void Vfifo_ecc___024root___ctor_var_reset(Vfifo_ecc___024root* vlSelf);

Vfifo_ecc___024root::Vfifo_ecc___024root(Vfifo_ecc__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vfifo_ecc___024root___ctor_var_reset(this);
}

void Vfifo_ecc___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vfifo_ecc___024root::~Vfifo_ecc___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpriority_enc.h for the primary calling header

#include "Vpriority_enc__pch.h"

void Vpriority_enc___024root___ctor_var_reset(Vpriority_enc___024root* vlSelf);

Vpriority_enc___024root::Vpriority_enc___024root(Vpriority_enc__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vpriority_enc___024root___ctor_var_reset(this);
}

void Vpriority_enc___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpriority_enc___024root::~Vpriority_enc___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

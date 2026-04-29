// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpriority_encoder.h for the primary calling header

#include "Vpriority_encoder__pch.h"

void Vpriority_encoder___024root___ctor_var_reset(Vpriority_encoder___024root* vlSelf);

Vpriority_encoder___024root::Vpriority_encoder___024root(Vpriority_encoder__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vpriority_encoder___024root___ctor_var_reset(this);
}

void Vpriority_encoder___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpriority_encoder___024root::~Vpriority_encoder___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

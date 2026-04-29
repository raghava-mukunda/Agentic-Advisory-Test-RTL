// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcomb_unit.h for the primary calling header

#include "Vcomb_unit__pch.h"

void Vcomb_unit___024root___ctor_var_reset(Vcomb_unit___024root* vlSelf);

Vcomb_unit___024root::Vcomb_unit___024root(Vcomb_unit__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vcomb_unit___024root___ctor_var_reset(this);
}

void Vcomb_unit___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcomb_unit___024root::~Vcomb_unit___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

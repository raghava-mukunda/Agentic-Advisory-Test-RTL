// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsat_alu.h for the primary calling header

#include "Vsat_alu__pch.h"

void Vsat_alu___024root___ctor_var_reset(Vsat_alu___024root* vlSelf);

Vsat_alu___024root::Vsat_alu___024root(Vsat_alu__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vsat_alu___024root___ctor_var_reset(this);
}

void Vsat_alu___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vsat_alu___024root::~Vsat_alu___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

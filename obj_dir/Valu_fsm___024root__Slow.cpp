// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Valu_fsm.h for the primary calling header

#include "Valu_fsm__pch.h"

void Valu_fsm___024root___ctor_var_reset(Valu_fsm___024root* vlSelf);

Valu_fsm___024root::Valu_fsm___024root(Valu_fsm__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Valu_fsm___024root___ctor_var_reset(this);
}

void Valu_fsm___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Valu_fsm___024root::~Valu_fsm___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

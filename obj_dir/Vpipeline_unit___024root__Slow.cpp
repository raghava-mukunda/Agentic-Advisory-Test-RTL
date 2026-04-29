// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline_unit.h for the primary calling header

#include "Vpipeline_unit__pch.h"

void Vpipeline_unit___024root___ctor_var_reset(Vpipeline_unit___024root* vlSelf);

Vpipeline_unit___024root::Vpipeline_unit___024root(Vpipeline_unit__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vpipeline_unit___024root___ctor_var_reset(this);
}

void Vpipeline_unit___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpipeline_unit___024root::~Vpipeline_unit___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

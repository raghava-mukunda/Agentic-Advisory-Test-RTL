// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsat_alu.h for the primary calling header

#ifndef VERILATED_VSAT_ALU___024ROOT_H_
#define VERILATED_VSAT_ALU___024ROOT_H_  // guard

#include "verilated.h"


class Vsat_alu__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsat_alu___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,7,0);
    VL_IN8(b,7,0);
    VL_IN8(op,2,0);
    VL_OUT8(y,7,0);
    VL_OUT8(err_overflow,0,0);
    VL_OUT8(err_div_zero,0,0);
    VL_OUT8(err_saturation,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VicoPhaseResult;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;

    // INTERNAL VARIABLES
    Vsat_alu__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vsat_alu___024root(Vsat_alu__Syms* symsp, const char* namep);
    ~Vsat_alu___024root();
    VL_UNCOPYABLE(Vsat_alu___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

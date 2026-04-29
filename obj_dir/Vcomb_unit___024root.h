// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcomb_unit.h for the primary calling header

#ifndef VERILATED_VCOMB_UNIT___024ROOT_H_
#define VERILATED_VCOMB_UNIT___024ROOT_H_  // guard

#include "verilated.h"


class Vcomb_unit__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcomb_unit___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,7,0);
    VL_IN8(b,7,0);
    VL_IN8(op,2,0);
    VL_OUT8(y,7,0);
    VL_OUT8(err_overflow,0,0);
    VL_OUT8(err_underflow,0,0);
    VL_OUT8(err_div_zero,0,0);
    VL_OUT8(err_flag,0,0);
    VL_OUT8(err_sat,0,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VicoPhaseResult;
    SData/*8:0*/ comb_unit__DOT__temp;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;

    // INTERNAL VARIABLES
    Vcomb_unit__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vcomb_unit___024root(Vcomb_unit__Syms* symsp, const char* namep);
    ~Vcomb_unit___024root();
    VL_UNCOPYABLE(Vcomb_unit___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

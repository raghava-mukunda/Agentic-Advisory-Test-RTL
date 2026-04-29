// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpipeline_unit.h for the primary calling header

#ifndef VERILATED_VPIPELINE_UNIT___024ROOT_H_
#define VERILATED_VPIPELINE_UNIT___024ROOT_H_  // guard

#include "verilated.h"


class Vpipeline_unit__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpipeline_unit___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(a,7,0);
    VL_IN8(b,7,0);
    VL_IN8(op,1,0);
    VL_OUT8(y,7,0);
    VL_OUT8(err_overflow,0,0);
    VL_OUT8(err_underflow,0,0);
    VL_OUT8(err_hazard,0,0);
    VL_OUT8(err_sat,0,0);
    CData/*7:0*/ pipeline_unit__DOT__a1;
    CData/*7:0*/ pipeline_unit__DOT__b1;
    CData/*7:0*/ pipeline_unit__DOT__a2;
    CData/*7:0*/ pipeline_unit__DOT__b2;
    CData/*7:0*/ pipeline_unit__DOT__res;
    CData/*1:0*/ pipeline_unit__DOT__op1;
    CData/*1:0*/ pipeline_unit__DOT__op2;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vpipeline_unit__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vpipeline_unit___024root(Vpipeline_unit__Syms* symsp, const char* namep);
    ~Vpipeline_unit___024root();
    VL_UNCOPYABLE(Vpipeline_unit___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

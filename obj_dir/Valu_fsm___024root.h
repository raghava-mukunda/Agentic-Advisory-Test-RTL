// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Valu_fsm.h for the primary calling header

#ifndef VERILATED_VALU_FSM___024ROOT_H_
#define VERILATED_VALU_FSM___024ROOT_H_  // guard

#include "verilated.h"


class Valu_fsm__Syms;

class alignas(VL_CACHE_LINE_BYTES) Valu_fsm___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(a,7,0);
    VL_IN8(b,7,0);
    VL_IN8(op,1,0);
    VL_OUT8(y,7,0);
    VL_OUT8(err_div_zero,0,0);
    VL_OUT8(err_overflow,0,0);
    VL_OUT8(err_underflow,0,0);
    VL_OUT8(state_out,1,0);
    CData/*1:0*/ alu_fsm__DOT__state;
    CData/*7:0*/ alu_fsm__DOT__a_reg;
    CData/*7:0*/ alu_fsm__DOT__b_reg;
    CData/*1:0*/ alu_fsm__DOT__op_reg;
    CData/*7:0*/ alu_fsm__DOT__accumulator;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*8:0*/ alu_fsm__DOT__result_wide;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Valu_fsm__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Valu_fsm___024root(Valu_fsm__Syms* symsp, const char* namep);
    ~Valu_fsm___024root();
    VL_UNCOPYABLE(Valu_fsm___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

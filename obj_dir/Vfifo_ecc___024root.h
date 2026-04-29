// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vfifo_ecc.h for the primary calling header

#ifndef VERILATED_VFIFO_ECC___024ROOT_H_
#define VERILATED_VFIFO_ECC___024ROOT_H_  // guard

#include "verilated.h"


class Vfifo_ecc__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vfifo_ecc___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(write_en,0,0);
    VL_IN8(read_en,0,0);
    VL_IN8(data_in,7,0);
    VL_IN8(burst_len,1,0);
    VL_OUT8(data_out,7,0);
    VL_OUT8(err_overflow,0,0);
    VL_OUT8(err_underflow,0,0);
    VL_OUT8(err_ecc,0,0);
    VL_OUT8(err_ptr,0,0);
    CData/*3:0*/ fifo_ecc__DOT__wr_ptr;
    CData/*3:0*/ fifo_ecc__DOT__rd_ptr;
    CData/*4:0*/ fifo_ecc__DOT__count;
    CData/*1:0*/ fifo_ecc__DOT__state;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*8:0*/ fifo_ecc__DOT__temp;
    IData/*31:0*/ fifo_ecc__DOT__i;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*8:0*/, 16> fifo_ecc__DOT__mem;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlNBACommitQueue<VlUnpacked<SData/*8:0*/, 16>, false, SData/*8:0*/, 1> __VdlyCommitQueuefifo_ecc__DOT__mem;

    // INTERNAL VARIABLES
    Vfifo_ecc__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vfifo_ecc___024root(Vfifo_ecc__Syms* symsp, const char* namep);
    ~Vfifo_ecc___024root();
    VL_UNCOPYABLE(Vfifo_ecc___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

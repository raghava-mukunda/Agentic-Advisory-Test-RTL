// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_ecc.h for the primary calling header

#include "Vfifo_ecc__pch.h"

void Vfifo_ecc___024root___eval_triggers_vec__act(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_triggers_vec__act\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((IData)(vlSelfRef.rst) 
                                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0))) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

bool Vfifo_ecc___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vfifo_ecc___024root___nba_sequent__TOP__0(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___nba_sequent__TOP__0\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout;
    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout = 0;
    CData/*7:0*/ __Vfunc_fifo_ecc__DOT__parity__0__d;
    __Vfunc_fifo_ecc__DOT__parity__0__d = 0;
    CData/*0:0*/ __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout;
    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout = 0;
    CData/*7:0*/ __Vfunc_fifo_ecc__DOT__parity__1__d;
    __Vfunc_fifo_ecc__DOT__parity__1__d = 0;
    CData/*3:0*/ __Vdly__fifo_ecc__DOT__wr_ptr;
    __Vdly__fifo_ecc__DOT__wr_ptr = 0;
    CData/*3:0*/ __Vdly__fifo_ecc__DOT__rd_ptr;
    __Vdly__fifo_ecc__DOT__rd_ptr = 0;
    CData/*4:0*/ __Vdly__fifo_ecc__DOT__count;
    __Vdly__fifo_ecc__DOT__count = 0;
    CData/*1:0*/ __Vdly__fifo_ecc__DOT__state;
    __Vdly__fifo_ecc__DOT__state = 0;
    SData/*8:0*/ __VdlyVal__fifo_ecc__DOT__mem__v0;
    __VdlyVal__fifo_ecc__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__fifo_ecc__DOT__mem__v0;
    __VdlyDim0__fifo_ecc__DOT__mem__v0 = 0;
    // Body
    __Vdly__fifo_ecc__DOT__wr_ptr = vlSelfRef.fifo_ecc__DOT__wr_ptr;
    __Vdly__fifo_ecc__DOT__rd_ptr = vlSelfRef.fifo_ecc__DOT__rd_ptr;
    __Vdly__fifo_ecc__DOT__count = vlSelfRef.fifo_ecc__DOT__count;
    __Vdly__fifo_ecc__DOT__state = vlSelfRef.fifo_ecc__DOT__state;
    if (vlSelfRef.rst) {
        __Vdly__fifo_ecc__DOT__wr_ptr = 0U;
        __Vdly__fifo_ecc__DOT__rd_ptr = 0U;
        __Vdly__fifo_ecc__DOT__count = 0U;
        __Vdly__fifo_ecc__DOT__state = 0U;
        vlSelfRef.err_overflow = 0U;
        vlSelfRef.err_underflow = 0U;
        vlSelfRef.err_ecc = 0U;
        vlSelfRef.err_ptr = 0U;
    } else {
        vlSelfRef.err_overflow = 0U;
        vlSelfRef.err_ptr = 0U;
        vlSelfRef.err_underflow = 0U;
        vlSelfRef.err_ecc = 0U;
        if ((0U == (IData)(vlSelfRef.fifo_ecc__DOT__state))) {
            if (vlSelfRef.write_en) {
                __Vdly__fifo_ecc__DOT__state = 1U;
            } else if (vlSelfRef.read_en) {
                __Vdly__fifo_ecc__DOT__state = 2U;
            }
        } else if ((1U == (IData)(vlSelfRef.fifo_ecc__DOT__state))) {
            vlSelfRef.fifo_ecc__DOT__i = 0U;
            while ((vlSelfRef.fifo_ecc__DOT__i < (IData)(vlSelfRef.burst_len))) {
                if ((0x10U == (IData)(vlSelfRef.fifo_ecc__DOT__count))) {
                    vlSelfRef.err_overflow = 1U;
                } else {
                    __Vdly__fifo_ecc__DOT__count = 
                        (0x0000001fU & ((IData)(1U) 
                                        + (IData)(vlSelfRef.fifo_ecc__DOT__count)));
                    __VdlyVal__fifo_ecc__DOT__mem__v0 
                        = ((([&]() {
                                    __Vfunc_fifo_ecc__DOT__parity__0__d 
                                        = vlSelfRef.data_in;
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout = 0U;
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & (IData)(__Vfunc_fifo_ecc__DOT__parity__0__d));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 1U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 2U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 3U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 4U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 5U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                                  >> 6U)));
                                    __Vfunc_fifo_ecc__DOT__parity__0__Vfuncout 
                                        = ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout) 
                                           ^ ((IData)(__Vfunc_fifo_ecc__DOT__parity__0__d) 
                                              >> 7U));
                                }(), (IData)(__Vfunc_fifo_ecc__DOT__parity__0__Vfuncout)) 
                            << 8U) | (IData)(vlSelfRef.data_in));
                    __VdlyDim0__fifo_ecc__DOT__mem__v0 
                        = vlSelfRef.fifo_ecc__DOT__wr_ptr;
                    vlSelfRef.__VdlyCommitQueuefifo_ecc__DOT__mem.enqueue(__VdlyVal__fifo_ecc__DOT__mem__v0, (IData)(__VdlyDim0__fifo_ecc__DOT__mem__v0));
                    __Vdly__fifo_ecc__DOT__wr_ptr = 
                        (0x0000000fU & ((IData)(1U) 
                                        + (IData)(vlSelfRef.fifo_ecc__DOT__wr_ptr)));
                }
                vlSelfRef.fifo_ecc__DOT__i = ((IData)(1U) 
                                              + vlSelfRef.fifo_ecc__DOT__i);
            }
            __Vdly__fifo_ecc__DOT__state = 3U;
        } else if ((2U == (IData)(vlSelfRef.fifo_ecc__DOT__state))) {
            vlSelfRef.fifo_ecc__DOT__i = 0U;
            while ((vlSelfRef.fifo_ecc__DOT__i < (IData)(vlSelfRef.burst_len))) {
                if ((0U == (IData)(vlSelfRef.fifo_ecc__DOT__count))) {
                    vlSelfRef.err_underflow = 1U;
                } else {
                    __Vdly__fifo_ecc__DOT__count = 
                        (0x0000001fU & ((IData)(vlSelfRef.fifo_ecc__DOT__count) 
                                        - (IData)(1U)));
                    vlSelfRef.fifo_ecc__DOT__temp = vlSelfRef.fifo_ecc__DOT__mem
                        [vlSelfRef.fifo_ecc__DOT__rd_ptr];
                    vlSelfRef.data_out = (0x000000ffU 
                                          & (IData)(vlSelfRef.fifo_ecc__DOT__temp));
                    if ((([&]() {
                                    __Vfunc_fifo_ecc__DOT__parity__1__d 
                                        = (0x000000ffU 
                                           & (IData)(vlSelfRef.fifo_ecc__DOT__temp));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout = 0U;
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & (IData)(__Vfunc_fifo_ecc__DOT__parity__1__d));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 1U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 2U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 3U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 4U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 5U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = (1U & ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                                 ^ 
                                                 ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                                  >> 6U)));
                                    __Vfunc_fifo_ecc__DOT__parity__1__Vfuncout 
                                        = ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout) 
                                           ^ ((IData)(__Vfunc_fifo_ecc__DOT__parity__1__d) 
                                              >> 7U));
                                }(), (IData)(__Vfunc_fifo_ecc__DOT__parity__1__Vfuncout)) 
                         != (1U & ((IData)(vlSelfRef.fifo_ecc__DOT__temp) 
                                   >> 8U)))) {
                        vlSelfRef.err_ecc = 1U;
                    }
                    __Vdly__fifo_ecc__DOT__rd_ptr = 
                        (0x0000000fU & ((IData)(1U) 
                                        + (IData)(vlSelfRef.fifo_ecc__DOT__rd_ptr)));
                }
                vlSelfRef.fifo_ecc__DOT__i = ((IData)(1U) 
                                              + vlSelfRef.fifo_ecc__DOT__i);
            }
            __Vdly__fifo_ecc__DOT__state = 3U;
        } else if ((3U == (IData)(vlSelfRef.fifo_ecc__DOT__state))) {
            __Vdly__fifo_ecc__DOT__state = 0U;
        }
    }
    vlSelfRef.fifo_ecc__DOT__wr_ptr = __Vdly__fifo_ecc__DOT__wr_ptr;
    vlSelfRef.fifo_ecc__DOT__rd_ptr = __Vdly__fifo_ecc__DOT__rd_ptr;
    vlSelfRef.fifo_ecc__DOT__count = __Vdly__fifo_ecc__DOT__count;
    vlSelfRef.fifo_ecc__DOT__state = __Vdly__fifo_ecc__DOT__state;
    vlSelfRef.__VdlyCommitQueuefifo_ecc__DOT__mem.commit(vlSelfRef.fifo_ecc__DOT__mem);
}

void Vfifo_ecc___024root___eval_nba(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_nba\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vfifo_ecc___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vfifo_ecc___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_ecc___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vfifo_ecc___024root___eval_phase__act(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_phase__act\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vfifo_ecc___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfifo_ecc___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vfifo_ecc___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vfifo_ecc___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vfifo_ecc___024root___eval_phase__nba(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_phase__nba\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vfifo_ecc___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vfifo_ecc___024root___eval_nba(vlSelf);
        Vfifo_ecc___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vfifo_ecc___024root___eval(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vfifo_ecc___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/fifo_ecc.v", 4, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vfifo_ecc___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/fifo_ecc.v", 4, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vfifo_ecc___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vfifo_ecc___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vfifo_ecc___024root___eval_debug_assertions(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_debug_assertions\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.write_en & 0xfeU)))) {
        Verilated::overWidthError("write_en");
    }
    if (VL_UNLIKELY(((vlSelfRef.read_en & 0xfeU)))) {
        Verilated::overWidthError("read_en");
    }
    if (VL_UNLIKELY(((vlSelfRef.burst_len & 0xfcU)))) {
        Verilated::overWidthError("burst_len");
    }
}
#endif  // VL_DEBUG

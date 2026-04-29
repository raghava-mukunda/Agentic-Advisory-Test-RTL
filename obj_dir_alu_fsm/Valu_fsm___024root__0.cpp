// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Valu_fsm.h for the primary calling header

#include "Valu_fsm__pch.h"

void Valu_fsm___024root___eval_triggers_vec__act(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_triggers_vec__act\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

bool Valu_fsm___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___trigger_anySet__act\n"); );
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

void Valu_fsm___024root___nba_sequent__TOP__0(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___nba_sequent__TOP__0\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vdly__alu_fsm__DOT__state;
    __Vdly__alu_fsm__DOT__state = 0;
    CData/*7:0*/ __Vdly__alu_fsm__DOT__accumulator;
    __Vdly__alu_fsm__DOT__accumulator = 0;
    SData/*8:0*/ __Vdly__alu_fsm__DOT__result_wide;
    __Vdly__alu_fsm__DOT__result_wide = 0;
    // Body
    __Vdly__alu_fsm__DOT__accumulator = vlSelfRef.alu_fsm__DOT__accumulator;
    __Vdly__alu_fsm__DOT__result_wide = vlSelfRef.alu_fsm__DOT__result_wide;
    __Vdly__alu_fsm__DOT__state = vlSelfRef.alu_fsm__DOT__state;
    if (vlSelfRef.rst) {
        __Vdly__alu_fsm__DOT__state = 0U;
        vlSelfRef.y = 0U;
        __Vdly__alu_fsm__DOT__accumulator = 0U;
        vlSelfRef.err_div_zero = 0U;
        vlSelfRef.err_overflow = 0U;
        vlSelfRef.err_underflow = 0U;
        __Vdly__alu_fsm__DOT__result_wide = 0U;
    } else if ((2U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
        if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
            vlSelfRef.y = (0x000000ffU & (IData)(vlSelfRef.alu_fsm__DOT__result_wide));
            __Vdly__alu_fsm__DOT__state = 0U;
            if ((IData)((((IData)(vlSelfRef.alu_fsm__DOT__result_wide) 
                          >> 8U) | (0xc8U < (0x000000ffU 
                                             & (IData)(vlSelfRef.alu_fsm__DOT__result_wide)))))) {
                vlSelfRef.err_overflow = 1U;
            }
            __Vdly__alu_fsm__DOT__accumulator = (0x000000ffU 
                                                 & ((IData)(vlSelfRef.alu_fsm__DOT__accumulator) 
                                                    + (IData)(vlSelfRef.alu_fsm__DOT__result_wide)));
            if ((0xdcU < (IData)(vlSelfRef.alu_fsm__DOT__accumulator))) {
                vlSelfRef.err_overflow = 1U;
            }
        } else {
            if ((2U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                    if ((0U == (IData)(vlSelfRef.alu_fsm__DOT__b_reg))) {
                        vlSelfRef.err_div_zero = 1U;
                        __Vdly__alu_fsm__DOT__result_wide = 0U;
                    } else {
                        __Vdly__alu_fsm__DOT__result_wide 
                            = (0x000000ffU & VL_DIV_III(8, (IData)(vlSelfRef.alu_fsm__DOT__a_reg), (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                    }
                } else {
                    __Vdly__alu_fsm__DOT__result_wide 
                        = (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                          * (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                }
            } else if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                if (((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                     < (IData)(vlSelfRef.alu_fsm__DOT__b_reg))) {
                    vlSelfRef.err_underflow = 1U;
                    __Vdly__alu_fsm__DOT__result_wide = 0U;
                } else {
                    __Vdly__alu_fsm__DOT__result_wide 
                        = (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                          - (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                }
            } else {
                __Vdly__alu_fsm__DOT__result_wide = 
                    (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                    + (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
            }
            __Vdly__alu_fsm__DOT__state = 3U;
        }
    } else if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
        __Vdly__alu_fsm__DOT__state = 2U;
    } else {
        vlSelfRef.err_div_zero = 0U;
        vlSelfRef.err_overflow = 0U;
        vlSelfRef.err_underflow = 0U;
        vlSelfRef.alu_fsm__DOT__a_reg = vlSelfRef.a;
        vlSelfRef.alu_fsm__DOT__b_reg = vlSelfRef.b;
        vlSelfRef.alu_fsm__DOT__op_reg = vlSelfRef.op;
        __Vdly__alu_fsm__DOT__state = 1U;
    }
    vlSelfRef.alu_fsm__DOT__accumulator = __Vdly__alu_fsm__DOT__accumulator;
    vlSelfRef.alu_fsm__DOT__result_wide = __Vdly__alu_fsm__DOT__result_wide;
    vlSelfRef.alu_fsm__DOT__state = __Vdly__alu_fsm__DOT__state;
    vlSelfRef.state_out = vlSelfRef.alu_fsm__DOT__state;
}

void Valu_fsm___024root___eval_nba(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_nba\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state;
    __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 0;
    CData/*7:0*/ __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator;
    __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator = 0;
    SData/*8:0*/ __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide;
    __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator 
            = vlSelfRef.alu_fsm__DOT__accumulator;
        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide 
            = vlSelfRef.alu_fsm__DOT__result_wide;
        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state 
            = vlSelfRef.alu_fsm__DOT__state;
        if (vlSelfRef.rst) {
            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 0U;
            vlSelfRef.y = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator = 0U;
            vlSelfRef.err_div_zero = 0U;
            vlSelfRef.err_overflow = 0U;
            vlSelfRef.err_underflow = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide = 0U;
        } else if ((2U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
                vlSelfRef.y = (0x000000ffU & (IData)(vlSelfRef.alu_fsm__DOT__result_wide));
                __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 0U;
                if ((IData)((((IData)(vlSelfRef.alu_fsm__DOT__result_wide) 
                              >> 8U) | (0xc8U < (0x000000ffU 
                                                 & (IData)(vlSelfRef.alu_fsm__DOT__result_wide)))))) {
                    vlSelfRef.err_overflow = 1U;
                }
                __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator 
                    = (0x000000ffU & ((IData)(vlSelfRef.alu_fsm__DOT__accumulator) 
                                      + (IData)(vlSelfRef.alu_fsm__DOT__result_wide)));
                if ((0xdcU < (IData)(vlSelfRef.alu_fsm__DOT__accumulator))) {
                    vlSelfRef.err_overflow = 1U;
                }
            } else {
                if ((2U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                    if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                        if ((0U == (IData)(vlSelfRef.alu_fsm__DOT__b_reg))) {
                            vlSelfRef.err_div_zero = 1U;
                            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide = 0U;
                        } else {
                            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide 
                                = (0x000000ffU & VL_DIV_III(8, (IData)(vlSelfRef.alu_fsm__DOT__a_reg), (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                        }
                    } else {
                        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide 
                            = (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                              * (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                    }
                } else if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__op_reg))) {
                    if (((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                         < (IData)(vlSelfRef.alu_fsm__DOT__b_reg))) {
                        vlSelfRef.err_underflow = 1U;
                        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide = 0U;
                    } else {
                        __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide 
                            = (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                              - (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                    }
                } else {
                    __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide 
                        = (0x000001ffU & ((IData)(vlSelfRef.alu_fsm__DOT__a_reg) 
                                          + (IData)(vlSelfRef.alu_fsm__DOT__b_reg)));
                }
                __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 3U;
            }
        } else if ((1U & (IData)(vlSelfRef.alu_fsm__DOT__state))) {
            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 2U;
        } else {
            vlSelfRef.err_div_zero = 0U;
            vlSelfRef.err_overflow = 0U;
            vlSelfRef.err_underflow = 0U;
            vlSelfRef.alu_fsm__DOT__a_reg = vlSelfRef.a;
            vlSelfRef.alu_fsm__DOT__b_reg = vlSelfRef.b;
            vlSelfRef.alu_fsm__DOT__op_reg = vlSelfRef.op;
            __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state = 1U;
        }
        vlSelfRef.alu_fsm__DOT__accumulator = __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__accumulator;
        vlSelfRef.alu_fsm__DOT__result_wide = __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__result_wide;
        vlSelfRef.alu_fsm__DOT__state = __Vinline__nba_sequent__TOP__0___Vdly__alu_fsm__DOT__state;
        vlSelfRef.state_out = vlSelfRef.alu_fsm__DOT__state;
    }
}

void Valu_fsm___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Valu_fsm___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Valu_fsm___024root___eval_phase__act(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_phase__act\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Valu_fsm___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Valu_fsm___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Valu_fsm___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Valu_fsm___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Valu_fsm___024root___eval_phase__nba(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_phase__nba\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Valu_fsm___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Valu_fsm___024root___eval_nba(vlSelf);
        Valu_fsm___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Valu_fsm___024root___eval(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Valu_fsm___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/alu_fsm.v", 22, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Valu_fsm___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/alu_fsm.v", 22, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Valu_fsm___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Valu_fsm___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Valu_fsm___024root___eval_debug_assertions(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_debug_assertions\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.op & 0xfcU)))) {
        Verilated::overWidthError("op");
    }
}
#endif  // VL_DEBUG

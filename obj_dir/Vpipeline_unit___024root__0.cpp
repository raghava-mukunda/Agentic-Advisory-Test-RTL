// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline_unit.h for the primary calling header

#include "Vpipeline_unit__pch.h"

void Vpipeline_unit___024root___eval_triggers_vec__act(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_triggers_vec__act\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

bool Vpipeline_unit___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___trigger_anySet__act\n"); );
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

void Vpipeline_unit___024root___nba_sequent__TOP__0(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___nba_sequent__TOP__0\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.err_overflow = 0U;
    if (vlSelfRef.rst) {
        vlSelfRef.err_hazard = 0U;
        vlSelfRef.err_underflow = 0U;
        vlSelfRef.y = 0U;
        vlSelfRef.err_sat = 0U;
    } else {
        vlSelfRef.err_hazard = 0U;
        if ((2U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
            if ((1U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
                if ((0U == (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                    vlSelfRef.err_hazard = 1U;
                }
                if ((0U != (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                    vlSelfRef.pipeline_unit__DOT__res 
                        = (0x000000ffU & VL_DIV_III(8, (IData)(vlSelfRef.pipeline_unit__DOT__a2), (IData)(vlSelfRef.pipeline_unit__DOT__b2)));
                }
            } else {
                vlSelfRef.pipeline_unit__DOT__res = 
                    (0x000000ffU & ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                    * (IData)(vlSelfRef.pipeline_unit__DOT__b2)));
            }
        } else {
            vlSelfRef.pipeline_unit__DOT__res = (0x000000ffU 
                                                 & ((1U 
                                                     & (IData)(vlSelfRef.pipeline_unit__DOT__op2))
                                                     ? 
                                                    (((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                                      < (IData)(vlSelfRef.pipeline_unit__DOT__b2))
                                                      ? 0U
                                                      : 
                                                     ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                                      - (IData)(vlSelfRef.pipeline_unit__DOT__b2)))
                                                     : 
                                                    ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                                     + (IData)(vlSelfRef.pipeline_unit__DOT__b2))));
        }
        vlSelfRef.err_underflow = 0U;
        if ((1U & (~ ((IData)(vlSelfRef.pipeline_unit__DOT__op2) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
                if (((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                     < (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                    vlSelfRef.err_underflow = 1U;
                }
            }
        }
        vlSelfRef.err_sat = 0U;
        if ((0xc8U < (IData)(vlSelfRef.pipeline_unit__DOT__res))) {
            vlSelfRef.err_sat = 1U;
        }
        vlSelfRef.y = vlSelfRef.pipeline_unit__DOT__res;
    }
}

void Vpipeline_unit___024root___nba_sequent__TOP__1(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___nba_sequent__TOP__1\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.pipeline_unit__DOT__a2 = vlSelfRef.pipeline_unit__DOT__a1;
    vlSelfRef.pipeline_unit__DOT__op2 = vlSelfRef.pipeline_unit__DOT__op1;
    vlSelfRef.pipeline_unit__DOT__b2 = vlSelfRef.pipeline_unit__DOT__b1;
    vlSelfRef.pipeline_unit__DOT__a1 = vlSelfRef.a;
    vlSelfRef.pipeline_unit__DOT__op1 = vlSelfRef.op;
    vlSelfRef.pipeline_unit__DOT__b1 = vlSelfRef.b;
}

void Vpipeline_unit___024root___eval_nba(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_nba\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.err_overflow = 0U;
        if (vlSelfRef.rst) {
            vlSelfRef.err_hazard = 0U;
            vlSelfRef.err_underflow = 0U;
            vlSelfRef.y = 0U;
            vlSelfRef.err_sat = 0U;
        } else {
            vlSelfRef.err_hazard = 0U;
            if ((2U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
                if ((1U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
                    if ((0U == (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                        vlSelfRef.err_hazard = 1U;
                    }
                    if ((0U != (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                        vlSelfRef.pipeline_unit__DOT__res 
                            = (0x000000ffU & VL_DIV_III(8, (IData)(vlSelfRef.pipeline_unit__DOT__a2), (IData)(vlSelfRef.pipeline_unit__DOT__b2)));
                    }
                } else {
                    vlSelfRef.pipeline_unit__DOT__res 
                        = (0x000000ffU & ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                          * (IData)(vlSelfRef.pipeline_unit__DOT__b2)));
                }
            } else {
                vlSelfRef.pipeline_unit__DOT__res = 
                    (0x000000ffU & ((1U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))
                                     ? (((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                         < (IData)(vlSelfRef.pipeline_unit__DOT__b2))
                                         ? 0U : ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                                 - (IData)(vlSelfRef.pipeline_unit__DOT__b2)))
                                     : ((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                                        + (IData)(vlSelfRef.pipeline_unit__DOT__b2))));
            }
            vlSelfRef.err_underflow = 0U;
            if ((1U & (~ ((IData)(vlSelfRef.pipeline_unit__DOT__op2) 
                          >> 1U)))) {
                if ((1U & (IData)(vlSelfRef.pipeline_unit__DOT__op2))) {
                    if (((IData)(vlSelfRef.pipeline_unit__DOT__a2) 
                         < (IData)(vlSelfRef.pipeline_unit__DOT__b2))) {
                        vlSelfRef.err_underflow = 1U;
                    }
                }
            }
            vlSelfRef.err_sat = 0U;
            if ((0xc8U < (IData)(vlSelfRef.pipeline_unit__DOT__res))) {
                vlSelfRef.err_sat = 1U;
            }
            vlSelfRef.y = vlSelfRef.pipeline_unit__DOT__res;
        }
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.pipeline_unit__DOT__a2 = vlSelfRef.pipeline_unit__DOT__a1;
        vlSelfRef.pipeline_unit__DOT__op2 = vlSelfRef.pipeline_unit__DOT__op1;
        vlSelfRef.pipeline_unit__DOT__b2 = vlSelfRef.pipeline_unit__DOT__b1;
        vlSelfRef.pipeline_unit__DOT__a1 = vlSelfRef.a;
        vlSelfRef.pipeline_unit__DOT__op1 = vlSelfRef.op;
        vlSelfRef.pipeline_unit__DOT__b1 = vlSelfRef.b;
    }
}

void Vpipeline_unit___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vpipeline_unit___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vpipeline_unit___024root___eval_phase__act(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_phase__act\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpipeline_unit___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vpipeline_unit___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vpipeline_unit___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vpipeline_unit___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vpipeline_unit___024root___eval_phase__nba(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_phase__nba\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vpipeline_unit___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vpipeline_unit___024root___eval_nba(vlSelf);
        Vpipeline_unit___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vpipeline_unit___024root___eval(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vpipeline_unit___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/pipeline_unit.v", 4, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vpipeline_unit___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/pipeline_unit.v", 4, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vpipeline_unit___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vpipeline_unit___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vpipeline_unit___024root___eval_debug_assertions(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_debug_assertions\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

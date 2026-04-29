// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcomb_unit.h for the primary calling header

#include "Vcomb_unit__pch.h"

void Vcomb_unit___024root___eval_triggers_vec__ico(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_triggers_vec__ico\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vcomb_unit___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___trigger_anySet__ico\n"); );
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

void Vcomb_unit___024root___ico_sequent__TOP__0(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___ico_sequent__TOP__0\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ comb_unit__DOT__carry;
    comb_unit__DOT__carry = 0;
    CData/*0:0*/ comb_unit__DOT__zero_flag;
    comb_unit__DOT__zero_flag = 0;
    // Body
    vlSelfRef.err_div_zero = 0U;
    vlSelfRef.err_underflow = 0U;
    if ((1U & (~ ((IData)(vlSelfRef.op) >> 2U)))) {
        if ((2U & (IData)(vlSelfRef.op))) {
            if ((1U & (IData)(vlSelfRef.op))) {
                if ((0U == (IData)(vlSelfRef.b))) {
                    vlSelfRef.err_div_zero = 1U;
                }
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.op) >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.op))) {
                if (((IData)(vlSelfRef.a) < (IData)(vlSelfRef.b))) {
                    vlSelfRef.err_underflow = 1U;
                }
            }
        }
    }
    vlSelfRef.err_overflow = 0U;
    vlSelfRef.err_flag = 0U;
    vlSelfRef.err_sat = 0U;
    comb_unit__DOT__carry = 0U;
    if ((4U & (IData)(vlSelfRef.op))) {
        if ((2U & (IData)(vlSelfRef.op))) {
            if ((1U & (IData)(vlSelfRef.op))) {
                vlSelfRef.comb_unit__DOT__temp = (0x000001ffU 
                                                  & ((IData)(vlSelfRef.a) 
                                                     + (IData)(vlSelfRef.b)));
                if ((0x00c8U < (IData)(vlSelfRef.comb_unit__DOT__temp))) {
                    vlSelfRef.err_sat = 1U;
                    vlSelfRef.y = 0xffU;
                } else {
                    vlSelfRef.y = (0x000000ffU & (IData)(vlSelfRef.comb_unit__DOT__temp));
                }
            } else {
                vlSelfRef.y = ((IData)(vlSelfRef.a) 
                               ^ (IData)(vlSelfRef.b));
            }
        } else {
            vlSelfRef.y = ((1U & (IData)(vlSelfRef.op))
                            ? ((IData)(vlSelfRef.a) 
                               | (IData)(vlSelfRef.b))
                            : ((IData)(vlSelfRef.a) 
                               & (IData)(vlSelfRef.b)));
        }
    } else if ((2U & (IData)(vlSelfRef.op))) {
        if ((1U & (IData)(vlSelfRef.op))) {
            vlSelfRef.y = ((0U == (IData)(vlSelfRef.b))
                            ? 0U : (0x000000ffU & VL_DIV_III(8, (IData)(vlSelfRef.a), (IData)(vlSelfRef.b))));
        } else {
            vlSelfRef.comb_unit__DOT__temp = (0x000001ffU 
                                              & ((IData)(vlSelfRef.a) 
                                                 * (IData)(vlSelfRef.b)));
            vlSelfRef.y = (0x000000ffU & (IData)(vlSelfRef.comb_unit__DOT__temp));
            if ((0x00ffU < (IData)(vlSelfRef.comb_unit__DOT__temp))) {
                vlSelfRef.err_overflow = 1U;
            }
        }
    } else if ((1U & (IData)(vlSelfRef.op))) {
        vlSelfRef.y = (((IData)(vlSelfRef.a) < (IData)(vlSelfRef.b))
                        ? 0U : (0x000000ffU & ((IData)(vlSelfRef.a) 
                                               - (IData)(vlSelfRef.b))));
    } else {
        vlSelfRef.comb_unit__DOT__temp = (0x000001ffU 
                                          & ((IData)(vlSelfRef.a) 
                                             + (IData)(vlSelfRef.b)));
        vlSelfRef.y = (0x000000ffU & (IData)(vlSelfRef.comb_unit__DOT__temp));
        comb_unit__DOT__carry = (1U & ((IData)(vlSelfRef.comb_unit__DOT__temp) 
                                       >> 8U));
        if (comb_unit__DOT__carry) {
            vlSelfRef.err_overflow = 1U;
        }
    }
    comb_unit__DOT__zero_flag = (0U == (IData)(vlSelfRef.y));
    if (((IData)(comb_unit__DOT__zero_flag) & ((IData)(vlSelfRef.a) 
                                               != (IData)(vlSelfRef.b)))) {
        vlSelfRef.err_flag = 1U;
    }
}

void Vcomb_unit___024root___eval_ico(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_ico\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vcomb_unit___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcomb_unit___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vcomb_unit___024root___eval_phase__ico(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_phase__ico\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vcomb_unit___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcomb_unit___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vcomb_unit___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vcomb_unit___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vcomb_unit___024root___eval(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vcomb_unit___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/comb_unit.v", 4, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vcomb_unit___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
}

#ifdef VL_DEBUG
void Vcomb_unit___024root___eval_debug_assertions(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_debug_assertions\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.op & 0xf8U)))) {
        Verilated::overWidthError("op");
    }
}
#endif  // VL_DEBUG

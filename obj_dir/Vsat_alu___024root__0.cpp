// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsat_alu.h for the primary calling header

#include "Vsat_alu__pch.h"

void Vsat_alu___024root___eval_triggers_vec__ico(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___eval_triggers_vec__ico\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vsat_alu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___trigger_anySet__ico\n"); );
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

void Vsat_alu___024root___ico_sequent__TOP__0(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___ico_sequent__TOP__0\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*8:0*/ sat_alu__DOT__temp;
    sat_alu__DOT__temp = 0;
    // Body
    vlSelfRef.err_div_zero = 0U;
    vlSelfRef.err_saturation = 0U;
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
                    vlSelfRef.err_saturation = 1U;
                }
            }
        }
    }
    vlSelfRef.err_overflow = 0U;
    sat_alu__DOT__temp = (0x000001ffU & ((4U & (IData)(vlSelfRef.op))
                                          ? ((2U & (IData)(vlSelfRef.op))
                                              ? ((1U 
                                                  & (IData)(vlSelfRef.op))
                                                  ? 
                                                 (~ 
                                                  ((IData)(vlSelfRef.a) 
                                                   & (IData)(vlSelfRef.b)))
                                                  : 
                                                 ((IData)(vlSelfRef.a) 
                                                  ^ (IData)(vlSelfRef.b)))
                                              : ((1U 
                                                  & (IData)(vlSelfRef.op))
                                                  ? 
                                                 VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.b), 3U)
                                                  : 
                                                 VL_SHIFTL_III(9,9,32, (IData)(vlSelfRef.a), 2U)))
                                          : ((2U & (IData)(vlSelfRef.op))
                                              ? ((1U 
                                                  & (IData)(vlSelfRef.op))
                                                  ? 
                                                 ((0U 
                                                   == (IData)(vlSelfRef.b))
                                                   ? 0U
                                                   : 
                                                  VL_DIV_III(9, (IData)(vlSelfRef.a), (IData)(vlSelfRef.b)))
                                                  : 
                                                 ((IData)(vlSelfRef.a) 
                                                  * (IData)(vlSelfRef.b)))
                                              : ((1U 
                                                  & (IData)(vlSelfRef.op))
                                                  ? 
                                                 (((IData)(vlSelfRef.a) 
                                                   < (IData)(vlSelfRef.b))
                                                   ? 0U
                                                   : 
                                                  ((IData)(vlSelfRef.a) 
                                                   - (IData)(vlSelfRef.b)))
                                                  : 
                                                 ((IData)(vlSelfRef.a) 
                                                  + (IData)(vlSelfRef.b))))));
    if ((0x00ffU < (IData)(sat_alu__DOT__temp))) {
        vlSelfRef.y = 0xffU;
        vlSelfRef.err_overflow = 1U;
    } else {
        vlSelfRef.y = (0x000000ffU & (IData)(sat_alu__DOT__temp));
    }
}

void Vsat_alu___024root___eval_ico(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___eval_ico\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vsat_alu___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsat_alu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vsat_alu___024root___eval_phase__ico(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___eval_phase__ico\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vsat_alu___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsat_alu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vsat_alu___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vsat_alu___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vsat_alu___024root___eval(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___eval\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vsat_alu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("sat_alu.v", 1, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vsat_alu___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
}

#ifdef VL_DEBUG
void Vsat_alu___024root___eval_debug_assertions(Vsat_alu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsat_alu___024root___eval_debug_assertions\n"); );
    Vsat_alu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.op & 0xf8U)))) {
        Verilated::overWidthError("op");
    }
}
#endif  // VL_DEBUG

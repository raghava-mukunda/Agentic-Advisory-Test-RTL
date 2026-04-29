// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpriority_enc.h for the primary calling header

#include "Vpriority_enc__pch.h"

void Vpriority_enc___024root___eval_triggers_vec__ico(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___eval_triggers_vec__ico\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vpriority_enc___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___trigger_anySet__ico\n"); );
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

void Vpriority_enc___024root___ico_sequent__TOP__0(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___ico_sequent__TOP__0\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ priority_encoder__DOT__found;
    priority_encoder__DOT__found = 0;
    // Body
    vlSelfRef.out = 0U;
    vlSelfRef.valid = 0U;
    vlSelfRef.err_multiple = 0U;
    priority_encoder__DOT__found = 0U;
    if ((0x00000080U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 7U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((0x00000040U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 6U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((0x00000020U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 5U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((0x00000010U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 4U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((8U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 3U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((4U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 2U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((2U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 1U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
    if ((1U & (IData)(vlSelfRef.in))) {
        if (priority_encoder__DOT__found) {
            vlSelfRef.err_multiple = 1U;
        } else {
            vlSelfRef.out = 0U;
            vlSelfRef.valid = 1U;
            priority_encoder__DOT__found = 1U;
        }
    }
}

void Vpriority_enc___024root___eval_ico(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___eval_ico\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vpriority_enc___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpriority_enc___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vpriority_enc___024root___eval_phase__ico(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___eval_phase__ico\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vpriority_enc___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vpriority_enc___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vpriority_enc___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vpriority_enc___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vpriority_enc___024root___eval(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___eval\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vpriority_enc___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("priority_enc.v", 1, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vpriority_enc___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
}

#ifdef VL_DEBUG
void Vpriority_enc___024root___eval_debug_assertions(Vpriority_enc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpriority_enc___024root___eval_debug_assertions\n"); );
    Vpriority_enc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG

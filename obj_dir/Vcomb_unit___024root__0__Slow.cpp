// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcomb_unit.h for the primary calling header

#include "Vcomb_unit__pch.h"

VL_ATTR_COLD void Vcomb_unit___024root___eval_static(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_static\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vcomb_unit___024root___eval_initial(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_initial\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vcomb_unit___024root___eval_final(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_final\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcomb_unit___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcomb_unit___024root___eval_phase__stl(Vcomb_unit___024root* vlSelf);

VL_ATTR_COLD void Vcomb_unit___024root___eval_settle(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_settle\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vcomb_unit___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/comb_unit.v", 4, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vcomb_unit___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vcomb_unit___024root___eval_triggers_vec__stl(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_triggers_vec__stl\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vcomb_unit___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcomb_unit___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vcomb_unit___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vcomb_unit___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___trigger_anySet__stl\n"); );
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

void Vcomb_unit___024root___ico_sequent__TOP__0(Vcomb_unit___024root* vlSelf);

VL_ATTR_COLD void Vcomb_unit___024root___eval_stl(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_stl\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vcomb_unit___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vcomb_unit___024root___eval_phase__stl(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___eval_phase__stl\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcomb_unit___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcomb_unit___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vcomb_unit___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vcomb_unit___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vcomb_unit___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcomb_unit___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vcomb_unit___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcomb_unit___024root___ctor_var_reset(Vcomb_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcomb_unit___024root___ctor_var_reset\n"); );
    Vcomb_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 510903276987443985ull);
    vlSelf->b = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16900879642891266615ull);
    vlSelf->op = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3630531923276091163ull);
    vlSelf->y = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11123243248953317070ull);
    vlSelf->err_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13275017405815594325ull);
    vlSelf->err_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3923452998542990170ull);
    vlSelf->err_div_zero = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18201362450266862548ull);
    vlSelf->err_flag = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15846061587655420913ull);
    vlSelf->err_sat = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11790580627754427477ull);
    vlSelf->comb_unit__DOT__temp = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 13451677356873335253ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Valu_fsm.h for the primary calling header

#include "Valu_fsm__pch.h"

VL_ATTR_COLD void Valu_fsm___024root___eval_static(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_static\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

VL_ATTR_COLD void Valu_fsm___024root___eval_initial(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_initial\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Valu_fsm___024root___eval_final(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_final\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Valu_fsm___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Valu_fsm___024root___eval_phase__stl(Valu_fsm___024root* vlSelf);

VL_ATTR_COLD void Valu_fsm___024root___eval_settle(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_settle\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Valu_fsm___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/Users/user/Desktop/StressTest/aat-rtl/alu_fsm.v", 22, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Valu_fsm___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Valu_fsm___024root___eval_triggers_vec__stl(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_triggers_vec__stl\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Valu_fsm___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Valu_fsm___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Valu_fsm___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Valu_fsm___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Valu_fsm___024root___stl_sequent__TOP__0(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___stl_sequent__TOP__0\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.state_out = vlSelfRef.alu_fsm__DOT__state;
}

VL_ATTR_COLD void Valu_fsm___024root___eval_stl(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_stl\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.state_out = vlSelfRef.alu_fsm__DOT__state;
    }
}

VL_ATTR_COLD bool Valu_fsm___024root___eval_phase__stl(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___eval_phase__stl\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Valu_fsm___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Valu_fsm___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Valu_fsm___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Valu_fsm___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Valu_fsm___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Valu_fsm___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Valu_fsm___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge rst)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Valu_fsm___024root___ctor_var_reset(Valu_fsm___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Valu_fsm___024root___ctor_var_reset\n"); );
    Valu_fsm__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 510903276987443985ull);
    vlSelf->b = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16900879642891266615ull);
    vlSelf->op = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3630531923276091163ull);
    vlSelf->y = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11123243248953317070ull);
    vlSelf->err_div_zero = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18201362450266862548ull);
    vlSelf->err_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13275017405815594325ull);
    vlSelf->err_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3923452998542990170ull);
    vlSelf->state_out = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16606792248447486632ull);
    vlSelf->alu_fsm__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 589688567056368789ull);
    vlSelf->alu_fsm__DOT__a_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14779528760387371588ull);
    vlSelf->alu_fsm__DOT__b_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7855667441855252630ull);
    vlSelf->alu_fsm__DOT__op_reg = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2216936950795880133ull);
    vlSelf->alu_fsm__DOT__result_wide = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 16733582928384578887ull);
    vlSelf->alu_fsm__DOT__accumulator = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10785241524996401675ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

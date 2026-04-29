// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline_unit.h for the primary calling header

#include "Vpipeline_unit__pch.h"

VL_ATTR_COLD void Vpipeline_unit___024root___eval_static(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_static\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

VL_ATTR_COLD void Vpipeline_unit___024root___eval_initial(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_initial\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vpipeline_unit___024root___eval_final(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_final\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vpipeline_unit___024root___eval_settle(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___eval_settle\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vpipeline_unit___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpipeline_unit___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vpipeline_unit___024root___trigger_anySet__act(triggers))))) {
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

VL_ATTR_COLD void Vpipeline_unit___024root___ctor_var_reset(Vpipeline_unit___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpipeline_unit___024root___ctor_var_reset\n"); );
    Vpipeline_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 510903276987443985ull);
    vlSelf->b = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16900879642891266615ull);
    vlSelf->op = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3630531923276091163ull);
    vlSelf->y = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11123243248953317070ull);
    vlSelf->err_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13275017405815594325ull);
    vlSelf->err_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3923452998542990170ull);
    vlSelf->err_hazard = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8301816362506115031ull);
    vlSelf->err_sat = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11790580627754427477ull);
    vlSelf->pipeline_unit__DOT__a1 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6673399157396232621ull);
    vlSelf->pipeline_unit__DOT__b1 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4122752240653817846ull);
    vlSelf->pipeline_unit__DOT__a2 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 107383227787735677ull);
    vlSelf->pipeline_unit__DOT__b2 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12903997981947928373ull);
    vlSelf->pipeline_unit__DOT__res = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14614761497552286964ull);
    vlSelf->pipeline_unit__DOT__op1 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2337416025511140327ull);
    vlSelf->pipeline_unit__DOT__op2 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 912094969100545208ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_ecc.h for the primary calling header

#include "Vfifo_ecc__pch.h"

VL_ATTR_COLD void Vfifo_ecc___024root___eval_static(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_static\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
}

VL_ATTR_COLD void Vfifo_ecc___024root___eval_initial(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_initial\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vfifo_ecc___024root___eval_final(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_final\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vfifo_ecc___024root___eval_settle(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___eval_settle\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vfifo_ecc___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_ecc___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vfifo_ecc___024root___trigger_anySet__act(triggers))))) {
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

VL_ATTR_COLD void Vfifo_ecc___024root___ctor_var_reset(Vfifo_ecc___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_ecc___024root___ctor_var_reset\n"); );
    Vfifo_ecc__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->write_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7858586797580960854ull);
    vlSelf->read_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13081553017976621511ull);
    vlSelf->data_in = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10574596302020702150ull);
    vlSelf->burst_len = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3894673251107555288ull);
    vlSelf->data_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11675680895196038875ull);
    vlSelf->err_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13275017405815594325ull);
    vlSelf->err_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3923452998542990170ull);
    vlSelf->err_ecc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12904509032181799408ull);
    vlSelf->err_ptr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7122263982052866294ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->fifo_ecc__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 361095271526269627ull);
    }
    vlSelf->fifo_ecc__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7764361774421718065ull);
    vlSelf->fifo_ecc__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11989160734180747219ull);
    vlSelf->fifo_ecc__DOT__count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11780534123553391281ull);
    vlSelf->fifo_ecc__DOT__temp = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 8873779819351496708ull);
    vlSelf->fifo_ecc__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 688111840314047320ull);
    vlSelf->fifo_ecc__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15273709702635221160ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

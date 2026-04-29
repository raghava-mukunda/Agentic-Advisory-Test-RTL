// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcomb_unit__pch.h"

//============================================================
// Constructors

Vcomb_unit::Vcomb_unit(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcomb_unit__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , op{vlSymsp->TOP.op}
    , y{vlSymsp->TOP.y}
    , err_overflow{vlSymsp->TOP.err_overflow}
    , err_underflow{vlSymsp->TOP.err_underflow}
    , err_div_zero{vlSymsp->TOP.err_div_zero}
    , err_flag{vlSymsp->TOP.err_flag}
    , err_sat{vlSymsp->TOP.err_sat}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcomb_unit::Vcomb_unit(const char* _vcname__)
    : Vcomb_unit(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcomb_unit::~Vcomb_unit() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcomb_unit___024root___eval_debug_assertions(Vcomb_unit___024root* vlSelf);
#endif  // VL_DEBUG
void Vcomb_unit___024root___eval_static(Vcomb_unit___024root* vlSelf);
void Vcomb_unit___024root___eval_initial(Vcomb_unit___024root* vlSelf);
void Vcomb_unit___024root___eval_settle(Vcomb_unit___024root* vlSelf);
void Vcomb_unit___024root___eval(Vcomb_unit___024root* vlSelf);

void Vcomb_unit::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcomb_unit::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcomb_unit___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcomb_unit___024root___eval_static(&(vlSymsp->TOP));
        Vcomb_unit___024root___eval_initial(&(vlSymsp->TOP));
        Vcomb_unit___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcomb_unit___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcomb_unit::eventsPending() { return false; }

uint64_t Vcomb_unit::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcomb_unit::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcomb_unit___024root___eval_final(Vcomb_unit___024root* vlSelf);

VL_ATTR_COLD void Vcomb_unit::final() {
    Vcomb_unit___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcomb_unit::hierName() const { return vlSymsp->name(); }
const char* Vcomb_unit::modelName() const { return "Vcomb_unit"; }
unsigned Vcomb_unit::threads() const { return 1; }
void Vcomb_unit::prepareClone() const { contextp()->prepareClone(); }
void Vcomb_unit::atClone() const {
    contextp()->threadPoolpOnClone();
}

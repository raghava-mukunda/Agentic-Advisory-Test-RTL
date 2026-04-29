// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsat_alu__pch.h"

//============================================================
// Constructors

Vsat_alu::Vsat_alu(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsat_alu__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , op{vlSymsp->TOP.op}
    , y{vlSymsp->TOP.y}
    , err_overflow{vlSymsp->TOP.err_overflow}
    , err_div_zero{vlSymsp->TOP.err_div_zero}
    , err_saturation{vlSymsp->TOP.err_saturation}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vsat_alu::Vsat_alu(const char* _vcname__)
    : Vsat_alu(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsat_alu::~Vsat_alu() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsat_alu___024root___eval_debug_assertions(Vsat_alu___024root* vlSelf);
#endif  // VL_DEBUG
void Vsat_alu___024root___eval_static(Vsat_alu___024root* vlSelf);
void Vsat_alu___024root___eval_initial(Vsat_alu___024root* vlSelf);
void Vsat_alu___024root___eval_settle(Vsat_alu___024root* vlSelf);
void Vsat_alu___024root___eval(Vsat_alu___024root* vlSelf);

void Vsat_alu::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsat_alu::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsat_alu___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsat_alu___024root___eval_static(&(vlSymsp->TOP));
        Vsat_alu___024root___eval_initial(&(vlSymsp->TOP));
        Vsat_alu___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsat_alu___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsat_alu::eventsPending() { return false; }

uint64_t Vsat_alu::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsat_alu::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsat_alu___024root___eval_final(Vsat_alu___024root* vlSelf);

VL_ATTR_COLD void Vsat_alu::final() {
    Vsat_alu___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsat_alu::hierName() const { return vlSymsp->name(); }
const char* Vsat_alu::modelName() const { return "Vsat_alu"; }
unsigned Vsat_alu::threads() const { return 1; }
void Vsat_alu::prepareClone() const { contextp()->prepareClone(); }
void Vsat_alu::atClone() const {
    contextp()->threadPoolpOnClone();
}

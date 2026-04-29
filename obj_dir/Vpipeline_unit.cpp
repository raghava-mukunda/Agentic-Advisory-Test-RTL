// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vpipeline_unit__pch.h"

//============================================================
// Constructors

Vpipeline_unit::Vpipeline_unit(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vpipeline_unit__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , op{vlSymsp->TOP.op}
    , y{vlSymsp->TOP.y}
    , err_overflow{vlSymsp->TOP.err_overflow}
    , err_underflow{vlSymsp->TOP.err_underflow}
    , err_hazard{vlSymsp->TOP.err_hazard}
    , err_sat{vlSymsp->TOP.err_sat}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vpipeline_unit::Vpipeline_unit(const char* _vcname__)
    : Vpipeline_unit(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vpipeline_unit::~Vpipeline_unit() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vpipeline_unit___024root___eval_debug_assertions(Vpipeline_unit___024root* vlSelf);
#endif  // VL_DEBUG
void Vpipeline_unit___024root___eval_static(Vpipeline_unit___024root* vlSelf);
void Vpipeline_unit___024root___eval_initial(Vpipeline_unit___024root* vlSelf);
void Vpipeline_unit___024root___eval_settle(Vpipeline_unit___024root* vlSelf);
void Vpipeline_unit___024root___eval(Vpipeline_unit___024root* vlSelf);

void Vpipeline_unit::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpipeline_unit::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vpipeline_unit___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vpipeline_unit___024root___eval_static(&(vlSymsp->TOP));
        Vpipeline_unit___024root___eval_initial(&(vlSymsp->TOP));
        Vpipeline_unit___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vpipeline_unit___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vpipeline_unit::eventsPending() { return false; }

uint64_t Vpipeline_unit::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vpipeline_unit::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vpipeline_unit___024root___eval_final(Vpipeline_unit___024root* vlSelf);

VL_ATTR_COLD void Vpipeline_unit::final() {
    Vpipeline_unit___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vpipeline_unit::hierName() const { return vlSymsp->name(); }
const char* Vpipeline_unit::modelName() const { return "Vpipeline_unit"; }
unsigned Vpipeline_unit::threads() const { return 1; }
void Vpipeline_unit::prepareClone() const { contextp()->prepareClone(); }
void Vpipeline_unit::atClone() const {
    contextp()->threadPoolpOnClone();
}

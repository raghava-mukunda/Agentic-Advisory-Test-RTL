// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Valu_fsm__pch.h"

//============================================================
// Constructors

Valu_fsm::Valu_fsm(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Valu_fsm__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , op{vlSymsp->TOP.op}
    , y{vlSymsp->TOP.y}
    , err_div_zero{vlSymsp->TOP.err_div_zero}
    , err_overflow{vlSymsp->TOP.err_overflow}
    , err_underflow{vlSymsp->TOP.err_underflow}
    , state_out{vlSymsp->TOP.state_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Valu_fsm::Valu_fsm(const char* _vcname__)
    : Valu_fsm(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Valu_fsm::~Valu_fsm() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Valu_fsm___024root___eval_debug_assertions(Valu_fsm___024root* vlSelf);
#endif  // VL_DEBUG
void Valu_fsm___024root___eval_static(Valu_fsm___024root* vlSelf);
void Valu_fsm___024root___eval_initial(Valu_fsm___024root* vlSelf);
void Valu_fsm___024root___eval_settle(Valu_fsm___024root* vlSelf);
void Valu_fsm___024root___eval(Valu_fsm___024root* vlSelf);

void Valu_fsm::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Valu_fsm::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Valu_fsm___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Valu_fsm___024root___eval_static(&(vlSymsp->TOP));
        Valu_fsm___024root___eval_initial(&(vlSymsp->TOP));
        Valu_fsm___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Valu_fsm___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Valu_fsm::eventsPending() { return false; }

uint64_t Valu_fsm::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Valu_fsm::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Valu_fsm___024root___eval_final(Valu_fsm___024root* vlSelf);

VL_ATTR_COLD void Valu_fsm::final() {
    Valu_fsm___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Valu_fsm::hierName() const { return vlSymsp->name(); }
const char* Valu_fsm::modelName() const { return "Valu_fsm"; }
unsigned Valu_fsm::threads() const { return 1; }
void Valu_fsm::prepareClone() const { contextp()->prepareClone(); }
void Valu_fsm::atClone() const {
    contextp()->threadPoolpOnClone();
}

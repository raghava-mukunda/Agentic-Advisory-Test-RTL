// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vfifo_ecc__pch.h"

//============================================================
// Constructors

Vfifo_ecc::Vfifo_ecc(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vfifo_ecc__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , write_en{vlSymsp->TOP.write_en}
    , read_en{vlSymsp->TOP.read_en}
    , data_in{vlSymsp->TOP.data_in}
    , burst_len{vlSymsp->TOP.burst_len}
    , data_out{vlSymsp->TOP.data_out}
    , err_overflow{vlSymsp->TOP.err_overflow}
    , err_underflow{vlSymsp->TOP.err_underflow}
    , err_ecc{vlSymsp->TOP.err_ecc}
    , err_ptr{vlSymsp->TOP.err_ptr}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vfifo_ecc::Vfifo_ecc(const char* _vcname__)
    : Vfifo_ecc(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vfifo_ecc::~Vfifo_ecc() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vfifo_ecc___024root___eval_debug_assertions(Vfifo_ecc___024root* vlSelf);
#endif  // VL_DEBUG
void Vfifo_ecc___024root___eval_static(Vfifo_ecc___024root* vlSelf);
void Vfifo_ecc___024root___eval_initial(Vfifo_ecc___024root* vlSelf);
void Vfifo_ecc___024root___eval_settle(Vfifo_ecc___024root* vlSelf);
void Vfifo_ecc___024root___eval(Vfifo_ecc___024root* vlSelf);

void Vfifo_ecc::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfifo_ecc::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vfifo_ecc___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vfifo_ecc___024root___eval_static(&(vlSymsp->TOP));
        Vfifo_ecc___024root___eval_initial(&(vlSymsp->TOP));
        Vfifo_ecc___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vfifo_ecc___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vfifo_ecc::eventsPending() { return false; }

uint64_t Vfifo_ecc::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vfifo_ecc::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vfifo_ecc___024root___eval_final(Vfifo_ecc___024root* vlSelf);

VL_ATTR_COLD void Vfifo_ecc::final() {
    Vfifo_ecc___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vfifo_ecc::hierName() const { return vlSymsp->name(); }
const char* Vfifo_ecc::modelName() const { return "Vfifo_ecc"; }
unsigned Vfifo_ecc::threads() const { return 1; }
void Vfifo_ecc::prepareClone() const { contextp()->prepareClone(); }
void Vfifo_ecc::atClone() const {
    contextp()->threadPoolpOnClone();
}

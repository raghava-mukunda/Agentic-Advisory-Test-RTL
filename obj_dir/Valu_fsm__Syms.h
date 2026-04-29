// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VALU_FSM__SYMS_H_
#define VERILATED_VALU_FSM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Valu_fsm.h"

// INCLUDE MODULE CLASSES
#include "Valu_fsm___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Valu_fsm__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Valu_fsm* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Valu_fsm___024root             TOP;

    // CONSTRUCTORS
    Valu_fsm__Syms(VerilatedContext* contextp, const char* namep, Valu_fsm* modelp);
    ~Valu_fsm__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard

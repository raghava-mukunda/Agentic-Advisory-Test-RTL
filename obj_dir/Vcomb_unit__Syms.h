// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCOMB_UNIT__SYMS_H_
#define VERILATED_VCOMB_UNIT__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcomb_unit.h"

// INCLUDE MODULE CLASSES
#include "Vcomb_unit___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vcomb_unit__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcomb_unit* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcomb_unit___024root           TOP;

    // CONSTRUCTORS
    Vcomb_unit__Syms(VerilatedContext* contextp, const char* namep, Vcomb_unit* modelp);
    ~Vcomb_unit__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard

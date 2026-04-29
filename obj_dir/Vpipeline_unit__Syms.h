// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPIPELINE_UNIT__SYMS_H_
#define VERILATED_VPIPELINE_UNIT__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vpipeline_unit.h"

// INCLUDE MODULE CLASSES
#include "Vpipeline_unit___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vpipeline_unit__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vpipeline_unit* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vpipeline_unit___024root       TOP;

    // CONSTRUCTORS
    Vpipeline_unit__Syms(VerilatedContext* contextp, const char* namep, Vpipeline_unit* modelp);
    ~Vpipeline_unit__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard

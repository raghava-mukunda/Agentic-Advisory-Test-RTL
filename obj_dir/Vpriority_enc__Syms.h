// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPRIORITY_ENC__SYMS_H_
#define VERILATED_VPRIORITY_ENC__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vpriority_enc.h"

// INCLUDE MODULE CLASSES
#include "Vpriority_enc___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vpriority_enc__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vpriority_enc* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vpriority_enc___024root        TOP;

    // CONSTRUCTORS
    Vpriority_enc__Syms(VerilatedContext* contextp, const char* namep, Vpriority_enc* modelp);
    ~Vpriority_enc__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard

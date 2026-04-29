// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSAT_ALU__SYMS_H_
#define VERILATED_VSAT_ALU__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vsat_alu.h"

// INCLUDE MODULE CLASSES
#include "Vsat_alu___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vsat_alu__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vsat_alu* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vsat_alu___024root             TOP;

    // CONSTRUCTORS
    Vsat_alu__Syms(VerilatedContext* contextp, const char* namep, Vsat_alu* modelp);
    ~Vsat_alu__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard

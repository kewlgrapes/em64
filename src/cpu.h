//cpu.h
//  Nick Becker
//  19 November, 2015

// requires <stdint.h>

#ifndef CPU_H
#define CPU_H

// special opcodes
#define CPU_SPECIAL 0x00
#define CPU_REGIMM  0x01  // BLTZ
#define CPU_COP0    0x10  // MFC0
#define CPU_COP1    0x00  // C.F

// registers
uint64_t cpu_gen_reg[32];
uint64_t cpu_float_reg[32];
uint32_t cpu_pc;
uint32_t cpu_ir;

// functions

/*
void cpu_init();

Initializes the program counter.
*/
#define cpu_init() {cpu_pc = 0;}

uint32_t cpu_fetch();

#endif

//cpu.h
//  Nick Becker
//  19 November, 2015

// requires <stdint.h>

#ifndef CPU_H
#define CPU_H

// special opcodes
#define CPU_OP_SPECIAL 0x00 
#define CPU_OP_REGIMM  0x01
#define CPU_OP_COP0    0x10
#define CPU_OP_COP1     0x11

// registers
uint64_t cpu_gen_reg[32];
uint64_t cpu_float_reg[32];
uint64_t cpu_pc;
uint32_t cpu_ir;

// functions

/*
void cpu_init();

Initializes the program counter.
*/
#define cpu_init() {cpu_pc = 0;}

uint32_t cpu_fetch();
uint64_t cpu_cycle();

void cpu_snapshot();


#endif

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

/*
void cpu_init();

Initializes the program counter.
*/
#define cpu_init() {cpu_pc = 0;}

/*
int cpu_bit_at(int_t n, int k)

Return the kth bit of a 64 bit integer. Assumes that 0 is the least
significant bit. No bounds checking.
*/
#define cpu_bit_at(n, k) ((n) >> (k) & 1)

/*
int cpu_bit_range(int n, int l, int r)

Return a bit range starting at position l and ending at position r.
Assumes that 0 is the least significant bit. No bounds checking.
*/
#define cpu_bit_range(n,l,r) (x >> r) & ~(~0 << (l-r+1))

uint32_t cpu_fetch();
uint64_t cpu_cycle();

void cpu_snapshot();



#endif

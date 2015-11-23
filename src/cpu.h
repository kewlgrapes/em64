//cpu.h
//  Nick Becker
//  19 November, 2015

// requires <stdint.h>

#ifndef CPU_H
#define CPU_H

// masks to determine endianness
#define CPU_BIG_ENDIAN    0x80371240 // we will convert to this format
#define CPU_LIT_ENDIAN    0x40123780
#define CPU_BYTE_SWAPPED  0x37804012
#define CPU_WORD_SWAPPPED 0x12408037

// special opcodes
#define CPU_SPECIAL 0x00
#define CPU_REGIMM  0x01  // BLTZ
#define CPU_COP0    0x10  // MFC0
#define CPU_COP1    0x00  // C.F

// registers
static uint64_t cpu_gen_reg[32];
static uint64_t cpu_float_reg[32];

#endif

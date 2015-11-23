// cpu.c
//   Nick Becker
//   19 November, 2015

#include <stdint.h>
#include <stdio.h>

#include "memory.h"
#include "cpu.h"

uint32_t cpu_fetch() {
  /*
  Loads the next instruction into the IR and increments the PC. Returns
  the fetched instruction.
  */
  cpu_ir = *(uint32_t *)(mem_rom + cpu_pc);
  cpu_pc += 4;
  return cpu_ir;
}

uint64_t cpu_cycle() {
  /*
  Perform 1 CPU cycle. Returns the updated PC.
  31---------26-25-----21-20------16-----------------5--------0
  |   opcode   |   fmt   |    rt   |                | function|
  |------6----------5----------5-------------------------6-----
  */

  cpu_fetch();
  switch (cpu_ir >> 26) {
    case CPU_OP_SPECIAL:
      break;
    case CPU_OP_REGIMM:
      break;
    case CPU_OP_COP0:
      break;
    case CPU_OP_COP1:
      break;
    default:
      break; 
  }

  return cpu_pc;
}

void cpu_snapshot() {
  /*
  Display a snapshot of the current CPU state.
  */
  int i;

  // program counter
  printf("PC\t%08x/%08x\n",
    *(uint32_t *)(&cpu_pc + sizeof(uint32_t)),
    *(uint32_t *)&cpu_pc);

  // instruction register
  printf("IR\t         %08x\n", cpu_ir);

  // for testing
  for (i = 0; i < 32; i++) {
    cpu_gen_reg[i] = 0x12345678;
    cpu_float_reg[i] = 0x87654321;
  }

  // general and floating point registers
  for (i = 0; i < 32 * sizeof(uint64_t); i+=sizeof(uint64_t))
    printf("GR%02x\t%08x/%08x\tFR%02x\t%08x/%08x\n",
      i >> 3,
      *(uint32_t *)(cpu_gen_reg + i + sizeof(uint32_t)),
      *(uint32_t *)(cpu_gen_reg + i),
      i << 3,
      *(uint32_t *)(cpu_float_reg + i + sizeof(uint32_t)),
      *(uint32_t *)(cpu_float_reg + i));
}

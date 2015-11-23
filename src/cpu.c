// cpu.c
//   Nick Becker
//   19 November, 2015

#include <stdint.h>

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

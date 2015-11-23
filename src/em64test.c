//testem64test.c
//  Nick Becker
//  23 November, 2015

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "fpu.h"
#include "graphics.h"
#include "locale.h"
#include "memory.h"
#include "mmu.h"
#include "rcp.h"

int main(int argc, char **argv) {
  /*
  Main entry point for program.
  */

  // initialize locale/logging settings
  if (argc)
    loc_init(argv[0], LOC_DEBUG);
  else
    loc_init("em64", LOC_DEBUG);

  // print usage message if invoked incorrectly
  //if (argc < 2) {
  //  loc_print_usage();
  //  return 1;
  //}

  // read program into memory
  //mem_read(argv[1]);

  // initialize cpu and read some instructions
  //cpu_init();
  //cpu_cycle();
  //cpu_snapshot();

  //free(mem_rom);

  // 0000 0000 0000 1001 1111 1011 1111 0001
  uint32_t x = 654321; // 0x0009FBF1
  //int i;
  //for (i = 0; i < 32; i++)
  //  printf("%d\n", cpu_bit_at(x, i));
  printf("%x\n", cpu_bit_range(x, 3, 0));
  printf("%x\n", cpu_bit_range(x, 7, 4));
  printf("%x\n", cpu_bit_range(x, 11, 8));
  printf("%x\n", cpu_bit_range(x, 31, 12));

  loc_log(LOC_INFO, INF_TERMINATE);
  return 0;
}

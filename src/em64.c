//em64.c
//  Nick Becker
//  19 November, 2015

#include <stdint.h>
#include <stdio.h>

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
  // record the program's invocation name
  if (argc)
    loc_prog_name = argv[0];

  if (argc < 2) {
    loc_print_usage();
    return 1;
  }
  loc_info(INF_READ, (int)mem_read(argv[1]), argv[1]);
  fix_endianness();

  return 0;
}

//em64test.c
//  Nick Becker
//  23 November, 2015
//  Runs regression tests.

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "em64test.h"

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

  // cpu tests
  tst_bit_at();
  tst_bit_range();

  return 0;
}

void tst_bit_at() {
  /*
  Tests cpu_bit_at() from cpu.h.
  */
  uint16_t n0 = 0xFFFF;
  uint32_t n1 = 0xFFFFFFFF;
  uint64_t n2 = 0xFFFFFFFFFFFFFFFF;
  int i;

  uint16_t x = 0;
  for (i = 0; i < 16; i++)
    x += cpu_bit_at(n0, i) << i;
  assert(x == n0);

  uint32_t y = 0;
  for (i = 0; i < 32; i++)
    y += cpu_bit_at(n1, i) << i;
  assert(y == n1);

  uint64_t z = 0;
  for (i = 0; i < 64; i++)
    z += cpu_bit_at(n2, i) << i;
  assert(z == n2);
}

void tst_bit_range() {
  uint16_t n0 = 0xFB95;
  uint32_t n1 = 0x13579BDF;
  uint64_t n2 = 0xFEDCBA9876543210;

  int i, j;
  
  for (i = 0; i < 16; i++) {
    assert(cpu_bit_range(n0, 15, i) == n0 >> i);
    assert(cpu_bit_range(n0, 15 - i, 0) == (n0 & (0xFFFF >> i)));
  }

  for (i = 0; i < 32; i++) {
    assert(cpu_bit_range(n1, 31, i) == n1 >> i);
    assert(cpu_bit_range(n1, 31 - i, 0) == (n1 & (0xFFFFFFFF >> i)));
  }

  //printf("%" PRIx64 "\n", ~(0xFFFFFFFFFFFFFFFF << 64));
  //printf("%" PRIx64 "\n", n2 & (0xFFFFFFFFFFFFFFFF >> 0));
  //printf("%" PRIx64 "\n", cpu_bit_range(n2, 63, 0));

  // this does appear to work for i = 0 as well... ^
  // for (i = 0; i <64; i++)
  for (i = 1; i < 64; i++) {
    assert(cpu_bit_range(n2, 63, i) == n2 >> i);
    assert(cpu_bit_range(n2, 63 - i, 0) == (n2 & (0xFFFFFFFFFFFFFFFF >> i)));
  }
  
}

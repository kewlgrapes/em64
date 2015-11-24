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
  loc_init(LOC_ERROR, argv[0]);

  // memory tests
  tst_fix_endianness();

  // cpu tests
  tst_bit_at();
  tst_bit_range();
  tst_cpu_fetch();

  // great job
  return 0;
}

///////////////////////////////////////////////////////////
// memory tests
///////////////////////////////////////////////////////////

void tst_fix_endianness() {
  /*
  Test mem_fix_endianness() from memory.c.
  */
  uint32_t rom[TST_ROM_LEN];

  int i, j;
  for (j = 0; j < TST_ROM_CNT; j++) {
    for (i = 0; i < TST_ROM_LEN; i++)
      rom[i] = TST_ROM[j][i];
    mem_fix_endianness((uint8_t *)rom, TST_ROM_LEN * sizeof(uint32_t));

    // ensure the ROM was converted to big endian format
    for (i = 0; i < TST_ROM_LEN; i++)
      assert(rom[i] == TST_ROM[0][i]);
  }
}

///////////////////////////////////////////////////////////
// cpu tests
///////////////////////////////////////////////////////////

void tst_bit_at() {
  /*
  Test cpu_bit_at() from cpu.h.
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
  /*
  Test cpu_bit_range() from cpu.h.
  */
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

void tst_cpu_fetch() {
  /*
  Tests cpu_fetch() from cpu.c.
  */
  int i, j;

  mem_rom_len = TST_ROM_LEN * sizeof(uint32_t);
  for (j = 0; j < TST_ROM_CNT; j++) {
    mem_rom = (uint8_t *)TST_ROM[j];
    cpu_init();
    assert(cpu_pc == 0);
    for(i = 0; i < TST_ROM_LEN; i++) {
      assert(cpu_fetch() == TST_ROM[j][i]);
      assert(cpu_ir == TST_ROM[j][i]);
      assert(cpu_pc == (i * sizeof(uint32_t) + sizeof(uint32_t)));
    }
  }
}

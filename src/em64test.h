//em64test.h
//  Nick Becker
//  23 November, 2015

#ifndef TST_H
#define TST_H

// these are all thes ame test ROM, but the format of each is different
#define TST_ROM_CNT 4
#define TST_ROM_LEN 16 // number of instructions in each ROM

static uint32_t TST_ROM[4][16] = {
  // big endian
  { 0x80371240, 0x0000000f, 0x80246000, 0x00001444,
    0x635a2bff, 0x8b022326, 0x00000000, 0x00000000,
    0x53555045, 0x52204d41, 0x52494f20, 0x36342020,
    0x20202020, 0x00000000, 0x0000004e, 0x644d4500 },

  // little endian
  { 0x40123780, 0x0f000000, 0x00602480, 0x44140000,
    0xff2b5a63, 0x2623028b, 0x00000000, 0x00000000,
    0x45505553, 0x414d2052, 0x204f4952, 0x20203436,
    0x20202020, 0x00000000, 0x4e000000, 0x00454d64 },

  // byte swapped
  { 0x37804012, 0x00000f00, 0x24800060, 0x00004414,
    0x5a63ff2b, 0x028b2623, 0x00000000, 0x00000000,
    0x55534550, 0x2052414d, 0x4952204f, 0x34362020,
    0x20202020, 0x00000000, 0x00004e00, 0x4d640045 },

  // word swapped
  { 0x12408037, 0x000f0000, 0x60008024, 0x14440000,
    0x2bff635a, 0x23268b02, 0x00000000, 0x00000000,
    0x50455355, 0x4d415220, 0x4f205249, 0x20203634,
    0x20202020, 0x00000000, 0x004e0000, 0x4500644d}};

void tst_bit_at();
void tst_bit_range();
void tst_fix_endianness();
void tst_cpu_fetch();

#endif

//memory.h
//  Nick Becker
//  19 November, 2015

#ifndef MEMORY_H
#define MEMORY_H

// masks to determine endianness
// all valid rom files should start with one of these
#define MEM_BIG_ENDIAN   0x80371240 // we will convert into this format
#define MEM_LIT_ENDIAN   0x40123780
#define MEM_BYTE_SWAPPED 0x37804012
#define MEM_WORD_SWAPPED 0x12408037

// pointer to the ROM stored in memory
uint8_t *mem_rom;
long mem_rom_len;

// functions
long mem_read(char *file_name);
long mem_fix_endianness(uint8_t *rom, long rom_len);

#endif

//memory.c
//  Nick Becker
//  19 November, 2015

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "locale.h"
#include "memory.h"

long mem_read(char *file_name) {
  /*
  Read an entire ROM file into memory. Returns the number of bytes read.
  */
  FILE *fd;
  long fsize;

  fd = fopen(file_name, "rb");
  if (fd)
    loc_log(LOC_INFO, INF_OPENED, file_name);
  else {
    loc_fatal(ERR_BADOPEN, file_name);
    return 0;
  }

  // get length of file and allocate memory
  fseek(fd, 0, SEEK_END);
  fsize = ftell(fd);

  // allocate memory and read in the entire file
  mem_rom = (uint32_t *)malloc(fsize);
  if (mem_rom) {
    fseek(fd, 0, SEEK_SET);
    if (!fread(mem_rom, fsize, 1, fd))
      loc_fatal(ERR_BADREAD, file_name);
    mem_rom_len = fsize;
    loc_log(LOC_INFO, INF_READ, fsize, file_name);
  }
  else
    loc_fatal(ERR_MALLOC, 0, fsize);
  fclose(fd);
  loc_log(LOC_INFO, INF_CLOSED, file_name);

  // convert to big endian format
  mem_fix_endianness(mem_rom, fsize);
  mem_rom_len = fsize;
  return fsize;
}

long mem_fix_endianness(uint32_t *rom, long rom_len) {
  /*
  Reorders the bytes of the ROM into big endian format. Returns the number
  of bytes converted.
  */
  long i;
  char *cur_word = (char *)rom;

  // check the first word in the rom
  switch(*rom) {
    // 0x80371240
    case MEM_BIG_ENDIAN:
      i = 0;
      break;

    // 0x40123780:
    case MEM_LIT_ENDIAN:
      loc_log(LOC_DEBUG, INF_LITENDIAN); 
      for (i = 0; i < rom_len; i += 4) {
        *(cur_word+0) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+0) ^ *(cur_word+3);
        *(cur_word+0) ^= *(cur_word+3);
        *(cur_word+1) ^= *(cur_word+2);
        *(cur_word+2) = *(cur_word+1) ^ *(cur_word+2);
        *(cur_word+1) ^= *(cur_word+2);
        cur_word += 4;
      }
      break;
    
    // 0x37804012
    case MEM_BYTE_SWAPPED:
      loc_log(LOC_DEBUG, INF_BYTESWAP); 
      for (i = 0; i < rom_len; i += 4) {
        *(cur_word+0) ^= *(cur_word+1);
        *(cur_word+1) = *(cur_word+0) ^ *(cur_word+1);
        *(cur_word+0) ^= *(cur_word+1);
        *(cur_word+2) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+2) ^ *(cur_word+3);
        *(cur_word+2) ^= *(cur_word+3);
        cur_word += 4;
      }
      break;

    // 0x12408037
    case MEM_WORD_SWAPPED:
      loc_log(LOC_DEBUG, INF_WORDSWAP); 
      for (i = 0; i < rom_len; i += 4) {
        *(cur_word+0) ^= *(cur_word+2);
        *(cur_word+2) = *(cur_word+0) ^ *(cur_word+2);
        *(cur_word+0) ^= *(cur_word+2);
        *(cur_word+1) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+1) ^ *(cur_word+3);
        *(cur_word+1) ^= *(cur_word+3);
        cur_word += 4;
      }
      break;
    default:
      loc_fatal(ERR_UNKFMT);
      return i;
  }
  loc_log(LOC_DEBUG, INF_CONVERTED, i >> 2);
  return i;
}

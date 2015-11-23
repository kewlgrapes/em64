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
    loc_info(INF_OPENED, file_name);
  else {
    loc_error(ERR_BADOPEN, file_name);
    return 0;
  }

  // get length of file and allocate memory
  fseek(fd, 0, SEEK_END);
  fsize = ftell(fd);

  // allocate memory and read the entire file
  mem_rom = (char *)malloc(fsize);
  if (mem_rom) {
    fseek(fd, 0, SEEK_SET);
    if (!fread(mem_rom, fsize, 1, fd)) {
      
    }
  }
  else
    loc_error(ERR_MALLOC, 0, fsize);
    
  fclose(fd);
  loc_info(INF_CLOSED, file_name);
  mem_rom_size = fsize;
  return fsize;
}

long fix_endianness() {
  /*
  Reorders the bytes of the ROM into big endian format. Assumes the ROM
  has already been read into memory (pointed to by *mem_rom). Returns
  the number of bytes converted.
  */
  long i;
  uint32_t *first_word = (uint32_t *)mem_rom;
  char *cur_word = (char *)mem_rom;

  switch(*first_word) {
    // 0x80371240
    case MEM_BIG_ENDIAN:
      i = 0;
      break;

    // 0x40123780:
    case MEM_LIT_ENDIAN:
      loc_info(INF_LITENDIAN); 
      for (i = 0; i < mem_rom_size; i += 4) {
        *(cur_word+0) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+0) ^ *(cur_word+3);
        *(cur_word+0) ^= *(cur_word+3);
        *(cur_word+1) ^= *(cur_word+2);
        *(cur_word+2) = *(cur_word+1) ^ *(cur_word+2);
        *(cur_word+1) ^= *(cur_word+2);
        cur_word += 4;
      } while (i < mem_rom_size);
      break;
    
    // 0x37804012
    case MEM_BYTE_SWAPPED:
      loc_info(INF_BYTESWAP); 
      for (i = 0; i < mem_rom_size; i += 4) {
        *(cur_word+0) ^= *(cur_word+1);
        *(cur_word+1) = *(cur_word+0) ^ *(cur_word+1);
        *(cur_word+0) ^= *(cur_word+1);
        *(cur_word+2) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+2) ^ *(cur_word+3);
        *(cur_word+2) ^= *(cur_word+3);
        cur_word += 4;
      } while (i < mem_rom_size);
      break;

    // 0x12408037
    case MEM_WORD_SWAPPED:
      loc_info(INF_WORDSWAP); 
      for (i = 0; i < mem_rom_size; i += 4) {
        *(cur_word+0) ^= *(cur_word+2);
        *(cur_word+2) = *(cur_word+0) ^ *(cur_word+2);
        *(cur_word+0) ^= *(cur_word+2);
        *(cur_word+1) ^= *(cur_word+3);
        *(cur_word+3) = *(cur_word+1) ^ *(cur_word+3);
        *(cur_word+1) ^= *(cur_word+3);
        cur_word += 4;
      } while (i < mem_rom_size);
      break;
    default:
      loc_error(ERR_UNKFMT);
  }
  loc_info(INF_CONVERTED, i);
}

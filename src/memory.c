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

void fix_endianness() {
  /*
  Reorders the bytes of the ROM into big endian format. Assumes the ROM
  has already been read into memory (pointed to by *mem_rom);
  */
  uint32_t *cur_word = (uint32_t *)mem_rom;
  printf("0x%08x\n", *cur_word);
}

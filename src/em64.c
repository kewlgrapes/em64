//em64.c
//  Nick Becker
//  19 November, 2015

#include <stdint.h>
#include <stdio.h>

#include "cpu.h"
#include "fpu.h"
#include "graphics.h"
#include "memory.h"
#include "mmu.h"
#include "rcp.h"

int main(int argc, char **argv) {
  /*
  */
  if (argc > 1)
    if (argv[1])
      read_file(argv[1]);
  return 0;
}

int read_file(char *filename) {
  char buff[20];
  FILE *f;
  printf("opening %s\n", filename);
  f = fopen(filename, "rb");
  if (!f)
    return 0;
  printf("opened %s\n", filename);

  fread(buff, sizeof(buff), 1, f);
  int i;
  for (i=0; i < sizeof(buff); i+=4)
    printf("%02b:%02x:%02x:%02x\n",
      buff[i] & 0xff,
      buff[1+i] & 0xff,
      buff[2+i] & 0xff,
      buff[3+i] & 0xff);

  fclose(f);
  printf("closed %s\n", filename);
  return sizeof(buff);
}

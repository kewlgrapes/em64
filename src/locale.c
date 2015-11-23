// locale.c
//   Nick Becker
//   22 November, 2015

// requires stdarg.h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "locale.h"

///////////////////////////////////////////////////////////
// error reporting
///////////////////////////////////////////////////////////

void loc_info(loc_code lc, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, lc);
  fprintf(stderr, "[%s] Info (%d): ", loc_prog_name, lc);
  vfprintf(stderr, loc_messages[lc], arg_ptr);
  fputc('\n', stderr);
  va_end(arg_ptr);
}

void loc_warning(loc_code lc, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, lc);
  fprintf(stderr, "[%s] Warning (%d): ", loc_prog_name, lc);
  vfprintf(stderr, loc_messages[lc], arg_ptr);
  fputc('\n', stderr);
  va_end(arg_ptr);
}

void loc_error(loc_code lc, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, lc);
  fprintf(stderr, "[%s] Fatal Error (%d): ", loc_prog_name, lc);
  vfprintf(stderr, loc_messages[lc], arg_ptr);
  fputc('\n', stderr);
  va_end(arg_ptr);
  exit(1);
}

///////////////////////////////////////////////////////////
// other stuff
///////////////////////////////////////////////////////////

void loc_print_usage() {
  fputs("Usage: em64 [OPTION]... [FILE]\n", stdout);
  fputs("\n", stdout);
  fputs("...except there are no OPTIONs, yet!\n", stdout);
}

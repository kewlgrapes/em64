// locale.c
//   Nick Becker
//   22 November, 2015

// requires stdarg.h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "locale.h"

void loc_init(char *pn, loc_level ll) {
  loc_prog_name = pn;
  loc_logging_level = ll;
  loc_log(LOC_INFO, DEB_LOGLEVEL, LOC_LEVEL[ll]);
}

///////////////////////////////////////////////////////////
// error reporting
///////////////////////////////////////////////////////////

void loc_log(loc_level ll, loc_code lc, ...) {
  va_list arg_ptr;
  if (ll >= loc_logging_level) {
    va_start(arg_ptr, lc);
    fprintf(stdout, "[%s] %s: ", loc_prog_name, LOC_LEVEL[ll]);
    vfprintf(stdout, loc_messages[lc], arg_ptr);
    fputc('\n', stdout);
    va_end(arg_ptr);
  }
}

void loc_fatal(loc_code lc, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, lc);
  fprintf(stderr, "[%s] %s (%d): ", loc_prog_name, LOC_LEVEL[LOC_ERROR], lc);
  vfprintf(stderr, loc_messages[lc], arg_ptr);
  va_end(arg_ptr);
  fprintf(stderr, "\n[%s] %s\n", loc_prog_name, loc_messages[INF_TERMINATE]);
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

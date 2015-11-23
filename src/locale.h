//locale.h
//  Nick Becker
//  19 November, 2015

char *loc_prog_name;

// to encode messages for various errors
typedef enum loc_code {
  // file access
  INF_OPENED,
  INF_CLOSED,
  INF_READ,
  ERR_BADOPEN,
  ERR_BADREAD,

  // memory access
  ERR_MALLOC
} loc_code;

// list of message text formats, mapped by loc_code enum
static const char *loc_messages[] = {
  // file access
  "Opened %s",
  "Closed %s",
  "Read %ld bytes from %s",
  "Failed to open %s",
  "Failed to read from %s",

  // memory access
  "Failed to allocate memory (%d allocated/%d requested)"
};

// logging/error reporting
void loc_info(loc_code lc, ...);
void loc_warning(loc_code lc, ...);
void loc_error(loc_code lc, ...);

// other stuff
void loc_print_usage();

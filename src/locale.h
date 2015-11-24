//locale.h
//  Nick Becker
//  19 November, 2015

// program invocation name
char *loc_prog_name;

// logging levels
typedef enum loc_level {
  LOC_DEBUG,
  LOC_INFO,
  LOC_WARNING,
  LOC_ERROR
} loc_level;

static const char *LOC_LEVEL[] = {
  "DEBUG",
  "INFO",
  "WARNING",
  "FATAL ERROR"
};

loc_level loc_logging_level;

// to encode messages for various errors
typedef enum loc_code {
  // file access
  INF_OPENED,
  INF_CLOSED,
  INF_READ,
  ERR_BADOPEN,
  ERR_BADREAD,

  // memory access
  ERR_MALLOC,
  ERR_BOUNDS,

  // endianness conversion
  INF_BIGENDIAN,
  INF_LITENDIAN,
  INF_BYTESWAP,
  INF_WORDSWAP,
  INF_CONVERTED,
  ERR_UNKFMT,

  // cpu processing
  WAR_UNKINST,

  // misc
  DEB_LOGLEVEL,
  INF_TERMINATE
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
  "Failed to allocate memory (%d allocated/%d requested)",
  "Attempted to fetch memory past bounds (%d requested/%d total)",

  // endianness conversion
  "ROM is in big endian format",
  "Converting ROM to big endian format (from little endian)",
  "Converting ROM to big endian format (from byte swapped)",
  "Converting ROM to big endian format (from word swapped)",
  "%ld instructions converted to big endian format",
  "ROM is in an unknown format",

  // CPU processing
  "Unknown instruction format: 0x%08x",

  // misc
  "Logging level set to %s",
  "Terminating..."
};

// initialization
void loc_init(loc_level lc, char *pn);

// logging/error reporting
void loc_log(loc_level ll, loc_code lc, ...);
void loc_fatal(loc_code lc, ...);

// other stuff
void loc_print_usage();

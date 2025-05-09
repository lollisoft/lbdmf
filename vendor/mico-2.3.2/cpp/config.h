#ifdef _WINDOWS
#include <mico/config-win32.h>
#include <io.h>
#include <malloc.h>
#include <stdlib.h>

#pragma warning (disable: 4018)

char *index( char *s, char c );
char *rindex( char *s, char c );

#else
#include <mico/config.h>
#endif

#define BITS_PER_UNIT SIZEOF_UNSIGNED_CHAR
#define BITS_PER_WORD SIZEOF_INT
#define HOST_BITS_PER_INT SIZEOF_INT

#define TARGET_BELL '\a'
#define TARGET_BS '\b'
#define TARGET_FF '\f'
#define TARGET_NEWLINE '\n'
#define TARGET_CR '\r'
#define TARGET_TAB '\t'
#define TARGET_VT '\v'

#define INCLUDE_DEFAULTS { { 0, 0, 0 } }
#define GCC_INCLUDE_DIR "/usr/include"

#define FATAL_EXIT_CODE 1
#define SUCCESS_EXIT_CODE 0

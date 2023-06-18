
#ifndef MKMK_STRINGTOOLS
#define MKMK_STRINGTOOLS

// Replaces the given string with std:regex and strdups it for the caller.
char* replaceStringAndDup(char* toReplace, const char* match, const char* replace);

#endif
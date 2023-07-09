#include "stringtools.h"
#include <string>
#ifdef __WATCOM__ || __MINGW__
#include <regex>
#endif

char* replaceStringAndDup(char* to, const char* match, const char* replace) {
#ifdef __WATCOM__ || __MINGW__
	std::string toReplace = to;
	std::regex_replace(toReplace, std::regex(match), replace);
#else
	size_t pos = 0;
	std::string toReplace = to;
    while ((pos = toReplace.find(match, pos)) != std::string::npos) {
         toReplace.replace(pos, match.length(), replace);
         pos += replace.length();
    }
#endif

	return strdup(toReplace.c_str());
}


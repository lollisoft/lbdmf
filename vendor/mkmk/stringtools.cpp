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
		std::string toReplace = to;
		std::replace( toReplace.begin(), toReplace.end(), match, replace); // replace all 'x' to 'y'	
#endif
		return strdup(toReplace.c_str());
}


#include "stringtools.h"
#include <string>
#include <string.h>
#include <stdlib.h> 

#if defined(__MINGW32__) || defined(__WATCOMC__) 
#include <regex>
#endif

char* replaceStringAndDup(char* to, const char* match, const char* replace) {
#if defined(__MINGW32__) || defined(__WATCOMC__) 
	std::string toReplace = to;
	std::regex_replace(toReplace, std::regex(match), replace);
#else
	size_t pos = 0;
	std::string toReplace = to;
	std::string toMatch = match;
    while ((pos = toReplace.find(toMatch, pos)) != std::string::npos) {
         toReplace.replace(pos, toMatch.length(), replace);
         pos += toReplace.length();
    }
#endif

	const std::string::size_type size = toReplace.size();
	char *buffer = (char*)malloc(size + 1);
	memcpy(buffer, toReplace.c_str(), size + 1);
	
	return buffer;
}


#include "stringtools.h"
#include <string>
#include <regex>

char* replaceStringAndDup(char* to, const char* match, const char* replace) {
		std::string toReplace = to;
		std::regex_replace(toReplace, std::regex(match), replace);
		return strdup(toReplace.c_str());
}


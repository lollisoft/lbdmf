#define OWDLL
#include "itest.h"
#include "owtestdll.h"
#include <stdio.h>

class Test : public ITest {
public:        
	lbErrCodes		API getInt(char* _int, bool showmsg);
    bool			API getbool();
    void			API test(char* text, char* p2);
    void			API release();

public:
	Test();
	virtual ~Test();
};

extern "C" DLLEXPORT ITest* API _gettestow() {
	printf("Test instance from OW DLL created via _gettestow.\n");
	return new Test();
}

extern "C" DLLEXPORT ITest* API gettestow() {
	printf("Test instance from OW DLL created via gettestow.\n");
    return _gettestow();
}

void test_impl(char* text) {
    printf("Hello from test DLL. Text is '%s'.\n", text);
}


Test::Test() {
	printf("OW Instance of Test created.\n");
}

Test::~Test() {
	printf("OW Instance of Test deleted.\n");
}

bool API Test::getbool() {
	return true;
}

lbErrCodes API Test::getInt(char* _int, bool showmsg) {
	if (showmsg) printf("Test if value is not NULL.\n");
	if (_int == NULL) return ERR_FAIL;
	return ERR_NONE;
}

void API Test::test(char* text, char* p2) {
	test_impl(text);
	test_impl(p2);
}

void API Test::release() {
	printf("OW Test::release() called.\n");
	delete this;
}

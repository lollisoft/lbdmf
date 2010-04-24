#include "itest.h"
#define OWDLL
#include "owtestdll.h"
#include <stdio.h>

class Test : public ITest {
public:
	Test();
	virtual ~Test();
        
	lbErrCodes		API getInt(char* _int);
    bool			API getbool();
    void			API test(char* text, char* p2);
        
    virtual void	API release();
};



extern "C" DLLEXPORT ITest* API _gettestow() {
	//printf("Test instance from OW DLL created.\n");
	Test* t = new Test();
	return t;
}

extern "C" DLLEXPORT ITest* API gettestow() {
	//printf("Test instance from OW DLL created.\n");
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

lbErrCodes API Test::getInt(char* _int) {
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

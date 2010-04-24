#define DLL
#include "itest.h"
#include "testdll.h"
#include <stdio.h>

void test_impl(char* text) {
    printf("Hello from test DLL. Text is '%s'.\n", text);
}

/*...sclass Test:0:*/
class Test : public ITest {
public:
	Test();
	virtual ~Test();
        
	lbErrCodes		API getInt(char* _int);
    bool			API getbool();
    void			API test(char* text, char* p2);
        
    virtual void	API release();
};

Test::Test() {
	printf("Instance of Test created.\n");
}

Test::~Test() {
	printf("Instance of Test deleted.\n");
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
	printf("Test::release() called.\n");
	delete this;
}
/*...e*/

DLLEXPORT void API _test(char* text) {
	test_impl(text);
}

DLLEXPORT bool API _getbool() {
    return true;
}

DLLEXPORT ITest* API _gettest() {
    return new Test();
}

DLLEXPORT void API test(char* text) {
	test_impl(text);
}

DLLEXPORT bool API getbool() {
    return _getbool();
}

DLLEXPORT ITest* API gettest() {
    return _gettest();
}


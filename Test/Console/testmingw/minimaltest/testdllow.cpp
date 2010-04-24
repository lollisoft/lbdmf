// Description of test and sample output.
// 
// The code demonstrates a problem returning values of type enum.
// The problem appears when MINGW tries to use a Open Watcom DLL.
// The problem only appears when the DLL is loaded dynamically.
// 
// Q:\develop\Projects\CPP\Test\Console\testmingw\minimaltest>testow
// Hello from test DLL. Text is 'From text.exe'.
// Instance of Test created.
// Hello from test DLL. Text is 'From object out of test.exe'.
// Hello from test DLL. Text is 'p2'.
// Have true.
// Success: ITest->getInt() returns 1
// Test::release() called.
// Instance of Test deleted.
// Test MINGW DLL.
// Loading testdllmingw DLL dynamically from Open Watcom EXE:
// Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
// Test OW DLL.
// Loading testdllow DLL dynamically from Open Watcom EXE:
// Test instance from OW DLL created via gettestow.
// Test instance from OW DLL created via _gettestow.
// OW Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
//
// Q:\develop\Projects\CPP\Test\Console\testmingw\minimaltest>testmingw
// Hello from test DLL. Text is 'From text.exe'.
// Instance of Test created.
// Hello from test DLL. Text is 'From object out of test.exe'.
// Hello from test DLL. Text is 'p2'.
// Have true.
// Success: ITest->getInt() returns 1
// Test::release() called.
// Instance of Test deleted.
// Test MINGW DLL.
// Loading testdllmingw DLL dynamically from MINGW32 EXE:
// Instance of Test created.
// Success: ITest->getInt() returns 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1
// Test OW DLL.
// Loading testdllow DLL dynamically from MINGW32 EXE:
// Test instance from OW DLL created via gettestow.
// Test instance from OW DLL created via _gettestow.
// OW Instance of Test created.
// Error: ITest->getInt() doesn't return 1
// Test if value is not NULL.
// Test if value is not NULL.
// Success: ITest->getInt() returns 1

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

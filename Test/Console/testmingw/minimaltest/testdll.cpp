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

#define DLL
#include "itest.h"
#include "testdll.h"
#include <stdio.h>
#include <string.h>

class Test : public ITest {
public:
	Test();
	virtual ~Test();

public:
	lbErrCodes		API getInt(char* _int, bool showmsg);
	int				API	IntegerSize();
    bool			API getbool();
    void			API test(char* text, char* p2);
    void			API release();
	lbErrCodes		API	registerHandler(ITest* instance, lbEvHandler handler, char* name);
	lbErrCodes		API	registerHandler(ITest* instance, lbEvHandler handler, int number);
	lbErrCodes		API	Foo(int param1, int param2, int param3);

public:
	lbErrCodes		API	queryInterface(char const* name, void** unknown);
	int				API getBase1();
	int				API getBase();
};

extern "C" DLLEXPORT lb_I_Unknown* API gettest() {
    return _gettest();
}

extern "C" DLLEXPORT lb_I_Unknown* API _gettest() {
    return new Test();
}

void test_impl(char* text) {
    printf("Hello from test DLL. Text is '%s'.\n", text);
}

lbErrCodes	API	Test::queryInterface(char const* name, void** unknown) {
	if (strcmp(name, "lb_I_Unknown") == 0) {
		*unknown = (lb_I_Unknown*) this;
	}
	if (strcmp(name, "ITest") == 0) {
		*unknown = (ITest*) this;
	}
	return ERR_NONE;
}

Test::Test() {
	printf("Instance of Test created.\n");
}

Test::~Test() {
	printf("Instance of Test deleted.\n");
}

int API Test::getBase() {
	return 123;
}

int API Test::getBase1() {
	return 1234;
}

bool API Test::getbool() {
	return true;
}

lbErrCodes API Test::getInt(char* _int, bool showmsg) {
	if (showmsg) printf("Test if value is not NULL.\n");
	if (_int == NULL) return ERR_FAIL;
	return ERR_NONE;
}

int API Test::IntegerSize() {
	return sizeof(int);
}

void API Test::test(char* text, char* p2) {
	test_impl(text);
	test_impl(p2);
}

void API Test::release() {
	printf("Test::release() called.\n");
	delete this;
}

lbErrCodes API Test::registerHandler(ITest* instance, lbEvHandler handler, char* name) {
	printf("Handler gets registered with the number %s\n", name);
	return ERR_NONE;
}

lbErrCodes API Test::registerHandler(ITest* instance, lbEvHandler handler, int number) {
	if (number != 12003) printf("Handler gets registered with the number %d\n", number);
	return ERR_NONE;
}

lbErrCodes	API Test::Foo(int param1, int param2, int param3) {
	printf("Foo %d, %d, %d\n", param1, param2, param3);
	return ERR_NONE;
}

DLLEXPORT void API _test(char* text) {
	test_impl(text);
}

DLLEXPORT bool API _getbool() {
    return true;
}

DLLEXPORT void API test(char* text) {
	test_impl(text);
}

DLLEXPORT bool API getbool() {
    return _getbool();
}


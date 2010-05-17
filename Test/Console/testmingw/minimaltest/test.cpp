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

#include "itest.h"
#include "testdll.h"
#include "owtestdll.h"

#include <stdio.h>
#include <windows.h>

typedef lb_I_Unknown* (API *Functor)();

Functor getFunctor(char* name, char* dll) {
	HINSTANCE hinst;
	Functor functor;

	hinst = LoadLibrary(dll);
	if (hinst != NULL) {
		functor = (Functor) GetProcAddress(hinst, name);
		if (functor != NULL) {
			return functor;
		} else {
			return NULL;
		}
	}
	printf("Error: Couln't find DLL.\n");
	return NULL;
}

void testDynamicLoading(char* dll) {
	Functor functor;
	functor = getFunctor("gettestow", dll);
	if (functor == NULL) {
		functor = getFunctor("_gettestow", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("gettestow@0", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("_gettestow@0", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("gettest", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("_gettest", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("gettest@0", dll);
	}
	if (functor == NULL) {
		functor = getFunctor("_gettest@0", dll);
	}

	if (functor != NULL) {
		// Test loading Open Watcom DLL from application dynamically
#ifdef __MINGW32__
		printf("Loading %s DLL dynamically from MINGW32 EXE:\n", dll);
#endif
#ifdef __WATCOMC__
		printf("Loading %s DLL dynamically from Open Watcom EXE:\n", dll);
#endif
		lb_I_Unknown* uk = functor();

		if (uk == NULL) {
			printf("Couldn't load object.\n");
			return;
		}

		ITest* d = NULL;

		uk->queryInterface("ITest", (void**) &d);

		if (d == NULL) {
			printf("Couldn't query interface.\n");
			return;
		}

		if (d->getInt(NULL, false) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
		if (d->getInt(NULL, true) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);

		printf("Size of integer is %d\n", d->IntegerSize());

		int lala = 12003;
		//if (d->registerHandler(NULL, NULL, "lala") == ERR_NONE) ;
		if (d->registerHandler(NULL, NULL, lala) == ERR_NONE) ;
		if (d->Foo(12003, 12004, 12005) == ERR_NONE) ;

		if (uk->getBase() != 123) 
			printf("Have INCORRECT getBase().\n");
	} else {
		printf("Error: Couln't find functor.\n");
	}
}

int main() {
	test("From text.exe");
	lb_I_Unknown* uk = gettest();

	ITest* t = NULL;

	uk->queryInterface("ITest", (void**) &t);

	if (t == NULL) {
		printf("Couldn't query interface.\n");
		return 1;
	}

	t->test("From object out of test.exe", "p2");

	if (getbool()) printf("Have true.\n");
	if (t->getBase() != 123)
		printf("Have INCORRECT getBase().\n");

	if (t->getInt(NULL, false) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);

	t->release();

	printf("Test MINGW DLL.\n");
	testDynamicLoading("testdllmingw");
	printf("Test OW DLL.\n");
	testDynamicLoading("testdllow");

	return 0;
}

#include "itest.h"
#include "testdll.h"
#include "owtestdll.h"

#include <stdio.h>
#include <windows.h>

typedef ITest* (API *Functor)();

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
		ITest* d = functor();
		if (d == NULL) {
			printf("Couldn't load object.\n");
			return;
		}
		if (d->getInt(NULL, false) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
		if (d->getInt(NULL, false) == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);
		if (d->getInt(NULL, true) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
		if (d->getInt(NULL, true) == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);
	} else {
		printf("Error: Couln't find functor.\n");
	}
}

int main() {
	test("From text.exe");
	ITest* t = gettest();

	t->test("From object out of test.exe", "p2");

	if (getbool()) printf("Have true.\n");

	if (t->getInt(NULL, false) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
	if (t->getInt(NULL, false) == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);

	t->release();

	printf("Test MINGW DLL.\n");
	testDynamicLoading("testdllmingw");
	printf("Test OW DLL.\n");
	testDynamicLoading("testdllow");

	return 0;
}

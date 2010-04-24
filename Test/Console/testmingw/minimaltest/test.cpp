#define SKIP_ONE_MANGLE
#include "itest.h"
#include "testdll.h"
#include "owtestdll.h"

#include <stdio.h>
#include <windows.h>

typedef ITest* (API *Functor)();


Functor getFunctor(char* name) {
	HINSTANCE hinst;
	Functor functor;

	hinst = LoadLibrary("testdllow");
	if (hinst != NULL) {
		functor = (Functor) GetProcAddress(hinst, name);
		if (functor != NULL) {
			return functor;
		} else {
			printf("Error: Couln't find functor %s.\n", name);
			return NULL;
		}
	}
	printf("Error: Couln't find DLL.\n");
	return NULL;
}

int main() {
	test("From text.exe");
	ITest* t = gettest();

	t->test("From object out of test.exe", "p2");

	if (getbool()) printf("Have true.\n");

	if (t->getInt(NULL) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
	if (t->getInt(NULL) == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);

	t->release();

	Functor functor;
	functor = getFunctor("gettestow");
	if (functor == NULL) {
		functor = getFunctor("_gettestow");
	}
	if (functor == NULL) {
		functor = getFunctor("gettestow@0");
	}
	if (functor == NULL) {
		functor = getFunctor("_gettestow@0");
	}

	if (functor != NULL) {
		// Test loading Open Watcom DLL from application dynamically
#ifdef __MINGW32__
		printf("Loading Open Watcom DLL dynamically from MINGW32 EXE:\n");
#endif
#ifdef __WATCOMC__
		printf("Loading Open Watcom DLL dynamically from Open Watcom EXE:\n");
#endif
		ITest* d = functor();
		if (d == NULL) {
			printf("Couldn't load object.\n");
			return 0;
		}
		if (d->getInt(NULL) != ERR_FAIL) printf("Error: ITest->getInt() doesn't return %d\n", ERR_FAIL);
		if (d->getInt(NULL) == ERR_FAIL) printf("Success: ITest->getInt() returns %d\n", ERR_FAIL);
	}

	return 0;
}

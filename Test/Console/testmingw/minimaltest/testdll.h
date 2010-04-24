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

#undef DLLEXPORT
#ifdef DLL
#define DLLEXPORT __declspec(dllexport)
#endif

#ifndef DLL
#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef __WATCOMC__
extern "C" void DLLEXPORT API test(char* text);
#endif
#ifdef __MINGW32__
extern "C" void DLLEXPORT API _test(char* text);
extern "C" void DLLEXPORT API test(char* text);
#endif

#ifdef __WATCOMC__
extern "C" bool DLLEXPORT API getbool();
#endif
#ifdef __MINGW32__
extern "C" bool DLLEXPORT API _getbool();
extern "C" bool DLLEXPORT API getbool();
#endif

#ifdef __WATCOMC__
extern "C" DLLEXPORT ITest* API gettest();
#endif

#ifdef __MINGW32__
extern "C" DLLEXPORT ITest* API _gettest();
extern "C" DLLEXPORT ITest* API gettest();
#endif

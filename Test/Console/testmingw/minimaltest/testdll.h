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

#undef DLLEXPORT

#ifdef OWDLL
#define DLLEXPORT __declspec(dllexport)
#endif

#ifndef OWDLL
#define DLLEXPORT __declspec(dllimport)
#endif

#ifdef __WATCOMC__
extern "C" DLLEXPORT ITest* API gettestow();
#endif

#ifdef __MINGW32__
extern "C" DLLEXPORT ITest* API _gettestow();
extern "C" DLLEXPORT ITest* API gettestow();
#endif

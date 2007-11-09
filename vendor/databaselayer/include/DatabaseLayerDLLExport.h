#ifdef WINDOWS
#ifdef DLLEXPORT
#undef DLLEXPORT
#endif
#define DLLEXPORT __declspec(dllexport)
#endif

#ifndef WINDOWS
#define DLLEXPORT
#endif
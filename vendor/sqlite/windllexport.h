#ifdef WINDOWS
#ifdef SQLITE_DLLEXPORT
#undef SQLITE_DLLEXPORT
#endif
#define SQLITE_DLLEXPORT __declspec(dllexport)
#endif
#ifndef WINDOWS
#define SQLITE_DLLEXPORT
#endif
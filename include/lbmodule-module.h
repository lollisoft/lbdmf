#undef DLLEXPORT

#ifdef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif

#endif

#ifndef LB_MODULE_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif

#endif


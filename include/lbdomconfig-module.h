#undef DLLEXPORT

#ifdef LB_DOMCONFIG_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#endif

#ifndef LB_DOMCONFIG_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#endif


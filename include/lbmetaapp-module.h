#undef DLLEXPORT

#ifdef LB_METAAPP_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif

#endif

#ifndef LB_METAAPP_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif

#endif


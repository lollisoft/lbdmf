#undef DLLEXPORT

#ifdef LB_CLASSES_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif

#endif

#ifndef LB_CLASSES_DLL

#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif

#endif

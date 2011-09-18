/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/

/**
 * \file lbConfigHook.h
 * \brief The main header for bootstrapping lbDMF
 *
 * This file must be included by each file to be able to use lbDMF.
 */

#ifdef WINDOWS
 #ifndef TVISION
  #ifndef TVISION_APP

   #ifdef DEBUG_MALLOC
    #define TRACKER
    #define MEMTRACK
   #endif

  #endif
 #endif
#endif

#ifdef LINUX
 #ifdef DEBUG_MALLOC
  #define TRACKER
  #define MEMTRACK
 #endif
#endif

#ifdef WINDOWS
 #ifndef LB_DMF_POWER
  #include <windows.h>
 #endif
#endif
#include <stdlib.h>

//#ifdef WINDOWS
#ifndef TVISION
 #include <conio.h>
#endif
//#endif

#if defined(__MINGW32__)
#include <string.h>
#endif


#include <stdio.h>
#ifdef WINDOWS

#define IOS ios
#define COUT cout
#define CIN cin
#define ENDL endl
#define OFSTREAM ofstream

 #include <iostream.h>
 #include <fstream.h>

#endif

#ifdef LINUX

#define IOS  std::ios
#define COUT std::cout
#define CIN  std::cin
#define ENDL std::endl
#define OFSTREAM std::ofstream

#include <iostream>
#include <fstream>
#include <string.h>
#endif

#ifdef OSX
#include <sys/malloc.h>
#endif

#include <time.h>

#ifndef OSX
#ifndef MEMTRACK
#include <malloc.h>
#endif
#endif


#define itoa lb_itoa
#define ltoa lb_ltoa
#define ptoa lb_ptoa

#include <lbInterfaces.h>

#ifndef OSX
/*...sMemory tracker:0:*/
#ifndef TRMEM_DEFINED
 #define TRMEM_DEFINED
 #ifdef MEMTRACK
  #ifdef LINUX
   #define USE_MPATROL
   #include <mpatrol.h>
  #endif


  #ifdef WINDOWS
   #include <trmemcvr.h>
  #endif

  #ifndef USE_MPATROL
   #undef malloc
   #undef free
   #undef realloc
   #undef memset

   #define malloc TRMemAlloc
   #define free TRMemFree
   #define realloc TRMemRealloc
   #define strdup TRMemStrdup
   #define memset TRMemSet
  #endif

  #ifdef USE_MPATROL
   // Undefined outside Open Watcom
   #define TRMemOpen()
   #define TRMemStartLocalCount()
   #define TRMemStopLocalCount()
   #define TRMemResetLocalCount()
   #define TRMemSetModuleName(name)
   #define TRMemSetAdrBreakPoint(ptr, c)
   #define TRMemStartLocalCount()
   #define TRMemStopLocalCount()
   #define TRMemResetLocalCount()
   #define TRMemFree(name) free(name)
   #define TRMemSetPointerValid(p1, p2)
  #endif

#ifdef SOLARIS
#define _TRMemValidate(name) (TRMemValidate(name) == true)
#endif
#ifndef SOLARIS
#define _TRMemValidate(name) lbPtrValidate(name)
#endif

 #endif // MEMTRACK

 #ifndef MEMTRACK
  #define _TRMemValidate(name) name != NULL
  #define TRMemOpen()
  #define TRMemStartLocalCount()
  #define TRMemStopLocalCount()
  #define TRMemResetLocalCount()
  #define TRMemSetModuleName(name)
  #define TRMemSetAdrBreakPoint(ptr, c)
  #define TRMemStartLocalCount()
  #define TRMemStopLocalCount()
  #define TRMemResetLocalCount()
  #define TRMemFree(name) free(name)
  #define TRMemSetPointerValid(p1, p2)
 #endif
#endif
/*...e*/
#endif // OSX

#ifdef OSX
 #ifndef MEMTRACK
  #define _TRMemValidate(name) OSXMemValidate(name)
   #define TRMemStartLocalCount()
   #define TRMemStopLocalCount()
   #define TRMemResetLocalCount()
   #define TRMemSetPointerValid(ptr, parent)
  //#define TRMemOpen()
  //#define TRMemSetModuleName(name)
  //#define TRMemSetAdrBreakPoint(ptr)
 #endif
#endif

#define _trans(text) translateText(text)

/*...sLogging macros:0:*/

/*...sLOG_INSTANCE:0:*/
#define LOG_INSTANCE \
                        if (getLoggerInstance() == NULL) { \
                                setInitializing(1); \
                                lb_I_Module* modMan = getModuleInstance(); \
                                \
                                if (modMan != NULL) { \
                                        lb_I_Unknown *Unknown = NULL; \
                                        modMan->initialize(); \
                                        lbErrCodes err = modMan->request("lb_I_Log", &Unknown); \
                                        \
                                        if (Unknown != NULL) { \
                                                lb_I_Log* log; \
                                                Unknown->queryInterface("lb_I_Log", (void**) &log, __FILE__, __LINE__); \
                                                setLoggerInstance(log); \
                                                Unknown->release(__FILE__, __LINE__); \
                                                if (log == NULL) { \
                                                        exit (1); \
                                                } else { \
                                                } \
                                        } else { \
                                                exit(1); \
                                        } \
                                        modMan->release(__FILE__, __LINE__); \
                                } else { \
                                        exit(1); \
                                } \
                        } \
                        setInitializing(0);
/*...e*/

/*...s_LOG:0:*/
#define LOG_IMPROVED
#ifdef LOG_IMPROVED

#define _LOG \
        if (!isLogActivated() || isInitializing() != 0) { \
        } else { \
			time_t Zeitstempel; \
			tm *nun; \
			Zeitstempel = time(0); \
			nun = localtime(&Zeitstempel); \
			createLogInstance(); \
			char tmstring[100] = ""; \
			sprintf(tmstring, "%4d.%2d.%2d - %2d:%2d:%2d", \
			nun->tm_year+1900, nun->tm_mon+1, nun->tm_mday, nun->tm_hour, nun->tm_min, nun->tm_sec); \
			*(getLoggerInstance()) << tmstring << " Datei: " << __FILE__ << " Zeile: " << __LINE__ << " Message: "

#define _LOGERROR \
		if (isInitializing() != 0) { \
		} else { \
			time_t Zeitstempel; \
			tm *nun; \
			Zeitstempel = time(0); \
			nun = localtime(&Zeitstempel); \
			createLogInstance(); \
			char tmstring[100] = ""; \
			sprintf(tmstring, "%4d.%2d.%2d - %2d:%2d:%2d", \
			nun->tm_year+1900, nun->tm_mon+1, nun->tm_mday, nun->tm_hour, nun->tm_min, nun->tm_sec); \
			*(getLoggerInstance()) << tmstring << " Datei: " << __FILE__ << " Zeile: " << __LINE__ << " Message: "

#endif

#define _LOGALWAYS _LOGERROR


#ifndef LOG_IMPROVED
#define _LOG \
        if (isInitializing() != 0) { \
        } else { \
                time_t Zeitstempel; \
                tm *nun; \
                Zeitstempel = time(0); \
                nun = localtime(&Zeitstempel); \
                LOG_INSTANCE \
                *(getLoggerInstance()) << nun->tm_year+1900 << '.' << nun->tm_mon+1 << '.' << nun->tm_mday \
                << " - " << nun->tm_hour << ':' << nun->tm_min << ':' << nun->tm_sec << " Datei: " << __FILE__ << " Zeile: " << __LINE__ << " Message: "


#endif
/*...e*/
/*...s LOG_:0:*/
#define  LOG_  << '\n'; }
/*...e*/

#define _CL_VERBOSE \
    if (isLogActivated() && isVerbose()) { \
        COUT << __FILE__ << ", " << __LINE__ << ": "

#ifndef SOLARIS
#define _CL_LOG \
	if (isLogActivated()) { \
        COUT << __FILE__ << ", " << __LINE__ << ": "
#endif

#ifdef SOLARIS
#define _CL_LOG \
    if (isLogActivated() && isVerbose()) { \
        COUT << __FILE__ << ", " << __LINE__ << ": "
#endif


/*...sLOG\40\msg\41\:0:*/
#define LOG(msg)        \
                        if (isInitializing() != 0) { \
                                COUT << "Tried to log while initializing the logger." << \
                                "Msg: " << msg << " File: " << __FILE__ << " Line: " << __LINE__ << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->log(msg, __LINE__, __FILE__); \
                        }
/*...e*/
/*...sLOGENABLE:0:*/
#define LOGENABLE       \
                        if (isInitializing() != 0) { \
                                COUT << "Tried to log while initializing the logger." << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->enable(); \
                        }
/*...e*/
/*...sLOGDISABLE:0:*/
#define LOGDISABLE      \
                        if (isInitializing() != 0) { \
                                COUT << "Tried to log while initializing the logger." << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->disable(); \
                        }
/*...e*/
/*...sLOGSTART:0:*/
#define LOGSTART        \
                        if (isInitializing != 0) { \
                                COUT << "Tried to log while initializing the logger." << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->event_begin(); \
                        }
/*...e*/
/*...sLOGEND:0:*/
#define LOGEND          \
                        if (isInitializing() != 0) { \
                                COUT << "Tried to log while initializing the logger." << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->event_end(); \
                        }
/*...e*/
/*...sLOGPREFIX:0:*/
#define LOGPREFIX(a)    \
                        if (isInitializing() != 0) { \
                                COUT << "Tried to log while initializing the logger." << ENDL; \
                        } else { \
                                LOG_INSTANCE \
                                getLoggerInstance()->setPrefix(a); \
                        }
/*...e*/
/*...e*/



#ifndef __LB_CONFIG_HOOK__
#define __LB_CONFIG_HOOK__

#ifdef LINUX
#define HINSTANCE void*
#endif

#if !defined(LB_CDECL)
#error LB_CDECL is not defined !
#endif



// MINGW wrapper functions

class lbStringKey;

#ifdef __MINGW32__
extern "C" DLLEXPORT bool 		LB_CDECL _isVerbose();
extern "C" DLLEXPORT bool 		LB_CDECL _isLogActivated();
extern "C" DLLEXPORT lbErrCodes 	LB_CDECL _lbLoadModule(const char* name, HINSTANCE & hinst, bool skipAutoUnload = false);
extern "C" DLLEXPORT lb_I_Module* 	LB_CDECL _getModuleInstance();
extern "C" DLLEXPORT void 		LB_CDECL _set_trackObject(char* track);
extern "C" DLLEXPORT char* 		LB_CDECL _get_trackObject();
extern "C" DLLEXPORT void 		LB_CDECL _track_Object(lb_I_Unknown* o, const char* msg);
extern "C" DLLEXPORT void 		LB_CDECL _setVerbose(bool what);
extern "C" DLLEXPORT void 		LB_CDECL _setLogActivated(bool what);
extern "C" DLLEXPORT void 		LB_CDECL _lbBreak();
extern "C" DLLEXPORT void 		LB_CDECL _logMessage(const char *msg, const char *f, int level = 0);
extern "C" DLLEXPORT char* 		LB_CDECL _getLogDirectory();
extern "C" DLLEXPORT char* 		LB_CDECL _setLogDirectory(char* name);
extern "C" DLLEXPORT void 		LB_CDECL _createDirectory(const char* name);
extern "C" DLLEXPORT void 		LB_CDECL _deleteDirectory(const char* name);
extern "C" DLLEXPORT HINSTANCE 		LB_CDECL _getModuleHandle();
extern "C" DLLEXPORT HINSTANCE 		LB_CDECL _getLBModuleHandle();
extern "C" DLLEXPORT void 		LB_CDECL _setModuleHandle(HINSTANCE h);
extern "C" DLLEXPORT void 		LB_CDECL _setLBModuleHandle(HINSTANCE h);
extern "C" DLLEXPORT int 		LB_CDECL _isInitializing();
extern "C" DLLEXPORT void 		LB_CDECL _setInitializing(int i);
extern "C" DLLEXPORT lb_I_Log* 		LB_CDECL _getLoggerInstance();
extern "C" DLLEXPORT void 		LB_CDECL _setLoggerInstance(lb_I_Log* l);
extern "C" DLLEXPORT void 		LB_CDECL _createLogInstance();
extern "C" DLLEXPORT bool 		LB_CDECL _isSetTRMemTrackBreak();
extern "C" DLLEXPORT void 		LB_CDECL _setTRMemTrackBreak(char* brk, int count);
extern "C" DLLEXPORT char* 		LB_CDECL _getTRMemTrackBreak();
extern "C" DLLEXPORT void 		LB_CDECL _InstanceCount(int inst);
extern "C" DLLEXPORT void 		LB_CDECL _Instances();
extern "C" DLLEXPORT lbErrCodes		LB_CDECL _lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn);
extern "C" DLLEXPORT lbStringKey*	LB_CDECL _getStringKey(char* buf);
extern "C" DLLEXPORT bool		LB_CDECL _DirectoryExists(char *filename);
extern "C" DLLEXPORT bool 		LB_CDECL _FileExists(char *filename);
extern "C" DLLEXPORT DWORD 		LB_CDECL _lbGetCurrentProcessId();
extern "C" DLLEXPORT char* 		LB_CDECL _lb_ptoa(void* ptr);
extern "C" DLLEXPORT char* 		LB_CDECL _lb_itoa(int ptr);
extern "C" DLLEXPORT char* 		LB_CDECL _lb_ltoa(const long ptr);
extern "C" DLLEXPORT DWORD 		LB_CDECL _lbGetCurrentThreadId();
extern "C" DLLEXPORT void		LB_CDECL _lb_sleep(int ms);
extern "C" DLLEXPORT lbErrCodes LB_CDECL _lbUnloadModule(const char* name);
extern "C" DLLEXPORT char*		LB_CDECL _translateText(const char* text);
extern "C" DLLEXPORT void		LB_CDECL _uninitLocale();
extern "C" DLLEXPORT void		LB_CDECL _unHookAll();
extern "C" DLLEXPORT const char*		LB_CDECL _getOsType();
#endif

extern "C" DLLEXPORT lbStringKey*	LB_CDECL getStringKey(char* buf);


extern "C" DLLEXPORT char* LB_CDECL lbstrristr(const char *String, const char *Pattern);
extern "C" DLLEXPORT char* LB_CDECL lbstristr(const char *String, const char *Pattern);



// Object tracking
extern "C" DLLEXPORT void LB_CDECL set_trackObject(char* track);
extern "C" DLLEXPORT char* LB_CDECL get_trackObject();
extern "C" DLLEXPORT void LB_CDECL track_Object(lb_I_Unknown* o, const char* msg);

/*...sMEMTRACKER:0:*/

/** \brief Checks wether if a memory track breakpoint is set.
 */
extern "C" DLLEXPORT bool LB_CDECL isSetTRMemTrackBreak();

/** \brief Set the break address.
 *
 * This sets the memory breakpoint address and flags isSetTRMemTrackBreak() to true.
 */
extern "C" DLLEXPORT void LB_CDECL setTRMemTrackBreak(char* brk, int count);

/** \brief Get the break address.
 *
 * This is used in all DLL modules to get the same address, if it is set.
 */
extern "C" DLLEXPORT char* LB_CDECL getTRMemTrackBreak();

#ifndef TRACKER
#define TRMemTrackOpen isSetTRMemTrackBreak
#endif

/*...e*/

/** \brief Activate or deactivate verbose messages. */
extern "C" DLLEXPORT void LB_CDECL setVerbose(bool what);
extern "C" DLLEXPORT void LB_CDECL setLogActivated(bool what);
extern "C" DLLEXPORT bool LB_CDECL isVerbose();
extern "C" DLLEXPORT bool LB_CDECL isLogActivated();
extern "C" DLLEXPORT void LB_CDECL lbBreak();
#define LOGFILE "lbDMF.log"

/** \brief Log a message to the given file. */
extern "C" DLLEXPORT void LB_CDECL logMessage(const char *msg, const char *f, int level = 0);

/** \brief Get the log directory.
 * Returns the log directory.
 *
 * The directory is user based and so, located in the home directory of the user.
 * Value is based on $(HOME)/log.
 */
extern "C" DLLEXPORT char* LB_CDECL getLogDirectory();
extern "C" DLLEXPORT char* LB_CDECL setLogDirectory(char* name);

extern "C" DLLEXPORT void LB_CDECL createDirectory(const char* name);
extern "C" DLLEXPORT void LB_CDECL deleteDirectory(const char* name);

extern "C" DLLEXPORT HINSTANCE LB_CDECL getModuleHandle();
extern "C" DLLEXPORT HINSTANCE LB_CDECL getLBModuleHandle();

extern "C" DLLEXPORT void LB_CDECL setModuleHandle(HINSTANCE h);
extern "C" DLLEXPORT void LB_CDECL setLBModuleHandle(HINSTANCE h);


extern "C" DLLEXPORT int LB_CDECL isInitializing();
extern "C" DLLEXPORT void LB_CDECL setInitializing(int i);
extern "C" DLLEXPORT lb_I_Log* LB_CDECL getLoggerInstance();
extern "C" DLLEXPORT void LB_CDECL setLoggerInstance(lb_I_Log* l);
extern "C" DLLEXPORT void LB_CDECL createLogInstance();

extern "C" DLLEXPORT const char* LB_CDECL getOsType();

#ifdef OSX
bool LB_CDECL OSXMemValidate(void* ptr);
#endif

extern "C" DLLEXPORT bool LB_CDECL lbPtrValidate(void* ptr);

extern "C" DLLEXPORT char* LB_CDECL translateText(const char* text);
extern "C" DLLEXPORT void LB_CDECL uninitLocale();


extern "C" DLLEXPORT bool LB_CDECL DirectoryExists(char *filename);
extern "C" DLLEXPORT bool LB_CDECL FileExists(char *filename);

extern "C" DLLEXPORT lbErrCodes LB_CDECL lbUnloadModule(const char* name);
/*...sDLLEXPORT lbErrCodes LB_CDECL lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\44\ bool skipAutoUnload \61\ false\41\:0:*/
/**
 * \fn Platform independend module loader. This function is used to load a DLL or so module.
 * \param name The name of the module to be load.
 * \param hinst The instance handle of the module would be stored here.
 */
extern "C" DLLEXPORT lbErrCodes LB_CDECL lbLoadModule(const char* name, HINSTANCE & hinst, bool skipAutoUnload = false);

/*...e*/
/*...sDLLEXPORT lbErrCodes LB_CDECL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
extern "C" DLLEXPORT lbErrCodes LB_CDECL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn);
/*...e*/


/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...slb_I_Module\42\ LB_CDECL getModuleInstance\40\\41\:0:*/
extern "C" DLLEXPORT lb_I_Module* LB_CDECL getModuleInstance();
/*...e*/
/*...slbErrCodes LB_CDECL releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
extern "C" DLLEXPORT lbErrCodes LB_CDECL releaseInstance(lb_I_Unknown* inst);
/*...e*/
/*...svoid LB_CDECL unHookAll\40\\41\:0:*/
extern "C" DLLEXPORT void LB_CDECL unHookAll();
/*...e*/

extern "C" DLLEXPORT void LB_CDECL lb_sleep(int ms);


extern "C" DLLEXPORT char* LB_CDECL lb_ptoa(void* ptr);
extern "C" DLLEXPORT char* LB_CDECL lb_itoa(int ptr);
extern "C" DLLEXPORT char* LB_CDECL lb_ltoa(const long ptr);

extern "C" DLLEXPORT DWORD LB_CDECL lbGetCurrentThreadId();
extern "C" DLLEXPORT DWORD LB_CDECL lbGetCurrentProcessId();

extern "C" DLLEXPORT void LB_CDECL InstanceCount(int inst);
extern "C" DLLEXPORT void LB_CDECL Instances();

/*...sclass lbStringKey \58\ public lb_I_KeyBase:0:*/
class DLLEXPORT
lbStringKey : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
     lbStringKey(char* file, int line) { key = ""; strcpy(keyType, "string"); }
#endif
    lbStringKey();
    lbStringKey(const char* _key);
    lbStringKey(const lb_I_KeyBase* k);
    virtual ~lbStringKey();

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_KEYBASE()

private:

    char keyType[10];
    char* key;
};
/*...e*/
/*...sclass lbKey \58\ public lb_I_KeyBase:0:*/
class DLLEXPORT lbKey_ : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
        lbKey_(char* file, int line); // { key = 0; strcpy(keyType, "int"); }
#endif

        lbKey_();
        lbKey_(int _key);
        lbKey_(const lb_I_KeyBase* k);
        virtual ~lbKey_();

        DECLARE_LB_UNKNOWN()

        DECLARE_LB_KEYBASE()

private:

        char keyType[10];
        int key;
};
/*...e*/

extern "C" DLLEXPORT void LB_CDECL CL_doLog(char* f, char* msg);

#ifdef LINUX
#ifndef INCLUDED_BY_LBDMF
#undef HINSTANCE
#endif
#endif

#endif // __LB_CONFIG_HOOK__

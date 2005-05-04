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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/

/**
 * \file lbConfigHook.h
 * \brief The main header for bootstrapping lbDMF
 *
 * This file must be included by each file to be able to use lbDMF.
 */
#ifdef USE_MPATROL
#include <mpatrol.h>
#endif

#ifdef WINDOWS
#ifndef TVISION
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

#include <stdio.h>
#ifdef WINDOWS

#define IOS ios
#define COUT cout
#define ENDL endl
#define OFSTREAM ofstream

 #include <iostream.h>
 #include <fstream.h>
#endif

#ifdef LINUX

#define IOS  std::ios
#define COUT std::cout
#define ENDL std::endl
#define OFSTREAM std::ofstream


 #include <iostream.h>
 #include <fstream.h>
#endif

#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef OSX
#include <malloc.h>
#endif

#ifndef OSX
/*...sMemory tracker:0:*/
#ifdef MEMTRACK

#ifdef WINDOWS
extern "C" {
#include "trmemcvr.h"
}
#endif

#undef malloc
#undef free

#define malloc TRMemAlloc
#define free TRMemFree
#endif
/*...e*/

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
						if (log == NULL) { \
							exit (1); \
						} else { \
						} \
					} else { \
						exit(1); \
					} \
				} else { \
					exit(1); \
				} \
			} \
			setInitializing(0);
/*...e*/

/*...s_LOG:0:*/
#define _LOG \
	if (isInitializing() != 0) { \
	} else { \
	        LOG_INSTANCE \
		if (getLoggerInstance() == NULL) printf("Fatal: log instance is NULL !!\n"); \
		*(getLoggerInstance()) << "Datei: " << __FILE__ << " Zeile: " << __LINE__ << " Message: "

/*...e*/
/*...s LOG_:0:*/
#define  LOG_  << '\n'; }
/*...e*/
#ifndef __MISC
#define _CL_LOG \
{ \
        COUT \
        
#endif
#ifdef __MISC
#define _CL_LOG \
{ \
        COUT \
        
#endif

#define _CL_VERBOSE \
    if (isVerbose()) { \
	COUT \


/*...sLOG\40\msg\41\:0:*/
#define LOG(msg)	\
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


#include <lbInterfaces.h>

#ifndef __LB_CONFIG_HOOK__
#define __LB_CONFIG_HOOK__

#ifdef LINUX
#define HINSTANCE void*
#endif

#ifdef bla

#ifdef DLLEXPORT
#undef DLLEXPORT
#endif

#define DLLEXPORT

#ifdef HOOK_DLL
#undef DLLEXPORT
#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX
#define DLLEXPORT
#endif

#endif

#ifndef HOOK_DLL
#undef DLLEXPORT
#ifdef WINDOWS
#define DLLEXPORT LB_DLLIMPORT
#endif
#ifdef LINUX
#define DLLEXPORT
#endif
#endif

#endif

// Object tracking
DLLEXPORT void LB_STDCALL set_trackObject(char* track);
DLLEXPORT char* LB_STDCALL get_trackObject();
DLLEXPORT void LB_STDCALL track_Object(lb_I_Unknown* o, char* msg);

/*...sMEMTRACKER:0:*/
/** \brief Checks wether if a memory track breakpoint is set.
 */
DLLEXPORT bool LB_STDCALL isSetTRMemTrackBreak();

/** \brief Set the break address.
 *
 * This sets the memory breakpoint address and flags isSetTRMemTrackBreak() to true.
 */
DLLEXPORT void LB_STDCALL setTRMemTrackBreak(char* brk);

/** \brief Get the break address.
 *
 * This is used in all DLL modules to get the same address, if it is set.
 */
DLLEXPORT char* LB_STDCALL getTRMemTrackBreak();

#ifndef TRACKER
#define TRMemTrackOpen isSetTRMemTrackBreak
#endif 
/*...e*/

DLLEXPORT void LB_STDCALL setVerbose(bool what);
DLLEXPORT bool LB_STDCALL isVerbose();

DLLEXPORT HINSTANCE LB_STDCALL getModuleHandle();
DLLEXPORT HINSTANCE LB_STDCALL getLBModuleHandle();

DLLEXPORT void LB_STDCALL setModuleHandle(HINSTANCE h);
DLLEXPORT void LB_STDCALL setLBModuleHandle(HINSTANCE h);


DLLEXPORT int LB_STDCALL isInitializing();
DLLEXPORT void LB_STDCALL setInitializing(int i);
DLLEXPORT lb_I_Log* LB_STDCALL getLoggerInstance();
DLLEXPORT void LB_STDCALL setLoggerInstance(lb_I_Log* l);


DLLEXPORT char* LB_STDCALL translateText(char* text);

/*...slbErrCodes LB_STDCALL lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\41\:0:*/
/**
 * \fn Platform independend module loader. This function is used to load a DLL or so module.
 * \param name The name of the module to be load.
 * \param hinst The instance handle of the module would be stored here.
 */



lbErrCodes DLLEXPORT LB_STDCALL lbLoadModule(const char* name, HINSTANCE & hinst);
/*...e*/
/*...slbErrCodes LB_STDCALL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn);
/*...e*/


/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...slb_I_Module\42\ LB_STDCALL getModuleInstance\40\\41\:0:*/
DLLEXPORT lb_I_Module* LB_STDCALL getModuleInstance();
/*...e*/
/*...slbErrCodes LB_STDCALL releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
lbErrCodes LB_STDCALL releaseInstance(lb_I_Unknown* inst);
/*...e*/
/*...svoid LB_STDCALL unHookAll\40\\41\:0:*/
DLLEXPORT void LB_STDCALL unHookAll();
/*...e*/

DLLEXPORT char* LB_STDCALL ltoa(void* ptr);
DLLEXPORT char* LB_STDCALL itoa(int ptr);


DLLEXPORT void LB_STDCALL InstanceCount(int inst);
DLLEXPORT void LB_STDCALL Instances();



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

DLLEXPORT void LB_STDCALL CL_doLog(char* f, char* msg);

#ifdef LINUX
#ifndef INCLUDED_BY_LBDMF 
#undef HINSTANCE
#endif
#endif

#endif // __LB_CONFIG_HOOK__

//#include <windows.h>
#include <stdlib.h>

#ifdef WINDOWS
#include <conio.h>
#endif

#include <stdio.h>
#include <iostream.h>

#include <lbInterfaces.h>

#ifndef __LB_CONFIG_HOOK__
#define __LB_CONFIG_HOOK__

#ifdef LINUX
#define HINSTANCE void*
#endif

extern HINSTANCE ModuleHandle;
extern HINSTANCE LB_Module_Handle;


/**
 * Platform independend module loader
 */
/*...slbErrCodes LB_STDCALL lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\41\:0:*/
lbErrCodes LB_STDCALL lbLoadModule(const char* name, HINSTANCE & hinst);
/*...e*/
/*...slbErrCodes LB_STDCALL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
lbErrCodes LB_STDCALL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn);
/*...e*/


/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...slb_I_Module\42\ LB_STDCALL getModuleInstance\40\\41\:0:*/
lb_I_Module* LB_STDCALL getModuleInstance();
/*...e*/
/*...slbErrCodes LB_STDCALL releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
lbErrCodes LB_STDCALL releaseInstance(lb_I_Unknown* inst);
/*...e*/
/*...svoid LB_STDCALL unHookAll\40\\41\:0:*/
void LB_STDCALL unHookAll();
/*...e*/

/*...sLogging macros:0:*/
extern lb_I_Log *log;
extern int isInitializing;


#define CL_LOG(msg) \
{ \
	char *datei = strrchr(__FILE__, '\\'); \
	if (datei == NULL) { \
		datei = __FILE__; \
	} \
	else { \
		datei++; \
	} \
	cout << "File: " << datei << ", Line: " << __LINE__ << ", Msg: " << msg << endl; \
}
#ifdef bla
#define CL_LOG(msg) \
	cout << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Msg: " << msg << endl;
#endif
	
/*...sGET_LOG_INSTANCE:0:*/
#define GET_LOG_INSTANCE \
			if (log == NULL) { \
				isInitializing = 1; \
				lb_I_Module* modMan = getModuleInstance(); \
				\
				if (modMan != NULL) { \
					lb_I_Unknown *Unknown = NULL; \
					lbErrCodes err = modMan->request("lb_I_Log", &Unknown); \
					\
					if (Unknown != NULL) { \
						Unknown->queryInterface("lb_I_Log", (void**) &log, __FILE__, __LINE__); \
						if (log == NULL) { \
							CL_LOG("Unknown object has no interface for lb_I_Log"); \
							exit (1); \
						} else { \
						} \
					} else { \
						char buf[1000] = ""; \
						sprintf(buf, "%s %d %s", "Instance could not be created, errcode is ", err, "."); \
						CL_LOG(buf); \
						getch(); \
						exit(1); \
					} \
				} else { \
					CL_LOG("Module manager could not be created"); \
					getch(); \
					exit(1); \
				} \
			} \
			isInitializing = 0;
/*...e*/

/*...sLOG:0:*/
#define LOG(msg)	\
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << \
				"Msg: " << msg << " File: " << __FILE__ << " Line: " << __LINE__ << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->log(msg, __LINE__, __FILE__); \
			}
/*...e*/
/*...sLOGENABLE:0:*/
#define LOGENABLE       \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->enable(); \
			}
/*...e*/
/*...sLOGDISABLE:0:*/
#define LOGDISABLE      \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->disable(); \
			}
/*...e*/
/*...sLOGSTART:0:*/
#define LOGSTART        \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->event_begin(); \
			}
/*...e*/
/*...sLOGEND:0:*/
#define LOGEND          \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->event_end(); \
			}
/*...e*/
/*...sLOGPREFIX:0:*/
#define LOGPREFIX(a)    \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->setPrefix(a); \
			}
/*...e*/
/*...e*/

#endif // __LB_CONFIG_HOOK__

#ifndef __LB_CONFIG_HOOK__
#define __LB_CONFIG_HOOK__

#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>


HINSTANCE ModuleHandle = NULL;
HINSTANCE LB_Module_Handle = NULL;

#include <lbInterfaces.h>



/**
 * Platform independend module loader
 */
/*...slbErrCodes lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\41\:0:*/
lbErrCodes lbLoadModule(const char* name, HINSTANCE & hinst) {
        if ((hinst = LoadLibrary(name)) == NULL)
        {
            printf("Kann DLL '%s.dll' nicht laden.\n", name); 
            getch(); 
            return ERR_MODULE_NOT_FOUND;
        }
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
lbErrCodes lbGetFunctionPtr(const char* name, const HINSTANCE & hinst, void** pfn) {
        if ((*pfn = (void*) GetProcAddress(hinst, name)) == NULL)
        {
            printf("Kann Funktion '%s' nicht finden.\n", name); 
            getch(); 
            return ERR_FUNCTION_NOT_FOUND;
        }
        return ERR_NONE;
}
/*...e*/


/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...slb_I_Module\42\ getModuleInstance\40\\41\:0:*/
lb_I_Module* getModuleInstance() {
typedef lbErrCodes (* __cdecl T_p_getlbModuleInstance) (lb_I_Module*&);
T_p_getlbModuleInstance DLL_GETMODULEINSTANCE;

	lb_I_Module* module = NULL;

	char* libname = getenv("MODULELIB");
	char* functor = getenv("LBMODULEFUNCTOR");

	if (LB_Module_Handle == NULL) {
		if (lbLoadModule(libname, LB_Module_Handle) != ERR_NONE) {
			exit(1);
		}
	}
	
	if (lbGetFunctionPtr(functor, LB_Module_Handle, (void**) &DLL_GETMODULEINSTANCE) != ERR_NONE) {
		exit(1);
	}
	
	DLL_GETMODULEINSTANCE(module);
	
	return module;
}
/*...e*/
/*...slbErrCodes releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
lbErrCodes releaseInstance(lb_I_Unknown* inst) {
	typedef lbErrCodes (* __cdecl T_p_releaseInstance) (lb_I_Unknown*);
	T_p_releaseInstance DLL_RELEASEINSTANCE;
	
	if (lbGetFunctionPtr("_lb_releaseInstance", LB_Module_Handle, (void**) &DLL_RELEASEINSTANCE) != ERR_NONE) {
		exit(1);
	}
	
	DLL_RELEASEINSTANCE(inst);
	
	return ERR_NONE;
}
/*...e*/
/*...svoid unHookAll\40\\41\:0:*/
void unHookAll() {
	if (ModuleHandle != NULL) FreeLibrary(ModuleHandle);
	if (LB_Module_Handle != NULL) FreeLibrary(LB_Module_Handle);
}
/*...e*/

/*...sLogging macros:0:*/
lb_I_Log *log = NULL;
int isInitializing = 0;

/*...sGET_LOG_INSTANCE:0:*/
#define GET_LOG_INSTANCE \
			if (log == NULL) { \
				isInitializing = 1; \
				cout << "Getting a log instance..." << endl; \
				lb_I_Module* modMan = getModuleInstance(); \
				getch(); \
				\
				if (modMan != NULL) { \
					lb_I_Unknown *Unknown = NULL; \
					modMan->request("instanceOfLogger", Unknown); \
					\
					if (Unknown != NULL) { \
						Unknown->queryInterface("lb_I_Log", (void**) &log); \
						if (log == NULL) { \
							cout << "Unknown object has no interface for lb_I_Log" << endl; \
							getch(); \
							exit (1); \
						} \
						cout << "Now have a log instance" << endl; \
					} else { \
						cout << "Instance could not be created" << endl; \
						getch(); \
						exit(1); \
					} \
				} else { \
					cout << "Module manager could not be created" << endl; \
					getch(); \
					exit(1); \
				} \
			} \
			isInitializing = 0;
/*...e*/

#define CL_LOG(msg) \
	cout << "File: " << __FILE__ << ", Line: " << __LINE__ << ", Msg: " << msg << endl;

#define LOG(msg)	\
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << \
				"Msg: " << msg << " File: " << __FILE__ << " Line: " << __LINE__ << endl; \
			} else { \
				GET_LOG_INSTANCE \
				cout << "Log a message: " << msg << endl; \
				log->log(msg, __LINE__, __FILE__); \
				cout << "Logged." << endl; \
			}
#define LOGENABLE       \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->enable(); \
			}
#define LOGDISABLE      \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->disable(); \
			}
#define LOGSTART        \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->event_begin(); \
			}
#define LOGEND          \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->event_end(); \
			}
#define LOGPREFIX(a)    \
			if (isInitializing != 0) { \
				cout << "Tried to log while initializing the logger." << endl; \
			} else { \
				GET_LOG_INSTANCE \
				log->setPrefix(a); \
			}
/*...e*/

#endif // __LB_CONFIG_HOOK__

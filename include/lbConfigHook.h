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

#endif // __LB_CONFIG_HOOK__

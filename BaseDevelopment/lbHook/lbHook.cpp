#include <stdarg.h>

// Where should I define standard switches to choose the correct code ?

#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef LINUX
#include <dlfcn.h>

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}
#endif            

#endif


//#include <windef.h>
//#include <winbase.h>

#include <lbConfigHook.h>



HINSTANCE ModuleHandle = NULL;
HINSTANCE LB_Module_Handle = NULL;
lb_I_Log *log = NULL;
int isInitializing = 0;

/**
 * Platform independend module loader
 */

#if !defined(LB_STDCALL)
#ifdef WINDOWS
#error LB_STDCALL is not defined !
#endif
#endif 
 
/*...slbErrCodes LB_STDCALL lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\41\:0:*/
lbErrCodes LB_STDCALL lbLoadModule(const char* name, HINSTANCE & hinst) {
#ifdef WINDOWS
        if ((hinst = LoadLibrary(name)) == NULL)
        {
            printf("Kann DLL '%s' nicht laden.\n", name); 
            getch(); 
            return ERR_MODULE_NOT_FOUND;
        }
#endif
#ifdef LINUX
	if ((hinst = dlopen(name, RTLD_LAZY)) == NULL)
	{
	    printf("Kann SO module '%s' nicht laden.\n", name);
	    getch();
	    return ERR_MODULE_NOT_FOUND;
	}
#endif
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
lbErrCodes LB_STDCALL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn) {
        char msg[1000] = "";
#ifdef WINDOWS	
        if ((*pfn = (void*) GetProcAddress(hinst, name)) == NULL)
        {
            sprintf(msg, "Kann Funktion '%s' nicht finden.", name);
            CL_LOG(msg); 
            getch(); 
            return ERR_FUNCTION_NOT_FOUND;
        }
#endif
#ifdef LINUX
	
	if ((*pfn = dlsym(hinst, name)) == NULL)
	{
	    printf("Handle for library is %p\n", (void*) hinst);
            sprintf(msg, "Kann Funktion '%s' nicht finden.", name);
            CL_LOG(msg); 
            getch(); 
            return ERR_FUNCTION_NOT_FOUND;	    
	}
#endif
        return ERR_NONE;
}
/*...e*/


/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...slb_I_Module\42\ LB_STDCALL getModuleInstance\40\\41\:0:*/
lb_I_Module* LB_STDCALL getModuleInstance() {
typedef lbErrCodes (LB_STDCALL *T_p_getlbModuleInstance) (lb_I_Module*&, lb_I_Module* m, char* file, int line);
T_p_getlbModuleInstance DLL_GETMODULEINSTANCE;
	lbErrCodes err = ERR_NONE;
	lb_I_Module* module = NULL;

	char* libname = getenv("MODULELIB");
	char* functor = getenv("LBMODULEFUNCTOR");

	if (functor == NULL) printf("Error: Have no functor!\n");


	if (LB_Module_Handle == NULL) {
		if (lbLoadModule(libname, LB_Module_Handle) != ERR_NONE) {
			printf("Failed to load module manager\n");
			exit(1);
		}
	}

    if (LB_Module_Handle == NULL) {
	printf("Error: Could not load shared library %s\n", libname);
    }
	
#ifdef bla	
	if (lbGetFunctionPtr(functor, 
			     LB_Module_Handle, 
			     reinterpret_cast<void **>(&DLL_GETMODULEINSTANCE)) != ERR_NONE) {
		exit(1);
	}
#endif
	if (lbGetFunctionPtr(functor, 
			     LB_Module_Handle, 
			     (void **) &DLL_GETMODULEINSTANCE) != ERR_NONE) {
		exit(1);
	}
	
	if ((err = DLL_GETMODULEINSTANCE(module, NULL, __FILE__, __LINE__)) == ERR_STATE_FURTHER_LOCK) {
		CL_LOG("Instance is locked. Must set module manager first");
		module->setModuleManager(module, __FILE__, __LINE__);
	} 
	
	return module;
}
/*...e*/
/*...slbErrCodes LB_STDCALL releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
lbErrCodes LB_STDCALL releaseInstance(lb_I_Unknown* inst) {
	typedef lbErrCodes (LB_STDCALL *T_p_releaseInstance) (lb_I_Unknown*);
	T_p_releaseInstance DLL_RELEASEINSTANCE;
	
	if (lbGetFunctionPtr("_lb_releaseInstance", LB_Module_Handle, (void**) &DLL_RELEASEINSTANCE) != ERR_NONE) {
		exit(1);
	}
	
	DLL_RELEASEINSTANCE(inst);
	
	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL unHookAll\40\\41\:0:*/
void LB_STDCALL unHookAll() {
	if (ModuleHandle != NULL) {
	#ifdef WINDOWS
		FreeLibrary(ModuleHandle);
	#endif
	#ifdef LINUX
		dlclose(ModuleHandle);
	#endif
		ModuleHandle = NULL;
	}
	
	if (LB_Module_Handle != NULL) {
	#ifdef WINDOWS
		FreeLibrary(LB_Module_Handle);
	#endif
	#ifdef LINUX
		dlclose(LB_Module_Handle);
	#endif
		LB_Module_Handle = NULL;
	}
	
	log = NULL;
}
/*...e*/

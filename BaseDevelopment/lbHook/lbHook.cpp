#define HOOK_DLL

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

#ifdef _MSC_VER
#pragma warning( disable: 4275 )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4101 )
#undef DLLEXPORT
#define DLLEXPORT
#endif

#include <lbConfigHook.h>
#include <lbKey.h>


HINSTANCE ModuleHandle = NULL;
HINSTANCE LB_Module_Handle = NULL;

char* trackObject = NULL;

DLLEXPORT void LB_STDCALL set_trackObject(char* track) {
	trackObject = track;
	printf("Have a tracking address: %s\n", trackObject);
}

DLLEXPORT void LB_STDCALL track_Object(lb_I_Unknown* o, char* msg) {
	char ptr[20] = "";
//	lb_I_Unknown *uk;
//	o->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
	sprintf(ptr, "%p", o);
	if (strcmp(ptr, (get_trackObject() == NULL) ? "" : get_trackObject()) == 0) {
		printf("Track object: %s\n", msg);
	}
}

DLLEXPORT char* LB_STDCALL get_trackObject() {
	if (trackObject == NULL) return getenv("TRACKOBJECT");
	return trackObject;
}

DLLEXPORT HINSTANCE LB_STDCALL getModuleHandle() {
	return ModuleHandle;
}

DLLEXPORT HINSTANCE LB_STDCALL getLBModuleHandle() {
	return LB_Module_Handle;
}

DLLEXPORT void LB_STDCALL setModuleHandle(HINSTANCE h) {
	ModuleHandle = h;
}

DLLEXPORT void LB_STDCALL setLBModuleHandle(HINSTANCE h) {
	LB_Module_Handle = h;
}

#ifdef bla
lb_I_Log *log = NULL;
int isInitializing = 0;
#endif

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

/*...sDLLEXPORT lb_I_Module\42\ LB_STDCALL getModuleInstance\40\\41\:0:*/
DLLEXPORT lb_I_Module* LB_STDCALL getModuleInstance() {
typedef lbErrCodes (LB_STDCALL *T_p_getlbModuleInstance) (lb_I_Module**, lb_I_Module* m, char* file, int line);
T_p_getlbModuleInstance DLL_GETMODULEINSTANCE;
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Module, module, __FILE__, __LINE__)

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
	
	if (lbGetFunctionPtr(functor, 
			     LB_Module_Handle, 
			     (void **) &DLL_GETMODULEINSTANCE) != ERR_NONE) {
		CL_LOG("Fatal: Could not get functor for the module manager!")
		exit(1);
	}
	
	if ((err = DLL_GETMODULEINSTANCE(&module, NULL, __FILE__, __LINE__)) == ERR_STATE_FURTHER_LOCK) {
		CL_LOG("Instance is locked. Must set module manager first");
		module->setModuleManager(module.getPtr(), __FILE__, __LINE__);
	} 
	
	UAP(lb_I_Module, inst, __FILE__, __LINE__)
	
	QI(module, lb_I_Module, inst, __FILE__, __LINE__)
	
	return inst.getPtr();
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
DLLEXPORT void LB_STDCALL unHookAll() {
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

/*...slbKey:0:*/
/*...sc\39\tors and d\39\tors:0:*/
lbKey::lbKey() {
    ref = STARTREF;
    key = 0;
	manager = NULL;
    strcpy(keyType, "int");
}

lbKey::lbKey(int _key) {
    ref = STARTREF;
    key = _key;
    strcpy(keyType, "int");
	manager = NULL;
}

lbKey::lbKey(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = ((lbKey) k).key;
}

lbKey::~lbKey(){
}
/*...e*/

/*...simplement lb_I_Unknown:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL lbKey::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}
/*...e*/

char* LB_STDCALL lbKey::getKeyType() const {
    return "int";
}

int LB_STDCALL lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKey*) _key)->key;
}

char* LB_STDCALL lbKey::charrep() const {
    char buf[100];
#ifdef WINDOWS
    itoa(key, buf, 10);
#endif
#ifdef LINUX
    sprintf(buf, "%d", key);
#endif    
    return strdup(buf);
}
/*...e*/
/*...slbKeyUL:0:*/


lbKeyUL::lbKeyUL() {
    ref = STARTREF;
    key = 0;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(unsigned long _key) {
    ref = STARTREF;
    key = _key;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = ((lbKeyUL*) k)->key;
}


lbKeyUL::~lbKeyUL(){
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbKeyUL)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbKeyUL::setData(lb_I_Unknown* uk) {
	CL_LOG("lbKey::setData() not implemented yet");
	return ERR_NONE;
}


char* LB_STDCALL lbKeyUL::getKeyType() const {
    return "UL";
}

int LB_STDCALL lbKeyUL::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKeyUL*) _key)->key;
}

char* LB_STDCALL lbKeyUL::charrep() const {
    char buf[100];

#ifdef WINDOWS
    itoa(key, buf, 10);
#endif
#ifdef LINUX
    sprintf(buf, "%d", key);
#endif    
    
    return strdup(buf);
}
/*...e*/
/*...slbStringKey:0:*/
lbStringKey::lbStringKey() {
    ref = STARTREF;
    key = "";
}

lbStringKey::lbStringKey(const char* _key) {
    ref = STARTREF;
    key = strdup(_key);
}

lbStringKey::lbStringKey(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = strdup(((lbStringKey*) k)->key);
}


lbStringKey::~lbStringKey(){
	if (key != NULL) {
		delete key;
	}
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbStringKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbStringKey::setData(lb_I_Unknown* uk) {
	
	lb_I_KeyBase* string = NULL;
	
	if (uk->queryInterface("lb_I_KeyBase", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Could not get interface lb_I_KeyBase");
	}
	
	if (string != NULL) {
		if (key != NULL) free(key);
		key = strdup(((lbStringKey*) string)->key);
	}
	
	return ERR_NONE;
}

char* LB_STDCALL lbStringKey::getKeyType() const {
    return "string";
}

int LB_STDCALL lbStringKey::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) == 0);
}

int LB_STDCALL lbStringKey::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) > 0);
}

int LB_STDCALL lbStringKey::lessthan(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) < 0);
}

char* LB_STDCALL lbStringKey::charrep() const {
    return key;
}
/*...e*/

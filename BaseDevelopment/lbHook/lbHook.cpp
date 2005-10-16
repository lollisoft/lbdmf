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
#define HOOK_DLL
/*...sLB_HOOK_DLL scope:0:*/
#define LB_HOOK_DLL
#include <lbhook-module.h>
/*...e*/

/*...sincludes:0:*/
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

//  #include <conio.h>

  #ifdef __cplusplus
    }
  #endif            

#endif
/*...e*/

#ifdef _MSC_VER
#pragma warning( disable: 4275 )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4101 )
#endif

#include <lbConfigHook.h>

#ifdef LINUX
#define HINSTANCE void*
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef WINDOWS
#ifndef LB_CLASSES_DLL
DLLEXPORT lb_I_Log *lb_log;
DLLEXPORT int lb_isInitializing;
#endif
#ifdef LB_CLASSES_DLL
LB_DLLIMPORT lb_I_Log *lb_log;
LB_DLLIMPORT int lb_isInitializing;
#endif
#endif
#ifdef LINUX
extern lb_I_Log *lb_log;     
extern int lb_isInitializing;
#endif

bool lbVerbose = FALSE;
int instances = 0;
char* lbLogDirectory = NULL;
char* lbLogFile = NULL;

#if defined(OSX) || defined(UNIX) || defined(LINUX)
#define SLASH "/"
#endif
#if defined(WINDOWS)
#define SLASH "\\"
#endif

DLLEXPORT void logMessage(const char *msg, char *f, int level) {
                FILE *fp;
                fp = fopen( f, "a" );
                if( fp != NULL ) {
                        char buf[1000] = "";
                        buf[0] = 0;
                        
                        int l = level;
                        
                        while (l > 0) {
                                sprintf(buf, "%s%s", buf, "    ");
                                l--;
                        }

#ifdef WINDOWS                        
                        fprintf( fp, "Pid %d\t:%s%s", ::GetCurrentProcessId(), buf, msg);
#endif
#if defined (OSX) || defined (LINUX) || defined(UNIX)
                        fprintf( fp, "Pid %d\t:%s%s", getpid(), buf, msg);
#endif						
						fclose( fp );
                }
}

void logMessage(const char *msg) {
	if (lbLogFile == NULL) {
		char* logpath = getLogDirectory();
		lbLogFile = (char*) malloc(strlen(logpath)+100);
		lbLogFile[0] = 0;
	
		strcat(lbLogFile, logpath);
		strcat(lbLogFile, SLASH);
		strcat(lbLogFile, LOGFILE);
	}

	logMessage(msg, lbLogFile, 0);
}

DLLEXPORT char* getLogDirectory() {
	if (lbLogDirectory == NULL) {
		char* home = 
		#if defined(WINDOWS)
		getenv("USERPROFILE");
		#endif
		#if defined(UNIX) || defined(LINUX) || defined(OSX)
		getenv("HOME");
		#endif
		
		lbLogDirectory = (char*) malloc(strlen(home)+10);
		lbLogDirectory[0] = 0;
		strcat(lbLogDirectory, home);
		strcat(lbLogDirectory, SLASH);
		strcat(lbLogDirectory, "log");
		
		// Don't ask for failure.
		#ifdef __WATCOMC__
		mkdir(lbLogDirectory);
		#endif
		#if defined(OSX) || defined(LINUX) || defined(UNIX)
		mkdir(lbLogDirectory, S_IRWXU);
		#endif
	}

	return lbLogDirectory;
}

DLLEXPORT void LB_STDCALL InstanceCount(int inst) {
	instances += inst;
}

DLLEXPORT void LB_STDCALL Instances() {
	printf("Current instances are %d.\n", instances);
}


DLLEXPORT void LB_STDCALL setVerbose(bool what) {
    lbVerbose = what;
}

DLLEXPORT bool LB_STDCALL isVerbose() {
	return lbVerbose;
}

/*...sHelpers:0:*/
DLLEXPORT int LB_STDCALL isInitializing() {
	return lb_isInitializing;
}

DLLEXPORT void LB_STDCALL setInitializing(int i) {
	lb_isInitializing = i;
}

DLLEXPORT lb_I_Log* LB_STDCALL getLoggerInstance() {
	return lb_log;
}

DLLEXPORT void LB_STDCALL setLoggerInstance(lb_I_Log* l) {
	lb_log = l;
}


HINSTANCE ModuleHandle = NULL;
HINSTANCE LB_Module_Handle = NULL;

char* trackObject = NULL;

DLLEXPORT char* LB_STDCALL itoa(int ptr) {
        static char buf[20] = "";           
        sprintf(buf, "%d", ptr);            
        return buf;                         
}                                           

DLLEXPORT char* LB_STDCALL ltoa(void* ptr) {
        static char buf[20] = "";
	sprintf(buf, "%p", ptr);
        return buf;
}

DLLEXPORT void LB_STDCALL CL_doLog(char* f, char* msg) {
                FILE *fp;
                fp = fopen( f, "a" );
                if( fp != NULL ) {
                        fprintf( fp, "%s", msg);
                }
                fclose( fp );
}

DLLEXPORT void LB_STDCALL set_trackObject(char* track) {
	trackObject = track;
	printf("Have a tracking address: %s\n", trackObject);
}

DLLEXPORT void LB_STDCALL track_Object(lb_I_Unknown* o, char* msg) {
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
/*...e*/


#ifdef LINUX
lb_I_Log *lb_log = NULL;
int lb_isInitializing = 0;
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
		char *buffer = (char*) malloc(100+strlen(name));
		buffer[0] = 0;
		sprintf(buffer, "Kann DLL '%s' nicht laden.\n", name); 
            
		logMessage(buffer);
		free(buffer);
			
            LPVOID lpMsgBuf;
	    if (!FormatMessage( 
	      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	      FORMAT_MESSAGE_FROM_SYSTEM | 
	      FORMAT_MESSAGE_IGNORE_INSERTS,
	      NULL,
	      GetLastError(),
	      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	      (LPTSTR) &lpMsgBuf,
	      0,
	      NULL ))
	    {
	      // Handle the error.
	      return ERR_MODULE_NOT_FOUND;
	    }

	    MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

            // Free the buffer.
            LocalFree( lpMsgBuf );
            
            return ERR_MODULE_NOT_FOUND;
        }
#endif
#ifdef LINUX
	if ((hinst = dlopen(name, RTLD_LAZY)) == NULL)
	{
			char* home = 
			#if defined(WINDOWS)
			getenv("USERPROFILE");
			#endif
			#if defined(UNIX) || defined(LINUX) || defined(OSX)
			getenv("HOME");
			#endif

			char* newname = (char*) malloc(strlen(home)+strlen(name)+6);
			
			newname[0] = 0;
			strcat(newname, home);
			strcat(newname, SLASH);
			strcat(newname, "lib");
			strcat(newname, SLASH);
			strcat(newname, name);
	
			if ((hinst = dlopen(newname, RTLD_LAZY)) != NULL) {
				free(newname);
				return ERR_NONE;
			}
			
			free(newname);
			
			char *buffer = (char*) malloc(strlen(name)+100);
			buffer[0] = 0;

			sprintf(buffer, "Kann SO module '%s' nicht laden.\n", name);
			
			logMessage(buffer);
			free(buffer);
			return ERR_MODULE_NOT_FOUND;
	}
#endif
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
lbErrCodes LB_STDCALL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn) {
#ifdef WINDOWS
        if ((*pfn = (void*) GetProcAddress(hinst, name)) == NULL)
        {
            _LOG << "Kann Funktion '" << name << "' nicht finden." LOG_
            return ERR_FUNCTION_NOT_FOUND;
        }
#endif
#ifdef LINUX
	if ((*pfn = dlsym(hinst, name)) == NULL)
	{
            _LOG << "Kann Funktion '" << name << "' nicht finden." LOG_
            return ERR_FUNCTION_NOT_FOUND;	    
	}
#endif
        return ERR_NONE;
}
/*...e*/

static int memTrackerInit = 0;

/*...sDLLEXPORT lb_I_Module\42\ LB_STDCALL getModuleInstance\40\\41\:0:*/
DLLEXPORT lb_I_Module* LB_STDCALL getModuleInstance() {
typedef lbErrCodes (LB_STDCALL *T_p_getlbModuleInstance) (lb_I_Module**, lb_I_Module* m, char* file, int line);
T_p_getlbModuleInstance DLL_GETMODULEINSTANCE;
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Module, module, __FILE__, __LINE__)

	if (memTrackerInit == 0) {
		//DebugBreak();
		memTrackerInit = 1;
		#ifdef WINDOWS
		TRMemOpen();
		TRMemSetModuleName(__FILE__);
		#endif
	}
	
	char* libname = getenv("MODULELIB");
	char* functor = getenv("LBMODULEFUNCTOR");

	if (libname == NULL) {
		#ifdef OSX
			libname = "lbModule.so";
		#endif
	}

	if (functor == NULL) {
		#ifdef OSX
			functor = "getlb_ModuleInstance";
		#endif
	}
	
#ifdef WINDOWS
#ifndef _MSC_VER
	char* temp = new char [strlen(functor)+2];
	temp[0] = 0;
	strcat(temp, "_");
	strcat(temp, functor);
	functor = temp;
#endif
#endif

	if (LB_Module_Handle == NULL) {
		if (lbLoadModule(libname, LB_Module_Handle) != ERR_NONE) {
			char* buf = "Failed to load module manager (%s)\n";
			char* msg = (char*) malloc(strlen(buf)+strlen(libname)+1);
			sprintf(msg, buf, libname);
			logMessage(msg);
			free(msg);
			return NULL;
		}
	}

	if (LB_Module_Handle == NULL) {
		logMessage("Error: Could not load shared library %s\n", libname);
		return NULL;
	}
	
	if (lbGetFunctionPtr(functor, 
			     LB_Module_Handle, 
			     (void **) &DLL_GETMODULEINSTANCE) != ERR_NONE) {
		logMessage("Fatal: Could not get functor for the module manager!\n");
		return NULL;
	}
	
#ifdef WINDOWS
#ifndef _MSC_VER
	if (temp) delete [] temp;
	functor = NULL;
#endif
#endif
	
	if ((err = DLL_GETMODULEINSTANCE(&module, NULL, __FILE__, __LINE__)) == ERR_STATE_FURTHER_LOCK) {
		logMessage("Instance is locked. Must set module manager first\n");
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
	
	setLoggerInstance(NULL);
}
/*...e*/

static bool _isSetTRMemTrackBreak = false;
static char TRMemTrackBreakAddr[21] = "DoNotBreak";

DLLEXPORT bool LB_STDCALL isSetTRMemTrackBreak() {
#ifdef MEMTRACK
	char breakPoint[100] = "";
	
	if (!_isSetTRMemTrackBreak) {
		COUT << "Please enter any memory address to be break at: ";
	
		CIN >> breakPoint ;
	
		setTRMemTrackBreak(breakPoint);
	}
#endif	
	return _isSetTRMemTrackBreak;
}

DLLEXPORT void LB_STDCALL setTRMemTrackBreak(char* brk) {
#ifdef WINDOWS
	if ((brk != NULL) && (strlen(brk) != 0)) {
		_isSetTRMemTrackBreak = true;
		strncpy(TRMemTrackBreakAddr, brk, 20);
		
		// Call TRMemSetAdrBreakPoint for lbHook it self.
		
		TRMemSetAdrBreakPoint(TRMemTrackBreakAddr);
		TRMemSetModuleName(__FILE__);
	} else {
		_isSetTRMemTrackBreak = false;
		// Using any string other than a pointer string let all strcmp fail.
		strncpy(TRMemTrackBreakAddr, "unset", 20);
		TRMemSetAdrBreakPoint("unset");
	}
#endif
}

DLLEXPORT char* LB_STDCALL getTRMemTrackBreak() {
	return TRMemTrackBreakAddr;
}

char* translated = NULL;

DLLEXPORT char* LB_STDCALL translateText(char* text) {
	lb_I_Module* mm = NULL;

	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	UAP_REQUEST(mm, lb_I_Locale, locale)

	locale->translate(&translated, text);

	return translated;
}

/**
 * A moduleinstance is a factory object for all other further instances
 * of registered modules.
 */

/*...sclass lbKey \58\ public lb_I_KeyBase:0:*/
class DLLEXPORT lbKey : public lb_I_KeyBase {
public:
#ifdef _MSC_VER
	lbKey(char* file, int line); // { key = 0; strcpy(keyType, "int"); }
#endif

	lbKey();
	lbKey(int _key);
	lbKey(const lb_I_KeyBase* k);
	virtual ~lbKey();

	DECLARE_LB_UNKNOWN()

	DECLARE_LB_KEYBASE()
	
private:

	char keyType[10];
	int key;
};
/*...e*/


/*...slbKey:0:*/
/*...sc\39\tors and d\39\tors:0:*/
#ifdef _MSC_VER
lbKey::lbKey(char* file, int line) {
        key = 0;
        strcpy(keyType, "int");
}
#endif
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
    _CL_VERBOSE << "lbKey::charrep() in lbHook.cpp" LOG_
    return strdup(buf);
}
/*...e*/
#ifdef bla
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
	_CL_VERBOSE << "lbKey::setData() not implemented yet" LOG_
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
#endif
/*...slbStringKey:0:*/
DLLEXPORT lbStringKey::lbStringKey() {
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
		free(key);
	}
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbStringKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbStringKey::setData(lb_I_Unknown* uk) {
	
	lb_I_KeyBase* string = NULL;
	
	if (uk->queryInterface("lb_I_KeyBase", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
		_CL_VERBOSE << "Error: Could not get interface lb_I_KeyBase" LOG_
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


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();

			if (isSetTRMemTrackBreak()) setTRMemTrackBreak(getTRMemTrackBreak());
			
                	TRMemSetModuleName(__FILE__);
                	
                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:

			free(translated);
			free(lbLogDirectory);
			free(lbLogFile);
			
                	
                	_CL_VERBOSE << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation)
                        {
                                _CL_LOG << "DLL " << __FILE__ << " released by system." LOG_
                        }
                        else
                        {
                                _CL_LOG << "DLL " << __FILE__ << " released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

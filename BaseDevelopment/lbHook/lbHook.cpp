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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sincludes:0:*/
#include <stdarg.h>

// Where should I define standard switches to choose the correct code ?

#ifdef WINDOWS
  #include <windows.h>
#endif
#ifdef OSX
  #include <CoreFoundation/CFBase.h>
#endif
#ifdef LINUX
  #include <dlfcn.h>
  #include <signal.h>
  #ifdef __cplusplus
    extern "C" {
  #endif

//  #include <conio.h>

  #ifdef __cplusplus
    }
  #endif

#endif
/*...e*/

/*...sDeactivate some MSVC warnings:0:*/
#ifdef _MSC_VER
#pragma warning( disable: 4275 )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4101 )
#endif
/*...e*/

	/*...sLB_HOOK_DLL scope:0:*/
#define HOOK_DLL
#define LB_HOOK_DLL
#include <lbhook-module.h>
/*...e*/

/*...smore includes:0:*/
#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef __MINGW32__
#include <direct.h>
#endif

#ifdef OSX
extern "C" {
#include <objc/malloc.h>
}
#endif
/*...e*/



/*...sDefines:0:*/
#ifdef LINUX
#define HINSTANCE void*
#endif
#if defined(OSX) || defined(UNIX) || defined(LINUX)
#define SLASH "/"
#endif
#if defined(WINDOWS)
#define SLASH "\\"
#endif
/*...e*/

/*...sGlobal variables:0:*/
#ifdef WINDOWS
#ifndef LB_CLASSES_DLL
DLLEXPORT lb_I_Log *lb_log = NULL;
DLLEXPORT int lb_isInitializing = 0;
#endif
#ifdef LB_CLASSES_DLL
LB_DLLIMPORT lb_I_Log *lb_log = NULL;
LB_DLLIMPORT int lb_isInitializing = 0;
#endif
#endif
HINSTANCE ModuleHandle = NULL;
HINSTANCE LB_Module_Handle = NULL;
bool lbVerbose = FALSE;
bool lbLogActivated = FALSE;
int instances = 0;
char* lbLogDirectory = NULL;
char* lbLogFile = NULL;
#ifdef LINUX
lb_I_Log *lb_log = NULL;
int lb_isInitializing = 0;
#endif
static int memTrackerInit = 0;

int countModules = 0;

/*...stypedef struct Module:0:*/
typedef struct Module {
	Module() {
		number = -1;
		name = NULL;
		next = NULL;
		lib = NULL;
		skip = false;
	}
	~Module() {
		countModules--;
	}
	// The number of the loaded module (count of loaded modules)
	int number;
	char* name;
	Module* next;
	HINSTANCE lib;
	// The references I have made while loading the module
	int libreferences;
	bool skip;
} _Modules;
/*...e*/

_Modules* loadedModules = NULL;
static bool b_isSetTRMemTrackBreak = false;
static char TRMemTrackBreakAddr[21] = "DoNotBreak";
char* translated = NULL;
/*...e*/

#ifdef __MINGW32__
extern "C" DLLEXPORT bool 		LB_CDECL _isVerbose() { return isVerbose(); }
extern "C" DLLEXPORT bool 		LB_CDECL _isLogActivated() { return isLogActivated(); }
extern "C" DLLEXPORT lbErrCodes 	LB_CDECL _lbLoadModule(const char* name, HINSTANCE & hinst, bool skipAutoUnload) { return lbLoadModule(name, hinst, skipAutoUnload); }
extern "C" DLLEXPORT lb_I_Module* 	LB_CDECL _getModuleInstance() { return getModuleInstance(); }
extern "C" DLLEXPORT void 		LB_CDECL _set_trackObject(char* track) { set_trackObject(track); }
extern "C" DLLEXPORT char* 		LB_CDECL _get_trackObject() { return get_trackObject(); }
extern "C" DLLEXPORT void 		LB_CDECL _track_Object(lb_I_Unknown* o, char* msg) { track_Object( o, msg); }
extern "C" DLLEXPORT void 		LB_CDECL _setVerbose(bool what) { setVerbose(what); }
extern "C" DLLEXPORT void 		LB_CDECL _setLogActivated(bool what) { setLogActivated(what); }
extern "C" DLLEXPORT void 		LB_CDECL _lbBreak() { lbBreak(); }
extern "C" DLLEXPORT void 		LB_CDECL _logMessage(const char *msg, char *f, int level) { logMessage(msg, f, level); }
extern "C" DLLEXPORT void 		LB_CDECL _createDirectory(const char* name) { createDirectory(name); }
extern "C" DLLEXPORT void 		LB_CDECL _deleteDirectory(const char* name) { deleteDirectory(name); }
extern "C" DLLEXPORT HINSTANCE 		LB_CDECL _getModuleHandle() { return getModuleHandle(); }
extern "C" DLLEXPORT HINSTANCE 		LB_CDECL _getLBModuleHandle() { return getLBModuleHandle(); }
extern "C" DLLEXPORT void 		LB_CDECL _setModuleHandle(HINSTANCE h) { setModuleHandle(h); }
extern "C" DLLEXPORT void 		LB_CDECL _setLBModuleHandle(HINSTANCE h) { setLBModuleHandle(h); }
extern "C" DLLEXPORT int 		LB_CDECL _isInitializing() { return isInitializing(); }
extern "C" DLLEXPORT void 		LB_CDECL _setInitializing(int i) { setInitializing(i); }
extern "C" DLLEXPORT lb_I_Log* 		LB_CDECL _getLoggerInstance() {return getLoggerInstance(); }
extern "C" DLLEXPORT void 		LB_CDECL _setLoggerInstance(lb_I_Log* l) { setLoggerInstance(l); }
extern "C" DLLEXPORT void 		LB_CDECL _createLogInstance() { return createLogInstance(); }
extern "C" DLLEXPORT bool 		LB_CDECL _isSetTRMemTrackBreak() { return isSetTRMemTrackBreak(); }
extern "C" DLLEXPORT void 		LB_CDECL _setTRMemTrackBreak(char* brk, int count) { setTRMemTrackBreak(brk, count); }
extern "C" DLLEXPORT char* 		LB_CDECL _getTRMemTrackBreak() { return getTRMemTrackBreak(); }
extern "C" DLLEXPORT void 		LB_CDECL _InstanceCount(int inst) { InstanceCount(inst); }
extern "C" DLLEXPORT void 		LB_CDECL _Instances() { Instances(); }
extern "C" DLLEXPORT lbErrCodes		LB_CDECL _lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn) { return lbGetFunctionPtr(name, hinst, pfn); }
extern "C" DLLEXPORT lbStringKey*	LB_CDECL _getStringKey(char* buf) { return getStringKey(buf); }
extern "C" DLLEXPORT char* 		LB_CDECL _getLogDirectory() { return getLogDirectory(); }
extern "C" DLLEXPORT char* 		LB_CDECL _setLogDirectory(char* name) { return setLogDirectory(name); }
extern "C" DLLEXPORT bool 		LB_CDECL _FileExists(char *filename) { return FileExists(filename);}
extern "C" DLLEXPORT bool 		LB_CDECL _DirectoryExists(char *filename) { return DirectoryExists(filename);}
extern "C" DLLEXPORT DWORD 		LB_CDECL _lbGetCurrentProcessId() { return lbGetCurrentProcessId(); }
extern "C" DLLEXPORT char* 		LB_CDECL _lb_ptoa(void* ptr) { return lb_ptoa(ptr); }
extern "C" DLLEXPORT char* 		LB_CDECL _lb_itoa(int ptr) { return lb_itoa(ptr); }
extern "C" DLLEXPORT char* 		LB_CDECL _lb_ltoa(const long ptr) { return lb_ltoa(ptr); }
extern "C" DLLEXPORT DWORD 		LB_CDECL _lbGetCurrentThreadId() { return lbGetCurrentThreadId(); }
extern "C" DLLEXPORT void		LB_CDECL _lb_sleep(int ms) { lb_sleep(ms); }
extern "C" DLLEXPORT lbErrCodes LB_CDECL _lbUnloadModule(const char* name) { return lbUnloadModule(name); }
extern "C" DLLEXPORT char*		LB_CDECL _translateText(char* text) { return translateText(text); }
extern "C" DLLEXPORT void		LB_CDECL _uninitLocale() { uninitLocale(); }
extern "C" DLLEXPORT void		LB_CDECL _unHookAll() { unHookAll(); }
extern "C" DLLEXPORT char*      LB_CDECL _lbstrristr(const char *String, const char *Pattern) { return lbstrristr(String, Pattern); }
extern "C" DLLEXPORT char*      LB_CDECL _lbstristr(const char *String, const char *Pattern) { return lbstristr(String, Pattern); }
extern "C" DLLEXPORT char*		LB_CDECL _getOsType() { return getOsType(); }

#endif

extern "C" DLLEXPORT lbStringKey*	LB_CDECL getStringKey(char* buf) { return new lbStringKey(buf); }



/*...sDLLEXPORT void createLogInstance\40\\41\:0:*/
extern "C" DLLEXPORT void LB_CDECL createLogInstance() {
			if (getLoggerInstance() == NULL) {
				setInitializing(1);
				lb_I_Module* modMan = getModuleInstance();

				if (modMan != NULL) {
					lb_I_Unknown *Unknown = NULL;
					modMan->initialize();
					lbErrCodes err = modMan->request("lb_I_Log", &Unknown);
					\
					if (Unknown != NULL) {
						lb_I_Log* log;
						Unknown->queryInterface("lb_I_Log", (void**) &log, __FILE__, __LINE__);
						setLoggerInstance(log);
						Unknown->release(__FILE__, __LINE__);
						if (log == NULL) {
							exit (1);
						} else {
						}
					} else {
						exit(1);
					}
					modMan->release(__FILE__, __LINE__);
				} else {
					exit(1);
				}
			}
			setInitializing(0);
}
/*...e*/

/*...sDLLEXPORT void logMessage\40\const char \42\msg\44\ char \42\f\44\ int level\41\:0:*/
DLLEXPORT void logMessage(const char *msg, char *f, int level) {
                FILE *fp;
				if (!isLogActivated()) return;
				if (!DirectoryExists(getLogDirectory())) createDirectory(getLogDirectory());
                fp = fopen( f, "a" );
                if( fp != NULL ) {
                        char* buf = (char*) malloc(strlen(msg)+100);
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

						if (isVerbose()) {
							// Also copy the log entry to console.
							_CL_VERBOSE << msg LOG_
						}
						fclose( fp );
						free(buf);
                }
}
/*...e*/
/*...svoid logMessage\40\const char \42\msg\41\:0:*/
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
/*...e*/

DLLEXPORT char* LB_CDECL setLogDirectory(char* name) {
	if (lbLogDirectory != NULL) free(lbLogDirectory);
	lbLogDirectory = strdup(name);
}

/*...sDLLEXPORT char\42\ LB_CDECL getLogDirectory\40\\41\:0:*/
DLLEXPORT char* LB_CDECL getLogDirectory() {
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
/*...e*/

/** \brief Return the operating system type.
 * On windows it will return "Windows".
 * On Mac it will return "Mac".
 * On Linux, Solaris and other Unix flavour systems it will return "Unix".
 */
extern "C" DLLEXPORT char* LB_CDECL getOsType() {
	static char* osIsMac = "Mac";
	static char* osIsWindows = "Windows";
	static char* osIsUnix = "Unix";

#ifdef __MINGW32__
	return osIsWindows;
#endif
#ifdef __WATCOMC__
	return osIsWindows;
#endif
#ifdef OSX
	return osIsMac;
#endif
#ifdef LINUX
	return osIsUnix;
#endif
#ifdef UNIX
	return osIsUnix;
#endif	
}


DLLEXPORT void LB_CDECL deleteDirectory(const char* name) {
		#ifdef __MINGW32__
		rmdir(name);
		#endif
		#ifdef __WATCOMC__
		rmdir(name);
		#endif
		#if defined(OSX) || defined(LINUX) || defined(UNIX)
        rmdir(name);
		#endif
}


/*...sDLLEXPORT void LB_CDECL createDirectory\40\const char\42\ name\41\:0:*/
DLLEXPORT void LB_CDECL createDirectory(const char* name) {
		#ifdef __MINGW32__
		mkdir(name);
		#endif
		#ifdef __WATCOMC__
		mkdir(name);
		#endif
		#if defined(OSX) || defined(LINUX) || defined(UNIX)
        mkdir(name, S_IRWXU);
		#endif
}
/*...e*/

/*...sDLLEXPORT void LB_CDECL InstanceCount\40\int inst\41\:0:*/
extern "C" DLLEXPORT void LB_CDECL InstanceCount(int inst) {
	instances += inst;
}
/*...e*/
/*...sDLLEXPORT void LB_CDECL Instances\40\\41\:0:*/
DLLEXPORT void LB_CDECL Instances() {
	printf("Current instances are %d.\n", instances);
}
/*...e*/
/*...sDLLEXPORT void LB_CDECL setVerbose\40\bool what\41\:0:*/
DLLEXPORT void LB_CDECL setVerbose(bool what) {
    lbVerbose = what;
}
/*...e*/
/*...sDLLEXPORT void LB_CDECL setVerbose\40\bool what\41\:0:*/
DLLEXPORT void LB_CDECL setLogActivated(bool what) {
    lbLogActivated = what;
}
/*...e*/
/*...sDLLEXPORT bool LB_CDECL isVerbose\40\\41\:0:*/
extern "C" DLLEXPORT bool LB_CDECL isVerbose() {
	return lbVerbose;
}
/*...e*/
/*...sDLLEXPORT bool LB_CDECL isLogActivated\40\\41\:0:*/
extern "C" DLLEXPORT bool LB_CDECL isLogActivated() {
	return lbLogActivated;
}
/*...e*/

/*...sHelpers:0:*/
DLLEXPORT int LB_CDECL isInitializing() {
	return lb_isInitializing;
}

DLLEXPORT void LB_CDECL setInitializing(int i) {
	lb_isInitializing = i;
}

DLLEXPORT lb_I_Log* LB_CDECL getLoggerInstance() {
	return lb_log;
}

DLLEXPORT void LB_CDECL setLoggerInstance(lb_I_Log* l) {
	lb_log = l;
}


char* trackObject = NULL;

DLLEXPORT char* LB_CDECL lb_itoa(int ptr) {
        static char buf[20] = "";
        sprintf(buf, "%d", ptr);
        return buf;
}

DLLEXPORT char* LB_CDECL lb_ltoa(const long ptr) {
        static char buf[20] = "";
        sprintf(buf, "%ld", ptr);
        return buf;
}

DLLEXPORT char* LB_CDECL lb_ptoa(void* ptr) {
        static char buf[20] = "";
	sprintf(buf, "%p", ptr);
        return buf;
}

DLLEXPORT void LB_CDECL CL_doLog(char* f, char* msg) {
                FILE *fp;
                fp = fopen( f, "a" );
                if( fp != NULL ) {
                        fprintf( fp, "%s", msg);
                }
                fclose( fp );
}

DLLEXPORT void LB_CDECL set_trackObject(char* track) {
	trackObject = track;
	printf("Have a tracking address: %s\n", trackObject);
}

DLLEXPORT void LB_CDECL track_Object(lb_I_Unknown* o, char* msg) {
}

DLLEXPORT char* LB_CDECL get_trackObject() {
	if (trackObject == NULL) return getenv("TRACKOBJECT");
	return trackObject;
}

DLLEXPORT HINSTANCE LB_CDECL getModuleHandle() {
	return ModuleHandle;
}

DLLEXPORT HINSTANCE LB_CDECL getLBModuleHandle() {
	return LB_Module_Handle;
}

DLLEXPORT void LB_CDECL setModuleHandle(HINSTANCE h) {
	ModuleHandle = h;
}

DLLEXPORT void LB_CDECL setLBModuleHandle(HINSTANCE h) {
	LB_Module_Handle = h;
}
/*...e*/

/*...s_Modules \42\createModule\40\const char\42\ name\41\:0:*/
_Modules *createModule(const char* name) {
    const char* moduleName = NULL;
    const char* copyOfName = NULL;

	copyOfName = strdup(name);
	
    moduleName = lbstrristr(copyOfName, "\\");
    if (moduleName == NULL) moduleName = lbstrristr(copyOfName, "/");
    if (moduleName == NULL) moduleName = copyOfName;

    char* cutoff = lbstristr(moduleName, ".");
    if (cutoff != NULL) cutoff[0] = 0;

    if (moduleName[0] == '\\') moduleName++;
    if (moduleName[0] == '/') moduleName++;
    if (isVerbose()) printf("Create a module entry: %s\n", moduleName);

	countModules++;
	_Modules* temp = NULL;
	if (loadedModules == NULL) {
		loadedModules = new _Modules;
		loadedModules->number = 1;
		loadedModules->name = (char*) malloc(strlen(moduleName)+1);
		loadedModules->name[0] = 0;
		loadedModules->next = NULL;
		strcpy(loadedModules->name, moduleName);
		return loadedModules;
	} else {
		temp = new _Modules;
		temp->number = loadedModules->number+1;
		temp->name = (char*) malloc(strlen(moduleName)+1);
		temp->name[0] = 0;
		strcpy(temp->name, moduleName);

		temp->next = loadedModules;
		loadedModules = temp;

		return temp;
	}
}
/*...e*/
/*...s_Modules \42\findModule\40\const char\42\ name\41\:0:*/
_Modules *findModule(const char* name) {
	_Modules *temp = loadedModules;
	_Modules *found = NULL;
	int count = 0;


    const char* moduleName = NULL;
    const char* copyOfName = NULL;
	
	copyOfName = strdup(name);
	
    moduleName = lbstrristr(copyOfName, "\\");
    if (moduleName == NULL) moduleName = lbstrristr(copyOfName, "/");
    if (moduleName == NULL) moduleName = copyOfName;
	
    char* cutoff = lbstristr(moduleName, ".");
    if (cutoff != NULL) cutoff[0] = 0;

    if (moduleName[0] == '\\') moduleName++;
    if (moduleName[0] == '/') moduleName++;


	while (temp != NULL) {
		count++;
		if (strcmp(temp->name, moduleName) == 0) {
			found = temp;
		}
		temp = temp->next;
	}

	if (count != countModules) {
		_CL_LOG << "ERROR: Count of loaded modules disagree with count value." LOG_
	}

	return found;
}
/*...e*/

/*...svoid destroyModuleStructure\40\_Modules\42\ m\41\:0:*/
void destroyModuleStructure(_Modules* m) {
	if (m->next) {
		destroyModuleStructure(m->next);
	}
	free(m->name);
	delete m;
}
/*...e*/

/*...sDLLEXPORT void LB_CDECL lbBreak\40\\41\:0:*/
DLLEXPORT void LB_CDECL lbBreak() {

#ifdef LINUX
#ifndef OSX
    raise(SIGTRAP);
#endif
#endif
#ifdef OSX
    Debugger();
#endif
#ifdef WINDOWS
    DebugBreak();
#endif

}
/*...e*/

/*...sDLLEXPORT bool LB_CDECL lbPtrValidate\40\void\42\ ptr\41\:0:*/
DLLEXPORT bool LB_CDECL lbPtrValidate(void* ptr) {
	if (ptr != NULL) {
		return true;
	} else {
		return false;
	}
}
/*...e*/

/*...sbool LB_CDECL OSXMemValidate\40\void\42\ ptr\41\:0:*/
#ifdef OSX
bool LB_CDECL OSXMemValidate(void* ptr) {
#ifdef DEBUG_MALLOC
	if (malloc_zone_check(0) == 1) {
			return true;
	} else {
			_CL_LOG << "FATAL: Heap corruption detected!" LOG_
	}
#endif
#ifndef DEBUG_MALLOC
	return true;
#endif
}
#endif
/*...e*/

extern "C" DLLEXPORT bool LB_CDECL DirectoryExists(char *filename)
{
	if (FileExists(filename)) return true;
#ifdef WINDOWS
	if (_mkdir(filename) == -1) return true;
#endif
#ifdef LINUX
	if (mkdir(filename, 0777) == -1) return true;
#endif
	rmdir(filename);
	return false;
}

/*...sDLLEXPORT bool LB_CDECL FileExists\40\char \42\filename\41\:0:*/
#ifdef WINDOWS
DLLEXPORT bool LB_CDECL FileExists(char *filename)
{
	OFSTRUCT ofs;
	return OpenFile(filename, &ofs, OF_EXIST) != HFILE_ERROR;
}
#endif
#ifndef OSX
#ifdef LINUX
DLLEXPORT bool LB_CDECL FileExists(char *filename)
{
	struct stat sb;
	return stat(filename, &sb) != -1;
}
#endif
#endif
#ifdef OSX
DLLEXPORT bool LB_CDECL FileExists(char *filename)
{
	struct stat sb;
	return stat(filename, &sb) != -1;
}
#endif
/*...e*/

/*...slbErrCodes LB_CDECL lbLoadModule\40\const char\42\ name\44\ HINSTANCE \38\ hinst\44\ bool skipAutoUnload\41\:0:*/
DLLEXPORT lbErrCodes LB_CDECL lbLoadModule(const char* name, HINSTANCE & hinst, bool skipAutoUnload) {
	if (name == NULL) {
		_LOG << "Erro: lbLoadModule() called with an invalid parameter!" LOG_
		return ERR_MODULE_INVALID_PARAMETER;
	}

	if (isVerbose()) {
		_LOG << "Try to load a module " << name LOG_
	}

#ifdef WINDOWS

	_Modules *m = findModule(name);

	if (m) {
		hinst = m->lib;
		m->libreferences++;
		return ERR_NONE;
	} else {
		m = createModule(name);
		m->libreferences = 1;
	}

	if ((hinst = LoadLibrary(name)) == NULL)
	{
		char *buffer = (char*) malloc(100+strlen(name)+strlen(__FILE__));
		buffer[0] = 0;
		sprintf(buffer, "%s:%d Kann DLL '%s' nicht laden.\n", __FILE__, __LINE__, name);

		logMessage(buffer);
		free(buffer);

		LPVOID lpMsgBuf;
		if (isVerbose()) {
			if (!FormatMessage(
								FORMAT_MESSAGE_ALLOCATE_BUFFER |
								FORMAT_MESSAGE_FROM_SYSTEM |
								FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL,
								GetLastError(),
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
								(LPTSTR) &lpMsgBuf,
								0,
								NULL))
			{
				// Handle the error.
				return ERR_MODULE_NOT_FOUND;
			}

			MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

			// Free the buffer.
			LocalFree( lpMsgBuf );
		}

		return ERR_MODULE_NOT_FOUND;
	}

	m->lib = hinst;
	m->skip = skipAutoUnload;
#endif
#ifdef LINUX

	_Modules *m = findModule(name);

	if (m != NULL) {
		hinst = m->lib;
		m->libreferences++;
		return ERR_NONE;
	} else {
		m = createModule(name);
		m->libreferences = 1;
	}

	if ((hinst = dlopen(name, RTLD_LAZY)) == NULL)
	{
		char* home = NULL;//(char*) malloc(100);
		char* newname = NULL;

		char* errmsg = dlerror();

		if (errmsg != NULL) {
			printf("DLERROR: %s\n", errmsg);
		}


#if defined(UNIX) || defined(LINUX) || defined(OSX)
		home = ".";//getcwd(home, 100);

			if (home != NULL) {
				newname = (char*) malloc(strlen(home)+strlen(name)+6);
				newname[0] = 0;
				strcat(newname, home);
				strcat(newname, SLASH);
				strcat(newname, "lib");
				strcat(newname, SLASH);
				strcat(newname, name);

				if ((hinst = dlopen(newname, RTLD_LAZY)) != NULL) {
					m->lib = hinst;
					m->skip = skipAutoUnload;
					free(newname);

					return ERR_NONE;
				} else {
					char* errmsg = dlerror();

					if (errmsg != NULL) {
						printf("DLERROR: %s\n", errmsg);
					}
				}

				free(newname);
			}
#endif

			home =
#if defined(WINDOWS)
			getenv("USERPROFILE");
#endif
#if defined(UNIX) || defined(LINUX) || defined(OSX)
			getenv("HOME");
#endif

			newname = (char*) malloc(strlen(home)+strlen(name)+6);

			newname[0] = 0;
			strcat(newname, home);
			strcat(newname, SLASH);
			strcat(newname, "lib");
			strcat(newname, SLASH);
			strcat(newname, name);

			if ((hinst = dlopen(newname, RTLD_LAZY)) != NULL) {
				m->lib = hinst;
				m->skip = skipAutoUnload;
				free(newname);

				return ERR_NONE;
			} else {
				free(newname);

				newname = (char*) malloc(strlen(".")+strlen(SLASH)*5+strlen("wxWrapper.app")+strlen("Contents")+strlen("lib")+strlen(name)+6);
				//newname = (char*) malloc(strlen(".")+strlen(SLASH)*5+strlen("wxWrapper.app")+strlen("Contents")+strlen("Resources")+strlen("lib")+strlen(name)+6);
				newname[0] = 0;

				strcat(newname, ".");
				strcat(newname, SLASH);
				strcat(newname, "wxWrapper.app");
				strcat(newname, SLASH);
				strcat(newname, "Contents");
				//strcat(newname, SLASH);
				//strcat(newname, "Resources");
				strcat(newname, SLASH);
				strcat(newname, "lib");
				strcat(newname, SLASH);
				strcat(newname, name);

				if ((hinst = dlopen(newname, RTLD_LAZY)) != NULL) {
					m->lib = hinst;
					m->skip = skipAutoUnload;
					free(newname);

					return ERR_NONE;
				}
				char* errmsg = dlerror();

				if (errmsg != NULL) {
					printf("DLERROR: %s\n", errmsg);
				}
			}

			free(newname);

			newname = (char*) malloc(strlen("..")+strlen(SLASH)+strlen("plugins")+strlen(SLASH)+strlen(name)+6);
			newname[0] = 0;
			strcat(newname, "..");
			strcat(newname, SLASH);
			strcat(newname, "plugins");
			strcat(newname, SLASH);
			strcat(newname, name);

#ifndef __WATCOMC__
		// Quick hack
#define MAX_PATH 512
#endif

		// Try a trick
			char oldcwd[MAX_PATH+1] = "";
			char newcwd[MAX_PATH+1] = "";
			getcwd(oldcwd, sizeof(oldcwd));
			strcat(newcwd, ".");
			strcat(newcwd, SLASH);
			strcat(newcwd, "wxWrapper.app");
			strcat(newcwd, SLASH);
			strcat(newcwd, "Contents");
			strcat(newcwd, SLASH);
			strcat(newcwd, "lib");

			chdir(newcwd);
			if ((hinst = dlopen(newname, RTLD_LAZY)) != NULL) {
				m->lib = hinst;
				m->skip = skipAutoUnload;
				free(newname);

				chdir(oldcwd);
				return ERR_NONE;
			}
			chdir(oldcwd);
			errmsg = dlerror();

			if (errmsg != NULL) {
				printf("DLERROR: %s\n", errmsg);
			}

			char *buffer = (char*) malloc(strlen(name)+strlen(__FILE__)+100);
			buffer[0] = 0;

			sprintf(buffer, "%s:%d Kann SO module '%s' nicht laden.\n", __FILE__, __LINE__, name);

			logMessage(buffer);
			free(buffer);
			return ERR_MODULE_NOT_FOUND;
	}

	m->lib = hinst;
	m->skip = skipAutoUnload;

#endif
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_CDECL lbGetFunctionPtr\40\const char\42\ name\44\ const HINSTANCE \38\ hinst\44\ void\42\\42\ pfn\41\:0:*/
DLLEXPORT lbErrCodes LB_CDECL lbGetFunctionPtr(const char* name, HINSTANCE hinst, void** pfn) {
		if (name == NULL) {
			_LOG << "Erro: lbGetFunctionPtr() called with an invalid parameter!" LOG_
			return ERR_MODULE_INVALID_PARAMETER;
		}

#ifdef WINDOWS
        if ((*pfn = (void*) GetProcAddress(hinst, name)) == NULL)
        {
            _CL_LOG << "Kann Funktion '" << name << "' nicht finden." LOG_
            return ERR_FUNCTION_NOT_FOUND;
        }
#endif
#ifdef LINUX
	if ((*pfn = dlsym(hinst, name)) == NULL)
	{
            _CL_LOG << "Kann Funktion '" << name << "' nicht finden." LOG_
            return ERR_FUNCTION_NOT_FOUND;
	}
#endif
        return ERR_NONE;
}
/*...e*/
/*...sDLLEXPORT lb_I_Module\42\ LB_CDECL getModuleInstance\40\\41\:0:*/
DLLEXPORT lb_I_Module* LB_CDECL getModuleInstance() {
typedef lbErrCodes (LB_CDECL *T_p_getlbModuleInstance) (lb_I_Module**, lb_I_Module* m, char* file, int line);
T_p_getlbModuleInstance DLL_GETMODULEINSTANCE;
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Module, module)

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
		#ifdef LINUX
			libname = "lbModule.so";
		#endif
		#ifdef WINDOWS
			libname = "lbModule.dll";
		#endif
	}

	if (functor == NULL) {
		#ifdef OSX
			functor = "getlb_ModuleInstance";
		#endif
		#ifdef LINUX
			functor = "getlb_ModuleInstance";
		#endif
		#ifdef WINDOWS
			functor = "getlb_ModuleInstance";
		#endif
	}

#ifdef WINDOWS
#ifndef _MSC_VER
#ifndef __MINGW32__
	char* temp = (char*) malloc(strlen(functor)+2);
	temp[0] = 0;
	strcat(temp, "_");
	strcat(temp, functor);
	functor = temp;
#endif
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
#ifndef __MINGW32__
	if (temp) free((void*)temp);
	functor = NULL;
#endif
#endif
#endif

	if ((err = DLL_GETMODULEINSTANCE(&module, NULL, __FILE__, __LINE__)) == ERR_STATE_FURTHER_LOCK) {
		logMessage("Instance is locked. Must set module manager first\n");
		module->setModuleManager(module.getPtr(), __FILE__, __LINE__);
	}
	UAP(lb_I_Module, inst)
	QI(module, lb_I_Module, inst)

	return inst.getPtr();
}
/*...e*/
/*...slbErrCodes LB_CDECL releaseInstance\40\lb_I_Unknown\42\ inst\41\:0:*/
lbErrCodes LB_CDECL releaseInstance(lb_I_Unknown* inst) {
	typedef lbErrCodes (LB_CDECL *T_p_releaseInstance) (lb_I_Unknown*);
	T_p_releaseInstance DLL_RELEASEINSTANCE;

	if (lbGetFunctionPtr("_lb_releaseInstance", LB_Module_Handle, (void**) &DLL_RELEASEINSTANCE) != ERR_NONE) {
		exit(1);
	}

	DLL_RELEASEINSTANCE(inst);

	return ERR_NONE;
}
/*...e*/
/*...sDLLEXPORT bool LB_CDECL isSetTRMemTrackBreak\40\\41\:0:*/
DLLEXPORT bool LB_CDECL isSetTRMemTrackBreak() {
#ifdef MEMTRACK
	char breakPoint[100] = "";
	int count = 0;

	if (!b_isSetTRMemTrackBreak) {
		COUT << "Please enter any memory address to be break at: ";
		CIN >> breakPoint ;

		COUT << "Please enter count at wich the break should happen: ";
		CIN >> count;

		setTRMemTrackBreak(breakPoint, count);
	}
#endif
	return b_isSetTRMemTrackBreak;
}
/*...e*/
/*...sDLLEXPORT void LB_CDECL setTRMemTrackBreak\40\char\42\ brk\44\ int count\41\:0:*/
DLLEXPORT void LB_CDECL setTRMemTrackBreak(char* brk, int count) {
#ifdef WINDOWS
	if ((brk != NULL) && (strlen(brk) != 0)) {
		b_isSetTRMemTrackBreak = true;
		strncpy(TRMemTrackBreakAddr, brk, 20);

		// Call TRMemSetAdrBreakPoint for lbHook it self.

		TRMemSetAdrBreakPoint(TRMemTrackBreakAddr, count);
		TRMemSetModuleName(__FILE__);
	} else {
		b_isSetTRMemTrackBreak = false;
		// Using any string other than a pointer string let all strcmp fail.
		strncpy(TRMemTrackBreakAddr, "unset", 20);
		TRMemSetAdrBreakPoint("unset", count);
	}
#endif
}
/*...e*/
/*...sDLLEXPORT char\42\ LB_CDECL getTRMemTrackBreak\40\\41\:0:*/
DLLEXPORT char* LB_CDECL getTRMemTrackBreak() {
	return TRMemTrackBreakAddr;
}
/*...e*/
/*...sDLLEXPORT char\42\ LB_CDECL translateText\40\char\42\ text\41\:0:*/

UAP(lb_I_Locale, locale)


DLLEXPORT void LB_CDECL uninitLocale() {
	if (locale != NULL) {
		locale--;
		locale.resetPtr();
	}
}

DLLEXPORT char* LB_CDECL translateText(char* text) {
	lbErrCodes err = ERR_NONE;

	if (locale == NULL) {
		REQUEST(getModuleInstance(), lb_I_Locale, locale)

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		// Need to derive filename from given application name
		UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
		*filename = "translations.dat";

		UAP_REQUEST(getModuleInstance(), lb_I_Database, database)

		if (database == NULL) return text;
		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			return text;
		}

		bool isFileAvailable = false;

		UAP(lb_I_DatabaseOperation, fDBOp)

		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");

		if (pl != NULL)	{
			ukPl = pl->getImplementation();
			if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fDBOp)
			isFileAvailable = fDBOp->begin("lbDMF", *&database);

			if (isFileAvailable) {
				UAP(lb_I_Plugin, plTranslations)
				UAP(lb_I_Unknown, ukPlTranslations)

				plTranslations = PM->getFirstMatchingPlugin("lb_I_Translations", "Model");
				if (plTranslations != NULL) {
					ukPlTranslations = plTranslations->getImplementation();
				} else {
					_LOG << "Warning: No translations datamodel plugin found." LOG_
				}

				ukPlTranslations->accept(*&fDBOp);

				locale->setTranslationData(*&ukPlTranslations);

				_CL_LOG << "Loaded translation data into translation model and provided it to locale." LOG_

				fDBOp->end();
			}
		}
	}

	locale->translate(&translated, text);
	return translated;
}
/*...e*/

#define NUL '\0'
char* LB_STDCALL lbstristr(const char *String, const char *Pattern)
{
	char *pptr, *sptr, *start;

	for (start = (char *)String; *start != NUL; start++)
	{
		/* find start of pattern in string */
		for ( ; ((*start!=NUL) && (toupper(*start) != toupper(*Pattern))); start++)
			;
		if (NUL == *start)
			return NULL;

		pptr = (char *)Pattern;
		sptr = (char *)start;

		while (toupper(*sptr) == toupper(*pptr))
		{
			sptr++;
			pptr++;

			/* if end of pattern then pattern was found */

			if (NUL == *pptr)
				return (start);
		}
	}
	return NULL;
}

char* LB_STDCALL lbstrristr(const char *String, const char *Pattern)
{
	char *r = NULL;

	if (!Pattern[0])
		return (char*)String + strlen(String);
	while (1) {
		char *p = lbstristr(String, Pattern);
		if (!p)
			return r;
		r = p;
		String = p + 1;
	}
}
#undef NUL

/*...sDLLEXPORT lbErrCodes LB_CDECL lbUnloadModule\40\const char\42\ name\41\:0:*/
DLLEXPORT lbErrCodes LB_CDECL lbUnloadModule(const char* name) {

#ifdef WINDOWS
		_Modules* temp = loadedModules;
		_Modules* lastMod = NULL;

		while (temp) {
			if (temp->name == NULL) {
				lastMod = temp;
				temp = temp->next;
				continue;
			}

			if (temp->name != NULL) {
				if (strcmp(temp->name, name) == 0) {
					_Modules* delMod = temp;

					if (loadedModules == temp) {
						lastMod = temp;
						temp = temp->next;
						loadedModules = temp;
					} else {
						lastMod = temp;
						temp = temp->next;
					}

                    if (isVerbose()) printf("Unloading module %s\n", delMod->name);
					if (FreeLibrary(delMod->lib) == 0) {
						printf("ERROR: Library could not be unloaded!\n");
					}

					free(delMod->name);
					lastMod->next = delMod->next;
					delete delMod;
				} else {
					lastMod = temp;
					temp = temp->next;
				}
			}
		}
#endif
#ifdef LINUX
		_Modules* temp = loadedModules;
		_Modules* lastMod = NULL;

		if (name == NULL) _CL_LOG << "ERROR: Could not unload unknown module.\n" LOG_

		while (temp) {
			if (temp->name == NULL) {
				lastMod = temp;
				temp = temp->next;
				continue;
			}

			if (temp->name != NULL) {
				if (isVerbose()) printf("Test if module %s is %s.\n", temp->name, name);
				if (lbstristr(temp->name, name) != 0) {
					_Modules* delMod = temp;
					temp = temp->next;

					if (lastMod != NULL) {
						lastMod->next = delMod->next;
					}

					if (loadedModules == delMod) {
						loadedModules = delMod->next;
					}
					int errCode = 0;
					printf("Unload module %s with %d references.\n", name, delMod->libreferences);
					while ((errCode = dlclose(delMod->lib)) == 0) {
						//if (isVerbose())
							printf("Unloaded module %s.\n", name);
					}
					{
						printf("Error while unloading module: %s\n", dlerror());
						if (isVerbose()) printf("ERROR: Library could not be unloaded!\n");
					}

					free(delMod->name);
					delete delMod;
				} else {
					lastMod = temp;
					temp = temp->next;
				}
			}
		}
#endif

	return ERR_NONE;
}
/*...e*/

void unloadModule(_Modules* m) {
    while(loadedModules) {
        if (strcmp(loadedModules->name, "lbModule") != 0) {
            lbUnloadModule(loadedModules->name);
        } else {
            if (loadedModules->next != NULL) {
                loadedModules = loadedModules->next;
            } else {
                if (strcmp(loadedModules->name, "lbModule") == 0) break;
            }
        }

    }
}

/*...svoid LB_CDECL unHookAll\40\\41\:0:*/
DLLEXPORT void LB_CDECL unHookAll() {
    uninitLocale();

    if (loadedModules)
        unloadModule(loadedModules);
}

DLLEXPORT void LB_CDECL unHookAll_old() {
	_Modules* skipped = NULL;
	_Modules* temp_skipped = NULL;

	if (lb_log) {
#ifndef __MINGW32__
		_LOG << "unHookAll() releases log instance. This should be the last entry for this process." LOG_
#endif
		//lb_log->release(__FILE__, __LINE__);
	}

	if (locale != NULL) {
		locale--;
		locale.resetPtr();
	}

#ifndef WINDOWS
		_Modules* temp = loadedModules;
		while (temp) {
			if (temp->name == NULL) {
				_Modules* delMod = temp;
				_CL_LOG << "ERROR: Found a module without a stored name!" LOG_
				if (dlclose(temp->lib) != 0) {
					char* msg = dlerror();
					if (msg) printf("%s\n", msg);
					temp = temp->next;
				} else {
					temp = temp->next;
					if (delMod == loadedModules) loadedModules = loadedModules->next;
					delete delMod;
					//if (temp == NULL) temp = loadedModules;
				}
			}
			if (temp->name != NULL) {
				_Modules* delMod = temp;

				if (strcmp(temp->name, "lbModule") == 0) {
					temp = temp->next;
					if (delMod == loadedModules) loadedModules = loadedModules->next;
					delete delMod;
					//if(temp == NULL) temp = loadedModules;
					continue;
				}

				_CL_VERBOSE << "Unhook module " << temp->name << "." LOG_

				if (dlclose(temp->lib) != 0) {
					char* msg = dlerror();
					if (msg) printf("%s\n", msg);
					temp = temp->next;
				} else {
					temp = temp->next;
					if (delMod == loadedModules) loadedModules = loadedModules->next;
					delete delMod;
					//if (temp == NULL) temp = loadedModules;
				}
			}
		}
#endif
#ifdef WINDOWS
		_Modules* temp = loadedModules;
		while (temp) {
			if (temp->name != NULL) {
				_Modules* delMod = temp;

				if (strcmp(temp->name, "lbModule") == 0) {
					temp = temp->next;
					if (delMod == loadedModules) loadedModules = loadedModules->next;
					free(delMod->name);
					delete delMod;
					if (temp) temp = loadedModules;
					continue;
				}

				if (temp->skip) {
					if (skipped == NULL)
					{
						skipped = temp;
						temp = temp->next;
						skipped->next = NULL;
					} else {
						temp_skipped = temp;
						temp = temp->next;
						temp_skipped->next = skipped;
						skipped = temp_skipped;
					}

					continue;
				}

				_CL_VERBOSE << "Unhook module " << temp->name << "." LOG_

				if (FreeLibrary(temp->lib) == 0) {
					printf("ERROR: Library could not be unloaded!\n");
					temp = temp->next;
				} else {
					temp = temp->next;
					if (delMod == loadedModules) loadedModules = loadedModules->next;
					free(delMod->name);
					delete delMod;
				}
			}
		}

		// Restore list of skipped modules -> loadedModules

		loadedModules = skipped;
#endif

	loadedModules = NULL;

	// Not freed anywhere
	if (translated) {
		free(translated);
		translated = NULL;
	}

}
/*...e*/
/*...sclass lbKey \58\ public lb_I_KeyBase:0:*/
class DLLEXPORT lbKey : public lb_I_KeyBase {

public:
	DECLARE_LB_KEYBASE()

public:
#ifdef _MSC_VER
	lbKey(char* file, int line); // { key = 0; strcpy(keyType, "int"); }
#endif

	lbKey();
	lbKey(int _key);
	lbKey(const lb_I_KeyBase* k);
	virtual ~lbKey();

	DECLARE_LB_UNKNOWN()

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


lbErrCodes LB_CDECL lbKey::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}
/*...e*/

char const* LB_CDECL lbKey::getKeyType() const {
    return "int";
}

int LB_CDECL lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int LB_CDECL lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

int LB_CDECL lbKey::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKey*) _key)->key;
}

char* LB_CDECL lbKey::charrep() const {
    char buf[100];
    sprintf(buf, "%d", key);
    return strdup(buf);
}
/*...e*/
#ifndef OSX
/*...slbKey_:0:*/
/*...sc\39\tors and d\39\tors:0:*/
#ifdef _MSC_VER
lbKey_::lbKey_(char* file, int line) {
        key = 0;
        strcpy(keyType, "int");
}
#endif
lbKey_::lbKey_() {
    ref = STARTREF;
    key = 0;
	manager = NULL;
    strcpy(keyType, "int");
}

lbKey_::lbKey_(int _key) {
    ref = STARTREF;
    key = _key;
    strcpy(keyType, "int");
	manager = NULL;
}

lbKey_::lbKey_(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = ((lbKey_) k).key;
}

lbKey_::~lbKey_(){
}
/*...e*/

/*...simplement lb_I_Unknown:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbKey_)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_CDECL lbKey_::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}
/*...e*/

char const* LB_CDECL lbKey_::getKeyType() const {
    return "int";
}

int LB_CDECL lbKey_::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey_*) _key)->key;
}

int LB_CDECL lbKey_::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey_*) _key)->key;
}

int LB_CDECL lbKey_::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKey_*) _key)->key;
}

char* LB_CDECL lbKey_::charrep() const {
    char buf[100];
    sprintf(buf, "%d", key);
    return strdup(buf);
}
/*...e*/
#endif
/*...slbStringKey:0:*/
DLLEXPORT lbStringKey::lbStringKey() {
    ref = STARTREF;
    key = strdup("");
}

DLLEXPORT lbStringKey::lbStringKey(const char* _key) {
    ref = STARTREF;
    key = strdup(_key);
}

DLLEXPORT lbStringKey::lbStringKey(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = strdup(((lbStringKey*) k)->key);
}


DLLEXPORT lbStringKey::~lbStringKey(){
	if (key != NULL) {
		free(key);
	}
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbStringKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_CDECL lbStringKey::setData(lb_I_Unknown* uk) {

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

char const * LB_CDECL lbStringKey::getKeyType() const {
    return "string";
}

int LB_CDECL lbStringKey::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) == 0);
}

int LB_CDECL lbStringKey::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) > 0);
}

int LB_CDECL lbStringKey::lessthan(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) < 0);
}

char* LB_CDECL lbStringKey::charrep() const {
    return key;
}
/*...e*/


/*...sThread and Process based functions:0:*/
DWORD
#ifdef LINUX
DLLEXPORT
#endif
#ifdef WINDOWS
LB_DLLEXPORT
#endif
LB_CDECL lbGetCurrentThreadId() {
#ifdef WINDOWS
	return ::GetCurrentThreadId();
#endif
#ifdef LINUX
	// No real threads supported.
	return 0L; //::getpid();
#endif
}

DWORD
#ifdef LINUX
DLLEXPORT
#endif
#ifdef WINDOWS
LB_DLLEXPORT
#endif
LB_CDECL lbGetCurrentProcessId() {
#ifdef WINDOWS
	return ::GetCurrentProcessId();
#endif
#ifdef LINUX
	return getpid();
#endif
}
/*...e*/



#ifdef __WXGTK__
void delay(long mikrosek)
{
        struct timeval timeout;

        timeout.tv_sec = mikrosek / 1000000;
        timeout.tv_usec = mikrosek % 1000000;
        select (0, NULL, NULL, NULL, &timeout);
}
#endif


DLLEXPORT void LB_CDECL lb_sleep(int ms)
{
#ifdef WINDOWS
        ::Sleep(ms);
#endif
#ifdef __WXGTK__
        delay(ms * 1000);
#endif
}


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();

			if (isSetTRMemTrackBreak()) setTRMemTrackBreak(getTRMemTrackBreak(), 0);

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

			if (translated) free(translated);
			if (lbLogDirectory) free(lbLogDirectory);
			if (lbLogFile) free(lbLogFile);

			if (loadedModules) destroyModuleStructure(loadedModules);

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


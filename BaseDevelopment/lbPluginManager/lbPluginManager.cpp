/*...sLicence:0:*/
/*

	DMF Distributed Multiplatform Framework (the initial goal of this library)
	This file is part of lbDMF.
	Copyright (C) 2000-2007  Lothar Behrens (lothar.behrens@lollisoft.de)

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
/*...sRevision history:0:*/
/**************************************************************
* $Locker:  $
* $Revision: 1.91.2.1 $
* $Name:  $
* $Id: lbPluginManager.cpp,v 1.91.2.1 2013/10/26 04:39:11 lollisoft Exp $
*
* $Log: lbPluginManager.cpp,v $
* Revision 1.91.2.1  2013/10/26 04:39:11  lollisoft
* Fixes on Linux related to socket and transfer classes.
*
* Revision 1.91  2011/10/16 10:01:46  lollisoft
* Fixed a buffer overflow.
*
* Revision 1.90  2011/10/15 21:47:12  lollisoft
* Removed all code that is obsolete. Current code compiles but still does not run.
*
* Revision 1.89  2011/10/15 13:14:04  lollisoft
* Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
* Currently the code crashes on windows, but lets see how it is working on Mac.
*
* Revision 1.88  2011/10/15 06:36:12  lollisoft
* All current changes including interfaces (starting mass changes).
*
* Revision 1.87  2011/10/09 07:26:34  lollisoft
* Fixed possible memory leak.
*
* Revision 1.86  2011/10/03 04:43:07  lollisoft
* Fixes to try cope with rare application crash.
*
* Revision 1.85  2011/10/01 07:20:58  lollisoft
* Splitted up code  to define blocks per platform to resolve editor issues in correct code folding.
*
* Revision 1.84  2011/09/24 06:52:27  lollisoft
* Problem with RPM installation on a non development machine. Changed default plugin location for non Windows systems.
*
* Revision 1.83  2011/09/21 04:59:03  lollisoft
* Removed temporary log activation.
*
* Revision 1.82  2011/07/10 06:18:58  lollisoft
* Changed some logging messages to be verbose only.
*
* Revision 1.81  2011/06/18 17:29:55  lollisoft
* Changed all char* to const char* where a corresponding warning was generated.
*
* Revision 1.80  2011/05/07 10:36:24  lollisoft
* Some bugfixes regarding plugin initialization.
* Completely implemented an UML based code generation workflow using UML Activit’es.
*
* Revision 1.79  2011/02/27 10:30:36  lollisoft
* Changed all copyright entries addresses to match my current postal address.
*
* Revision 1.78  2011/02/19 18:57:13  lollisoft
* Adopted code to use server instance name for creating a namespace like protocol naming.
*
* Revision 1.77  2011/01/16 21:49:45  lollisoft
* Log to file instead to console for this case.
*
* Revision 1.76  2011/01/15 08:37:28  lollisoft
* Corrected server related plugin handling and added a function to return
* the server plugin module that may be responsible to startup a server
* instance at once.
*
* Revision 1.75  2010/05/29 07:48:40  lollisoft
* Compiles with mingw. Found a bug with not initialized variable.
*
* Revision 1.74  2010/01/22 22:14:54  lollisoft
* Fixed a null pointer bug.
*
* Revision 1.73  2010/01/14 17:31:25  lollisoft
* More changes for interceptor functionality, but crashes on Mac OS X (PPC).
*
* Revision 1.72  2009/12/07 11:33:08  lollisoft
* Restored lost code.
*
* Revision 1.71  2009/12/06 19:20:16  lollisoft
* Modified build process to use precompiled files.
* Corrected the long build time problem. It is located in the _LOG macro.
* Updated wxPropgrid to 1.4.9.1 and updated building against wxMSW 2.8.10.
*
* Build works, but running the application fails with not properly initialized error.
* (0xc0000005)
*
* Also updated the iss files for the new planned release.
*
* Revision 1.70  2009/11/27 15:57:02  lollisoft
* Missed return value.
*
* Revision 1.69  2009/11/24 21:30:47  lollisoft
* Lost initialisation of flag to only once create an unit test menu.
*
* Revision 1.68  2009/11/21 10:35:07  lollisoft
* Corrected unittest menu creation.
*
* Revision 1.67  2009/11/08 11:49:32  lollisoft
* Implemented 'unit test' like capabilities. The TestPlugin in the Plugins directory demonstrates the usage. Yet missing is a real test listener and stuff to display results. But it shows a working unit test mechanism using plugins.
*
* Corrected mkmk to find also include files in <> brackets.
*
* Corrected make system to work correctly with the new mkmk version. There may be a performance problem when compiling tvision code, thus that target is deactivated.
*
* Fixed some warnings.
*
* Revision 1.66  2009/09/09 07:53:19  lollisoft
* Fixed a memory leak.
*
* Revision 1.65  2009/07/19 22:37:14  lollisoft
* Implemented new 'install' functionality for each plugin module. The lb_I_PluginModule became a default implementation to do nothing.
*
* Revision 1.64  2009/06/04 12:27:50  lollisoft
* Added new functions into plugin manager and plugin module to support query of registered modules.
*
* Revision 1.63  2009/05/28 16:20:35  lollisoft
* Some more log messages and added search for libraries in bundle. This has to be reworked and the other changes for searching in bundles too to remove hardcoded executable name.
*
* Revision 1.62  2009/02/13 20:42:22  lollisoft
* Removed or verbosized some log messages.
*
* Revision 1.61  2009/02/01 09:32:10  lollisoft
* Missing making copy of version string in clone function.
*
* Revision 1.60  2009/01/31 10:37:09  lollisoft
* Bugfix: New version variable was not correctly initialized and not deleted at destruction.
*
* Revision 1.59  2009/01/31 09:58:03  lollisoft
* Added code for plugin versioning.
*
* Revision 1.58  2009/01/10 10:32:43  lollisoft
* Return NULL if there is no implementation.
*
* Revision 1.57  2008/07/26 07:37:33  lollisoft
* Log some usefull messages. This identified the plugin problem.
* Propably load failure interferes other plugins in the registry.
*
* Revision 1.56  2008/07/25 16:43:50  lollisoft
* Fixed application crash at exit.
*
* Revision 1.55  2007/11/16 20:53:19  lollisoft
* Initial DatabaseLayer based lb_I_Query and lb_I_Database classes. Rudimentary readonly queries are working.
*
* But also full cursor functionality emulation works.
*
* More than simple queries are not tested.
* (No order, where, join and subqueries)
*
* See DatabaseLayerWrapperTest.
*
* Revision 1.54  2007/06/18 22:54:50  lollisoft
* Partly rewrite of the database report classes works.
* There are still the issues to place the report to the
* correct location.
*
* Currently the sample text blocks are good.
*
* Revision 1.53  2007/04/22 20:39:38  lollisoft
* Minimal changes on Mac.
*
* Revision 1.52  2007/04/22 13:51:46  lollisoft
* Added code to scan for server plugins. Stuff is related to client/server
* redesign and is not yet tested.
*
* Revision 1.51  2007/01/29 20:12:59  lollisoft
* Checkin for Linux.
*
* Revision 1.50  2006/10/23 21:20:48  lollisoft
* Small changes to compile under Linux again
*
* Revision 1.49  2006/10/22 18:34:36  lollisoft
* Many memory leaks resolved, but they were caused by small errors :-(
* This is also a sync.
*
* Revision 1.48  2006/07/22 19:27:02  lollisoft
* Removed logging messages.
*
* Revision 1.47  2006/07/17 17:37:45  lollisoft
* Changes dueto bugfix in plugin manager. Repeadable iterator problem.
* Not correctly finished the iteration, thus plugins in the same DLL wouldn't
* be found any more after first query.
*
* Code works well with improved trmem library, but there is still a crash in
* database classes (pgODBC library).
*
* Revision 1.46  2006/06/24 06:19:54  lollisoft
* Commit due to travel to Duesseldorf.
*
* Revision 1.45  2006/06/03 06:16:57  lollisoft
* Changes against new Datamodel classes.
* These are used instead spread SQL commands.
*
* Currently, the SQL commands are for fallback issues,
* if there is no data in the config files.
*
* Later the planned fallback SQL commands are replaced by
* a controlled visitor operation.
*
* Work is in process.
*
* Revision 1.44  2006/03/19 23:35:42  lollisoft
* Removed some log messages and reformatted some code.
*
* Revision 1.43  2006/03/06 11:45:46  lollisoft
* Corrected search criteria creation time point
*
* Revision 1.42  2006/03/05 08:00:49  lollisoft
* Added check for /usr/plugins as plugindir.
*
* Revision 1.41  2006/02/27 11:22:16  lollisoft
* Corrected plugin path settings. On Windows, environment PLUGIN_DIR
* overwrites home/plugins.
*
* Revision 1.40  2006/02/26 23:46:19  lollisoft
* Changed build method for shared libraries under Mac OS X
* to be frameworks. These would be embedable into the
* application bundle - thus enables better install method.
*
* Revision 1.39  2006/02/24 14:22:53  lollisoft
* Second fallback to $PWD/plugins
*
* Revision 1.38  2006/02/21 19:35:51  lollisoft
* Implemented autoload mechanism of last loaded application.
* It demonstrates the new capabilities operating with files.
*
* Revision 1.37  2006/01/30 15:54:15  lollisoft
* Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
* This was an unnessesary thing and makes programming easier.
*
* Revision 1.36  2005/12/11 19:15:16  lollisoft
* Release changes for 0.6.0. Added todo entries.
*
* Revision 1.35  2005/12/02 17:38:11  lollisoft
* Lesser log messages. Put them to be verbose only.
*
* Revision 1.34  2005/11/18 23:41:31  lollisoft
* More memory leaks have been fixed. There are currently less than 200
* chunks unfreed, wich may be located in the plugin mechanism.
*
* Revision 1.33  2005/11/16 13:07:39  lollisoft
* Added Memtrack breakpoint counter.
*
* Revision 1.32  2005/11/11 22:47:35  lollisoft
* Memory leaks removed. There was a hack with singletons, but the current
* variant without singletons is tested well.
*
* Revision 1.31  2005/11/10 08:49:55  lollisoft
* Small memory leak, but it only happens, if the plugin directory is not present.
*
* Revision 1.30  2005/11/02 16:24:28  lollisoft
* Bug for the program ending crash and the cout crash found. See history in
* lbDB.cpp.
*
* Revision 1.29  2005/10/31 21:55:16  lollisoft
* Deactivated too early include of lbInterface.h.
*
* Revision 1.28  2005/10/31 15:05:12  lollisoft
* Added an unload function for correct cleanup. Only delete char* if not NULL.
* Corrected malloc include.
*
* Revision 1.27  2005/10/31 09:59:01  lollisoft
* Added support for mpatrol library, but it is deactivated. Use DEBUG_MEMORY=yes to activate it.
*
* Revision 1.26  2005/10/01 21:44:08  lollisoft
* Added handling of namespaces.
*
* Revision 1.25  2005/08/21 23:09:36  lollisoft
* Bugfix: Plugins, that are not found will stay open.
* For this a releaseImplementation has been added.
*
* Revision 1.24  2005/06/27 10:32:09  lollisoft
* Mostly changes to conio.h conflicts while XCode build
*
* Revision 1.23  2005/06/24 23:09:49  lollisoft
* Changes to build with new wxWidgets version 2.6.1.
* Added fallback to hardcoded settings, if no environment
* variables are found. Logging changed to reside in a
* $(HOME)/log directory.
*
* GUI application build process enhanced to also make the
* bundle. App runs from clicking on the desktop icon.
*
* Revision 1.22  2005/05/11 13:19:40  lollisoft
* Bugfix for reference count error and changed back any _CL_LOG messages to be _CL_VERBOSE only
*
* Revision 1.21  2005/05/04 22:09:39  lollisoft
* Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
*
* Revision 1.20  2005/05/03 21:16:51  lollisoft
* Better memtrack support
*
* Revision 1.19  2005/05/01 21:27:39  lollisoft
* Added informative filename to show when printing memory leaks.
*
* Thanks to the trmem code from Open Watcom.
*
* Revision 1.18  2005/05/01 01:12:36  lollisoft
* Found a really big memory leak. It happens due to missing setup of ref variable
* in lbFunctorEntity class of lbModule.cpp.
*
* Due to the fact, that I use this class for each instance retrival, it wasted
* much memory. More: See documentation in that class.
*
* Revision 1.17  2005/04/27 12:44:42  lollisoft
* Ignoring *.so.* files and .
*
* Revision 1.16  2005/04/03 22:08:10  lollisoft
* Removed much logging messages.
*
* Revision 1.15  2005/04/02 12:49:06  lollisoft
* Bugfix, if PLUGIN_DIR is not configured
*
* Revision 1.14  2005/03/31 09:00:55  lollisoft
* Copyright text problems under linux.
*
* Revision 1.13  2005/03/15 22:26:40  lollisoft
* More changes on OSX to compile plugins
*
* Revision 1.12  2005/03/15 14:43:52  lollisoft
* Changes for linux to build and let GUI running with plugins
*
* Revision 1.11  2005/03/14 18:59:02  lollisoft
* Various changes and additions to make plugins also work with database forms
*
* Revision 1.10  2005/03/10 16:48:27  lollisoft
* Fully implemented plugin functionality
*
* Revision 1.9  2005/03/10 09:01:19  lollisoft
* Plugin code complete until real loading.
*
* Revision 1.8  2005/03/05 23:13:33  lollisoft
* More changes to build source tree under Mac OS X
*
* Revision 1.7  2005/03/03 08:38:00  lollisoft
* Removed multiple code. Reporting failure or success of plugin loading.
*
* Revision 1.5  2004/06/16 22:12:31  lollisoft
* More code for plugin management
*
* Revision 1.4  2004/06/09 06:59:59  lollisoft
* Loading plugin module and insertin to internal PluginModules list implemented
*
* Revision 1.3  2004/06/07 20:26:30  lollisoft
* Initial plugin manager implementation
*
* Revision 1.2  2004/06/06 12:53:29  lollisoft
* Include file lower case
*
* Revision 1.1  2004/06/06 12:31:21  lollisoft
* Initial
*
**************************************************************/

/*...e*/

/*...sincludes:0:*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#ifdef __WATCOMC__

#include <dos.h>
#define dd_findfirst(x,y,z) _dos_findfirst(x,y,z)
#define dd_findnext _dos_findnext
#define dd_ffblk find_t
#define dd_name name

#endif

#ifdef LINUX
#include <sys/types.h>
#include <dirent.h>
#endif

#include <stdio.h>
#ifndef OSX
#ifndef USE_MPATROL
#ifndef MEMTRACK
#include <malloc.h>
#endif
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <iostream>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

#include <lbPluginManager.h>
/*...e*/

/*...sclass lbPluginManager:0:*/
/// \brief Plugin manager implementation.
class lbPluginManager :
public lb_I_PluginManager,
public lb_I_EventHandler
{
public:

	lbPluginManager();
	virtual ~lbPluginManager();

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	lb_I_Unknown* LB_STDCALL getUnknown();


	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL runInstallers();
	void LB_STDCALL unload();
	bool LB_STDCALL beginEnumPlugins();
	bool LB_STDCALL beginEnumServerPlugins();

	lb_I_Plugin* LB_STDCALL getFirstMatchingPlugin(const char* match, const char* _namespace, const char* _version);
	lb_I_Plugin* LB_STDCALL nextPlugin();

	lb_I_ApplicationServerModul* LB_STDCALL nextServerPluginModul();
	lb_I_Plugin* LB_STDCALL getFirstMatchingServerPlugin(const char* match, const char* _namespace);
	lb_I_Plugin* LB_STDCALL nextServerPlugin();

	bool LB_STDCALL attach(lb_I_PluginModule* toAttach);
	bool LB_STDCALL detach(lb_I_PluginModule* toAttach);

	lb_I_String* LB_STDCALL getPluginDirectory();

	bool LB_STDCALL isRegistered(const char* name);

private:


	bool LB_STDCALL tryLoad(const char* module, const char* path);
	bool LB_STDCALL tryLoadServerModule(const char* module, const char* path);

	bool LB_STDCALL tryLoadUnitTestModule(const char* module, const char* path);
	lbErrCodes LB_STDCALL runUnitTests(lb_I_Unknown* uk);
	bool LB_STDCALL beginEnumUnitTestPlugins();
	lb_I_Plugin* LB_STDCALL nextUnitTestPlugin();


	bool isInitialized;
	bool begunEnumerate;
	bool firstEnumerate;

	bool isServerInitialized;
	bool begunServerEnumerate;
	bool firstServerEnumerate;

	bool isUnitTestInitialized;
	bool begunUnitTestEnumerate;
	bool firstUnitTestEnumerate;

	UAP(lb_I_Container, PluginModules)
	UAP(lb_I_Container, PluginContainer)

	UAP(lb_I_Container, PluginServerModules)
	UAP(lb_I_Container, PluginServerContainer)

	UAP(lb_I_Container, PluginUnitTestModules)
	UAP(lb_I_Container, PluginUnitTestContainer)

	UAP(lb_I_String, MyPluginDir)

	bool firstPlugin;
	bool lastPlugin;
	bool firstServerPlugin;
	bool lastServerPlugin;
	bool firstUnitTestPlugin;
	bool lastUnitTestPlugin;
};
/*...e*/
/*...simplementation of class lbPluginManager:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbPluginManager)
ADD_INTERFACE(lb_I_PluginManager)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginManager, lbPluginManager)

lb_I_Unknown* LB_STDCALL lbPluginManager::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}


lbPluginManager::lbPluginManager() {
	
	begunEnumerate = firstEnumerate = begunUnitTestEnumerate = false;
	begunServerEnumerate = firstServerEnumerate = firstUnitTestEnumerate = false;
	firstUnitTestPlugin = false;
	firstPlugin = true;
	firstServerPlugin = true;
	lastPlugin = false;
	lastServerPlugin = false;
	lastUnitTestPlugin = false;
	isInitialized = false;
	isUnitTestInitialized = false;
	isServerInitialized = false;
	REQUEST(getModuleInstance(), lb_I_String, MyPluginDir)
	_CL_VERBOSE << "lbPluginManager::lbPluginManager() called." LOG_
}

lbPluginManager::~lbPluginManager() {
	_CL_VERBOSE << "lbPluginManager::~lbPluginManager() called." LOG_
}

lb_I_String* LB_STDCALL lbPluginManager::getPluginDirectory() {
	MyPluginDir++;
	return MyPluginDir.getPtr();
}

bool LB_STDCALL lbPluginManager::isRegistered(const char* name) {
	lbErrCodes err = ERR_NONE;
	PluginModules->finishIteration();
	while (PluginModules->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_PluginModule, plM)

		uk = PluginModules->nextElement();

		QI(uk, lb_I_PluginModule, plM)

		if (plM != NULL) {
			UAP(lb_I_String, compare)
			compare = plM->getModule();

			if (*compare == name) {
				PluginModules->finishIteration();
				return true;
			}
		}
	}

	return false;
}

/*...svoid LB_STDCALL lbPluginManager\58\\58\unload\40\\41\:0:*/
void LB_STDCALL lbPluginManager::unload() {

	if (PluginModules == NULL) _CL_LOG << "Warning: PluginModules is NULL." LOG_

	if (PluginModules != NULL) {
		if (PluginModules->getRefCount() > 1) {
			_CL_LOG << "Warning: lbPluginManager::unload() doesn't affect unloading PluginModules!" LOG_
		}
		PluginModules--;
		PluginModules.resetPtr();
	}

	if (PluginContainer != NULL) {
		PluginContainer--;
		PluginContainer.resetPtr();
	}


	if (PluginServerModules == NULL) _CL_LOG << "Warning: PluginServerModules is NULL." LOG_

	if (PluginServerModules != NULL) {
		if (PluginServerModules->getRefCount() > 1) {
			_CL_LOG << "Warning: lbPluginManager::unload() doesn't affect unloading PluginServerModules!" LOG_
		}
		PluginServerModules--;
		PluginServerModules.resetPtr();
	}

	if (PluginServerContainer != NULL) {
		PluginServerContainer--;
		PluginServerContainer.resetPtr();
	}

	if (PluginUnitTestModules == NULL) _CL_LOG << "Warning: PluginUnitTestModules is NULL." LOG_

	if (PluginUnitTestModules != NULL) {
		if (PluginUnitTestModules->getRefCount() > 1) {
			_CL_LOG << "Warning: lbPluginManager::unload() doesn't affect unloading PluginUnitTestModules!" LOG_
		}
		PluginUnitTestModules--;
		PluginUnitTestModules.resetPtr();
	}

	if (PluginUnitTestContainer != NULL) {
		PluginUnitTestContainer--;
		PluginUnitTestContainer.resetPtr();
	}

	isInitialized = false;
}
/*...e*/

lbErrCodes LB_STDCALL lbPluginManager::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbPluginManager::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

/*...sbool LB_STDCALL lbPluginManager\58\\58\tryLoad\40\char\42\ module\41\:0:*/
bool LB_STDCALL lbPluginManager::tryLoad(const char* module, const char* path) {
	lbErrCodes err = ERR_NONE;

	if (strcmp(".", module) == 0) return false;
	if (strstr(module, "so.") != NULL) return false;

	_LOG << "Try to load module '" << module << "'" LOG_

	char* pluginDir = NULL;

	pluginDir = (char*) malloc(strlen(path)+1);

	pluginDir[0] = 0;
	strcat(pluginDir, path);

	/*...sbuild PREFIX:0:*/
#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
	/*...e*/

	// Instantiate an lb_I_PluginModule object

	char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2);
	pluginModule[0] = 0;
	strcat(pluginModule, pluginDir);
#ifdef WINDOWS
	strcat(pluginModule, "\\");
#endif
#ifdef LINUX
#ifndef OSX
	strcat(pluginModule, "/");
#endif
#endif
#ifdef OSX
	strcat(pluginModule, "/");
#endif
	strcat(pluginModule, module);

	UAP(lb_I_Unknown, ukPlugin)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pluginName)
	pluginName->setData(module);

	UAP(lb_I_KeyBase, key)
	QI(pluginName, lb_I_KeyBase, key)

	/*...sTry to load a plugin module:8:*/
	if (PluginModules->exists(&key) != 0) {
		_LOG << "Warning: Plugin already registered. (" << pluginName->charrep() << ")" LOG_
		free(pluginModule);
		free(pluginDir);
	} else {
		if (getModuleInstance()->makeInstance(PREFIX "instanceOfPluginModule", pluginModule, &ukPlugin) != ERR_NONE) {

			// It may be a Microsoft compiled plugin...
			if (getModuleInstance()->makeInstance("instanceOfPluginModule", pluginModule, &ukPlugin) == ERR_NONE) {

				

				PluginModules->insert(&ukPlugin, &key);

				UAP(lb_I_Unknown, ukPlugin1)

				ukPlugin1 = PluginModules->getElement(&key);

				UAP(lb_I_PluginModule, plM)
				QI(ukPlugin1, lb_I_PluginModule, plM)

				plM->setModule(pluginModule);
				plM->initialize();
				_LOG << "Info: Plugin registered. (" << pluginName->charrep() << ")" LOG_

				free(pluginModule);
				free(pluginDir);
				return true;
			}
			free(pluginModule);
			free(pluginDir);

			return false;

		} else {
			
			PluginModules->insert(&ukPlugin, &key);

			UAP(lb_I_Unknown, ukPlugin1)

			ukPlugin1 = PluginModules->getElement(&key);

			UAP(lb_I_PluginModule, plM)
			QI(ukPlugin1, lb_I_PluginModule, plM)

			plM->setModule(pluginModule);
			plM->initialize();
			_LOG << "Info: Plugin registered. (" << pluginName->charrep() << ")" LOG_

			free(pluginModule);
			free(pluginDir);
		}
	}
	/*...e*/

	return true;
}
/*...e*/
/*...sbool LB_STDCALL lbPluginManager\58\\58\tryLoadServerModule\40\char\42\ module\41\:0:*/
bool LB_STDCALL lbPluginManager::tryLoadServerModule(const char* module, const char* path) {
	lbErrCodes err = ERR_NONE;

	if (strcmp(".", module) == 0) return false;
	if (strstr(module, "so.") != NULL) return false;

	_CL_LOG << "Try to load server module '" << module << "'" LOG_

	char* pluginDir = NULL;

	pluginDir = (char*) malloc(strlen(path)+1);

	pluginDir[0] = 0;
	strcat(pluginDir, path);

	/*...sbuild PREFIX:0:*/
#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
	/*...e*/

	// Instantiate an lb_I_PluginModule object

	char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2);
	pluginModule[0] = 0;
	strcat(pluginModule, pluginDir);
#ifdef WINDOWS
	strcat(pluginModule, "\\");
#endif
#ifdef LINUX
#ifndef OSX
	strcat(pluginModule, "/");
#endif
#endif
#ifdef OSX
	strcat(pluginModule, "/");
#endif
	strcat(pluginModule, module);

	UAP(lb_I_Unknown, ukPlugin)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pluginName)
	pluginName->setData(module);

	UAP(lb_I_KeyBase, key)
	QI(pluginName, lb_I_KeyBase, key)

	/*...sTry to load a plugin module:8:*/
	if (PluginServerModules->exists(&key) != 0) {
		_CL_LOG << "Warning: Server plugin already registered." LOG_
		free(pluginModule);
		free(pluginDir);
	} else {
		if (getModuleInstance()->makeInstance(PREFIX "instanceOfPluginServerModule", pluginModule, &ukPlugin) != ERR_NONE) {

			// It may be a Microsoft compiled plugin...
			if (getModuleInstance()->makeInstance("instanceOfPluginServerModule", pluginModule, &ukPlugin) == ERR_NONE) {
				UAP(lb_I_Unknown, ukPlugin1)
				UAP(lb_I_ApplicationServerModul, plM)
				UAP(lb_I_ApplicationServerModul, plMTest)

				

				QI(ukPlugin, lb_I_ApplicationServerModul, plMTest)

				if (plMTest != NULL) {
					PluginServerModules->insert(&ukPlugin, &key);
					ukPlugin1 = PluginServerModules->getElement(&key);
					QI(ukPlugin, lb_I_ApplicationServerModul, plM)
					plM->setModule(pluginModule);
					plM->initialize();
				}

				free(pluginModule);
				free(pluginDir);
				return true;
			}
			free(pluginModule);
			free(pluginDir);

			return false;

		} else {
			UAP(lb_I_Unknown, ukPlugin1)
			UAP(lb_I_ApplicationServerModul, plM)
			UAP(lb_I_ApplicationServerModul, plMTest)

			

			QI(ukPlugin, lb_I_ApplicationServerModul, plMTest)

			if (plMTest != NULL) {
				PluginServerModules->insert(&ukPlugin, &key);
				ukPlugin1 = PluginServerModules->getElement(&key);
				QI(ukPlugin1, lb_I_ApplicationServerModul, plM)
				plM->setModule(pluginModule);
				plM->initialize();
			}
			
			free(pluginModule);
			free(pluginDir);
		}
	}
	/*...e*/

	return true;
}
/*...e*/

/*...sbool LB_STDCALL lbPluginManager\58\\58\tryLoadUnitTestModule\40\char\42\ module\41\:0:*/
bool LB_STDCALL lbPluginManager::tryLoadUnitTestModule(const char* module, const char* path) {
	lbErrCodes err = ERR_NONE;

	if (strcmp(".", module) == 0) return false;
	if (strstr(module, "so.") != NULL) return false;

	_CL_VERBOSE << "Try to load unit test module '" << module << "'" LOG_

	char* pluginDir = NULL;

	pluginDir = (char*) malloc(strlen(path)+1);

	pluginDir[0] = 0;
	strcat(pluginDir, path);

	/*...sbuild PREFIX:0:*/
#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
	/*...e*/

	// Instantiate an lb_I_PluginModule object

	char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2);
	pluginModule[0] = 0;
	strcat(pluginModule, pluginDir);
#ifdef WINDOWS
	strcat(pluginModule, "\\");
#endif
#ifdef LINUX
#ifndef OSX
	strcat(pluginModule, "/");
#endif
#endif
#ifdef OSX
	strcat(pluginModule, "/");
#endif
	strcat(pluginModule, module);

	UAP(lb_I_Unknown, ukPlugin)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pluginName)
	pluginName->setData(module);

	UAP(lb_I_KeyBase, key)
	QI(pluginName, lb_I_KeyBase, key)

	/*...sTry to load a plugin module:8:*/
	if (PluginUnitTestModules->exists(&key) != 0) {
		_CL_LOG << "Warning: Server plugin already registered." LOG_
		free(pluginModule);
		free(pluginDir);
	} else {
		if (getModuleInstance()->makeInstance(PREFIX "instanceOfPluginUnitTestModule", pluginModule, &ukPlugin) != ERR_NONE) {

			// It may be a Microsoft compiled plugin...
			if (getModuleInstance()->makeInstance("instanceOfPluginUnitTestModule", pluginModule, &ukPlugin) == ERR_NONE) {

				

				PluginUnitTestModules->insert(&ukPlugin, &key);

				UAP(lb_I_Unknown, ukPlugin1)

				ukPlugin1 = PluginUnitTestModules->getElement(&key);

				UAP(lb_I_UnitTestModul , plM)
				QI(ukPlugin1, lb_I_UnitTestModul, plM)

				plM->setModule(pluginModule);
				plM->initialize();

				free(pluginModule);
				free(pluginDir);
				return true;
			}
			free(pluginModule);
			free(pluginDir);

			return false;

		} else {
			
			PluginUnitTestModules->insert(&ukPlugin, &key);

			UAP(lb_I_Unknown, ukPlugin1)

			ukPlugin1 = PluginUnitTestModules->getElement(&key);

			UAP(lb_I_UnitTestModul, plM)
			QI(ukPlugin1, lb_I_UnitTestModul, plM)

			_CL_VERBOSE << "lb_I_PluginModule has " << plM->getRefCount() << " references." LOG_

			plM->setModule(pluginModule);
			plM->initialize();

			free(pluginModule);
			free(pluginDir);
		}
	}
	/*...e*/

	return true;
}
/*...e*/

/*...svoid LB_STDCALL lbPluginManager\58\\58\initialize\40\\41\:0:*/
#ifdef WINDOWS
void LB_STDCALL lbPluginManager::initialize() {
	lbErrCodes err = ERR_NONE;
	isInitialized = true;
	isServerInitialized = true;
	// Why I have done this? It's rubbish.

	if (!firstEnumerate) {
		firstEnumerate = true;

		if (PluginModules != NULL) {
			PluginModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginModules)
	}

	if (!firstServerEnumerate) {
		firstServerEnumerate = true;

		if (PluginServerModules != NULL) {
			PluginServerModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginServerModules)
	}

	if (!firstUnitTestEnumerate) {
		firstUnitTestEnumerate = true;

		if (PluginUnitTestModules != NULL) {
			PluginUnitTestModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginUnitTestModules)
	}

	_finddata_t find;
	char* mask = "*.dll";

	char* pluginDir = getenv("PLUGIN_DIR");
	///\todo Change the plugin path to user share lbdmf plugins.
	if (pluginDir == NULL) {
		_LOGERROR << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
		pluginDir = (char*) malloc(strlen(getenv("USERPROFILE"))+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, getenv("USERPROFILE"));

		strcat(pluginDir, "/plugins");
	} else {
		char* temp = pluginDir;
		pluginDir = (char*) malloc(strlen(pluginDir)+1);
		pluginDir[0] = 0;
		strcpy(pluginDir, temp);
	}

	char* toFind = (char*) malloc(strlen(mask)+strlen(pluginDir)+2);
	toFind[0] = 0;

	strcat(toFind, pluginDir);
	strcat(toFind, "\\");
	strcat(toFind, mask);
	long handle = _findfirst(toFind, &find);

#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif

	if (handle != -1) {
		tryLoad(find.name, pluginDir);
		tryLoadServerModule(find.name, pluginDir);
		tryLoadUnitTestModule(find.name, pluginDir);

		while (_findnext(handle, &find) == 0) {
			tryLoad(find.name, pluginDir);
			tryLoadServerModule(find.name, pluginDir);
			tryLoadUnitTestModule(find.name, pluginDir);
		}
		_findclose(handle);
	} else {
		printf("No plugins found.\n");
	}

	free(pluginDir);
	free(toFind);
	if (!isUnitTestInitialized && PluginUnitTestModules->Count() > 0) {
		_LOG << "Have found unit tests in some plugin modules. Activate menu for starting the tests." LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		int runUnitTests = 0;

		eman->registerEvent("runUnitTests", runUnitTests);
		registerEventHandler(*&dispatcher);


		//meta->addMenuBar(_trans("&Unittests"));
		meta->addMenuEntry(_trans("&Unittests"), "run Unit Tests", "runUnitTests", "");
	}

	isUnitTestInitialized = true;
}
#endif

#ifdef LINUX
#ifndef OSX
void LB_STDCALL lbPluginManager::initialize() {
	lbErrCodes err = ERR_NONE;
	isInitialized = true;
	isServerInitialized = true;
	// Why I have done this? It's rubbish.

	if (!firstEnumerate) {
		firstEnumerate = true;

		if (PluginModules != NULL) {
			PluginModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginModules)
	}

	if (!firstServerEnumerate) {
		firstServerEnumerate = true;

		if (PluginServerModules != NULL) {
			PluginServerModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginServerModules)
	}

	if (!firstUnitTestEnumerate) {
		firstUnitTestEnumerate = true;

		if (PluginUnitTestModules != NULL) {
			PluginUnitTestModules--;
		}
		REQUEST(getModuleInstance(), lb_I_Container, PluginUnitTestModules)
	}

	const char* mask = "*.so";

	/*...sPrepare plugin directory to scan:0:*/
	char* pluginDir = getenv("PLUGIN_DIR");
	///\todo Change the plugin path to user share lbdmf plugins.
	if (pluginDir == NULL) {
		_LOGERROR << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
		pluginDir = (char*) malloc(strlen("/usr")+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, "/usr");
		strcat(pluginDir, "/plugins");
	} else {
		char* temp = pluginDir;
		pluginDir = (char*) malloc(strlen(pluginDir)+1);
		pluginDir[0] = 0;
		strcpy(pluginDir, temp);
	}

	DIR *dir;
	struct dirent *dir_info;

	/*...sfor direntry:8:*/
	_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
	if ((dir = opendir(pluginDir)) == NULL) {

		free(pluginDir);

		const char* pwd = getenv("PWD");
		if (pwd == NULL) pwd = ".";

		pluginDir = (char*) malloc(strlen(pwd)+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, pwd);
		strcat(pluginDir, "/plugins");

		_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
		if ((dir = opendir(pluginDir)) == NULL) {

			/// \todo Change to a better plugin directory.
			const char* pl = "/usr";
			free(pluginDir);
			pluginDir = (char*) malloc(strlen(pl)+strlen("/plugins")+1);
			pluginDir[0] = 0;
			strcat(pluginDir, pl);
			strcat(pluginDir, "/plugins");

			_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
			if ((dir = opendir(pluginDir)) == NULL) {

				free(pluginDir);

				const char* pwd = getenv("PWD");
				if (pwd == NULL) pwd = ".";
				///\todo Rework this.
				pluginDir = (char*) malloc(strlen(pwd)+strlen("/wxWrapper.app/Contents/Resources")+strlen("/plugins")+1);
				pluginDir[0] = 0;
				strcat(pluginDir, pwd);
				strcat(pluginDir, "/wxWrapper.app/Contents/Resources/plugins");

				_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
				if ((dir = opendir(pluginDir)) == NULL) {
					_LOG << "Plugin directory not found." LOG_

					free(pluginDir);
					pluginDir = NULL;
					return;
				}
			}
		}
	}
	_LOG << "Plugin directory is at '" << pluginDir << "'." LOG_
	*MyPluginDir = pluginDir;

	char* toFind = (char*) malloc(strlen(mask)+strlen(pluginDir)+2);
	toFind[0] = 0;

	strcat(toFind, pluginDir);
	strcat(toFind, "/");
	strcat(toFind, mask);

	dir_info = readdir(dir);

#define PREFIX ""

	if (dir_info != NULL) {
		tryLoad(dir_info->d_name, pluginDir);
		tryLoadServerModule(dir_info->d_name, pluginDir);
		tryLoadUnitTestModule(dir_info->d_name, pluginDir);

		while ((dir_info = readdir(dir)) != NULL) {
			if (strstr(dir_info->d_name, ".so") != NULL) {
				tryLoad(dir_info->d_name, pluginDir);
				tryLoadServerModule(dir_info->d_name, pluginDir);
				tryLoadUnitTestModule(dir_info->d_name, pluginDir);
			}
		}
	} else {
		printf("No plugins found.\n");
	}

	free(pluginDir);
	free(toFind);
	if (!isUnitTestInitialized && PluginUnitTestModules->Count() > 0) {
		_LOG << "Have found unit tests in some plugin modules. Activate menu for starting the tests." LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		int runUnitTests = 0;

		eman->registerEvent("runUnitTests", runUnitTests);
		registerEventHandler(*&dispatcher);


		//meta->addMenuBar(_trans("&Unittests"));
		meta->addMenuEntry(_trans("&Unittests"), "run Unit Tests", "runUnitTests", "");
	}

	isUnitTestInitialized = true;
}
#endif
#endif

#ifdef OSX
void LB_STDCALL lbPluginManager::initialize() {
	lbErrCodes err = ERR_NONE;
	isInitialized = true;
	isServerInitialized = true;
	// Why I have done this? It's rubbish.

	if (!firstEnumerate) {
		firstEnumerate = true;

		if (PluginModules != NULL) {
			PluginModules--;
		}
	}

	if (!firstServerEnumerate) {
		firstServerEnumerate = true;

		if (PluginServerModules != NULL) {
			PluginServerModules--;
		}
	}

	if (!firstUnitTestEnumerate) {
		firstUnitTestEnumerate = true;

		if (PluginUnitTestModules != NULL) {
			PluginUnitTestModules--;
		}
	}

	if (PluginModules == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, PluginModules)
	}

	if (PluginServerModules == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, PluginServerModules)
	}
	if (PluginUnitTestModules == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, PluginUnitTestModules)
	}

	const char* mask = "*.so";

	/*...sPrepare plugin directory to scan:0:*/
	char* pluginDir = getenv("PLUGIN_DIR");
	///\todo Change the plugin path to user share lbdmf plugins.
	if (pluginDir == NULL) {
		_LOGERROR << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
		pluginDir = (char*) malloc(strlen("/usr")+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, "/usr");
		strcat(pluginDir, "/plugins");
	} else {
		char* temp = pluginDir;
		pluginDir = (char*) malloc(strlen(pluginDir)+1);
		pluginDir[0] = 0;
		strcpy(pluginDir, temp);
	}

	DIR *dir;
	struct dirent *dir_info;

	/*...sfor direntry:8:*/
	_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
	if ((dir = opendir(pluginDir)) == NULL) {

		free(pluginDir);

		const char* pwd = getenv("PWD");
		if (pwd == NULL) pwd = ".";

		pluginDir = (char*) malloc(strlen(pwd)+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, pwd);
		strcat(pluginDir, "/plugins");

		_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
		if ((dir = opendir(pluginDir)) == NULL) {

			/// \todo Change to a better plugin directory.
			const char* pl = "/usr";
			free(pluginDir);
			pluginDir = (char*) malloc(strlen(pl)+strlen("/plugins")+1);
			pluginDir[0] = 0;
			strcat(pluginDir, pl);
			strcat(pluginDir, "/plugins");

			_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
			if ((dir = opendir(pluginDir)) == NULL) {

				free(pluginDir);

				const char* pwd = getenv("PWD");
				if (pwd == NULL) pwd = ".";
				///\todo Rework this.
				pluginDir = (char*) malloc(strlen(pwd)+strlen("/wxWrapper.app/Contents/Resources")+strlen("/plugins")+1);
				pluginDir[0] = 0;
				strcat(pluginDir, pwd);
				strcat(pluginDir, "/wxWrapper.app/Contents/Resources/plugins");

				_LOG << "Check for plugin directory at '" << pluginDir << "'." LOG_
				if ((dir = opendir(pluginDir)) == NULL) {
					_LOG << "Plugin directory not found." LOG_

					free(pluginDir);
					pluginDir = NULL;
					return;
				}
			}
		}
	}
	_LOG << "Plugin directory is at '" << pluginDir << "'." LOG_
	*MyPluginDir = pluginDir;

	char* toFind = (char*) malloc(strlen(mask)+strlen(pluginDir)+2);
	toFind[0] = 0;

	strcat(toFind, pluginDir);
	strcat(toFind, "/");
	strcat(toFind, mask);

	dir_info = readdir(dir);

#define PREFIX ""

	if (dir_info != NULL) {
		tryLoad(dir_info->d_name, pluginDir);
		tryLoadServerModule(dir_info->d_name, pluginDir);
		tryLoadUnitTestModule(dir_info->d_name, pluginDir);

		while ((dir_info = readdir(dir)) != NULL) {
			if (strstr(dir_info->d_name, ".so") != NULL) {
				tryLoad(dir_info->d_name, pluginDir);
				tryLoadServerModule(dir_info->d_name, pluginDir);
				tryLoadUnitTestModule(dir_info->d_name, pluginDir);
			}
		}
	} else {
		printf("No plugins found.\n");
	}

	free(pluginDir);
	free(toFind);
	if (!isUnitTestInitialized && PluginUnitTestModules->Count() > 0) {
		_LOG << "Have found unit tests in some plugin modules. Activate menu for starting the tests." LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		int runUnitTests = 0;

		eman->registerEvent("runUnitTests", runUnitTests);
		registerEventHandler(*&dispatcher);


		//meta->addMenuBar(_trans("&Unittests"));
		meta->addMenuEntry(_trans("&Unittests"), "run Unit Tests", "runUnitTests", "");
	}

	isUnitTestInitialized = true;
}
#endif
/*...e*/

lbErrCodes lbPluginManager::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &lbPluginManager::runUnitTests, "runUnitTests");
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbPluginManager::runUnitTests(lb_I_Unknown* uk) {
	_LOG << "Unittests starting." LOG_

	if (beginEnumUnitTestPlugins()) {
		while (true) {
			UAP(lb_I_Plugin, pl)
			pl = nextUnitTestPlugin();
			if (pl == NULL) break;

			UAP(lb_I_Unknown, uk)

			if (pl->hasInterface("lb_I_TestFixture")) {
				lbErrCodes err = ERR_NONE;
				UAP(lb_I_TestFixture, fixture)
				uk = pl->getImplementation();
				QI(uk, lb_I_TestFixture, fixture)

				fixture->registerTests();
				fixture->setUp();

				fixture->runTest();

				fixture->tearDown();
			}
		}
	}
	_LOG << "Unittests ready." LOG_
	return ERR_NONE;
}

/** \todo Need to think about the copy iterator problem.
* The need for a copy iterator or saving the current iteration if a new one
* should start, should be thought about, since without that an endless loop
* may occur.
*/
void LB_STDCALL lbPluginManager::runInstallers() {
	lbErrCodes err = ERR_NONE;
	if (!isInitialized) initialize();

	UAP_REQUEST(getModuleInstance(), lb_I_Container, copy)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, pos)
	UAP(lb_I_KeyBase, key)
	QI(pos, lb_I_KeyBase, key)

	int i = 0;

	copy->setCloning(false);

	// Copy the list to avoid an endless loop if any plugin wants to load another plugin
	PluginModules->finishIteration();
	while (PluginModules->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_PluginModule, plM)

		uk = PluginModules->nextElement();

		if (uk == NULL) {
			_LOG << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
			continue;
		}

		// Copy the element as a reference
		i++;
		pos->setData(i);
		copy->insert(&uk, &key);
	}
	PluginModules->finishIteration();

	copy->finishIteration();
	while (copy->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_PluginModule, plM)

		uk = copy->nextElement();

		if (uk == NULL) {
			_LOG << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
			continue;
		}
		QI(uk, lb_I_PluginModule, plM)
		plM->install();
	}
	copy->finishIteration();
}
/*...sbool LB_STDCALL lbPluginManager\58\\58\beginEnumPlugins\40\\41\:0:*/
bool LB_STDCALL lbPluginManager::beginEnumPlugins() {
	if (!isInitialized) initialize();

	PluginModules->finishIteration();

	if (PluginModules->hasMoreElements()) {
		begunEnumerate = true;
		firstPlugin = true;
		return true;
	}
	return false;
}
/*...e*/
/*...slb_I_Plugin\42\ LB_STDCALL lbPluginManager\58\\58\nextPlugin\40\\41\:0:*/
lb_I_Plugin* LB_STDCALL lbPluginManager::nextPlugin() {
	lbErrCodes err = ERR_NONE;

	if (!isInitialized) initialize();

	if (begunEnumerate) {
		if (firstPlugin) {
			firstPlugin = FALSE;

			/*
			If no more plugin modules found return NULL.

			If there are more plugins in a plugin module, return one.

			If No more plugins in a module, go to next module and try there.
			*/

			while (PluginModules->hasMoreElements()) {
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_PluginModule, plM)

				uk = PluginModules->nextElement();

				if (uk == NULL) {
					_LOGERROR << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
					return NULL;
				}

				QI(uk, lb_I_PluginModule, plM)

				if (PluginContainer != NULL) {
					PluginContainer--;
					PluginContainer.resetPtr();
				}

				_LOG << "Initialize plugin " << plM->getModule()->charrep() LOG_
				
				PluginContainer = plM->getPlugins();

				if (PluginContainer == NULL) {
					_LOG << "Error: Plugin module returned no plugin list. Maybe not initialized!" LOG_
					return NULL;
				}

				if (PluginContainer->Count() == 0) {
					_LOG << "Error: Plugin module returned empty plugin list. Maybe not initialized!" LOG_
				}

				if (PluginContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginContainer->nextElement();

					if (uk == NULL) {
						_LOGERROR << "FATAL: Plugin container reported having at least one more element, but it may be corrupted." LOG_
						return NULL;
					}
					
					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				}
			}

			return NULL;
		} else {

			if (!lastPlugin) {
				if (PluginContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					lb_I_Unknown* u = PluginContainer->nextElement();

					if (u != NULL && u != (void*)0x7) {
						uk = u;
					} else {
						lbBreak();
					}
					
					if (uk == NULL) {
						_LOGERROR << "FATAL: Plugin container reported having at least one more element, but it may be corrupted." LOG_
						return NULL;
					}
					
					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				} else {
					firstPlugin = true;

					return nextPlugin();
				}
			}
		}

	} else {
		_CL_VERBOSE << "ERROR: Not begun with enumeration!" LOG_
	}

	return NULL;
}
/*...e*/
/*...slb_I_Plugin\42\ LB_STDCALL lbPluginManager\58\\58\getFirstMatchingPlugin\40\char\42\ match\44\ char\42\ _namespace\41\:0:*/
/// \todo Extend namespace feature by comma separated property list. (Or threaded as feature list).
lb_I_Plugin* LB_STDCALL lbPluginManager::getFirstMatchingPlugin(const char* match, const char* _namespace, const char* _version) {
	if (beginEnumPlugins()) {
		while (true) {
			UAP(lb_I_Plugin, pl)
			pl = nextPlugin();
			
			if (pl == NULL) {
				_LOGERROR "lbPluginManager::getFirstMatchingPlugin('" << match << "', '" << _namespace << "', '" << _version << "'): Didn't find any plugin.!" LOG_
				return NULL;
			}

			_LOG "lbPluginManager::getFirstMatchingPlugin('" << match << "', '" << pl->getNamespace() << "', '" << pl->getVersion() << "'): Searching.!" LOG_
			
			if ((strcmp(pl->getNamespace(), _namespace) == 0) && (strcmp(pl->getVersion(), _version) == 0) && pl->hasInterface(match)) {
				_LOG << "lbPluginManager::getFirstMatchingPlugin(...) found one." LOG_
				PluginContainer->finishIteration();
				PluginModules->finishIteration();

				pl++;

				return pl.getPtr();
			}
		}
		_LOG "lbPluginManager::getFirstMatchingPlugin('" << match << "', '" << _namespace << "', '" << _version << "'): Didn't find any plugin.!" LOG_
		_CL_LOG "Plugins registered:" LOG_


		if (beginEnumPlugins()) {

			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = nextPlugin();

				if (pl == NULL) break;

				//pl->initialize();

				_CL_LOG << "Plugin name, namespace, version: " << pl->getName() << ", " << pl->getNamespace() << ", " << pl->getVersion() LOG_
#ifdef bla
				if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
					UAP(lb_I_Unknown, uk)

					uk = pl->getImplementation();
					if (uk != NULL) {
						_CL_LOG << "Loaded: " << uk->getClassName() LOG_
					} else {
						_CL_LOG << "Failed to get plugin implementation." LOG_
					}
				}
#endif
			}
		}

		return NULL;
	} else {
		_LOG "lbPluginManager::getFirstMatchingPlugin('" << match << "', '" << _namespace << "', '" << _version << "'): No plugins registered!" LOG_
		return NULL;
	}
}
/*...e*/

/*...sbool LB_STDCALL lbPluginManager\58\\58\beginEnumServerPlugins\40\\41\:0:*/
bool LB_STDCALL lbPluginManager::beginEnumServerPlugins() {
	if (!isServerInitialized) initialize();

	PluginServerModules->finishIteration();

	if (PluginServerModules->hasMoreElements()) {
		begunServerEnumerate = true;
		return true;
	}
	return false;
}
/*...e*/

lb_I_ApplicationServerModul* LB_STDCALL lbPluginManager::nextServerPluginModul() {
	lbErrCodes err = ERR_NONE;

	if (!isServerInitialized) initialize();

	if (begunServerEnumerate) {
		while (PluginServerModules->hasMoreElements()) {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_ApplicationServerModul, plM)

			uk = PluginServerModules->nextElement();

			if (uk == NULL) {
				_LOG << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
				return NULL;
			}

			QI(uk, lb_I_ApplicationServerModul, plM)
			
			if (plM != NULL) {
				plM++;
				return plM.getPtr();
			}
		}
		begunServerEnumerate = false;
		return NULL;
	} else {
		_CL_VERBOSE << "ERROR: Not begun with enumeration!" LOG_
	}

	return NULL;
}

/*...slb_I_ApplicationServerModul\42\ LB_STDCALL lbPluginManager\58\\58\nextServerPlugin\40\\41\:0:*/
lb_I_Plugin* LB_STDCALL lbPluginManager::nextServerPlugin() {
	lbErrCodes err = ERR_NONE;

	if (!isServerInitialized) initialize();

	if (begunServerEnumerate) {
		if (firstServerPlugin) {
			firstServerPlugin = FALSE;

			/*
			If no more plugin modules found return NULL.

			If there are more plugins in a plugin module, return one.

			If No more plugins in a module, go to next module and try there.
			*/

			while (PluginServerModules->hasMoreElements()) {
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_ApplicationServerModul, plM)

				uk = PluginServerModules->nextElement();

				if (uk == NULL) {
					_LOG << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
					return NULL;
				}

				QI(uk, lb_I_ApplicationServerModul, plM)


				if (PluginServerContainer != NULL) {
					PluginServerContainer--;
					PluginServerContainer.resetPtr();
				}

				PluginServerContainer = plM->getPlugins();

				if (PluginServerContainer == NULL) {
					_LOG << "Error: Plugin module returned no plugin list. Maybe not initialized!" LOG_
					return NULL;
				}


				if (PluginServerContainer->Count() == 0) {
					_LOG << "Error: Plugin module returned empty plugin list. Maybe not initialized!" LOG_
				}

				if (PluginServerContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginServerContainer->nextElement();

					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				}
			}

			return NULL;
		} else {

			if (!lastServerPlugin) {
				if (PluginServerContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginServerContainer->nextElement();

					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				} else {
					firstServerPlugin = true;

					return nextServerPlugin();
				}
			}
		}

	} else {
		_CL_VERBOSE << "ERROR: Not begun with enumeration!" LOG_
	}

	return NULL;
}
/*...e*/

/*...slb_I_Plugin\42\ LB_STDCALL lbPluginManager\58\\58\getFirstMatchingServerPlugin\40\char\42\ match\44\ char\42\ _namespace\41\:0:*/
/// \todo Extend namespace feature by comma separated property list. (Or threaded as feature list).
lb_I_Plugin* LB_STDCALL lbPluginManager::getFirstMatchingServerPlugin(const char* match, const char* _namespace) {
	if (beginEnumServerPlugins()) {
		while (true) {
			UAP(lb_I_Plugin, pl)
			pl = nextServerPlugin();
			if (pl == NULL) break;

			if ((strcmp(pl->getNamespace(), _namespace) == 0) && pl->hasInterface(match)) {
				PluginServerContainer->finishIteration();
				PluginServerModules->finishIteration();

				pl++;

				return pl.getPtr();
			}
		}
		_LOG "lbPluginManager::getFirstMatchingServerPlugin('" << match << "', '" << _namespace << "'): Didn't find any plugin.!" LOG_
		_LOG "Plugins registered:" LOG_


		if (beginEnumServerPlugins()) {

			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = nextServerPlugin();

				if (pl == NULL) break;

				pl->initialize();

				_LOG << "Plugin name: " << pl->getName() LOG_
#ifdef bla
				if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
					UAP(lb_I_Unknown, uk)

					uk = pl->getImplementation();
					if (uk != NULL) {
						_CL_LOG << "Loaded: " << uk->getClassName() LOG_
					} else {
						_CL_LOG << "Failed to get plugin implementation." LOG_
					}
				}
#endif
			}
		}

		return NULL;
	} else {
		_LOG "lbPluginManager::getFirstMatchingServerPlugin('" << match << "', '" << _namespace << "'): No plugins registered!" LOG_
		return NULL;
	}
}
/*...e*/
/*...sbool LB_STDCALL lbPluginManager\58\\58\beginEnumPlugins\40\\41\:0:*/
bool LB_STDCALL lbPluginManager::beginEnumUnitTestPlugins() {
	if (!isInitialized) initialize();

	PluginUnitTestModules->finishIteration();

	if (PluginUnitTestModules->hasMoreElements()) {
		begunUnitTestEnumerate = true;
		firstUnitTestPlugin = true;
		return true;
	}
	return false;
}
/*...e*/
/*...slb_I_Plugin\42\ LB_STDCALL lbPluginManager\58\\58\nextPlugin\40\\41\:0:*/
lb_I_Plugin* LB_STDCALL lbPluginManager::nextUnitTestPlugin() {
	lbErrCodes err = ERR_NONE;

	if (!isInitialized) initialize();

	if (begunUnitTestEnumerate) {
		if (firstUnitTestPlugin) {
			firstUnitTestPlugin = FALSE;

			/*
				If no more plugin modules found return NULL.

				If there are more plugins in a plugin module, return one.

				If No more plugins in a module, go to next module and try there.
				*/

			while (PluginUnitTestModules->hasMoreElements()) {
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_UnitTestModul, plM)

				uk = PluginUnitTestModules->nextElement();

				if (uk == NULL) {
					_LOG << "Error: Got a NULL pointer, but reported was another element in PluginModules!" LOG_
					return NULL;
				}

				QI(uk, lb_I_UnitTestModul, plM)

				if (PluginUnitTestContainer != NULL) {
					PluginUnitTestContainer--;
					PluginUnitTestContainer.resetPtr();
				}

				_LOG << "Processing test fixture " << plM->getTestFixture() LOG_

				PluginUnitTestContainer = plM->getPlugins();

				if (PluginUnitTestContainer == NULL) {
					_LOG << "Error: Plugin module returned no plugin list. Maybe not initialized!" LOG_
					return NULL;
				}

				if (PluginUnitTestContainer->Count() == 0) {
					_LOG << "Error: Plugin module returned empty plugin list. Maybe not initialized!" LOG_
				}

				if (PluginUnitTestContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginUnitTestContainer->nextElement();

					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				}
			}

			return NULL;
		} else {

			if (!lastUnitTestPlugin) {
				if (PluginUnitTestContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginUnitTestContainer->nextElement();

					UAP(lb_I_Plugin, plugin)
					QI(uk, lb_I_Plugin, plugin)
					plugin++;

					return plugin.getPtr();
				} else {
					firstUnitTestPlugin = true;

					return nextUnitTestPlugin();
				}
			}
		}

	} else {
		_CL_VERBOSE << "ERROR: Not begun with enumeration!" LOG_
	}

	return NULL;
}
/*...e*/

/// \todo Implement plugin installation mechanism.
bool LB_STDCALL lbPluginManager::attach(lb_I_PluginModule* toAttach) {
	return FALSE;
}
/// \todo Implement plugin deinstallation mechanism.
bool LB_STDCALL lbPluginManager::detach(lb_I_PluginModule* toAttach) {
	return FALSE;
}
/*...e*/

/*...sclass lbPlugin:0:*/
/// \brief Plugin entity implementation.
class lbPlugin : public lb_I_Plugin {
public:
	
	lbPlugin();
	virtual ~lbPlugin();
	
	DECLARE_LB_UNKNOWN()
	
	lb_I_Unknown* 		LB_STDCALL getImplementation();
	bool 			LB_STDCALL hasInterface(const char* name);
	
	void 			LB_STDCALL preinitialize();
	
	bool			LB_STDCALL canAutorun();
	lbErrCodes		LB_STDCALL autorun();
	void 			LB_STDCALL initialize();
	bool 			LB_STDCALL run();
	void 			LB_STDCALL uninitialize();
	
	void 			LB_STDCALL setPluginManager(lb_I_PluginManager* plM);
	void 			LB_STDCALL setAttached(lb_I_PluginImpl* impl);
	lb_I_PluginImpl*	LB_STDCALL getAttached();
	
	void LB_STDCALL setModule(const char* module);
	void LB_STDCALL setName(const char* name);
	void LB_STDCALL setVersion(const char* version);
	void LB_STDCALL setNamespace(const char* __namespace);
	char* LB_STDCALL getModule() { return _module; }
	char* LB_STDCALL getName() { return _name; }
	char* LB_STDCALL getVersion() { return _version; }
	char* LB_STDCALL getNamespace() { return _namespace; }
	
private:
	lb_I_Unknown* LB_STDCALL peekImplementation();
	
	char* _name;
	char* _version;
	char* _namespace;
	char* _module;
	//	UAP(lb_I_PluginManager, _plM)
	
	UAP(lb_I_Unknown, implementation)
	
	bool isPreInitialized;
	bool postInitialized;
	
};
/*...e*/
/*...simplementation of class lbPlugin:0:*/
IMPLEMENT_FUNCTOR(instanceOfPlugin, lbPlugin)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin)
ADD_INTERFACE(lb_I_Plugin)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbPlugin\58\\58\lbPlugin\40\\41\:0:*/
lbPlugin::lbPlugin() {
	_module = NULL;
	_name = NULL;
	_namespace = NULL;
	_version = NULL;
	
	
	;
	postInitialized = false;
	
	//	implementation = NULL;
	isPreInitialized = false;
}
/*...e*/
/*...slbPlugin\58\\58\\126\lbPlugin\40\\41\:0:*/
lbPlugin::~lbPlugin() {
	if (implementation != NULL)
	_CL_VERBOSE << "lbPlugin::~lbPlugin() Implementation has " << implementation->getRefCount() << " references." LOG_
	
	if (_version) free (_version);
	if (_module) free(_module);
	if (_name) free(_name);
	if (_namespace) free(_namespace);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbPlugin\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPlugin::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPlugin::setData(...) called." LOG_
	
	UAP(lb_I_Plugin, pl)
	QI(uk, lb_I_Plugin, pl)
	
	setName(pl->getName());
	setModule(pl->getModule());
	setNamespace(pl->getNamespace());
	setVersion(pl->getVersion());
	
	setAttached(pl->getAttached());
	
	// getAttached increments reference, but this is not needed here.
	implementation--;
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...svoid LB_STDCALL lbPlugin\58\\58\setPluginManager\40\lb_I_PluginManager\42\ plM\41\:0:*/
void LB_STDCALL lbPlugin::setPluginManager(lb_I_PluginManager* plM) {
	//	_plM = plM;
	//	_plM++;
}
/*...e*/

/*...svoid LB_STDCALL lbPlugin\58\\58\setAttached\40\lb_I_PluginImpl\42\ impl\41\:0:*/
void LB_STDCALL lbPlugin::setAttached(lb_I_PluginImpl* impl) {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		_CL_VERBOSE << "lbPlugin::setAttached(NULL) called." LOG_
		return;
	}
	
	QI(impl, lb_I_Unknown, implementation)
	
	if (implementation == NULL) _CL_LOG << "Error: lbPlugin::setAttached() failure!" LOG_
}
/*...e*/
/*...slb_I_PluginImpl\42\ LB_STDCALL lbPlugin\58\\58\getAttached\40\\41\:0:*/
lb_I_PluginImpl* LB_STDCALL lbPlugin::getAttached() {
	lbErrCodes err = ERR_NONE;
	
	if (implementation == NULL) return NULL;
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	impl++;
	
	return impl.getPtr();
}
/*...e*/

void LB_STDCALL lbPlugin::uninitialize() {
	lbErrCodes err = ERR_NONE;
	if (implementation != NULL) {
		UAP(lb_I_PluginImpl, impl)
		QI(implementation, lb_I_PluginImpl, impl)
		
		impl->releaseImplementation();
	}
}
/*...svoid LB_STDCALL lbPlugin\58\\58\setModule\40\char\42\ module\41\:0:*/
void LB_STDCALL lbPlugin::setModule(const char* module) {
	if (_module) free(_module);
	_module = NULL;
	if (module) {
		_module = (char*) malloc(strlen(module)+1);
		_module[0] = 0;
		strcpy(_module, module);
	}
}
/*...e*/
/*...svoid LB_STDCALL lbPlugin\58\\58\setName\40\char\42\ name\41\:0:*/
void LB_STDCALL lbPlugin::setName(const char* name) {
	if (_name) free(_name);
	_name = NULL;
	if (name) {
		_name = (char*) malloc(strlen(name)+1);
		_name[0] = 0;
		strcpy(_name, name);
	}
}
/*...e*/
/*...svoid LB_STDCALL lbPlugin\58\\58\setVersion\40\char\42\ version\41\:0:*/
void LB_STDCALL lbPlugin::setVersion(const char* version) {
	if (_version) free(_version);
	_version = NULL;
	if (version) {
		_version = (char*) malloc(strlen(version)+1);
		_version[0] = 0;
		strcpy(_version, version);
	}
}
/*...e*/
/*...svoid LB_STDCALL lbPlugin\58\\58\setNamespace\40\char\42\ __namespace\41\:0:*/
void LB_STDCALL lbPlugin::setNamespace(const char* __namespace) {
	if (_namespace) free(_namespace);
	_namespace = NULL;
	if (__namespace) {
		_namespace = (char*) malloc(strlen(__namespace)+1);
		_namespace[0] = 0;
		strcpy(_namespace, __namespace);
	}
}
/*...e*/

/*...svoid LB_STDCALL lbPlugin\58\\58\preinitialize\40\\41\:0:*/
void LB_STDCALL lbPlugin::preinitialize() {
	lbErrCodes err = ERR_NONE;
	if (isPreInitialized) return;
	
	UAP(lb_I_Unknown, ukPlugin)
	
	char* name = (char*) malloc(strlen(PREFIX)+strlen("instanceOf")+strlen(_name)+1);
	
	name[0] = 0;
	strcat(name, PREFIX);
	strcat(name, "instanceOf");
	strcat(name, _name);
	
	_CL_VERBOSE << "lbPlugin::preinitialize() tries to get " << name << " from " << _module LOG_
	
	if (getModuleInstance()->makeInstance(name, _module, &ukPlugin) == ERR_NONE) {
		
		
		
		QI(ukPlugin, lb_I_Unknown, implementation)
		
		isPreInitialized = true;
		
	} else {
		name[0] = 0;
		strcat(name, "instanceOf");
		strcat(name, _name);
		
		if (getModuleInstance()->makeInstance(name, _module, &ukPlugin) == ERR_NONE) {
			QI(ukPlugin, lb_I_Unknown, implementation)
			
			isPreInitialized = true;
			
		} else {
			_LOG << "lbPlugin::preinitialize() failed to load plugin (name = '" << name << "', module = '" << _module << "')! Maybe the configured plugin is not implemented, or not with that name." LOG_
		}
	}
	
	_CL_VERBOSE << "Preinitialized instance has " << implementation->getRefCount() << " references (implementation)." LOG_
	
	free(name);
}
/*...e*/

bool	LB_STDCALL lbPlugin::canAutorun() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	
	if (impl != NULL) return impl->canAutorun();
	return false;
}

lbErrCodes		LB_STDCALL lbPlugin::autorun() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_PluginImpl, impl)
	
	preinitialize();
	
	if (isPreInitialized) {
		QI(implementation, lb_I_PluginImpl, impl)
		if(impl == NULL) {
			_LOG << "Error: Could not get interface lb_I_PluginImpl for implementation." LOG_
			return ERR_NONE;
		}
		return impl->autorun();
	}
	
	return ERR_PLUGIN_NOT_INITIALIZED;
}


void LB_STDCALL lbPlugin::initialize() {
	lbErrCodes err = ERR_NONE;
	
	preinitialize();
	
	_CL_VERBOSE << "lbPlugin::initialize() has preinitialized underlying class." LOG_
	
	if (isPreInitialized && !postInitialized) {
		UAP(lb_I_PluginImpl, impl)
		QI(implementation, lb_I_PluginImpl, impl)
		
		_CL_VERBOSE << "lbPlugin::initialize() calls preinitialized underlying class'es initializer." LOG_
		impl->initialize();
	}
	_CL_VERBOSE << "lbPlugin::initialize() returns." LOG_
	
	if (implementation == NULL) _CL_LOG << "Fatal: Have no implementation, but should have one!" LOG_
}

bool LB_STDCALL lbPlugin::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPlugin\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPlugin::peekImplementation() {
	/*
		This would give back the plugin implementation class, but possibly not the
		underlying class. The reason may be the fact, that the plugin is implemented
		in two parts.
		The first may be the lb_I_PluginImpl and the second may be the real implementation
		of any interface. May be, this would be a database form (lb_I_DatabaseForm).
		
		In such a case, it is better to call the lb_I_PluginImpl::getImplementation() function.
		It would eventually return another instance, where it not would be the lb_I_PluginImpl.
		*/
	
	lbErrCodes err = ERR_NONE;
	
	if (implementation == NULL) {
		_LOG << "lbPlugin::peekImplementation() Error: Have no plugin implementation. Could not proceed." LOG_
		return NULL;
	}
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	
	lb_I_Unknown* uk = NULL;
	
	if (impl == NULL) {
		_CL_LOG << "Error: Could not instantiate plugin implementation with given interface. (" << _name << ")" LOG_
		return NULL;
	}
	
	
	uk = impl->peekImplementation();
	
	return uk;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPlugin\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPlugin::getImplementation() {
	/*
		This would give back the plugin implementation class, but possibly not the
		underlying class. The reason may be the fact, that the plugin is implemented
		in two parts.
		The first may be the lb_I_PluginImpl and the second may be the real implementation
		of any interface. May be, this would be a database form (lb_I_DatabaseForm).
		
		In such a case, it is better to call the lb_I_PluginImpl::getImplementation() function.
		It would eventually return another instance, where it not would be the lb_I_PluginImpl.
		*/
	
	lbErrCodes err = ERR_NONE;
	
	if (implementation == NULL) {
		_LOG << "lbPlugin::getImplementation() Error: Have no plugin implementation. Could not proceed. Call initialize first." LOG_
	}
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	
	lb_I_Unknown* uk = NULL;
	
	if (impl == NULL) {
		_CL_LOG << "Error: Could not instantiate plugin implementation with given interface. (" << _name << ")" LOG_
		return NULL;
	}
	
	
	uk = impl->getImplementation();
	
	return uk;
}
/*...e*/
/*...sbool LB_STDCALL lbPlugin\58\\58\hasInterface\40\char\42\ name\41\:0:*/
bool LB_STDCALL lbPlugin::hasInterface(const char* name) {
	lbErrCodes err = ERR_NONE;
	lb_I_Unknown* temp;
	
	if (implementation == NULL) preinitialize();
	
	lb_I_Unknown* uk;
	
	uk = peekImplementation();
	
	/*
		It may be a combined plugin implementation. Currently these, could not have
		any other interface than lb_I_PluginImpl. This is due to multible inheritation
		problems and the same base class lb_I_Unknown.
		*/
	
	if (uk == NULL) {
		_LOG << "Warning: hasInterface(...) is useless, when peekImplementation returns a NULL pointer!" LOG_
		_LOG << "Info: Plugin name is " << _name << ", Modul is " << _module << ", Namespace is " << _namespace LOG_
		return false;
	}
	
	if (uk->queryInterface(name, (void**) &temp, __FILE__, __LINE__) == ERR_NONE) {
		temp->release(__FILE__, __LINE__);
		return true;
	}
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	
	impl->releaseImplementation();
	
	return false;
}
/*...e*/
/*...e*/


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
	char buf[100]="";
	
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		TRMemOpen();
		TRMemSetModuleName(__FILE__);
		
		if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
		
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
		_CL_LOG << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
		if (situation)
		{
			_CL_VERBOSE << "DLL released by system." LOG_
		}
		else
		{
			_CL_VERBOSE << "DLL released by program.\n" LOG_
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

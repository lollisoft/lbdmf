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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.40 $
 * $Name:  $
 * $Id: lbPluginManager.cpp,v 1.40 2006/02/26 23:46:19 lollisoft Exp $
 *
 * $Log: lbPluginManager.cpp,v $
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

//#include <lbInterfaces.h>
#include <lbConfigHook.h>

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



/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

#include <lbPluginManager.h>
/*...e*/

/*...sclass lbPluginManager:0:*/
/// \brief Plugin manager implementation.
class lbPluginManager : public lb_I_PluginManager {
public:

	lbPluginManager();
	virtual ~lbPluginManager();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL unload();
        bool LB_STDCALL beginEnumPlugins();

	lb_I_Plugin* LB_STDCALL getFirstMatchingPlugin(char* match, char* _namespace);
        lb_I_Plugin* LB_STDCALL nextPlugin();

        bool LB_STDCALL attach(lb_I_PluginModule* toAttach);
        bool LB_STDCALL detach(lb_I_PluginModule* toAttach);
        
private:


	bool LB_STDCALL tryLoad(char* module, char* path);

	bool begunEnumerate;
	bool firstEnumerate;
	
	UAP(lb_I_Container, PluginModules)


	UAP(lb_I_Container, PluginContainer)
	
	bool firstPlugin;
	bool lastPlugin;
};
/*...e*/
/*...simplementation of class lbPluginManager:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbPluginManager)
        ADD_INTERFACE(lb_I_PluginManager)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginManager, lbPluginManager)


lbPluginManager::lbPluginManager() {
	ref = STARTREF;
	begunEnumerate = firstEnumerate = false;
	firstPlugin = true;
	lastPlugin = false;
}

lbPluginManager::~lbPluginManager() {
	_CL_LOG << "lbPluginManager::~lbPluginManager() called." LOG_
}

void LB_STDCALL lbPluginManager::unload() {
	if(PluginContainer != NULL) {
		/**
		 * Releasing a reference, where the instance will not be deleted,
		 * an additional reset must be used.
		 *
		 * TODO: Rewrite UAP macro to reset pointer always.
		 */
		PluginContainer->release(__FILE__, __LINE__);
		PluginContainer.resetPtr();
	}
	
	PluginModules--;
	PluginModules.resetPtr();
}

lbErrCodes LB_STDCALL lbPluginManager::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginManager::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...sbool LB_STDCALL lbPluginManager\58\\58\tryLoad\40\char\42\ module\41\:0:*/
bool LB_STDCALL lbPluginManager::tryLoad(char* module, char* path) {
	lbErrCodes err = ERR_NONE;
	
	if (strcmp(".", module) == 0) return false;
	if (strstr(module, "so.") != NULL) return false;
	
	_CL_VERBOSE << "Try to load module '" << module << "'" LOG_
		
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
	strcat(pluginModule, "/");
#endif
#ifdef OSX
	strcat(pluginModule, "/");
#endif
	strcat(pluginModule, module);
	
	UAP(lb_I_Unknown, ukPlugin)
		UAP_REQUEST(manager.getPtr(), lb_I_String, pluginName)
		pluginName->setData(module);
	
	UAP(lb_I_KeyBase, key)
		QI(pluginName, lb_I_KeyBase, key)
		
		if (PluginModules->exists(&key) != 0) {
			_CL_LOG << "Warning: Plugin already registered." LOG_
		} else {
			if (manager->makeInstance(PREFIX "instanceOfPluginModule", pluginModule, &ukPlugin) != ERR_NONE) {
				
				// It may be a Microsoft compiled plugin...
				if (manager->makeInstance("instanceOfPluginModule", pluginModule, &ukPlugin) == ERR_NONE) {
					
					ukPlugin->setModuleManager(*&manager, __FILE__, __LINE__);
					
					PluginModules->insert(&ukPlugin, &key);
					
					UAP(lb_I_Unknown, ukPlugin1)
						
						ukPlugin1 = PluginModules->getElement(&key);
					
					UAP(lb_I_PluginModule, plM)
						QI(ukPlugin1, lb_I_PluginModule, plM)
						
						plM->setModule(pluginModule);
					free(pluginModule);
					free(pluginDir);
					return true;	
				}
				free(pluginModule);
				free(pluginDir);
				
				return false;
				
			} else {
				ukPlugin->setModuleManager(*&manager, __FILE__, __LINE__);
				PluginModules->insert(&ukPlugin, &key);
				
				UAP(lb_I_Unknown, ukPlugin1)
					
					ukPlugin1 = PluginModules->getElement(&key);
				
				UAP(lb_I_PluginModule, plM)
					QI(ukPlugin1, lb_I_PluginModule, plM)
					
					_CL_LOG << "lb_I_PluginModule has " << plM->getRefCount() << " references." LOG_
					
					plM->setModule(pluginModule);
				free(pluginModule);
				free(pluginDir);
			}
		}
	return true;
}
/*...e*/
/*...svoid LB_STDCALL lbPluginManager\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL lbPluginManager::initialize() {
	if (!firstEnumerate) {
		firstEnumerate = true;
		
		REQUEST(manager.getPtr(), lb_I_Container, PluginModules)
	}

	if (PluginModules == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, PluginModules)
	}

#ifdef WINDOWS	
	_finddata_t find;
#endif

#ifdef WINDOWS
	char* mask = "*.dll";
#endif
#ifdef LINUX
	char* mask = "*.so";
#endif
#ifndef LINUX
#ifdef OSX
	char* mask = "*.so";
#endif
#endif

	char* pluginDir = getenv("PLUGIN_DIR");
	
	if (pluginDir == NULL) {
		_LOG << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
		pluginDir = (char*) malloc(strlen(getenv("HOME"))+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, getenv("HOME"));
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
#ifdef WINDOWS
	strcat(toFind, "\\");
#endif
#ifdef LINUX
	strcat(toFind, "/");
#endif
#ifndef LINUX
#ifdef OSX
	strcat(toFind, "/");
#endif
#endif
	strcat(toFind, mask);

#ifdef WINDOWS	
	long handle = _findfirst(toFind, &find);
#endif
#ifdef LINUX
	DIR *dir;
	struct dirent *dir_info;
	
	if ((dir = opendir(pluginDir)) == NULL) {

	    free(toFind);
	    free(pluginDir);
		
		char* pwd = getenv("PWD");
		if (pwd == NULL) pwd = ".";

		pluginDir = (char*) malloc(strlen(pwd)+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, pwd);
		strcat(pluginDir, "/plugins");
		
		if ((dir = opendir(pluginDir)) == NULL) {
			_LOG << "Plugin directory not found!" LOG_
		
			free(toFind);
			free(pluginDir);
		
			return;
		}
	}
	
	dir_info = readdir(dir);
#endif

#ifndef LINUX
        #ifdef __WATCOMC__
        #define PREFIX "_"
        #endif
        #ifdef _MSC_VER
        #define PREFIX ""
        #endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif

#ifdef WINDOWS
	if (handle != -1) {
#endif
#ifdef LINUX
	if (dir_info != NULL) {
#endif
#ifdef WINDOWS	
		tryLoad(find.name, pluginDir);
#endif
#ifdef LINUX
		tryLoad(dir_info->d_name, pluginDir);
#endif
		
#ifdef WINDOWS
		while (_findnext(handle, &find) == 0) {
			tryLoad(find.name, pluginDir);
		}
#endif
#ifdef LINUX
		while ((dir_info = readdir(dir)) != NULL) {
			if (strstr(dir_info->d_name, ".so") != NULL) {
				_CL_LOG << "Try to load plugin: " << pluginDir << "/" << dir_info->d_name LOG_
			    tryLoad(dir_info->d_name, pluginDir);
			}
		}
#endif
#ifdef WINDOWS		
		_findclose(handle);
#endif
	} else {
		printf("No plugins found.\n");
	}
	
	free(pluginDir);
	free(toFind);
}
/*...e*/
/*...sbool LB_STDCALL lbPluginManager\58\\58\beginEnumPlugins\40\\41\:0:*/
bool LB_STDCALL lbPluginManager::beginEnumPlugins() {
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
		
				if (uk == NULL) return NULL;
		
				QI(uk, lb_I_PluginModule, plM)
		
				// Get all plugins of this module


				// This was a cause of the difficult bug that later on occures.
				//
				// The PluginContainer is a smart pointer that does the release
				// on it's instance, when assignement operator is used. Thus a
				// doulbe release also deletes the list of lb_I_PluginImpl instances.
				//
				//if (PluginContainer != NULL) {
				//	PluginContainer->release(__FILE__, __LINE__);
				//}
				
				plM->initialize();

				PluginContainer = plM->getPlugins();
			
				if (PluginContainer == NULL) return NULL;
			
				if (PluginContainer->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					uk = PluginContainer->nextElement();
				
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
				        uk = PluginContainer->nextElement();

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
lb_I_Plugin* LB_STDCALL lbPluginManager::getFirstMatchingPlugin(char* match, char* _namespace) {
	
	if (beginEnumPlugins()) {

        	while (true) {

	                UAP(lb_I_Plugin, pl)

	                pl = nextPlugin();

                	if (pl == NULL) break;

			lb_I_Unknown* uk;

			_CL_LOG << "Check for plugin with required interface and " << pl->getRefCount() << " references." LOG_

        	        if ((strcmp(pl->getNamespace(), _namespace) == 0) && pl->hasInterface(match)) {
        	        	_CL_LOG << "Return plugin with required interface and " << pl->getRefCount() << " references." LOG_
        	        	return pl.getPtr();
        	        }

	        }

		return NULL;
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
	bool 			LB_STDCALL hasInterface(char* name);

	void 			LB_STDCALL preinitialize();

	void 			LB_STDCALL initialize();
	bool 			LB_STDCALL run();
	void 			LB_STDCALL uninitialize();
	
	void 			LB_STDCALL setPluginManager(lb_I_PluginManager* plM);
	void 			LB_STDCALL setAttached(lb_I_PluginImpl* impl);
	lb_I_PluginImpl*	LB_STDCALL getAttached();

	void LB_STDCALL setModule(char* module);
	void LB_STDCALL setName(char* name);
	void LB_STDCALL setNamespace(char* __namespace);
	char* LB_STDCALL getModule() { return _module; }
	char* LB_STDCALL getName() { return _name; }
	char* LB_STDCALL getNamespace() { return _namespace; }

private:
	lb_I_Unknown* LB_STDCALL peekImplementation();

	char* _name;
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
	ref = STARTREF;
	
//	implementation = NULL;
	isPreInitialized = false;
}
/*...e*/
/*...slbPlugin\58\\58\\126\lbPlugin\40\\41\:0:*/
lbPlugin::~lbPlugin() {
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

void LB_STDCALL lbPlugin::setAttached(lb_I_PluginImpl* impl) {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		_CL_VERBOSE << "lbPlugin::setAttached(NULL) called." LOG_
		return;
	}
	
	QI(impl, lb_I_Unknown, implementation)
}

lb_I_PluginImpl* LB_STDCALL lbPlugin::getAttached() {
	lbErrCodes err = ERR_NONE;

	if (implementation == NULL) return NULL;
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)
	impl++;
	
	return impl.getPtr();
}

void LB_STDCALL lbPlugin::uninitialize() {

}
void LB_STDCALL lbPlugin::setModule(char* module) {
	if (_module) free(_module);
	_module = NULL;
	if (module) {
		_module = (char*) malloc(strlen(module)+1);
		_module[0] = 0;
		strcpy(_module, module);
	}
}
	
void LB_STDCALL lbPlugin::setName(char* name) { 
	if (_name) free(_name);
	_name = NULL;
	if (name) {
		_name = (char*) malloc(strlen(name)+1);
		_name[0] = 0;
		strcpy(_name, name);
	}
}
	
void LB_STDCALL lbPlugin::setNamespace(char* __namespace) {
	if (_namespace) free(_namespace);
	_namespace = NULL;
	if (__namespace) {
		_namespace = (char*) malloc(strlen(__namespace)+1);
		_namespace[0] = 0;
		strcpy(_namespace, __namespace);
	}
}

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

	if (manager.getPtr() == NULL) {
		_CL_VERBOSE << "FATAL: lbPlugin::preinitialize() uses a NULL pointer for the manager!" LOG_
	}

	_CL_VERBOSE << "lbPlugin::preinitialize() tries to get " << name << " from " << _module LOG_

	if (manager->makeInstance(name, _module, &ukPlugin) == ERR_NONE) {

		ukPlugin->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	        UAP(lb_I_PluginImpl, impl)
	        QI(ukPlugin, lb_I_PluginImpl, impl)
	        //impl++;

	        QI(ukPlugin, lb_I_Unknown, implementation)
	        //implementation++;
		
		isPreInitialized = true;

	} else {
		name[0] = 0;
		strcat(name, "instanceOf");
		strcat(name, _name);

		if (manager->makeInstance(name, _module, &ukPlugin) == ERR_NONE) {
		
			ukPlugin->setModuleManager(manager.getPtr(), __FILE__, __LINE__);;
		
			UAP(lb_I_PluginImpl, impl)
			QI(ukPlugin, lb_I_PluginImpl, impl)
			//impl++;
		
			QI(ukPlugin, lb_I_Unknown, implementation)
			//implementation++;

			isPreInitialized = true;

		} else {
			printf("lbPlugin::initialize() failed to forward call!\n");
		}
	}

	_CL_VERBOSE << "Preinitialized instance has " << implementation->getRefCount() << " references." LOG_

	free(name);
}
/*...e*/

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
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)

	lb_I_Unknown* uk = impl->peekImplementation();

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
	
	UAP(lb_I_PluginImpl, impl)
	QI(implementation, lb_I_PluginImpl, impl)

	lb_I_Unknown* uk = impl->getImplementation();

	return uk;
}
/*...e*/
/*...sbool LB_STDCALL lbPlugin\58\\58\hasInterface\40\char\42\ name\41\:0:*/
bool LB_STDCALL lbPlugin::hasInterface(char* name) {
	lbErrCodes err = ERR_NONE;
	lb_I_Unknown* temp;
	
	if (implementation == NULL) preinitialize();
	
	UAP(lb_I_Unknown, uk)

	/*
		This function firstly creates an instance of the implementation behind
		the plugin. So the reference count is at STARTREF. The above UAP variable
		then would release the instance.
	
		This should not be this way, because the lb_I_PluginImpl stores only one
		reverence to the instance.
		
		So, at this point, we need to increment the reference count manually!
	*/
	
	uk = peekImplementation();
	
	/*
		It may be a combined plugin implementation. Currently these, could not have
		any other interface than lb_I_PluginImpl. This is due to multible inheritation
		problems and the same base class lb_I_Unknown.
        */
        
	if (uk == NULL) return false;

	if (uk->queryInterface(name, (void**) &temp, __FILE__, __LINE__) == ERR_NONE) {
		temp->release(__FILE__, __LINE__);
		uk++;
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

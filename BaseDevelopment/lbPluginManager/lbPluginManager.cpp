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
            
            40235 DÅsseldorf (germany)
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.6 $
 * $Name:  $
 * $Id: lbPluginManager.cpp,v 1.6 2005/03/03 07:34:33 lollisoft Exp $
 *
 * $Log: lbPluginManager.cpp,v $
 * Revision 1.6  2005/03/03 07:34:33  lollisoft
 * Improoved the plugin loader code.
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

#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <malloc.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>



/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

#include <lbPluginManager.h>
/*...e*/

/*...sclass lbPluginManager:0:*/
class lbPluginManager : public lb_I_PluginManager {
public:

	lbPluginManager();
	virtual ~lbPluginManager();

	DECLARE_LB_UNKNOWN()

        bool LB_STDCALL beginEnumPlugins();
        lb_I_Plugin* LB_STDCALL nextPlugin();
        bool LB_STDCALL attach(lb_I_Plugin* toAttach);
        bool LB_STDCALL detach(lb_I_Plugin* toAttach);
        
private:


	bool LB_STDCALL tryLoad(char* module);

	bool begunEnumerate;
	bool firstEnumerate;
	
	UAP(lb_I_Container, PluginModules, __FILE__, __LINE__)
	UAP(lb_I_Container, PluginContainer, __FILE__, __LINE__)
	
	bool firstPlugin;
	bool lastPlugin;
};
/*...e*/
/*...simplementation of class lbPluginManager:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginManager)
        ADD_INTERFACE(lb_I_PluginManager)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginManager, lbPluginManager)


lbPluginManager::lbPluginManager() {
	ref = STARTREF;
	begunEnumerate = firstEnumerate = FALSE;
	firstPlugin = TRUE;
	lastPlugin = FALSE;
}

lbPluginManager::~lbPluginManager() {
	printf("lbPluginManager::~lbPluginManager() called\n");
}

lbErrCodes LB_STDCALL lbPluginManager::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPluginManager::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...sbool LB_STDCALL lbPluginManager\58\\58\tryLoad\40\char\42\ module\41\:0:*/
bool LB_STDCALL lbPluginManager::tryLoad(char* module) {
	lbErrCodes err = ERR_NONE;
	char* pluginDir = getenv("PLUGIN_DIR");
				
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
				
	// Instantiate an lb_I_PluginModule object
		
	char* pluginModule = new char[strlen(pluginDir)+strlen(module)+2];
	pluginModule[0] = 0;
	strcat(pluginModule, pluginDir);
	strcat(pluginModule, "\\");
	strcat(pluginModule, module);
		
	UAP(lb_I_Unknown, ukPlugin, __FILE__, __LINE__)
				       
	if (manager->makeInstance(PREFIX "instanceOfPluginModule", pluginModule, &ukPlugin) != ERR_NONE) {
	
		// It may be a Microsoft compiled plugin...
		if (manager->makeInstance("instanceOfPluginModule", pluginModule, &ukPlugin) == ERR_NONE) {
			ukPlugin->setModuleManager(*&manager, __FILE__, __LINE__);
		
			delete [] pluginModule;
		
			UAP_REQUEST(manager.getPtr(), lb_I_String, pluginName)
			pluginName->setData(module);
			
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
			
			QI(pluginName, lb_I_KeyBase, key, __FILE__, __LINE__)

			PluginModules->insert(&ukPlugin, &key);
	
			delete [] pluginModule;
	
			return true;	
		}
	
	
		delete [] pluginModule;
	
		return false;
	
	} else {
		
		ukPlugin->setModuleManager(*&manager, __FILE__, __LINE__);
		
		delete [] pluginModule;
		
		UAP_REQUEST(manager.getPtr(), lb_I_String, pluginName)
		pluginName->setData(module);
			
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
			
		QI(pluginName, lb_I_KeyBase, key, __FILE__, __LINE__)

		PluginModules->insert(&ukPlugin, &key);
	}

	return true;
}
/*...e*/

/*...sbool LB_STDCALL lbPluginManager\58\\58\beginEnumPlugins\40\\41\:0:*/
bool LB_STDCALL lbPluginManager::beginEnumPlugins() {
	if (!firstEnumerate) {
		firstEnumerate = TRUE;
		
		REQUEST(manager.getPtr(), lb_I_Container, PluginModules)
	}
	
	// Scan the plugin directory for DLL's or so's and try to get the plugin module instance.
	// If the instance could be loaded, insert its plugin definitions into the container.
	
	// ...
	
	
	_finddata_t find;

	char* mask = "*.dll";
	char* pluginDir = getenv("PLUGIN_DIR");
	char* toFind = new char[strlen(mask)+strlen(pluginDir)+2];
	toFind[0] = 0;
	
	strcat(toFind, pluginDir);
	strcat(toFind, "\\");
	strcat(toFind, mask);
	
	long handle = _findfirst(toFind, &find);


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
	
	if (handle != -1) {
		printf("Try to load plugin '%s'\n", find.name);
		tryLoad(find.name);
/*...stest:16:*/
#ifdef bla
		if (PluginModules->exists(&key) == 1) {
			printf("Stored element is really in the container.\n");
			
			ukPlugin = PluginModules->getElement(&key);
			
			UAP(lb_I_PluginModule, PM, __FILE__, __LINE__)
			QI(ukPlugin, lb_I_PluginModule, PM, __FILE__, __LINE__)
			
			
			PM->initialize();
		}
#endif
/*...e*/

		while (_findnext(handle, &find) == 0) {
			printf("Try to load plugin '%s'\n", find.name);
			tryLoad(find.name);
		}
		
		_findclose(handle);
	} else {
		printf("No plugins found.\n");
	}
	
	delete [] toFind;
	
	if (PluginModules->hasMoreElements()) {
		begunEnumerate = TRUE;
		return TRUE;
	}
	return FALSE;
}
/*...e*/

/*...slb_I_Plugin\42\ LB_STDCALL lbPluginManager\58\\58\nextPlugin\40\\41\:0:*/
lb_I_Plugin* LB_STDCALL lbPluginManager::nextPlugin() {

	if (begunEnumerate) {
	
	#ifdef rubbish
	// Must be established in beginEnumPlugins because of the possible failure,
	// if the plugin module has really no modules.
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_PluginModule, plM, __FILE__, __LINE__)
		
		if (firstPlugin) {
		// Have first Plugin of one module
			firstPlugin = FALSE;
		
			uk = PluginModules->nextElement();
		
			QI(uk, lb_I_PluginModule, plM, __FILE__, __LINE__)
		
			PluginCountainer = plM->getPlugins();
		} else {
			
		}	
	#endif
	
	}

	return NULL;
}
/*...e*/

bool LB_STDCALL lbPluginManager::attach(lb_I_Plugin* toAttach) {
	return FALSE;
}

bool LB_STDCALL lbPluginManager::detach(lb_I_Plugin* toAttach) {
	return FALSE;
}
/*...e*/
/*...sclass lbPlugin:0:*/
class lbPlugin : public lb_I_Plugin {
public:

        lbPlugin();
        virtual ~lbPlugin();

        DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL uninitialize();
	
	void LB_STDCALL setPluginManager(lb_I_PluginManager* plM);
	void LB_STDCALL setAttached(lb_I_PluginImpl* impl);
	
	void LB_STDCALL setModule(char* module) { _module = strdup(module); }
	void LB_STDCALL setName(char* name) { _name = strdup(name); }
	void LB_STDCALL setScope(char* scope) { _scope = strdup(scope); }

	char* LB_STDCALL getModule() { return _module; }
	char* LB_STDCALL getName() { return _name; }
	char* LB_STDCALL getScope() { return _scope; }

	char* _name;
	char* _scope;
	char* _module;
	UAP(lb_I_PluginManager, _plM, __FILE__, __LINE__)
};
/*...e*/
/*...simplementation of class lbPlugin:0:*/
IMPLEMENT_FUNCTOR(instanceOfPlugin, lbPlugin)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPlugin)
        ADD_INTERFACE(lb_I_Plugin)
END_IMPLEMENT_LB_UNKNOWN()

lbPlugin::lbPlugin() {
	ref = STARTREF;
}

lbPlugin::~lbPlugin() {

}

lbErrCodes LB_STDCALL lbPlugin::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPlugin::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbPlugin::setPluginManager(lb_I_PluginManager* plM) {
	_plM = plM;
	_plM++;
}

void LB_STDCALL lbPlugin::setAttached(lb_I_PluginImpl* impl) {

}

void LB_STDCALL lbPlugin::uninitialize() {

}

void LB_STDCALL lbPlugin::initialize() {

}
/*...e*/

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
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbPluginManager.cpp,v 1.4 2004/06/09 06:59:59 lollisoft Exp $
 *
 * $Log: lbPluginManager.cpp,v $
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
	bool begunEnumerate;
	bool firstEnumerate;
	
	UAP(lb_I_Container, PluginModules, __FILE__, __LINE__)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginManager)
        ADD_INTERFACE(lb_I_PluginManager)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginManager, lbPluginManager)


lbPluginManager::lbPluginManager() {
	ref = STARTREF;
	begunEnumerate = firstEnumerate = FALSE;
}

lbPluginManager::~lbPluginManager() {

}

lbErrCodes LB_STDCALL lbPluginManager::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPluginManager::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

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

	char* pluginDir = getenv("PLUGIN_DIR");
	char* mask = "*.dll";
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
		printf("Plugin: %s\n", find.name);

		lbErrCodes err = ERR_NONE;
			
		// Instantiate an lb_I_PluginModule object
		
		char* pluginModule = new char[strlen(pluginDir)+strlen(find.name)+2];
		pluginModule[0] = 0;
		strcat(pluginModule, pluginDir);
		strcat(pluginModule, "\\");
		strcat(pluginModule, find.name);
		
		UAP(lb_I_Unknown, ukPlugin, __FILE__, __LINE__)
				       
		manager->makeInstance(PREFIX "instanceOfPluginModule", pluginModule, &ukPlugin);
		delete [] pluginModule;
		
		UAP_REQUEST(manager.getPtr(), lb_I_String, pluginName)
		pluginName->setData(find.name);
			
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
			
		QI(pluginName, lb_I_KeyBase, key, __FILE__, __LINE__)
			
		PluginModules->insert(&ukPlugin, &key);

		while (_findnext(handle, &find) == 0) {
/*...sTry load plugin and insert into list:24:*/
			printf("Found plugin in while loop: %s\n", find.name);
			
			// Instantiate an lb_I_PluginModule object
		
			char* pluginModule = new char[strlen(pluginDir)+strlen(find.name)+2];
			pluginModule[0] = 0;
			strcat(pluginModule, pluginDir);
			strcat(pluginModule, "\\");
			strcat(pluginModule, find.name);
		
			UAP(lb_I_Unknown, ukPlugin, __FILE__, __LINE__)
			manager->makeInstance(PREFIX "instanceOfPluginModule", pluginModule, &ukPlugin);
			delete [] pluginModule;
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, pluginName)
			pluginName->setData(find.name);
			
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
			
			QI(pluginName, lb_I_KeyBase, key, __FILE__, __LINE__)
			
			PluginModules->insert(&ukPlugin, &key);
/*...e*/
		}
		
		_findclose(handle);
	} else {
		printf("No plugins found.\n");
	}
	
	delete [] toFind;
	
	if (PluginModules->hasMoreElements() == 1) return TRUE;
	
	return FALSE;
}
/*...e*/

lb_I_Plugin* LB_STDCALL lbPluginManager::nextPlugin() {

	if (begunEnumerate) {
	
	}

	return NULL;
}

bool LB_STDCALL lbPluginManager::attach(lb_I_Plugin* toAttach) {
	return FALSE;
}

bool LB_STDCALL lbPluginManager::detach(lb_I_Plugin* toAttach) {
	return FALSE;
}

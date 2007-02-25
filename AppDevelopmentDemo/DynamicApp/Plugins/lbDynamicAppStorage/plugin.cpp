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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
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

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>
#include <lbInterfaces.h>



/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/

/*...sclass lbPluginModuleDynamicAppStorage:0:*/
class lbPluginModuleDynamicAppStorage : public lb_I_PluginModule {
public:

	lbPluginModuleDynamicAppStorage();
	virtual ~lbPluginModuleDynamicAppStorage();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleDynamicAppStorage implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleDynamicAppStorage)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleDynamicAppStorage)

BEGIN_PLUGINS(lbPluginModuleDynamicAppStorage)
	ADD_PLUGIN(lbPluginDynamicAppInputXMLStreamVisitor,			DynamicAppInputXMLStreamVisitor)
	ADD_PLUGIN(lbPluginDynamicAppOutputXMLStreamVisitor,		DynamicAppOutputXMLStreamVisitor)
END_PLUGINS()



lbPluginModuleDynamicAppStorage::lbPluginModuleDynamicAppStorage() {
	ref = STARTREF;
}

lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() {
	_CL_VERBOSE << "lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() called." LOG_
}

void LB_STDCALL lbPluginModuleDynamicAppStorage::initialize() {
	_CL_VERBOSE << "lbPluginModuleDynamicAppStorage::initialize() called." LOG_
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModuleDynamicAppStorage::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleDynamicAppStorage::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_LOG << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

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
            
            40235 D�sseldorf (germany)
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

#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <malloc.h>

#include <lbConfigHook.h>
#include <lbInterfaces.h>



/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

#include <lbDatabaseForm.h>
/*...e*/

class lbPluginModule : public lb_I_PluginModule {
public:

	lbPluginModule();
	virtual ~lbPluginModule();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModule)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginModule, lbPluginModule)


BEGIN_PLUGINS(lbPluginModule)
	ADD_PLUGIN(databaseForm, GUI)
END_PLUGINS()

lbPluginModule::lbPluginModule() {
	ref = STARTREF;
}

lbPluginModule::~lbPluginModule() {

}

void LB_STDCALL lbPluginModule::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModule::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPluginModule::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

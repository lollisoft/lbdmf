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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lbPluginManager.cpp,v 1.1 2004/06/06 12:31:21 lollisoft Exp $
 *
 * $Log: lbPluginManager.cpp,v $
 * Revision 1.1  2004/06/06 12:31:21  lollisoft
 * Initial
 *
 **************************************************************/

/*...e*/

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
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
#include <lbPluginManager-module.h>
/*...e*/

#include <lbPluginManager.h>
/*...e*/




class lbPluginManager : public lb_I_PluginManager {
public:

	lbPluginManager() {}
	virtual ~lbPluginManager() {}

	DECLARE_LB_UNKNOWN()

        void LB_STDCALL beginEnumPlugins();
        lb_I_Plugin* LB_STDCALL nextPlugin();
        bool LB_STDCALL attach(lb_I_Plugin* toAttach);
        bool LB_STDCALL detach(lb_I_Plugin* toAttach);
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginManager)
        ADD_INTERFACE(lb_I_PluginManager)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginManager, lbPluginManager)

lbErrCodes LB_STDCALL lbPluginManager::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPluginManager::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbPluginManager::beginEnumPlugins() {

}

lb_I_Plugin* LB_STDCALL lbPluginManager::nextPlugin() {
	return NULL;
}

bool LB_STDCALL lbPluginManager::attach(lb_I_Plugin* toAttach) {
	return FALSE;
}

bool LB_STDCALL lbPluginManager::detach(lb_I_Plugin* toAttach) {
	return FALSE;
}

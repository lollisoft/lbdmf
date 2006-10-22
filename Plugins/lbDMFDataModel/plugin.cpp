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

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

/*...e*/

/*...sclass lbPluginModulelbDMFDataModel:0:*/
class lbPluginModulelbDMFDataModel : public lb_I_PluginModule {
public:

	lbPluginModulelbDMFDataModel();
	virtual ~lbPluginModulelbDMFDataModel();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModulelbDMFDataModel implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulelbDMFDataModel)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulelbDMFDataModel)

BEGIN_PLUGINS(lbPluginModulelbDMFDataModel)
	ADD_PLUGIN(lbPluginApplications, Model)
	ADD_PLUGIN(lbPluginUsersModel, Model)	
	ADD_PLUGIN(lbPluginFormularsModel, Model)	
	ADD_PLUGIN(lbPluginUserApplicationRelationModel, Model)
	ADD_PLUGIN(lbPluginFormularParameters, Model)
	ADD_PLUGIN(lbPluginApplicationParameters, Model)
	ADD_PLUGIN(lbPluginActionsModel, Model)
	ADD_PLUGIN(lbPluginActionTypesModel, Model)
	ADD_PLUGIN(lbPluginActionStepsModel, Model)
	ADD_PLUGIN(lbPluginTranslationsModel, Model)
END_PLUGINS()

lbPluginModulelbDMFDataModel::lbPluginModulelbDMFDataModel() {
	ref = STARTREF;
	_CL_VERBOSE << "lbPluginModulelbDMFDataModel::lbPluginModulelbDMFDataModel() called." LOG_
}

lbPluginModulelbDMFDataModel::~lbPluginModulelbDMFDataModel() {
	_CL_VERBOSE << "lbPluginModulelbDMFDataModel::~lbPluginModulelbDMFDataModel() called." LOG_
}

void LB_STDCALL lbPluginModulelbDMFDataModel::initialize() {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModulelbDMFDataModel::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulelbDMFDataModel::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

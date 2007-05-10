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
#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#include <lbConfigHook.h>
/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbDynamicAppStorage.h>

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppXMLStorage, lbDynamicAppXMLStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppXMLStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppXMLStorage::lbDynamicAppXMLStorage() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppStorage::lbDynamicAppStorage() called." LOG_
}

lbDynamicAppXMLStorage::~lbDynamicAppXMLStorage() {
	_CL_LOG << "lbDynamicAppStorage::~lbDynamicAppStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppInternalStorage, lbDynamicAppInternalStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppInternalStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() called." LOG_
}

lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() {
	_CL_LOG << "lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppInternalStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Uknkown, uk)

	UAP(lb_I_Formulars, forms)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)

	UAP_REQUEST(getMuduleInstance(), lb_I_MetaApplication, meta)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = meta->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)
			
	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, forms)
			
	*name = "FormParams";
	uk = document->getElement(&key);
	QI(formParams, lb_I_FormularParameter, formParams)
			
	*name = "AppParams";
	uk = document->getElement(&key);
	QI(appParams, lb_I_ApplicationParameter, appParams)
	
	*name = "AppActions";
	uk = document->getElement(&key);
	QI(appActions, lb_I_Actions, appActions)
			
	*name = "AppActionSteps";
	uk = document->getElement(&key);
	QI(appActionSteps, lb_I_Action_Steps, appActionSteps)
			
	*name = "AppActionTypes";
	uk = document->getElement(&key);
	QI(appActionTypes, lb_I_Action_Types, appActionTypes)


	if (forms != NULL) {
		_CL_LOG << "Save a forms model object..." LOG_
		forms->accept(*&aspect);
	}

	if (formParams != NULL) {
		_CL_LOG << "Save a formParams model object..." LOG_
		formParams->accept(*&aspect);
	}

	if (appParams != NULL) {
		_CL_LOG << "Save a appParams model object..." LOG_
		appParams->accept(*&aspect);
	}
					
	if (appActions != NULL) {
		_CL_LOG << "Save a appActions model object..." LOG_
		appActions->accept(*&aspect);
	}
			
	if (appActionTypes != NULL) {
		_CL_LOG << "Save a appActionTypes model object..." LOG_
		appActionTypes->accept(*&aspect);
	}
					
	if (appActionSteps != NULL) {
		_CL_LOG << "Save a appActionSteps model object..." LOG_
		appActionSteps->accept(*&aspect);
	}

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}


/*...sclass lbPluginDynamicAppXMLStorage implementation:0:*/
/*...slbPluginDynamicAppXMLStorage:0:*/
class lbPluginDynamicAppXMLStorage : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppXMLStorage();
	
	virtual ~lbPluginDynamicAppXMLStorage();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppXMLStorage)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppXMLStorage, lbPluginDynamicAppXMLStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppXMLStorage::lbPluginDynamicAppXMLStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDynamicAppXMLStorage::~lbPluginDynamicAppXMLStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppXMLStorage::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppXMLStorage::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppXMLStorage::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppXMLStorage::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




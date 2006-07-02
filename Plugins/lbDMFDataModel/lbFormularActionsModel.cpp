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
#define LB_DMFDATAMODEL_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>
#include <lbdmfdatamodel-module.h>

#include <lbFormularActionsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbFormularActionsModel, lbFormularActionsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormularActionsModel)
	ADD_INTERFACE(lb_I_Actions)
END_IMPLEMENT_LB_UNKNOWN()


lbFormularActionsModel::lbFormularActionsModel() {
	ref = STARTREF;

	REQUEST(getModuleInstance(), lb_I_Container, FormularActions)
	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularActionFormularID)
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularActionActionID)
	
	REQUEST(getModuleInstance(), lb_I_String, currentFormularActionEvent)
}

lbFormularActionsModel::~lbFormularActionsModel() {

}

lbErrCodes LB_STDCALL lbFormularActionsModel::setData(lb_I_Unknown*) {
		_CL_LOG << "Error: lbFormularActionsModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormularActionsModel::addFormularAction(long formular, long action,  const char* event, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Formular)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ActionID)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Event)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*Event = event;
	Formular->setData(formular);
	ActionID->setData(action);
	ID->setData(_id);
	
	*paramname = "Formular";
	param->setUAPLong(*&paramname, *&Formular);
	*paramname = "Action";
	param->setUAPLong(*&paramname, *&ActionID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "Event";
	param->setUAPString(*&paramname, *&Event);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FormularActions->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbFormularActionsModel::selectFormularAction(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = FormularActions->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
	
		*name = "Formular";
		param->getUAPLong(*&name, *&currentFormularActionFormularID);
		*name = "Action";
		param->getUAPLong(*&name, *&currentFormularActionActionID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentFormularActionID);
		*name = "Event";
		param->getUAPString(*&name, *&currentFormularActionEvent);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbFormularActionsModel::getFormularActionsCount() {
	return FormularActions->Count();
}

bool  LB_STDCALL lbFormularActionsModel::hasMoreFormularActions() {
	return FormularActions->hasMoreElements();
}

void  LB_STDCALL lbFormularActionsModel::setNextFormularAction() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = FormularActions->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Formular";
	param->getUAPLong(*&name, *&currentFormularActionFormularID);
	*name = "Action";
	param->getUAPLong(*&name, *&currentFormularActionActionID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentFormularActionID);
	*name = "Event";
	param->getUAPString(*&name, *&currentFormularActionEvent);
}

void  LB_STDCALL lbFormularActionsModel::finishFormularActionIteration() {
	FormularActions->finishIteration();
}

long LB_STDCALL lbFormularActionsModel::getFormularActionID() {
	return currentFormularActionID->getData();
}

char*  LB_STDCALL lbFormularActionsModel::getFormularActionEvent() {
	return currentFormularActionEvent->charrep();
}

long LB_STDCALL lbFormularActionsModel::getFormularActionFormularID() {
	return currentFormularActionFormularID->getData();
}

long LB_STDCALL lbFormularActionsModel::getFormularActionActionID() {
	return currentFormularActionActionID->getData();
}

/*...sclass lbPluginFormularActionsModel implementation:0:*/
/*...slbPluginFormularActionsModel:0:*/
class lbPluginFormularActionsModel : public virtual lb_I_PluginImpl {
public:
	lbPluginFormularActionsModel();
	
	virtual ~lbPluginFormularActionsModel();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularActionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularActionsModel, lbPluginFormularActionsModel)

/*...slbErrCodes LB_STDCALL lbPluginFormularActionsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginFormularActionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularActionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFormularActionsModel::lbPluginFormularActionsModel() {
	_CL_VERBOSE << "lbPluginFormularActionsModel::lbPluginFormularActionsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginFormularActionsModel::~lbPluginFormularActionsModel() {
	_CL_VERBOSE << "lbPluginFormularActionsModel::~lbPluginFormularActionsModel() called.\n" LOG_
}

void LB_STDCALL lbPluginFormularActionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularActionsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularActionsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularActionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularActions == NULL) {
		lbFormularActionsModel* ActionsModel = new lbFormularActionsModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukFormularActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularActionsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularActionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormularActionsModel* ActionsModel = new lbFormularActionsModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukFormularActions)
	}
	
	lb_I_Unknown* r = ukFormularActions.getPtr();
	ukFormularActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFormularActionsModel::releaseImplementation() {
}
/*...e*/
/*...e*/




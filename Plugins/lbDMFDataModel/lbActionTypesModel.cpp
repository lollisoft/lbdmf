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

#include <lbActionTypesModel.h>

IMPLEMENT_FUNCTOR(instanceOflbActionTypesModel, lbActionTypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionTypesModel)
	ADD_INTERFACE(lb_I_Action_Types)
END_IMPLEMENT_LB_UNKNOWN()


lbActionTypesModel::lbActionTypesModel() {
	ref = STARTREF;

	REQUEST(getModuleInstance(), lb_I_Container, Actions)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTyp)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTarget)
	REQUEST(getModuleInstance(), lb_I_String, currentActionName)
	REQUEST(getModuleInstance(), lb_I_String, currentActionSource)
	_CL_LOG << "lbActionTypesModel::lbActionTypesModel() called." LOG_
}

lbActionTypesModel::~lbActionTypesModel() {
	_CL_LOG << "lbActionTypesModel::~lbActionTypesModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionTypesModel::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbActionTypesModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionTypesModel::addAction(const char* name, long typ, const char* source, long target, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Source)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Typ)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Target)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionTypesModel: " << name LOG_

	*Name = name;
	*Source = source;
	Typ->setData(typ);
	Target->setData(target);
	ID->setData(_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Source";
	param->setUAPString(*&paramname, *&Source);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "Target";
	param->setUAPLong(*&paramname, *&Target);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbActionTypesModel::selectAction(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Actions->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentActionName);
		*name = "Source";
		param->getUAPString(*&name, *&currentActionSource);
		*name = "ID";
		param->getUAPLong(*&name, *&currentActionID);
		*name = "Typ";
		param->getUAPLong(*&name, *&currentActionTyp);
		*name = "Target";
		param->getUAPLong(*&name, *&currentActionTarget);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbActionTypesModel::getActionCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionTypesModel::hasMoreActions() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionTypesModel::setNextAction() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Actions->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentActionName);
	*name = "Source";
	param->getUAPString(*&name, *&currentActionSource);
	*name = "ID";
	param->getUAPLong(*&name, *&currentActionID);
	*name = "Typ";
	param->getUAPLong(*&name, *&currentActionTyp);
	*name = "Target";
	param->getUAPLong(*&name, *&currentActionTarget);
}

void  LB_STDCALL lbActionTypesModel::finishActionIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionTypesModel::getActionID() {
	return currentActionID->getData();
}

char*  LB_STDCALL lbActionTypesModel::getActionName() {
	return currentActionName->charrep();
}

char*  LB_STDCALL lbActionTypesModel::getActionSource() {
	return currentActionSource->charrep();
}

long LB_STDCALL lbActionTypesModel::getActionTyp() {
	return currentActionTyp->getData();
}

long LB_STDCALL lbActionTypesModel::getActionTarget() {
	return currentActionTarget->getData();
}

/*...sclass lbPluginActionTypesModel implementation:0:*/
/*...slbPluginActionTypesModel:0:*/
class lbPluginActionTypesModel : public lb_I_PluginImpl {
public:
	lbPluginActionTypesModel();
	
	virtual ~lbPluginActionTypesModel();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionTypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionTypesModel, lbPluginActionTypesModel)

/*...slbErrCodes LB_STDCALL lbPluginActionTypesModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionTypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionTypesModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionTypesModel::lbPluginActionTypesModel() {
	_CL_VERBOSE << "lbPluginActionTypesModel::lbPluginActionTypesModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginActionTypesModel::~lbPluginActionTypesModel() {
	_CL_VERBOSE << "lbPluginActionTypesModel::~lbPluginActionTypesModel() called.\n" LOG_
}

void LB_STDCALL lbPluginActionTypesModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionTypesModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionTypesModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionTypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbActionTypesModel* ActionsModel = new lbActionTypesModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionTypesModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionTypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionTypesModel* ActionsModel = new lbActionTypesModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionTypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




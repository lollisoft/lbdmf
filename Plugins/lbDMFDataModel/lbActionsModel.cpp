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
            Ginsterweg 4

            65760 Eschborn (germany)
*/
/*...e*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbActionsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbActionsModel, lbActionsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionsModel)
	ADD_INTERFACE(lb_I_Actions)
END_IMPLEMENT_LB_UNKNOWN()


lbActionsModel::lbActionsModel() {
	

	REQUEST(getModuleInstance(), lb_I_Container, Actions)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionApplicationID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTyp)
	REQUEST(getModuleInstance(), lb_I_String, currentActionTarget)
	REQUEST(getModuleInstance(), lb_I_String, currentActionName)
	REQUEST(getModuleInstance(), lb_I_String, currentActionSource)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	
	_CL_VERBOSE << "lbActionsModel::lbActionsModel() called." LOG_
}

lbActionsModel::~lbActionsModel() {
	_CL_VERBOSE << "lbActionsModel::~lbActionsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void		LB_STDCALL lbActionsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActions()) {
		setNextAction();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getActionID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActions()) {
		setNextAction();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getActionID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}


long  LB_STDCALL lbActionsModel::addAction(const char* name, long typ, const char* source, const char* target, long _applicationid, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Source)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ApplicationID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Typ)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Target)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionsModel: " << name LOG_

	*Name = name;
	*Source = source;
	Typ->setData(typ);
	*Target = target;
	ID->setData(_id);
	ApplicationID->setData(_applicationid);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Source";
	param->setUAPString(*&paramname, *&Source);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "ApplicationID";
	param->setUAPLong(*&paramname, *&ApplicationID);
	*paramname = "Target";
	param->setUAPString(*&paramname, *&Target);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbActionsModel::selectAction(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Actions->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentActionName);
		*name = "Source";
		param->getUAPString(*&name, *&currentActionSource);
		*name = "ID";
		param->getUAPLong(*&name, *&currentActionID);
		*name = "ApplicationID";
		param->getUAPLong(*&name, *&currentActionApplicationID);
		*name = "Typ";
		param->getUAPLong(*&name, *&currentActionTyp);
		*name = "Target";
		param->setUAPString(*&name, *&currentActionTarget);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}

bool LB_STDCALL lbActionsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbActionsModel::getActionCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionsModel::hasMoreActions() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionsModel::setNextAction() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
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
	*name = "ApplicationID";
	param->getUAPLong(*&name, *&currentActionApplicationID);
	*name = "Typ";
	param->getUAPLong(*&name, *&currentActionTyp);
	*name = "Target";
	param->getUAPString(*&name, *&currentActionTarget);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionsModel::finishActionIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionsModel::getActionID() {
	return currentActionID->getData();
}

long LB_STDCALL lbActionsModel::getActionApplicationID() {
	return currentActionApplicationID->getData();
}

char*  LB_STDCALL lbActionsModel::getActionName() {
	return currentActionName->charrep();
}

char*  LB_STDCALL lbActionsModel::getActionSource() {
	return currentActionSource->charrep();
}

long LB_STDCALL lbActionsModel::getActionTyp() {
	return currentActionTyp->getData();
}

char* LB_STDCALL lbActionsModel::getActionTarget() {
	return currentActionTarget->charrep();
}

/*...sclass lbPluginActionsModel implementation:0:*/
/*...slbPluginActionsModel:0:*/
class lbPluginActionsModel : public lb_I_PluginImpl {
public:
	lbPluginActionsModel();
	
	virtual ~lbPluginActionsModel();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionsModel, lbPluginActionsModel)

/*...slbErrCodes LB_STDCALL lbPluginActionsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionsModel::lbPluginActionsModel() {
	_CL_VERBOSE << "lbPluginActionsModel::lbPluginActionsModel() called.\n" LOG_
	
	
	;
}

lbPluginActionsModel::~lbPluginActionsModel() {
	_CL_VERBOSE << "lbPluginActionsModel::~lbPluginActionsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbActionsModel* ActionsModel = new lbActionsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionsModel* ActionsModel = new lbActionsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




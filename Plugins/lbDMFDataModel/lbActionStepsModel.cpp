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


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif

#include <lbConfigHook.h>
/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbActionStepsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbActionStepsModel, lbActionStepsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionStepsModel)
	ADD_INTERFACE(lb_I_Action_Steps)
END_IMPLEMENT_LB_UNKNOWN()


lbActionStepsModel::lbActionStepsModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Actions)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTyp)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTarget)
	REQUEST(getModuleInstance(), lb_I_String, currentActionName)
	REQUEST(getModuleInstance(), lb_I_String, currentActionSource)
}

lbActionStepsModel::~lbActionStepsModel() {

}

lbErrCodes LB_STDCALL lbActionStepsModel::setData(lb_I_Unknown*) {
		_CL_LOG << "Error: lbActionStepsModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionStepsModel::addAction(const char* name, long typ, const char* source, long target, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Source)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Typ)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Target)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionStepsModel: " << name LOG_

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

bool  LB_STDCALL lbActionStepsModel::selectAction(long _id) {
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

int  LB_STDCALL lbActionStepsModel::getActionCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionStepsModel::hasMoreActions() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionStepsModel::setNextAction() {
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

void  LB_STDCALL lbActionStepsModel::finishActionIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionStepsModel::getActionID() {
	return currentActionID->getData();
}

char*  LB_STDCALL lbActionStepsModel::getActionName() {
	return currentActionName->charrep();
}

char*  LB_STDCALL lbActionStepsModel::getActionSource() {
	return currentActionSource->charrep();
}

long LB_STDCALL lbActionStepsModel::getActionTyp() {
	return currentActionTyp->getData();
}

long LB_STDCALL lbActionStepsModel::getActionTarget() {
	return currentActionTarget->getData();
}

/*...sclass lbPluginActionStepsModel implementation:0:*/
/*...slbPluginActionStepsModel:0:*/
class lbPluginActionStepsModel : public lb_I_PluginImpl {
public:
	lbPluginActionStepsModel();
	
	virtual ~lbPluginActionStepsModel();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStepsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStepsModel, lbPluginActionStepsModel)

/*...slbErrCodes LB_STDCALL lbPluginActionStepsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionStepsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStepsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionStepsModel::lbPluginActionStepsModel() {
	_CL_VERBOSE << "lbPluginActionStepsModel::lbPluginActionStepsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginActionStepsModel::~lbPluginActionStepsModel() {
	_CL_VERBOSE << "lbPluginActionStepsModel::~lbPluginActionStepsModel() called.\n" LOG_
}

void LB_STDCALL lbPluginActionStepsModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionStepsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbActionStepsModel* ActionsModel = new lbActionStepsModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionStepsModel* ActionsModel = new lbActionStepsModel();
		ActionsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionStepsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions->release(__FILE__, __LINE__);
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




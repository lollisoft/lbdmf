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
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepType)
	REQUEST(getModuleInstance(), lb_I_String, currentActionStepWhat)
	REQUEST(getModuleInstance(), lb_I_String, currentActionStepBezeichnung)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepOrderNo)
		
	REQUEST(getModuleInstance(), lb_I_Long, marked)

	_CL_LOG << "lbActionStepsModel::lbActionStepsModel() called." LOG_
}

lbActionStepsModel::~lbActionStepsModel() {
	_CL_LOG << "lbActionStepsModel::~lbActionStepsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionStepsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionStepsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionStepsModel::addActionStep(const char* bezeichnung, long actionid, long orderNo, long type, const char* what, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)

	UAP_REQUEST(manager.getPtr(), lb_I_String, Bezeichnung)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ActionId)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, OrderNo)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Typ)
	UAP_REQUEST(manager.getPtr(), lb_I_String, What)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionStepsModel: " << bezeichnung LOG_

	*Bezeichnung = bezeichnung;
	ActionId->setData(actionid);
	Typ->setData(type);
	*What = what;
	ID->setData(_id);
	
	*paramname = "Bezeichnung";
	param->setUAPString(*&paramname, *&Bezeichnung);
	*paramname = "ActionId";
	param->setUAPLong(*&paramname, *&ActionId);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "OrderNo";
	param->setUAPLong(*&paramname, *&OrderNo);
	*paramname = "What";
	param->setUAPString(*&paramname, *&What);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

bool LB_STDCALL lbActionStepsModel::ismarked() {
	if (marked->getData() == 1) return true;
	return false;
}

void LB_STDCALL lbActionStepsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionStepsModel::unmark() {
	marked->setData((long) 0);
}

bool  LB_STDCALL lbActionStepsModel::selectActionStep(long _id) {
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
		
		*name = "Bezeichnung";
		param->getUAPString(*&name, *&currentActionStepBezeichnung);
		*name = "ActionId";
		param->getUAPLong(*&name, *&currentActionStepActionID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentActionStepID);
		*name = "OrderNo";
		param->getUAPLong(*&name, *&currentActionStepOrderNo);
		*name = "Typ";
		param->getUAPLong(*&name, *&currentActionStepType);
		*name = "What";
		param->getUAPString(*&name, *&currentActionStepWhat);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbActionStepsModel::getActionStepCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionStepsModel::hasMoreActionSteps() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionStepsModel::setNextActionStep() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Actions->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Bezeichnung";
	param->getUAPString(*&name, *&currentActionStepBezeichnung);
	*name = "ActionId";
	param->getUAPLong(*&name, *&currentActionStepActionID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentActionStepID);
	*name = "OrderNo";
	param->getUAPLong(*&name, *&currentActionStepOrderNo);
	*name = "Typ";
	param->getUAPLong(*&name, *&currentActionStepType);
	*name = "What";
	param->getUAPString(*&name, *&currentActionStepWhat);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionStepsModel::finishActionStepIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionStepsModel::getActionStepID() {
	return currentActionStepID->getData();
}

char*  LB_STDCALL lbActionStepsModel::getActionStepBezeichnung() {
	return currentActionStepBezeichnung->charrep();
}

char*  LB_STDCALL lbActionStepsModel::getActionStepWhat() {
	return currentActionStepWhat->charrep();
}

long LB_STDCALL lbActionStepsModel::getActionStepType() {
	return currentActionStepType->getData();
}

/*...sclass lbPluginActionStepsModel implementation:0:*/
/*...slbPluginActionStepsModel:0:*/
class lbPluginActionStepsModel : public lb_I_PluginImpl {
public:
	lbPluginActionStepsModel();
	
	virtual ~lbPluginActionStepsModel();

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

bool LB_STDCALL lbPluginActionStepsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStepsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
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
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




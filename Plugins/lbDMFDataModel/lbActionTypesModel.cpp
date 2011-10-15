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

#include <lbActionTypesModel.h>

IMPLEMENT_FUNCTOR(instanceOflbActionTypesModel, lbActionTypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionTypesModel)
	ADD_INTERFACE(lb_I_Action_Types)
END_IMPLEMENT_LB_UNKNOWN()


lbActionTypesModel::lbActionTypesModel() {
	

	REQUEST(getModuleInstance(), lb_I_Container, ActionTypes)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionTypesID)
	REQUEST(getModuleInstance(), lb_I_String, currentActionTypesBezeichnung)
	REQUEST(getModuleInstance(), lb_I_String, currentActionTypesHandler)
	REQUEST(getModuleInstance(), lb_I_String, currentActionTypesModule)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbActionTypesModel::lbActionTypesModel() called." LOG_
}

lbActionTypesModel::~lbActionTypesModel() {
	_CL_VERBOSE << "lbActionTypesModel::~lbActionTypesModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionTypesModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionTypesModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void		LB_STDCALL lbActionTypesModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ActionTypes->finishIteration();
	while (hasMoreActionTypes()) {
		setNextActionType();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getActionTypeID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ActionTypes->remove(&key);
			ActionTypes->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionTypesModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ActionTypes->finishIteration();
	while (hasMoreActionTypes()) {
		setNextActionType();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getActionTypeID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ActionTypes->remove(&key);
			ActionTypes->finishIteration();
		}
	}
}


long  LB_STDCALL lbActionTypesModel::addActionTypes(const char* bezeichnung, const char* action_handler , const char* module, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, ActionTypesBezeichnung)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ActionTypesHandler)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ActionTypesModule)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionTypesModel: " << bezeichnung LOG_

	*ActionTypesBezeichnung = bezeichnung;
	*ActionTypesHandler = action_handler;
	*ActionTypesModule = module;
	ID->setData(_id);
	
	*paramname = "ActionTypesBezeichnung";
	param->setUAPString(*&paramname, *&ActionTypesBezeichnung);
	*paramname = "ActionTypesHandler";
	param->setUAPString(*&paramname, *&ActionTypesHandler);
	*paramname = "ActionTypesModule";
	param->setUAPString(*&paramname, *&ActionTypesModule);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ActionTypes->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbActionTypesModel::selectActionType(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = ActionTypes->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*paramname = "ActionTypesBezeichnung";
		param->getUAPString(*&paramname, *&currentActionTypesBezeichnung);
		*paramname = "ActionTypesHandler";
		param->getUAPString(*&paramname, *&currentActionTypesHandler);
		*paramname = "ActionTypesModule";
		param->getUAPString(*&paramname, *&currentActionTypesModule);
		*paramname = "ID";
		param->getUAPLong(*&paramname, *&currentActionTypesID);
		*paramname = "marked";
		param->setUAPLong(*&paramname, *&marked);
		
		return true;
	}
	
	return false;
}

bool LB_STDCALL lbActionTypesModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionTypesModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionTypesModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbActionTypesModel::getActionTypesCount() {
	return ActionTypes->Count();
}

bool  LB_STDCALL lbActionTypesModel::hasMoreActionTypes() {
	return ActionTypes->hasMoreElements();
}

void  LB_STDCALL lbActionTypesModel::setNextActionType() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = ActionTypes->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*paramname = "ActionTypesBezeichnung";
	param->getUAPString(*&paramname, *&currentActionTypesBezeichnung);
	*paramname = "ActionTypesHandler";
	param->getUAPString(*&paramname, *&currentActionTypesHandler);
	*paramname = "ActionTypesModule";
	param->getUAPString(*&paramname, *&currentActionTypesModule);
	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentActionTypesID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
}

void  LB_STDCALL lbActionTypesModel::finishActionTypeIteration() {
	ActionTypes->finishIteration();
}

long LB_STDCALL lbActionTypesModel::getActionTypeID() {
	return currentActionTypesID->getData();
}

char*  LB_STDCALL lbActionTypesModel::getActionTypeBezeichnung() {
	return currentActionTypesBezeichnung->charrep();
}

char*  LB_STDCALL lbActionTypesModel::getActionTypeHandler() {
	return currentActionTypesHandler->charrep();
}

char*  LB_STDCALL lbActionTypesModel::getActionTypeModule() {
	return currentActionTypesModule->charrep();
}

/*...sclass lbPluginActionTypesModel implementation:0:*/
/*...slbPluginActionTypesModel:0:*/
class lbPluginActionTypesModel : public lb_I_PluginImpl {
public:
	lbPluginActionTypesModel();
	
	virtual ~lbPluginActionTypesModel();

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
	
	
	further_lock = 1;
}

lbPluginActionTypesModel::~lbPluginActionTypesModel() {
	_CL_VERBOSE << "lbPluginActionTypesModel::~lbPluginActionTypesModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionTypesModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionTypesModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
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





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
#include <lbInterfaces-lbDMFManager.h>
#include <Generated_EntityModelAction_Types.h>

IMPLEMENT_FUNCTOR(instanceOflbAction_TypesModel, lbAction_TypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbAction_TypesModel)
	ADD_INTERFACE(lb_I_Action_Types)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbAction_TypesModel)

void		LB_STDCALL lbAction_TypesModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbAction_TypesModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbAction_TypesModel::lbAction_TypesModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Action_Types)

    REQUEST(getModuleInstance(), lb_I_String, currentbezeichnung)
    REQUEST(getModuleInstance(), lb_I_String, currentaction_handler)
    REQUEST(getModuleInstance(), lb_I_String, currentmodule)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAction_TypesID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbAction_TypesModel::lbAction_TypesModel() called." LOG_
}

lbAction_TypesModel::~lbAction_TypesModel() {
	_CL_VERBOSE << "lbAction_TypesModel::~lbAction_TypesModel() called." LOG_
}

lbErrCodes LB_STDCALL lbAction_TypesModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbAction_TypesModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbAction_TypesModel::addAction_Types(const char* _bezeichnung, const char* _action_handler, const char* _module,  long _Action_TypesID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __bezeichnung)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __action_handler)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __module)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Action_TypesID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__bezeichnung = _bezeichnung;
    *__action_handler = _action_handler;
    *__module = _module;

	
	__Action_TypesID->setData(_Action_TypesID);

    *paramname = "bezeichnung";
    param->setUAPString(*&paramname, *&__bezeichnung);
    *paramname = "action_handler";
    param->setUAPString(*&paramname, *&__action_handler);
    *paramname = "module";
    param->setUAPString(*&paramname, *&__module);


	*paramname = "Action_TypesID";
	param->setUAPLong(*&paramname, *&__Action_TypesID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Action_TypesID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Action_Types->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbAction_TypesModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Action_Types->finishIteration();
	while (hasMoreAction_Types()) {
		setNextAction_Types();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Types->remove(&key);
			Action_Types->finishIteration();
		}
	}
}

void		LB_STDCALL lbAction_TypesModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Action_Types->finishIteration();
	while (hasMoreAction_Types()) {
		setNextAction_Types();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Types->remove(&key);
			Action_Types->finishIteration();
		}
	}
}

bool LB_STDCALL lbAction_TypesModel::selectAction_Types(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Action_Types->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "action_handler";
    param->getUAPString(*&paramname, *&currentaction_handler);
    *paramname = "module";
    param->getUAPString(*&paramname, *&currentmodule);


		*paramname = "Action_TypesID";
		param->getUAPLong(*&paramname, *&currentAction_TypesID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbAction_TypesModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbAction_TypesModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbAction_TypesModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbAction_TypesModel::getAction_TypesCount() {
	return Action_Types->Count();
}

bool  LB_STDCALL lbAction_TypesModel::hasMoreAction_Types() {
	return (Action_Types->hasMoreElements() == 1);
}

void  LB_STDCALL lbAction_TypesModel::setNextAction_Types() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Action_Types->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "action_handler";
    param->getUAPString(*&paramname, *&currentaction_handler);
    *paramname = "module";
    param->getUAPString(*&paramname, *&currentmodule);

	*paramname = "Action_TypesID";
	param->getUAPLong(*&paramname, *&currentAction_TypesID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbAction_TypesModel::finishAction_TypesIteration() {
	Action_Types->finishIteration();
}

long LB_STDCALL lbAction_TypesModel::get_id() {
	return currentAction_TypesID->getData();
}


char* LB_STDCALL lbAction_TypesModel::get_bezeichnung() {
	return currentbezeichnung->charrep();
}

char* LB_STDCALL lbAction_TypesModel::get_action_handler() {
	return currentaction_handler->charrep();
}

char* LB_STDCALL lbAction_TypesModel::get_module() {
	return currentmodule->charrep();
}


class lbPluginAction_TypesModel : public lb_I_PluginImpl {
public:
	lbPluginAction_TypesModel();
	
	virtual ~lbPluginAction_TypesModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_TypesModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_TypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_TypesModel, lbPluginAction_TypesModel)

lbErrCodes LB_STDCALL lbPluginAction_TypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_TypesModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_TypesModel::lbPluginAction_TypesModel() {
	_CL_VERBOSE << "lbPluginAction_TypesModel::lbPluginAction_TypesModel() called.\n" LOG_
}

lbPluginAction_TypesModel::~lbPluginAction_TypesModel() {
	_CL_VERBOSE << "lbPluginAction_TypesModel::~lbPluginAction_TypesModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_TypesModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_TypesModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_TypesModel::initialize() {
}
	
bool LB_STDCALL lbPluginAction_TypesModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModel == NULL) {
		lbAction_TypesModel* Action_TypesModel = new lbAction_TypesModel();
		
	
		QI(Action_TypesModel, lb_I_Unknown, ukAction_TypesModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_TypesModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbAction_TypesModel* Action_TypesModel = new lbAction_TypesModel();
		
	
		QI(Action_TypesModel, lb_I_Unknown, ukAction_TypesModel)
	}
	
	lb_I_Unknown* r = ukAction_TypesModel.getPtr();
	ukAction_TypesModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_TypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_TypesModel != NULL) {
                ukAction_TypesModel--;
                ukAction_TypesModel.resetPtr();
        }
}

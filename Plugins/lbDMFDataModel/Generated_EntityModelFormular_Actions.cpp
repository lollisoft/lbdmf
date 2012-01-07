
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
#include <Generated_EntityModelFormular_Actions.h>

IMPLEMENT_FUNCTOR(instanceOflbFormular_ActionsModel, lbFormular_ActionsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormular_ActionsModel)
	ADD_INTERFACE(lb_I_Formular_Actions)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbFormular_ActionsModel)

void		LB_STDCALL lbFormular_ActionsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbFormular_ActionsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbFormular_ActionsModel::lbFormular_ActionsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formular_Actions)

    REQUEST(getModuleInstance(), lb_I_String, currentevent)
    REQUEST(getModuleInstance(), lb_I_Long, currentaction)
    REQUEST(getModuleInstance(), lb_I_Long, currentformular)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormular_ActionsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbFormular_ActionsModel::lbFormular_ActionsModel() called." LOG_
}

lbFormular_ActionsModel::~lbFormular_ActionsModel() {
	_CL_VERBOSE << "lbFormular_ActionsModel::~lbFormular_ActionsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbFormular_ActionsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbFormular_ActionsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormular_ActionsModel::addFormular_Actions(const char* _event, long _action, long _formular,  long _Formular_ActionsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __event)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __action)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formular)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Formular_ActionsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__event = _event;
    __action->setData(_action);
    __formular->setData(_formular);

	
	__Formular_ActionsID->setData(_Formular_ActionsID);

    *paramname = "event";
    param->setUAPString(*&paramname, *&__event);
    *paramname = "action";
    param->setUAPLong(*&paramname, *&__action);
    *paramname = "formular";
    param->setUAPLong(*&paramname, *&__formular);


	*paramname = "Formular_ActionsID";
	param->setUAPLong(*&paramname, *&__Formular_ActionsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Formular_ActionsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formular_Actions->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbFormular_ActionsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Actions->finishIteration();
	while (hasMoreFormular_Actions()) {
		setNextFormular_Actions();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Actions->remove(&key);
			Formular_Actions->finishIteration();
		}
	}
}

void		LB_STDCALL lbFormular_ActionsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Actions->finishIteration();
	while (hasMoreFormular_Actions()) {
		setNextFormular_Actions();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Actions->remove(&key);
			Formular_Actions->finishIteration();
		}
	}
}

bool LB_STDCALL lbFormular_ActionsModel::selectFormular_Actions(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formular_Actions->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "event";
    param->getUAPString(*&paramname, *&currentevent);
    *paramname = "action";
    param->getUAPLong(*&paramname, *&currentaction);
    *paramname = "formular";
    param->getUAPLong(*&paramname, *&currentformular);


		*paramname = "Formular_ActionsID";
		param->getUAPLong(*&paramname, *&currentFormular_ActionsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbFormular_ActionsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbFormular_ActionsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbFormular_ActionsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbFormular_ActionsModel::getFormular_ActionsCount() {
	return Formular_Actions->Count();
}

bool  LB_STDCALL lbFormular_ActionsModel::hasMoreFormular_Actions() {
	return (Formular_Actions->hasMoreElements() == 1);
}

void  LB_STDCALL lbFormular_ActionsModel::setNextFormular_Actions() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formular_Actions->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "event";
    param->getUAPString(*&paramname, *&currentevent);
    *paramname = "action";
    param->getUAPLong(*&paramname, *&currentaction);
    *paramname = "formular";
    param->getUAPLong(*&paramname, *&currentformular);

	*paramname = "Formular_ActionsID";
	param->getUAPLong(*&paramname, *&currentFormular_ActionsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbFormular_ActionsModel::finishFormular_ActionsIteration() {
	Formular_Actions->finishIteration();
}

long LB_STDCALL lbFormular_ActionsModel::get_id() {
	return currentFormular_ActionsID->getData();
}


char* LB_STDCALL lbFormular_ActionsModel::get_event() {
	return currentevent->charrep();
}

long LB_STDCALL lbFormular_ActionsModel::get_action() {
	return currentaction->getData();
}

long LB_STDCALL lbFormular_ActionsModel::get_formular() {
	return currentformular->getData();
}


class lbPluginFormular_ActionsModel : public lb_I_PluginImpl {
public:
	lbPluginFormular_ActionsModel();
	
	virtual ~lbPluginFormular_ActionsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_ActionsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_ActionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_ActionsModel, lbPluginFormular_ActionsModel)

lbErrCodes LB_STDCALL lbPluginFormular_ActionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_ActionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_ActionsModel::lbPluginFormular_ActionsModel() {
	_CL_VERBOSE << "lbPluginFormular_ActionsModel::lbPluginFormular_ActionsModel() called.\n" LOG_
}

lbPluginFormular_ActionsModel::~lbPluginFormular_ActionsModel() {
	_CL_VERBOSE << "lbPluginFormular_ActionsModel::~lbPluginFormular_ActionsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_ActionsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_ActionsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_ActionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_ActionsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModel == NULL) {
		lbFormular_ActionsModel* Formular_ActionsModel = new lbFormular_ActionsModel();
		
	
		QI(Formular_ActionsModel, lb_I_Unknown, ukFormular_ActionsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_ActionsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormular_ActionsModel* Formular_ActionsModel = new lbFormular_ActionsModel();
		
	
		QI(Formular_ActionsModel, lb_I_Unknown, ukFormular_ActionsModel)
	}
	
	lb_I_Unknown* r = ukFormular_ActionsModel.getPtr();
	ukFormular_ActionsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_ActionsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_ActionsModel != NULL) {
                ukFormular_ActionsModel--;
                ukFormular_ActionsModel.resetPtr();
        }
}

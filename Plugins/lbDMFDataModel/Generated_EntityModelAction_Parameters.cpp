
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
#include <Generated_EntityModelAction_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOflbAction_ParametersModel, lbAction_ParametersModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbAction_ParametersModel)
	ADD_INTERFACE(lb_I_Action_Parameters)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbAction_ParametersModel)

void		LB_STDCALL lbAction_ParametersModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbAction_ParametersModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbAction_ParametersModel::lbAction_ParametersModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Action_Parameters)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentvalue)
    REQUEST(getModuleInstance(), lb_I_String, currentinterface)
    REQUEST(getModuleInstance(), lb_I_String, currentdescription)
    REQUEST(getModuleInstance(), lb_I_Long, currentactionid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAction_ParametersID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbAction_ParametersModel::lbAction_ParametersModel() called." LOG_
}

lbAction_ParametersModel::~lbAction_ParametersModel() {
	_CL_VERBOSE << "lbAction_ParametersModel::~lbAction_ParametersModel() called." LOG_
}

lbErrCodes LB_STDCALL lbAction_ParametersModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbAction_ParametersModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbAction_ParametersModel::addAction_Parameters(const char* _name, const char* _value, const char* _interface, const char* _description, long _actionid,  long _Action_ParametersID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __value)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __interface)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __actionid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Action_ParametersID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__name = _name;
    *__value = _value;
    *__interface = _interface;
    *__description = _description;
    __actionid->setData(_actionid);

	
	__Action_ParametersID->setData(_Action_ParametersID);

    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "value";
    param->setUAPString(*&paramname, *&__value);
    *paramname = "interface";
    param->setUAPString(*&paramname, *&__interface);
    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);
    *paramname = "actionid";
    param->setUAPLong(*&paramname, *&__actionid);


	*paramname = "Action_ParametersID";
	param->setUAPLong(*&paramname, *&__Action_ParametersID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Action_ParametersID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Action_Parameters->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbAction_ParametersModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Action_Parameters->finishIteration();
	while (hasMoreAction_Parameters()) {
		setNextAction_Parameters();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Parameters->remove(&key);
			Action_Parameters->finishIteration();
		}
	}
}

void		LB_STDCALL lbAction_ParametersModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Action_Parameters->finishIteration();
	while (hasMoreAction_Parameters()) {
		setNextAction_Parameters();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Action_Parameters->remove(&key);
			Action_Parameters->finishIteration();
		}
	}
}

bool LB_STDCALL lbAction_ParametersModel::selectAction_Parameters(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Action_Parameters->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "value";
    param->getUAPString(*&paramname, *&currentvalue);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);


		*paramname = "Action_ParametersID";
		param->getUAPLong(*&paramname, *&currentAction_ParametersID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbAction_ParametersModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbAction_ParametersModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbAction_ParametersModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbAction_ParametersModel::getAction_ParametersCount() {
	return Action_Parameters->Count();
}

bool  LB_STDCALL lbAction_ParametersModel::hasMoreAction_Parameters() {
	return (Action_Parameters->hasMoreElements() == 1);
}

void  LB_STDCALL lbAction_ParametersModel::setNextAction_Parameters() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Action_Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "value";
    param->getUAPString(*&paramname, *&currentvalue);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);

	*paramname = "Action_ParametersID";
	param->getUAPLong(*&paramname, *&currentAction_ParametersID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbAction_ParametersModel::finishAction_ParametersIteration() {
	Action_Parameters->finishIteration();
}

long LB_STDCALL lbAction_ParametersModel::get_id() {
	return currentAction_ParametersID->getData();
}


char* LB_STDCALL lbAction_ParametersModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL lbAction_ParametersModel::get_value() {
	return currentvalue->charrep();
}

char* LB_STDCALL lbAction_ParametersModel::get_interface() {
	return currentinterface->charrep();
}

char* LB_STDCALL lbAction_ParametersModel::get_description() {
	return currentdescription->charrep();
}

long LB_STDCALL lbAction_ParametersModel::get_actionid() {
	return currentactionid->getData();
}


class lbPluginAction_ParametersModel : public lb_I_PluginImpl {
public:
	lbPluginAction_ParametersModel();
	
	virtual ~lbPluginAction_ParametersModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_ParametersModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_ParametersModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_ParametersModel, lbPluginAction_ParametersModel)

lbErrCodes LB_STDCALL lbPluginAction_ParametersModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_ParametersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_ParametersModel::lbPluginAction_ParametersModel() {
	_CL_VERBOSE << "lbPluginAction_ParametersModel::lbPluginAction_ParametersModel() called.\n" LOG_
}

lbPluginAction_ParametersModel::~lbPluginAction_ParametersModel() {
	_CL_VERBOSE << "lbPluginAction_ParametersModel::~lbPluginAction_ParametersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_ParametersModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_ParametersModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_ParametersModel::initialize() {
}
	
bool LB_STDCALL lbPluginAction_ParametersModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModel == NULL) {
		lbAction_ParametersModel* Action_ParametersModel = new lbAction_ParametersModel();
		
	
		QI(Action_ParametersModel, lb_I_Unknown, ukAction_ParametersModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_ParametersModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbAction_ParametersModel* Action_ParametersModel = new lbAction_ParametersModel();
		
	
		QI(Action_ParametersModel, lb_I_Unknown, ukAction_ParametersModel)
	}
	
	lb_I_Unknown* r = ukAction_ParametersModel.getPtr();
	ukAction_ParametersModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_ParametersModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_ParametersModel != NULL) {
                ukAction_ParametersModel--;
                ukAction_ParametersModel.resetPtr();
        }
}

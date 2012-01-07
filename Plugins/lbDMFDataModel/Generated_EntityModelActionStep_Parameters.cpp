
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
#include <Generated_EntityModelActionStep_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOflbActionStep_ParametersModel, lbActionStep_ParametersModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionStep_ParametersModel)
	ADD_INTERFACE(lb_I_ActionStep_Parameters)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbActionStep_ParametersModel)

void		LB_STDCALL lbActionStep_ParametersModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionStep_ParametersModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbActionStep_ParametersModel::lbActionStep_ParametersModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ActionStep_Parameters)

    REQUEST(getModuleInstance(), lb_I_String, currentdescription)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentvalue)
    REQUEST(getModuleInstance(), lb_I_String, currentinterface)
    REQUEST(getModuleInstance(), lb_I_Long, currentaction_step_id)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStep_ParametersID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbActionStep_ParametersModel::lbActionStep_ParametersModel() called." LOG_
}

lbActionStep_ParametersModel::~lbActionStep_ParametersModel() {
	_CL_VERBOSE << "lbActionStep_ParametersModel::~lbActionStep_ParametersModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionStep_ParametersModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionStep_ParametersModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionStep_ParametersModel::addActionStep_Parameters(const char* _description, const char* _name, const char* _value, const char* _interface, long _action_step_id,  long _ActionStep_ParametersID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __value)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __interface)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __action_step_id)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ActionStep_ParametersID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__description = _description;
    *__name = _name;
    *__value = _value;
    *__interface = _interface;
    __action_step_id->setData(_action_step_id);

	
	__ActionStep_ParametersID->setData(_ActionStep_ParametersID);

    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "value";
    param->setUAPString(*&paramname, *&__value);
    *paramname = "interface";
    param->setUAPString(*&paramname, *&__interface);
    *paramname = "action_step_id";
    param->setUAPLong(*&paramname, *&__action_step_id);


	*paramname = "ActionStep_ParametersID";
	param->setUAPLong(*&paramname, *&__ActionStep_ParametersID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ActionStep_ParametersID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ActionStep_Parameters->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbActionStep_ParametersModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ActionStep_Parameters->finishIteration();
	while (hasMoreActionStep_Parameters()) {
		setNextActionStep_Parameters();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ActionStep_Parameters->remove(&key);
			ActionStep_Parameters->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionStep_ParametersModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ActionStep_Parameters->finishIteration();
	while (hasMoreActionStep_Parameters()) {
		setNextActionStep_Parameters();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ActionStep_Parameters->remove(&key);
			ActionStep_Parameters->finishIteration();
		}
	}
}

bool LB_STDCALL lbActionStep_ParametersModel::selectActionStep_Parameters(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ActionStep_Parameters->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "value";
    param->getUAPString(*&paramname, *&currentvalue);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "action_step_id";
    param->getUAPLong(*&paramname, *&currentaction_step_id);


		*paramname = "ActionStep_ParametersID";
		param->getUAPLong(*&paramname, *&currentActionStep_ParametersID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbActionStep_ParametersModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionStep_ParametersModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionStep_ParametersModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbActionStep_ParametersModel::getActionStep_ParametersCount() {
	return ActionStep_Parameters->Count();
}

bool  LB_STDCALL lbActionStep_ParametersModel::hasMoreActionStep_Parameters() {
	return (ActionStep_Parameters->hasMoreElements() == 1);
}

void  LB_STDCALL lbActionStep_ParametersModel::setNextActionStep_Parameters() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ActionStep_Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "value";
    param->getUAPString(*&paramname, *&currentvalue);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "action_step_id";
    param->getUAPLong(*&paramname, *&currentaction_step_id);

	*paramname = "ActionStep_ParametersID";
	param->getUAPLong(*&paramname, *&currentActionStep_ParametersID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbActionStep_ParametersModel::finishActionStep_ParametersIteration() {
	ActionStep_Parameters->finishIteration();
}

long LB_STDCALL lbActionStep_ParametersModel::get_id() {
	return currentActionStep_ParametersID->getData();
}


char* LB_STDCALL lbActionStep_ParametersModel::get_description() {
	return currentdescription->charrep();
}

char* LB_STDCALL lbActionStep_ParametersModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL lbActionStep_ParametersModel::get_value() {
	return currentvalue->charrep();
}

char* LB_STDCALL lbActionStep_ParametersModel::get_interface() {
	return currentinterface->charrep();
}

long LB_STDCALL lbActionStep_ParametersModel::get_action_step_id() {
	return currentaction_step_id->getData();
}


class lbPluginActionStep_ParametersModel : public lb_I_PluginImpl {
public:
	lbPluginActionStep_ParametersModel();
	
	virtual ~lbPluginActionStep_ParametersModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionStep_ParametersModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStep_ParametersModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStep_ParametersModel, lbPluginActionStep_ParametersModel)

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStep_ParametersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionStep_ParametersModel::lbPluginActionStep_ParametersModel() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersModel::lbPluginActionStep_ParametersModel() called.\n" LOG_
}

lbPluginActionStep_ParametersModel::~lbPluginActionStep_ParametersModel() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersModel::~lbPluginActionStep_ParametersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStep_ParametersModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStep_ParametersModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionStep_ParametersModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModel == NULL) {
		lbActionStep_ParametersModel* ActionStep_ParametersModel = new lbActionStep_ParametersModel();
		
	
		QI(ActionStep_ParametersModel, lb_I_Unknown, ukActionStep_ParametersModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionStep_ParametersModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionStep_ParametersModel* ActionStep_ParametersModel = new lbActionStep_ParametersModel();
		
	
		QI(ActionStep_ParametersModel, lb_I_Unknown, ukActionStep_ParametersModel)
	}
	
	lb_I_Unknown* r = ukActionStep_ParametersModel.getPtr();
	ukActionStep_ParametersModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionStep_ParametersModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionStep_ParametersModel != NULL) {
                ukActionStep_ParametersModel--;
                ukActionStep_ParametersModel.resetPtr();
        }
}

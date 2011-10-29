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
#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#include <lbConfigHook.h>
/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbInterfaces-lbDMFManager.h>
#include <lbParameters.h>

IMPLEMENT_FUNCTOR(instanceOflbActionParameters, lbActionParameters)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionParameters)
	ADD_INTERFACE(lb_I_Action_Parameters)
END_IMPLEMENT_LB_UNKNOWN()


void		LB_STDCALL lbActionParameters::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionParameters::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}


lbActionParameters::lbActionParameters() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Parameters)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterName)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterValue)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterDescription)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterInterface)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbActionParameters::lbActionParameters() called." LOG_
}

lbActionParameters::~lbActionParameters() {
	_CL_VERBOSE << "lbActionParameters::~lbActionParameters() called." LOG_
}

lbErrCodes LB_STDCALL lbActionParameters::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionParameters::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionParameters::addActionParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Interface)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ActionID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	_CL_VERBOSE << "Add a parameter to lbActionParameters: " << name LOG_

	*Description = description;
	*Interface = _interface;
	*Name = name;
	*Value = value;
	ID->setData(_id);
	ActionID->setData(actionid);

	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "Interface";
	param->setUAPString(*&paramname, *&Interface);
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Value";
	param->setUAPString(*&paramname, *&Value);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "ActionID";
	param->setUAPLong(*&paramname, *&ActionID);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)

	Parameters->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbActionParameters::selectActionParameter(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Parameters->getElement(&key);

	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)

		*name = "Description";
		param->getUAPString(*&name, *&currentParameterDescription);
		*name = "Interface";
		param->getUAPString(*&name, *&currentParameterInterface);
		*name = "Name";
		param->getUAPString(*&name, *&currentParameterName);
		*name = "Value";
		param->getUAPString(*&name, *&currentParameterValue);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "ActionID";
		param->getUAPLong(*&name, *&currentActionID);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);

		return true;
	}

	return false;
}

void LB_STDCALL lbActionParameters::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionParameters::unmark() {
	marked->setData((long) 0);
}

bool LB_STDCALL lbActionParameters::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

int  LB_STDCALL lbActionParameters::getActionParametersCount() {
	return Parameters->Count();
}

void		LB_STDCALL lbActionParameters::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Parameters->finishIteration();
	while (hasMoreActionParameters()) {
		setNextActionParameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());

			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)

			Parameters->remove(&key);
			Parameters->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionParameters::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Parameters->finishIteration();
	while (hasMoreActionParameters()) {
		setNextActionParameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());

			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)

			Parameters->remove(&key);
			Parameters->finishIteration();
		}
	}
}

bool  LB_STDCALL lbActionParameters::hasMoreActionParameters() {
	return Parameters->hasMoreElements();
}

void  LB_STDCALL lbActionParameters::setNextActionParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)

	uk = Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)

	*name = "Description";
	param->getUAPString(*&name, *&currentParameterDescription);
	*name = "Interface";
	param->getUAPString(*&name, *&currentParameterInterface);
	*name = "Name";
	param->getUAPString(*&name, *&currentParameterName);
	*name = "Value";
	param->getUAPString(*&name, *&currentParameterValue);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "ActionID";
	param->getUAPLong(*&name, *&currentActionID);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionParameters::finishActionParameterIteration() {
	Parameters->finishIteration();
}

long LB_STDCALL lbActionParameters::getID() {
	return currentID->getData();
}

char*  LB_STDCALL lbActionParameters::getActionParameterName() {
	return currentParameterName->charrep();
}

char*  LB_STDCALL lbActionParameters::getActionParameterValue() {
	return currentParameterValue->charrep();
}

char*  LB_STDCALL lbActionParameters::getActionParameterDescription() {
	return currentParameterDescription->charrep();
}

char*  LB_STDCALL lbActionParameters::getActionParameterInterface() {
	return currentParameterInterface->charrep();
}

long LB_STDCALL lbActionParameters::getActionParameterActionID() {
	return currentActionID->getData();
}

IMPLEMENT_FUNCTOR(instanceOflbActionStepParameters, lbActionStepParameters)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionStepParameters)
ADD_INTERFACE(lb_I_ActionStep_Parameters)
END_IMPLEMENT_LB_UNKNOWN()


void		LB_STDCALL lbActionStepParameters::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionStepParameters::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbActionStepParameters::lbActionStepParameters() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Parameters)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterName)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterValue)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterDescription)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterInterface)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbActionStepParameters::lbActionStepParameters() called." LOG_
}

lbActionStepParameters::~lbActionStepParameters() {
	_CL_VERBOSE << "lbActionStepParameters::~lbActionStepParameters() called." LOG_
}

lbErrCodes LB_STDCALL lbActionStepParameters::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionStepParameters::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionStepParameters::addActionStepParameter(const char* description, const char* name, const char* value, const char* _interface, long actionid, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Interface)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ActionID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	_CL_VERBOSE << "Add a parameter to lbActionStepParameters: " << name LOG_

	*Description = description;
	*Interface = _interface;
	*Name = name;
	*Value = value;
	ID->setData(_id);
	ActionID->setData(actionid);

	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "Interface";
	param->setUAPString(*&paramname, *&Interface);
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Value";
	param->setUAPString(*&paramname, *&Value);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "ActionID";
	param->setUAPLong(*&paramname, *&ActionID);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)

	Parameters->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbActionStepParameters::selectActionStepParameter(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Parameters->getElement(&key);

	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)

		*name = "Description";
		param->getUAPString(*&name, *&currentParameterDescription);
		*name = "Interface";
		param->getUAPString(*&name, *&currentParameterInterface);
		*name = "Name";
		param->getUAPString(*&name, *&currentParameterName);
		*name = "Value";
		param->getUAPString(*&name, *&currentParameterValue);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "ActionID";
		param->getUAPLong(*&name, *&currentActionID);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);

		return true;
	}

	return false;
}

void LB_STDCALL lbActionStepParameters::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionStepParameters::unmark() {
	marked->setData((long) 0);
}

bool LB_STDCALL lbActionStepParameters::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

int  LB_STDCALL lbActionStepParameters::getActionStepParametersCount() {
	return Parameters->Count();
}

void		LB_STDCALL lbActionStepParameters::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Parameters->finishIteration();
	while (hasMoreActionStepParameters()) {
		setNextActionStepParameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());

			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)

			Parameters->remove(&key);
			Parameters->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionStepParameters::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Parameters->finishIteration();
	while (hasMoreActionStepParameters()) {
		setNextActionStepParameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());

			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)

			Parameters->remove(&key);
			Parameters->finishIteration();
		}
	}
}

bool  LB_STDCALL lbActionStepParameters::hasMoreActionStepParameters() {
	return Parameters->hasMoreElements();
}

void  LB_STDCALL lbActionStepParameters::setNextActionStepParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)

	uk = Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)

	*name = "Description";
	param->getUAPString(*&name, *&currentParameterDescription);
	*name = "Interface";
	param->getUAPString(*&name, *&currentParameterInterface);
	*name = "Name";
	param->getUAPString(*&name, *&currentParameterName);
	*name = "Value";
	param->getUAPString(*&name, *&currentParameterValue);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "ActionID";
	param->getUAPLong(*&name, *&currentActionID);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionStepParameters::finishActionStepParameterIteration() {
	Parameters->finishIteration();
}

long LB_STDCALL lbActionStepParameters::getID() {
	return currentID->getData();
}

char*  LB_STDCALL lbActionStepParameters::getActionStepParameterName() {
	return currentParameterName->charrep();
}

char*  LB_STDCALL lbActionStepParameters::getActionStepParameterValue() {
	return currentParameterValue->charrep();
}

char*  LB_STDCALL lbActionStepParameters::getActionStepParameterDescription() {
	return currentParameterDescription->charrep();
}

char*  LB_STDCALL lbActionStepParameters::getActionStepParameterInterface() {
	return currentParameterInterface->charrep();
}

long LB_STDCALL lbActionStepParameters::getActionStepParameterActionID() {
	return currentActionID->getData();
}

/*...sclass lbPluginActionParameters implementation:0:*/
/*...slbPluginActionParameters:0:*/
class lbPluginActionParameters : public lb_I_PluginImpl {
public:
	lbPluginActionParameters();

	virtual ~lbPluginActionParameters();

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

	UAP(lb_I_Unknown, ukActionParameters)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionParameters)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionParameters, lbPluginActionParameters)

/*...slbErrCodes LB_STDCALL lbPluginActionParameters\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionParameters::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionParameters::setData(...) called.\n" LOG_

	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionParameters::lbPluginActionParameters() {
	_CL_VERBOSE << "lbPluginActionParameters::lbPluginActionParameters() called.\n" LOG_
	
	
	;
}

lbPluginActionParameters::~lbPluginActionParameters() {
	_CL_VERBOSE << "lbPluginActionParameters::~lbPluginActionParameters() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionParameters::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionParameters::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionParameters::initialize() {
}

bool LB_STDCALL lbPluginActionParameters::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionParameters\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionParameters::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionParameters == NULL) {
		lbActionParameters* ActionParameters = new lbActionParameters();
		

		QI(ActionParameters, lb_I_Unknown, ukActionParameters)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return ukActionParameters.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionParameters\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionParameters::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionParameters == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbActionParameters* ActionParameters = new lbActionParameters();
		

		QI(ActionParameters, lb_I_Unknown, ukActionParameters)
	}

	lb_I_Unknown* r = ukActionParameters.getPtr();
	ukActionParameters.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionParameters::releaseImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionParameters != NULL) {
		ukActionParameters--;
		ukActionParameters.resetPtr();
	}
}
/*...e*/
/*...e*/

/*...sclass lbPluginActionStepParameters implementation:0:*/
/*...slbPluginActionStepParameters:0:*/
class lbPluginActionStepParameters : public lb_I_PluginImpl {
public:
	lbPluginActionStepParameters();

	virtual ~lbPluginActionStepParameters();

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

	UAP(lb_I_Unknown, ukActionStepParameters)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStepParameters)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStepParameters, lbPluginActionStepParameters)

/*...slbErrCodes LB_STDCALL lbPluginActionStepParameters\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionStepParameters::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStepParameters::setData(...) called.\n" LOG_

	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionStepParameters::lbPluginActionStepParameters() {
	_CL_VERBOSE << "lbPluginActionStepParameters::lbPluginActionStepParameters() called.\n" LOG_
	
	
	;
}

lbPluginActionStepParameters::~lbPluginActionStepParameters() {
	_CL_VERBOSE << "lbPluginActionStepParameters::~lbPluginActionStepParameters() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStepParameters::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStepParameters::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStepParameters::initialize() {
}

bool LB_STDCALL lbPluginActionStepParameters::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepParameters\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepParameters::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStepParameters == NULL) {
		lbActionStepParameters* ActionStepParameters = new lbActionStepParameters();
		

		QI(ActionStepParameters, lb_I_Unknown, ukActionStepParameters)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return ukActionStepParameters.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepParameters\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepParameters::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStepParameters == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbActionStepParameters* ActionStepParameters = new lbActionStepParameters();
		

		QI(ActionStepParameters, lb_I_Unknown, ukActionStepParameters)
	}

	lb_I_Unknown* r = ukActionStepParameters.getPtr();
	ukActionStepParameters.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionStepParameters::releaseImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStepParameters != NULL) {
		ukActionStepParameters--;
		ukActionStepParameters.resetPtr();
	}
}
/*...e*/
/*...e*/



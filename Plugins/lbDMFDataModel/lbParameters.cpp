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

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>
#include <lbdmfdatamodel-module.h>

#include <lbParameters.h>

IMPLEMENT_FUNCTOR(instanceOflbFormularParameters, lbFormularParameters)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormularParameters)
	ADD_INTERFACE(lb_I_FormularParameter)
END_IMPLEMENT_LB_UNKNOWN()


lbFormularParameters::lbFormularParameters() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Parameters)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterName)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterValue)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularID)
}

lbFormularParameters::~lbFormularParameters() {

}

lbErrCodes LB_STDCALL lbFormularParameters::setData(lb_I_Unknown*) {
		_CL_LOG << "Error: lbFormularParameters::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormularParameters::addParameter(const char* name, const char* value, long formular_id, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Value)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, FormularID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbFormularParameters: " << name LOG_

	*Name = name;
	*Value = value;
	ID->setData(_id);
	FormularID->setData(formular_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Value";
	param->setUAPString(*&paramname, *&Value);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "FormularID";
	param->setUAPLong(*&paramname, *&FormularID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Parameters->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbFormularParameters::selectParameter(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Parameters->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentParameterName);
		*name = "Value";
		param->getUAPString(*&name, *&currentParameterValue);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "FormularID";
		param->getUAPLong(*&name, *&currentFormularID);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbFormularParameters::getParameterCount() {
	return Parameters->Count();
}

bool  LB_STDCALL lbFormularParameters::hasMoreParameters() {
	return Parameters->hasMoreElements();
}

void  LB_STDCALL lbFormularParameters::setNextParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentParameterName);
	*name = "Value";
	param->getUAPString(*&name, *&currentParameterValue);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "FormularID";
	param->getUAPLong(*&name, *&currentFormularID);
}

void  LB_STDCALL lbFormularParameters::finishParameterIteration() {
	Parameters->finishIteration();
}

long LB_STDCALL lbFormularParameters::getParameterID() {
	return currentID->getData();
}

char*  LB_STDCALL lbFormularParameters::getParameterName() {
	return currentParameterName->charrep();
}

char*  LB_STDCALL lbFormularParameters::getParameter(const char* name, long formular_id) {
	finishParameterIteration();
	
	while (hasMoreParameters()) {
		setNextParameter();
		
		if ((strcmp(getParameterName(), name) == 0) && (getFormularID() == formular_id)) {
			finishParameterIteration();
			return getParameterValue();
		}
	}
	
	return "";
}

char*  LB_STDCALL lbFormularParameters::getParameterValue() {
	return currentParameterValue->charrep();
}

long LB_STDCALL lbFormularParameters::getFormularID() {
	return currentFormularID->getData();
}

IMPLEMENT_FUNCTOR(instanceOflbApplicationParameters, lbApplicationParameters)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplicationParameters)
	ADD_INTERFACE(lb_I_ApplicationParameter)
END_IMPLEMENT_LB_UNKNOWN()


lbApplicationParameters::lbApplicationParameters() {
	ref = STARTREF;
	_CL_LOG << "lbApplicationParameters::lbApplicationParameters() called." LOG_
	REQUEST(getModuleInstance(), lb_I_Container, Parameters)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterName)
	REQUEST(getModuleInstance(), lb_I_String, currentParameterValue)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationID)
}

lbApplicationParameters::~lbApplicationParameters() {
	_CL_LOG << "lbApplicationParameters::~lbApplicationParameters() called." LOG_
}

lbErrCodes LB_STDCALL lbApplicationParameters::setData(lb_I_Unknown*) {
		_CL_LOG << "Error: lbApplicationParameters::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbApplicationParameters::addParameter(const char* name, const char* value, long application_id, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Value)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ApplicationID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbApplicationParameters: " << name LOG_

	*Name = name;
	*Value = value;
	ID->setData(_id);
	ApplicationID->setData(application_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Value";
	param->setUAPString(*&paramname, *&Value);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "ApplicationID";
	param->setUAPLong(*&paramname, *&ApplicationID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Parameters->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbApplicationParameters::selectParameter(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Parameters->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentParameterName);
		*name = "Value";
		param->getUAPString(*&name, *&currentParameterValue);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "ApplicationID";
		param->getUAPLong(*&name, *&currentApplicationID);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbApplicationParameters::getParameterCount() {
	return Parameters->Count();
}

bool  LB_STDCALL lbApplicationParameters::hasMoreParameters() {
	return Parameters->hasMoreElements();
}

void  LB_STDCALL lbApplicationParameters::setNextParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Parameters->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentParameterName);
	*name = "Value";
	param->getUAPString(*&name, *&currentParameterValue);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "ApplicationID";
	param->getUAPLong(*&name, *&currentApplicationID);
}

void  LB_STDCALL lbApplicationParameters::finishParameterIteration() {
	Parameters->finishIteration();
}

long LB_STDCALL lbApplicationParameters::getParameterID() {
	return currentID->getData();
}

char*  LB_STDCALL lbApplicationParameters::getParameterName() {
	return currentParameterName->charrep();
}

char*  LB_STDCALL lbApplicationParameters::getParameter(const char* name, long application_id) {
	finishParameterIteration();
	
	while (hasMoreParameters()) {
		setNextParameter();
		
		if ((strcmp(getParameterName(), name) == 0) && (getApplicationID() == application_id)) {
			finishParameterIteration();
			return getParameterValue();
		}
	}
	
	return "";
}

char*  LB_STDCALL lbApplicationParameters::getParameterValue() {
	return currentParameterValue->charrep();
}

long LB_STDCALL lbApplicationParameters::getApplicationID() {
	return currentApplicationID->getData();
}



/*...sclass lbPluginUsersModel implementation:0:*/
/*...slbPluginUsersModel:0:*/
class lbPluginFormularParameters : public virtual lb_I_PluginImpl {
public:
	lbPluginFormularParameters();
	
	virtual ~lbPluginFormularParameters();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularParameters)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularParameters)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularParameters, lbPluginFormularParameters)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginFormularParameters::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFormularParameters::lbPluginFormularParameters() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginFormularParameters::~lbPluginFormularParameters() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
}

void LB_STDCALL lbPluginFormularParameters::initialize() {
}
	
bool LB_STDCALL lbPluginFormularParameters::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularParameters::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameters == NULL) {
		lbFormularParameters* Users_ApplicationModel = new lbFormularParameters();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukFormularParameters)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularParameters.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularParameters::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameters == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormularParameters* Users_ApplicationModel = new lbFormularParameters();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukFormularParameters)
	}
	
	lb_I_Unknown* r = ukFormularParameters.getPtr();
	ukFormularParameters.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFormularParameters::releaseImplementation() {
}
/*...e*/
/*...e*/

/*...sclass lbPluginApplicationParameters implementation:0:*/
/*...slbPluginApplicationParameters:0:*/
class lbPluginApplicationParameters : public virtual lb_I_PluginImpl {
public:
	lbPluginApplicationParameters();
	
	virtual ~lbPluginApplicationParameters();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationParameters)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationParameters)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationParameters, lbPluginApplicationParameters)

/*...slbErrCodes LB_STDCALL lbPluginApplicationParameters\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginApplicationParameters::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationParameters::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginApplicationParameters::lbPluginApplicationParameters() {
	_CL_VERBOSE << "lbPluginApplicationParameters::lbPluginApplicationParameters() called.\n" LOG_
	ref = STARTREF;
}

lbPluginApplicationParameters::~lbPluginApplicationParameters() {
	_CL_VERBOSE << "lbPluginApplicationParameters::~lbPluginApplicationParameters() called.\n" LOG_
}

void LB_STDCALL lbPluginApplicationParameters::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationParameters::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationParameters\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationParameters::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameters == NULL) {
		lbApplicationParameters* ApplicationParameters = new lbApplicationParameters();
		ApplicationParameters->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ApplicationParameters, lb_I_Unknown, ukApplicationParameters)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationParameters.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationParameters\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationParameters::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameters == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbApplicationParameters* ApplicationParameters = new lbApplicationParameters();
		ApplicationParameters->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(ApplicationParameters, lb_I_Unknown, ukApplicationParameters)
	}
	
	lb_I_Unknown* r = ukApplicationParameters.getPtr();
	ukApplicationParameters.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginApplicationParameters::releaseImplementation() {
}
/*...e*/
/*...e*/



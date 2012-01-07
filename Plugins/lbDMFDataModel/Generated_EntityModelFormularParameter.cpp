
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
#include <Generated_EntityModelFormularParameter.h>

IMPLEMENT_FUNCTOR(instanceOflbFormularParameterModel, lbFormularParameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormularParameterModel)
	ADD_INTERFACE(lb_I_FormularParameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbFormularParameterModel)

void		LB_STDCALL lbFormularParameterModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbFormularParameterModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbFormularParameterModel::lbFormularParameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, FormularParameter)

    REQUEST(getModuleInstance(), lb_I_String, currentparametervalue)
    REQUEST(getModuleInstance(), lb_I_String, currentparametername)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularParameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbFormularParameterModel::lbFormularParameterModel() called." LOG_
}

lbFormularParameterModel::~lbFormularParameterModel() {
	_CL_VERBOSE << "lbFormularParameterModel::~lbFormularParameterModel() called." LOG_
}

lbErrCodes LB_STDCALL lbFormularParameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbFormularParameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormularParameterModel::addFormularParameter(const char* _parametervalue, const char* _parametername, long _formularid,  long _FormularParameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametervalue)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametername)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormularParameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__parametervalue = _parametervalue;
    *__parametername = _parametername;
    __formularid->setData(_formularid);

	
	__FormularParameterID->setData(_FormularParameterID);

    *paramname = "parametervalue";
    param->setUAPString(*&paramname, *&__parametervalue);
    *paramname = "parametername";
    param->setUAPString(*&paramname, *&__parametername);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "FormularParameterID";
	param->setUAPLong(*&paramname, *&__FormularParameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormularParameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FormularParameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbFormularParameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	FormularParameter->finishIteration();
	while (hasMoreFormularParameter()) {
		setNextFormularParameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularParameter->remove(&key);
			FormularParameter->finishIteration();
		}
	}
}

void		LB_STDCALL lbFormularParameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	FormularParameter->finishIteration();
	while (hasMoreFormularParameter()) {
		setNextFormularParameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularParameter->remove(&key);
			FormularParameter->finishIteration();
		}
	}
}

bool LB_STDCALL lbFormularParameterModel::selectFormularParameter(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = FormularParameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "FormularParameterID";
		param->getUAPLong(*&paramname, *&currentFormularParameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbFormularParameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbFormularParameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbFormularParameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbFormularParameterModel::getFormularParameterCount() {
	return FormularParameter->Count();
}

bool  LB_STDCALL lbFormularParameterModel::hasMoreFormularParameter() {
	return (FormularParameter->hasMoreElements() == 1);
}

void  LB_STDCALL lbFormularParameterModel::setNextFormularParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = FormularParameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "FormularParameterID";
	param->getUAPLong(*&paramname, *&currentFormularParameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbFormularParameterModel::finishFormularParameterIteration() {
	FormularParameter->finishIteration();
}

long LB_STDCALL lbFormularParameterModel::get_id() {
	return currentFormularParameterID->getData();
}


char* LB_STDCALL lbFormularParameterModel::get_parametervalue() {
	return currentparametervalue->charrep();
}

char* LB_STDCALL lbFormularParameterModel::get_parametername() {
	return currentparametername->charrep();
}

long LB_STDCALL lbFormularParameterModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginFormularParameterModel : public lb_I_PluginImpl {
public:
	lbPluginFormularParameterModel();
	
	virtual ~lbPluginFormularParameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularParameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularParameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularParameterModel, lbPluginFormularParameterModel)

lbErrCodes LB_STDCALL lbPluginFormularParameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularParameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularParameterModel::lbPluginFormularParameterModel() {
	_CL_VERBOSE << "lbPluginFormularParameterModel::lbPluginFormularParameterModel() called.\n" LOG_
}

lbPluginFormularParameterModel::~lbPluginFormularParameterModel() {
	_CL_VERBOSE << "lbPluginFormularParameterModel::~lbPluginFormularParameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularParameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularParameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularParameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularParameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModel == NULL) {
		lbFormularParameterModel* FormularParameterModel = new lbFormularParameterModel();
		
	
		QI(FormularParameterModel, lb_I_Unknown, ukFormularParameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularParameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormularParameterModel* FormularParameterModel = new lbFormularParameterModel();
		
	
		QI(FormularParameterModel, lb_I_Unknown, ukFormularParameterModel)
	}
	
	lb_I_Unknown* r = ukFormularParameterModel.getPtr();
	ukFormularParameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularParameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularParameterModel != NULL) {
                ukFormularParameterModel--;
                ukFormularParameterModel.resetPtr();
        }
}

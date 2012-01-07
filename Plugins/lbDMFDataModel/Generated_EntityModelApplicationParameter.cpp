
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
#include <Generated_EntityModelApplicationParameter.h>

IMPLEMENT_FUNCTOR(instanceOflbApplicationParameterModel, lbApplicationParameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplicationParameterModel)
	ADD_INTERFACE(lb_I_ApplicationParameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbApplicationParameterModel)

void		LB_STDCALL lbApplicationParameterModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbApplicationParameterModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbApplicationParameterModel::lbApplicationParameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ApplicationParameter)

    REQUEST(getModuleInstance(), lb_I_String, currentparametername)
    REQUEST(getModuleInstance(), lb_I_String, currentparametervalue)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationParameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbApplicationParameterModel::lbApplicationParameterModel() called." LOG_
}

lbApplicationParameterModel::~lbApplicationParameterModel() {
	_CL_VERBOSE << "lbApplicationParameterModel::~lbApplicationParameterModel() called." LOG_
}

lbErrCodes LB_STDCALL lbApplicationParameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbApplicationParameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbApplicationParameterModel::addApplicationParameter(const char* _parametername, const char* _parametervalue, long _anwendungid,  long _ApplicationParameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametername)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametervalue)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ApplicationParameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__parametername = _parametername;
    *__parametervalue = _parametervalue;
    __anwendungid->setData(_anwendungid);

	
	__ApplicationParameterID->setData(_ApplicationParameterID);

    *paramname = "parametername";
    param->setUAPString(*&paramname, *&__parametername);
    *paramname = "parametervalue";
    param->setUAPString(*&paramname, *&__parametervalue);
    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);


	*paramname = "ApplicationParameterID";
	param->setUAPLong(*&paramname, *&__ApplicationParameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ApplicationParameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ApplicationParameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbApplicationParameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ApplicationParameter->finishIteration();
	while (hasMoreApplicationParameter()) {
		setNextApplicationParameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ApplicationParameter->remove(&key);
			ApplicationParameter->finishIteration();
		}
	}
}

void		LB_STDCALL lbApplicationParameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ApplicationParameter->finishIteration();
	while (hasMoreApplicationParameter()) {
		setNextApplicationParameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ApplicationParameter->remove(&key);
			ApplicationParameter->finishIteration();
		}
	}
}

bool LB_STDCALL lbApplicationParameterModel::selectApplicationParameter(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ApplicationParameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);


		*paramname = "ApplicationParameterID";
		param->getUAPLong(*&paramname, *&currentApplicationParameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbApplicationParameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbApplicationParameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbApplicationParameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbApplicationParameterModel::getApplicationParameterCount() {
	return ApplicationParameter->Count();
}

bool  LB_STDCALL lbApplicationParameterModel::hasMoreApplicationParameter() {
	return (ApplicationParameter->hasMoreElements() == 1);
}

void  LB_STDCALL lbApplicationParameterModel::setNextApplicationParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ApplicationParameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);

	*paramname = "ApplicationParameterID";
	param->getUAPLong(*&paramname, *&currentApplicationParameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbApplicationParameterModel::finishApplicationParameterIteration() {
	ApplicationParameter->finishIteration();
}

long LB_STDCALL lbApplicationParameterModel::get_id() {
	return currentApplicationParameterID->getData();
}


char* LB_STDCALL lbApplicationParameterModel::get_parametername() {
	return currentparametername->charrep();
}

char* LB_STDCALL lbApplicationParameterModel::get_parametervalue() {
	return currentparametervalue->charrep();
}

long LB_STDCALL lbApplicationParameterModel::get_anwendungid() {
	return currentanwendungid->getData();
}


class lbPluginApplicationParameterModel : public lb_I_PluginImpl {
public:
	lbPluginApplicationParameterModel();
	
	virtual ~lbPluginApplicationParameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationParameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationParameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationParameterModel, lbPluginApplicationParameterModel)

lbErrCodes LB_STDCALL lbPluginApplicationParameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationParameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationParameterModel::lbPluginApplicationParameterModel() {
	_CL_VERBOSE << "lbPluginApplicationParameterModel::lbPluginApplicationParameterModel() called.\n" LOG_
}

lbPluginApplicationParameterModel::~lbPluginApplicationParameterModel() {
	_CL_VERBOSE << "lbPluginApplicationParameterModel::~lbPluginApplicationParameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationParameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationParameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationParameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationParameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationParameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameterModel == NULL) {
		lbApplicationParameterModel* ApplicationParameterModel = new lbApplicationParameterModel();
		
	
		QI(ApplicationParameterModel, lb_I_Unknown, ukApplicationParameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationParameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationParameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbApplicationParameterModel* ApplicationParameterModel = new lbApplicationParameterModel();
		
	
		QI(ApplicationParameterModel, lb_I_Unknown, ukApplicationParameterModel)
	}
	
	lb_I_Unknown* r = ukApplicationParameterModel.getPtr();
	ukApplicationParameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationParameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationParameterModel != NULL) {
                ukApplicationParameterModel--;
                ukApplicationParameterModel.resetPtr();
        }
}

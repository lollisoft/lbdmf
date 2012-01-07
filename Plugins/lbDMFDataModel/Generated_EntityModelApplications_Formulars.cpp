
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
#include <Generated_EntityModelApplications_Formulars.h>

IMPLEMENT_FUNCTOR(instanceOflbApplications_FormularsModel, lbApplications_FormularsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplications_FormularsModel)
	ADD_INTERFACE(lb_I_Applications_Formulars)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbApplications_FormularsModel)

void		LB_STDCALL lbApplications_FormularsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbApplications_FormularsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbApplications_FormularsModel::lbApplications_FormularsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Applications_Formulars)

    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentApplications_FormularsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbApplications_FormularsModel::lbApplications_FormularsModel() called." LOG_
}

lbApplications_FormularsModel::~lbApplications_FormularsModel() {
	_CL_VERBOSE << "lbApplications_FormularsModel::~lbApplications_FormularsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbApplications_FormularsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbApplications_FormularsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbApplications_FormularsModel::addApplications_Formulars(long _anwendungid, long _formularid,  long _Applications_FormularsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Applications_FormularsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __anwendungid->setData(_anwendungid);
    __formularid->setData(_formularid);

	
	__Applications_FormularsID->setData(_Applications_FormularsID);

    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "Applications_FormularsID";
	param->setUAPLong(*&paramname, *&__Applications_FormularsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Applications_FormularsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Applications_Formulars->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbApplications_FormularsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Applications_Formulars->finishIteration();
	while (hasMoreApplications_Formulars()) {
		setNextApplications_Formulars();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications_Formulars->remove(&key);
			Applications_Formulars->finishIteration();
		}
	}
}

void		LB_STDCALL lbApplications_FormularsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Applications_Formulars->finishIteration();
	while (hasMoreApplications_Formulars()) {
		setNextApplications_Formulars();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications_Formulars->remove(&key);
			Applications_Formulars->finishIteration();
		}
	}
}

bool LB_STDCALL lbApplications_FormularsModel::selectApplications_Formulars(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Applications_Formulars->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "Applications_FormularsID";
		param->getUAPLong(*&paramname, *&currentApplications_FormularsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbApplications_FormularsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbApplications_FormularsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbApplications_FormularsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbApplications_FormularsModel::getApplications_FormularsCount() {
	return Applications_Formulars->Count();
}

bool  LB_STDCALL lbApplications_FormularsModel::hasMoreApplications_Formulars() {
	return (Applications_Formulars->hasMoreElements() == 1);
}

void  LB_STDCALL lbApplications_FormularsModel::setNextApplications_Formulars() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Applications_Formulars->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "Applications_FormularsID";
	param->getUAPLong(*&paramname, *&currentApplications_FormularsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbApplications_FormularsModel::finishApplications_FormularsIteration() {
	Applications_Formulars->finishIteration();
}

long LB_STDCALL lbApplications_FormularsModel::get_id() {
	return currentApplications_FormularsID->getData();
}


long LB_STDCALL lbApplications_FormularsModel::get_anwendungid() {
	return currentanwendungid->getData();
}

long LB_STDCALL lbApplications_FormularsModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginApplications_FormularsModel : public lb_I_PluginImpl {
public:
	lbPluginApplications_FormularsModel();
	
	virtual ~lbPluginApplications_FormularsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplications_FormularsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplications_FormularsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplications_FormularsModel, lbPluginApplications_FormularsModel)

lbErrCodes LB_STDCALL lbPluginApplications_FormularsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplications_FormularsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplications_FormularsModel::lbPluginApplications_FormularsModel() {
	_CL_VERBOSE << "lbPluginApplications_FormularsModel::lbPluginApplications_FormularsModel() called.\n" LOG_
}

lbPluginApplications_FormularsModel::~lbPluginApplications_FormularsModel() {
	_CL_VERBOSE << "lbPluginApplications_FormularsModel::~lbPluginApplications_FormularsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplications_FormularsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplications_FormularsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplications_FormularsModel::initialize() {
}
	
bool LB_STDCALL lbPluginApplications_FormularsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModel == NULL) {
		lbApplications_FormularsModel* Applications_FormularsModel = new lbApplications_FormularsModel();
		
	
		QI(Applications_FormularsModel, lb_I_Unknown, ukApplications_FormularsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplications_FormularsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplications_FormularsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplications_FormularsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbApplications_FormularsModel* Applications_FormularsModel = new lbApplications_FormularsModel();
		
	
		QI(Applications_FormularsModel, lb_I_Unknown, ukApplications_FormularsModel)
	}
	
	lb_I_Unknown* r = ukApplications_FormularsModel.getPtr();
	ukApplications_FormularsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplications_FormularsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplications_FormularsModel != NULL) {
                ukApplications_FormularsModel--;
                ukApplications_FormularsModel.resetPtr();
        }
}

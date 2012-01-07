
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
#include <Generated_EntityModelReportParameters.h>

IMPLEMENT_FUNCTOR(instanceOflbReportParametersModel, lbReportParametersModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportParametersModel)
	ADD_INTERFACE(lb_I_ReportParameters)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbReportParametersModel)

void		LB_STDCALL lbReportParametersModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbReportParametersModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbReportParametersModel::lbReportParametersModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ReportParameters)

    REQUEST(getModuleInstance(), lb_I_Integer, currentvalue)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_Long, currentreportid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportParametersID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbReportParametersModel::lbReportParametersModel() called." LOG_
}

lbReportParametersModel::~lbReportParametersModel() {
	_CL_VERBOSE << "lbReportParametersModel::~lbReportParametersModel() called." LOG_
}

lbErrCodes LB_STDCALL lbReportParametersModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbReportParametersModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbReportParametersModel::addReportParameters(int _value, const char* _name, long _reportid,  long _ReportParametersID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __value)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __reportid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportParametersID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __value->setData(_value);
    *__name = _name;
    __reportid->setData(_reportid);

	
	__ReportParametersID->setData(_ReportParametersID);

    *paramname = "value";
    param->setUAPInteger(*&paramname, *&__value);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "reportid";
    param->setUAPLong(*&paramname, *&__reportid);


	*paramname = "ReportParametersID";
	param->setUAPLong(*&paramname, *&__ReportParametersID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportParametersID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportParameters->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbReportParametersModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ReportParameters->finishIteration();
	while (hasMoreReportParameters()) {
		setNextReportParameters();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportParameters->remove(&key);
			ReportParameters->finishIteration();
		}
	}
}

void		LB_STDCALL lbReportParametersModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ReportParameters->finishIteration();
	while (hasMoreReportParameters()) {
		setNextReportParameters();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportParameters->remove(&key);
			ReportParameters->finishIteration();
		}
	}
}

bool LB_STDCALL lbReportParametersModel::selectReportParameters(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportParameters->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "value";
    param->getUAPInteger(*&paramname, *&currentvalue);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);


		*paramname = "ReportParametersID";
		param->getUAPLong(*&paramname, *&currentReportParametersID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbReportParametersModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbReportParametersModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbReportParametersModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbReportParametersModel::getReportParametersCount() {
	return ReportParameters->Count();
}

bool  LB_STDCALL lbReportParametersModel::hasMoreReportParameters() {
	return (ReportParameters->hasMoreElements() == 1);
}

void  LB_STDCALL lbReportParametersModel::setNextReportParameters() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ReportParameters->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "value";
    param->getUAPInteger(*&paramname, *&currentvalue);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);

	*paramname = "ReportParametersID";
	param->getUAPLong(*&paramname, *&currentReportParametersID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbReportParametersModel::finishReportParametersIteration() {
	ReportParameters->finishIteration();
}

long LB_STDCALL lbReportParametersModel::get_id() {
	return currentReportParametersID->getData();
}


int LB_STDCALL lbReportParametersModel::get_value() {
	return currentvalue->getData();
}

char* LB_STDCALL lbReportParametersModel::get_name() {
	return currentname->charrep();
}

long LB_STDCALL lbReportParametersModel::get_reportid() {
	return currentreportid->getData();
}


class lbPluginReportParametersModel : public lb_I_PluginImpl {
public:
	lbPluginReportParametersModel();
	
	virtual ~lbPluginReportParametersModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportParametersModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportParametersModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportParametersModel, lbPluginReportParametersModel)

lbErrCodes LB_STDCALL lbPluginReportParametersModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportParametersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportParametersModel::lbPluginReportParametersModel() {
	_CL_VERBOSE << "lbPluginReportParametersModel::lbPluginReportParametersModel() called.\n" LOG_
}

lbPluginReportParametersModel::~lbPluginReportParametersModel() {
	_CL_VERBOSE << "lbPluginReportParametersModel::~lbPluginReportParametersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportParametersModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportParametersModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportParametersModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportParametersModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModel == NULL) {
		lbReportParametersModel* ReportParametersModel = new lbReportParametersModel();
		
	
		QI(ReportParametersModel, lb_I_Unknown, ukReportParametersModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportParametersModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportParametersModel* ReportParametersModel = new lbReportParametersModel();
		
	
		QI(ReportParametersModel, lb_I_Unknown, ukReportParametersModel)
	}
	
	lb_I_Unknown* r = ukReportParametersModel.getPtr();
	ukReportParametersModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportParametersModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportParametersModel != NULL) {
                ukReportParametersModel--;
                ukReportParametersModel.resetPtr();
        }
}

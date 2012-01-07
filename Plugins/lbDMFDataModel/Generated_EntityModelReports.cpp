
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
#include <Generated_EntityModelReports.h>

IMPLEMENT_FUNCTOR(instanceOflbReportsModel, lbReportsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportsModel)
	ADD_INTERFACE(lb_I_Reports)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbReportsModel)

void		LB_STDCALL lbReportsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbReportsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbReportsModel::lbReportsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Reports)

    REQUEST(getModuleInstance(), lb_I_String, currentdescription)
    REQUEST(getModuleInstance(), lb_I_String, currentname)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbReportsModel::lbReportsModel() called." LOG_
}

lbReportsModel::~lbReportsModel() {
	_CL_VERBOSE << "lbReportsModel::~lbReportsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbReportsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbReportsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbReportsModel::addReports(const char* _description, const char* _name,  long _ReportsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__description = _description;
    *__name = _name;

	
	__ReportsID->setData(_ReportsID);

    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);


	*paramname = "ReportsID";
	param->setUAPLong(*&paramname, *&__ReportsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Reports->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbReportsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Reports->finishIteration();
	while (hasMoreReports()) {
		setNextReports();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reports->remove(&key);
			Reports->finishIteration();
		}
	}
}

void		LB_STDCALL lbReportsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Reports->finishIteration();
	while (hasMoreReports()) {
		setNextReports();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reports->remove(&key);
			Reports->finishIteration();
		}
	}
}

bool LB_STDCALL lbReportsModel::selectReports(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Reports->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);


		*paramname = "ReportsID";
		param->getUAPLong(*&paramname, *&currentReportsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbReportsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbReportsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbReportsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbReportsModel::getReportsCount() {
	return Reports->Count();
}

bool  LB_STDCALL lbReportsModel::hasMoreReports() {
	return (Reports->hasMoreElements() == 1);
}

void  LB_STDCALL lbReportsModel::setNextReports() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Reports->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);

	*paramname = "ReportsID";
	param->getUAPLong(*&paramname, *&currentReportsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbReportsModel::finishReportsIteration() {
	Reports->finishIteration();
}

long LB_STDCALL lbReportsModel::get_id() {
	return currentReportsID->getData();
}


char* LB_STDCALL lbReportsModel::get_description() {
	return currentdescription->charrep();
}

char* LB_STDCALL lbReportsModel::get_name() {
	return currentname->charrep();
}


class lbPluginReportsModel : public lb_I_PluginImpl {
public:
	lbPluginReportsModel();
	
	virtual ~lbPluginReportsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportsModel, lbPluginReportsModel)

lbErrCodes LB_STDCALL lbPluginReportsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportsModel::lbPluginReportsModel() {
	_CL_VERBOSE << "lbPluginReportsModel::lbPluginReportsModel() called.\n" LOG_
}

lbPluginReportsModel::~lbPluginReportsModel() {
	_CL_VERBOSE << "lbPluginReportsModel::~lbPluginReportsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportsModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportsModel == NULL) {
		lbReportsModel* ReportsModel = new lbReportsModel();
		
	
		QI(ReportsModel, lb_I_Unknown, ukReportsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportsModel* ReportsModel = new lbReportsModel();
		
	
		QI(ReportsModel, lb_I_Unknown, ukReportsModel)
	}
	
	lb_I_Unknown* r = ukReportsModel.getPtr();
	ukReportsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportsModel != NULL) {
                ukReportsModel--;
                ukReportsModel.resetPtr();
        }
}

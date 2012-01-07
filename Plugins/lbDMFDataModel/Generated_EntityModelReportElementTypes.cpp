
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
#include <Generated_EntityModelReportElementTypes.h>

IMPLEMENT_FUNCTOR(instanceOflbReportElementTypesModel, lbReportElementTypesModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportElementTypesModel)
	ADD_INTERFACE(lb_I_ReportElementTypes)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbReportElementTypesModel)

void		LB_STDCALL lbReportElementTypesModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbReportElementTypesModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbReportElementTypesModel::lbReportElementTypesModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ReportElementTypes)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentdescription)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportElementTypesID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbReportElementTypesModel::lbReportElementTypesModel() called." LOG_
}

lbReportElementTypesModel::~lbReportElementTypesModel() {
	_CL_VERBOSE << "lbReportElementTypesModel::~lbReportElementTypesModel() called." LOG_
}

lbErrCodes LB_STDCALL lbReportElementTypesModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbReportElementTypesModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbReportElementTypesModel::addReportElementTypes(const char* _name, const char* _description,  long _ReportElementTypesID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportElementTypesID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__name = _name;
    *__description = _description;

	
	__ReportElementTypesID->setData(_ReportElementTypesID);

    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);


	*paramname = "ReportElementTypesID";
	param->setUAPLong(*&paramname, *&__ReportElementTypesID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportElementTypesID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportElementTypes->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbReportElementTypesModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ReportElementTypes->finishIteration();
	while (hasMoreReportElementTypes()) {
		setNextReportElementTypes();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportElementTypes->remove(&key);
			ReportElementTypes->finishIteration();
		}
	}
}

void		LB_STDCALL lbReportElementTypesModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ReportElementTypes->finishIteration();
	while (hasMoreReportElementTypes()) {
		setNextReportElementTypes();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportElementTypes->remove(&key);
			ReportElementTypes->finishIteration();
		}
	}
}

bool LB_STDCALL lbReportElementTypesModel::selectReportElementTypes(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportElementTypes->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);


		*paramname = "ReportElementTypesID";
		param->getUAPLong(*&paramname, *&currentReportElementTypesID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbReportElementTypesModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbReportElementTypesModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbReportElementTypesModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbReportElementTypesModel::getReportElementTypesCount() {
	return ReportElementTypes->Count();
}

bool  LB_STDCALL lbReportElementTypesModel::hasMoreReportElementTypes() {
	return (ReportElementTypes->hasMoreElements() == 1);
}

void  LB_STDCALL lbReportElementTypesModel::setNextReportElementTypes() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ReportElementTypes->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);

	*paramname = "ReportElementTypesID";
	param->getUAPLong(*&paramname, *&currentReportElementTypesID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbReportElementTypesModel::finishReportElementTypesIteration() {
	ReportElementTypes->finishIteration();
}

long LB_STDCALL lbReportElementTypesModel::get_id() {
	return currentReportElementTypesID->getData();
}


char* LB_STDCALL lbReportElementTypesModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL lbReportElementTypesModel::get_description() {
	return currentdescription->charrep();
}


class lbPluginReportElementTypesModel : public lb_I_PluginImpl {
public:
	lbPluginReportElementTypesModel();
	
	virtual ~lbPluginReportElementTypesModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportElementTypesModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementTypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementTypesModel, lbPluginReportElementTypesModel)

lbErrCodes LB_STDCALL lbPluginReportElementTypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementTypesModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementTypesModel::lbPluginReportElementTypesModel() {
	_CL_VERBOSE << "lbPluginReportElementTypesModel::lbPluginReportElementTypesModel() called.\n" LOG_
}

lbPluginReportElementTypesModel::~lbPluginReportElementTypesModel() {
	_CL_VERBOSE << "lbPluginReportElementTypesModel::~lbPluginReportElementTypesModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementTypesModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementTypesModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementTypesModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementTypesModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModel == NULL) {
		lbReportElementTypesModel* ReportElementTypesModel = new lbReportElementTypesModel();
		
	
		QI(ReportElementTypesModel, lb_I_Unknown, ukReportElementTypesModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementTypesModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportElementTypesModel* ReportElementTypesModel = new lbReportElementTypesModel();
		
	
		QI(ReportElementTypesModel, lb_I_Unknown, ukReportElementTypesModel)
	}
	
	lb_I_Unknown* r = ukReportElementTypesModel.getPtr();
	ukReportElementTypesModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementTypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementTypesModel != NULL) {
                ukReportElementTypesModel--;
                ukReportElementTypesModel.resetPtr();
        }
}

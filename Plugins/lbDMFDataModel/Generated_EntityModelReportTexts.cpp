
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
#include <Generated_EntityModelReportTexts.h>

IMPLEMENT_FUNCTOR(instanceOflbReportTextsModel, lbReportTextsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportTextsModel)
	ADD_INTERFACE(lb_I_ReportTexts)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbReportTextsModel)

void		LB_STDCALL lbReportTextsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbReportTextsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbReportTextsModel::lbReportTextsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ReportTexts)

    REQUEST(getModuleInstance(), lb_I_Integer, currentline)
    REQUEST(getModuleInstance(), lb_I_String, currenttext)
    REQUEST(getModuleInstance(), lb_I_Long, currentelementid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportTextsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbReportTextsModel::lbReportTextsModel() called." LOG_
}

lbReportTextsModel::~lbReportTextsModel() {
	_CL_VERBOSE << "lbReportTextsModel::~lbReportTextsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbReportTextsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbReportTextsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbReportTextsModel::addReportTexts(int _line, const char* _text, long _elementid,  long _ReportTextsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __line)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __text)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __elementid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportTextsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __line->setData(_line);
    *__text = _text;
    __elementid->setData(_elementid);

	
	__ReportTextsID->setData(_ReportTextsID);

    *paramname = "line";
    param->setUAPInteger(*&paramname, *&__line);
    *paramname = "text";
    param->setUAPString(*&paramname, *&__text);
    *paramname = "elementid";
    param->setUAPLong(*&paramname, *&__elementid);


	*paramname = "ReportTextsID";
	param->setUAPLong(*&paramname, *&__ReportTextsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportTextsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportTexts->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbReportTextsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ReportTexts->finishIteration();
	while (hasMoreReportTexts()) {
		setNextReportTexts();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportTexts->remove(&key);
			ReportTexts->finishIteration();
		}
	}
}

void		LB_STDCALL lbReportTextsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ReportTexts->finishIteration();
	while (hasMoreReportTexts()) {
		setNextReportTexts();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportTexts->remove(&key);
			ReportTexts->finishIteration();
		}
	}
}

bool LB_STDCALL lbReportTextsModel::selectReportTexts(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportTexts->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "line";
    param->getUAPInteger(*&paramname, *&currentline);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);
    *paramname = "elementid";
    param->getUAPLong(*&paramname, *&currentelementid);


		*paramname = "ReportTextsID";
		param->getUAPLong(*&paramname, *&currentReportTextsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbReportTextsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbReportTextsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbReportTextsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbReportTextsModel::getReportTextsCount() {
	return ReportTexts->Count();
}

bool  LB_STDCALL lbReportTextsModel::hasMoreReportTexts() {
	return (ReportTexts->hasMoreElements() == 1);
}

void  LB_STDCALL lbReportTextsModel::setNextReportTexts() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ReportTexts->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "line";
    param->getUAPInteger(*&paramname, *&currentline);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);
    *paramname = "elementid";
    param->getUAPLong(*&paramname, *&currentelementid);

	*paramname = "ReportTextsID";
	param->getUAPLong(*&paramname, *&currentReportTextsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbReportTextsModel::finishReportTextsIteration() {
	ReportTexts->finishIteration();
}

long LB_STDCALL lbReportTextsModel::get_id() {
	return currentReportTextsID->getData();
}


int LB_STDCALL lbReportTextsModel::get_line() {
	return currentline->getData();
}

char* LB_STDCALL lbReportTextsModel::get_text() {
	return currenttext->charrep();
}

long LB_STDCALL lbReportTextsModel::get_elementid() {
	return currentelementid->getData();
}


class lbPluginReportTextsModel : public lb_I_PluginImpl {
public:
	lbPluginReportTextsModel();
	
	virtual ~lbPluginReportTextsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportTextsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportTextsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportTextsModel, lbPluginReportTextsModel)

lbErrCodes LB_STDCALL lbPluginReportTextsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportTextsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportTextsModel::lbPluginReportTextsModel() {
	_CL_VERBOSE << "lbPluginReportTextsModel::lbPluginReportTextsModel() called.\n" LOG_
}

lbPluginReportTextsModel::~lbPluginReportTextsModel() {
	_CL_VERBOSE << "lbPluginReportTextsModel::~lbPluginReportTextsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportTextsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportTextsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportTextsModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportTextsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModel == NULL) {
		lbReportTextsModel* ReportTextsModel = new lbReportTextsModel();
		
	
		QI(ReportTextsModel, lb_I_Unknown, ukReportTextsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportTextsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportTextsModel* ReportTextsModel = new lbReportTextsModel();
		
	
		QI(ReportTextsModel, lb_I_Unknown, ukReportTextsModel)
	}
	
	lb_I_Unknown* r = ukReportTextsModel.getPtr();
	ukReportTextsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportTextsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportTextsModel != NULL) {
                ukReportTextsModel--;
                ukReportTextsModel.resetPtr();
        }
}

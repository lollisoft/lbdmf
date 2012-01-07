
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
#include <Generated_EntityModelReportElements.h>

IMPLEMENT_FUNCTOR(instanceOflbReportElementsModel, lbReportElementsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportElementsModel)
	ADD_INTERFACE(lb_I_ReportElements)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbReportElementsModel)

void		LB_STDCALL lbReportElementsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbReportElementsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbReportElementsModel::lbReportElementsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ReportElements)

    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentdescription)
    REQUEST(getModuleInstance(), lb_I_Integer, currentx)
    REQUEST(getModuleInstance(), lb_I_Integer, currenty)
    REQUEST(getModuleInstance(), lb_I_Integer, currentw)
    REQUEST(getModuleInstance(), lb_I_Integer, currenth)
    REQUEST(getModuleInstance(), lb_I_Long, currentreportid)
    REQUEST(getModuleInstance(), lb_I_Long, currenttyp)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportElementsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbReportElementsModel::lbReportElementsModel() called." LOG_
}

lbReportElementsModel::~lbReportElementsModel() {
	_CL_VERBOSE << "lbReportElementsModel::~lbReportElementsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbReportElementsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbReportElementsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbReportElementsModel::addReportElements(const char* _name, const char* _description, int _x, int _y, int _w, int _h, long _reportid, long _typ,  long _ReportElementsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)
    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __x)
    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __y)
    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __w)
    UAP_REQUEST(getModuleInstance(), lb_I_Integer, __h)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __reportid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __typ)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportElementsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__name = _name;
    *__description = _description;
    __x->setData(_x);
    __y->setData(_y);
    __w->setData(_w);
    __h->setData(_h);
    __reportid->setData(_reportid);
    __typ->setData(_typ);

	
	__ReportElementsID->setData(_ReportElementsID);

    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);
    *paramname = "x";
    param->setUAPInteger(*&paramname, *&__x);
    *paramname = "y";
    param->setUAPInteger(*&paramname, *&__y);
    *paramname = "w";
    param->setUAPInteger(*&paramname, *&__w);
    *paramname = "h";
    param->setUAPInteger(*&paramname, *&__h);
    *paramname = "reportid";
    param->setUAPLong(*&paramname, *&__reportid);
    *paramname = "typ";
    param->setUAPLong(*&paramname, *&__typ);


	*paramname = "ReportElementsID";
	param->setUAPLong(*&paramname, *&__ReportElementsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportElementsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportElements->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbReportElementsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ReportElements->finishIteration();
	while (hasMoreReportElements()) {
		setNextReportElements();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportElements->remove(&key);
			ReportElements->finishIteration();
		}
	}
}

void		LB_STDCALL lbReportElementsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ReportElements->finishIteration();
	while (hasMoreReportElements()) {
		setNextReportElements();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ReportElements->remove(&key);
			ReportElements->finishIteration();
		}
	}
}

bool LB_STDCALL lbReportElementsModel::selectReportElements(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportElements->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "x";
    param->getUAPInteger(*&paramname, *&currentx);
    *paramname = "y";
    param->getUAPInteger(*&paramname, *&currenty);
    *paramname = "w";
    param->getUAPInteger(*&paramname, *&currentw);
    *paramname = "h";
    param->getUAPInteger(*&paramname, *&currenth);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);


		*paramname = "ReportElementsID";
		param->getUAPLong(*&paramname, *&currentReportElementsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbReportElementsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbReportElementsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbReportElementsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbReportElementsModel::getReportElementsCount() {
	return ReportElements->Count();
}

bool  LB_STDCALL lbReportElementsModel::hasMoreReportElements() {
	return (ReportElements->hasMoreElements() == 1);
}

void  LB_STDCALL lbReportElementsModel::setNextReportElements() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ReportElements->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "x";
    param->getUAPInteger(*&paramname, *&currentx);
    *paramname = "y";
    param->getUAPInteger(*&paramname, *&currenty);
    *paramname = "w";
    param->getUAPInteger(*&paramname, *&currentw);
    *paramname = "h";
    param->getUAPInteger(*&paramname, *&currenth);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);

	*paramname = "ReportElementsID";
	param->getUAPLong(*&paramname, *&currentReportElementsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbReportElementsModel::finishReportElementsIteration() {
	ReportElements->finishIteration();
}

long LB_STDCALL lbReportElementsModel::get_id() {
	return currentReportElementsID->getData();
}


char* LB_STDCALL lbReportElementsModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL lbReportElementsModel::get_description() {
	return currentdescription->charrep();
}

int LB_STDCALL lbReportElementsModel::get_x() {
	return currentx->getData();
}

int LB_STDCALL lbReportElementsModel::get_y() {
	return currenty->getData();
}

int LB_STDCALL lbReportElementsModel::get_w() {
	return currentw->getData();
}

int LB_STDCALL lbReportElementsModel::get_h() {
	return currenth->getData();
}

long LB_STDCALL lbReportElementsModel::get_reportid() {
	return currentreportid->getData();
}

long LB_STDCALL lbReportElementsModel::get_typ() {
	return currenttyp->getData();
}


class lbPluginReportElementsModel : public lb_I_PluginImpl {
public:
	lbPluginReportElementsModel();
	
	virtual ~lbPluginReportElementsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportElementsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsModel, lbPluginReportElementsModel)

lbErrCodes LB_STDCALL lbPluginReportElementsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementsModel::lbPluginReportElementsModel() {
	_CL_VERBOSE << "lbPluginReportElementsModel::lbPluginReportElementsModel() called.\n" LOG_
}

lbPluginReportElementsModel::~lbPluginReportElementsModel() {
	_CL_VERBOSE << "lbPluginReportElementsModel::~lbPluginReportElementsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementsModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModel == NULL) {
		lbReportElementsModel* ReportElementsModel = new lbReportElementsModel();
		
	
		QI(ReportElementsModel, lb_I_Unknown, ukReportElementsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportElementsModel* ReportElementsModel = new lbReportElementsModel();
		
	
		QI(ReportElementsModel, lb_I_Unknown, ukReportElementsModel)
	}
	
	lb_I_Unknown* r = ukReportElementsModel.getPtr();
	ukReportElementsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementsModel != NULL) {
                ukReportElementsModel--;
                ukReportElementsModel.resetPtr();
        }
}

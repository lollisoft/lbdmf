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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
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

#include <lbDBReportModel.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportElementTypes)
	ADD_INTERFACE(lb_I_ReportElementTypes)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbReportElementTypes::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportTexts)
	ADD_INTERFACE(lb_I_ReportTexts)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbReportTexts::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportElements)
	ADD_INTERFACE(lb_I_ReportElements)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbReportElements::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReportParameters)
	ADD_INTERFACE(lb_I_ReportParameters)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbReportParameters::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbReports)
	ADD_INTERFACE(lb_I_Reports)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbReports::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}

 
 
 


lbReports::lbReports() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Reports)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentDescription)
}
	
lbReports::~lbReports() {

}

long		LB_STDCALL lbReports::addReport(const char* name, const char* description, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "lbReports::addReport('" << name << "', '" << description << "', '" << _id << "') called." LOG_

	*Name = name;
	*Description = description;
	ID->setData(_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Reports->insert(&ukParam, &key);

	return -1;
}

bool		LB_STDCALL lbReports::selectReport(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Reports->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentName);
		*name = "Description";
		param->getUAPString(*&name, *&currentDescription);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		
		return true;
	}

	return false;
}

int			LB_STDCALL lbReports::getReportCount() {
	return Reports->Count();
}

bool		LB_STDCALL lbReports::hasMoreReports() {
	return Reports->hasMoreElements() == 1;
}

void		LB_STDCALL lbReports::setNextReport() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Reports->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentName);
	*name = "Description";
	param->getUAPString(*&name, *&currentDescription);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
}

void		LB_STDCALL lbReports::finishReportIteration() {
	Reports->finishIteration();
}


long		LB_STDCALL lbReports::getReportID() {
	return currentID->getData();
}

char*		LB_STDCALL lbReports::getReportName() {
	return currentName->charrep();
}

char*		LB_STDCALL lbReports::getReportDescription() {
	return currentDescription->charrep();
}


class lbPluginReportsModel : public lb_I_PluginImpl {
public:
	lbPluginReportsModel();
	
	virtual ~lbPluginReportsModel();

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
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportsModel, lbPluginReportsModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReportsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReportsModel::lbPluginReportsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReportsModel::~lbPluginReportsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
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

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbReports* Users_ApplicationModel = new lbReports();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReports* Users_ApplicationModel = new lbReports();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginReportsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/


lbReportParameters::lbReportParameters() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, ReportParameters)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentReportID)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentValue)	
}

lbReportParameters::~lbReportParameters() {

}

long		LB_STDCALL lbReportParameters::addParameter(long reportid, const char* name, const char* value, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Value)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ReportID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "lbReportParameters::addParameter('" << reportid << "', '" << name << "', '" << value << "', '" << _id << "') called." LOG_

	*Name = name;
	*Value = value;
	ReportID->setData(reportid);
	ID->setData(_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Value";
	param->setUAPString(*&paramname, *&Value);
	*paramname = "ReportID";
	param->setUAPLong(*&paramname, *&ReportID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportParameters->insert(&ukParam, &key);

	return -1;
}


bool		LB_STDCALL lbReportParameters::selectParameter(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportParameters->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentName);
		*name = "Value";
		param->getUAPString(*&name, *&currentValue);
		*name = "ReportID";
		param->getUAPLong(*&name, *&currentReportID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		
		return true;
	}

	return false;
}

int			LB_STDCALL lbReportParameters::getParameterCount() {
	return ReportParameters->Count();
}

bool		LB_STDCALL lbReportParameters::hasMoreParameters() {
	return ReportParameters->hasMoreElements() == 1;
}

void		LB_STDCALL lbReportParameters::setNextParameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = ReportParameters->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentName);
	*name = "Value";
	param->getUAPString(*&name, *&currentValue);
	*name = "ReportID";
	param->getUAPLong(*&name, *&currentReportID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
}

void		LB_STDCALL lbReportParameters::finishParameterIteration() {
	ReportParameters->finishIteration();
}

long		LB_STDCALL lbReportParameters::getReportID() {
	return currentReportID->getData();
}

long		LB_STDCALL lbReportParameters::getParameterID() {
	return currentID->getData();
}

char*		LB_STDCALL lbReportParameters::getParameterName() {
	return currentName->charrep();
}

char*		LB_STDCALL lbReportParameters::getParameterValue() {
	return currentValue->charrep();
}

class lbPluginReportParametersModel : public lb_I_PluginImpl {
public:
	lbPluginReportParametersModel();
	
	virtual ~lbPluginReportParametersModel();

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
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportParametersModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportParametersModel, lbPluginReportParametersModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReportParametersModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReportParametersModel::lbPluginReportParametersModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReportParametersModel::~lbPluginReportParametersModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
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

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportParametersModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbReportParameters* Users_ApplicationModel = new lbReportParameters();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportParametersModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportParameters* Users_ApplicationModel = new lbReportParameters();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginReportParametersModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/



lbReportElements::lbReportElements() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, ReportElements)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentReportID)
	REQUEST(getModuleInstance(), lb_I_Long, currentTyp)
	REQUEST(getModuleInstance(), lb_I_Long, currentX)
	REQUEST(getModuleInstance(), lb_I_Long, currentY)
	REQUEST(getModuleInstance(), lb_I_Long, currentW)
	REQUEST(getModuleInstance(), lb_I_Long, currentH)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentDescription)	
}

lbReportElements::~lbReportElements() {

}


long		LB_STDCALL lbReportElements::addElement(long reportid, const char* name, long typ, long x, long y, long w, long h, const char* description, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ReportID)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Typ)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, X)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Y)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, W)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, H)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "lbReportElements::addElement('" << reportid << "', '" << name << "', '" << typ << "', '" << x << "', '" << y << "', '" << w << "', '" << h << "', '" << description << "', '" << _id << "') called." LOG_

	*Name = name;
	*Description = description;
	ID->setData(_id);
	Typ->setData(typ);
	ReportID->setData(reportid);
	X->setData(x);
	Y->setData(y);
	W->setData(w);
	H->setData(h);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "ReportID";
	param->setUAPLong(*&paramname, *&ReportID);
	*paramname = "X";
	param->setUAPLong(*&paramname, *&X);
	*paramname = "Y";
	param->setUAPLong(*&paramname, *&Y);
	*paramname = "W";
	param->setUAPLong(*&paramname, *&W);
	*paramname = "H";
	param->setUAPLong(*&paramname, *&H);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportElements->insert(&ukParam, &key);

	return -1;
}

bool		LB_STDCALL lbReportElements::selectElement(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportElements->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentName);
		*name = "Description";
		param->getUAPString(*&name, *&currentDescription);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "Typ";
		param->getUAPLong(*&name, *&currentTyp);
		*name = "ReportID";
		param->getUAPLong(*&name, *&currentReportID);
		*name = "X";
		param->getUAPLong(*&name, *&currentX);
		*name = "Y";
		param->getUAPLong(*&name, *&currentY);
		*name = "W";
		param->getUAPLong(*&name, *&currentW);
		*name = "H";
		param->getUAPLong(*&name, *&currentH);
		
		return true;
	}

	return false;
}

int			LB_STDCALL lbReportElements::getElementCount() {
	return ReportElements->Count();
}

bool		LB_STDCALL lbReportElements::hasMoreElements() {
	return ReportElements->hasMoreElements() == 1;
}

void		LB_STDCALL lbReportElements::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = ReportElements->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentName);
	*name = "Description";
	param->getUAPString(*&name, *&currentDescription);
	*name = "Typ";
	param->getUAPLong(*&name, *&currentTyp);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "ReportID";
	param->getUAPLong(*&name, *&currentReportID);
	*name = "X";
	param->getUAPLong(*&name, *&currentX);
	*name = "Y";
	param->getUAPLong(*&name, *&currentY);
	*name = "W";
	param->getUAPLong(*&name, *&currentW);
	*name = "H";
	param->getUAPLong(*&name, *&currentH);
}

void		LB_STDCALL lbReportElements::finishElementIteration() {
	ReportElements->finishIteration();
}

long		LB_STDCALL lbReportElements::getElementReportID() {
	return currentReportID->getData();
}

long		LB_STDCALL lbReportElements::getElementID() {
	return currentID->getData();
}

char*		LB_STDCALL lbReportElements::getElementName() {
	return currentName->charrep();
}

char*		LB_STDCALL lbReportElements::getElementDescription() {
	return currentDescription->charrep();
}

long		LB_STDCALL lbReportElements::getElementTyp() {
	return currentTyp->getData();
}

long		LB_STDCALL lbReportElements::getElementX() {
	return currentX->getData();
}

long		LB_STDCALL lbReportElements::getElementY() {
	return currentY->getData();
}

long		LB_STDCALL lbReportElements::getElementW() {
	return currentW->getData();
}

long		LB_STDCALL lbReportElements::getElementH() {
	return currentH->getData();
}

class lbPluginReportElementsModel : public lb_I_PluginImpl {
public:
	lbPluginReportElementsModel();
	
	virtual ~lbPluginReportElementsModel();

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
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsModel, lbPluginReportElementsModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReportElementsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReportElementsModel::lbPluginReportElementsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReportElementsModel::~lbPluginReportElementsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
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

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportElementsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbReportElements* Users_ApplicationModel = new lbReportElements();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportElementsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportElements* Users_ApplicationModel = new lbReportElements();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginReportElementsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/


lbReportElementTypes::lbReportElementTypes() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, ElementTypes)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentDescription)	
}

lbReportElementTypes::~lbReportElementTypes() {

}


long		LB_STDCALL lbReportElementTypes::addElementType(const char* name, const char* description, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "lbReportElementTypes::addElementType('" << name << "', '" << description << "', '" << _id << "') called." LOG_

	*Name = name;
	*Description = description;
	ID->setData(_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ElementTypes->insert(&ukParam, &key);

	return -1;
}

bool		LB_STDCALL lbReportElementTypes::selectElementType(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ElementTypes->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "Name";
		param->getUAPString(*&name, *&currentName);
		*name = "Description";
		param->getUAPString(*&name, *&currentDescription);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		
		return true;
	}

	return false;
}

int			LB_STDCALL lbReportElementTypes::getElementTypeCount() {
	return ElementTypes->Count();
}

bool		LB_STDCALL lbReportElementTypes::hasMoreElementTypes() {
	return ElementTypes->hasMoreElements();
}

void		LB_STDCALL lbReportElementTypes::setNextElementType() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = ElementTypes->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Name";
	param->getUAPString(*&name, *&currentName);
	*name = "Description";
	param->getUAPString(*&name, *&currentDescription);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
}

void		LB_STDCALL lbReportElementTypes::finishElementTypeIteration() {
	ElementTypes->finishIteration();
}

long		LB_STDCALL lbReportElementTypes::getElementID() {
	return currentID->getData();
}

char*		LB_STDCALL lbReportElementTypes::getElementName() {
	return currentName->charrep();
}

char*		LB_STDCALL lbReportElementTypes::getElementDescription() {
	return currentDescription->charrep();
}



class lbPluginReportElementTypesModel : public lb_I_PluginImpl {
public:
	lbPluginReportElementTypesModel();
	
	virtual ~lbPluginReportElementTypesModel();

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
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementTypesModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementTypesModel, lbPluginReportElementTypesModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReportElementTypesModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReportElementTypesModel::lbPluginReportElementTypesModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReportElementTypesModel::~lbPluginReportElementTypesModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
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

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbReportElementTypes* Users_ApplicationModel = new lbReportElementTypes();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportElementTypes* Users_ApplicationModel = new lbReportElementTypes();
		Users_ApplicationModel->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginReportElementTypesModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/



lbReportTexts::lbReportTexts() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, ReportTexts)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentElementID)
	REQUEST(getModuleInstance(), lb_I_String, currentText)
	REQUEST(getModuleInstance(), lb_I_Long, currentLine)	
}

lbReportTexts::~lbReportTexts() {

}

	
long		LB_STDCALL lbReportTexts::addText(long elementid, long line, const char* text, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Text)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ElementID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Line)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_LOG << "lbReportTexts::addText('" << elementid << "', '" << line << "', '" << text << "', '" << _id << "') called." LOG_

	*Text = text;
	ID->setData(_id);
	ElementID->setData(elementid);
	Line->setData(line);
	
	*paramname = "Text";
	param->setUAPString(*&paramname, *&Text);
	*paramname = "Line";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "ElementID";
	param->setUAPLong(*&paramname, *&ElementID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ReportTexts->insert(&ukParam, &key);

	return -1;
}


bool		LB_STDCALL lbReportTexts::selectText(long _id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ReportTexts->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "Text";
		param->getUAPString(*&name, *&currentText);
		*name = "Line";
		param->getUAPLong(*&name, *&currentLine);
		*name = "ElementID";
		param->getUAPLong(*&name, *&currentElementID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		
		return true;
	}

	return false;
}

int			LB_STDCALL lbReportTexts::getTextCount() {
	return ReportTexts->Count();
}

bool		LB_STDCALL lbReportTexts::hasMoreTexts() {
	return ReportTexts->hasMoreElements() == 1;
}

void		LB_STDCALL lbReportTexts::setNextText() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = ReportTexts->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Text";
	param->getUAPString(*&name, *&currentText);
	*name = "ElementID";
	param->getUAPLong(*&name, *&currentElementID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "Line";
	param->getUAPLong(*&name, *&currentLine);
}

void		LB_STDCALL lbReportTexts::finishTextIteration() {
	ReportTexts->finishIteration();
}

char*		LB_STDCALL lbReportTexts::getText() {
	return currentText->charrep();
}

long		LB_STDCALL lbReportTexts::getLine() {
	return currentLine->getData();
}

long		LB_STDCALL lbReportTexts::getElementID() {
	return currentElementID->getData();
}

long		LB_STDCALL lbReportTexts::getID() {
	return currentID->getData();
}


class lbPluginReportTextsModel : public lb_I_PluginImpl {
public:
	lbPluginReportTextsModel();
	
	virtual ~lbPluginReportTextsModel();

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
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportTextsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportTextsModel, lbPluginReportTextsModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginReportTextsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginReportTextsModel::lbPluginReportTextsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginReportTextsModel::~lbPluginReportTextsModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
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

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportTextsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbReportTexts* reporttexts = new lbReportTexts();
		reporttexts->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(reporttexts, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginReportTextsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbReportTexts* reporttexts = new lbReportTexts();
		reporttexts->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(reporttexts, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginReportTextsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/




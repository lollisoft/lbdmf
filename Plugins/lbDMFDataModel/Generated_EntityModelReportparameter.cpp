
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
#include <Generated_EntityModelReportparameter.h>

IMPLEMENT_FUNCTOR(instanceOfReportparameterModel, ReportparameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportparameterModel)
	ADD_INTERFACE(lb_I_Reportparameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(ReportparameterModel)

ReportparameterModel::ReportparameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Reportparameter)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_Long, currentvalue)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_Long, currentreportid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportparameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "ReportparameterModel::ReportparameterModel() called." LOG_
}

ReportparameterModel::~ReportparameterModel() {
	_CL_VERBOSE << "ReportparameterModel::~ReportparameterModel() called." LOG_
}

lbErrCodes LB_STDCALL ReportparameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportparameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL ReportparameterModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Reportparameter";
	
	UAP(lb_I_KeyBase, key)
	QI(CNS, lb_I_KeyBase, key)
	
	if (objectExtensions->exists(*&key)) {
		UAP(lb_I_ExtensionObject, ex)
		UAP(lb_I_KeyBase, key)
		
		uk = objectExtensions->getElement(*&key);
		QI(uk, lb_I_ExtensionObject, ex)
		ex++;
		return ex;
	}
		
	AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_ExtensionObject, dbbackend, extension, "'database plugin'")
	if (extension == NULL) {
		_LOG << "Error: Did not find extension object for given namespace " << CNS->charrep() LOG_
		return NULL;
	}
	extension++;
	return extension.getPtr();
}

lb_I_ExtensionObject* LB_STDCALL ReportparameterModel::getExtension(const char* contextnamespace) {
/*
	These extensions may be supported until yet. At least the following are required.

	Required
	
	ADD_PLUGIN(lbPluginInputStream,			InputStreamVisitor)
	ADD_PLUGIN(lbPluginDatabaseInputStream,	DatabaseInputStreamVisitor)
	ADD_PLUGIN(lbPluginOutputStream,		OutputStreamVisitor)
	ADD_PLUGIN(lbPluginXMLOutputStream,		XMLOutputStreamVisitor)

	May
	
	ADD_PLUGIN(lbPluginXMLInputStream,		XMLInputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONOutputStream,	JSONOutputStreamVisitor)
	ADD_PLUGIN(lbPluginJSONInputStream,		JSONInputStreamVisitor)
*/
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	return getExtension(*&CNS);
}

	
lbErrCodes LB_STDCALL ReportparameterModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL ReportparameterModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL ReportparameterModel::addReportparameter(long _value, const char* _name, long _reportid,  long _ReportparameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __value)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __reportid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportparameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __value->setData(_value);
    *__name = _name;
    __reportid->setData(_reportid);

	
	__ReportparameterID->setData(_ReportparameterID);

    *paramname = "value";
    param->setUAPLong(*&paramname, *&__value);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "reportid";
    param->setUAPLong(*&paramname, *&__reportid);


	*paramname = "ReportparameterID";
	param->setUAPLong(*&paramname, *&__ReportparameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportparameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Reportparameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL ReportparameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Reportparameter->finishIteration();
	while (hasMoreReportparameter()) {
		setNextReportparameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reportparameter->remove(&key);
			Reportparameter->finishIteration();
		}
	}
}

void		LB_STDCALL ReportparameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Reportparameter->finishIteration();
	while (hasMoreReportparameter()) {
		setNextReportparameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reportparameter->remove(&key);
			Reportparameter->finishIteration();
		}
	}
}

bool LB_STDCALL ReportparameterModel::selectReportparameter(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Reportparameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "value";
    param->getUAPLong(*&paramname, *&currentvalue);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);


		*paramname = "ReportparameterID";
		param->getUAPLong(*&paramname, *&currentReportparameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL ReportparameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL ReportparameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL ReportparameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL ReportparameterModel::getReportparameterCount() {
	return Reportparameter->Count();
}

bool  LB_STDCALL ReportparameterModel::hasMoreReportparameter() {
	return (Reportparameter->hasMoreElements() == 1);
}

void  LB_STDCALL ReportparameterModel::setNextReportparameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Reportparameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "value";
    param->getUAPLong(*&paramname, *&currentvalue);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "reportid";
    param->getUAPLong(*&paramname, *&currentreportid);

	*paramname = "ReportparameterID";
	param->getUAPLong(*&paramname, *&currentReportparameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL ReportparameterModel::finishReportparameterIteration() {
	Reportparameter->finishIteration();
}

long LB_STDCALL ReportparameterModel::get_id() {
	return currentReportparameterID->getData();
}


long LB_STDCALL ReportparameterModel::get_value() {
	return currentvalue->getData();
}

char* LB_STDCALL ReportparameterModel::get_name() {
	return currentname->charrep();
}

long LB_STDCALL ReportparameterModel::get_reportid() {
	return currentreportid->getData();
}


class lbPluginReportparameterModel : public lb_I_PluginImpl {
public:
	lbPluginReportparameterModel();
	
	virtual ~lbPluginReportparameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportparameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportparameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportparameterModel, lbPluginReportparameterModel)

lbErrCodes LB_STDCALL lbPluginReportparameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportparameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportparameterModel::lbPluginReportparameterModel() {
	_CL_VERBOSE << "lbPluginReportparameterModel::lbPluginReportparameterModel() called.\n" LOG_
}

lbPluginReportparameterModel::~lbPluginReportparameterModel() {
	_CL_VERBOSE << "lbPluginReportparameterModel::~lbPluginReportparameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportparameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportparameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportparameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportparameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModel == NULL) {
		ReportparameterModel* aReportparameterModel = new ReportparameterModel();
		
	
		QI(aReportparameterModel, lb_I_Unknown, ukReportparameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportparameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportparameterModel* aReportparameterModel = new ReportparameterModel();
		
	
		QI(aReportparameterModel, lb_I_Unknown, ukReportparameterModel)
	}
	
	lb_I_Unknown* r = ukReportparameterModel.getPtr();
	ukReportparameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportparameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportparameterModel != NULL) {
                ukReportparameterModel--;
                ukReportparameterModel.resetPtr();
        }
}

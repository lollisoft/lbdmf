
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
#include <Generated_EntityModelReportdefinitionen.h>

IMPLEMENT_FUNCTOR(instanceOfReportdefinitionenModel, ReportdefinitionenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportdefinitionenModel)
	ADD_INTERFACE(lb_I_Reportdefinitionen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(ReportdefinitionenModel)

ReportdefinitionenModel::ReportdefinitionenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Reportdefinitionen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentdescription)
    REQUEST(getModuleInstance(), lb_I_String, currentname)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportdefinitionenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "ReportdefinitionenModel::ReportdefinitionenModel() called." LOG_
}

ReportdefinitionenModel::~ReportdefinitionenModel() {
	_CL_VERBOSE << "ReportdefinitionenModel::~ReportdefinitionenModel() called." LOG_
}

lbErrCodes LB_STDCALL ReportdefinitionenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportdefinitionenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL ReportdefinitionenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Reportdefinitionen";
	
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

lb_I_ExtensionObject* LB_STDCALL ReportdefinitionenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL ReportdefinitionenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL ReportdefinitionenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL ReportdefinitionenModel::addReportdefinitionen(const char* _description, const char* _name,  long _ReportdefinitionenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __description)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ReportdefinitionenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__description = _description;
    *__name = _name;

	
	__ReportdefinitionenID->setData(_ReportdefinitionenID);

    *paramname = "description";
    param->setUAPString(*&paramname, *&__description);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);


	*paramname = "ReportdefinitionenID";
	param->setUAPLong(*&paramname, *&__ReportdefinitionenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ReportdefinitionenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Reportdefinitionen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL ReportdefinitionenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Reportdefinitionen->finishIteration();
	while (hasMoreReportdefinitionen()) {
		setNextReportdefinitionen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reportdefinitionen->remove(&key);
			Reportdefinitionen->finishIteration();
		}
	}
}

void		LB_STDCALL ReportdefinitionenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Reportdefinitionen->finishIteration();
	while (hasMoreReportdefinitionen()) {
		setNextReportdefinitionen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Reportdefinitionen->remove(&key);
			Reportdefinitionen->finishIteration();
		}
	}
}

bool LB_STDCALL ReportdefinitionenModel::selectReportdefinitionen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Reportdefinitionen->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);


		*paramname = "ReportdefinitionenID";
		param->getUAPLong(*&paramname, *&currentReportdefinitionenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL ReportdefinitionenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL ReportdefinitionenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL ReportdefinitionenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL ReportdefinitionenModel::getReportdefinitionenCount() {
	return Reportdefinitionen->Count();
}

bool  LB_STDCALL ReportdefinitionenModel::hasMoreReportdefinitionen() {
	return (Reportdefinitionen->hasMoreElements() == 1);
}

void  LB_STDCALL ReportdefinitionenModel::setNextReportdefinitionen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Reportdefinitionen->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "description";
    param->getUAPString(*&paramname, *&currentdescription);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);

	*paramname = "ReportdefinitionenID";
	param->getUAPLong(*&paramname, *&currentReportdefinitionenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL ReportdefinitionenModel::finishReportdefinitionenIteration() {
	Reportdefinitionen->finishIteration();
}

long LB_STDCALL ReportdefinitionenModel::get_id() {
	return currentReportdefinitionenID->getData();
}


char* LB_STDCALL ReportdefinitionenModel::get_description() {
	return currentdescription->charrep();
}

char* LB_STDCALL ReportdefinitionenModel::get_name() {
	return currentname->charrep();
}


class lbPluginReportdefinitionenModel : public lb_I_PluginImpl {
public:
	lbPluginReportdefinitionenModel();
	
	virtual ~lbPluginReportdefinitionenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportdefinitionenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportdefinitionenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportdefinitionenModel, lbPluginReportdefinitionenModel)

lbErrCodes LB_STDCALL lbPluginReportdefinitionenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportdefinitionenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportdefinitionenModel::lbPluginReportdefinitionenModel() {
	_CL_VERBOSE << "lbPluginReportdefinitionenModel::lbPluginReportdefinitionenModel() called.\n" LOG_
}

lbPluginReportdefinitionenModel::~lbPluginReportdefinitionenModel() {
	_CL_VERBOSE << "lbPluginReportdefinitionenModel::~lbPluginReportdefinitionenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportdefinitionenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportdefinitionenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportdefinitionenModel::initialize() {
}
	
bool LB_STDCALL lbPluginReportdefinitionenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportdefinitionenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportdefinitionenModel == NULL) {
		ReportdefinitionenModel* aReportdefinitionenModel = new ReportdefinitionenModel();
		
	
		QI(aReportdefinitionenModel, lb_I_Unknown, ukReportdefinitionenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportdefinitionenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportdefinitionenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportdefinitionenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportdefinitionenModel* aReportdefinitionenModel = new ReportdefinitionenModel();
		
	
		QI(aReportdefinitionenModel, lb_I_Unknown, ukReportdefinitionenModel)
	}
	
	lb_I_Unknown* r = ukReportdefinitionenModel.getPtr();
	ukReportdefinitionenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportdefinitionenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportdefinitionenModel != NULL) {
                ukReportdefinitionenModel--;
                ukReportdefinitionenModel.resetPtr();
        }
}

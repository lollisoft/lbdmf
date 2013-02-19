
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

IMPLEMENT_FUNCTOR(instanceOfReportTextsModel, ReportTextsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportTextsModel)
	ADD_INTERFACE(lb_I_ReportTexts)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(ReportTextsModel)

ReportTextsModel::ReportTextsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, ReportTexts)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_Long, currentline)
    REQUEST(getModuleInstance(), lb_I_String, currenttext)
    REQUEST(getModuleInstance(), lb_I_Long, currentelementid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentReportTextsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "ReportTextsModel::ReportTextsModel() called." LOG_
}

ReportTextsModel::~ReportTextsModel() {
	_CL_VERBOSE << "ReportTextsModel::~ReportTextsModel() called." LOG_
}

lbErrCodes LB_STDCALL ReportTextsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportTextsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL ReportTextsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_ReportTexts";
	
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

lb_I_ExtensionObject* LB_STDCALL ReportTextsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL ReportTextsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL ReportTextsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL ReportTextsModel::add(long _line, const char* _text, long _elementid,  long _ReportTextsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __line)
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
    param->setUAPLong(*&paramname, *&__line);
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

void		LB_STDCALL ReportTextsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ReportTexts->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
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

void		LB_STDCALL ReportTextsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ReportTexts->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
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

bool LB_STDCALL ReportTextsModel::selectById(long user_id) {
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
    param->getUAPLong(*&paramname, *&currentline);
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

bool LB_STDCALL ReportTextsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL ReportTextsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL ReportTextsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL ReportTextsModel::Count() {
	return ReportTexts->Count();
}

bool  LB_STDCALL ReportTextsModel::hasMoreElements() {
	return (ReportTexts->hasMoreElements() == 1);
}

void  LB_STDCALL ReportTextsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ReportTexts->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "line";
    param->getUAPLong(*&paramname, *&currentline);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);
    *paramname = "elementid";
    param->getUAPLong(*&paramname, *&currentelementid);

	*paramname = "ReportTextsID";
	param->getUAPLong(*&paramname, *&currentReportTextsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL ReportTextsModel::finishIteration() {
	ReportTexts->finishIteration();
}

long LB_STDCALL ReportTextsModel::get_id() {
	return currentReportTextsID->getData();
}


long LB_STDCALL ReportTextsModel::get_line() {
	return currentline->getData();
}

char* LB_STDCALL ReportTextsModel::get_text() {
	return currenttext->charrep();
}

long LB_STDCALL ReportTextsModel::get_elementid() {
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
		ReportTextsModel* aReportTextsModel = new ReportTextsModel();
		
	
		QI(aReportTextsModel, lb_I_Unknown, ukReportTextsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportTextsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportTextsModel* aReportTextsModel = new ReportTextsModel();
		
	
		QI(aReportTextsModel, lb_I_Unknown, ukReportTextsModel)
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

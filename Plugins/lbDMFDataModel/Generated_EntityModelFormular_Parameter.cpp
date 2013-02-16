
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
#include <Generated_EntityModelFormular_Parameter.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_ParameterModel, Formular_ParameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_ParameterModel)
	ADD_INTERFACE(lb_I_Formular_Parameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(Formular_ParameterModel)

Formular_ParameterModel::Formular_ParameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Formular_Parameter)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentparametervalue)
    REQUEST(getModuleInstance(), lb_I_String, currentparametername)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormular_ParameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "Formular_ParameterModel::Formular_ParameterModel() called." LOG_
}

Formular_ParameterModel::~Formular_ParameterModel() {
	_CL_VERBOSE << "Formular_ParameterModel::~Formular_ParameterModel() called." LOG_
}

lbErrCodes LB_STDCALL Formular_ParameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_ParameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL Formular_ParameterModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Formular_Parameter";
	
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

lb_I_ExtensionObject* LB_STDCALL Formular_ParameterModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL Formular_ParameterModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL Formular_ParameterModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL Formular_ParameterModel::addFormular_Parameter(const char* _parametervalue, const char* _parametername, long _formularid,  long _Formular_ParameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametervalue)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametername)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __Formular_ParameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__parametervalue = _parametervalue;
    *__parametername = _parametername;
    __formularid->setData(_formularid);

	
	__Formular_ParameterID->setData(_Formular_ParameterID);

    *paramname = "parametervalue";
    param->setUAPString(*&paramname, *&__parametervalue);
    *paramname = "parametername";
    param->setUAPString(*&paramname, *&__parametername);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "Formular_ParameterID";
	param->setUAPLong(*&paramname, *&__Formular_ParameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__Formular_ParameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formular_Parameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL Formular_ParameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Parameter->finishIteration();
	while (hasMoreFormular_Parameter()) {
		setNextFormular_Parameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Parameter->remove(&key);
			Formular_Parameter->finishIteration();
		}
	}
}

void		LB_STDCALL Formular_ParameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formular_Parameter->finishIteration();
	while (hasMoreFormular_Parameter()) {
		setNextFormular_Parameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formular_Parameter->remove(&key);
			Formular_Parameter->finishIteration();
		}
	}
}

bool LB_STDCALL Formular_ParameterModel::selectFormular_Parameter(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formular_Parameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "Formular_ParameterID";
		param->getUAPLong(*&paramname, *&currentFormular_ParameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL Formular_ParameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL Formular_ParameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL Formular_ParameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL Formular_ParameterModel::getFormular_ParameterCount() {
	return Formular_Parameter->Count();
}

bool  LB_STDCALL Formular_ParameterModel::hasMoreFormular_Parameter() {
	return (Formular_Parameter->hasMoreElements() == 1);
}

void  LB_STDCALL Formular_ParameterModel::setNextFormular_Parameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formular_Parameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "Formular_ParameterID";
	param->getUAPLong(*&paramname, *&currentFormular_ParameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL Formular_ParameterModel::finishFormular_ParameterIteration() {
	Formular_Parameter->finishIteration();
}

long LB_STDCALL Formular_ParameterModel::get_id() {
	return currentFormular_ParameterID->getData();
}


char* LB_STDCALL Formular_ParameterModel::get_parametervalue() {
	return currentparametervalue->charrep();
}

char* LB_STDCALL Formular_ParameterModel::get_parametername() {
	return currentparametername->charrep();
}

long LB_STDCALL Formular_ParameterModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginFormular_ParameterModel : public lb_I_PluginImpl {
public:
	lbPluginFormular_ParameterModel();
	
	virtual ~lbPluginFormular_ParameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_ParameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_ParameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_ParameterModel, lbPluginFormular_ParameterModel)

lbErrCodes LB_STDCALL lbPluginFormular_ParameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_ParameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_ParameterModel::lbPluginFormular_ParameterModel() {
	_CL_VERBOSE << "lbPluginFormular_ParameterModel::lbPluginFormular_ParameterModel() called.\n" LOG_
}

lbPluginFormular_ParameterModel::~lbPluginFormular_ParameterModel() {
	_CL_VERBOSE << "lbPluginFormular_ParameterModel::~lbPluginFormular_ParameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_ParameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_ParameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_ParameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_ParameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ParameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ParameterModel == NULL) {
		Formular_ParameterModel* aFormular_ParameterModel = new Formular_ParameterModel();
		
	
		QI(aFormular_ParameterModel, lb_I_Unknown, ukFormular_ParameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_ParameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ParameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ParameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_ParameterModel* aFormular_ParameterModel = new Formular_ParameterModel();
		
	
		QI(aFormular_ParameterModel, lb_I_Unknown, ukFormular_ParameterModel)
	}
	
	lb_I_Unknown* r = ukFormular_ParameterModel.getPtr();
	ukFormular_ParameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_ParameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_ParameterModel != NULL) {
                ukFormular_ParameterModel--;
                ukFormular_ParameterModel.resetPtr();
        }
}

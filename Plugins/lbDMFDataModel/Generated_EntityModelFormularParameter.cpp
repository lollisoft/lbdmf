
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
#include <Generated_EntityModelFormularParameter.h>

IMPLEMENT_FUNCTOR(instanceOfFormularParameterModel, FormularParameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularParameterModel)
	ADD_INTERFACE(lb_I_FormularParameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FormularParameterModel)

FormularParameterModel::FormularParameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, FormularParameter)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentparametervalue)
    REQUEST(getModuleInstance(), lb_I_String, currentparametername)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularParameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FormularParameterModel::FormularParameterModel() called." LOG_
}

FormularParameterModel::~FormularParameterModel() {
	_CL_VERBOSE << "FormularParameterModel::~FormularParameterModel() called." LOG_
}

lbErrCodes LB_STDCALL FormularParameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularParameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FormularParameterModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_FormularParameter";
	
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

lb_I_ExtensionObject* LB_STDCALL FormularParameterModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FormularParameterModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FormularParameterModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FormularParameterModel::add(const char* _parametervalue, const char* _parametername, long _formularid,  long _FormularParameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametervalue)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametername)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormularParameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__parametervalue = _parametervalue;
    *__parametername = _parametername;
    __formularid->setData(_formularid);

	
	__FormularParameterID->setData(_FormularParameterID);

    *paramname = "parametervalue";
    param->setUAPString(*&paramname, *&__parametervalue);
    *paramname = "parametername";
    param->setUAPString(*&paramname, *&__parametername);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "FormularParameterID";
	param->setUAPLong(*&paramname, *&__FormularParameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormularParameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FormularParameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FormularParameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	FormularParameter->finishIteration();
	while (hasMoreFormularParameter()) {
		setNextFormularParameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularParameter->remove(&key);
			FormularParameter->finishIteration();
		}
	}
}

void		LB_STDCALL FormularParameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	FormularParameter->finishIteration();
	while (hasMoreFormularParameter()) {
		setNextFormularParameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularParameter->remove(&key);
			FormularParameter->finishIteration();
		}
	}
}

bool LB_STDCALL FormularParameterModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = FormularParameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "FormularParameterID";
		param->getUAPLong(*&paramname, *&currentFormularParameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FormularParameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FormularParameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FormularParameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FormularParameterModel::Count() {
	return FormularParameter->Count();
}

bool  LB_STDCALL FormularParameterModel::hasMoreElements() {
	return (FormularParameter->hasMoreElements() == 1);
}

void  LB_STDCALL FormularParameterModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = FormularParameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "FormularParameterID";
	param->getUAPLong(*&paramname, *&currentFormularParameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FormularParameterModel::finishIteration() {
	FormularParameter->finishIteration();
}

long LB_STDCALL FormularParameterModel::get_id() {
	return currentFormularParameterID->getData();
}


char* LB_STDCALL FormularParameterModel::get_parametervalue() {
	return currentparametervalue->charrep();
}

char* LB_STDCALL FormularParameterModel::get_parametername() {
	return currentparametername->charrep();
}

long LB_STDCALL FormularParameterModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginFormularParameterModel : public lb_I_PluginImpl {
public:
	lbPluginFormularParameterModel();
	
	virtual ~lbPluginFormularParameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularParameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularParameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularParameterModel, lbPluginFormularParameterModel)

lbErrCodes LB_STDCALL lbPluginFormularParameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularParameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularParameterModel::lbPluginFormularParameterModel() {
	_CL_VERBOSE << "lbPluginFormularParameterModel::lbPluginFormularParameterModel() called.\n" LOG_
}

lbPluginFormularParameterModel::~lbPluginFormularParameterModel() {
	_CL_VERBOSE << "lbPluginFormularParameterModel::~lbPluginFormularParameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularParameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularParameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularParameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularParameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModel == NULL) {
		FormularParameterModel* aFormularParameterModel = new FormularParameterModel();
		
	
		QI(aFormularParameterModel, lb_I_Unknown, ukFormularParameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularParameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularParameterModel* aFormularParameterModel = new FormularParameterModel();
		
	
		QI(aFormularParameterModel, lb_I_Unknown, ukFormularParameterModel)
	}
	
	lb_I_Unknown* r = ukFormularParameterModel.getPtr();
	ukFormularParameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularParameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularParameterModel != NULL) {
                ukFormularParameterModel--;
                ukFormularParameterModel.resetPtr();
        }
}

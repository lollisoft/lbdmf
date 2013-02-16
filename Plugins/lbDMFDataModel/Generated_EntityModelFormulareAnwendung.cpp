
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
#include <Generated_EntityModelFormulareAnwendung.h>

IMPLEMENT_FUNCTOR(instanceOfFormulareAnwendungModel, FormulareAnwendungModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormulareAnwendungModel)
	ADD_INTERFACE(lb_I_FormulareAnwendung)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(FormulareAnwendungModel)

FormulareAnwendungModel::FormulareAnwendungModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, FormulareAnwendung)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)
    REQUEST(getModuleInstance(), lb_I_Long, currentformularid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormulareAnwendungID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "FormulareAnwendungModel::FormulareAnwendungModel() called." LOG_
}

FormulareAnwendungModel::~FormulareAnwendungModel() {
	_CL_VERBOSE << "FormulareAnwendungModel::~FormulareAnwendungModel() called." LOG_
}

lbErrCodes LB_STDCALL FormulareAnwendungModel::setData(lb_I_Unknown*) {
	_LOG << "Error: FormulareAnwendungModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL FormulareAnwendungModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_FormulareAnwendung";
	
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

lb_I_ExtensionObject* LB_STDCALL FormulareAnwendungModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL FormulareAnwendungModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL FormulareAnwendungModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL FormulareAnwendungModel::addFormulareAnwendung(long _anwendungid, long _formularid,  long _FormulareAnwendungID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __formularid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __FormulareAnwendungID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __anwendungid->setData(_anwendungid);
    __formularid->setData(_formularid);

	
	__FormulareAnwendungID->setData(_FormulareAnwendungID);

    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);
    *paramname = "formularid";
    param->setUAPLong(*&paramname, *&__formularid);


	*paramname = "FormulareAnwendungID";
	param->setUAPLong(*&paramname, *&__FormulareAnwendungID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__FormulareAnwendungID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FormulareAnwendung->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL FormulareAnwendungModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	FormulareAnwendung->finishIteration();
	while (hasMoreFormulareAnwendung()) {
		setNextFormulareAnwendung();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormulareAnwendung->remove(&key);
			FormulareAnwendung->finishIteration();
		}
	}
}

void		LB_STDCALL FormulareAnwendungModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	FormulareAnwendung->finishIteration();
	while (hasMoreFormulareAnwendung()) {
		setNextFormulareAnwendung();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormulareAnwendung->remove(&key);
			FormulareAnwendung->finishIteration();
		}
	}
}

bool LB_STDCALL FormulareAnwendungModel::selectFormulareAnwendung(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = FormulareAnwendung->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);


		*paramname = "FormulareAnwendungID";
		param->getUAPLong(*&paramname, *&currentFormulareAnwendungID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL FormulareAnwendungModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL FormulareAnwendungModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL FormulareAnwendungModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL FormulareAnwendungModel::getFormulareAnwendungCount() {
	return FormulareAnwendung->Count();
}

bool  LB_STDCALL FormulareAnwendungModel::hasMoreFormulareAnwendung() {
	return (FormulareAnwendung->hasMoreElements() == 1);
}

void  LB_STDCALL FormulareAnwendungModel::setNextFormulareAnwendung() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = FormulareAnwendung->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);
    *paramname = "formularid";
    param->getUAPLong(*&paramname, *&currentformularid);

	*paramname = "FormulareAnwendungID";
	param->getUAPLong(*&paramname, *&currentFormulareAnwendungID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL FormulareAnwendungModel::finishFormulareAnwendungIteration() {
	FormulareAnwendung->finishIteration();
}

long LB_STDCALL FormulareAnwendungModel::get_id() {
	return currentFormulareAnwendungID->getData();
}


long LB_STDCALL FormulareAnwendungModel::get_anwendungid() {
	return currentanwendungid->getData();
}

long LB_STDCALL FormulareAnwendungModel::get_formularid() {
	return currentformularid->getData();
}


class lbPluginFormulareAnwendungModel : public lb_I_PluginImpl {
public:
	lbPluginFormulareAnwendungModel();
	
	virtual ~lbPluginFormulareAnwendungModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormulareAnwendungModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulareAnwendungModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulareAnwendungModel, lbPluginFormulareAnwendungModel)

lbErrCodes LB_STDCALL lbPluginFormulareAnwendungModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulareAnwendungModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulareAnwendungModel::lbPluginFormulareAnwendungModel() {
	_CL_VERBOSE << "lbPluginFormulareAnwendungModel::lbPluginFormulareAnwendungModel() called.\n" LOG_
}

lbPluginFormulareAnwendungModel::~lbPluginFormulareAnwendungModel() {
	_CL_VERBOSE << "lbPluginFormulareAnwendungModel::~lbPluginFormulareAnwendungModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormulareAnwendungModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulareAnwendungModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulareAnwendungModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormulareAnwendungModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareAnwendungModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareAnwendungModel == NULL) {
		FormulareAnwendungModel* aFormulareAnwendungModel = new FormulareAnwendungModel();
		
	
		QI(aFormulareAnwendungModel, lb_I_Unknown, ukFormulareAnwendungModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormulareAnwendungModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareAnwendungModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareAnwendungModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormulareAnwendungModel* aFormulareAnwendungModel = new FormulareAnwendungModel();
		
	
		QI(aFormulareAnwendungModel, lb_I_Unknown, ukFormulareAnwendungModel)
	}
	
	lb_I_Unknown* r = ukFormulareAnwendungModel.getPtr();
	ukFormulareAnwendungModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulareAnwendungModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormulareAnwendungModel != NULL) {
                ukFormulareAnwendungModel--;
                ukFormulareAnwendungModel.resetPtr();
        }
}

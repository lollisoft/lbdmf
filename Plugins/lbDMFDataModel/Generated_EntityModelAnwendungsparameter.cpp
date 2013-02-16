
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
#include <Generated_EntityModelAnwendungsparameter.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungsparameterModel, AnwendungsparameterModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungsparameterModel)
	ADD_INTERFACE(lb_I_Anwendungsparameter)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(AnwendungsparameterModel)

AnwendungsparameterModel::AnwendungsparameterModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Anwendungsparameter)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentparametervalue)
    REQUEST(getModuleInstance(), lb_I_String, currentparametername)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAnwendungsparameterID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "AnwendungsparameterModel::AnwendungsparameterModel() called." LOG_
}

AnwendungsparameterModel::~AnwendungsparameterModel() {
	_CL_VERBOSE << "AnwendungsparameterModel::~AnwendungsparameterModel() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungsparameterModel::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungsparameterModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL AnwendungsparameterModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Anwendungsparameter";
	
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

lb_I_ExtensionObject* LB_STDCALL AnwendungsparameterModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL AnwendungsparameterModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL AnwendungsparameterModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL AnwendungsparameterModel::addAnwendungsparameter(const char* _parametervalue, const char* _parametername, long _anwendungid,  long _AnwendungsparameterID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametervalue)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __parametername)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __AnwendungsparameterID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__parametervalue = _parametervalue;
    *__parametername = _parametername;
    __anwendungid->setData(_anwendungid);

	
	__AnwendungsparameterID->setData(_AnwendungsparameterID);

    *paramname = "parametervalue";
    param->setUAPString(*&paramname, *&__parametervalue);
    *paramname = "parametername";
    param->setUAPString(*&paramname, *&__parametername);
    *paramname = "anwendungid";
    param->setUAPLong(*&paramname, *&__anwendungid);


	*paramname = "AnwendungsparameterID";
	param->setUAPLong(*&paramname, *&__AnwendungsparameterID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__AnwendungsparameterID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Anwendungsparameter->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL AnwendungsparameterModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Anwendungsparameter->finishIteration();
	while (hasMoreAnwendungsparameter()) {
		setNextAnwendungsparameter();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Anwendungsparameter->remove(&key);
			Anwendungsparameter->finishIteration();
		}
	}
}

void		LB_STDCALL AnwendungsparameterModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Anwendungsparameter->finishIteration();
	while (hasMoreAnwendungsparameter()) {
		setNextAnwendungsparameter();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Anwendungsparameter->remove(&key);
			Anwendungsparameter->finishIteration();
		}
	}
}

bool LB_STDCALL AnwendungsparameterModel::selectAnwendungsparameter(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Anwendungsparameter->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);


		*paramname = "AnwendungsparameterID";
		param->getUAPLong(*&paramname, *&currentAnwendungsparameterID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL AnwendungsparameterModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL AnwendungsparameterModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL AnwendungsparameterModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL AnwendungsparameterModel::getAnwendungsparameterCount() {
	return Anwendungsparameter->Count();
}

bool  LB_STDCALL AnwendungsparameterModel::hasMoreAnwendungsparameter() {
	return (Anwendungsparameter->hasMoreElements() == 1);
}

void  LB_STDCALL AnwendungsparameterModel::setNextAnwendungsparameter() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Anwendungsparameter->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "parametervalue";
    param->getUAPString(*&paramname, *&currentparametervalue);
    *paramname = "parametername";
    param->getUAPString(*&paramname, *&currentparametername);
    *paramname = "anwendungid";
    param->getUAPLong(*&paramname, *&currentanwendungid);

	*paramname = "AnwendungsparameterID";
	param->getUAPLong(*&paramname, *&currentAnwendungsparameterID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL AnwendungsparameterModel::finishAnwendungsparameterIteration() {
	Anwendungsparameter->finishIteration();
}

long LB_STDCALL AnwendungsparameterModel::get_id() {
	return currentAnwendungsparameterID->getData();
}


char* LB_STDCALL AnwendungsparameterModel::get_parametervalue() {
	return currentparametervalue->charrep();
}

char* LB_STDCALL AnwendungsparameterModel::get_parametername() {
	return currentparametername->charrep();
}

long LB_STDCALL AnwendungsparameterModel::get_anwendungid() {
	return currentanwendungid->getData();
}


class lbPluginAnwendungsparameterModel : public lb_I_PluginImpl {
public:
	lbPluginAnwendungsparameterModel();
	
	virtual ~lbPluginAnwendungsparameterModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungsparameterModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungsparameterModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungsparameterModel, lbPluginAnwendungsparameterModel)

lbErrCodes LB_STDCALL lbPluginAnwendungsparameterModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungsparameterModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungsparameterModel::lbPluginAnwendungsparameterModel() {
	_CL_VERBOSE << "lbPluginAnwendungsparameterModel::lbPluginAnwendungsparameterModel() called.\n" LOG_
}

lbPluginAnwendungsparameterModel::~lbPluginAnwendungsparameterModel() {
	_CL_VERBOSE << "lbPluginAnwendungsparameterModel::~lbPluginAnwendungsparameterModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungsparameterModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungsparameterModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungsparameterModel::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungsparameterModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungsparameterModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungsparameterModel == NULL) {
		AnwendungsparameterModel* aAnwendungsparameterModel = new AnwendungsparameterModel();
		
	
		QI(aAnwendungsparameterModel, lb_I_Unknown, ukAnwendungsparameterModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungsparameterModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungsparameterModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungsparameterModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungsparameterModel* aAnwendungsparameterModel = new AnwendungsparameterModel();
		
	
		QI(aAnwendungsparameterModel, lb_I_Unknown, ukAnwendungsparameterModel)
	}
	
	lb_I_Unknown* r = ukAnwendungsparameterModel.getPtr();
	ukAnwendungsparameterModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungsparameterModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungsparameterModel != NULL) {
                ukAnwendungsparameterModel--;
                ukAnwendungsparameterModel.resetPtr();
        }
}

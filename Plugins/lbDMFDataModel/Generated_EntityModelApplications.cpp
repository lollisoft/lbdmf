
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
#include <Generated_EntityModelApplications.h>

IMPLEMENT_FUNCTOR(instanceOfApplicationsModel, ApplicationsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationsModel)
	ADD_INTERFACE(lb_I_Applications)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(ApplicationsModel)

ApplicationsModel::ApplicationsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Applications)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currenttitel)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentinterface)
    REQUEST(getModuleInstance(), lb_I_String, currentfunctor)
    REQUEST(getModuleInstance(), lb_I_String, currentmodulename)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "ApplicationsModel::ApplicationsModel() called." LOG_
}

ApplicationsModel::~ApplicationsModel() {
	_CL_VERBOSE << "ApplicationsModel::~ApplicationsModel() called." LOG_
}

lbErrCodes LB_STDCALL ApplicationsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: ApplicationsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL ApplicationsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Applications";
	
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

lb_I_ExtensionObject* LB_STDCALL ApplicationsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL ApplicationsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL ApplicationsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL ApplicationsModel::add(const char* _titel, const char* _name, const char* _interface, const char* _functor, const char* _modulename,  long _ApplicationsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __titel)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __interface)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __functor)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __modulename)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ApplicationsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__titel = _titel;
    *__name = _name;
    *__interface = _interface;
    *__functor = _functor;
    *__modulename = _modulename;

	
	__ApplicationsID->setData(_ApplicationsID);

    *paramname = "titel";
    param->setUAPString(*&paramname, *&__titel);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "interface";
    param->setUAPString(*&paramname, *&__interface);
    *paramname = "functor";
    param->setUAPString(*&paramname, *&__functor);
    *paramname = "modulename";
    param->setUAPString(*&paramname, *&__modulename);


	*paramname = "ApplicationsID";
	param->setUAPLong(*&paramname, *&__ApplicationsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ApplicationsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Applications->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL ApplicationsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Applications->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications->remove(&key);
			Applications->finishIteration();
		}
	}
}

void		LB_STDCALL ApplicationsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Applications->finishIteration();
	while (hasMoreElements()) {
		setNextElement();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Applications->remove(&key);
			Applications->finishIteration();
		}
	}
}

bool LB_STDCALL ApplicationsModel::selectById(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Applications->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "titel";
    param->getUAPString(*&paramname, *&currenttitel);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "functor";
    param->getUAPString(*&paramname, *&currentfunctor);
    *paramname = "modulename";
    param->getUAPString(*&paramname, *&currentmodulename);


		*paramname = "ApplicationsID";
		param->getUAPLong(*&paramname, *&currentApplicationsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL ApplicationsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL ApplicationsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL ApplicationsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL ApplicationsModel::Count() {
	return Applications->Count();
}

bool  LB_STDCALL ApplicationsModel::hasMoreElements() {
	return (Applications->hasMoreElements() == 1);
}

void  LB_STDCALL ApplicationsModel::setNextElement() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Applications->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "titel";
    param->getUAPString(*&paramname, *&currenttitel);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "interface";
    param->getUAPString(*&paramname, *&currentinterface);
    *paramname = "functor";
    param->getUAPString(*&paramname, *&currentfunctor);
    *paramname = "modulename";
    param->getUAPString(*&paramname, *&currentmodulename);

	*paramname = "ApplicationsID";
	param->getUAPLong(*&paramname, *&currentApplicationsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL ApplicationsModel::finishIteration() {
	Applications->finishIteration();
}

long LB_STDCALL ApplicationsModel::get_id() {
	return currentApplicationsID->getData();
}


char* LB_STDCALL ApplicationsModel::get_titel() {
	return currenttitel->charrep();
}

char* LB_STDCALL ApplicationsModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL ApplicationsModel::get_interface() {
	return currentinterface->charrep();
}

char* LB_STDCALL ApplicationsModel::get_functor() {
	return currentfunctor->charrep();
}

char* LB_STDCALL ApplicationsModel::get_modulename() {
	return currentmodulename->charrep();
}


class lbPluginApplicationsModel : public lb_I_PluginImpl {
public:
	lbPluginApplicationsModel();
	
	virtual ~lbPluginApplicationsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationsModel, lbPluginApplicationsModel)

lbErrCodes LB_STDCALL lbPluginApplicationsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationsModel::lbPluginApplicationsModel() {
	_CL_VERBOSE << "lbPluginApplicationsModel::lbPluginApplicationsModel() called.\n" LOG_
}

lbPluginApplicationsModel::~lbPluginApplicationsModel() {
	_CL_VERBOSE << "lbPluginApplicationsModel::~lbPluginApplicationsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationsModel::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModel == NULL) {
		ApplicationsModel* aApplicationsModel = new ApplicationsModel();
		
	
		QI(aApplicationsModel, lb_I_Unknown, ukApplicationsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationsModel* aApplicationsModel = new ApplicationsModel();
		
	
		QI(aApplicationsModel, lb_I_Unknown, ukApplicationsModel)
	}
	
	lb_I_Unknown* r = ukApplicationsModel.getPtr();
	ukApplicationsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationsModel != NULL) {
                ukApplicationsModel--;
                ukApplicationsModel.resetPtr();
        }
}

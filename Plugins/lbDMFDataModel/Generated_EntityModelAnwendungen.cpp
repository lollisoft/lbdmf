
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
#include <Generated_EntityModelAnwendungen.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungenModel, AnwendungenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungenModel)
	ADD_INTERFACE(lb_I_Anwendungen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(AnwendungenModel)

AnwendungenModel::AnwendungenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Anwendungen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currenttitel)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_String, currentinterface)
    REQUEST(getModuleInstance(), lb_I_String, currentfunctor)
    REQUEST(getModuleInstance(), lb_I_String, currentmodulename)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAnwendungenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "AnwendungenModel::AnwendungenModel() called." LOG_
}

AnwendungenModel::~AnwendungenModel() {
	_CL_VERBOSE << "AnwendungenModel::~AnwendungenModel() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL AnwendungenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Anwendungen";
	
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

lb_I_ExtensionObject* LB_STDCALL AnwendungenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL AnwendungenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL AnwendungenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL AnwendungenModel::addAnwendungen(const char* _titel, const char* _name, const char* _interface, const char* _functor, const char* _modulename,  long _AnwendungenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __titel)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __interface)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __functor)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __modulename)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __AnwendungenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__titel = _titel;
    *__name = _name;
    *__interface = _interface;
    *__functor = _functor;
    *__modulename = _modulename;

	
	__AnwendungenID->setData(_AnwendungenID);

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


	*paramname = "AnwendungenID";
	param->setUAPLong(*&paramname, *&__AnwendungenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__AnwendungenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Anwendungen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL AnwendungenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Anwendungen->finishIteration();
	while (hasMoreAnwendungen()) {
		setNextAnwendungen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Anwendungen->remove(&key);
			Anwendungen->finishIteration();
		}
	}
}

void		LB_STDCALL AnwendungenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Anwendungen->finishIteration();
	while (hasMoreAnwendungen()) {
		setNextAnwendungen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Anwendungen->remove(&key);
			Anwendungen->finishIteration();
		}
	}
}

bool LB_STDCALL AnwendungenModel::selectAnwendungen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Anwendungen->getElement(&key);

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


		*paramname = "AnwendungenID";
		param->getUAPLong(*&paramname, *&currentAnwendungenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL AnwendungenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL AnwendungenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL AnwendungenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL AnwendungenModel::getAnwendungenCount() {
	return Anwendungen->Count();
}

bool  LB_STDCALL AnwendungenModel::hasMoreAnwendungen() {
	return (Anwendungen->hasMoreElements() == 1);
}

void  LB_STDCALL AnwendungenModel::setNextAnwendungen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Anwendungen->nextElement();
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

	*paramname = "AnwendungenID";
	param->getUAPLong(*&paramname, *&currentAnwendungenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL AnwendungenModel::finishAnwendungenIteration() {
	Anwendungen->finishIteration();
}

long LB_STDCALL AnwendungenModel::get_id() {
	return currentAnwendungenID->getData();
}


char* LB_STDCALL AnwendungenModel::get_titel() {
	return currenttitel->charrep();
}

char* LB_STDCALL AnwendungenModel::get_name() {
	return currentname->charrep();
}

char* LB_STDCALL AnwendungenModel::get_interface() {
	return currentinterface->charrep();
}

char* LB_STDCALL AnwendungenModel::get_functor() {
	return currentfunctor->charrep();
}

char* LB_STDCALL AnwendungenModel::get_modulename() {
	return currentmodulename->charrep();
}


class lbPluginAnwendungenModel : public lb_I_PluginImpl {
public:
	lbPluginAnwendungenModel();
	
	virtual ~lbPluginAnwendungenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungenModel, lbPluginAnwendungenModel)

lbErrCodes LB_STDCALL lbPluginAnwendungenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungenModel::lbPluginAnwendungenModel() {
	_CL_VERBOSE << "lbPluginAnwendungenModel::lbPluginAnwendungenModel() called.\n" LOG_
}

lbPluginAnwendungenModel::~lbPluginAnwendungenModel() {
	_CL_VERBOSE << "lbPluginAnwendungenModel::~lbPluginAnwendungenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungenModel::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenModel == NULL) {
		AnwendungenModel* aAnwendungenModel = new AnwendungenModel();
		
	
		QI(aAnwendungenModel, lb_I_Unknown, ukAnwendungenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungenModel* aAnwendungenModel = new AnwendungenModel();
		
	
		QI(aAnwendungenModel, lb_I_Unknown, ukAnwendungenModel)
	}
	
	lb_I_Unknown* r = ukAnwendungenModel.getPtr();
	ukAnwendungenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungenModel != NULL) {
                ukAnwendungenModel--;
                ukAnwendungenModel.resetPtr();
        }
}

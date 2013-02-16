
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
#include <Generated_EntityModelAktionsschrittezuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionsschrittezuordnenModel, AktionsschrittezuordnenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionsschrittezuordnenModel)
	ADD_INTERFACE(lb_I_Aktionsschrittezuordnen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(AktionsschrittezuordnenModel)

AktionsschrittezuordnenModel::AktionsschrittezuordnenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Aktionsschrittezuordnen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currentbezeichnung)
    REQUEST(getModuleInstance(), lb_I_String, currentwhat)
    REQUEST(getModuleInstance(), lb_I_Long, currenta_order_nr)
    REQUEST(getModuleInstance(), lb_I_Long, currenttype)
    REQUEST(getModuleInstance(), lb_I_Long, currentactionid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAktionsschrittezuordnenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "AktionsschrittezuordnenModel::AktionsschrittezuordnenModel() called." LOG_
}

AktionsschrittezuordnenModel::~AktionsschrittezuordnenModel() {
	_CL_VERBOSE << "AktionsschrittezuordnenModel::~AktionsschrittezuordnenModel() called." LOG_
}

lbErrCodes LB_STDCALL AktionsschrittezuordnenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionsschrittezuordnenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL AktionsschrittezuordnenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Aktionsschrittezuordnen";
	
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

lb_I_ExtensionObject* LB_STDCALL AktionsschrittezuordnenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL AktionsschrittezuordnenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL AktionsschrittezuordnenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL AktionsschrittezuordnenModel::addAktionsschrittezuordnen(const char* _bezeichnung, const char* _what, long _a_order_nr, long _type, long _actionid,  long _AktionsschrittezuordnenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __bezeichnung)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __what)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __a_order_nr)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __type)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __actionid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __AktionsschrittezuordnenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__bezeichnung = _bezeichnung;
    *__what = _what;
    __a_order_nr->setData(_a_order_nr);
    __type->setData(_type);
    __actionid->setData(_actionid);

	
	__AktionsschrittezuordnenID->setData(_AktionsschrittezuordnenID);

    *paramname = "bezeichnung";
    param->setUAPString(*&paramname, *&__bezeichnung);
    *paramname = "what";
    param->setUAPString(*&paramname, *&__what);
    *paramname = "a_order_nr";
    param->setUAPLong(*&paramname, *&__a_order_nr);
    *paramname = "type";
    param->setUAPLong(*&paramname, *&__type);
    *paramname = "actionid";
    param->setUAPLong(*&paramname, *&__actionid);


	*paramname = "AktionsschrittezuordnenID";
	param->setUAPLong(*&paramname, *&__AktionsschrittezuordnenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__AktionsschrittezuordnenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Aktionsschrittezuordnen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL AktionsschrittezuordnenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Aktionsschrittezuordnen->finishIteration();
	while (hasMoreAktionsschrittezuordnen()) {
		setNextAktionsschrittezuordnen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Aktionsschrittezuordnen->remove(&key);
			Aktionsschrittezuordnen->finishIteration();
		}
	}
}

void		LB_STDCALL AktionsschrittezuordnenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Aktionsschrittezuordnen->finishIteration();
	while (hasMoreAktionsschrittezuordnen()) {
		setNextAktionsschrittezuordnen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Aktionsschrittezuordnen->remove(&key);
			Aktionsschrittezuordnen->finishIteration();
		}
	}
}

bool LB_STDCALL AktionsschrittezuordnenModel::selectAktionsschrittezuordnen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Aktionsschrittezuordnen->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "what";
    param->getUAPString(*&paramname, *&currentwhat);
    *paramname = "a_order_nr";
    param->getUAPLong(*&paramname, *&currenta_order_nr);
    *paramname = "type";
    param->getUAPLong(*&paramname, *&currenttype);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);


		*paramname = "AktionsschrittezuordnenID";
		param->getUAPLong(*&paramname, *&currentAktionsschrittezuordnenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL AktionsschrittezuordnenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL AktionsschrittezuordnenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL AktionsschrittezuordnenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL AktionsschrittezuordnenModel::getAktionsschrittezuordnenCount() {
	return Aktionsschrittezuordnen->Count();
}

bool  LB_STDCALL AktionsschrittezuordnenModel::hasMoreAktionsschrittezuordnen() {
	return (Aktionsschrittezuordnen->hasMoreElements() == 1);
}

void  LB_STDCALL AktionsschrittezuordnenModel::setNextAktionsschrittezuordnen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Aktionsschrittezuordnen->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "bezeichnung";
    param->getUAPString(*&paramname, *&currentbezeichnung);
    *paramname = "what";
    param->getUAPString(*&paramname, *&currentwhat);
    *paramname = "a_order_nr";
    param->getUAPLong(*&paramname, *&currenta_order_nr);
    *paramname = "type";
    param->getUAPLong(*&paramname, *&currenttype);
    *paramname = "actionid";
    param->getUAPLong(*&paramname, *&currentactionid);

	*paramname = "AktionsschrittezuordnenID";
	param->getUAPLong(*&paramname, *&currentAktionsschrittezuordnenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL AktionsschrittezuordnenModel::finishAktionsschrittezuordnenIteration() {
	Aktionsschrittezuordnen->finishIteration();
}

long LB_STDCALL AktionsschrittezuordnenModel::get_id() {
	return currentAktionsschrittezuordnenID->getData();
}


char* LB_STDCALL AktionsschrittezuordnenModel::get_bezeichnung() {
	return currentbezeichnung->charrep();
}

char* LB_STDCALL AktionsschrittezuordnenModel::get_what() {
	return currentwhat->charrep();
}

long LB_STDCALL AktionsschrittezuordnenModel::get_a_order_nr() {
	return currenta_order_nr->getData();
}

long LB_STDCALL AktionsschrittezuordnenModel::get_type() {
	return currenttype->getData();
}

long LB_STDCALL AktionsschrittezuordnenModel::get_actionid() {
	return currentactionid->getData();
}


class lbPluginAktionsschrittezuordnenModel : public lb_I_PluginImpl {
public:
	lbPluginAktionsschrittezuordnenModel();
	
	virtual ~lbPluginAktionsschrittezuordnenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionsschrittezuordnenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionsschrittezuordnenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionsschrittezuordnenModel, lbPluginAktionsschrittezuordnenModel)

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionsschrittezuordnenModel::lbPluginAktionsschrittezuordnenModel() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenModel::lbPluginAktionsschrittezuordnenModel() called.\n" LOG_
}

lbPluginAktionsschrittezuordnenModel::~lbPluginAktionsschrittezuordnenModel() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenModel::~lbPluginAktionsschrittezuordnenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionsschrittezuordnenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenModel::initialize() {
}
	
bool LB_STDCALL lbPluginAktionsschrittezuordnenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModel == NULL) {
		AktionsschrittezuordnenModel* aAktionsschrittezuordnenModel = new AktionsschrittezuordnenModel();
		
	
		QI(aAktionsschrittezuordnenModel, lb_I_Unknown, ukAktionsschrittezuordnenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionsschrittezuordnenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionsschrittezuordnenModel* aAktionsschrittezuordnenModel = new AktionsschrittezuordnenModel();
		
	
		QI(aAktionsschrittezuordnenModel, lb_I_Unknown, ukAktionsschrittezuordnenModel)
	}
	
	lb_I_Unknown* r = ukAktionsschrittezuordnenModel.getPtr();
	ukAktionsschrittezuordnenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionsschrittezuordnenModel != NULL) {
                ukAktionsschrittezuordnenModel--;
                ukAktionsschrittezuordnenModel.resetPtr();
        }
}

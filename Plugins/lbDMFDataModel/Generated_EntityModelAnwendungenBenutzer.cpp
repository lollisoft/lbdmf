
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
#include <Generated_EntityModelAnwendungenBenutzer.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungenBenutzerModel, AnwendungenBenutzerModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungenBenutzerModel)
	ADD_INTERFACE(lb_I_AnwendungenBenutzer)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(AnwendungenBenutzerModel)

AnwendungenBenutzerModel::AnwendungenBenutzerModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, AnwendungenBenutzer)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_Long, currentuserid)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungenid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentAnwendungenBenutzerID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "AnwendungenBenutzerModel::AnwendungenBenutzerModel() called." LOG_
}

AnwendungenBenutzerModel::~AnwendungenBenutzerModel() {
	_CL_VERBOSE << "AnwendungenBenutzerModel::~AnwendungenBenutzerModel() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungenBenutzerModel::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungenBenutzerModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL AnwendungenBenutzerModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_AnwendungenBenutzer";
	
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

lb_I_ExtensionObject* LB_STDCALL AnwendungenBenutzerModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL AnwendungenBenutzerModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL AnwendungenBenutzerModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL AnwendungenBenutzerModel::addAnwendungenBenutzer(long _userid, long _anwendungenid,  long _AnwendungenBenutzerID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __userid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungenid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __AnwendungenBenutzerID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __userid->setData(_userid);
    __anwendungenid->setData(_anwendungenid);

	
	__AnwendungenBenutzerID->setData(_AnwendungenBenutzerID);

    *paramname = "userid";
    param->setUAPLong(*&paramname, *&__userid);
    *paramname = "anwendungenid";
    param->setUAPLong(*&paramname, *&__anwendungenid);


	*paramname = "AnwendungenBenutzerID";
	param->setUAPLong(*&paramname, *&__AnwendungenBenutzerID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__AnwendungenBenutzerID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	AnwendungenBenutzer->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL AnwendungenBenutzerModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	AnwendungenBenutzer->finishIteration();
	while (hasMoreAnwendungenBenutzer()) {
		setNextAnwendungenBenutzer();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			AnwendungenBenutzer->remove(&key);
			AnwendungenBenutzer->finishIteration();
		}
	}
}

void		LB_STDCALL AnwendungenBenutzerModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	AnwendungenBenutzer->finishIteration();
	while (hasMoreAnwendungenBenutzer()) {
		setNextAnwendungenBenutzer();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			AnwendungenBenutzer->remove(&key);
			AnwendungenBenutzer->finishIteration();
		}
	}
}

bool LB_STDCALL AnwendungenBenutzerModel::selectAnwendungenBenutzer(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = AnwendungenBenutzer->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "userid";
    param->getUAPLong(*&paramname, *&currentuserid);
    *paramname = "anwendungenid";
    param->getUAPLong(*&paramname, *&currentanwendungenid);


		*paramname = "AnwendungenBenutzerID";
		param->getUAPLong(*&paramname, *&currentAnwendungenBenutzerID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL AnwendungenBenutzerModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL AnwendungenBenutzerModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL AnwendungenBenutzerModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL AnwendungenBenutzerModel::getAnwendungenBenutzerCount() {
	return AnwendungenBenutzer->Count();
}

bool  LB_STDCALL AnwendungenBenutzerModel::hasMoreAnwendungenBenutzer() {
	return (AnwendungenBenutzer->hasMoreElements() == 1);
}

void  LB_STDCALL AnwendungenBenutzerModel::setNextAnwendungenBenutzer() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = AnwendungenBenutzer->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "userid";
    param->getUAPLong(*&paramname, *&currentuserid);
    *paramname = "anwendungenid";
    param->getUAPLong(*&paramname, *&currentanwendungenid);

	*paramname = "AnwendungenBenutzerID";
	param->getUAPLong(*&paramname, *&currentAnwendungenBenutzerID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL AnwendungenBenutzerModel::finishAnwendungenBenutzerIteration() {
	AnwendungenBenutzer->finishIteration();
}

long LB_STDCALL AnwendungenBenutzerModel::get_id() {
	return currentAnwendungenBenutzerID->getData();
}


long LB_STDCALL AnwendungenBenutzerModel::get_userid() {
	return currentuserid->getData();
}

long LB_STDCALL AnwendungenBenutzerModel::get_anwendungenid() {
	return currentanwendungenid->getData();
}


class lbPluginAnwendungenBenutzerModel : public lb_I_PluginImpl {
public:
	lbPluginAnwendungenBenutzerModel();
	
	virtual ~lbPluginAnwendungenBenutzerModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungenBenutzerModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungenBenutzerModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungenBenutzerModel, lbPluginAnwendungenBenutzerModel)

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungenBenutzerModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungenBenutzerModel::lbPluginAnwendungenBenutzerModel() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerModel::lbPluginAnwendungenBenutzerModel() called.\n" LOG_
}

lbPluginAnwendungenBenutzerModel::~lbPluginAnwendungenBenutzerModel() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerModel::~lbPluginAnwendungenBenutzerModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungenBenutzerModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungenBenutzerModel::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungenBenutzerModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModel == NULL) {
		AnwendungenBenutzerModel* aAnwendungenBenutzerModel = new AnwendungenBenutzerModel();
		
	
		QI(aAnwendungenBenutzerModel, lb_I_Unknown, ukAnwendungenBenutzerModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungenBenutzerModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungenBenutzerModel* aAnwendungenBenutzerModel = new AnwendungenBenutzerModel();
		
	
		QI(aAnwendungenBenutzerModel, lb_I_Unknown, ukAnwendungenBenutzerModel)
	}
	
	lb_I_Unknown* r = ukAnwendungenBenutzerModel.getPtr();
	ukAnwendungenBenutzerModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungenBenutzerModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungenBenutzerModel != NULL) {
                ukAnwendungenBenutzerModel--;
                ukAnwendungenBenutzerModel.resetPtr();
        }
}

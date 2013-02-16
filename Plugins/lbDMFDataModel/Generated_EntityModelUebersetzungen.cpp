
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
#include <Generated_EntityModelUebersetzungen.h>

IMPLEMENT_FUNCTOR(instanceOfUebersetzungenModel, UebersetzungenModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(UebersetzungenModel)
	ADD_INTERFACE(lb_I_Uebersetzungen)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(UebersetzungenModel)

UebersetzungenModel::UebersetzungenModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Uebersetzungen)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currenttranslated)
    REQUEST(getModuleInstance(), lb_I_String, currenttext)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentUebersetzungenID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "UebersetzungenModel::UebersetzungenModel() called." LOG_
}

UebersetzungenModel::~UebersetzungenModel() {
	_CL_VERBOSE << "UebersetzungenModel::~UebersetzungenModel() called." LOG_
}

lbErrCodes LB_STDCALL UebersetzungenModel::setData(lb_I_Unknown*) {
	_LOG << "Error: UebersetzungenModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL UebersetzungenModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Uebersetzungen";
	
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

lb_I_ExtensionObject* LB_STDCALL UebersetzungenModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL UebersetzungenModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL UebersetzungenModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL UebersetzungenModel::addUebersetzungen(const char* _translated, const char* _text,  long _UebersetzungenID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __translated)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __text)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __UebersetzungenID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__translated = _translated;
    *__text = _text;

	
	__UebersetzungenID->setData(_UebersetzungenID);

    *paramname = "translated";
    param->setUAPString(*&paramname, *&__translated);
    *paramname = "text";
    param->setUAPString(*&paramname, *&__text);


	*paramname = "UebersetzungenID";
	param->setUAPLong(*&paramname, *&__UebersetzungenID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__UebersetzungenID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Uebersetzungen->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL UebersetzungenModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Uebersetzungen->finishIteration();
	while (hasMoreUebersetzungen()) {
		setNextUebersetzungen();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Uebersetzungen->remove(&key);
			Uebersetzungen->finishIteration();
		}
	}
}

void		LB_STDCALL UebersetzungenModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Uebersetzungen->finishIteration();
	while (hasMoreUebersetzungen()) {
		setNextUebersetzungen();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Uebersetzungen->remove(&key);
			Uebersetzungen->finishIteration();
		}
	}
}

bool LB_STDCALL UebersetzungenModel::selectUebersetzungen(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Uebersetzungen->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "translated";
    param->getUAPString(*&paramname, *&currenttranslated);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);


		*paramname = "UebersetzungenID";
		param->getUAPLong(*&paramname, *&currentUebersetzungenID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL UebersetzungenModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL UebersetzungenModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL UebersetzungenModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL UebersetzungenModel::getUebersetzungenCount() {
	return Uebersetzungen->Count();
}

bool  LB_STDCALL UebersetzungenModel::hasMoreUebersetzungen() {
	return (Uebersetzungen->hasMoreElements() == 1);
}

void  LB_STDCALL UebersetzungenModel::setNextUebersetzungen() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Uebersetzungen->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "translated";
    param->getUAPString(*&paramname, *&currenttranslated);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);

	*paramname = "UebersetzungenID";
	param->getUAPLong(*&paramname, *&currentUebersetzungenID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL UebersetzungenModel::finishUebersetzungenIteration() {
	Uebersetzungen->finishIteration();
}

long LB_STDCALL UebersetzungenModel::get_id() {
	return currentUebersetzungenID->getData();
}


char* LB_STDCALL UebersetzungenModel::get_translated() {
	return currenttranslated->charrep();
}

char* LB_STDCALL UebersetzungenModel::get_text() {
	return currenttext->charrep();
}


class lbPluginUebersetzungenModel : public lb_I_PluginImpl {
public:
	lbPluginUebersetzungenModel();
	
	virtual ~lbPluginUebersetzungenModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUebersetzungenModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUebersetzungenModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUebersetzungenModel, lbPluginUebersetzungenModel)

lbErrCodes LB_STDCALL lbPluginUebersetzungenModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUebersetzungenModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUebersetzungenModel::lbPluginUebersetzungenModel() {
	_CL_VERBOSE << "lbPluginUebersetzungenModel::lbPluginUebersetzungenModel() called.\n" LOG_
}

lbPluginUebersetzungenModel::~lbPluginUebersetzungenModel() {
	_CL_VERBOSE << "lbPluginUebersetzungenModel::~lbPluginUebersetzungenModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginUebersetzungenModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUebersetzungenModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUebersetzungenModel::initialize() {
}
	
bool LB_STDCALL lbPluginUebersetzungenModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUebersetzungenModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUebersetzungenModel == NULL) {
		UebersetzungenModel* aUebersetzungenModel = new UebersetzungenModel();
		
	
		QI(aUebersetzungenModel, lb_I_Unknown, ukUebersetzungenModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUebersetzungenModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUebersetzungenModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUebersetzungenModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		UebersetzungenModel* aUebersetzungenModel = new UebersetzungenModel();
		
	
		QI(aUebersetzungenModel, lb_I_Unknown, ukUebersetzungenModel)
	}
	
	lb_I_Unknown* r = ukUebersetzungenModel.getPtr();
	ukUebersetzungenModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUebersetzungenModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUebersetzungenModel != NULL) {
                ukUebersetzungenModel--;
                ukUebersetzungenModel.resetPtr();
        }
}

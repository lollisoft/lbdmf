
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
#include <Generated_EntityModelTranslations.h>

IMPLEMENT_FUNCTOR(instanceOfTranslationsModel, TranslationsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(TranslationsModel)
	ADD_INTERFACE(lb_I_Translations)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(TranslationsModel)

TranslationsModel::TranslationsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Translations)
	REQUEST(getModuleInstance(), lb_I_Container, objectExtensions)

    REQUEST(getModuleInstance(), lb_I_String, currenttranslated)
    REQUEST(getModuleInstance(), lb_I_String, currenttext)
    REQUEST(getModuleInstance(), lb_I_String, currentlanguage)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentTranslationsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "TranslationsModel::TranslationsModel() called." LOG_
}

TranslationsModel::~TranslationsModel() {
	_CL_VERBOSE << "TranslationsModel::~TranslationsModel() called." LOG_
}

lbErrCodes LB_STDCALL TranslationsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: TranslationsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

#ifdef bla
lb_I_ExtensionObject* LB_STDCALL TranslationsModel::getExtension(lb_I_String* contextnamespace) {
	// Lookup the matching extension by the context namespace.
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_String, CNS)
	*CNS = contextnamespace;
	*CNS += "_For_Translations";
	
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

lb_I_ExtensionObject* LB_STDCALL TranslationsModel::getExtension(const char* contextnamespace) {
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

	
lbErrCodes LB_STDCALL TranslationsModel::addExtension(lb_I_String* contextnamespace, lb_I_ExtensionObject* extension) {

}

lbErrCodes LB_STDCALL TranslationsModel::addExtension(const char* contextnamespace, lb_I_ExtensionObject* extension) {

}
#endif

long  LB_STDCALL TranslationsModel::addTranslations(const char* _translated, const char* _text, const char* _language,  long _TranslationsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __translated)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __text)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __language)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __TranslationsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__translated = _translated;
    *__text = _text;
    *__language = _language;

	
	__TranslationsID->setData(_TranslationsID);

    *paramname = "translated";
    param->setUAPString(*&paramname, *&__translated);
    *paramname = "text";
    param->setUAPString(*&paramname, *&__text);
    *paramname = "language";
    param->setUAPString(*&paramname, *&__language);


	*paramname = "TranslationsID";
	param->setUAPLong(*&paramname, *&__TranslationsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__TranslationsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Translations->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL TranslationsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Translations->finishIteration();
	while (hasMoreTranslations()) {
		setNextTranslations();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Translations->remove(&key);
			Translations->finishIteration();
		}
	}
}

void		LB_STDCALL TranslationsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Translations->finishIteration();
	while (hasMoreTranslations()) {
		setNextTranslations();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Translations->remove(&key);
			Translations->finishIteration();
		}
	}
}

bool LB_STDCALL TranslationsModel::selectTranslations(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Translations->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "translated";
    param->getUAPString(*&paramname, *&currenttranslated);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);
    *paramname = "language";
    param->getUAPString(*&paramname, *&currentlanguage);


		*paramname = "TranslationsID";
		param->getUAPLong(*&paramname, *&currentTranslationsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL TranslationsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL TranslationsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL TranslationsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL TranslationsModel::getTranslationsCount() {
	return Translations->Count();
}

bool  LB_STDCALL TranslationsModel::hasMoreTranslations() {
	return (Translations->hasMoreElements() == 1);
}

void  LB_STDCALL TranslationsModel::setNextTranslations() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Translations->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "translated";
    param->getUAPString(*&paramname, *&currenttranslated);
    *paramname = "text";
    param->getUAPString(*&paramname, *&currenttext);
    *paramname = "language";
    param->getUAPString(*&paramname, *&currentlanguage);

	*paramname = "TranslationsID";
	param->getUAPLong(*&paramname, *&currentTranslationsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL TranslationsModel::finishTranslationsIteration() {
	Translations->finishIteration();
}

long LB_STDCALL TranslationsModel::get_id() {
	return currentTranslationsID->getData();
}


char* LB_STDCALL TranslationsModel::get_translated() {
	return currenttranslated->charrep();
}

char* LB_STDCALL TranslationsModel::get_text() {
	return currenttext->charrep();
}

char* LB_STDCALL TranslationsModel::get_language() {
	return currentlanguage->charrep();
}


class lbPluginTranslationsModel : public lb_I_PluginImpl {
public:
	lbPluginTranslationsModel();
	
	virtual ~lbPluginTranslationsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukTranslationsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginTranslationsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginTranslationsModel, lbPluginTranslationsModel)

lbErrCodes LB_STDCALL lbPluginTranslationsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginTranslationsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginTranslationsModel::lbPluginTranslationsModel() {
	_CL_VERBOSE << "lbPluginTranslationsModel::lbPluginTranslationsModel() called.\n" LOG_
}

lbPluginTranslationsModel::~lbPluginTranslationsModel() {
	_CL_VERBOSE << "lbPluginTranslationsModel::~lbPluginTranslationsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginTranslationsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginTranslationsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginTranslationsModel::initialize() {
}
	
bool LB_STDCALL lbPluginTranslationsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginTranslationsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslationsModel == NULL) {
		TranslationsModel* aTranslationsModel = new TranslationsModel();
		
	
		QI(aTranslationsModel, lb_I_Unknown, ukTranslationsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTranslationsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginTranslationsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslationsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		TranslationsModel* aTranslationsModel = new TranslationsModel();
		
	
		QI(aTranslationsModel, lb_I_Unknown, ukTranslationsModel)
	}
	
	lb_I_Unknown* r = ukTranslationsModel.getPtr();
	ukTranslationsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginTranslationsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukTranslationsModel != NULL) {
                ukTranslationsModel--;
                ukTranslationsModel.resetPtr();
        }
}

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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif

#include <lbConfigHook.h>

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbTranslationsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbTranslationsModel, lbTranslationsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbTranslationsModel)
	ADD_INTERFACE(lb_I_Translations)
END_IMPLEMENT_LB_UNKNOWN()


lbTranslationsModel::lbTranslationsModel() {
	ref = STARTREF;

	REQUEST(getModuleInstance(), lb_I_Container, Translations)
	REQUEST(getModuleInstance(), lb_I_Container, Lookup)
	REQUEST(getModuleInstance(), lb_I_Long, currentTranslationID)
	REQUEST(getModuleInstance(), lb_I_String, currentTranslationLanguage)
	REQUEST(getModuleInstance(), lb_I_String, currentTranslationText)
	REQUEST(getModuleInstance(), lb_I_String, currentTranslationTranslated)

	_CL_LOG << "lbTranslationsModel::lbTranslationsModel() called." LOG_
}

lbTranslationsModel::~lbTranslationsModel() {
	_CL_LOG << "lbTranslationsModel::~lbTranslationsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbTranslationsModel::setData(lb_I_Unknown*) {
	_CL_LOG << "Error: lbTranslationsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbTranslationsModel::addTranslation(const char* text, const char* translated, const char* language, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Text)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Translated)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Language)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	UAP(lb_I_KeyBase, keyText)

	_CL_VERBOSE << "lbTranslationsModel::addTranslation('" << text << "', '" << translated << "', '" << language << "', '" << _id << "') called." LOG_

	*Text = text;
	*Translated = translated;
	*Language = language;
	ID->setData(_id);
	
	*paramname = "Text";
	param->setUAPString(*&paramname, *&Text);
	*paramname = "Translated";
	param->setUAPString(*&paramname, *&Translated);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "Language";
	param->setUAPString(*&paramname, *&Language);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	UAP(lb_I_Unknown, ukKey)
	QI(ID, lb_I_KeyBase, key)
	QI(ID, lb_I_Unknown, ukKey)
	QI(param, lb_I_Unknown, ukParam)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, lookupKey)
	*lookupKey = Text->charrep();
	*lookupKey += "-";
	*lookupKey += Language->charrep();
	
	QI(lookupKey, lb_I_KeyBase, keyText)
	
	Translations->insert(&ukParam, &key);
	Lookup->insert(&ukKey, &keyText);

	return -1;
}

bool  LB_STDCALL lbTranslationsModel::selectText(const char* text, const char* language) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, ukKey)
	UAP_REQUEST(manager.getPtr(), lb_I_String, lookupKey)
	*lookupKey = text;
	*lookupKey += "-";
	*lookupKey += language;

	QI(lookupKey, lb_I_KeyBase, ukKey)
	
	uk = Lookup->getElement(&ukKey);
	
	if (uk != NULL) {
		UAP(lb_I_Long, ID)
		QI(uk, lb_I_Long, ID)
		
		if (ID != NULL) {
			selectTranslation(ID->getData());
			return true;
		}
	}
	
	return false;
}

bool  LB_STDCALL lbTranslationsModel::selectTranslation(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Translations->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Text";
		param->getUAPString(*&name, *&currentTranslationText);
		*name = "Translated";
		param->getUAPString(*&name, *&currentTranslationTranslated);
		*name = "ID";
		param->getUAPLong(*&name, *&currentTranslationID);
		*name = "Language";
		param->getUAPString(*&name, *&currentTranslationLanguage);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbTranslationsModel::getTranslationsCount() {
	return Translations->Count();
}

bool  LB_STDCALL lbTranslationsModel::hasMoreTranslations() {
	return Translations->hasMoreElements();
}

void  LB_STDCALL lbTranslationsModel::setNextTranslation() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Translations->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Text";
	param->getUAPString(*&name, *&currentTranslationText);
	*name = "Translated";
	param->getUAPString(*&name, *&currentTranslationTranslated);
	*name = "ID";
	param->getUAPLong(*&name, *&currentTranslationID);
	*name = "Language";
	param->getUAPString(*&name, *&currentTranslationLanguage);
}

void  LB_STDCALL lbTranslationsModel::finishTranslationIteration() {
	Translations->finishIteration();
}

long LB_STDCALL lbTranslationsModel::getTranslationID() {
	return currentTranslationID->getData();
}

char*  LB_STDCALL lbTranslationsModel::getTranslationText() {
	return currentTranslationText->charrep();
}

char*  LB_STDCALL lbTranslationsModel::getTranslationTranslated() {
	return currentTranslationTranslated->charrep();
}

char* LB_STDCALL lbTranslationsModel::getTranslationLanguage() {
	return currentTranslationLanguage->charrep();
}

/*...sclass lbPluginTranslationsModel implementation:0:*/
/*...slbPluginTranslationsModel:0:*/
class lbPluginTranslationsModel : public lb_I_PluginImpl {
public:
	lbPluginTranslationsModel();
	
	virtual ~lbPluginTranslationsModel();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukTranslations)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginTranslationsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginTranslationsModel, lbPluginTranslationsModel)

/*...slbErrCodes LB_STDCALL lbPluginTranslationsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginTranslationsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginTranslationsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginTranslationsModel::lbPluginTranslationsModel() {
	_LOG << "lbPluginTranslationsModel::lbPluginTranslationsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginTranslationsModel::~lbPluginTranslationsModel() {
	_LOG << "lbPluginTranslationsModel::~lbPluginTranslationsModel() called.\n" LOG_
}

void LB_STDCALL lbPluginTranslationsModel::initialize() {
}
	
bool LB_STDCALL lbPluginTranslationsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginTranslationsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginTranslationsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslations == NULL) {
		lbTranslationsModel* TranslationsModel = new lbTranslationsModel();
		TranslationsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(TranslationsModel, lb_I_Unknown, ukTranslations)
	} else {
		_CL_VERBOSE << "lbPluginTranslationModel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukTranslations.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginTranslationsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginTranslationsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukTranslations == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbTranslationsModel* TranslationsModel = new lbTranslationsModel();
		TranslationsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(TranslationsModel, lb_I_Unknown, ukTranslations)
	}
	
	lb_I_Unknown* r = ukTranslations.getPtr();
	ukTranslations.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginTranslationsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukTranslations != NULL) {
                ukTranslations--;
                ukTranslations.resetPtr();
        }
}
/*...e*/
/*...e*/




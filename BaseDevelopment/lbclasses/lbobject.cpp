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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4101 )
#pragma warning( disable: 4172 )

#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <lbobject.h>
#include <lbkey.h>

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfInteger, lbInteger)
IMPLEMENT_FUNCTOR(instanceOfBinaryData, lbBinaryData)
IMPLEMENT_FUNCTOR(instanceOfFileLocation, lbFileLocation)
IMPLEMENT_FUNCTOR(instanceOfDirLocation, lbDirLocation)
IMPLEMENT_FUNCTOR(instanceOfLong, lbLong)
IMPLEMENT_FUNCTOR(instanceOfBoolean, lbBoolean)
IMPLEMENT_FUNCTOR(instanceOfString, lbString)
#ifndef _MSC_VER
IMPLEMENT_FUNCTOR(instanceOfReference, lbReference)
#endif
IMPLEMENT_FUNCTOR(instanceOfParameter, lbParameter)

IMPLEMENT_FUNCTOR(instanceOfLocale, lbLocale)

#ifdef __cplusplus
}
#endif            


/*...slbLocale:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbLocale)
        ADD_INTERFACE(lb_I_Locale)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLocale::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}

/// \todo Use environment variable to select language.
lbLocale::lbLocale() {
	ref = STARTREF;
	_lang = (char*) malloc(100);
	_lang[0] = 0;
	strcpy(_lang, "german");
	dbAvailable = true;
	//REQUEST(getModuleInstance(), lb_I_Translations, translations)
}

lbLocale::~lbLocale() {
	if (_lang) free(_lang);
	_CL_LOG << "lbLocale::~lbLocale() called." LOG_
}

void LB_STDCALL lbLocale::setLanguage(char const * lang) {
	if (_lang) free(_lang);
	_lang = (char*) malloc(strlen(lang)+1);
	_lang[0] = 0;
	strcpy(_lang, lang);
}

void LB_STDCALL lbLocale::setTranslationData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	QI(uk, lb_I_Translations, translations)
}


/*...svoid LB_STDCALL lbLocale\58\\58\translate\40\char \42\\42\ text\44\ char const \42\ to_translate\41\:0:*/
/// \todo Add default language in insert statement. This enables automatic creation of new languages, if selected.
void LB_STDCALL lbLocale::translate(char ** text, char const * to_translate) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	if (translations == NULL) {
		UAP(lb_I_Database, database)
		
		char* dbbackend = meta->getApplicationDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}
		
		_LOG << "Translate text with SQL statements..." LOG_
		
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		if (!dbAvailable || database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			_LOG << "lbLocale::translate() Error: Failed to connect to the database." LOG_
			dbAvailable = false;
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate)+1);
			*text[0] = 0;
			strcpy(*text, to_translate);
			if (temp) free(temp);
			return;
		}
		
		UAP(lb_I_Query, sampleQuery)
			
			sampleQuery = database->getQuery("lbDMF", 0);
		
		char buffer[800] = "";
		
		sprintf(buffer, "select translated from translations where language = '%s' and text = '%s'", _lang, to_translate);
		
		sampleQuery->skipFKCollecting();
		sampleQuery->query(buffer);
		
		// Fill up the available applications for that user.
		
		lbErrCodes err = sampleQuery->first();
		
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			
	        UAP_REQUEST(manager.getPtr(), lb_I_String, s1)
			
	        s1 = sampleQuery->getAsString(1);
			
			char* temp = *text;
			
			if (strcmp(s1->charrep(), "") == 0) {
				*text = (char*) malloc(strlen(to_translate) + 1);
				*text[0] = 0;
				strcpy(*text, to_translate);
			} else {
				*text = (char*) malloc(strlen(s1->charrep()) + 1);
				*text[0] = 0;
				strcpy(*text, s1->charrep());
			}
			if (temp) free(temp);
		} else {
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate) + 1);
			*text[0] = 0;
			if (temp) free(temp);
			
			_LOG << "Translation for '" << to_translate << "' not found. Insert into database" LOG_
				
				buffer[0] = 0;
			
			sprintf(buffer, "insert into translations (text, translated, language) values('%s', '%s', '%s')", to_translate, to_translate, _lang);
			
			/* Sybase SQL Anywhere 5.5 has problems with state 24000. Maybe an auto commit problem */
			UAP(lb_I_Query, sampleQuery1)
				sampleQuery1 = database->getQuery("lbDMF", 0);
			sampleQuery1->skipFKCollecting();
			sampleQuery1->query(buffer);
			sampleQuery1->enableFKCollecting();
			
			strcpy(*text, to_translate);
		}
		
		sampleQuery->enableFKCollecting();
	} else {
		if (translations->selectText(to_translate, _lang) == false) {
			UAP(lb_I_Database, database)
			
			char* dbbackend = meta->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}
			
			_LOG << "Translate text with SQL statements..." LOG_
			
			database->init();
			
			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";
			
			if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
				char* temp = *text;
				*text = (char*) malloc(strlen(to_translate)+1);
				*text[0] = 0;
				strcpy(*text, to_translate);
				if (temp) free(temp);
				return;
			}
			char buffer[800] = "";
			char* temp = *text;
			*text = (char*) malloc(strlen(to_translate) + 1);
			*text[0] = 0;
			if (temp) free(temp);
			
			_LOG << "Translation for '" << to_translate << "' not found. Insert into database" LOG_
				
				buffer[0] = 0;
			
			sprintf(buffer, "insert into translations (text, translated, language) values('%s', '%s', '%s')", to_translate, to_translate, _lang);
			
			/* Sybase SQL Anywhere 5.5 has problems with state 24000. Maybe an auto commit problem */
			UAP(lb_I_Query, sampleQuery1)
				sampleQuery1 = database->getQuery("lbDMF", 0);
			sampleQuery1->skipFKCollecting();
			
			sampleQuery1->query(buffer);
			sampleQuery1->enableFKCollecting();
			
			// Also store into translations object.
			
			translations->addTranslation(to_translate, *text, _lang);
			
			strcpy(*text, to_translate);
		} else {
			UAP_REQUEST(manager.getPtr(), lb_I_String, s1)
			char* temp = *text;
			
			*s1 = translations->getTranslationTranslated();
			
			if (strcmp(s1->charrep(), "") == 0) {
				*text = (char*) malloc(strlen(to_translate) + 1);
				*text[0] = 0;
				strcpy(*text, to_translate);
			} else {
				*text = (char*) malloc(strlen(s1->charrep()) + 1);
				*text[0] = 0;
				strcpy(*text, s1->charrep());
			}
			if (temp) free(temp);
		}
	}
}
/*...e*/
/*...e*/
/*...slbParameter:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbParameter)
	ADD_INTERFACE(lb_I_Parameter)
END_IMPLEMENT_LB_UNKNOWN()

lb_I_Container* LB_STDCALL lbParameter::getParameterList() {
	if (parameters == NULL) return NULL;
	
	parameters++;
	
	return parameters.getPtr();
}

lbErrCodes LB_STDCALL lbParameter::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Parameter, source)
	QI(uk, lb_I_Parameter, source)
	
	if (source != NULL) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Container, c)
		
		c = source->getParameterList();
		
		uk = c->clone(__FILE__, __LINE__);
		
		QI(uk, lb_I_Container,  parameters)
	}
		
	return ERR_NOT_IMPLEMENTED;
}

int LB_STDCALL lbParameter::Count() {
	if (parameters == NULL) return 0;
	return parameters->Count();
}

void LB_STDCALL lbParameter::setCloning(bool doClone) {
	cloning = doClone;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	parameters->setCloning(cloning);
}


void LB_STDCALL lbParameter::setUAPContainer(lb_I_String*& parameter, lb_I_Container*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
		parameters->setCloning(cloning);
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)

	if (parameters->exists(&k_parameter)) {
		parameters->remove(&k_parameter);
	}
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPContainer(lb_I_String*& parameter, lb_I_Container*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;
	
	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_container)

	uk_p_container = parameters->getElement(&key);

	if (uk_p_container == NULL) return ERR_PARAM_NOT_FOUND;

	p->setData(*&uk_p_container);
	
	return ERR_NONE;
}






void LB_STDCALL lbParameter::setUAPString(lb_I_String*& parameter, lb_I_String*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPString(lb_I_String*& parameter, lb_I_String*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;
	
	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_string)

	uk_p_string = parameters->getElement(&key);

	if (uk_p_string == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_String, string)
	QI(uk_p_string, lb_I_String, string)
	
	
	p->setData(string->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPParameter(lb_I_String*& parameter, lb_I_Parameter*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;
	
	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_parameter)

	uk_p_parameter = parameters->getElement(&key);

	if (uk_p_parameter == NULL) return ERR_PARAM_NOT_FOUND;

	p->setData(*&uk_p_parameter);
		
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPLong(lb_I_String*& parameter, lb_I_Long*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPLong(lb_I_String*& parameter, lb_I_Long*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_integer)

	uk_p_integer = parameters->getElement(&key);

	if (uk_p_integer == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_Long, integer)
	QI(uk_p_integer, lb_I_Long, integer)
	
	if (integer.getPtr() != NULL) p->setData(integer->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_integer)

	uk_p_integer = parameters->getElement(&key);

	if (uk_p_integer == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_Integer, integer)
	QI(uk_p_integer, lb_I_Integer, integer)
	
	if (integer.getPtr() != NULL) p->setData(integer->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPFileLocation(lb_I_String*& parameter, lb_I_FileLocation*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_fileloc)

	uk_p_fileloc = parameters->getElement(&key);

	if (uk_p_fileloc == NULL) {
		_LOG << "Error: Parameter not found." LOG_
		return ERR_PARAM_NOT_FOUND;
	}
	
	UAP(lb_I_FileLocation, fileloc)
	QI(uk_p_fileloc, lb_I_FileLocation, fileloc)
	
	if (fileloc.getPtr() != NULL) p->setData(fileloc->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPDirLocation(lb_I_String*& parameter, lb_I_DirLocation*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_fileloc)

	uk_p_fileloc = parameters->getElement(&key);

	if (uk_p_fileloc == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_DirLocation, fileloc)
	QI(uk_p_fileloc, lb_I_DirLocation, fileloc)
	
	if (fileloc.getPtr() != NULL) p->setData(fileloc->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::setUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p) {
	lbErrCodes err = ERR_NONE;
	if (parameters == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, parameters)
		if (parameters == NULL) {
			_LOG << "Error: Could not get container instance for parameres" LOG_
			return;
		}
	}	
	
	UAP(lb_I_KeyBase, k_parameter)
	QI(parameter, lb_I_KeyBase, k_parameter)

	UAP(lb_I_Unknown, uk_p)
	QI(p, lb_I_Unknown, uk_p)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPBoolean(lb_I_String*& parameter, lb_I_Boolean*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key)
	QI(pp, lb_I_KeyBase, key)
	
	UAP(lb_I_Unknown, uk_p_boolean)

	uk_p_boolean = parameters->getElement(&key);

	if (uk_p_boolean == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_Boolean, _bool)
	QI(uk_p_boolean, lb_I_Boolean, _bool)
	
	if (_bool.getPtr() != NULL) p->setData(_bool->getData());
	
	
	return ERR_NONE;
}

void LB_STDCALL lbParameter::delParameter(lb_I_String*& parameter) {
	lbErrCodes err = ERR_NONE;
	if (parameters != NULL) {
		UAP(lb_I_KeyBase, key)
		QI(parameter, lb_I_KeyBase, key)

		if (parameters->exists(&key) == 1) {
			parameters->remove(&key);
		}
	}
}

/*...e*/
/*...slbReference:0:*/
#ifndef _MSC_VER
BEGIN_IMPLEMENT_LB_UNKNOWN(lbReference)
	ADD_INTERFACE(lb_I_Reference)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbReference::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbReference::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbReference::set(lb_I_Unknown* r) {
	
	_r = r;
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbReference::get(lb_I_Unknown*& r) {
	
	r = _r.getPtr();
	
	return ERR_NONE;
}
#endif
/*...e*/
/*...slbString:0:*/
lbString::lbString() {
	ref = STARTREF;
	stringdata = NULL;
	buffersize = 0L;
}

lbString::~lbString() {

	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	_CL_VERBOSE << "lbString::~lbString() called. Data is " << stringdata << ", this is " << ptr LOG_

	if (stringdata != NULL) free(stringdata);
	
	stringdata = NULL;
}

lb_I_String& LB_STDCALL lbString::operator += (const lb_I_String* toAppend) {
		return *this += toAppend->charrep();
}

lb_I_String& LB_STDCALL lbString::operator += (const char* toAppend) {
	char* temp = stringdata;

	if (stringdata == NULL) {
		buffersize = strlen(toAppend)+1;
		stringdata = (char*) malloc(buffersize);
		stringdata[0] = 0;
	} else {
		long s = strlen(stringdata)+strlen(toAppend)*2;
		if (buffersize >= s) {
		} else {
			buffersize = s;
			stringdata = (char*) malloc(s);
			stringdata[0] = 0;
			strcat(stringdata, temp);
			free(temp);
		}
	}

	if (toAppend != NULL) strcat(stringdata, toAppend);
	
	return *this;
}

int LB_STDCALL lbString::operator == (const char* toCompare) const {
	return strcmp(charrep(), toCompare) == 0;
}

int LB_STDCALL lbString::operator == (const lb_I_String* toCompare) const {
	return strcmp(charrep(), toCompare->charrep()) == 0;
}

lb_I_String& LB_STDCALL lbString::operator = (const lb_I_String* toAppend) {
		return *this = toAppend->charrep();
}

lb_I_String& LB_STDCALL lbString::operator = (const char* toAppend) {
	if (toAppend == NULL) {
		setData("");
		return *this;
	}

    long s = strlen(toAppend)+1;
	
	if (stringdata == NULL) {
		buffersize = s;
		stringdata = (char*) malloc(s);
		stringdata[0] = 0;
		strcat(stringdata, toAppend);
	} else {
		if (buffersize >= s) {
			// Buffer is big enough
			stringdata[0] = 0;
			strcat(stringdata, toAppend);
		} else {
			char* temp = stringdata;
			buffersize = s;
			stringdata = (char*) malloc(s);
			stringdata[0] = 0;
			strcat(stringdata, toAppend);
			free(temp);
		}
	}
	
	return *this;
}

lb_I_String& LB_STDCALL lbString::replace(const char* toReplace, const char* with) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
	
	bool trailing = false;

	char* temp = (char*) malloc(strlen(stringdata)+1);
	
	temp[0] = 0;
	int ii = 0;
	
	for (int i = strlen(stringdata)-1; i >= 0; i--) {
		temp[ii++] = stringdata[i];
	}
	
	if (strncmp(temp, toReplace, strlen(toReplace)) == 0) trailing = true;
	
	free(temp);
	
	char* token = strtok(stringdata, toReplace);

	if ((token != NULL) && (token != stringdata)) {
		*rep += with;
	} 
	
	while(token != NULL) 
	{ 
		*rep += token;
		token = strtok(NULL, toReplace); 
		if (token != NULL) *rep += with;
	} 
	
	if (trailing) *rep += with;
	
	setData(rep->charrep());
	
	return *this;
}


void LB_STDCALL lbString::setData(char const * p) {
	if (stringdata != NULL) free(stringdata);
	
	stringdata = NULL;
	
	if (p == NULL) return;

	buffersize = strlen(p)+1;
	stringdata = (char*) malloc(strlen(p)+1);
	stringdata[0] = 0;
	strcpy(stringdata, p);
}

#define NUL '\0'
/// \brief Code borrowed from http://c.snippets.org/index.php#TOP
char* LB_STDCALL lbString::stristr(const char *String, const char *Pattern)
{
      char *pptr, *sptr, *start;

      for (start = (char *)String; *start != NUL; start++)
      {
            /* find start of pattern in string */
            for ( ; ((*start!=NUL) && (toupper(*start) != toupper(*Pattern))); start++)
                  ;
            if (NUL == *start)
                  return NULL;

            pptr = (char *)Pattern;
            sptr = (char *)start;

            while (toupper(*sptr) == toupper(*pptr))
            {
                  sptr++;
                  pptr++;

                  /* if end of pattern then pattern was found */

                  if (NUL == *pptr)
                        return (start);
            }
      }
      return NULL;
}

void LB_STDCALL lbString::trim() {
	while (stringdata[strlen(stringdata)-1] == ' ') 
		stringdata[strlen(stringdata)-1] = 0;
}

void LB_STDCALL lbString::toLower() {
	for (int i = 0; i < strlen(stringdata); i++) {
		stringdata[i] = tolower(stringdata[i]);
	}
}

char* LB_STDCALL lbString::getData() const {
	return stringdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbString)
	ADD_INTERFACE(lb_I_String)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbString::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
	UAP(lb_I_String, string)
	
	QI(uk, lb_I_String, string)
	
	if (string != NULL) {
		setData(string->charrep());
	}
	
	return ERR_NONE;
}

/*...sKey:0:*/
char* LB_STDCALL lbString::getKeyType() const {
    return "string";
}

int LB_STDCALL lbString::equals(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        printf("Stringvergleich %s == %s = %d\n", 
        	stringdata, 
        	((const lbString*) _key)->stringdata, 
        	strcmp(stringdata, ((const lbString*) _key)->stringdata));
#endif        	
/*...e*/
	return strcmp(stringdata, ((const lbString*) _key)->stringdata) == 0 ? 1 : 0;
    } else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbString::greater(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(stringdata, ((const lbString*) _key)->stringdata) > 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbString::lessthan(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(stringdata, ((const lbString*) _key)->stringdata) < 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

char* LB_STDCALL lbString::charrep() const {
	// No need for an extra key representation.
    return stringdata;
}
/*...e*/
/*...e*/
/*...slbFileLocation:0:*/
lbFileLocation::lbFileLocation() {
	ref = STARTREF;
	_path = NULL;
}

lbFileLocation::~lbFileLocation() {
	if (_path != NULL) free(_path);
}

void lbFileLocation::setData(char* path) {
	if (_path != NULL) free(_path);
	if (path == NULL) {
		_path = strdup("");
		return;
	}
	_path = strdup(path);
}

char* lbFileLocation::getData() const {
	return _path;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFileLocation)
	ADD_INTERFACE(lb_I_FileLocation)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbFileLocation::setData(lb_I_Unknown* uk) {
	lbErrCodes err= ERR_NONE;
	
	if (uk) {
		UAP(lb_I_FileLocation, f)
		QI(uk, lb_I_FileLocation, f)
		
		setData(f->getData());
	} else {
		_LOG << "WARNING: File not given as an unknown object (NULL pointer)!" LOG_
		setData("");
	}
	
	return err;
}

/*...sKey:0:*/
char* LB_STDCALL lbFileLocation::getKeyType() const {
    return "fileloc";
}

int LB_STDCALL lbFileLocation::equals(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        printf("Stringvergleich %s == %s = %d\n", 
        	_path, 
        	((const lbFileLocation*) _key)->_path, 
        	strcmp(_path, ((const lbFileLocation*) _key)->_path));
#endif        	
/*...e*/
	return strcmp(_path, ((const lbFileLocation*) _key)->_path) == 0 ? 1 : 0;
    } else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbFileLocation::greater(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(_path, ((const lbFileLocation*) _key)->_path) > 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbFileLocation::lessthan(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(_path, ((const lbFileLocation*) _key)->_path) < 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

char* LB_STDCALL lbFileLocation::charrep() const {
	return _path;
}
/*...e*/
/*...e*/
/*...slbFileLocation:0:*/
lbDirLocation::lbDirLocation() {
	ref = STARTREF;
	_path = NULL;
}

lbDirLocation::~lbDirLocation() {
	if (_path != NULL) free(_path);
}

void lbDirLocation::setData(char* path) {
	if (_path != NULL) free(_path);
	_path = strdup(path);
}

char* lbDirLocation::getData() const {
	return _path;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDirLocation)
	ADD_INTERFACE(lb_I_DirLocation)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbDirLocation::setData(lb_I_Unknown* uk) {
	lbErrCodes err= ERR_NONE;
	
	if (uk) {
		UAP(lb_I_DirLocation, f)
		QI(uk, lb_I_DirLocation, f)
		
		setData(f->getData());
	} else {
		_LOG << "WARNING: Directory not given as an unknown object (NULL pointer)!" LOG_
		setData("");
	}
	
	return err;
}

/*...sKey:0:*/
char* LB_STDCALL lbDirLocation::getKeyType() const {
    return "dirloc";
}

int LB_STDCALL lbDirLocation::equals(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        printf("Stringvergleich %s == %s = %d\n", 
        	_path, 
        	((const lbDirLocation*) _key)->_path, 
        	strcmp(_path, ((const lbDirLocation*) _key)->_path));
#endif        	
/*...e*/
	return strcmp(_path, ((const lbDirLocation*) _key)->_path) == 0 ? 1 : 0;
    } else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbDirLocation::greater(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(_path, ((const lbDirLocation*) _key)->_path) > 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbDirLocation::lessthan(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(_path, ((const lbDirLocation*) _key)->_path) < 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

char* LB_STDCALL lbDirLocation::charrep() const {
	return _path;
}
/*...e*/
/*...e*/

/*...slbInteger:0:*/
lbInteger::lbInteger() {
	ref = STARTREF;
	integerdata = 0;
	key = NULL;
}

lbInteger::~lbInteger() {
	free(key);
}

void lbInteger::setData(int p) {
	if (key == NULL) {
		key = (char*) malloc(20);
	}
#ifndef UNIX
	itoa(p, key, 10);
#endif
#ifdef UNIX
	sprintf(key, "%d", p);
#endif

	integerdata = p;
}

int lbInteger::getData() const {
	return integerdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInteger)
	ADD_INTERFACE(lb_I_Integer)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbInteger::setData(lb_I_Unknown* uk) {
	lbErrCodes err= ERR_NONE;
	UAP(lb_I_Integer, i)
	QI(uk, lb_I_Integer, i)
	
	int v = i->getData();
	setData(v);
	
	return err;
}

/*...sKey:0:*/
char* LB_STDCALL lbInteger::getKeyType() const {
    return "int";
}

int LB_STDCALL lbInteger::equals(const lb_I_KeyBase* _key) const {
    return integerdata == ((lbInteger*) _key)->integerdata;
}

int LB_STDCALL lbInteger::greater(const lb_I_KeyBase* _key) const {
    return integerdata > ((lbInteger*) _key)->integerdata;
}

int LB_STDCALL lbInteger::lessthan(const lb_I_KeyBase* _key) const {
    return integerdata < ((lbInteger*) _key)->integerdata;
}

char* LB_STDCALL lbInteger::charrep() const {
	return key;
}
/*...e*/
/*...e*/
/*...slbBoolean:0:*/
lbBoolean::lbBoolean() {
	ref = STARTREF;
	integerdata = 0;
	key = "false";
}

lbBoolean::~lbBoolean() {
}

void lbBoolean::setData(bool p) {
	integerdata = p;
	if (p == 0) key = "false";
	else key = "true";
}

bool lbBoolean::getData() const {
	return integerdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBoolean)
	ADD_INTERFACE(lb_I_Boolean)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbBoolean::setData(lb_I_Unknown* uk) {
	lbErrCodes err= ERR_NONE;
	UAP(lb_I_Boolean, i)
	QI(uk, lb_I_Boolean, i)
	
	bool v = i->getData();
	setData(v);
	
	return err;
}

/*...sKey:0:*/
char* LB_STDCALL lbBoolean::getKeyType() const {
    return "bool";
}

int LB_STDCALL lbBoolean::equals(const lb_I_KeyBase* _key) const {
    return integerdata == ((lbBoolean*) _key)->integerdata;
}

int LB_STDCALL lbBoolean::greater(const lb_I_KeyBase* _key) const {
    return integerdata > ((lbBoolean*) _key)->integerdata;
}

int LB_STDCALL lbBoolean::lessthan(const lb_I_KeyBase* _key) const {
    return integerdata < ((lbBoolean*) _key)->integerdata;
}

char* LB_STDCALL lbBoolean::charrep() const {
	if (integerdata) return "true";
	else return "false";
}
/*...e*/
/*...e*/
lbBinaryData::lbBinaryData() {
	ref = STARTREF;
	blob = NULL;
}

lbBinaryData::~lbBinaryData() {
	free(blob);
}

lbErrCodes LB_STDCALL lbBinaryData::append(void* value, long len) {
	if (blob == NULL) {
		setData(value, len);
		return ERR_NONE;
	}
	
	blob = realloc(blob, size + len);
	
	char* temp = (char*) blob;
	
	temp += size;
	
	memcpy((void*)temp, value, len);
	
	size += len;

    return ERR_NONE;
}

lbErrCodes LB_STDCALL lbBinaryData::setData(void* value, long len) {
	if (value == NULL) {
		free(blob);
		blob = NULL;
		size = 0L;
		return ERR_NONE;
	}
	
	if (blob != NULL) free(blob);

	if (len == 0L) {
		_LOG << "lbBinaryData::setData(...) Warning: Zero allocation ignored." LOG_
		blob = strdup("");
		size = 1;
		return ERR_NONE;
	}

	blob = malloc(len);
	
	if (blob == NULL) {
		_LOG << "lbBinaryData::setData(...) Error: Memory allocation failed! (" << len << " bytes should be allocated)" LOG_
		size = 0;
		return ERR_MEMORY_ALLOC;
	}
	
	memcpy(blob, value, len);
	size = len;
	return ERR_NONE;
}

void* LB_STDCALL lbBinaryData::getData() const {
	return blob;
}

long LB_STDCALL lbBinaryData::getSize() const {
	return size;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbBinaryData)
	ADD_INTERFACE(lb_I_BinaryData)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbBinaryData::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_BinaryData, l)
	
	if (uk != NULL) {
		QI(uk, lb_I_BinaryData, l)
		void* _l = l->getData();
		setData(_l, l->getSize());
	}
	
	return ERR_NONE;
}

/*...slbLong:0:*/
lbLong::lbLong() {
	ref = STARTREF;
	longdata = 0;
	key = NULL;
	strcpy(keyType, "UL");
}

lbLong::~lbLong() {
	free(key);
}

void lbLong::setData(long p) {
	longdata = p;

	if (key == NULL) {
		key = (char*) malloc(30);
	}
	
#ifndef UNIX
	itoa(longdata, key, 10);
#endif
#ifdef UNIX
	sprintf(key, "%d", longdata);
#endif
}

long lbLong::getData() const {
	return longdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLong)
	ADD_INTERFACE(lb_I_Long)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLong::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Long, l)
	
	if (uk != NULL) {
		QI(uk, lb_I_Long, l)
		long _l = l->getData();
		setData(_l);
	}
	
	return ERR_NONE;
}

/*...slbKeyUL:0:*/
char* LB_STDCALL lbLong::getKeyType() const {
    return "UL";
}

int LB_STDCALL lbLong::equals(const lb_I_KeyBase* _key) const {
    return longdata == ((lbLong*) _key)->longdata;
}

int LB_STDCALL lbLong::greater(const lb_I_KeyBase* _key) const {
    return longdata > ((lbLong*) _key)->longdata;
}

int LB_STDCALL lbLong::lessthan(const lb_I_KeyBase* _key) const {
    return longdata < ((lbLong*) _key)->longdata;
}

char* LB_STDCALL lbLong::charrep() const {
	return key;
}
/*...e*/
/*...e*/
#ifdef bla
/*...slbStringList:0:*/
lbStringList::lbStringList() {
	ref = STARTREF;
	list = NULL;
	count = 0;
}

lbStringList::~lbStringList() {
	list->deleteAll();
	RELEASE(list);
}

void lbStringList::setType() {
	OTyp = LB_STRINGLIST;
}

lb_I_Unknown* lbStringList::clone() const {
	lbStringList* cloned = new lbStringList();
	
	lb_I_Unknown* uk_stringlist = list->clone();
	
	uk_stringlist->queryInterface("lb_I_Container", (void**) &cloned->list);
	cloned->count = count;
	
	lb_I_Unknown* uk_cloned = NULL;
	
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned) != ERR_NONE) {
		_CL_VERBOSE << "Error: query interface failed" LOG_
	}
	
	return uk_cloned;
}

void lbStringList::insert(lb_I_String* s) {
	count++;
	/**
	 * It should be passed a lb_I_Unknown pointer. Internally the needed interface should be
	 * queried.
	 */
	
	list->insert(s, &lbKey(count));
}

int lbStringList::remove(const lb_I_String* s) {
	if (exists(s)) {
		list->remove(&lbKey(count));
		count--;
		return 1;
	} else return 0;
}

int lbStringList::exists(const lb_I_String* s) {
	int result = 0;
	while (hasMoreElements()) {
		if (strcmp(s->getData(), ((lbString*) nextElement())->getData()) == 0) result = 1;
	}
	return result;
}

int lbStringList::hasMoreElements() {
	return list->hasMoreElements();
}

lb_I_String* lbStringList::nextElement() {
	lb_I_Unknown* uk_object = NULL;
	lb_I_String* s = NULL;
	
	uk_object = list->nextElement();
	
	if (uk_object->queryInterface("lb_I_String", (void**) &s) != ERR_NONE) {
		_CL_VERBOSE << "Error: query interface failed" LOG_
	}
	
	return s;
}

/*...e*/
#endif

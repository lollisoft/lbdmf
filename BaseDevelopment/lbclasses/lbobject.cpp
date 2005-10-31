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

#pragma warning( disable: 4101 )
#pragma warning( disable: 4172 )

#endif

#include <stdio.h>
#include <string.h>
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
IMPLEMENT_FUNCTOR(instanceOfString, lbString)
IMPLEMENT_FUNCTOR(instanceOfReference, lbReference)
IMPLEMENT_FUNCTOR(instanceOfParameter, lbParameter)

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfLocale, lbLocale)

#ifdef __cplusplus
}
#endif            


/*...slbLocale:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbLocale)
        ADD_INTERFACE(lb_I_Locale)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLocale::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}

lbLocale::lbLocale() {
	ref = STARTREF;
	_lang = (char*) malloc(100);
	_lang[0] = 0;
	strcpy(_lang, "german");
}

lbLocale::~lbLocale() {
	free(_lang);
}

void LB_STDCALL lbLocale::setLanguage(char const * lang) {
	free(_lang);
	_lang = strdup(lang);
}

/*...svoid LB_STDCALL lbLocale\58\\58\translate\40\char \42\\42\ text\44\ char const \42\ to_translate\41\:0:*/
void LB_STDCALL lbLocale::translate(char ** text, char const * to_translate) {


	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	if (database->connect("lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
		*text = (char*) realloc(*text, strlen(to_translate) + 1);
		*text[0] = 0;
		strcpy(*text, to_translate);
		return;
	}

	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

	sampleQuery = database->getQuery(0);

	char buffer[800] = "";

	sprintf(buffer, "select translated from translations where language = '%s' and text = '%s'", _lang, to_translate);

	sampleQuery->skipFKCollecting();
	sampleQuery->query(buffer);

	// Fill up the available applications for that user.
	
	lbErrCodes err = sampleQuery->first();

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

	        UAP_REQUEST(manager.getPtr(), lb_I_String, s1)

	        s1 = sampleQuery->getAsString(1);

		*text = (char*) realloc((void*) (*text), strlen(s1->charrep()) + 1);
		*text[0] = 0;

		if (strcmp(s1->charrep(), "") == 0) 
			strcpy(*text, to_translate);
		else
			strcpy(*text, s1->charrep());
	} else {
		*text = (char*) realloc(*text, strlen(to_translate) + 1);
		*text[0] = 0;

		_CL_VERBOSE << "šbersetzung fr '" << to_translate << "' nicht gefunden!" LOG_

		buffer[0] = 0;
		
		sprintf(buffer, "insert into translations (text, translated) values('%s', '%s')", to_translate, to_translate);

		/* Sybase SQL Anywhere 5.5 has problems with state 24000. Maybe an auto commit problem */
		UAP(lb_I_Query, sampleQuery1, __FILE__, __LINE__)
		sampleQuery1 = database->getQuery(0);
		sampleQuery1->skipFKCollecting();
		sampleQuery1->query(buffer);
		sampleQuery1->enableFKCollecting();

		strcpy(*text, to_translate);
	}

	sampleQuery->enableFKCollecting();
}
/*...e*/
/*...e*/
/*...slbParameter:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbParameter)
	ADD_INTERFACE(lb_I_Parameter)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbParameter::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbParameter::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

int LB_STDCALL lbParameter::Count() {
	if (parameters == NULL) return 0;
	return parameters->Count();
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
	
	UAP(lb_I_KeyBase, k_parameter, __FILE__, __LINE__)
	QI(parameter, lb_I_KeyBase, k_parameter, __FILE__, __LINE__)

	UAP(lb_I_Unknown, uk_p, __FILE__, __LINE__)
	QI(p, lb_I_Unknown, uk_p, __FILE__, __LINE__)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPString(lb_I_String*& parameter, lb_I_String*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;
	
	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(pp, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	UAP(lb_I_Unknown, uk_p_string, __FILE__, __LINE__)

	uk_p_string = parameters->getElement(&key);

	if (uk_p_string == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_String, string, __FILE__, __LINE__)
	QI(uk_p_string, lb_I_String, string, __FILE__, __LINE__)
	
	
	p->setData(string->getData());
	
	
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
	
	UAP(lb_I_KeyBase, k_parameter, __FILE__, __LINE__)
	QI(parameter, lb_I_KeyBase, k_parameter, __FILE__, __LINE__)

	UAP(lb_I_Unknown, uk_p, __FILE__, __LINE__)
	QI(p, lb_I_Unknown, uk_p, __FILE__, __LINE__)
	
	
	parameters->insert(&uk_p, &k_parameter);
}

lbErrCodes LB_STDCALL lbParameter::getUAPInteger(lb_I_String*& parameter, lb_I_Integer*& p) {
	lbErrCodes err = ERR_NONE;
	
	if (parameters == NULL) return ERR_PARAM_NOT_FOUND;

	lb_I_String* pp = parameter;
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(pp, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	UAP(lb_I_Unknown, uk_p_integer, __FILE__, __LINE__)

	uk_p_integer = parameters->getElement(&key);

	if (uk_p_integer == NULL) return ERR_PARAM_NOT_FOUND;

	UAP(lb_I_Integer, integer, __FILE__, __LINE__)
	QI(uk_p_integer, lb_I_Integer, integer, __FILE__, __LINE__)
	
	if (integer.getPtr() != NULL) p->setData(integer->getData());
	
	
	return ERR_NONE;
}
/*...e*/
/*...slbReference:0:*/
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
/*...e*/
/*...slbString:0:*/
lbString::lbString() {
	ref = STARTREF;
	stringdata = NULL;
	key = NULL;
}

lbString::~lbString() {

	char ptr[20] = "";
	sprintf(ptr, "%p", this);

	_CL_VERBOSE << "lbString::~lbString() called. Data is " << stringdata << ", this is " << ptr LOG_

	if (stringdata != NULL) free(stringdata);
	
	if (key != NULL) free(key);
	stringdata = NULL;
	key = NULL;
}

lb_I_String& LB_STDCALL lbString::operator += (const lb_I_String* toAppend) {
		return *this += toAppend->charrep();
}

lb_I_String& LB_STDCALL lbString::operator += (const char* toAppend) {
	stringdata = (char*) realloc(stringdata, strlen(stringdata)+strlen(toAppend)+1);
	strcat(stringdata, toAppend);
	key = (char*) realloc(key, strlen(key)+strlen(toAppend)+1);
	strcat(key, toAppend);
	
	return *this;
}

lb_I_String& LB_STDCALL lbString::operator = (const lb_I_String* toAppend) {
		return *this = toAppend->charrep();
}

lb_I_String& LB_STDCALL lbString::operator = (const char* toAppend) {
	stringdata = (char*) realloc(stringdata, strlen(toAppend)+1);
	stringdata[0] = 0;
	strcpy(stringdata, toAppend);
	
	key = (char*) realloc(key, strlen(toAppend)+1);
	key[0] = 0;
	strcpy(key, toAppend);
	
	return *this;
}

void LB_STDCALL lbString::setData(char const * p) {
	if (stringdata != NULL) free(stringdata);
	if (key != NULL) free(key);
	
	stringdata = NULL;
	key = NULL;
	
	if (p == NULL) return;

	stringdata = (char*) malloc(strlen(p)+1);
	stringdata[0] = 0;
	strcpy(stringdata, p);
	
	if (key != NULL) free(key);
	
	key = (char*) malloc(strlen(p)+1);
	key[0] = 0;
	strcpy(key, p);
}

void LB_STDCALL lbString::trim() {
	while (stringdata[strlen(stringdata)-1] == ' ') 
		stringdata[strlen(stringdata)-1] = 0;
	
	if (key != NULL) free(key);
	
	key = (char*) malloc(strlen(stringdata)+1);
	key[0] = 0;
	key = strcpy(key, stringdata);
}

char* LB_STDCALL lbString::getData() const {
	return stringdata;
}

/*...sbla:0:*/
#ifdef bla

void lbString::setType() {
	OTyp = LB_STRING;
}


lb_I_Unknown* lbString::clone() const {
	lbString* cloned = new lbString();
	
	cloned->setData(getData());
	
	lb_I_Unknown* uk_cloned = NULL;
	
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned) != ERR_NONE) {
		_CL_VERBOSE << "Error while getting interface" LOG_
	}
	
	return uk_cloned;
}

void lbString::setData(char* p) {
	stringdata = strdup(p);
}

char* lbString::getData() const {
	return stringdata;
}
#endif
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbString)
	ADD_INTERFACE(lb_I_String)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbString::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
	UAP(lb_I_String, string, __FILE__, __LINE__)
	
	QI(uk, lb_I_String, string, __FILE__, __LINE__)
	
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
        	key, 
        	((const lbString*) _key)->key, 
        	strcmp(key, ((const lbString*) _key)->key));
#endif        	
/*...e*/
	return strcmp(key, ((const lbString*) _key)->key) == 0 ? 1 : 0;
    } else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbString::greater(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(key, ((const lbString*) _key)->key) > 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

int LB_STDCALL lbString::lessthan(const lb_I_KeyBase* _key) const {
    if (strcmp(getKeyType(), _key->getKeyType()) == 0)
	return strcmp(key, ((const lbString*) _key)->key) < 0 ? 1 : 0;
    else {
    	_LOG << "Error: Comparing wrong key types" LOG_
    	return 0;
    }
}

char* LB_STDCALL lbString::charrep() const {
    return key;
}
/*...e*/
/*...e*/
/*...slbInteger:0:*/
lbInteger::lbInteger() {
	ref = STARTREF;
	integerdata = 0;
}

lbInteger::~lbInteger() {
}

void lbInteger::setData(int p) {
	integerdata = p;
	key = p;
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
	UAP(lb_I_Integer, i, __FILE__, __LINE__)
	QI(uk, lb_I_Integer, i, __FILE__, __LINE__)
	
	int v = i->getData();
	setData(v);
	
	return err;
}

/*...sKey:0:*/
char* LB_STDCALL lbInteger::getKeyType() const {
    return "int";
}

int LB_STDCALL lbInteger::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbInteger*) _key)->key;
}

int LB_STDCALL lbInteger::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbInteger*) _key)->key;
}

int LB_STDCALL lbInteger::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbInteger*) _key)->key;
}

char* LB_STDCALL lbInteger::charrep() const {
	static char buf[100];
	buf[0] = 0;
	
#ifndef UNIX
	itoa(key, buf, 10);
#endif
#ifdef UNIX
	sprintf(buf, "%d", key);
#endif
    
	return buf;
}
/*...e*/
/*...e*/
/*...slbLong:0:*/
lbLong::lbLong() {
	ref = STARTREF;
	longdata = 0;
	key = 0;
	strcpy(keyType, "UL");
}

lbLong::~lbLong() {
}

void lbLong::setData(long p) {
	longdata = p;
}

long lbLong::getData() const {
	return longdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLong)
	ADD_INTERFACE(lb_I_Long)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLong::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbLong::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

/*...slbKeyUL:0:*/
char* LB_STDCALL lbLong::getKeyType() const {
    return "UL";
}

int LB_STDCALL lbLong::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbLong*) _key)->key;
}

int LB_STDCALL lbLong::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbLong*) _key)->key;
}

int LB_STDCALL lbLong::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbLong*) _key)->key;
}

char* LB_STDCALL lbLong::charrep() const {
	static char buf[100];
	buf[0] = 0;
	
#ifndef UNIX
	itoa(key, buf, 10);
#endif
#ifdef UNIX
	sprintf(buf, "%d", key);
#endif
    
	return buf;
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


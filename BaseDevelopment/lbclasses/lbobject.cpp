/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <stdio.h>
#include <string.h>
#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

#include <lbobject.h>
#include <lbkey.h>

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfInteger, lbInteger)
IMPLEMENT_FUNCTOR(instanceOfString, lbString)

#ifdef __cplusplus
}
#endif            

#ifdef bla
/*...slbObject:0:*/
void lbObject::setName(const char* d) {
	if (name != NULL) delete name;
    name = strdup(d);
}

const char* lbObject::getName() const {
    return name;
}

ObjectTyp lbObject::getType() const {
	if (OTyp == LB_OBJECT) {
		LOG("Derived object has not been initialized correctly!");
	}
	return OTyp;
}

void lbObject::setType() {
	LOG("Error: Base object has no object type");
}

lbErrCodes LB_STDCALL lbObject::setData(lb_I_Unknown* uk) {
	CL_LOG("lbObject::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}


BEGIN_IMPLEMENT_LB_UNKNOWN(lbObject)
	ADD_INTERFACE(lb_I_Object)
END_IMPLEMENT_LB_UNKNOWN()
/*...e*/
#endif

/*...slbString:0:*/
lbString::lbString() {
	ref = STARTREF;
	stringdata = NULL;
	key = NULL;
}

lbString::~lbString() {
	if (stringdata != NULL) delete[] stringdata;
	if (key != NULL) delete[] key;
}

void LB_STDCALL lbString::setData(char* p) {
	if (stringdata != NULL) delete[] stringdata;
	stringdata = strdup(p);
	if (key != NULL) delete[] key;
	key = strdup(p);
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
		CL_LOG("Error while getting interface");
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
	
	lb_I_String* string = NULL;
	
	if (uk->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Could not get interface lb_I_String");
	}
	
	if (string != NULL) {
		setData(string->getData());
	}
	
	return ERR_NONE;
}

/*...sKey:0:*/
/*
lbString::lbString(const char* _key) {
    key = strdup(_key);
}

lbString::lbString(const lb_I_KeyBase* k) {
    key = strdup(((lbString*) k)->key);
}
*/

char* LB_STDCALL lbString::getKeyType() {
    return "string";
}

int lbString::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbString*) _key)->key) == 0);
}

int lbString::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbString*) _key)->key) > 0);
}

char* lbString::charrep() {
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
}

int lbInteger::getData() const {
	return integerdata;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInteger)
	ADD_INTERFACE(lb_I_Integer)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbInteger::setData(lb_I_Unknown* uk) {
	CL_LOG("lbInteger::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

/*...sKey:0:*/
/*
char* LB_STDCALL lbInteger::getKeyType() {
    return "integer";
}

int lbInteger::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbInteger*) _key)->key) == 0);
}

int lbInteger::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbInteger*) _key)->key) > 0);
}

char* lbInteger::charrep() {
    char buffer[50] = "";
    return itoa(key, buffer, 10);
}

*/

char* LB_STDCALL lbInteger::getKeyType() {
    return "int";
}

int lbInteger::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbInteger*) _key)->key;
}

int lbInteger::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbInteger*) _key)->key;
}

char* lbInteger::charrep() {
    char buf[100];

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
	CL_LOG("lbLong::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

/*...slbKeyUL:0:*/
char* LB_STDCALL lbLong::getKeyType() {
    return "UL";
}

int lbLong::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbLong*) _key)->key;
}

int lbLong::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbLong*) _key)->key;
}

char* lbLong::charrep() {
    char buf[100];

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
		CL_LOG("Error: query interface failed");
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
		CL_LOG("Error: query interface failed");
	}
	
	return s;
}

/*...e*/
#endif


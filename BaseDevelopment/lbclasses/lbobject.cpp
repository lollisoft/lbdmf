#define LB_CONTAINER_DLL

#include <string.h>
#include <lbInterfaces.h>
#include <lbObject.h>
#include <lbKey.h>
#include <windows.h>
#include <lbConfigHook.h>

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


BEGIN_IMPLEMENT_LB_UNKNOWN(lbObject)
	ADD_INTERFACE(lb_I_Object)
END_IMPLEMENT_LB_UNKNOWN()
/*...e*/
/*...slbString:0:*/
lbString::lbString() {
	stringdata = NULL;
}

lbString::~lbString() {
	if (stringdata != NULL) delete[] stringdata;
}

void lbString::setData(char* p) {
	stringdata = strdup(p);
}

char* lbString::getData() const {
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
END_IMPLEMENT_LB_UNKNOWN()

/*...e*/
/*...slbStringList:0:*/
lbStringList::lbStringList() {
	list = NULL;
	count = 0;
}

lbStringList::~lbStringList() {
	list->deleteAll();
	list->release();
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



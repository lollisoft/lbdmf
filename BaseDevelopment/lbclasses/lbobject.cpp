#define LB_CONTAINER_DLL

#include <string.h>
#include <lbInclude.h>


/*...slbObject:0:*/
void lbObject::setName(const char* d) {
	if (name != NULL) delete name;
    name = strdup(d);
}

const char* lbObject::getName() const {
    return name;
}

lbObject::ObjectTyp lbObject::getType() const {
	if (OTyp == LB_OBJECT) {
		LOG("Derived object has not been initialized correctly!");
	}
	return OTyp;
}
/*...e*/
/*...slbString:0:*/
lbString::lbString() {
	stringdata = NULL;
}

lbString::~lbString() {
	if (stringdata != NULL) delete[] stringdata;
}

void lbString::setType() {
	OTyp = LB_STRING;
}

lbObject* lbString::clone() const {
	lbString* cloned = new lbString();
	
	cloned->setData(getData());
	
	return (lbObject*) cloned;
}

void lbString::setData(char* p) {
	stringdata = strdup(p);
}

char* lbString::getData() const {
	return stringdata;
}


/*...e*/
/*...slbStringList:0:*/
lbStringList::lbStringList() {
	list = NULL;
	count = 0;
}

lbStringList::~lbStringList() {
	list->deleteAll();
	delete list;
}

void lbStringList::setType() {
	OTyp = LB_STRINGLIST;
}

lbObject* lbStringList::clone() const {
	lbStringList* cloned = new lbStringList();
	
	cloned->list = (lbComponentDictionary*) list->clone();
	cloned->count = count;
	
	return (lbObject*) cloned;
}

void lbStringList::insert(lbString &s) {
	count++;
	list->insert(s, lbKey(count));
}

int lbStringList::remove(const lbString &s) {
	if (exists(s)) {
		list->remove(lbKey(count));
		count--;
		return 1;
	} else return 0;
}

int lbStringList::exists(const lbString &s) {
	int result = 0;
	while (hasMoreElements()) {
		if (strcmp(s.getData(), ((lbString*) nextElement())->getData()) == 0) result = 1;
	}
	return result;
}

int lbStringList::hasMoreElements() {
	return list->hasMoreElements();
}

lbString* lbStringList::nextElement() {
	return (lbString*) list->nextElement();
}

/*...e*/






/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbcontainer.cpp,v 1.4 2000/06/24 21:32:07 lolli Exp $
 * $Log: lbcontainer.cpp,v $
 * Revision 1.4  2000/06/24 21:32:07  lolli
 * Socket bugfix
 *
 * Revision 1.3  2000/04/27 01:36:24  lolli
 * Commit in order of data GAU
 *
 * Revision 1.2  2000/03/06 22:55:50  lolli
 * Fold in revision log
 *
 * Revision 1.1.1.1  2000/03/06 20:54:58  lolli
 * Imported
 *
 * Revision 1.3  1999/12/14 21:07:03  lolli
 * Many changes
 *
 * Revision 1.2  1999/11/25 20:48:49  lothar
 * Checked in due to working directory change
 *
 * Revision 1.1  1999/10/08 21:27:00  Administrator
 * Initial
 *
 ************************************************************************************************************/
/*...e*/
#define VERBOSE
//Define DLL here for implementing the module

#define LB_CONTAINER_DLL

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <lbInclude.h>


lbCritSect containerSection;
lbCritSect elementSection;

lbContainer::lbContainer() {
    iteration = 0;
    ref = 0;
    iterator = NULL;
    count = 0;
//    lbLog l = lbLog(); // Initialize logging
}

lbContainer::lbContainer(const lbContainer & c) {
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
    ref = c.ref;
}

lbContainer& lbContainer::operator= (const lbContainer & c) {
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
    return *this;
}

lbContainer::~lbContainer() {
}

int lbContainer::Count() {
	return count;
}

/*...slbErrCodes lbContainer\58\\58\insert\40\const lbObject \38\e\44\ const lbKeyBase \38\key\41\:0:*/
lbErrCodes lbContainer::insert(const lbObject &e, const lbKeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _insert(e, key)) != ERR_NONE) {
		LOG("lbContainer::insert(...) Failed!");
		return err;
	}

	count++;
	return err;
}
/*...e*/

/*...slbErrCodes lbContainer\58\\58\remove\40\const lbKeyBase \38\key\41\:0:*/
lbErrCodes lbContainer::remove(const lbKeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _remove(key)) != ERR_NONE) {
		LOG("lbContainer::remove(...) Failed!");
		return err;
	}

	count--;
	return err;
}
/*...e*/

lbComponentDictionary::lbComponentDictionary() : lbContainer() {
    data = NULL;
}

lbComponentDictionary::lbComponentDictionary(const lbComponentDictionary & c) {
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
}

lbComponentDictionary& lbComponentDictionary::operator= (const lbComponentDictionary & c) {
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
    data = c.data;
    ref++;
    return *this;
}


lbComponentDictionary::~lbComponentDictionary() {
	ref --;
	if (ref < 0) LOG("Error, reference count not implemented corectly!");
	if (ref == 0) deleteAll();
}

/*...slbComponentDictionary\58\\58\clone\40\\41\:0:*/
lbContainer* lbComponentDictionary::clone() {
//lbLock lock(containerSection, "containerSection");

	lbComponentDictionary* dic = new lbComponentDictionary();
	
	while (hasMoreElements()) {
		lbElement* e = nextElement();

		dic->insert(*(e->getObject()), *(e->getKey()));
	}	

	return dic;
}
/*...e*/

/*...slbComponentDictionary\58\\58\deleteAll\40\\41\:0:*/
void lbComponentDictionary::deleteAll() {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
cout << "lbComponentDictionary::deleteAll() called" << endl;
#endif
/*...e*/
//lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
cout << "containerSection locked" << endl;
#endif
/*...e*/
	while (hasMoreElements()) {
		lbElement* e = nextElement();
if (e == NULL) LOG("NULL pointer");
		remove(*(e->getKey()));
        }
        count = 0;
}
/*...e*/

/*...slbComponentDictionary\58\\58\_insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbComponentDictionary::_insert(const lbObject &e, const lbKeyBase &key) {

//    lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    LOG("lbComponentDictionary::insert(...) called");
#endif
/*...e*/
    if (data == NULL) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbComponentDictionary::insert(...) Inserting first element");
#endif
/*...e*/
        data = new lbElement(e, key);
	if (data->getObject() == NULL) {
		LOG("Failed to insert first element in lbComponentDictionary::insert");
		return ERR_CONTAINER_INSERT;
	}
    }
    else {
        lbElement* temp;
        for (temp = data; temp != NULL; temp = temp->getNext()) {
            lbElement* next = temp->getNext();

            if (next != NULL) {
                if (next->getKey() < &key) {
                    temp->setNext(new lbElement(e, key, next));
/*...sCLASSES_VERBOSE:0:*/
            	    #ifdef CLASSES_VERBOSE
            	    LOG("lbComponentDictionary::insert(...) leave");
                    #endif
/*...e*/
                    return ERR_NONE;
                }
            }
            else {
                temp->setNext(new lbElement(e, key));
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
            	LOG("lbComponentDictionary::insert(...) leave");
#endif
/*...e*/
                return ERR_NONE;
            }
        }
    }
    return ERR_NONE;      
}
/*...e*/

/*...slbComponentDictionary\58\\58\_remove\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbComponentDictionary::_remove(const lbKeyBase &key) {
//    lbLock lock(containerSection, "containerSection");
    
    if (data == NULL) {
    	LOG("lbComponentDictionary::remove(...) Error: Can't remove from empty container!");
    	return ERR_CONTAINER_REMOVE;
    }

    lbElement* pre = data;
    data = data->getNext();

    if (pre->getKey() == &key) {
        delete pre;
        return ERR_NONE;
    }
    
    for (lbElement* temp = data; temp != NULL; temp = data->getNext()) {
        if (temp->getKey() == &key) {
            pre->setNext(temp->getNext());
            delete temp;
            return ERR_NONE;
        }
    }
    LOG("lbComponentDictionary::remove(...) Error: No object with that key");
    return ERR_CONTAINER_REMOVE;
}
/*...e*/

int lbComponentDictionary::exists(const lbKeyBase &key) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    cout << "lbComponentDictionary::exists(const lbKeyBase &key) called" << endl;
#endif
/*...e*/
    if (getElement(key) == NULL) return 0;
    return 1;
}

int lbComponentDictionary::hasMoreElements() {
//lbLock lock(containerSection, "containerSection");
    if (iteration == 0) {
		iteration = 1;
        iterator = data;
    }

    if (iterator == NULL) {
        // reset state to be out of iteration
        iteration = 0;
        return 0;
    }

    return 1;
}

lbElement* lbComponentDictionary::nextElement() {
//    lbLock lock(containerSection, "containerSection");
    lbElement *temp = iterator;
    iterator = iterator->getNext();
	
    return temp;
}

lbObject* lbComponentDictionary::nextObject() {
//    lbLock lock(containerSection, "containerSection");
    
    lbElement *temp = iterator;
    iterator = iterator->getNext();

    if (temp == NULL) LOG("Temporary iterator object is NULL!");

    lbObject *o = temp->getObject();

    if (o == NULL) LOG("Temporary object o is NULL!");

    return temp->getObject();
}



lbObject* lbComponentDictionary::getElement(const lbKeyBase &key) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    cout << "lbComponentDictionary::getElement(...) called" << endl;
#endif
/*...e*/
//    lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    cout << "lbLock lock(containerSection) Is locked" << endl;
#endif    
/*...e*/
    lbElement* temp = data;
    while (temp) {
        if ((temp) && (*(temp->getKey()) == key)) {
          lbObject *o = temp->getObject();
          return o;
        }

        temp = temp->getNext();
    }
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE    
    LOG("lbComponentDictionary::getElement() Keys compared not succsesfully");
#endif
/*...e*/
    return NULL;
}

void lbComponentDictionary::setElement(lbKeyBase &key, lbObject const &e) {
//    lbLock lock(containerSection, "containerSection");
    remove(key);
    insert(e, key);
}
 
lbObject* lbComponentDictionary::getObject() {
//    lbLock lock(containerSection, "containerSection");
    return data->getObject();
}

lbElement::lbElement(const lbObject &o, const lbKeyBase &_key, lbElement *_next) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbElement::lbElement(const lbObject &o, const lbKeyBase &_key, lbElement *_next) called");
#endif
/*...e*/
    lbLock lock(elementSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbElement::lbElement(const lbObject &o, const lbKeyBase &_key, lbElement *_next) entered");    
#endif
/*...e*/
    next = _next;
    data = o.clone();
    key = _key.clone();
    if (key == NULL) LOG("Key cloning in constructor failed. May be a memory problem"); 
}
lbElement::~lbElement() {
}

lbObject* lbElement::getObject() const {
    return data;
}


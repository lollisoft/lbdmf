


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: lbcontainer.cpp,v 1.3 2000/04/27 01:36:24 lolli Exp $
 * $Log: lbcontainer.cpp,v $
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

//Define DLL here for implementing the module

#define LB_CONTAINER_DLL

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <lb_misc.h>
#include <lbKey.h>
#include <lbObject.h>
#include <lbElement.h>
#include <lbContainer.h>

lbContainer::lbContainer() {
    iteration = 0;
    iterator = NULL;
//    lbLog l = lbLog(); // Initialize logging
}

lbContainer::~lbContainer() {
}


lbComponentDictionary::lbComponentDictionary() {
    data = NULL;
}

lbComponentDictionary::~lbComponentDictionary() {
}

lbContainer* lbComponentDictionary::clone() {
	lbComponentDictionary* dic = new lbComponentDictionary();
	
	while (hasMoreElements()) {
		lbElement* e = nextElement();

		dic->insert(*(e->getObject()), *(e->getKey()));
	}	
	return dic;
}

void lbComponentDictionary::deleteAll() {
	while (hasMoreElements()) {
		lbElement* e = nextElement();

		remove(*(e->getKey()));
        }
}

void lbComponentDictionary::insert(const lbObject &e, const lbKeyBase &key) {
    if (data == NULL) {
        data = new lbElement(e, key);
		if (data->getObject() == NULL) LOG("Failed to insert first element in lbComponentDictionary::insert");
    }
    else {
        lbElement* temp;

        for (temp = data; temp != NULL; temp = data->getNext()) {
            lbElement* next = temp->getNext();
            if (next != NULL) {
                if (next->getKey() > &key) {
                    temp->setNext(new lbElement(e, key, next));
                    return;
                }
            }
            else {
                temp->setNext(new lbElement(e, key));
                return;
            }
        }
    }
      
}

void lbComponentDictionary::remove(const lbKeyBase &key) {
    if (data == NULL) return;

    lbElement* pre = data;
    data = data->getNext();

    if (pre->getKey() == &key) {
        delete pre;
        return;
    }
    
    for (lbElement* temp = data; temp != NULL; temp = data->getNext()) {
        if (temp->getKey() == &key) {
            pre->setNext(temp->getNext());
            delete temp;
            return;
        }
    }
}

int lbComponentDictionary::exists(const lbKeyBase &key) {
    if (getElement(key) == NULL) return 0;
    return 1;
}

int lbComponentDictionary::hasMoreElements() {
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
	lbElement *temp = iterator;
	iterator = iterator->getNext();
	
	return temp;
}

lbObject* lbComponentDictionary::nextObject() {
    lbElement *temp = iterator;
	iterator = iterator->getNext();

	if (temp == NULL) LOG("Temporary iterator object is NULL!");

	lbObject *o = temp->getObject();

	if (o == NULL) LOG("Temporary object o is NULL!");

    return temp->getObject();
}



lbObject* lbComponentDictionary::getElement(const lbKeyBase &key) {
    lbElement* temp = data;

    while (temp) {
        if ((temp) && (*(temp->getKey()) == key))
            return temp->getObject();

        temp = temp->getNext();
    }
    LOG("lbComponentDictionary::getElement() Keys compared not succsesfully");
    return NULL;
}

void lbComponentDictionary::setElement(lbKeyBase &key, lbObject const &e) {
    remove(key);
    insert(e, key);
}
 
lbObject* lbComponentDictionary::getObject() {
    return data->getObject();
}

lbElement::lbElement(const lbObject &o, const lbKeyBase &_key, lbElement *_next) {
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


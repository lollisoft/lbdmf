


/*...sRevision history:0:*/
/************************************************************************************************************
 * $Locker:  $
 * $Revision: 1.8 $
 * $Name:  $
 * $Id: lbcontainer.cpp,v 1.8 2001/03/04 18:30:24 lolli Exp $
 * $Log: lbcontainer.cpp,v $
 * Revision 1.8  2001/03/04 18:30:24  lolli
 * Compiles now with interface support
 *
 * Revision 1.7  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
 * Revision 1.6  2000/10/05 22:56:45  lothar
 * Most changes are interface issues
 *
 * Revision 1.5  2000/06/28 20:33:08  lolli
 * Deactivated some cout messages
 *
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
#include <iostream.h>

//#include <lbInclude.h>
#include <lbInterfaces.h>

#include <lbThread.h>
#include <lbConfigHook.h>
#include <lbElement.h>

lbCritSect containerSection;


/*...sclass lbContainer:0:*/
class lbContainer : 	public lb_I_Container
{

public:
    lbContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbContainer();
    virtual ~lbContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

/*...sbla:0:*/
#ifdef bla
    int Count();

    lbErrCodes insert(const lb_I_Unknown* e, const lb_I_KeyBase* key);
    lbErrCodes remove(const lb_I_KeyBase* key);
    
	/**
	 * General functions needed for storage (key driven)
	 */
    virtual lbErrCodes _insert(const lb_I_Object* e, const lb_I_KeyBase* key) = 0;
    virtual lbErrCodes _remove(const lb_I_KeyBase* key) = 0;
    virtual int exists(const lb_I_KeyBase* e) = 0;

	/**
	 * Iterator (forward only)
	 */
    virtual int hasMoreElements() = 0;
    virtual lb_I_Unknown* nextObject() = 0;

protected:
    /**
     * This should be used internally only
     */
    virtual lb_I_Element* nextElement() = 0;

public:

	/**
	 * Direct access over key
	 */
    virtual lb_I_Unknown* getElement(const lb_I_KeyBase* key) = 0;
    virtual void setElement(lb_I_KeyBase* key, const lb_I_Unknown* e) = 0;

    virtual void deleteAll() = 0;

protected:
    int count;
    int iteration; // This shows, if iteration has begun
    lb_I_Element* iterator;

    lbCritSect critsect;
    
#endif    
/*...e*/
};
/*...e*/

#ifdef bla
/*...sclass lbComponentDictionary:0:*/
class DLLEXPORT lbComponentDictionary: public lbContainer {

private:
    lbComponentDictionary(const lbComponentDictionary* c);
    lbComponentDictionary& operator= (const lbComponentDictionary* c);

public:

    lbComponentDictionary();
    virtual ~lbComponentDictionary();

    DECLARE_LB_UNKNOWN()

    
    virtual lbErrCodes _insert(const lb_I_Object* e, const lb_I_KeyBase* key);
    virtual lbErrCodes _remove(const lb_I_KeyBase* key);
    
    virtual int exists(const lb_I_KeyBase* key);

    virtual int hasMoreElements();
    virtual lb_I_Unknown* nextObject();
    virtual lb_I_Element* nextElement();

    virtual lb_I_Container* clone();

    virtual void deleteAll();

    virtual lb_I_Unknown* getElement(const lb_I_KeyBase* key);
    virtual void setElement(lb_I_KeyBase* key, const lb_I_Unknown* e);
    virtual lb_I_Object* getObject();

private:

    lb_I_Element* data;    
};
/*...e*/
#endif

lbErrCodes DLLEXPORT instanceOf_lb_I_Container(lb_I_Container*& inst) {
	inst = new lbContainer();
	
	return ERR_NONE;
}


BEGIN_IMPLEMENT_LB_UNKNOWN(lbContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_I_CONTAINER_IMPL(lbContainer)

#ifdef bla
/*...slbContainer:0:*/
/*...slbContainer\58\\58\lbContainer\40\\41\:0:*/
lbContainer::lbContainer() {
    iteration = 0;
    ref = 0;
    iterator = NULL;
    count = 0;
//    lbLog l = lbLog(); // Initialize logging
}
/*...e*/
/*...slbContainer\58\\58\\126\lbContainer\40\\41\:0:*/
lbContainer::~lbContainer() {
}
/*...e*/
/*...slbContainer\58\\58\lbContainer\40\const lbContainer\42\ c\41\:0:*/
lbContainer::lbContainer(const lb_I_Container* c) {
    CL_LOG("This is not good!");
/*
    iteration = c->iteration;
    iterator = c->iterator;
    count = c->count;
    ref = c->ref;
*/
}
/*...e*/
/*...slbContainer\58\\58\operator\61\ \40\const lbContainer\42\ c\41\:0:*/
lb_I_Container* lbContainer::operator= (const lb_I_Container* c) {
    CL_LOG("This is not good!");
/*    
    iteration = c->iteration;
    iterator = c->iterator;
    count = c->count;
*/
    return this;
}
/*...e*/
/*...slbContainer\58\\58\Count\40\\41\:0:*/
int lbContainer::Count() {
	return count;
}
/*...e*/
/*...slbErrCodes lbContainer\58\\58\insert\40\const lb_I_Object\42\ e\44\ const lb_I_KeyBase\42\ key\41\:0:*/
lbErrCodes lbContainer::insert(const lb_I_Object* e, const lb_I_KeyBase* key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _insert(e, key)) != ERR_NONE) {
		LOG("lbContainer::insert(...) Failed!");
		return err;
	}

	count++;
	return err;
}
/*...e*/
/*...slbErrCodes lbContainer\58\\58\remove\40\const lb_I_KeyBase\42\ key\41\:0:*/
lbErrCodes lbContainer::remove(const lb_I_KeyBase* key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _remove(key)) != ERR_NONE) {
		LOG("lbContainer::remove(...) Failed!");
		return err;
	}

	count--;
	return err;
}
/*...e*/
/*...e*/
#endif
#ifdef bla
/*...slbComponentDictionary:0:*/
/*...slbComponentDictionary\58\\58\lbComponentDictionary\40\\41\:0:*/
lbComponentDictionary::lbComponentDictionary() : lbContainer() {
    data = NULL;
}
/*...e*/
/*...slbComponentDictionary\58\\58\lbComponentDictionary\40\\46\\46\\46\\41\:0:*/
lbComponentDictionary::lbComponentDictionary(const lbComponentDictionary* c) {
    CL_LOG("This is not goog!");
/*    
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
*/
}
/*...e*/
/*...slbComponentDictionary\58\\58\operator\61\ \40\\46\\46\\46\\41\:0:*/
lbComponentDictionary& lbComponentDictionary::operator= (const lbComponentDictionary* c) {
    CL_LOG("This is not good");
/*
    iteration = c.iteration;
    iterator = c.iterator;
    count = c.count;
    data = c.data;
    ref++;
*/
    return *this;
}
/*...e*/
/*...slbComponentDictionary\58\\58\\126\lbComponentDictionary\40\\41\:0:*/
lbComponentDictionary::~lbComponentDictionary() {
	ref --;
	if (ref < 0) LOG("Error, reference count not implemented corectly!");
	if (ref == 0) deleteAll();
}
/*...e*/
/*...slbComponentDictionary\58\\58\clone\40\\41\:0:*/
lb_I_Container* lbComponentDictionary::clone() {
//lbLock lock(containerSection, "containerSection");

	lbComponentDictionary* dic = new lbComponentDictionary();
	
	while (hasMoreElements()) {
		lb_I_Element* e = nextElement();
		dic->insert(e->getObject(), e->getKey());
	}	

	return dic;
}
/*...e*/
/*...slbComponentDictionary\58\\58\deleteAll\40\\41\:0:*/
void lbComponentDictionary::deleteAll() {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
//cout << "lbComponentDictionary::deleteAll() called" << endl;
#endif
/*...e*/
//lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
//cout << "containerSection locked" << endl;
#endif
/*...e*/
	while (hasMoreElements()) {
		lb_I_Element* e = nextElement();
if (e == NULL) LOG("NULL pointer");
		remove(e->getKey());
        }
        count = 0;
}
/*...e*/
/*...slbComponentDictionary\58\\58\_insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbComponentDictionary::_insert(const lb_I_Object* e, const lb_I_KeyBase* key) {

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
        lbElement* _data = new lbElement(e, key);
        
        _data->queryInterface("lb_I_Element", (void**) &data);
        
	if (data->getObject() == NULL) {
		LOG("Failed to insert first element in lbComponentDictionary::insert");
		return ERR_CONTAINER_INSERT;
	}
    }
    else {
        lb_I_Element* temp;
        for (temp = data; temp != NULL; temp = temp->getNext()) {
            lb_I_Element* next = temp->getNext();

            if (next != NULL) {
                if (next->getKey() < key) {
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
lbErrCodes lbComponentDictionary::_remove(const lb_I_KeyBase* key) {
//    lbLock lock(containerSection, "containerSection");
    
    if (data == NULL) {
    	LOG("lbComponentDictionary::remove(...) Error: Can't remove from empty container!");
    	return ERR_CONTAINER_REMOVE;
    }

    lb_I_Element* pre = data;
    data = data->getNext();

    if (pre->getKey() == key) {
        pre->release();
        return ERR_NONE;
    }
    
    for (lb_I_Element* temp = data; temp != NULL; temp = data->getNext()) {
        if (temp->getKey() == key) {
            pre->setNext(temp->getNext());
            temp->release();
            return ERR_NONE;
        }
    }
    LOG("lbComponentDictionary::remove(...) Error: No object with that key");
    return ERR_CONTAINER_REMOVE;
}
/*...e*/
/*...slbComponentDictionary\58\\58\exists\40\\46\\46\\46\\41\:0:*/
int lbComponentDictionary::exists(const lb_I_KeyBase* key) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    //cout << "lbComponentDictionary::exists(const lbKeyBase &key) called" << endl;
#endif
/*...e*/
    if (getElement(key) == NULL) return 0;
    return 1;
}
/*...e*/
/*...slbComponentDictionary\58\\58\hasMoreElements\40\\41\:0:*/
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
/*...e*/
/*...slbComponentDictionary\58\\58\nextElement\40\\41\:0:*/
lb_I_Element* lbComponentDictionary::nextElement() {
//    lbLock lock(containerSection, "containerSection");
    lb_I_Element *temp = iterator;
    iterator = iterator->getNext();
	
    return temp;
}
/*...e*/
/*...slbComponentDictionary\58\\58\nextObject\40\\41\:0:*/
lb_I_Object* lbComponentDictionary::nextObject() {
//    lbLock lock(containerSection, "containerSection");
    
    lb_I_Element *temp = iterator;
    iterator = iterator->getNext();

    if (temp == NULL) LOG("Temporary iterator object is NULL!");

    lb_I_Object *o = temp->getObject();

    if (o == NULL) LOG("Temporary object o is NULL!");

    return temp->getObject();
}
/*...e*/
/*...slbComponentDictionary\58\\58\getElement\40\\46\\46\\46\\41\:0:*/
lb_I_Object* lbComponentDictionary::getElement(const lb_I_KeyBase* key) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    //cout << "lbComponentDictionary::getElement(...) called" << endl;
#endif
/*...e*/
//    lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    //cout << "lbLock lock(containerSection) Is locked" << endl;
#endif    
/*...e*/
    lb_I_Element* temp = data;
    while (temp) {
        if ((temp) && (*(temp->getKey()) == key)) {
          lb_I_Object *o = temp->getObject();
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
/*...e*/
/*...slbComponentDictionary\58\\58\setElement\40\\46\\46\\46\\41\:0:*/
void lbComponentDictionary::setElement(lb_I_KeyBase* key, lb_I_Object const* e) {
//    lbLock lock(containerSection, "containerSection");
    remove(key);
    insert(e, key);
}
/*...e*/
/*...slbComponentDictionary\58\\58\getObject\40\\41\:0:*/
lb_I_Object* lbComponentDictionary::getObject() {
//    lbLock lock(containerSection, "containerSection");
    return data->getObject();
}
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbComponentDictionary)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()
#endif

/*...sbla:0:*/
#ifdef bla
lbElement::lbElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lbElement *_next) {
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

lb_I_Object* lbElement::getObject() const {
    return data;
}
#endif
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)



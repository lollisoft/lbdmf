/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.9 $
 * $Name:  $
 * $Id: lbDOMConfig.cpp,v 1.9 2001/05/01 15:51:48 lothar Exp $
 *
 * $Log: lbDOMConfig.cpp,v $
 * Revision 1.9  2001/05/01 15:51:48  lothar
 * First instance could be loaded over the new module management
 *
 * Revision 1.8  2001/04/13 07:39:26  lothar
 * Commit for backup
 *
 * Revision 1.7  2001/03/30 20:08:04  lothar
 * Commit due to possible head crash on anakin (Linux)
 *
 * Revision 1.6  2001/02/15 20:32:39  lothar
 * May work now
 *
 * Revision 1.5  2001/02/06 20:38:15  lothar
 * Commit for backup the data
 *
 * Revision 1.4  2000/11/24 21:05:03  lothar
 * Current version works with lbNodeList and the test program.
 * But the log instance could not created yet.
 *
 * Revision 1.3  2000/10/27 12:18:59  lothar
 * Added DOM list abstraction
 *
 * Revision 1.2  2000/10/20 04:36:31  lothar
 * Minor changes
 *
 * Revision 1.1  2000/10/20 04:28:07  lothar
 * Initial
 *
 **************************************************************/

/*...e*/
/*...sincludes:0:*/
#include <sax/SAXParseException.hpp>
#include <sax/ErrorHandler.hpp>


#include <util/PlatformUtils.hpp>
#include <parsers/DOMParser.hpp>
#include <dom/DOM_Node.hpp>
#include <dom/DOM_NamedNodeMap.hpp>
#include <dom/DOMString.hpp>
#include <iostream.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

#include <conio.h>

//#include <lbInclude.h>

#include <windows.h>

#include <lbConfigHook.h>

#include <lbInterfaces.h>
#include <lbDOMConfig.h>

#include <lbKey.h>
/*...e*/

int initialized = 0;

/*...sforward declarations:0:*/
// Global streaming operator for DOMString is defined in DOMPrint.cpp
void          outputContent(ostream& target, const DOMString &s);
extern ostream& operator<<(ostream& target, const DOMString& s);
ostream& operator<<(ostream& target, DOM_Node& toWrite);


/**
 * lbDOMNode is an abstraction of the implementation of DOM_Node from
 * the IBM implementation. A lbDOMNode must have a back pointer to the
 * lbDOMConfig implementation to be able to use it.
 *
 * A lbDOMNode can only be created by an lbDOMConfig instance. So this
 * is the factory class.
 */
class lbNodeList;
class lbDOMConfig;
/*...e*/

bool doEscapes = false;

class lbDOMContainer;

/*...slbKey:0:*/
lbKey::lbKey() {
    key = 0;
}

lbKey::lbKey(int _key) {
    key = _key;
}

lbKey::lbKey(const lb_I_KeyBase* k) {
    key = ((lbKey) k).key;
}


lbKey::~lbKey(){
}

int lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

lb_I_KeyBase* lbKey::clone() const{
    lbKey *k = new lbKey(key);
    return k;
}

char* lbKey::charrep() {
    char buf[100];

    itoa(key, buf, 10);
    
    return buf;
}
/*...e*/


/*...sclass DOMTreeErrorReporter:0:*/
/*...sclass DOMTreeErrorReporter:0:*/
class DOMTreeErrorReporter : public ErrorHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DOMTreeErrorReporter()
    {
    }

    ~DOMTreeErrorReporter()
    {
    } 


    // -----------------------------------------------------------------------
    //  Implementation of the error handler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& toCatch);
    void error(const SAXParseException& toCatch);
    void fatalError(const SAXParseException& toCatch);
    void resetErrors();
};
/*...e*/
/*...sDOMTreeErrorReporter\58\\58\warning\40\\46\\46\\46\\41\:0:*/
void DOMTreeErrorReporter::warning(const SAXParseException&)
{
    //
    // Ignore all warnings.
    //
}
/*...e*/
/*...sDOMTreeErrorReporter\58\\58\error\40\\46\\46\\46\\41\:0:*/
void DOMTreeErrorReporter::error(const SAXParseException& toCatch)
{
    cerr << "Error at file \"" << DOMString(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << DOMString(toCatch.getMessage()) << endl;
}
/*...e*/
/*...sDOMTreeErrorReporter\58\\58\fatalError\40\\46\\46\\46\\41\:0:*/
void DOMTreeErrorReporter::fatalError(const SAXParseException& toCatch)
{
    cerr << "Fatal Error at file \"" << DOMString(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << DOMString(toCatch.getMessage()) << endl;
}
/*...e*/
/*...sDOMTreeErrorReporter\58\\58\resetErrors\40\\41\:0:*/
void DOMTreeErrorReporter::resetErrors()
{
    // No-op in this case
}
/*...e*/


/*...e*/
/*...sclass lbDOMNode \58\ public lb_I_ConfigObject:0:*/
class lbDOMNode : public lb_I_ConfigObject
//		  , public lb_I_Object // For container usage
		  //public lb_I_Unknown
{
public:
	lbDOMNode();
	virtual ~lbDOMNode();
	
	DECLARE_LB_UNKNOWN()
/*
	DECLARE_LB_OBJECT(lbDOMNode)
*/

/*...slb_I_ConfigObject:0:*/
/* lb_I_ConfigObject */

	virtual lbErrCodes LB_STDCALL getParam(const char* name, lb_I_String*& value);


	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object);
	virtual lbErrCodes LB_STDCALL getParent(lb_I_ConfigObject*& _parent);
	
	virtual lbErrCodes LB_STDCALL getFirstChildren(lb_I_ConfigObject*& children);
	virtual lbErrCodes LB_STDCALL getNextChildren(lb_I_ConfigObject*& children);
	
	virtual int LB_STDCALL getChildrenCount();

	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr);
	virtual lbErrCodes LB_STDCALL getAttributeValue(const char* name, char*& attr);
	virtual char*      LB_STDCALL getName();
/*...e*/

// Some more needed functions not available in the interface

						// Bad here - no interface
	virtual lbErrCodes LB_STDCALL setChildrens(lbNodeList* _childs);
	virtual lbErrCodes LB_STDCALL setParent(lb_I_ConfigObject* _parent);
	
	virtual lbErrCodes LB_STDCALL setNode(DOM_Node _node);
	lbDOMContainer* LB_STDCALL createAbstractedChildList(DOM_Node _node);
protected:


	DOM_Node   node;
	lbDOMNode*   parent;
	
	lbDOMContainer* lbDOMchilds;
	
	int currentChildIndex;
	
	friend class lbDOMConfig;
};
/*...e*/

/*...sContainer for DOM elements:0:*/
/*...sclass lbDOMContainer:0:*/
class lbDOMContainer : 	public lb_I_Container
{

public:
    lbDOMContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbDOMContainer();
    virtual ~lbDOMContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/
/*...sclass lbElement:0:*/
class lbElement : public lb_I_Element {
public:
    lbElement() { next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
	
//    lbElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lb_I_Element *_next=NULL);
    lbElement(const lb_I_Element &e) { next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

#ifdef bla
    void setNext(lb_I_Element *e){ next = e; }
    lb_I_Unknown* getObject() const;

//    lbKeyBase &getKey() const { return *key; }
    lb_I_KeyBase LB_STDCALL *getKey() const
    {
        if (!key) printf("Key in lbElement is null\n");
        return key;
    }

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;
#endif

};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbDOMContainer::lbDOMContainer() {
    iteration = 0;
    ref = 0;
    iterator = NULL;
    count = 0;
    container_data = NULL;
}

lbDOMContainer::~lbDOMContainer() {
}

lbErrCodes LB_STDCALL lbDOMContainer::setData(lb_I_Unknown* data) {
	CL_LOG("lbDOMContainer::setData(lb_I_Unknown* data) called");
	getch();
	return ERR_NONE;
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbDOMContainer)


BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

lbErrCodes LB_STDCALL lbElement::setData(lb_I_Unknown* data) {
	CL_LOG("lbElement::setData(lb_I_Unknown* data) called");
	
	return ERR_NONE;
}

int LB_STDCALL lbElement::equals(const lb_I_Element* a) const {
	return 0;
}

int LB_STDCALL lbElement::equals(const lb_I_KeyBase* key) const {
	return 0;
}
/*...e*/

/*...sclass lbDOMAttribute \58\ public lb_I_Attribute:0:*/
class lbDOMAttribute : public lb_I_Attribute
{

	DECLARE_LB_UNKNOWN()

//	DECLARE_LB_ATTRIBUTE()

	virtual lbErrCodes LB_STDCALL getName(char*& name);
	virtual lbErrCodes LB_STDCALL getValue(char*& value);
	virtual lbErrCodes LB_STDCALL getType(char*& type);
};

lbErrCodes LB_STDCALL lbDOMAttribute::getName(char*& name) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMAttribute::getValue(char*& value) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMAttribute::getType(char*& type) {
	return ERR_NONE;
}


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMAttribute)
	ADD_INTERFACE(lb_I_Attribute)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDOMAttribute::setData(lb_I_Unknown* uk) {
	CL_LOG("lbDOMAttribute::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

/*...e*/

/*...sOld container implementation:0:*/
#ifdef bla
typedef struct __lbDOMNodeList {
	lbDOMNode* element;
	__lbDOMNodeList* next;
} _lbDOMNodeList, * _plbDOMNodeList;

/*...slbDOMContainerElement:0:*/
class lbDOMContainerElement : public lb_I_Element /*,
                              Is already in lb_I_Element.
                              public lb_I_Unknown */ {
public:
    lbDOMContainerElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lb_I_Element *_next=NULL);
    lbDOMContainerElement(const lb_I_Element &e) { next = e.getNext(); }
    virtual ~lbDOMContainerElement();

    virtual lbErrCodes LB_STDCALL release();
    virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown);


    lb_I_Element*      LB_STDCALL getNext() const {return next; }
    void               LB_STDCALL setNext(lb_I_Element *e){ next = e; }
    lb_I_Unknown*      LB_STDCALL getObject() const;

    lb_I_KeyBase*      LB_STDCALL getKey() const
    {
        if (!key) printf("Key in lbElement is null\n");
        return key;
    }

    virtual int        LB_STDCALL equals(const lb_I_Element &a) const;
    virtual int        LB_STDCALL equals(const lb_I_KeyBase &key) const;


//    int operator == (const lb_I_Element &a) const;

//    int operator == (const lb_I_KeyBase &key) const;

private:

    lb_I_Element* next;
    lb_I_Unknown* data;
    lb_I_KeyBase* key;
    
    int ref;
};

lbDOMContainerElement::lbDOMContainerElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lb_I_Element *_next) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbDOMContainerElement::lbDOMContainerElement(const lbObject &o, const lbKeyBase &_key, lbDOMContainerElement *_next) called");
#endif
/*...e*/
//    lbLock lock(elementSection, "containerSection");
    LOG("Warning: No lock used for thread saveness!");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbDOMContainerElement::lbDOMContainerElement(const lbObject &o, const lbKeyBase &_key, lbDOMContainerElement *_next) entered");    
#endif
/*...e*/
    next = _next;
    lb_I_Unknown* uk = o.clone();
    uk->queryInterface("lb_I_Object", (void**) &data);
    key = _key.clone();
    if (key == NULL) LOG("Key cloning in constructor failed. May be a memory problem"); 
}

lbDOMContainerElement::~lbDOMContainerElement() {
}

/*...slbErrCodes lbDOMContainerElement\58\\58\release\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMContainerElement::release() {

// From the lbXMLConfig. But it seems, that this is not used
//	if (interface_used != 0) ref--;

	ref--;

/*...sVERBOSE:0:*/
#ifdef VERBOSE	
cout << "lbDOMContainerElement::release() called (ref is now " << ref << ")" << endl;	
#endif
/*...e*/
	if (ref == STARTREF) {
		cout << "Delete lbDOMContainerElement object" << endl;
		delete this;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbDOMContainerElement\58\\58\queryInterface\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMContainerElement::queryInterface(char* name, void** unknown) {
	
	if (strcmp(name, "lb_I_Unknown") == 0) {
		ref++;
		//interface_used++;
		*unknown = (lb_I_Unknown*) this;
		return ERR_NONE;
	}
	
	return ERR_NO_INTERFACE;
}
/*...e*/

lb_I_Unknown* lbDOMContainerElement::getObject() const {
    return data;
}

int LB_STDCALL lbDOMContainerElement::equals(const lb_I_Element &a) const {
	return (this->getKey() == a.getKey());
}

int LB_STDCALL lbDOMContainerElement::equals(const lb_I_KeyBase &key) const {
	return (this->getKey() == &key);
}
/*...e*/

/*...slbDOMNodeList:0:*/
/*...sclass lbDOMNodeList:0:*/
class lbDOMNodeList : public lb_I_Container {
public:

	lbDOMNodeList();
	virtual ~lbDOMNodeList();

	DECLARE_LB_I_CONTAINER_IMPL
	
private:
	lbErrCodes _remove(const lb_I_KeyBase &key);
	lbErrCodes _insert(const lb_I_Object &e, const lb_I_KeyBase &key);
	
	lb_I_Element* data;
};
/*...e*/
/*...sclass lbDOMNodeList implementation:0:*/
lbDOMNodeList::lbDOMNodeList() {
	iteration = 0;
	ref = 0;
	iterator = NULL;
	count = 0;
}

lbDOMNodeList::~lbDOMNodeList() {
}

/*...slbDOMNodeList\58\\58\Count\40\\41\:0:*/
int LB_STDCALL lbDOMNodeList::Count() {
	return count;
}
/*...e*/
/*...slbDOMNodeList\58\\58\insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNodeList::insert(const lb_I_Object &e, const lb_I_KeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _insert(e, key)) != ERR_NONE) {
		LOG("lbContainer::insert(...) Failed!");
		return err;
	}

	count++;
	return err;
}
/*...e*/
/*...slbDOMNodeList\58\\58\remove\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNodeList::remove(const lb_I_KeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _remove(key)) != ERR_NONE) {
		LOG("lbContainer::remove(...) Failed!");
		return err;
	}

	count--;
	return err;
}
/*...e*/
/*...slbDOMNodeList\58\\58\_insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbDOMNodeList::_insert(const lb_I_Object &e, const lb_I_KeyBase &key) {

//    lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    LOG("lbDOMNodeList::insert(...) called");
#endif
/*...e*/
    if (data == NULL) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbDOMNodeList::insert(...) Inserting first element");
#endif
/*...e*/
        data = new lbDOMContainerElement(e, key);
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
                if (next->getKey() < &key) {
                    temp->setNext(new lbDOMContainerElement(e, key, next));
/*...sCLASSES_VERBOSE:0:*/
            	    #ifdef CLASSES_VERBOSE
            	    LOG("lbDOMNodeList::insert(...) leave");
                    #endif
/*...e*/
                    return ERR_NONE;
                }
            }
            else {
                temp->setNext(new lbDOMContainerElement(e, key));
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
            	LOG("lbDOMNodeList::insert(...) leave");
#endif
/*...e*/
                return ERR_NONE;
            }
        }
    }
    return ERR_NONE;      
}
/*...e*/
/*...slbDOMNodeList\58\\58\_remove\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbDOMNodeList::_remove(const lb_I_KeyBase &key) {
//    lbLock lock(containerSection, "containerSection");
    
    if (data == NULL) {
    	LOG("lbDOMNodeList::remove(...) Error: Can't remove from empty container!");
    	return ERR_CONTAINER_REMOVE;
    }

    lb_I_Element* pre = data;
    data = data->getNext();

    if (pre->getKey() == &key) {
        //delete pre;
        pre->release();
        return ERR_NONE;
    }
    
    for (lb_I_Element* temp = data; temp != NULL; temp = data->getNext()) {
        if (temp->getKey() == &key) {
            pre->setNext(temp->getNext());
            temp->release();
            return ERR_NONE;
        }
    }
    LOG("lbDOMNodeList::remove(...) Error: No object with that key");
    return ERR_CONTAINER_REMOVE;
}
/*...e*/
/*...slbDOMNodeList\58\\58\exists\40\const lb_I_KeyBase\38\ e\41\:0:*/
int LB_STDCALL lbDOMNodeList::exists(const lb_I_KeyBase& e) {
	LOG("Error: lbDOMNodeList::exists(const lb_I_KeyBase& e) is not implemented");
	return 0;
}
/*...e*/
/*...slbDOMNodeList\58\\58\nextObject\40\\41\:0:*/
lb_I_Object* LB_STDCALL lbDOMNodeList::nextObject() {
	return NULL;
}
/*...e*/
/*...slbDOMNodeList\58\\58\hasMoreElements\40\\41\:0:*/
int LB_STDCALL lbDOMNodeList::hasMoreElements() {
	return 0;
}
/*...e*/
/*...slbDOMNodeList\58\\58\getElement\40\const lb_I_KeyBase \38\key\41\:0:*/
lb_I_Object* LB_STDCALL lbDOMNodeList::getElement(const lb_I_KeyBase &key) {
	return NULL;
}
/*...e*/
/*...slbDOMNodeList\58\\58\setElement\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbDOMNodeList::setElement(lb_I_KeyBase &key, const lb_I_Object &e) {
	
}
/*...e*/

lb_I_Container* LB_STDCALL lbDOMNodeList::clone() {
	return NULL;
}

void LB_STDCALL lbDOMNodeList::deleteAll() {

}
/*...e*/
/*...e*/

/*...slbNodeList:0:*/
#ifdef bla
/*...s:0:*/
class lbDOMNodeList : public lb_I_Container {
public:

	lbDOMNodeList();
	virtual ~lbDOMNodeList();

	DECLARE_LB_I_CONTAINER_IMPL
	
private:
	lbErrCodes _remove(const lb_I_KeyBase &key);
	lbErrCodes _insert(const lb_I_Object &e, const lb_I_KeyBase &key);
	
	lbDOMContainerElement* data;
};

lbDOMNodeList::lbDOMNodeList() {
	iteration = 0;
	ref = 0;
	iterator = NULL;
	count = 0;
}

lbDOMNodeList::~lbDOMNodeList() {
}

/*...slbDOMNodeList\58\\58\Count\40\\41\:0:*/
int LB_STDCALL lbDOMNodeList::Count() {
	return count;
}
/*...e*/
/*...slbDOMNodeList\58\\58\insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNodeList::insert(const lb_I_Object &e, const lb_I_KeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _insert(e, key)) != ERR_NONE) {
		LOG("lbContainer::insert(...) Failed!");
		return err;
	}

	count++;
	return err;
}
/*...e*/
/*...slbDOMNodeList\58\\58\remove\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNodeList::remove(const lb_I_KeyBase &key) {
	lbErrCodes err = ERR_NONE;

	if ((err = _remove(key)) != ERR_NONE) {
		LOG("lbContainer::remove(...) Failed!");
		return err;
	}

	count--;
	return err;
}
/*...e*/
/*...slbDOMNodeList\58\\58\_insert\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbDOMNodeList::_insert(const lb_I_Object &e, const lb_I_KeyBase &key) {

//    lbLock lock(containerSection, "containerSection");
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
    LOG("lbDOMNodeList::insert(...) called");
#endif
/*...e*/
    if (data == NULL) {
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
LOG("lbDOMNodeList::insert(...) Inserting first element");
#endif
/*...e*/
        data = new lbDOMContainerElement(e, key);
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
                if (next->getKey() < &key) {
                    temp->setNext(new lbDOMContainerElement(e, key, next));
/*...sCLASSES_VERBOSE:0:*/
            	    #ifdef CLASSES_VERBOSE
            	    LOG("lbDOMNodeList::insert(...) leave");
                    #endif
/*...e*/
                    return ERR_NONE;
                }
            }
            else {
                temp->setNext(new lbDOMContainerElement(e, key));
/*...sCLASSES_VERBOSE:0:*/
#ifdef CLASSES_VERBOSE
            	LOG("lbDOMNodeList::insert(...) leave");
#endif
/*...e*/
                return ERR_NONE;
            }
        }
    }
    return ERR_NONE;      
}
/*...e*/
/*...slbDOMNodeList\58\\58\_remove\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbDOMNodeList::_remove(const lb_I_KeyBase &key) {
//    lbLock lock(containerSection, "containerSection");
    
    if (data == NULL) {
    	LOG("lbDOMNodeList::remove(...) Error: Can't remove from empty container!");
    	return ERR_CONTAINER_REMOVE;
    }

    lb_I_Element* pre = data;
    data = data->getNext();

    if (pre->getKey() == &key) {
        delete pre;
        return ERR_NONE;
    }
    
    for (lb_I_Element* temp = data; temp != NULL; temp = data->getNext()) {
        if (temp->getKey() == &key) {
            pre->setNext(temp->getNext());
            delete temp;
            return ERR_NONE;
        }
    }
    LOG("lbDOMNodeList::remove(...) Error: No object with that key");
    return ERR_CONTAINER_REMOVE;
}
/*...e*/
/*...slbDOMNodeList\58\\58\exists\40\const lb_I_KeyBase\38\ e\41\:0:*/
int LB_STDCALL lbDOMNodeList::exists(const lb_I_KeyBase& e) {
	LOG("Error: lbDOMNodeList::exists(const lb_I_KeyBase& e) is not implemented");
	return 0;
}
/*...e*/
/*...slbDOMNodeList\58\\58\nextObject\40\\41\:0:*/
lb_I_Object* LB_STDCALL lbDOMNodeList::nextObject() {
	return NULL;
}
/*...e*/
/*...slbDOMNodeList\58\\58\hasMoreElements\40\\41\:0:*/
int LB_STDCALL lbDOMNodeList::hasMoreElements() {
	return 0;
}
/*...e*/
/*...slbDOMNodeList\58\\58\getElement\40\const lb_I_KeyBase \38\key\41\:0:*/
lb_I_Object* LB_STDCALL lbDOMNodeList::getElement(const lb_I_KeyBase &key) {
	return NULL;
}
/*...e*/
/*...slbDOMNodeList\58\\58\setElement\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbDOMNodeList::setElement(lb_I_KeyBase &key, const lb_I_Object &e) {
	
}
/*...e*/

lb_I_Container* LB_STDCALL lbDOMNodeList::clone() {
	return NULL;
}

void LB_STDCALL lbDOMNodeList::deleteAll() {

}
/*...e*/
#endif

class lbNodeList { //: public lb_I_Container {
public:
	lbNodeList() { 
		count = 0; 
		childs = NULL; 
		parent = NULL; 
	}
	virtual ~lbNodeList() {}

	lbErrCodes setParent(lb_I_Unknown *_parent);
	lbErrCodes insert(lb_I_Unknown *node);
	lbErrCodes remove(int i);
	lbErrCodes find(const char *nodeName, int & i);
	lbErrCodes get(lb_I_Unknown*& node, int i);
	
	int Count() { return count; }
	
	lb_I_Container* clone() const;

protected:
	lbDOMNode* parent;
	_plbDOMNodeList childs;
	int count;
};
/*...e*/
#endif
/*...e*/




/*...sclass lbDOMNode implementation:0:*/
//IMPLEMENT_LB_OBJECT(lbDOMNode, LB_DOM_NODE)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMNode)
	ADD_INTERFACE(lb_I_Object)
	ADD_INTERFACE(lb_I_ConfigObject)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDOMNode::setData(lb_I_Unknown* uk) {
	lbDOMNode* _node = NULL;
	
	if (uk->queryInterface("lb_I_ConfigObject", (void**) &_node) != ERR_NONE) {
		CL_LOG("Error: Cloning interface not present!");
		getch();
	}
	
	node = _node->node;
	
	if (_node->parent == _node) {
#ifdef VERBOSE
		CL_LOG("Warning: Cloning a object without parent pointing to a real parent!");
		getch();
#endif
	}
	else
	if (_node->parent->queryInterface("lb_I_Unknown", (void**) &parent) != ERR_NONE) {
		CL_LOG("Error: Cloning lbDOMNode failed due to increment refcount of source's parent!");
		getch();
	}
	
	return ERR_NONE;
}


lbDOMNode::lbDOMNode() {
	ref = STARTREF;
	currentChildIndex = 0;
	lbDOMchilds = NULL;
	parent = this;
#ifdef VERBOSE
	CL_LOG("Warning: Parent is set to my self in c'tor");
#endif
}

lbDOMNode::~lbDOMNode() {
	if (ref != STARTREF) 
		CL_LOG("Error: Reference count mismatch");
}

lbErrCodes LB_STDCALL lbDOMNode::setChildrens(lbNodeList* _childs) {
	CL_LOG("Not implemented yet");
	getch();
	return ERR_NONE;
}
/*...slbDOMNode\58\\58\getParent\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getParent(lb_I_ConfigObject*& _parent) {
	if (parent == NULL) {
		CL_LOG("Error: lbDOMNode is not correctly set up. Parent is NULL!");
		getch();
	}
	parent->queryInterface("lb_I_ConfigObject", (void**) &_parent);



	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lbDOMNode::setParent(lb_I_ConfigObject* _parent) {
	CL_LOG("lbDOMNode::setParent(...) not implemented yet");
	getch();
	return ERR_NONE;
}

/*...slbDOMNode\58\\58\setNode\40\DOM_Node _node\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::setNode(DOM_Node _node) {
	/**
	 * A node possibly has some childs. Because of the search result, the nodes
	 * are not encapsulated in a lbDOMNode. To increase the speed for further
	 * requests, the abstracted childs of that node are created now.
	 */

	if (_node.isNull()) {
		CL_LOG("Error: Null node could not be set!");
		getch();
	}

	lbDOMchilds = createAbstractedChildList(_node);
	
	if (lbDOMchilds == NULL) {
		CL_LOG("Error: Here must be a result!");
		
	}
	
	node = _node; 
	if (node.isNull()) {
		CL_LOG("Error: Null node could not be set!");
		getch();
	}
	
	DOM_Node pnode = _node.getParentNode();

	if (pnode != NULL) {
		if (parent != NULL) {
#ifdef VERBOSE		
			CL_LOG("Previous parent node will be overwritten!");
#endif			
		}
		parent = new lbDOMNode;
		parent->setNode(pnode);
	} else {
		if (parent != NULL) {
			CL_LOG("Previous parent node must be deleted!");
			
		}
	}
	return ERR_NONE;
}
/*...e*/
#ifdef bla
// Body already defined (macro)
/*...slbDOMNode\58\\58\clone\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbDOMNode::clone() const {
	lbDOMNode* _node = new lbDOMNode();
	
	_node->node = node;
	if (_node->node.isNull()) {
		CL_LOG("Error: Cloning failed due to NULL pointer in node!");
		getch();
	}
	
	lb_I_Container* cloned= lbDOMchilds->clone();
	_node->lbDOMchilds = (lbNodeList*) cloned;

	/**
	 * Return an unknown object pointer
	 */	
	lb_I_Unknown* ret = NULL;
	_node->queryInterface("lb_I_Unknown", (void**) ret);
	
	//QI(_node, "lb_I_Unknown", ret);
	
	return ret;
}
/*...e*/
#endif
/*...slbDOMNode\58\\58\getParam\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getParam(const char* name, lb_I_String*& value) {
	CL_LOG("Not implemented yet");
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getChildrenCount\40\\41\:0:*/
int LB_STDCALL lbDOMNode::getChildrenCount() {
	CL_LOG("Not implemented yet");
	return 0;
}
/*...e*/
/*...slbDOMNode\58\\58\findObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::findObject(const char* name, lb_I_ConfigObject*& object) {
	CL_LOG("Not implemented yet");
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getFirstChildren\40\lb_I_ConfigObject\42\\38\ children\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getFirstChildren(lb_I_ConfigObject*& children) {
	if (lbDOMchilds == NULL) {
		CL_LOG("Error, no childrens in config object");
		return ERR_CONFIG_NO_CHILDS;
	}
	
	currentChildIndex = 0;
	
	lb_I_Unknown* unknown = NULL;

	if (lbDOMchilds->hasMoreElements() == 1) {
		unknown = lbDOMchilds->nextElement();
	} else {
		CL_LOG("ERROR: No child found");
		return ERR_CONFIG_EMPTY_CONTAINER;
	}

	if (unknown == NULL) {
		CL_LOG("Fatal: Must have a children here!");
	}

	unknown->queryInterface("lb_I_ConfigObject", (void**) &children);

	unknown->release();

	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getNextChildren\40\lb_I_ConfigObject\42\\38\ children\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getNextChildren(lb_I_ConfigObject*& children) {
	lbErrCodes err = ERR_NONE;
	
	if (lbDOMchilds == NULL) return ERR_CONFIG_NO_CHILDS;
	
	currentChildIndex++;
	
	if (currentChildIndex >= lbDOMchilds->Count()) {
		CL_LOG("ERR_CONFIG_NO_MORE_CHILDS");
		
		return ERR_CONFIG_NO_MORE_CHILDS;
	}
	
	lb_I_Unknown* unknown;

	unknown = lbDOMchilds->nextElement();

	if (unknown == NULL) {
		CL_LOG("Fatal: Must have a children here!");
		
	}

	unknown->queryInterface("lb_I_ConfigObject", (void**) &children);
	
	unknown->release();
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\createAbstractedChildList\40\DOM_Node node\41\:0:*/
lbDOMContainer* LB_STDCALL lbDOMNode::createAbstractedChildList(DOM_Node _node) {


	DOM_NodeList DOMlist = _node.getChildNodes();
	int len = DOMlist.getLength();	
	lbDOMContainer* list = new lbDOMContainer;
	lbErrCodes err = ERR_NONE;

	for (int i = 0; i < len; i++) {
	        DOM_Node child = DOMlist.item(i);	
	        lbDOMNode* lbNode = new lbDOMNode;
	        
	        lbNode->node = child;

		lb_I_Unknown* unknown = NULL;

		if (lbNode->queryInterface("lb_I_Unknown", (void**) &unknown) != ERR_NONE) {
		        CL_LOG("lbNode->queryInterface() Failed!");
		}
		lbKey* key = new lbKey(i);
		if (unknown == NULL) CL_LOG("Error: Inserting a null pointer!");
		list->insert(unknown, key);
		
	}

	return list;
}
/*...e*/
/*...slbDOMNode\58\\58\getAttribute\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getAttribute(const char* name, lb_I_Attribute*& attr) {

	/**
	 * In the first use of this function, I like to get a functor as an attribute.
	 */
	CL_LOG("lbDOMNode::getAttribute(...): Not implemented yet");
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getAttributeValue\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getAttributeValue(const char* name, char*& attr) {

	DOM_NamedNodeMap attributeMap = node.getAttributes();
	
	if (attributeMap == NULL) {
		CL_LOG("Error: This node is not of type ELEMENT");
		
		return ERR_UNSPECIFIED;
	}
	
	DOM_Attr an_attr = (DOM_Attr&) attributeMap.getNamedItem(DOMString(name));	
	
	if (an_attr == NULL) {
		CL_LOG("Error: Attribute not found");
		
		return ERR_UNSPECIFIED;
	}
	
	DOMString value = an_attr.getValue();
		
	attr = value.transcode();
	
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getName\40\\41\:0:*/
char* LB_STDCALL lbDOMNode::getName() {
#ifdef VERBOSE
	CL_LOG("lbDOMNode::getName() called");
	getch();
#endif
	if (node.isNull()) {
		CL_LOG("node is NULL!");
		getch();
		return "";
	}

	DOMString string = node.getNodeName();

#ifdef VERBOSE
	CL_LOG("Got the DOMString");
	getch();
#endif

	char* temp = string.transcode();

#ifdef VERBOSE
	CL_LOG("Got the node name");
	getch();
#endif	
	return temp;
}
/*...e*/



#ifdef bla
/*...slbDOMNode\58\\58\release\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::release() {
        ref--;

        if (ref == STARTREF) delete this;
	
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\queryInterface\40\char\42\ name\44\ void\42\\42\ unknown\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::queryInterface(char* name, void** unknown) {
cout << "lbDOMNode::queryInterface(char* name, void** unknown) called" << endl;
        if (strcmp(name, "lb_I_Unknown") == 0) {
                ref++;
                *unknown = (lb_I_Unknown*) this;
                return ERR_NONE;
        }

        if (strcmp(name, "lb_I_Object") == 0) {
                ref++;
                *unknown = (lb_I_Object*) this;
                return ERR_NONE;
        }

        if (strcmp(name, "lb_I_ConfigObject") == 0) {
                ref++;
                *unknown = (lb_I_ConfigObject*) this;
                return ERR_NONE;
        }


        return ERR_NO_INTERFACE;
}
/*...e*/
#endif
/*...e*/
#ifdef bla
/*...sclass lbNodeList implementation:0:*/

/**
 * What can be stored in a node list ?
 * 
 */

/*...slbNodeList\58\\58\clone\40\\41\:0:*/
lb_I_Container* lbNodeList::clone() const {
	lbNodeList* list = new lbNodeList();
	lb_I_Unknown *u = parent->clone();
	u->queryInterface("lb_I_NodeList", (void**) list->parent);
	u->release();

CL_LOG("lbNodeList::clone() called");


	/**
	 * The content of 'childs' must be copied sequential.
	 */
	
	_plbDOMNodeList temp = childs;
	_plbDOMNodeList tempother = list->childs;
	list->childs = new _lbDOMNodeList;
	list->childs->next = NULL;
	
	while (temp != NULL) {
		lb_I_Unknown *u = temp->element->clone();
		u->queryInterface("lb_I_DOMNode", (void**) list->childs->element);
		u->release();
		
		list->childs->next = new _lbDOMNodeList;
		list->childs->next->next = NULL;
		list->childs = list->childs->next;
	}
	
	list->childs = tempother;
	
	return NULL;
}
/*...e*/
/*...slbNodeList\58\\58\setParent\40\lb_I_Unknown \42\_parent\41\:0:*/
lbErrCodes lbNodeList::setParent(lb_I_Unknown *_parent) {
	/**
	 * Check if the given object has a lb_I_ConfigObject interface
	 */

	_parent->queryInterface("lb_I_ConfigObject", (void**) parent);

	if (parent != NULL) 
		return ERR_NONE;
	else
		cout << "Error: The parent object has no lb_I_ConfigObject interface" << endl;
		return ERR_NO_INTERFACE;
}
/*...e*/
/*...slbNodeList\58\\58\insert\40\lb_I_Unknown \42\node\41\:0:*/
lbErrCodes lbNodeList::insert(lb_I_Unknown *node) {
	_plbDOMNodeList list = childs;
	lb_I_Object* object = NULL;
	lbDOMNode* newNode = NULL;
	
	node->queryInterface("lb_I_Object", (void**) &object);

	if (object == NULL) {
		cout << "Try to log" << endl;
		cout << "Error: Only objects, that provide a lb_I_Object interface, could be stored" << endl;
		cout << "Logged" << endl;
		node->release();
		return ERR_NO_INTERFACE;
	}
	
	// The lb_I_Object reference is no more used now
	node->release();
	
	node->queryInterface("lb_I_ConfigObject", (void**) &newNode);
	
	if (newNode == NULL) {
		cout << "Error: This container can only store lb_I_ConfigObjects" << endl;
		return ERR_NO_INTERFACE;
	} 
	
	if (list == NULL) {
		childs = list = new _lbDOMNodeList;
		list->next = NULL;
		list->element = newNode;
	} else {
		while (list->next != NULL) list = list->next;
	
		list->next = new _lbDOMNodeList;
		list = list->next;
	
		list->element = newNode;
		list->next = NULL;
	}

	if (childs == NULL) {
		CL_LOG("Error: childs is still a NULL pointer !!");
		
	}
	
	count++;
		
	return ERR_NONE;
}
/*...e*/
/*...slbNodeList\58\\58\remove\40\int i\41\:0:*/
lbErrCodes lbNodeList::remove(int i) {
	cout << "lbNodeList::remove(...) not implemented!" << endl;
	return ERR_NONE;
}
/*...e*/
/*...slbNodeList\58\\58\find\40\const char \42\nodeName\44\ int \38\ i\41\:0:*/
lbErrCodes lbNodeList::find(const char *nodeName, int & i) {
	cout << "lbNodeList::find(const char* '" << nodeName << "', int i) not implemented!" << endl;
	_plbDOMNodeList list = childs;
	return ERR_NONE;
}
/*...e*/
/*...slbNodeList\58\\58\get\40\lb_I_Unknown\42\\38\ node\44\ int i\41\:0:*/
lbErrCodes lbNodeList::get(lb_I_Unknown*& node, int i) {
	if (childs == NULL) {
		CL_LOG("Container lbNodeList is empty !");
		return ERR_CONFIG_EMPTY_CONTAINER;
	}
	
	if (i >= count) {
		CL_LOG("Container lbNodeList bounds !");
		return ERR_CONFIG_CONTAINER_BOUND;
	}
	
	_plbDOMNodeList list = childs;
	
	for (int ii = 0; ii < i; ii++) {
		if (list == NULL) {
			CL_LOG("Found a bug at lbNodeList::get(lb_I_Unknown*& node, int i)");
			
		}
		
		list = list->next;
	}
	if (list == NULL) {
		CL_LOG("list is NULL!");
		
	}
	
	if (list->element == NULL) {
		CL_LOG("list->element is NULL!");
		
	}	
	
	list->element->queryInterface("lb_I_Unknown", (void**) &node);
	
	if (node == NULL) {
		cout << "Error, stored object has no lb_I_Unknown interface!" << endl;
		return ERR_CONFIG_INTERNAL;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...e*/
#endif
/*...sclass lbDOMConfig \58\ public lb_I_XMLConfig:0:*/
/*...sclass lbDOMConfig:0:*/
class lbDOMConfig : 
		public lb_I_XMLConfig
{
public:
	lbDOMConfig();
	~lbDOMConfig();
	lbDOMConfig(const lbDOMConfig & t) {
		ref = STARTREF;
		errReporter = NULL;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbDOMConfig(const lbDOMConfig* & t) called" << endl;
	
#endif	
/*...e*/
	}

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL parse();
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName, int & count);
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject*& cfgObj, const char* const cfgObjectName);

protected:
	lbDOMContainer* LB_STDCALL findNodesAtTreePos(const char* treePos);
	lbDOMContainer* LB_STDCALL createAbstractedChildList(const DOM_Node node);

	int interface_used;
	ErrorHandler *errReporter;
	
	int errorsOccured;
	DOM_Document doc;
	
	lbDOMContainer* lastResult;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMConfig)
	ADD_INTERFACE(lb_I_XMLConfig)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDOMConfig::setData(lb_I_Unknown* uk) {
	CL_LOG("lbDOMConfig::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

/*...slbDOMConfig\58\\58\lbDOMConfig\40\\41\:0:*/
lbDOMConfig::lbDOMConfig() {
	ref = STARTREF;
	interface_used = 0;
	errReporter = new DOMTreeErrorReporter();
	
	    if (initialized == 0) {
/*...sInitialize the DOM4C2 system:20:*/
		    // Initialize the DOM4C2 system
		    try
		    {
				XMLPlatformUtils::Initialize();
		    }

			catch (const XMLException& toCatch)
		    {
				cout << "Error during initialization! :\n"
		                 << toCatch.getMessage() << endl;
		         //return ERR_XML_INIT;
		    }		
/*...e*/
	    }
	    
	parse();	
}
/*...e*/
/*...slbDOMConfig\58\\58\\126\lbDOMConfig\40\\41\:0:*/
lbDOMConfig::~lbDOMConfig() {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbDOMConfig::~lbDOMConfig() called" << endl;
#endif
/*...e*/
	if (ref != STARTREF) cout << "Error: Reference count mismatch!" << endl;
	
	if (errReporter != NULL) {
		delete errReporter;
	}
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::parse() {
	lbErrCodes err = ERR_NONE;
cout << "lbDOMConfig::parse() called ('" << hex << (void*) this << dec << "')" << endl;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "Parse file '" << filename << "'..." << endl;
#endif
/*...e*/

	if (filename != NULL) {
#ifdef bla
	    if (initialized == 0) {
/*...sInitialize the DOM4C2 system:20:*/
		    // Initialize the DOM4C2 system
		    try
		    {
				XMLPlatformUtils::Initialize();
		    }

			catch (const XMLException& toCatch)
		    {
				cout << "Error during initialization! :\n"
		                 << toCatch.getMessage() << endl;
		         return ERR_XML_INIT;
		    }		
/*...e*/
	    }
#endif
//for (long i = 0; i < 1000000; i++) {

/*...sSetup objects:12:*/
	    // Begin parsing...
	    DOMParser parser;
	    parser.setDoValidation(true);

	    parser.setErrorHandler(errReporter);
		
/*...e*/


/*...stry parsing \40\no explicid allocation\41\:12:*/
	    // Parse the file and catch any exceptions that propogate out
	    try	
		{
		    errorsOccured = 0;
	            parser.parse(filename);
	            
	            doc = parser.getDocument();
		}

		catch (const XMLException& )
	        {
			cout << "Parse error\n" << endl;
			errorsOccured = 1;
			return ERR_XML_NOFILE;
		}
/*...e*/

	    // Clean up our parser and handler
	    //delete handler;
//}	

	} else return ERR_NO_ENVIRONMENT;
	return err;
}
/*...e*/
/*...slbDOMContainer\42\ lbDOMConfig\58\\58\findNodesAtTreePos\40\const char\42\ treePos\41\:0:*/
lbDOMContainer* LB_STDCALL lbDOMConfig::findNodesAtTreePos(const char* treePos) {
	char* part = NULL;
	char* name = NULL;
	char* savename = NULL;
	int count = 1;
	
	
/*...sPrepare search:8:*/
	/**
	 * Use a lb_I_Container (implemented here)
	 */
	lbDOMContainer* list = new lbDOMContainer;

	if (treePos == NULL) {
		cout << "Null pointer detected!" << endl;
		
		exit(1);
	}	

	savename = strdup(treePos);
	name = strrchr(savename, '/');
	if (name == NULL) name = savename;
	
	cout << "Search for nodename '" << ((name[0] == '/') ? &name[1] : name) << "'" << endl;
	
	DOM_NodeList DOMlist = doc.getElementsByTagName(((name[0] == '/') ? &name[1] : name));
	int len = DOMlist.getLength();

	DOMString path;
/*...e*/

	if (len == 0) cout << "Nothing found" << endl;
	
	for (int i = 0; i < len; i++) {
		path = "";
		DOM_Node node = DOMlist.item(i);
		DOM_Node currentnode = node;
		
/*...sBuild the path:16:*/
		/**
		 * Build the path to this node by recursively getting
		 * parents.
		 */
		 
		while (node != NULL) {
			DOMString name = node.getNodeName();
			node = node.getParentNode();
			path = name + DOMString(((path == "") ? "" : "/")) + path;
		}
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Node XPointer: '" << path << "'" << endl
		     << "Search for   : '" << DOMString(treePos) << "'" << endl;
#endif
/*...e*/
/*...sFound a entry \63\ insert in list:16:*/
		if (path.equals(treePos)) {
/*...sVERBOSE:16:*/
#ifdef VERBOSE
			cout << "Found a entry." << endl;
#endif		
/*...e*/
			/**
			 * Create the wrapper object lbDOMNode, after it has
			 * implemented all abstract members.
			 */
			
			lbDOMNode* lbNode = new lbDOMNode;
			
			lbNode->setNode(currentnode);
/*...sbla:16:*/
#ifdef bla
			lbNode->node = currentnode;
			
			/**
			 * The element is a view in a list. So the list is the parent,
			 * not the parent of currentnode! Currently, the list is not
			 * an abstraction of a lb_I_ConfigObject. So there can't be assigned
			 * a list to parent.
			 */
			//lbNode->parent = list; //currentnode.getParentNode();
			
			/**
			 * At this point I should construct a list of childs where a lb_I_ConfigObject
			 * abstracts the DOM_Node. So the elements in a view can be used to really get
			 * their childs.
			 *
			 * lbNode->childs -> lb_I_ConfigObject >> DOM_Node
			 *                   lb_I_ConfigObject >> DOM_Node
			 *                   lb_I_ConfigObject >> DOM_Node
			 *                   lb_I_ConfigObject >> DOM_Node
			 *
			 */
			
			/**
			 * A node possibly some childs. Because of the search result, the nodes
			 * are not encapsulated in a lbDOMNode. To increase the speed for further
			 * requests, the abstracted childs of that node are created now.
			 */
			lbNode->childs = createAbstractedChildList(lbNode->node); 
			 
			//lbNode->childs = NULL;
#endif
/*...e*/
			lb_I_Unknown* unknown = NULL;
			if (lbNode->queryInterface("lb_I_Unknown", (void**) &unknown) != ERR_NONE) {
				CL_LOG("lbNode->queryInterface() Failed!");
			}
			lbKey* key = new lbKey(count++);
			list->insert(unknown, key);
/*...sVERBOSE:16:*/
#ifdef VERBOSE
			cout << "Inserted the entry" << endl;
#endif
/*...e*/
		} else cout << "Path '" << path << "' does not match" << endl;
/*...e*/

	}
	return list;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDOMConfig\58\\58\hasConfigObject\40\const char\42\ \44\ int \38\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::hasConfigObject(const char* cfgObjectName, int & count) {
	lb_I_ConfigObject* obj = NULL;
	lbErrCodes err = ERR_NONE;

	DOMString name = DOMString(cfgObjectName);

	if (errorsOccured == 0) {
		
		lastResult = findNodesAtTreePos(cfgObjectName);

		count = lastResult->Count(); //= lastResult->getChildrenCount();

		return err;
	} else cout << "Any errors while parsing has been occured!" << endl;
	
	return err;
/*...sbla:0:*/
#ifdef bla		
		
		
		if (len == 0) {
			err = ERR_NO_OBJECT;
			cout << "No object found" << endl;
			return err;
		}
		
		if (len > 1) {
			err = ERR_MORE_OBJECTS;
			cout << "Found " << len << " objects" << endl;
			return err;
		}
		
		
		err = ERR_SINGLE_OBJECT;
		cout << "Found 1 object" << endl;
	} else cout << "Any errors while parsing has been occured!" << endl;

	return err;
#endif
/*...e*/
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\getConfigObject\40\lb_I_ConfigObject\42\\38\ \44\ const char\42\ const\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::getConfigObject(lb_I_ConfigObject*& cfgObj, 
                                        const char* const cfgObjectName) {
	lbErrCodes err = ERR_NONE;
	// Try to locate the identifer in the tree

	/**
	 * Create the view for this result.
	 */
	 
	lbDOMNode *node = new lbDOMNode;
	node->lbDOMchilds = lastResult;
	node->node = NULL; // See null pointer operator
	
	cout << "lbDOMNode has been created. How should a view be structured ?" << endl;

	// This interface is needed:
	node->queryInterface("lb_I_ConfigObject", (void**) &cfgObj);

#ifdef bla
	cout << "lbDOMConfig::getConfigObject(...) called" << endl;

	if ((err = gTopLevel->m_plbConfigObject->findObject(cfgObjectName, cfgObj)) != ERR_NONE) {
		return err;
	}
#endif	
	return err;
}
/*...e*/
/*...e*/
/*...sLBDOMCONFIG_API getlbDOMConfigInstance\40\lb_I_XMLConfig\42\\38\ inst\41\:0:*/
lbErrCodes LBDOMCONFIG_API __cdecl getlbDOMConfigInstance(lb_I_XMLConfig*& inst) {
/*...sMEMTEST:0:*/
#ifdef MEMTEST	
	cout << "Initialize lbXMLConfig object" << endl;
	
	
	for (long i = 0; i < 1000000; i++) { 
#endif
/*...e*/
		inst = new lbDOMConfig();
		
/*...sMEMTEST:0:*/
#ifdef MEMTEST		
		inst->release();
	}
	
	cout << "Done it" << endl;
	
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...sostream\38\ operator\60\\60\\40\ostream\38\ target\44\ const DOMString\38\ s\41\:0:*/
// ---------------------------------------------------------------------------
//
//  ostream << DOMString    Stream out a DOM string.
//                          Doing this requires that we first transcode
//                          to char * form in the default code page
//                          for the system
//
// ---------------------------------------------------------------------------
ostream& operator<<(ostream& target, const DOMString& s)
{
    char *p = NULL;
    p = s.transcode();
    target << ((p) ? p : "?");
    
    // May be static buffer ??
    //if (p) free(p);
    
    return target;
}
/*...e*/
/*...sostream\38\ operator\60\\60\\40\ostream\38\ target\44\ DOM_Node\38\ toWrite\41\:0:*/
ostream& operator<<(ostream& target, DOM_Node& toWrite)
{
    // Get the name and value out for convenience
    DOMString   nodeName = toWrite.getNodeName();
    DOMString   nodeValue = toWrite.getNodeValue();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "Got node name and value" << endl;
if (nodeValue == NULL) 
	cout << "Value is NULL" << endl;
else
	cout << "Value is " << nodeValue << endl;
	
if (nodeName == NULL) 
	cout << "Name is NULL" << endl;
else
	cout << "Name is " << nodeName << endl;

cout << "Check done" << endl;
#endif
/*...e*/
	switch (toWrite.getNodeType())
    {
		case DOM_Node::TEXT_NODE:
        {
            outputContent(target, ((nodeValue == NULL) ? "?" : nodeValue));
            break;
        }

        case DOM_Node::PROCESSING_INSTRUCTION_NODE :
        {
            target  << "<?"
                    << nodeName
                    << ' '
                    << ((nodeValue == NULL) ? "?" : nodeValue)
                    << "?>";
            break;
        }

        case DOM_Node::DOCUMENT_NODE :
        {
            // Bug here:  we need to find a way to get the encoding name
            //   for the default code page on the system where the
            //   program is running, and plug that in for the encoding
            //   name.  
            target << "<?xml version='1.0' encoding='ISO-8859-1' ?>\n";
            DOM_Node child = toWrite.getFirstChild();
            while( child != 0)
            {
                target << child << endl;
                child = child.getNextSibling();
            }

            break;
        }

        case DOM_Node::ELEMENT_NODE :
        {
            // Output the element start tag.
            target << '<' << nodeName;

            // Output any attributes on this element
            DOM_NamedNodeMap attributes = toWrite.getAttributes();
            int attrCount = attributes.getLength();
            for (int i = 0; i < attrCount; i++)
            {
                DOM_Node  attribute = attributes.item(i);

                target  << ' ' << attribute.getNodeName()
                        << " = \"";
                        //  Note that "<" must be escaped in attribute values.
                        outputContent(target, attribute.getNodeValue());
                        target << '"';
            }

            //
            //  Test for the presence of children, which includes both
            //  text content and nested elements.
            //
            DOM_Node child = toWrite.getFirstChild();
            if (child != 0)
            {
                // There are children. Close start-tag, and output children.
                target << ">";
                while( child != 0)
                {
                    target << child;
                    child = child.getNextSibling();
                }

                // Done with children.  Output the end tag.
                target << "</" << nodeName << ">";
            }
            else
            {
                //
                //  There were no children.  Output the short form close of the
                //  element start tag, making it an empty-element tag.
                //
                target << "/>";
            }
            break;
        }

        case DOM_Node::ENTITY_REFERENCE_NODE:
        {
            DOM_Node child;
            for (child = toWrite.getFirstChild(); child != 0; child = child.getNextSibling())
                target << child;
            break;
        }

        case DOM_Node::CDATA_SECTION_NODE:
        {
            target << "<![CDATA[" << ((nodeValue == NULL) ? "?" : nodeValue) << "]]>";
            break;
        }

        case DOM_Node::COMMENT_NODE:
        {
            target << "<!--" << ((nodeValue == NULL) ? "?" : nodeValue) << "-->";
            break;
        }

        default:
            cerr << "Unrecognized node type = "
                 << (long)toWrite.getNodeType() << endl;
    }
	return target;
}
/*...e*/


// ---------------------------------------------------------------------------
//
//  outputContent  - Write document content from a DOMString to a C++ ostream.
//                   Escape the XML special characters (<, &, etc.) unless this
//                   is suppressed by the command line option.
//
// ---------------------------------------------------------------------------
/*...soutputContent\40\ostream\38\ target\44\ const DOMString \38\toWrite\41\:0:*/
void outputContent(ostream& target, const DOMString &toWrite)
{
    
    if (doEscapes == false)
    {
        target << toWrite;
    }
     else
    {
        int            length = toWrite.length();
        const XMLCh*   chars  = toWrite.rawBuffer();
        
        int index;
        for (index = 0; index < length; index++)
        {
            switch (chars[index])
            {
            case chAmpersand :
                target << "&amp;";
                break;
                
            case chOpenAngle :
                target << "&lt;";
                break;
                
            case chCloseAngle:
                target << "&gt;";
                break;
                
            case chDoubleQuote :
                target << "&quot;";
                break;
                
            default:
                // If it is none of the special characters, print it as such
                target << toWrite.substringData(index, 1);
                break;
            }
        }
    }

    return;
}
/*...e*/


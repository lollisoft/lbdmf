/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.29 $
 * $Name:  $
 * $Id: lbDOMConfig.cpp,v 1.29 2002/10/01 19:22:59 lothar Exp $
 *
 * $Log: lbDOMConfig.cpp,v $
 * Revision 1.29  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.28  2002/08/31 10:51:34  lothar
 * Use a member variable for char* return. Delete buffer before create new buffer
 *
 * Revision 1.27  2002/07/23 17:48:56  lothar
 * Current version runs
 *
 * Revision 1.26  2002/06/20 21:29:40  lothar
 * More debug information
 *
 * Revision 1.25  2002/06/01 10:18:53  lothar
 * pragma warning affect here
 *
 * Revision 1.24  2002/06/01 09:52:00  lothar
 * Removed some debug lines
 *
 * Revision 1.23  2002/05/30 17:53:01  lothar
 * Current development seems to run
 *
 * Revision 1.22  2002/05/01 14:17:11  lothar
 * This version does not compile
 *
 * Revision 1.21  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.20  2002/02/25 06:17:43  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.19  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.18  2001/12/08 13:03:58  lothar
 * Changes under linux also working here.
 * But the xerces library is still the version 1.3
 *
 * Revision 1.17  2001/12/08 11:51:12  lothar
 * Modified line 896 due to compilation errors
 *
 * Revision 1.16  2001/10/04 19:28:32  lothar
 * Current version seems to work good (without big memory holes)
 *
 * Revision 1.15  2001/08/18 07:38:55  lothar
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.14  2001/07/18 22:44:41  lothar
 * Using more UAP's - works, but mem leak still there ?
 *
 * Revision 1.13  2001/07/18 05:52:27  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.12  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.11  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 * Revision 1.10  2001/06/21 06:39:53  lothar
 * Much changes
 *
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

// As in http://groups.google.com/groups?q=how+to+disable+warning+C4275&hl=en&lr=&selm=uGr0NDca%23GA.248%40uppssnewspub04.moswest.msn.net&rnum=1
// documented
#pragma warning( disable: 4275 )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4101 )


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

#ifdef __cplusplus
extern "C" {
#endif

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#ifdef WINDOWS
#include <windows.h>
#endif

#include <lbConfigHook.h>

/*...sLB_DOMCONFIG_DLL scope:0:*/
#define LB_DOMCONFIG_DLL
#include <lbdomconfig-module.h>
/*...e*/

#include <lbInterfaces.h>

#include <lbDOMConfig.h>

#include <lbkey.h>
/*...e*/

int initialized = 0;
/*...scheckPtr\40\void\42\ addr\44\ int line\44\ char\42\ file\44\ char\42\ cmp\41\:0:*/
void checkPtr(void* addr, int line, char* file, char* cmp) {
	char buf[20] = "";
	
	sprintf(buf, "%p", (void*) addr);
	
	if (strcmp(buf, cmp) == 0) {
		char msg[1000] = "";
		sprintf(msg, "Object created at File: %s, Line: %d\n", file, line);
		CL_LOG(msg);
	}
}
/*...e*/
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
/*...sbla:0:*/
#ifdef bla
/*...slbKey:0:*/
/*...sc\39\tors and d\39\tors:0:*/
lbKey::lbKey() {
    ref = STARTREF;
    key = 0;
	manager = NULL;
    strcpy(keyType, "int");
}

lbKey::lbKey(int _key) {
    ref = STARTREF;
    key = _key;
    strcpy(keyType, "int");
	manager = NULL;
}

lbKey::lbKey(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = ((lbKey) k).key;
}

lbKey::~lbKey(){
}
/*...e*/

/*...simplement lb_I_Unknown:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()


lbErrCodes LB_STDCALL lbKey::setData(lb_I_Unknown* uk) {
	return ERR_NONE;
}
/*...e*/

char* LB_STDCALL lbKey::getKeyType() const {
    return "int";
}

int LB_STDCALL lbKey::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKey*) _key)->key;
}

int LB_STDCALL lbKey::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKey*) _key)->key;
}

char* LB_STDCALL lbKey::charrep() const {
    char buf[100];
#ifdef WINDOWS
    itoa(key, buf, 10);
#endif
#ifdef LINUX
    sprintf(buf, "%d", key);
#endif    
    return strdup(buf);
}
/*...e*/
/*...slbKeyUL:0:*/


lbKeyUL::lbKeyUL() {
    ref = STARTREF;
    key = 0;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(unsigned long _key) {
    ref = STARTREF;
    key = _key;
    strcpy(keyType, "UL");
}

lbKeyUL::lbKeyUL(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = ((lbKeyUL*) k)->key;
}


lbKeyUL::~lbKeyUL(){
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbKeyUL)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbKeyUL::setData(lb_I_Unknown* uk) {
	CL_LOG("lbKey::setData() not implemented yet");
	return ERR_NONE;
}


char* LB_STDCALL lbKeyUL::getKeyType() const {
    return "UL";
}

int LB_STDCALL lbKeyUL::equals(const lb_I_KeyBase* _key) const {
    return key == ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::greater(const lb_I_KeyBase* _key) const {
    return key > ((lbKeyUL*) _key)->key;
}

int LB_STDCALL lbKeyUL::lessthan(const lb_I_KeyBase* _key) const {
    return key < ((lbKeyUL*) _key)->key;
}

char* LB_STDCALL lbKeyUL::charrep() const {
    char buf[100];

#ifdef WINDOWS
    itoa(key, buf, 10);
#endif
#ifdef LINUX
    sprintf(buf, "%d", key);
#endif    
    
    return strdup(buf);
}
/*...e*/
/*...slbStringKey:0:*/
lbStringKey::lbStringKey() {
    ref = STARTREF;
    key = "";
}

lbStringKey::lbStringKey(const char* _key) {
    ref = STARTREF;
    key = strdup(_key);
}

lbStringKey::lbStringKey(const lb_I_KeyBase* k) {
    ref = STARTREF;
    key = strdup(((lbStringKey*) k)->key);
}


lbStringKey::~lbStringKey(){
	if (key != NULL) {
		delete key;
	}
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbStringKey)
	ADD_INTERFACE(lb_I_KeyBase)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbStringKey::setData(lb_I_Unknown* uk) {
	CL_LOG("lbKey::setData() not implemented yet");
	return ERR_NONE;
}

char* LB_STDCALL lbStringKey::getKeyType() const {
    return "string";
}

int LB_STDCALL lbStringKey::equals(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) == 0);
}

int LB_STDCALL lbStringKey::greater(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) > 0);
}

int LB_STDCALL lbStringKey::lessthan(const lb_I_KeyBase* _key) const {
    return (strcmp(key, ((const lbStringKey*) _key)->key) < 0);
}

char* LB_STDCALL lbStringKey::charrep() const {
    return key;
}
/*...e*/
#endif
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
{
private:
	lbDOMNode(lbDOMNode & n) { printf("lbDOMNode(lbDOMNode & n) called\n"); }
public:
	lbDOMNode(char* file, int line);
	lbDOMNode();
	virtual ~lbDOMNode();
	
	DECLARE_LB_UNKNOWN()

/*...slb_I_ConfigObject:0:*/
/* lb_I_ConfigObject */

	virtual lbErrCodes LB_STDCALL getParam(const char* name, lb_I_String*& value);


	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object);
	virtual lbErrCodes LB_STDCALL getParent(lb_I_ConfigObject** _parent);
	
	virtual lbErrCodes LB_STDCALL getFirstChildren(lb_I_ConfigObject** children);
	virtual lbErrCodes LB_STDCALL getNextChildren(lb_I_ConfigObject** children);
	
	virtual int LB_STDCALL getChildrenCount();

	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr);
	virtual lbErrCodes LB_STDCALL getAttributeValue(const char* name, char*& attr);
	virtual lbErrCodes LB_STDCALL deleteValue(char*& attr);
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
	char* getNameValue;
	int debug;
	UAP(lb_I_ConfigObject, parent, __FILE__, __LINE__)
	
	UAP(lb_I_Container, lbDOMchilds, __FILE__, __LINE__)
	
//	int currentChildIndex;
	
	friend class lbDOMConfig;
};
/*...e*/

/*...sContainer for DOM elements:0:*/
/*...sclass lbDOMContainer:0:*/
class lbDOMContainer : 	public lb_I_Container
{

public:
    lbDOMContainer(char* file, int line);
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
    lbElement() { 
    	ref = STARTREF; 
    	next = NULL; 
    	data = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    lbElement(char* file, int line) { 
    	ref = STARTREF; 
    	next = NULL; 
    	data = NULL; 
    	key = NULL; 
    	manager = NULL;
    }
    virtual ~lbElement();
	
//    lbElement(const lb_I_Object &o, const lb_I_KeyBase &_key, lb_I_Element *_next=NULL);
    lbElement(const lb_I_Element &e) { 
    	ref = STARTREF; 
    	next = e.getNext(); 
    	manager = NULL;
    }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

};
/*...e*/

/*...scontainer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMContainer)
	ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbDOMContainer::lbDOMContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
    manager = NULL;
}

lbDOMContainer::lbDOMContainer(char* file, int line) {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
    manager = NULL;
}

lbDOMContainer::~lbDOMContainer() {
	deleteAll();
}

lbErrCodes LB_STDCALL lbDOMContainer::setData(lb_I_Unknown* data) {
	CL_LOG("lbDOMContainer::setData(lb_I_Unknown* data) called");
	getch();

	return ERR_NONE;
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbDOMContainer)
/*...e*/

/*...selement:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)
lbErrCodes LB_STDCALL lbElement::setData(lb_I_Unknown* data) {
#ifdef VERBOSE
	CL_LOG("lbElement::setData(lb_I_Unknown* data) called");
#endif	
	return ERR_NONE;
}

/*...e*/
/*...e*/

/*...sclass lbDOMAttribute \58\ public lb_I_Attribute:0:*/
class lbDOMAttribute : public lb_I_Attribute
{

	DECLARE_LB_UNKNOWN()

	lbDOMAttribute(char* file, int line) {}
	lbDOMAttribute() {}

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




/*...sclass lbDOMNode implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMNode)
	ADD_INTERFACE(lb_I_ConfigObject)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes lbDOMNode\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes lbDOMNode::setData(lb_I_Unknown* uk) {
	
	lbDOMNode* _node = NULL;
	lbErrCodes err = ERR_NONE;

	if (uk->queryInterface("lb_I_ConfigObject", (void**) &_node, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Cloning interface not present!");
		getch();
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	if (strcmp(_node->getName(), "InterfaceName") == 0) {
	
		char buf[1000] = "";
		sprintf(buf, "Cloned lbDOMNode at %p gets data from %p.\nCloned: %s\nOrginal: %s", 
			(void*) this, (void*) uk, getCreationLoc(), uk->getCreationLoc());
		CL_LOG(buf)
	
	}
#endif	
/*...e*/
	node = _node->node;
	if (_node->lbDOMchilds != NULL) {
		QI(_node->lbDOMchilds, lb_I_Container, lbDOMchilds, __FILE__, __LINE__)
//		_node->lbDOMchilds->queryInterface("lb_I_Container", (void**) & lbDOMchilds, __FILE__, __LINE__);
	}

/**
 * The parent node is not copied, so it may be a non deep copy from uk.
 */
	if (_node->parent == NULL) {
#ifdef VERBOSE
		CL_LOG("Warning: Cloning a object without parent pointing to a real parent!");
#endif
	}
	else
	if (_node->parent->queryInterface("lb_I_Unknown", (void**) &parent, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Cloning lbDOMNode failed due to increment refcount of source's parent!");
		getch();
	}
	
//	_node->release(__FILE__, __LINE__);
	
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\lbDOMNode\40\char\42\ file\44\ int line\41\:0:*/
lbDOMNode::lbDOMNode(char* file, int line) {

	char ptr[2] = "";
	sprintf(ptr, "%p", this);
	char msg[1000] = "";
	sprintf(msg, "lbDOMNode::lbDOMNode(...) called at %d in %s", line, file);
	track_Object(this, msg);
	getNameValue = NULL;


	resetRefcount();
//	currentChildIndex = 0;
	lbDOMchilds = NULL;
	debug = 0;

	parent = NULL;
	
	manager = NULL;
	

	parent.setFile(__FILE__);
	parent.setLine(__LINE__);

	lbDOMchilds.setFile(__FILE__);
	lbDOMchilds.setLine(__LINE__);


	// This was the bug for the wrong deletion while leave scope
	//parent++;
#ifdef VERBOSE
	CL_LOG("Warning: Parent is set to my self in c'tor");
#endif
}
/*...e*/
/*...slbDOMNode\58\\58\lbDOMNode\40\\41\:0:*/
lbDOMNode::lbDOMNode() {

	char ptr[2] = "";
	sprintf(ptr, "%p", this);

	resetRefcount();
//	currentChildIndex = 0;
	lbDOMchilds = NULL;
	debug = 0;
	getNameValue = NULL;

	parent = NULL;
	
	manager = NULL;
	

	parent.setFile(__FILE__);
	parent.setLine(__LINE__);

	lbDOMchilds.setFile(__FILE__);
	lbDOMchilds.setLine(__LINE__);


	// This was the bug for the wrong deletion while leave scope
	//parent++;
#ifdef VERBOSE
	CL_LOG("Warning: Parent is set to my self in c'tor");
#endif
}
/*...e*/
/*...slbDOMNode\58\\58\\126\lbDOMNode\40\\41\:0:*/
lbDOMNode::~lbDOMNode() {
	char ptr[20] = "";
	sprintf(ptr, "%p", (void*) this);

	if (getNameValue != NULL) {
		deleteValue(getNameValue);
		getNameValue = NULL;
	}

	if (ref != STARTREF) 
		CL_LOG("Error: Reference count mismatch");


	// Bugfix (in createAbstractedChildList)
	lbDOMchilds--;
/*
// No more because UAP	
	if (lbDOMchilds != NULL) {
		lbDOMchilds->deleteAll();
		RELEASE(lbDOMchilds);
		lbDOMchilds = NULL;
	}
*/
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDOMNode\58\\58\setChildrens\40\lbNodeList\42\ _childs\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::setChildrens(lbNodeList* _childs) {
	CL_LOG("Error: Not implemented yet");
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getParent\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getParent(lb_I_ConfigObject** _parent) {
	if (parent == NULL) {
		CL_LOG("Error: lbDOMNode is not correctly set up. Parent is NULL!");
	}

	parent->queryInterface("lb_I_ConfigObject", (void**) _parent, __FILE__, __LINE__);

	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lbDOMNode::setParent(lb_I_ConfigObject* _parent) {
	CL_LOG("lbDOMNode::setParent(...) not implemented yet");
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
	lb_I_Container* c = createAbstractedChildList(_node);

	if (c != NULL)
		c->queryInterface("lb_I_Container", (void**) &lbDOMchilds, __FILE__, __LINE__);
	else
		CL_LOG("Error: Creation of abstracted childs returns NULL");

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
			CL_LOG("Previous parent node will be overwritten!");
		}
		lbDOMNode* _parent = new lbDOMNode(__FILE__, __LINE__);
		
		_parent->setFurtherLock(0);
		if (manager == NULL) CL_LOG("Error: Set manager in parent with a NULL pointer!");
		_parent->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		_parent->setNode(pnode);
		parent = _parent;
		parent++;
	} else {
		if (parent != NULL) {
		#ifdef VERBOSE
			CL_LOG("Previous parent node must be deleted!");
		#endif	
		}
	}

	char ptr[20] = "";
	sprintf(ptr, "%p", (void*) this);

	if (strcmp(ptr, "00C81D60") == 0) {
		char buf[1000] = "";
		sprintf(buf, "This is the node with %s and tagname %s", ptr, getName());
		CL_LOG(buf)
	}

	return ERR_NONE;
}
/*...e*/
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
/*...slbDOMNode\58\\58\getFirstChildren\40\lb_I_ConfigObject\42\\42\ children\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getFirstChildren(lb_I_ConfigObject** children) {
	if (lbDOMchilds == NULL) {
		CL_LOG("Error, no childrens in config object");
		return ERR_CONFIG_NO_CHILDS;
	}
	
//	currentChildIndex = 0;
	
	UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)

	unknown.setFile(__FILE__);
	unknown.setLine(__LINE__);

	if (lbDOMchilds->hasMoreElements() == 1) {
		unknown = lbDOMchilds->nextElement();
//		currentChildIndex++;
	} else {
		CL_LOG("ERROR: No child found");
		return ERR_CONFIG_EMPTY_CONTAINER;
	}
	
	if (unknown == NULL) {
		CL_LOG("Fatal: Must have a children here!");
	}

	unknown->queryInterface("lb_I_ConfigObject", (void**) children, __FILE__, __LINE__);
	
	/**
	 * Return a reference! So increment my own because of UAP
	 */
	//unknown++;

	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getNextChildren\40\lb_I_ConfigObject\42\\42\ children\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getNextChildren(lb_I_ConfigObject** children) {
	lbErrCodes err = ERR_NONE;
	
/*...sreturn state no childs:8:*/
	if (lbDOMchilds == NULL) {
		CL_LOG("Error: Returning ERR_CONFIG_NO_CHILDS");
		getch();
		return ERR_CONFIG_NO_CHILDS;
	}
/*...e*/
	
	char buf[100] = "";

/*...sreturn state no more childs:8:*/
	if (!lbDOMchilds->hasMoreElements()) {
		return ERR_CONFIG_NO_MORE_CHILDS;
	}
/*...e*/
	
	//currentChildIndex++;

	UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)
	unknown.setFile(__FILE__);
	unknown.setLine(__LINE__);

	unknown = lbDOMchilds->nextElement();

/*...serror unknown \61\ NULL:8:*/
	if (unknown == NULL) {
		CL_LOG("Fatal: Must have a children here!");
		getch();
	}
/*...e*/

	unknown->queryInterface("lb_I_ConfigObject", (void**) children, __FILE__, __LINE__);

	/**
	 * Return a reference! So increment my own because of UAP
	 * Note: queryInterface does that !
	 */
	//unknown++;

	if (children == NULL) {
		CL_LOG("Error: queryInterface creates a NULL pointer!");
		getch();
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\createAbstractedChildList\40\DOM_Node node\41\:0:*/
lbDOMContainer* LB_STDCALL lbDOMNode::createAbstractedChildList(DOM_Node _node) {


	DOM_NodeList DOMlist = _node.getChildNodes();
	int len = DOMlist.getLength();	
	lbDOMContainer* list = new lbDOMContainer;
	lbErrCodes err = ERR_NONE;

	if (manager == NULL) CL_LOG("Error: Setting in lbDOMNode::createAbstractedChildList() a NULL pointer as manager");
	
	list->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	// Create an instance and create one reference. Then give it out.	
	// This is the bug - see in lbDOMNode destructor
	lb_I_Unknown* temp;
	list->queryInterface("lb_I_Unknown", (void**) &temp, __FILE__, __LINE__);
	
	char buf[100] = "";
/*...sloop:8:*/
	for (int i = 0; i < len; i++) {
		DOM_Node child = DOMlist.item(i);	

		lbDOMNode* lbNode = new lbDOMNode(__FILE__, __LINE__);
		
		lbNode->setFurtherLock(0);
		lbNode->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		lbNode->node = child;
		
		UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)

		QI(lbNode, lb_I_Unknown, unknown, __FILE__, __LINE__)
		
		/*
		if (lbNode->queryInterface("lb_I_Unknown", (void**) &unknown, __FILE__, __LINE__) != ERR_NONE) {
		        CL_LOG("lbNode->queryInterface() Failed!");
		}
		*/
		
		if (unknown == NULL) CL_LOG("Error: The unknown pointer must not be NULL!");
		
		if (unknown != lbNode) {
			CL_LOG("Error: Pointer of unknown instance differs from created instance");
			getch();
		}
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		key = new lbKey(i);

		char addr[20] = "";
		sprintf(addr, "%p", (void*) key.getPtr());
		char buf[1000] = "";
		sprintf(buf, "Created an instance for lbKey at %s", addr);
		if (strcmp(addr, "011f4440") == 0) CL_LOG(buf)
		
		sprintf(addr, "%p", (void*) &key);
		sprintf(buf, "Created an instance for lbKey at %p", (void*) &key);
		if (strcmp(addr, "011f4440") == 0) CL_LOG(buf)
		
		key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		key++;
		if (unknown == NULL) CL_LOG("Error: Inserting a null pointer!");
		list->insert(&unknown, &key);
		key--;
	}
/*...e*/

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
	
	DOM_Node an_attr = attributeMap.getNamedItem(DOMString(name));	
	
	if (an_attr == NULL) {
		CL_LOG("Error: Attribute not found");
		
		return ERR_UNSPECIFIED;
	}
	
	DOMString value = an_attr.getNodeValue();
	char* result = value.transcode();

#ifdef bla
	if (debug == 0) {
		debug = 1;
		DOMString string = getName();
		char* temp = string.transcode();
/*...sVERBOSE:16:*/
#ifdef VERBOSE		
		if (strcmp(temp, "InterfaceName") == 0) {
			char* v = NULL;
			getAttributeValue("Name", v);
			printf("Interface name is %s\n", v);
		}
#endif		
/*...e*/
		debug = 0;
	}
#endif	
	attr = strdup(result);
#ifdef WINDOWS
//	value.deletetranscoded(result);
#endif		
//	free((void*) result);
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\deleteValue\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::deleteValue(char*& attr) {
	DOMString value = DOMString();
#ifdef WINDOWS
//	value.deletetranscoded(attr);
	delete [] attr;
	attr = NULL;
#endif
#ifdef LINUX
	delete attr;
	attr = NULL;
#endif	
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
/*...sVERBOSE:0:*/
	#ifdef VERBOSE
		CL_LOG("node is NULL!");
	#endif
/*...e*/
		return "Internal node not defined!";
	}

	DOMString string = node.getNodeName();

#ifdef VERBOSE
	CL_LOG("Got the DOMString");
	getch();
#endif

	if (getNameValue != NULL) deleteValue(getNameValue);
	getNameValue = string.transcode();

#ifdef VERBOSE
	CL_LOG("Got the node name");
	getch();
#endif	
	return getNameValue;
}
/*...e*/
/*...e*/
/*...sclass lbDOMConfig \58\ public lb_I_XMLConfig:0:*/
/*...sclass lbDOMConfig:0:*/
class lbDOMConfig : 
		public lb_I_XMLConfig
{
protected:
	lbDOMConfig(const lbDOMConfig & t) {
		CL_LOG("lbDOMConfig::lbDOMConfig(const lbDOMConfig & t) called !!!");
		ref = STARTREF;
		errReporter = NULL;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbDOMConfig(const lbDOMConfig* & t) called" << endl;
	
#endif	
/*...e*/
	}
public:
	lbDOMConfig(char* file, int line);
	lbDOMConfig();
	virtual ~lbDOMConfig();
	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL parse();
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName, int & count);
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject** cfgObj, const char* const cfgObjectName);

protected:
	/**
	 * These members must return a previously queried interface. So the caller becomes it's
	 * own reference to the object. He must be responsible for release the returned reference.
	 *
	 * A Bug (no reference returned) in findNodesAtTreePos caused, that the lbDOMNode contained
	 * the same instance as this class (with one reference count less than it must be.
	 */
	lb_I_Container* LB_STDCALL findNodesAtTreePos(const char* treePos);
	lb_I_Container* LB_STDCALL createAbstractedChildList(const DOM_Node node);

	int interface_used;
	ErrorHandler *errReporter;
	
	int errorsOccured;
	DOM_Document doc;


	UAP(lb_I_Container, lastResult, __FILE__, __LINE__)
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDOMConfig)
	ADD_INTERFACE(lb_I_XMLConfig)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDOMConfig::setData(lb_I_Unknown* uk) {
	CL_LOG("lbDOMConfig::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

/*...slbDOMConfig\58\\58\lbDOMConfig\40\char\42\ file\44\ int line\41\:0:*/
lbDOMConfig::lbDOMConfig(char* file, int line) {
	manager = NULL;
	ref = STARTREF;
	lastResult = NULL;
	interface_used = 0;
	errReporter = new DOMTreeErrorReporter();
	
	if (initialized == 0) {
/*...sInitialize the DOM4C2 system:16:*/
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
/*...slbDOMConfig\58\\58\lbDOMConfig\40\\41\:0:*/
lbDOMConfig::lbDOMConfig() {
	manager = NULL;
	ref = STARTREF;
	lastResult = NULL;
	interface_used = 0;
	errReporter = new DOMTreeErrorReporter();
	
	if (initialized == 0) {
/*...sInitialize the DOM4C2 system:16:*/
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
	if (lastResult != NULL) {
		lastResult->deleteAll();
		RELEASE(lastResult);
	}
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::parse() {
	lbErrCodes err = ERR_NONE;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "Parse file '" << filename << "'..." << endl;
#endif
/*...e*/

	if (filename != NULL) {

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

	} else return ERR_NO_ENVIRONMENT;
	return err;
}
/*...e*/
/*...slbDOMContainer\42\ lbDOMConfig\58\\58\findNodesAtTreePos\40\const char\42\ treePos\41\:0:*/
lb_I_Container* LB_STDCALL lbDOMConfig::findNodesAtTreePos(const char* treePos) {
	char* part = NULL;
	char* name = NULL;
	char* savename = NULL;
	DOMString path;
	int count = 1;
	
	/**
	 * Use a lb_I_Container (implemented here)
	 */
	lbDOMContainer* DOM_list = new lbDOMContainer;
	lb_I_Container* list = NULL;

	DOM_list->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	if (DOM_list->queryInterface("lb_I_Container", (void**) &list, __FILE__, __LINE__) != NULL) {
		CL_LOG("Error: Could not generate a reference with interface lb_I_Container");
		if (list != NULL) CL_LOG("Obviously failed queryInterface, instance pointer is not NULL!!!!");
		return NULL;
	}
/*...sPrepare search:8:*/

	if (treePos == NULL) {
		cout << "Null pointer detected!" << endl;
		
		exit(1);
	}	

	savename = strdup(treePos);
	name = strrchr(savename, '/');
	if (name == NULL) name = savename;
	
	DOM_NodeList DOMlist = doc.getElementsByTagName(((name[0] == '/') ? &name[1] : name));
	int len = DOMlist.getLength();

	// Cleanup
	
	delete [] savename;

/*...e*/

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
			 
			 
			lbDOMNode* lbNode = new lbDOMNode(__FILE__, __LINE__);
			
			lbNode->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
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
			UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

			if (lbNode->queryInterface("lb_I_Unknown", (void**) &unknown, __FILE__, __LINE__) != ERR_NONE) {
				CL_LOG("lbNode->queryInterface() Failed!");
			} else {
				unknown.setLine(__LINE__);
				unknown.setFile(__FILE__);
			}
			
			key = new lbKey(count++);
			
			key.setLine(__LINE__);
			key.setFile(__FILE__);
			
			key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
			key++;
			
			list->insert(&unknown, &key);
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
		char buf[100] = "";
		lastResult = findNodesAtTreePos(cfgObjectName);
		count = lastResult->Count(); //= lastResult->getChildrenCount();
		return err;
	} else cout << "Any errors while parsing has been occured!" << endl;
	
	return err;
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\getConfigObject\40\lb_I_ConfigObject\42\\42\ \44\ const char\42\ const\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::getConfigObject(lb_I_ConfigObject** cfgObj, 
                                        const char* const cfgObjectName) {
	lbErrCodes err = ERR_NONE;
	// Try to locate the identifer in the tree

	/**
	 * Create the view for this result.
	 */
	 
	lbDOMNode *node = new lbDOMNode(__FILE__, __LINE__);
	
	lb_I_Container* c = NULL;
	
	if (manager.getPtr() == NULL) CL_LOG("Error: Manager in lbDOMConfig is a NULL pointer!")

	node->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	if (lastResult == NULL) {
		CL_LOG("Error: Function sequence may be wrong. Please call hasConfigObject first!");
		return ERR_FUNCTION_SEQUENCE;
	}
	
	lastResult->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	if ((lastResult != NULL) && (lastResult->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__)) != ERR_NONE) {
		CL_LOG("Error: Could not get interface lb_I_Container");
		getch();
	}
	
	if (c == NULL) CL_LOG("Error: Failed to get container instance of lastResult");
	
	node->lbDOMchilds = c;
	node->node = NULL; // See null pointer operator (this results in the error in the destructor)
	
	// This interface is needed:
	node->queryInterface("lb_I_ConfigObject", (void**) cfgObj, __FILE__, __LINE__);

	track_Object(*cfgObj, "Problematic instance created");

	return err;
}
/*...e*/
/*...e*/

IMPLEMENT_FUNCTOR(getlbDOMConfigInstance, lbDOMConfig)

/*...sunused yet:0:*/
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
#ifdef bla        
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
#endif
    }

    return;
}
/*...e*/
/*...e*/

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

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.52 $
 * $Name:  $
 * $Id: lbDOMConfig.cpp,v 1.52 2005/05/04 22:09:39 lollisoft Exp $
 *
 * $Log: lbDOMConfig.cpp,v $
 * Revision 1.52  2005/05/04 22:09:39  lollisoft
 * Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
 *
 * Revision 1.51  2005/03/31 09:01:30  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.50  2005/02/13 12:57:15  lollisoft
 * Removed unnessesary messages
 *
 * Revision 1.49  2005/01/23 13:43:04  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.48  2004/05/08 10:53:11  lollisoft
 * minor change
 *
 * Revision 1.47  2004/03/22 22:11:08  lollisoft
 * Current version works under linux
 *
 * Revision 1.46  2003/12/13 21:15:10  lollisoft
 * Compiles again under Linux using iODBC aka libiodbc.so
 *
 * Revision 1.45  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.44  2003/08/22 17:31:54  lollisoft
 * removed unused code and debuging
 *
 * Revision 1.43  2003/08/16 18:13:37  lollisoft
 * Added my new address due to move
 *
 * Revision 1.42  2003/08/08 16:35:17  lollisoft
 * New implementation of interface repository works, but I have problems with multiple module loading in lbhook
 *
 * Revision 1.41  2003/07/31 20:12:30  lollisoft
 * Added new interface repository -  not complete yet
 *
 * Revision 1.40  2003/07/17 18:51:41  lollisoft
 * Begin develop a hopefully faster and less memory consuming
 * XML wrapper.
 *
 * Revision 1.39  2003/07/15 22:23:00  lollisoft
 * Removed debug messages
 *
 * Revision 1.38  2003/06/16 21:50:37  lollisoft
 * Removed debug message
 *
 * Revision 1.37  2003/04/28 20:32:49  lollisoft
 * Moved back to watcom
 *
 * Revision 1.36  2003/03/14 16:00:50  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.35  2003/01/27 21:18:54  lothar
 * More logging
 *
 * Revision 1.34  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.33  2002/12/09 19:37:56  lothar
 * removed debugging messages
 *
 * Revision 1.32  2002/12/07 06:55:00  lothar
 * Current Linux attempt is buggy
 *
 * Revision 1.31  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.30  2002/10/28 18:36:55  lothar
 * Using _CL_VERBOSE ... LOG_
 *
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
//#pragma warning( disable: 4275 )
//#pragma warning( disable: 4251 )
//#pragma warning( disable: 4101 )


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
void LB_STDCALL checkPtr(void* addr, int line, char* file, char* cmp) {
	char buf[20] = "";
	
	sprintf(buf, "%p", (void*) addr);
	
	if (strcmp(buf, cmp) == 0) {
		_CL_VERBOSE << "Object created at File: " << file << ", Line: " << line LOG_
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
	_CL_VERBOSE << "lbKey::setData() not implemented yet" LOG_
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
	_CL_VERBOSE << "lbKey::setData() not implemented yet" LOG_
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

    virtual ~DOMTreeErrorReporter()
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
         << "   Message: " << DOMString(toCatch.getMessage()) << ENDL;
}
/*...e*/
/*...sDOMTreeErrorReporter\58\\58\fatalError\40\\46\\46\\46\\41\:0:*/
void DOMTreeErrorReporter::fatalError(const SAXParseException& toCatch)
{
    cerr << "Fatal Error at file \"" << DOMString(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "   Message: " << DOMString(toCatch.getMessage()) << ENDL;
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
	lbDOMNode(lbDOMNode & n) { c = NULL; }
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
	//lb_I_Container* lbDOMchilds;
#ifdef bla
/*...sbla:0:*/
		class UAPUnknown_Reference {
		private:
		UAPUnknown_Reference(UAPUnknown_Reference& from) {
			_CL_VERBOSE << "Copy constructor called!" LOG_
		}
		public:
	        UAPUnknown_Reference() {
	        	_autoPtr = NULL;
	        	_line = -1;
	        	_file = NULL;
	        	allowDelete = 1;
		}
		virtual ~UAPUnknown_Reference() {
			if (_autoPtr != NULL) {
				if (allowDelete != 1) {
					if (_autoPtr->deleteState() == 1) {
						_CL_VERBOSE << "Error: Instance would be deleted, but it's not allowed !!" LOG_
					}
				}
				if (_line == -1) {
				}
				RELEASE_1(_autoPtr, _file, _line);
			}
			if (_file != NULL) {
				char ptr[20] = "";
				sprintf(ptr, "%p", (void*) _file);
				if (strcmp(ptr, "0x81fd020") != 0) free(_file);
			}
		}
		void setFile(char* __file) {
			if (_file != NULL) delete [] _file;
			if (__file != NULL) {
				//_file = new char [strlen(__file) + 1];
				//_file = strcpy(_file, __file);
				_file = strdup(__file);
			}
		}
		void setLine(int __line) {
			_line = __line;
		}
		
		lb_I_Container* getPtr() const { return _autoPtr; }
		void setPtr(lb_I_Container*& source) {
			if (_autoPtr != NULL) {
				_CL_VERBOSE << "Error: UAP object still initialized!" LOG_
			}
			_autoPtr = source;
		}
		
		lb_I_Container& operator * () {
		return *_autoPtr; }
		lb_I_Container* operator -> () const {
			if (_autoPtr == NULL) {
			}
			return _autoPtr;
		}
		lb_I_Container* operator -> () {
			if (_autoPtr == NULL) {
			}
			return _autoPtr;
		}
		UAPUnknown_Reference& operator++(int) {
			lb_I_Container* temp = NULL;
			_autoPtr->queryInterface("lb_I_Container", (void**) &temp, __FILE__, __LINE__);
			return *this;
		}
		UAPUnknown_Reference& operator--(int) {
			lb_I_Container* temp = NULL;
			if (_autoPtr->release(__FILE__, __LINE__) == ERR_RELEASED) _autoPtr = NULL;
			return *this;
		}
		
		lb_I_Container ** operator & () {
			return &_autoPtr;
		}
		
		UAPUnknown_Reference& operator = (lb_I_Container* autoPtr) {
			_autoPtr = autoPtr;
			return *this;
		}
		int operator == (const lb_I_Container* b) const {
			return _autoPtr == b;
		}
		int operator != (const lb_I_Container* b) const {
			return _autoPtr != b;
		}
		void setDelete(int _allow) { allowDelete = _allow; }
		
		protected:
	        lb_I_Container* _autoPtr;
	        int _line;
	        char* _file;
	        int allowDelete;
		};
/*...e*/
        lb_I_Container* _UAPUnknown_Reference;
        UAPUnknown_Reference lbDOMchilds;
#endif
	
		
//	int currentChildIndex;
	lb_I_Container* c;	
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
	_CL_VERBOSE << "lbDOMContainer::setData(lb_I_Unknown* data) called" LOG_
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
	_CL_VERBOSE << "lbElement::setData(lb_I_Unknown* data) called" LOG_
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
	_CL_VERBOSE << "lbDOMAttribute::setData(...) not implemented yet" LOG_
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
		_CL_VERBOSE << "Error: Cloning interface not present!" LOG_
		getch();
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	if (strcmp(_node->getName(), "InterfaceName") == 0) {
		_CL_VERBOSE << "Cloned lbDOMNode at " << ltoa(this) << " gets data from " <<
		ltoa(uk) << ". Cloned: " << getCreationLoc() << " Orginal: " << uk->getCreationLoc() LOG_
	
	}
#endif	
/*...e*/
	node = _node->node;
	if (_node->lbDOMchilds != NULL) {
		//QI(_node->lbDOMchilds, lb_I_Container, lbDOMchilds, __FILE__, __LINE__)
		_node->lbDOMchilds->queryInterface("lb_I_Container", (void**) &lbDOMchilds, __FILE__, __LINE__);
	}

/**
 * The parent node is not copied, so it may be a non deep copy from uk.
 */
	if (_node->parent == NULL) {
#ifdef VERBOSE
		_CL_VERBOSE << "Warning: Cloning a object without parent pointing to a real parent!" LOG_
#endif
	}
	else
	if (_node->parent->queryInterface("lb_I_Unknown", (void**) &parent, __FILE__, __LINE__) != ERR_NONE) {
		_CL_VERBOSE << "Error: Cloning lbDOMNode failed due to increment refcount of source's parent!" LOG_
		getch();
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\lbDOMNode\40\char\42\ file\44\ int line\41\:0:*/
lbDOMNode::lbDOMNode(char* file, int line) {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);
	char msg[1000] = "";
	sprintf(msg, "lbDOMNode::lbDOMNode(...) called at %d in %s", line, file);
	track_Object(this, msg);
	getNameValue = NULL;


	c = NULL;

	resetRefcount();
//	currentChildIndex = 0;
	lbDOMchilds = NULL;
	debug = 0;

	parent = NULL;
	
	manager = NULL;

	parent.setFile(__FILE__);
	parent.setLine(__LINE__);
//	lbDOMchilds.setFile(__FILE__);
//	lbDOMchilds.setLine(__LINE__);

	// This was the bug for the wrong deletion while leave scope
	//parent++;
#ifdef VERBOSE
	_CL_VERBOSE << "Warning: Parent is set to my self in c'tor" LOG_
#endif
}
/*...e*/
/*...slbDOMNode\58\\58\lbDOMNode\40\\41\:0:*/
lbDOMNode::lbDOMNode() {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);
	resetRefcount();
//	currentChildIndex = 0;
	lbDOMchilds = NULL;
	debug = 0;
	getNameValue = NULL;

	parent = NULL;

	c = NULL;
	
	manager = NULL;

	parent.setFile(__FILE__);
	parent.setLine(__LINE__);

//	lbDOMchilds.setFile(__FILE__);
//	lbDOMchilds.setLine(__LINE__);


	// This was the bug for the wrong deletion while leave scope
	//parent++;
#ifdef VERBOSE
	_CL_VERBOSE << "Warning: Parent is set to my self in c'tor" LOG_
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
		_CL_VERBOSE << "Error: Reference count mismatch" LOG_


	// Bugfix (in createAbstractedChildList)
//	lbDOMchilds--;
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
	_CL_VERBOSE << "Error: Not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getParent\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getParent(lb_I_ConfigObject** _parent) {
	if (parent == NULL) {
		_CL_VERBOSE << "Error: lbDOMNode is not correctly set up. Parent is NULL!" LOG_
	}

	parent->queryInterface("lb_I_ConfigObject", (void**) _parent, __FILE__, __LINE__);

	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lbDOMNode::setParent(lb_I_ConfigObject* _parent) {
	_CL_VERBOSE << "lbDOMNode::setParent(...) not implemented yet" LOG_
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
		_CL_VERBOSE << "Error: Null node could not be set!" LOG_
		getch();
	}
	if (c != NULL) {
		c->deleteAll();
		RELEASE(c)
		c = NULL;
	}
	c = createAbstractedChildList(_node);

	if (c != NULL)
		c->queryInterface("lb_I_Container", (void**) &lbDOMchilds, __FILE__, __LINE__);
	else
		_CL_VERBOSE << "Error: Creation of abstracted childs returns NULL" LOG_

	if (lbDOMchilds == NULL) {
		_CL_VERBOSE << "Error: Here must be a result!" LOG_
		
	}
	
	node = _node;
	if (node.isNull()) {
		_CL_VERBOSE << "Error: Null node could not be set!" LOG_
		getch();
	}
	
	DOM_Node pnode = _node.getParentNode();

	if (pnode != NULL) {
		
		if (parent != NULL) {
			_CL_VERBOSE << "Previous parent node will be overwritten!" LOG_
		}
		lbDOMNode* _parent = new lbDOMNode(__FILE__, __LINE__);
		
		_parent->setFurtherLock(0);
		if (manager == NULL) _LOG << "Error: Set manager in parent with a NULL pointer!" LOG_
		_parent->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		
		_parent->setNode(pnode);
		parent = _parent;
		parent++;
	} else {
		if (parent != NULL) {
		#ifdef VERBOSE
			_CL_VERBOSE << "Previous parent node must be deleted!" LOG_
		#endif	
		}
	}

	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getParam\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getParam(const char* name, lb_I_String*& value) {
	_CL_VERBOSE << "Not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getChildrenCount\40\\41\:0:*/
int LB_STDCALL lbDOMNode::getChildrenCount() {
	_CL_VERBOSE << "Not implemented yet" LOG_
	return 0;
}
/*...e*/
/*...slbDOMNode\58\\58\findObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::findObject(const char* name, lb_I_ConfigObject*& object) {
	_CL_VERBOSE << "Not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getFirstChildren\40\lb_I_ConfigObject\42\\42\ children\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getFirstChildren(lb_I_ConfigObject** children) {
	if (lbDOMchilds == NULL) {
		_CL_VERBOSE << "Error, no childrens in config object" LOG_
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
		_CL_VERBOSE << "ERROR: No child found" LOG_
		return ERR_CONFIG_EMPTY_CONTAINER;
	}
	
	if (unknown == NULL) {
		_CL_VERBOSE << "Fatal: Must have a children here!" LOG_
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
		_CL_VERBOSE << "Error: Returning ERR_CONFIG_NO_CHILDS" LOG_
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
		_CL_VERBOSE << "Fatal: Must have a children here!" LOG_
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
		_CL_VERBOSE << "Error: queryInterface creates a NULL pointer!" LOG_
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

	if (manager == NULL) _LOG << "Error: Setting in lbDOMNode::createAbstractedChildList() a NULL pointer as manager" LOG_
	
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
		
		if (unknown == NULL) _LOG << "Error: The unknown pointer must not be NULL!" LOG_
		
		if (unknown != lbNode) {
			_CL_VERBOSE << "Error: Pointer of unknown instance differs from created instance" LOG_
			getch();
		}
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		key = new lbKey(i);

		key->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		key++;
		if (unknown == NULL) _LOG << "Error: Inserting a null pointer!" LOG_
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
	_CL_VERBOSE << "lbDOMNode::getAttribute(...): Not implemented yet" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbDOMNode\58\\58\getAttributeValue\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMNode::getAttributeValue(const char* name, char*& attr) {

	DOM_NamedNodeMap attributeMap = node.getAttributes();
	
	if (attributeMap == NULL) {
		_CL_VERBOSE << "Error: This node is not of type ELEMENT" LOG_
		
		return ERR_UNSPECIFIED;
	}
	
	DOM_Node an_attr = attributeMap.getNamedItem(DOMString(name));	
	
	if (an_attr == NULL) {
		_CL_VERBOSE << "Error: Attribute not found" LOG_
		
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
	_CL_VERBOSE << "lbDOMNode::getName() called" LOG_
	getch();
#endif
	if (node.isNull()) {
/*...sVERBOSE:0:*/
	#ifdef VERBOSE
		_CL_VERBOSE << "node is NULL!" LOG_
	#endif
/*...e*/
		return "Internal node not defined!";
	}

	DOMString string = node.getNodeName();

#ifdef VERBOSE
	_CL_VERBOSE << "Got the DOMString" LOG_
	getch();
#endif

	if (getNameValue != NULL) deleteValue(getNameValue);
	getNameValue = string.transcode();

#ifdef VERBOSE
	_CL_VERBOSE << "Got the node name" LOG_
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
		_CL_VERBOSE << "lbDOMConfig::lbDOMConfig(const lbDOMConfig & t) called !!!" LOG_
		ref = STARTREF;
		errReporter = NULL;
		lastResult = NULL;
		haveFunctorList = 0;
		if (lastResult.getPtr() != NULL) printf("ERROR: Setting lastResult to NULL failed!\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	COUT << "lbDOMConfig(const lbDOMConfig* & t) called" << ENDL;
	
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
	int haveFunctorList;


	UAP(lb_I_Container, lastResult, __FILE__, __LINE__)
//	lb_I_Container* lastResult;
};
/*...e*/

BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbDOMConfig)
#ifdef bla
/*...slocal implemented:0:*/
char* LB_STDCALL lbDOMConfig::getClassName() {
	return "lbDOMConfig";
}
char* LB_STDCALL lbDOMConfig::_queryInterface(char* name, void** unknown, char* file, int line) {
	char* ID = new char[strlen(name)+strlen("lbDOMConfig")+strlen(file)+1];
	ID[0] = 0;
	strcat(ID, name);
	strcat(ID, "lbDOMConfig");
	strcat(ID, file);
	lbErrCodes err = ERR_NONE;
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) {
		_CL_VERBOSE <<"Error: queryInterface failed (in _queryInterface)!" LOG_
		return "";
	}
	
	return ID;
}
lb_I_Module* LB_STDCALL lbDOMConfig::getModuleManager() {
		lbErrCodes err = ERR_NONE;
		UAP(lb_I_Module, _mm, __FILE__, __LINE__)
		if (manager == NULL) {
			_CL_VERBOSE << "Error: Can't return module manager. Call setModuleManager(...) on me first!" LOG_
			return NULL;
		}
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__)
		return _mm.getPtr();
}

void LB_STDCALL lbDOMConfig::setModuleManager(lb_I_Module* m, char* file, int line) {
	if (m == NULL) {
		_CL_VERBOSE << "Error: Set module manager with a NULL pointer in " << "lbDOMConfig" << " while setModuleManager(...)!" LOG_
		return;
	}
	
	further_lock = 0;
	if (debug_macro == 1) {
		_CL_VERBOSE << "Warning: setModuleManager() must be enhanced by module manager use" LOG_
	}
	if (m != manager.getPtr()) {
	    if (m != NULL) m->queryInterface("lb_I_Module", (void**) &manager, file, line);
	}
	manager.setLine(__LINE__);
	manager.setFile(__FILE__);
	
	if (manager != NULL) {
		char *datei = strrchr(file, '\\');
		if (datei == NULL)
			datei = file;
		else
			datei++;
		manager->notify_create(this, "lbDOMConfig", datei, line);
	} else {
		_CL_VERBOSE << "Error: Query interface failed for manager in " << "lbDOMConfig" << " while setModuleManager(...)!" LOG_
	}
}

void LB_STDCALL lbDOMConfig::resetRefcount() { ref = STARTREF; }
int LB_STDCALL lbDOMConfig::deleteState() {
	return (ref-1 == STARTREF) ? 1 : 0;
}
char*      LB_STDCALL lbDOMConfig::getCreationLoc() const {
	char buf[20] = "";
	sprintf(buf, "%p", (void*) this);
	if (manager != NULL) return manager->getCreationLoc(buf);
	return strdup("Have no manager - location can't be found");
}
lbErrCodes LB_STDCALL lbDOMConfig::release(char* file, int line) {
        ref--;
        if (strcmp("lb_EventManager", "lbDOMConfig") == 0) {
        	_CL_VERBOSE << "lb_EventManager::release() called" LOG_
        }
	char ptr[20] = "";
        if (manager != NULL) {
        	manager->notify_release(this, "lbDOMConfig", file, line);
        }
	
        if (ref == STARTREF) {
        	if (manager != NULL) {
        		if (manager->can_delete(this, "lbDOMConfig") == 1)	{
        			manager->notify_destroy(this, "lbDOMConfig", file, line);
        			delete this;
        			return ERR_RELEASED;
        		}
        		else
        			_CL_VERBOSE << "Error: Instance has been deleted prior!" LOG_
        	}
        	return ERR_NONE;
        }
        if (ref < STARTREF) {
        	_CL_VERBOSE << "Error: Reference count of instance " << ptr << " of object type " << "lbDOMConfig" << " is less than " << STARTREF << " (" << ref << ") !!!" LOG_
        	return ERR_REFERENCE_COUNTING;
        }
        return ERR_INSTANCE_STILL_USED;
}

lb_I_Unknown* LB_STDCALL lbDOMConfig::clone(char* file, int line) const {

	lbDOMConfig* cloned = new lbDOMConfig();
	cloned->setDebug(0);
	lb_I_Unknown* uk_this;

	lb_I_Unknown* uk_cloned = NULL;

	cloned->setFurtherLock(0);
	if (manager == NULL) _CL_VERBOSE << "lbDOMConfig" << "::clone() can't be used because manager is a NULL pointer!" LOG_
	cloned->setModuleManager(manager.getPtr(), file, line);
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) {
		_CL_VERBOSE << "Error while getting interface" LOG_
	}

	uk_cloned->setData((lb_I_Unknown*) this);

	cloned->resetRefcount();
	
	if (manager != NULL) {
		lb_I_Unknown* that = (lb_I_Unknown*) cloned;
	        manager->notify_add(that, cloned->getClassName(), file, line);
	}
        else
		if (debug_macro == 1) {
                	_CL_VERBOSE << "Module manager was not set!" LOG_
		}
	
	lb_I_Unknown* uk = NULL;
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) {
		_CL_VERBOSE << "Error while getting unknown interface of cloned object" LOG_
	}

	if (uk->getRefCount() > 1) {
		_CL_VERBOSE << "Cloned object has %d references" << uk->getRefCount() LOG_
	}
	return uk;

}

lbErrCodes LB_STDCALL lbDOMConfig::queryInterface(char* name, void** unknown, char* file, int line) {
	char buf[1000] = "";
	char iFaces[1000] = "";
	char _classname[100] = "lbDOMConfig";
	if (further_lock == 1) {
		_CL_VERBOSE <<"Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!" LOG_
		return ERR_STATE_FURTHER_LOCK;
	}
	if (unknown == NULL) {
		_CL_VERBOSE << "Error: Got NULL pointer reference while queryInterface() called for " <<
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_
	}

	strcat(iFaces, "lb_I_Unknown, ");
        if (strcmp(name, "lb_I_Unknown") == 0) {
        	if (ref < STARTREF) {
        		_CL_VERBOSE << "Reference count error in queryInterface (" "lbDOMConfig" ")" LOG_
        	}
                ref++;
                *unknown = (lb_I_Unknown*) this;
                if (manager != NULL) {
                	lb_I_Unknown* that = (lb_I_Unknown*) this;
		        manager->notify_add(that, _classname, file, line);
		}
		else {
	        	setFurtherLock(1);
	        	_CL_VERBOSE << "Lock object due to missing manager!" LOG_
	        	return ERR_STATE_FURTHER_LOCK;
		}
                return ERR_NONE;
        }

/*...e*/
#endif
	ADD_INTERFACE(lb_I_XMLConfig)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDOMConfig::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbDOMConfig::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

/*...slbDOMConfig\58\\58\lbDOMConfig\40\char\42\ file\44\ int line\41\:0:*/
lbDOMConfig::lbDOMConfig(char* file, int line) {
	_CL_VERBOSE << "lbDOMConfig::lbDOMConfig(char* file, int line) called" LOG_
	manager = NULL;
	ref = STARTREF;
	lastResult = NULL;
	haveFunctorList = 0;
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
				COUT << "Error during initialization! :\n"
		                 << toCatch.getMessage() << ENDL;
		         //return ERR_XML_INIT;
		    }		
/*...e*/
	}

	parse();
}
/*...e*/
/*...slbDOMConfig\58\\58\lbDOMConfig\40\\41\:0:*/
lbDOMConfig::lbDOMConfig() {
	_CL_VERBOSE << "lbDOMConfig::lbDOMConfig() called" LOG_
	manager = NULL;
	ref = STARTREF;
	lastResult = NULL;
	haveFunctorList = 0;
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
				COUT << "Error during initialization! :\n"
		                 << toCatch.getMessage() << ENDL;
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
	COUT << "lbDOMConfig::~lbDOMConfig() called" << ENDL;
/*...e*/

	if (ref != STARTREF) COUT << "Error: Reference count mismatch!" << ENDL;
	if (errReporter != NULL) {
		delete errReporter;
	}
	if (lastResult != NULL) {
		lastResult->deleteAll();
		RELEASE(lastResult);
		lastResult = NULL;
	}
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::parse() {
	lbErrCodes err = ERR_NONE;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	COUT << "Parse file '" << filename << "'..." << ENDL;
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
			COUT << "Parse error\n" << ENDL;
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
		_CL_VERBOSE << "Error: Could not generate a reference with interface lb_I_Container" LOG_
		if (list != NULL) _LOG << "Obviously failed queryInterface, instance pointer is not NULL!!!!" LOG_
		return NULL;
	}
/*...sPrepare search:8:*/

	if (treePos == NULL) {
		COUT << "Null pointer detected!" << ENDL;
		
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
		COUT << "Node XPointer: '" << path << "'" << ENDL
		     << "Search for   : '" << DOMString(treePos) << "'" << ENDL;
#endif
/*...e*/
/*...sFound a entry \63\ insert in list:16:*/
//		COUT << path << ENDL;
		if (path.equals(treePos)) {
//			COUT << "match" << ENDL;
/*...sVERBOSE:16:*/
#ifdef VERBOSE
			COUT << "Found a entry." << ENDL;
#endif		
/*...e*/
			/**
			 * Create the wrapper object lbDOMNode, after it has
			 * implemented all abstract members.
			 */
			
			lbDOMNode* lbNode = new lbDOMNode(__FILE__, __LINE__);
			lbNode->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
			lbNode->setNode(currentnode);

			
			UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

			if (lbNode->queryInterface("lb_I_Unknown", (void**) &unknown, __FILE__, __LINE__) != ERR_NONE) {
				_CL_VERBOSE << "lbNode->queryInterface() Failed!" LOG_
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
			COUT << "Inserted the entry" << ENDL;
#endif
/*...e*/
		} else COUT << "Path '" << path << "' does not match" << ENDL;
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
		//if (haveFunctorList == 0) {
		//	printf("lbDOMConfig::hasConfigObject() called with using findNodesAtTreePos();\n");
			lastResult = findNodesAtTreePos(cfgObjectName);
		//	printf("lbDOMConfig::hasConfigObject(...) has produced %d elements in lastResult\n", count);
		//} else {
		//	printf("lbDOMConfig::hasConfigObject() called without using findNodesAtTreePos();\n");
		//}
		count = lastResult->Count(); //= lastResult->getChildrenCount();
		return err;
	} else COUT << "Any errors while parsing has been occured!" << ENDL;
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
	
	if (manager.getPtr() == NULL) _LOG << "Error: Manager in lbDOMConfig is a NULL pointer!" LOG_

	node->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	if (lastResult == NULL) {
		_CL_VERBOSE << "Error: Function sequence may be wrong. Please call hasConfigObject first!" LOG_
		return ERR_FUNCTION_SEQUENCE;
	}
	
	lastResult->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	if ((lastResult != NULL) && (lastResult->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__)) != ERR_NONE) {
		_CL_VERBOSE << "Error: Could not get interface lb_I_Container" LOG_
		getch();
	}
	
	if (c == NULL) _LOG << "Error: Failed to get container instance of lastResult" LOG_
	
	node->lbDOMchilds = c;
	node->node = NULL; // See null pointer operator (this results in the error in the destructor)
	
	// This interface is needed:
	node->queryInterface("lb_I_ConfigObject", (void**) cfgObj, __FILE__, __LINE__);

	track_Object(*cfgObj, "Problematic instance created");
	haveFunctorList = 1;

	return err;
}
/*...e*/
/*...e*/

/*...sclass lbFunctorEntity:0:*/
class lbFunctorEntity : public lb_I_FunctorEntity
{
public:

        lbFunctorEntity() {
        	_functor = NULL;
        	_module = NULL;
        	_interface = NULL;
        }
        
        virtual ~lbFunctorEntity() {
        	if (_functor) free(_functor);
        	if (_module) free(_module);
        	if (_interface) free(_interface);
        }

public:

        virtual void LB_STDCALL setFunctor(char* functor) {
        	_functor = strdup(functor);
        }
        
        virtual void LB_STDCALL setModule(char* module) {
        	_module = strdup(module);
        }
        
        virtual void LB_STDCALL setInterface(char* iface) {
        	_interface = strdup(iface);
        }

	
public:

	DECLARE_LB_UNKNOWN()


        virtual char* LB_STDCALL getFunctor() {
        	return _functor;
        }
        
        virtual char* LB_STDCALL getModule() {
        	return _module;
        }
        
        virtual char* LB_STDCALL getInterface() {
        	return _interface;
	}

        friend class lb_I_InterfaceRepository;

	char* _functor;
	char* _module;
	char* _interface;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFunctorEntity)
        ADD_INTERFACE(lb_I_FunctorEntity)
END_IMPLEMENT_LB_UNKNOWN()



lbErrCodes lbFunctorEntity::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbFunctorEntity::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...sclass lbInterfaceRepository:0:*/
class lbInterfaceRepository : public lb_I_InterfaceRepository
{
public:
        lbInterfaceRepository();
        virtual ~lbInterfaceRepository();

        DECLARE_LB_UNKNOWN()

	void LB_STDCALL setCurrentSearchInterface(const char* iface);
	lb_I_FunctorEntity* LB_STDCALL getFirstEntity();

	lbErrCodes LB_STDCALL parse();
	
	
	void initIntefaceList();
	
	ErrorHandler *errReporter;
	int errorsOccured;
	DOM_Document doc;
	
	// Created once and contains all interface nodes
	DOM_NodeList DOMlist;
	unsigned int interfaces; // current interface index
	unsigned int len;
	
	/**
	 * Indicates the current search mode (currently only over interfaces).
	 */
	int CurrentSearchMode;
	DOMString searchArgument;
	
	/**
	 * Indicates an invalid search status like 
	 * 	noPrevious interface;
	 *	noNext     interface;
	 *
	 * Note:	Moving to first or last interface resets any invalid status.
	 */
	int invalidSearchStatus;
};

BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbInterfaceRepository)
        ADD_INTERFACE(lb_I_InterfaceRepository)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfInterfaceRepository, lbInterfaceRepository)

lbInterfaceRepository::lbInterfaceRepository() {	
	printf("lbInterfaceRepository::lbInterfaceRepository() called\n");
	_CL_VERBOSE << "lbInterfaceRepository::lbInterfaceRepository() called" LOG_
	manager = NULL;
	ref = STARTREF;
	errReporter = new DOMTreeErrorReporter();
	_CL_VERBOSE << "DOMTreeErrorReporter() created" LOG_

	if (initialized == 0) {
/*...sInitialize the DOM4C2 system:16:*/
		    // Initialize the DOM4C2 system
		    try
		    {
				XMLPlatformUtils::Initialize();
		    }

			catch (const XMLException& toCatch)
		    {
				COUT << "Error during initialization! :\n"
		                 << toCatch.getMessage() << ENDL;
		         //return ERR_XML_INIT;
		    }		
/*...e*/
	}

	parse();
	_CL_VERBOSE << "parse() called" LOG_
}

lbInterfaceRepository::~lbInterfaceRepository() {
}

lbErrCodes lbInterfaceRepository::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbInterfaceRepository::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbInterfaceRepository::setCurrentSearchInterface(const char* iface) {
	searchArgument = DOMString(iface);
	interfaces = 0;
	CurrentSearchMode = 1;
	printf("Call lbInterfaceRepository::setCurrentSearchInterface(...):initIntefaceList()\n");
	initIntefaceList();
}

/*...slb_I_FunctorEntity\42\ LB_STDCALL lbInterfaceRepository\58\\58\getFirstEntity\40\\41\:0:*/
lb_I_FunctorEntity* LB_STDCALL lbInterfaceRepository::getFirstEntity() {
	if (CurrentSearchMode == 0) {
		printf("SearchMode not set. Please call first lbInterfaceRepository::setCurrentSearchInterface(char* iface)\nOr any further other setCurrentSearch<Mode>(char* argument) function\n");
		return NULL;
	}
	
	if (CurrentSearchMode != 1) {
		printf("SearchMode currently not provided.\n");
		return NULL;
	}


	// Search for that node, containing specifed intarfece.
	for (interfaces; interfaces < len; interfaces++) {
		DOM_Node node = DOMlist.item(interfaces);
		
		DOM_NamedNodeMap attributeMap = node.getAttributes();
		
		DOM_Node InterfaceName = attributeMap.getNamedItem(DOMString("Name"));
		
		if (InterfaceName.getNodeValue().equals(DOMString(searchArgument))) {
		
			DOMString nodename = node.getNodeName();
		
			char* module = NULL;
			char* functor = NULL;
		
			// Navidate to the Function node to get the functor name
			node = node.getParentNode().getParentNode();
			DOM_NodeList nodeList = node.getChildNodes();
		
/*...sfind function name value:24:*/
		// Find function name
		for (unsigned int index = 0; index < nodeList.getLength(); index++) {
			node = nodeList.item(index);
			if (node.getNodeName().equals(DOMString("FunctionName"))) break;
		}
				
		attributeMap = node.getAttributes();

		DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

		if (an_attr == NULL) {
		        printf("Error: Attribute not found\n"); // LOG_

		        return NULL;
		        
		}
/*...e*/
			DOMString functorName = an_attr.getNodeValue();

			DOM_Node moduleNode = node.getParentNode().getParentNode().getParentNode();
			nodeList = moduleNode.getChildNodes();
			
/*...sfind module for that functor:24:*/

			DOM_Node moduleNameNode;

	                // Find module name
	                for (int i = 0; i < nodeList.getLength(); i++) {
	                        moduleNameNode = nodeList.item(i);
	                        if (moduleNameNode.getNodeName().equals(DOMString("ModuleName"))) break;
	                }			

			attributeMap = moduleNameNode.getAttributes();
			an_attr = attributeMap.getNamedItem(DOMString("Name"));
			
			if (an_attr == NULL) {
			        printf("Error: Attribute not found\n"); //" LOG_
			        for (unsigned int l = 0; l < attributeMap.getLength(); l++) {
			        	DOM_Node n = attributeMap.item(l);
			        	printf("Debug of Node ");
			        	moduleNode.getNodeName().print();
			        	printf(" has Attribute ");
			        	n.getNodeName().println();
			        }

			        return NULL;

			}
			
/*...e*/

			DOMString moduleName = an_attr.getNodeValue();

			char* temp = functorName.transcode();
			functor = strdup(temp);
			functorName.deletetranscoded(temp);
			
			temp = moduleName.transcode();
			module = strdup(temp);
			moduleName.deletetranscoded(temp);
			
			
			lbFunctorEntity* fe = new lbFunctorEntity;
			fe->setModuleManager(this->getModuleManager(), __FILE__, __LINE__);
			lb_I_FunctorEntity* _fe = NULL;
			fe->queryInterface("lb_I_FunctorEntity", (void**) &_fe, __FILE__, __LINE__);
			
			_fe->setModule(module);
			_fe->setFunctor(functor);
			
			
			return _fe;
			
		}
/*...sRubbish:0:*/
#ifdef bla
		if (value == DOMString(iface)) {
/*...sget the nodes\44\ that contains the data:24:*/
			// Get the functor and module for creation of FunctorEntity
			DOM_Node module = node.getParentNode();
			module = module.getParentNode();
			module = module.getParentNode();
			module = module.getParentNode();
			
			DOM_Node functor = node.getParentNode();
			functor = functor.getParentNode();
/*...e*/

			DOM_NodeList DOMlist = module.getChildNodes();
			int count = DOMlist.getLength();
			
			DOM_Node child;
			char* modulename = NULL;
			char* functorname = NULL;
			
/*...sget module name:24:*/
			for (int ii = 0; ii < count; ii++) {
				child = DOMlist.item(ii);
				
				if (child.getNodeName() == DOMString("ModuleName")) {
					DOM_NamedNodeMap attributeMap = child.getAttributes();

					if (attributeMap == NULL) {
					        _CL_VERBOSE << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_VERBOSE << "Error: Attribute not found" LOG_

					        return NULL;
					}

					DOMString value = an_attr.getNodeValue();
					char* temp = value.transcode();
					
					// Bugfix in XML4C - do cleanup directly
					modulename = strdup(temp);
					value.deletetranscoded(temp);
					temp = NULL;
					break;
				}
			}
/*...e*/
			
			DOMlist = functor.getChildNodes();
			count = DOMlist.getLength();
			
/*...sget functor name:24:*/
			for (ii = 0; ii < count; ii++) {
				child = DOMlist.item(ii);
				
				if (child.getNodeName() == DOMString("FunctionName")) {
					DOM_NamedNodeMap attributeMap = child.getAttributes();

					if (attributeMap == NULL) {
					        _CL_VERBOSE << "Error: This node is not of type ELEMENT" LOG_

					        return NULL;
					}

					DOM_Node an_attr = attributeMap.getNamedItem(DOMString("Name"));

					if (an_attr == NULL) {
					        _CL_VERBOSE << "Error: Attribute not found" LOG_

					        return NULL;
					}

					DOMString value = an_attr.getNodeValue();
					char* temp = value.transcode();
					
					// Bugfix in XML4C - do cleanup directly
					functorname = strdup(temp);
					value.deletetranscoded(temp);
					temp = NULL;
				}
			}
/*...e*/

			printf("lbInterfaceRepository got functor %s in module %s for %s\n", functorname, modulename, iface);
			
			break;
		}
#endif
/*...e*/
	}

	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbInterfaceRepository\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbInterfaceRepository::parse() {
	lbErrCodes err = ERR_NONE;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	COUT << "Parse file '" << filename << "'..." << ENDL;
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
			COUT << "Parse error\n" << ENDL;
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
/*...svoid lbInterfaceRepository\58\\58\initIntefaceList\40\\41\:0:*/
void lbInterfaceRepository::initIntefaceList() {
	char* name = NULL;
	char* savename = NULL;
        savename = strdup("#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName");
	printf("Call strrchr\n");
        name = strrchr(savename, '/');
	printf("Called and have %s\n", name);
        if (name == NULL) name = savename;
	printf("Call getElementsByTagName(...) with %s\n", (name[0] == '/') ? &name[1] : name);
	
	DOMString s = DOMString((name[0] == '/') ? &name[1] : name);
	printf("Have created a DOMString\n");
	
	if (doc.isNull()) printf("ERROR: DOM document is null!\n");
	
        DOMlist = doc.getElementsByTagName(s);
	printf("Called getElementsByTagName(...)\n");
        len = DOMlist.getLength();
        // Cleanup
	printf("lbInterfaceRepository::initIntefaceList(): cleanup\n");
        delete [] savename;
}
/*...e*/
/*...e*/

// IMPLEMENT_SINGLETON_FUNCTOR does not work
IMPLEMENT_FUNCTOR(getlbDOMConfigInstance, lbDOMConfig)
#ifdef bla
/*...s:0:*/
lbErrCodes DLLEXPORT LB_FUNCTORCALL getlbDOMConfigInstance(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) {

	lbErrCodes err = ERR_NONE;
        lbDOMConfig* instance = new lbDOMConfig();
        
        *uk = NULL;
        instance->setFurtherLock(0);
        if (m != NULL) {
        	_CL_VERBOSE << "Try to set module manager" LOG_
        	instance->setModuleManager(m, __FILE__, __LINE__);
		_CL_VERBOSE << "Functor called setModuleManager" LOG_
        } else {
        	_CL_VERBOSE << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_
        }
       
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) {
                _CL_VERBOSE << "Failed to create unknown reference to instance of " <<
                "lbDOMConfig" << ". Errcode is " << err LOG_
                if (err == ERR_STATE_FURTHER_LOCK) {
                	_CL_VERBOSE << "ERR_STATE_FURTHER_LOCK" LOG_
                	return err;
                }
                return ERR_FUNCTOR;
        }

        return ERR_NONE;
}
/*...e*/
#endif
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
COUT << "Got node name and value" << ENDL;
if (nodeValue == NULL) 
	COUT << "Value is NULL" << ENDL;
else
	COUT << "Value is " << nodeValue << ENDL;
	
if (nodeName == NULL) 
	COUT << "Name is NULL" << ENDL;
else
	COUT << "Name is " << nodeName << ENDL;

COUT << "Check done" << ENDL;
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
                target << child << ENDL;
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
                 << (long)toWrite.getNodeType() << ENDL;
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

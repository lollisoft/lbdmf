#define LBXMLCONFIG_EXPORTS

/*...sincludes:0:*/
#include <util/PlatformUtils.hpp>
#include <parsers/SAXParser.hpp>
#include <util/XMLUni.hpp>
#include <sax/AttributeList.hpp>

#include "XMLConfig.h"
#include "XMLConfigHandlers.h"


#include "stdafx.h"
#include "lbXMLConfig.h"
#include "lbXMLConfigDoc.h"
#include "TypeHandlers.h" // Must be the last here

#include <conio.h>
/*...e*/

lbConfigObject* p_ConfigObject;

/*...sDllMain:0:*/
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
/*...e*/

int initialized = 0;

/*...sclass lbXMLConfig \58\ public lb_I_XMLConfig:0:*/
/*...sclass lbXMLConfig:0:*/
class lbXMLConfig : 
		public lb_I_XMLConfig
{
public:
	lbXMLConfig();
	~lbXMLConfig();
	lbXMLConfig(const lbXMLConfig & t) {
		ref = STARTREF;
		handler = NULL;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbXMLConfig(const lbXMLConfig* & t) called" << endl;
	
#endif	
/*...e*/
		gTopLevel = t.gTopLevel;
	}

	virtual lbErrCodes LB_STDCALL release();
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown);
	

	virtual lbErrCodes LB_STDCALL parse();
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName);
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject*& cfgObj, const char* const cfgObjectName);

	static TopLevel *gTopLevel;
protected:
	int ref;
	int interface_used;
	XMLTreeBuilder*  handler;
};
/*...e*/

/*...slbXMLConfig\58\\58\lbXMLConfig\40\\41\:0:*/
lbXMLConfig::lbXMLConfig() {
	ref = STARTREF;
	interface_used = 0;
	gTopLevel = new TopLevel;
	handler = NULL;
}
/*...e*/
/*...slbXMLConfig\58\\58\\126\lbXMLConfig\40\\41\:0:*/
lbXMLConfig::~lbXMLConfig() {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbXMLConfig::~lbXMLConfig() called" << endl;
#endif
/*...e*/
	if (ref != STARTREF) cout << "Error: Reference count mismatch!" << endl;
	
	if (gTopLevel != NULL) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE		
		cout << "Delete gTopLevel object" << endl;
#endif		
/*...e*/
		delete handler;
		delete gTopLevel;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Deleted gTopLevel object" << endl;
#endif
/*...e*/
	}
}
/*...e*/
/*...slbErrCodes lbXMLConfig\58\\58\release\40\\41\:0:*/
lbErrCodes LB_STDCALL lbXMLConfig::release() {

	if (interface_used != 0) ref--;
/*...sVERBOSE:0:*/
#ifdef VERBOSE	
cout << "lbXMLConfig::release() called (ref is now " << ref << ")" << endl;	
#endif
/*...e*/
	if (ref == STARTREF) {
		cout << "Delete lbXMLConfig object" << endl;
		delete this;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbXMLConfig\58\\58\queryInterface\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbXMLConfig::queryInterface(char* name, void** unknown) {
	if (strcmp(name, "lb_I_XMLConfig") == 0) {
		ref++;
		interface_used++;
		cout << "Test parsing..." << endl;
		parse();
		cout << "Tested parse" << endl;
		*unknown = (lb_I_XMLConfig*) this;
		cout << "lbXMLConfig::queryInterface(\"lb_I_XMLConfig\", unknown) ('" 
		<< hex << (void*) this << dec << "') called (returning '" 
		<< hex << (void*) *unknown << dec << "')" << endl;
		return ERR_NONE;
	}
	
	if (strcmp(name, "lb_I_Unknown") == 0) {
		ref++;
		interface_used++;
		*unknown = (lb_I_Unknown*) this;
		return ERR_NONE;
	}
	
	return ERR_NO_INTERFACE;
}
/*...e*/
/*...slbErrCodes lbXMLConfig\58\\58\parse\40\\41\:0:*/
lbErrCodes LB_STDCALL lbXMLConfig::parse() {
	lbErrCodes err = ERR_NONE;
cout << "lbXMLConfig::parse() called ('" << hex << (void*) this << dec << "')" << endl;
	char *filename = getenv("LBHOSTCFGFILE");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "Parse file '" << filename << "'..." << endl;
#endif
/*...e*/

	if (filename != NULL) {
	    if (initialized == 0) {
/*...sInitialize the XML4C2 system:20:*/
		    // Initialize the XML4C2 system
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

//for (long i = 0; i < 1000000; i++) {

/*...sSetup objects:12:*/
	    // Begin parsing...
	    SAXParser parser;
	    parser.setDoValidation(true);

	    handler = new XMLTreeBuilder();
	    handler->setTopLevelDocument(gTopLevel); // Internally stored static !!

	    parser.setDocumentHandler(handler);
	    parser.setErrorHandler(handler);
		
/*...e*/


/*...stry parsing \40\no explicid allocation\41\:12:*/
	    // Parse the file and catch any exceptions that propogate out
	    try	
		{
	            parser.parse(filename);

		    if (gTopLevel->m_plbConfigObject->getGeneralParseError()) {
			// Error while parsing
			err = ERR_XML_GENERAL_PARSE_FAILED;
		    }
		}

		catch (const XMLException& )
	        {
			CL_LOG("Parse error");
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
/*...slbErrCodes lbXMLConfig\58\\58\hasConfigObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbXMLConfig::hasConfigObject(const char* cfgObjectName) {
	lb_I_ConfigObject* obj = NULL;
	lbErrCodes err = ERR_NONE;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "Search '" << cfgObjectName << "'" << endl;
#endif
/*...e*/
	if ((err = gTopLevel->m_plbConfigObject->findObject(cfgObjectName,obj)) == ERR_NONE) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Call obj->release()" << endl;
#endif
/*...e*/
		obj->release();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Called" << endl;
#endif		
/*...e*/
	} else {
		cout << "No such object found" << endl;
	}

	return err;
}
/*...e*/
/*...slbErrCodes lbXMLConfig\58\\58\getConfigObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbXMLConfig::getConfigObject(lb_I_ConfigObject*& cfgObj, 
                                        const char* const cfgObjectName) {
	lbErrCodes err = ERR_NONE;
	// Try to locate the identifer in the tree

	cout << "lbXMLConfig::getConfigObject(...) called" << endl;

	if ((err = gTopLevel->m_plbConfigObject->findObject(cfgObjectName, cfgObj)) != ERR_NONE) {
		return err;
	}
	
	return err;
}
/*...e*/
/*...e*/

TopLevel* lbXMLConfig::gTopLevel = NULL;

/*...sgetlbXMLConfigInstance\40\lb_I_XMLConfig\42\\38\ inst\41\:0:*/
lbErrCodes LBXMLCONFIG_API __cdecl getlbXMLConfigInstance(lb_I_XMLConfig*& inst) {
/*...sMEMTEST:0:*/
#ifdef MEMTEST	
	cout << "Initialize lbXMLConfig object" << endl;
	
	
	for (long i = 0; i < 1000000; i++) { 
#endif
/*...e*/
		inst = new lbXMLConfig();
		cout << "Created lbXMLConfig instance" << endl;
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

/*...spragma \43\ vars:0:*/
// Turn off warning about identifier truncated in debug info.
#pragma warning(disable:4786)


XMLHandler* const kLeafTag = NULL;
XMLHandler* const kSwallowTagSet = NULL;

// We only need one null handler. It can be reused
// over and over.
NullHandler gNullHandler;
/*...e*/

//virtual
/*...sXMLHandler\42\ TopLevel\58\\58\startElement\40\\46\\46\\46\\41\:0:*/
XMLHandler* TopLevel::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "TopLevel::startElement() called" << flush << endl;
#endif
/*...e*/
	/**
	 * Assume parse error. As by the test lbConfigObject::startElement(...)
	 * is not called and so the error state would not be reseted.
	 */

	m_plbConfigObject->setGeneralParseError(TRUE);
	m_plbConfigObject->setDeep(0);
	cout << "Toplevel object: " << hex << (void*) m_plbConfigObject << dec << endl;

	return m_plbConfigObject;
}
/*...e*/
/*...svoid TopLevel\58\\58\test\40\\41\:0:*/
void TopLevel::test() {
	cout << "TopLevel::test() called" << endl;
}
/*...e*/
/*...sclass lbConfigObject:0:*/
char* lb_wcstombs(const wchar_t *pwcs) {
	size_t len = wcslen(pwcs);
	char* target = (char*) malloc(len+1);
	
	wcstombs(target, pwcs, len);
	
	target[len] = 0;
	
	return target;
}

int lbConfigObject::ocount = 0;
plbElementList lbConfigObject::all_elements = NULL;
/*...slbConfigObject\58\\58\lbConfigObject\40\lbConfigObject\42\ _parent\41\:0:*/
lbConfigObject::lbConfigObject(lbConfigObject* _parent) {
ocount++;
	int count = 0;
	interface_used = 0;
	ref = STARTREF;

/*...sMEMTEST:0:*/
#ifdef MEMTEST
	if (all_elements == NULL) {
		all_elements = new lbElementList;
		all_elements->next = NULL;
		all_elements->obj = _parent;
		
		cout << dec << "Have allocated " << count << " objects yet" << endl;
		
	}
	plbElementList temp = all_elements;

	int skipthis = 0;
	int skip_parent = 0;

	while (temp->next != NULL) {
		if (temp->obj == this) skipthis = 1;
		if (temp->obj == _parent) skip_parent = 1;
		temp = temp->next;
		count++;
	}
	      

	cout << dec << "Have " << count << " objects now" << endl;
	
	      
	// May be to save
	if (skipthis == 0) {
		temp->next = new lbElementList;
		temp = temp->next;
		
		temp->next = NULL;
		temp->obj = this;
	}
		
	if (skip_parent = 0) {
		temp->next = new lbElementList;
		temp = temp->next;
		
		temp->next = NULL;
		temp->obj = _parent;
	}
#endif
/*...e*/
	_name = NULL;
	attribut_list = NULL;
	parent = _parent;
	if (parent != NULL) deep = parent->getDeep() + 1;
	childs = NULL;//_parent->childs;
}
/*...e*/
/*...slbConfigObject\58\\58\\126\lbConfigObject\40\\41\:0:*/
lbConfigObject::~lbConfigObject() {
ocount--;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "lbConfigObject::~lbConfigObject() called (" << ((_name) ? _name : "?") << ")" << endl;
#endif
/*...e*/
	if (ref != STARTREF) cout << "Reference count mismatch!" << endl;

	if (_name != NULL) free(_name);

	while (attribut_list != NULL) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Have to delete the attribut_list" << endl;
#endif
/*...e*/
		plbAttribut pList = attribut_list;
		attribut_list = attribut_list->next;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Delete pList->name" << endl;
#endif
/*...e*/
		if (pList->name != NULL) free(pList->name); 
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Delete pList->value" << endl;
#endif
/*...e*/
		if (pList->value != NULL) free(pList->value); 
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Delete pList" << endl;
#endif
/*...e*/
		delete pList;
	}

	while (childs != NULL) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Have to delete the childs" << endl;
#endif
/*...e*/
		plbElementList pChild = childs;
		childs = childs->next;
/*...sVERBOSE:0:*/
#ifdef VERBOSE		
		cout << "Release a lbConfigObject object (" << hex << (void*) pChild->obj << ")" << endl;
#endif
/*...e*/
		pChild->obj->release();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Released" << endl;
#endif		
/*...e*/
		delete pChild;
	}
}
/*...e*/
/*...slbConfigObject\58\\58\release\40\\41\:0:*/
lbErrCodes LB_STDCALL lbConfigObject::release() {
	if (interface_used != 0) ref--;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbConfigObject::release() called (ref now is " << ref << ")" << endl;
#endif
/*...e*/
	if (ref == STARTREF) {
#ifdef bla	
/*...scleanup:16:*/
		if (all_elements != NULL) {
			plbElementList temp = all_elements;
			plbElementList pre = temp;
		
			while ((temp->next != NULL) && (temp->obj != this)) {
				pre = temp;
				temp = temp->next;
			}
		
			if ((temp->obj == this) && (pre != temp)) {
				// Anywhere in the list
				pre->next = temp->next;
				delete temp;
			} else {
				all_elements = temp->next;
				delete temp;
			}
		}	
/*...e*/
#endif	

		cout << "Delete object (" << ((_name) ? _name : "?") << ") " << hex << (void*) this << dec << endl;
		delete this;
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbConfigObject\58\\58\queryInterface\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbConfigObject::queryInterface(char* name, void** unknown) {
	
	if (strcmp(name, "lb_I_ConfigObject") == 0) {
		ref++;
		interface_used++;
		*unknown = (lb_I_ConfigObject*) this;
		return ERR_NONE;
	}
	
	if (strcmp(name, "lb_I_Unknown") == 0) {
		ref++;
		interface_used++;
		*unknown = (lb_I_Unknown*) this;
		return ERR_NONE;
	}
	
	return ERR_NO_INTERFACE;
}
/*...e*/
/*...sint lbConfigObject\58\\58\getDeep\40\\41\:0:*/
int lbConfigObject::getDeep() {
	return deep;
}
/*...e*/
/*...svoid lbConfigObject\58\\58\setDeep\40\int d\41\:0:*/
void lbConfigObject::setDeep(int d) {
	deep = d;
}
/*...e*/
/*...svoid lbConfigObject\58\\58\setGeneralParseError\40\BOOL _parseError\41\:0:*/
void lbConfigObject::setGeneralParseError(BOOL _parseError) {
	parseError = _parseError;
}
/*...e*/
/*...sBOOL lbConfigObject\58\\58\getGeneralParseError\40\\41\:0:*/
BOOL lbConfigObject::getGeneralParseError() {
	return parseError;
}
/*...e*/
/*...sXMLHandler\42\ lbConfigObject\58\\58\startElement\40\\46\\46\\46\\41\:0:*/

//virtual
XMLHandler* lbConfigObject::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	/**
	 * If this instance has a LOCID, then set a back pointer 
	 * to this instance for all childrens.
	 */
	int haveLOCID = 0;
	

	for (int ii=0; ii<deep; ii++) wcout << L" ";
		
	_name = lb_wcstombs(name);

	if (strcmp(_name, "ModuleName") == 0) {
		cout << "I saw element: " << _name << " " << hex << (void*) this << dec << endl;
	}
	
	if (_name == NULL) {
		cout << "Error! _name is a NULL pointer" << endl;
		
	}
	
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	cout << "lbConfigObject::startElement '" << _name << "' object: " << hex << (void*) this << dec << endl;
#endif
/*...e*/
/*...sCheck\44\ if a LOCID attribute is available:8:*/
	/**
	 * Check, if a LOCID attribute is available. If so, then create a
	 * container for ID's with that tag type.
	 */
	 
	const XMLCh* value = attributes.getValue("LOCID");
	
	if (value != NULL) {
//		for (int i=0; i<deep; i++) wcout << L" ";
//		wcout << L"Have a LOCID descriptor pointing to " << value << L"\n";
		
		haveLOCID = 1;
	} 
/*...e*/

	setGeneralParseError(FALSE);

	/**
	 * This is an entrypoint of a document
	 */
	lbConfigObject* temp = new lbConfigObject(this);

	if (haveLOCID == 1) {
	/**
	 * This entry describes, that a new subtree id would be used.
	 * Also this defines the tagname, containing an id.
	 * LOCID has an entry of the tag name.
	 */
		//temp->setBackPtr(this, value);
	}
#define STORE_DATA	
#ifdef STORE_DATA	
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "Begin storing data" << endl;
#endif
/*...e*/
/*...sstore element:8:*/
	plbElementList firstElement = NULL;

	if (childs == NULL) {
/*...sVERBOSE:8:*/
#ifdef VERBOSE
	cout << "childs == NULL" << endl;
#endif
/*...e*/
		childs = new lbElementList;
		childs->next = NULL;
		childs->obj = temp;
/*...sVERBOSE:8:*/
#ifdef VERBOSE
		cout << "Stored object is " << hex << (void*) childs->obj << endl;
		
#endif
/*...e*/
	} else {
/*...sVERBOSE:8:*/
#ifdef VERBOSE
	cout << "childs != NULL" << endl;
#endif
/*...e*/
		firstElement = childs;
	
		while (childs->next != NULL) childs = childs->next;
		childs->next = new lbElementList;
		childs = childs->next;
		childs->next = NULL;
/*...sVERBOSE:8:*/
#ifdef VERBOSE
	cout << "Assign temp" << endl;
#endif
/*...e*/
		childs->obj = temp;
/*...sVERBOSE:8:*/
#ifdef VERBOSE	
		cout << "Stored object is " << hex << (void*) childs->obj << endl;
		
#endif
/*...e*/
		childs = firstElement;
	}
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "Stored element" << endl;
#endif
/*...e*/
/*...sstore attributes:8:*/
	unsigned int count = attributes.getLength();
		
	if (attribut_list == NULL) {
		attribut_list = new lbAttribut;
		attribut_list->name = NULL;
		attribut_list->value = NULL;
		attribut_list->where = NULL;
		attribut_list->next = NULL;
	}
	
	plbAttribut first = attribut_list;
	
	while (attribut_list->next != NULL) attribut_list = attribut_list->next; 
		
/*...sfill up with all attributes:16:*/
	for (unsigned int i = 0; i < count; i++) {
		attribut_list->name = lb_wcstombs(attributes.getName(i));
		attribut_list->value = lb_wcstombs(attributes.getValue(i));
		attribut_list->where = this;

/*...sVERBOSE:32:*/
#ifdef VERBOSE
		cout << "Have attribute for " << _name << " '" 
		<< attribut_list->name 
		<< "' = '"
		<< attribut_list->value
		<< "'"
		<< " Type '"
		<< lb_wcstombs(attributes.getType(i))
		<< "'" << endl;
#endif
/*...e*/

		attribut_list->next = new lbAttribut;
		attribut_list = attribut_list->next;
		attribut_list->name = NULL;
		attribut_list->value = NULL;
		attribut_list->next = NULL;
	}
/*...e*/

	attribut_list = first;
	

		
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "Stored attributes" << endl;
#endif
/*...e*/
	if (childs == NULL) {
		cout << "Childs = NULL" << endl;
		
	}
#endif
	

	return temp;
}
/*...e*/
/*...slbErrCodes lbConfigObject\58\\58\findObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbConfigObject::findObject(const char* name, lb_I_ConfigObject*& object) {
	char* pattern = NULL;

	for (int ii=0; ii<deep; ii++) cout << " ";
		
	cout << "I (" << hex << (void*) this << dec << ") saw element: " << ((_name) ? _name : "?") << endl;


	plbElementList pChild = childs;
	
	deep++;	
		
/*...sSearch the list:8:*/
			while (childs != NULL) {
				lbErrCodes err = ERR_NONE;

				if ((err = childs->obj->findObject(name, object)) == ERR_NONE) {
					childs = pChild;
					return err;
				}
				childs = childs->next;
			}
/*...e*/
	
	deep--;
		
	childs = pChild;
	
	return ERR_NO_OBJECT;		
	
	if (name == NULL) {
		cout << "Name is a NULL pointer!" << endl;
		return ERR_NONE;
	}
	
	pattern = strdup(name);
	
	char* at = strchr(pattern, '/');

	


	if (at == NULL) {
/*...shandle simple name:8:*/
		cout << "No / found" << endl;
		
		if (_name == NULL) {
			cout << "Object not found - return" << endl;
			free(pattern);
			return ERR_NO_OBJECT;
		}
		cout << "strcmp(_name: '" << _name << "')..." << endl;
		
		if (strcmp(_name, pattern) == 0) {
			cout << "Found object with name '" << pattern << "'" << endl;
			queryInterface("lb_I_ConfigObject", (void**) &object);
			if (object != NULL) cout << "Got interface" << endl;
		} else {
			cout << "Strings are different" << endl;
			free(pattern);
			return ERR_NO_OBJECT;
		}
		
/*...e*/
	} else {
/*...shandle path:8:*/
		cout << "handle path" << endl;
		at[0] = 0;
		char* part = strdup(pattern);
		char* rest = strdup(at+1);
		
		cout << "Address of _name is " << hex << (void*) _name << endl;
		if (_name) cout << "Objectname: " << _name << endl;
		cout << "part: " << part << " rest: " << rest << endl;
		
		if (_name == NULL) {
/*...sAssume root element:24:*/
			plbElementList pChild = childs;
			
			if (childs == NULL) {
				cout << "Root element has no childs!" << endl;
			}
			
/*...sSearch the list:48:*/
			while (childs != NULL) {
				lbErrCodes err = ERR_NONE;
		
				cout << "Search on " << name << endl;
				
				if ((err = childs->obj->findObject(name, object)) == ERR_NONE) {
					childs = pChild;
					if (part) free(part);
					if (rest) free(rest);
					free(pattern);
					return err;
				}
				cout << "Search next element (_name == NULL)" << endl;
				childs = childs->next;
			}
/*...e*/
		
			childs = pChild;
			if (part) free(part);
			if (rest) free(rest);
			cout << "Return ERR_NO_OBJECT" << endl;
			free(pattern);
			return ERR_NO_OBJECT;
/*...e*/
		} else {
/*...sAssume childs of root element:24:*/
			plbElementList pChild = childs;
			
/*...sSearch the list:48:*/
			while (childs != NULL) {
				lbErrCodes err = ERR_NONE;

				cout << "Search on " << rest << endl;
				
				if ((err = childs->obj->findObject(rest, object)) == ERR_NONE) {
					childs = pChild;
					if (part) free(part);
					if (rest) free(rest);
					free(pattern);
					return err;
				}
				cout << "Search next element (_name != NULL)" << endl;
				childs = childs->next;
			}
/*...e*/
		
			childs = pChild;
			if (part) free(part);
			if (rest) free(rest);
			free(pattern);
			return ERR_NO_OBJECT;
/*...e*/
		}
		
		cout << "Not a NULL pointer, go ahead" << endl;
		
		
		if (strcmp(_name, part) == 0) {
			cout << "Found object with name '" << name << "'" << endl;
			queryInterface("lb_I_Unknown", (void**) &object);
			if (object != NULL) cout << "Got interface" << endl;
		}
	
		cout << "Element: " << part 
		<< "Rest: " << rest
		<< endl;
		
		if (part) free(part);
		if (rest) free(rest);
/*...e*/
	}
	
	free(pattern);
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbConfigObject\58\\58\getAttribute\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbConfigObject::getAttribute(const char* name, lb_I_Attribute*& attr) {
	return ERR_NONE;
}
/*...e*/
/*...e*/

/*...sclass XMLTreeBuilder:0:*/
// ---------------------------------------------------------------------------
//  XMLTreeBuilder: Constructors and Destructor
// ---------------------------------------------------------------------------
XMLTreeBuilder::XMLTreeBuilder()
{
}

XMLTreeBuilder::~XMLTreeBuilder()
{
}

void XMLTreeBuilder::setTopLevelDocument(XMLHandler* handler)
{ 
    	gTopLevel = handler;
}



// ---------------------------------------------------------------------------
//  XMLTreeBuilder: Overrides of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void XMLTreeBuilder::characters(const     XMLCh* const    chars,
                                const   unsigned int    length)
{
	m_Handlers.top()->characters(chars, length);
}


void XMLTreeBuilder::endDocument()
{
}


void XMLTreeBuilder::endElement(const XMLCh* const name)
{
	XMLHandler* curHandler = m_Handlers.top();
	if (m_Handlers.top()->endElement())
		m_Handlers.pop();
}

XMLHandler* XMLTreeBuilder::gTopLevel = NULL;

void XMLTreeBuilder::startDocument()
{
	if (gTopLevel == NULL) cout << "XMLTreeBuilder::startDocument() has a NULL pointer" << endl;
	m_Handlers.push(gTopLevel);
}

void XMLTreeBuilder::startElement(const   XMLCh* const    name,
                                  AttributeList&  attributes)
{
	XMLHandler* curHandler = m_Handlers.top();
	XMLHandler* nextHandler = m_Handlers.top()->startElement(name, attributes);
	m_Handlers.push(nextHandler ? nextHandler : &gNullHandler );
}



// ---------------------------------------------------------------------------
//  XMLTreeBuilder: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void XMLTreeBuilder::error(const SAXParseException& e)
{
//#ifdef VERBOSE
    cout << "Error at (file " << e.getSystemId()
            << ", line " << e.getLineNumber()
            << ", char " << e.getColumnNumber()
            << "): " << e.getMessage() << endl;
//#endif
}

void XMLTreeBuilder::fatalError(const SAXParseException& e)
{
//#ifdef VERBOSE
    wcout << L"Fatal Error at (file " << e.getSystemId()
            << L", line " << e.getLineNumber()
            << L", char " << e.getColumnNumber()
            << L"): " << e.getMessage() << L"\n";
//#endif
}

void XMLTreeBuilder::warning(const SAXParseException& e)
{
//#ifdef VERBOSE
    cout << "Warning at (file " << e.getSystemId()
            << ", line " << e.getLineNumber()
            << ", char " << e.getColumnNumber()
            << "): " << e.getMessage() << endl;
//#endif
}



// ---------------------------------------------------------------------------
//  XMLTreeBuilder: Overrides of the SAX DTDHandler interface
// ---------------------------------------------------------------------------
void XMLTreeBuilder::unparsedEntityDecl(const     XMLCh* const name
                                          , const   XMLCh* const publicId
                                          , const   XMLCh* const systemId
                                          , const   XMLCh* const notationName)
{
    // Not used at this time
	wcout << L"unparsedEntityDecl: " << name << L"\n";
}


void XMLTreeBuilder::notationDecl(const   XMLCh* const name
                                    , const XMLCh* const publicId
                                    , const XMLCh* const systemId)
{
    // Not used at this time
	wcout << L"notationDecl: " << name << L"\n";
}


/*...e*/

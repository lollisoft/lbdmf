/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.4 $
 * $Name:  $
 * $Id: lbDOMConfig.cpp,v 1.4 2000/11/24 21:05:03 lothar Exp $
 *
 * $Log: lbDOMConfig.cpp,v $
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

#include <lbConfigHook.h>

#include <lbInterfaces.h>
#include <lbDOMConfig.h>
/*...e*/

int initialized = 0;

// Global streaming operator for DOMString is defined in DOMPrint.cpp
void          outputContent(ostream& target, const DOMString &s);
extern ostream& operator<<(ostream& target, const DOMString& s);
ostream& operator<<(ostream& target, DOM_Node& toWrite);


bool doEscapes = false;

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
 
/*...sclass lbDOMNode \58\ public lb_I_ConfigObject:0:*/
class lbDOMNode : public lb_I_ConfigObject,
		  public lb_I_Object // For container usage
		  //public lb_I_Unknown
{
public:
	lbDOMNode();
	virtual ~lbDOMNode();
	

/*...slb_I_ConfigObject:0:*/
/* lb_I_ConfigObject */

	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object);
	virtual lbErrCodes LB_STDCALL getParent(lb_I_ConfigObject*& parent);
	virtual lbErrCodes LB_STDCALL getChildren(lb_I_Container*& children);

	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr);
	virtual char*      LB_STDCALL getName();
/*...e*/

/*...slb_I_Unknown:0:*/
/* lb_I_Unknown */

	virtual lbErrCodes LB_STDCALL release();
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown);
/*...e*/

/* lb_I_Object */

	DECLARE_LB_OBJECT(lbDOMNode)


protected:
	DOM_Node   node;
	lbNodeList* childs;
	
	int ref;
	
	friend class lbDOMConfig;
};
/*...e*/

typedef struct __lbDOMNodeList {
	lbDOMNode* element;
	__lbDOMNodeList* next;
} _lbDOMNodeList, * _plbDOMNodeList;

/*...sclass lbNodeList:0:*/
class lbNodeList { //: public lb_I_Container {
public:
	lbNodeList() { childs = NULL; parent = NULL; }
	virtual ~lbNodeList() {}

	lbErrCodes setParent(lb_I_Unknown *_parent);
	lbErrCodes insert(lb_I_Unknown *node);
	lbErrCodes remove(int i);
	lbErrCodes find(const char *nodeName, int & i);
	lbErrCodes get(lb_I_Unknown*& node, int i);
	
	lb_I_Container* clone() const;

protected:
	lbDOMNode* parent;
	_plbDOMNodeList childs;
};
/*...e*/
 
/*...sclass lbDOMNode implementation:0:*/

	

IMPLEMENT_LB_OBJECT(lbDOMNode, LB_DOM_NODE)

lbDOMNode::lbDOMNode() {
	ref = STARTREF;
}

lbDOMNode::~lbDOMNode() {
	if (ref != STARTREF) 
		cout << "Error: Reference count mismatch" << endl;
}

/*...slbDOMNode\58\\58\clone\40\\41\:0:*/
lb_I_Unknown* lbDOMNode::clone() const {
	lbDOMNode* _node = new lbDOMNode();
	_node->node = node;
	lb_I_Container* cloned= childs->clone();
	_node->childs = (lbNodeList*) cloned;

	/**
	 * Return an unknown object pointer
	 */	
	lb_I_Unknown* ret = NULL;
	_node->queryInterface("lb_I_Unknown", (void**) ret);
	
	//QI(_node, "lb_I_Unknown", ret);
	
	return ret;
}
/*...e*/

lbErrCodes LB_STDCALL lbDOMNode::findObject(const char* name, lb_I_ConfigObject*& object) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMNode::getParent(lb_I_ConfigObject*& parent) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMNode::getChildren(lb_I_Container*& children) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMNode::getAttribute(const char* name, lb_I_Attribute*& attr) {
	return ERR_NONE;
}

char* LB_STDCALL lbDOMNode::getName() {
	return "";
}

lbErrCodes LB_STDCALL lbDOMNode::release() {
        ref--;

        if (ref == STARTREF) delete this;
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDOMNode::queryInterface(char* name, void** unknown) {

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
/*...sclass lbNodeList implementation:0:*/

/*...slbNodeList\58\\58\clone\40\\41\:0:*/
lb_I_Container* lbNodeList::clone() const {
	lbNodeList* list = new lbNodeList();
	lb_I_Unknown *u = parent->clone();
	u->queryInterface("lb_I_NodeList", (void**) list->parent);
	u->release();

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

lbErrCodes lbNodeList::setParent(lb_I_Unknown *_parent) {
	/**
	 * Check if the given object has a lb_I_ConfigObject interface
	 */

	_parent->queryInterface("lb_I_ConfigObject", (void**) parent);

	if (parent != NULL) 
		return ERR_NONE;
	else
		LOG("Error: The parent object has no lb_I_ConfigObject interface");
		return ERR_NO_INTERFACE;
}

lbErrCodes lbNodeList::insert(lb_I_Unknown *node) {
	_plbDOMNodeList list = childs;
	lb_I_Object* object = NULL;
	lbDOMNode* newNode = NULL;
	
	if (list == NULL) {
		childs = list = new _lbDOMNodeList;
		list->next = NULL;
	}
	
	node->queryInterface("lb_I_Object", (void**) &object);

	if (object == NULL) {
		cout << "Try to log" << endl;
		LOG("Error: Only objects, that provide a lb_I_Object interface, could be stored");
		cout << "Logged" << endl;
		node->release();
		return ERR_NO_INTERFACE;
	}
	
	// The lb_I_Object reference is no more used now
	node->release();
	
	node->queryInterface("lb_I_ConfigObject", (void**) &newNode);
	
	if (newNode == NULL) {
		LOG("Error: This container can only store lb_I_ConfigObjects");
		return ERR_NO_INTERFACE;
	} 
	
	cout << "lbNodeList::insert(): Passed check" << endl;
	getch();
	while (list->next != NULL) list = list->next;
	
	list->next = new _lbDOMNodeList;
	list = list->next;
	
	list->element = newNode;
	list->next = NULL;
	
	cout << "Inserted a lb_I_ConfigObject" << endl;
	getch();
		
	return ERR_NONE;
}

lbErrCodes lbNodeList::remove(int i) {
	return ERR_NONE;
}

lbErrCodes lbNodeList::find(const char *nodeName, int & i) {
	return ERR_NONE;
}

lbErrCodes lbNodeList::get(lb_I_Unknown*& node, int i) {
	return ERR_NONE;
}
/*...e*/

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
	getch();
#endif	
/*...e*/
	}

	virtual lbErrCodes LB_STDCALL release();
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown);
	

	virtual lbErrCodes LB_STDCALL parse();
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName, int & count);
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject*& cfgObj, const char* const cfgObjectName);

protected:
	lbNodeList* LB_STDCALL findNodesAtTreePos(const char* treePos);

	int ref;
	int interface_used;
	ErrorHandler *errReporter;
	
	int errorsOccured;
	DOM_Document doc;
	
	lbNodeList* lastResult;
};
/*...e*/

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
/*...slbErrCodes lbDOMConfig\58\\58\release\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::release() {

	if (interface_used != 0) ref--;
/*...sVERBOSE:0:*/
#ifdef VERBOSE	
cout << "lbDOMConfig::release() called (ref is now " << ref << ")" << endl;	
#endif
/*...e*/
	if (ref == STARTREF) {
		cout << "Delete lbDOMConfig object" << endl;
		delete this;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\queryInterface\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::queryInterface(char* name, void** unknown) {
	if (strcmp(name, "lb_I_XMLConfig") == 0) {
		ref++;
		interface_used++;
		cout << "Test parsing..." << endl;
		parse();
		cout << "Tested parse" << endl;
		*unknown = (lb_I_XMLConfig*) this;
		cout << "lbDOMConfig::queryInterface(\"lb_I_XMLConfig\", unknown) ('" 
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
/*...slbNodeList\42\ lbDOMConfig\58\\58\findNodesAtTreePos\40\const char\42\ treePos\41\:0:*/
lbNodeList* LB_STDCALL lbDOMConfig::findNodesAtTreePos(const char* treePos) {
	char* part = NULL;
	char* name = NULL;
	char* savename = NULL;
	
	lbNodeList* list = new lbNodeList;

	if (treePos == NULL) {
		cout << "Null pointer detected!" << endl;
		getch();
		exit(1);
	}	

	savename = strdup(treePos);
	name = strrchr(savename, '/');
	if (name == NULL) name = savename;
	
	cout << "Search for nodename '" << ((name[0] == '/') ? &name[1] : name) << "'" << endl;
	
	DOM_NodeList DOMlist = doc.getElementsByTagName(((name[0] == '/') ? &name[1] : name));
	int len = DOMlist.getLength();

	DOMString path;
	
	if (len == 0) cout << "Nothing found" << endl;
	
	for (int i = 0; i < len; i++) {
		path = "";
		DOM_Node node = DOMlist.item(i);
		DOM_Node currentnode = node;
		
		while (node != NULL) {
			DOMString name = node.getNodeName();
			node = node.getParentNode();
			path = name + DOMString(((path == "") ? "" : "/")) + path;
		}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		cout << "Node XPointer: '" << path << "'" << endl
		     << "Search for   : '" << DOMString(treePos) << "'" << endl;
#endif
/*...e*/
		if (path.equals(treePos)) {
			cout << "Found a entry." << endl;
			/**
			 * Create the wrapper object lbDOMNode, after it has
			 * implemented all abstract members.
			 */
			 
			lbDOMNode* lbNode = new lbDOMNode;
			lbNode->node = currentnode;
			//lbNode->parent = currentnode.getParentNode();
			lbNode->childs = NULL;

			lb_I_Unknown* unknown = NULL;
			lbNode->queryInterface("lb_I_Unknown", (void**) &unknown);

			list->insert(unknown);
			cout << "Inserted the entry" << endl;
			
		} else cout << "Path '" << path << "' does not match" << endl;
	}
	
	return list;
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\hasConfigObject\40\const char\42\ \44\ int \38\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::hasConfigObject(const char* cfgObjectName, int & count) {
	lb_I_ConfigObject* obj = NULL;
	lbErrCodes err = ERR_NONE;

	DOMString name = DOMString(cfgObjectName);

	if (errorsOccured == 0) {
		
		//cout << "Output XML file: " << endl;
		//cout << doc;
		
		Beep(1000, 100);
		getch();
		lastResult = findNodesAtTreePos(cfgObjectName);
		Beep(2000, 100);
		
		DOM_NodeList list = doc.getElementsByTagName(name);
		
		int len = list.getLength();
		
		getch();
		
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
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\getConfigObject\40\lb_I_ConfigObject\42\\38\ \44\ const char\42\ const\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::getConfigObject(lb_I_ConfigObject*& cfgObj, 
                                        const char* const cfgObjectName) {
	lbErrCodes err = ERR_NONE;
	// Try to locate the identifer in the tree

	lbDOMNode *node = new lbDOMNode;
	node->childs = lastResult;

	node->queryInterface("lb_I_ConfigObject", (void**) cfgObj);

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
	getch();
	
	for (long i = 0; i < 1000000; i++) { 
#endif
/*...e*/
		inst = new lbDOMConfig();
		
/*...sMEMTEST:0:*/
#ifdef MEMTEST		
		inst->release();
	}
	
	cout << "Done it" << endl;
	getch();
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


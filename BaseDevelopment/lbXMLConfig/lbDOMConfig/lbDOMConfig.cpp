/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lbDOMConfig.cpp,v 1.2 2000/10/20 04:36:31 lothar Exp $
 *
 * $Log: lbDOMConfig.cpp,v $
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

// ??
class lbDOMNode : public lb_I_ConfigObject {
};

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
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName);
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject*& cfgObj, const char* const cfgObjectName);

protected:
	int ref;
	int interface_used;
	ErrorHandler *errReporter;
	
	int errorsOccured;
	DOM_Document doc;
};
/*...e*/

/*...slbDOMConfig\58\\58\lbDOMConfig\40\\41\:0:*/
lbDOMConfig::lbDOMConfig() {
	ref = STARTREF;
	interface_used = 0;
	errReporter = new DOMTreeErrorReporter();
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
/*...slbErrCodes lbDOMConfig\58\\58\hasConfigObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::hasConfigObject(const char* cfgObjectName) {
	lb_I_ConfigObject* obj = NULL;
	lbErrCodes err = ERR_NONE;

	DOMString name = DOMString(cfgObjectName);

	if (errorsOccured == 0) {
		
		//cout << "Output XML file: " << endl;
		//cout << doc; 

		DOM_NodeList list = doc.getElementsByTagName(/*"dtdHostCfgDoc/Modules",*/ name);
		
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
	}

	return err;
}
/*...e*/
/*...slbErrCodes lbDOMConfig\58\\58\getConfigObject\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbDOMConfig::getConfigObject(lb_I_ConfigObject*& cfgObj, 
                                        const char* const cfgObjectName) {
	lbErrCodes err = ERR_NONE;
	// Try to locate the identifer in the tree
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


/*
 * Sample code for Visual C++ Developers Journal
 * Loading XML Documents in C++, by Jim Beveridge.
 * January, 2000
 *
 * This code base on sample code from IBM.
 */


#ifndef __XML_HOST_CFG_HANDLERS__
#define __XML_HOST_CFG_HANDLERS__

#include    <sax/HandlerBase.hpp>
#include	<stack>
#include	<map>
#include	<string>


using namespace std;


//
// XMLHandler is a mixin interface that must be inherited
// by every object that can receive data from the
// XMLTreeBuilder dispatcher. These objects will
// never be called directly by SAX.
//
class XMLHandler
{
public:
	virtual XMLHandler* startElement(const   XMLCh* const    name,
						AttributeList&  attributes) = 0;

	// Returns whether or not to pop the handler stack
	virtual bool endElement()
		{return true; }

	virtual void characters(const XMLCh* const chars, const unsigned int length)
		{};

	virutal ~XMLHandler(){}
};


//
// XMLTreeBuilder is called by the SAX events. It is
// responsible for dispatching the SAX event to
// whichever object is currently responsible for
// handling it. This object is at the top of the stack.
//
class XMLTreeBuilder : public HandlerBase
{
public:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    XMLTreeBuilder();
    ~XMLTreeBuilder();


    // -----------------------------------------------------------------------
    //  Implementations of the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
    void endDocument();

    void endElement(const XMLCh* const name);

    void characters(const XMLCh* const chars, const unsigned int length);

    void startDocument();

    void startElement(const XMLCh* const name, AttributeList& attributes);



    // -----------------------------------------------------------------------
    //  Implementations of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exception);
    void error(const SAXParseException& exception);
    void fatalError(const SAXParseException& exception);



    // -----------------------------------------------------------------------
    //  Implementation of the SAX DTDHandler interface
    // -----------------------------------------------------------------------
    void notationDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
    );

    void unparsedEntityDecl
    (
        const   XMLCh* const    name
        , const XMLCh* const    publicId
        , const XMLCh* const    systemId
        , const XMLCh* const    notationName
    );

    stack<XMLHandler*> m_Handlers;
	
    void setTopLevelDocument(XMLHandler* handler);
	
    static XMLHandler* gTopLevel;
};


#endif // __XML_HOST_CFG_HANDLERS__

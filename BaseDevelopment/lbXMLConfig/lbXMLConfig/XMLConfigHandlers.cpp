/*
 * Sample code for Visual C++ Developers Journal
 * Loading XML Documents in C++, by Jim Beveridge.
 * January, 2000
 *
 * Apr 10, 2000 - Updated for version 3.1.0 of XML4C.
 *
 * This code base on sample code from IBM.
 */

// Turn off warning about identifier truncated in debug info.
#pragma warning(disable:4786)

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <util/XMLUni.hpp>
#include <sax/AttributeList.hpp>

//#include "SalesOrder.h"
#include "TypeHandlers.h"
//#include "VcdjSalesOrder.h"

XMLHandler* const kLeafTag = NULL;
XMLHandler* const kSwallowTagSet = NULL;

// We only need one null handler. It can be reused
// over and over.
NullHandler gNullHandler;

// The top-most handler that looks for XML documents'
// outermost tags.
TopLevel gTopLevel;

//////////////////////////////////////
//////////////////////////////////////


//virtual
XMLHandler* TopLevel::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"VcdjSalesOrder"))
		return &m_SalesOrdersDocument;

	return kSwallowTagSet;
}

//virtual
XMLHandler* SalesOrdersDocument::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"Customers"))
		return &m_Customers;
	else if (!wcscmp(name, L"Orders"))
		return &m_Orders;
	else if (!wcscmp(name, L"Products"))
		return &m_Products;

	return kSwallowTagSet;	// Unrecognized tag
}

XMLHandler* Order::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"OrderDetails"))
		return &m_Details;

	return kSwallowTagSet;	// Unrecognized tag
}

XMLHandler* Orders::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"Order"))
	{
		wstring id = attributes.getValue(L"ID");
		Order order;
		order.m_OrderId = id;
		order.m_CustomerId = attributes.getValue(L"CustomerId");
		order.m_OrderDate = attributes.getValue(L"OrderDate");
		(*this)[id] = order;
		// Hand off to the Order object to
		// read the OrderDetails.
		return &(*this)[id];
	}

	return kSwallowTagSet;	// Unrecognized tag
}

XMLHandler* OrderDetails::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"OrderDetail"))
	{
		wstring id = attributes.getValue(L"ID");
		OrderDetail detail;
		detail.m_OrderDetailId = id;
		detail.m_ProductId = attributes.getValue(L"ProductId");
		detail.m_Quantity = _wtoi(attributes.getValue(L"Quantity"));
		(*this)[id] = detail;
		return kLeafTag;	// No nested tags
	}

	return kSwallowTagSet;	// Unrecognized tag
}

XMLHandler* Products::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"Product"))
	{
		wstring id = attributes.getValue(L"ID");
		Product product;
		product.m_ProdId = id;
		product.m_ProductName = attributes.getValue(L"ProductName");
		wchar_t* stop;
		product.m_UnitPrice = wcstod(attributes.getValue(L"UnitPrice"), &stop);

		(*this)[id] = product;
		return kLeafTag;	// No nested tags
	}

	return kSwallowTagSet;	// Unrecognized tag
}

XMLHandler* Customers::startElement(const   XMLCh* const    name,
						AttributeList&  attributes)
{
	if (!wcscmp(name, L"Customer"))
	{
		wstring id = attributes.getValue(L"ID");
		Customer cust;
		cust.m_CustomerId = id;
		cust.m_CompanyName = attributes.getValue(L"CompanyName");
		cust.m_PhoneNumber = attributes.getValue(L"PhoneNumber");

		(*this)[id] = cust;
		return kLeafTag;	// No nested tags
	}

	return kSwallowTagSet;	// Unrecognized tag
}


// ---------------------------------------------------------------------------
//  XMLTreeBuilder: Constructors and Destructor
// ---------------------------------------------------------------------------
XMLTreeBuilder::XMLTreeBuilder()
{
}

XMLTreeBuilder::~XMLTreeBuilder()
{
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


void XMLTreeBuilder::startDocument()
{
	m_Handlers.push(&gTopLevel);
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
    cout << "Error at (file " << e.getSystemId()
            << ", line " << e.getLineNumber()
            << ", char " << e.getColumnNumber()
            << "): " << e.getMessage() << endl;
}

void XMLTreeBuilder::fatalError(const SAXParseException& e)
{
    cout << "Fatal Error at (file " << e.getSystemId()
            << ", line " << e.getLineNumber()
            << ", char " << e.getColumnNumber()
            << "): " << e.getMessage() << endl;
}

void XMLTreeBuilder::warning(const SAXParseException& e)
{
    cout << "Warning at (file " << e.getSystemId()
            << ", line " << e.getLineNumber()
            << ", char " << e.getColumnNumber()
            << "): " << e.getMessage() << endl;
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
}


void XMLTreeBuilder::notationDecl(const   XMLCh* const name
                                    , const XMLCh* const publicId
                                    , const XMLCh* const systemId)
{
    // Not used at this time
}



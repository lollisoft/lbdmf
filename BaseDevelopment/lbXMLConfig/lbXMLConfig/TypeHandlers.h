/*
 * Sample code for Visual C++ Developers Journal
 * Loading XML Documents in C++, by Jim Beveridge.
 * January, 2000
 *
 * This code base on sample code from IBM.
 */


#include <util/PlatformUtils.hpp>
#include <parsers/SAXParser.hpp>
#include "XMLConfig.h"
#include "XMLConfigHandlers.h"


///////////////////////////////////////////////////
//	NullHandler
///////////////////////////////////////////////////

class NullHandler : public XMLHandler
{
public:
	NullHandler() {}

	virtual XMLHandler* startElement(const   XMLCh* const    name,
		AttributeList&  attributes)
		{ return NULL; }
	virtual bool endElement()
		{ return true; }
	virtual void characters(const XMLCh* const chars, const unsigned int length)
		{ }
};

///////////////////////////////////////////////////
//	CharacterHandler
//
// To be used if data will be held between tags
// instead of in attributes. This handler is for
// string data. 
///////////////////////////////////////////////////

class CharacterHandler : public XMLHandler
{
public:
	CharacterHandler(wstring& wstr) : m_DestString(wstr) {}

	virtual XMLHandler* startElement(const   XMLCh* const    name,
		AttributeList&  attributes)
		{ return NULL; }
	virtual bool endElement()
		{ delete this; return true; }
	virtual void characters(const XMLCh* const chars, const unsigned int length)
		{ m_DestString = chars;}

	wstring& m_DestString;
};


///////////////////////////////////////////////////
//	CharacterHandler
//
// To be used if data will be held between tags
// instead of in attributes. This handler is for
// strings that get converted to double. 
///////////////////////////////////////////////////

class DoubleHandler : public XMLHandler
{
public:
	DoubleHandler(double& wstr) : m_DestDouble(wstr) {}

	virtual XMLHandler* startElement(const   XMLCh* const    name,
		AttributeList&  attributes)
		{ return NULL; }
	virtual bool endElement()
		{ delete this; return true; }
	virtual void characters(const XMLCh* const chars, const unsigned int length)
		{ wchar_t* stop; m_DestDouble = wcstod(chars, &stop);}

	double& m_DestDouble;
};


///////////////////////////////////////////////////
//	CharacterHandler
//
// To be used if data will be held between tags
// instead of in attributes. This handler is for
// strings that get converted to int. 
///////////////////////////////////////////////////

class IntHandler : public XMLHandler
{
public:
	// The ctor takes as a n argument the place
	// to put the int after it is read.
	IntHandler(int& destint) : m_DestInt(destint) {}

	virtual XMLHandler* startElement(const   XMLCh* const    name,
		AttributeList&  attributes)
		{ return NULL; }
	virtual bool endElement()
		{ delete this; return true; }
	virtual void characters(const XMLCh* const chars, const unsigned int length)
		{ m_DestInt = _wtoi(chars);}

	int& m_DestInt;
};

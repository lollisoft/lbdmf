/*...sincludes:0:*/
#include <conio.h>
#include <util/PlatformUtils.hpp>
#include <parsers/SAXParser.hpp>
#include "XMLConfig.h"
#include "XMLConfigHandlers.h"

#include <lbInterfaces.h>
//-sub-classes.h>
/*...e*/

#ifndef __XMLConfigDocument__
#define __XMLConfigDocument__

class lbConfigObject;

typedef struct _lbAttribut {
	char* name;
	char* value;
	lbConfigObject* where;
	_lbAttribut* next;
} lbAttribut, *plbAttribut;

typedef struct _lbElementList {
	lb_I_ConfigObject* obj;
	_lbElementList* next;
} lbElementList, *plbElementList;

/*...sclass lbConfigObject \58\ public lb_I_ConfigObject:0:*/
class lbConfigObject : 	public XMLHandler,
			public lb_I_ConfigObject
{
public:
	lbConfigObject() { 
		interface_used = 0;
		ocount++;
		ref = STARTREF; 
		childs = NULL; 
		deep = 0; 
		attribut_list = NULL;
		_name = NULL;
	}
	
	lbConfigObject(lbConfigObject* _parent);
	
	lbConfigObject(const lbConfigObject& c) {
		//ocount++;
		cout << "lbConfigObject::lbConfigObject(const lbConfigObject& c) called" << flush << endl;
	}
	
	virtual ~lbConfigObject();

	virtual XMLHandler* startElement(const   XMLCh* const    name,
						AttributeList&  attributes);

	virtual lbErrCodes LB_STDCALL release();

	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown);


	/**
	 * Public accessors to the data
	 */

	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object);
	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr);


	void setGeneralParseError(BOOL _parseError);
	BOOL getGeneralParseError();
	
	int  getDeep();
	void setDeep(int d);

private:
	int interface_used;
	BOOL parseError;
	int deep;
	lbConfigObject* parent;
	plbElementList childs;
	char* _name;
	
	plbAttribut attribut_list;
	
	static plbElementList all_elements;
	
	int ref;
	
	/**
	 * Helper for local unique identifers.
	 */
	 
	//lb_I_Container* uniques; 
	static int ocount;
};
/*...e*/

extern 	lbConfigObject* p_ConfigObject;

/*...sclass TopLevel \58\ public XMLHandler:0:*/
class TopLevel : public XMLHandler
{
public:
	TopLevel() { 
/*...sVERBOSE:0:*/
#ifdef VERBOSE	
		cout << "TopLevel() called" << endl;
#endif	
/*...e*/
		m_plbConfigObject = new lbConfigObject; 
	}
	virtual ~TopLevel() { 
	}
	
	virtual XMLHandler* startElement(const   XMLCh* const    name,
						AttributeList&  attributes);

	virtual void test();
	// Hardcoded for a single instance, but that
	// is easy to fix if desired.
	UAP(lbConfigObject, m_plbConfigObject)
};
/*...e*/

#endif // __XMLConfigDocument__

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
#ifndef __LB_CONFIGOBJECT__
#define __LB_CONFIGOBJECT__
/*...sclass lb_I_Attribute:0:*/
class lb_I_Attribute : public lb_I_Unknown {
protected:
	lb_I_Attribute() {}
	virtual ~lb_I_Attribute() {}
	
public:
	virtual lbErrCodes LB_STDCALL getName(char*& name) = 0;
	virtual lbErrCodes LB_STDCALL getValue(char*& value) = 0;
	virtual lbErrCodes LB_STDCALL getType(char*& type) = 0;
};
/*...e*/
class lb_I_XMLConfig;

/*...sWrapper for some DOM interfaces:0:*/
/*...e*/

/*...sclass lb_I_ConfigObject:0:*/
class lb_I_ConfigObject : public lb_I_Unknown {
/*...sprotected ctor\39\s and dtor\39\s:0:*/
protected:
	lb_I_ConfigObject() {}
	virtual ~lb_I_ConfigObject() {}
/*...e*/
public:
/*...sSimple access:8:*/
	/**
	 * Get the value for a parameter in the config object.
	 */ 
	virtual lbErrCodes LB_STDCALL getParam(const char* name, lb_I_String*& value) = 0;
/*...e*/
/*...sdoc:8:*/
	/**
	 * Access to objects from here
	 */
/*...e*/
	/*                            findNode */ 
	virtual lbErrCodes LB_STDCALL findObject(const char* name, lb_I_ConfigObject*& object) = 0;
/*...sdoc:8:*/
	/**
	 * Which parent ?
	 * In a view of search result may be more than one parent available.
	 */
/*...e*/
	virtual lbErrCodes LB_STDCALL getParent(lb_I_ConfigObject** _parent) = 0;
/*...sdoc:8:*/
	/**
	 * A config object may be only a view. So the internal childrens may
	 * not really reflect the structure of the xml file. This may only
	 * return if there is a result of found nodes with the search criteria.
	 *
	 * Sample: There may a search for all functors. So the result may be a
	 *         list of functors in that xml file. but the modules may be 
	 *         different.
	 */
/*...e*/
	virtual int LB_STDCALL getChildrenCount() = 0;

	// Simple list access functions
	virtual lbErrCodes LB_STDCALL getFirstChildren(lb_I_ConfigObject** children) = 0;
	virtual lbErrCodes LB_STDCALL getNextChildren(lb_I_ConfigObject** children) = 0;
	
/*...sdoc:8:*/
	/**
	 * Sample: Get a node, that contains an attribute with the given
	 *         name and value. As a result, that node may be used to find
	 *         the modulename, containing that node - attribute.
	 *
	 * Call sample:
	 *         object->getRelativeNodeWithAttr(
	 *                 "../FunctionName",	// expected node
	 *                 "Name",		// expected attribute
	 *                 "instanceOfLogger",	// expected value
	 *                 relNode);
	 *
	 *         Finding an instance for an object:
	 *         The result may be a list of nodes, because there may be
	 *         more than one module, implementing an instance of that
	 *         name. 
	 */
/*...e*/
/*...sbla:0:*/
/*
	virtual lbErrCodes LB_STDCALL navigateToNodeWithAttr(
				const char* relNodeName, 
				const char* attrName,
				const char* attrVal,
				bool prefered = FALSE) = 0;
*/
/*...e*/
	/**
	 * After the search for nodes like the sample above, this function
	 * navigates to a specific node in the document. That node must be
	 * available. With this function I can move to that node, containing
	 * the modulename - the real result.
	 */
/*...sbla:0:*/
/*	 
	virtual lbErrCodes LB_STDCALL navigateToNode(const char* relName) = 0;
*/				
/*...e*/
	/**
	 * Properties from this object
	 */
	virtual lbErrCodes LB_STDCALL getAttribute(const char* name, lb_I_Attribute*& attr) = 0;
	virtual lbErrCodes LB_STDCALL getAttributeValue(const char* name, char*& attr) = 0;
	virtual lbErrCodes LB_STDCALL deleteValue(char*& attr) = 0;
//	virtual lbErrCodes getDefaultImpl(char* interfacename, lb_I_ConfigObject* node, char*& implTor, char*& module) = 0;
	virtual char*      LB_STDCALL getName() = 0;

	friend class lb_I_XMLConfig;
};
/*...e*/
/*...sclass lb_I_XMLConfig:0:*/
class lb_I_XMLConfig : public lb_I_Unknown
{
protected:
	lb_I_XMLConfig() {}
	virtual ~lb_I_XMLConfig() {}
public:
	
	virtual lbErrCodes LB_STDCALL parse() = 0;
	
	/**
	 * Generic access to an xml config file. This should allow to ask
	 * for any parameter in the config file. In normal circumstances,
	 * a config object is a node (DOM_Node), but it may result also
	 * in a list of nodes. So a counter will also returned.
	 */
	 
	virtual lbErrCodes LB_STDCALL hasConfigObject(const char* cfgObjectName, int & count) = 0;
	
	/**
	 * This returns an instancepointer to the config object. The pointer
	 * must not be deleted by client. Client must call release for that.
	 */
	virtual lbErrCodes LB_STDCALL getConfigObject(lb_I_ConfigObject** cfgObj, const char* const cfgObjectName) = 0;
};
/*...e*/
/*...sclass lb_I_FunctorEntity:0:*/
/**
 * This interface will replace the recent approach of getting functors from
 * interfaces. This is because I have produced a big memory leak. The best winn
 * be to build a new repository code base.
 */


class lb_I_FunctorEntity : public lb_I_Unknown
{
protected:
	lb_I_FunctorEntity() {}
	virtual ~lb_I_FunctorEntity() {}
	
public:
	virtual void LB_STDCALL setFunctor(char* functor) = 0;
	virtual void LB_STDCALL setModule(char* module) = 0;
	virtual void LB_STDCALL setInterface(char* iface) = 0;

	virtual char* LB_STDCALL getFunctor() = 0;
	virtual char* LB_STDCALL getModule() = 0;
	virtual char* LB_STDCALL getInterface() = 0;

	friend class lb_I_InterfaceRepository;
};
/*...e*/
/*...sclass lb_I_InterfaceRepository:0:*/
class lb_I_InterfaceRepository : public lb_I_Unknown
{
protected:
        lb_I_InterfaceRepository() {}
        virtual ~lb_I_InterfaceRepository() {}
public:

	/**
	 * Set an actual search argument as interface to be searched. This resets the internal
	 * index over all interfaces to zero.
	 */
	virtual void LB_STDCALL setCurrentSearchInterface(const char* iface) = 0;
	virtual lb_I_FunctorEntity* LB_STDCALL getFirstEntity() = 0;
};
/*...e*/


#endif // __LB_CONFIGOBJECT__

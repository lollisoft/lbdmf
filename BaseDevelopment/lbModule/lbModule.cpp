//#define VERBOSE
#define LB_MODULE_DLL
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.12 $
 * $Name:  $
 * $Id: lbModule.cpp,v 1.12 2001/07/18 05:50:18 lothar Exp $
 *
 * $Log: lbModule.cpp,v $
 * Revision 1.12  2001/07/18 05:50:18  lothar
 * Seems to work now (lbDOMNode::parent - refcount must be corrected)
 *
 * Revision 1.11  2001/07/12 20:45:46  lothar
 * Test UNKNOWN_AUTO_PTR, but a declaration does not
 * work in a class, because of the explicit reference argument.
 *
 * Revision 1.10  2001/07/11 16:04:33  lothar
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.9  2001/06/23 07:18:53  lothar
 * Interface repository now works with the basic test
 *
 **************************************************************/
/*...e*/

/*...sLB_MODULE_DLL scope:0:*/
#define LB_MODULE_DLL
#include <lbmodule-module.h>
/*...e*/

/*...sincludes:0:*/
#include <windows.h>

#include <conio.h>
#include <stdio.h>
#include <malloc.h>

#include <lbInterfaces.h>
#include <lbKey.h>
#include <lbModule.h>
#include <lbXMLConfig.h>
#include <lbConfigHook.h>
/*...e*/

T_pLB_GET_UNKNOWN_INSTANCE DLL_LB_GET_UNKNOWN_INSTANCE;
/*...sclass lbModuleContainer:0:*/
class lbModuleContainer :       public lb_I_Container
{

public:
    lbModuleContainer(const lb_I_Container* c);
    lb_I_Container* operator= (const lb_I_Container* c);

public:

    lbModuleContainer();
    virtual ~lbModuleContainer();

    DECLARE_LB_UNKNOWN()

// This may be a string container

    DECLARE_LB_I_CONTAINER_IMPL()

};
/*...e*/

lb_I_Container* moduleList = NULL;
/*...sclass lbModule and implementation:0:*/
/*...sclass lbModule:0:*/
class lbModule : 
                public lb_I_Module
{
public:
        lbModule() {
                ref = STARTREF;
                loadedModules = NULL;
                internalInstanceRequest = 0;
                xml_Instance = NULL;
        }
        
        virtual ~lbModule() {
                if (ref != STARTREF) cout << "Error: Reference count mismatch" << endl;
                CL_LOG("lbModule::~lbModule() called");
        }

        DECLARE_LB_UNKNOWN()

        virtual lbErrCodes LB_STDCALL initialize();
        virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result);
        virtual lbErrCodes LB_STDCALL uninitialize();
        
        
//        void operator delete(void * del) { delete del; }
        
        virtual lbErrCodes LB_STDCALL load(char* name);
        virtual lbErrCodes LB_STDCALL getObjectInstance(const char* name, lb_I_Container*& inst);

        virtual lbErrCodes LB_STDCALL getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
        virtual lbErrCodes LB_STDCALL getDefaultImpl(char* interfacename, lb_I_ConfigObject* node, char*& implTor, char*& module);
        
protected:

        void getXMLConfigObject(lb_I_XMLConfig** inst);
        lb_I_ConfigObject* LB_STDCALL findFunctorNode(lb_I_ConfigObject** _node, const char* request);
        char* LB_STDCALL findFunctorModule(lb_I_ConfigObject** _node);
        char* LB_STDCALL findFunctorName(lb_I_ConfigObject** ___node);

        lbErrCodes LB_STDCALL makeInstance(char* functor, char* module, lb_I_Unknown** instance);
        
        int internalInstanceRequest;
        UAP(lb_I_Container, loadedModules)
        UAP(lb_I_XMLConfig, xml_Instance)
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbModule)
        ADD_INTERFACE(lb_I_Module)
END_IMPLEMENT_LB_UNKNOWN()

/*...slb_I_XMLConfig\42\ lbModule\58\\58\getXMLConfigObject\40\\41\:0:*/
typedef lbErrCodes (* LB_STDCALL T_pLB_GETXML_CONFIG_INSTANCE) (lb_I_XMLConfig** inst);
T_pLB_GETXML_CONFIG_INSTANCE DLL_LB_GETXML_CONFIG_INSTANCE;

void lbModule::getXMLConfigObject(lb_I_XMLConfig** inst) {
     
        char *libname = getenv("LBXMLLIB");
        char *ftrname = getenv("LBXMLFUNCTOR");
        char *cfgname = getenv("LBHOSTCFGFILE");

        UAP(lb_I_XMLConfig, xml_I)

        if (libname == NULL) return;
        if (ftrname == NULL) return;
        if (cfgname == NULL) return;

        if (lbLoadModule(libname, ModuleHandle) != ERR_NONE) {
                exit(1);
        }

        if ((DLL_LB_GETXML_CONFIG_INSTANCE = (T_pLB_GETXML_CONFIG_INSTANCE)
               GetProcAddress(ModuleHandle, ftrname)) == NULL)
        {
            char buf[100] = "";
            sprintf(buf, "Kann Funktion '%s' nicht finden.\n", ftrname);  
            CL_LOG(buf);
            exit(1);
        }

        lbErrCodes err = DLL_LB_GETXML_CONFIG_INSTANCE(&xml_I);

        if (xml_I == NULL) {
            CL_LOG("Konnte XML Konfigurationsinstanz nicht bekommen.\n");
            exit(1);
        }
        /**
         * Because of UNKNOWN_AUTO_PTR, here I must ensure, having one reference more than
         * it is returned by the functor. Increase it by a dummy call.
         *
         * The functor *MUST* call queryInterface it self. Using the macro, it should.
         */
         
         
        xml_I->queryInterface("lb_I_XMLConfig", (void**) inst);
}
/*...e*/

/*...slbErrCodes lbModule\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::setData(lb_I_Unknown* uk) {
        CL_LOG("lbModule::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbModule\58\\58\initialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::initialize() {
#ifdef VERBOSE
        CL_LOG("lbModule::initialize() called");
#endif
	// Should be NULL because of UNKNOWN_AUTO_PTR
        // xml_Instance = NULL;
        
        if (moduleList != NULL) {
                CL_LOG("Warning: lbModule::initialize() called more than once!");
                return ERR_NONE;
        } else {
        	lbModuleContainer* MList = new lbModuleContainer();
        	MList->queryInterface("lb_I_Container", (void**) &moduleList);
        }
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL uninitialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbModule::uninitialize() {
        if (xml_Instance != NULL) {
        #ifndef USE_UAP
        	RELEASE(xml_Instance);
        	xml_Instance = NULL;
        #endif
        }
        if (moduleList != NULL) {
	#ifndef USE_UAP
                RELEASE(moduleList);
                moduleList = NULL;
        #endif
        }
        return ERR_NONE;
}
/*...e*/
// Helpers to abstract XML structure
/*...slbModule\58\\58\findFunctorNode\40\\46\\46\\46\\41\:0:*/
/**
 * Creates a view of needed data in a lb_I_ConfigObject.
 * The node then contains only one subtree for a functor.
 * 
 * Input:       A list of functor nodes in a view of a lb_I_ConfigObject
 *              
 *              The request itself
 *
 * Output:      Only one node from the list in a new view
 */
lb_I_ConfigObject* LB_STDCALL lbModule::findFunctorNode(lb_I_ConfigObject** _node, const char* request) {
        UAP(lb_I_ConfigObject, temp_node)
        lb_I_ConfigObject* node = *_node;
        
        temp_node.setDelete(0);


        lbErrCodes err = ERR_NONE;

	/**
	 * This gets a reference for me. Autodeleted, if scope is leaved.
	 */
        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
//                lb_I_Attribute* attribute;
                
                //temp_node->getAttribute("Functor", attribute);
                
                /**
                 * This is the functor node !! It has no attributes. All parents also contains
                 * the 'FunctionName' node, where the search criteria is stored. So the following
                 * must be done here to check if this node is the one be searched:
                 *
                 * Go up one node (in the tree), get all 'FunctionName' nodes by calling
                 * temp_node->getParentNode(). As the given node itself is a view of the DOM document,
                 * a question must be issued here:
                 *
                 * Has my implementation for this view any parents?
                 */
                 
                if (temp_node == NULL) {
                        CL_LOG("temp_node is NULL!");
                        getch();
                } 
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                	/**
                	 * If I get a return value. It is a new reference.
                	 * If I get a value by reference. It is a new reference.
                	 *
                	 * If I return a pointer from any interface reference,
                	 * I *MUST* add a reference.
                	 */
                	temp_node++;
                        return *&temp_node;
                }
                
        } else CL_LOG("Get first child failed");

        while ((err = node->getNextChildren(&temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "Functor")) == 0) {
                        temp_node++;
                        return *&temp_node;
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                CL_LOG("No more childs found");
        }

	#ifdef USE_UAP
        if (temp_node != NULL) RELEASE(temp_node);
        #endif
        
        CL_LOG("Returning a NULL value");
        getch();        
        return NULL;
}
/*...e*/
/*...slbModule\58\\58\findFunctorModule\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorModule(lb_I_ConfigObject** _node) {
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *_node;

	char buf[100] = "";
	
	sprintf(buf, "findFunctorModule(%x) called", node);
	CL_LOG(buf);

        if (node == NULL) {
                CL_LOG("NULL pointer detected!");
                return "NULL";
        }
        
        CL_LOG("lbModule::findFunctorModule(...) called");
        
        if (strcmp (node->getName(), "Module") == 0) {
        	CL_LOG("Got a module");
                { 
                UAP(lb_I_ConfigObject, temp_node)
                temp_node.setDelete(0);
                	if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
/*...swork on temp_node:32:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;
                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        CL_LOG("Error while getting attribute value");
                                        CL_LOG(value);
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }               
/*...e*/
                	}
                }

                do {
                UAP(lb_I_ConfigObject, temp_node)
                temp_node.setDelete(0);
                	err = node->getNextChildren(&temp_node);
/*...swork on temp_node:24:*/
                        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
                                char* value = NULL;

                                err = temp_node->getAttributeValue("Name", value);
                                
                                if (err != ERR_NONE) {
                                        CL_LOG("Error while getting attribute value");
                                        return "NULL";
                                } else {
                                        return value;
                                }
                        }
/*...e*/
                } while (err == ERR_NONE);
        }
        else {
                UAP(lb_I_ConfigObject, temp_node)
                temp_node.setDelete(0);
                
                sprintf(buf, "Try to get parent from node %s", node->getName());
                CL_LOG(buf);
                
               	err = node->getParent(&temp_node);
                temp_node++;

		if (err == ERR_NONE) {
			char* result = findFunctorModule(&temp_node);
			
			return result;
		}
                
        }

        return "NULL";
}
/*...e*/
/*...slbModule\58\\58\findFunctorName\40\\46\\46\\46\\41\:0:*/
char* LB_STDCALL lbModule::findFunctorName(lb_I_ConfigObject** ___node) {
        /**
         * Go up one level and get the children 'FunctionName'
         */
         
        UAP(lb_I_ConfigObject, _node)
        _node.setDelete(0);
        UAP(lb_I_ConfigObject, __node)
        __node.setDelete(0);
        
        lbErrCodes err = ERR_NONE;
        lb_I_ConfigObject* node = *___node;
        char buf[100] = "";
        
        /**
         * Warning!
         * 
         * This is hard coded moving in a tree of a xml document.
         */
        
        sprintf(buf, "Get parent of node %s", node->getName());
        CL_LOG(buf);
        
        if ((err = node->getParent(&_node)) != ERR_NONE) {
                CL_LOG("Some errors have ocured while getting a parent node!");
        } 
        
        sprintf(buf, "Get parent of parent-node %s", _node->getName());
        CL_LOG(buf);
        
        if ((err = _node->getParent(&__node)) != ERR_NONE) {
                CL_LOG("Some errors have ocured while getting a parent node!");
        }
        
        if (_node != NULL) {
                int first = 1;

                
                while (err == ERR_NONE) {
                	UAP(lb_I_ConfigObject, child)
                	child.setDelete(0);
                        
                        if (first == 1) {
		                err = __node->getFirstChildren(&child);
		                
		                if (err != ERR_NONE) {
		                        CL_LOG("Error. Children expected");
		                        return NULL;
		                }
		                first = 0;
                        } else err = __node->getNextChildren(&child);
                        
                        /**
                         * Check that node...
                         */
                         
                        if (err != ERR_NONE) break; 
                 
                        if (strcmp(child->getName(), "FunctionName") == 0) {
                                /**
                                 * Have the node. Here I must get an attribute...
                                 */
                                 
                                char* value = NULL; 
                                err = child->getAttributeValue("Name", value); 
                                
                                if (err != ERR_NONE) {
                                        CL_LOG("Error while getting attribute value");
                                        return NULL;
                                } else {
                                #ifdef VERBOSE
                                        cout << "Found function name '" << value << "'" << endl;
                                        getch();
                                #endif
                                        return value;
                                }
                        }
                }
        } else {
                CL_LOG("A parent node was not found!?");
        }
        
        char *result = new char[100];
        result[0] = 0;
        return result;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getDefaultImpl\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ char\42\\38\ implTor\44\ char\42\\38\ module\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getDefaultImpl(char* interfacename, lb_I_ConfigObject* node, char*& implTor, char*& module) {
        lbErrCodes err = ERR_NONE;
        int count = 0;
	UAP(lb_I_ConfigObject, _node)
	_node = node;
	_node++; // UAP must check the pointer here too

        implTor = new char[100];
        module = new char[100];

{
	UAP(lb_I_ConfigObject, temp_node)
	
	/**
	 * Use _node instead of the interface pointer. Later UAP will be able to check
	 * if the interface pointer is valid. (Inside the -> operator)
	 */
	
/*...sget first children:8:*/
        if ((err = _node->getFirstChildren(&temp_node)) == ERR_NONE) {
                if (temp_node == NULL) {
                        CL_LOG("temp_node is NULL!");
                        getch();
                } 

                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);

			printf("getDefaultImpl() looks at %s for %s and have %s\n", temp_node->getName(), interfacename, attr);
                
                        
                        if (strcmp(interfacename, attr) == 0) {
                                printf("Get the results and return\n");
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                printf("Return ERR_NONE\n");
                                return ERR_NONE;
                        }
                        
                        temp_node->deleteValue(attr);
                        
                }
                
        } else CL_LOG("Get first child failed");
/*...e*/
}

/*...sget next children:0:*/
	err = ERR_NONE;
        while (err == ERR_NONE) {
        	UAP(lb_I_ConfigObject, temp_node)
        	
        	err = _node->getNextChildren(&temp_node);
        	
                if (temp_node == NULL) {
                        CL_LOG("temp_node is NULL!");
                        getch();
                        continue;
                } 
                
                if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
                        lb_I_Unknown* uk = NULL;
                        char* attr = NULL;
                        
                        temp_node->getAttributeValue("Interface", attr);
                        
                        if (strcmp(interfacename, attr) == 0) {
                                CL_LOG("Got the standard implementation.");
                                
                                temp_node->getAttributeValue("Module", module);
                                temp_node->getAttributeValue("Functor", implTor);
                                temp_node->deleteValue(attr);
                                
                                return ERR_NONE;
                        }
                        temp_node->deleteValue(attr);
                }
        }

/*...e*/

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getFunctors\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ lb_I_Unknown\42\\38\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbModule::getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
#ifdef bla
        lbModuleContainer* functors = new lbModuleContainer();

        UAP(lb_I_ConfigObject, temp_node)

        lbErrCodes err = ERR_NONE;
        int count = 0;

        if ((err = node->getFirstChildren(&temp_node)) == ERR_NONE) {
                lb_I_Attribute* attribute;
                
                if (temp_node == NULL) {
                        CL_LOG("temp_node is NULL!");
                        getch();
                } 
                
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;
                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                CL_LOG("Error: Could not get unknown interface!");
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                CL_LOG("Error: Don't expect a NULL pointer here!");
                                exit(1);
                        }
                        
                        char* functor = NULL;
                        char* module = NULL;
                        
                        if ((err == getDefaultImpl("lb_I_Integer", node, functor, module)) != ERR_NONE) {
                                CL_LOG("Oops!");
                        }
                        
                        
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
                
        } else CL_LOG("Get first child failed");

        while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
                if ((strcmp(temp_node->getName(), "InterfaceName")) == 0) {
                        //return temp_node;

                        lb_I_Unknown* uk = NULL;
                        
                        if (temp_node->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                                CL_LOG("Error: Could not get unknown interface!");
                                exit(1);
                        }
                        
                        if (uk == NULL) {
                                CL_LOG("Error: Don't expect a NULL pointer here!");
                                exit(1);
                        }
                        
                        //lbKey* key = new lbKey(++count);
                        
                        //functors->insert(uk, key);
                }
        }
        
        if (err == ERR_CONFIG_NO_MORE_CHILDS) {
                CL_LOG("No more childs found");
        }

        if (temp_node != NULL) RELEASE(temp_node);
#endif
	CL_LOG("lbModule::getFunctors(...) not implemented");
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\makeInstance\40\char\42\ functor\44\ char\42\ module\44\ lb_I_Unknown\42\\42\ instance\41\:0:*/
lbErrCodes LB_STDCALL lbModule::makeInstance(char* functor, char* module, lb_I_Unknown** instance) {
char msg[100] = "";
lbErrCodes err = ERR_NONE;

                        /**
                         * ModuleHandle is the result for this loaded module.
                         */
         
                        if ((err = lbLoadModule(module, ModuleHandle)) != ERR_NONE) {
                                // report error if still loaded
                                
                                // return error if loading is impossible
                        }

                        
                        if ((err = lbGetFunctionPtr(functor, ModuleHandle, (void**) &DLL_LB_GET_UNKNOWN_INSTANCE)) != ERR_NONE) {
                                CL_LOG("Error while loading a functionpointer!");
                        } else {
                                err = DLL_LB_GET_UNKNOWN_INSTANCE(instance);

                                if (err != ERR_NONE) 
                                {
                                        CL_LOG("Could not get the instance!");
                                }
                                if (instance == NULL) CL_LOG("Something goes wrong while calling functor");
                        }

        return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbModule::getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
        return ERR_NONE;
}
/*...e*/

/*...sclass lbNamedValue:0:*/
class lbNamedValue :    public lb_I_Unknown {
public:
        lbNamedValue() {
                name = strdup("");
        }
        
        virtual ~lbNamedValue() {
                delete[] name;
        }

        DECLARE_LB_UNKNOWN()

        lbErrCodes getName(char* & _name);
        lbErrCodes setName(const char* const _name);
        
        /**
         * This is a one value container. Objects in a container are copies of inserted
         * ones. This prevents manipulation of an object outside of the container.
         *
         * A modification must explicidly set into the container via the set function.
         */
        lbErrCodes setValue(lb_I_Unknown* _value);
        lbErrCodes getValue(lb_I_Unknown* & _value);
        
        char*         name;
        lb_I_Unknown* uk_value;
};
/*...e*/
/*...sclass lbElement:0:*/
class lbElement : public lb_I_Element {
private:

public:
    lbElement() { ref = STARTREF; next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
        
    lbElement(const lb_I_Element &e) { ref = STARTREF; next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    int operator == (const lb_I_Element &a) const;

    int operator == (const lb_I_KeyBase &key) const;

};
/*...e*/

/*...simplementation of lbModuleContainer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbModuleContainer)
        ADD_INTERFACE(lb_I_Container)
END_IMPLEMENT_LB_UNKNOWN()

lbModuleContainer::lbModuleContainer() {
    iteration = 0;
    ref = STARTREF;
    iterator = NULL;
    count = 0;
    container_data = NULL;
}

lbModuleContainer::~lbModuleContainer() {
}


IMPLEMENT_LB_I_CONTAINER_IMPL(lbModuleContainer)

lbErrCodes lbModuleContainer::setData(lb_I_Unknown* uk) {
        CL_LOG("lbModuleContainer::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...simplementation of lbElement:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbElement)
        ADD_INTERFACE(lb_I_Element)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_LB_ELEMENT(lbElement)

lbErrCodes lbElement::setData(lb_I_Unknown* uk) {
        CL_LOG("lbElement::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}


int LB_STDCALL lbElement::equals(const lb_I_Element* a) const {
        return 0;
}

int LB_STDCALL lbElement::equals(const lb_I_KeyBase* key) const {
        return 0;
}
/*...e*/
/*...simplementation of lbNamedValue:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbNamedValue)
// No additionally interface, because it's not used externally yet.
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbNamedValue::setData(lb_I_Unknown* uk) {
        CL_LOG("lbNamedValue::setData(...) not implemented yet");
        getch();
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbNamedValue\58\\58\setName\40\\41\:0:*/
lbErrCodes lbNamedValue::setName(const char* const _name) {
        name = strdup((_name == NULL) ? "" : _name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getName\40\\41\:0:*/
lbErrCodes lbNamedValue::getName(char* & _name) {
        _name = strdup(name);
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\setValue\40\\41\:0:*/
lbErrCodes lbNamedValue::setValue(lb_I_Unknown* _value) {
        if (uk_value != NULL) RELEASE(uk_value);
        
        // clone() set's the ref counter to 1, so a release above deletes the object.
        uk_value = _value->clone();
        return ERR_NONE;
}
/*...e*/
/*...slbNamedValue\58\\58\getValue\40\\41\:0:*/
lbErrCodes lbNamedValue::getValue(lb_I_Unknown* & _value) {
        _value = uk_value->clone();
        
        return ERR_NONE;
}
/*...e*/

lbNamedValue* namedValue = NULL;
//lb_I_Container* moduleList = NULL;

typedef struct instances_of_module {
        char* moduleName;
        int   count;
} instModule;




/*...sDocu for Module management:0:*/
/**
 * lbModule is a manager for creating instances of interfaces, regartless where
 * it came from. lbModule must be responsible for the following tasks:
 *
 * Knowing of loaded modules,
 * loading new modules,
 * releasing a module, if no more instances from there are in use.
 *
 *
 * So these functions may be declared for that issues:
 *
 * protected:
 * // Handle is managed internally
 * lbErrCodes lbModule::loadModule(const char* modulename);
 *
 * // Not the handle is needed. A module can only loaded once in a process.
 * lbErrCodes lbModule::unloadModule(const char* modulename);   
 *
 *
 * A general problem here is, that a bootstraping of some base instances must be
 * made. For the module management I need a container instance. For this problem,
 * It may be usefull to implement simple classes for that interfaces.
 *
 *
 *
 */
/*...e*/

/*...slbModule\58\\58\request\40\\46\\46\\46\\41\:0:*/
/**
 * The requestable interface simply return result of 'spoken' requests.
 * The 'spoken' request may be only one word or it may a sentence.
 *
 * A possible request may like this:
 *      get instance from interface '<parameter>'
 *
 * With this, a requestable object may be instructable by a simple script
 * language.
 */
lbErrCodes LB_STDCALL lbModule::request(const char* request, lb_I_Unknown** result) {
        lbErrCodes err = ERR_NONE;
        char buf[100] = "";
        if (moduleList == NULL) {
                CL_LOG("Error: Module manager is not initialized!");
                getch();
        }
        
        if (xml_Instance == NULL) {
                getXMLConfigObject(&xml_Instance);
        }

	char* functorName = NULL;

        UAP(lb_I_ConfigObject, impl)
        impl.setDelete(0);

CL_LOG("Begin dispatch the request");
/*...sget my unknown interface:8:*/
        if (strcmp(request, "instance/XMLConfig") == 0) {
                //xml_Instance->hasConfigObject("Dat/object");
                //result = (lb_I_Unknown*) xml_Instance;
                
                CL_LOG("Query unknown interface of xml_Interface!");
                xml_Instance->queryInterface("lb_I_Unknown", (void**) result);
                
                return ERR_NONE;
        }
/*...e*/
        else {
/*...sget any interface:8:*/
/*...sdoc:8:*/
        /**
         * Here should be created an unknown object. The mapping of a real
         * instance is done in the xml file instead of if blocks.
         */
/*...e*/
                char* node = "#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor/InterfaceName";
                lb_I_ConfigObject* config = NULL;
                int count = 0;
                                        // request is a functor
/*...sdoc:8:*/
                /**
                 * Get the nodes that match the path in 'node'. It may simple to change this
                 * to get all 'InterfaceName' entries. It should work the same way.
                 *
                 * 1. It is better to let this as it is. In the new XML file, an interfacename
                 * is a chield of the functor. I must find the functor's that implements the
                 * requiered interface.
                 *
                 * findFunctorNode, implemented as now, has a bug: It returns every times the
                 * first element.
                 * It should be an iterator to get all the elements found by hasConfigobject.
                 * Leaving the current technique, enables the searchability for functors dirctly
                 * and also enables the search for interfaces.
                 *
                 * The only thing, that must not appear, is an interfacename is the same as a
                 * functor !
                 */
/*...e*/
                if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
/*...svars:32:*/
			char* moduleName = NULL;
                        lb_I_ConfigObject* implementations = NULL;
                        char* value = NULL;
/*...e*/
/*...sdoc:8:*/
                        /**
                         * Get the list of found objects as a list.
                         * The result is a view of notes in a max deep
                         * of one level.
                         */
/*...e*/
                        xml_Instance->getConfigObject(config, node);
/*...sdoc:8:*/
                        /**
                         * Check, which element implements the requested interface.
                         * If there are more than one for an interface, get the first.
                         * Later, get the default.
                         */
/*...e*/
			CL_LOG("Find the needed node");
/*...sfind the needed node:32:*/
                        if ((err = config->getFirstChildren(&impl)) == ERR_NONE) {
                                char buf[100] = "";
                                CL_LOG("Get an attribute of impl");
                                err = impl->getAttributeValue("Name", value);

                                if (strcmp(value, request) == 0) {
                                        //impl is the needed object     
                                } else {
/*...ssuche weiter:72:*/
                                        int stop = 1;
                                        while (stop == 1) {
						CL_LOG("RELEASE(impl)");
                                        	RELEASE(impl);
                                        	CL_LOG("RELEASED");
                                        	
                                                if ((err = config->getNextChildren(&impl)) != ERR_NONE) {
                                                        stop = 0;
                                                        break;
                                                }


                                                if (value != NULL) 
                                                {
                                                        char buf[100] = "";
                                                        CL_LOG("Delete a value using impl");
                                                        impl->deleteValue(value);
                                                        CL_LOG("Deleted");
                                                        value = NULL;
                                                }
                                                
                                                err = impl->getAttributeValue("Name", value);
                                                
                                                if (strcmp(value, request) == 0) {
                                                        stop = 0;
                                                }
                                        }
/*...e*/
                                }
                        }
/*...e*/
/*...sreturn error if value \61\ NULL:32:*/
                        if (value == NULL) {
                                CL_LOG("return ERR_MODULE_NO_INTERFACE");
                                return ERR_MODULE_NO_INTERFACE;
                        }
/*...e*/
/*...sreturn error \40\no implementation for that interface\41\:32:*/
                        if (strcmp(request, value) != 0) {
                                CL_LOG("Error: There is no implementation for wanted interface");
                                
                                if (value != NULL) {
                                        impl->deleteValue(value);
                                }
                                return ERR_MODULE_NO_INTERFACE;
                        }
/*...e*/
                        char buf[100] = "";
/*...sclean up \63\\63\\63\:32:*/
                        if (value != NULL) {
				CL_LOG("Delete a value using impl");
                                impl->deleteValue(value);
                        }
/*...e*/
/*...sfind up names:32:*/
                        CL_LOG("Find up module name");
                        moduleName = findFunctorModule(&impl);
			CL_LOG("Find up functor name");
                        functorName = findFunctorName(&impl);
			CL_LOG("Found any");
/*...e*/
/*...sclean up \63\\63\\63\:32:*/
                        if (value != NULL) {
                                impl->deleteValue(value);
                        }
/*...e*/
/*...sinternal management of loaded modules:32:*/
/*...svars:64:*/
                                // Set the value of the object
                        
                                UAP(lb_I_String, string)
                                UAP(lb_I_KeyBase, stringKey)

                                /**
                                 * Get a default implementation - needed here to avoid recursive
                                 * calls of request.
                                 */

                                UAP(lb_I_Unknown, key)

                                char* defaultFunctor = NULL;
                                char* defaultModule = NULL;
/*...e*/
                                char* node = "#document/dtdHostCfgDoc/StandardFunctor";
                                lb_I_ConfigObject* i_config = NULL;

                                if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
                                        xml_Instance->getConfigObject(i_config, node);

                                        getDefaultImpl("lb_I_String", i_config, defaultFunctor, defaultModule);
                                        makeInstance(defaultFunctor, defaultModule, &key);
                                
/*...sprepare for string:72:*/
                                        if (key == NULL) {
                                                CL_LOG("Error: Key is NULL!");
                                                getch();
                                        }
                                
                                        if (key->queryInterface("lb_I_String", (void**) & string) != ERR_NONE) {
                                                CL_LOG("Error: Unknown has not the requested interface!");
                                                getch();
                                        }
                                
                                        if (string == NULL) {
                                                CL_LOG("Error: NULL pointer detected at stringKey!");
                                                getch();
                                        }
/*...e*/
/*...sprepare for stringKey:72:*/
                                        if (key == NULL) {
                                                CL_LOG("Error: Key is NULL!");
                                                getch();
                                        }
                                
                                        if (key->queryInterface("lb_I_KeyBase", (void**) & stringKey) != ERR_NONE) {
                                                CL_LOG("Error: Unknown has not the requested interface!");
                                                getch();
                                        }
                                
                                        if (stringKey == NULL) {
                                                CL_LOG("Error: NULL pointer detected at stringKey!");
                                                getch();
                                        }
/*...e*/
                                
                                        string->setData(moduleName);
                                
/*...sdoc:72:*/
                        /**
                         * Get element in the loaded modules list. It returns the existing instances
                         * of the module. If the result is a NULL pointer, there is no loaded module.
                         */
/*...e*/
                        
                        		UAP(lb_I_Unknown, instances)
                        		
                                        instances = moduleList->getElement(&stringKey);
                                        if (instances == NULL) {
/*...sCreate the new module entry:80:*/
                                        	/**
                                        	 * This module is loaded the first time. Make an entry in the
                                        	 * moduleList with the key(modulename) and as an element an
                                        	 * instance of a container.
                                        	 */
                                        	 
                                        	UAP(lb_I_Unknown, c)

                                        	lbModuleContainer* _instanceList = new lbModuleContainer();
                                        	
                                        	if (_instanceList->queryInterface("lb_I_Container", (void**) &c) != ERR_NONE) {
                                        		CL_LOG("Error: Could not get reference to interface lb_I_Container!");
                                        	} else {
                                        		/**
                                        		 * Note: All input is cloned. 
                                        		 * Use getElement(stringKey) for manipulation.
                                        		 */
                                        		moduleList->insert(&c, &stringKey);
                                        		
                                        		// Cleanup
                                        	}
/*...e*/
                                        }
                                        
                                        instances = moduleList->getElement(&stringKey);
                                        
                                        if (instances == NULL) {
                                        	CL_LOG("Error: After inserting the element, it's not possible to manipulate it");
                                        } else {
                                        	lb_I_Container* instanceList = NULL;
                                        	if (instances->queryInterface("lb_I_Container", (void**) &instanceList) != ERR_NONE) {
                                        		CL_LOG("Error: The element in the module container is not a container!");
                                        	} else {
/*...sdocu for avoiding double deletion of the same pointer:88:*/
      		/**
      		 * Store for each instance one enty in the list with the 
   		 * following contents:
    		 *
   		 * The interface name,
 		 * the functor name, 
       		 * the reference count, 
       		 * the pointer to the instance.
		 *
  		 * The key for each of this object will be the pointer to
   		 * the instance.
  		 *
      		 * If instance->release() is called. It would first check if the
    		 * object was deleted before. This checks that it does not delete
   		 * an undefined pointer. This leads in much data overhead about the
   		 * deleted instances.
   		 *
   		 * To avoid this, I will suggest this:
   		 * 
   		 * A macro like INSTANCE_REF(interfacename, variablename) may be used instead of
   		 * directly declare the reference pointer. (A normal pointer, not a reference).
   		 *
   		 * The macro can use an inatance on the stack of a specific class that tells to the
   		 * module management, when the used reference is out of scope.
   		 *
   		 */
/*...e*/
                                        	}
                                        }

/*...sclean up:72:*/
                                        RELEASE(i_config);
                                        RELEASE(stringKey);
                                        RELEASE(key);
                                        
                                        impl->deleteValue(defaultFunctor);
                                        impl->deleteValue(defaultModule);
/*...e*/
                                }

/*...e*/
/*...smake the hells needed instance:32:*/
                        makeInstance(functorName, moduleName, result);
/*...e*/

/*...sclean up:32:*/
                        if (moduleName != NULL) impl->deleteValue(moduleName);
                        if (config != NULL) RELEASE(config);
/*...e*/
                } else {
                        cout << "Something goes wrong!" << endl;
                        cout << "xml_Instance->hasConfigObject() returns <> ERR_NONE!" << endl;
                }
                
                
/*...e*/
        }
CL_LOG("End dispatch the request");
        RELEASE(xml_Instance);
        xml_Instance = NULL;


        if (functorName != NULL) impl->deleteValue(functorName);

        return ERR_NONE;
}
/*...e*/

IMPLEMENT_FUNCTOR(getlb_ModuleInstance, lbModule)

/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
        UAP(lb_I_XMLConfig, xml_Instance)

        getXMLConfigObject(&xml_Instance);
        
        cout << "lbModule::load(char* name) called" << endl;

        if (xml_Instance != NULL) {
            if (xml_Instance->parse() != ERR_NONE) {
                CL_LOG("Error while parsing XML document\n");
            }
        }
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getObjectInstance\40\const char\42\ name\44\ lb_I_Container\42\\38\ inst\41\:0:*/
lbErrCodes lbModule::getObjectInstance(const char* name, lb_I_Container*& inst) {
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance\40\lb_I_Unknown \42\ inst\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst) {
        RELEASE(inst);
        return ERR_NONE;
}
/*...e*/

/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";
        
        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        if (situation) {
                                CL_LOG("DLL statically loaded.\n");
                        }
                        else {
                                CL_LOG("DLL dynamically loaded.\n");
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        CL_LOG("New thread starting.\n");
                        break;
                case DLL_PROCESS_DETACH:                        
                        if (situation)
                        {
                                CL_LOG("DLL released by system.\n");
                        }
                        else
                        {
                                CL_LOG("DLL released by program.\n");
                        }
                        break;
                case DLL_THREAD_DETACH:
                        CL_LOG("Thread terminating.\n");
                derault:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/

//#define VERBOSE
#define LB_MODULE_DLL

/*...sincludes:0:*/
#include <windows.h>

#include <conio.h>
#include <stdio.h>

#include <lbInterfaces.h>
#include <lbKey.h>
#include <lbModule.h>
#include <lbXMLConfig.h>
#include <lbConfigHook.h>
/*...e*/

/*...slb_I_XMLConfig\42\ getXMLConfigObject\40\\41\:0:*/
lb_I_XMLConfig* getXMLConfigObject() {
        typedef lbErrCodes (__cdecl * T_pLB_GETXML_CONFIG_INSTANCE) (lb_I_XMLConfig*&);
        T_pLB_GETXML_CONFIG_INSTANCE DLL_LB_GETXML_CONFIG_INSTANCE;
        
        char *libname = getenv("LBXMLLIB");
        char *ftrname = getenv("LBXMLFUNCTOR");
        char *cfgname = getenv("LBHOSTCFGFILE");
        lb_I_XMLConfig* xml_Instance = NULL;

        if (libname == NULL) return NULL;
        if (ftrname == NULL) return NULL;
        if (cfgname == NULL) return NULL;

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

        lbErrCodes err = DLL_LB_GETXML_CONFIG_INSTANCE(xml_Instance);

        if (xml_Instance == NULL) {
            CL_LOG("Konnte XML Konfigurationsinstanz nicht bekommen.\n");
            exit(1);
        }

        return xml_Instance;
}
/*...e*/

/*...sclass lb_gcManager:0:*/
class lb_gcManager : public lb_I_gcManager {
public:
        lb_gcManager();
        virtual ~lb_gcManager();
        
        lbErrCodes toTrash(lb_I_Unknown* inst);
};

lb_gcManager::lb_gcManager() {
}

lb_gcManager::~lb_gcManager() {
}

lbErrCodes lb_gcManager::toTrash(lb_I_Unknown* inst) {
        delete inst;
        
        return ERR_NONE;
}
/*...e*/

T_pLB_GET_UNKNOWN_INSTANCE DLL_LB_GET_UNKNOWN_INSTANCE;

lb_gcManager gcManager;

/*...sclass lbModuleContainer:0:*/
class lbModuleContainer : 	public lb_I_Container
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
        }
        
        virtual ~lbModule() {
                if (ref != STARTREF) cout << "Error: Reference count mismatch" << endl;
        }

	DECLARE_LB_UNKNOWN()

        virtual lbErrCodes initialize();
        virtual lbErrCodes request(const char* request, lb_I_Unknown*& result);
        virtual lbErrCodes uninitialize();
        
        
//        void operator delete(void * del) { delete del; }
        
        virtual lbErrCodes load(char* name);
        virtual lbErrCodes getObjectInstance(const char* name, lb_I_Container*& inst);

	virtual lbErrCodes getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
	virtual lbErrCodes getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk);
	virtual lbErrCodes getDefaultImpl(char* interfacename, lb_I_ConfigObject* node, char*& implTor, char*& module);
        
protected:

	lb_I_ConfigObject* findFunctorNode(lb_I_ConfigObject* node, const char* request);
	char* findFunctorModule(lb_I_ConfigObject* node);
	char* findFunctorName(lb_I_ConfigObject* node);

	lbErrCodes makeInstance(char* functor, char* module, lb_I_Unknown*& instance);
	
	lb_I_Container* loadedModules;
	int internalInstanceRequest;
	lb_I_XMLConfig* xml_Instance;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbModule)
	ADD_INTERFACE(lb_I_Module)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes lbModule\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes lbModule::setData(lb_I_Unknown* uk) {
	CL_LOG("lbModule::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\initialize\40\\41\:0:*/
lbErrCodes lbModule::initialize() {
#ifdef VERBOSE
	CL_LOG("lbModule::initialize() called");
#endif
	xml_Instance = NULL;
	moduleList = new lbModuleContainer();
        return ERR_NONE;
}
/*...e*/
// Helpers to abstract XML structure
/*...slbModule\58\\58\findFunctorNode\40\\46\\46\\46\\41\:0:*/
/**
 * Creates a view of needed data in a lb_I_ConfigObject.
 * The node then contains only one subtree for a functor.
 * 
 * Input:	A list of functor nodes in a view of a lb_I_ConfigObject
 *		
 *		The request itself
 *
 * Output:	Only one node from the list in a new view
 */
lb_I_ConfigObject* lbModule::findFunctorNode(lb_I_ConfigObject* node, const char* request) {
	lb_I_ConfigObject* temp_node = NULL;
	lbErrCodes err = ERR_NONE;
	if ((err = node->getFirstChildren(temp_node)) == ERR_NONE) {
		lb_I_Attribute* attribute;
		
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
#ifdef bla			
/*...sWith this test the result in parent\39\s child\39\s is ok:0:*/
			
lb_I_ConfigObject* _node = NULL;
lbErrCodes err = ERR_NONE;

if ((err = temp_node->getParent(_node)) != ERR_NONE) {
        CL_LOG("Some errors have ocured while getting a parent node!");
}			
	if (_node != NULL) {
		lb_I_ConfigObject* __node = NULL;
#ifdef VERBOSE
		CL_LOG("DEBUG PAUSE 1");
#endif		

		err = _node->getFirstChildren(__node);
#ifdef VERBOSE		
		CL_LOG("DEBUG PAUSE 2");
#endif		
		
		if (err != ERR_NONE) {
			CL_LOG("Error. Children expected");
			
			return NULL;
		}
#ifdef VERBOSE
		CL_LOG("No error found!");
#endif
}
/*...e*/
#endif			
			return temp_node;
		}
		
	} else CL_LOG("Get first child failed");

	while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
		if ((strcmp(temp_node->getName(), "Functor")) == 0) {
			return temp_node;
		}
	}
	
	if (err == ERR_CONFIG_NO_MORE_CHILDS) {
		CL_LOG("No more childs found");
	}

	if (temp_node != NULL) temp_node->release();
	
	CL_LOG("Returning a NULL value");
	getch();	
	return NULL;
}
/*...e*/
/*...slbModule\58\\58\findFunctorModule\40\\46\\46\\46\\41\:0:*/
char* lbModule::findFunctorModule(lb_I_ConfigObject* node) {
	lbErrCodes err = ERR_NONE;
	lb_I_ConfigObject* temp_node = node;

	if (node == NULL) {
		CL_LOG("NULL pointer detected!");
		return "NULL";
	}

	if (strcmp (node->getName(), "Module") == 0) {
		
		if ((err = node->getFirstChildren(temp_node)) == ERR_NONE) {
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
		}

		while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
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
		}
	}
	else {
		while ((err = node->getParent(temp_node)) == ERR_NONE) {
			if (temp_node == NULL) {
				CL_LOG("Error: No parent");
				getch();
			}
			return findFunctorModule(temp_node);
		} 
	}

	return "NULL";
}
/*...e*/
/*...slbModule\58\\58\findFunctorName\40\\46\\46\\46\\41\:0:*/
char* lbModule::findFunctorName(lb_I_ConfigObject* node) {
	/**
	 * Go up one level and get the children 'FunctionName'
	 */
	 
	lb_I_ConfigObject* _node = NULL;
	lbErrCodes err = ERR_NONE;
	
	if ((err = node->getParent(_node)) != ERR_NONE) {
		CL_LOG("Some errors have ocured while getting a parent node!");
	} 
	
	if (_node != NULL) {
		lb_I_ConfigObject* __node = NULL;

		err = _node->getFirstChildren(__node);
		
		if (err != ERR_NONE) {
			CL_LOG("Error. Children expected");
			return NULL;
		}
		while (err == ERR_NONE) {

			/**
			 * Check that node...
			 */
		 
			if (strcmp(__node->getName(), "FunctionName") == 0) {
				/**
				 * Have the node. Here I must get an attribute...
				 */
				 
				char* value = NULL; 
				err = __node->getAttributeValue("Name", value); 
				
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
		
			err = _node->getNextChildren(__node);
		
			//err = ERR_CONFIG_NO_MORE_CHILDS;
		}
	} else {
		CL_LOG("A parent node was not found!?");
	}
	
	return "NULL";
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getDefaultImpl\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ char\42\\38\ implTor\44\ char\42\\38\ module\41\:0:*/
lbErrCodes lbModule::getDefaultImpl(char* interfacename, lb_I_ConfigObject* node, char*& implTor, char*& module) {
//	lbModuleContainer* functors = new lbModuleContainer();
	lb_I_ConfigObject* temp_node = NULL;
	lbErrCodes err = ERR_NONE;
	int count = 0;

	implTor = new char[100];
	module = new char[100];


/*...sget first children:0:*/
	if ((err = node->getFirstChildren(temp_node)) == ERR_NONE) {
		if (temp_node == NULL) {
			CL_LOG("temp_node is NULL!");
			getch();
		} 
		
		if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
			lb_I_Unknown* uk = NULL;
			char* attr = NULL;
			
			temp_node->getAttributeValue("Interface", attr);
			
			if (strcmp(interfacename, attr) == 0) {
				CL_LOG("Got the standard implementation.");
				
				temp_node->getAttributeValue("Module", module);
				temp_node->getAttributeValue("Functor", implTor);
			}
			
		}
	} else CL_LOG("Get first child failed");
/*...e*/

/*...sget next children:0:*/
	while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
		if (temp_node == NULL) {
			CL_LOG("temp_node is NULL!");
			getch();
		} 
		
		if ((strcmp(temp_node->getName(), "StandardFunctor")) == 0) {
			lb_I_Unknown* uk = NULL;
			char* attr = NULL;
			
			temp_node->getAttributeValue("Interface", attr);
			
			if (strcmp(interfacename, attr) == 0) {
				CL_LOG("Got the standard implementation.");
				
				temp_node->getAttributeValue("Module", module);
				temp_node->getAttributeValue("Functor", implTor);
			}
			
		}
	}

/*...e*/

#ifdef VERBOSE
CL_LOG("Really leaved next children!");
getch();
#endif
	
	if (err == ERR_CONFIG_NO_MORE_CHILDS) {
		CL_LOG("No more childs found");
	}
#ifdef VERBOSE
CL_LOG("Done lbModule::getDefaultImpl(...)");
getch();
#endif
	if (temp_node != NULL) temp_node->release();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getFunctors\40\char\42\ interfacename\44\ lb_I_ConfigObject\42\ node\44\ lb_I_Unknown\42\\38\ uk\41\:0:*/
lbErrCodes lbModule::getFunctors(char* interfacename, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
	lbModuleContainer* functors = new lbModuleContainer();
	lb_I_ConfigObject* temp_node = NULL;
	lbErrCodes err = ERR_NONE;
	int count = 0;

	if ((err = node->getFirstChildren(temp_node)) == ERR_NONE) {
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

	if (temp_node != NULL) temp_node->release();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\makeInstance\40\char\42\ functor\44\ char\42\ module\44\ lb_I_Unknown\42\\38\ instance\41\:0:*/
lbErrCodes lbModule::makeInstance(char* functor, char* module, lb_I_Unknown*& instance) {
char msg[100] = "";
lbErrCodes err = ERR_NONE;

#ifdef VERBOSE
sprintf(msg, "Begin loading module %s", module);
CL_LOG(msg);
getch();		
#endif
			/**
			 * ModuleHandle is the result for this loaded module.
			 */
	 
			if ((err = lbLoadModule(module, ModuleHandle)) != ERR_NONE) {
				// report error if still loaded
				
				// return error if loading is impossible
			}
#ifdef VERBOSE
CL_LOG("End loading module");
getch();
#endif		

#ifdef VERBOSE
			msg[0] = 0;
			sprintf(msg, "Create instance with functor '%s'.", functor);
			CL_LOG(msg);
#endif
			
			if ((err = lbGetFunctionPtr(functor, ModuleHandle, (void**) &DLL_LB_GET_UNKNOWN_INSTANCE)) != ERR_NONE) {
				CL_LOG("Error while loading a functionpointer!");
			} else {
				err = DLL_LB_GET_UNKNOWN_INSTANCE(instance);
				if (err == ERR_NONE) 
				{
				#ifdef VERBOSE
					CL_LOG("Got the requested instance!");
				#endif
				}
				else
				{
					CL_LOG("Could not get the instance!");
				}
				
				if (instance != NULL) {
				#ifdef VERBOSE
					CL_LOG("Instancepointer is available");
				#endif
				}
				
			}

	return ERR_NONE;
}
/*...e*/

lbErrCodes lbModule::getInstance(char* functorname, lb_I_ConfigObject* node, lb_I_Unknown*& uk) {
	return ERR_NONE;
}
/*...e*/

/*...sclass lbNamedValue:0:*/
class lbNamedValue :	public lb_I_Unknown {
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
    lbElement() { next = NULL; data = NULL; key = NULL; }
    virtual ~lbElement();
	
    lbElement(const lb_I_Element &e) { next = e.getNext(); }

    DECLARE_LB_UNKNOWN()

    DECLARE_LB_ELEMENT(lbElement)

    lb_I_Unknown* getObject() const;

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
    ref = 0;
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
	if (uk_value != NULL) uk_value->release();
	
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
 *	get instance from interface '<parameter>'
 *
 * With this, a requestable object may be instructable by a simple script
 * language.
 */
lbErrCodes lbModule::request(const char* request, lb_I_Unknown*& result) {
        //lb_I_XMLConfig* xml_Instance = NULL;
        lbErrCodes err = ERR_NONE;
        char buf[100] = "";

	if (moduleList == NULL) {
		CL_LOG("Error: Module manager is not initialized!");
		getch();
	}
	
	sprintf(buf, "Request interface %s\n", request);
	CL_LOG(buf);
	
        if (xml_Instance == NULL) xml_Instance = getXMLConfigObject();
        
/*...sget my unknown interface:8:*/
        if (strcmp(request, "instance/XMLConfig") == 0) {
                //xml_Instance->hasConfigObject("Dat/object");
                //result = (lb_I_Unknown*) xml_Instance;
                
                xml_Instance->queryInterface("lb_I_Unknown", (void**) &result);
                
                return ERR_NONE;
        }
/*...e*/
	else {
/*...sget any interface:8:*/
	/**
	 * Here should be created an unknown object. The mapping of a real
	 * instance is done in the xml file instead of if blocks.
	 */
	
		char* node = "#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor";
		lb_I_ConfigObject* config = NULL;
		int count = 0;
					// request is a functor
		if (internalInstanceRequest == 1) {
			CL_LOG("xml_Instance->hasConfigObject(node, count):");
		}
		
		if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
			if (internalInstanceRequest == 1) {
				CL_LOG("xml_Instance->getConfigObject(config, node):");
			}
			/**
			 * Get the list of found objects as a list.
			 * The result is a view of notes in a max deep
			 * of one level.
			 */
/*...sVERBOSE:32:*/
#ifdef VERBOSE
CL_LOG("Try to get the config object");			
#endif
/*...e*/
			xml_Instance->getConfigObject(config, node);
/*...sVERBOSE:32:*/
#ifdef VERBOSE
CL_LOG("Got a config object (will the next crash ?)");
#endif
/*...e*/
			if (internalInstanceRequest == 1) {
				CL_LOG("findFunctorNode(config, request):");
			}
			
			lb_I_ConfigObject* functorNode = findFunctorNode(config, request);
/*...sVERBOSE:32:*/
#ifdef VERBOSE
CL_LOG("Not crashed!");
#endif			
/*...e*/
			if (internalInstanceRequest == 1) {
				CL_LOG("findFunctorModule(functorNode):");
			}
			
			if (functorNode == NULL) {
				cout << "Couldn't find the desired functor (nullpointer)!" << endl;
				
			}
getch();
			char* moduleName = findFunctorModule(functorNode);
			if (internalInstanceRequest == 1) {
				CL_LOG("findFunctorName(functorNode):");
			}
			cout << "Search for this name '" << request << "'" << endl;
			char* functorName = findFunctorName(functorNode);

			CL_LOG("Got this functor name:");
			CL_LOG(functorName);
getch();
/*...sdoc:32:*/
			/**
			 * Now I should have all my information, create the instance.
			 *
			 * The basic question here is: What must be stored as information
			 * for a newly created interface.
			 *
			 * The Module, where it is loaded from, the interface itself ?
			 * 
			 * How to unload ?
			 *
			 * Currently all instances, used, are unloaded (released) by their
			 * user. The user only is responsible for releasing it's instances.
			 *
			 * The lb_I_Unknown interface is responsible for informing the module -
			 * manager, that it's instance will be released.
			 *
			 * How to count used instances ?
			 */
			 
			/** 
			 * Check, if module is already loaded. Therefore it is necessary to make
			 * a key from the given string. My current thinking about the key interface
			 * is as follows: I should not create interfaces with functionality, wich
			 * would be availabe in other interfaces. A key is responsible for comparsion,
			 * but not to manipulate it's value. The type of the value is unknown.
			 *
			 * A better way is to use base types like integer and string interfaces to
			 * manipulate or set a value and then get the key interface of it.
			 * Better - put the value directly.
			 */
/*...e*/
			 
#ifdef bla			
/*...sbla:8:*/
			/**
			 * If a request want's to get any of these interface instances, I should not try
			 * to call recursive my own function.
			 * 
			 * lb_I_String, lb_I_Container
			 *
			 * To manage loaded modules and instances I should use internal implementations.
			 * 
			 * So, use a struct containing the module name and a count of instances,
			 * use a instance pointer map to the containing module, to be able to decrease
			 * the correct module instance counter
			 */
			if (internalInstanceRequest == 1) {
				CL_LOG("Did I have am instance of my string?");
			}
			 			 
			if (internalInstanceRequest == 0) { 
				internalInstanceRequest = 1;
				CL_LOG("------------------- Begin recursive call! ----------------------");
				if ((err = this->request("lb_I_String", key)) != ERR_NONE) {
					CL_LOG("Error: Could not get a lb_I_String instance!");
					getch();
				}
				CL_LOG("-------------------- End recursive call! -----------------------");
				internalInstanceRequest = 0;
			}
/*...e*/
#endif bla
		
/*...sinternal recursive call \63\:32:*/
#ifdef bla
			if (internalInstanceRequest == 0) {
#endif
				// Set the value of the object
			
				CL_LOG("Try to get the string instance");
				getch();
			
				lb_I_String* stringKey = NULL;

				/**
				 * Get a default implementation - needed here to avoid recursive
				 * calls of request.
				 */

				lb_I_Unknown* key = NULL;
				char* defaultFunctor = NULL;
				char* defaultModule = NULL;
			

				char* node = "#document/dtdHostCfgDoc/StandardFunctor";
				lb_I_ConfigObject* config = NULL;

				if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
					xml_Instance->getConfigObject(config, node);

					getDefaultImpl("lb_I_String", config, defaultFunctor, defaultModule);
					CL_LOG("Called getDefaultImpl(...)");
					getch();
					makeInstance(defaultFunctor, defaultModule, key);
					CL_LOG("Made an instance ?");
					getch();
				
					if (key == NULL) {
						CL_LOG("Error: Key is NULL!");
						getch();
					}
				
					if (key->queryInterface("lb_I_String", (void**) & stringKey) != ERR_NONE) {
						CL_LOG("Error: Unknown has not the requested interface!");
						getch();
					}
				
					CL_LOG("Try to set the c string into lb_I_String instance");
					getch();
				
					if (stringKey == NULL) {
						CL_LOG("Error: NULL pointer detected at stringKey!");
						getch();
					}
				
					stringKey->setData(moduleName);
				
					CL_LOG("Have set data in the string :-)");
					getch();
				
/*...sdoc:64:*/
			/**
			 * Get element in the loaded modules list. It returns the existing instances
			 * of the module. If the result is a NULL pointer, there is no loaded module.
			 */
/*...e*/
			
					lb_I_Unknown* instances = moduleList->getElement(stringKey);
					if (instances == NULL) {
						CL_LOG("Module is loaded at first time!");
						getch();
					}
					
					CL_LOG("Got the element");
					getch();
				}

#ifdef bla
			} else {
				CL_LOG("Skipping code in recursive mode");
			}		
#endif
/*...e*/
			
			makeInstance(functorName, moduleName, result);
/*...sbla:8:*/
#ifdef bla
char msg[100] = "";
sprintf(msg, "Begin loading module %s", moduleName);
CL_LOG(msg);
getch();		
			/**
			 * ModuleHandle is the result for this loaded module.
			 */
	 
			if ((err = lbLoadModule(moduleName, ModuleHandle)) != ERR_NONE) {
				// report error if still loaded
				
				// return error if loading is impossible
			}
CL_LOG("End loading module");
getch();		

			lbNamedValue* nv = new lbNamedValue;
			
			msg[0] = 0;
			sprintf(msg, "Create instance with functor '%s'.", functorName);
			CL_LOG(msg);
			
			if ((err = lbGetFunctionPtr(functorName, ModuleHandle, (void**) &DLL_LB_GET_UNKNOWN_INSTANCE)) != ERR_NONE) {
				CL_LOG("Error while loading a functionpointer!");
			} else {
				err = DLL_LB_GET_UNKNOWN_INSTANCE(result);
				if (err == ERR_NONE) 
				{
					CL_LOG("Got the requested instance!");
				}
				else
				{
					CL_LOG("Could not get the instance!");
				}
				
				if (result != NULL) {
					CL_LOG("Instancepointer is available");
				}
				
				getch();
			}

#endif
/*...e*/
		} else {
			cout << "Something goes wrong!" << endl;
			cout << "xml_Instance->hasConfigObject() returns <> ERR_NONE!" << endl;
		}
		
		
/*...e*/
	}
        
        // Possibly wrong here
        //xml_Instance->release();

        return ERR_NONE;
}
/*...e*/

lbErrCodes lbModule::uninitialize() {
	if (xml_Instance != NULL) xml_Instance->release();
        return ERR_NONE;
}


/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
        lb_I_XMLConfig* xml_Instance = NULL;

        xml_Instance = getXMLConfigObject();
        
        cout << "lbModule::load(char* name) called" << endl;

        if (xml_Instance) {
            if (xml_Instance->parse() != ERR_NONE) {
                CL_LOG("Error while parsing XML document\n");
            }
        }
        
	xml_Instance->release();        
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getObjectInstance\40\const char\42\ name\44\ lb_I_Container\42\\38\ inst\41\:0:*/
lbErrCodes lbModule::getObjectInstance(const char* name, lb_I_Container*& inst) {
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes DLLEXPORT LB_STDCALL getlb_ModuleInstance\40\lb_I_Module\42\\38\ inst\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL getlb_ModuleInstance(lb_I_Module*& inst) {
        inst = (lb_I_Module*) new lbModule();
        //inst->release();
        //inst = NULL;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance\40\lb_I_Unknown \42\ inst\41\:0:*/
lbErrCodes DLLEXPORT LB_STDCALL lb_releaseInstance(lb_I_Unknown * inst) {
        delete inst;
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

#define LB_MODULE_DLL

/*...sincludes:0:*/
#include <windows.h>

#include <conio.h>
#include <stdio.h>

#include <lbInterfaces.h>
#include <lbModule.h>
#include <lbXMLConfig.h>
#include <lbConfigHook.h>
#include <lbKey.h>
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
            printf("Kann Funktion '%s' nicht finden.\n", ftrname);  exit(1);
        }

        lbErrCodes err = DLL_LB_GETXML_CONFIG_INSTANCE(xml_Instance);

        if (xml_Instance == NULL) {
            printf("Konnte XML Konfigurationsinstanz nicht bekommen.\n");  exit(1);
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
/*...sclass lbModule and implementation:0:*/
/*...sclass lbModule:0:*/
class lbModule : 
                public lb_I_Module
{
public:
        lbModule() {
                ref = STARTREF;
                loadedModules = NULL;
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
        
protected:

	lb_I_ConfigObject* findFunctorNode(lb_I_ConfigObject* node, const char* request);
	char* findFunctorModule(lb_I_ConfigObject* node);
	char* findFunctorName(lb_I_ConfigObject* node);
	
	lb_I_Container* loadedModules;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbModule)
	ADD_INTERFACE(lb_I_Module)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbModule::setData(lb_I_Unknown* uk) {
	CL_LOG("lbModule::setData(...) not implemented yet");
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes lbModule::initialize() {
        return ERR_NONE;
}

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
		CL_LOG("DEBUG PAUSE 1");
		

		err = _node->getFirstChildren(__node);
		
		CL_LOG("DEBUG PAUSE 2");
		
		
		if (err != ERR_NONE) {
			CL_LOG("Error. Children expected");
			
			return NULL;
		}
		CL_LOG("No error found!");
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
lb_I_Container* moduleList = NULL;

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
        lb_I_XMLConfig* xml_Instance = NULL;
        lbErrCodes err = ERR_NONE;

CL_LOG("Get a XML config object");
        xml_Instance = getXMLConfigObject();
CL_LOG("Got it!");
        
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
	
		cout << "Requested a unknown instance for this interface: " << request << ". Try to get one." << endl;
		char* node = "#document/dtdHostCfgDoc/Modules/Module/Functions/Function/Functor";
		lb_I_ConfigObject* config = NULL;
		int count = 0;
					// request is a functor
		if (xml_Instance->hasConfigObject(node, count) == ERR_NONE) {
			/**
			 * Get the list of found objects as a list.
			 * The result is a view of notes in a max deep
			 * of one level.
			 */
#ifdef VERBOSE
CL_LOG("Try to get the config object");			
#endif
			xml_Instance->getConfigObject(config, node);
#ifdef VERBOSE
CL_LOG("Got a config object (will the next crash ?)");
#endif
			
			lb_I_ConfigObject* functorNode = findFunctorNode(config, request);
#ifdef VERBOSE
CL_LOG("Not crashed!");
#endif			
			
			if (functorNode == NULL) {
				cout << "Couldn't find the desired functor (nullpointer)!" << endl;
				
			}
			char* moduleName = findFunctorModule(functorNode);
			char* functorName = findFunctorName(functorNode);

			CL_LOG("Got this functor name:");
			CL_LOG(functorName);

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
			 
			// Check, if module is already loaded 
			 
//			lbStringKey* key = new lbStringKey(moduleName);

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
        return ERR_NONE;
}


/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
        lb_I_XMLConfig* xml_Instance = NULL;

        xml_Instance = getXMLConfigObject();
        
        cout << "lbModule::load(char* name) called" << endl;

        if (xml_Instance) {
            if (xml_Instance->parse() != ERR_NONE) {
                printf("Error while parsing XML document\n");
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

/*...slbErrCodes DLLEXPORT __cdecl getlb_ModuleInstance\40\lb_I_Module\42\\38\ inst\41\:0:*/
lbErrCodes DLLEXPORT __cdecl getlb_ModuleInstance(lb_I_Module*& inst) {
        inst = (lb_I_Module*) new lbModule();
        //inst->release();
        //inst = NULL;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes DLLEXPORT __cdecl lb_releaseInstance\40\lb_I_Unknown \42\ inst\41\:0:*/
lbErrCodes DLLEXPORT __cdecl lb_releaseInstance(lb_I_Unknown * inst) {
        delete inst;
        return ERR_NONE;
}
/*...e*/

/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";
        
        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        if (situation)
                                printf("DLL statically loaded.\n");
                        else
                                printf("DLL dynamically loaded.\n");
                        break;
                case DLL_THREAD_ATTACH:
                        printf("New thread starting.\n");
                        break;
                case DLL_PROCESS_DETACH:                        
                        if (situation)
                                printf("DLL released by system.\n");
                        else
                                printf("DLL released by program.\n");
                        break;
                case DLL_THREAD_DETACH:
                        printf("Thread terminating.\n");
                derault:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/

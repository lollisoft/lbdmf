#define LB_MODULE_DLL

/*...sincludes:0:*/
#include <windows.h>

#include <conio.h>
#include <stdio.h>

#include <lbInterfaces.h>
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
            printf("Kann Funktion '%s' nicht finden.\n", ftrname); getch(); exit(1);
        }

        lbErrCodes err = DLL_LB_GETXML_CONFIG_INSTANCE(xml_Instance);

        if (xml_Instance == NULL) {
            printf("Konnte XML Konfigurationsinstanz nicht bekommen.\n"); getch(); exit(1);
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

lb_gcManager gcManager;

/*...slbErrCodes lbModule\58\\58\release\40\\41\:0:*/
lbErrCodes lbModule::release() {
        ref--;

        if (ref == STARTREF) delete this;
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\queryInterface\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbModule::queryInterface(char* name, void** unknown) {

        /**
         * Lookup the interface name and then call the registered
         * functor for this interface.
         */

        if (strcmp(name, "lb_I_Module") == 0) {
                ref++;
                *unknown = (lb_I_Module*) this;
                return ERR_NONE;
        }
        
        if (strcmp(name, "lb_I_Unknown") == 0) {
                ref++;
                lb_I_Unknown* const pUnknown = this;
                *unknown = pUnknown;
                return ERR_NONE;
        }

        return ERR_NO_INTERFACE;
}
/*...e*/

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
	CL_LOG("lbModule::findFunctorNode() called");

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
		if ((strcmp(temp_node->getName(), "Functor")) == 0) {
			CL_LOG("Found the requested node");
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
		getch();

		err = _node->getFirstChildren(__node);
		
		CL_LOG("DEBUG PAUSE 2");
		getch();
		
		if (err != ERR_NONE) {
			CL_LOG("Error. Children expected");
			getch();
			return NULL;
		}
		CL_LOG("No error found!");
}
/*...e*/
#endif			
			return temp_node;
		}
		
		getch();
		
		
	} else CL_LOG("Get first child failed");


	while ((err = node->getNextChildren(temp_node)) == ERR_NONE) {
		CL_LOG("Get next child");
		if ((strcmp(temp_node->getName(), "Functor")) == 0) {
			CL_LOG("Found the requested node");
			return temp_node;
		}
	}
	
	if (err == ERR_CONFIG_NO_MORE_CHILDS) {
		CL_LOG("No more childs found");
	}

CL_LOG("Release the temp_node reference");
getch();	
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
		CL_LOG("Found node 'Module'");
		getch();
		
		if ((err = node->getFirstChildren(temp_node)) == ERR_NONE) {
			CL_LOG("Test first children");
			CL_LOG(temp_node->getName());
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
		        CL_LOG("Get next child");
		        CL_LOG(temp_node->getName());
		        if ((strcmp(temp_node->getName(), "ModuleName")) == 0) {
				char* value = NULL;
				CL_LOG("Found 'ModuleName'");
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
	else
	while ((err = node->getParent(temp_node)) == ERR_NONE) {
		return findFunctorModule(temp_node);
	} 


	return "NULL";
}
/*...e*/
/*...slbModule\58\\58\findFunctorName\40\\46\\46\\46\\41\:0:*/
char* lbModule::findFunctorName(lb_I_ConfigObject* node) {
	CL_LOG("Not yet implemented");
	
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


/*...slbModule\58\\58\request\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbModule::request(const char* request, lb_I_Unknown*& result) {
        lb_I_XMLConfig* xml_Instance = NULL;

        xml_Instance = getXMLConfigObject();
        
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
			
			xml_Instance->getConfigObject(config, node);
			
			lb_I_ConfigObject* functorNode = findFunctorNode(config, request);
			
			if (functorNode == NULL) {
				cout << "Couldn't find the desired functor (nullpointer)!" << endl;
				getch();
			}
			
			CL_LOG("Try to get module name");
			char* moduleName = findFunctorModule(functorNode);
			CL_LOG("Got this module name");
			CL_LOG(moduleName);
			
			CL_LOG("Try to get functor name");
			char* functorName = findFunctorName(functorNode);
			
			CL_LOG("Got this functor name:");
			CL_LOG(functorName);
			
			/**
			 * Now I should have all my information, create the instance.
			 */
			 
			 
			
		} else {
			cout << "Something goes wrong!" << endl;
			cout << "xml_Instance->hasConfigObject() returns <> ERR_NONE!" << endl;
		}
		
		getch();
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

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

lbErrCodes lbModule::request(const char* request, lb_I_Unknown*& result) {
        lb_I_XMLConfig* xml_Instance = NULL;

        xml_Instance = getXMLConfigObject();
        
        if (strcmp(request, "instance/XMLConfig") == 0) {
                //xml_Instance->hasConfigObject("Dat/object");
                //result = (lb_I_Unknown*) xml_Instance;
                
                xml_Instance->queryInterface("lb_I_Unknown", (void**) &result);
                
                return ERR_NONE;
        }
        
        xml_Instance->release();

        return ERR_NONE;
}

lbErrCodes lbModule::uninitialize() {
        return ERR_NONE;
}


/*...slbErrCodes lbModule\58\\58\load\40\char\42\ name\41\:0:*/
lbErrCodes lbModule::load(char* name) {
        lb_I_XMLConfig* xml_Instance = NULL;

        xml_Instance = getXMLConfigObject();

        if (xml_Instance) {
            if (xml_Instance->parse() != ERR_NONE) {
                printf("Error while parsing XML document\n");
            }
        }
        
	xml_Instance->release();        
        
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lbModule\58\\58\getObjectInstance\40\char\42\ name\44\ lb_I_Container\42\\38\ inst\41\:0:*/
lbErrCodes lbModule::getObjectInstance(char* name, lb_I_Container*& inst) {
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

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <malloc.h>

//#include "testdll.h"

#include <lbConfigHook.h>


#define LOOP

void main() {
        char* hostname = NULL;
        char* port = NULL;
        int count = 0;

/*...sbla:0:*/
#ifdef bla
        lb_I_test *t = NULL;

        getInstance(t);
        
        t->release();
#endif
/*...e*/
	getch();

	lb_I_Module* mm = getModuleInstance();

	mm->initialize();
LOG("Test using logger before loading module manager");

        LOG("Test has been started");
        LOG("Test has been started");

	mm->uninitialize();
        mm->release();
        unHookAll();
        getch();

	CL_LOG("Test container implementation");
	getch();
	
	mm = getModuleInstance();
	mm->initialize();
	lb_I_Unknown* uk = NULL;
	
	if (mm->request("lb_I_Container", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
	}
	
	lb_I_Container* c = NULL;
	
	if (uk->queryInterface("lb_I_Container", (void**) &c) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
	}
	
	CL_LOG("Container requested");
	getch();

	if (mm->request("lb_I_Integer", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
	}
#ifdef bla
	lb_I_KeyBase* key = NULL;
	if (uk->queryInterface("lb_I_KeyBase", (void**) &key) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
	}
#endif
	mm->uninitialize();
	mm->release();

	CL_LOG("Basic tests ended");
	getch();

        /**
         * Get module manager
         */
#ifdef LOOP
        for (long i = 0; i < 10000000; i++) {
#endif
                lb_I_Module* modMan = getModuleInstance();
                modMan->initialize();

LOG("Call lb_I_Module->load()");
        
                modMan->load("Test");
                
                lb_I_Unknown* pUnknown;
                lb_I_XMLConfig* XMLinst;
                
                /**
                 * Getting an instance of a precreated object is not possible,
                 * because this object must also be created the same way.
                 */
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "modMan->request('instance/XMLConfig', pUnknown)" << endl;
#endif
/*...e*/
		/**
		 * Get an instance from anywhere by an indirect request.
		 * (From the lb_I_Requestable interface)
		 */
                if (modMan->request("instance/XMLConfig", pUnknown) != ERR_NONE) {
                        // error
                }
/*...sVERBOSE:0:*/
#ifdef VERBOSE
cout << "pUnknown->queryInterface('lb_I_XMLConfig', (void**) &XMLinst)" << endl;                
#endif
/*...e*/
                pUnknown->queryInterface("lb_I_XMLConfig", (void**) &XMLinst);
                
                if (XMLinst == NULL) {
                        printf("Could not get XML instance!\n");
                        getch();
                        return;
                }
                
                cout << "Call XMLinst->parse() ('" << hex << (void*) XMLinst << "') ..." << endl;
                
		if (XMLinst->parse() != ERR_NONE) {
                	printf("Error while parsing XML document\n");
		}
                
                cout << "Called XMLinst->parse()" << endl;
                
                if (XMLinst->hasConfigObject("#document/dtdHostCfgDoc/Modules/Module/ModuleName", count) != ERR_NONE) {
                        printf("Object not found\n");
                } else {
                        printf("Object was found\n");
                }
                
                XMLinst->release();
                pUnknown->release();
		modMan->uninitialize();
                modMan->release();
                
              
                        
#ifdef LOOP
        }
#endif
        unHookAll();
        getch();
}

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
	lb_I_Module* modMan1 = getModuleInstance();
        LOG("Test has been started");
        modMan1->release();
        unHookAll();
        getch();

        /**
         * Get module manager
         */
#ifdef LOOP
        for (long i = 0; i < 10000000; i++) {
#endif
                lb_I_Module* modMan = getModuleInstance();
        
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
                modMan->release();
                
              
                        
#ifdef LOOP
        }
#endif
        unHookAll();
        getch();
}

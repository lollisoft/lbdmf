#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <malloc.h>

//#include "testdll.h"

#include <lbConfigHook.h>


#define LOOP

void main() {
/*...svars:0:*/
    char* hostname = NULL;
    char* port = NULL;
    char buf[100] = "";
    int count = 0;
    lb_I_Unknown* unknown = NULL;
    lb_I_Unknown* uk = NULL;
/*...e*/
/*...sinit:0:*/
	printf("Program starting...\n");
	getch();

	lb_I_Module* mm = getModuleInstance();
	mm->initialize();
/*...e*/
/*...stest string:0:*/
	CL_LOG("Test using lb_I_String");
	mm->request("lb_I_String", unknown);
	if (unknown != NULL) {
		lb_I_String* string = NULL;
		lbErrCodes err = ERR_NONE;

		CL_LOG("Try to get interface lb_I_String");
		getch();
		if ((err = unknown->queryInterface("lb_I_String", (void**) &string)) != ERR_NONE) {
			sprintf(buf, "Getting a string failed (string instance is %x, ErrCode = %d) !!!!!!!!", string, err);
			CL_LOG(buf);
		}

		if (string != NULL) {
			CL_LOG("Using the string :-)");
			string->setData("müll");
		}

		CL_LOG("Unknown instance of lb_I_String is no more needed!");
		unknown->release();
		getch();

		CL_LOG("Now release the string");
		string->release();
		getch();

	}
/*...e*/
/*...stest logger:0:*/
	CL_LOG("Test invoking logger interface directly (requesting)...");
	mm->request("lb_I_Log", unknown);

	if (unknown != NULL) {
		lb_I_Log* logger = NULL;
		if (unknown->queryInterface("lb_I_Log", (void**) &logger) != ERR_NONE) {
			CL_LOG("Getting a logger failed !!!!!!!!");
		}

		if (logger != NULL) {
				logger->enable("Bla");
				logger->log("Test logging", 100L, "Blubber");
		}
	}
/*...e*/
/*...stest container:0:*/
	if (mm->request("lb_I_Container", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
	
	lb_I_Container* c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
		getch();
	}
	
	CL_LOG("Container requested");
	getch();
/*...e*/
/*...stest integer:0:*/
	if (mm->request("lb_I_Integer", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
/*...e*/

/*...stest unloading module manager:0:*/
	CL_LOG("Test unloading module manager");
	mm->uninitialize();
	mm->release();
	unHookAll();
	getch();
/*...e*/
/*...stest after unloading:0:*/
	mm = getModuleInstance();
	mm->initialize();
	LOG("Test logging after initializing the second one");
/*...e*/
	
	uk = NULL;

/*...stest countainer:0:*/
	if (mm->request("lb_I_Container", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
	
	c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
		getch();
	}
	
	CL_LOG("Container requested");
	getch();
/*...e*/

/*...stest integer:0:*/
	if (mm->request("lb_I_Integer", uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
/*...e*/

	mm->uninitialize();
	mm->release();

	CL_LOG("Basic tests ended");
	getch();


	CL_LOG("Memory test ------------------------------------------");
	getch();
	
        /**
         * Get module manager
         */
        lb_I_Module* modMan = getModuleInstance();
        modMan->initialize();

	
	#ifdef LOOP
        for (long i = 0; i < 10000000; i++) {
    #endif
			if (modMan->request("lb_I_Container", uk) != ERR_NONE) {
				printf("Error: Could not get needed instance!\n");
				getch();
			}

			if (uk != NULL) {

				lb_I_Container* container = NULL;

				if (uk->queryInterface("lb_I_Container", (void**) &container) != ERR_NONE) {
					CL_LOG("Error: Could not query for interface lb_I_Container");
				}
				RELEASE(uk);

				if (modMan->request("lb_I_String", uk) != ERR_NONE) {
					printf("Error: Could not get needed instance!\n");
					getch();
				}

				if (uk != NULL) {
					lb_I_String* string = NULL;

					if (uk->queryInterface("lb_I_String", (void**) &string) != ERR_NONE) {
						printf("Error: Could not get needed interface!\n");
						getch();
					}

					if (string != NULL) {
						// Fill up the container
						
						string->setData("Bla");
						container->insert(string, string);
						string->setData("Bla1");
						container->insert(string, string);
						string->setData("Bla2");
						container->insert(string, string);
						string->setData("Bla3");
						container->insert(string, string);
						string->setData("Bla4");
						container->insert(string, string);
					}
				}

				container->deleteAll();
				RELEASE(container);
				
			} else {
				CL_LOG("Here must be an object!!!");
				getch();
			}

	#ifdef LOOP
		}
	#endif

        CL_LOG("End test lb_I_Container loop");
		getch();

#ifdef LOOP
        for (i = 0; i < 10000000; i++) {

#endif
printf("Test LOG macro\n");
LOG("Call lb_I_Module->load()");
getch();

		if (modMan->request("lb_I_Integer", uk) != ERR_NONE) {
			CL_LOG("Error: Could not get needed instance!");
		}
        	
        	uk->release();
        	
                lb_I_Unknown* pUnknown;
                lb_I_XMLConfig* XMLinst;
        
                        
#ifdef LOOP
        }
#endif
	modMan->uninitialize();
        modMan->release();
        unHookAll();
        getch();
}

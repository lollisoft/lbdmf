#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <malloc.h>

//#include "testdll.h"

#include <lbConfigHook.h>

#ifdef bla
		class UAP_theVariable {
		public:
	        UAP_theVariable() {
	        	_autoPtr = NULL;
			}
			virtual ~UAP_theVariable() { RELEASE(_autoPtr); }
			
		lb_I_Unknown& operator * () { return *_autoPtr; }
		lb_I_Unknown* operator -> () { return _autoPtr; }
		lb_I_Unknown*& operator & () { return _autoPtr; }
		
		UAP_theVariable& operator = (lb_I_Unknown*& autoPtr) { _autoPtr = autoPtr; return *this; }
		friend int operator ==(const UAP_theVariable& a, const lb_I_Unknown* b) {
			return a._autoPtr == b;
		}
		friend int operator !=(const UAP_theVariable& a, const lb_I_Unknown* b) {
			return a._autoPtr != b;
		}
		
		protected:
	        lb_I_Unknown* _autoPtr;
		};
#endif

#define LOOP

void main() {
/*...svars:0:*/
    char* hostname = NULL;
    char* port = NULL;
    char buf[100] = "";
    int count = 0;
    UAP(lb_I_Unknown, unknown)
    UAP(lb_I_Unknown, uk)
/*...e*/
/*...sinit:0:*/
	printf("Program starting...\n");
	getch();

	lb_I_Module* mm = getModuleInstance();
	mm->initialize();
/*...e*/
/*...stest string:0:*/
	CL_LOG("Test using lb_I_String");
	mm->request("lb_I_String", &unknown);
	CL_LOG("Requested the string instance as unknown");
	
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
		//string->release();
		getch();

	}
/*...e*/
/*...stest logger:0:*/
	CL_LOG("Test invoking logger interface directly (requesting)...");
	mm->request("lb_I_Log", &unknown);

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
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
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
	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
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
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
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
	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
/*...e*/

/*...stest unknown auto pointer:0:*/
	if (1)
	{
		UAP(lb_I_Unknown, theVariable)
		UAP(lb_I_String, string)
		
		class A {
		protected:
			UAP(lb_I_Unknown, test)
		};
		
		A a;
		
		
		if (theVariable.getPtr() != NULL) CL_LOG("Error: UAP does not correctly work");

		CL_LOG("Test unknown auto pointer");
		getch();
		lb_I_Unknown* uk = NULL;
		lb_I_String* s = NULL;

		if (mm->request("lb_I_String", &uk) != NULL) {
			CL_LOG("Error: Failed to get an instance lb_I_String");
		}
		
		theVariable = uk;
		
CL_LOG("Query interface lb_I_String");		

		if (theVariable == NULL) CL_LOG("Error: UAP is not initialized!");

		if (theVariable->queryInterface("lb_I_String", (void**) &string) != ERR_NONE) {
			CL_LOG("Error: Failed to get a reference to the interface lb_I_String");
		}
CL_LOG("Query done");		
		if (string != NULL) {
			CL_LOG("Test the created unknown autopointer !!!");
	
			string->setData("Blubber\n");
			
			char* buf = NULL;
			
			buf = string->getData();
			
			printf(buf);
			CL_LOG("Tested the created unknown autopointer !!!");
			getch();
		}
		CL_LOG("Releasing focus of auto pointer");
	}
	CL_LOG("Lost focus of auto pointer");
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

	
/*...sTest container with inserting strings:0:*/
	#ifdef LOOP
        for (long i = 0; i < 10000000; i++) {
    	#endif
    			UAP(lb_I_Unknown, uk)
    			
			if (modMan->request("lb_I_Container", &uk) != ERR_NONE) {
				printf("Error: Could not get needed instance!\n");
				getch();
			}

			if (uk != NULL) {
				UAP(lb_I_Unknown, uk1)
				UAP(lb_I_Container, container)

				if (uk->queryInterface("lb_I_Container", (void**) &container) != ERR_NONE) {
					CL_LOG("Error: Could not query for interface lb_I_Container");
				}
			
				if (modMan->request("lb_I_String", &uk1) != ERR_NONE) {
					printf("Error: Could not get needed instance!\n");
					getch();
				}

				if (uk1 != NULL) {
					UAP(lb_I_String, string)

					if (uk->queryInterface("lb_I_String", (void**) &string) != ERR_NONE) {
						printf("Error: Could not get needed interface!\n");
						getch();
					}

					if (string != NULL) {
						// Fill up the container
						UAP(lb_I_Unknown, uk)
						UAP(lb_I_KeyBase, key)
						
						string->queryInterface("lb_I_Unknown", (void**) &uk);
						string->queryInterface("lb_I_KeyBase", (void**) &key);
						
						string->setData("Bla");
						container->insert(&uk, &key);
						string->setData("Bla1");
						container->insert(&uk, &key);
						string->setData("Bla2");
						container->insert(&uk, &key);
						string->setData("Bla3");
						container->insert(&uk, &key);
						string->setData("Bla4");
						container->insert(&uk, &key);
					}
				}

				container->deleteAll();
				
			} else {
				CL_LOG("Here must be an object!!!");
				getch();
			}

	#ifdef LOOP
		}
	#endif
/*...e*/

        CL_LOG("End test lb_I_Container loop");
		getch();

#ifdef LOOP
        for (i = 0; i < 10000000; i++) {

#endif
printf("Test LOG macro\n");
LOG("Call lb_I_Module->load()");
getch();

		

		if (modMan->request("lb_I_Integer", &uk) != ERR_NONE) {
			CL_LOG("Error: Could not get needed instance!");
		}
        	
        	
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

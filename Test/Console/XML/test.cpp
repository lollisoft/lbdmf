/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {      
#endif            
#include <conio.h>

#ifdef __cplusplus
}
#endif            

#include <stdio.h>
#include <iostream.h>
#include <malloc.h>

//#include "testdll.h"

#include <lbConfigHook.h>
/*...e*/

/*...sbla:0:*/
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
/*...e*/

#define LOOP
// (trackObject == NULL) ? "" : trackObject int argc, char *argv[]
void main(int argc, char *argv[]) {
	char* file = "";
	int line = 0;
	lbErrCodes err = ERR_NONE;
/*...svars:0:*/
    char* hostname = NULL;
    char* port = NULL;
    char buf[100] = "";
    int count = 0;
    UAP(lb_I_Unknown, unknown, __FILE__, __LINE__)
    UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
/*...e*/
/*...sinit:0:*/
	printf("Program starting with %d arguments ...\n", argc);
	
	
	
	if ((argc == 3) && (strcmp(argv[1], "-trackObject") == 0)) {
		printf("Running in tracking mode\n");
		set_trackObject(strdup(argv[2]));
	}

	lb_I_Module* mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);
/*...e*/
/*...stest container:0:*/
{	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
	
	lb_I_Container* c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
		getch();
	}
}
/*...e*/
	CL_LOG("Tested container")
/*...stest logger:0:*/
	mm->request("lb_I_Log", &unknown);
	
	CL_LOG("Requested a instance for interface lb_I_Log")
	
	if (unknown != NULL) {
		lb_I_Log* logger = NULL;
		if (unknown->queryInterface("lb_I_Log", (void**) &logger, __FILE__, __LINE__) != ERR_NONE) {
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

	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
		getch();
	}
/*...e*/
/*...stest integer:0:*/
	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
/*...e*/

/*...stest unloading module manager:0:*/
	mm->uninitialize();
	RELEASE(mm)
	unHookAll();
/*...e*/
/*...stest after unloading:0:*/
	mm = getModuleInstance();
	LOG("Test logging after initializing the second one")
	CL_LOG("Tested logging after initializing the second one")
/*...e*/
	
	uk = NULL;

/*...stest countainer:0:*/
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
	
	c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		CL_LOG("Error: Could not get needed interface!");
		getch();
	}
	
/*...e*/

/*...stest integer:0:*/
	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
		CL_LOG("Error: Could not get needed instance!");
		getch();
	}
/*...e*/

/*...stest unknown auto pointer:0:*/
		UAP(lb_I_Unknown, theVariable, __FILE__, __LINE__)
		UAP(lb_I_String, string, __FILE__, __LINE__)
		
		if (theVariable.getPtr() != NULL) CL_LOG("Error: UAP does not correctly work");

		if (mm->request("lb_I_String", &theVariable) != NULL) {
			CL_LOG("Error: Failed to get an instance lb_I_String");
		}
		
		if (theVariable == NULL) CL_LOG("Error: UAP is not initialized!");

		if (theVariable->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
			CL_LOG("Error: Failed to get a reference to the interface lb_I_String");
		}
		if (string != NULL) {
			string->setData("Blubber\n");
			
			char* buf = NULL;
			
			buf = string->getData();
			
			printf(buf);
		}
/*...e*/

	CL_LOG("Test metaapplication");
	UAP_REQUEST(mm, lb_I_MetaApplication, meta)
	
	if (meta != NULL) {
		meta->Initialize();
	}
	
	
	CL_LOG("Tested metaapplication");

	mm->uninitialize();
	RELEASE(mm)
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
        for (long i = 0; i < 1; i++) {
    	#endif
    			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
    			
			if (modMan->request("lb_I_Container", &uk) != ERR_NONE) {
				printf("Error: Could not get needed instance!\n");
				getch();
			}

			if (uk != NULL) {
				UAP(lb_I_Unknown, uk1, __FILE__, __LINE__)
				UAP(lb_I_Container, container, __FILE__, __LINE__)

				if (uk->queryInterface("lb_I_Container", (void**) &container, __FILE__, __LINE__) != ERR_NONE) {
					CL_LOG("Error: Could not query for interface lb_I_Container");
				}
			
				if (modMan->request("lb_I_String", &uk1) != ERR_NONE) {
					printf("Error: Could not get needed instance!\n");
					getch();
				}

				if (uk1 != NULL) {
					CL_LOG("Test the container");
					UAP(lb_I_String, string, __FILE__, __LINE__)
					if (uk1->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
						printf("Error: Could not get needed interface!\n");
						getch();
					}
					CL_LOG("Have the string interface, insert data");
					if (string != NULL) {
						// Fill up the container
						for (long i = 0; i < 10000000; i++) {
/*...sand delete it after that again:56:*/
							UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
							UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
						
							string->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
							string->queryInterface("lb_I_KeyBase", (void**) &key, __FILE__, __LINE__);
						
							uk->setDebug(1);
						
							string->setData("Bla");
							CL_LOG("Insert first element");
						
						
							if (container == NULL) CL_LOG("Container is NULL");
							
							sprintf(buf, "RefCount of uk and key is %d, %d", uk->getRefCount(), key->getRefCount());
							CL_LOG(buf);
						
							container->insert(&uk, &key);
							CL_LOG("Inserted first element");
							
							lb_I_Unknown* ukdata = container->getElement(&key);
							printf("Have searched for an element\n");
							if (ukdata == NULL) printf("NULL pointer while searching for first element (search for '%s')!\n", key->charrep());
							
							string->setData("Bla1");
							container->insert(&uk, &key);
							string->setData("Bla2");
							container->insert(&uk, &key);
							string->setData("Bla3");
							container->insert(&uk, &key);
							string->setData("Bla4");
							container->insert(&uk, &key);
							
							
/*...sfind an element:112:*/
							string->setData("Bla3");
							ukdata = container->getElement(&key);
							
							if (ukdata == NULL) printf("NULL pointer!\n");
							
							lb_I_String* s = NULL;
							lbErrCodes err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);
							
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
/*...sfind an element:112:*/
							string->setData("Bla2");
							ukdata = container->getElement(&key);
							
							if (ukdata == NULL) printf("NULL pointer!\n");
							
							s = NULL;
							err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);
							
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
/*...sfind an element:112:*/
							string->setData("Bla1");
							ukdata = container->getElement(&key);
							
							if (ukdata == NULL) printf("NULL pointer!\n");
							
							s = NULL;
							err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);
							
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
/*...sfind an element:112:*/
							string->setData("Bla4");
							ukdata = container->getElement(&key);
							
							if (ukdata == NULL) printf("NULL pointer!\n");
							
							s = NULL;
							err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);
							
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
/*...sfind an element:112:*/
							string->setData("Bla");
							ukdata = container->getElement(&key);
							
							if (ukdata == NULL) printf("NULL pointer!\n");
							
							s = NULL;
							err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);
							
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
	
							printf("Try to dump content of container\n");	
							while (container->hasMoreElements() == 1) {
								lb_I_Unknown* e = container->nextElement();
								printf("Dump it\n");
								if (e != NULL) {
									lb_I_String* s;
									if (e->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__) != ERR_NONE) {
										printf("Something goes wrong :-(\n");
									}
									
									printf("String is: %s\n", s->getData());
								}
							}
	
							container->deleteAll();
							CL_LOG("Deleted all container data");
							getch();
/*...e*/
						}
					}
				}
				
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
        for (long ii = 0; ii < 10000000; ii++) {
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
        RELEASE(modMan)
        unHookAll();
        getch();
}

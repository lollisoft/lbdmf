/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    lbModule.h is part of DMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Borsteler Bogen 4

            22453 Hamburg (germany)
*/
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
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
		//set_trackObject(strdup(argv[2]));
	}

	lb_I_Module* mm = getModuleInstance();
	getch();
	mm->setModuleManager(mm, __FILE__, __LINE__);
/*...e*/
/*...stest container:0:*/
{
	printf("Request lb_I_Container\n");
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		printf("Requesting lb_I_Container failed\n");
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}
	
	lb_I_Container* c = NULL;
	printf("test container 1\n");
	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed interface!" LOG_
	}
}
/*...e*/
	printf("Tested container 1\n");
	getch();

	_CL_LOG << "Test database library" LOG_

	UAP_REQUEST(mm, lb_I_Database, database)

	database->init();
	database->connect("trainres", "dba", "trainres");
	
	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	query = database->getQuery();

	query->query("select ObjectTyp, X, Y, W, H from World");

	query->next();

	char ObjectTyp[1000];
	char X[100];
	char Y[100];
	char W[100];
	char H[100];

	strcpy(ObjectTyp, query->getChar(1));
	strcpy(X, query->getChar(2));
	strcpy(Y, query->getChar(3));
	strcpy(W, query->getChar(4));
	strcpy(H, query->getChar(5));


	printf("%s;%s;%s;%s;%s\n", ObjectTyp, X, Y, W, H);


	/* Todo:
	 * Create a viewer instance for the current query and
	 * test navigation.
	 */




	
	_CL_LOG << "Tested database" LOG_
	getch();

/*...stest logger:0:*/
	printf("test logger\n");
	mm->request("lb_I_Log", &unknown);
	
	_CL_LOG << "Requested a instance for interface lb_I_Log" LOG_
	printf("Tested container\n");
	if (unknown != NULL) {
		lb_I_Log* logger = NULL;
		if (unknown->queryInterface("lb_I_Log", (void**) &logger, __FILE__, __LINE__) != ERR_NONE) {
			_CL_LOG << "Getting a logger failed !!!!!!!!" LOG_
		}

		if (logger != NULL) {
				logger->enable("Bla");
				logger->log("Test logging", 100L, "Blubber");
		}
	}
/*...e*/
/*...stest container:0:*/
	printf("test container 2\n");
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}
	printf("have instance\n");
	lb_I_Container* c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed interface!" LOG_
	}
	printf("---- have lb_I_Container interface\n");
/*...e*/
/*...stest integer:0:*/

	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}
/*...e*/

/*...stest unloading module manager:0:*/
	printf("Uninitialize module manager\n");
	mm->uninitialize();
	printf("Release it\n");
	RELEASE(mm)
	printf("Unhook all modules\n");
	unHookAll();
/*...e*/
/*...stest after unloading:0:*/
	printf("Create a new module manager\n");
	mm = getModuleInstance();
	_CL_LOG << "Test logging after initializing the second one" LOG_
	_CL_LOG << "Tested logging after initializing the second one" LOG_
/*...e*/
	
	uk = NULL;

/*...stest countainer:0:*/
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}
	
	c = NULL;

	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed interface!" LOG_
	}
	
/*...e*/

/*...stest integer:0:*/
	if (mm->request("lb_I_Integer", &uk) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}
/*...e*/

/*...stest unknown auto pointer:0:*/
		UAP(lb_I_Unknown, theVariable, __FILE__, __LINE__)
		UAP(lb_I_String, string, __FILE__, __LINE__)
		
		if (theVariable.getPtr() != NULL) _CL_LOG << "Error: UAP does not correctly work" LOG_

		if (mm->request("lb_I_String", &theVariable) != NULL) {
			_CL_LOG << "Error: Failed to get an instance lb_I_String" LOG_
		}
		
		if (theVariable == NULL) _CL_LOG << "Error: UAP is not initialized!" LOG_

		if (theVariable->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
			_CL_LOG << "Error: Failed to get a reference to the interface lb_I_String" LOG_
		}
		if (string != NULL) {
			string->setData("Blubber\n");
			
			char* buf = NULL;
			
			buf = string->getData();
			
			printf(buf);
		}
/*...e*/

	_CL_LOG << "Test metaapplication" LOG_
	
	printf("Test meta application\n");
	UAP_REQUEST(mm, lb_I_MetaApplication, meta) 
	printf("Meta application loaded\n");
	
	if (meta != NULL) {
		meta->Initialize();
	}
	printf("Meta application initialized\n");
	
	_CL_LOG << "Tested metaapplication" LOG_

	mm->uninitialize();
	RELEASE(mm)
	_CL_LOG << "Basic tests ended" LOG_

	_CL_LOG << "Memory test ------------------------------------------" LOG_
	
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
			}

			if (uk != NULL) {
				UAP(lb_I_Unknown, uk1, __FILE__, __LINE__)
				UAP(lb_I_Container, container, __FILE__, __LINE__)

				if (uk->queryInterface("lb_I_Container", (void**) &container, __FILE__, __LINE__) != ERR_NONE) {
					_CL_LOG << "Error: Could not query for interface lb_I_Container" LOG_
				}
			
				if (modMan->request("lb_I_String", &uk1) != ERR_NONE) {
					printf("Error: Could not get needed instance!\n");
				}

				if (uk1 != NULL) {
					_CL_LOG << "Test the container" LOG_
					UAP(lb_I_String, string, __FILE__, __LINE__)
					if (uk1->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
						printf("Error: Could not get needed interface!\n");
					}
					_CL_LOG << "Have the string interface, insert data" LOG_
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
							_CL_LOG << "Insert first element" LOG_
						
						
							if (container == NULL) _CL_LOG << "Container is NULL" LOG_
							
							_CL_LOG << "RefCount of uk and key is " << uk->getRefCount() << ", " << key->getRefCount() LOG_
						
							container->insert(&uk, &key);
							_CL_LOG << "Inserted first element" LOG_
							
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
							_CL_LOG << "Deleted all container data" LOG_
/*...e*/
						}
					}
				}
				
			} else {
				_CL_LOG << "Here must be an object!!!" LOG_
			}

	#ifdef LOOP
		}
	#endif
/*...e*/

        _CL_LOG << "End test lb_I_Container loop" LOG_

#ifdef LOOP
        for (long ii = 0; ii < 10000000; ii++) {
#endif
printf("Test LOG macro\n");
	_CL_LOG << "Call lb_I_Module->load()" LOG_

		

		if (modMan->request("lb_I_Integer", &uk) != ERR_NONE) {
			_CL_LOG << "Error: Could not get needed instance!" LOG_
		}
        	
        	
                lb_I_Unknown* pUnknown;
                lb_I_XMLConfig* XMLinst;
        
                        
#ifdef LOOP
        }
#endif
	modMan->uninitialize();
        RELEASE(modMan)
        unHookAll();
}

/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
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

#include <lbConfigHook.h>

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#ifndef MEMTRACK
#include <malloc.h>
#endif
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif
//#include "testdll.h"

/*...e*/

#define LOOP


void PrintData(lb_I_Query* q) {
	if (q->first() == ERR_NONE) {

	    for (int cols = 1; cols <= q->getColumns()-1; cols++) { 
		printf("%s;", q->getAsString(cols)->charrep());
	    };
	    
	    printf("%s\n", q->getAsString(q->getColumns())->charrep());
	    
	    while (q->next() == ERR_NONE) {
		for (int cols = 1; cols <= q->getColumns()-1; cols++) { 
			printf("%s;", q->getAsString(cols)->charrep());
		};
		printf("%s\n", q->getAsString(q->getColumns())->charrep());
	    };
	    
	}
}

// (trackObject == NULL) ? "" : trackObject int argc, char *argv[]
int main(int argc, char *argv[]) {

{
	char* file = "";
	int line = 0;
	lbErrCodes err = ERR_NONE;
/*...svars:0:*/
    char* hostname = NULL;
    char* port = NULL;
    char buf[100] = "";
    int count = 0;
    UAP(lb_I_Unknown, unknown)
    UAP(lb_I_Unknown, uk)
/*...e*/
/*...sinit:0:*/
	printf("Program starting with %d arguments ...\n", argc);
	
	
	
	if ((argc == 3) && (strcmp(argv[1], "-trackObject") == 0)) {
		printf("Running in tracking mode\n");
		//set_trackObject(strdup(argv[2]));
	}

	lb_I_Module* mm = NULL;
	mm = getModuleInstance();
	//mm->setModuleManager(mm, __FILE__, __LINE__);

/*...e*/

/*...sTest plugins:0:*/
#ifdef TestPlugins
int a = 1;
int b = 1;

if (a == b) {
	UAP_REQUEST(mm, lb_I_PluginManager, PM)
	printf("Test plugin manager\n");	
	PM->beginEnumPlugins();
	printf("Tested plugin manager\n");	
}
#endif
/*...e*/

/*...sTest database:0:*/
	_CL_LOG << "Test database library" LOG_
{
	UAP_REQUEST(mm, lb_I_Database, database)

	database->init();
	database->connect("trainres", "dba", "trainres");
	
	UAP_REQUEST(mm, lb_I_Database, database1)

	UAP(lb_I_Query, query)
	UAP(lb_I_Query, query1)
	UAP(lb_I_Query, query2)

	query = database->getQuery(0);


#ifdef USE_PK
	query->query("select objecttyp, x, y, w, h, id from world order by id");
#endif
#ifndef USE_PK
	query->query("select objecttyp, x, y, w, h from world order by id");
#endif
// Second run fails ??

/*...sforward:8:*/

	PrintData(*&query);

	UAP(lb_I_Query, testquery)
	
	testquery = database->getQuery(0);

#ifdef USE_PK
	testquery->query("select x, y, w, h, id from world order by id");
#endif
#ifndef USE_PK
	testquery->query("select x, y, w, h from world order by id");
#endif
	PrintData(testquery.getPtr());
	PrintData(*&query);

	database1->init();
	database1->connect("lbDMF", "dba", "trainres");
	
	query1 = database1->getQuery(0);
	query2 = database1->getQuery(0);
	
	query1->query("select * from users order by id");
	query2->query("select * from formulare order by id");	
	
	PrintData(*&query1);
	PrintData(*&query2);
	PrintData(*&query);

/*...e*/

#ifdef bla
/*...s:0:*/
	printf("Test for database deletion with cursor\n");


	UAP_REQUEST(mm, lb_I_Database, db1)
	UAP_REQUEST(mm, lb_I_Database, database2)
	UAP(lb_I_Query, query11)
	UAP(lb_I_Query, query12)
	
	db1->init();
	db1->connect("trainres", "dba", "trainres");
	database2->init();
	database2->connect("trainres", "dba", "trainres");
	
	query11 = db1->getQuery(0);
	
	UAP_REQUEST(mm, lb_I_String, t1)
	UAP_REQUEST(mm, lb_I_String, t2)

	query1->query("drop table test");

printf("Dropped table test\n");	

	query1->query("create table test (text char(300), id int)");

printf("Created table test\n");

	query11->query("delete from test");

	query11->query("insert into test values ('Test1', 1)");
	query11->query("insert into test values ('Test2', 2)");
	query11->query("insert into test values ('Test3', 3)");
	query11->query("insert into test values ('Test4', 4)");
	query11->query("insert into test values ('Test5', 5)");
	query11->query("insert into test values ('Test6', 6)");

	query12 = database2->getQuery(0);

	query12->query("select text, id from test");

	query12->first();
	t1 = query12->getAsString(1);
	t2 = query12->getAsString(2);
	printf("%s;%s\n", t1->charrep(), t2->charrep());
	query12->next();
	t1 = query12->getAsString(1);
	t2 = query12->getAsString(2);
	printf("%s;%s\n", t1->charrep(), t2->charrep());
	query12->next();
	t1 = query12->getAsString(1);
	t2 = query12->getAsString(2);
	printf("%s;%s\n", t1->charrep(), t2->charrep());
	query12->remove();
	t1 = query12->getAsString(1);
	t2 = query12->getAsString(2);
	printf("%s;%s\n", t1->charrep(), t2->charrep());

printf("Deleted a row\n");
	
	PrintData(*&query12);

	printf("Tested database cleanup\n");
/*...e*/
#endif //bla
}
/*...e*/
#ifdef bla
/*...sTest all other things:0:*/
/*...stest container:0:*/
{
	printf("Request lb_I_Container\n");
	if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
		printf("Requesting lb_I_Container failed\n");
		_CL_LOG << "Error: Could not get needed instance!" LOG_
	}

	printf("Requested container\n");
	
	lb_I_Container* c = NULL;
	printf("test container 1\n");
	if (uk->queryInterface("lb_I_Container", (void**) &c, __FILE__, __LINE__) != ERR_NONE) {
		_CL_LOG << "Error: Could not get needed interface!" LOG_
	}
	printf("Interface queried for container\n");
	RELEASE(c)
	printf("Released Container\n");
}
/*...e*/

	/* Todo:
	 * Create a viewer instance for the current query and
	 * test navigation.
	 */


// Database tests moved to ... init

	
	_CL_LOG << "Tested database" LOG_
#ifdef bla
	UAP_REQUEST(mm, lb_I_InterfaceRepository, ir)
//DebugBreak();	

	ir->setCurrentSearchInterface("lb_I_Container");	
	if (ir->getFirstEntity() == NULL) exit;
#endif	

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
/*...sTest container with inserting strings and manipulate one reference to show changes in other reference:0:*/
{
		UAP(lb_I_Unknown, uk)
    			
		if (mm->request("lb_I_Container", &uk) != ERR_NONE) {
			printf("Error: Could not get needed instance!\n");
		}

		if (uk != NULL) {
			UAP(lb_I_Unknown, uk1)
			UAP(lb_I_Container, container)

			if (uk->queryInterface("lb_I_Container", (void**) &container, __FILE__, __LINE__) != ERR_NONE) {
				_CL_LOG << "Error: Could not query for interface lb_I_Container" LOG_
			}
			
			if (mm->request("lb_I_String", &uk1) != ERR_NONE) {
				printf("Error: Could not get needed instance!\n");
			}

			if (uk1 != NULL) {
				_CL_LOG << "Test the container" LOG_
				UAP(lb_I_String, string)
				if (uk1->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
					printf("Error: Could not get needed interface!\n");
				}
				_CL_LOG << "Have the string interface, insert data" LOG_
				if (string != NULL) {
					// Fill up the container
/*...sand delete it after that again:40:*/
/*...screate key and uk for the container filling:40:*/
							UAP(lb_I_Unknown, uk)
							UAP(lb_I_KeyBase, key)
						
							string->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
							string->queryInterface("lb_I_KeyBase", (void**) &key, __FILE__, __LINE__);
/*...e*/
						
/*...sfill data into the container \40\insert clones the given instance\41\:40:*/
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
/*...e*/
							
							
/*...sfind an element for reference testing:40:*/
							string->setData("Bla3");
							
							lb_I_String* s = NULL;
							ukdata = container->getElement(&key);
							if (ukdata == NULL) printf("NULL pointer!\n");
							lbErrCodes err = ukdata->queryInterface("lb_I_String", (void**) &s, __FILE__, __LINE__);

							lb_I_String* s1 = NULL;
							ukdata = container->getElement(&key);
							if (ukdata == NULL) printf("NULL pointer!\n");
							err = ukdata->queryInterface("lb_I_String", (void**) &s1, __FILE__, __LINE__);
							
							s1->setData("Changed");
							char* cp1 = s1->getData();
							char* cp = s->getData();
							
							printf("Have changed s1 from Bla3 to %s. s is %s\n", cp1, cp);
							if (err == ERR_NONE) printf("Found string %s\n", s->getData());
/*...e*/
	
/*...sdump content:40:*/
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
/*...e*/
	
		container->deleteAll();
		_CL_LOG << "Deleted all container data" LOG_
/*...e*/
				}
			}
			printf("Have tested container reference handling\n");
			printf("----------------------------------------\n");
		} else {
			_CL_LOG << "Here must be an object!!!" LOG_
		}
}
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
//	DebugBreak();
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
		UAP(lb_I_Unknown, theVariable)
		UAP(lb_I_String, string)
		
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
    			UAP(lb_I_Unknown, uk)
    			
			if (modMan->request("lb_I_Container", &uk) != ERR_NONE) {
				printf("Error: Could not get needed instance!\n");
			}

			if (uk != NULL) {
				UAP(lb_I_Unknown, uk1)
				UAP(lb_I_Container, container)

				if (uk->queryInterface("lb_I_Container", (void**) &container, __FILE__, __LINE__) != ERR_NONE) {
					_CL_LOG << "Error: Could not query for interface lb_I_Container" LOG_
				}
			
				if (modMan->request("lb_I_String", &uk1) != ERR_NONE) {
					printf("Error: Could not get needed instance!\n");
				}

				if (uk1 != NULL) {
					_CL_LOG << "Test the container" LOG_
					UAP(lb_I_String, string)
					if (uk1->queryInterface("lb_I_String", (void**) &string, __FILE__, __LINE__) != ERR_NONE) {
						printf("Error: Could not get needed interface!\n");
					}
					_CL_LOG << "Have the string interface, insert data" LOG_
					if (string != NULL) {
						// Fill up the container
						for (long i = 0; i < 10000000; i++) {
/*...sand delete it after that again:56:*/
							UAP(lb_I_Unknown, uk)
							UAP(lb_I_KeyBase, key)
						
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

/*...sA loop:0:*/
#ifdef LOOP
        for (long oo = 0; oo < 10000000; oo++) {
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
/*...e*/
	modMan->uninitialize();
        RELEASE(modMan)

}
/*...e*/
#endif
        unHookAll();
        return 0;
}
}

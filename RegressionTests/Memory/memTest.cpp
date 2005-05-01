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
#ifndef OSX            
#include <conio.h>
#endif
#ifdef __cplusplus
}
#endif            

#include <stdio.h>
#include <iostream.h>
#ifndef OSX
#include <malloc.h>
#endif
//#include "testdll.h"

#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page Memorytest Testing DMF environment - memory test.
 *
 * \section Introduction
 *
 * Test the framework for memory usage and insatance usages:
 *
 * \code
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

	TRMemOpen();
	TRMemSetModuleName(__FILE__);
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

#define MEM_TEST
#define CONTAINER_TEST
#define ACCESS_TEST

#ifdef MEM_TEST
	{
		_CL_LOG << "Memory regression tests..." LOG_
	
		for (int i = 0; i < 50; i++) {
			UAP_REQUEST(mm, lb_I_String, string)
			string->setData("Test");
		}

		char* t = (char*) new char[100];
		t[0] = 0;
		
		sprintf(t, "Unfreed memory :-)\n");
	
		printf("Ready.\n");
	}

	Instances();
#endif
	{

	UAP_REQUEST(mm, lb_I_Container, container)
	UAP_REQUEST(mm, lb_I_String, string)


	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

	QI(string, lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(string, lb_I_KeyBase, key, __FILE__, __LINE__)

	string->setData("Bla");

	container->insert(&uk, &key);
	string->setData("Bla1");
	container->insert(&uk, &key);
	
	container->deleteAll();

#ifdef CONTAINER_TEST

	container->insert(&uk, &key);
	string->setData("Bla1");
	container->insert(&uk, &key);
	string->setData("Bla2");
	container->insert(&uk, &key);
	string->setData("Bla3");
	container->insert(&uk, &key);
	string->setData("Bla4");
	container->insert(&uk, &key);

	container->deleteAll();
	
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
	
	string->setData("Bla3");
#endif

#ifdef ACCESS_TEST

	\endcode

	\section UsingUAP Using automatic pointers

	These brackets are nessesary due to the fact, that the memory leak printer in the
	destructor ~Memory prints a not yet deleted object.
	The object is stored in a container, who does not delete an entry, that has been
	referenced here.
	This shows the functioning reference counting, if automatic pointers (UAP's) are
	used.
	
	There is an order of when the automatic pointers in maim and the static Memory instance
	from trmem gets deleted.
	
	So the brackets are more for demonstration.
	
	\code	
{
	UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)

	UAP(lb_I_String, s, __FILE__, __LINE__)

	ukdata = container->getElement(&key);
	if (ukdata == NULL) printf("NULL pointer!\n");

	QI(ukdata, lb_I_String, s, __FILE__, __LINE__)

	UAP(lb_I_String, s1, __FILE__, __LINE__)

	ukdata = container->getElement(&key);
	if (ukdata == NULL) printf("NULL pointer!\n");

	QI(ukdata, lb_I_String, s1, __FILE__, __LINE__)

	s1->setData("Changed");
	char* cp1 = s1->getData();
	char* cp = s->getData();

	printf("Have changed s1 from Bla3 to %s. s is %s\n", cp1, cp);
	if (s != NULL) printf("Found string %s\n", s->getData());

	printf("Try to dump content of container\n");	
	while (container->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, e, __FILE__, __LINE__)
		e = container->nextElement();
		if (e != NULL) {
			UAP(lb_I_String, s, __FILE__, __LINE__)
			
			QI(e, lb_I_String, s, __FILE__, __LINE__)
						
			printf("String is: %s\n", s->getData());
		}
	}
}


#endif

	container->deleteAll();

	}
	
	mm->release(__FILE__, __LINE__);
	getchar();
	
	return 0;
}
 * \endcode
 *
 * \section Details
 *
 * This test is aimed to detect memory leaks and a try to get the amount of instances for
 * all classes in use of this test.
 *
 */


/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;

	TRMemOpen();
	TRMemSetModuleName(__FILE__);
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

#define MEM_TEST
#define CONTAINER_TEST
//#define ACCESS_TEST

#ifdef MEM_TEST
/*...sMemory test:0:*/

	{
		

		_CL_LOG << "Memory regression tests..." LOG_
	
		for (int i = 0; i < 50; i++) {
			UAP_REQUEST(mm, lb_I_String, string)
			string->setData("Test");
		}

		char* t = (char*) new char[100];
		t[0] = 0;
		
		sprintf(t, "Unfreed memory :-)\n");
	
		printf("Ready.\n");
	}

	Instances();
/*...e*/
#endif
	{

	UAP_REQUEST(mm, lb_I_Container, container)
	UAP_REQUEST(mm, lb_I_String, string)


	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

	QI(string, lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(string, lb_I_KeyBase, key, __FILE__, __LINE__)

	string->setData("Bla");

	container->insert(&uk, &key);
	string->setData("Bla1");
	container->insert(&uk, &key);
	
	container->deleteAll();

#ifdef CONTAINER_TEST
/*...sContainer test:0:*/

	container->insert(&uk, &key);
	string->setData("Bla1");
	container->insert(&uk, &key);
	string->setData("Bla2");
	container->insert(&uk, &key);
	string->setData("Bla3");
	container->insert(&uk, &key);
	string->setData("Bla4");
	container->insert(&uk, &key);

	container->deleteAll();
	
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
	
	string->setData("Bla3");
/*...e*/
#endif



#ifdef ACCESS_TEST
/*...sContainer access and search test:0:*/
{
	UAP(lb_I_Unknown, ukdata, __FILE__, __LINE__)

	UAP(lb_I_String, s, __FILE__, __LINE__)

	ukdata = container->getElement(&key);
	if (ukdata == NULL) printf("NULL pointer!\n");

	QI(ukdata, lb_I_String, s, __FILE__, __LINE__)

	UAP(lb_I_String, s1, __FILE__, __LINE__)

	ukdata = container->getElement(&key);
	if (ukdata == NULL) printf("NULL pointer!\n");

	QI(ukdata, lb_I_String, s1, __FILE__, __LINE__)

	s1->setData("Changed");
	char* cp1 = s1->getData();
	char* cp = s->getData();

	printf("Have changed s1 from Bla3 to %s. s is %s\n", cp1, cp);
	if (s != NULL) printf("Found string %s\n", s->getData());

	printf("Try to dump content of container\n");	
	while (container->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, e, __FILE__, __LINE__)
		e = container->nextElement();
		if (e != NULL) {
			UAP(lb_I_String, s, __FILE__, __LINE__)
			
			QI(e, lb_I_String, s, __FILE__, __LINE__)
						
			printf("String is: %s\n", s->getData());
		}
	}
}

/*...e*/
#endif

	container->deleteAll();

	}
	
	mm->release(__FILE__, __LINE__);
	getchar();
	
	return 0;
}

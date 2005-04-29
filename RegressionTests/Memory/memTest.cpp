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
 * Test the framework for memory usage and insatance usages.
 *
 * \code
int main(int argc, char *argv[]) {
	{
		lbErrCodes err = ERR_NONE;
		lb_I_Module* mm = NULL;

		Instances();
	
		mm = getModuleInstance();
		
		Instances();
		
		mm->setModuleManager(mm, __FILE__, __LINE__);

		Instances();

		_CL_LOG << "Memory regression tests..." LOG_
	
		Instances();
	
		for (int i = 0; i < 10; i++) {
			UAP_REQUEST(mm, lb_I_String, string)
			string->setData("Test");

			Instances();
		}

		char* t = (char*) malloc(100);
	
		printf("Ready.\n");
		Instances();
	}

	Instances();
	
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
	{
		lbErrCodes err = ERR_NONE;
		lb_I_Module* mm = NULL;

		Instances();
	
		mm = getModuleInstance();
		
		Instances();
		
		mm->setModuleManager(mm, __FILE__, __LINE__);

		Instances();

		_CL_LOG << "Memory regression tests..." LOG_
	
		Instances();
	
		for (int i = 0; i < 10; i++) {
			UAP_REQUEST(mm, lb_I_String, string)
			string->setData("Test");

			Instances();
		}

		char* t = (char*) malloc(100);
	
		printf("Ready.\n");
		Instances();
	}

	Instances();
	
	getchar();
	
	return 0;
}

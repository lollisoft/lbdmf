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

#include <stdio.h>
#include <iostream.h>
#include <malloc.h>

//#include "testdll.h"

#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page FirstSample Beginning programming in DMF environment - Hello world.
 *
 * \section FirstSample1 Hello world sample code
 *
 * The sample is located in Samples/HelloWorld.
 *
 * \code
 *	int main(int argc, char *argv[]) {
 *		lbErrCodes err = ERR_NONE;
 *		lb_I_Module* mm = NULL;
 *
 *		// Get the repository.
 *		mm = getModuleInstance();
 *		mm->setModuleManager(mm, __FILE__, __LINE__);
 *
 *		_CL_LOG << "Hello world" LOG_
 *
 *		UAP_REQUEST(mm, lb_I_String, string)
 *
 *		string->setData("Console logging...");
 *		_CL_LOG << string->charrep() LOG_
 *		
 *		return 0;
 *	}
 * \endcode
 *
 * \section Details
 *	This is a very simple application. But it includes some special aspects, that a normal
 *	C++ application not have.
 *
 *	To use the string class lb_I_String (an interface to it), you must get an instance of the
 *	module manager. This class knows, where the implementations from an interface come from.
 *
 *	The function getModuleInstance(); located in lbHook, gets the DLL/so and function name
 *	information from environment variables. Then it creates an instance.
 *
 *	After creating the instance for the module manager, you see a _CL_LOG line. It outputs
 *	the given message to the console. This is similar to cout. In fakt, it is cout.
 *
 * \section UAP_REQUEST
 *	To get any instance for an interface, you need to request for that interface. UAP_REQUEST
 *	is a macro and hides some code. After that request, you will have an instance of a class
 *	having that interface.
 *
 *	You can see the usage of that class in the _CL_LOG line, followed after string->setData(...)
 */
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Hello world" LOG_
	
	UAP_REQUEST(mm, lb_I_String, string)
	
	string->setData("Console logging...");
	_CL_LOG << string->charrep() LOG_

        return 0;
}

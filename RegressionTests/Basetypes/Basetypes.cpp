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
#include <iostream>
#ifndef OSX
#include <malloc.h>
#endif
#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page Basetypes Testing DMF environment - Test basic data types.
 *
 * \section Introduction
 *
 * The sample is located in RegressionTests/Basetypes.
 *
 * \code
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test basetypes" LOG_
	
	UAP_REQUEST(mm, lb_I_String, string1)
	UAP_REQUEST(mm, lb_I_String, string2)

	string1->setData("Test basetypes...");
	string2->setData("Test basetypes...");
	
	if (*&string1 == *&string2) {
		_CL_LOG << "Strings are identical" LOG_
	} else {
		_CL_LOG << "Strings are not identical" LOG_
	}

	lb_I_String* s1 = string1.getPtr();
	lb_I_String* s2 = string2.getPtr();

        if (s1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	if (string1->equals(*&string2)) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	if (string1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

        return 0;
}
 * \endcode
 *
 * \section Details
 *
 */
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test basetypes" LOG_

	UAP_REQUEST(mm, lb_I_String, string1)
	char buf1[100] = "";
	UAP_REQUEST(mm, lb_I_String, string2)
	char buf2[100] = "";

	string1->setData("Test basetypes...");
	string2->setData("Test basetypes...");

	_CL_LOG << "Test (*&string1 == *&string2)" LOG_
	
	if (*&string1 == *&string2) {
		_CL_LOG << "Strings are identical" LOG_
	} else {
		_CL_LOG << "Strings are not identical" LOG_
	}

	lb_I_String* s1 = string1.getPtr();
	lb_I_String* s2 = string1.getPtr();

	_CL_LOG << "String has " << s1->getRefCount() << " references." LOG_

	s1->release(__FILE__, __LINE__);

	_CL_LOG << "Test (s1 == s2)" LOG_

        if (s1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test (string1->equals(*&string2))" LOG_

	if (string1->equals(*&string2)) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test (string1 == s2)" LOG_

	if (string1 == s2) {
                _CL_LOG << "Strings are identical" LOG_
        } else {
                _CL_LOG << "Strings are not identical" LOG_
        }

	_CL_LOG << "Test a container" LOG_
	
	{
		UAP_REQUEST(mm, lb_I_Container, container)
	
		UAP_REQUEST(mm, lb_I_String, data)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		QI(data, lb_I_KeyBase, key, __FILE__, __LINE__)
		QI(data, lb_I_Unknown, uk, __FILE__, __LINE__)
		
		data->setData("Test1");
		
		container->insert(&uk, &key);
		
		data->setData("Test2");
		
		container->insert(&uk, &key);
		
		data->setData("Test1");
		
		container->remove(&key);

		UAP(lb_I_Unknown, uk1, __FILE__, __LINE__)
		
		data->setData("Test2");
		
		uk1 = container->getElement(&key);
		
		// Memory leaks will appear, if this line is uncommented.
		//container->detachAll();
	}
	_CL_LOG << "Tested a container" LOG_
	
        return 0;
}

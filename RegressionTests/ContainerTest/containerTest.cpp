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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
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
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
#include <lbConfigHook.h>
/*...e*/

void printContainer(lb_I_Container* container) {
	lbErrCodes err = ERR_NONE;
	while (container->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, e)
		e = container->nextElement();
		if (e != NULL) {
			UAP(lb_I_String, s)
			
			QI(e, lb_I_String, s)
			
			printf("String is: %s\n", s->getData());
		}
	}
}

void fillContainer(lb_I_Container* container) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SData)

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(IData, lb_I_KeyBase, key)
	QI(SData, lb_I_Unknown, uk)

	for (int i = 1; i <= 10; i++) {
			IData->setData(i);
			*SData = "Element ";
			*SData += IData->charrep();
			
			container->insert(&uk, &key);
	}
}


int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();
	mm->setModuleManager(mm, __FILE__, __LINE__);

	_CL_LOG << "Test MetaApplication" LOG_

	// Preload lbClasses DLL with this line !
	UAP_REQUEST(mm, lb_I_String, s)
	
	UAP_REQUEST(mm, lb_I_MetaApplication, meta)

	UAP_REQUEST(mm, lb_I_Container, container)
	UAP_REQUEST(mm, lb_I_Container, container1)
	
	container->setCloning(true);
	fillContainer(*&container);
	printContainer(*&container);

	container1->setCloning(false);
	//container->deleteAll();
	
	fillContainer(*&container1);
	printContainer(*&container1);

	return 0;
}

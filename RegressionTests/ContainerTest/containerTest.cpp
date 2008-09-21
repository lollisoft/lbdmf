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

void fillContainerFromDBProblems(lb_I_Container* container) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SData)
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(IData, lb_I_KeyBase, key)
	QI(SData, lb_I_Unknown, uk)
	
	int i = 0;
	i++;
	IData->setData(i);
	*SData = "ID";
	container->insert(&uk, &key);
	i++;
	IData->setData(i);
	*SData = "test";
	container->insert(&uk, &key);
	i++;
	IData->setData(i);
	*SData = "id_reg";
	container->insert(&uk, &key);
	
}


void searchContainerElement(lb_I_Container* container, int i) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
	QI(IData, lb_I_KeyBase, key)
	
	IData->setData(i);
	
	if (container->exists(&key) == 1) {
		UAP(lb_I_String, SData)
		UAP(lb_I_Unknown, uk)
		uk = container->getElement(&key);
		QI(uk, lb_I_String, SData)
		_CL_LOG << "Found element: " << SData->charrep() LOG_
	} else {
		_CL_LOG << "Don't found element: " << i LOG_
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

	searchContainerElement(*&container, 1);
	searchContainerElement(*&container, 2);
	searchContainerElement(*&container, 9);
	searchContainerElement(*&container, 10);
	searchContainerElement(*&container, 5);
	searchContainerElement(*&container, 6);
	searchContainerElement(*&container, 3);
	searchContainerElement(*&container, 4);
	searchContainerElement(*&container, 7);
	searchContainerElement(*&container, 8);
	searchContainerElement(*&container, 4711);
	
	container->deleteAll();
	
	fillContainerFromDBProblems(*&container);
	
	printContainer(*&container);

	printf("Container has %d elements.\n", container->Count());
	
	container->deleteAll();

	fillContainerFromDBProblems(*&container);
	
	printContainer(*&container);
	
	printf("Container has %d elements.\n", container->Count());
	
	return 0;
}

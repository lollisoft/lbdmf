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
 Ginsterweg 4
 
 65760 Eschborn (germany)
 */
/*...e*/
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif


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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


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

void fillContainer(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SData)
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(IData, lb_I_KeyBase, key)
	QI(SData, lb_I_Unknown, uk)
	
	for (int i = 1; i <= howMany; i++) {
		IData->setData(i);
		*SData = "Element ";
		*SData += IData->charrep();
		
		container->insert(&uk, &key);
	}
}

void fillContainerStringKey(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SData)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SKey)
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, uk)
	
	QI(SKey, lb_I_KeyBase, key)
	QI(SData, lb_I_Unknown, uk)
	
	for (int i = 1; i <= howMany; i++) {
		IData->setData(i);
		*SKey = "Huge keydata ";
		*SKey += IData->charrep();
		*SData = "Element ";
		*SData += IData->charrep();
		
		container->insert(&uk, &key);
	}
}

void fillContainerRequestInLoop(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	
	for (int i = 1; i <= howMany; i++) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
		UAP_REQUEST(getModuleInstance(), lb_I_String, SData)
		
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		QI(IData, lb_I_KeyBase, key)
		QI(SData, lb_I_Unknown, uk)
		
		IData->setData(i);
		*SData = "Element ";
		*SData += IData->charrep();
		
		container->insert(&uk, &key);
	}
}

void fillContainerStringKeyRequestInLoop(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	
	for (int i = 1; i <= howMany; i++) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
		UAP_REQUEST(getModuleInstance(), lb_I_String, SData)
		UAP_REQUEST(getModuleInstance(), lb_I_String, SKey)
		
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		QI(SKey, lb_I_KeyBase, key)
		QI(SData, lb_I_Unknown, uk)
		
		IData->setData(i);
		*SKey = "Huge keydata ";
		*SKey += IData->charrep();
		*SData = "Element ";
		*SData += IData->charrep();
		
		container->insert(&uk, &key);
	}
}

void fillContainerRequestInLoopWithParameter(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	
	container->setCloning(false);
	
	for (int i = 1; i <= howMany; i++) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
		UAP_REQUEST(getModuleInstance(), lb_I_String, P1)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N1)
		UAP_REQUEST(getModuleInstance(), lb_I_String, P2)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N2)
		UAP_REQUEST(getModuleInstance(), lb_I_String, P3)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N3)
		
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
		
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		QI(IData, lb_I_KeyBase, key)
		QI(param, lb_I_Unknown, uk)
		
		IData->setData(i);
		*P1 = "Parameter ";
		*P1 += IData->charrep();
		*N1 = "Parameter ";
		*N1 += IData->charrep();
		*P2 = "Parameter ";
		*P2 += IData->charrep();
		*N2 = "Parameter ";
		*N2 += IData->charrep();
		*P3 = "Parameter ";
		*P3 += IData->charrep();
		*N3 = "Parameter ";
		*N3 += IData->charrep();
		
		param->setUAPString(*&N1, *&P1);
		param->setUAPString(*&N2, *&P2);
		param->setUAPString(*&N3, *&P3);
		
		container->insert(&uk, &key);
	}
}

void fillContainerStringKeyRequestInLoopWithParameter(lb_I_Container* container, int howMany) {
	lbErrCodes err = ERR_NONE;
	
	container->setCloning(false);
	
	for (int i = 1; i <= howMany; i++) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, IData)
		UAP_REQUEST(getModuleInstance(), lb_I_String, SKey)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, P1)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N1)
		UAP_REQUEST(getModuleInstance(), lb_I_String, P2)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N2)
		UAP_REQUEST(getModuleInstance(), lb_I_String, P3)
		UAP_REQUEST(getModuleInstance(), lb_I_String, N3)
		
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
		
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		QI(SKey, lb_I_KeyBase, key)
		QI(param, lb_I_Unknown, uk)
		
		IData->setData(i);
		*SKey = "Huge keydata ";
		*SKey += IData->charrep();
		
		*P1 = "Parameter ";
		*P1 += IData->charrep();
		*N1 = "Parameter ";
		*N1 += IData->charrep();
		*P2 = "Parameter ";
		*P2 += IData->charrep();
		*N2 = "Parameter ";
		*N2 += IData->charrep();
		*P3 = "Parameter ";
		*P3 += IData->charrep();
		*N3 = "Parameter ";
		*N3 += IData->charrep();
		
		param->setUAPString(*&N1, *&P1);
		param->setUAPString(*&N2, *&P2);
		param->setUAPString(*&N3, *&P3);
		
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
	
	{
		mm = getModuleInstance();
		mm->setModuleManager(mm, __FILE__, __LINE__);
		
		_CL_LOG << "Test MetaApplication" LOG_
		
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(mm, lb_I_String, s)
		
		//UAP_REQUEST(mm, lb_I_MetaApplication, meta)
		
		UAP_REQUEST(mm, lb_I_Container, container)
		UAP_REQUEST(mm, lb_I_Container, container1)
		
		container->setCloning(true);
		fillContainer(*&container);
		
		container->deleteAll();

		printContainer(*&container);
		
		container1->setCloning(false);
		container->deleteAll();
		
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
		
		container->deleteAll();
		
		_LOG << "Test with 10." LOG_
		fillContainer(*&container, 10);
		_LOG << "Test with 100." LOG_
		fillContainer(*&container, 100);
		_LOG << "Test with 1000." LOG_
		fillContainer(*&container, 1000);
/*
		_LOG << "Test with 10000." LOG_
		fillContainer(*&container, 10000);
		_LOG << "Test with 100000." LOG_
		fillContainer(*&container, 100000);
		_LOG << "Done testing" LOG_
*/		
		container->deleteAll();
		
		_LOG << "Test stringkey with 10." LOG_
		fillContainerStringKey(*&container, 10);
		_LOG << "Test stringkey with 100." LOG_
		fillContainerStringKey(*&container, 100);
		_LOG << "Test stringkey with 1000." LOG_
		fillContainerStringKey(*&container, 1000);
/*
		_LOG << "Test stringkey with 10000." LOG_
		fillContainerStringKey(*&container, 10000);
		_LOG << "Test stringkey with 100000." LOG_
		fillContainerStringKey(*&container, 100000);
		_LOG << "Done testing" LOG_
*/
		
		container->deleteAll();
		
		_LOG << "Test request in loop with 10." LOG_
		fillContainerRequestInLoop(*&container, 10);
		_LOG << "Test request in loop with 100." LOG_
		fillContainerRequestInLoop(*&container, 100);
		_LOG << "Test request in loop with 1000." LOG_
		fillContainerRequestInLoop(*&container, 1000);
/*
		_LOG << "Test request in loop with 10000." LOG_
		fillContainerRequestInLoop(*&container, 10000);
		_LOG << "Test request in loop with 100000." LOG_
		fillContainerRequestInLoop(*&container, 100000);
		_LOG << "Done testing" LOG_
*/
		
		container->deleteAll();
		
		_LOG << "Test request in loop stringkey with 10." LOG_
		fillContainerStringKeyRequestInLoop(*&container, 10);
		_LOG << "Test request in loop stringkey with 100." LOG_
		fillContainerStringKeyRequestInLoop(*&container, 100);
		_LOG << "Test request in loop stringkey with 1000." LOG_
		fillContainerStringKeyRequestInLoop(*&container, 1000);
/*
		_LOG << "Test request in loop stringkey with 10000." LOG_
		fillContainerStringKeyRequestInLoop(*&container, 10000);
		_LOG << "Test request in loop stringkey with 100000." LOG_
		fillContainerStringKeyRequestInLoop(*&container, 100000);
		_LOG << "Done testing" LOG_
*/		
		container->deleteAll();
		
		_LOG << "Test request in loop with parameter with 10." LOG_
		fillContainerRequestInLoopWithParameter(*&container, 10);
		_LOG << "Test request in loop with parameter with 100." LOG_
		fillContainerRequestInLoopWithParameter(*&container, 100);
		_LOG << "Test request in loop with parameter with 1000." LOG_
		fillContainerRequestInLoopWithParameter(*&container, 1000);
/*
		_LOG << "Test request in loop with parameter with 10000." LOG_
		fillContainerRequestInLoopWithParameter(*&container, 10000);
		_LOG << "Test request in loop with parameter with 100000." LOG_
		fillContainerRequestInLoopWithParameter(*&container, 100000);
		_LOG << "Done testing" LOG_
*/		
		container->deleteAll();
		
		_LOG << "Test request in loop with parameter stringkey with 10." LOG_
		fillContainerStringKeyRequestInLoopWithParameter(*&container, 10);
		_LOG << "Test request in loop with parameter stringkey with 100." LOG_
		fillContainerStringKeyRequestInLoopWithParameter(*&container, 100);
		_LOG << "Test request in loop with parameter stringkey with 1000." LOG_
		fillContainerStringKeyRequestInLoopWithParameter(*&container, 1000);
/*
		_LOG << "Test request in loop with parameter stringkey with 10000." LOG_
		fillContainerStringKeyRequestInLoopWithParameter(*&container, 10000);
		_LOG << "Test request in loop with parameter stringkey with 100000." LOG_
		fillContainerStringKeyRequestInLoopWithParameter(*&container, 100000);
		_LOG << "Done testing" LOG_
*/
	}
	
	unHookAll();
	
	exit(0);
	return 0;
}

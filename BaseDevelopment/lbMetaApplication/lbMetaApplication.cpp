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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.27 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.27 2003/07/15 22:18:05 lollisoft Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
 * Revision 1.27  2003/07/15 22:18:05  lollisoft
 * Removed debug messages, implemented numeric dispatcher and much more
 *
 * Revision 1.26  2003/07/10 21:13:06  lollisoft
 * Adding menu entry implemented
 *
 * Revision 1.25  2003/03/14 16:00:36  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.24  2003/02/17 21:34:34  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.23  2003/02/09 13:22:50  lothar
 * Different log usage
 *
 * Revision 1.22  2003/01/27 21:18:04  lothar
 * Missed STARTREF setup
 *
 * Revision 1.21  2003/01/19 17:31:31  lothar
 * Runs now with MSC
 *
 * Revision 1.20  2003/01/15 22:42:20  lothar
 * Compiles with MSC
 *
 * Revision 1.19  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.18  2002/12/12 20:59:38  lothar
 * Now it runs under Linux again
 *
 * Revision 1.17  2002/12/08 17:07:23  lothar
 * More tries to run under linux
 *
 * Revision 1.16  2002/11/29 19:50:26  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.15  2002/11/08 18:53:25  lothar
 * Compiles now (-d1)
 *
 * Revision 1.13  2002/10/04 16:53:11  lothar
 * Replaced old LOG macro with the new
 * _LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.12  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.11  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.10  2002/09/17 04:26:36  lothar
 * First API-Callback works
 *
 * Revision 1.9  2002/09/12 18:34:02  lothar
 * Added some UI wrapper and sub module creation. Cleanup
 *
 * Revision 1.8  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.7  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.6  2002/08/21 17:59:42  lothar
 * More functions implemented
 *
 * Revision 1.5  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.4  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.3  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/
#define LB_METAAPP_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

#include <lbmetaapp-module.h>

#include <lbMetaApplication.h>
/*...e*/

/*...sFunctors:0:*/
#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)
IMPLEMENT_FUNCTOR(instanceOfEventMapper, lb_EventMapper)
IMPLEMENT_FUNCTOR(instanceOfEvHandler, lb_EvHandler)

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDispatcher, lb_Dispatcher)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfEventManager, lb_EventManager)

#ifdef __cplusplus
}
#endif            
/*...e*/


/*...slb_MetaApplication:0:*/
/*...sctors\47\dtors:0:*/
lb_MetaApplication::lb_MetaApplication() {
	ref = STARTREF;
	gui = NULL;
	printf("Instance of lb_I_MetaApplication created\n");
	_LOG << "Instance of lb_I_MetaApplication created" LOG_
}

lb_MetaApplication::~lb_MetaApplication() {
	_LOG << "Instance of lb_I_MetaApplication destroyed" LOG_
}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler1, "getBasicApplicationInfo");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler2, "getMainModuleInfo");

	return ERR_NONE;
}
/*...e*/

/*...sevent handlers\44\ that can be registered:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler1(lb_I_Unknown* uk) {
	_LOG << "lb_MetaApplication::lbEvHandler1() called" LOG_
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler2(lb_I_Unknown* uk) {
	_LOG << "lb_MetaApplication::lbEvHandler2() called" LOG_

	if (gui != NULL) {
	        gui->msgBox("Information", "getMainModuleInfo called up");
	} else {
	        cout << "lb_MetaApplication::Initialize() called in console mode" << endl;
	}

	return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	_LOG << "lb_MetaApplication::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager \42\ lb_MetaApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager * lb_MetaApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\Initialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::Initialize() {
/*...sdoc:8:*/
/**
 * At this point should be found the real application. The real one
 * may be defined by an environment variable, that is defined out of
 * a batch file.
 * The variable contains the name of the application, where a xml tag
 * resolves the functor for this application.
 */
/*...e*/
	char* applicationName = getenv("TARGET_APPLICATION");

/*...sdispatch integer values:8:*/
	/*
	 * This variable is needed, if this instance also implements a little dispatcher.
	 * It should moved into the class declatation and used in the dispatch functions.
	 */
	int getBasicApplicationInfo;
	int getMainModuleInfo;
/*...e*/

/*...sget the event manager:8:*/
	/**
	 * Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */
	
	lb_I_Module* m = *&manager;
	printf("Get an event manager\n");
	REQUEST(m, lb_I_EventManager, eman)
/*...e*/
	
/*...sregister a basic event \40\getBasicApplicationInfo\41\ by the event manager:8:*/
	printf("Register some events\n"); 
	eman->registerEvent("getBasicApplicationInfo", getBasicApplicationInfo);
	eman->registerEvent("getMainModuleInfo", getMainModuleInfo);
	printf("Registered some events\n");

/*...e*/

/*...sget the dispatcher instance:8:*/
	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());
/*...e*/
	printf("Connect the event handlers to the dispatcher\n");	
	registerEventHandler(dispatcher.getPtr());
	printf("Connected\n");

	// Step 3 (Load sub components, handling menus and else needed for an UI)
	loadSubModules();

	/**
	 * After initializion of all event handlers, we need to get up all
	 * GUI accessible handlers - like menus or else.
	 * This class, as an example, provides two handlers
	 * getBasicApplicationInfo and getMainModuleInfo
	 * 
	 * The handler depends on some capabilities:
	 *
	 * 	1. A basic dialog to show text
	 *		This may be a container of capabilities
	 *		 must:SimpleTextDialog
	 *		 optional:PictureElements
	 *
	 * It provides these capabilities:
	 *
	 *	1. An information about menu creation
	 *		This may be a simple string - lb_I_String
	 */


	/**
	 * Init the application (menu, toolbar, accelerators)
	 *
	 * This will be done by the loaded application from the
	 * environment variable (TARGET_APPLICATION)
	 */
	
	printf("Add a menubar\n");
	addMenuBar("Edit");
	_LOG << "Added first menu bar" LOG_
	addMenuBar("Help");
	_LOG << "Added second menu bar" LOG_
	printf("Added menubars\n");
	// Let the GUI show a message box
	
	
	addMenuEntry("Edit", "MainModuleInfo", "getMainModuleInfo", "");
	
	if (gui != NULL) {
		gui->msgBox("Information", "Meta application started up");
		//cout << "lb_MetaApplication::Initialize() called in console mode" << endl;
	} else {
		cout << "lb_MetaApplication::Initialize() called in console mode" << endl;
	}
	addMenuBar("Test");

	return ERR_NONE;
}
/*...e*/


// This starts the main application

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);	
#endif
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::loadSubModules() {
	return ERR_NONE;
}

/*...sBasic functions to be used for a UI application:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuBar(char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	string->setData(name);
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(string, lb_I_Unknown, uk, __FILE__, __LINE__)

	// Avoids GPF while leaving the function
	string++;

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)

	if (uk == NULL) _LOG << "Error: Cannot call with a null pointer!" LOG_
	
	_LOG << "Begin dispatch function" LOG_

// Produces crash
	dispatcher->dispatch("AddMenuBar", uk.getPtr(), &uk_result);
	_LOG << "Have dispatched function" LOG_

	return err;
}

lbErrCodes LB_STDCALL lb_MetaApplication::addMenu(char* name) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	
	
	parameter->setData("menubar");
	value->setData(in_menu);
	param->setUAPString(*&parameter, *&value);
	
	parameter->setData("menuname");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);
	

	return ERR_NONE;
}
/*...e*/
/*...e*/
/*...slb_EventMapper:0:*/
lb_EventMapper::lb_EventMapper() {
	ref = STARTREF;
	_LOG << "Instance of lb_I_EventMapper created" LOG_
	_name = NULL;
}

lb_EventMapper::~lb_EventMapper() {
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventMapper)
	ADD_INTERFACE(lb_I_EventMapper)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_EventMapper::setData(lb_I_Unknown* uk) {
	_LOG << "lb_EventMapper::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EventMapper::setEvent(char* name, lbEvHandler handler) {
	_name = strdup(name);
	return ERR_NONE;
}

char* LB_STDCALL lb_EventMapper::getName() {
	if (_name != NULL) return _name;
	return NULL;
}

int LB_STDCALL lb_EventMapper::getID() {
	return _id;
}

void LB_STDCALL lb_EventMapper::setID(int id) {
	_id = id;
}

/*...e*/

/*...slb_EventManager:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventManager)
	ADD_INTERFACE(lb_I_EventManager)
END_IMPLEMENT_LB_UNKNOWN()

lb_EventManager::lb_EventManager() {
	_LOG << "lb_EventManager::lb_EventManager() called" LOG_
	maxEvId = 0;
	ref = STARTREF;
}

lb_EventManager::~lb_EventManager() {
	_LOG << "lb_EventManager::~lb_EventManager() called" LOG_
}
	
lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	_LOG << "lb_EventManager::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}

/*...slb_EventManager\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_EventManager::registerEvent(char* EvName, int & EvNr) {
	lbErrCodes err = ERR_NONE;
	int newId = maxEvId + 1;

/*...sInit containers:8:*/
	if (events == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, events)

		// For housekeeping	
		REQUEST(manager.getPtr(), lb_I_Container, freeIds)
		
		// The reverse
		REQUEST(manager.getPtr(), lb_I_Container, reverse_events)
	}
/*...e*/
	
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringData)
	stringData->setData(EvName);
	
	UAP(lb_I_KeyBase, sk, __FILE__, __LINE__)
	QI(stringData, lb_I_Unknown, sk, __FILE__, __LINE__)
/*...e*/
	
/*...sError handling:8:*/
	if (events == NULL) _LOG << "Nullpointer detected (events)!" LOG_
	if (*&sk == NULL) _LOG << "Nullpointer detected (sk)!" LOG_
	if (events->exists(&sk) == 1) {
		_LOG << "lb_EventManager::registerEvent(): Error: Event schon registriert" LOG_
		return ERR_EVENT_EXISTS;
	}
/*...e*/
/*...sdetermine id:8:*/
	if (freeIds->Count() == 0) {
		maxEvId++;
	} else {
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

		key = freeIds->getKeyAt(freeIds->Count());
		uk = freeIds->getElementAt(freeIds->Count());
		
		freeIds->remove(&key);
			
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		QI(uk, lb_I_Integer, i, __FILE__, __LINE__)

		newId = i->getData();
	}
/*...e*/
/*...sinsert new event:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerData)
	integerData->setData(maxEvId);
	
	UAP(lb_I_Unknown, idata, __FILE__, __LINE__)
	QI(integerData, lb_I_Unknown, idata, __FILE__, __LINE__)

	events->insert(&idata, &sk);
	
	UAP(lb_I_KeyBase, ik, __FILE__, __LINE__)
	QI(integerData, lb_I_Unknown, ik, __FILE__, __LINE__)

	UAP(lb_I_Unknown, sdata, __FILE__, __LINE__)
	QI(stringData, lb_I_Unknown, sdata, __FILE__, __LINE__)
	
	reverse_events->insert(&sdata, &ik);
	
	EvNr = maxEvId;
/*...e*/

	if (events->exists(&sk) != 1) {
		_LOG << "lb_EventManager::registerEvent(): Error: Event could not be registered" LOG_
		return ERR_EVENT_NOTREGISTERED;
	}
	
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_EventManager::resolveEvent(char* EvName, int & evNr) {
	lbErrCodes err = ERR_NONE;
	
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey)
	stringKey->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	stringKey->setData(EvName);
	
	UAP(lb_I_KeyBase, kk, __FILE__, __LINE__)
	QI(stringKey, lb_I_Unknown, kk, __FILE__, __LINE__)
/*...e*/

/*...sresolve event:8:*/
	if (events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object, __FILE__, __LINE__)
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		
		object = events->getElement(&kk);
		QI(object, lb_I_Integer, i, __FILE__, __LINE__)
		evNr = i->getData();
	} else {
		_LOG << "Error: Event name not registered" LOG_
	}
/*...e*/

	return ERR_NONE;
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {
	_LOG << "lb_Dispatcher::lb_Dispatcher() called" LOG_
	ref = STARTREF;
}

lb_Dispatcher::~lb_Dispatcher() {
	_LOG << "lb_Dispatcher::~lb_Dispatcher() called" LOG_
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	_LOG << "lb_Dispatcher::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setEventManager\40\lb_I_EventManager\42\ EvManager\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setEventManager(lb_I_EventManager* EvManager) {
	_LOG << "lb_Dispatcher::setEventManager() called" LOG_
	
	evManager = EvManager;
	evManager++;
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName) {
	/*
	 * Create an instance of a function pointer object
	 */
	
	int id = 0;
	evManager->resolveEvent(EvName, id);
	addEventHandlerFn(evHandlerInstance, evHandler, id);	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ int EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) {
	lbErrCodes err = ERR_NONE;
	
	if (dispatcher == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, dispatcher)
		dispatcher->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	}

	UAP_REQUEST(manager.getPtr(), lb_I_EvHandler, evH)
	evH->setHandler(evHandlerInstance, evHandler);

	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setData(EvNr);

	  UAP(lb_I_KeyBase, k, __FILE__, __LINE__)
	QI(i, lb_I_KeyBase, k, __FILE__, __LINE__)

	    UAP(lb_I_Unknown, e, __FILE__, __LINE__)
	QI(evH, lb_I_Unknown, e, __FILE__, __LINE__)
	if (dispatcher->exists(&k) == 1) {
        	dispatcher->remove(&k);
	}

	if ((err = dispatcher->insert(&e, &k)) != ERR_NONE) _LOG << "Error: Inserting new container element failed" LOG_

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)

	uk = dispatcher->getElement(&k);
	
	if (uk == NULL) _LOG << "Error: Adding event handler failed (not stored)" LOG_

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	_LOG << "lb_Dispatcher::addDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delDispatcher(lb_I_Dispatcher* disp) {
	_LOG << "lb_Dispatcher::delDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slb_I_DispatchResponce\42\ lb_Dispatcher\58\\58\dispatch\40\lb_I_DispatchRequest\42\ req\41\:0:*/
lb_I_DispatchResponce* lb_Dispatcher::dispatch(lb_I_DispatchRequest* req) {
	_LOG << "lb_Dispatcher::dispatch() called" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\int EvNr\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	_LOG << "lb_Dispatcher::dispatchEvent() called" LOG_

	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setData(EvNr);
	_LOG << "Set the event id" LOG_
	
	UAP(lb_I_KeyBase, ik, __FILE__, __LINE__)
	QI(i, lb_I_KeyBase, ik, __FILE__, __LINE__)
	
	
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_EvHandler, ev, __FILE__, __LINE__)
	
	_LOG <<"Get the handler out from the dispatcher" LOG_
	
	if (dispatcher == NULL) {
		_LOG << "Error: Have no dispatcher" LOG_
	} else {
	
		uk = dispatcher->getElement(&ik);
	
		if (uk == NULL) {
			_LOG << "Error: Could not get the handler from the id" LOG_
			return ERR_DISPATCH_FAILS;
		}
	
		QI(uk, lb_I_EvHandler, ev, __FILE__, __LINE__)

		ev->call(EvData, EvResult);
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {

	int id = 0;
	lbErrCodes err = ERR_NONE;
	
	_LOG << "Resolve handler now " << EvName LOG_
	evManager->resolveEvent(EvName, id);
	_LOG << "Resolved handler now " << EvName LOG_

	return dispatch(id, EvData, EvResult);
}
/*...e*/
/*...e*/

/*...slb_EvHandler:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EvHandler)
	ADD_INTERFACE(lb_I_EvHandler)
END_IMPLEMENT_LB_UNKNOWN()

lb_EvHandler::lb_EvHandler() {
	ev = NULL;
	ref = STARTREF;
}

lb_EvHandler::~lb_EvHandler() {
	_LOG << "lb_EvHandler::~lb_EvHandler() called" LOG_
}

lbEvHandler LB_STDCALL lb_EvHandler::getHandler() {
	return ev;
}

lbErrCodes LB_STDCALL lb_EvHandler::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_EvHandler, eh, __FILE__, __LINE__)
	QI(uk, lb_I_EvHandler, eh, __FILE__, __LINE__)
	
	setHandler(eh->getHandlerInstance(), eh->getHandler());
	
	return ERR_NONE;
}

lb_I_EventHandler* LB_STDCALL lb_EvHandler::getHandlerInstance() {
	return _evHandlerInstance;
}

lbErrCodes LB_STDCALL lb_EvHandler::setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) {
	_evHandlerInstance = evHandlerInstance;
	ev = evHandler;
	return ERR_NONE;
}


lbErrCodes LB_STDCALL lb_EvHandler::call(lb_I_Unknown* evData, lb_I_Unknown** evResult) {
	(_evHandlerInstance->*(lbEvHandler) ev) (evData);
	
	return ERR_NONE;
}
/*...e*/

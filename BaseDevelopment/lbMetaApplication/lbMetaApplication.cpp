/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.7 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.7 2002/09/04 17:52:12 lothar Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
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

/*...slb_EvHandler:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EvHandler)
	ADD_INTERFACE(lb_I_EvHandler)
END_IMPLEMENT_LB_UNKNOWN()

lb_EvHandler::lb_EvHandler() {
	ev = NULL;
}

lb_EvHandler::~lb_EvHandler() {
	LOG("lb_EvHandler::~lb_EvHandler() called")
}

lbErrCodes LB_STDCALL lb_EvHandler::setData(lb_I_Unknown* uk) {
	LOG("lb_EvHandler::setData() has not been implemented");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EvHandler::setHandler(lbEvHandler evHandler) {
	ev = evHandler;
	return ERR_NONE;
}

lbEvHandler LB_STDCALL lb_EvHandler::getHandler() {
	return ev;
}
/*...e*/

/*...slb_MetaApplication:0:*/
lb_MetaApplication::lb_MetaApplication() {
	ref = STARTREF;
	LOG("Instance of lb_I_MetaApplication created")
}

lb_MetaApplication::~lb_MetaApplication() {
	LOG("Instance of lb_I_MetaApplication destroyed")
}


lbErrCodes LB_STDCALL lb_MetaApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	disp->addEventHandlerFn((lbEvHandler) lbEvHandler1, "getBasicApplicationInfo");
	disp->addEventHandlerFn((lbEvHandler) lbEvHandler2, "getMainModuleInfo");

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler1(lb_I_Unknown* uk) {
	LOG("lb_MetaApplication::lbEvHandler1() called")
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler2(lb_I_Unknown* uk) {
	LOG("lb_MetaApplication::lbEvHandler2() called")
	return ERR_NONE;
}


BEGIN_IMPLEMENT_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	LOG("lb_MetaApplication::setData() has not been implemented");
	
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
/**
 * At this point should be found the real application. The real one
 * may be defined by an environment variable, that is defined out of
 * a batch file.
 * The variable contains the name of the application, where a xml tag
 * resolves the functor for this application.
 */


	char* applicationName = getenv("TARGET_APPLICATION");

	/*
	 * This variable is needed, if this instance also implements a little dispatcher.
	 * It should moved into the class declatation and used in the dispatch functions.
	 */
	int getBasicApplicationInfo;
	int getMainModuleInfo;

	/**
	 * Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */
	
	lb_I_Module* m = *&manager;

	REQUEST(m, lb_I_EventManager, eman)
	eman->setModuleManager(m, __FILE__, __LINE__);
	
	// Step 1
/*...sregister a basic event \40\getBasicApplicationInfo\41\ by the event manager:8:*/
	 
	eman->registerEvent("getBasicApplicationInfo", getBasicApplicationInfo);
	eman->registerEvent("getMainModuleInfo", getMainModuleInfo);

	char buf[1000] = "";
	
	sprintf(buf, "Registered an event 'getBasicApplicationInfo' as %d", getBasicApplicationInfo);
	
	LOG(buf)

	sprintf(buf, "Registered an event 'getMainModuleInfo' as %d", getMainModuleInfo);
	
	LOG(buf)
/*...e*/

/*...s\63\\63\\63\:8:*/
/*...srequest a reference object \63\\63\:16:*/
/*
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	
	if (manager != NULL) {
		manager->request("lb_I_Reference", &uk);
		
		UAP(lb_I_Reference, ref, __FILE__, __LINE__)
		
		uk->queryInterface("lb_I_Reference", (void**) &ref, __FILE__, __LINE__);
	
		//gui->queryEvent("getFrame", ref);
	}
*/
/*...e*/
	
/*...s\63\\63\\63\:16:*/
	/*
	 * 1. Let the GUI server setup his events, that it can handle
	 * 	This should be done before this function will be called
	 *	from the GUI server.
	 */
	
	
	/*
	UAP(lb_I_Frame, frame, __FILE__, __LINE__)
	
	frame = gui->getFrame();
	
	frame->registerEvent("quit",  LB_COMMAND_MENU_SELECTED, frame->getDispatcherFn());
	frame->registerEvent("about", LB_COMMAND_MENU_SELECTED, frame->getDispatcherFn());
	*/
/*...e*/
/*...e*/
	
	// Step 2
	REQUEST(m, lb_I_Dispatcher, dispatcher)

	dispatcher->setEventManager(eman.getPtr());
	dispatcher->setModuleManager(m, __FILE__, __LINE__);
		
	registerEventHandler(dispatcher.getPtr());
	

	// Let the GUI show a message box
	
	gui->msgBox("Information", "Meta application started up");

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::run() {

	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);	

	return ERR_NONE;
}
/*...e*/
/*...e*/
/*...slb_EventMapper:0:*/
lb_EventMapper::lb_EventMapper() {
	ref = STARTREF;
	LOG("Instance of lb_I_EventMapper created")
	_name = NULL;
}

lb_EventMapper::~lb_EventMapper() {
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventMapper)
	ADD_INTERFACE(lb_I_EventMapper)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_EventMapper::setData(lb_I_Unknown* uk) {
	LOG("lb_EventMapper::setData() has not been implemented");
	
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
	LOG("lb_EventManager::lb_EventManager() called")
	maxEvId = 0;
}

lb_EventManager::~lb_EventManager() {
	LOG("lb_EventManager::~lb_EventManager() called")
}
	
lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	LOG("lb_EventManager::setData() has not been implemented");
	
	return ERR_NONE;
}

/*...slb_EventManager\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_EventManager::registerEvent(char* EvName, int & EvNr) {
	char buf[100] = "";
	lbErrCodes err = ERR_NONE;

/*...sInit containers:8:*/
	if (events == NULL) {
		LOG("Create the instance of event containers")
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, events)
		events->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

		// For housekeeping	
		REQUEST(manager.getPtr(), lb_I_Container, freeIds)
		freeIds->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	}
/*...e*/
	
	sprintf(buf, "lb_EventManager::registerEvent(%s)", EvName);
	LOG(buf)
	
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey)
	stringKey->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	stringKey->setData(EvName);
	
	UAP(lb_I_KeyBase, kk, __FILE__, __LINE__)
	QI(stringKey, lb_I_Unknown, kk, __FILE__, __LINE__)
/*...e*/
	
	LOG("Test if event is still registered")
	
/*...sError handling:8:*/
	if (events == NULL) LOG("Nullpointer detected (events)!")
	if (*&kk == NULL) LOG("Nullpointer detected (kk)!")
	if (events->exists(&kk) == 1) {
		LOG("lb_EventManager::registerEvent(): Error: Event schon registriert")
		return ERR_EVENT_EXISTS;
	}
/*...e*/
	
	LOG("Determine id")
/*...sdetermine id:8:*/
	if (freeIds->Count() == 0) {
		maxEvId++;
	} else {
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
		
		uk = freeIds->getElementAt(0);
		key = freeIds->getKeyAt(0);
		
		freeIds->remove(&key);
		
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		QI(uk, lb_I_Integer, i, __FILE__, __LINE__)
		maxEvId = i->getData();
	}
/*...e*/
	
	LOG("Insert new")
/*...sinsert new event:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, newKey)
	newKey->setData(maxEvId);
	
	UAP(lb_I_Unknown, k, __FILE__, __LINE__)
	QI(newKey, lb_I_Unknown, k, __FILE__, __LINE__)

	events->insert(&k, &kk);
	
	EvNr = maxEvId;
/*...e*/
	
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_EventManager::resolveEvent(char* EvName, int & evNr) {
	lbErrCodes err = ERR_NONE;
#ifdef bla
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey)
	stringKey->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	stringKey->setData(EvName);
	
	UAP(lb_I_KeyBase, kk, __FILE__, __LINE__)
	QI(stringKey, lb_I_Unknown, kk, __FILE__, __LINE__)
/*...e*/


	if (events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object, __FILE__, __LINE__)
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		
		object = events->getElement(&kk);
		QI(object, lb_I_Integer, i, __FILE__, __LINE__)
		
		evNr = i->getData();
	}
#endif
	return ERR_NONE;
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {
	LOG("lb_Dispatcher::lb_Dispatcher() called")
}

lb_Dispatcher::~lb_Dispatcher() {
}

lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	LOG("lb_Dispatcher::setData() has not been implemented");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::setEventManager(lb_I_EventManager* EvManager) {
	LOG("lb_Dispatcher::setEventManager() called")
	
	evManager = EvManager;
	
	return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lbEvHandler evHandler, char* EvName) {
	LOG("lb_Dispatcher::addEventHandlerFn(lbEvHandler evHandler, char* EvName) called")
	

	/*
	 * Create an instance of a function pointer object
	 */
	
	int id = 0;
	evManager->resolveEvent(EvName, id);
	LOG("Resolved EvName")

	addEventHandlerFn(evHandler, id);	

	LOG("Added event handler id")
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lbEvHandler evHandler\44\ int EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lbEvHandler evHandler, int EvNr) {
	lbErrCodes err = ERR_NONE;
	
	LOG("lb_Dispatcher::addEventHandlerFn(lbEvHandler evHandler, int EvNr) called")
	
	if (dispatcher == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, dispatcher)
		dispatcher->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	}

	UAP_REQUEST(manager.getPtr(), lb_I_EvHandler, evH)
	evH->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	i->setData(EvNr);

	  UAP(lb_I_KeyBase, k, __FILE__, __LINE__)
	QI(i, lb_I_KeyBase, k, __FILE__, __LINE__)

	    UAP(lb_I_Unknown, e, __FILE__, __LINE__)
	QI(evH, lb_I_Unknown, e, __FILE__, __LINE__)

	if (dispatcher->exists(&k) == 1) {
		LOG("Warning: Overwriting existing event handler")
        	dispatcher->remove(&k);
        	LOG("Removed old event handler")
	}
	LOG("Insert a dispatch handler")
	dispatcher->insert(&e, &k);
	LOG("Inserted")
	
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	LOG("lb_Dispatcher::addDispatcher() called")
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::delDispatcher(lb_I_Dispatcher* disp) {
	LOG("lb_Dispatcher::delDispatcher() called")
	return ERR_NONE;
}

lb_I_DispatchResponce* lb_Dispatcher::dispatch(lb_I_DispatchRequest* req) {
	LOG("lb_Dispatcher::dispatch() called")
	return NULL;
}

lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	LOG("lb_Dispatcher::dispatchEvent() called")
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	LOG("lb_Dispatcher::dispatch() called (not implemented yet")
	return ERR_NONE;
}
/*...e*/

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.2 2002/02/25 06:13:07 lothar Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/
#define LB_METAAPP_DLL
/*...sincludes:0:*/
#include <lbmetaapp-module.h>


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

#include <lbMetaApplication.h>
/*...e*/

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)
IMPLEMENT_FUNCTOR(instanceOfEventMapper, lb_EventMapper)

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDispatcher, lb_Dispatcher)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfEventManager, lb_EventManager)

#ifdef __cplusplus
}
#endif            

/*...slb_MetaApplication:0:*/
lb_MetaApplication::lb_MetaApplication() {
	ref = STARTREF;
	LOG("Instance of lb_I_MetaApplication created")
}

lb_MetaApplication::~lb_MetaApplication() {
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	LOG("lb_MetaApplication::setData() has not been implemented");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::Initialize() {
/**
 * At this point should be found the real application. The real one
 * may be defined by an environment variable, that is defined out of
 * a batch file.
 * The variable contains the name of the application, where a xml tag
 * resolves the functor for this application.
 */


	char* applicationName = getenv("TARGET_APPLICATION");

	int getBasicApplicationInfo;

	/**
	 * Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */
	
	REQUEST(manager, lb_I_EventManager, eman)
	 
	eman->registerEvent("getBasicApplicationInfo", getBasicApplicationInfo);

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	
	if (manager != NULL) {
		manager->request("lb_I_Reference", &uk);
		
		UAP(lb_I_Reference, ref, __FILE__, __LINE__)
		
		uk->queryInterface("lb_I_Reference", (void**) &ref, __FILE__, __LINE__);
	
		//gui->queryEvent("getFrame", ref);
	}
	


	




	return ERR_NONE;
}
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
}

lb_EventManager::~lb_EventManager() {
}
	
lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	LOG("lb_EventManager::setData() has not been implemented");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EventManager::registerEvent(char* EvName, int & EvNr) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EventManager::resolveEvent(char* EvName, int & evNr) {
	return ERR_NONE;
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {
}

lb_Dispatcher::~lb_Dispatcher() {
}

lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	LOG("lb_Dispatcher::setData() has not been implemented");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::setEventManager(lb_I_EventManager* EvManager) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::dispatchEvent(int EvNr, lb_I_Unknown* EvData) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_Dispatcher::queryEvent(char* EvName, lb_I_Unknown* EvData) {
	return ERR_NONE;
}
/*...e*/

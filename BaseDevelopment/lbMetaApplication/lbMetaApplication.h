/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.8 $
 * $Name:  $
 * $Id: lbMetaApplication.h,v 1.8 2002/09/12 18:32:59 lothar Exp $
 *
 * $Log: lbMetaApplication.h,v $
 * Revision 1.8  2002/09/12 18:32:59  lothar
 * Added some UI wrapper and sub module creation
 *
 * Revision 1.7  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.6  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.5  2002/08/21 18:00:28  lothar
 * Added UAP variables
 *
 * Revision 1.4  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.3  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/

#ifndef _LB_METAAPP_
#define _LB_METAAPP_

#include <stdio.h>
#include <lbInterfaces.h>


/*...sclass lb_MetaApplication:0:*/
class lb_MetaApplication : 
public lb_I_MetaApplication,
public lb_I_EventHandler
{
public:
	lb_MetaApplication();
	virtual ~lb_MetaApplication();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	
	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	virtual lbErrCodes LB_STDCALL Initialize();
	virtual lbErrCodes LB_STDCALL run();
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);

	virtual lb_I_EventManager * getEVManager( void );

	void LB_STDCALL getBasicApplicationInfo(lb_I_Unknown** info);
	

	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	
	
	lbErrCodes LB_STDCALL loadSubModules();

	lbErrCodes LB_STDCALL lbEvHandler1(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbEvHandler2(lb_I_Unknown* uk);

/*...sWrapper for some usual GUI functions:8:*/

	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	virtual lbErrCodes LB_STDCALL addMenuBar(char* name);

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(char* name);
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL);
	
/*...e*/
	

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman, __FILE__, __LINE__)
	UAP(lb_I_Dispatcher, dispatcher, __FILE__, __LINE__)
};
/*...e*/
/*...sclass lb_EventMapper:0:*/
class lb_EventMapper :
public lb_I_EventMapper
{
public:
        lb_EventMapper();
        virtual ~lb_EventMapper();

        DECLARE_LB_UNKNOWN()

        /**
         * If handler is NULL, then the event manager knows, that the requesting
         * instance has a dispatcher and therefore handles it self. You must register
         * the dispatcher after all requested id's for your events.
         */
        virtual lbErrCodes LB_STDCALL setEvent(char* name, lbEvHandler handler = NULL);
        /**
         * Get the id back.
         */
        virtual int LB_STDCALL getID();	
        
protected:
	virtual char* LB_STDCALL getName();
        virtual void LB_STDCALL setID(int id);

	friend class lb_I_EventManager;
        
	char* _name;
	int _id;
};
/*...e*/

/*...sclass lb_Dispatcher:0:*/
class lb_Dispatcher : public lb_I_Dispatcher {
public:
	lb_Dispatcher();
	virtual ~lb_Dispatcher();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setEventManager(lb_I_EventManager* EvManager);
	virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp);
	virtual lbErrCodes LB_STDCALL delDispatcher(lb_I_Dispatcher* disp);
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName);
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr);
	
	/**
	 * ID variant
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	/**
	 * Name variant
	 *
	 * This variant let's the programmer issue any events from his/her module.
	 * As a sample, it must be possible to query from an event name an id.
	 * Also it must be possible to call this function to announce a handler.
	 * 
	 * This may be solved this way:
	 * EvName = "AnnounceHandler"
	 * EvData = lb_I_HandlerAddress
	 */
	virtual lbErrCodes LB_STDCALL dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	
	virtual lb_I_DispatchResponce* dispatch(lb_I_DispatchRequest* req);
	
	UAP(lb_I_Container, dispatcher, __FILE__, __LINE__)
	UAP(lb_I_EventManager, evManager, __FILE__, __LINE__)
};
/*...e*/
/*...sclass lb_EventManager:0:*/
class lb_EventManager : public lb_I_EventManager {
public:
	lb_EventManager();
	virtual ~lb_EventManager();
	
	DECLARE_LB_UNKNOWN()
	
	virtual lbErrCodes LB_STDCALL registerEvent(char* EvName, int & EvNr);
	virtual lbErrCodes LB_STDCALL resolveEvent(char* EvName, int & evNr);

protected:


	friend class lb_I_Dispatcher;

	// Maps id to event name	
	UAP(lb_I_Container, events, __FILE__, __LINE__)
	
	// Holds free id
	UAP(lb_I_Container, freeIds, __FILE__, __LINE__)
	
	// Reverse mapping name -> id
	UAP(lb_I_Container, reverse_events, __FILE__, __LINE__)
	
	int maxEvId;
};
/*...e*/

/*...sclass lb_EvHandler:0:*/
class lb_EvHandler : public lb_I_EvHandler {
public:
	lb_EvHandler();
	virtual ~lb_EvHandler();

	DECLARE_LB_UNKNOWN()
        
	virtual lbErrCodes LB_STDCALL setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler);
        virtual lbEvHandler LB_STDCALL getHandler();
        virtual lb_I_EventHandler* LB_STDCALL getHandlerInstance();

	virtual lbErrCodes LB_STDCALL call(lb_I_Unknown* evData, lb_I_Unknown** evResult);
        
        lb_I_EventHandler* _evHandlerInstance;
        lbEvHandler ev;
};
/*...e*/

/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DECLARE_FUNCTOR(instanceOfMetaApplication)
DECLARE_FUNCTOR(instanceOfEventMapper)
DECLARE_FUNCTOR(instanceOfEvHandler)

DECLARE_SINGLETON_FUNCTOR(instanceOfDispatcher)
DECLARE_SINGLETON_FUNCTOR(instanceOfEventManager)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_OBJECT

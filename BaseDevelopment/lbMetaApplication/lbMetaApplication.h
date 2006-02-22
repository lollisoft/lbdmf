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
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.31 $
 * $Name:  $
 * $Id: lbMetaApplication.h,v 1.31 2006/02/22 11:49:57 lollisoft Exp $
 *
 * $Log: lbMetaApplication.h,v $
 * Revision 1.31  2006/02/22 11:49:57  lollisoft
 * Moved the general part to meta application. wxWrapper does ask for it when left panel will be shown.
 *
 * Revision 1.30  2006/02/21 19:35:50  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.29  2006/02/19 18:41:35  lollisoft
 * Feedback of properties works good. I am use the
 * dispatcher mechanism to forward the change events
 * on per lb_I_Parameter instance and the category name
 * to a registered handler.
 *
 * So one handler must be capable to recieve values for all
 * elements of one lb_I_Parameter instance.
 *
 * Revision 1.28  2006/02/17 23:57:16  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.27  2006/01/30 15:54:14  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.26  2006/01/26 14:03:23  lollisoft
 * Added event en/disable and toggle functions. Also added
 * askYesNo function.
 *
 * Revision 1.25  2006/01/21 23:48:14  lollisoft
 * Added new member to ask the user for a file.
 *
 * Revision 1.24  2005/11/18 23:41:31  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.23  2005/11/16 13:17:03  lollisoft
 * Added Memtrack breakpoint counter.
 *
 * Corrected reference count bug by using UAP for 'a' and using preload to
 * delegate unloading of shared library, loaded by loadApplication into
 * destructor.
 *
 * Revision 1.22  2005/06/20 11:18:46  lollisoft
 * Added interface set/get User and ApplicationName
 *
 * Revision 1.21  2005/06/01 10:57:22  lollisoft
 * Replaced DEBUG_UAP with UAP
 *
 * Revision 1.20  2005/03/31 08:59:34  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.19  2005/01/05 13:41:36  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.18  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.17  2004/07/16 20:24:41  lollisoft
 * Added handler to enter into the debugger
 *
 * Revision 1.16  2004/01/24 16:17:29  lollisoft
 * Added support for loading application
 *
 * Revision 1.15  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.14  2003/08/22 17:38:35  lollisoft
 * Implemented a handler for a button press event and code to demonstrate
 *
 * Revision 1.13  2003/08/16 18:03:53  lollisoft
 * Added my new address due to move
 *
 * Revision 1.12  2003/03/14 16:00:38  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.11  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.10  2002/10/08 16:33:38  lothar
 * Missing LB_STDCALL
 *
 * Revision 1.9  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
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
	lbErrCodes LB_STDCALL Initialize(char* user = NULL, char* app = NULL);
	lbErrCodes LB_STDCALL run();
	lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);

	lbErrCodes LB_STDCALL setUserName(char* user);
	lbErrCodes LB_STDCALL setApplicationName(char* app);

	void	   LB_STDCALL setAutoload(bool b);
	void	   LB_STDCALL setAutoselect(bool b);
	bool	   LB_STDCALL getAutoload();
	bool	   LB_STDCALL getAutoselect();

	lb_I_EventManager * getEVManager( void );

	void LB_STDCALL getBasicApplicationInfo(lb_I_Unknown** info);
	

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	
	
	lbErrCodes LB_STDCALL loadSubModules();
	
	/**
	 * Load the real application.
	 */
	lbErrCodes LB_STDCALL loadApplication(char* user, char* app);

	lbErrCodes LB_STDCALL enterDebugger(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL getLoginData(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbEvHandler1(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbEvHandler2(lb_I_Unknown* uk);

/*...sWrapper for some usual GUI functions:8:*/

	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	lbErrCodes LB_STDCALL addMenuBar(char* name, char* after = NULL);

	/**
	 * Add a menu behind the last.
	 */
	lbErrCodes LB_STDCALL addMenu(char* name);
	
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
	lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL);
	lbErrCodes LB_STDCALL addMenuEntryCheckable(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL);
	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h);
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h);
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h);
	
	lbErrCodes LB_STDCALL enableEvent(char* name);
	lbErrCodes LB_STDCALL disableEvent(char* name);
	lbErrCodes LB_STDCALL toggleEvent(char* name);
	
	lb_I_InputStream* LB_STDCALL askOpenFileReadStream(char* extentions);
	bool			  LB_STDCALL askYesNo(char* msg);
	
	/** \brief Let the GUI show the given parameters in a property panel.
	 *
	 */
	lbErrCodes LB_STDCALL showPropertyPanel(lb_I_Parameter* params);
	
/*...e*/

	lbErrCodes LB_STDCALL lbButtonTestHandler(lb_I_Unknown* uk);	

	lbErrCodes LB_STDCALL registerPropertyChangeEventGroup(char* name, lb_I_Parameter* params, lb_I_EventHandler* target, lbEvHandler handler);

	lb_I_Parameter* LB_STDCALL getParameter();

	/// \brief My handler for changed properties.
	lbErrCodes LB_STDCALL propertyChanged(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL doAutoload(lb_I_Unknown* uk);
protected:
	lb_I_GUI* gui;
	
	char* moduleName;
	
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Application, app)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
	
	UAP(lb_I_Parameter, myProperties)

	bool _autoload;
	bool _autoselect;
	
	char gwedgd[100];
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
	virtual lbErrCodes LB_STDCALL delEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName);
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr);
	
	/**
	 * ID variant
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	/**
	 * Name variant
	 *
	 * This variant let's the programmer issue any events from his or her module.
	 * As a sample, it must be possible to query from an event name an id.
	 * Also it must be possible to call this function to announce a handler.
	 * 
	 * This may be solved this way:
	 * EvName = "AnnounceHandler"
	 * EvData = lb_I_HandlerAddress
	 */
	virtual lbErrCodes LB_STDCALL dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult);
	
	virtual lb_I_DispatchResponse* LB_STDCALL dispatch(lb_I_DispatchRequest* req);
	
	UAP(lb_I_Container, dispatcher)
	UAP(lb_I_EventManager, evManager)
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
	virtual char* LB_STDCALL reverseEvent(int evNr);

protected:


	friend class lb_I_Dispatcher;

	// Maps id to event name	
	UAP(lb_I_Container, events)
	
	// Holds free id
	UAP(lb_I_Container, freeIds)
	
	// Reverse mapping name -> id
	UAP(lb_I_Container, reverse_events)
	
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

DECLARE_FUNCTOR(instanceOfEventMapper)
DECLARE_FUNCTOR(instanceOfEvHandler)

DECLARE_SINGLETON_FUNCTOR(instanceOfDispatcher)
DECLARE_SINGLETON_FUNCTOR(instanceOfEventManager)
DECLARE_SINGLETON_FUNCTOR(instanceOfMetaApplication)

/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#endif //LB_OBJECT

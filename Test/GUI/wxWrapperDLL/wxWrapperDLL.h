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

#ifndef __LB_LoginWizard__
#define __LB_LoginWizard__
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: wxWrapperDLL.h,v 1.2 2005/08/28 11:05:05 lollisoft Exp $
 *
 * $Log: wxWrapperDLL.h,v $
 * Revision 1.2  2005/08/28 11:05:05  lollisoft
 * Registering database forms, that are not created by lb_I_GUI implementation
 * is intented. A centralized registry of forms would be a goal.
 *
 * Revision 1.1  2005/08/21 23:24:59  lollisoft
 * Moving code to wxWrapper DLL/so module.
 *
 * Revision 1.3  2005/05/10 21:05:42  lollisoft
 * Including made more actually language conform
 *
 * Revision 1.2  2005/03/31 09:21:02  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.1  2005/03/05 23:25:30  lollisoft
 * Initial wx plugin attempt
 *
 * Revision 1.2  2004/06/16 22:17:27  lollisoft
 * First plugin beginnings
 *
 * Revision 1.1  2004/06/07 20:04:45  lollisoft
 * Initial
 *
 * Revision 1.1  2004/06/06 12:31:21  lollisoft
 * Initial
 *
 **************************************************************/

/*...e*/

#include <iostream>

// ID for the menu commands
#define DYNAMIC_QUIT            1000
#define DYNAMIC_TEXT            1001
#define DYNAMIC_ABOUT           1002
#define DYNAMIC_BUILDMENU       1003
#define DYNAMIC_TEST1           1004
#define DYNAMIC_TEST2           1005
#define DYNAMIC_VERBOSE         1006
#define DYNAMIC_PLUGINTEST	1007

class lb_wxGUI;

/*...sclass lb_wxFrame:0:*/
/**
 * \brief This is the main frame implementation.
 *
 * It implements the main event handling interface via OnDispatch.
 */
class DLLEXPORT lb_wxFrame : 
		public wxFrame,
                public lb_I_wxFrame
{ 
public:
/*...sctors\47\dtors:8:*/
	/**
	 * Initialize a default application layout.
	 */
        lb_wxFrame():
        	wxFrame(NULL, -1, _trans("Dynamic sample"), wxPoint(50, 50), wxSize(450, 340))
        {
        	menu_bar = NULL; 
        	gui = NULL;
        	guiCleanedUp = 0;
        }
        
        virtual ~lb_wxFrame();
/*...e*/
public:
        lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h);

        DECLARE_LB_UNKNOWN()

	/**
	 * Set the GUI wrapper instance.
	 */
	void setGUI(lb_wxGUI* _gui) { gui = _gui; }

	/**
	 * Intented to typecast to derived class. Not sure, if this is really stupid.
	 * Where is it used ?
	 */
        virtual lb_wxFrame* getPeer() { return this; } 

public:
        void OnQuit(wxCommandEvent& event);
        void OnVerbose(wxCommandEvent& event);
        void OnPluginTest(wxCommandEvent& event );
        
        /**
         * Displays the about form of the application.
         */
        void OnAbout(wxCommandEvent& event);

	/**
	 * Displays the logon wizard dialog.
	 */
	void OnRunLogonWizard(wxCommandEvent& WXUNUSED(event));


        /**
         * This dispatcher converts all events to lb_I_Dispatcher events
         * and forwards them to such a dispatcher.
         * 
         * wx Handlers are forwarded directly.
         */
        void OnDispatch(wxCommandEvent& event);

	/**
	 * Build the minimal standard menu of the application.
	 */
	void OnBuildMenu(wxCommandEvent& event);
	
	/**
	 * \deprecated This was only a menu instance pointer check - debug.
	 */
	void OnCheck(wxCommandEvent& event);

	/**
	 * Return the frames menubar. Internal use only.
	 */
	wxMenuBar* LB_STDCALL getMenuBar() {
		return menu_bar;
	}


    
public:
        /**
         * Mixin the interface code, so the base of wxFrame can be used.
         * Simple a dummy code yet.
         */
        virtual lb_I_EventCallback LB_STDCALL getEventFunction(char* name) { return NULL; }
        virtual lbErrCodes LB_STDCALL Connect(char* evName, lb_I_EventCallback evFn) { return ERR_NONE; }
        virtual lbErrCodes LB_STDCALL getSinkEventList(lb_I_Container* c) { return ERR_NONE; }

        virtual lbErrCodes LB_STDCALL registerEvents(lb_I_EventConnector* object);
        
        virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object);
        virtual lb_I_Unknown* LB_STDCALL getEventsource(lb_I_EventConnector* object) { return NULL; }
        
        wxMenuBar* menu_bar;
        
        lb_wxGUI* gui;
        int guiCleanedUp;
        
        UAP(lb_I_EventManager, eman, __FILE__, __LINE__)
        UAP(lb_I_Dispatcher, dispatcher, __FILE__, __LINE__)
};
/*...e*/

/*...sclass lb_wxGUI:0:*/
class DLLEXPORT lb_wxGUI
: public lb_I_wxGUI,
  public lb_I_EventHandler

{
public:
/*...sctor\47\dtor:8:*/
        lb_wxGUI() {
		#ifdef VERBOSE        	
                _LOG << "lb_I_wxGUI object will be created and initialized" LOG_
		#endif                
                
                eventCount = 0;
                sampleQuery = NULL;
                handlersInitialized = FALSE;
                frame = NULL;
		dialog = NULL;
        }

	virtual ~lb_wxGUI() { 
		#ifdef VERBOSE
	        _LOG << "lb_wxGUI::~lb_wxGUI() called.\n" LOG_
	        #endif
	}
/*...e*/

        DECLARE_LB_UNKNOWN()

/*...sGUI element creation functions:8:*/
        virtual lb_I_Unknown* LB_STDCALL createFrame();
        virtual lb_I_Unknown* LB_STDCALL createMenu();
        virtual lb_I_Unknown* LB_STDCALL createMenuBar();
        virtual lb_I_Unknown* LB_STDCALL createMenuEntry();

	virtual lb_I_DatabaseForm* LB_STDCALL createDBForm(char* formName, char* queryString, char* DBName, char* DBUser, char* DBPass);

	virtual lb_I_Form* LB_STDCALL createLoginForm();
/*...e*/

/*...sGUI element getter functions:8:*/
        virtual lb_I_Unknown* LB_STDCALL getFrame();
/*...e*/
        
/*...sEvent related stuff:8:*/
        /**
         * Event related code.
         *
         * Register an event handler by the event registry.
         * This is from interface lb_I_EventManager
         */
        virtual lbErrCodes LB_STDCALL registerEvent(char* EvName, int & EvNr);
        
        /**
         * This is from lb_I_EventHandler. A event handler must provide
         * this function, to be able to call it from the dispatcher.
         */
        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
        
        /**
         * To be able to recieve any events, it is neccesary to provide the dispatcher.
         * An other way may be registrering a direct callback, without dispatching it.
         */
        virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp);
        virtual lbErrCodes LB_STDCALL dispatchEvent(int EvNr, lb_I_Unknown* EvData);

        lbErrCodes LB_STDCALL setDiapatcher(lb_I_Dispatcher* disp);
        lb_I_Dispatcher* LB_STDCALL getDispatcher();

        /**
         * Provide a function to interact with event names instead if their ID's.
         * If the event is not known, it returns ERR_EVENT_UNKNOWN and leaves
         * the provided EvData untouched.
         *
         * As a sample, you may create a new menu in the GUI. This menu is the
         * new help menu, for that you want provide a basic application about
         * dialog.
         *
         * To be able, creating a simple about dialog, it is neccesary to have
         * a pointer to the frame, in with the dialog should be displayed.
         * So first you must query for a frame reference.
         */

        virtual lbErrCodes LB_STDCALL queryEvent(char* EvName, lb_I_Unknown* EvData);
/*...e*/
        
/*...sMenu related manipulation and navigation:8:*/
        /**
         * Menu manipulation based on current position. The members
         * deleates this calls to the lb_I_GUI instance.
         */
         
        virtual lbErrCodes LB_STDCALL deactivateMenuEntry();
        virtual lbErrCodes LB_STDCALL activateMenuEntry();
        
        virtual lbErrCodes LB_STDCALL gotoMenuRoot();
        virtual lbErrCodes LB_STDCALL gotoMenuEntry(char* entry);
        
        virtual lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* entry);
        virtual lbErrCodes LB_STDCALL insertMenuEntry(lb_I_Unknown* entry);

/*...e*/
        
        virtual lbErrCodes LB_STDCALL msgBox(char* windowTitle, char* msg);
        
        virtual lbErrCodes LB_STDCALL setDispatcher(lb_I_Dispatcher* disp);

/*...sTypical GUI handler\44\ that do not need to be dispatched:8:*/
	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	virtual lbErrCodes LB_STDCALL addMenuBar(char* name) { return ERR_NONE; };

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(char* name) { return ERR_NONE; };
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered prior.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) { return ERR_NONE; };

	/**
	 * Add a button at a given position.
	 *
	 * Input:
	 *	char* buttonText	The text for that button
	 *	char* evHandler		The name of a registered event handler, that handle this
	 *	int x 			X coordinade
	 *	int y			Y coordinade
	 *	int w			W coordinade
	 *	int h			H coordinade
	 */
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };


	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };


	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };
/*...e*/
        
	void LB_STDCALL registerDBForm(char* formName, lb_I_DatabaseForm* form);

	lb_I_DatabaseForm* LB_STDCALL findDBForm(char* name);

	/*
	 * Cleanup. This will destroy all possible (hidden) dialogs.
	 * These dialogs are like the database form sample dialog, wich woild
	 * be created only once and then reused by ShowModal().
	 */

	lbErrCodes LB_STDCALL cleanup();



        int eventCount;
        
        lb_I_Unknown* _main_frame;
        lb_I_Dispatcher* myDispatcher;
        
        lb_I_Query* sampleQuery;
        
        bool handlersInitialized;
        
        lb_I_DatabaseForm* dialog;

        // The frame has the main dispatcher and is a wxEventHandler subclass
        lb_wxFrame* frame;
	
	UAP(lb_I_Container, forms, __FILE__, __LINE__)
	char buffer[100];
};
/*...e*/

/*...s\35\ifdef __cplusplus \123\:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

//DECLARE_FUNCTOR(instanceOfPluginModule)

/*...s\35\ifdef __cplusplus \125\:0:*/
#ifdef __cplusplus
}
#endif

/*...e*/

#endif // __LB_LoginWizard__

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
 * $Revision: 1.21 $
 * $Name:  $
 * $Id: wxWrapperDLL.h,v 1.21 2007/02/03 11:04:36 lollisoft Exp $
 *
 * $Log: wxWrapperDLL.h,v $
 * Revision 1.21  2007/02/03 11:04:36  lollisoft
 * Implemented directory location property handler. This is used in lbMetaApplication.
 *
 * Revision 1.20  2007/01/30 20:43:37  lollisoft
 * Probably fixed the bug in status bar handling.
 *
 * Revision 1.19  2007/01/29 20:12:59  lollisoft
 * Checkin for Linux.
 *
 * Revision 1.18  2007/01/14 15:03:45  lollisoft
 * Added a new handler to show a simple message box.
 *
 * Revision 1.17  2006/03/24 17:15:40  lollisoft
 * Added GUI state for maximized or not.
 * Size events didn't work ??
 *
 * Revision 1.16  2006/02/21 19:35:51  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.15  2006/02/19 18:42:24  lollisoft
 * Feedback of properties works good. I am use the
 * dispatcher mechanism to forward the change events
 * on per lb_I_Parameter instance and the category name
 * to a registered handler.
 *
 * So one handler must be capable to recieve values for all
 * elements of one lb_I_Parameter instance.
 *
 * Revision 1.14  2006/02/19 12:03:29  lollisoft
 * Populating properties works. Currently it is not possible to
 * add sub properties, but handling categories.
 *
 * Note: Each property name must be unique.
 *
 * Revision 1.13  2006/02/17 23:57:17  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.12  2006/02/16 10:09:36  lollisoft
 * I have it now.
 *
 * Revision 1.11  2006/02/15 12:44:44  lollisoft
 * Acceptable layout capabilities with wxAUI, but still no  visible properties.
 *
 * Revision 1.10  2006/02/06 14:49:41  lollisoft
 * Try to implement left panel using wxPropertyGrid
 *
 * Revision 1.9  2006/02/04 11:16:32  lollisoft
 * Changed wxFrame class structure and added support for splitter windows.
 *
 * Revision 1.8  2006/01/30 15:54:15  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.7  2006/01/30 06:23:48  lollisoft
 * Removed OnPluginTest and added preparation for splitter windows.
 *
 * Revision 1.6  2005/12/02 00:28:43  lollisoft
 * Deleting a row works for some tests. Deleting data in join queries is not tested
 * and would propably not work. This is at least due to lack of creating a delete
 * statement per related table.
 *
 * Now this deleting also includes the ability to reopen the query as needed.
 * Form code is adopted to the case if there are no peek aheads are done
 * while fetching new data.
 *
 * Code cleanup would be done later.
 *
 * Revision 1.5  2005/11/16 20:51:44  lollisoft
 * Moved code, removed memory leaks and trmem counted breakpoint support added.
 *
 * Revision 1.4  2005/10/02 16:51:48  lollisoft
 * New wxNotebook layout completed. Not yet changeable at runtime, but it works.
 *
 * Revision 1.3  2005/10/01 21:50:49  lollisoft
 * Begin using panel based dialogs. Fails creating under Windows.
 * (wxWindowBase::SetName routed to wrong function ??)
 *
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

#define PGID					1007

class lb_wxGUI;

/*...sclass lb_wxFrame:0:*/
/**
 * \brief This is the main frame implementation.
 *
 * It implements the main event handling interface via OnDispatch.
 */
class DLLEXPORT lb_wxFrame : 
public wxFrame,
public lb_I_Frame,
public lb_I_EventHandler
{ 
public:
	/*...sctors\47\dtors:8:*/
	/**
	* Initialize a default application layout.
	 */
	lb_wxFrame(); 
	virtual ~lb_wxFrame();
	/*...e*/
public:
        lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h);
	
		DECLARE_LB_UNKNOWN()
		
		/**
		* Set the GUI wrapper instance.
		 */
		void setGUI(lb_wxGUI* _gui) { gui = _gui; }
	
public:
	void OnQuit(wxCommandEvent& event);
	void OnVerbose(wxCommandEvent& event);
	
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
	
#ifdef USE_WXAUI	
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
#endif

	void OnPropertyGridChange (wxPropertyGridEvent& event);

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
		
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	
	/// Show or hide left panel.
	void LB_STDCALL showLeftPanel(bool show);
	
	/// Is left panel visible ?
	bool LB_STDCALL isSplitted() { return _isSplitted; }
	
	bool LB_STDCALL isPanelUsage() { return panelUsage; }
	
#ifdef USE_WXAUI
	wxFrameManager& getAUIManager() { return m_mgr; }
#endif		


	void populateProperties(wxPropertyGrid* pg, lb_I_Container* properties, char* category = NULL);
	void populateInteger(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category = NULL);
	void populateString(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category = NULL);
	void populateFileLocation(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category = NULL);
	void populateDirLocation(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category = NULL);
	void populateBoolean(wxPropertyGrid* pg, lb_I_Unknown* uk, lb_I_KeyBase* name, char* category = NULL);

	wxPropertyGrid* CreatePropertyGrid(wxWindow* parent);
	wxTreeCtrl* CreateTreeCtrl(wxWindow* parent);
	wxPoint GetStartPosition();

	
	
	// Event handlers        
	
	lbErrCodes LB_STDCALL showLeftPropertyBar(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL switchPanelUse(lb_I_Unknown* uk);
	
	lbErrCodes LB_STDCALL setPreferredPropertyPanelByNamespace(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL showMsgBox(lb_I_Unknown* uk);
	
	// Statusbar handlers
	
	/// \brief Add a status bar to the frame. 
	lbErrCodes LB_STDCALL addStatusBar(lb_I_Unknown* uk);
	
	/// \brief Add a information text area to the statusbar.
	lbErrCodes LB_STDCALL addStatusBarTextArea(lb_I_Unknown* uk);
	
	/// \brief Remove a information text area to the statusbar.
	lbErrCodes LB_STDCALL removeStatusBarTextArea(lb_I_Unknown* uk);
	
	/// \brief Set text in a given text status bar area.
	lbErrCodes LB_STDCALL setText_To_StatusBarTextArea(lb_I_Unknown* uk);
	
	wxMenuBar* menu_bar;
	int *stb_withs;
	long stb_areas;
	UAP(lb_I_Container, statusbar_name_mappings)
	
	
	// Splitter window handling
	wxScrolledWindow *m_left, *m_right;
	wxSplitterWindow* m_splitter;
	wxWindow *m_replacewindow;
	
	bool _isSplitted;            
	bool panelUsage;
	
	lb_wxGUI* gui;
	int guiCleanedUp;
	
	// Registered event handler IS's
	int on_panel_usage;
	int _showLeftPropertyBar;
	
#ifdef USE_WXAUI
private:
	wxFrameManager m_mgr;
	DECLARE_EVENT_TABLE()
#endif		

	
	UAP(lb_I_String, PanelNamespace)
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Parameter, currentProperties)
};
/*...e*/

/*...sclass lb_wxGUI:0:*/
class DLLEXPORT lb_wxGUI
: public lb_I_wxGUI,
  public lb_I_EventHandler

{
public:

	lb_wxGUI() {
		#ifdef VERBOSE        	
	        _LOG << "lb_I_wxGUI object will be created and initialized" LOG_
		#endif                
                
	        eventCount = 0;
	        sampleQuery = NULL;
	        handlersInitialized = FALSE;
	        frame = NULL;
	        notebook = NULL;
		dialog = NULL;
		sizerMain = NULL;
		
	}

	virtual ~lb_wxGUI() { 
		#ifdef VERBOSE
	        _LOG << "lb_wxGUI::~lb_wxGUI() called.\n" LOG_
	        #endif
	}

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

	void LB_STDCALL showForm(char* name);

	void LB_STDCALL setIcon(char* name);

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
        wxNotebook* notebook;
	wxBoxSizer* sizerMain;

        // The frame has the main dispatcher and is a wxEventHandler subclass
        lb_wxFrame* frame;
	
	UAP(lb_I_Container, forms)
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

/*...sCopyright notice:0:*/
// Orginal version:
/////////////////////////////////////////////////////////////////////////////
// Name:        dynamic.cpp
// Purpose:     Dynamic events wxWindows sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: dynamic.cpp,v 1.13 2004/04/11 07:50:38 lollisoft Exp $
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

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
            
            40235 DÅsseldorf (germany)
*/
/*...e*/
/*...e*/

/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef LB_I_EXTENTIONS
#include <lbInterfaces.h>
#include <lbConfigHook.h>
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
#include "mondrian.xpm"
#endif
/*...e*/
/*...e*/

// ID for the menu commands
#define DYNAMIC_QUIT		1000
#define DYNAMIC_TEXT		1001
#define DYNAMIC_ABOUT		1002
#define DYNAMIC_BUILDMENU	1003
#define DYNAMIC_TEST1		1004
#define DYNAMIC_TEST2           1005

#ifdef LB_I_EXTENTIONS
/*...sclass lb_wxFrame:0:*/
class lb_wxFrame : 
                public lb_I_wxFrame,
		public wxFrame
{ 
public:
        lb_wxFrame():
        wxFrame(NULL, -1, "Dynamic sample", wxPoint(50, 50), wxSize(450, 340)) { menu_bar = NULL; }
        virtual ~lb_wxFrame() {
        	_LOG << "Closing GUI frame" LOG_
        }
public:
        lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h);

        DECLARE_LB_UNKNOWN()

        virtual lb_wxFrame* getPeer() { return this; } 

public:
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);


        /**
         * This dispatcher converts all events to lb_I_Dispatcher events
         * and forwards them to such a dispatcher.
         * 
         * wx Handlers are forwarded directly.
         */
        void OnDispatch(wxCommandEvent& event);

	void OnBuildMenu(wxCommandEvent& event);
	void OnCheck(wxCommandEvent& event);

	wxMenuBar* LB_STDCALL getMenuBar() {
		char ptr[200] = "";
		sprintf(ptr, "%p for instance %p", menu_bar, this);
		_LOG << "Return a menu pointer: " << ptr LOG_
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
        UAP(lb_I_EventManager, eman, __FILE__, __LINE__)
        UAP(lb_I_Dispatcher, dispatcher, __FILE__, __LINE__)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxFrame)
//        ADD_INTERFACE(lb_I_EventSink)
        ADD_INTERFACE(lb_I_wxFrame)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes lb_wxFrame\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxFrame::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\registerEvents\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::registerEvents(lb_I_EventConnector* object) {
       _LOG << "lb_wxFrame::registerEvents(...)" LOG_
        lb_wxFrame* peer = getPeer();

        
        ((wxFrame*) peer)->Connect( DYNAMIC_QUIT,  -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

        ((wxFrame*) peer)->Connect( DYNAMIC_ABOUT, -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

	((wxFrame*) peer)->Connect( DYNAMIC_BUILDMENU, -1, wxEVT_COMMAND_MENU_SELECTED,
	          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnDispatch );

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\createEventsource\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::createEventsource(lb_I_EventConnector* object) {
       _LOG << "lb_wxFrame::createEventsource(...)" LOG_
/*...screate a menu:0:*/
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  
  _LOG << "Create Build menu" LOG_
  file_menu->Append(DYNAMIC_BUILDMENU, "&Build menu");  
  _LOG << "Create About menu" LOG_
  file_menu->Append(DYNAMIC_ABOUT, "&About");
  _LOG << "Create Exit menu" LOG_
  file_menu->Append(DYNAMIC_QUIT, "E&xit");

//  file_menu->Append(GUI->useEvent("DYNAMIC_ABOUT"), "&About");
//  file_menu->Append(GUI->useEvent("DYNAMIC_QUIT"), "E&xit");

  _LOG << "Create MenuBar" LOG_
  menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
  
  
  char ptr[20] = "";
  sprintf(ptr, "%p", menu_bar);
  _LOG << "Return a menu pointer: " << ptr LOG_
  
  _LOG << "Appended File menu" LOG_
/*...e*/

/*...sset the created menubar:0:*/
  _LOG << "Set the menubar" LOG_
  SetMenuBar(menu_bar);
  _LOG << "Set up menubar" LOG_
/*...e*/
        return ERR_NONE;
}
/*...e*/
/*...e*/
#endif

/*...sclass lb_wxGUI:0:*/
#ifdef LB_I_EXTENTIONS

/*...sclass lb_wxGUI:0:*/
class lb_wxGUI
: public lb_I_wxGUI,
  public lb_I_EventHandler

{
public:
/*...sctor\47\dtor:8:*/
        lb_wxGUI() {
                _LOG << "lb_I_wxGUI object will be created and initialized" LOG_;
                eventCount = 0;
        }

	virtual ~lb_wxGUI() { }
/*...e*/

        DECLARE_LB_UNKNOWN()

/*...sGUI element creation functions:8:*/
        virtual lb_I_Unknown* LB_STDCALL createFrame();
        virtual lb_I_Unknown* LB_STDCALL createMenu();
        virtual lb_I_Unknown* LB_STDCALL createMenuBar();
        virtual lb_I_Unknown* LB_STDCALL createMenuEntry();
/*...e*/

/*...sGUI element getter functions:8:*/
        virtual lb_I_Frame* LB_STDCALL getFrame();
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
	 * if provided. The handler must be registered.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) { return ERR_NONE; };
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };
/*...e*/
        
        int eventCount;
        
        lb_I_Unknown* _main_frame;
        lb_I_Dispatcher* myDispatcher;
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxGUI)
        ADD_INTERFACE(lb_I_wxGUI)
END_IMPLEMENT_LB_UNKNOWN()

/**
 * As this is the GUI server, it is also the place to manage the
 * events.
 */

/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\setDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "lb_wxGUI::setDispatcher() not implemented yet" LOG_
        
        return ERR_NONE;
}
/*...e*/


/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEventHandler(lb_I_Dispatcher* disp) {
       _LOG << "Register event handler" LOG_;
        
        /**
         * Need a event name map to event id
         */
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEvent(char* EvName, int & EvNr) {
       _LOG << "Registering an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "Add a sub dispatcher" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\dispatchEvent\40\int EvNr\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::dispatchEvent(int EvNr, lb_I_Unknown* EvData) {
       _LOG << "Dispatch an event" LOG_;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\queryEvent\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::queryEvent(char* EvName, lb_I_Unknown* EvData) {
       _LOG << "Query an event" LOG_;
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes lb_wxGUI\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setData(lb_I_Unknown* uk) {
        _LOG << "lb_wxGUI::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createFrame() {
        lb_wxFrame* frame = new lb_wxFrame();
        
        frame->setModuleManager(getModuleManager(), __FILE__, __LINE__);
        frame->queryInterface("lb_I_Unknown", (void**) &_main_frame, __FILE__, __LINE__);

	char ptr[20] = "";
	sprintf(ptr, "%p", frame);
	
	_LOG << "Created a lb_wxFrame object at " << ptr LOG_
        
        return frame;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenu\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenu() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuBar\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuBar() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createMenuEntry\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return NULL;
}
/*...e*/

/*...slb_I_Frame\42\ LB_STDCALL lb_wxGUI\58\\58\getFrame\40\\41\:0:*/
lb_I_Frame* LB_STDCALL lb_wxGUI::getFrame() {
        lb_I_Frame* f = NULL;
        
        _main_frame->queryInterface("lb_I_Frame", (void**) &f, __FILE__, __LINE__);
        
        return f;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\deactivateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::deactivateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\activateMenuEntry\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::activateMenuEntry() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuRoot\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuRoot() {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\gotoMenuEntry\40\char\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::gotoMenuEntry(char* entry) {
        lbErrCodes err = ERR_NONE;
        UAP(lb_I_Frame, frame, __FILE__, __LINE__)
        
        QI(_main_frame, lb_I_Frame, frame, __FILE__, __LINE__)


        /**
         * Create the dispatch request
         */


        UAP_REQUEST(manager.getPtr(), lb_I_DispatchRequest, d_req)
        
        /**
         * We get a dispatch responce
         */
         
        UAP(lb_I_DispatchResponce, d_res, __FILE__, __LINE__)

        if (d_req.getPtr()) {
                // d_req must resolve the symbolic request name to its Id.
                // So it must have an instance from lb_I_EventManager
                d_req->setRequestName("hasMenuEntry");

                d_res = myDispatcher->dispatch(*&d_req);

                if ((d_res.getPtr()) && (d_res->isOk())) {
                } else {
                }
        } 

/*        id (frame->hasMenuEntry(entry)) {
                if (currentMenuEntry) free(currentMenuEntry);
                currentMenuEntry = strdup(entry);
        }
*/
        return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\addMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::addMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\insertMenuEntry\40\lb_I_Unknown\42\ entry\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::insertMenuEntry(lb_I_Unknown* entry) {
       _LOG << "Error: Function has not been implemented!" LOG_
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\msgBox\40\char\42\ windowTitle\44\ char\42\ msg\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::msgBox(char* windowTitle, char* msg) {
        wxMessageDialog dialog(NULL, msg, windowTitle, wxYES_NO|wxCANCEL);

        dialog.ShowModal();

        return ERR_NONE;
}
/*...e*/
#endif
/*...e*/
#ifndef LB_I_EXTENTIONS
class MyFrame;
#endif
/*...sclass MyApp:0:*/
// Define a new application type
class MyApp: public wxApp
#ifdef LB_I_EXTENTIONS
, public lb_I_Unknown
, public lb_I_EventConnector
, public lb_I_EventHandler
#endif
{ public:
	MyApp() {
#ifdef LB_I_EXTENTIONS	
	  wxGUI = NULL;
	  metaApp = NULL;
#endif
	 panel = NULL;
	}

	virtual ~MyApp() { 
/*
 * It seems, that frame was deleted prior !!
 */
//		_CL_LOG << "frame has " << frame->getRefCount() LOG_
	}

    bool OnInit(void);

#ifdef LB_I_EXTENTIONS
/*...ssome docs:0:*/
    /**
     * This instance knows of some events, have to be interconnected.
     * The source are menus and the target is the frame, that handles
     * it.
     * As in general, the application must define the events it needs
     * for the proper work. We see, that the OnInit method defines some
     * events, here exit and about. The application needs to be able for
     * exiting and may provide an about dialog. As an interpreter here, the
     * application will be in a module later and the interpreter loads the app.
     *
     * The application in the module is the real application. This object simply
     * delegates the functionality to it.
     */
/*...e*/
        virtual lbErrCodes LB_STDCALL getConnectorEventList(lb_I_Container* c) { return ERR_NONE; }
        virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object) { return ERR_NONE; }


        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);

	// I provide some eventhandlers

	lbErrCodes LB_STDCALL lbEvHandler1(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbEvHandler2(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL lbEvHandler3(lb_I_Unknown* uk);	
	lbErrCodes LB_STDCALL addButton(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL addLabel(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL addTextField(lb_I_Unknown* uk);

        lbErrCodes LB_STDCALL HandleGetFrame(lb_I_Unknown* uk); // Thread parameter as output
        lbErrCodes LB_STDCALL HandleAddMenu(lb_I_Unknown* uk);  // Thread parameter as input
    
        DECLARE_LB_UNKNOWN()
    
protected:
/*...ssome docs:0:*/
        /**
         * This instance will be known in the meta application. So all events from the
         * application logic will be forwarded to this instance.
         *
         * Every event from the meta app or any registered components would be mapped to
         * wxWindows events, so that the wxWindows objects could be manipulated.
         */
/*...e*/
        lb_wxGUI* wxGUI;
        lb_wxFrame* frame_peer;
        
        int AddMenu;
        int AddMenuBar;
        int AddMenuEntry;
        int AddLabel;
        int AddTextField;
        
        
/*...sevent manager:8:*/
        /**
         * I need an instance of the event manager. The event manager is used to give me id's for my
         * symbolic event names. First I do not handle a scope.
         */
        
        DEBUG_UAP(lb_I_EventManager, ev_manager, __FILE__, __LINE__)
/*...e*/
/*...smeta application:8:*/
        /**
         * I also need an instance of the meta application, that is loaded as the application wrapper.
         */
         
        DEBUG_UAP(lb_I_MetaApplication, metaApp, __FILE__, __LINE__) 
/*...e*/
/*...sframe:8:*/
//        DEBUG_UAP(lb_I_wxFrame, frame, __FILE__, __LINE__)
	lb_I_wxFrame *frame;
/*...e*/

	char buffer[100];
#endif

        #ifndef LB_I_EXTENTIONS
        MyFrame *frame;
        #endif
        wxPanel *panel;
};
/*...e*/

#ifndef LB_I_EXTENTIONS
/*...sclass MyFrame:0:*/
// Define a new frame type
class MyFrame: public wxFrame
{ public:
    MyFrame(wxFrame *frame, char *title, int x, int y, int w, int h);

 public:
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
/*...e*/
#endif



#ifdef LB_I_EXTENTIONS
BEGIN_IMPLEMENT_LB_UNKNOWN(MyApp)
//        ADD_INTERFACE(lb_I_EventConnector)
//        ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()
#endif 


// Create a new application object
IMPLEMENT_APP  (MyApp)

/*...sMyApp\58\\58\OnInit\40\void\41\:0:*/
// `Main program' equivalent, creating windows and returning main app frame
void testthis(void* t) {
#ifdef bla
	char ptr[20] = "";
	sprintf(ptr, "%p", t);
	_LOG << "This is " << ptr LOG_
#endif
}

bool MyApp::OnInit(void)
{
    char b[100] = "";
/*...sCreate the frame:0:*/
#ifndef LB_I_EXTENTIONS
  // Create the main frame window
  frame = new MyFrame(NULL, "Dynamic wxWindows App", 50, 50, 450, 340);
#endif
#ifdef LB_I_EXTENTIONS
    lbErrCodes err = ERR_NONE;
/*...sBasic setup:0:*/

  UAP(lb_I_Module, mm, __FILE__, __LINE__)
  mm = getModuleInstance();
  mm->setModuleManager(mm.getPtr(), __FILE__, __LINE__);
  setModuleManager(mm.getPtr(), __FILE__, __LINE__);
/*...e*/

/*...sget the event manager:0:*/

/*...sbla:0:*/
#ifdef bla
       _LOG << "Get event manager instance" LOG_
        lb_I_Unknown* uk_em;
        if (mm->request("lb_I_EventManager", &uk_em) != ERR_NONE) {
               _LOG << "Error getting the event manager. Can not initialize the application" LOG_
        }
        
        uk_em->setModuleManager(mm, __FILE__, __LINE__);
        
	_LOG << "Query interface of event manager" LOG_        
        QI(uk_em, lb_I_EventManager, ev_manager, __FILE__, __LINE__)
        
        if (ev_manager.getPtr() == NULL) _LOG << "Fatal: Got an instance not providing that interface" LOG_
       _LOG << "Got event manager instance" LOG_
#endif
/*...e*/

	REQUEST(mm.getPtr(), lb_I_EventManager, ev_manager)        
//	ev_manager->setModuleManager(*&mm, __FILE__, __LINE__);
	ev_manager++;
/*...e*/
/*...sget the dispatcher \40\all handlers must be registered there\41\:0:*/
        UAP_REQUEST(mm.getPtr(), lb_I_Dispatcher, disp)
//	disp->setModuleManager(*&mm, __FILE__, __LINE__);
	disp->setEventManager(ev_manager.getPtr());
		
        if (disp == NULL) _LOG << "Fatal: Have not got a dispatcher!" LOG_
/*...e*/

//  UAP_REQUEST(mm, lb_I_Log, logger)

/*...sdid I need wxGUI here \63\ It registers event handlers from the wxGUI:0:*/
  if (wxGUI == NULL) {
        wxGUI = new lb_wxGUI();
        wxGUI->setModuleManager(mm.getPtr(), __FILE__, __LINE__);
        wxGUI->setDispatcher(*&disp);


	// Register Events, that I provide

	ev_manager->registerEvent("AddMenu", AddMenu);
	ev_manager->registerEvent("AddMenuBar", AddMenuBar);
	
	
	
	/*
	 * Registering an AddMenuEntry handler is a more specific handler,
	 * that need special handler data. This means herefore, an information,
	 * who is responsible for that event and what event should be issued to
	 * the targed handler. It might be these parameters:
	 *
	 * target	= target handler for handling id 
	 * event	= event id to be issued
	 */
	
	ev_manager->registerEvent("AddMenuEntry", AddMenuEntry);
	ev_manager->registerEvent("AddLabel", AddLabel);
	ev_manager->registerEvent("AddTextField", AddTextField);

        /**
         * Register any event handler from this instance by the wxGUI wrapper.
         */
        registerEventHandler(*&disp);
  }
/*...e*/

/*...sload the frame \40\peer is the frame \63\\63\\41\:0:*/

  lb_I_Unknown *uk = wxGUI->createFrame();
  char ptr[20] = "";
  sprintf(ptr, "%p", uk);
  
  _LOG << "Have got a frame: " << ptr LOG_
  
  /**
   * A Peer interface to get the derived class
   */

//  QI(uk_em, lb_I_EventManager, ev_manager, __FILE__, __LINE__)
//  QI(uk, lb_I_wxFrame, frame, __FILE__, __LINE__)
	uk->queryInterface("lb_I_wxFrame", (void**) &frame, __FILE__, __LINE__);
  frame_peer = frame->getPeer();
  
  sprintf(ptr, "%p", frame_peer);
  
/*...e*/
  
#endif
/*...e*/


#ifdef LB_I_EXTENTIONS
#endif
/*...sInitializiation of the hardcoded part \40\regardless of delegation or not\41\:0:*/
/*...sHardcoded event registration\9\\40\we do it here\41\:0:*/
#ifndef LB_I_EXTENTIONS
  frame->Connect( DYNAMIC_QUIT,  -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &MyFrame::OnQuit );
  frame->Connect( DYNAMIC_ABOUT, -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &MyFrame::OnAbout );
#endif
/*...e*/
/*...sDelegated event registration\9\\40\peer does this for us\41\:0:*/
#ifdef LB_I_EXTENTIONS
  /**
   * Lets the frame search for events, that can handled by this instance.
   * For that, the class MyApp must be derived from lb_I_EventHandler.
   * registerEvents is self calls that->getHandlerHavetoConnected() to get a
   * list of events have to be connected for that object.
   * In this case, a quit and an about event.
   */
  frame_peer->registerEvents(this);
/*...sregisterEvents\40\\41\ sample:0:*/
/*
  MyFrane::registerEvents(lb_I_EventConnector* object) {
      // Register my own event handler, but the info about what events
      // comes from an extern event connector.
      list = object->getHandlerHavetoConnected();

      for (int i = 0; i < list->getCount(); i++) {
        char* eventName = list->getAt(i);
        Connect(eventName, getEventFunction(eventName));
      }
  }
*/
/*...e*/
#endif
/*...e*/

/*...sset an icon:0:*/
#ifndef LB_I_EXTENTIONS
/*...san icon:0:*/
  // Give it an icon
#ifdef __WXMSW__
  frame->SetIcon(wxIcon("mondrian"));
#else
  frame->SetIcon(wxIcon(mondrian_xpm));
#endif
/*...e*/
#endif
#ifdef LB_I_EXTENTIONS
/*...san icon:0:*/
  // Give it an icon
#ifdef __WXMSW__
  frame_peer->SetIcon(wxIcon("mondrian"));
#else
  frame_peer->SetIcon(wxIcon(mondrian_xpm));
#endif
/*...e*/
#endif
/*...e*/

/*...sHardcoded menu \9\\9\\9\\40\we do it here\41\:0:*/
#ifndef LB_I_EXTENTIONS
/*...screate a menu:0:*/
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  
  file_menu->Append(DYNAMIC_ABOUT, "&About");
  file_menu->Append(DYNAMIC_QUIT, "E&xit");

//  file_menu->Append(GUI->useEvent("DYNAMIC_ABOUT"), "&About");
//  file_menu->Append(GUI->useEvent("DYNAMIC_QUIT"), "E&xit");

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
/*...e*/

/*...sset the created menubar:0:*/
#ifndef LB_I_EXTENTIONS
  frame->SetMenuBar(menu_bar);
#endif
#ifdef LB_I_EXTENTIONS
  frame_peer->SetMenuBar(menu_bar);
#endif
/*...e*/
#endif
/*...e*/
/*...sDelegated menucreation \9\\9\\40\peer does this for us\41\:0:*/
#ifdef LB_I_EXTENTIONS
/*...sDoc \45\ creating the menu:0:*/
  /**
   * Make an event source from the app event list.
   * The application may have more events than the frame.
   * This is nod bad. In this case not all event source objects are
   * created. So the application is not completely implemented, but
   * it can be tested with that functionality.
   * A menu event source may be assigned to the frame. But it may also
   * assigned a toolbar. So the result sould be an unknown reference.
   *
   * It may be decided by the developer of an application.
   */
/*...e*/

  err = frame_peer->createEventsource(this);
  _LOG << "Called frame_peer->createEventsource(this)" LOG_
  if (err != ERR_NONE) _LOG << "Have some problems to set up menu event sources" LOG_
  
/*...sa text edit sample:0:*/
  /**
   * As a sample, the application is a simple texteditor, then a texteditormodule
   * may be used for that functionality.
   
   The module for the text editor will be in another library. While getting this information
   from the module manager, it is simple to implement this (hidden here).

   lb_I_TextEditor* textedit = GUI->createTextEditor();
   
   All the events will be registered.
   
   textedit->registerEvents(this);
   
   The event source may be modified. Possibly with the following additions:
   A menu for open a document,
   close it,
   save it and
   show document property.
   
   textedit->createEventsource(this);
   
   if (textedit->checkEvents() == 0) {
        // Show an error, that some event groups are not completely
        // connected.
   }
   
   */
/*...e*/
  
#endif
/*...e*/

/*...sMake a panel with a message:0:*/
  // Make a panel with a message
#ifdef LB_I_EXTENTIONS
  panel = new wxPanel(frame_peer, -1, wxPoint(0, 0), wxSize(400, 200), wxTAB_TRAVERSAL);
#endif
#ifndef LB_I_EXTENTIONS
  panel = new wxPanel(frame, -1, wxPoint(0, 0), wxSize(400, 200), wxTAB_TRAVERSAL);
#endif
#ifdef LB_I_EXTENTIONS
  (void)new wxStaticText(panel, 311, "Hello!", wxPoint(10, 10), wxSize(-1, -1), 0);
#endif
#ifndef LB_I_EXTENTIONS
  (void)new wxStaticText(panel, 311, "Hello!", wxPoint(10, 10), wxSize(-1, -1), 0);
#endif
/*...e*/
#ifdef LB_I_EXTENTIONS
_LOG << "Made panel" LOG_
#endif
/*...sShow the window:0:*/
#ifdef LB_I_EXTENTIONS
  // Show the frame
  frame_peer->Show(TRUE);

  SetTopWindow(frame_peer);
#endif
#ifndef LB_I_EXTENTIONS
  // Show the frame
  frame->Show(TRUE);

  SetTopWindow(frame);
#endif
/*...e*/
#ifdef LB_I_EXTENTIONS
_LOG << "Showed the window" LOG_
#endif

/*...sInit the meta application:0:*/
#ifdef LB_I_EXTENTIONS
  UAP_REQUEST(mm.getPtr(), lb_I_MetaApplication, metaApp)
  metaApp++;
  if (metaApp != NULL) {
      metaApp->setGUI(wxGUI);

      /**
       * Try to register an event source for a basic information about the
       * application module as a first step.
       */
      metaApp->Initialize();
      _LOG << "Initialized the meta application" LOG_
  } 
#endif
/*...e*/

#ifdef LB_I_EXTENTIONS
_LOG << "Initialized metaapplication" LOG_
#endif

/*...e*/
#ifdef LB_I_EXTENTIONS
  if (metaApp != NULL) metaApp->run();
#endif
  return TRUE;
}
/*...e*/
#ifdef LB_I_EXTENTIONS
/*...sMyApp\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL MyApp::setData(lb_I_Unknown* uk) {
        _LOG << "MyApp::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...e*/

/*...sMyApp\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL MyApp::registerEventHandler(lb_I_Dispatcher* disp) {
       _LOG << "Register event handler" LOG_;
        
        // We provide some menu manipulation
        disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::lbEvHandler1, "AddMenu");
        disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::lbEvHandler2, "AddMenuBar");
        disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::lbEvHandler3, "AddMenuEntry");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addButton, "AddButton");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addLabel, "AddLabel");
	disp->addEventHandlerFn(this, (lbEvHandler) &MyApp::addTextField, "AddTextField");

        return ERR_NONE;
}
/*...e*/
/*...sevent handler:0:*/
/*...slbErrCodes LB_STDCALL MyApp\58\\58\HandleGetFrame\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL MyApp::HandleGetFrame(lb_I_Unknown* uk) {
        if(frame != NULL) {
                lb_I_Unknown* _uk;
                UAP(lb_I_Reference, ref, __FILE__, __LINE__)
                frame->queryInterface("lb_I_Unknown", (void**) &_uk, __FILE__, __LINE__);
                
                uk->queryInterface("lb_I_Reference", (void**) &ref, __FILE__, __LINE__);
                
                ref->set(_uk);
        }
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL MyApp\58\\58\HandleAddMenu\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL MyApp::HandleAddMenu(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_String, string, __FILE__, __LINE__)
	if (uk == NULL) _LOG << "Have got a null pointer" LOG_;
	QI(uk, lb_I_String, string, __FILE__, __LINE__)
	
	wxMenu *menu = new wxMenu;

	menu->Append(DYNAMIC_TEST1, "&About");
	menu->Append(DYNAMIC_TEST2, "E&xit");
	    
	wxMenuBar* mBar = frame_peer->getMenuBar();
	mBar->Append(menu, "&Edit");

#ifdef bla
	wxMenu *menu = new wxMenu;
	
	menu->Append(DYNAMIC_ABOUT, "&About");
	menu->Append(DYNAMIC_QUIT, "E&xit");
	    
	frame_peer->getMenuBar()->Append(menu, "Edit");
#endif

        return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL MyApp::lbEvHandler1(lb_I_Unknown* uk) {
	_LOG << "MyApp::lbEvHandler1 called" LOG_
	return ERR_NONE;
}

/*...sAddMenuBar\9\\9\Handler:0:*/
lbErrCodes LB_STDCALL MyApp::lbEvHandler2(lb_I_Unknown* uk) {

	lbErrCodes err = ERR_NONE;

	UAP(lb_I_String, string, __FILE__, __LINE__)
	if (uk == NULL) _LOG << "Have got a null pointer" LOG_;
	QI(uk, lb_I_String, string, __FILE__, __LINE__)
	
	wxMenu *menu = new wxMenu;

	wxMenuBar* mbar = frame_peer->getMenuBar();
	if (mbar) mbar->Append(menu, string->getData());

	return err;
}
/*...e*/
/*...sAddMenuEntry\9\Handler:0:*/
/**
 * Add a menu entry to a specific menubar.
 *
 * Params:
 *	menubar:	Name of menubar
 *	menuname:	Name of menu entry
 *	handlername:	Name of handler
 */
lbErrCodes LB_STDCALL MyApp::lbEvHandler3(lb_I_Unknown* uk) {
/*...scode:0:*/
	_LOG << "MyApp::lbEvHandler3 called" LOG_
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, menubar)
	UAP_REQUEST(manager.getPtr(), lb_I_String, menuname)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	
	
	UAP(lb_I_Parameter, param, __FILE__, __LINE__)

	QI(uk, lb_I_Parameter, param, __FILE__, __LINE__)


	parameter->setData("menubar");
	param->getUAPString(*&parameter, *&menubar);
	parameter->setData("menuname");
	param->getUAPString(*&parameter, *&menuname);
	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);
	
	
	int EvNr = 0;
	ev_manager->resolveEvent(handlername->getData(), EvNr);

	wxMenuBar* mbar = frame_peer->getMenuBar();
	wxMenu* menu = mbar->GetMenu(mbar->FindMenu(wxString(menubar->getData())));

	menu->Append(EvNr, menuname->getData());


	((wxFrame*) frame_peer)->Connect( EvNr,  -1, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
          &lb_wxFrame::OnDispatch );

	return ERR_NONE;
/*...e*/
}
/*...e*/
/*...sAddButton \9\\9\Handler:0:*/
/**
 * Add a button to the active window.
 *
 * Params:
 *      buttontext:     Text of the button
 *      handlername:    Name of handler
 */
lbErrCodes LB_STDCALL MyApp::addButton(lb_I_Unknown* uk) {
/*...scode:0:*/
	_LOG << "MyApp::lbEvHandler3 called" LOG_
	lbErrCodes err = ERR_NONE;


//addButton("Press me for test", "Button Test pressed", 10, 10, 100, 20);


	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_String, handlername)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	
	UAP(lb_I_Parameter, param, __FILE__, __LINE__)

	QI(uk, lb_I_Parameter, param, __FILE__, __LINE__)


	parameter->setData("buttontext");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("handlername");
	param->getUAPString(*&parameter, *&handlername);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	int EvNr = 0;
	ev_manager->resolveEvent(handlername->getData(), EvNr);



	lb_wxFrame* f = frame_peer->getPeer();
	
	_LOG "Create a button" LOG_
	
//	if (panel == NULL) panel = new wxPanel(f);
	
	wxButton *button = new wxButton(panel, EvNr, buttontext->getData(), 
					wxPoint(x->getData(),y->getData()), 
					wxSize((int) w->getData(),(int) h->getData() ));

	((wxFrame*) frame_peer)->Connect( EvNr,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
	  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
	    &lb_wxFrame::OnDispatch );

/*
	wxMenuBar* mbar = frame_peer->getMenuBar();
	wxMenu* menu = mbar->GetMenu(mbar->FindMenu(wxString(menubar->getData())));

	menu->Append(EvNr, menuname->getData());


	((wxFrame*) frame_peer)->Connect( EvNr,  -1, wxEVT_COMMAND_MENU_SELECTED,
          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
          &lb_wxFrame::OnDispatch );
*/



	return ERR_NONE;
/*...e*/
}
/*...e*/

lbErrCodes LB_STDCALL MyApp::addLabel(lb_I_Unknown* uk) {
	_LOG << "lbErrCodes LB_STDCALL MyApp::addLabel(lb_I_Unknown* uk) called" LOG_
/*...scode:0:*/
	_LOG << "MyApp::addLabel called" LOG_
	lbErrCodes err = ERR_NONE;


	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	
	UAP(lb_I_Parameter, param, __FILE__, __LINE__)

	QI(uk, lb_I_Parameter, param, __FILE__, __LINE__)


	parameter->setData("labeltext");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	lb_wxFrame* f = frame_peer->getPeer();
	
	_LOG "Create a static text" LOG_


	wxStaticText *text = new wxStaticText(panel, -1, buttontext->getData(), wxPoint(x->getData(),y->getData()),
					wxSize((int) w->getData(),(int) h->getData() ));

	return ERR_NONE;
/*...e*/
	return ERR_NONE;
}

lbErrCodes LB_STDCALL MyApp::addTextField(lb_I_Unknown* uk) {
	_LOG << "lbErrCodes LB_STDCALL MyApp::addTextField(lb_I_Unknown* uk) called" LOG_
/*...scode:0:*/
	_LOG << "MyApp::addTextField called" LOG_
	lbErrCodes err = ERR_NONE;


	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, buttontext)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, x)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, y)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, w)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, h)	
	
	
	UAP(lb_I_Parameter, param, __FILE__, __LINE__)

	QI(uk, lb_I_Parameter, param, __FILE__, __LINE__)


	parameter->setData("text");
	param->getUAPString(*&parameter, *&buttontext);
	parameter->setData("x");
	param->getUAPInteger(*&parameter, *&x);	
	parameter->setData("y");
	param->getUAPInteger(*&parameter, *&y);	
	parameter->setData("w");
	param->getUAPInteger(*&parameter, *&w);	
	parameter->setData("h");
	param->getUAPInteger(*&parameter, *&h);	
	
	lb_wxFrame* f = frame_peer->getPeer();
	
	_LOG "Create a static text" LOG_


	wxTextCtrl *text = new 
	
	wxTextCtrl(panel, -1, buttontext->getData(), wxPoint(x->getData(),y->getData()),
					wxSize((int) w->getData(),(int) h->getData() ));

	return ERR_NONE;
/*...e*/
	return ERR_NONE;
}
/*...e*/
#endif
#ifndef LB_I_EXTENTIONS
/*...sMyFrame:0:*/
// My frame constructor
MyFrame::MyFrame(wxFrame *frame, char *title, int x, int y, int w, int h):
  wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
{}

/*...sMyFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  Close(TRUE);
}
/*...e*/
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  wxMessageDialog dialog(this, "This demonstrates dynamic event handling",
    "About Dynamic", wxYES_NO|wxCANCEL);

  dialog.ShowModal();
}
/*...e*/
#endif
#ifdef LB_I_EXTENTIONS
/*...slb_wxFrame:0:*/
// My frame constructor
lb_wxFrame::lb_wxFrame(wxFrame *frame, char *title, int x, int y, int w, int h):
  wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
{
	menu_bar = NULL;
}

/*...slb_wxFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  _LOG << "Closing GUI demo" LOG_
  Close(TRUE);
}
/*...e*/
/*...slb_wxFrame\58\\58\OnAbout\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  wxMessageDialog dialog(NULL, "This is the wxWindows GUI wrapper.\nA interface to any application.",
    "About wxWindows GUI wrapper", wxYES_NO|wxCANCEL);

  dialog.ShowModal();
}
/*...e*/
/*...slb_wxFrame\58\\58\OnCheck\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnCheck(wxCommandEvent& WXUNUSED(event) ) {
	char ptr[200] = "";
	sprintf(ptr, "%p for instance %p", menu_bar, this);
	
	_LOG << "Have this instance now: " << ptr LOG_
}
/*...e*/
/*...slb_wxFrame\58\\58\OnBuildMenu\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnBuildMenu(wxCommandEvent& WXUNUSED(event) ) {
	wxMenu *menu = new wxMenu;
	wxMenuBar* mbar = NULL;
	
	menu->Append(DYNAMIC_ABOUT, "&About");
	menu->Append(DYNAMIC_QUIT, "E&xit");

	char ptr[200] = "";
	sprintf(ptr, "%p for instance %p", menu_bar, this);
	_LOG << "Request for a menu pointer: " << ptr LOG_
	
	mbar = getMenuBar();
	if (menu_bar) menu_bar->Append(menu, "T&est");

}
/*...e*/
/*...slb_wxFrame\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lb_wxFrame::OnDispatch(wxCommandEvent& event ) {
        switch (event.GetId()) {
        case DYNAMIC_QUIT:
        	_LOG << "Call OnQuit()" LOG_
                OnQuit(event);
                _LOG << "Called OnQuit()" LOG_
                break;
        case DYNAMIC_ABOUT:
                OnAbout(event);
                break;
        case DYNAMIC_BUILDMENU:
        	{
        		char ptr[20] = "";
        		sprintf(ptr, "%p", this);
        		_LOG << "lb_wxFrame this pointer is " << ptr LOG_
        		OnBuildMenu(event);
        	}
        	break;
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
			lb_I_Module* m = *&manager;
			if (eman == NULL) {
				printf("Get an event manager\n");
				REQUEST(m, lb_I_EventManager, eman)
			}
		
			if (dispatcher == NULL) {
				printf("Get a dispatcher\n");
				REQUEST(m, lb_I_Dispatcher, dispatcher)
				dispatcher->setEventManager(eman.getPtr());
			}				

			UAP_REQUEST(manager.getPtr(), lb_I_String, param)
			param->setData("wxWindows app calls dynamically assigned handler");
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
			QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)
		
			UAP_REQUEST(manager.getPtr(), lb_I_String, result)
			UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
			QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)
		
			dispatcher->dispatch(event.GetId(), uk.getPtr(), &uk_result);
                }
                break;
        }
}
/*...e*/
/*...e*/
#endif

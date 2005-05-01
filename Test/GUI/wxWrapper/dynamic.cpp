// used for documentation

#ifdef LB_I_EXTENTIONS
#undef LB_I_EXTENTIONS
#define LB_I_EXTENTIONS
#endif

/*...sCopyright notice:0:*/
// Orginal version:
/////////////////////////////////////////////////////////////////////////////
// Name:        dynamic.cpp
// Purpose:     Dynamic events wxWindows sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: dynamic.cpp,v 1.71 2005/05/01 21:34:12 lollisoft Exp $
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
            
            40235 Duesseldorf (germany)
*/
/*...e*/
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.71 $
 * $Name:  $
 * $Id: dynamic.cpp,v 1.71 2005/05/01 21:34:12 lollisoft Exp $
 *
 * $Log: dynamic.cpp,v $
 * Revision 1.71  2005/05/01 21:34:12  lollisoft
 * Added informative filename to show when printing memory leaks.
 * Deactivated FreeConsole for memory tests.
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.70  2005/04/28 10:20:19  lollisoft
 * Made password field hide characters.
 *
 * Revision 1.69  2005/04/28 09:46:30  lollisoft
 * Some changes under Linux to built correctly
 *
 * Revision 1.68  2005/04/28 07:25:56  lollisoft
 * Freeing console problem solved.
 *
 * Revision 1.67  2005/04/18 19:01:59  lollisoft
 * Changes due to interface changings in lb_I_Form and lb_I_DatabaseForm.
 *
 * Revision 1.66  2005/04/03 22:10:08  lollisoft
 * Form gets destroyed and - so - self deleted. UAP is not really needed.
 *
 * Revision 1.65  2005/04/02 12:49:56  lollisoft
 * More translations
 *
 * Revision 1.64  2005/04/02 09:45:06  lollisoft
 * Removed log messages and little code changes.
 *
 * Revision 1.63  2005/03/31 15:21:00  lollisoft
 * Reporting name of menu to append after
 *
 * Revision 1.62  2005/03/31 14:42:51  lollisoft
 * Changes to get menubar appending to work
 *
 * Revision 1.61  2005/03/31 09:22:03  lollisoft
 * Copyright text problems under linux.
 * Bugfix while calling _trans in function parameter twice.
 *
 * Revision 1.60  2005/03/19 16:44:05  lollisoft
 * Implemented i18n. Removed unused code.
 *
 * Revision 1.59  2005/03/15 22:26:50  lollisoft
 * More changes on OSX to compile plugins
 *
 * Revision 1.58  2005/03/15 20:52:29  lollisoft
 * Removed from now on unused code.
 *
 * Revision 1.57  2005/03/15 14:43:52  lollisoft
 * Changes for linux to build and let GUI running with plugins
 *
 * Revision 1.56  2005/03/14 18:59:03  lollisoft
 * Various changes and additions to make plugins also work with database forms
 *
 * Revision 1.55  2005/03/10 09:02:34  lollisoft
 * Plugin code complete until real loading.
 *
 * Revision 1.54  2005/03/07 20:27:25  lollisoft
 * Minor compile problem fixed due to Linux changes
 *
 * Revision 1.53  2005/03/07 20:09:34  lollisoft
 * Minor changes to compile under Linux
 *
 * Revision 1.52  2005/03/07 19:30:22  lollisoft
 * Changes to again build correctly under linux
 *
 * Revision 1.51  2005/03/05 23:13:33  lollisoft
 * More changes to build source tree under Mac OS X
 *
 * Revision 1.50  2005/03/03 08:42:21  lollisoft
 * Added loading of plugins.
 *
 * Revision 1.49  2005/03/02 20:02:47  lollisoft
 * Now using DLL version of wxWidgets library
 *
 * Revision 1.48  2005/02/20 18:01:23  lollisoft
 * Bugfix due to buffer overflow affecting GUI sample under Linux
 *
 * Revision 1.47  2005/02/20 09:38:44  lollisoft
 * Removed unneeded menu entries.
 *
 * Revision 1.46  2005/02/14 16:37:14  lollisoft
 * Much tries to get foreign key handling work under linux. But there might be some magic bugs, that don't let them use
 *
 * Revision 1.45  2005/02/12 15:56:27  lollisoft
 * Changed SQL queries and enabled user and password settings via
 * environment.
 *
 * Revision 1.44  2005/02/10 19:16:23  lollisoft
 * Begun with new database types, removed messages
 *
 * Revision 1.43  2005/02/02 13:30:30  lollisoft
 * Latest changes for version 0.4.1
 *
 * Revision 1.42  2005/01/27 12:59:11  lollisoft
 * Changed logging messages and SQL query to not use " in it
 *
 * Revision 1.41  2005/01/25 12:52:56  lollisoft
 * Be only on linux verbose
 *
 * Revision 1.40  2005/01/25 12:28:35  lollisoft
 * Changes for linux due to several reasons. The GUI sample has still problems with database access. Crash in lbDB.cpp while creating bound columns. Console works
 *
 * Revision 1.39  2005/01/24 22:21:24  lollisoft
 * Changes on Linux to get database access running. Login and selecting / loading an application works. But the application would not load
 *
 * Revision 1.38  2005/01/23 17:30:56  lollisoft
 * Some problems under Linux
 *
 * Revision 1.37  2005/01/23 11:35:00  lollisoft
 * Now the code compiles under SuSE Linux 9.1 except wx. It has link problems
 *
 * Revision 1.36  2005/01/22 11:54:57  lollisoft
 * Removed log messages
 *
 * Revision 1.35  2005/01/05 13:40:02  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.34  2004/12/14 19:25:01  lollisoft
 * Change due to temporary variable differences in cleanup
 *
 * Revision 1.33  2004/12/14 16:13:17  lollisoft
 * Implemented a login wizard with application selection from database configuration.
 *
 * Revision 1.32  2004/11/16 19:49:57  lollisoft
 * Added much code to implement a login wizard
 *
 * Revision 1.31  2004/10/05 22:19:54  lollisoft
 * Corrected a bug in enabling/disabling the right buttons in the RIGHT windows.
 * Attention: There is a documented bugfix.
 *
 * Revision 1.30  2004/08/16 05:11:29  lollisoft
 * Better handling of database navigation.
 *
 * Revision 1.29  2004/08/10 18:23:45  lollisoft
 * Lesser logging messages and a try to disable database navigation buttons
 * if they are not needed.
 *
 * Revision 1.28  2004/08/03 22:01:10  lollisoft
 * Implemented adding of new data.
 *
 * Revision 1.27  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.26  2004/07/31 15:51:38  lollisoft
 * Added doxygen formatted documentation.
 *
 * Revision 1.25  2004/07/28 20:45:51  lollisoft
 * Added add and delete handlers, but doesn't work due to incomplete lbDB
 * implementation.
 *
 * Revision 1.24  2004/07/26 22:00:40  lollisoft
 * Better layout and resizeable database form
 *
 * Revision 1.23  2004/07/22 23:36:38  lollisoft
 * Different database forms now working. Cleanup handled correctly and
 * the app always quits correctly.
 *
 * Revision 1.22  2004/07/21 22:21:10  lollisoft
 * Hang on exit solved by providing lb_wxGUI instance to lb_wxFrame. The
 * frame then can cleanup on exit.
 *
 * Revision 1.21  2004/07/18 07:28:26  lollisoft
 * Now the database sample works also under linux. Some bugs solved and minor changes
 *
 * Revision 1.20  2004/07/17 22:25:37  lollisoft
 * GUI demo now works for one database form. I have still one problem: where
 * to cleanup the instances. The app stays running. You will see it at the cmd
 * promt. It doesn't reappear. Press CTRL+C.
 *
 **************************************************************/
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

#include "wx/wizard.h"
/*...e*/

// ID for the menu commands
#define DYNAMIC_QUIT		1000
#define DYNAMIC_TEXT		1001
#define DYNAMIC_ABOUT		1002
#define DYNAMIC_BUILDMENU	1003
#define DYNAMIC_TEST1		1004
#define DYNAMIC_TEST2           1005
#define DYNAMIC_VERBOSE		1006

class lb_wxGUI;

#ifdef LB_I_EXTENTIONS
/*...sclass lb_wxFrame:0:*/
/**
 * \brief This is the main frame implementation.
 *
 * It implements the main event handling interface via OnDispatch.
 */
class lb_wxFrame : 
                public lb_I_wxFrame,
		public wxFrame
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

	((wxFrame*) peer)->Connect( DYNAMIC_VERBOSE, -1, wxEVT_COMMAND_MENU_SELECTED,
	          (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &lb_wxFrame::OnVerbose );


        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\createEventsource\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::createEventsource(lb_I_EventConnector* object) {

/*...screate a menu:0:*/
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  
  file_menu->Append(DYNAMIC_ABOUT, _trans("&About\tCtrl-A"));
  file_menu->Append(DYNAMIC_VERBOSE, _trans("&Verbose\tCtrl-V"));
  file_menu->Append(DYNAMIC_QUIT, _trans("E&xit\tCtrl-x"));

  menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, _trans("&File"));
  
/*...e*/

/*...sset the created menubar:0:*/

  SetMenuBar(menu_bar);

/*...e*/
        return ERR_NONE;
}
/*...e*/
/*...e*/
#endif

/*...swxAppSelectPage:0:*/
class wxAppSelectPage :
public lb_I_Unknown,
public lb_I_EventHandler, 
public wxWizardPageSimple
{
public:

	wxAppSelectPage() {
		app = wxString("");
	}
	
	virtual ~wxAppSelectPage() {
	    _CL_VERBOSE << "wxAppSelectPage::~wxAppSelectPage() called" LOG_
	}


	DECLARE_LB_UNKNOWN()

/*...swxAppSelectPage\40\wxWizard \42\parent\41\:8:*/
	wxAppSelectPage(wxWizard *parent) : wxWizardPageSimple(parent)
	{
	        //m_bitmap = wxBITMAP(wiztest2);

	        box = new wxComboBox(this, -1);
	}

/*...e*/
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

	wxString LB_STDCALL getSelectedApp() { return app; }

/*...svoid setLoggedOnUser\40\char\42\ user\41\:8:*/
	void setLoggedOnUser(char* user) {
		userid = strdup(user);
		 
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		sampleQuery = database->getQuery(0);

		char buffer[800] = "";

		sprintf(buffer, 
			"select Anwendungen.name from Anwendungen inner join User_Anwendungen on "
			"Anwendungen.id = User_Anwendungen.anwendungenid "
			"inner join Users on User_Anwendungen.userid = Users.id where "
			"Users.userid = '%s'"
				, userid);


		sampleQuery->skipFKCollecting();
		sampleQuery->query(buffer);
		sampleQuery->enableFKCollecting();
		
		// Fill up the available applications for that user.

		lbErrCodes err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

			UAP_REQUEST(manager.getPtr(), lb_I_String, s1)	

			s1 = sampleQuery->getAsString(1);

			box->Append(wxString(s1->charrep()));

			while (TRUE) {
				lbErrCodes err = sampleQuery->next();
				
				if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
					s1 = sampleQuery->getAsString(1);
					
					box->Append(wxString(s1->charrep()));
					
					if (err == WARN_DB_NODATA) break;
				}
			}
		}

		return;
	}
/*...e*/

/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
		// The application must have been selected here by the user.
	
		int sel = box->GetSelection();
		
		app = box->GetString(sel);

		if (!app.IsEmpty()) {
			UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		
			char* _app = strdup(app.c_str());
			
			meta->loadApplication(userid, _app);
			
			free(_app);
		}
	
	        return TRUE;
	}
/*...e*/

private:
	wxCheckBox *m_checkbox;
	char* userid;
	wxComboBox* box;
	wxString app;

	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

	
	
	
	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
};


BEGIN_IMPLEMENT_LB_UNKNOWN(wxAppSelectPage)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL wxAppSelectPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxAppSelectPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbErrCodes LB_STDCALL wxAppSelectPage\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL wxAppSelectPage::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	return ERR_NONE;
}
/*...e*/
/*...e*/
/*...swxLogonPage:0:*/
class wxLogonPage :
public lb_I_Unknown,
public lb_I_EventHandler,
public wxWizardPageSimple
{
public:


DECLARE_LB_UNKNOWN()

	wxLogonPage() {
	
	}
	
	virtual ~wxLogonPage() {
	}

	wxLogonPage(wxWizard *parent) : wxWizardPageSimple(parent)
	{
	        //m_bitmap = wxBITMAP(wiztest2);
	}

	char const * LB_STDCALL getTextValue(char* _name);

	void setAppSelectPage(wxAppSelectPage* p) {
		appselect = p;
	}

	// wizard event handlers
	void OnWizardCancel(wxWizardEvent& event)
	{
	        if ( wxMessageBox(_T("Do you really want to cancel?"), _T("Question"),
	                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
	        {
	            // not confirmed
	            event.Veto();
	        }
	}

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

/*...slbErrCodes LB_STDCALL createPasswdCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createPasswdCtrl(char* _name) {
		char* name = NULL;

		name = strdup(_name);

		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint(), wxDefaultSize, wxTE_PASSWORD);

		text->SetName(name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		char* tLabel = new char[strlen(name) + 1];

		tLabel[0] = 0;

		tLabel = strcat(tLabel, name);

		wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
	
		free(name);

		return ERR_NONE;
	}
/*...e*/
/*...slbErrCodes LB_STDCALL createTextCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createTextCtrl(char* _name) {
		char* name = NULL;

		name = strdup(_name);

		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint());

		text->SetName(name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		char* tLabel = new char[strlen(name) + 1];

		tLabel[0] = 0;

		tLabel = strcat(tLabel, name);

		wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
	
		free(name);

		return ERR_NONE;
	}
/*...e*/
/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
		lbErrCodes err = ERR_NONE;
		
		REQUEST(manager.getPtr(), lb_I_Database, database)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		err = database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		sampleQuery = database->getQuery(0);

		char buffer[800] = "";

		char* pass = strdup(getTextValue("Passwort:"));
		char* user = strdup(getTextValue("Benutzer:"));


		sampleQuery->skipFKCollecting();

		sprintf(buffer, "select userid, passwort from Users where userid = '%s' and passwort = '%s'",
                	user, pass);

_CL_VERBOSE << "Query for user " << user LOG_

		if (sampleQuery->query(buffer) != ERR_NONE) {
		    printf("Query for user and password failed\n");
		    sampleQuery->enableFKCollecting();
		    return FALSE;
		}
		
		sampleQuery->enableFKCollecting();

		err = sampleQuery->first();

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			appselect->setLoggedOnUser(user);

			if (pass) free(pass);
			if (user) free(user);

			return TRUE;
		} else {
		        printf("User authentication failed\n");

			if (pass) free(pass);
			if (user) free(user);

			return FALSE;
		}
	}
/*...e*/
/*...svoid init\40\wxWindow\42\ parent\41\:8:*/
	void init(wxWindow* parent)
	{
		char prefix[100] = "";
		sprintf(prefix, "%p", this);

		SetTitle("Login");

		sizerMain  = new wxBoxSizer(wxVERTICAL);
		sizerHor   = new wxBoxSizer(wxHORIZONTAL);
		sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
		sizerLeft  = new wxBoxSizer(wxVERTICAL);	
		sizerRight = new wxBoxSizer(wxVERTICAL);

		int LoginOk;
		int LoginCancel;
	
		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

		char eventName[100] = "";
		
		dispatcher->setEventManager(eman.getPtr());

		registerEventHandler(dispatcher.getPtr());

		sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
		sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);
	
		createTextCtrl("Benutzer:");
		createPasswdCtrl("Passwort:");

		//#define CONNECTOR ((wxFrame*) frame)
		#define CONNECTOR this
	
		SetAutoLayout(TRUE);
		
		sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
		sizerMain->Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);
		
		SetSizer(sizerMain);
	
		sizerMain->SetSizeHints(this);
		sizerMain->Fit(this);
		
		//Centre();
	}
/*...e*/

    
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)


	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];

	wxWindow* OkButton;
	wxWindow* CancelButton;
	
	wxString textValue;

	wxBoxSizer* sizerMain;
	wxBoxSizer* sizerHor;
	wxBoxSizer* sizerAddRem;
	wxBoxSizer* sizerLeft;
	wxBoxSizer* sizerRight;

	wxAppSelectPage* appselect;
};


BEGIN_IMPLEMENT_LB_UNKNOWN(wxLogonPage)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL wxLogonPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxLogonPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbErrCodes LB_STDCALL wxLogonPage\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL wxLogonPage::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	return ERR_NONE;
}
/*...e*/

/*...schar const \42\ LB_STDCALL wxLogonPage\58\\58\getTextValue\40\char\42\ _name\41\:0:*/
char const * LB_STDCALL wxLogonPage::getTextValue(char* _name) {
	
	wxWindow* w = FindWindowByName(wxString(_name));

	if (w != NULL) {
        	wxTextCtrl* tx = (wxTextCtrl*) w;

	        textValue = tx->GetValue();

		return textValue.c_str();
	}

	return "";
}
/*...e*/
/*...e*/

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
/*...sbla:8:*/
/* 
	Handled in cleanup event handler	
	
		if (dialog) {
			dialog->Destroy();
			delete dialog;
			dialog = NULL;
		}
*/
/*...e*/
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
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_wxGUI)
        ADD_INTERFACE(lb_I_wxGUI)
END_IMPLEMENT_LB_UNKNOWN()

/*...sUnimplemented code:0:*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\setDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::setDispatcher(lb_I_Dispatcher* disp) {
       _LOG << "lb_wxGUI::setDispatcher() not implemented yet" LOG_
        
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
/*...e*/

/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::registerEventHandler(lb_I_Dispatcher* disp) {

// Cleanup is no event handler.        
//        disp->addEventHandlerFn(this, (lbEvHandler) &lb_wxGUI::cleanup, "wxGUI_Cleanup"); 
         
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\cleanup\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::cleanup() {
	
	// destroy all still created forms that are hidden.

	if (forms == NULL) {
		_CL_LOG << "lb_wxGUI::cleanup() has nothing to clean up." LOG_
		return ERR_NONE;
	} 

	while (forms->hasMoreElements()) {
		lbErrCodes err = ERR_NONE;
				
		lb_I_Unknown* form = forms->nextElement();

		if (!form) continue;

		UAP(lb_I_DatabaseForm, d, __FILE__, __LINE__)		
		QI(form, lb_I_DatabaseForm, d, __FILE__, __LINE__)
		
		_CL_LOG << "Destroy a form..." LOG_
		
		d->destroy();
	}


        return ERR_NONE;
}
/*...e*/
/*...slb_I_Form\42\ LB_STDCALL lb_wxGUI\58\\58\createLoginForm\40\\41\:0:*/
lb_I_Form* LB_STDCALL lb_wxGUI::createLoginForm() {
	wxWizard *wizard = new wxWizard(NULL, -1, _T("Anmeldung"));

	wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

	wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

	wxSize size = text->GetBestSize();

	wxLogonPage *page2 = new wxLogonPage(wizard);
	
	page2->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	page2->init(frame);

	wxAppSelectPage *page3 = new wxAppSelectPage(wizard);
	page3->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	page2->setAppSelectPage(page3);


	page1->SetNext(page2);
	page2->SetPrev(page1);
	page2->SetNext(page3);
	page3->SetPrev(page2);
	

	wizard->SetPageSize(size);

	if ( ! wizard->RunWizard(page1) )
	{
	    wxMessageBox(_T("Anmeldung fehlgeschlagen"), _T("That's all"),
            wxICON_INFORMATION | wxOK);
        }

//	wxString app = page3->getSelectedApp();

	wizard->Destroy();


#ifdef bla
/*...s:0:*/

	lbErrCodes err = ERR_NONE;

	// Locate the form instance in the container
	
	lbLoginDialog* _dialog = NULL;
	
	if (forms == NULL) {
		REQUEST(getModuleManager(), lb_I_Container, forms)
	}	

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	fName->setData("LoginForm");
	
	QI(fName, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	uk = forms->getElement(&key);	
	
	if (uk != NULL) {
		_dialog = (lbLoginDialog*) *&uk;
	}

	if (_dialog) {
		_dialog->Show(TRUE);
	} else {
		_dialog = new lbLoginDialog();
		_dialog->setModuleManager(getModuleManager(), __FILE__, __LINE__);
		
		QI(_dialog, lb_I_Unknown, uk, __FILE__, __LINE__)
		
		forms->insert(&uk, &key);
		
		delete _dialog;
		_dialog = NULL;
		
		uk = forms->getElement(&key);
		
		if (uk != NULL) {
		        _dialog = (lbLoginDialog*) *&uk;
		}
		
		_dialog->init(frame);
		_dialog->Show();
	}
/*...e*/
#endif
	return NULL;
}
/*...e*/
/*...slb_I_DatabaseForm\42\ LB_STDCALL lb_wxGUI\58\\58\createDBForm\40\char\42\ formName\44\ char\42\ queryString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::createDBForm(char* formName, char* queryString, char* DBName, char* DBUser, char* DBPass) {
	lbErrCodes err = ERR_NONE;

	// Locate the form instance in the container
	
	UAP(lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
	
	if (forms == NULL) {
		REQUEST(getModuleManager(), lb_I_Container, forms)
	}	

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	fName->setData(formName);
	
	QI(fName, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	uk = forms->getElement(&key);	
	
	if (uk != NULL) {
		QI(uk, lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
	}

	if (_dialog.getPtr() != NULL) {
		_dialog->show();
	} else {
	
		/*
		 * Try to find a database form plugin, having the interface lb_I_DatabaseForm.
		 *
		 * This interface contains one and only one member function to initialize the
		 * form with a given SQL query, the required database name, login and password.
		 *
		 * This demonstrates the extensibleability of the GUI wrapper with the new plugin
		 * framework.
		 */

		UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
		UAP(lb_I_Plugin, pl, __FILE__, __LINE__)
		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm");

		if (pl == NULL) {
			char* msg = (char*) malloc(200);
			msg[0] = 0;
			strcpy(msg, _trans("Database form plugin not found or not installed.\n\nDatabase forms are not available."));
			msgBox(_trans("Error"), msg);
			free(msg);
			return NULL;
		}

		uk = pl->getImplementation();
		
		forms->insert(&uk, &key);
		
		//-------------------------------------------------------
		// The form has been cloned. Destroy the unused instance.
		// This avoids application hang at exit.
		
		UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)
		QI(uk, lb_I_DatabaseForm, form, __FILE__, __LINE__)
		
		form->destroy();
		form = NULL;
		//-------------------------------------------------------
		
		uk = forms->getElement(&key);
		
		if (uk != NULL) {
		        QI(uk, lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
		}
		
		_dialog->setName(formName);
		_dialog->init(queryString, DBName, DBUser, DBPass);
		_dialog->show();
	}
	
	return NULL;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\createFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::createFrame() {
        frame = new lb_wxFrame();
        
        frame->setModuleManager(getModuleManager(), __FILE__, __LINE__);
        frame->queryInterface("lb_I_Unknown", (void**) &_main_frame, __FILE__, __LINE__);

	frame->setGUI(this);

	#ifdef VERBOSE
	char ptr[20] = "";
	sprintf(ptr, "%p", frame);
	
	_LOG << "Created a lb_wxFrame object at " << ptr LOG_
        #endif
        
        return frame;
}
/*...e*/
/*...slb_I_Frame\42\ LB_STDCALL lb_wxGUI\58\\58\getFrame\40\\41\:0:*/
lb_I_Frame* LB_STDCALL lb_wxGUI::getFrame() {
        lb_I_Frame* f = NULL;
        
        _main_frame->queryInterface("lb_I_Frame", (void**) &f, __FILE__, __LINE__);
        
        return f;
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
         
        UAP(lb_I_DispatchResponse, d_res, __FILE__, __LINE__)

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
/*...slbErrCodes LB_STDCALL lb_wxGUI\58\\58\msgBox\40\char\42\ windowTitle\44\ char\42\ msg\41\:0:*/
lbErrCodes LB_STDCALL lb_wxGUI::msgBox(char* windowTitle, char* msg) {
        wxMessageDialog dialog(NULL, msg, windowTitle, wxOK);

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

/**
 * \brief Sample application. The main of a wxWidgets application.
 *
 * It is used to demonstrate a GUI sample application.
 */
class MyApp: public wxApp
#ifdef LB_I_EXTENTIONS
, public lb_I_Unknown
, public lb_I_EventConnector
, public lb_I_EventHandler
#endif
{ public:
	/**
	 * Initialisation.
	 */
	MyApp() {
#ifdef LB_I_EXTENTIONS	
	  wxGUI = NULL;
	  metaApp = NULL;
#endif
	 panel = NULL;
	}

	/**
	 * Deletes the lb_I_GUI instance used for independent GUI component handlers.
	 */
	virtual ~MyApp() { 
/*
 * It seems, that frame was deleted prior !!
 */

		if (wxGUI) delete wxGUI;

		printf("MyApp::~MyApp() called.\n");
	}

	/**
	 * Main initialisation member. It shows the integration of my framework into a wxWidgets application.
	 */
    bool OnInit(void);
    
    int  OnExit();

#ifdef LB_I_EXTENTIONS
/*...ssome docs:0:*/
    /*
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

	/**
	 * Create event handler, that this application would provide to the lbDMF user.
	 */
        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);

	// I provide some eventhandlers
	
	/**
	 * Event handler to add a menu in the main application. It is not implemented because
	 * the sample application creates it directly to have a menu if no other modules are
	 * found. At leasd an exit handling is created.
	 */
	lbErrCodes LB_STDCALL lbEvHandler1(lb_I_Unknown* uk);
	
	/**
	 * Event handler to add a menu bar on the main menu. This is used in my lb_I_MetaApplication and
	 * also used in the demo app module.
	 */
	lbErrCodes LB_STDCALL lbEvHandler2(lb_I_Unknown* uk);
	
	/**
	 * Event handler to add a menu entry in a given menu bar name.
	 * \note These handlers should not called by the user of lbDMF. The programmer would use lb_I_MetaApplication to abstract from the real GUI implementation.
	 */
	lbErrCodes LB_STDCALL lbEvHandler3(lb_I_Unknown* uk);	
	
	// These event handlers are canditates for an API replacement

	/**
	 * Add a button to the main frame.
	 */	
	lbErrCodes LB_STDCALL addButton(lb_I_Unknown* uk);
	
	/**
	 * Add a label to the main frame.
	 */
	lbErrCodes LB_STDCALL addLabel(lb_I_Unknown* uk);
	
	/**
	 * Add a text control to the main frame.
	 */
	lbErrCodes LB_STDCALL addTextField(lb_I_Unknown* uk);

	/**
	 * Unused ?
	 */
        lbErrCodes LB_STDCALL HandleGetFrame(lb_I_Unknown* uk); // Thread parameter as output
        
        /**
         * Unused ?
         */
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

	// Storage for event ID's generated on the fly
        
        int AddMenu;
        int AddMenuBar;
        int AddMenuEntry;
        int AddLabel;
        int AddTextField;
        int AddButton;
        
        
/*...sevent manager:8:*/
        /*
         * I need an instance of the event manager. The event manager is used to give me id's for my
         * symbolic event names. First I do not handle a scope.
         */
        
        DEBUG_UAP(lb_I_EventManager, ev_manager, __FILE__, __LINE__)
/*...e*/
/*...smeta application:8:*/
        /*
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
    void OnVerbose(wxCommandEvent& event);
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
#ifdef OSX
IMPLEMENT_APP  (MyApp)
#endif
#ifdef LINUX
#ifndef OSX
IMPLEMENT_APP  (MyApp)
#endif
#endif

int MyApp::OnExit() {
	return 0;
}
/*...sMyApp\58\\58\OnInit\40\void\41\:0:*/
// `Main program' equivalent, creating windows and returning main app frame
/*...stestthis:0:*/
void testthis(void* t) {
#ifdef bla
	char ptr[20] = "";
	sprintf(ptr, "%p", t);
	_LOG << "This is " << ptr LOG_
#endif
}
/*...e*/

bool MyApp::OnInit(void)
{
    char b[100] = "";
    
    wxStopWatch sw;
    
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

#ifdef WINDOWS
// Only windows makes problems with the open console output window
//  FreeConsole();
#endif  
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

/* No event for a cleanup issue, that can be handled by lb_wxFrame knowing of wxGUI
	int wxGUI_Cleanup;

	ev_manager->registerEvent("wxGUI_Cleanup", wxGUI_Cleanup);

        wxGUI->registerEventHandler(*&disp);
*/


	// Register Events, that I provide

	ev_manager->registerEvent("AddMenu", AddMenu);
	ev_manager->registerEvent("AddMenuBar", AddMenuBar);
	ev_manager->registerEvent("AddButton", AddButton);	
	
	
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

	#ifdef VERBOSE
	char ptr[20] = "";
	sprintf(ptr, "%p", uk);
  
	_LOG << "Have got a frame: " << ptr LOG_
  	#endif
  	
	/**
	 * A Peer interface to get the derived class
	 */

	//  QI(uk_em, lb_I_EventManager, ev_manager, __FILE__, __LINE__)
	//  QI(uk, lb_I_wxFrame, frame, __FILE__, __LINE__)


	uk->queryInterface("lb_I_wxFrame", (void**) &frame, __FILE__, __LINE__);
	
	frame_peer = frame->getPeer();
  
  
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
  frame->Connect( DYNAMIC_VERBOSE, -1, wxEVT_COMMAND_MENU_SELECTED,
                  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
                  &MyFrame::OnVerbose );
		  
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
#ifndef OSX
  frame_peer->SetIcon(wxIcon(mondrian_xpm));
#endif
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
  file_menu->Append(DYNAMIC_VERBOSE, "&Verbose");

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
  char* hello = NULL;
#ifdef LB_I_EXTENTIONS
  hello = strdup(_trans("Hello!"));
  (void)new wxStaticText(panel, 311, hello, wxPoint(10, 10), wxSize(-1, -1), 0);
  free(hello);
#endif
#ifndef LB_I_EXTENTIONS
  hello = "Hello!";
  (void)new wxStaticText(panel, 311, hello, wxPoint(10, 10), wxSize(-1, -1), 0);
#endif
/*...e*/
#ifdef LB_I_EXTENTIONS
#ifdef VERBOSE
_LOG << "Made panel" LOG_
#endif
#endif
/*...sShow the window:0:*/
#ifdef LB_I_EXTENTIONS
  // Show the frame
  
  frame_peer->Centre();
  frame_peer->Show(TRUE);

  SetTopWindow(frame_peer);
#endif
#ifndef LB_I_EXTENTIONS
  // Show the frame
  
  frame->Centre();
  frame->Show(TRUE);

  SetTopWindow(frame);
#endif
/*...e*/
#ifdef LB_I_EXTENTIONS
#ifdef VERBOSE
_LOG << "Showed the window" LOG_
#endif
#endif


/*...e*/

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
#ifdef VERBOSE
_LOG << "Initialized metaapplication" LOG_
#endif
#endif

// Not yet working under Mac OS X, not yet tested under Linux
//#ifndef OSX
//#ifndef LINUX
/*
 * Try to load all plugins and initialize it.
 */

	UAP_REQUEST(mm.getPtr(), lb_I_PluginManager, PM)

	PM->initialize();

	if (PM->beginEnumPlugins()) {
	
		while (TRUE) {
		
			UAP(lb_I_Plugin, pl, __FILE__, __LINE__)
			
			pl = PM->nextPlugin();
			
			if (pl == NULL) break;

			pl->initialize();
		
		}
	
	
	}

//#endif
//#endif

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
        #ifdef VERBOSE
        _LOG << "Register event handler" LOG_;
        #endif
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

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, after)

	UAP(lb_I_Parameter, param, __FILE__, __LINE__)
	
	QI(uk, lb_I_Parameter, param, __FILE__, __LINE__)
	
	parameter->setData("name");
	param->getUAPString(*&parameter, *&name);

	if (param->Count() > 1) {
		parameter->setData("after");
		param->getUAPString(*&parameter, *&after);
		
		wxMenu *menu = new wxMenu;
		
		wxMenuBar* mbar = frame_peer->getMenuBar();
		
		int pos = 0;
		
		if (mbar) {
			wxString m = wxString(after->getData());
			pos = mbar->FindMenu(m);
			mbar->Insert(pos+1, menu, name->getData());
		}
	} else {
		wxMenu *menu = new wxMenu;

		wxMenuBar* mbar = frame_peer->getMenuBar();
		if (mbar) mbar->Append(menu, name->getData());
	}
	
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
	lbErrCodes err = ERR_NONE;

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
	
//	if (panel == NULL) panel = new wxPanel(f);
	
	wxButton *button = new wxButton(panel, EvNr, buttontext->getData(), 
					wxPoint(x->getData(),y->getData()), 
					wxSize((int) w->getData(),(int) h->getData() ));

	((wxFrame*) frame_peer)->Connect( EvNr,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
	  (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
	    &lb_wxFrame::OnDispatch );

	return ERR_NONE;
/*...e*/
}
/*...e*/

lbErrCodes LB_STDCALL MyApp::addLabel(lb_I_Unknown* uk) {
#ifdef VERBOSE
	_LOG << "lbErrCodes LB_STDCALL MyApp::addLabel(lb_I_Unknown* uk) called" LOG_
#endif
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

/*...e*/
	return ERR_NONE;
}

lbErrCodes LB_STDCALL MyApp::addTextField(lb_I_Unknown* uk) {
#ifdef VERBOSE
	_LOG << "lbErrCodes LB_STDCALL MyApp::addTextField(lb_I_Unknown* uk) called" LOG_
#endif
/*...scode:0:*/
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
	
#ifdef VERBOSE
	_LOG "Create a static text" LOG_
#endif

	wxTextCtrl *text = new 
	
	wxTextCtrl(panel, -1, buttontext->getData(), wxPoint(x->getData(),y->getData()),
					wxSize((int) w->getData(),(int) h->getData() ));

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

void MyFrame::OnVerbose(wxCommandEvent& WXUNUSED(event) )
{
  setVerbose(!isVerbose());
}

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
	guiCleanedUp = 0;
}

lb_wxFrame::~lb_wxFrame() {
        _LOG << "Closing GUI frame" LOG_
        printf("lb_wxFrame::~lb_wxFrame() called.\n");

        if (guiCleanedUp == 0) {
                if (gui) gui->cleanup();
                guiCleanedUp = 1;
        }
}

void lb_wxFrame::OnRunLogonWizard(wxCommandEvent& WXUNUSED(event)) {
    wxWizard *wizard = new wxWizard(this, -1, _T("Anmeldung"));

    wxWizardPageSimple *page1 = new wxWizardPageSimple(wizard);

    wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

    wxSize size = text->GetBestSize();

    wxLogonPage *page2 = new wxLogonPage(wizard);
    wxAppSelectPage *page3 = new wxAppSelectPage(wizard);
    
    wxWizardPageSimple::Chain(page2, page3);
    
    wizard->SetPageSize(size);

    if ( wizard->RunWizard(page1) )
    {
        wxMessageBox(_T("The wizard successfully completed"), _T("That's all"),
                     wxICON_INFORMATION | wxOK);
    }

    wizard->Destroy();
                                             

}
/*...slb_wxFrame\58\\58\OnQuit\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  	/*
  	 * Let the lb_wxGUI class cleanup it's created  and hidden forms.
  	 * The database form sample is a modal form and may be making the
  	 * problem, if it is not destroyed here.
  	 */
  	 
  	 
	if (guiCleanedUp == 0) {
        	if (gui) gui->cleanup();
        	guiCleanedUp = 1;
	}
	
	Close(TRUE);
}

void lb_wxFrame::OnVerbose(wxCommandEvent& WXUNUSED(event) ) {
    setVerbose(!isVerbose());
}

/*...e*/
/*...slb_wxFrame\58\\58\OnAbout\40\wxCommandEvent\38\ WXUNUSED\40\event\41\ \41\:0:*/
void lb_wxFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  char* buf = strdup(_trans("This is the wxWindows GUI wrapper.\nA interface to any application."));
  char* buf1 = strdup(_trans("About wxWidgets GUI wrapper"));
  wxMessageDialog dialog(NULL, buf, buf1, wxOK);

  dialog.ShowModal();

  free(buf);
  free(buf1);
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
                OnQuit(event);
                break;
        case DYNAMIC_ABOUT:
                OnAbout(event);
                break;
	case DYNAMIC_VERBOSE:
		OnVerbose(event);
		break;
        case DYNAMIC_BUILDMENU:
        	{
        		OnBuildMenu(event);
        	}
        	break;
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
			lb_I_Module* m = getModuleInstance();
			
			//if (eman == NULL) {
				REQUEST(m, lb_I_EventManager, eman)
			//}
		
			//if (dispatcher == NULL) {
				REQUEST(m, lb_I_Dispatcher, dispatcher)
				dispatcher->setEventManager(eman.getPtr());
			//}				

			UAP_REQUEST(m, lb_I_Integer, param)
			
			param->setData(event.GetId());
			
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
			QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)
		
			UAP_REQUEST(m, lb_I_String, result)
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

/*...sWindows based WinMain implementation:0:*/
#ifndef OSX
#ifndef LINUX
wxApp *wxCreateApp()
    {
        wxApp::CheckBuildOptions(wxBuildOptions());
        return new MyApp;
    }

//wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) &wxCreateApp);
MyApp& wxGetApp() { return *(MyApp *)wxTheApp; }

wxApp* _app = NULL;

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    //wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);

    TRMemOpen();
    TRMemSetModuleName(__FILE__);
    
    MyApp::SetInitializerFunction(wxCreateApp);
    
    return wxEntry((WXHINSTANCE) hInstance, (WXHINSTANCE) hPrevInstance, lpCmdLine, nCmdShow);
}
#endif
#endif
/*...e*/

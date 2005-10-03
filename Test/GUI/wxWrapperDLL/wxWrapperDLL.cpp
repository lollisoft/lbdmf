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

/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "lbLoginWizard.cpp"
#pragma interface "lbLoginWizard.cpp"
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
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
/*...e*/
/*...sLB_DATABASE_DLL scope:0:*/
#define LB_LOGINWIZARD_DLL
#include <lbloginwizard-module.h>
/*...e*/

#include <lbConfigHook.h>
#include <lbInterfaces.h>
#include <wxWrapperDLL.h>

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

			sizerMain  = new wxBoxSizer(wxVERTICAL);

			wxStaticText* text = new wxStaticText(this, -1, _trans("Application:"));
			box = new wxChoice(this, -1);
	        
			sizerMain->Add(text, 0, wxEXPAND | wxALL, 5);
			sizerMain->Add(box, 0, wxEXPAND | wxALL, 5);
	        
			SetSizer(sizerMain);
	        
			sizerMain->SetSizeHints(this);
			sizerMain->Fit(this);
	        
			box->SetFocusFromKbd();
			
			Centre();
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

		// Clear the box, if it was previously filled due to navigation.
		
		box->Clear();
		
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
					
					if (err == WARN_DB_NODATA) {
						box->SetSelection(0);
						break;
					}
				}
			}
		}

		sizerMain->Fit(this);

		return;
	}
/*...e*/

/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
	        return TRUE;
	}
/*...e*/

	void OnWizardPageChanging(wxWizardEvent& event) {
		if (event.GetDirection()) {
			int sel = box->GetSelection();
			app = box->GetString(sel);

			if (!app.IsEmpty()) {
				UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		
				char* _app = strdup(app.c_str());
			
				meta->loadApplication(userid, _app);
			
				free(_app);
			}
		}
	}

private:
	wxCheckBox *m_checkbox;
	char* userid;
	wxChoice* box;
	wxString app;
	wxBoxSizer* sizerMain;

	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

	DECLARE_EVENT_TABLE()	
	
	
	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
};

BEGIN_EVENT_TABLE(wxAppSelectPage, wxWizardPageSimple)
    EVT_WIZARD_PAGE_CHANGING(-1, wxAppSelectPage::OnWizardPageChanging)
END_EVENT_TABLE()

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

#ifdef LB_I_EXTENTIONS
/*...sclass lb_wxFrame:0:*/
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

	((wxFrame*) peer)->Connect( DYNAMIC_PLUGINTEST, -1, wxEVT_COMMAND_MENU_SELECTED,
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)
		&lb_wxFrame::OnPluginTest );


        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes lb_wxFrame\58\\58\createEventsource\40\lb_I_EventConnector\42\ object\41\:0:*/
lbErrCodes LB_STDCALL lb_wxFrame::createEventsource(lb_I_EventConnector* object) {

/*...screate a menu:0:*/
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  
  file_menu->Append(DYNAMIC_ABOUT	, _trans("&About\tCtrl-A"));
  file_menu->Append(DYNAMIC_VERBOSE	, _trans("&Verbose\tCtrl-V"));
  file_menu->Append(DYNAMIC_QUIT	, _trans("E&xit\tCtrl-x"));
  file_menu->Append(DYNAMIC_PLUGINTEST	, _trans("&Test Plugin\tCtrl-T"));

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

/*...sclass lb_wxGUI:0:*/
#ifdef LB_I_EXTENTIONS


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
	
	/* Destroy all still created forms that are hidden.
	 * If this would not be taken, the application will hang,
	 * because these windows are still there.
	 *
	 * But the container must be deleted and there seems to be
	 * a double delete. So I need a removeAll function for the container. 
	 */

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
		
		/* Really needed here !
		 * The wxWidgets system doesn't have a or at least has it's own reference counting system.
		 *
		 * So here I must ensure, that the object it self doesn't get deleted in the container.
		 * wxWidgets should call the destructor of the form.
		 */
		 
		 
		_CL_LOG << "Destroy a form with " << d->getRefCount() << " references ..." LOG_
		 
		d++;
		
		d->destroy();
		
		_CL_LOG << "Destroyed the form." LOG_
	}
	
	forms->detachAll();

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

	if (panelUsage) {
		if (!notebook) {
			notebook = new wxNotebook(frame, -1);
			sizerMain = new wxBoxSizer(wxVERTICAL);
			
			frame->SetAutoLayout(TRUE);
	
			sizerMain->Add(notebook, 1, wxEXPAND | wxALL, 0);
	
			frame->SetSizer(sizerMain);
		}
	}
	
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

/*...sCheck for recreation of the form:8:*/
	if ((_dialog.getPtr() != NULL) && (strcmp(queryString, _dialog->getQuery()) != 0)) {
	
		// SQL query from database has been changed. Recreate the dialog from scratch. 
	
		// Don't delete any forms inside the container
		forms->detachAll();
	
		forms->remove(&key);
		
		_dialog->destroy();
	
		_dialog.resetPtr();
	}
/*...e*/

/*...sCreate new\44\ if not yet done:8:*/
	if (_dialog.getPtr() == NULL) {
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

		if (panelUsage) {
			pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUIPanel");
		} else {
			pl = PM->getFirstMatchingPlugin("lb_I_DatabaseForm", "GUIDialog");
		}

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

		if (panelUsage) {
			_dialog->create(notebook->GetId());
		}
		
		_dialog->init(queryString, DBName, DBUser, DBPass);
		
		if (panelUsage) {
			wxWindow* w = frame->FindWindowById(_dialog->getId());
			notebook->AddPage(w, formName, true);
			notebook->Show(true);
		
			sizerMain->SetSizeHints(frame);
			sizerMain->Fit(frame);
		
			frame->Centre();
		}
	
	} else {
		if (panelUsage) {
			int num = notebook->GetPageCount();
			for (int i = 0; i < num; i++) {
				if (strcmp(notebook->GetPageText(i).c_str(), formName) == 0) {
					notebook->SetSelection(i);
				}
			}
		}
	}
/*...e*/

	_dialog++;
	
	return _dialog.getPtr();
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
/*...slb_I_Unknown\42\ LB_STDCALL lb_wxGUI\58\\58\getFrame\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lb_wxGUI::getFrame() {
        lb_I_Unknown* f = NULL;
        
        _main_frame->queryInterface("lb_I_Unknown", (void**) &f, __FILE__, __LINE__);
        
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
/*...slb_I_DatabaseForm\42\ LB_STDCALL lb_wxGUI\58\\58\findDBForm\40\char\42\ name\41\:0:*/
lb_I_DatabaseForm* LB_STDCALL lb_wxGUI::findDBForm(char* name) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleManager(), lb_I_String, fName)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	
	fName->setData(name);
	
	QI(fName, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	uk = forms->getElement(&key);
	
	if (uk == NULL) {
		_CL_LOG << "Error: No form with name '" << name << "' found." LOG_
		return NULL;
	}
	
	UAP(lb_I_DatabaseForm, w, __FILE__, __LINE__)
	QI(uk, lb_I_DatabaseForm, w, __FILE__, __LINE__)
	// Not really needed, because my dialogs are forced to not be smart.
	w++;
	return w.getPtr();
}
/*...e*/
void LB_STDCALL lb_wxGUI::showForm(char* name) {
	if (panelUsage) {
		int num = notebook->GetPageCount();
		for (int i = 0; i < num; i++) {
		        if (strcmp(notebook->GetPageText(i).c_str(), name) == 0) {
	                        notebook->SetSelection(i);
	                }
	        }
	} else {
		lb_I_DatabaseForm* f = findDBForm(name);
		
		if (f) f->show();
	}
}
void LB_STDCALL lb_wxGUI::registerDBForm(char* formName, lb_I_DatabaseForm* form) {

}
#endif
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
        _CL_LOG << "lb_wxFrame::~lb_wxFrame() called." LOG_

        if (guiCleanedUp == 0) {
        	_CL_LOG << "lb_wxFrame::~lb_wxFrame() cleans up GUI" LOG_
                if (gui) gui->cleanup();
                _CL_LOG << "lb_wxFrame::~lb_wxFrame() cleaned up GUI" LOG_
                guiCleanedUp = 1;
        } else {
        	_CL_LOG << "lb_wxFrame::~lb_wxFrame() GUI has been cleaned up prior." LOG_
        	_CL_LOG << "********************************************************" LOG_
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

	_CL_LOG << "lb_wxFrame::OnQuit(...) called." LOG_  	 
  	 
	if (guiCleanedUp == 0) {
		_CL_LOG << "lb_wxFrame::OnQuit(...) cleans up GUI" LOG_
        	if (gui) gui->cleanup();
        	_CL_LOG << "lb_wxFrame::OnQuit(...) cleaned up GUI" LOG_
        	guiCleanedUp = 1;
	}

	_CL_LOG << "lb_wxFrame::OnQuit(...) calls Close(TRUE);" LOG_
	
	Close(TRUE);
	
	_CL_LOG << "lb_wxFrame::OnQuit(...) called Close(TRUE);" LOG_
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


void lb_wxFrame::OnPluginTest(wxCommandEvent& WXUNUSED(event) ) {

	UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl, __FILE__, __LINE__)

	pl = PM->getFirstMatchingPlugin("lb_I_DatabaseNixfind", "bla");
}


/*...e*/
#endif

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak());
                	
                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:                        
                	_CL_LOG << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation)
                        {
                                _CL_VERBOSE << "DLL released by system." LOG_
                        }
                        else
                        {
                                _CL_VERBOSE << "DLL released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }
        
        return TRUE;
}
/*...e*/
#endif

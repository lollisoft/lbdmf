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
#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
/*...e*/
/*...sLB_DATABASE_DLL scope:0:*/
#define LB_LOGINWIZARD_DLL
#include <lbloginwizard-module.h>
/*...e*/
#include <lbLoginWizard.h>

/** \brief This is the plugin module definition class for the login wizard.
 *
 */
class lbPluginModuleLoginWizard :
	public lb_I_PluginModule {
public:

	lbPluginModuleLoginWizard();
	virtual ~lbPluginModuleLoginWizard();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};

/*...sclass lbPluginModuleLoginWizard implementation:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbPluginModuleLoginWizard)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginModule, lbPluginModuleLoginWizard)

BEGIN_PLUGINS(lbPluginModuleLoginWizard)
	ADD_PLUGIN(lbPluginLoginWizard, GUI)
END_PLUGINS()

lbPluginModuleLoginWizard::lbPluginModuleLoginWizard() {
	ref = STARTREF;
}

lbPluginModuleLoginWizard::~lbPluginModuleLoginWizard() {
	_CL_LOG << "lbPluginModuleLoginWizard::~lbPluginModuleLoginWizard() called." LOG_
}

void LB_STDCALL lbPluginModuleLoginWizard::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModuleLoginWizard::setData(lb_I_Unknown* uk) {
        _LOG << "lbPluginModuleLoginWizard::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/


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
			//sizerMain->Fit(this);
	        
			box->SetFocusFromKbd();
			Layout();
			
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

			while (err == ERR_NONE) {
				lbErrCodes err = sampleQuery->next();
				
				if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
					s1 = sampleQuery->getAsString(1);
					
					box->Append(wxString(s1->charrep()));
					
					if (err == WARN_DB_NODATA) {
						break;
					}
				}
			}
			box->SetSelection(0);
		}

		sizerMain->Fit(this);
		//Fit();

		return;
	}
/*...e*/

/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
		// The application must have been selected here by the user.
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

	DECLARE_EVENT_TABLE()

	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

	
	
	
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

		if (err != ERR_NONE) {
			char* buf = strdup(_trans("Login to database failed.\n\nYou could not use the dynamic features of the\napplication without a proper configured database."));
			char* buf1 = strdup(_trans("Error"));
			wxMessageDialog dialog(NULL, buf, buf1, wxOK);

			dialog.ShowModal();

			free(buf);
			free(buf1);		
		}

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

/** \brief Implements a wizard based login plugin.
 *
 */
class lbPluginLoginWizard :
	public lb_I_PluginImpl,
	public lb_I_EventHandler
{
public:

	lbPluginLoginWizard();
	virtual ~lbPluginLoginWizard();

	DECLARE_LB_UNKNOWN()

	/** \brief Registers internally needed event handlers.
	 *
	 * This function registers one event handler, that let the GUI invoke it from
	 * menu actions.
	 */
	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	
	/** \brief Init the menu emtries.
	 *
	 * This connects the login feature to a menu.
	 */
	virtual void LB_STDCALL initialize();
	
	/** \brief Run the login manually.
	 *
	 * This let the login wizard appear manually without invoking it from
	 * the menu entry. You could use this to start the login wizard automatically.
	 */
	virtual bool LB_STDCALL run();

	/** \brief Get the underlying implementation.
	 *
	 * Not needed in this implementation. This implementation has no separate
	 * class with the implementation. This is due to the not existing problem
	 * of multible base class inheritation of lb_I_Unknown.
	 *
	 * If multible intarfaces could be queried, then each
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation();

	virtual lb_I_Unknown* LB_STDCALL peekImplementation();
	void LB_STDCALL releaseImplementation();

	lbErrCodes LB_STDCALL runLogin(lb_I_Unknown* uk);
	
	
	wxWizard *wizard;
	wxWizardPageSimple *page1;
};	

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginLoginWizard)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginLoginWizard, lbPluginLoginWizard)

lbErrCodes LB_STDCALL lbPluginLoginWizard::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbPluginLoginWizard::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginLoginWizard::lbPluginLoginWizard() {
	wizard = NULL;
	page1 = NULL;
	ref = STARTREF;
}

lbPluginLoginWizard::~lbPluginLoginWizard() {
	_CL_LOG << "lbPluginLoginWizard::~lbPluginLoginWizard() called." LOG_
	if (wizard != NULL) {
		_CL_LOG << "Destroy wizard." LOG_
		//wizard->Destroy();
		_CL_LOG << "Wizard destroyed." LOG_
	}
}
	
	
lbErrCodes LB_STDCALL lbPluginLoginWizard::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &lbPluginLoginWizard::runLogin, "RunLogin");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbPluginLoginWizard::runLogin(lb_I_Unknown* uk) {
	run();
	return ERR_NONE;
}
	
/*...svoid LB_STDCALL lbPluginLoginWizard\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL lbPluginLoginWizard::initialize() {

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev)
	
	int lEvent;
	
	ev->registerEvent("RunLogin", lEvent);

	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, disp)
	
	registerEventHandler(*&disp);

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	char* file = strdup(_trans("&File"));
	char* entry = strdup(_trans("Login via &Plugin\tCtrl-P"));
	
	meta->addMenuEntry(file, entry, "RunLogin", "");
	
	free(file);
	free(entry);
}
/*...e*/

/*...sbool LB_STDCALL lbPluginLoginWizard\58\\58\run\40\\41\:0:*/
bool LB_STDCALL lbPluginLoginWizard::run() {
	wizard = new wxWizard(NULL, -1, _T("Anmeldung via Plugin"));

	page1 = new wxWizardPageSimple(wizard);

	wxStaticText *text = new wxStaticText(page1, -1, _T("Melden Sie sich nun an.\n"));

	wxSize size = text->GetBestSize();

	wxLogonPage *page2 = new wxLogonPage(wizard);
	
	page2->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	//page2->init(frame);
	page2->init(NULL);

	wxAppSelectPage *page3 = new wxAppSelectPage(wizard);
	page3->setModuleManager(getModuleManager(), __FILE__, __LINE__);

	page2->setAppSelectPage(page3);

	page1->SetNext(page2);
	page2->SetPrev(page1);
	page2->SetNext(page3);
	page3->SetPrev(page2);
	
	wizard->SetPageSize(size);

	if ( !wizard->RunWizard(page1) )
	{
		wizard->Destroy();
		return false;
        }

	wizard->Destroy();

	return true;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoginWizard\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginLoginWizard::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginLoginWizard\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginLoginWizard::getImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
void LB_STDCALL lbPluginLoginWizard::releaseImplementation() {
	_CL_LOG << "lbPluginLoginWizard::releaseImplementation() called." LOG_
}

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

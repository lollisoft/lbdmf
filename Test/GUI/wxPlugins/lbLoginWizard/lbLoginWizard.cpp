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


#include <lbConfigHook.h>

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
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleLoginWizard)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleLoginWizard)

BEGIN_PLUGINS(lbPluginModuleLoginWizard)
	ADD_PLUGIN(lbPluginLoginWizard, GUI)
END_PLUGINS()

lbPluginModuleLoginWizard::lbPluginModuleLoginWizard() {
	ref = STARTREF;
}

lbPluginModuleLoginWizard::~lbPluginModuleLoginWizard() {
	_CL_VERBOSE << "lbPluginModuleLoginWizard::~lbPluginModuleLoginWizard() called." LOG_
}

void LB_STDCALL lbPluginModuleLoginWizard::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModuleLoginWizard::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleLoginWizard::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/


/*...swxAppSelectPage:0:*/
class wxAppSelectPage :
public lb_I_Unknown,
public lb_I_AppSelectPage, 
public wxWizardPageSimple
{
public:

	wxAppSelectPage() {
		app = wxString("");
	}

	virtual ~wxAppSelectPage();
		
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

	wxString LB_STDCALL getSelectedApp() { return app; }

/*...svoid setLoggedOnUser\40\char\42\ user\41\:8:*/
	void setLoggedOnUser(char* user) {
		lbErrCodes err = ERR_NONE;

		if (userid != NULL) free(userid);
		userid = strdup(user);

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_Container, apps)
		
		meta->setUserName(user);
		
		apps = meta->getApplications();

		box->Clear();
		
		while (apps->hasMoreElements()) {
			UAP(lb_I_String, name)
			UAP(lb_I_Unknown, uk)
			
			uk = apps->nextElement();
			QI(uk, lb_I_String, name)
			
			box->Append(wxString(name->charrep()));
		}

		box->SetSelection(0);

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

	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)

	
	
	
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

wxAppSelectPage::~wxAppSelectPage() {
    _CL_VERBOSE << "wxAppSelectPage::~wxAppSelectPage() called" LOG_
    if (userid != NULL) free(userid);
}



lbErrCodes LB_STDCALL wxAppSelectPage::setData(lb_I_Unknown* uk) {
        _LOG << "wxAppSelectPage::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...swxLogonPage:0:*/
class wxLogonPage :
public lb_I_Unknown,
public lb_I_LogonPage,
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

/*...slbErrCodes LB_STDCALL createTextCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createTextCtrl(char* _name) {
		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint());

		text->SetName(_name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		wxStaticText *label = new wxStaticText(this, -1, _name, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);

		return ERR_NONE;
	}
/*...e*/
/*...slbErrCodes LB_STDCALL createPasswdCtrl\40\char\42\ _name\41\:8:*/
	lbErrCodes LB_STDCALL createPasswdCtrl(char* _name) {
		wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint(), wxDefaultSize, wxTE_PASSWORD);

		text->SetName(_name);

		sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

		wxStaticText *label = new wxStaticText(this, -1, _name, wxPoint());
		sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);

		return ERR_NONE;
	}
/*...e*/
/*...svirtual bool TransferDataFromWindow\40\\41\:8:*/
	virtual bool TransferDataFromWindow()
	{
		lbErrCodes err = ERR_NONE;
		
		char* pass = strdup(getTextValue("Passwort:"));
		char* user = strdup(getTextValue("Benutzer:"));
		
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
			
			if (meta->login(user, pass)) {
				appselect->setLoggedOnUser(user);
				if (pass) free(pass);
				if (user) free(user);
				
				return TRUE;
			} else {
				char* buf = strdup(_trans("Login to database failed.\n\nYou could not use the dynamic features of the\napplication without a proper configured database."));
				char* buf1 = strdup(_trans("Error"));
				wxMessageDialog dialog(NULL, buf, buf1, wxOK);
				
				dialog.ShowModal();
				
				free(buf);
				free(buf1);
				
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
	
		char eventName[100] = "";
		
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

    
	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)


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

class lbLoginHandler : 
	public lb_I_Unknown,
	public lb_I_LogonHandler,
	public lb_I_EventHandler {
public:
		lbLoginHandler();
		virtual ~lbLoginHandler();

		DECLARE_LB_UNKNOWN()

		lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
		lbErrCodes LB_STDCALL runLogin(lb_I_Unknown* uk);
		
		wxWizard *wizard;
		wxWizardPageSimple *page1;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLoginHandler)
	ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLoginHandler::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbLoginHandler::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbLoginHandler::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &lbLoginHandler::runLogin, "RunLogin");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbLoginHandler::runLogin(lb_I_Unknown* uk) {
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
		return ERR_NONE;
    }

	wizard->Destroy();

	return ERR_NONE;
}

lbLoginHandler::lbLoginHandler() {
	wizard = NULL;
	page1 = NULL;
	ref = STARTREF;
}

lbLoginHandler::~lbLoginHandler() {
	_CL_VERBOSE << "lbLoginHandler::~lbLoginHandler() called." LOG_
}


/** \brief Implements a wizard based login plugin.
 *
 */
class lbPluginLoginWizard :
	public lb_I_PluginImpl
{
public:

	lbPluginLoginWizard();
	virtual ~lbPluginLoginWizard();

	DECLARE_LB_UNKNOWN()
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
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
	
	UAP(lb_I_Unknown, loginHandler)
};	

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginLoginWizard)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginLoginWizard, lbPluginLoginWizard)

lbErrCodes LB_STDCALL lbPluginLoginWizard::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginLoginWizard::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginLoginWizard::lbPluginLoginWizard() {
	ref = STARTREF;
}

lbPluginLoginWizard::~lbPluginLoginWizard() {
	_CL_VERBOSE << "lbPluginLoginWizard::~lbPluginLoginWizard() called." LOG_
}

bool LB_STDCALL lbPluginLoginWizard::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginLoginWizard::autorun() {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev)
	
	int lEvent;
	
	ev->registerEvent("RunLogin", lEvent);

	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, disp)
	
	lbLoginHandler* hdl = new lbLoginHandler();
	hdl->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
	QI(hdl, lb_I_Unknown, loginHandler)
	
	hdl->registerEventHandler(*&disp);

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	char* file = strdup(_trans("&File"));
	char* entry = strdup(_trans("Login via &Plugin\tCtrl-P"));
	
	meta->addMenuEntry(file, entry, "RunLogin", "");
	
	free(file);
	free(entry);

	return err;
}

/*...svoid LB_STDCALL lbPluginLoginWizard\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL lbPluginLoginWizard::initialize() {
}
/*...e*/

/*...sbool LB_STDCALL lbPluginLoginWizard\58\\58\run\40\\41\:0:*/
bool LB_STDCALL lbPluginLoginWizard::run() {
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
	_CL_VERBOSE << "lbPluginLoginWizard::releaseImplementation() called." LOG_
}

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
                	
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

/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
*/
/*...e*/


#include <lbConfigHook.h>

/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "wxUpdateChecker.cpp"
#pragma interface "wxUpdateChecker.cpp"
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

#include "wx/sstream.h"
#include "wx/protocol/http.h"

#include "wx/jsonreader.h"
#include "wx/jsonval.h"

/*...e*/
/*...sLB_DATABASE_DLL scope:0:*/
#define LB_LOGINWIZARD_DLL
#include <wxUpdateChecker-module.h>
/*...e*/

#include <timerEventInterceptor.h>
#include <wxUpdateChecker.h>

/** \brief This is the plugin module definition class for the login wizard.
 *
 */
class lbPluginModulewxUpdateChecker :
	public lb_I_PluginModule {
public:

	lbPluginModulewxUpdateChecker();
	virtual ~lbPluginModulewxUpdateChecker();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL install();

	DECLARE_PLUGINS()
};

/*...sclass lbPluginModuleLoginWizard implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulewxUpdateChecker)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulewxUpdateChecker)

BEGIN_PLUGINS(lbPluginModulewxUpdateChecker)
	ADD_PLUGIN(wxUpdateChecker, GUI)
END_PLUGINS()

lbPluginModulewxUpdateChecker::lbPluginModulewxUpdateChecker() {
}

lbPluginModulewxUpdateChecker::~lbPluginModulewxUpdateChecker() {
	_CL_VERBOSE << "lbPluginModuleLoginWizard::~lbPluginModuleLoginWizard() called." LOG_
}

void LB_STDCALL lbPluginModulewxUpdateChecker::initialize() {
	enumPlugins();
}

void LB_STDCALL lbPluginModulewxUpdateChecker::install() {
	
}

lbErrCodes LB_STDCALL lbPluginModulewxUpdateChecker::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulewxUpdateChecker::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

class UpdateCheckerHandler :
	public lb_I_Unknown,
	public lb_I_LogonHandler,
	public lb_I_EventHandler {
public:
		UpdateCheckerHandler();
		virtual ~UpdateCheckerHandler();

		DECLARE_LB_UNKNOWN()

		lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
		lb_I_Unknown* LB_STDCALL getUnknown();
		lbErrCodes LB_STDCALL RunUpdateCheck(lb_I_Unknown* uk);
		lbErrCodes LB_STDCALL RunManualUpdateCheck(lb_I_Unknown* uk);
		lbErrCodes LB_STDCALL RunSilentUpdateCheck(lb_I_Unknown* uk);
		lbErrCodes LB_STDCALL openReleasePage(lb_I_Unknown* uk);

		lb_I_String* LB_STDCALL getReleaseUri();

protected:
	UAP(lb_I_String, lastReleaseUri)
	bool silentRan;
	bool updateCheckRan;

	bool updateDetected;
	bool silent;
	int silent_retry;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(UpdateCheckerHandler)
	ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

UpdateCheckerHandler::UpdateCheckerHandler() {
	_CL_VERBOSE << "UpdateCheckerHandler::UpdateCheckerHandler() called." LOG_
	silentRan = false;
	updateDetected = false;
	silent = false;
	silent_retry = 5;
	updateCheckRan = false;
	REQUEST(getModuleInstance(), lb_I_String, lastReleaseUri)
}

UpdateCheckerHandler::~UpdateCheckerHandler() {
	_CL_VERBOSE << "UpdateCheckerHandler::~UpdateCheckerHandler() called." LOG_
}

lbErrCodes LB_STDCALL UpdateCheckerHandler::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "UpdateCheckerHandler::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lb_I_Unknown* LB_STDCALL UpdateCheckerHandler::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}

lbErrCodes LB_STDCALL UpdateCheckerHandler::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &UpdateCheckerHandler::RunUpdateCheck, "RunUpdateCheck");
	disp->addEventHandlerFn(this, (lbEvHandler) &UpdateCheckerHandler::RunManualUpdateCheck, "RunManualUpdateCheck");	
	disp->addEventHandlerFn(this, (lbEvHandler) &UpdateCheckerHandler::RunSilentUpdateCheck, "RunSilentUpdateCheck");
	disp->addEventHandlerFn(this, (lbEvHandler) &UpdateCheckerHandler::openReleasePage, "openReleasePage");

	return ERR_NONE;
}

/// Run update checks at application start.
lbErrCodes LB_STDCALL UpdateCheckerHandler::RunManualUpdateCheck(lb_I_Unknown* uk) {
	updateCheckRan = false;
	RunUpdateCheck(NULL);
}


/// Run update checks at application start.
lbErrCodes LB_STDCALL UpdateCheckerHandler::RunSilentUpdateCheck(lb_I_Unknown* uk) {
	if (!silentRan) {
		silent = true;
		
		if (silent_retry > 0 && RunUpdateCheck(NULL) != ERR_NONE) 
			silent_retry--;
		else
			silentRan = true;
		
		silent = false;
	}
	return ERR_NONE;
}

/// Run update check per week.
lbErrCodes LB_STDCALL UpdateCheckerHandler::RunUpdateCheck(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	// Do not check twice per application start.
	if (updateCheckRan) return ERR_NONE;
	updateCheckRan = true;
	
	wxHTTP get;
#ifdef LBWXVERSION_OLD
	get.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
#endif
#ifdef LBWXVERSION_CURRENT
	get.SetHeader("Content-type", "text/html; charset=utf-8");
#endif
	int timeout = 10;
	get.SetTimeout(timeout);
	
	int retry = 5;
	
	meta->setStatusText("Info", _trans("Checking for software update. Please be patient for some seconds ."));
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, durationPoints)

	*durationPoints = "Checking for software update. Connection failed. Do a retry ";
	
	// this will wait until the user connects to the internet. It is important in case of dialup (or ADSL) connections
	wxString connectString = 
#ifdef LBWXVERSION_OLD
	_T("www.lollisoft.de");
#endif
#ifdef LBWXVERSION_CURRENT
	"www.lollisoft.de";
#endif

	while (!get.Connect(connectString))  // only the server, no pages here yet ...
	{
		timeout++;

		meta->setStatusText("Info", _trans(durationPoints->charrep()));
		*durationPoints += ".";
		if (!silent) wxSleep(1);
		
		if (retry-- == 0)
			return ERR_WEBSITE_UNREACHABLE;
	}

	meta->setStatusText("Info", _trans("Checking for software update. Please be patient for some seconds .."));

	
	wxApp::IsMainLoopRunning(); // should return true
	
	// use _T("/") for index.html, index.php, default.asp, etc.
	wxInputStream *httpStream = NULL;

	wxString wxUri;
#ifdef LBWXVERSION_OLD
	wxUri = wxString::Format(_T("/updates/lbdmf.json?ostype=%s&version="), getOsType(), VERSIONINFO);
#endif
#ifdef LBWXVERSION_CURRENT
	wxUri = wxString::Format("/updates/lbdmf.json?ostype=%s&version=", getOsType(), VERSIONINFO);
#endif
	
	httpStream = get.GetInputStream(wxUri);
	
	UAP(lb_I_Parameter, UpdateSettings)
	
	meta->setStatusText("Info", _trans("Checking for software update. Please be patient for some seconds ..."));

	if (get.GetError() == wxPROTO_NOERR)
	{
		wxJSONValue  lastReleaseInfo;
		wxString res;
		wxStringOutputStream out_stream(&res);
		httpStream->Read(out_stream);
		
		// construct a JSON parser
		wxJSONReader reader;

		bool updateAvailable = false;
		bool possibleUpdateAvailable = false;
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg_version)
		UAP_REQUEST(getModuleInstance(), lb_I_String, possible_msg_versions)
		
		_LOGALWAYS << res.c_str() LOG_
		
		int numErrors = reader.Parse( res, &lastReleaseInfo );
		
		if (numErrors > 0) {
#ifdef LBWXVERSION_OLD
			wxMessageBox(_T("Unable to read update information!"));
#endif
#ifdef LBWXVERSION_CURRENT
			wxMessageBox("Unable to read update information!");
#endif
		} else {
			//wxMessageBox(res);
			
			meta->setStatusText("Info", _trans("Got release information. Parsing ..."));
			
			// now retrive the array of supported languages
#ifdef LBWXVERSION_OLD
			wxJSONValue releases = lastReleaseInfo[_T("releases")];
#endif
#ifdef LBWXVERSION_CURRENT
			wxJSONValue releases = lastReleaseInfo["releases"];
#endif
			
			bool isArray = releases.IsArray();
			
			UpdateSettings = meta->getPropertySet("UpdateSettings");
			//UpdateSettings->getUAPContainer(*&name, *&KnownVersions);
			
			*msg = "There are new versions available. Go to the product page and download the following version: ";
			
			if (isArray) {
				for ( int i = 0; i < releases.Size(); i++ ) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, version)
#ifdef LBWXVERSION_OLD
					wxString release = releases[i][_T("version")].AsString();
#endif
#ifdef LBWXVERSION_CURRENT
					wxString release = releases[i]["version"].AsString();
#endif
					*version = release.c_str();
					
					wxString release_uri = releases[0]["download"].AsString();
					*lastReleaseUri = release_uri.c_str();

					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, uk)
					QI(version, lb_I_KeyBase, key)
					QI(version, lb_I_Unknown, uk)
					
					// Save version check at position 0
					if (i == 0 && release != VERSIONINFO) {
						updateAvailable = true;
					
						if (!(*msg_version == ""))
							*msg_version += ", ";
						*msg_version += version->charrep();
					}

					// There is a missing visitor implementation for containers. Feature not yet possible.
					
					// Only detect any changes when silent is false. Thus sync only at first run, or when storage has been gone.
					/*
					if (KnownVersions->exists(&key) == 0 && !silent) {
						// Any new entry indicates possible version change
						possibleUpdateAvailable = true;
						
						_LOG << "Insert known version " << version->charrep() << " at position " << i LOG_
						KnownVersions->insert(&uk, &key);
						
						if (!(*possible_msg_versions == ""))
							*possible_msg_versions += ", ";
						*possible_msg_versions += version->charrep();
					}
					*/
				}
				//UpdateSettings->setUAPContainer(*&name, *&KnownVersions);
			}
		}
		
		if (updateAvailable || possibleUpdateAvailable) {
			meta->addPropertySet(*&UpdateSettings, "UpdateSettings");
	
			if (possibleUpdateAvailable) {
				*msg = "The version information has been changed or is initially synchronized. Go to the product page and download the most recent version. Available are: ";
				*msg += possible_msg_versions->charrep();
			}
			else {
				*msg += msg_version->charrep();
			}
			
#ifdef LBWXVERSION_OLD
			if (!silent) wxMessageBox(_T(msg->charrep()));
#endif
#ifdef LBWXVERSION_CURRENT
			if (!silent) wxMessageBox(msg->charrep());
#endif

			if (!updateDetected) {
				int temp;
				updateDetected = true;
				UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
				UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
				eman->registerEvent("openReleasePage", temp);
				disp->addEventHandlerFn(this, (lbEvHandler) &UpdateCheckerHandler::openReleasePage, "openReleasePage");
	
				char* updatemenu = strdup(_trans("Updates available"));
				
				UAP_REQUEST(getModuleInstance(), lb_I_String, menText)
				
				*menText = _trans("This version (");
				*menText += VERSIONINFO;
				*menText += _trans(") is old. Check out for new releases. Detected version: ");
				*menText += msg_version->charrep();
				
				char* menutext = strdup(menText->charrep());

				if (possibleUpdateAvailable) {
					free(menutext);
					menutext = strdup(_trans("A version change has been detected. Please check your version against found ones..."));
				}
				
				meta->addMenuEntry(updatemenu, "Go to release page...", "openReleasePage", "");

				meta->addToolBar("Update Toolbar");
				meta->addToolBarButton("Update Toolbar", menutext, "openReleasePage", "bell.png");
	
				free(updatemenu);
				free(menutext);
			}
		} else {
			meta->setStatusText("Info", _trans("Your software is up to date."));
			wxSleep(1);
		}
	} else {
		wxDELETE(httpStream);
		get.Close();
		return ERR_WEBSITE_UNREACHABLE;
	}

	
	wxDELETE(httpStream);
	get.Close();
	
	return ERR_NONE;
}

lb_I_String* LB_STDCALL UpdateCheckerHandler::getReleaseUri() {
	UAP_REQUEST(getModuleInstance(), lb_I_String, releaseUri)

	*releaseUri = lastReleaseUri->charrep(); 
	releaseUri++;

	return *&releaseUri;
}

lbErrCodes LB_STDCALL UpdateCheckerHandler::openReleasePage(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, releaseUri)
	lb_I_GUI* gui;
	meta->getGUI(&gui);

	releaseUri = getReleaseUri();

	gui->openWebPage("New product release", releaseUri->charrep());
	return ERR_NONE;
}

/** \brief Implements a wizard based login plugin.
 *
 */
class wxUpdateChecker :
	public lb_I_PluginImpl
{
public:

	wxUpdateChecker();
	virtual ~wxUpdateChecker();

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

	UAP(lb_I_Unknown, wxUpdateCheckerHandler)
	UAP(lb_I_DispatchInterceptor, timerEventInterceptor)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(wxUpdateChecker)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfwxUpdateChecker, wxUpdateChecker)

lbErrCodes LB_STDCALL wxUpdateChecker::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "wxUpdateChecker::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

wxUpdateChecker::wxUpdateChecker() {
}

wxUpdateChecker::~wxUpdateChecker() {
	_CL_VERBOSE << "wxUpdateChecker::~wxUpdateChecker() called." LOG_
}

bool LB_STDCALL wxUpdateChecker::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL wxUpdateChecker::autorun() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev)

	int lEvent;

	ev->registerEvent("RunUpdateCheck", lEvent);
	ev->registerEvent("RunManualUpdateCheck", lEvent);
	ev->registerEvent("RunSilentUpdateCheck", lEvent);

	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)

	UpdateCheckerHandler* hdl = new UpdateCheckerHandler();
	
	QI(hdl, lb_I_Unknown, wxUpdateCheckerHandler)
	// Instance needs to survive this call and needs to be
	// destroyed by the owner (wxUpdateChecker)
	wxUpdateCheckerHandler++;
	
	hdl->registerEventHandler(*&disp);

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	char* file = strdup(_trans("&File"));
	char* entry = strdup(_trans("Check for &Updates\tCtrl-U"));

	meta->addMenuEntry(file, entry, "RunManualUpdateCheck", "");

	free(file);
	free(entry);

	lbTimerEventInterceptor* ti = new lbTimerEventInterceptor();
	
	QI(ti, lb_I_DispatchInterceptor, timerEventInterceptor)
	// Instance needs to survive this call and needs to be
	// destroyed by the owner (wxUpdateChecker)
	timerEventInterceptor++;
	
	return err;
}

/*...svoid LB_STDCALL wxUpdateChecker\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL wxUpdateChecker::initialize() {
}
/*...e*/

/*...sbool LB_STDCALL wxUpdateChecker\58\\58\run\40\\41\:0:*/
bool LB_STDCALL wxUpdateChecker::run() {
	return true;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL wxUpdateChecker\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL wxUpdateChecker::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL wxUpdateChecker\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL wxUpdateChecker::getImplementation() {
	lbErrCodes err = ERR_NONE;

	return this;
}
/*...e*/
void LB_STDCALL wxUpdateChecker::releaseImplementation() {
	_CL_VERBOSE << "wxUpdateChecker::releaseImplementation() called." LOG_
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

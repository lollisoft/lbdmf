/*...sLicence:0:*/
/*...sLicence:0:*/
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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>
#include <lbInterfaces.h>



/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
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

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
#include <wx/image.h>
#include <wx/datectrl.h>
#include <wx/file.h>
/*...e*/

#include <lbDatabaseForm.h>

/*...sdoc:0:*/
/*
	This database dialog sample uses a fixed query yet.
	It is used as the only dialog from lb_wxGUI::createDBForm(char* formName).
	
	It should be changed in any way, if there are more different sample queries.
	Handling creation and usage of form elements directly in wxDialog failed
	anyhow.
	
	So I decided to use a derivation of it and put the handlers for the navigation
	into this class and use it only by this class.
	
	I am not sure, if it will work if I create more than one dialog. The peoblem
	may be my event handling mechanism.
	
	Here I use the following code to register my handlers:
	
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBFirst, "DatabaseFirst");
	
	It registers the event "DatabaseFirst" for this instance, because the this pointer is used inside
	my dispatching functionality.
	
	The identifer used here - "DatabaseFirst" - is a logical one. To be sure to get a free ID that
	also works inside wxWidgets, eman registers ID's above 5000 - I think.
	
	To get a different ID for the second 'different' dialog - showing other data, It would be the best
	idea to use the following unique things:
	
	process ID, thread ID optional, this pointer and the hostname.
	
	This leads into difficult code to build up the unique identifer, but macros would help.
	
	
	At least:
	
	It would be easy to implement the native wxWidgets event handling mechanism, but then I am not
	able to do a programmatical navigation from outside wxWidgets.
	
	This is only an idea - a remote control at application level.
*/
/*...e*/

/*...sclass lbOwnerDrawControl:0:*/
class lbOwnerDrawControl :
        public lb_I_Control,
public wxControl {
	
public:
	lbOwnerDrawControl();
	
	virtual ~lbOwnerDrawControl();
	
	void LB_STDCALL create(int parentId) { }
	int  LB_STDCALL getId() { return GetId(); }
	
	void LB_STDCALL windowIsClosing(lb_I_Window* w);
	void LB_STDCALL init(lb_I_Window* parent);
	
	void OnPaint(wxPaintEvent &event);
	
	DECLARE_LB_UNKNOWN()
	
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(lbOwnerDrawControl, wxControl)
    EVT_PAINT  (lbOwnerDrawControl::OnPaint)
END_EVENT_TABLE()
   

BEGIN_IMPLEMENT_LB_UNKNOWN(lbOwnerDrawControl)
        ADD_INTERFACE(lb_I_Control)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbOwnerDrawControl, lbOwnerDrawControl)

lbOwnerDrawControl::lbOwnerDrawControl() : wxControl() {
	ref = STARTREF;
}

lbOwnerDrawControl::~lbOwnerDrawControl() {

}

lbErrCodes LB_STDCALL lbOwnerDrawControl::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbOwnerDrawControl::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbOwnerDrawControl::windowIsClosing(lb_I_Window* w) {
}

void LB_STDCALL lbOwnerDrawControl::init(lb_I_Window* parent) {
	
	// Not sure, if it is a panel based dialog or a dialog.

	lbDatabasePanel* p = (lbDatabasePanel*) parent;
	Create(p, -1, wxPoint(), wxSize(40,40)); 
}

void lbOwnerDrawControl::OnPaint(wxPaintEvent &WXUNUSED(event)) {
	wxPaintDC dc(this);
	PrepareDC(dc);
        
        dc.SetPen(*wxMEDIUM_GREY_PEN);
        for ( int i = 1; i <= 4; i++ )
 	       dc.DrawLine(0, i*10, i*10, 0);
}
/*...e*/

/*...slbDatabasePanel:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
	ADD_INTERFACE(lb_I_Window)
	ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabasePanel, lbDatabasePanel)


/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE << "lbDatabasePanel::setData(...) not implemented yet" LOG_

		UAP(lb_I_DatabaseForm, dbForm)
		QI(uk, lb_I_DatabaseForm, dbForm)
		
		fa = ((lbDatabasePanel*) dbForm.getPtr())->fa;
		((lbDatabasePanel*) dbForm.getPtr())->fa = NULL;
		
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabasePanel\58\\58\lbDatabasePanel\40\\41\:0:*/
lbDatabasePanel::lbDatabasePanel() 
//	: wxPanel(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
//	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbDatabasePanel::lbDatabasePanel() called." LOG_
	ref = STARTREF;
	formName = strdup("Database dialog");
	untranslated_formName = NULL;
	base_formName = NULL;
	noDataAvailable = false;
	_created = false;
	fa = NULL;
	FFI = NULL;
	if (SQLWhere == NULL) {
		REQUEST(getModuleInstance(), lb_I_String, SQLWhere)
	}
}
/*...e*/
/*...slbDatabasePanel\58\\58\\126\lbDatabasePanel\40\\41\:0:*/
lbDatabasePanel::~lbDatabasePanel() {
	_CL_LOG << "lbDatabasePanel::~lbDatabasePanel() called." LOG_

	if (fa != NULL) delete fa;
	if (FFI != NULL) delete FFI;
	free (formName);
	free (base_formName);
	free (untranslated_formName);
	_CL_LOG << "lbDatabasePanel::~lbDatabasePanel() ready." LOG_
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\create\40\int parentId\41\:0:*/
void LB_STDCALL lbDatabasePanel::create(int parentId) {
	wxWindow* w = FindWindowById(parentId);
	
	Create(w, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panel");
	SetFocus();
	_created = true;
}
/*...e*/

/*...sMacros DISABLE_EOF\44\ DISABLE_BOF\44\ DISABLE_FOR_ONE_DATA\44\ DISABLE_FOR_NO_DATA:0:*/


#define DISABLE_EOF() \
	if (sampleQuery->dataFetched()) activateActionButtons(); \
	else deactivateActionButtons(); \
	refreshButton->Enable(); \
	if (allNaviDisabled == false) { \
		nextButton->Disable(); \
		lastButton->Disable(); \
		firstButton->Enable(); \
		prevButton->Enable(); \
		deleteButton->Enable(); \
	} \
	allNaviDisabled = false;


#define DISABLE_BOF() \
	if (sampleQuery->dataFetched()) activateActionButtons(); \
	else deactivateActionButtons(); \
	refreshButton->Enable(); \
	if (allNaviDisabled == false) { \
		prevButton->Disable(); \
		firstButton->Disable(); \
		lastButton->Enable(); \
		nextButton->Enable(); \
		deleteButton->Enable(); \
	} \
	allNaviDisabled = false;


#define DISABLE_FOR_ONE_DATA() \
	refreshButton->Enable(); \
	deleteButton->Enable(); \
	prevButton->Enable(); \
	firstButton->Enable(); \
	lastButton->Disable(); \
	nextButton->Disable();


#define DISABLE_FOR_NO_DATA() \
	deactivateActionButtons(); \
	DISABLE_FOR_ONE_DATA() \
	deleteButton->Disable(); \
	refreshButton->Disable(); \
	allNaviDisabled = true;

/*...e*/


/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	
	sprintf(eventName, "%pDatabaseFirst", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBFirst, eventName);

	sprintf(eventName, "%pDatabaseNext", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBNext,  eventName);

	sprintf(eventName, "%pDatabasePrev", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBPrev,  eventName);

	sprintf(eventName, "%pDatabaseLast", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBLast,  eventName);
	
	sprintf(eventName, "%pDatabaseAdd", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBAdd,  eventName);
	
	sprintf(eventName, "%pDatabaseDelete", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBDelete,  eventName);
	
	sprintf(eventName, "%pDatabaseRefresh", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::lbDBRefresh,  eventName);
	
	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabasePanel\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabasePanel::init(char* _SQLString, char* DBName, char* DBUser, char* DBPass) {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, params)
	
	if (ImageButtonMapperList == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ImageButtonMapperList)
	}
	
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, params)

	if (params != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		params->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		params->getUAPContainer(*&name, *&document);

		*name = "Formulars";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formulars, forms)

		*name = "FormularFields";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formular_Fields, formularfields)

		*name = "FormActions";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formular_Actions, formActions)

		*name = "FormParams";
		uk = document->getElement(&key);
		QI(uk, lb_I_FormularParameter, formParams)

		*name = "AppParams";
		uk = document->getElement(&key);
		QI(uk, lb_I_ApplicationParameter, appParams)

		*name = "AppActions";
		uk = document->getElement(&key);
		QI(uk, lb_I_Actions, appActions)
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		*name = "AppActionTypes";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Types, appActionTypes)


		if ((forms == NULL) || 
		(formParams == NULL) || 
		(appActions == NULL) || 
		(appActionSteps == NULL) || 
		(appActionTypes == NULL) ||
		(appParams == NULL)) {
			_LOG << "Error: Could not recieve one of the required document elements of application!" LOG_
		} else {
			// Preload more data.
			
			
		}
	}

	// Activate relative memory access counts
	//TRMemStartLocalCount();

	if (ignoredPKTables == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ignoredPKTables)
	}

	SetName(formName);

/*...sSizers:8:*/
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = NULL;
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	//wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	//wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);
/*...e*/

/*...sDatabase connection and the stuff:8:*/
	if (database != NULL) {
		_CL_LOG << "WARNING: Database instance available!" LOG_
	}
	
	char* dbbackend = meta->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (database == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return;
	}

	database->init();
	if (database->connect(DBName, DBName, DBUser, DBPass) != ERR_NONE) {
		_LOG << "Error: Could not connect to given database: '" << DBName << "'" LOG_

		return;
	}

	if (_DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBName)
		_DBName->setData(DBName);
	}
	if (_DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBUser)
		_DBUser->setData(DBUser);
	}
	if (_DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, _DBPass)
		_DBPass->setData(DBPass);
	}

	sampleQuery = database->getQuery(DBName, 0);

/*...e*/
		
/*...svariables:8:*/
	int DatabaseFirst;
	int DatabaseNext;
	int DatabasePrev;
	int DatabaseLast;
	int DatabaseAdd;
	int DatabaseDelete;
	int DatabaseRefresh;
	int ImageButtonClick;
/*...e*/
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

/*...sInitialize navigation handlers:8:*/
		char eventName[100] = "";
		
		sprintf(eventName, "%pDatabaseFirst", this);
		eman->registerEvent(eventName, DatabaseFirst);

		sprintf(eventName, "%pDatabaseNext", this);
		eman->registerEvent(eventName,  DatabaseNext);

		sprintf(eventName, "%pDatabasePrev", this);
		eman->registerEvent(eventName,  DatabasePrev);

		sprintf(eventName, "%pDatabaseLast", this);
		eman->registerEvent(eventName,  DatabaseLast);

		sprintf(eventName, "%pDatabaseAdd", this);
		eman->registerEvent(eventName,  DatabaseAdd);

		sprintf(eventName, "%pDatabaseDelete", this);
		eman->registerEvent(eventName,  DatabaseDelete);

		sprintf(eventName, "%pDatabaseRefresh", this);
		eman->registerEvent(eventName,  DatabaseRefresh);

//		sprintf(eventName, "%pImageButtonClick", this);
//		eman->registerEvent(eventName,  ImageButtonClick);

		dispatcher->setEventManager(eman.getPtr());

		registerEventHandler(dispatcher.getPtr());

/*...e*/
	
	sampleQuery->enableFKCollecting();

	sampleQuery->setAutoRefresh(meta->getAutorefreshData());

	if (SQLString == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLString)
		SQLString->setData(_SQLString);
	}

	//sampleQuery->skipPeeking();
	sampleQuery->query(SQLString->charrep(), false);

/*...sDetermine readonly fields:8:*/
	if (FFI != NULL) delete FFI;
	
	/// \todo Add passing a parameter for the application ID.
	FFI = new FormularFieldInformation(formName, sampleQuery.getPtr());

	int columns = sampleQuery->getColumns();

	for (int co = 1; co <= columns; co++) {
		UAP(lb_I_String, name)
		name = sampleQuery->getColumnName(co);

		if (FFI->isReadonly(name->charrep())) {
		        sampleQuery->setReadonly(name->charrep());
		}
	}
/*...e*/

	if (sampleQuery->bind() != ERR_NONE) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_String, msglog)

		*msg = _trans("Failed to prepare database formular.\n\nThe logfile contains more information about this error.");
		
		*msglog = _trans("Failed to bind columns for query:\n\n");
		*msglog += SQLString->charrep();
		*msglog += _trans("\n\nDatabase: ");
		*msglog += _DBName->charrep();
		*msglog += _trans("\nUser: ");
		*msglog += _DBUser->charrep();

		_LOG << msglog->charrep() LOG_

		meta->msgBox(_trans("Error"), msg->charrep());
		return;
	}

	sampleQuery->first();
	
/*...screate database form elements:8:*/
	REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapperList)

	for(int i = 1; i <= columns; i++) {
		sizerHor = new wxBoxSizer(wxHORIZONTAL);
		UAP(lb_I_String, name)

		bool createdControl = false;

		UAP(lb_I_Query, FKColumnQuery)
		UAP(lb_I_Query, FKColumnQuery1)
		
		name = sampleQuery->getColumnName(i);

		/* Determine, if the column is a foreign key. If so try to get the
		   configured column to show instead.
		*/ 

		bool hideThisColumn = false;

		if (sampleQuery->hasFKColumn(name->charrep()) == 1) {
/*...sCreate a combobox:32:*/
			lbErrCodes err = ERR_NONE;

			// Create a mapping instance for this combo box
			UAP_REQUEST(manager.getPtr(), lb_I_Container, _ComboboxMapper)
			UAP_REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapper)

			UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
			UAP(lb_I_KeyBase, key_cbName)
			
			QI(cbName, lb_I_KeyBase, key_cbName)
			QI(_ComboboxMapper, lb_I_Unknown, uk_ComboboxMapper)

			// This is the input parameter

			*cbName = name->charrep();
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, table)
			UAP(lb_I_KeyBase, key)
	
			UAP(lb_I_String, t)
	
			t = sampleQuery->getPKTable(name->charrep());
	
			table->setData(t->charrep());
	
			QI(table, lb_I_KeyBase, key)
	
			if (ignoredPKTables->exists(&key) == 1) hideThisColumn = true;
			
			ComboboxMapperList->insert(&uk_ComboboxMapper, &key_cbName);

			ukComboboxMapper = ComboboxMapperList->getElement(&key_cbName);
			
			QI(ukComboboxMapper, lb_I_Container, ComboboxMapper)
			
			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;

			bool definitionFound = false;
			bool formFound = false;

			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			UAP_REQUEST(getModuleInstance(), lb_I_Long, FID)
			ID->setData(meta->getApplicationID());
			
			forms->finishFormularIteration();
			while (forms->hasMoreFormulars()) {
				forms->setNextFormular();
				FID->setData(forms->getApplicationID());
				
				if (FID->equals(*&ID)) {
					if (strcmp(formName, forms->getName()) == 0) {
						forms->finishFormularIteration();
						formFound = true;
						_LOG << "Found formular name in datamodel." LOG_
						break;
					}
				}
			}
			
			if (formFound == false) {
						_LOG << "Didn't not found formular name for application " << ID->getData() << " in datamodel. (" << formName << ")" LOG_
			}
			
			long FormID = forms->getFormularID();
			
			formularfields->finishFieldsIteration();
			while (formularfields->hasMoreFields()) {
				formularfields->setNextField();
				
				if (formularfields->getFormularID() == FormID) {
					if (strcmp(formularfields->getName(), name->charrep()) == 0) {
						definitionFound = true;
						formularfields->finishFieldsIteration();
						break;
					}
				}
			}
			
			if (definitionFound == false) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
				lbConfigure_FK_PK_MappingDialog* fkpkPanel = new lbConfigure_FK_PK_MappingDialog(FormID);
				fkpkPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				// Pass through the target connection and the current query	
				fkpkPanel->init(sampleQuery.getPtr(), DBName, DBUser, DBPass);
				fkpkPanel->show();
				fkpkPanel->destroy();
				meta->setLoadFromDatabase(true);

				long ID = meta->getApplicationID();
				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();
					
					if (forms->getApplicationID() == ID) {
						if (strcmp(formName, forms->getName()) == 0) {
							forms->finishFormularIteration();
							break;
						}
					}
				}
				
				long FormID = forms->getFormularID();
				
				while (formularfields->hasMoreFields()) {
					formularfields->setNextField();
					
					if (formularfields->getFormularID() == FormID) {
						if (strcmp(formularfields->getName(), name->charrep()) == 0) {
							definitionFound = true;
							formularfields->finishFieldsIteration();
							break;
						}
					}
				}

				UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
				UAP_REQUEST(manager.getPtr(), lb_I_String, name)
				UAP(lb_I_Unknown, uk)
				UAP(lb_I_KeyBase, key)
				
				QI(name, lb_I_KeyBase, key)
				*name = "ApplicationData";
				params->getUAPContainer(*&name, *&document);
				
				*name = "FormularFields";
				if (document->exists(&key) == 1) document->remove(&key);
				QI(formularfields, lb_I_Unknown, uk)
				document->insert(&uk, &key);
				
				database->open(DBName);
				sampleQuery--;
				sampleQuery = database->getQuery(DBName, 0);
				sampleQuery->query(SQLString->charrep(), false);

				// Rebind the query and fetch the first entry as it was before finding out foreign keys.
				if (sampleQuery->bind() != ERR_NONE) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
					UAP_REQUEST(getModuleInstance(), lb_I_String, msglog)

					*msg = _trans("Failed to prepare database formular.\n\nThe logfile contains more information about this error.");
					
					*msglog = _trans("Failed to bind columns for query:\n\n");
					*msglog += SQLString->charrep();
					*msglog += _trans("\n\nDatabase: ");
					*msglog += _DBName->charrep();
					*msglog += _trans("\nUser: ");
					*msglog += _DBUser->charrep();

					_LOG << msglog->charrep() LOG_

					meta->msgBox(_trans("Error"), msg->charrep());
					return;
				}

				sampleQuery->first();
				
			}

#ifdef USE_FKPK_QUERY			
/*...sGet column to display instead key:56:*/
			sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
					"where FKName = '%s' and FKTable = '%s'", name, sampleQuery->getTableName(name));

			UAP(lb_I_Database, lbDMF_DB)
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, lbDMF_DB, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, lbDMF_DB)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (lbDMF_DB == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_DYNAMIC_APP_LOAD_FKPK_SCHEMA;
			}

			lbDMF_DB->init();

			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");

			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			lbDMF_DB->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

			FKColumnQuery = lbDMF_DB->getQuery("lbDMF", 0);
			
			_CL_LOG << "Query for showing visible column of a foreign key: " << buffer << "." LOG_
			
			FKColumnQuery->query(buffer);
			
			err = FKColumnQuery->first();
/*...e*/
			
			//UAP_REQUEST(manager.getPtr(), lb_I_String, VColumn)
			
			// Define this function in my data model
			//VColumn = data_model->getVisualColumnName(name, sampleQuery);
			
			// ------------------
			
			if (err == ERR_DB_NODATA) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
				lbConfigure_FK_PK_MappingDialog* fkpkPanel = new lbConfigure_FK_PK_MappingDialog();
				fkpkPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				// Pass through the target connection and the current query	
				fkpkPanel->init(sampleQuery.getPtr(), DBName, DBUser, DBPass);
				fkpkPanel->show();
				fkpkPanel->destroy();

				FKColumnQuery1 = FKColumnQuery.getPtr();
				FKColumnQuery.resetPtr();
				FKColumnQuery = lbDMF_DB->getQuery(DBName, 0);
				FKColumnQuery->query(buffer);
				err = FKColumnQuery->first();
				
				sampleQuery->open();
				if (!sampleQuery->dataFetched()) err = ERR_DB_NODATA;
			}
#else
			err = ERR_NONE;
#endif			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sHave mapping to visible data for the combobox:64:*/
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)

				UAP_REQUEST(manager.getPtr(), lb_I_String, TargetPKColumn)

				UAP(lb_I_Long, l)
				
#ifdef USE_FKPK_QUERY			
				PKName = FKColumnQuery->getAsString(1);
				PKTable = FKColumnQuery->getAsString(2);
#else
				*PKName = formularfields->getFKName(); /// \todo Semantically wrong. The foreign key of this query points to primary table's ID value. The function should be renamed.
				*PKTable = formularfields->getFKTable(); 
#endif					
				wxChoice *cbox = new wxChoice(this, -1);
				cbox->SetName(name->charrep());
				
				long old_fk = -1;
				
				if (sampleQuery->dataFetched()) {
					l = sampleQuery->getAsLong(i);
					old_fk = l->getData();
				}
				
				buffer[0] = 0;
				
				*TargetPKColumn = sampleQuery->getPKColumn(name->charrep());
				
				// This query is dynamic. Thus it could not mapped to an object. Also these data is from target database, not config database.
				sprintf(buffer, "select \"%s\", \"%s\" from \"%s\" order by \"%s\"", PKName->charrep(), TargetPKColumn->charrep(), PKTable->charrep(), TargetPKColumn->charrep());
				
				_LOG << "Fill combobox based on the following query: " << buffer LOG_
				
				UAP(lb_I_Query, ReplacementColumnQuery)
				
				database->connect(DBName, DBName, DBUser, DBPass);
				
				ReplacementColumnQuery = database->getQuery(DBName, 0);
				
				ReplacementColumnQuery->query(buffer);
				
				lbErrCodes DBerr = ReplacementColumnQuery->first();
				
				int cbox_pos = 0;
				
				if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
/*...sHave data to fill into the combobox and create mappings:104:*/
					UAP_REQUEST(manager.getPtr(), lb_I_String, data)
					UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk)
					
					data = ReplacementColumnQuery->getAsString(1);
					
					data->trim();
					
					if (*data == "") *data = "<empty>";
					if (data->charrep() == NULL) *data = "<empty>";
					
					possible_fk = ReplacementColumnQuery->getAsLong(2);
					
					long possible_fk_pos = possible_fk->getData();
					
					cbox->Append(wxString(data->charrep()));
					
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					
					UAP(lb_I_Unknown, uk_possible_fk)
					UAP(lb_I_KeyBase, key_cbox_pos)
					
					if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
					
					key->setData(cbox_pos);
					cbox_pos++;
					
					QI(key, lb_I_KeyBase, key_cbox_pos)
					UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk_long)

					possible_fk_long->setData(possible_fk_pos);

					QI(possible_fk_long, lb_I_Unknown, uk_possible_fk)
					
					ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
					
					if (DBerr != WARN_DB_NODATA)
					// Only if not WARN_DB_NODATA					
					while ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
						UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk)
						UAP(lb_I_Unknown, uk_possible_fk)
						UAP(lb_I_KeyBase, key_cbox_pos)
						
						DBerr = ReplacementColumnQuery->next();
						
						// Break out in case of no data (not peeking)
						if (DBerr == ERR_DB_NODATA) break;
						
						data = ReplacementColumnQuery->getAsString(1);
						
						data->trim();
						
						if (*data == "") *data = "<empty>";
						if (data->charrep() == NULL) *data = "<empty>";
						
						possible_fk = ReplacementColumnQuery->getAsLong(2);
					
						possible_fk_pos = possible_fk->getData();
					
						cbox->Append(wxString(data->charrep()));
					
						if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
					
						key->setData(cbox_pos);
						cbox_pos++;
						
						QI(key, lb_I_KeyBase, key_cbox_pos)
						UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk_long)
						
						possible_fk_long->setData(possible_fk_pos);
						
						QI(possible_fk_long, lb_I_Unknown, uk_possible_fk)
					
						ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
					
						if (DBerr == WARN_DB_NODATA) break;
					}
					
/*...e*/
				}
				
				if (hideThisColumn == false) {
					addLabel(name->charrep(), sizerHor, hideThisColumn);
					sizerHor->Add(cbox, 1, wxALL, 5);
					sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
				}
				createdControl = true;
/*...e*/
			}

			free(buffer);
/*...e*/
		} else {
			if (FFI->isSpecialColumn(name->charrep())) {
/*...sCreate controls based on configuration in a database:40:*/
				//printf("Creating a special control. (%s)\n", FFI->getControlType(name));

				char* type = FFI->getControlType(name->charrep());

				if (strcmp(type, "toolbarimagefile") == 0) {
					UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
					UAP_REQUEST(manager.getPtr(), lb_I_String, file)
					UAP_REQUEST(manager.getPtr(), lb_I_String, images)
					
					*file = app->getDirLocation();
					
#ifdef OSX
							*images = "/toolbarimages/";
#endif
#ifdef LINUX
							*images = "/toolbarimages/";
#endif
#ifdef WINDOWS
							*images = "\\toolbarimages\\";
#endif

					*file += images->charrep();
					*file += "new.xpm";

					if (!wxFile::Exists(file->charrep())) {
						// Fallback
			#ifdef OSX
			#endif
			#ifdef LINUX
						*file = "/usr/share/lbdmf";			
						*file += images->charrep();
						*file += "new.xpm";
			#endif
			#ifdef WINDOWS
			#endif			    
					}



					int ImageButonClick;
					sprintf(eventName, "%pImageButtonClick%s", this, name->charrep());
					eman->registerEvent(eventName,  ImageButonClick);
					
					_LOG << "Assign a file to an image button: " << file->charrep() LOG_
					
					wxImage im = wxImage(file->charrep(), wxBITMAP_TYPE_XPM);
					im.Rescale(32, 32);
					wxBitmap bm = wxBitmap(im);
					wxBitmapButton* imagebutton = new wxBitmapButton(this, ImageButonClick, bm);
					imagebutton->SetName(name->charrep());
					
					addLabel(name->charrep(), sizerHor, hideThisColumn);
					sizerHor->Add(imagebutton, 1, wxALL, 5);
					sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);

					UAP_REQUEST(manager.getPtr(), lb_I_String, element)
					UAP_REQUEST(manager.getPtr(), lb_I_String, elementname)
					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, uk)
					
					*elementname = name->charrep();
					*element = "";
					
					QI(element, lb_I_Unknown, uk)
					QI(elementname, lb_I_KeyBase, key)
					
					ImageButtonMapperList->insert(&uk, &key);
					
					this->Connect( ImageButonClick,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
						(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnImageButtonClick);
				}
				
				if (strcmp(type, "ownerdraw") == 0) {
					lbOwnerDrawControl *ownerdraw = new lbOwnerDrawControl();
					ownerdraw->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
					ownerdraw->init(this);
				
					ownerdraw->SetName(name->charrep());
				
					addLabel(name->charrep(), sizerHor, hideThisColumn);
					sizerHor->Add(ownerdraw, 1, 0, 5);
					sizerMain->Add(sizerHor, 1, wxALL, 5);

					if (FFI->isReadonly(name->charrep())) {
				        ownerdraw->Disable();
					}
				}

				if (strcmp(type, "image") == 0) {
					UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
					UAP_REQUEST(manager.getPtr(), lb_I_String, file)
					UAP_REQUEST(manager.getPtr(), lb_I_String, images)
					
					*file = app->getDirLocation();
					
#ifdef OSX
							*images = "/toolbarimages/";
#endif
#ifdef LINUX
							*images = "/toolbarimages/";
#endif
#ifdef WINDOWS
							*images = "\\toolbarimages\\";
#endif

					*file += images->charrep();
					*file += "new.xpm";

					if (!wxFile::Exists(file->charrep())) {
						// Fallback
			#ifdef OSX
			#endif
			#ifdef LINUX
						*file = "/usr/share/lbdmf";			
						*file += images->charrep();
						*file += "new.xpm";
			#endif
			#ifdef WINDOWS
			#endif			    
					}


					wxImage im = wxImage(file->charrep(), wxBITMAP_TYPE_XPM);
					im.Rescale(32, 32);
					wxBitmap bm = wxBitmap(im);
					wxStaticBitmap *bitmap = new wxStaticBitmap(this, -1, bm);
					bitmap->SetName(name->charrep());
				
					addLabel(name->charrep(), sizerHor, hideThisColumn);
					sizerHor->Add(bitmap, 1, wxALL, 5);
					sizerMain->Add(sizerHor, 1, wxEXPAND | wxALL, 5);

					if (FFI->isReadonly(name->charrep())) {
				        bitmap->Disable();
					}
				}
				
				free(type);

				createdControl = true;
/*...e*/
			} else {
/*...sCreate controls based on database type:40:*/
			lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

			switch (coltype) {
				case lb_I_Query::lbDBColumnBit:
					{
						wxCheckBox *check = new wxCheckBox(this, -1, 
							"", wxPoint());
						check->SetName(name->charrep());
						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(check, 1, wxALL, 5);	
						sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);

						if (FFI->isReadonly(name->charrep())) {
						        check->Disable();
						}

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnFloat:
					{
						_CL_LOG << "Have a numeric field." LOG_	
						wxTextValidator val = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
						wxArrayString ValArray;
						ValArray.Add(".");
						ValArray.Add("-");
						ValArray.Add("0");
						ValArray.Add("1");
						ValArray.Add("2");
						ValArray.Add("3");
						ValArray.Add("4");
						ValArray.Add("5");
						ValArray.Add("6");
						ValArray.Add("7");
						ValArray.Add("8");
						ValArray.Add("9");
						
						val.SetIncludes(ValArray);
					
						UAP(lb_I_String, s)
						
						s = sampleQuery->getAsString(i);
						
						wxTextCtrl *text = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize, 0, val);
						text->SetName(name->charrep());

						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(text, 1, wxALL, 5);
						sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
							text->Disable();
						}

						createdControl = true;
					}
					break;
				case lb_I_Query::lbDBColumnChar:
					{
						UAP(lb_I_String, s)
						//wxFlexGridSizer* sizerHor = new wxFlexGridSizer(wxHORIZONTAL);
						s = sampleQuery->getAsString(i);
						
						wxTextCtrl *text = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize);
						text->SetName(name->charrep());

						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(text, 1, wxALL, 5);
						sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
							text->Disable();
						}

						createdControl = true;
					}
					break;
				case lb_I_Query::lbDBColumnDate:
					{
						UAP(lb_I_String, s)
						
						s = sampleQuery->getAsString(i);
						wxDateTime dt;
						dt.ParseDate(wxString(s->charrep()));
#ifdef WINDOWS						
						wxDatePickerCtrl *date = new wxDatePickerCtrl(this, -1, dt, wxPoint(), wxDefaultSize, wxDP_DROPDOWN|wxDP_SHOWCENTURY);
#endif
#ifndef WINDOWS
						wxDatePickerCtrl *date = new wxDatePickerCtrl(this, -1, dt, wxPoint(), wxDefaultSize);
#endif
						date->SetName(name->charrep());

						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(date, 1, wxALL, 5);
						sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
							date->Disable();
						}

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnBinary:
				{
					UAP(lb_I_BinaryData, binary)
					
					binary = sampleQuery->getBinaryData(name->charrep());
					
					if (binary == NULL) {
						wxTextCtrl *text = new wxTextCtrl(this, -1, "", wxPoint(), wxSize(200, 20), wxTE_MULTILINE);
						text->SetName(name->charrep());
						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(text, 1, wxEXPAND | wxALL, 5);
						sizerMain->Add(sizerHor, 1, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
							text->Disable();
						}
					} else {
						char* buffer = (char*) malloc(binary->getSize()+1);
						memcpy((void*) buffer, binary->getData(), binary->getSize());
						buffer[binary->getSize()] = 0;
						
						wxTextCtrl *text = new wxTextCtrl(this, -1, buffer, wxPoint(), wxSize(200, 20), wxTE_MULTILINE);
						free(buffer);
						text->SetName(name->charrep());
						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(text, 1, wxEXPAND | wxALIGN_TOP | wxALL, 5);
						sizerMain->Add(sizerHor, 1, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
							text->Disable();
						}
					}
					createdControl = true;
				}
					break;

				case lb_I_Query::lbDBColumnBigInteger:
				case lb_I_Query::lbDBColumnInteger:
					{
						_CL_LOG << "Have a numeric field." LOG_	
						wxTextValidator val = wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, new wxString(""));
						
						wxArrayString ValArray;
						ValArray.Add("0");
						ValArray.Add("1");
						ValArray.Add("2");
						ValArray.Add("3");
						ValArray.Add("4");
						ValArray.Add("5");
						ValArray.Add("6");
						ValArray.Add("7");
						ValArray.Add("8");
						ValArray.Add("9");
						ValArray.Add("-");
						
						val.SetIncludes(ValArray);

						UAP(lb_I_String, s)
						
						s = sampleQuery->getAsString(i);
					
						wxTextCtrl *text = new wxTextCtrl(this, -1, s->charrep(), wxPoint(), wxDefaultSize, 0, val);
				        text->SetName(name->charrep());
						addLabel(name->charrep(), sizerHor, hideThisColumn);
						sizerHor->Add(text, 1, wxALL, 5);
						sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name->charrep())) {
 							text->Disable();
						}

				        createdControl = true;
					}
					break;
				case lb_I_Query::lbDBColumnUnknown:
					_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
					break;
			}
/*...e*/
			}
		}
	}
/*...e*/

	//sizerHor->Add(sizerLeft, 1, wxSHAPED | wxALL, 5);
	//sizerHor->Add(sizerRight, 1, wxSHAPED | wxALL, 5);

	wxButton *button1 = new wxButton(this, DatabaseFirst, _trans("First"));
	wxButton *button2 = new wxButton(this, DatabasePrev, _trans("Prev"));
	wxButton *button3 = new wxButton(this, DatabaseNext, _trans("Next"));
	wxButton *button4 = new wxButton(this, DatabaseLast, _trans("Last"));
	
	firstButton = button1;
	prevButton = button2;
	nextButton = button3;
	lastButton = button4;

	button1->Disable();
	button2->Disable();

	sizerNavi->Add(button1, 1, wxEXPAND | wxALL, 5);
	sizerNavi->Add(button2, 1, wxEXPAND | wxALL, 5);
	sizerNavi->Add(button3, 1, wxEXPAND | wxALL, 5);
	sizerNavi->Add(button4, 1, wxEXPAND | wxALL, 5);

	wxButton *buttonAdd = new wxButton(this, DatabaseAdd, _trans("Add"));
	wxButton *buttonDelete = new wxButton(this, DatabaseDelete, _trans("Delete"));
	wxButton *buttonRefresh = new wxButton(this, DatabaseRefresh, _trans("Refresh"));

	deleteButton = buttonDelete;
	refreshButton = buttonRefresh;

	sizerAddRem->Add(buttonAdd, 1, wxEXPAND | wxALL, 5);
	sizerAddRem->Add(buttonDelete, 1, wxEXPAND | wxALL, 5);
	sizerAddRem->Add(refreshButton, 1, wxEXPAND | wxALL, 5);

/*...sAction handler initializion:8:*/

	if (actionButtons == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, actionButtons)
	}

	//   formulars      <-      NM               ->   actions
	if ((forms != NULL) && (formActions != NULL) && (appActions != NULL)) {
		forms->finishFormularIteration();
		formActions->finishFormularActionIteration();
		appActions->finishActionIteration();
		
		if (fa == NULL) fa = new FormularActions;	
		
		while (forms->hasMoreFormulars()) {
			forms->setNextFormular();

			if (forms->getApplicationID() == meta->getApplicationID()) {
				if (strcmp(forms->getName(), formName) == 0) {
					long FormID = forms->getFormularID();
					
					while (formActions->hasMoreFormularActions()) {
						formActions->setNextFormularAction();
						
						if (formActions->getFormularActionFormularID() == FormID) {
							// Actions for this formular
							long ActionID = formActions->getFormularActionActionID();
							char* eventName = formActions->getFormularActionEvent();
							
							appActions->selectAction(ActionID);
							char* actionName = appActions->getActionName();
							
							// Helps to faster lookup the action ID from event name
							fa->addRegisteredAction(ActionID, eventName);
							
							int actionID = 0;
							char *evName = (char*) malloc(strlen(eventName) + 20);
							sprintf(evName, "%p(%s)", this, eventName);
							eman->registerEvent(evName, actionID);
							wxButton *actionButton = new wxButton(this, actionID, _trans(actionName));
							dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::OnActionButton, evName);
							this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
											(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
							sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);
						}
					}
				}
			}
		}
	} else {
		UAP(lb_I_Query, actionQuery)
		_LOG << "Create actions for formular '" << formName << "' by query." LOG_
		actionQuery = database->getQuery("lbDMF", 0);

		char *_actionquery = "select actions.name, formular_actions.event from actions "
			     "inner join formular_actions on actions.id = formular_actions.action "
			     "inner join Formulare on formular_actions.formular = Formulare.id "
			     "where Formulare.name = '%s'";
		
		char *buf = (char*) malloc(strlen(_actionquery) + strlen(base_formName) + 1);
		buf[0] = 0;
		
		sprintf(buf, _actionquery, base_formName);
		
		_CL_LOG << "Have action query: '" << buf << "'" LOG_ 
			
		actionQuery->skipFKCollecting();	
		actionQuery->query(buf);
		actionQuery->enableFKCollecting();
		free(buf);
		
		err = actionQuery->first();
		
/*...sloop through and find actions:16:*/
		while (err == ERR_NONE) {
			UAP(lb_I_String, action)
			UAP(lb_I_String, actionWhat)
			
			action = actionQuery->getAsString(1);
			actionWhat = actionQuery->getAsString(2);
			
			actionWhat->trim();
			
			int actionID = 0;
			char *eventName = (char*) malloc(strlen(actionWhat->charrep()) + 20);
			sprintf(eventName, "%p(%s)", this, actionWhat->charrep());
			eman->registerEvent(eventName, actionID);
			action->trim();
			wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));
			dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::OnActionButton, eventName);
			this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
						   (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
			sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);
			_CL_LOG << "Added an action (while loop): " << eventName LOG_
			free(eventName);
			err = actionQuery->next();
		}
		
/*...e*/
/*...sget last action:16:*/
		if (err == WARN_DB_NODATA) {
			UAP(lb_I_String, action)
			UAP(lb_I_String, actionWhat)
			action = actionQuery->getAsString(1);
			actionWhat = actionQuery->getAsString(2);
			actionWhat->trim();
			int actionID = 0;
			char *eventName = (char*) malloc(strlen(actionWhat->charrep()) + 20);
			sprintf(eventName, "%p(%s)", this, actionWhat->charrep());
			eman->registerEvent(eventName, actionID);
			action->trim();
			wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));
			dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::OnActionButton, eventName);
			this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
						   (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
			sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);
			_CL_LOG << "Added an action: " << eventName LOG_
			free(eventName);
		}
/*...e*/
/*...e*/
	}
	

_CL_LOG << "Connect event handlers" LOG_
/*...sconnect event handlers:8:*/
//#define CONNECTOR ((wxFrame*) frame)
#define CONNECTOR this

	CONNECTOR->Connect( DatabaseFirst,  -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	CONNECTOR->Connect( DatabaseNext,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	CONNECTOR->Connect( DatabasePrev,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	CONNECTOR->Connect( DatabaseLast,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);

	CONNECTOR->Connect( DatabaseAdd,  -1, wxEVT_COMMAND_BUTTON_CLICKED,   
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	CONNECTOR->Connect( DatabaseDelete, -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	CONNECTOR->Connect( DatabaseRefresh, -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
/*...e*/


	/*
	 * Connect the 'ownerdrawn' controls to the OnPaint handler.
	 *
	 * This would be a loop for all controls. The data for that
	 * control should be in any format. The drawing handler must
	 * be capable to handle it independently.
	 */

	//TRMemStopLocalCount();
	//TRMemResetLocalCount();


	SetAutoLayout(TRUE);
	
	//sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerActions, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerNavi, 0, wxEXPAND | wxALL, 5);
	
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	//Centre();

	_CL_LOG << "lbDatabasePanel::init(...) ready. Move to first row." LOG_

	if (sampleQuery->dataFetched()) {
		activateActionButtons();
		sampleQuery->first();
		lbDBRead();
	} else {
		deactivateActionButtons();
		nextButton->Disable();
		lastButton->Disable();
		deleteButton->Disable();
	}
	_created = true;
	
	if (sampleQuery->getColumns() == 0) {
		meta->msgBox("Warning", "Database backend does not contain any columns.");
	}
}
/*...e*/

void LB_STDCALL lbDatabasePanel::activateActionButtons() {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	if ((forms != NULL) && (formActions != NULL) && (appActions != NULL)) {
		forms->finishFormularIteration();
		formActions->finishFormularActionIteration();
		appActions->finishActionIteration();
		
		if (fa == NULL) fa = new FormularActions;	
		
		while (forms->hasMoreFormulars()) {
			forms->setNextFormular();

			if (forms->getApplicationID() == meta->getApplicationID()) {
				if (strcmp(forms->getName(), base_formName) == 0) {
					long FormID = forms->getFormularID();
					
					while (formActions->hasMoreFormularActions()) {
						formActions->setNextFormularAction();
						
						if (formActions->getFormularActionFormularID() == FormID) {
							// Actions for this formular
							long ActionID = formActions->getFormularActionActionID();
							char* eventName = formActions->getFormularActionEvent();
							char* actionName = strdup (_trans(appActions->getActionName()));
							appActions->selectAction(ActionID);
							
							_LOG << "Activate action '" << actionName << "'" LOG_
							
							wxWindow* w = FindWindowByLabel(actionName, this);
							if (w) w->Enable();
							free(actionName);
						}
					}
				}
			}
		}
	}
}

void LB_STDCALL lbDatabasePanel::deactivateActionButtons() {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	if ((forms != NULL) && (formActions != NULL) && (appActions != NULL)) {
		forms->finishFormularIteration();
		formActions->finishFormularActionIteration();
		appActions->finishActionIteration();
		
		if (fa == NULL) fa = new FormularActions;	
		
		while (forms->hasMoreFormulars()) {
			forms->setNextFormular();

			if (forms->getApplicationID() == meta->getApplicationID()) {
				if (strcmp(forms->getName(), base_formName) == 0) {
					long FormID = forms->getFormularID();
					
					while (formActions->hasMoreFormularActions()) {
						formActions->setNextFormularAction();
						
						if (formActions->getFormularActionFormularID() == FormID) {
							// Actions for this formular
							long ActionID = formActions->getFormularActionActionID();
							char* eventName = formActions->getFormularActionEvent();
							char* actionName = strdup (_trans(appActions->getActionName()));
							appActions->selectAction(ActionID);

							_LOG << "Deactivate action '" << actionName << "'" LOG_

							wxWindow* w = FindWindowByLabel(actionName, this);
							if (w) w->Disable();
							free(actionName);
						}
					}
				}
			}
		}
	}
}


void LB_STDCALL lbDatabasePanel::addLabel(char* text, wxSizer* sizer, bool hideThisColumn) {
	char* tLabel = (char*) malloc(strlen(text) + 6);
	tLabel[0] = 0;
	tLabel = strcat(tLabel, text); 
	wxStaticText *label = new wxStaticText(this, -1, _trans(tLabel), wxPoint());
	tLabel = strcat(tLabel, "_lbl");
	label->SetName(_trans(tLabel));
	if (hideThisColumn == false) sizer->Add(label, 1, wxALL|wxADJUST_MINSIZE, 5);
	
	free(tLabel);
}

void  LB_STDCALL lbDatabasePanel::reopen() {
	/*
	 sampleQuery->reopen();
	 
	 prevButton->Enable();
	 firstButton->Enable();
	 lastButton->Enable();
	 nextButton->Enable();
	 deleteButton->Enable();
	 
	 if (sampleQuery->isFirst()) lbDBFirst(NULL);
	 if (sampleQuery->isLast()) lbDBLast(NULL);
	 lbDBRead();
	 */
	lbDBRefresh(NULL);
}

lbErrCodes  LB_STDCALL lbDatabasePanel::close() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	_LOG << "lbErrCodes LB_STDCALL lbDatabasePanel::close() called." LOG_
	
	if (database == NULL) {
		char* dbbackend = meta->getApplicationDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}
		
		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
		database->init();
	}
	
	if (err == ERR_DB_NODATA) {
		DISABLE_FOR_NO_DATA()
		
		return ERR_DB_NODATA;
	}
	
	_LOG << "lbDatabasePanel::close() closes the database." LOG_
	database->close();
	return ERR_NONE;
}

lbErrCodes  LB_STDCALL lbDatabasePanel::open() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	_LOG << "lbErrCodes LB_STDCALL lbDatabasePanel::open() called." LOG_
	
	if (database == NULL) {
		char* dbbackend = meta->getApplicationDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}
		
		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
		database->init();
	}

	
	_LOG << "lbErrCodes LB_STDCALL lbDatabasePanel::open() opens the database." LOG_
	database->open(_DBName->charrep());
	sampleQuery--;
	sampleQuery = database->getQuery(_DBName->charrep(), 0);
	char* newSql = sampleQuery->setWhereClause(getQuery(), SQLWhere->charrep());
	_LOG << "Got a new query for reopen: " << newSql LOG_
	sampleQuery->query(newSql, false);
	free(newSql);
	
	// Rebind the query and fetch the first entry as it was before finding out foreign keys.
	if (sampleQuery->bind() != ERR_NONE) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_String, msglog)
		
		*msg = _trans("Failed to prepare database formular.\n\nThe logfile contains more information about this error.");
		
		*msglog = _trans("Failed to bind columns for query:\n\n");
		*msglog += SQLString->charrep();
		*msglog += _trans("\n\nDatabase: ");
		*msglog += _DBName->charrep();
		*msglog += _trans("\nUser: ");
		*msglog += _DBUser->charrep();
		
		_LOG << msglog->charrep() LOG_
		
		meta->msgBox(_trans("Error"), msg->charrep());
		return ERR_DB_NODATA;
	}
	
	_LOG << "lbErrCodes LB_STDCALL lbDatabasePanel::open() fetches a record." LOG_
	sampleQuery->first();
	
	lbDBRead();
	
	FFI = new FormularFieldInformation(formName, sampleQuery.getPtr());
	
	int columns = sampleQuery->getColumns();
	
	for (int co = 1; co <= columns; co++) {
		UAP(lb_I_String, name)
		name = sampleQuery->getColumnName(co);
		
		if (FFI->isReadonly(name->charrep())) {
			sampleQuery->setReadonly(name->charrep());
		}
	}
	
	REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapperList)
	
	for(int i = 1; i <= columns; i++) {
		UAP(lb_I_String, name)
		
		bool createdControl = false;
		
		UAP(lb_I_Query, FKColumnQuery)
		UAP(lb_I_Query, FKColumnQuery1)
		
		name = sampleQuery->getColumnName(i);
		
		bool hideThisColumn = false;
		
		if (sampleQuery->hasFKColumn(name->charrep()) == 1) {
			/*...sCreate a combobox:32:*/
			lbErrCodes err = ERR_NONE;
			
			// Create a mapping instance for this combo box
			UAP_REQUEST(manager.getPtr(), lb_I_Container, _ComboboxMapper)
			UAP_REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapper)
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
			UAP(lb_I_KeyBase, key_cbName)
			
			QI(cbName, lb_I_KeyBase, key_cbName)
			QI(_ComboboxMapper, lb_I_Unknown, uk_ComboboxMapper)
			
			// This is the input parameter
			
			*cbName = name->charrep();
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, table)
			UAP(lb_I_KeyBase, key)
			
			UAP(lb_I_String, t)
			
			t = sampleQuery->getPKTable(name->charrep());
			
			table->setData(t->charrep());
			
			QI(table, lb_I_KeyBase, key)
			
			if (ignoredPKTables->exists(&key) == 1) hideThisColumn = true;
			
			if (ComboboxMapperList->exists(&key_cbName) == 1) {
				ComboboxMapperList->remove(&key_cbName);
			}
			
			ComboboxMapperList->insert(&uk_ComboboxMapper, &key_cbName);
			
			ukComboboxMapper = ComboboxMapperList->getElement(&key_cbName);
			
			QI(ukComboboxMapper, lb_I_Container, ComboboxMapper)
			
			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;
			
			bool definitionFound = false;
			bool formFound = false;
			
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			UAP_REQUEST(getModuleInstance(), lb_I_Long, FID)
			ID->setData(meta->getApplicationID());
			
			forms->finishFormularIteration();
			while (forms->hasMoreFormulars()) {
				forms->setNextFormular();
				FID->setData(forms->getApplicationID());
				
				if (FID->equals(*&ID)) {
					if (strcmp(base_formName, forms->getName()) == 0) {
						forms->finishFormularIteration();
						formFound = true;
						_LOG << "Found formular name in datamodel." LOG_
						break;
					}
				}
			}
			
			if (formFound == false) {
				_LOG << "Didn't not found formular name for application " << ID->getData() << " in datamodel. (" << formName << ")" LOG_
			}
			
			long FormID = forms->getFormularID();
			
			formularfields->finishFieldsIteration();
			while (formularfields->hasMoreFields()) {
				formularfields->setNextField();
				
				if (formularfields->getFormularID() == FormID) {
					if (strcmp(formularfields->getName(), name->charrep()) == 0) {
						definitionFound = true;
						formularfields->finishFieldsIteration();
						break;
					}
				}
			}
			
			if (definitionFound == false) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
				lbConfigure_FK_PK_MappingDialog* fkpkPanel = new lbConfigure_FK_PK_MappingDialog(FormID);
				fkpkPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				// Pass through the target connection and the current query	
				fkpkPanel->init(sampleQuery.getPtr(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());
				fkpkPanel->show();
				fkpkPanel->destroy();
				
				UAP(lb_I_Parameter, params)
				UAP(lb_I_Unknown, uk)
				uk = meta->getActiveDocument();
				QI(uk, lb_I_Parameter, params)
				
				UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
				UAP_REQUEST(manager.getPtr(), lb_I_String, name)
				UAP(lb_I_KeyBase, key)
				
				QI(name, lb_I_KeyBase, key)
				*name = "ApplicationData";
				params->getUAPContainer(*&name, *&document);
				
				*name = "FormularFields";
				if (document->exists(&key) == 1) document->remove(&key);
				QI(formularfields, lb_I_Unknown, uk)
				document->insert(&uk, &key);
				
				
				database->open(DBName->charrep());
				sampleQuery--;
				sampleQuery = database->getQuery(DBName->charrep(), 0);
                
                char* newSql = sampleQuery->setWhereClause(getQuery(), SQLWhere->charrep());
				_LOG << "Got a new query for reopen: " << newSql LOG_
				sampleQuery->query(newSql, false);
				free(newSql);
				
				long ID = meta->getApplicationID();
				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();
					
					if (forms->getApplicationID() == ID) {
						if (strcmp(formName, forms->getName()) == 0) {
							forms->finishFormularIteration();
							break;
						}
					}
				}
				
				long FormID = forms->getFormularID();
				
				while (formularfields->hasMoreFields()) {
					formularfields->setNextField();
					
					if (formularfields->getFormularID() == FormID) {
						if (strcmp(formularfields->getName(), name->charrep()) == 0) {
							definitionFound = true;
							formularfields->finishFieldsIteration();
							break;
						}
					}
				}
			}
			
#ifdef USE_FKPK_QUERY			
			/*...sGet column to display instead key:56:*/
			sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
					"where FKName = '%s' and FKTable = '%s'", name, sampleQuery->getTableName(name));
			
			UAP(lb_I_Database, lbDMF_DB)
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, lbDMF_DB, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, lbDMF_DB)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}
			
			if (lbDMF_DB == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
			}
			lbDMF_DB->init();
			
			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";
			
			lbDMF_DB->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
			
			FKColumnQuery = lbDMF_DB->getQuery("lbDMF", 0);
			
			_CL_LOG << "Query for showing visible column of a foreign key: " << buffer << "." LOG_
			
			FKColumnQuery->query(buffer);
			
			err = FKColumnQuery->first();
			/*...e*/
			
			//UAP_REQUEST(manager.getPtr(), lb_I_String, VColumn)
			
			// Define this function in my data model
			//VColumn = data_model->getVisualColumnName(name, sampleQuery);
			
			// ------------------
			
			if (err == ERR_DB_NODATA) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
				lbConfigure_FK_PK_MappingDialog* fkpkPanel = new lbConfigure_FK_PK_MappingDialog();
				fkpkPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				// Pass through the target connection and the current query	
				fkpkPanel->init(sampleQuery.getPtr(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());
				fkpkPanel->show();
				fkpkPanel->destroy();
				
				FKColumnQuery1 = FKColumnQuery.getPtr();
				FKColumnQuery.resetPtr();
				FKColumnQuery = lbDMF_DB->getQuery(DBName, 0);
				FKColumnQuery->query(buffer);
				err = FKColumnQuery->first();
			}
#else
			err = ERR_NONE;
#endif			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				/*...sHave mapping to visible data for the combobox:64:*/
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
				
				UAP_REQUEST(manager.getPtr(), lb_I_String, TargetPKColumn)
				
				UAP(lb_I_Long, l)
				
#ifdef USE_FKPK_QUERY			
				PKName = FKColumnQuery->getAsString(1);
				PKTable = FKColumnQuery->getAsString(2);
#else
				*PKName = formularfields->getFKName(); /// \todo Semantically wrong. The foreign key of this query points to primary table's ID value. The function should be renamed.
				*PKTable = formularfields->getFKTable(); 
#endif					
				
				wxWindow* w = FindWindowByName(wxString(name->charrep()), this);
				wxChoice *cbox = (wxChoice*) w;
				cbox->Clear();
				//cbox->SetName(name->charrep());
				
				l = sampleQuery->getAsLong(i);
				
				int old_fk = l->getData();
				
				buffer[0] = 0;
				
				*TargetPKColumn = sampleQuery->getPKColumn(name->charrep());
				
				// This query is dynamic. Thus it could not mapped to an object. Also these data is from target database, not config database.
				sprintf(buffer, "select \"%s\", \"%s\" from \"%s\" order by \"%s\"", PKName->charrep(), TargetPKColumn->charrep(), PKTable->charrep(), TargetPKColumn->charrep());
				
				_LOG << "Fill combobox based on the following query: " << buffer LOG_
				
				UAP(lb_I_Query, ReplacementColumnQuery)
				
				database->connect(_DBName->charrep(), _DBName->charrep(), _DBUser->charrep(), _DBPass->charrep());
				
				ReplacementColumnQuery = database->getQuery(_DBName->charrep(), 0);
				
				ReplacementColumnQuery->query(buffer);
				
				lbErrCodes DBerr = ReplacementColumnQuery->first();
				
				int cbox_pos = 0;
				
				if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
					/*...sHave data to fill into the combobox and create mappings:104:*/
					UAP_REQUEST(manager.getPtr(), lb_I_String, data)
					UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk)
					
					data = ReplacementColumnQuery->getAsString(1);
					
					data->trim();
					
					if (*data == "") *data = "<empty>";
					if (data->charrep() == NULL) *data = "<empty>";
					
					possible_fk = ReplacementColumnQuery->getAsLong(2);
					
					long possible_fk_pos = possible_fk->getData();
					
					cbox->Append(wxString(data->charrep()));
					
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					
					UAP(lb_I_Unknown, uk_possible_fk)
					UAP(lb_I_KeyBase, key_cbox_pos)
					
					if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
					
					key->setData(cbox_pos);
					cbox_pos++;
					
					QI(key, lb_I_KeyBase, key_cbox_pos)
					UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk_long)
					
					possible_fk_long->setData(possible_fk_pos);
					
					QI(possible_fk_long, lb_I_Unknown, uk_possible_fk)
					
					ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
					
					if (DBerr != WARN_DB_NODATA)
						// Only if not WARN_DB_NODATA					
						while ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
							UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk)
							UAP(lb_I_Unknown, uk_possible_fk)
							UAP(lb_I_KeyBase, key_cbox_pos)
							
							DBerr = ReplacementColumnQuery->next();
							
							// Break out in case of no data (not peeking)
							if (DBerr == ERR_DB_NODATA) break;
							
							data = ReplacementColumnQuery->getAsString(1);
							
							data->trim();
							
							if (*data == "") *data = "<empty>";
							if (data->charrep() == NULL) *data = "<empty>";
							
							possible_fk = ReplacementColumnQuery->getAsLong(2);
							
							possible_fk_pos = possible_fk->getData();
							
							cbox->Append(wxString(data->charrep()));
							
							if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
							
							key->setData(cbox_pos);
							cbox_pos++;
							
							QI(key, lb_I_KeyBase, key_cbox_pos)
							UAP_REQUEST(manager.getPtr(), lb_I_Long, possible_fk_long)
							
							possible_fk_long->setData(possible_fk_pos);
							
							QI(possible_fk_long, lb_I_Unknown, uk_possible_fk)
							
							ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
							
							if (DBerr == WARN_DB_NODATA) break;
						}
					
					/*...e*/
				}
				/*...e*/
			}
			
			free(buffer);
			/*...e*/
		}
	}
	
    DISABLE_EOF()
    return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::setName(char const * name, char const * appention) {
	if (formName) free(formName);
	if (untranslated_formName) free(untranslated_formName);

	char* transl = _trans((char*) name);
		
	char* temp = (char*) malloc(strlen(transl)+1);
	temp[0] = 0;
	strcpy(temp, transl);

	if (appention) {
		formName = (char*) malloc(1+strlen(temp)+strlen(appention));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name)+strlen(appention));
	} else {
		formName = (char*) malloc(1+strlen(temp));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name));
	}
	
	formName[0] = 0;
	strcat(formName, temp);
	if (appention) strcat(formName, appention);
	free(temp);
		
	untranslated_formName[0] = 0;
	strcat(untranslated_formName, name);
	if (appention) strcat(untranslated_formName, appention);
		
	base_formName[0] = 0;
	strcat(base_formName, name);
		
	return ERR_NONE;
}
/*...e*/

/*...schar\42\ LB_STDCALL lbDatabasePanel\58\\58\getQuery\40\\41\:0:*/
char* LB_STDCALL lbDatabasePanel::getQuery() {
	return SQLString->charrep();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabasePanel\58\\58\getColumnName\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabasePanel::getColumnName(int pos) {
	return sampleQuery->getColumnName(pos);
}
/*...e*/

void LB_STDCALL lbDatabasePanel::windowIsClosing(lb_I_Window* w) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_DatabaseForm, form)
	QI(w, lb_I_DatabaseForm, form)
	
	if (form.getPtr() == _master) {
		_master = NULL;
	}
	
	if (form.getPtr() == _detail) {
		_detail = NULL;
	}
}

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\setMasterForm\40\lb_I_DatabaseMasterForm\42\ master\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabasePanel::setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params) {
	
	// Now build the where clause that sets the foreign key columns of this form as equal condition to the values of the masters pk columns.
	
	_master = master;
	_params = params;

	if (masterForm == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, masterForm)
	}
	if (SourceFieldName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	}
	if (SourceFieldValue == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	}
	if (app == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, app)
	}
	if (DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBName)
	}
	if (DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBUser)
	}
	if (DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBPass)
	}

	
	updateFromMaster();
}
/*...e*/
/*...svoid LB_STDCALL lbDatabasePanel\58\\58\setDetailForm\40\lb_I_DatabaseMasterForm\42\ detail\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabasePanel::setDetailForm(lb_I_DatabaseForm* detail, lb_I_Parameter* params) {
	
	// Now build the where clause that sets the foreign key columns of this form as equal condition to the values of the masters pk columns.
	
	_detail = detail;
	_params = params;

	if (detailForm == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, detailForm)
	}
	if (SourceFieldName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	}
	if (SourceFieldValue == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	}
	if (app == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, app)
	}
	if (DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBName)
	}
	if (DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBUser)
	}
	if (DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBPass)
	}

	
	updateFromDetail();
}
/*...e*/

/*...sint LB_STDCALL lbDatabasePanel\58\\58\getControls\40\\41\:0:*/
int LB_STDCALL lbDatabasePanel::getControls() {
	return sampleQuery->getColumns();
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabasePanel\58\\58\getControlValue\40\int pos\41\:0:*/
const char* LB_STDCALL lbDatabasePanel::getControlValue(int pos) {
	UAP(lb_I_String, c)
	c = getColumnName(pos);
	return getControlValue(c->charrep());
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabasePanel\58\\58\getControlValue\40\char\42\ name\41\:0:*/
const char* LB_STDCALL lbDatabasePanel::getControlValue(char* name) {

	wxString value;

	wxWindow* w = FindWindowByName(wxString(name), this);

/*...sGet the content:8:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(name);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
							if (check->GetValue() == TRUE) {
								value = "true";
							} else {
								value = "false";
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							value = tx->GetValue();
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							value = tx->GetValue();
						}
						break;
					
					
					case lb_I_Query::lbDBColumnUnknown:
					
						break;
				}
/*...e*/

	return value.c_str();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\ignoreForeignKeys\40\char\42\ toTable\41\:0:*/
void LB_STDCALL lbDatabasePanel::ignoreForeignKeys(char* toTable) {
	lbErrCodes err = ERR_NONE;
	
	if (ignoredPKTables == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ignoredPKTables)
	}

	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	string->setData(toTable);
	
	QI(string, lb_I_Unknown, uk)
	QI(string, lb_I_KeyBase, key)
	
	ignoredPKTables->insert(&uk, &key);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabasePanel::updateFromMaster() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	_LOG << "lbDatabasePanel::updateFromMaster() called." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newMasterIDQuery)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)
	
	// Using the new = and += operators of the string interface. 
	// Note: If used in an UAP, explizit 'dereferencing' must be used.
	
	*newWhereClause = " where ";

	// Build the query to get the ID from the given *&SourceFieldName
	
	*newMasterIDQuery = "select ";
	
	// Add the primary key names from the table, that are related to *&SourceFieldName

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

/*...sRetrieve parameter values:8:*/
	parameter->setData("DBName");
	_params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	_params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	_params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	_params->getUAPString(*&parameter, *&masterForm);
	parameter->setData("source field");
	_params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source value");
	_params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("application");
	_params->getUAPString(*&parameter, *&app);
	parameter->setData("actionID");
	_params->getUAPLong(*&parameter, *&actionID);
	if (actionID->getData() == -1) {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP_REQUEST(manager.getPtr(), lb_I_String, msg)
		
		*msg = _trans("No action ID has been transferred!");

		meta->msgBox(_trans("Error"), msg->charrep());
	}
/*...e*/

	if (DBUser->charrep() == NULL) {
		_LOG << "Error: No user name for database passed!" LOG_
	} 
	
	if (DBName->charrep() == NULL) {
		_LOG << "Error: No database name for database passed!" LOG_
	}
	
	if (DBPass->charrep() == NULL) {
		_LOG << "Error: No password for database passed!" LOG_
	}

	masterForm->trim();
	SourceFieldName->trim();
	SourceFieldValue->trim();

	_LOG << "Have master form '" << masterForm->charrep() << 
	           "', source field name '" << SourceFieldName->charrep() << 
	           "' and source field value '" << SourceFieldValue->charrep() <<
	           "' for detail form '" << formName << "'" LOG_


/*...sDetermine the primary key values of the current master entry\44\ based on the value of the \42\\38\SourceFieldName\46\:8:*/
	UAP(lb_I_String, colName)
	int columns = _master->getPrimaryColumns();
	
	if (columns == 0) {
		
		if (meta->askYesNo(_trans("Failed to modify result set based on master detail relation. Should I try to fix it."))) {
			/// \todo Fixing code.
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return;
			}
			UAP(lb_I_Query, correctionQuery)
			UAP_REQUEST(manager.getPtr(), lb_I_String, SQL)

			database->init();
			database->connect("lbDMF", "lbDMF", DBUser->charrep(), DBPass->charrep());

			correctionQuery = database->getQuery("lbDMF", 0);
			
			*SQL = "update action_steps set type = (select id from action_types where bezeichnung = 'Open master form' and module = 'lbDatabaseForm') where id = ";
			*SQL += actionID->charrep();
			
			correctionQuery->skipFKCollecting();
			correctionQuery->query(SQL->charrep());
			correctionQuery->enableFKCollecting();
		}

		return;
	}

	bool isChar = _master->isCharacterColumn(SourceFieldName->charrep());
	
	for (int i = 1; i <= columns-1; i++) {
		colName = _master->getPrimaryColumn(i);
		
		*newMasterIDQuery += "\"";
		*newMasterIDQuery += colName->charrep();
		*newMasterIDQuery += "\", \"";
	}

	colName = _master->getPrimaryColumn(columns);
		
	*newMasterIDQuery += "\"";
	*newMasterIDQuery += colName->charrep();
	*newMasterIDQuery += "\"";

	UAP_REQUEST(getModuleInstance(), lb_I_String, tableName)
	
	*tableName = _master->getTableName(SourceFieldName->charrep());
	
	tableName->replace("\"", "");
	
	*newMasterIDQuery += " from \"";	
	*newMasterIDQuery += tableName->charrep();
	*newMasterIDQuery += "\" where \"";
	*newMasterIDQuery += SourceFieldName->charrep();

	if (isChar) 
		*newMasterIDQuery += "\" = '";
	else
		*newMasterIDQuery += "\" = ";
	
	*newMasterIDQuery += SourceFieldValue->charrep();

	if (isChar) *newMasterIDQuery += "'";
/*...e*/
	
	_LOG << "lbDatabasePanel::updateFromMaster() generated new master id query: '" <<
		newMasterIDQuery->charrep() << "'" LOG_

	if (MasterDetailRelationData == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, MasterDetailRelationData)
	} else {
		MasterDetailRelationData->deleteAll();
	}

/*...sRetrieve the values from the primary keys and build up the where clause to be used in detail form:8:*/
	char* dbbackend = meta->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (database == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return;
	}
	UAP(lb_I_Query, PKQuery)

	database->init();
	
	_LOG << "Info: Connect to database." LOG_
	_LOG << "Info: DBName: " << DBName->charrep() LOG_
	_LOG << "Info: DBUser: " << DBUser->charrep() LOG_
	
	
	if (database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		_LOG << "Error: Failed to connect to database." LOG_
		_LOG << "Info: DBName: " << DBName->charrep() LOG_
		_LOG << "Info: DBUser: " << DBUser->charrep() LOG_
	}

	PKQuery = database->getQuery(DBName->charrep(), 0);

	err = PKQuery->query(newMasterIDQuery->charrep());

	UAP(lb_I_String, c)
	if (err == ERR_NONE) {

		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_Long, colValue)

		err = PKQuery->first();

		int columns = PKQuery->getColumns();


		while (err == ERR_NONE) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				c = PKQuery->getColumnName(i);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
				UAP(lb_I_String, tn)
		
				tn = PKQuery->getTableName(colName->charrep());
				fk = sampleQuery->getFKColumn(tn->charrep(), colName->charrep());
		
				if (fk == NULL) {
					_LOG << "Error: could not get foreign column for '" << tn->charrep() << "." << colName->charrep() << "' on newMasterIDQuery '" << newMasterIDQuery->charrep() << "' !" LOG_
					_LOG << "Have master form '" << masterForm->charrep() << 
					           "', source field name '" << SourceFieldName->charrep() << 
					           "' and source field value '" << SourceFieldValue->charrep() <<
		        			   "' for detail form '" << formName << "'" LOG_
					return;
				}
				
				*newWhereClause += fk->charrep();

				wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
				if (w) w->Hide();
				w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
				if (w) w->Hide();

				if (isChar) 
					*newWhereClause += " = '";
				else
					*newWhereClause += " = ";
	
				*newWhereClause += colValue->charrep();
			
				if (isChar) *newWhereClause += "'";
			
				*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue)
				UAP(lb_I_KeyBase, key_fk)
				
				QI(colValue, lb_I_Unknown, uk_colValue)
				QI(fk, lb_I_KeyBase, key_fk)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}

/*...sBuild expression for last column:32:*/
			c = PKQuery->getColumnName(columns);
			*colName = c->charrep();
			colValue = PKQuery->getAsLong(columns);
		
			bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
			UAP(lb_I_String, fk)
			UAP(lb_I_String, tn)
		
			tn = PKQuery->getTableName(colName->charrep());
			fk = sampleQuery->getFKColumn(tn->charrep(), colName->charrep());
		
			if (fk == NULL) {
				_LOG << "Error: could not get foreign column for '" << tn->charrep() << "." << colName->charrep() << "' on newMasterIDQuery '" << newMasterIDQuery->charrep() << "' !" LOG_
				_LOG << "Have master form '" << masterForm->charrep() << 
				           "', source field name '" << SourceFieldName->charrep() << 
				           "' and source field value '" << SourceFieldValue->charrep() <<
	        			   "' for detail form '" << formName << "'" LOG_
				return;
			}

			*newWhereClause += fk->charrep();

			wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
			if (w) w->Hide();
			w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
			if (w) w->Hide();
			
			if (isChar) 
				*newWhereClause += " = '";
			else
				*newWhereClause += " = ";
	
			*newWhereClause += colValue->charrep();
			
			if (isChar) *newWhereClause += "'";

			UAP(lb_I_Unknown, uk_colValue)
			UAP(lb_I_KeyBase, key_fk)
				
			QI(colValue, lb_I_Unknown, uk_colValue)
			QI(fk, lb_I_KeyBase, key_fk)

			MasterDetailRelationData->insert(&uk_colValue, &key_fk);
			_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			
			*newWhereClause += ") ";

			err = PKQuery->next();
			
			if (err != ERR_DB_NODATA) 
				*newWhereClause += " or ";
		}
		
		if (err == WARN_DB_NODATA) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				c = PKQuery->getColumnName(i);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
				UAP(lb_I_String, tn)
		
				tn = PKQuery->getTableName(colName->charrep());
				fk = sampleQuery->getFKColumn(
						tn->charrep(),
						colName->charrep()
						);
		
				if (fk == NULL) {
					_LOG << "Error: could not get foreign column for '" << tn->charrep() << "." << colName->charrep() << "' on newMasterIDQuery '" << newMasterIDQuery->charrep() << "' !" LOG_
					_LOG << "Have master form '" << masterForm->charrep() << 
					           "', source field name '" << SourceFieldName->charrep() << 
					           "' and source field value '" << SourceFieldValue->charrep() <<
		        			   "' for detail form '" << formName << "'" LOG_
					return;
				}
				
				*newWhereClause += fk->charrep();

				wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
				if (w) w->Hide();
				w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
				if (w) w->Hide();

				if (isChar) 
					*newWhereClause += " = '";
				else
					*newWhereClause += " = ";
	
				*newWhereClause += colValue->charrep();
			
				if (isChar) *newWhereClause += "'";
			
				*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue)
				UAP(lb_I_KeyBase, key_fk)
				
				QI(colValue, lb_I_Unknown, uk_colValue)
				QI(fk, lb_I_KeyBase, key_fk)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);
				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}
			
/*...sBuild expression for last column:32:*/
			c = PKQuery->getColumnName(columns);
			*colName = c->charrep();
			colValue = PKQuery->getAsLong(columns);
		
			bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
			UAP(lb_I_String, fk)
			UAP(lb_I_String, tn)
			tn = PKQuery->getTableName(colName->charrep());
			fk = sampleQuery->getFKColumn(
					tn->charrep(),
					colName->charrep()
					);
		
			if (fk == NULL) {
				_LOG << "Error: could not get foreign column for '" << tn->charrep() << "." << colName->charrep() << "' on newMasterIDQuery '" << newMasterIDQuery->charrep() << "' !" LOG_
				_LOG << "Have master form '" << masterForm->charrep() << 
				           "', source field name '" << SourceFieldName->charrep() << 
				           "' and source field value '" << SourceFieldValue->charrep() <<
	        			   "' for detail form '" << formName << "'" LOG_
						   
				*newWhereClause += "'";
				_LOG << "New where clause until yet: '" << newWhereClause->charrep() LOG_
				return;
			}

			*newWhereClause += "\"";
			*newWhereClause += fk->charrep();
			*newWhereClause += "\"";

			wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
			if (w) w->Hide();
			w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
			if (w) w->Hide();

			if (isChar) 
				*newWhereClause += " = '";
			else
				*newWhereClause += " = ";
	
			*newWhereClause += colValue->charrep();
			
			if (isChar) *newWhereClause += "'";

			UAP(lb_I_Unknown, uk_colValue)
			UAP(lb_I_KeyBase, key_fk)
				
			QI(colValue, lb_I_Unknown, uk_colValue)
			QI(fk, lb_I_KeyBase, key_fk)

			MasterDetailRelationData->insert(&uk_colValue, &key_fk);
			_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/

			*newWhereClause += ")";
		}

		Layout();		
		
		
	}
/*...e*/

	// Savely reconnect due to the possibility of connection overriding
	if (database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		_LOG << "Error: Failed to connect to database." LOG_
		_LOG << "Info: DBName: " << DBName->charrep() LOG_
		_LOG << "Info: DBUser: " << DBUser->charrep() LOG_
	}

	sampleQuery = database->getQuery(DBName->charrep(), 0);

	_LOG << "Create a new query based on query: " << getQuery() << " and where clause: " << newWhereClause->charrep() LOG_
	
	setFilter(newWhereClause->charrep());
	*newQuery = sampleQuery->setWhereClause(getQuery(), newWhereClause->charrep());

	_LOG << "Have created new query: '" << newQuery->charrep() << "'" LOG_ 
	_LOG << " ... On database '" << DBName->charrep() << "', with user" LOG_ 
	_LOG << " ... '" << DBUser->charrep() << "'" LOG_

	err = sampleQuery->query(newQuery->charrep());
	
	if (err != ERR_NONE) {
			_CL_LOG << "Error: Failed to get data for detail form." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton->Disable();
			prevButton->Disable();
			lastButton->Disable();
			nextButton->Disable();
			deleteButton->Disable();
			deactivateActionButtons();
			noDataAvailable = false;	
	} else {
		err = sampleQuery->first();

		if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
			_CL_LOG << "Error: Failed to get data for detail form (after moving to first)." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton->Disable();
			prevButton->Disable();
			lastButton->Disable();
			nextButton->Disable();
			deleteButton->Disable();
			deactivateActionButtons();
			noDataAvailable = false;	
		} else {
			lbDBRead();
			lastButton->Enable();
			nextButton->Enable();
			activateActionButtons();
			deleteButton->Enable();
		}
	}
	
	SetName(formName);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\updateFromDetail\40\\41\:0:*/
void LB_STDCALL lbDatabasePanel::updateFromDetail() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newMasterIDQuery)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)

	_LOG << "lbDatabasePanel::updateFromDetail() called." LOG_


	// Using the new = and += operators of the string interface. 
	// Note: If used in an UAP, explizit 'dereferencing' must be used.
	
	*newWhereClause = " where "; // 'primary keys' = <foreign values>

	// Build the query to get the ID from the given *&SourceFieldName
	
	*newMasterIDQuery = "select "; // 'Foreign keys' from detail table where detail id = 
	
	// Add the primary key names from the table, that are related to *&SourceFieldName

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

/*...sRetrieve parameter values:8:*/
	parameter->setData("DBName");
	_params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	_params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	_params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	_params->getUAPString(*&parameter, *&detailForm);
	parameter->setData("source field");
	_params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source value");
	_params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("application");
	_params->getUAPString(*&parameter, *&app);
	parameter->setData("actionID");
	_params->getUAPLong(*&parameter, *&actionID);
	if (actionID->charrep() == NULL) {
		meta->msgBox(_trans("Error"), _trans("No action ID has been transferred!"));
	}
/*...e*/

	detailForm->trim();
	SourceFieldName->trim();
	SourceFieldValue->trim();

	_LOG << "Have detail form '" << detailForm->charrep() << 
	           "', source field name '" << SourceFieldName->charrep() << 
	           "' and source field value '" << SourceFieldValue->charrep() <<
	           "' for master form '" << formName << "'" LOG_


/*...sDetermine the foreign key values of the current detail entry\44\ based on the value of the \42\\38\SourceFieldName\46\:8:*/
	UAP(lb_I_String, colName)
	int columns = _detail->getForeignColumns();
	
	if (columns == 0) {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		
		if (meta->askYesNo(_trans("Failed to modify result set based on master detail relation. Should I try to fix it."))) {
			/// \todo Fixing code.
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return;
			}
			UAP(lb_I_Query, correctionQuery)
			UAP_REQUEST(manager.getPtr(), lb_I_String, SQL)

			database->init();
			database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());

			correctionQuery = database->getQuery(DBName->charrep(), 0);
			
			*SQL = "update action_steps set type = (select id from action_types where bezeichnung = 'Open detail form' and module = 'lbDatabaseForm') where id = ";
			*SQL += actionID->charrep();
			
			correctionQuery->skipFKCollecting();
			correctionQuery->query(SQL->charrep());
			correctionQuery->enableFKCollecting();
		}

		return;
	}
	
	bool isChar = _detail->isCharacterColumn(SourceFieldName->charrep());
	
	UAP(lb_I_String, sourceTable)
	sourceTable = _detail->getTableName(SourceFieldName->charrep());
	
	UAP(lb_I_String, tn)
	for (int i = 1; i <= columns-1; i++) {
		colName = _detail->getForeignColumn(i);
		tn = _detail->getTableName(colName->charrep());

		_CL_LOG << "lbDatabasePanel::updateFromDetail() creates query column '" << colName->charrep() << "'" LOG_
		
		if (strcmp(sourceTable->charrep(), tn->charrep()) == 0) {
			*newMasterIDQuery += colName->charrep();
			*newMasterIDQuery += ", ";
		}
	}

	colName = _detail->getForeignColumn(columns);
		
	_CL_LOG << "lbDatabasePanel::updateFromDetail() creates query column '" << colName->charrep() << "'" LOG_
	tn = _detail->getTableName(colName->charrep());
	if (strcmp(sourceTable->charrep(), tn->charrep()) == 0) {
		*newMasterIDQuery += colName->charrep();
	}

	tn = _detail->getTableName(SourceFieldName->charrep());
	*newMasterIDQuery += " from \"";
	*newMasterIDQuery += tn->charrep();
	*newMasterIDQuery += "\" where \"";
	*newMasterIDQuery += SourceFieldName->charrep();
	*newMasterIDQuery += "\"";

	if (isChar) 
		*newMasterIDQuery += " = '";
	else
		*newMasterIDQuery += " = ";
	
	*newMasterIDQuery += SourceFieldValue->charrep();

	if (isChar) *newMasterIDQuery += "'";
/*...e*/
	
	_LOG << "lbDatabasePanel::updateFromDetail() generated new master id query: \n'" <<
		newMasterIDQuery->charrep() << "'" LOG_

	if (MasterDetailRelationData == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, MasterDetailRelationData)
	} else {
		MasterDetailRelationData->deleteAll();
	}

/*...sRetrieve the values from the primary keys and build up the where clause to be used in detail form:8:*/
	char* dbbackend = meta->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (database == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return;
	}
	UAP(lb_I_Query, PKQuery)
	UAP(lb_I_Query, sourceTableQuery)

	database->init();
	database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());

	PKQuery = database->getQuery(DBName->charrep(), 0);
	sourceTableQuery = database->getQuery(DBName->charrep(), 0);

	err = PKQuery->query(newMasterIDQuery->charrep());

	UAP_REQUEST(getModuleInstance(), lb_I_String, st)

	UAP(lb_I_String, c)
	_LOG << "Try to get table name for old query: " << getQuery() LOG_
	if (sourceTableQuery->query(getQuery()) != ERR_NONE) {
		*st = "Unknown table";
		meta->setStatusText("Info", "Error: Could not get table name of target formular!");
	} else {
		c = sourceTableQuery->getColumnName(1);
		*st = sourceTableQuery->getTableName(c->charrep());
	}

	if (err == ERR_NONE) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_Long, colValue)

		err = PKQuery->first();

		int columns = PKQuery->getColumns();


		while (err == ERR_NONE) {
			int subClause = 0;
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				c = PKQuery->getColumnName(i);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
				UAP(lb_I_String, pt)
		
				pt = PKQuery->getPKTable(colName->charrep());
				
				_LOG << "Compare strings '" << pt->charrep() << "' == '" << st->charrep() << "'." LOG_
				
				if (*pt == *&st) {
					if (subClause == 0) {
						subClause++;
					} else {
						*newWhereClause += " and ";
						subClause++;				
					}
				
					fk = PKQuery->getPKColumn(colName->charrep());
					*newWhereClause += fk->charrep();

					wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
					if (w) w->Hide();
					w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
					if (w) w->Hide();

					if (isChar) 
						*newWhereClause += " = '";
					else
						*newWhereClause += " = ";
	
					*newWhereClause += colValue->charrep();
			
					if (isChar) *newWhereClause += "'";
			
					UAP(lb_I_Unknown, uk_colValue)
					UAP(lb_I_KeyBase, key_fk)
				
					QI(colValue, lb_I_Unknown, uk_colValue)
					QI(fk, lb_I_KeyBase, key_fk)

					MasterDetailRelationData->insert(&uk_colValue, &key_fk);

					_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
				}
/*...e*/
			}

/*...sBuild expression for one column:32:*/
				c = PKQuery->getColumnName(columns);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(columns);
		
				bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
		
				UAP(lb_I_String, pt)
				
				pt = PKQuery->getPKTable(colName->charrep());
				
				_LOG << "Compare strings '" << pt->charrep() << "' == '" << st->charrep() << "'." LOG_

				if (*pt == *&st) {
					if (subClause == 0) {
						subClause++;
					} else {
						*newWhereClause += " and ";
						subClause++;				
					}

					fk = PKQuery->getPKColumn(colName->charrep());
					*newWhereClause += fk->charrep();

					wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
					if (w) w->Hide();
					w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
					if (w) w->Hide();

					if (isChar) 
						*newWhereClause += " = '";
					else
						*newWhereClause += " = ";
	
					*newWhereClause += colValue->charrep();
			
					if (isChar) *newWhereClause += "'";
			
					UAP(lb_I_Unknown, uk_colValue)
					UAP(lb_I_KeyBase, key_fk)
				
					QI(colValue, lb_I_Unknown, uk_colValue)
					QI(fk, lb_I_KeyBase, key_fk)

					MasterDetailRelationData->insert(&uk_colValue, &key_fk);

					_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
				}
/*...e*/
			
			*newWhereClause += ") ";
			
			err = PKQuery->next();
			
			if (err != ERR_DB_NODATA) 
				*newWhereClause += " or ";
		}
		
		if (err == WARN_DB_NODATA) {
			int subClause = 0;
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				c = PKQuery->getColumnName(i);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
				UAP(lb_I_String, pt)
				
				pt = PKQuery->getPKTable(colName->charrep());
				
				_LOG << "Compare strings '" << pt->charrep() << "' == '" << st->charrep() << "'." LOG_

				if (*pt == *&st) {
					if (subClause == 0) {
						subClause++;
					} else {
						*newWhereClause += " and ";
						subClause++;				
					}
					fk = PKQuery->getPKColumn(colName->charrep());
					*newWhereClause += fk->charrep();

					wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
					if (w) w->Hide();
					w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
					if (w) w->Hide();

					if (isChar) 
						*newWhereClause += " = '";
					else
						*newWhereClause += " = ";
	
					*newWhereClause += colValue->charrep();
			
					if (isChar) *newWhereClause += "'";
			
					UAP(lb_I_Unknown, uk_colValue)
					UAP(lb_I_KeyBase, key_fk)
				
					QI(colValue, lb_I_Unknown, uk_colValue)
					QI(fk, lb_I_KeyBase, key_fk)

					MasterDetailRelationData->insert(&uk_colValue, &key_fk);

					_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
				}
/*...e*/
			}
			
/*...sBuild expression for one column:32:*/
				c = PKQuery->getColumnName(columns);
				*colName = c->charrep();
				colValue = PKQuery->getAsLong(columns);
		
				bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk)
				UAP(lb_I_String, pt)
				
				pt = PKQuery->getPKTable(colName->charrep());
				
				_LOG << "Compare strings '" << pt->charrep() << "' == '" << st->charrep() << "'." LOG_

				if (*pt == *&st) {
					if (subClause == 0) {
						subClause++;
					} else {
						*newWhereClause += " and ";
						subClause++;				
					}

					fk = PKQuery->getPKColumn(colName->charrep());
					*newWhereClause += fk->charrep();

					wxWindow* w = FindWindowByName(wxString(fk->charrep()), this);
					if (w) w->Hide();
					w = FindWindowByName(wxString(fk->charrep())+wxString("_lbl"), this);
					if (w) w->Hide();

					if (isChar) 
						*newWhereClause += " = '";
					else
						*newWhereClause += " = ";
	
					*newWhereClause += colValue->charrep();
			
					if (isChar) *newWhereClause += "'";
			
					UAP(lb_I_Unknown, uk_colValue)
					UAP(lb_I_KeyBase, key_fk)
				
					QI(colValue, lb_I_Unknown, uk_colValue)
					QI(fk, lb_I_KeyBase, key_fk)

					MasterDetailRelationData->insert(&uk_colValue, &key_fk);

					_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
				}
/*...e*/

			*newWhereClause += ")";
		}

		Layout();		

		
	}
/*...e*/


	newQuery->setData(getQuery());
	
	setFilter(newWhereClause->charrep());

	*newQuery = sampleQuery->setWhereClause(getQuery(), newWhereClause->charrep());
	
	_LOG << "Have new query for detail form: '" << newQuery->charrep() << "'" LOG_
	
	sampleQuery = database->getQuery(DBName->charrep(), 0);

	err = sampleQuery->query(newQuery->charrep());
	
	if (err != ERR_NONE) {
			_CL_LOG << "Error: Failed to get data for master form." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton->Disable();
			prevButton->Disable();
			lastButton->Disable();
			nextButton->Disable();
			deleteButton->Disable();
			deactivateActionButtons();
			noDataAvailable = false;	
	} else {
		err = sampleQuery->first();

		if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
			_CL_LOG << "Error: Failed to get data for master form (after moving to first)." LOG_
			noDataAvailable = true;
			lbDBClear();
			firstButton->Disable();
			prevButton->Disable();
			lastButton->Disable();
			nextButton->Disable();
			deleteButton->Disable();
			deactivateActionButtons();
			noDataAvailable = false;	
		} else {
			lbDBRead();
			lastButton->Enable();
			nextButton->Enable();
			activateActionButtons();
			deleteButton->Enable();
		}
	}
	
	SetName(formName);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabasePanel::setFilter(char* filter) {
	if (filter != NULL) SQLWhere->setData(filter);
}
/*...e*/

/*...schar\42\ lbDatabasePanel\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
lb_I_String* lbDatabasePanel::getTableName(char* columnName) {
	return sampleQuery->getTableName(columnName);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBClear() {
	int columns = sampleQuery->getColumns();

	for (int i = 1; i <= columns; i++) {
		UAP(lb_I_String, name)
		name = sampleQuery->getColumnName(i);

		wxWindow* w = FindWindowByName(wxString(name->charrep()), this);

		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name->charrep()) == 1) {
/*...sUpdate drop down box:32:*/
				wxChoice* cbox = (wxChoice*) w;
				if (sampleQuery->isAdding() == 1)
					if (cbox->IsEnabled()) sampleQuery->setNull(name->charrep());
				cbox->SetSelection(-1);
/*...e*/
			} else {
				if (FFI->isSpecialColumn(name->charrep())) {
				} else {
/*...sUpdate controls:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
							
							check->SetValue(false);
						}
						break;
					

					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							tx->SetValue(wxString(""));
						}
						break;
			
					case lb_I_Query::lbDBColumnDate:
						{
							wxDatePickerCtrl* tx = (wxDatePickerCtrl*) w;
							wxDateTime dt = wxDateTime::Now();
			
							tx->SetValue(dt);
						}
						break;
			
					case lb_I_Query::lbDBColumnBigInteger:		
					case lb_I_Query::lbDBColumnInteger:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							tx->SetValue(wxString(""));
						}
						break;
					case lb_I_Query::lbDBColumnBinary:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
						
							tx->SetValue(wxString(""));
						}
						break;
					case lb_I_Query::lbDBColumnUnknown:
						break;
				}

				
/*...e*/
				}
			}
		} else {
			_CL_VERBOSE << "Control '" << name->charrep() << "' nicht gefunden." LOG_
		}
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBUpdate() {
	//if (noDataAvailable) return ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	if (!database->isConnected()) {
		sampleQuery = database->getQuery(_DBName->charrep(), 0);

		sampleQuery->enableFKCollecting();
		sampleQuery->query(SQLString->charrep(), true);
		sampleQuery->setAutoRefresh(meta->getAutorefreshData());
	}
	
	SetName(formName);

	int columns = sampleQuery->getColumns();
	
	for (int i = 1; i <= columns; i++) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, col)
		UAP_REQUEST(manager.getPtr(), lb_I_String, val)
		UAP(lb_I_String, name)
		name = sampleQuery->getColumnName(i);

		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name->charrep()), this);

		if (w != NULL) {
		
			if (sampleQuery->hasFKColumn(name->charrep()) == 1) {
/*...sUpdate drop down box:32:*/
				wxChoice* cbox = (wxChoice*) w;
				
				int pos = cbox->GetSelection();
				
				if (pos != -1) {
					lbErrCodes err = ERR_NONE;

					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
					cbName->setData(name->charrep());
					
					UAP(lb_I_KeyBase, key_cbName)
					UAP(lb_I_Unknown, uk_cbMapper)
					UAP(lb_I_Container, cbMapper)
					
					QI(cbName, lb_I_KeyBase, key_cbName)
					
					uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);
					
					if (uk_cbMapper == NULL) {
						_LOG << "Error: Could not find mapping container for '" << name->charrep() << "'. Key was '" << key_cbName->charrep() << "'. List of elements:" LOG_
						
						ComboboxMapperList->finishIteration();
						
						while (ComboboxMapperList->hasMoreElements() == 1) {
							UAP(lb_I_Unknown, uk)
							UAP(lb_I_KeyBase, key)
							uk = ComboboxMapperList->nextElement();
							key = ComboboxMapperList->currentKey();
							_LOG << "Element '" << key->charrep() << "'." LOG_
						}
					} else {
						QI(uk_cbMapper, lb_I_Container, cbMapper)
						
						key->setData(pos);
						
						UAP(lb_I_KeyBase, key_pos)
						
						QI(key, lb_I_KeyBase, key_pos)
						
						UAP(lb_I_Unknown, uk_mapping)
						
						uk_mapping = cbMapper->getElement(&key_pos);
						
						if (uk_mapping == NULL)  { 
							if (!sampleQuery->isNullable(name->charrep())) {
								if (!meta->askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
							}
						} else {
							UAP(lb_I_Integer, FK_id)
							
							QI(uk_mapping, lb_I_Long, FK_id)
							
							col->setData(name->charrep());
							val->setData(FK_id->charrep());
							
							sampleQuery->setNull(name->charrep(), false);
							sampleQuery->setString(*&col, *&val);
						}
					}
				} else {
					if (!sampleQuery->isNullable(name->charrep())) {
						if (!meta->askYesNo(_trans("Failed to save data. Not all fields are filled."))) return ERR_UPDATE_FAILED;
					}
				}
/*...e*/
			} else {
				if (FFI->isSpecialColumn(name->charrep())) {
					_CL_LOG << "lbDatabasePanel::lbDBUpdate() updates special column" LOG_
					lbErrCodes err = ERR_NONE;
					
					char* type = FFI->getControlType(name->charrep());

					if (strcmp(type, "toolbarimagefile") == 0) {
						UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
						UAP_REQUEST(manager.getPtr(), lb_I_String, controlname)
						*controlname = name->charrep();
						UAP(lb_I_KeyBase, key)
						QI(controlname, lb_I_KeyBase, key)
						
						UAP(lb_I_Unknown, uk)
						
						uk = ImageButtonMapperList->getElement(&key);
						QI(uk, lb_I_String, filename)
						
						sampleQuery->setString(*&controlname, *&filename);
					}
				} else {
/*...sUpdate controls:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							if (!sampleQuery->getReadonly(name->charrep())) {
								wxCheckBox *check = (wxCheckBox*) w;
								if (check->GetValue() == TRUE) {
									wxString v = "true";
									col->setData(name->charrep());
									val->setData(v.c_str());
							
									sampleQuery->setString(*&col, *&val);
								} else {
									wxString v = "false";
									col->setData(name->charrep());
									val->setData(v.c_str());
								
									sampleQuery->setString(*&col, *&val);
								}
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnFloat:
					case lb_I_Query::lbDBColumnChar:
						{
							if (!sampleQuery->getReadonly(name->charrep())) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name->charrep());
								val->setData(v.c_str());

								sampleQuery->setString(*&col, *&val);
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnDate:
						{
							if (!sampleQuery->getReadonly(name->charrep())) {
								wxDatePickerCtrl* tx = (wxDatePickerCtrl*) w;
			
								wxDateTime v = tx->GetValue();
			
								col->setData(name->charrep());
								val->setData(v.FormatISODate().c_str());

								sampleQuery->setString(*&col, *&val);
								_LOG << "lbDatabasePanel::lbDBUpdate() sets date column value to '" << val->charrep() << "'" LOG_
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnBigInteger:
					case lb_I_Query::lbDBColumnInteger:
						{
							if (!sampleQuery->getReadonly(name->charrep())) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name->charrep());
								val->setData(v.c_str());

								sampleQuery->setString(*&col, *&val);
							}
						}
						break;
					case lb_I_Query::lbDBColumnBinary:
						{
							if (!sampleQuery->getReadonly(name->charrep())) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name->charrep());

								UAP_REQUEST(getModuleInstance(), lb_I_BinaryData, binary)
								
								if (v.Length() > 0) { 
									int len = v.Length()+1;
									void* buffer = malloc(len);
									memcpy(buffer, v.c_str(), len);
									binary->setData(buffer, len);
									free(buffer);
									sampleQuery->setBinaryData(col->charrep(), *&binary);
								}
							}
						}
						break;
					
					
					case lb_I_Query::lbDBColumnUnknown:
					
						break;
				}

				
/*...e*/
				}
			}
		} else {
			_LOG << "Control '" << name->charrep() << "' nicht gefunden." LOG_
		}
	}

	if (sampleQuery->update() != ERR_NONE) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

		newTitle->setData(formName);
		
		*newTitle += ": Update failed !";

		SetName(newTitle->charrep());

		if (meta->askYesNo("Error while updating data. Would you re - read the current data and retry ?")) {
			sampleQuery->reopen();
			lbDBRead();
		}
		
		_LOG << "Update a database record failed." LOG_

		return ERR_UPDATE_FAILED;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBRead() {

	SetName(formName);

	int columns = sampleQuery->getColumns();
	
	for (int i = 1; i <= columns; i++) {
		UAP(lb_I_String, name)
		name = sampleQuery->getColumnName(i);
		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name->charrep()), this);
		
		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name->charrep()) == 1) {
/*...sfill combo box with data:32:*/
				wxChoice* cbox = (wxChoice*) w;
				
				lbErrCodes err = ERR_NONE;

				UAP_REQUEST(manager.getPtr(), lb_I_Long, key)
				UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)

				cbName->setData(name->charrep());

				UAP(lb_I_KeyBase, key_cbName)
				UAP(lb_I_Unknown, uk_cbMapper)
				UAP(lb_I_Container, cbMapper)

				QI(cbName, lb_I_KeyBase, key_cbName)

				uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);

				QI(uk_cbMapper, lb_I_Container, cbMapper)
				
				int count = cbMapper->Count();
				
				if (count != 0) {
					char *newFK = NULL;
					UAP(lb_I_Long, l)

					key = sampleQuery->getAsLong(i);
	
					UAP(lb_I_KeyBase, key_FK_id)
				
					QI(key, lb_I_KeyBase, key_FK_id)
				
					UAP(lb_I_Unknown, uk_cbBoxPosition)
					UAP(lb_I_Integer, cbBoxPosition)
				
					int cbPos = 0;
				
					while (cbMapper->hasMoreElements() == 1) {
						UAP(lb_I_Integer, sel)
					        UAP(lb_I_Unknown, e)
					        e = cbMapper->nextElement();
					        QI(e, lb_I_Long, sel)
				        
					        if (sel->equals(*&key)) {
					        	cbox->SetSelection(cbPos);
					        }
					        cbPos++;
					}
				}
/*...e*/
			} else {
				if (FFI->isSpecialColumn(name->charrep())) {
					lbErrCodes err = ERR_NONE;
					char* type = FFI->getControlType(name->charrep());
					
					if (strcmp(type, "toolbarimagefile") == 0) {
						UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
						UAP_REQUEST(manager.getPtr(), lb_I_String, controlname)
						UAP_REQUEST(manager.getPtr(), lb_I_String, toolbarfile)
						UAP_REQUEST(manager.getPtr(), lb_I_String, images)

						*controlname = name->charrep();
						UAP(lb_I_KeyBase, key)
						QI(controlname, lb_I_KeyBase, key)
						
						UAP(lb_I_Unknown, uk)
						
						uk = ImageButtonMapperList->getElement(&key);
						QI(uk, lb_I_String, filename)
						
						UAP(lb_I_String, s)
							
						s = sampleQuery->getAsString(i);

						if (strcmp(s->charrep(), "") == 0) {
						} else {
							UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
							*toolbarfile += app->getDirLocation();

#ifdef OSX
							*images = "/toolbarimages/";
#endif
#ifdef LINUX
							*images = "/toolbarimages/";
#endif
#ifdef WINDOWS
							*images = "\\toolbarimages\\";
#endif
							*toolbarfile += images->charrep();
							*toolbarfile += s->charrep();

							if (!wxFile::Exists(toolbarfile->charrep())) {
								// Fallback
					#ifdef OSX
					#endif
					#ifdef LINUX
								*toolbarfile = "/usr/share/lbdmf";			
								*toolbarfile += images->charrep();
								*toolbarfile += s->charrep();
					#endif
					#ifdef WINDOWS
					#endif			    
							}

							*filename = s->charrep();
							
							wxString f = wxString(s->charrep());
							
							wxImage* im;
							
							_LOG << "Assign a file to an image button: " << toolbarfile->charrep() LOG_
							
							if (f.Upper().Contains(".XPM") == 1) {
								im = new wxImage(toolbarfile->charrep(), wxBITMAP_TYPE_XPM);
							}

							if (f.Upper().Contains(".PNG") == 1) {
								im = new wxImage(toolbarfile->charrep(), wxBITMAP_TYPE_PNG);
							}
							
							wxBitmap bm = wxBitmap(*im);
							wxBitmapButton* bmb = (wxBitmapButton*) w;
							bmb->SetBitmapLabel(bm);
							bmb->Refresh();
						}
					}
				} else {
/*...sfill controls with data:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
#ifndef OSX	
							if (sampleQuery->isNull(i)) {
								check->SetValue(false);
							} else {
#endif
								UAP(lb_I_String, s)
								
								s = sampleQuery->getAsString(i);
								
								if ((strcmp(s->charrep(), "true") == 0) || (strcmp(s->charrep(), "1") == 0)) {
									check->SetValue(true);
								} else {
									check->SetValue(false);
								}
#ifndef OSX
							}
#endif
						}
						break;
					
					case lb_I_Query::lbDBColumnFloat:
					case lb_I_Query::lbDBColumnChar:
						{
							UAP(lb_I_String, s)
							
							s = sampleQuery->getAsString(i);
							
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(s->charrep()));
						}
						break;
					case lb_I_Query::lbDBColumnDate:
						{
							UAP(lb_I_String, s)
							
							s = sampleQuery->getAsString(i);
							
							wxDatePickerCtrl* tx = (wxDatePickerCtrl*) w;
							
							wxDateTime dt;
							dt.ParseDate(wxString(s->charrep()));

							tx->SetValue(dt);
						}
						break;
					
					case lb_I_Query::lbDBColumnBigInteger:
					case lb_I_Query::lbDBColumnInteger:
						{
							UAP(lb_I_String, s)
							
							s = sampleQuery->getAsString(i);
							
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(s->charrep()));
						}
						break;
					case lb_I_Query::lbDBColumnBinary:
						{
							UAP(lb_I_BinaryData, binary)
							
							binary = sampleQuery->getBinaryData(i);
							binary->append((void*) "\0", 1);
							
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString((char*) binary->getData()));
						}
						break;
					case lb_I_Query::lbDBColumnUnknown:
						break;
				}

/*...e*/
				}
			}
		} else {
			_CL_VERBOSE << "Control '" << name->charrep() << "' nicht gefunden." LOG_
		}
	}
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBFirst(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbDBClear();

	err = sampleQuery->first();

	while (err == ERR_DB_ROWDELETED) err = sampleQuery->next();

	if (err == ERR_DB_NODATA) {
		sampleQuery->reopen();
		
		err = sampleQuery->first();
		
		if (err == ERR_DB_NODATA) {
			DISABLE_FOR_NO_DATA()

			return ERR_DB_NODATA;
		} else {
			DISABLE_BOF()
		}
	}

	lbDBRead();
	
	DISABLE_BOF()

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBNext(lb_I_Unknown* uk) {
	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbErrCodes err = sampleQuery->next();

	// Skip all deleted rows
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->next();
	
	if (err == WARN_DB_NODATA) {
		nextButton->Disable();
		lastButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
		sampleQuery->reopen();
		
		err = sampleQuery->last();
		
		if (err == ERR_DB_NODATA) {
			prevButton->Disable();
			firstButton->Disable();
			return ERR_DB_NODATA;
		} else {
			DISABLE_EOF()
		}
		
	} else {
		prevButton->Enable();
		firstButton->Enable();
		deleteButton->Enable();
	
		lbDBClear();
	}
		
	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBPrev(lb_I_Unknown* uk) {
	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;

	lbErrCodes err = sampleQuery->previous();

	// Skip all deleted rows
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->previous();

	if (err == WARN_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
	
		sampleQuery->reopen();
		err = sampleQuery->first();
		
		if (err == ERR_DB_NODATA) {
			nextButton->Disable();
			lastButton->Disable();
			return ERR_DB_NODATA;
		} else {
			DISABLE_BOF()
		}
	} else {
		nextButton->Enable();
		lastButton->Enable();
		deleteButton->Enable();

		lbDBClear();
	}

	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBLast(lb_I_Unknown* uk) {
	if (lbDBUpdate() != ERR_NONE) return ERR_UPDATE_FAILED;
	lbDBClear();

	lbErrCodes err = sampleQuery->last();
	
	while (err == ERR_DB_ROWDELETED) err = sampleQuery->previous();

	if (err == ERR_DB_NODATA) {
		sampleQuery->reopen();
		err = sampleQuery->last();
	
		if (err == ERR_DB_NODATA) {
			DISABLE_FOR_NO_DATA()

			return ERR_DB_NODATA;
		}
	}

	lbDBRead();

	DISABLE_EOF()

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbDatabasePanel::lbDBRefresh(lb_I_Unknown* uk) {
	close();
	
	open();
	
	return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBAdd(lb_I_Unknown* uk) {
	lbErrCodes errUpdate = ERR_NONE;
	_CL_LOG << "lbDatabasePanel::lbDBAdd() called. Have query: " << getQuery() LOG_
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	if (sampleQuery->isAdding() == 0) {
		if (sampleQuery->dataFetched()) errUpdate = lbDBUpdate();

		if (sampleQuery->add() != ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

			newTitle->setData(formName);
		
			*newTitle += ": Add failed !";
			
			_LOG << newTitle->charrep() LOG_

			SetName(_trans(newTitle->charrep()));
		} else {
			// Delete fields and set foreign key columns to NULL
			
			if (sampleQuery->dataFetched()) lbDBClear(); // Clear fields and two step mode
			errUpdate = ERR_NONE;
		}
	} else {
		_CL_LOG << "Query is in add mode." LOG_
	}
	
	char* foreignkey = NULL;
	char* foreignkey_value = NULL;
	
/*...sPrefill data to hidden fields\46\ This would mostly be combo boxes\46\:8:*/
	if (MasterDetailRelationData != NULL) {
	
		_CL_LOG << "Have " << MasterDetailRelationData->Count() << " elements in list." LOG_
	
		for (int i = 1; i <= MasterDetailRelationData->Count(); i++) {
			lbErrCodes err = ERR_NONE;
		
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_KeyBase, key)
			
			UAP(lb_I_Long, value)
			
			uk = MasterDetailRelationData->getElementAt(i);
			key = MasterDetailRelationData->getKeyAt(i);
			
			
			QI(uk, lb_I_Long, value)
			
			_LOG << "Set control '" << key->charrep() << "' with ref = " << key->getRefCount() << " to '" << value->charrep() << "'" LOG_

			foreignkey = strdup(key->charrep());
			foreignkey_value = strdup(value->charrep());

			
			wxWindow* w = FindWindowByName(wxString(key->charrep()), this);
		
			if (w != NULL) {
				if (sampleQuery->hasFKColumn(key->charrep()) == 1) {
					_LOG << "lbDatabasePanel::lbDBAdd() Set dropdown control '" << 
					key->charrep() << 
					"' to '" << 
					value->charrep() << "'" LOG_
					/*...sfill combo box with data:48:*/
					wxChoice* cbox = (wxChoice*) w;
					
					lbErrCodes err = ERR_NONE;
					
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key1)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
					cbName->setData(key->charrep());
					
					UAP(lb_I_KeyBase, key_cbName)
					UAP(lb_I_Unknown, uk_cbMapper)
					UAP(lb_I_Container, cbMapper)
					
					QI(cbName, lb_I_KeyBase, key_cbName)
					
					uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);
					
					QI(uk_cbMapper, lb_I_Container, cbMapper)
					
					int count = cbMapper->Count();
					
					if (count != 0) {
						key1->setData(value->getData());
						UAP(lb_I_KeyBase, key_FK_id)
						QI(key1, lb_I_KeyBase, key_FK_id)
						
						UAP(lb_I_Unknown, uk_cbBoxPosition)
						UAP(lb_I_Integer, cbBoxPosition)
						
						int cbPos = 0;
						bool selected = false;
						
						cbMapper->finishIteration();
						while (cbMapper->hasMoreElements() == 1) {
							UAP(lb_I_Integer, sel)
					        UAP(lb_I_Unknown, e)
					        e = cbMapper->nextElement();
					        QI(e, lb_I_Long, sel)
							
					        if (sel->equals(*&key_FK_id)) {
					        	selected = true;
					        	cbox->SetSelection(cbPos);
					        }
					        cbPos++;
						}
						
						if (!selected) {
							_LOG << "Error: Dropdown control couldn't correctly set." LOG_
						}
					} else {
						_LOG << "lbDatabasePanel::lbDBAdd() Error: Have no combobox mapper values." LOG_
					}
					/*...e*/
				} else {
					if (FFI->isSpecialColumn(key->charrep())) {
						_CL_VERBOSE << "Set special control '" << 
							key->charrep() << 
							"' to '" << 
							value->charrep() << "'" LOG_
					} else {
						_CL_VERBOSE << "Set text control '" << 
							key->charrep() << 
							"' to '" << 
							value->charrep() << "'" LOG_
					#ifdef bla
/*...sfill controls with data:56:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
#ifndef OSX	
							if (sampleQuery->isNull(i)) {
								check->SetValue(false);
							} else {
#endif
								if (strcmp(sampleQuery->getAsString(i)->charrep(), "true") == 0) {
									check->SetValue(true);
								} else {
									check->SetValue(false);
								}
#ifndef OSX
							}
#endif
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(sampleQuery->getAsString(i)->charrep()));
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(sampleQuery->getAsString(i)->charrep()));
						}
						break;
					case lb_I_Query::lbDBColumnUnknown:
						_CL_LOG << "Error: Setting hidden control of unknown type'" << key->charrep() << "'." LOG_
						break;
				}

/*...e*/
					#endif
					}
				}
			} else {
				_CL_LOG << "Control '" << key->charrep() << "' not found." LOG_
			}
		}
	}
/*...e*/

	// Instead of deleting fields on no data do the add operation in one step.
	if (!sampleQuery->dataFetched()) {
		lbDBUpdate();
		sampleQuery->reopen();
		sampleQuery->first();
		lbDBRead();
		DISABLE_FOR_ONE_DATA()
		return ERR_NONE;
	}
	
	_CL_LOG << "Determine update failed..." LOG_

	if (errUpdate == ERR_UPDATE_FAILED) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
		_CL_LOG << "Updating after add failed." LOG_
		
		newTitle->setData(formName);
		
		*newTitle += ": Missing fields !";
		
		_LOG << newTitle->charrep() LOG_
		
		SetName(_trans(newTitle->charrep()));
	} else {
		_CL_LOG << "Updating after add succeeded. Move to last." LOG_
		
		if (allNaviDisabled == true) {
			lbDBFirst(NULL);
			lbDBClear();
		} else {
			if (sampleQuery->dataFetched()) {
				if (foreignkey != NULL) {
					if (sampleQuery->isNull(foreignkey)) {
						_CL_LOG << "Column for foreignkey binding is set to NULL. -- Wrong" LOG_
						UAP_REQUEST(manager.getPtr(), lb_I_String, col)
						UAP_REQUEST(manager.getPtr(), lb_I_String, val)
						
						*col = foreignkey;
						*val = foreignkey_value;
						
						sampleQuery->setString(*&col, *&val);
					} else {
						_CL_LOG << "Column for foreignkey binding is not set to NULL." LOG_				
					}
				}
				if (lbDBLast(NULL) != ERR_NONE) {
					_CL_LOG << "Move to last after updating failed." LOG_
					lbDBFirst(NULL);
				} else {
					lbDBClear();
				}
			} else {
				if (foreignkey != NULL) {
					if (sampleQuery->isNull(foreignkey)) {
						_CL_LOG << "Column for foreignkey binding is set to NULL. -- Wrong" LOG_
						UAP_REQUEST(manager.getPtr(), lb_I_String, col)
						UAP_REQUEST(manager.getPtr(), lb_I_String, val)
						
						*col = foreignkey;
						*val = foreignkey_value;
						
						sampleQuery->setString(*&col, *&val);
					} else {
						_CL_LOG << "Column for foreignkey binding is not set to NULL." LOG_				
					}
				}
				_LOG << "lbDatabasePanel::lbDBAdd() Actually update record data." LOG_
				
				lbDBUpdate();
				
				if (sampleQuery->update() == ERR_NONE) {
					if (sampleQuery->last() == ERR_NONE)
						lbDBRead();
					else
						_LOG << "Error: Moving to new record failed." LOG_
				} else {
					if (meta->askYesNo("Error: Adding new record failed!\n\nDo you want to retry ?")) {
						lbDBClear();
						if (sampleQuery->update() != ERR_NONE) {
							UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
							newTitle->setData(formName);
							*newTitle += ": Add failed !";
							_LOG << newTitle->charrep() LOG_
							SetName(_trans(newTitle->charrep()));
							_LOG << "Fatal: Adding a new record failed." LOG_
						}
					}
				}
			}
		}
	}

	_CL_LOG << "Return from lbDatabasePanel::lbDBAdd(lb_I_Unknown* uk)" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBDelete(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	err = sampleQuery->remove();
	
	if (err == ERR_DB_ROWDELETED) {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		meta->msgBox("Error", "Could not delete entry. It is in use.");
		return ERR_NONE;
	}
	
	if (err == INFO_DB_REOPENED) {
		lbDBRead();

		return ERR_NONE;
	} else {
		if (err == ERR_DB_NODATA) {
			err = sampleQuery->first();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				DISABLE_BOF()
				lbDBRead();
				return ERR_NONE;
			} else {
				lbDBClear();
				DISABLE_FOR_NO_DATA()
				deactivateActionButtons();
				return ERR_NONE;
			}
		}
		
		err = sampleQuery->next();
		
		if (err == WARN_DB_NODATA) {
			DISABLE_EOF()
			lbDBRead();
			return ERR_NONE;
		}
		
		if (err == ERR_DB_NODATA) {
			err = sampleQuery->first();
			if (err == ERR_DB_NODATA) {
				lbDBClear();
				DISABLE_FOR_NO_DATA()
				deactivateActionButtons();
				return ERR_NONE;
			}
			
			DISABLE_BOF()
		} else {
			nextButton->Enable();
			lastButton->Enable();
			prevButton->Enable();
			firstButton->Enable();
		}
	}
	
	lbDBRead();
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::OnActionButton(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	meta->setStatusText("Info", "Executing action ...");

	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		
/*...sResolve the related data for the action button \40\to be cached later\41\:16:*/
		char* reversedEvent = NULL;
		UAP(lb_I_Integer, eventID)
		QI(uk, lb_I_Integer, eventID)
		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		meta->setStatusText("Info", "Reversing event name to ID ...");
		char* eventName = (char*) strdup(eman->reverseEvent(eventID->getData()));
		reversedEvent = strdup(strtok(eventName, "("));
		free(reversedEvent);
		reversedEvent = strdup(strtok(NULL, ")"));
		meta->setStatusText("Info", "Lookup action source field ...");
		*s = fa->getActionSourceDataField(reversedEvent);
		wxWindow* w = FindWindowByName(wxString(s->charrep()), this);
		wxString value;
		wxString errmsg;
		
		if (w == NULL) 	{
			UAP_REQUEST(getModuleInstance(), lb_I_String, err)
			*err = "Didn't found a control with given name. Check, if your action settings use an existing field from the form. (";
			*err += s->charrep();
			*err += ")\n\nThis may also an UML design error.";
			meta->msgBox("Error", err->charrep());
			return ERR_NONE;
		} else {
			errmsg = wxString("Found a control with given name: ") + wxString(s->charrep());
			meta->setStatusText("Info", errmsg.c_str());
		}
		
		if (sampleQuery->hasFKColumn(s->charrep()) == 1) {
				wxChoice* cbox = (wxChoice*) w;		
				int pos = cbox->GetSelection();
				if (pos != -1) {
					lbErrCodes err = ERR_NONE;
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					cbName->setData(s->charrep());
					UAP(lb_I_KeyBase, key_cbName)
					UAP(lb_I_Unknown, uk_cbMapper)
					UAP(lb_I_Container, cbMapper)
					QI(cbName, lb_I_KeyBase, key_cbName)
					uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);
					QI(uk_cbMapper, lb_I_Container, cbMapper)
					key->setData(pos);
					UAP(lb_I_KeyBase, key_pos)
					QI(key, lb_I_KeyBase, key_pos)
					UAP(lb_I_Unknown, uk_mapping)
					uk_mapping = cbMapper->getElement(&key_pos);
					if (uk_mapping == NULL)  { 
						printf("ERROR: cbMapper didn't found an entry for above search argument\n");
					} else {
						UAP(lb_I_Integer, FK_id)
						QI(uk_mapping, lb_I_Integer, FK_id)
						int p = FK_id->getData();
						char pp[20] = "";
						sprintf(pp, "%d", p);
						value = pp;
					}
				}
/*...e*/
		} else {
/*...sGet the content from text control:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(s->charrep());

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
							if (check->GetValue() == TRUE) {
								value = "true";
							} else {
								value = "false";
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							value = tx->GetValue();
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							value = tx->GetValue();
						}
						break;
					
					
					case lb_I_Query::lbDBColumnUnknown:
					
						break;
				}
/*...e*/
		}
/*...e*/
		
		_LOG << "Have these event: " << reversedEvent << "." LOG_		
		_LOG << "Have got source field: " << s->charrep() << "." LOG_
		_LOG << "The value for the field is " << value.c_str() << "." LOG_		

		errmsg = wxString("Data for the required field '") + wxString(s->charrep()) + wxString("' is '") + value + wxString("'");
		meta->setStatusText("Info", errmsg.c_str());

		UAP(lb_I_Action, action)
		action = fa->getAction(fa->getActionID(reversedEvent));

/*...sBuild up parameter list:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, v)

		parameter->setData("DBName");
		v->setData(_DBName->charrep());
		param->setUAPString(*&parameter, *&v);

		parameter->setData("DBUser");
		v->setData(_DBUser->charrep());
		param->setUAPString(*&parameter, *&v);

		parameter->setData("DBPass");
		v->setData(_DBPass->charrep());
		param->setUAPString(*&parameter, *&v);

		parameter->setData("source Form");
		v->setData(base_formName);
		param->setUAPString(*&parameter, *&v);

		parameter->setData("source field");
		v->setData(s->charrep());
		param->setUAPString(*&parameter, *&v);

		parameter->setData("source value");
		v->setData(value.c_str());
		param->setUAPString(*&parameter, *&v);

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		parameter->setData("application");

		meta->getApplicationName(&v);

		param->setUAPString(*&parameter, *&v);
/*...e*/

		meta->setStatusText("Info", errmsg.c_str());

		action->execute(*&param);

		free(eventName);
	}

	return ERR_NONE;
}
/*...e*/

/*...svoid lbDatabasePanel\58\\58\OnImageButtonClick\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabasePanel::OnImageButtonClick(wxCommandEvent& event ) {

	wxObject* o = event.GetEventObject();
	
	if (o != NULL) {
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
		UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
		UAP_REQUEST(manager.getPtr(), lb_I_String, newfilename)
		UAP_REQUEST(manager.getPtr(), lb_I_String, images)
		UAP_REQUEST(manager.getPtr(), lb_I_String, controlname)

		wxBitmapButton* bmb = (wxBitmapButton*) o;
		*controlname = bmb->GetName().c_str();

		UAP(lb_I_KeyBase, key)
		QI(controlname, lb_I_KeyBase, key)
						
		UAP(lb_I_Unknown, uk)
						
		uk = ImageButtonMapperList->getElement(&key);
		QI(uk, lb_I_String, filename)
		
#ifdef OSX
		*images = "/toolbarimages/";
#endif
#ifdef LINUX
		*images = "/toolbarimages/";
#endif
#ifdef WINDOWS
		*images = "\\toolbarimages\\";
#endif
		*newfilename = app->getDirLocation();
		*newfilename += images->charrep();
		
		wxFileDialog fileDialog(NULL, _trans("Choose a toolbar image"), newfilename->charrep(), "", wxT("XPM Files (*.xpm)|*.xpm|PNG Files (*.png)|*.png"), wxOPEN);

		if (fileDialog.ShowModal() == wxID_OK) {
			*filename = fileDialog.GetFilename().c_str();

			wxString f = wxString(filename->charrep());
							
			wxImage* im;
							
			if (f.Upper().Contains(".XPM") == 1) {
				im = new wxImage(fileDialog.GetPath().c_str(), wxBITMAP_TYPE_XPM);
			}

			if (f.Upper().Contains(".PNG") == 1) {
				im = new wxImage(fileDialog.GetPath().c_str(), wxBITMAP_TYPE_PNG);
			}

			wxBitmap bm = wxBitmap(*im);
			bmb->SetBitmapLabel(bm);
		}
		
	} else {
		_LOG << "Error: Image button click event didn't work!" LOG_
	}

}
/*...e*/

/*...svoid \9\\9\  lbDatabasePanel\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabasePanel::OnDispatch(wxCommandEvent& event ) {
        switch (event.GetId()) {
        default:
                // Delegate all other events
                {
                	lbErrCodes err = ERR_NONE;
			lb_I_Module* m = getModuleInstance();
			
			UAP_REQUEST(m, lb_I_EventManager, eman)
		
			UAP_REQUEST(m, lb_I_Dispatcher, dispatcher)
			dispatcher->setEventManager(eman.getPtr());

			UAP_REQUEST(m, lb_I_Integer, param)
			
			param->setData(event.GetId());
			
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)
		
			UAP_REQUEST(m, lb_I_String, result)
			UAP(lb_I_Unknown, uk_result)
			QI(result, lb_I_Unknown, uk_result)
		
			dispatcher->dispatch(event.GetId(), uk.getPtr(), &uk_result);
                }
                break;
        }
}
/*...e*/

void lbDatabasePanel::OnMouseMove(wxMouseEvent& evt)
{
	wxPoint pt = evt.GetPosition();
	if (evt.Dragging() && evt.LeftIsDown())
	{
		wxPoint pos = ClientToScreen(pt);
		//Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
	}
}
/*...svoid\9\\9\  lbDatabasePanel\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabasePanel::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/

/*...sint LB_STDCALL lbDatabasePanel\58\\58\getPrimaryColumns\40\\41\:0:*/
int LB_STDCALL lbDatabasePanel::getPrimaryColumns()
{
	/*
	   Directly forward the request to the formular field information class.
	   
	   But it would not simply be the primary columns, that are logically
	   the master columns.
	   For sample, a customer relationship management (CRM) system may have
	   a customer number, wich is not the internal ID of the customer entry.
	   
	   So for the database form, it may be the readonly field - the customer
	   number, that has not to be changed.
	   
	 */

	int PKColumns = sampleQuery->getPKColumns();
	
	return PKColumns;
}
/*...e*/
/*...sint LB_STDCALL lbDatabasePanel\58\\58\getForeignColumns\40\char\42\ primaryTable\41\:0:*/
int LB_STDCALL lbDatabasePanel::getForeignColumns(char* primaryTable)
{
	/*
	   Directly forward the request to the formular field information class.
	   
	   But it would not simply be the primary columns, that are logically
	   the master columns.
	   For sample, a customer relationship management (CRM) system may have
	   a customer number, wich is not the internal ID of the customer entry.
	   
	   So for the database form, it may be the readonly field - the customer
	   number, that has not to be changed.
	   
	 */

	int PKColumns = sampleQuery->getFKColumns();

	_CL_LOG << "lbDatabasePanel::getForeignColumns(...) returns " << PKColumns << " columns." LOG_
	
	return PKColumns;
}
/*...e*/
	
lb_I_String* LB_STDCALL lbDatabasePanel::getPrimaryColumn(int pos)
{
	return sampleQuery->getPKColumn(pos);
}

lb_I_String* LB_STDCALL lbDatabasePanel::getForeignColumn(int pos)
{
	return sampleQuery->getFKColumn(pos);
}
	   
bool LB_STDCALL lbDatabasePanel::isCharacterColumn(char* name)
{
	return sampleQuery->getColumnType(name) == lb_I_Query::lbDBColumnChar;
}
/*...e*/

/*...sclass lbPluginDatabasePanel implementation:0:*/
/*...slbPluginDatabasePanel:0:*/
class lbPluginDatabasePanel : public lb_I_PluginImpl {
public:
	lbPluginDatabasePanel();
	
	virtual ~lbPluginDatabasePanel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbForm)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabasePanel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabasePanel, lbPluginDatabasePanel)

/*...slbErrCodes LB_STDCALL lbPluginDatabasePanel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabasePanel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl)
	QI(uk, lb_I_PluginImpl, pl)

	dbForm = pl->getImplementation();
*/

	_CL_VERBOSE << "lbPluginDatabasePanel::setData(...) called.\n" LOG_

	if (dbForm == NULL) {
		_CL_VERBOSE << "ERROR: Cloning database form plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabasePanel::lbPluginDatabasePanel() {
	_CL_VERBOSE << "lbPluginDatabasePanel::lbPluginDatabasePanel() called.\n" LOG_
	dbForm = NULL;
	ref = STARTREF;
}

lbPluginDatabasePanel::~lbPluginDatabasePanel() {
	_CL_LOG << "lbPluginDatabasePanel::~lbPluginDatabasePanel() called.\n" LOG_
	
	if (dbForm != NULL) {
		_CL_LOG << "dbForm is not NULL." LOG_
		_CL_LOG << "*******************" LOG_
	}
}

bool LB_STDCALL lbPluginDatabasePanel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabasePanel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDatabasePanel::initialize() {
}
	
bool LB_STDCALL lbPluginDatabasePanel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabasePanel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabasePanel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {
		lbDatabasePanel* dbPanel = new lbDatabasePanel();
		dbPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbPanel, lb_I_Unknown, dbForm)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return dbForm.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabasePanel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabasePanel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDatabasePanel* dbPanel = new lbDatabasePanel();
		dbPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbPanel, lb_I_Unknown, dbForm)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabasePanel::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (dbForm != NULL) {
		UAP(lb_I_DatabaseForm, form)
		QI(dbForm, lb_I_DatabaseForm, form)
		form->destroy();
		
		dbForm.resetPtr();
	}
}
/*...e*/
/*...e*/

/*...slbDatabaseDialog:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
        ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseDialog, lbDatabaseDialog)


/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbDatabaseDialog::setData(...) not implemented yet" LOG_

#ifdef bla
		UAP(lb_I_DatabaseForm, dbForm)
		QI(uk, lb_I_DatabaseForm, dbForm)
		
		fa = ((lbDatabaseDialog*) dbForm.getPtr())->fa;
		((lbDatabaseDialog*) dbForm.getPtr())->fa = NULL;
	
#endif
		
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseDialog\58\\58\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::lbDatabaseDialog() 
	: wxDialog(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbDatabaseDialog::lbDatabaseDialog() called." LOG_
	ref = STARTREF;
	panel = new lbDatabasePanel();
	_created = true;
}
/*...e*/
/*...slbDatabaseDialog\58\\58\\126\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::~lbDatabaseDialog() {
	_CL_LOG << "lbDatabaseDialog::~lbDatabaseDialog() called." LOG_
}
/*...e*/

void LB_STDCALL lbDatabaseDialog::create(int parentId) {
	// Don't need a parent
}

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	
	sprintf(eventName, "%pDatabaseFirst", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBFirst, eventName);

	sprintf(eventName, "%pDatabaseNext", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBNext,  eventName);

	sprintf(eventName, "%pDatabasePrev", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBPrev,  eventName);

	sprintf(eventName, "%pDatabaseLast", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBLast,  eventName);
	
	sprintf(eventName, "%pDatabaseAdd", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBAdd,  eventName);
	
	sprintf(eventName, "%pDatabaseDelete", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBDelete,  eventName);
	
	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabaseDialog::init(char* _SQLString, char* DBName, char* DBUser, char* DBPass) {
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);

	panel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	panel->create(this->GetId());

	sizerMain->Add(panel, 1, wxEXPAND | wxALL, 5);

	panel->init(_SQLString, DBName, DBUser, DBPass);

	SetName(panel->getFormName());

	SetAutoLayout(TRUE);
		
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	//Centre();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setName(char const * name, char const * appention) {

	return panel->setName(name, appention);
}
/*...e*/

char*      LB_STDCALL lbDatabaseDialog::getFormName() {
	return panel->getFormName();
}

/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getQuery\40\\41\:0:*/
char* LB_STDCALL lbDatabaseDialog::getQuery() {
	return panel->getQuery();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getColumnName\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseDialog::getColumnName(int pos) {
	return panel->getColumnName(pos);
}
/*...e*/

void LB_STDCALL lbDatabaseDialog::windowIsClosing(lb_I_Window* w) {
	panel->windowIsClosing(w);
}

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setMasterForm\40\lb_I_DatabaseMasterForm\42\ master\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params) {
	panel->setMasterForm(master, params);
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setDetailForm\40\lb_I_DatabaseMasterForm\42\ detail\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setDetailForm(lb_I_DatabaseForm* detail, lb_I_Parameter* params) {
	panel->setDetailForm(detail, params);
}
/*...e*/

/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getControls\40\\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getControls() {
	return panel->getControls();
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseDialog\58\\58\getControlValue\40\int pos\41\:0:*/
const char* LB_STDCALL lbDatabaseDialog::getControlValue(int pos) {
	UAP(lb_I_String, c)
	c = panel->getColumnName(pos);
	return panel->getControlValue(c->charrep());
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseDialog\58\\58\getControlValue\40\char\42\ name\41\:0:*/
const char* LB_STDCALL lbDatabaseDialog::getControlValue(char* name) {

	wxString value;

	value = panel->getControlValue(name);
	
	return value.c_str();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\ignoreForeignKeys\40\char\42\ toTable\41\:0:*/
void LB_STDCALL lbDatabaseDialog::ignoreForeignKeys(char* toTable) {
	panel->ignoreForeignKeys(toTable);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabaseDialog::updateFromMaster() {
	panel->updateFromMaster();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\updateFromDetail\40\\41\:0:*/
void LB_STDCALL lbDatabaseDialog::updateFromDetail() {
	panel->updateFromDetail();
}
/*...e*/

void  LB_STDCALL lbDatabaseDialog::reopen() {
	panel->reopen();
}

lbErrCodes  LB_STDCALL lbDatabaseDialog::close() {
	return panel->close();
}

lbErrCodes  LB_STDCALL lbDatabaseDialog::open() {
	return panel->open();
}

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setFilter(char* filter) {
	panel->setFilter(filter);
}
/*...e*/

/*...schar\42\ lbDatabaseDialog\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
lb_I_String* lbDatabaseDialog::getTableName(char* columnName) {
	return panel->getTableName(columnName);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBClear() {
	return panel->lbDBClear();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBUpdate() {
	return panel->lbDBUpdate();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBRead() {
	return panel->lbDBRead();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBFirst(lb_I_Unknown* uk) {
	return panel->lbDBFirst(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBNext(lb_I_Unknown* uk) {
	return panel->lbDBNext(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBPrev(lb_I_Unknown* uk) {
	return panel->lbDBPrev(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBLast(lb_I_Unknown* uk) {
	return panel->lbDBLast(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBAdd(lb_I_Unknown* uk) {
	return panel->lbDBAdd(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBDelete(lb_I_Unknown* uk) {
	return panel->lbDBDelete(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::OnActionButton(lb_I_Unknown* uk) {
	return panel->OnActionButton(uk);
}
/*...e*/

/*...svoid \9\\9\  lbDatabaseDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnDispatch(wxCommandEvent& event ) {
	// Dispatcher should be called inside panel
}
/*...e*/
/*...svoid\9\\9\  lbDatabaseDialog\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/

/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getPrimaryColumns\40\\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getPrimaryColumns()
{
	return panel->getPrimaryColumns();
}
/*...e*/
/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getForeignColumns\40\char\42\ primaryTable\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getForeignColumns(char* primaryTable)
{
	return panel->getForeignColumns(primaryTable);
}
/*...e*/
	
lb_I_String* LB_STDCALL lbDatabaseDialog::getPrimaryColumn(int pos)
{
	return panel->getPrimaryColumn(pos);
}

lb_I_String* LB_STDCALL lbDatabaseDialog::getForeignColumn(int pos)
{
	return panel->getForeignColumn(pos);
}
	   
bool LB_STDCALL lbDatabaseDialog::isCharacterColumn(char* name)
{
	return panel->isCharacterColumn(name);
}
/*...e*/

/*...sclass lbPluginDatabaseDialog implementation:0:*/
/*...slbPluginDatabaseDialog:0:*/
class lbPluginDatabaseDialog : public lb_I_PluginImpl {
public:
	lbPluginDatabaseDialog();
	
	virtual ~lbPluginDatabaseDialog();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbForm)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseDialog)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseDialog, lbPluginDatabaseDialog)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseDialog::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl)
	QI(uk, lb_I_PluginImpl, pl)

	dbForm = pl->getImplementation();
*/

	_CL_VERBOSE << "lbPluginDatabaseDialog::setData(...) called.\n" LOG_

	if (dbForm == NULL) {
		_CL_VERBOSE << "ERROR: Cloning database form plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseDialog::lbPluginDatabaseDialog() {
	_CL_VERBOSE << "lbPluginDatabaseDialog::lbPluginDatabaseDialog() called.\n" LOG_
	dbForm = NULL;
	ref = STARTREF;
}

lbPluginDatabaseDialog::~lbPluginDatabaseDialog() {
	_CL_VERBOSE << "lbPluginDatabaseDialog::~lbPluginDatabaseDialog() called.\n" LOG_

	if (dbForm != NULL) {
		_CL_LOG << "dbForm is not NULL." LOG_
		_CL_LOG << "*******************" LOG_
	}
}

void LB_STDCALL lbPluginDatabaseDialog::initialize() {
}

bool LB_STDCALL lbPluginDatabaseDialog::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabaseDialog::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

bool LB_STDCALL lbPluginDatabaseDialog::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseDialog\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseDialog::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {
		lbDatabaseDialog* dbDialog = new lbDatabaseDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbDialog, lb_I_Unknown, dbForm)
	} else {
		_CL_VERBOSE << "lbPluginDatabaseDialog::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return dbForm.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseDialog\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseDialog::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDatabaseDialog* dbDialog = new lbDatabaseDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbDialog, lb_I_Unknown, dbForm)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseDialog::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (dbForm != NULL) {
		UAP(lb_I_DatabaseForm, form)
		QI(dbForm, lb_I_DatabaseForm, form)
	
		form->destroy();
		
		dbForm.resetPtr();
	}
}
/*...e*/
/*...e*/


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

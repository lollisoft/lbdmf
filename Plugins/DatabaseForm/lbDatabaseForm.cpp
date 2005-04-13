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
#include <malloc.h>
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

#include <lbDatabaseForm.h>
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
/*...e*/

class lbPluginModuleDatabaseForm : public lb_I_PluginModule {
public:

	lbPluginModuleDatabaseForm();
	virtual ~lbPluginModuleDatabaseForm();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};

/*...sclass lbConfigure_FK_PK_MappingDialog:0:*/
/*...sclass lbConfigure_FK_PK_MappingDialog definition:0:*/
class lbConfigure_FK_PK_MappingDialog :
	public lb_I_EventHandler,
	public lb_I_Unknown,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbConfigure_FK_PK_MappingDialog();

	/**
	 * Destructor
	 */
	virtual ~lbConfigure_FK_PK_MappingDialog();

	int prepareDialogHandler();

	void LB_STDCALL init(lb_I_Query* query);

	void LB_STDCALL show() { ShowModal (); };
	void LB_STDCALL destroy() { Destroy(); };
	
	/**
	 * Column has been selected.
	 *
	 * Store the retrieved data in the tables and destroy the form.
	 */

	lbErrCodes LB_STDCALL selectedColumn(lb_I_Unknown* uk);

	/**
	 * This function acts in a special way for registering the above navigation handlers
	 *
	 * It uses a string of the this pointer + a name for the respective eventhandler.
	 * This is neccessary for handling more than one database dialog per application.
	 *
	 * This is a good sample, if you need to be able to handle more than one instance of
	 * your registered event handlers.
	 */
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);

	void OnDispatch(wxCommandEvent& event);

	DECLARE_LB_UNKNOWN()


	void OnFKComboBoxSelected( wxCommandEvent &event );
	void OnPKComboBoxSelected( wxCommandEvent &event );
	    
/*...svariables:8:*/
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	
	/**
	 * \brief Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id). 
	 */
	UAP(lb_I_Container, ComboboxMapperList, __FILE__, __LINE__)
	UAP(lb_I_Query, sourceQuery, __FILE__, __LINE__)
	

	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
	
	wxWindow* firstButton;

	wxComboBox* cBoxFKNames;
	wxComboBox* cBoxPKNames;

	wxStaticText *label;
	wxStaticText *labelF;
	
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
/*...e*/
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbConfigure_FK_PK_MappingDialog)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbConfigure_FK_PK_MappingDialog\58\\58\lbConfigure_FK_PK_MappingDialog\40\\41\:0:*/
lbConfigure_FK_PK_MappingDialog::lbConfigure_FK_PK_MappingDialog() 
: wxDialog(NULL, -1, wxString(_T("lbConfigure_FK_PK_MappingDialog dialog")), wxDefaultPosition,
wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	ref = STARTREF;
}
/*...e*/
/*...slbConfigure_FK_PK_MappingDialog\58\\58\\126\lbConfigure_FK_PK_MappingDialog\40\\41\:0:*/
lbConfigure_FK_PK_MappingDialog::~lbConfigure_FK_PK_MappingDialog() {

}
/*...e*/
/*...slbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbConfigure_FK_PK_MappingDialog::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnFKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected( wxCommandEvent &event ) {
	wxString s = cBoxFKNames->GetStringSelection();
	
	cBoxFKNames->Disable();
	
	REQUEST(manager.getPtr(), lb_I_Database, database)
	
	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
	
	UAP(lb_I_String, PKTable, __FILE__, __LINE__)
	
	PKTable = sourceQuery->getPKTable(s.c_str());
	
	char buf[] = "select * from %s";
	char* buffer = (char*) malloc(strlen(buf)+strlen(PKTable->charrep())+1);
	sprintf(buffer, buf, PKTable->charrep());
	
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	
	sampleQuery = database->getQuery(0);

	sampleQuery->query(buffer);
	
	for (int i = 1; i <= sampleQuery->getColumns(); i++) {
		char* name = sampleQuery->getColumnName(i);
		cBoxPKNames->Append(wxString(name));
	}
	
	cBoxPKNames->Enable();
}
/*...e*/
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnPKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected( wxCommandEvent &event ) {
	wxString PKName = cBoxPKNames->GetStringSelection();
	wxString FKName = cBoxFKNames->GetStringSelection();

	UAP(lb_I_String, PKTable, __FILE__, __LINE__)
	
	char* fkTable = strdup(sourceQuery->getTableName());
	
	char* p = strdup(FKName.c_str());
	
	PKTable = sourceQuery->getPKTable(p);
	
	free(p);
	
	cBoxPKNames->Disable();
	
	// Delete the entry, we now will put into the configuration
	
	cBoxFKNames->Delete(cBoxFKNames->GetSelection());
	
	
	REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
	
	char buf[] = "insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) values('%s','%s', '%s', '%s')";
	char* buffer = (char*) malloc(	strlen(buf)+
					PKName.Length()+
					strlen(fkTable)+
					FKName.Length()+
					strlen(PKTable->charrep())+1);

	buffer[0] = 0;

	sprintf(buffer, buf, FKName.c_str(), fkTable, PKName.c_str(), PKTable->charrep());

	printf("%s\n", buffer);
	
	query = database->getQuery(0);
	
	query->query(buffer);
	
	if (cBoxFKNames->GetCount() > 0) {
		cBoxFKNames->SetSelection(-1);
		cBoxFKNames->Enable();
		cBoxPKNames->Clear();
		cBoxPKNames->Disable();
	} else {
		cBoxPKNames->Disable();
		cBoxFKNames->Disable();

		firstButton->Enable();		
	}
	
}
/*...e*/

lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::selectedColumn(lb_I_Unknown* uk) {
	EndModal(wxID_OK);

	return ERR_NONE;
}

/*...sint lbConfigure_FK_PK_MappingDialog\58\\58\prepareDialogHandler\40\\41\:0:*/
int lbConfigure_FK_PK_MappingDialog::prepareDialogHandler() {
	int SelectedColumn;
	int cbFKSel;
	int cbPKSel;
	
	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
	UAP_REQUEST(manager.getPtr(), lb_I_Dispatcher, dispatcher)

	char eventName[100] = "";
		
	sprintf(eventName, "%pSelectedColumn", this);
	eman->registerEvent(eventName, SelectedColumn);

	dispatcher->setEventManager(eman.getPtr());

	// Register lbDMF dispatched event handler

	registerEventHandler(dispatcher.getPtr());

	this->Connect( SelectedColumn,  -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnDispatch);

	// Register normal wxWidgets event handler

	this->Connect( cBoxFKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_UPDATED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected);

	this->Connect( cBoxPKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_UPDATED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected);

	this->Connect( cBoxFKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_ENTER, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected);

	this->Connect( cBoxPKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_ENTER, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected);

	return SelectedColumn;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::registerEventHandler(lb_I_Dispatcher* dispatcher) {
	lbErrCodes err = ERR_NONE;

	char eventName[100] = "";

	sprintf(eventName, "%pSelectedColumn", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbConfigure_FK_PK_MappingDialog::selectedColumn, eventName);

	return err;
}
/*...e*/
/*...svoid LB_STDCALL lbConfigure_FK_PK_MappingDialog\58\\58\init\40\lb_I_Query\42\ query\41\:0:*/
void LB_STDCALL lbConfigure_FK_PK_MappingDialog::init(lb_I_Query* query) {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	QI(query, lb_I_Query, sourceQuery, __FILE__, __LINE__)
	sourceQuery++;
	
/*...ssizers:0:*/
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);
/*...e*/

	sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
	sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);

	label = new wxStaticText(this, -1, "Dropdown Element:", wxPoint());
	sizerLeft->Add(label, 1, wxALL, 5);
	
	cBoxFKNames = new wxComboBox(this, -1);
	sizerLeft->Add(cBoxFKNames, 1, wxALL, 5);

	labelF = new wxStaticText(this, -1, "Feld anzuzeigen:", wxPoint());
	sizerRight->Add(labelF, 1, wxALL, 5);
	
	cBoxPKNames = new wxComboBox(this, -1);
	sizerRight->Add(cBoxPKNames, 1, wxALL, 5);

	int SelectedColumn = prepareDialogHandler();

	cBoxPKNames->Disable();

	for (int i = 1; i <= query->getColumns(); i++) {
		char* name = query->getColumnName(i);
		
		if (query->hasFKColumn(name) == 1) {
			cBoxFKNames->Append(wxString(name));
		}
	}

	firstButton = new wxButton(this, SelectedColumn, "Ready", wxPoint(), wxSize(100,20));
	firstButton->Disable();

	sizerNavi->Add(firstButton, 1, wxALL, 5);

	SetAutoLayout(TRUE);
	
	sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerNavi, 0, wxEXPAND | wxALL, 5);
	
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	Centre();

}
/*...e*/
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnDispatch(wxCommandEvent& event ) {
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

/*...sclass lbPluginModuleDatabaseForm implementation:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbPluginModuleDatabaseForm)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginModule, lbPluginModuleDatabaseForm)

BEGIN_PLUGINS(lbPluginModuleDatabaseForm)
	ADD_PLUGIN(lbPluginDatabaseDialog, GUI)
END_PLUGINS()

lbPluginModuleDatabaseForm::lbPluginModuleDatabaseForm() {
	ref = STARTREF;
}

lbPluginModuleDatabaseForm::~lbPluginModuleDatabaseForm() {
	_CL_LOG << "lbPluginModuleDatabaseForm::~lbPluginModuleDatabaseForm() called." LOG_
}

void LB_STDCALL lbPluginModuleDatabaseForm::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModuleDatabaseForm::setData(lb_I_Unknown* uk) {
        _LOG << "lbPluginModuleDatabaseForm::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...sclass lbPluginDatabaseDialog and lbDatabaseDialog implementation:0:*/
/*...slbDatabaseDialog:0:*/
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
/*...sclass lbDatabaseDialog:0:*/
/**
 * This is the sample database dialog for a wxWidgets based GUI.
 */


class lbDatabaseDialog :
	public lb_I_DatabaseForm,
	public wxDialog {
public:
	/**
	 * Default constructor - implemented in BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
	 */
	lbDatabaseDialog();

	/**
	 * Destructor
	 */
	virtual ~lbDatabaseDialog();

	lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) { return ERR_NONE; };
	lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	lbErrCodes LB_STDCALL addOwnerDrawn(char* name, int x, int y, int w, int h) { return ERR_NONE; };

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() { Destroy(); };
	
/*...sfrom DatabaseForm interface:8:*/
	/**
	 * This function creates the dialog on the fly.
	 *
	 * It builds the layout, navigation elements and instanciate the needed
	 * database classes.
	 */
	void LB_STDCALL init(char* formName, char* SQLString, char* DBName, char* DBUser, char* DBPass);
/*...e*/

/*...sData navigation and other handlers:8:*/
	/**
	 * Database navigation
	 * 
	 * Moves to the first row.
	 */
	lbErrCodes LB_STDCALL lbDBFirst(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the next row.
	 */
	lbErrCodes LB_STDCALL lbDBNext(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the previous row.
	 */
	lbErrCodes LB_STDCALL lbDBPrev(lb_I_Unknown* uk);

	/**
	 * Database navigation
	 * 
	 * Moves to the last row.
	 */
	lbErrCodes LB_STDCALL lbDBLast(lb_I_Unknown* uk);
	
	/**
	 * Database manipulation
	 * 
	 * This adds a new row, while it copies the values of the actual form into the row.
	 */
	lbErrCodes LB_STDCALL lbDBAdd(lb_I_Unknown* uk);

	/**
	 * Database manipulation
	 * 
	 * Deletes the current row.
	 */
	lbErrCodes LB_STDCALL lbDBDelete(lb_I_Unknown* uk);

	/**
	 * Database manipulation
	 * 
	 * Internally used to update the current row.
	 */
	lbErrCodes LB_STDCALL lbDBUpdate();

	/**
	 * Database manipulation
	 *
	 * Clear the form.
	 */

	lbErrCodes LB_STDCALL lbDBClear();

	/**
	 * Database manipulation
	 * 
	 * Internally used to read data from the cursor to the current row.
	 */
	lbErrCodes LB_STDCALL lbDBRead();
/*...e*/

/*...sfrom EventHandler interface:8:*/
	/**
	 * This function acts in a special way for registering the above navigation handlers
	 *
	 * It uses a string of the this pointer + a name for the respective eventhandler.
	 * This is neccessary for handling more than one database dialog per application.
	 *
	 * This is a good sample, if you need to be able to handle more than one instance of
	 * your registered event handlers.
	 */
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
/*...e*/

	void OnDispatch(wxCommandEvent& event);

	/** \brief Paint the control.
	 *
	 * This handler should be used to paint an 'ownerdrawn' control.
	 * As in my Power++ code 'EditSymbol', this should also work under
	 * wxWidgets.
	 *
	 * The only problem would be the selection of which control currently
	 * fires the event. 'EditSymbol' only handles one such control.
	 */
	void OnPaint(wxCommandEvent& event);

	DECLARE_LB_UNKNOWN()

/*...svariables:8:*/
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	
	/**
	 * \brief Maps positions to id's for each displayed combo box.
	 *
	 * Store a container for each combo box with key(pos) and data(id). 
	 */
	UAP(lb_I_Container, ComboboxMapperList, __FILE__, __LINE__)
	

	// l gets overwritten, while assigning a lb_I_Query* pointer to sampleQuery !!
	// l and buf are therefore as a bugfix.
	long l;
	char buf[100];
	
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
/*...e*/
};
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
        ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseDialog, lbDatabaseDialog)

lbErrCodes LB_STDCALL lbDatabaseDialog::setData(lb_I_Unknown* uk) {
        _CL_LOG << "lbDatabaseDialog::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbDatabaseDialog::lbDatabaseDialog() 
	: wxDialog(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbDatabaseDialog::lbDatabaseDialog() called." LOG_
}

lbDatabaseDialog::~lbDatabaseDialog() {
	_CL_LOG << "lbDatabaseDialog::~lbDatabaseDialog() called." LOG_
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
/*...svoid lbDatabaseDialog\58\\58\init\40\char\42\ formName\44\ char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void lbDatabaseDialog::init(char* formName, char* SQLString, char* DBName, char* DBUser, char* DBPass) {
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	SetTitle(formName);

	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);

	REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();
	
	printf("Connecting to %s as %s\n", DBName, DBUser);
	
	database->connect(DBName, DBUser, DBPass);

	char* _q = strdup(SQLString);

	sampleQuery = database->getQuery(0);
		
/*...svariables:8:*/
	int DatabaseFirst;
	int DatabaseNext;
	int DatabasePrev;
	int DatabaseLast;
	int DatabaseAdd;
	int DatabaseDelete;
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

		dispatcher->setEventManager(eman.getPtr());

		registerEventHandler(dispatcher.getPtr());

/*...e*/
	
	sampleQuery->enableFKCollecting();
	sampleQuery->query(_q);

	free(_q);

	int columns = sampleQuery->getColumns();

	printf("Create %d formular elements.\n", columns);

	sampleQuery->first();
	
/*...screate database form elements:8:*/
	REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapperList)

	for(int i = 1; i <= columns; i++) {
		char* name = NULL;

		bool createdControl = false;

		UAP(lb_I_Query, FKColumnQuery, __FILE__, __LINE__)
		UAP(lb_I_Query, FKColumnQuery1, __FILE__, __LINE__)
		
		name = strdup(sampleQuery->getColumnName(i));

		printf("Setup form element for '%s'\n", name);

		/* Determine, if the column is a foreign key. If so try to get the
		   configured column to show instead.
		*/ 

		if (sampleQuery->hasFKColumn(name) == 1) {
/*...sCreate a combobox:32:*/
			lbErrCodes err = ERR_NONE;

printf("Create a drop down box for '%s'\n", name);
			
			// Create a mapping instance for this combo box
			UAP_REQUEST(manager.getPtr(), lb_I_Container, _ComboboxMapper)
			UAP_REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapper)

			UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
			UAP(lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
			
			QI(cbName, lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
			QI(_ComboboxMapper, lb_I_Unknown, uk_ComboboxMapper, __FILE__, __LINE__)

			cbName->setData(name);
			
			ComboboxMapperList->insert(&uk_ComboboxMapper, &key_cbName);

			ukComboboxMapper = ComboboxMapperList->getElement(&key_cbName);
			
			QI(ukComboboxMapper, lb_I_Container, ComboboxMapper, __FILE__, __LINE__)
			
			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;
			
			sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
					"where FKName = '%s' and FKTable = '%s'", name, sampleQuery->getTableName());

			FKColumnQuery = database->getQuery(0);
			
			FKColumnQuery->query(buffer);
			
			err = FKColumnQuery->first();
			
			if (err == ERR_DB_NODATA) {
				_CL_LOG << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
			
	
				lbConfigure_FK_PK_MappingDialog* fkpkDialog = new lbConfigure_FK_PK_MappingDialog();
				
				fkpkDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				
				fkpkDialog->init(sampleQuery.getPtr());
				
				fkpkDialog->show();
				
				fkpkDialog->destroy();

				FKColumnQuery1 = FKColumnQuery.getPtr();
			
				FKColumnQuery = NULL;
				
				FKColumnQuery = database->getQuery(0);
			
				FKColumnQuery->query(buffer);
				
				err = FKColumnQuery->first();
			}

			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sHave mapping to visible data for the combobox:64:*/
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
				
				PKName = FKColumnQuery->getAsString(1);
				PKTable = FKColumnQuery->getAsString(2);
					
				wxComboBox *cbox = new wxComboBox(this, -1, wxString(""));
				cbox->SetName(name);
				
				int old_fk = atoi(sampleQuery->getAsString(i)->charrep());
				
				buffer[0] = 0;
				
				sprintf(buffer, "select %s, id from %s order by id", PKName->charrep(), PKTable->charrep());
				
				UAP(lb_I_Query, ReplacementColumnQuery, __FILE__, __LINE__)
				
				ReplacementColumnQuery = database->getQuery(0);
				
				ReplacementColumnQuery->query(buffer);
				
				lbErrCodes DBerr = ReplacementColumnQuery->first();
				
				int cbox_pos = 0;
				
				if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
/*...sHave data to fill into the combobox and create mappings:104:*/
					UAP_REQUEST(manager.getPtr(), lb_I_String, data)
					UAP_REQUEST(manager.getPtr(), lb_I_String, possible_fk)
					
					data = ReplacementColumnQuery->getAsString(1);
					possible_fk = ReplacementColumnQuery->getAsString(2);
					
					int possible_fk_pos = atoi(possible_fk->charrep());
					
					cbox->Append(wxString(data->charrep()));
					
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					
					UAP(lb_I_Unknown, uk_possible_fk, __FILE__, __LINE__)
					UAP(lb_I_KeyBase, key_cbox_pos, __FILE__, __LINE__)
					
					if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
					
					key->setData(cbox_pos);
					cbox_pos++;
					
					QI(key, lb_I_KeyBase, key_cbox_pos, __FILE__, __LINE__)
					UAP_REQUEST(manager.getPtr(), lb_I_Integer, possible_fk_int)

					possible_fk_int->setData(possible_fk_pos);

					QI(possible_fk_int, lb_I_Unknown, uk_possible_fk, __FILE__, __LINE__)
					
					ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
					
					if (DBerr != WARN_DB_NODATA)
					// Only if not WARN_DB_NODATA					
					while ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
						DBerr = ReplacementColumnQuery->next();
						
						data = ReplacementColumnQuery->getAsString(1);
						possible_fk = ReplacementColumnQuery->getAsString(2);
					
						possible_fk_pos = atoi(possible_fk->charrep());
					
						cbox->Append(wxString(data->charrep()));
					
						if (old_fk == possible_fk_pos) cbox->SetSelection(cbox_pos);
					
						key->setData(cbox_pos);
						cbox_pos++;
						
						QI(key, lb_I_KeyBase, key_cbox_pos, __FILE__, __LINE__)
						UAP_REQUEST(manager.getPtr(), lb_I_Integer, possible_fk_int)
						
						possible_fk_int->setData(possible_fk_pos);
						
						QI(possible_fk_int, lb_I_Unknown, uk_possible_fk, __FILE__, __LINE__)
					
						ComboboxMapper->insert(&uk_possible_fk, &key_cbox_pos);
					
						if (DBerr == WARN_DB_NODATA) break;
					}
					
/*...e*/
				}
				
				sizerRight->Add(cbox, 1, wxEXPAND | wxALL, 5);
				
				createdControl = true;
/*...e*/
			}

			free(buffer);
/*...e*/
		} else {
/*...sCreate controls based on database type:32:*/
			lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

			switch (coltype) {
				case lb_I_Query::lbDBColumnBit:
					{
						printf("Creating a checkbox control.\n");
						
						wxCheckBox *check = new wxCheckBox(this, -1, 
							"", wxPoint());
						check->SetName(name);
						sizerRight->Add(check, 1, wxEXPAND | wxALL, 5);	

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnChar:
					{
						wxTextCtrl *text = new wxTextCtrl(this, -1, 
							sampleQuery->getAsString(i)->charrep(), wxPoint());
						text->SetName(name);
						sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnBinary:
					break;

				case lb_I_Query::lbDBColumnInteger:
				case lb_I_Query::lbDBColumnUnknown:
					break;
			}
/*...e*/
		}
		
		if (createdControl) {
			char* tLabel = new char[strlen(name) + 1];
		
			tLabel[0] = 0;
		
			tLabel = strcat(tLabel, name); 
		
			wxStaticText *label = new wxStaticText(this, -1, tLabel, wxPoint());
			sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
		}	
		
		free(name);
	}
/*...e*/

	sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
	sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);

	wxButton *button1 = new wxButton(this, DatabaseFirst, "First", wxPoint(), wxSize(100,20));
	wxButton *button2 = new wxButton(this, DatabasePrev, "Prev", wxPoint(), wxSize(100,20));
	wxButton *button3 = new wxButton(this, DatabaseNext, "Next", wxPoint(), wxSize(100,20));
	wxButton *button4 = new wxButton(this, DatabaseLast, "Last", wxPoint(), wxSize(100,20));

	firstButton = button1;
	prevButton = button2;
	nextButton = button3;
	lastButton = button4;

	button1->Disable();
	button2->Disable();

	sizerNavi->Add(button1, 1, wxALL, 5);
	sizerNavi->Add(button2, 1, wxALL, 5);
	sizerNavi->Add(button3, 1, wxALL, 5);
	sizerNavi->Add(button4, 1, wxALL, 5);

	wxButton *buttonAdd = new wxButton(this, DatabaseAdd, "Add", wxPoint(), wxSize(100,20));
	wxButton *buttonDelete = new wxButton(this, DatabaseDelete, "Delete", wxPoint(), wxSize(100,20));


	sizerAddRem->Add(buttonAdd, 1, wxALL, 5);
	sizerAddRem->Add(buttonDelete, 1, wxALL, 5);


	/*
	 * Create action elements as configured.
	 */

	UAP(lb_I_Query, actionQuery, __FILE__, __LINE__)
	
	actionQuery = database->getQuery(0);

	char *_actionquery = "select actions.name, action_target.what from actions "
			     
			     "inner join action_target on actions.id = action_target.id "
			     
			     "inner join formular_actions on actions.id = formular_actions.action "
			     
			     "inner join formulare on formular_actions.formular = formulare.id "
			     
			     "where formulare.name = '%s'";

	char *buf = (char*) malloc(strlen(_actionquery) + strlen(formName) + 1);
	buf[0] = 0;
	
	sprintf(buf, _actionquery, formName);
	
	printf("%s\n", buf);
	
	actionQuery->query(buf);
	lbErrCodes err = actionQuery->first();
	
	while (err == ERR_NONE) {
		UAP(lb_I_String, action, __FILE__, __LINE__)
		UAP(lb_I_String, actionWhat, __FILE__, __LINE__)
		
		action = actionQuery->getAsString(1);
		actionWhat = actionQuery->getAsString(2);

		int actionID = 0;
		
		char eventName[100] = "";
		
		sprintf(eventName, "%s", this, actionWhat->charrep());
		eman->registerEvent(eventName, actionID);
		
		wxButton *actionButton = new wxButton(this, actionID, action->charrep(), wxPoint(), wxSize(100,20));
		
		sizerActions->Add(actionButton);

		err = actionQuery->next();
	}
	
	if (err == WARN_DB_NODATA) {
		UAP(lb_I_String, action, __FILE__, __LINE__)
		UAP(lb_I_String, actionWhat, __FILE__, __LINE__)
		
		action = actionQuery->getAsString(1);
		actionWhat = actionQuery->getAsString(2);

		int actionID = 0;
		
		char eventName[100] = "";
		
		sprintf(eventName, "%s", this, actionWhat->charrep());
		eman->registerEvent(eventName, actionID);
		
		wxButton *actionButton = new wxButton(this, actionID, action->charrep(), wxPoint(), wxSize(100,20));
		
		sizerActions->Add(actionButton);
	
	}


//#define CONNECTOR ((wxFrame*) frame)
#define CONNECTOR this

	CONNECTOR->Connect( DatabaseFirst,  -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
	CONNECTOR->Connect( DatabaseNext,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
	CONNECTOR->Connect( DatabasePrev,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
	CONNECTOR->Connect( DatabaseLast,  -1, wxEVT_COMMAND_BUTTON_CLICKED,  
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);

	CONNECTOR->Connect( DatabaseAdd,  -1, wxEVT_COMMAND_BUTTON_CLICKED,   
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
	CONNECTOR->Connect( DatabaseDelete, -1, wxEVT_COMMAND_BUTTON_CLICKED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);


	/*
	 * Connect the 'ownerdrawn' controls to the OnPaint handler.
	 *
	 * This would be a loop for all controls. The data for that
	 * control should be in any format. The drawing handler must
	 * be capable to handle it independently.
	 */


	
	

	SetAutoLayout(TRUE);
	
	sizerMain->Add(sizerHor, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerActions, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerAddRem, 0, wxEXPAND | wxALL, 5);
	sizerMain->Add(sizerNavi, 0, wxEXPAND | wxALL, 5);
	
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	Centre();


}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBClear() {
	int columns = sampleQuery->getColumns();

	for (int i = 1; i <= columns; i++) {
		char* name = strdup(sampleQuery->getColumnName(i));

		wxWindow* w = FindWindowByName(wxString(name), this);

		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name) == 1) {
/*...sUpdate drop down box:32:*/
				wxComboBox* cbox = (wxComboBox*) w;
				
				cbox->SetSelection(-1);
/*...e*/
			} else {
/*...sUpdate controls:32:*/
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
					
					case lb_I_Query::lbDBColumnInteger:
					case lb_I_Query::lbDBColumnUnknown:
						break;
				}

				
/*...e*/
			}
		} else {
			_CL_VERBOSE << "Control '" << name << "' nicht gefunden." LOG_
		}
		
		free(name);
	}
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBUpdate() {
	int columns = sampleQuery->getColumns();

	UAP_REQUEST(manager.getPtr(), lb_I_String, col)
	UAP_REQUEST(manager.getPtr(), lb_I_String, val)
					
	for (int i = 1; i <= columns; i++) {
		char* name = strdup(sampleQuery->getColumnName(i));

		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name), this);

		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name) == 1) {
/*...sUpdate drop down box:32:*/
				wxComboBox* cbox = (wxComboBox*) w;
				
				int pos = cbox->GetSelection();
				
				if (pos != -1) {
					lbErrCodes err = ERR_NONE;

					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
					cbName->setData(name);
					
					UAP(lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
					UAP(lb_I_Unknown, uk_cbMapper, __FILE__, __LINE__)
					UAP(lb_I_Container, cbMapper, __FILE__, __LINE__)
					
					QI(cbName, lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
					
					uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);
					
					QI(uk_cbMapper, lb_I_Container, cbMapper, __FILE__, __LINE__)
					
					key->setData(pos);
					
					UAP(lb_I_KeyBase, key_pos, __FILE__, __LINE__)
					
					QI(key, lb_I_KeyBase, key_pos, __FILE__, __LINE__)
				
					UAP(lb_I_Unknown, uk_mapping, __FILE__, __LINE__)
					
					uk_mapping = cbMapper->getElement(&key_pos);
					
					if (uk_mapping == NULL)  { 
						printf("ERROR: cbMapper didn't found an entry for above search argument\n");
					} else {
						UAP(lb_I_Integer, FK_id, __FILE__, __LINE__)
					
						QI(uk_mapping, lb_I_Integer, FK_id, __FILE__, __LINE__)
					
						int p = FK_id->getData();
					
						char pp[20] = "";
						
						sprintf(pp, "%d", p);
					
						col->setData(name);
						val->setData(pp);
					
						sampleQuery->setString(*&col, *&val);
					}
				}
/*...e*/
			} else {
/*...sUpdate controls:32:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
							if (check->GetValue() == TRUE) {
								wxString v = "true";
								col->setData(name);
								val->setData(v.c_str());
								
								sampleQuery->setString(*&col, *&val);
							} else {
								wxString v = "false";
								col->setData(name);
								val->setData(v.c_str());
								
								sampleQuery->setString(*&col, *&val);
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
			
							wxString v = tx->GetValue();
			
							col->setData(name);
							val->setData(v.c_str());

							sampleQuery->setString(*&col, *&val);
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
					case lb_I_Query::lbDBColumnUnknown:
						break;
				}

				
/*...e*/
			}
		} else {
			_CL_VERBOSE << "Control '" << name << "' nicht gefunden." LOG_
		}
		
		free(name);
	}

	if (sampleQuery->update() != ERR_NONE) {
		printf("sampleQuery->update() failed.\n");
		return ERR_UPDATE_FAILED;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBRead() {
	int columns = sampleQuery->getColumns();
	
	for (int i = 1; i <= columns; i++) {
		char* name = strdup(sampleQuery->getColumnName(i));
		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name), this);
		
		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name) == 1) {
/*...sfill combo box with data:32:*/
				wxComboBox* cbox = (wxComboBox*) w;
				
				lbErrCodes err = ERR_NONE;

				UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
				UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)

				cbName->setData(name);

				UAP(lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
				UAP(lb_I_Unknown, uk_cbMapper, __FILE__, __LINE__)
				UAP(lb_I_Container, cbMapper, __FILE__, __LINE__)

				QI(cbName, lb_I_KeyBase, key_cbName, __FILE__, __LINE__)

				uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);

				QI(uk_cbMapper, lb_I_Container, cbMapper, __FILE__, __LINE__)
				
				int count = cbMapper->Count();
				
				char *newFK = NULL;

				newFK = (char*) malloc(strlen(sampleQuery->getAsString(i)->charrep()) + 1);
				newFK[0] = 0;
								
				strcpy(newFK, sampleQuery->getAsString(i)->charrep());
				
				key->setData(atoi(newFK));
				
				UAP(lb_I_KeyBase, key_FK_id, __FILE__, __LINE__)
				
				QI(key, lb_I_KeyBase, key_FK_id, __FILE__, __LINE__)
				
				UAP(lb_I_Unknown, uk_cbBoxPosition, __FILE__, __LINE__)
				UAP(lb_I_Integer, cbBoxPosition, __FILE__, __LINE__)
				
				int cbPos = 0;
				
				while (cbMapper->hasMoreElements() == 1) {
					UAP(lb_I_Integer, sel, __FILE__, __LINE__)
				        lb_I_Unknown* e = cbMapper->nextElement();
				        QI(e, lb_I_Integer, sel, __FILE__, __LINE__)
				        
				        if (sel->getData() == atoi(newFK)) {
				        	cbox->SetSelection(cbPos);
				        }
				        cbPos++;
				}
				
				if (newFK) {
				    free(newFK);
				    newFK = NULL;
				}
/*...e*/
			} else {
/*...sfill controls with data:32:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							wxCheckBox *check = (wxCheckBox*) w;
							
							if (sampleQuery->isNull(i)) {
								check->SetValue(false);
							} else {
								if (strcmp(sampleQuery->getAsString(i)->charrep(), "true") == 0) {
									printf("Read data for checkbox is true.\n");
									check->SetValue(true);
								} else {
									printf("Read data for checkbox is false.\n");
									check->SetValue(false);
								}
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(sampleQuery->getAsString(i)->charrep()));
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
					case lb_I_Query::lbDBColumnUnknown:
						break;
				}

/*...e*/
			}
		} else {
			_CL_VERBOSE << "Control '" << name << "' nicht gefunden." LOG_
		}
		
		free(name);
	}
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBFirst(lb_I_Unknown* uk) {
	lbDBUpdate();

	sampleQuery->first();

	lbDBRead();

	prevButton->Disable();
	firstButton->Disable();
	lastButton->Enable();
	nextButton->Enable();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBNext(lb_I_Unknown* uk) {
	lbDBUpdate();

	if (sampleQuery->next() == WARN_DB_NODATA) {
		nextButton->Disable();
		lastButton->Disable();
	}

	prevButton->Enable();
	firstButton->Enable();

	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBPrev(lb_I_Unknown* uk) {
	lbDBUpdate();

	if (sampleQuery->previous() == WARN_DB_NODATA) {
	        prevButton->Disable();
		firstButton->Disable();
	}

	nextButton->Enable();
	lastButton->Enable();
		
	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBLast(lb_I_Unknown* uk) {
	lbDBUpdate();

	sampleQuery->last();

	lbDBRead();

	nextButton->Disable();
	lastButton->Disable();
	firstButton->Enable();
	prevButton->Enable();
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBAdd(lb_I_Unknown* uk) {
	lbDBUpdate();

	lbDBClear();

	sampleQuery->add();

//	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBDelete(lb_I_Unknown* uk) {
	//lbDBUpdate();

	sampleQuery->remove();

	lbDBRead();

	return ERR_NONE;
}
/*...e*/

/*...slbDatabaseDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnDispatch(wxCommandEvent& event ) {
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
/*...slbDatabaseDialog\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/
/*...e*/

/*...slbPluginDatabaseDialog:0:*/
class lbPluginDatabaseDialog : public virtual lb_I_PluginImpl {
public:
	lbPluginDatabaseDialog();
	
	virtual ~lbPluginDatabaseDialog();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbForm, __FILE__, __LINE__)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseDialog)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseDialog, lbPluginDatabaseDialog)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseDialog::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl, __FILE__, __LINE__)
	QI(uk, lb_I_PluginImpl, pl, __FILE__, __LINE__)

	dbForm = pl->getImplementation();
*/

	_CL_LOG << "lbPluginDatabaseDialog::setData(...) called.\n" LOG_

	if (dbForm == NULL) {
		_CL_LOG << "ERROR: Cloning database form plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseDialog::lbPluginDatabaseDialog() {
	_CL_LOG << "lbPluginDatabaseDialog::lbPluginDatabaseDialog() called.\n" LOG_
	dbForm = NULL;
}

lbPluginDatabaseDialog::~lbPluginDatabaseDialog() {
	_CL_LOG << "lbPluginDatabaseDialog::~lbPluginDatabaseDialog() called.\n" LOG_
}

void LB_STDCALL lbPluginDatabaseDialog::initialize() {
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
	
		QI(dbDialog, lb_I_Unknown, dbForm, __FILE__, __LINE__)
	} else {
		_CL_LOG << "lbPluginDatabaseDialog::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return dbForm.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseDialog\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseDialog::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {

		_CL_LOG << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDatabaseDialog* dbDialog = new lbDatabaseDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbDialog, lb_I_Unknown, dbForm, __FILE__, __LINE__)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm == NULL;
	return r;
}
/*...e*/
/*...e*/
/*...e*/


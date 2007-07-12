/*...sLicense:0:*/
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

/*...sStandard includes:0:*/
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
/*...e*/

#include <lbConfigHook.h>
#include <lbInterfaces.h>

#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>

#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif

#include "wx/wizard.h"

#include <lbDatabaseForm.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbConfigure_FK_PK_MappingDialog)
END_IMPLEMENT_LB_UNKNOWN()

lbConfigure_FK_PK_MappingDialog::lbConfigure_FK_PK_MappingDialog() 
: wxDialog(NULL, -1, wxString(_T("lbConfigure_FK_PK_MappingDialog dialog")), wxDefaultPosition,
wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	ref = STARTREF;
	pass = 0;
}
lbConfigure_FK_PK_MappingDialog::~lbConfigure_FK_PK_MappingDialog() {

	if (_DBUser) free(_DBUser);
	if (_DBPass) free(_DBPass);
	if (_DBName) free(_DBName);

}
lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbConfigure_FK_PK_MappingDialog::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnFKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected( wxCommandEvent &event ) {
	wxString s = cBoxFKNames->GetStringSelection();
	
	cBoxFKNames->Disable();
	
	UAP(lb_I_String, PKTable)
	
	PKTable = sourceQuery->getPKTable(s.c_str());
	
	char buf[] = "select * from %s";
	char* buffer = (char*) malloc(strlen(buf)+strlen(PKTable->charrep())+1);
	sprintf(buffer, buf, PKTable->charrep());
	
	UAP_REQUEST(manager.getPtr(), lb_I_Database, queryDB)
	
	queryDB->init();
	
	queryDB->connect(_DBName, _DBName, _DBUser, _DBPass);
	
	UAP(lb_I_Query, sampleQuery)
	
	sampleQuery = queryDB->getQuery(_DBName, 0);

	sampleQuery->query(buffer);
	
	for (int i = 1; i <= sampleQuery->getColumns(); i++) {
		char* name = sampleQuery->getColumnName(i);
		cBoxPKNames->Append(wxString(name));
	}
	
	cBoxPKNames->Enable();
	cBoxPKNames->SetSelection(-1);
}
/*...e*/
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnPKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected( wxCommandEvent &event ) {
	wxString PKName = cBoxPKNames->GetStringSelection();
	wxString FKName = cBoxFKNames->GetStringSelection();

	REQUEST(manager.getPtr(), lb_I_Database, database)
	
	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_String, PKTable)
	
	char* fkTable = strdup(sourceQuery->getTableName((char*) FKName.c_str()));
	
	char* p = strdup(FKName.c_str());
	
	PKTable = sourceQuery->getPKTable(p);
	
	free(p);
	
	// Delete the entry, we now will put into the configuration
	
	cBoxFKNames->Delete(cBoxFKNames->GetSelection());
	
	UAP(lb_I_Query, query)
	
	char buf[] = "insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) values('%s','%s', '%s', '%s')";

	int size = strlen(buf)+	PKName.Length()+ strlen(fkTable)+ FKName.Length()+ strlen(PKTable->charrep())+ 1;

	char* buffer = (char*) malloc(size);

	buffer[0] = 0;

	sprintf(buffer, buf, FKName.c_str(), fkTable, PKName.c_str(), PKTable->charrep());

	query = database->getQuery("lbDMF", 0);
	
	query->skipFKCollecting();
	query->query(buffer);
	query->enableFKCollecting();
	
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

	this->Connect( cBoxFKNames->GetId(),  -1, wxEVT_COMMAND_CHOICE_SELECTED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected);

	this->Connect( cBoxPKNames->GetId(),  -1, wxEVT_COMMAND_CHOICE_SELECTED, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected);
/*
	this->Connect( cBoxFKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_ENTER, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected);

	this->Connect( cBoxPKNames->GetId(),  -1, wxEVT_COMMAND_TEXT_ENTER, 
		(wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) 
			&lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected);
*/
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
/*...svoid LB_STDCALL lbConfigure_FK_PK_MappingDialog\58\\58\init\40\lb_I_Query\42\ query\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbConfigure_FK_PK_MappingDialog::init(lb_I_Query* query, char* DBName, char* DBUser, char* DBPass) {
	lbErrCodes err = ERR_NONE;
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	_DBName = strdup(DBName);
	_DBUser = strdup(DBUser);
	_DBPass = strdup(DBPass);

	QI(query, lb_I_Query, sourceQuery)
	
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);

	sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
	sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);

	label = new wxStaticText(this, -1, "Dropdown Element:", wxPoint());
	sizerLeft->Add(label, 1, wxALL, 5);

	cBoxFKNames = new wxChoice(this, -1);
	sizerLeft->Add(cBoxFKNames, 1, wxALL, 5);

	labelF = new wxStaticText(this, -1, "Feld anzuzeigen:", wxPoint());
	sizerRight->Add(labelF, 1, wxALL, 5);
	
	cBoxPKNames = new wxChoice(this, -1);
	sizerRight->Add(cBoxPKNames, 1, wxALL, 5);

	int SelectedColumn = prepareDialogHandler();

	cBoxPKNames->Disable();

	for (int i = 1; i <= query->getColumns(); i++) {
		char* name = query->getColumnName(i);
		
		if (query->hasFKColumn(name) == 1) {
			cBoxFKNames->Append(wxString(name));
		}
	}

	cBoxFKNames->SetSelection(-1);

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

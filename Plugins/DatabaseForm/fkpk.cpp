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
            Ginsterweg 4
            
            65760 Eschborn (germany)
*/
/*...e*/

/*...sStandard includes:0:*/
#include <lbDMF_wxPrec.h>

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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
/*...e*/

#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>

#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

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

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <lbDatabaseForm.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbConfigure_FK_PK_MappingDialog)
END_IMPLEMENT_LB_UNKNOWN()

lbConfigure_FK_PK_MappingDialog::lbConfigure_FK_PK_MappingDialog() 
: wxDialog(NULL, -1, wxString(_T("lbConfigure_FK_PK_MappingDialog dialog")), wxDefaultPosition,
wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	
	
	;
	pass = 0;
	_FoimularID = -1; 
	_DBUser = NULL;
	_DBPass = NULL;
	_DBName = NULL;
	firstButton = NULL;
	cBoxFKNames = NULL;
	cBoxPKNames = NULL;
	label = NULL;
	labelF = NULL;
}

lbConfigure_FK_PK_MappingDialog::lbConfigure_FK_PK_MappingDialog(lb_I_Formulars* _forms, lb_I_Formular_Fields* _fields) 
: wxDialog(NULL, -1, wxString(_T("lbConfigure_FK_PK_MappingDialog dialog")), wxDefaultPosition,
wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	
	
	;
	pass = 0;
	_FoimularID = _forms->get_id(); 
	_DBUser = NULL;
	_DBPass = NULL;
	_DBName = NULL;
	forms = _forms;
	forms++;
	formularfields = _fields;
	formularfields++;
	firstButton = NULL;
	cBoxFKNames = NULL;
	cBoxPKNames = NULL;
	label = NULL;
	labelF = NULL;
}

lbConfigure_FK_PK_MappingDialog::~lbConfigure_FK_PK_MappingDialog() {
        if (_DBUser != NULL) free(_DBUser);
        if (_DBPass != NULL) free(_DBPass);
        if (_DBName != NULL) free(_DBName);
        sourceQuery.resetPtr(); // Propably a reference count problem 
}

lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbConfigure_FK_PK_MappingDialog::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}

bool LB_STDCALL lbConfigure_FK_PK_MappingDialog::haveNotMappedForeignKeyFields(const char* formName, const char* tableName, const char* fieldName) {
	bool definitionFound = false;
	bool formFound = false;
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, FID)
	UAP(lb_I_SecurityProvider, securityManager)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
	ID->setData(securityManager->getApplicationID());
	
	forms->finishFormularsIteration();
	while (forms->hasMoreFormulars()) {
		forms->setNextFormulars();
		FID->setData(forms->get_anwendungid());
		
		if (FID->equals(*&ID)) {
			if (strcmp(formName, forms->get_name()) == 0) {
				forms->finishFormularsIteration();
				formFound = true;
				_LOG << "Found formular name in datamodel." LOG_
				break;
			}
		}
	}
	
	if (formFound == false) {
		_LOG << "Didn't not found formular name for application " << ID->getData() << " in datamodel. (" << formName << ")" LOG_
	}
	
	long FormID = forms->get_id();
	
	formularfields->finishFormular_FieldsIteration();
	while (formularfields->hasMoreFormular_Fields()) {
		formularfields->setNextFormular_Fields();
		
		if (formularfields->get_formularid() == FormID) {
			if (strcmp(formularfields->get_name(), fieldName) == 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, fkt)
				UAP_REQUEST(getModuleInstance(), lb_I_String, fkn)
				
				*fkt = formularfields->get_fktable();
				*fkn = formularfields->get_fkname();
				
				if ((*fkt == "") || (*fkn == "")) break; // Not really a definition, because the *required* fields are empty.
				
				definitionFound = true;
				formularfields->finishFormular_FieldsIteration();
				break;
			}
		}
	}
	return definitionFound;
}

/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnFKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnFKComboBoxSelected( wxCommandEvent &event ) {
        lbErrCodes err = ERR_NONE;
        wxString s = cBoxFKNames->GetStringSelection();
        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

        cBoxFKNames->Disable();
        
        UAP(lb_I_String, PKTable)
        
        PKTable = sourceQuery->getPKTable(s.c_str());
        
        char buf[] = "select * from \"%s\"";
        char* buffer = (char*) malloc(strlen(buf)+strlen(PKTable->charrep())+1);
        sprintf(buffer, buf, PKTable->charrep());
        
        UAP(lb_I_Database, queryDB)
        char* dbbackend = meta->getApplicationDatabaseBackend();

        if (strcmp(_DBName, "lbDMF") == 0) {
                dbbackend = meta->getSystemDatabaseBackend();
        }
        
        if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
                UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
                AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, queryDB, "'database plugin'")
                _LOG << "Using plugin database backend for UML import operation..." LOG_
        } else {
                // Use built in
                REQUEST(getModuleInstance(), lb_I_Database, queryDB)
                _LOG << "Using built in database backend for UML import operation..." LOG_
        }

        if (queryDB == NULL) {
                _LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
                return;
        }
        
        queryDB->init();
        
        queryDB->connect(_DBName, _DBName, _DBUser, _DBPass);
        
        UAP(lb_I_Query, sampleQuery)
        
        sampleQuery = queryDB->getQuery(_DBName, 0);

        sampleQuery->query(buffer);
        
        for (int i = 1; i <= sampleQuery->getColumns(); i++) {
                UAP(lb_I_String, name)
                name = sampleQuery->getColumnName(i);
                cBoxPKNames->Append(wxString(name->charrep()));
        }
        
        if (sampleQuery->getColumns() == 0) {
                _LOG << "Error: Should have got some columns from the query: " << buffer LOG_
        }
        
        sampleQuery->close();
        
        free(buffer);
        
        cBoxPKNames->Enable();
        cBoxPKNames->SetSelection(-1);
}
/*...e*/
/*...svoid lbConfigure_FK_PK_MappingDialog\58\\58\OnPKComboBoxSelected\40\ wxCommandEvent \38\event \41\:0:*/
void lbConfigure_FK_PK_MappingDialog::OnPKComboBoxSelected( wxCommandEvent &event ) {
        lbErrCodes err = ERR_NONE;
        wxString PKName = cBoxPKNames->GetStringSelection();
        wxString FKName = cBoxFKNames->GetStringSelection();

        UAP(lb_I_Formular_Fields, formularfields)
        UAP(lb_I_Unknown, uk)

        UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
        UAP_REQUEST(getModuleInstance(), lb_I_String, param)
        
        UAP(lb_I_Unknown, ukDoc)
        UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

        UAP(lb_I_Unknown, ukParams)
        UAP(lb_I_Parameter, params)

        ukParams = meta->getActiveDocument();
        QI(ukParams, lb_I_Parameter, params)

        *param = "ApplicationData";
        document->setCloning(false);
        params->getUAPContainer(*&param, *&document);   

        UAP_REQUEST(getModuleInstance(), lb_I_String, name)

        UAP(lb_I_KeyBase, key)
        QI(name, lb_I_KeyBase, key)
                        
                        
        *name = "FormularFields";
        uk = document->getElement(&key);
        QI(uk, lb_I_Formular_Fields, formularfields)


        if (formularfields != NULL) {			
                UAP(lb_I_String, PKTable)
                UAP_REQUEST(getModuleInstance(), lb_I_String, fkName)
                UAP_REQUEST(getModuleInstance(), lb_I_String, fkTable)
                UAP_REQUEST(getModuleInstance(), lb_I_String, PKN)

                *fkName = FKName.c_str();
                *PKN = PKName.c_str();
                *fkTable = sourceQuery->getTableName((char*) FKName.c_str());

                lb_I_Query::lbDBColumnTypes coltype = sourceQuery->getColumnType(fkName->charrep());

                
                char* p = strdup(FKName.c_str());
                PKTable = sourceQuery->getPKTable(p);
                free(p);

                switch (coltype) {
                        case lb_I_Query::lbDBColumnBit: // Force replace
								_LOG << "Save the visible column into the internal object model. (" << fkName->charrep() << " in " << fkTable->charrep() << " to " << PKN->charrep() << " in " << PKTable->charrep() << ")" LOG_
                                formularfields->addFormular_Fields(fkName->charrep(), fkTable->charrep(), "Bit", true, PKN->charrep(), PKTable->charrep(), _FoimularID, -2);
                                break;
                        case lb_I_Query::lbDBColumnFloat:
								_LOG << "Save the visible column into the internal object model. (" << fkName->charrep() << " in " << fkTable->charrep() << " to " << PKN->charrep() << " in " << PKTable->charrep() << ")" LOG_
                                formularfields->addFormular_Fields(fkName->charrep(), fkTable->charrep(), "Float", true, PKN->charrep(), PKTable->charrep(), _FoimularID, -2);
                                break;
                        case lb_I_Query::lbDBColumnChar:
								_LOG << "Save the visible column into the internal object model. (" << fkName->charrep() << " in " << fkTable->charrep() << " to " << PKN->charrep() << " in " << PKTable->charrep() << ")" LOG_
                                formularfields->addFormular_Fields(fkName->charrep(), fkTable->charrep(), "String", true, PKN->charrep(), PKTable->charrep(), _FoimularID, -2);
                                break;
                        case lb_I_Query::lbDBColumnBinary:
								_LOG << "Save the visible column into the internal object model. (" << fkName->charrep() << " in " << fkTable->charrep() << " to " << PKN->charrep() << " in " << PKTable->charrep() << ")" LOG_
                                formularfields->addFormular_Fields(fkName->charrep(), fkTable->charrep(), "Binary", true, PKN->charrep(), PKTable->charrep(), _FoimularID, -2);
                                break;
                                
                        case lb_I_Query::lbDBColumnBigInteger:
                        case lb_I_Query::lbDBColumnInteger:
								_LOG << "Save the visible column into the internal object model. (" << fkName->charrep() << " in " << fkTable->charrep() << " to " << PKN->charrep() << " in " << PKTable->charrep() << ")" LOG_
                                formularfields->addFormular_Fields(fkName->charrep(), fkTable->charrep(), "Integer", true, PKN->charrep(), PKTable->charrep(), _FoimularID, -2);
                                break;
                        case lb_I_Query::lbDBColumnUnknown:
                                _CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
                                break;
                }
                cBoxFKNames->Delete(cBoxFKNames->GetSelection());
        }
        
        // Always add the field to the database. The datamodel didn't put it back to the database yet.
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
                _LOGERROR << "Error: Could not load database backend, either plugin or built in version." LOG_
                return;
        }
        
        database->init();
        
        const char* lbDMFPasswd = getenv("lbDMFPasswd");
        const char* lbDMFUser   = getenv("lbDMFUser");
        
        if (!lbDMFUser) lbDMFUser = "dba";
        if (!lbDMFPasswd) lbDMFPasswd = "trainres";
        
        database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
        
        UAP(lb_I_String, PKTable)
        UAP(lb_I_String, T)
                
        T = sourceQuery->getTableName((char*) FKName.c_str());
        char* fkTable = strdup(T->charrep());
        
        char* p = strdup(FKName.c_str());
        
        PKTable = sourceQuery->getPKTable(p);
        
        free(p);
        
        // Delete the entry, we now will put into the configuration
        
        cBoxFKNames->Delete(cBoxFKNames->GetSelection());
        
        UAP(lb_I_Query, query)
                
        const char* buf;
        if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
                buf = "--Skip Rewrite\ninsert into \"foreignkey_visibledata_mapping\" (\"fkname\", \"fktable\", \"pkname\", \"pktable\") values('%s','%s', '%s', '%s')";
        } else {
                buf = "insert into ForeignKey_VisibleData_Mapping (FKName, FKTable, PKName, PKTable) values('%s','%s', '%s', '%s')";
        }
        
        int size = strlen(buf)+ PKName.Length()+ strlen(fkTable)+ FKName.Length()+ strlen(PKTable->charrep())+ 1;
        
        char* buffer = (char*) malloc(size);
        
        buffer[0] = 0;
        
        sprintf(buffer, buf, FKName.c_str(), fkTable, PKName.c_str(), PKTable->charrep());
        
        sourceQuery->close();
        database->close();

        query = database->getQuery("lbDMF", 0);
        
        query->skipFKCollecting();
		_LOG << "Also save the visible column into the databse. (" << FKName.c_str() << " in " << fkTable << " to " << PKName.c_str() << " in " << PKTable->charrep() << ")" LOG_
		if (query->query(buffer) != ERR_NONE) {
			_LOG << "Saving the visible column into the databse failed!" LOG_
		}
        query->enableFKCollecting();
        query->close();

        database->close();
        
        
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
		free(fkTable);
}
/*...e*/

void LB_STDCALL lbConfigure_FK_PK_MappingDialog::windowIsClosing(lb_I_Window* w) {
}

lbErrCodes LB_STDCALL lbConfigure_FK_PK_MappingDialog::selectedColumn(lb_I_Unknown* uk) {
        EndModal(wxID_OK);

        return ERR_NONE;
}

/*...sint lbConfigure_FK_PK_MappingDialog\58\\58\prepareDialogHandler\40\\41\:0:*/
int lbConfigure_FK_PK_MappingDialog::prepareDialogHandler() {
        int SelectedColumn;
        int cbFKSel;
        int cbPKSel;
        
        UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
        UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

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

lb_I_Unknown* LB_STDCALL lbConfigure_FK_PK_MappingDialog::getUnknown() {
        lb_I_Unknown* ukp;
        queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
        return ukp;
}


/*...svoid LB_STDCALL lbConfigure_FK_PK_MappingDialog\58\\58\init\40\lb_I_Query\42\ query\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbConfigure_FK_PK_MappingDialog::init(lb_I_Query* query, const char* DBName, const char* DBUser, const char* DBPass) {
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
                UAP(lb_I_String, name)
                name = query->getColumnName(i);
                UAP(lb_I_String, tName)
                tName = query->getTableName(name->charrep());
                
                if (query->hasFKColumn(name->charrep()) == 1 && !haveNotMappedForeignKeyFields(forms->get_name(), tName->charrep(), name->charrep())) {
                        cBoxFKNames->Append(wxString(name->charrep()));
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

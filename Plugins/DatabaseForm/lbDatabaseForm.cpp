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

void LB_STDCALL lbOwnerDrawControl::init(lb_I_Window* parent) {
	lbDatabaseDialog* p = (lbDatabaseDialog*) parent;
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

/*...slbAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbAction)
	ADD_INTERFACE(lb_I_Action)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbAction, lbAction)

lbErrCodes LB_STDCALL lbAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbAction::lbAction() {
	ref = STARTREF;
	myActionID = NULL;
}

lbAction::~lbAction() {
	free(myActionID);
}

void LB_STDCALL lbAction::setActionID(char* id) {
	_CL_LOG << "lbAction::setActionID('" << id << "')" LOG_
	
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}

void LB_STDCALL lbAction::execute() {
	_CL_LOG << "lbAction::execute()" LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query, __FILE__, __LINE__)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery(0);	
	
	char buf[] = "select type from action_steps where actionid = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);
	
	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, type)
			
			type = query->getAsString(1);
			
			printf("Have an action step of type: %s\n", type->charrep());
			err = query->next();
		}
		
		if (err == WARN_DB_NODATA) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, type)
			
			type = query->getAsString(1);
			
			printf("Have an action step of type: %s\n", type->charrep());
		}
	}
}
/*...e*/

/*...slbDatabaseDialog:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
        ADD_INTERFACE(lb_I_DatabaseForm)
        ADD_INTERFACE(lb_I_DatabaseMasterForm)
        ADD_INTERFACE(lb_I_DatabaseDetailForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseDialog, lbDatabaseDialog)


/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDatabaseDialog::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseDialog\58\\58\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::lbDatabaseDialog() 
	: wxDialog(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_VERBOSE << "lbDatabaseDialog::lbDatabaseDialog() called." LOG_
	ref = STARTREF;
	formName = strdup("Database dialog");
}
/*...e*/
/*...slbDatabaseDialog\58\\58\\126\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::~lbDatabaseDialog() {
	_CL_LOG << "lbDatabaseDialog::~lbDatabaseDialog() called." LOG_

	if (detailForms == NULL) return;

	while (detailForms->hasMoreElements()) {
		lbErrCodes err = ERR_NONE;
				
		lb_I_Unknown* form = detailForms->nextElement();

		if (!form) continue;

		UAP(lb_I_DatabaseForm, d, __FILE__, __LINE__)		
		QI(form, lb_I_DatabaseForm, d, __FILE__, __LINE__)
		
		/* Really needed here !
		 * The wxWidgets system doesn't have a or at least has it's own reference counting system.
		 *
		 * So here I must ensure, that the object it self doesn't get deleted in the container.
		 * wxWidgets should call the destructor of the form.
		 */
		 
		d++;
		 
		d->destroy();
	}
}
/*...e*/

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


	if (detailForms == NULL) {
		// Create the instance for my detail formulars, if any.
		REQUEST(manager.getPtr(), lb_I_Container, detailForms)

		// Forbid autodeletion.
		detailForms->detachAll();
	}

	SetTitle(_trans(formName));

/* Tests the combo box and shows the difference between Linux and Windows
	testComboBox* t = new testComboBox();

	t->ShowModal();
*/
/*...sSizers:8:*/
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* sizerHor   = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerAddRem = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerNavi  = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizerActions = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* sizerLeft  = new wxBoxSizer(wxVERTICAL);	
	wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);
/*...e*/

/*...sDatabase connection and the stuff:8:*/
	REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();
	database->connect(DBName, DBUser, DBPass);

	sampleQuery = database->getQuery(0);
/*...e*/
		
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

	if (SQLString == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLString)
		SQLString->setData(_SQLString);
	}
	
	sampleQuery->query(SQLString->charrep(), false);

_CL_LOG << "Get new instance of FormularFieldInformation." LOG_
	
/*...sDetermine readonly fields:8:*/
	FFI = new FormularFieldInformation(formName, sampleQuery.getPtr());

_CL_LOG << "Got the new instance." LOG_

	int columns = sampleQuery->getColumns();

	for (int co = 1; co <= columns; co++) {
		char* name = NULL;
		name = strdup(sampleQuery->getColumnName(co));
		
		if (FFI->isReadonly(name)) {
		        sampleQuery->setUpdateable(name);
		}
		
		free(name);
	}
/*...e*/

	sampleQuery->bind();

	sampleQuery->first();
	
/*...screate database form elements:8:*/
	REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapperList)

	for(int i = 1; i <= columns; i++) {
		char* name = NULL;

		bool createdControl = false;

		UAP(lb_I_Query, FKColumnQuery, __FILE__, __LINE__)
		UAP(lb_I_Query, FKColumnQuery1, __FILE__, __LINE__)
		
		name = strdup(sampleQuery->getColumnName(i));

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

			UAP_REQUEST(manager.getPtr(), lb_I_Database, db)
			db->init();

			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");

			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			db->connect("lbDMF", lbDMFUser, lbDMFPasswd);

			FKColumnQuery = db->getQuery(0);
			
			FKColumnQuery->query(buffer);
			
			err = FKColumnQuery->first();
			
			if (err == ERR_DB_NODATA) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
			
	
				lbConfigure_FK_PK_MappingDialog* fkpkDialog = new lbConfigure_FK_PK_MappingDialog();
				
				fkpkDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				
				fkpkDialog->init(database.getPtr(), sampleQuery.getPtr());
				
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
			if (FFI->isSpecialColumn(name)) {
/*...sCreate controls based on configuration in a database:40:*/
				printf("Creating a special control. (%s)\n", FFI->getControlType(name));

				lbOwnerDrawControl *ownerdraw = new lbOwnerDrawControl();
				ownerdraw->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				ownerdraw->init(this);
				
				ownerdraw->SetName(name);
				
				sizerRight->Add(ownerdraw, 1, 0, 5);

				if (FFI->isReadonly(name)) {
				        ownerdraw->Disable();
				}

				createdControl = true;
/*...e*/
			} else {
/*...sCreate controls based on database type:40:*/
			lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

			switch (coltype) {
				case lb_I_Query::lbDBColumnBit:
					{
						printf("Creating a checkbox control.\n");
						
						wxCheckBox *check = new wxCheckBox(this, -1, 
							"", wxPoint());
						check->SetName(name);
						sizerRight->Add(check, 1, wxEXPAND | wxALL, 5);	

						if (FFI->isReadonly(name)) {
						        check->Disable();
						}

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnChar:
					{
						_CL_LOG << "Create text control for '" << name << "'" LOG_
						wxTextCtrl *text = new wxTextCtrl(this, -1, 
							sampleQuery->getAsString(i)->charrep(), wxPoint());
						text->SetName(name);
						sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name)) {
							text->Disable();
						}

						createdControl = true;
					}
					break;
					
				case lb_I_Query::lbDBColumnBinary:
					break;

				case lb_I_Query::lbDBColumnInteger:
					{
						wxTextCtrl *text = new wxTextCtrl(this, -1,
						        sampleQuery->getAsString(i)->charrep(), wxPoint());
					        text->SetName(name);
					        sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name)) {
 							text->Disable();
						}

					        createdControl = true;
					}
					break;
				case lb_I_Query::lbDBColumnUnknown:
					_CL_LOG << "lbDatabaseDialog::init(...) Creating control failed due to unknown column type" LOG_
					break;
			}
/*...e*/
			}
		}
		
		if (createdControl) {
			char* tLabel = new char[strlen(name) + 1];
		
			tLabel[0] = 0;
		
			tLabel = strcat(tLabel, name); 
		
			wxStaticText *label = new wxStaticText(this, -1, _trans(tLabel), wxPoint());
			sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
			
			delete [] tLabel;
		}	
		
		free(name);
	}
/*...e*/

	sizerHor->Add(sizerLeft, 1, wxEXPAND | wxALL, 5);
	sizerHor->Add(sizerRight, 1, wxEXPAND | wxALL, 5);

	wxButton *button1 = new wxButton(this, DatabaseFirst, _trans("First")); //, wxPoint(), wxSize(100,20));
	wxButton *button2 = new wxButton(this, DatabasePrev, _trans("Prev")); //, wxPoint(), wxSize(100,20));
	wxButton *button3 = new wxButton(this, DatabaseNext, _trans("Next")); //, wxPoint(), wxSize(100,20));
	wxButton *button4 = new wxButton(this, DatabaseLast, _trans("Last")); //, wxPoint(), wxSize(100,20));

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

	wxButton *buttonAdd = new wxButton(this, DatabaseAdd, _trans("Add")); //, wxPoint(), wxSize(100,20));
	wxButton *buttonDelete = new wxButton(this, DatabaseDelete, _trans("Delete")); //, wxPoint(), wxSize(100,20));


	sizerAddRem->Add(buttonAdd, 1, wxEXPAND | wxALL, 5);
	sizerAddRem->Add(buttonDelete, 1, wxEXPAND | wxALL, 5);

/*...sAction handler initializion:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_Database, actionsDatabase)

	actionsDatabase->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	actionsDatabase->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, actionQuery, __FILE__, __LINE__)
	
	actionQuery = actionsDatabase->getQuery(0);

	char *_actionquery = "select actions.name, formular_actions.event from actions "
			     "inner join formular_actions on actions.id = formular_actions.action "
			     "inner join formulare on formular_actions.formular = formulare.id "
			     "where formulare.name = '%s'";

	char *buf = (char*) malloc(strlen(_actionquery) + strlen(formName) + 1);
	buf[0] = 0;
	
	sprintf(buf, _actionquery, formName);
	
	actionQuery->query(buf);
	lbErrCodes err = actionQuery->first();
	
/*...sloop through and find actions:16:*/
	while (err == ERR_NONE) {
		UAP(lb_I_String, action, __FILE__, __LINE__)
		UAP(lb_I_String, actionWhat, __FILE__, __LINE__)
		
		action = actionQuery->getAsString(1);
		actionWhat = actionQuery->getAsString(2);

		actionWhat->trim();

		int actionID = 0;
		
		char *eventName = (char*) malloc(strlen(actionWhat->charrep()) + 20);
		
		sprintf(eventName, "%p(%s)", this, actionWhat->charrep());
		
		eman->registerEvent(eventName, actionID);
		
		wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));
		
		dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::OnActionButton, eventName);
		
		this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
		        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
	
		sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);

		free(eventName);

		err = actionQuery->next();
	}
/*...e*/
/*...sget last action:16:*/
	if (err == WARN_DB_NODATA) {
		UAP(lb_I_String, action, __FILE__, __LINE__)
		UAP(lb_I_String, actionWhat, __FILE__, __LINE__)
		
		action = actionQuery->getAsString(1);
		actionWhat = actionQuery->getAsString(2);

		actionWhat->trim();

		int actionID = 0;
		
		char *eventName = (char*) malloc(strlen(actionWhat->charrep()) + 20);
		
		sprintf(eventName, "%p(%s)", this, actionWhat->charrep());

		eman->registerEvent(eventName, actionID);
		
		wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));

		dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::OnActionButton, eventName);
		
		this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
		        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabaseDialog::OnDispatch);
		
		sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);
		
		free(eventName);
	
	}
/*...e*/
/*...e*/


/*...sconnect event handlers:8:*/
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
/*...e*/


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

char* LB_STDCALL lbDatabaseDialog::getQuery() {
	return SQLString->charrep();
}

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setMasterForm\40\lb_I_DatabaseMasterForm\42\ master\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setMasterForm(lb_I_DatabaseMasterForm* master) {
	
	// Now build the where clause that sets the foreign key columns of this form as equal condition to the values of the masters pk columns.
	
	_master = master;
	
	updateFromMaster();
}
/*...e*/

/*...sconst char\42\ LB_STDCALL lbDatabaseDialog\58\\58\getControlValue\40\char\42\ name\41\:0:*/
const char* LB_STDCALL lbDatabaseDialog::getControlValue(char* name) {

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

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabaseDialog::updateFromMaster() {

	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	
	// Using the new = and += operators of the string interface. Note: If used in an UAP, explizit 'dereferencing' must be used.
	*newWhereClause = " where ";
	
	for (int i = 0; i < _master->getMasterColumns()-1; i++) {
		UAP(lb_I_String, colName, __FILE__, __LINE__)
		colName = _master->getMasterColumn(i);
		
		*newWhereClause += *&colName;
		bool isChar = _master->isCharacterColumn(i); 

		if (isChar) 
			*newWhereClause += " = '";
		else
			*newWhereClause += " = ";

		*newWhereClause += _master->getControlValue(colName->charrep());
			
		if (isChar) *newWhereClause += "'";
	}
	
	_CL_LOG << "lbDatabaseDialog::updateFromMaster() generated new where clause: '" << newWhereClause->charrep() << "'" LOG_
}
/*...e*/

void LB_STDCALL lbDatabaseDialog::setFilter(char* filter) {
	if (SQLWhere == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLWhere)
		if (filter != NULL) SQLWhere->setData(filter);
	}
}

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
				if (FFI->isSpecialColumn(name)) {
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
					
					case lb_I_Query::lbDBColumnInteger:
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

		_CL_VERBOSE << "Update column " << name LOG_

		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name), this);

		if (w != NULL) {
		
			_CL_VERBOSE << "Have a control to be updated" LOG_
		
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
				if (FFI->isSpecialColumn(name)) {
					_CL_LOG << "lbDatabaseDialog::lbDBUpdate() updates special column" LOG_
				} else {
/*...sUpdate controls:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							if (!FFI->isReadonly(name)) {
								wxCheckBox *check = (wxCheckBox*) w;
								if (check->GetValue() == TRUE) {
									wxString v = "true";
									col->setData(name);
									val->setData(v.c_str());
							
									_CL_LOG << "Update column '" << name << "' with true" LOG_	
									sampleQuery->setString(*&col, *&val);
								} else {
									wxString v = "false";
									col->setData(name);
									val->setData(v.c_str());
								
									_CL_LOG << "Update column '" << name << "' with false" LOG_	
									sampleQuery->setString(*&col, *&val);
								}
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							if (!FFI->isReadonly(name)) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name);
								val->setData(v.c_str());

								sampleQuery->setString(*&col, *&val);
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnInteger:
						{
							if (!FFI->isReadonly(name)) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name);
								val->setData(v.c_str());

								sampleQuery->setString(*&col, *&val);
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
			_CL_VERBOSE << "Control '" << name << "' nicht gefunden." LOG_
		}
		
		_CL_VERBOSE << "Updated column " << name LOG_
		free(name);
	}

	_CL_VERBOSE << "Call sampleQuery->update()" LOG_

	if (sampleQuery->update() != ERR_NONE) {
		printf("sampleQuery->update() failed.\n");
		return ERR_UPDATE_FAILED;
	}
	
	_CL_VERBOSE << "Called sampleQuery->update()" LOG_
	
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
				if (FFI->isSpecialColumn(name)) {
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
								if (strcmp(sampleQuery->getAsString(i)->charrep(), "true") == 0) {
									printf("Read data for checkbox is true.\n");
									check->SetValue(true);
								} else {
									printf("Read data for checkbox is false.\n");
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
						break;
				}

/*...e*/
				}
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

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::OnActionButton(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbDatabaseDialog::OnActionButton(...) called" LOG_

/*...sDoc:8:*/
	/*
		An action button event may need some additional data to proceed.
		If a user presses, for sample, 'reserve a trip' in a customer form,
		the action will need the customer number to be added to the event,
		that would be generated.
		
		So, for this sample I need the field that must be forwarded as additional
		data.
		
		The 'action' is 'Reserve a trip', having a target with id = 1 and 
		bezeichnung = 'Customer want to reserve a trip'.
		
		So the Button has the text 'Reserve a trip' and maybe have a help text of
		'Customer want to reserve a trip'.
		
		To get the source data field for that action, I will need the action_steps.id field.
		ID would be retrieved in two steps. The retrival is implemented in FormularActions class.
	 */
/*...e*/

	if (uk != NULL) {
		_CL_LOG << "OnActionButton parameter given." LOG_
		
		char* reversedEvent = NULL;
		
/*...sReverse the event ID:16:*/
		/* The parameter is the id of the event, that has been emitted.
		   Resolve the name of that id. */
		
		UAP(lb_I_Integer, eventID, __FILE__, __LINE__)
		QI(uk, lb_I_Integer, eventID, __FILE__, __LINE__)
		
		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		
		char* eventName = (char*) strdup(eman->reverseEvent(eventID->getData()));
		
		/*
		  This event name has a prefix of the pointer for the instance of the form.
		  
		  That pointer must be removed in any way, before I can get other data from
		  the configuration database.
		 */

		reversedEvent = strdup(strtok(eventName, "("));

		free(reversedEvent);

		reversedEvent = strdup(strtok(NULL, ")"));
	
/*...e*/

		// Regarding to the event name, we must get back some information from the database.

		FormularActions fa;

		char* s = fa.getActionSourceDataField(reversedEvent);

		/*
		  Now I can get the data from the source field and put it into the event parameters.
		 */

		wxWindow* w = FindWindowByName(wxString(s), this);
		
		wxString value;
		
/*...sGet the content:16:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(s);

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
		
		_CL_LOG << "Have these event: " << reversedEvent << "." LOG_		
		_CL_LOG << "Have got source field: " << s << "." LOG_
		_CL_LOG << "The value for the field is " << value.c_str() << "." LOG_		

/*...sShema doc for actions:16:*/
		/*
		   The current database shema has no entry for an event to be used
		   as a forwardable event. So here I suggest to add a prefix to the
		   event name that is configured and routed to here.
		   
		   A handler then could be a plugin similar to the plugin version of the
		   login wizard.
		   
		   The remaining problem would be the initializion of the configuration data.
		   
		   The plugin must take care about all the configuration data it needs to be
		   called. It also must know, from where the events can occur.
		   
		   In the case of a type 1 action - eg Buttonpress, the what field contains only
		   an event identifer. To be able to forward the event, the plugin must provide
		   a handler for it.
		   
		   I suggest as prefix the type of the action. In the case of Buttonpress their ID 1.
		   
		   In the case of a type 2 event - eg. a 'Dynamic detail form' event ID = 2, the 'what'
		   field does not contain only the event name that would be routed to here.
		   
		   It also contains the information about the form to open. As in the mailto b.allgaier@...,
		   I have defined a sample for opening a form:

		   
			Data fields:
		
				'Aktion Name' char(20)
				'Aktion Typ' int 		-> 	'ActionTypes':'id'
									'ActionTypes':'Bezeichnung'
				'Action Source Data' char(20) (Eigentlich die Kunden ID)
				'Action Target' int		->	'ActionTarget':'id'
									'ActionTarget':'Bezeichnung'
									'ActionTarget':'A_Order_Nr'
									'ActionTarget':'What'

			Sample that issues an event handler in a plugin:

				'Reserve a trip'
				'1' int		 		-> 	'AktionTypes':'1'
									'AktionTypes':'Buttonpress'

				'kundennr'	(The customer id, not the ID of the row)
				'1' int				->	'ActionTarget':'1'
									'ActionTarget':'Customer want to reserve a trip'
									'ActionTarget':'1'
									'ActionTarget':'evt_Reserve_Customer_Trip'

			Sample that opens a detail formular:

				'Reserved trips ...'
				'2' int		 		-> 	'AktionTypes':'2'
									'AktionTypes':'Dynamic detail form'

				'kundennr'	(The customer id, not the ID of the row)
				'1' int				->	'ActionTarget':'1'
									'ActionTarget':'Overview of the customers trips'
									'ActionTarget':'1'
									'ActionTarget':'OpenForm:TripsOverview'

		*/
/*...e*/

		// Try to abstract the action.

		UAP(lb_I_Action, action, __FILE__, __LINE__)
		
		action = fa.getAction(fa.getActionID(reversedEvent));

		action->execute();

		_CL_LOG << "Action has been executed." LOG_

#ifdef bla
/*...sCreate the detail form:16:*/
		UAP(lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
	
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
		UAP_REQUEST(getModuleManager(), lb_I_String, fName)
		fName->setData(detailFormName);
	
		QI(fName, lb_I_KeyBase, key, __FILE__, __LINE__)
	
		uk = detailForms->getElement(&key);	
	
		if (uk != NULL) {
			QI(uk, lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
		}

		if ((_dialog.getPtr() != NULL) && (strcmp(queryString, _dialog->getQuery()) != 0)) {
	
			// SQL query from database has been changed. Recreate the dialog from scratch. 
	
			detailForms->remove(&key);
		
			_dialog->destroy();
	
			_dialog.resetPtr();
		}

		if (_dialog.getPtr() == NULL) {
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
		
			detailForms->insert(&uk, &key);
		
			UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)
			QI(uk, lb_I_DatabaseForm, form, __FILE__, __LINE__)
		
			form->destroy();
			form = NULL;
		
			uk = forms->getElement(&key);
		
			if (uk != NULL) {
			        QI(uk, lb_I_DatabaseForm, _dialog, __FILE__, __LINE__)
			}
		
			_dialog->setName(formName);
			
			_dialog->init(queryString, DBName, DBUser, DBPass);
		
		}

		_dialog->show();
/*...e*/
#endif
		free(s);
		
		free(eventName);
		
	}


	return ERR_NONE;
}
/*...e*/

/*...svoid \9\\9\  lbDatabaseDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
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
/*...svoid\9\\9\  lbDatabaseDialog\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/

int LB_STDCALL lbDatabaseDialog::getMasterColumns()
{
	return 0;
}
	
lb_I_String* LB_STDCALL lbDatabaseDialog::getMasterColumn(int pos)
{
	return NULL;
}
	   
bool LB_STDCALL lbDatabaseDialog::isCharacterColumn(int pos)
{
	return false;
}
/*...e*/

/*...sclass lbPluginDatabaseDialog implementation:0:*/
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
	
		QI(dbDialog, lb_I_Unknown, dbForm, __FILE__, __LINE__)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm == NULL;
	return r;
}
/*...e*/
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
                	_CL_VERBOSE << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
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

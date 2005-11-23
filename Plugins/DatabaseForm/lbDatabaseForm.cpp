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

	void LB_STDCALL create(int parentId) { }
	int  LB_STDCALL getId() { return GetId(); }

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
	_CL_LOG << "lbAction::~lbAction() called." LOG_
	if (actions != NULL) {
		_CL_LOG << "Have " << actions->Count() << " elements in action list." LOG_
		actions->deleteAll();
	}
	_CL_LOG << "Deleted all delegation actions." LOG_
}

/*...svoid LB_STDCALL lbAction\58\\58\setActionID\40\char\42\ id\41\:0:*/
void LB_STDCALL lbAction::setActionID(char* id) {
	
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}
/*...e*/

/*...svoid LB_STDCALL lbAction\58\\58\delegate\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::delegate(lb_I_Parameter* params) {
	/*
		Resolve the parameters that we need here.
		Currently only the id of the action step.
	 */

	UAP_REQUEST(manager.getPtr(), lb_I_String, id)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	if (actions == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, actions)
	}

	parameter->setData("id");
	params->getUAPString(*&parameter, *&id);

	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	query = db->getQuery(0);
	
	char buf[] = "select action_handler, module from action_types inner join action_steps on action_types.id = action_steps.type where action_steps.id = %s";
	
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, id->charrep());

	if (query->query(q) == ERR_NONE) {
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(manager.getPtr(), lb_I_String, key)
		UAP(lb_I_KeyBase, ukey, __FILE__, __LINE__)

		err = query->first();
	
		while (err == ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
			UAP_REQUEST(manager.getPtr(), lb_I_String, module)
			UAP(lb_I_DelegatedAction, action, __FILE__, __LINE__)
			
			action_handler = query->getAsString(1);
			module = query->getAsString(2);
			action_handler->trim();
			module->trim();

			key->setData(module->charrep());
			*key += *&action_handler;
			
			QI(key, lb_I_KeyBase, ukey, __FILE__, __LINE__)
			
			if (actions->exists(&ukey) == 0) {
/*...sInstanciate one and insert into actions:32:*/
				char* pluginDir = getenv("PLUGIN_DIR");
				if (pluginDir == NULL) {
					_LOG << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
					pluginDir = (char*) malloc(strlen(getenv("HOME"))+strlen("/plugins")+1);
					pluginDir[0] = 0;
					strcat(pluginDir, getenv("HOME"));
					strcat(pluginDir, "/plugins");
				} else {
					pluginDir = strdup(pluginDir);
				}
				

/*...sbuild PREFIX:64:*/
#ifndef LINUX
        #ifdef __WATCOMC__
        #define PREFIX "_"
        #endif
        #ifdef _MSC_VER
        #define PREFIX ""
        #endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
/*...e*/

/*...sBuild up pluginModule:64:*/
			        char* pluginModule = new char[strlen(pluginDir)+strlen(module->charrep())+2];
			        pluginModule[0] = 0;
			        strcat(pluginModule, pluginDir);
			#ifdef WINDOWS
			        strcat(pluginModule, "\\");
			#endif
			#ifdef LINUX
			        strcat(pluginModule, "/");
			#endif
			#ifdef OSX
			        strcat(pluginModule, "/");
			#endif
			        strcat(pluginModule, module->charrep());
/*...e*/
	
				UAP(lb_I_Unknown, result, __FILE__, __LINE__)
			
				char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
				ah[0] = 0;
			
				strcat(ah, PREFIX);
				strcat(ah, action_handler->charrep());
			
				if (manager->makeInstance(ah, module->charrep(), &result) != ERR_NONE) {
					if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						_CL_LOG << "ERROR: Configured module '" << pluginModule << "' could not be loaded." LOG_
					}
				}
			
				result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
				actions->insert(&result, &ukey);
/*...e*/
			}
			
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
				
			uk = actions->getElement(&ukey);
				
			QI(uk, lb_I_DelegatedAction, action, __FILE__, __LINE__)
			
			action->setActionID(id->charrep());
			action->execute(*&params);
			
			_CL_LOG << "References for delegated action are " << action->getRefCount() << "." LOG_
			
			err = query->next();
		}
		
		if (err == WARN_DB_NODATA) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
			UAP_REQUEST(manager.getPtr(), lb_I_String, module)
			UAP(lb_I_DelegatedAction, action, __FILE__, __LINE__)
			
			action_handler = query->getAsString(1);
			module = query->getAsString(2);
			action_handler->trim();
			module->trim();

			key->setData(module->charrep());
			*key += *&action_handler;
			
			QI(key, lb_I_KeyBase, ukey, __FILE__, __LINE__)
			
			if (actions->exists(&ukey) == 0) {
/*...sInstanciate one and insert into actions:32:*/
				char* pluginDir = getenv("PLUGIN_DIR");
				if (pluginDir == NULL) {
					_LOG << "ERROR: No plugin directory configured. Try fallback. Please create one and set environment PLUGIN_DIR properly." LOG_
					pluginDir = (char*) malloc(strlen(getenv("HOME"))+strlen("/plugins")+1);
					pluginDir[0] = 0;
					strcat(pluginDir, getenv("HOME"));
					strcat(pluginDir, "/plugins");
				} else {
					pluginDir = strdup(pluginDir);
				}
				
/*...sbuild PREFIX:64:*/
#ifndef LINUX
        #ifdef __WATCOMC__
        #define PREFIX "_"
        #endif
        #ifdef _MSC_VER
        #define PREFIX ""
        #endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
/*...e*/

/*...sBuild up pluginModule:64:*/
			        char* pluginModule = new char[strlen(pluginDir)+strlen(module->charrep())+2];
			        pluginModule[0] = 0;
			        strcat(pluginModule, pluginDir);
			#ifdef WINDOWS
			        strcat(pluginModule, "\\");
			#endif
			#ifdef LINUX
			        strcat(pluginModule, "/");
			#endif
			#ifdef OSX
			        strcat(pluginModule, "/");
			#endif
			        strcat(pluginModule, module->charrep());
/*...e*/
	
				UAP(lb_I_Unknown, result, __FILE__, __LINE__)
			
				char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
				ah[0] = 0;
			
				strcat(ah, PREFIX);
				strcat(ah, action_handler->charrep());
			
				if (manager->makeInstance(ah, module->charrep(), &result) != ERR_NONE) {
					if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						_CL_LOG << "ERROR: Configured module '" << pluginModule << "' could not be loaded." LOG_
					}
				}
			
				result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
				actions->insert(&result, &ukey);
/*...e*/
			}
			
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
				
			uk = actions->getElement(&ukey);
				
			QI(uk, lb_I_DelegatedAction, action, __FILE__, __LINE__)
			action->setActionID(id->charrep());
			
			_CL_LOG << "Execute delegated action..." LOG_
						
			action->execute(*&params);
		}
	}
}
/*...e*/

/*...svoid LB_STDCALL lbAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::execute(lb_I_Parameter* params) {
	REQUEST(manager.getPtr(), lb_I_Database, db)
	UAP(lb_I_Query, query, __FILE__, __LINE__)

	db->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	db->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	query = db->getQuery(0);	
	
	char buf[] = "select id from action_steps where actionid = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, id)
			
			id = query->getAsString(1);
			
			parameter->setData("id");
			params->setUAPString(*&parameter, *&id);
			
			delegate(*&params);
			
			err = query->next();
		}
		
		if (err == WARN_DB_NODATA) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, id)
			
			id = query->getAsString(1);
			
			parameter->setData("id");
			params->setUAPString(*&parameter, *&id);
			
			delegate(*&params);
		}
	}
}
/*...e*/
/*...e*/

/*...slbDetailFormAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDetailFormAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDetailFormAction, lbDetailFormAction)

lbErrCodes LB_STDCALL lbDetailFormAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDetailFormAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbDetailFormAction::lbDetailFormAction() {
	ref = STARTREF;
	myActionID = NULL;
	detailForm = NULL;
}

lbDetailFormAction::~lbDetailFormAction() {
	free(myActionID);

// lb_I_GUI implementation does this from now
//	if (detailForm != NULL) { 
//	    detailForm->destroy();
//	}
}

void LB_STDCALL lbDetailFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDetailFormAction::setActionID(char* id) {
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}

/*...svoid LB_STDCALL lbDetailFormAction\58\\58\openDetailForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDetailFormAction::openDetailForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;

	if (detailForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_
	
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&masterForm);
		
		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		detailForm->setName(formularname->charrep(), parameter->charrep());

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui, __FILE__, __LINE__)
		
		meta->getGUI(&gui);

		lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		detailForm->setMasterForm(f, *&params);
		
		detailForm->updateFromMaster();
		gui->showForm(formularname->charrep());	
	} else {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui, __FILE__, __LINE__)
	
		meta->getGUI(&gui);

		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

		parameter->setData("DBName");
		params->getUAPString(*&parameter, *&DBName);
		parameter->setData("DBUser");
		params->getUAPString(*&parameter, *&DBUser);
		parameter->setData("DBPass");
		params->getUAPString(*&parameter, *&DBPass);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&masterForm);
	//	parameter->setData("source field");
	//	params->getUAPString(*&parameter, *&SourceFieldName);
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("application");
		params->getUAPString(*&parameter, *&app);

		//lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

/*...sGet the SQL query based on formular name\44\ application name\46\:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_String, user)
		meta->getUserName(&user);		

		char* b =
		        "select Formulare.id from Formulare inner join Anwendungen_Formulare on "
		        "Formulare.id = Anwendungen_Formulare.formularid "
		        "inner join Anwendungen on Anwendungen_Formulare.anwendungid = Anwendungen.id inner join "
		        "User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		        " User_Anwendungen.userid = Users.id where "
		        "Users.userid = '%s' and Anwendungen.name = '%s' and "
		        "Formulare.name = '%s'";

		char* buffer = (char*) malloc(strlen(b)+
						strlen(user->charrep())+
						strlen(app->charrep())+
						strlen(formularname->charrep())+1);
		
		buffer[0] = 0;
		
		sprintf(buffer, b, user->charrep(), app->charrep(), formularname->charrep());
		
		UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
		UAP(lb_I_Query, query, __FILE__, __LINE__)
		
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
		
		query = database->getQuery(0);
/*...e*/

		if (query->query(buffer) == ERR_NONE) {
			lbErrCodes err = query->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, id)
				
/*...sPrepare query to get parameter value based on given ID:32:*/
				id = query->getAsString(1);
				
				char* b = "select parametervalue from formular_parameters where formularid = %s";

				char* buffer = (char*) malloc(strlen(b)+strlen(id->charrep())+1);
				buffer[0] = 0;
				sprintf(buffer, b, id->charrep());

				UAP(lb_I_Query, query, __FILE__, __LINE__)

				query = database->getQuery(0);

				err = query->query(buffer);
/*...e*/
				
				if (err == ERR_NONE) {
/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl, __FILE__, __LINE__)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();
					
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
						
						sql = query->getAsString(1);

						UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)

						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui, __FILE__, __LINE__)
						meta->getGUI(&gui);
						
						form = gui->createDBForm(formularname->charrep(),
									sql->charrep(),
									DBName->charrep(), 
									DBUser->charrep(), 
									DBPass->charrep());
						detailForm = form.getPtr();

						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						
						form->setName(formularname->charrep(), parameter->charrep());

/*...sDocs:136:*/
						/* Set the other information of master / detail form here
						
						   There is a problem for forms, if the foreign key is not
						   shown in it. In that case the relation could not full filled
						   by the add action.
						   
						   The only way may be any kind of temporal default value.
						*/
/*...e*/
						
						UAP(lb_I_DatabaseForm, f, __FILE__, __LINE__)
						UAP(lb_I_DatabaseForm, master, __FILE__, __LINE__)

						f = gui->findDBForm(masterForm->charrep());

						if (f == NULL) {
							_CL_LOG << "Error: Bail out, no master form found." LOG_
							return; 
						}

						QI(f, lb_I_DatabaseForm, master, __FILE__, __LINE__)						
						
						UAP_REQUEST(manager.getPtr(), lb_I_String, table)
						
						master->getPrimaryColumns();
						
						*table = master->getTableName(master->getColumnName(1));
						
						form->ignoreForeignKeys(table->charrep());
						
						//form->init(sql->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());
						
						form->setMasterForm(*&master, *&params);
						
/*...e*/
						
/*...sSome docs:88:*/
/*
 * What should I do to 'interconnect' the forms over the
 * relation 'customer number' ?
 *
 * lbDetailFormAction could manage these information and
 * control the form class over the existing interface.
 *
 * These are the setFilter and setMasterForm functions.
 *
 * With these functions, it is possible to only show data,
 * that is related to both, the master form and detail form
 * data.
 *
 * setFilter could set the following value:
 *
 * " where customerid = 
 *     (select id from <table of masterForm> where <SourceFieldName> = '<SourceFieldValue>')"
 */
/*...e*/
						
						// Get the related table for the source field
						
						gui->showForm(formularname->charrep());
						form++;
					}
/*...e*/
				} else {
					_CL_LOG << "ERROR: Expected query for the formular ID failed:\n" << buffer LOG_
				}
			}
		}
	}
}
/*...e*/

/*...svoid LB_STDCALL lbDetailFormAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDetailFormAction::execute(lb_I_Parameter* params) {
/*...sInit variables for params:8:*/
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
/*...e*/

	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query, __FILE__, __LINE__)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery(0);	
	
	char buf[] = "select what from action_steps where id = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();

			openDetailForm(*&what, *&params);
			
			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();
			
			openDetailForm(*&what, *&params);
/*...e*/
		}
	}
}
/*...e*/
/*...e*/
/*...slbMasterFormAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbMasterFormAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbMasterFormAction, lbMasterFormAction)

lbErrCodes LB_STDCALL lbMasterFormAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbMasterFormAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbMasterFormAction::lbMasterFormAction() {
	ref = STARTREF;
	myActionID = NULL;
	masterForm = NULL;
}

lbMasterFormAction::~lbMasterFormAction() {
	free(myActionID);

// lb_I_GUI implementation does this from now
//	if (masterForm != NULL) { 
//	    masterForm->destroy();
//	}
}

void LB_STDCALL lbMasterFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbMasterFormAction::setActionID(char* id) {
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}

/*...svoid LB_STDCALL lbMasterFormAction\58\\58\openMasterForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbMasterFormAction::openMasterForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;

	if (masterForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_
	
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&detailForm);

		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		masterForm->setName(formularname->charrep(), parameter->charrep());
				
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui, __FILE__, __LINE__)
		
		meta->getGUI(&gui);

		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

		masterForm->setDetailForm(f, *&params);
		
		masterForm->updateFromDetail();
		gui->showForm(formularname->charrep());
	} else {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui, __FILE__, __LINE__)
	
		meta->getGUI(&gui);
	

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&detailForm);
//	parameter->setData("source field");
//	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("application");
	params->getUAPString(*&parameter, *&app);

		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

/*...sGet the SQL query based on formular name\44\ application name\46\:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_String, user)
		meta->getUserName(&user);		

		char* b =
		        "select Formulare.id from Formulare inner join Anwendungen_Formulare on "
		        "Formulare.id = Anwendungen_Formulare.formularid "
		        "inner join Anwendungen on Anwendungen_Formulare.anwendungid = Anwendungen.id inner join "
		        "User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		        " User_Anwendungen.userid = Users.id where "
		        "Users.userid = '%s' and Anwendungen.name = '%s' and "
		        "Formulare.name = '%s'";

		char* buffer = (char*) malloc(strlen(b)+
						strlen(user->charrep())+
						strlen(app->charrep())+
						strlen(formularname->charrep())+1);
		
		buffer[0] = 0;
		
		sprintf(buffer, b, user->charrep(), app->charrep(), formularname->charrep());
		
		UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
		UAP(lb_I_Query, query, __FILE__, __LINE__)
		
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
		
		query = database->getQuery(0);
/*...e*/

		if (query->query(buffer) == ERR_NONE) {
			lbErrCodes err = query->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, id)
				
/*...sPrepare query to get parameter value based on given ID:32:*/
				id = query->getAsString(1);
				
				char* b = "select parametervalue from formular_parameters where formularid = %s";

				char* buffer = (char*) malloc(strlen(b)+strlen(id->charrep())+1);
				buffer[0] = 0;
				sprintf(buffer, b, id->charrep());

				UAP(lb_I_Query, query, __FILE__, __LINE__)

				query = database->getQuery(0);

				err = query->query(buffer);
/*...e*/
				
				if (err == ERR_NONE) {
/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl, __FILE__, __LINE__)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();
					
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
						
						sql = query->getAsString(1);
						
						UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)
						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui, __FILE__, __LINE__)

						meta->getGUI(&gui);

						form = gui->createDBForm(formularname->charrep(),
					                        sql->charrep(),
		                                                DBName->charrep(),
                                                                DBUser->charrep(),
                                                                DBPass->charrep());

                                                masterForm = form.getPtr();

						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						
						form->setName(formularname->charrep(), parameter->charrep());

						/* Set the other information of master / detail form here
						
						   There is a problem for forms, if the foreign key is not
						   shown in it. In that case the relation could not full filled
						   by the add action.
						   
						   The only way may be any kind of temporal default value.
						*/
						
						UAP(lb_I_DatabaseForm, f, __FILE__, __LINE__)

						UAP(lb_I_DatabaseForm, detail, __FILE__, __LINE__)

						f = gui->findDBForm(detailForm->charrep());

						QI(f, lb_I_DatabaseForm, detail, __FILE__, __LINE__)						
						
						UAP_REQUEST(manager.getPtr(), lb_I_String, table)
						
						detail->getPrimaryColumns();
						
						*table = detail->getTableName(detail->getColumnName(1));
						
						form->ignoreForeignKeys(table->charrep());
						
						//form->init(sql->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());
						
						form->setDetailForm(*&detail, *&params);
/*...e*/
						
/*...sSome docs:88:*/
/*
 * What should I do to 'interconnect' the forms over the
 * relation 'customer number' ?
 *
 * lbMasterFormAction could manage these information and
 * control the form class over the existing interface.
 *
 * These are the setFilter and setMasterForm functions.
 *
 * With these functions, it is possible to only show data,
 * that is related to both, the master form and detail form
 * data.
 *
 * setFilter could set the following value:
 *
 * " where customerid = 
 *     (select id from <table of masterForm> where <SourceFieldName> = '<SourceFieldValue>')"
 */
/*...e*/
						
						// Get the related table for the source field
						
						gui->showForm(formularname->charrep());
						form++;
					}
/*...e*/
				} else {
					_CL_LOG << "ERROR: Expected query for the formular ID failed:\n" << buffer LOG_
				}
			}
		}
	}
}
/*...e*/

/*...svoid LB_STDCALL lbMasterFormAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbMasterFormAction::execute(lb_I_Parameter* params) {
/*...sInit variables for params:8:*/
	if (masterForm == NULL) {
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
/*...e*/

	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query, __FILE__, __LINE__)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery(0);	
	
	char buf[] = "select what from action_steps where id = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();

			openMasterForm(*&what, *&params);
			
			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();

			openMasterForm(*&what, *&params);
/*...e*/
		}
	}
}
/*...e*/
/*...e*/
/*...slbSQLQueryAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbSQLQueryAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbSQLQueryAction, lbSQLQueryAction)

lbErrCodes LB_STDCALL lbSQLQueryAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbSQLQueryAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbSQLQueryAction::lbSQLQueryAction() {
	ref = STARTREF;
	myActionID = NULL;
}

lbSQLQueryAction::~lbSQLQueryAction() {
	free(myActionID);
}

void LB_STDCALL lbSQLQueryAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbSQLQueryAction::setActionID(char* id) {
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}

void LB_STDCALL lbSQLQueryAction::execute(lb_I_Parameter* params) {
	_CL_LOG << "lbSQLQueryAction::execute()" LOG_
	
}
/*...e*/

/*...slbDatabasePanel:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabasePanel)
        ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabasePanel, lbDatabasePanel)


/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE << "lbDatabasePanel::setData(...) not implemented yet" LOG_

		UAP(lb_I_DatabaseForm, dbForm, __FILE__, __LINE__)
		QI(uk, lb_I_DatabaseForm, dbForm, __FILE__, __LINE__)
		
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

void LB_STDCALL lbDatabasePanel::create(int parentId) {
	wxWindow* w = FindWindowById(parentId);
	
	Create(w, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panel");
	SetFocus();
	_created = true;
}

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
	
	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabasePanel\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabasePanel::init(char* _SQLString, char* DBName, char* DBUser, char* DBPass) {
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	// Activate relative memory access counts
	//TRMemStartLocalCount();

	if (ignoredPKTables == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, ignoredPKTables)
	}

	SetTitle(formName);

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
	if (database != NULL) {
		_CL_LOG << "WARNING: Database instance available!" LOG_
	}
	
	REQUEST(manager.getPtr(), lb_I_Database, database)

	database->init();
	database->connect(DBName, DBUser, DBPass);

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

/*...sDetermine readonly fields:8:*/
	if (FFI != NULL) delete FFI;
	
	FFI = new FormularFieldInformation(formName, sampleQuery.getPtr());

	int columns = sampleQuery->getColumns();

	for (int co = 1; co <= columns; co++) {
		char* name = NULL;
		name = strdup(sampleQuery->getColumnName(co));

		if (FFI->isReadonly(name)) {
		        sampleQuery->setReadonly(name);
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

		bool hideThisColumn = false;

		if (sampleQuery->hasFKColumn(name) == 1) {
/*...sCreate a combobox:32:*/
			lbErrCodes err = ERR_NONE;

			// Create a mapping instance for this combo box
			UAP_REQUEST(manager.getPtr(), lb_I_Container, _ComboboxMapper)
			UAP_REQUEST(manager.getPtr(), lb_I_Container, ComboboxMapper)

			UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
			UAP(lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
			
			QI(cbName, lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
			QI(_ComboboxMapper, lb_I_Unknown, uk_ComboboxMapper, __FILE__, __LINE__)

			// This is the input parameter

			cbName->setData(name);
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, table)
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
			UAP(lb_I_String, t, __FILE__, __LINE__)
	
			t = sampleQuery->getPKTable(name);
	
			table->setData(t->charrep());
	
			QI(table, lb_I_KeyBase, key, __FILE__, __LINE__)
	
			if (ignoredPKTables->exists(&key) == 1) hideThisColumn = true;
			
			ComboboxMapperList->insert(&uk_ComboboxMapper, &key_cbName);

			ukComboboxMapper = ComboboxMapperList->getElement(&key_cbName);
			
			QI(ukComboboxMapper, lb_I_Container, ComboboxMapper, __FILE__, __LINE__)
			
			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;
			
/*...sGet column to display instead key:56:*/
			sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
					"where FKName = '%s' and FKTable = '%s'", name, sampleQuery->getTableName(name));

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
/*...e*/
			
			//UAP_REQUEST(manager.getPtr(), lb_I_String, VColumn)
			
			/// \todo Define this function in my data model
			//VColumn = data_model->getVisualColumnName(name, sampleQuery);
			
			// ------------------
			
			if (err == ERR_DB_NODATA) {
				_CL_VERBOSE << "ERROR: No data column definition to be displayed instead of primary key.\n" LOG_
			
	
				lbConfigure_FK_PK_MappingDialog* fkpkPanel = new lbConfigure_FK_PK_MappingDialog();
				
				fkpkPanel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
				
				fkpkPanel->init(database.getPtr(), sampleQuery.getPtr());
				
				fkpkPanel->show();
				
				fkpkPanel->destroy();

				FKColumnQuery1 = FKColumnQuery.getPtr();
			
				FKColumnQuery.resetPtr();

				FKColumnQuery = db->getQuery(0);

				FKColumnQuery->query(buffer);

				err = FKColumnQuery->first();
			}

			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sHave mapping to visible data for the combobox:64:*/
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKName)
				UAP_REQUEST(manager.getPtr(), lb_I_String, PKTable)
				UAP(lb_I_String, s, __FILE__, __LINE__)
				
				
				PKName = FKColumnQuery->getAsString(1);
				PKTable = FKColumnQuery->getAsString(2);
					
				wxChoice *cbox = new wxChoice(this, -1);
				cbox->SetName(name);
				
				s = sampleQuery->getAsString(i);
				
				int old_fk = atoi(s->charrep());
				
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
					
					data->trim();
					
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
						UAP_REQUEST(manager.getPtr(), lb_I_String, possible_fk)
						UAP(lb_I_Unknown, uk_possible_fk, __FILE__, __LINE__)
						UAP(lb_I_KeyBase, key_cbox_pos, __FILE__, __LINE__)
						
						DBerr = ReplacementColumnQuery->next();
						
						data = ReplacementColumnQuery->getAsString(1);
						
						data->trim();
						
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
				
				if (hideThisColumn == false) sizerRight->Add(cbox, 1, wxEXPAND | wxALL, 5);
				
				createdControl = true;
/*...e*/
			}

			free(buffer);
/*...e*/
		} else {
			if (FFI->isSpecialColumn(name)) {
/*...sCreate controls based on configuration in a database:40:*/
				//printf("Creating a special control. (%s)\n", FFI->getControlType(name));

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
						UAP(lb_I_String, s, __FILE__, __LINE__)
						
						s = sampleQuery->getAsString(i);
						
						wxTextCtrl *text = new wxTextCtrl(this, -1, s->charrep(), wxPoint());
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

				case lb_I_Query::lbDBColumnBigInteger:
				case lb_I_Query::lbDBColumnInteger:
					{
						UAP(lb_I_String, s, __FILE__, __LINE__)
						
						s = sampleQuery->getAsString(i);
					
						wxTextCtrl *text = new wxTextCtrl(this, -1, s->charrep(), wxPoint());
					        text->SetName(name);
					        sizerRight->Add(text, 1, wxEXPAND | wxALL, 5);
						
						if (FFI->isReadonly(name)) {
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
		
		if (createdControl) {
			char* tLabel = (char*) malloc(strlen(name) + 6);
		
			tLabel[0] = 0;
			
			tLabel = strcat(tLabel, name); 
						
			wxStaticText *label = new wxStaticText(this, -1, _trans(tLabel), wxPoint());

			tLabel = strcat(tLabel, "_lbl");
						
			label->SetName(_trans(tLabel));
			
			if (hideThisColumn == false) sizerLeft->Add(label, 1, wxEXPAND | wxALL, 5);
			
			free(tLabel);
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
/*
	UAP_REQUEST(manager.getPtr(), lb_I_Database, actionsDatabase)

	actionsDatabase->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	actionsDatabase->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, actionQuery, __FILE__, __LINE__)
	
	actionQuery = actionsDatabase->getQuery(0);

*/
	UAP(lb_I_Query, actionQuery, __FILE__, __LINE__)
	
	actionQuery = database->getQuery(0);


	char *_actionquery = "select actions.name, formular_actions.event from actions "
			     "inner join formular_actions on actions.id = formular_actions.action "
			     "inner join formulare on formular_actions.formular = formulare.id "
			     "where formulare.name = '%s'";

	char *buf = (char*) malloc(strlen(_actionquery) + strlen(base_formName) + 1);
	buf[0] = 0;
	
	sprintf(buf, _actionquery, base_formName);

	_CL_LOG << "Have action query: '" << buf << "'" LOG_ 

	actionQuery->skipFKCollecting();	
	actionQuery->query(buf);
	actionQuery->enableFKCollecting();
	free(buf);

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
		
		action->trim();
		
		wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));
		
		dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::OnActionButton, eventName);
		
		this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
		        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
	
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
		
		action->trim();
		
		wxButton *actionButton = new wxButton(this, actionID, _trans(action->charrep())); //, wxPoint(), wxSize(100,20));

		dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabasePanel::OnActionButton, eventName);
		
		this->Connect( actionID,  -1, wxEVT_COMMAND_BUTTON_CLICKED,
		        (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &lbDatabasePanel::OnDispatch);
		
		sizerActions->Add(actionButton, 1, wxEXPAND | wxALL, 5);
		
		free(eventName);
	
	}
/*...e*/
/*...e*/


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
char* LB_STDCALL lbDatabasePanel::getColumnName(int pos) {
	return sampleQuery->getColumnName(pos);
}
/*...e*/

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
	return getControlValue(getColumnName(pos));
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
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	
	string->setData(toTable);
	
	QI(string, lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(string, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	ignoredPKTables->insert(&uk, &key);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabasePanel::updateFromMaster() {

	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newMasterIDQuery)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)
	
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
/*...e*/

	masterForm->trim();
	SourceFieldName->trim();
	SourceFieldValue->trim();

	_CL_LOG << "Have master form '" << masterForm->charrep() << 
	           "', source field name '" << SourceFieldName->charrep() << 
	           "' and source field value '" << SourceFieldValue->charrep() <<
	           "' for detail form '" << formName << "'" LOG_


/*...sDetermine the primary key values of the current master entry\44\ based on the value of the \42\\38\SourceFieldName\46\:8:*/
	UAP(lb_I_String, colName, __FILE__, __LINE__)
	int columns = _master->getPrimaryColumns();
	bool isChar = _master->isCharacterColumn(SourceFieldName->charrep());
	
	for (int i = 1; i <= columns-1; i++) {
		colName = _master->getPrimaryColumn(i);
		
		*newMasterIDQuery += colName->charrep();
		*newMasterIDQuery += ", ";
	}

	colName = _master->getPrimaryColumn(columns);
		
	*newMasterIDQuery += colName->charrep();

	
	*newMasterIDQuery += " from ";
	*newMasterIDQuery += _master->getTableName(SourceFieldName->charrep());
	*newMasterIDQuery += " where ";
	*newMasterIDQuery += SourceFieldName->charrep();

	if (isChar) 
		*newMasterIDQuery += " = '";
	else
		*newMasterIDQuery += " = ";
	
	*newMasterIDQuery += SourceFieldValue->charrep();

	if (isChar) *newMasterIDQuery += "'";
/*...e*/
	
	_CL_LOG << "lbDatabasePanel::updateFromMaster() generated new master id query: \n'" <<
		newMasterIDQuery->charrep() << "'" LOG_

	if (MasterDetailRelationData == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, MasterDetailRelationData)
	}

/*...sRetrieve the values from the primary keys and build up the where clause to be used in detail form:8:*/
	REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, PKQuery, __FILE__, __LINE__)

	database->init();
	database->connect(DBName->charrep(), DBUser->charrep(), DBPass->charrep());

	PKQuery = database->getQuery(0);

	lbErrCodes err = PKQuery->query(newMasterIDQuery->charrep());

	if (err == ERR_NONE) {

		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_String, colValue, __FILE__, __LINE__)

		err = PKQuery->first();

		int columns = PKQuery->getColumns();


		while (err == ERR_NONE) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				*colName = PKQuery->getColumnName(i);
				colValue = PKQuery->getAsString(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
				fk = sampleQuery->getFKColumn(
						PKQuery->getTableName(colName->charrep()),
						colName->charrep()
						);
		
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

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}

/*...sBuild expression for last column:32:*/
			*colName = PKQuery->getColumnName(columns);
			colValue = PKQuery->getAsString(columns);
		
			bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
			UAP(lb_I_String, fk, __FILE__, __LINE__)
		
			fk = sampleQuery->getFKColumn(
					PKQuery->getTableName(colName->charrep()),
					colName->charrep()
					);
		
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

			UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
			UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
			QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
			QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

			MasterDetailRelationData->insert(&uk_colValue, &key_fk);
			_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			
			*newWhereClause += ") or ";
	
			err = PKQuery->next();
		}
		
		if (err == WARN_DB_NODATA) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				*colName = PKQuery->getColumnName(i);
				colValue = PKQuery->getAsString(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
				fk = sampleQuery->getFKColumn(
						PKQuery->getTableName(colName->charrep()),
						colName->charrep()
						);
		
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

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);
				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}
			
/*...sBuild expression for last column:32:*/
			*colName = PKQuery->getColumnName(columns);
			colValue = PKQuery->getAsString(columns);
		
			bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
			UAP(lb_I_String, fk, __FILE__, __LINE__)
		
			fk = sampleQuery->getFKColumn(
					PKQuery->getTableName(colName->charrep()),
					colName->charrep()
					);
		
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

			UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
			UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
			QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
			QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

			MasterDetailRelationData->insert(&uk_colValue, &key_fk);
			_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/

			*newWhereClause += ")";
		}

		Layout();		
		
		
	}
/*...e*/

	newQuery->setData(getQuery());
	
	*newQuery += newWhereClause->charrep();
	
	_CL_VERBOSE << "Have new query for detail form: '" << newQuery->charrep() << "'" LOG_
	
	sampleQuery = database->getQuery(0);

	sampleQuery->query(newQuery->charrep());

	if (lbDBFirst(NULL) == ERR_DB_NODATA) {
		// Assume no data available
		noDataAvailable = true;
		lbDBClear();
		noDataAvailable = false;	
	}
	
	SetTitle(formName);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\updateFromDetail\40\\41\:0:*/
void LB_STDCALL lbDatabasePanel::updateFromDetail() {
	UAP_REQUEST(manager.getPtr(), lb_I_String, newWhereClause)
	UAP_REQUEST(manager.getPtr(), lb_I_String, newMasterIDQuery)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)
	
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
/*...e*/

	detailForm->trim();
	SourceFieldName->trim();
	SourceFieldValue->trim();

	_CL_LOG << "Have detail form '" << detailForm->charrep() << 
	           "', source field name '" << SourceFieldName->charrep() << 
	           "' and source field value '" << SourceFieldValue->charrep() <<
	           "' for master form '" << formName << "'" LOG_


/*...sDetermine the foreign key values of the current detail entry\44\ based on the value of the \42\\38\SourceFieldName\46\:8:*/
	UAP(lb_I_String, colName, __FILE__, __LINE__)
	int columns = _detail->getForeignColumns();
	bool isChar = _detail->isCharacterColumn(SourceFieldName->charrep());
	
	char* sourceTable = strdup(_detail->getTableName(SourceFieldName->charrep()));
	
	for (int i = 1; i <= columns-1; i++) {
		colName = _detail->getForeignColumn(i);

		_CL_LOG << "lbDatabasePanel::updateFromDetail() creates query column '" << 
			colName->charrep() << "'" LOG_
		
		if (strcmp(sourceTable, _detail->getTableName(colName->charrep())) == 0) {
			*newMasterIDQuery += colName->charrep();
			*newMasterIDQuery += ", ";
		}
	}

	colName = _detail->getForeignColumn(columns);
		
	_CL_LOG << "lbDatabasePanel::updateFromDetail() creates query column '" <<
		colName->charrep() << "'" LOG_
		
	if (strcmp(sourceTable, _detail->getTableName(colName->charrep())) == 0) {
		*newMasterIDQuery += colName->charrep();
	}

	free(sourceTable);
	
	*newMasterIDQuery += " from ";
	*newMasterIDQuery += _detail->getTableName(SourceFieldName->charrep());
	*newMasterIDQuery += " where ";
	*newMasterIDQuery += SourceFieldName->charrep();

	if (isChar) 
		*newMasterIDQuery += " = '";
	else
		*newMasterIDQuery += " = ";
	
	*newMasterIDQuery += SourceFieldValue->charrep();

	if (isChar) *newMasterIDQuery += "'";
/*...e*/
	
	_CL_LOG << "lbDatabasePanel::updateFromDetail() generated new master id query: \n'" <<
		newMasterIDQuery->charrep() << "'" LOG_

	if (MasterDetailRelationData == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, MasterDetailRelationData)
	}

/*...sRetrieve the values from the primary keys and build up the where clause to be used in detail form:8:*/
	REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, PKQuery, __FILE__, __LINE__)

	database->init();
	database->connect(DBName->charrep(), DBUser->charrep(), DBPass->charrep());

	PKQuery = database->getQuery(0);

	lbErrCodes err = PKQuery->query(newMasterIDQuery->charrep());

	if (err == ERR_NONE) {

		UAP_REQUEST(manager.getPtr(), lb_I_String, colName)
		UAP(lb_I_String, colValue, __FILE__, __LINE__)

		err = PKQuery->first();

		int columns = PKQuery->getColumns();


		while (err == ERR_NONE) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				*colName = PKQuery->getColumnName(i);
				colValue = PKQuery->getAsString(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
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
			
				*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}

/*...sBuild expression for one column:32:*/
				*colName = PKQuery->getColumnName(columns);
				colValue = PKQuery->getAsString(columns);
		
				bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
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
			
				//*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			
			*newWhereClause += ") or ";
	
			err = PKQuery->next();
		}
		
		if (err == WARN_DB_NODATA) {
			*newWhereClause += "(";
			
			for (int i = 1; i <= columns-1; i++) {
/*...sBuild expression for one column:40:*/
				*colName = PKQuery->getColumnName(i);
				colValue = PKQuery->getAsString(i);
		
				bool isChar = PKQuery->getColumnType(i) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
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
			
				*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/
			}
			
/*...sBuild expression for one column:32:*/
				*colName = PKQuery->getColumnName(columns);
				colValue = PKQuery->getAsString(columns);
		
				bool isChar = PKQuery->getColumnType(columns) == lb_I_Query::lbDBColumnChar;
		
				UAP(lb_I_String, fk, __FILE__, __LINE__)
		
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
			
				//*newWhereClause += " and ";

				UAP(lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				UAP(lb_I_KeyBase, key_fk, __FILE__, __LINE__)
				
				QI(colValue, lb_I_Unknown, uk_colValue, __FILE__, __LINE__)
				QI(fk, lb_I_KeyBase, key_fk, __FILE__, __LINE__)

				MasterDetailRelationData->insert(&uk_colValue, &key_fk);

				_CL_VERBOSE << "Set control '" << fk->charrep() << "' to '" << colValue->charrep() << "'" LOG_
/*...e*/

			*newWhereClause += ")";
		}

		Layout();		

		
	}
/*...e*/

	newQuery->setData(getQuery());
	
	*newQuery += newWhereClause->charrep();
	
	_CL_LOG << "Have new query for detail form: '" << newQuery->charrep() << "'" LOG_
	
	sampleQuery = database->getQuery(0);

	sampleQuery->query(newQuery->charrep());

	if (lbDBFirst(NULL) == ERR_DB_NODATA) {
		// Assume no data available
		noDataAvailable = true;
		lbDBClear();
		noDataAvailable = false;	
	}
	
	SetTitle(formName);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabasePanel\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabasePanel::setFilter(char* filter) {
	if (SQLWhere == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SQLWhere)
	}

	if (filter != NULL) SQLWhere->setData(filter);
}
/*...e*/

/*...schar\42\ lbDatabasePanel\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
char* lbDatabasePanel::getTableName(char* columnName) {
	return sampleQuery->getTableName(columnName);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBClear() {
	int columns = sampleQuery->getColumns();

	for (int i = 1; i <= columns; i++) {
		char* name = strdup(sampleQuery->getColumnName(i));

		wxWindow* w = FindWindowByName(wxString(name), this);

		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name) == 1) {
/*...sUpdate drop down box:32:*/
				wxChoice* cbox = (wxChoice*) w;
				
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
			
					case lb_I_Query::lbDBColumnBigInteger:		
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
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBUpdate() {

	if (noDataAvailable) return ERR_NONE;

	SetTitle(formName);

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
				wxChoice* cbox = (wxChoice*) w;
				
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
					_CL_LOG << "lbDatabasePanel::lbDBUpdate() updates special column" LOG_
				} else {
/*...sUpdate controls:40:*/
				lb_I_Query::lbDBColumnTypes coltype = sampleQuery->getColumnType(i);

				switch (coltype) {
					case lb_I_Query::lbDBColumnBit:
						{
							if (!sampleQuery->getReadonly(name)) {
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
						}
						break;
					
					case lb_I_Query::lbDBColumnChar:
						{
							if (!sampleQuery->getReadonly(name)) {
								wxTextCtrl* tx = (wxTextCtrl*) w;
			
								wxString v = tx->GetValue();
			
								col->setData(name);
								val->setData(v.c_str());

								sampleQuery->setString(*&col, *&val);
							}
						}
						break;
					
					case lb_I_Query::lbDBColumnBigInteger:
					case lb_I_Query::lbDBColumnInteger:
						{
							if (!sampleQuery->getReadonly(name)) {
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
			_LOG << "Control '" << name << "' nicht gefunden." LOG_
		}
		
		free(name);
	}

	if (sampleQuery->update() != ERR_NONE) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

		newTitle->setData(formName);
		
		*newTitle += ": Update failed !";

		SetTitle(_trans(newTitle->charrep()));
		
		_LOG << "Update a database record failed." LOG_

		return ERR_UPDATE_FAILED;
	}
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBRead() {

	SetTitle(formName);

	int columns = sampleQuery->getColumns();
	
	for (int i = 1; i <= columns; i++) {
		char* name = strdup(sampleQuery->getColumnName(i));
		// Find the corresponding window
		
		wxWindow* w = FindWindowByName(wxString(name), this);
		
		if (w != NULL) {
			if (sampleQuery->hasFKColumn(name) == 1) {
/*...sfill combo box with data:32:*/
				wxChoice* cbox = (wxChoice*) w;
				
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
				
				if (count != 0) {
					char *newFK = NULL;
					UAP(lb_I_String, s, __FILE__, __LINE__)

					s = sampleQuery->getAsString(i);
	
					newFK = (char*) malloc(strlen(s->charrep()) + 1);
					newFK[0] = 0;
								
					strcpy(newFK, s->charrep());
				
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
								UAP(lb_I_String, s, __FILE__, __LINE__)
								
								s = sampleQuery->getAsString(i);
								
								if (strcmp(s->charrep(), "true") == 0) {
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
							UAP(lb_I_String, s, __FILE__, __LINE__)
							
							s = sampleQuery->getAsString(i);
							
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(s->charrep()));
						}
						break;
					
					case lb_I_Query::lbDBColumnBigInteger:
					case lb_I_Query::lbDBColumnInteger:
						{
							UAP(lb_I_String, s, __FILE__, __LINE__)
							
							s = sampleQuery->getAsString(i);
							
							wxTextCtrl* tx = (wxTextCtrl*) w;
							tx->SetValue(wxString(s->charrep()));
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

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBFirst(lb_I_Unknown* uk) {
	lbDBUpdate();

	if (sampleQuery->first() == ERR_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
		lastButton->Disable();
		nextButton->Disable();

		return ERR_DB_NODATA;
	}
	
	lbDBRead();

	prevButton->Disable();
	firstButton->Disable();
	lastButton->Enable();
	nextButton->Enable();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBNext(lb_I_Unknown* uk) {
	lbErrCodes err;
	lbDBUpdate();

	err = sampleQuery->next();
	
	if (err == WARN_DB_NODATA) {
		nextButton->Disable();
		lastButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
		return ERR_DB_NODATA;
	} else {
		prevButton->Enable();
		firstButton->Enable();
	}
	
	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBPrev(lb_I_Unknown* uk) {
	lbDBUpdate();
	lbErrCodes err;

	if ((err = sampleQuery->previous()) == WARN_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
	}

	if (err == ERR_DB_NODATA) {
		nextButton->Disable();
		lastButton->Disable();
		return ERR_DB_NODATA;
	} else {
		nextButton->Enable();
		lastButton->Enable();
	}

	lbDBRead();

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBLast(lb_I_Unknown* uk) {
	lbDBUpdate();

	if (sampleQuery->last() == ERR_DB_NODATA) {
		prevButton->Disable();
		firstButton->Disable();
		lastButton->Disable();
		nextButton->Disable();

		return ERR_DB_NODATA;
	}

	lbDBRead();

	nextButton->Disable();
	lastButton->Disable();
	firstButton->Enable();
	prevButton->Enable();
	
	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBAdd(lb_I_Unknown* uk) {
	
	_CL_LOG << "lbDatabasePanel::lbDBAdd() called." LOG_
/*	
	if (isAdding == true) {
		isAdding = false;
		if (noDataAvailable) {
			// Goto first data, because there was no data before.
			return lbDBFirst(NULL);
		}

			
		return lbDBLast(NULL);
	}

	isAdding = true;
*/
	lbDBUpdate();

	lbDBClear();

	//noDataAvailable = false;

	if (sampleQuery->add() != ERR_NONE) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)

		newTitle->setData(formName);
		
		*newTitle += ": Add failed !";

		SetTitle(_trans(newTitle->charrep()));
	}

/*...sPrefill data to hidden fields\46\ This would mostly be combo boxes\46\:8:*/
	if (MasterDetailRelationData != NULL) {
	
		_CL_VERBOSE << "Have " << MasterDetailRelationData->Count() << " elements in list." LOG_
	
		for (int i = 1; i <= MasterDetailRelationData->Count(); i++) {
			lbErrCodes err = ERR_NONE;
		
			UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
			UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
			
			UAP(lb_I_String, value, __FILE__, __LINE__)
			
			uk = MasterDetailRelationData->getElementAt(i);
			key = MasterDetailRelationData->getKeyAt(i);
			
			QI(uk, lb_I_String, value, __FILE__, __LINE__)
			
			_CL_VERBOSE << "Set control '" << key->charrep() << "' to '" << value->charrep() << "'" LOG_
			
			
			wxWindow* w = FindWindowByName(wxString(key->charrep()), this);
		
			if (w != NULL) {
				if (sampleQuery->hasFKColumn(key->charrep()) == 1) {
					_CL_VERBOSE << "Set dropdown control '" << 
						key->charrep() << 
						"' to '" << 
						value->charrep() << "'" LOG_
/*...sfill combo box with data:48:*/
				wxChoice* cbox = (wxChoice*) w;
				
				lbErrCodes err = ERR_NONE;

				UAP_REQUEST(manager.getPtr(), lb_I_Integer, key1)
				UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)

				cbName->setData(key->charrep());

				UAP(lb_I_KeyBase, key_cbName, __FILE__, __LINE__)
				UAP(lb_I_Unknown, uk_cbMapper, __FILE__, __LINE__)
				UAP(lb_I_Container, cbMapper, __FILE__, __LINE__)

				QI(cbName, lb_I_KeyBase, key_cbName, __FILE__, __LINE__)

				uk_cbMapper = ComboboxMapperList->getElement(&key_cbName);

				QI(uk_cbMapper, lb_I_Container, cbMapper, __FILE__, __LINE__)
				
				int count = cbMapper->Count();
				
				if (count != 0) {
					char *newFK = NULL;

					newFK = (char*) malloc(strlen(value->charrep()) + 1);
					newFK[0] = 0;
								
					strcpy(newFK, value->charrep());
				
					key1->setData(atoi(newFK));
				
					UAP(lb_I_KeyBase, key_FK_id, __FILE__, __LINE__)
				
					QI(key1, lb_I_KeyBase, key_FK_id, __FILE__, __LINE__)
				
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
						break;
				}

/*...e*/
					#endif
					}
				}
			} else {
			_CL_VERBOSE << "Control '" << key->charrep() << "' not found." LOG_
			}
		}
	}
/*...e*/

	if (lbDBUpdate() == ERR_UPDATE_FAILED) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newTitle)
		
		newTitle->setData(formName);
		
		*newTitle += ": Missing fields !";
		
		SetTitle(_trans(newTitle->charrep()));
		
		_CL_LOG << "Updating after add failed." LOG_
	} else {
		_CL_LOG << "Updating after add succeeded. Move to last." LOG_
		
		if (lbDBLast(NULL) != ERR_NONE) {
			_CL_LOG << "Move to last after updating failed." LOG_
			lbDBFirst(NULL);
		} else {
			_CL_LOG << "Move to last after updating succeeded." LOG_
		}
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::lbDBDelete(lb_I_Unknown* uk) {
	//lbDBUpdate();

	sampleQuery->remove();

	lbDBRead();

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabasePanel\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabasePanel::OnActionButton(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
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
		char* s = NULL;
		
/*...sResolve the related data for the action button \40\to be cached later\41\:16:*/
		char* reversedEvent = NULL;
//DebugBreak();		
/*...sReverse the event ID from given uk data:32:*/
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

		if (fa == NULL) fa = new FormularActions;	

		s = fa->getActionSourceDataField(reversedEvent);

		/*
		  Now I can get the data from the source field and put it into the event parameters.
		 */

		wxWindow* w = FindWindowByName(wxString(s), this);
		
		wxString value;
		
		if (sampleQuery->hasFKColumn(s) == 1) {
/*...sGet the content from choice control:40:*/
				wxChoice* cbox = (wxChoice*) w;		
			
				int pos = cbox->GetSelection();
				
				if (pos != -1) {
					lbErrCodes err = ERR_NONE;

					UAP_REQUEST(manager.getPtr(), lb_I_Integer, key)
					UAP_REQUEST(manager.getPtr(), lb_I_String, cbName)
					
					cbName->setData(s);
					
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
					
						value = pp;
					
					}
				}
/*...e*/
		} else {
/*...sGet the content from text control:40:*/
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

		UAP(lb_I_Action, action, __FILE__, __LINE__)
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
		v->setData(s);
		param->setUAPString(*&parameter, *&v);

		parameter->setData("source value");
		v->setData(value.c_str());
		param->setUAPString(*&parameter, *&v);

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		parameter->setData("application");

		meta->getApplicationName(&v);

		param->setUAPString(*&parameter, *&v);
/*...e*/

		action->execute(*&param);

		free(s);
		
		free(eventName);
	}

	return ERR_NONE;
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
class lbPluginDatabasePanel : public virtual lb_I_PluginImpl {
public:
	lbPluginDatabasePanel();
	
	virtual ~lbPluginDatabasePanel();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbForm, __FILE__, __LINE__)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabasePanel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabasePanel, lbPluginDatabasePanel)

/*...slbErrCodes LB_STDCALL lbPluginDatabasePanel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabasePanel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl, __FILE__, __LINE__)
	QI(uk, lb_I_PluginImpl, pl, __FILE__, __LINE__)

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
	
		QI(dbPanel, lb_I_Unknown, dbForm, __FILE__, __LINE__)
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
	
		QI(dbPanel, lb_I_Unknown, dbForm, __FILE__, __LINE__)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabasePanel::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (dbForm != NULL) {
		UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)
		QI(dbForm, lb_I_DatabaseForm, form, __FILE__, __LINE__)
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
		UAP(lb_I_DatabaseForm, dbForm, __FILE__, __LINE__)
		QI(uk, lb_I_DatabaseForm, dbForm, __FILE__, __LINE__)
		
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

	SetTitle(panel->getFormName());

	SetAutoLayout(TRUE);
		
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	Centre();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setName(char const * name, char const * appention) {

	return panel->setName(name, appention);
}
/*...e*/

/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getQuery\40\\41\:0:*/
char* LB_STDCALL lbDatabaseDialog::getQuery() {
	return panel->getQuery();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getColumnName\40\int pos\41\:0:*/
char* LB_STDCALL lbDatabaseDialog::getColumnName(int pos) {
	return panel->getColumnName(pos);
}
/*...e*/

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
	return panel->getControlValue(panel->getColumnName(pos));
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

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setFilter(char* filter) {
	panel->setFilter(filter);
}
/*...e*/

/*...schar\42\ lbDatabaseDialog\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
char* lbDatabaseDialog::getTableName(char* columnName) {
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
class lbPluginDatabaseDialog : public virtual lb_I_PluginImpl {
public:
	lbPluginDatabaseDialog();
	
	virtual ~lbPluginDatabaseDialog();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
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

	if (dbForm != NULL) {
		_CL_LOG << "dbForm is not NULL." LOG_
		_CL_LOG << "*******************" LOG_
	}
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
void LB_STDCALL lbPluginDatabaseDialog::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (dbForm != NULL) {
		UAP(lb_I_DatabaseForm, form, __FILE__, __LINE__)
		QI(dbForm, lb_I_DatabaseForm, form, __FILE__, __LINE__)
	
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

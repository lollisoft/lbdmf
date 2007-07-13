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

void makePluginName(char* path, char* module, char*& result) {
		char* pluginDir = NULL;

		#ifndef WINDOWS
		pluginDir = (char*) malloc(strlen(path)+strlen("/plugins")+1);
		pluginDir[0] = 0;
		strcat(pluginDir, path);
		strcat(pluginDir, "/plugins");
		#endif

		#ifdef WINDOWS
		// Overwrites hardcoded path
		pluginDir = getenv("PLUGIN_DIR");
		if (pluginDir == NULL) {
			pluginDir = (char*) malloc(strlen(path)+strlen("\\plugins")+1);
			pluginDir[0] = 0;
			strcat(pluginDir, path);
			strcat(pluginDir, "\\plugins");
		} else {
			pluginDir = strdup(pluginDir);
		}
		#endif 

		/*...sBuild up pluginModule:64:*/
		char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2);
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
		strcat(pluginModule, module);
		/*...e*/
		result = pluginModule;
		free(pluginDir);
}

/*...svoid LB_STDCALL lbAction\58\\58\delegate\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::delegate(lb_I_Parameter* params) {
	/*
	 Resolve the parameters that we need here.
	 Currently only the id of the action step.
	 */
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
	
	char* pluginModule = NULL;
	
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, id)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		
	if (actions == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, actions)
	}
	
	parameter->setData("id");
	params->getUAPString(*&parameter, *&id);
	
	UAP(lb_I_Query, query)
		
	query = db->getQuery("lbDMF", 0);
	
	char buf[] = "select action_handler, module from action_types inner join "
		"action_steps on action_types.id = action_steps.type where action_steps.id = %s";
	
	char* q = (char*) malloc(strlen(buf)+strlen(id->charrep())+1);
	q[0] = 0;
	sprintf(q, buf, id->charrep());
	
	if (query->query(q) == ERR_NONE) {
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(manager.getPtr(), lb_I_String, key)
		UAP(lb_I_KeyBase, ukey)
			
		err = query->first();
		
		while (err == ERR_NONE) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
			UAP_REQUEST(manager.getPtr(), lb_I_String, module)
			UAP(lb_I_DelegatedAction, action)
			
			action_handler = query->getAsString(1);
			module = query->getAsString(2);
			action_handler->trim();
			module->trim();
			
			key->setData(module->charrep());
			*key += *&action_handler;
			
			QI(key, lb_I_KeyBase, ukey)
				
				if (actions->exists(&ukey) == 0) {
					/*...sInstanciate one and insert into actions:32:*/
					
					UAP(lb_I_Unknown, result)
					
					char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
					ah[0] = 0;
					
					strcat(ah, PREFIX);
					strcat(ah, action_handler->charrep());
					
					char* home = NULL;
					
					#ifdef LINUX
					home = getenv("HOME");
					#endif
					#ifdef WINDOWS
					home = getenv("USERPROFILE");
					#endif
					
					
					makePluginName(home, module->charrep(), pluginModule);
					
					if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						
						free(pluginModule);
						char* pwd = getenv("PWD");
						if (pwd == NULL) pwd = ".";
						makePluginName(pwd, module->charrep(), pluginModule);
						
						if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						
							free(pluginModule);
							char* pwd = "/usr";
							makePluginName(pwd, module->charrep(), pluginModule);
						
							if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
							    _CL_LOG << "ERROR: Plugin could not be loaded." LOG_
							}
						}
						
					}
					
					result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
					actions->insert(&result, &ukey);
					/*...e*/
				}
			
			UAP(lb_I_Unknown, uk)
				
			uk = actions->getElement(&ukey);
			
			QI(uk, lb_I_DelegatedAction, action)
				
			action->setActionID(id->charrep());	

			wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
			meta->setStatusText("Info", msg.c_str());

			action->execute(*&params);
			
			_CL_LOG << "References for delegated action are " << action->getRefCount() << "." LOG_
				
			err = query->next();
		}
		
		if (err == WARN_DB_NODATA) {
			UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
			UAP_REQUEST(manager.getPtr(), lb_I_String, module)
			UAP(lb_I_DelegatedAction, action)
			
			action_handler = query->getAsString(1);
			module = query->getAsString(2);
			action_handler->trim();
			module->trim();
			
			key->setData(module->charrep());
			*key += *&action_handler;
			
			QI(key, lb_I_KeyBase, ukey)
				
				if (actions->exists(&ukey) == 0) {
					
					UAP(lb_I_Unknown, result)
					
					char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
					ah[0] = 0;
					
					strcat(ah, PREFIX);
					strcat(ah, action_handler->charrep());
					
					char* home = NULL;
					
					#ifdef LINUX
					home = getenv("HOME");
					#endif
					#ifdef WINDOWS
					home = getenv("USERPROFILE");
					#endif
					
					makePluginName(home, module->charrep(), pluginModule);
					
					if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						
						free(pluginModule);
						char* pwd = getenv("PWD");
						if (pwd == NULL) pwd = ".";
						makePluginName(pwd, module->charrep(), pluginModule);
						
						if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						
							free(pluginModule);
							char* pwd = "/usr";
							makePluginName(pwd, module->charrep(), pluginModule);
						
							if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
							    _CL_LOG << "ERROR: Plugin could not be loaded." LOG_
							}
						}
						
					}
					
					result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
					actions->insert(&result, &ukey);
					/*...e*/
				}
			
			UAP(lb_I_Unknown, uk)
				
			uk = actions->getElement(&ukey);
			
			QI(uk, lb_I_DelegatedAction, action)
			action->setActionID(id->charrep());
			
			wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
			meta->setStatusText("Info", msg.c_str());
				
			action->execute(*&params);
		}
	} else {
		wxString errmsg = wxString("Error: Query for action handlers didn't found any handlers.");
		meta->setStatusText("Info", errmsg.c_str());
	}
}
/*...e*/

/*...svoid LB_STDCALL lbAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::execute(lb_I_Parameter* params) {
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	REQUEST(manager.getPtr(), lb_I_Database, db)
	UAP(lb_I_Query, query)

	db->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	db->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = db->getQuery("lbDMF", 0);	
	
	char buf[] = "select id from action_steps where actionid = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	_LOG << "Get action steps from id = " << myActionID << ". Query is " << q LOG_
	
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
	} else {
		wxString errmsg = wxString("Fehler: Abfrage '") + wxString(buf) + wxString("' hat keine Daten geliefert.!");
		meta->setStatusText("Info", errmsg.c_str());
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
	UAP_REQUEST(manager.getPtr(), lb_I_String, actionID)

	if (detailForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_
	
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
		// Pass my action ID
		parameter->setData("actionID");
		*actionID = myActionID;
		params->setUAPString(*&parameter, *&actionID);
		
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&masterForm);
		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		detailForm->setName(formularname->charrep(), parameter->charrep());

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui)
		
		meta->getGUI(&gui);

		lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		if (f == NULL) {
			_CL_LOG << "Error: Bail out, no master form found." LOG_
			return; 
		}

		detailForm->setMasterForm(f, *&params);
		
		detailForm->updateFromMaster();
		gui->showForm(formularname->charrep());	
	} else {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui)
	
		meta->getGUI(&gui);

		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

		parameter->setData("actionID");
		*actionID = myActionID;
		params->setUAPString(*&parameter, *&actionID);
		
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
		        "select Formulare.id from Formulare "
		        "inner join Anwendungen on Formulare.anwendungid = Anwendungen.id inner join "
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
		UAP(lb_I_Query, query)
		
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		query = database->getQuery("lbDMF", 0);
/*...e*/

		if (query->query(buffer) == ERR_NONE) {
			lbErrCodes err = query->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, id)
				
/*...sPrepare query to get parameter value based on given ID:32:*/
				id = query->getAsString(1);
				
				char* b = "select parametervalue from Formular_Parameters where formularid = %s";

				char* buffer = (char*) malloc(strlen(b)+strlen(id->charrep())+1);
				buffer[0] = 0;
				sprintf(buffer, b, id->charrep());

				UAP(lb_I_Query, query)

				query = database->getQuery("lbDMF", 0);

				err = query->query(buffer);
/*...e*/
				
				if (err == ERR_NONE) {
/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();
					
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk)
						
						sql = query->getAsString(1);

						UAP(lb_I_DatabaseForm, form)

						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui)
						meta->getGUI(&gui);
						
						form = gui->createDBForm(formularname->charrep(),
									sql->charrep(),
									DBName->charrep(), 
									DBUser->charrep(), 
									DBPass->charrep());
									
						if (form == NULL) {
							_CL_LOG << "Error: Bail out, detail form could not be created." LOG_
							return; 
						}
									
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
						
						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, master)

						f = gui->findDBForm(masterForm->charrep());

						if (f == NULL) {
							_CL_LOG << "Error: Bail out, no master form found." LOG_
							
							if (detailForm != NULL) {
								// Cleanup
								detailForm->destroy();
							}
							
							return; 
						}

						QI(f, lb_I_DatabaseForm, master)						
						
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
					free(buffer);
				}
			} else {
				_CL_LOG << "ERROR: No data found for query to get detailform:\n\n" << buffer LOG_
				free(buffer);
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

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query)

	wxString msg = wxString("lbDetailFormAction::execute(") + wxString(myActionID) + wxString(")");
	meta->setStatusText("Info", msg.c_str());

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
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
			
			_CL_LOG << "Open detail form (" << what->charrep() << ")" LOG_
			
			openDetailForm(*&what, *&params);
			
			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();
			
			_CL_LOG << "Open detail form (" << what->charrep() << ")" LOG_

			openDetailForm(*&what, *&params);
/*...e*/
		}
	} else {
		wxString errmsg = wxString("lbDetailFormAction::execute(") + wxString(myActionID) + wxString(") failed.");
		meta->setStatusText("Info", errmsg.c_str());
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
	UAP_REQUEST(manager.getPtr(), lb_I_String, actionID)

	/// \todo This is a possible bug if there are more than one such form.
	if (masterForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_
	
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
		// Pass my action ID
		parameter->setData("actionID");
		*actionID = myActionID;
		params->setUAPString(*&parameter, *&actionID);

		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&detailForm);
		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		masterForm->setName(formularname->charrep(), parameter->charrep());
				
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui)
		
		meta->getGUI(&gui);

		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

		if (f == NULL) {
			_CL_LOG << "ERROR: Could not find detail form. Bail out." LOG_
			return;
		}

		masterForm->setDetailForm(f, *&params);
		
		masterForm->updateFromDetail();
		gui->showForm(formularname->charrep());
	} else {
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui)
		
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
		
		parameter->setData("actionID");
		*actionID = myActionID;
		params->setUAPString(*&parameter, *&actionID);

		//	parameter->setData("source field");
		//	params->getUAPString(*&parameter, *&SourceFieldName);
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("application");
		params->getUAPString(*&parameter, *&app);
		
		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

		if (f == NULL) {
			_CL_LOG << "ERROR: Could not find detail form. Bail out." LOG_
			return;
		}

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
		UAP(lb_I_Query, query)
		
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		query = database->getQuery("lbDMF", 0);
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

				UAP(lb_I_Query, query)

				query = database->getQuery("lbDMF", 0);

				err = query->query(buffer);
/*...e*/
				
				if (err == ERR_NONE) {
/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();
					
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk)
						
						sql = query->getAsString(1);
						
						UAP(lb_I_DatabaseForm, form)
						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui)

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
						
						UAP(lb_I_DatabaseForm, f)

						UAP(lb_I_DatabaseForm, detail)

						f = gui->findDBForm(detailForm->charrep());

						QI(f, lb_I_DatabaseForm, detail)						
						
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

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query)

	wxString msg = wxString("lbMasterFormAction::execute(") + wxString(myActionID) + wxString(")");
	meta->setStatusText("Info", msg.c_str());

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
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
	} else {
		wxString errmsg = wxString("lbMasterFormAction::execute(") + wxString(myActionID) + wxString(") failed.");
		meta->setStatusText("Info", errmsg.c_str());
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
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("source field");
	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&SourceFormName);


	wxString msg = wxString("lbSQLQueryAction::execute(") + wxString(myActionID) + wxString(")");
	meta->setStatusText("Info", msg.c_str());

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %s";
	char* q = (char*) malloc(strlen(buf)+strlen(myActionID)+1);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	UAP_REQUEST(getModuleInstance(), lb_I_Database, db)
	db->init();
	if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
		return;
	}
	
	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();
		
			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}"; 
		
			wxString s = wxString(what->charrep());
		
			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s.c_str();
			if (q->query(what->charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return;
			}
			q->enableFKCollecting();

			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();
		
			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}"; 
		
			wxString s = wxString(what->charrep());
		
			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s.c_str();
			if (q->query(what->charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return;
			}
			q->enableFKCollecting();
/*...e*/
		}
	} else {
		wxString errmsg = wxString("lbSQLQueryAction::execute(") + wxString(myActionID) + wxString(") failed.");
		meta->setStatusText("Info", errmsg.c_str());
	}
	
	lb_I_GUI* gui;

	meta->getGUI(&gui);
	
	if (gui != NULL) {
		UAP(lb_I_DatabaseForm, f)
		
		f = gui->findDBForm(SourceFormName->charrep());
		
		if (f != NULL) f->reopen();
	}
}
/*...e*/

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
	lbErrCodes err = ERR_NONE;
	ref = STARTREF;
	myActionID = -1;
	initialized = false;
}

lbAction::~lbAction() {
	
	_CL_LOG << "lbAction::~lbAction() called." LOG_
	if (actions != NULL) {
		_CL_LOG << "Have " << actions->Count() << " elements in action list." LOG_
		actions->deleteAll();
	}
	_CL_LOG << "Deleted all delegation actions." LOG_
}

/*...svoid LB_STDCALL lbAction\58\\58\setActionID\40\char\42\ id\41\:0:*/
void LB_STDCALL lbAction::setActionID(long id) {
	myActionID = id;
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
#ifndef LINUX
#ifdef OSX
		strcat(pluginModule, "/");
#endif
#endif
		strcat(pluginModule, module);
		/*...e*/
		result = pluginModule;
		free(pluginDir);
}

void LB_STDCALL lbAction::loadDataModel() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL && !initialized) {
		initialized = true;
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

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
}

/*...svoid LB_STDCALL lbAction\58\\58\delegate\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::delegate(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	loadDataModel();

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
	
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
		
	if (actions == NULL) {
		REQUEST(manager.getPtr(), lb_I_Container, actions)
	}
	
	parameter->setData("id");
	params->getUAPLong(*&parameter, *&id);

	if ((appActionTypes != NULL) && (appActionSteps != NULL)) {
		_LOG << "Execute actions based on lbDMFDataModel classes." LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
		UAP_REQUEST(getModuleInstance(), lb_I_String, module)
		UAP_REQUEST(getModuleInstance(), lb_I_String, key)
		UAP(lb_I_KeyBase, keybase)
		QI(key, lb_I_KeyBase, keybase)
		
		appActionSteps->selectActionStep(id->getData());
		appActionTypes->selectActionType(appActionSteps->getActionStepType());
			
		*action_handler = appActionTypes->getActionTypeHandler();
		*module = appActionTypes->getActionTypeModule();
			
		*key = *&module;
		*key += *&action_handler;

		_LOG << "Got action handler '" << action_handler->charrep() << "' from '" << module->charrep() << "' for action ID = " << id->charrep() LOG_

		if (actions->exists(&keybase) == 0) {
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
			_LOG << "Try to load a plugin at: " << pluginModule LOG_
			if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
				free(pluginModule);
				char* pwd = getenv("PWD");
				if (pwd == NULL) pwd = ".";
				makePluginName(pwd, module->charrep(), pluginModule);
						
				_LOG << "Try to load a plugin at: " << pluginModule LOG_
				if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
					free(pluginModule);
					char* pwd = "/usr";
					makePluginName(pwd, module->charrep(), pluginModule);
					if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
						_CL_LOG << "ERROR: Plugin could not be loaded." LOG_
					}
				}
			}
			if (result == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)
				*errmsg = "Failed to load module for configured action!\n\n";
				*errmsg += "Module: ";
				*errmsg += module->charrep();
				*errmsg += "\nAction handler: ";
				*errmsg += action_handler->charrep();
				meta->msgBox("Error", errmsg->charrep());
				return;
			}
			result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
			actions->insert(&result, &keybase);
/*...e*/
		}
		UAP(lb_I_DelegatedAction, action)
		UAP(lb_I_Unknown, uk)
		uk = actions->getElement(&keybase);
		QI(uk, lb_I_DelegatedAction, action)
		action->setActionID(id->getData());	
		wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
		meta->setStatusText("Info", msg.c_str());
		_LOG << "Execute delegated action by document model..." LOG_
		action->execute(*&params);
	} else {
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
						
						_LOG << "Try to load a plugin at: " << pluginModule LOG_
							if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
								
								free(pluginModule);
								char* pwd = getenv("PWD");
								if (pwd == NULL) pwd = ".";
								makePluginName(pwd, module->charrep(), pluginModule);
								
								_LOG << "Try to load a plugin at: " << pluginModule LOG_
									if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
										
										free(pluginModule);
										char* pwd = "/usr";
										makePluginName(pwd, module->charrep(), pluginModule);
										
										if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
											_CL_LOG << "ERROR: Plugin could not be loaded." LOG_
										}
									}
							}
						
						if (result == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)
							
							*errmsg = "Failed to load module for configured action!\n\n";
							*errmsg += "Module: ";
							*errmsg += module->charrep();
							*errmsg += "\nAction handler: ";
							*errmsg += action_handler->charrep();
							
							
							meta->msgBox("Error", errmsg->charrep());
							return;
						}
						
						
						result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
						actions->insert(&result, &ukey);
						/*...e*/
					}
				
				UAP(lb_I_Unknown, uk)
					
				uk = actions->getElement(&ukey);
				
				QI(uk, lb_I_DelegatedAction, action)
					
				action->setActionID(id->getData());	
				
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
						_LOG << "Try to load a plugin at: " << pluginModule LOG_
							if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
								
								free(pluginModule);
								char* pwd = getenv("PWD");
								if (pwd == NULL) pwd = ".";
								makePluginName(pwd, module->charrep(), pluginModule);
								_LOG << "Try to load a plugin at: " << pluginModule LOG_
									if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
										
										free(pluginModule);
										char* pwd = "/usr";
										makePluginName(pwd, module->charrep(), pluginModule);
										
										if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
											_CL_LOG << "ERROR: Plugin could not be loaded." LOG_
										}
									}
								
							}
						
						if (result == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)
							
							*errmsg = "Failed to load module for configured action!\n\n";
							*errmsg += "Module: ";
							*errmsg += module->charrep();
							*errmsg += "\nAction handler: ";
							*errmsg += action_handler->charrep();
							
							
							meta->msgBox("Error", errmsg->charrep());
							return;
						}
						
						result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
						actions->insert(&result, &ukey);
						/*...e*/
					}
				
				UAP(lb_I_Unknown, uk)
					
				uk = actions->getElement(&ukey);
				
				QI(uk, lb_I_DelegatedAction, action)
				action->setActionID(id->getData());
				
				wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
				meta->setStatusText("Info", msg.c_str());
				
				action->execute(*&params);
			}
		} else {
			wxString errmsg = wxString("Error: Query for action handlers didn't found any handlers.");
			meta->setStatusText("Info", errmsg.c_str());
		}
	}
}
/*...e*/

/*...svoid LB_STDCALL lbAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	
	loadDataModel();
	
	if (appActionSteps != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_Container, sortedActionSteps)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, order)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, stepid)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		_LOG << "Execute action steps based on actionsteps model." LOG_
		
		QI(order, lb_I_KeyBase, key)
		QI(stepid, lb_I_Unknown, uk)
		
		UAP_REQUEST(getModuleInstance(), lb_I_Long, actionid)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, actionidcmp)
		
		actionidcmp->setData(myActionID);
		
		appActionSteps->finishActionStepIteration();
		while (appActionSteps->hasMoreActionSteps()) {
			appActionSteps->setNextActionStep();
			_LOG << "Sort entry ..." LOG_
			actionid->setData(appActionSteps->getActionStepActionID());
			
			if (actionidcmp->equals(*&actionid)) {
			    _LOG << "Sort action steps by ordering column: " << appActionSteps->getActionStepOrderNo() << "." LOG_
				order->setData(appActionSteps->getActionStepOrderNo());
				stepid->setData(appActionSteps->getActionStepID());
				sortedActionSteps->insert(&uk, &key);
			}
		}
		appActionSteps->finishActionStepIteration();
		
		sortedActionSteps->finishIteration();
		while (sortedActionSteps->hasMoreElements() == 1) {
			uk = sortedActionSteps->nextElement();
			
			stepid->setData(*&uk);
		
			parameter->setData("id");
			params->setUAPLong(*&parameter, *&stepid);
				
			_LOG << "Delegate action ..." LOG_
			delegate(*&params);		
		}
		return;
	} else {
		char* dbbackend = meta->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, db)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}

		if (db == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return;
		}
		UAP(lb_I_Query, query)

		_LOG << "Read actionsteps sequentially from the database." LOG_

		db->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		db->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		
		query = db->getQuery("lbDMF", 0);	
		
		char buf[] = "select id from action_steps where actionid = %d order by a_order_no";
		char* q = (char*) malloc(strlen(buf)+10);
		q[0] = 0;
		sprintf(q, buf, myActionID);
		
		_LOG << "Get action steps from id = " << myActionID << ". Query is " << q LOG_
			
			if (query->query(q) == ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, statechangeID)
				lbErrCodes err = query->first();
				
				*paramname = "statechange";
				
				while(err == ERR_NONE) {
					UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
					
					id = query->getAsLong(1);
					
					parameter->setData("id");
					params->setUAPLong(*&parameter, *&id);
					
					delegate(*&params);
					
					// If the actionstep returns a statechange parameter, then it is propably no more a linear action execution flow.
					// In that case an action may be a desicion and therefore a statechange informs about the next state to be entered.
					// A state is a specific action step where the state is the ID of that step.

					if (params->getUAPLong(*&paramname, *&statechangeID) == ERR_PARAM_NOT_FOUND) {
						err = query->next();
					} else {
						// A statechange comes back
						if (query->first() == ERR_NONE) {
							//UAP(lb_I_KeyBase, comp1)
							//UAP(lb_I_KeyBase, comp2)
							//QI(id, lb_I_KeyBase, comp1)
							//QI(statechangeID, lb_I_KeyBase, comp2)
							id = query->getAsLong(1);
							
							while ((err != ERR_DB_NODATA) && (id->getData() != (long) statechangeID->getData())) {
								err = query->next();
								id = query->getAsLong(1);
							}
						}
					}
				}
				
				if (err == WARN_DB_NODATA) {
					UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
					
					id = query->getAsLong(1);
					
					parameter->setData("id");
					params->setUAPLong(*&parameter, *&id);
					
					delegate(*&params);
				}
			} else {
				wxString errmsg = wxString("Fehler: Abfrage '") + wxString(buf) + wxString("' hat keine Daten geliefert.!");
				meta->setStatusText("Info", errmsg.c_str());
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
	myActionID = -1;
	detailForm = NULL;
}

lbDetailFormAction::~lbDetailFormAction() {
}

void LB_STDCALL lbDetailFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDetailFormAction::setActionID(long id) {
	myActionID = id;
}

/*...svoid LB_STDCALL lbDetailFormAction\58\\58\openDetailForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDetailFormAction::openDetailForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbDetailFormAction::openDetailForm() called." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&masterForm);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("actionID");
	actionID->setData(myActionID);
	params->setUAPLong(*&parameter, *&actionID);
	parameter->setData("application");
	params->getUAPString(*&parameter, *&app);

	if (detailForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_
	
		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		detailForm->setName(formularname->charrep(), parameter->charrep());

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
		UAP(lb_I_GUI, gui)
		meta->getGUI(&gui);


		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, docparams)
			
		uk = meta->getActiveDocument();
		QI(uk, lb_I_Parameter, docparams)
			
		if (docparams != NULL) {
			// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
			UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_Action_Steps, appActionSteps)
			UAP(lb_I_KeyBase, key)

			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Formulars, forms)
			UAP(lb_I_FormularParameter, formParams)
			
			docparams->setCloning(false);
			document->setCloning(false);
			
			QI(name, lb_I_KeyBase, key)
			*name = "ApplicationData";
			docparams->getUAPContainer(*&name, *&document);
			
			*name = "Formulars";
			uk = document->getElement(&key);
			QI(uk, lb_I_Formulars, forms)

			*name = "FormParams";
			uk = document->getElement(&key);
			QI(uk, lb_I_FormularParameter, formParams)
			
			
			if ((formParams != NULL) && (forms != NULL)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
				long AppID = meta->getApplicationID();
				
				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();
					
					if ((forms->getApplicationID() == AppID) && (strcmp(forms->getName(), formularname->charrep()) == 0)) {
						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, master)
						UAP(lb_I_DatabaseForm, form)
						long FormularID = forms->getFormularID();
						*SQL = formParams->getParameter("query", FormularID);
						forms->finishFormularIteration();
						form = gui->createDBForm(formularname->charrep(),
									SQL->charrep(),
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
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)
						// The connection may be closed.
						master->reopen();
						master->getPrimaryColumns();
						*column = master->getColumnName(1);
						*table = master->getTableName(column->charrep());
						form->ignoreForeignKeys(table->charrep());
						form->setMasterForm(*&master, *&params);
						gui->showForm(formularname->charrep());
						form++;
						return;
					}
				}
				meta->setStatusText("Info", "Did not found detailform.");
				return;
			}
		}

		// - old database variant -

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
		
		UAP(lb_I_Database, database)
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
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)
						
						master->getPrimaryColumns();

						*column = master->getColumnName(1);
						*table = master->getTableName(column->charrep());
						
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
	lbErrCodes err = ERR_NONE;
	_LOG "lbDetailFormAction::execute() called" LOG_
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
	
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
		
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)
		
	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		
		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Open detail form (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());
			openDetailForm(*&What, *&params);
			return;
		}
	}

	// - Old database variant -
	
	UAP(lb_I_Database, database)
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
	UAP(lb_I_Query, query)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = "Open detail form (";
			*msg += what->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());
			
			openDetailForm(*&what, *&params);
			
			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = "Open detail form (";
			*msg += what->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());

			openDetailForm(*&what, *&params);
/*...e*/
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbDetailFormAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
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
	myActionID = -1;
	masterForm = NULL;
}

lbMasterFormAction::~lbMasterFormAction() {
}

void LB_STDCALL lbMasterFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbMasterFormAction::setActionID(long id) {
	myActionID = id;
}

/*...svoid LB_STDCALL lbMasterFormAction\58\\58\openMasterForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbMasterFormAction::openMasterForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbMasterFormAction::openMasterForm() called." LOG_
	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&detailForm);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("actionID");
	actionID->setData(myActionID);
	params->setUAPLong(*&parameter, *&actionID);
	parameter->setData("application");
	params->getUAPString(*&parameter, *&app);
		
	/// \todo This is a possible bug if there are more than one such form.
	if (masterForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_

		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		masterForm->setName(formularname->charrep(), parameter->charrep());
				
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
		UAP(lb_I_GUI, gui)
		meta->getGUI(&gui);
		

		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, docparams)
			
		uk = meta->getActiveDocument();
		QI(uk, lb_I_Parameter, docparams)
			
		if (docparams != NULL) {
			// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
			UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_Action_Steps, appActionSteps)
			UAP(lb_I_KeyBase, key)
			UAP(lb_I_Unknown, uk)
			
			UAP(lb_I_Formulars, forms)
			UAP(lb_I_FormularParameter, formParams)
			
			docparams->setCloning(false);
			document->setCloning(false);
			
			QI(name, lb_I_KeyBase, key)
			*name = "ApplicationData";
			docparams->getUAPContainer(*&name, *&document);
			
			*name = "Formulars";
			uk = document->getElement(&key);
			QI(uk, lb_I_Formulars, forms)

			*name = "FormParams";
			uk = document->getElement(&key);
			QI(uk, lb_I_FormularParameter, formParams)
			
			
			if ((formParams != NULL) && (forms != NULL)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
				long AppID = meta->getApplicationID();
				
				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();
					
					if ((forms->getApplicationID() == AppID) && (strcmp(forms->getName(), formularname->charrep()) == 0)) {
						UAP_REQUEST(getModuleInstance(), lb_I_String, table)
						UAP_REQUEST(getModuleInstance(), lb_I_String, column)
						UAP(lb_I_DatabaseForm, form)
						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, detail)

						long FormularID = forms->getFormularID();
						*SQL = formParams->getParameter("query", FormularID);
						form = gui->createDBForm(formularname->charrep(),
											SQL->charrep(),
											DBName->charrep(),
											DBUser->charrep(),
											DBPass->charrep());
						masterForm = form.getPtr();
						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						form->setName(formularname->charrep(), parameter->charrep());
						f = gui->findDBForm(detailForm->charrep());
						QI(f, lb_I_DatabaseForm, detail)
						detail->getPrimaryColumns();
						*column = detail->getColumnName(1);
						*table = detail->getTableName(column->charrep());
						form->ignoreForeignKeys(table->charrep());
						form->setDetailForm(*&detail, *&params);
						gui->showForm(formularname->charrep());
						form++;
						return;
					}
				}
				meta->setStatusText("Info", "Did not found masterform.");
				return;
			}
		}

		// - old database variant -

		
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
		
		UAP(lb_I_Database, database)
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
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)
						
						detail->getPrimaryColumns();
						
						*column = detail->getColumnName(1);
						*table = detail->getTableName(column->charrep());
						
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
	lbErrCodes err = ERR_NONE;
	_LOG "lbMasterFormAction::execute() called" LOG_
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
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
		
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)
		
	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		
		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Open master form (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());
			openMasterForm(*&What, *&params);
			return;
		}
	}
	
	// - Old database variant -
	
	UAP(lb_I_Database, database)
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
	UAP(lb_I_Query, query)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
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
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbMasterFormAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
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
	myActionID = -1;
}

lbSQLQueryAction::~lbSQLQueryAction() {
}

void LB_STDCALL lbSQLQueryAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbSQLQueryAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbSQLQueryAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbSQLQueryAction::execute()" LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	
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
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
		
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)
		
	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		
		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Execute query (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());

			UAP(lb_I_Database, db)
			char* dbbackend = meta->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, db)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (db == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return;
			}
			db->init();
			if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
				meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
				return;
			}

			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}"; 
		
			wxString s = wxString(What->charrep());
		
			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*What = s.c_str();
			
			if ((err = q->query(What->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return;
			}
			q->enableFKCollecting();

			return;
		}
	}
	
	// - Old database variant -
		
	UAP(lb_I_Database, database)
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
	UAP(lb_I_Query, query)



	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %d order by a_order_nr";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	UAP(lb_I_Database, db)
	dbbackend = meta->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, db)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (db == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return;
	}
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
			if ((err = q->query(what->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
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
			if (q->query(what->charrep(), false) != ERR_NONE) {
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
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbSQLQueryAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
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

#ifdef USE_NEW_ACTIONS

/*...lbDecisionAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDecisionAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDecisionAction, lbDecisionAction)

lbErrCodes LB_STDCALL lbDecisionAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDecisionAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbDecisionAction::lbDecisionAction() {
	ref = STARTREF;
	myActionID = -1;
}

lbDecisionAction::~lbDecisionAction() {
}

void LB_STDCALL lbDecisionAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDecisionAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbDecisionAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbDecisionAction::execute()" LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	
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
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
		
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)
		
	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		
		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Execute query (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());

			UAP(lb_I_Database, db)
			char* dbbackend = metaapp->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, db)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (db == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
			}
			db->init();
			if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
				meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
				return;
			}

			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}"; 
		
			wxString s = wxString(What->charrep());
		
			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*What = s.c_str();
			
			if (q->query(What->charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return;
			}
			q->enableFKCollecting();

			return;
		}
	}
	
	// - Old database variant -
		
	UAP(lb_I_Database, database)
	char* dbbackend = metaapp->getSystemDatabaseBackend();
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
	UAP(lb_I_Query, query)



	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	UAP(lb_I_Database, db)
	char* dbbackend = metaapp->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, db)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (db == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
	}
	db->init();
	if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
		return;
	}
	
	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
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
		}
		
		if (err == WARN_DB_NODATA) {
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
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbSQLQueryAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
	}
	
	lb_I_GUI* gui;

	meta->getGUI(&gui);
	
	if (gui != NULL) {
		UAP(lb_I_DatabaseForm, f)
		
		f = gui->findDBForm(SourceFormName->charrep());
		
		if (f != NULL) f->reopen();
	}
}

/****************



/*...lbOpAqueOperation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbOpAqueOperation)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbOpAqueOperation, lbOpAqueOperation)

lbErrCodes LB_STDCALL lbOpAqueOperation::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbOpAqueOperation::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbOpAqueOperation::lbOpAqueOperation() {
	ref = STARTREF;
	myActionID = -1;
}

lbOpAqueOperation::~lbOpAqueOperation() {
}

void LB_STDCALL lbOpAqueOperation::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbOpAqueOperation::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbOpAqueOperation::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbOpAqueOperation::execute()" LOG_
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	
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
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
		
	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)
		
	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		
		docparams->setCloning(false);
		document->setCloning(false);
		
		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);
		
		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)
		
		*name = "AppAction_Step_Transitions";
		
		
		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Execute query (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());

			UAP(lb_I_Database, db)
			char* dbbackend = metaapp->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, db)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (db == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
			}
			db->init();
			if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
				meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
				return;
			}

			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}"; 
		
			wxString s = wxString(What->charrep());
		
			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*What = s.c_str();
			
			if (q->query(What->charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return;
			}
			q->enableFKCollecting();

			return;
		}
	}
	
	// - Old database variant -
		
	UAP(lb_I_Database, database)
	char* dbbackend = metaapp->getSystemDatabaseBackend();
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
	UAP(lb_I_Query, query)



	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);	
	
	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	UAP(lb_I_Database, db)
	char* dbbackend = metaapp->getApplicationDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
		_LOG << "Using plugin database backend for UML import operation..." LOG_
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, db)
		_LOG << "Using built in database backend for UML import operation..." LOG_
	}

	if (db == NULL) {
		_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
		return;
	}
	db->init();
	if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
		return;
	}
	
	if (query->query(q) == ERR_NONE) {
	
		lbErrCodes err = query->first();
	
		while(err == ERR_NONE) {
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
		}
		
		if (err == WARN_DB_NODATA) {
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
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbSQLQueryAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
	}
	
	lb_I_GUI* gui;

	meta->getGUI(&gui);
	
	if (gui != NULL) {
		UAP(lb_I_DatabaseForm, f)
		
		f = gui->findDBForm(SourceFormName->charrep());
		
		if (f != NULL) f->reopen();
	}
}

#endif //#ifdef USE_NEW_ACTIONS
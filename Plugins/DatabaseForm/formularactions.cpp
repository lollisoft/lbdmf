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
            Ginsterweg 4
            
            65760 Eschborn (germany)
*/
/*...e*/
/*...sincludes:0:*/
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

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <lbDatabaseForm.h>

#ifndef USE_EXRERNAL_FORMULARACTIONS
void FormularActions::addRegisteredAction(long ActionID, const char* eventName) {
	lbErrCodes err = ERR_NONE;
	if (eventmapping == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, eventmapping)
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_String, EvName)
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	QI(ID, lb_I_Unknown, uk)
	QI(EvName, lb_I_KeyBase, key)
	
	*EvName = eventName;
	ID->setData(ActionID);
	
	if (!eventmapping->exists(&key)) eventmapping->insert(&uk, &key);
}


/*...slb_I_Action\42\ FormularActions\58\\58\getAction\40\char\42\ id\41\:0:*/
lb_I_Action* FormularActions::getAction(long id) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Unknown, uk)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_KeyBase, key)
	ID->setData(id);
	QI(ID, lb_I_KeyBase, key)

	lb_I_Action* action;
	
	if (actions == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, actions)
	}
	
	if (actions->exists(&key) == 0) {
		lbAction* _action = new lbAction();
		
		_action->queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);

		actions->insert(&uk, &key);
		
		delete _action;
		uk.resetPtr();
	}

	uk = actions->getElement(&key);
	uk->queryInterface("lb_I_Action", (void**) &action, __FILE__, __LINE__);

	// Store the id of the action for later use.
	
	_CL_VERBOSE << "Create an action object with id = '" << id << "'" LOG_
	
	action->setActionID(id);

	return action;
}
/*...e*/

long FormularActions::getActionTargetIDLong(const char* reversed_event) {
	lbErrCodes err = ERR_NONE;
	if (eventmapping != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, eventname)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Long, ActionID)
		QI(eventname, lb_I_KeyBase, key)
		
		*eventname = reversed_event;
		
		if (eventmapping->exists(&key)) {
			uk = eventmapping->getElement(&key);
			QI(uk, lb_I_Long, ActionID)
				
			return ActionID->getData();
		}
	}
	return -1;
}

/*...schar\42\ FormularActions\58\\58\getActionTargetID\40\char\42\ what\41\:0:*/
char* FormularActions::getActionTargetID(const char* reversed_event) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	if (eventmapping != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, eventname)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Long, ActionID)
		QI(eventname, lb_I_KeyBase, key)
		
		*eventname = reversed_event;
		
		if (eventmapping->exists(&key)) {
			uk = eventmapping->getElement(&key);
			QI(uk, lb_I_Long, ActionID)
			
			_LOG << "Returning action ID by event mapping." LOG_
			return ActionID->charrep();
		}
	}	
	
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
		return strdup("-1");
	}
	UAP_REQUEST(getModuleInstance(), lb_I_String, What)
	
	What->setData(reversed_event);
	What->trim();

	database->init();
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);	

	UAP(lb_I_Query, query)
	
	query = database->getQuery("lbDMF", 0);
	
	char buf[] = "select action from formular_actions where event = '%s'";
	
	char* buffer = (char*) malloc(strlen(buf)+strlen(What->charrep())+1);
	
	sprintf(buffer, buf, What->charrep());
	
	query->query(buffer);

	free(buffer);
	
	if (((err = query->first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
	
		UAP(lb_I_String, source)
		
		source = query->getAsString(1);
		
		_CL_VERBOSE << "FormularActions::getActionTargetID('" << What->charrep() << 
		"') returns '" << source->charrep() << "'" LOG_
		
		return strdup(source->charrep());
	}
	
	_CL_LOG << "FormularActions::getActionTargetID('" << What->charrep() << "') failed!" LOG_
		
	return strdup("");
}
/*...e*/
/*...schar\42\ FormularActions\58\\58\getActionSourceDataField\40\char\42\ what\41\:0:*/
char* FormularActions::getActionSourceDataField(const char* reversed_event) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	if (eventmapping != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, params)
		
		uk = meta->getActiveDocument();
		QI(uk, lb_I_Parameter, params)
			
		if (params != NULL) {
			// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
			UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_KeyBase, key)
			UAP(lb_I_Unknown, uk)
			
			params->setCloning(false);
			document->setCloning(false);
			
			QI(name, lb_I_KeyBase, key)
			*name = "ApplicationData";
			params->getUAPContainer(*&name, *&document);
			
			*name = "AppActions";
			uk = document->getElement(&key);
			QI(uk, lb_I_Actions, appActions)
		}
		
		
		if (appActions != NULL) {
			appActions->selectById(getActionTargetIDLong(reversed_event));
			_LOG << "Returning action source by event mapping." LOG_
			return appActions->get_source();
		}
	}
	
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
		return strdup("Error");
	}

	database->init();
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);	

	UAP(lb_I_Query, query)
	
	query = database->getQuery("lbDMF", 0);
	
	char buf[] = "select source from actions where id = %s";
	
	char* buffer = (char*) malloc(strlen(buf)+20);
	char* targetID = getActionTargetID(reversed_event);
	sprintf(buffer, buf, targetID);

	query->query(buffer);

	free(buffer);
	free(targetID);
	
	if (((err = query->first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
	
		UAP(lb_I_String, source)
		
		source = query->getAsString(1);
		
		source->trim();
				
		return strdup(source->charrep());
	}
	
	return strdup("");
}
/*...e*/
/*...schar\42\ FormularActions\58\\58\getActionID\40\char\42\ what\41\:0:*/
long FormularActions::getActionID(const char* what) {
	lbErrCodes err = ERR_NONE;
	
	// Get it from the foreign key in formular_actions
	return getActionTargetIDLong(what);
}
/*...e*/

#endif
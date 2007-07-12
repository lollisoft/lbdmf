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



/*...slb_I_Action\42\ FormularActions\58\\58\getAction\40\char\42\ id\41\:0:*/
lb_I_Action* FormularActions::getAction(char* id) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Unknown, uk)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ID)
	UAP(lb_I_KeyBase, key)
	ID->setData(id);
	QI(ID, lb_I_KeyBase, key)

	lb_I_Action* action;
	
	if (actions == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, actions)
	}
	
	if (actions->exists(&key) == 0) {
		lbAction* _action = new lbAction();
		_action->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
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
/*...schar\42\ FormularActions\58\\58\getActionTargetID\40\char\42\ what\41\:0:*/
char* FormularActions::getActionTargetID(char* what) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_String, What)
	
	What->setData(what);
	What->trim();

	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
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
char* FormularActions::getActionSourceDataField(char* what) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_Database, database)
	
	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);	

	UAP(lb_I_Query, query)
	
	query = database->getQuery("lbDMF", 0);
	
	char buf[] = "select source from actions where id = %s";
	
	char* buffer = (char*) malloc(strlen(buf)+20);
	
	sprintf(buffer, buf, getActionTargetID(what));

	query->query(buffer);

	free(buffer);
	
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
char* FormularActions::getActionID(char* what) {
	lbErrCodes err = ERR_NONE;
	
	// Get it from the foreign key in formular_actions
	return getActionTargetID(what);
}
/*...e*/

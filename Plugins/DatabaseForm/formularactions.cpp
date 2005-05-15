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
	
	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);	

	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	query = database->getQuery(0);
	
	char buf[] = "select id from action_target where what = '%s'";
	
	char* buffer = (char*) malloc(strlen(buf)+strlen(What->charrep())+1);
	
	sprintf(buffer, buf, What->charrep());
	
	query->query(buffer);
	
	if (((err = query->first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
	
		UAP(lb_I_String, source, __FILE__, __LINE__)
		
		source = query->getAsString(1);
		
		return strdup(source->charrep());
	}
	
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
	
	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);	

	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	query = database->getQuery(0);
	
	char buf[] = "select source from actions where target = %s";
	
	char* buffer = (char*) malloc(strlen(buf)+20);
	
	sprintf(buffer, buf, getActionTargetID(what));

	query->query(buffer);
	
	if (((err = query->first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
	
		UAP(lb_I_String, source, __FILE__, __LINE__)
		
		source = query->getAsString(1);
		
		source->trim();
				
		return strdup(source->charrep());
	}
	
	return strdup("");
}
/*...e*/
/*...e*/

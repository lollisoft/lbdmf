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


/*...sFormularFieldInformation\58\\58\FormularFieldInformation\40\char const \42\ formularname\44\ lb_I_Query\42\ query\41\:0:*/
FormularFieldInformation::FormularFieldInformation(char const * formularname, lb_I_Query* query) {

	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Database, database)

	REQUEST(getModuleInstance(), lb_I_Container, ROFields)
	REQUEST(getModuleInstance(), lb_I_Container, SCFields)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

	UAP(lb_I_Query, ROquery, __FILE__, __LINE__)

	ROquery = database->getQuery(0);

	char buf[] = "select tablename, name, \"specialColumn\", \"controlType\", ro from column_types";

	ROquery->query(buf);
	
	err = ROquery->first();

	while (err == ERR_NONE) {
/*...sGet row data:16:*/
	        UAP(lb_I_String, tablename, __FILE__, __LINE__)
	        UAP(lb_I_String, fieldname, __FILE__, __LINE__)
	        UAP(lb_I_String, specialColumn, __FILE__, __LINE__)
	        UAP(lb_I_String, columnType, __FILE__, __LINE__)
	        UAP(lb_I_String, ro, __FILE__, __LINE__)

	        tablename = ROquery->getAsString(1);
		fieldname = ROquery->getAsString(2);
		specialColumn = ROquery->getAsString(3);
		columnType = ROquery->getAsString(4);
		ro = ROquery->getAsString(5);

		fieldname->trim();
		columnType->trim();

/*...e*/

		for (int i = 1; i <= query->getColumns(); i++) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, col)
			
			col->setData(query->getColumnName(i));

/*...sCheck for readonly column:24:*/
			if ((strcmp(col->charrep(), fieldname->charrep()) == 0) && (strcmp("true", ro->charrep()) == 0)) {
				UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
				UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
				
				QI(col, lb_I_KeyBase, key, __FILE__, __LINE__)
				QI(col, lb_I_Unknown, uk, __FILE__, __LINE__)
				
				ROFields->insert(&uk, &key);
			}
/*...e*/

/*...sCheck for special column:24:*/
			if ((strcmp(col->charrep(), fieldname->charrep()) == 0) && (strcmp("true", specialColumn->charrep()) == 0)) {
				UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
				UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
				
				QI(col, lb_I_KeyBase, key, __FILE__, __LINE__)
				QI(columnType, lb_I_Unknown, uk, __FILE__, __LINE__)
				
				SCFields->insert(&uk, &key);
			}
/*...e*/
		}		
		err = ROquery->next();
	}
	
	if (err == WARN_DB_NODATA) {
/*...sGet row data:16:*/
                UAP(lb_I_String, tablename, __FILE__, __LINE__)
                UAP(lb_I_String, fieldname, __FILE__, __LINE__)
		UAP(lb_I_String, specialColumn, __FILE__, __LINE__)
		UAP(lb_I_String, columnType, __FILE__, __LINE__)
		UAP(lb_I_String, ro, __FILE__, __LINE__)
		
                tablename = ROquery->getAsString(1);
                fieldname = ROquery->getAsString(2);
		specialColumn = ROquery->getAsString(3);
		columnType = ROquery->getAsString(4);
		ro = ROquery->getAsString(5);

		fieldname->trim();
		columnType->trim();

/*...e*/
		
                for (int i = 1; i <= query->getColumns(); i++) {
                        UAP_REQUEST(getModuleInstance(), lb_I_String, col)

                        col->setData(query->getColumnName(i));
			
/*...sCheck for readonly column:24:*/
			if ((strcmp(col->charrep(), fieldname->charrep()) == 0) && (strcmp("true", ro->charrep()) == 0)) {
                                UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
                                UAP(lb_I_Unknown, uk, __FILE__, __LINE__)

                                QI(col, lb_I_KeyBase, key, __FILE__, __LINE__)
                                QI(col, lb_I_Unknown, uk, __FILE__, __LINE__)

                                ROFields->insert(&uk, &key);
                        }
/*...e*/

/*...sCheck for special column:24:*/
			if ((strcmp(col->charrep(), fieldname->charrep()) == 0) && (strcmp("true", specialColumn->charrep()) == 0)) {
				UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
				UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
				
				QI(col, lb_I_KeyBase, key, __FILE__, __LINE__)
				QI(columnType, lb_I_Unknown, uk, __FILE__, __LINE__)
				
				SCFields->insert(&uk, &key);
			}
/*...e*/
                }
	}
}
/*...e*/

/*...sbool FormularFieldInformation\58\\58\isReadonly\40\char\42\ field\41\:0:*/
bool FormularFieldInformation::isReadonly(char* field) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, f)
	f->setData(field);
	
	f->trim();
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(f, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	if (ROFields->exists(&key) == 1) {
		return true;
	}
	else {
		return false;
	}
	
}
/*...e*/
/*...sbool FormularFieldInformation\58\\58\isSpecialColumn\40\char\42\ field\41\:0:*/
bool FormularFieldInformation::isSpecialColumn(char* field) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, f)
	f->setData(field);
	
	f->trim();

	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(f, lb_I_KeyBase, key, __FILE__, __LINE__)
	
	if (SCFields->exists(&key) == 1) {
		return true;
	}

	return false;
}
/*...e*/
/*...schar\42\ FormularFieldInformation\58\\58\getControlType\40\char\42\ name\41\:0:*/
char* FormularFieldInformation::getControlType(char* name) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, f)
	f->setData(name);
	
	f->trim();
	
	UAP(lb_I_KeyBase, key, __FILE__, __LINE__)
	QI(f, lb_I_KeyBase, key, __FILE__, __LINE__)

	if (SCFields->exists(&key) == 1) {
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP_REQUEST(getModuleInstance(), lb_I_String, type)
		uk = SCFields->getElement(&key);
		QI(uk, lb_I_String, type, __FILE__, __LINE__)
		
		return strdup(type->charrep());
	}
	
	return "";
}
/*...e*/
/*...e*/

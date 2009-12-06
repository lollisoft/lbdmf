/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002 Lothar Behrens (lothar.behrens@lollisoft.de)

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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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
#pragma implementation "lbDatabaseReport.cpp"
#pragma interface "lbDatabaseReport.cpp"
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
#include "wx/splitter.h"
#include "wx/treectrl.h"
#include <wx/notebook.h>
#include <wx/splash.h>

/*...e*/

#ifndef OSX
#ifndef LINUX
//#include <wx/repwrt.h>
#endif
#endif

#include "wx/propgrid/propgrid.h"
#include <wxWrapperDLL.h>
#include <lbDatabaseReport.h>


/*
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBReportProperties)
	ADD_INTERFACE(lb_I_DBReportProperties)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes lbDBReportProperties::setData(lb_I_Unknown* uk) {
	return ERR_NOT_IMPLEMENTED;
}
*/
lbDBReportProperties::lbDBReportProperties() {
	REQUEST(getModuleInstance(), lb_I_Parameter, params)
	REQUEST(getModuleInstance(), lb_I_Parameter, textlines)
	REQUEST(getModuleInstance(), lb_I_Container, textblocks)
	_report = NULL;
}

lbDBReportProperties::~lbDBReportProperties() {
}

long lbDBReportProperties::getReportID(const char* name) {
	UAP(lb_I_Query, reportidQuery)
	UAP_REQUEST(getModuleInstance(), lb_I_String, q)
	
	reportidQuery = ReportCFGDB->getQuery("lbDMF", 0);
	
	*q = "select id from reports where name = '";
	*q += name;
	*q += "'";
	
	if (reportidQuery->query("lbDMF", q->charrep()) == ERR_NONE) {
		lbErrCodes err = ERR_NONE;
		
		err = reportidQuery->first();
		
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
		
			ID = reportidQuery->getAsLong(1);
			
			return ID->getData();
		} else {
			_LOG << "Error: Failed to retrieve report ID from given report name (no data found for query " << q->charrep() << ")." LOG_
		}
	
	} else {
		_LOG << "Error: Failed to retrieve report ID from given report name (Query failed)." LOG_
	}
	
	return (long) -1;
}


void  lbDBReportProperties::initReportParameters(long id) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, buffer)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	
	if (ReportCFGDB == NULL) {
		REQUEST(getModuleInstance(), lb_I_Database, ReportCFGDB)
		ReportCFGDB->init();
    }
	
	UAP(lb_I_Query, query)
	
	query = ReportCFGDB->getQuery("lbDMF", 0);
	
	ID->setData(id);
	
	*buffer = "select name, value from report_parameters where reportid = ";
	*buffer += ID->charrep();
	
	
	if (query->query(buffer->charrep()) == ERR_NONE) {
		lbErrCodes err = query->first();
		
		while(err == ERR_NONE) {
			UAP(lb_I_String, key)
			UAP(lb_I_String, value)
			
			key = query->getAsString(1);
			value = query->getAsString(2);
        	
			key->trim();
			value->trim();
			
			//_CL_LOG << "Insert in lbDBReportProperties: " << key->charrep() << " = " << value->charrep() LOG_
        	
			params->setUAPString(*&key, *&value);
			
			err = query->next();
		}
		
		if (err == WARN_DB_NODATA) {
			UAP(lb_I_String, key)
			UAP(lb_I_String, value)

			key = query->getAsString(1);
			value = query->getAsString(2);
			
			key->trim();
			value->trim();
			
			//_CL_LOG << "Insert in lbDBReportProperties: " << key->charrep() << " = " << value->charrep() LOG_
			
			params->setUAPString(*&key, *&value);
		}
	}
}

long  lbDBReportProperties::initData(char* report) {
	if (ReportCFGDB == NULL) {
		REQUEST(getModuleInstance(), lb_I_Database, ReportCFGDB)
		ReportCFGDB->init();
    }
	    
	UAP(lb_I_Query, query)

	if (_report) free(_report);
	if (report) _report = strdup(report);
	

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	ReportCFGDB->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = ReportCFGDB->getQuery("lbDMF", 0);
 
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)

	long id = getReportID(report);

	initReportParameters(id);
	
	return id;
}

void lbDBReportProperties::setIntParameter(char* name, int _value) {
	UAP_REQUEST(getModuleInstance(), lb_I_Database, ReportCFGDB)
	UAP(lb_I_Query, query)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, V)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	
	*key = name;
	V->setData(_value);
	*value = V->charrep();
	
	ReportCFGDB->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	ReportCFGDB->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
	
	query = ReportCFGDB->getQuery("lbDMF", 0);
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	ID->setData(getReportID(_report));
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
		
	*SQL = "insert into report_parameters (reportid, name, value) values (";
	*SQL += ID->charrep();
	*SQL += ", '";
	*SQL += name;
	*SQL += "', ";
	*SQL += value->charrep();
	*SQL += ")";
	
	query->skipFKCollecting();		
	query->query(SQL->charrep());
	query->enableFKCollecting();
	
	key->trim();
	value->trim();
	
	params->setUAPString(*&key, *&value);
}

int   lbDBReportProperties::getIntParameter(char* name) {
	int i = 0;
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	
	*key = name;
	
	*value = "12";
	
	if (params->getUAPString(*&key, *&value) != ERR_NONE) {
		setIntParameter(name, 12);
	}

	i = atoi(value->charrep());

	return i;
}

float lbDBReportProperties::getFloatParameter(char* name) {
	float i = 0;
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	
	*key = name;

	params->getUAPString(*&key, *&value);
	
	i = atoi(value->charrep());
	
	return i;
}

lb_I_String* lbDBReportProperties::getCharParameter(char* name) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	
	*key = name;
	
	params->getUAPString(*&key, *&value);
	
	value++;
	
	return value.getPtr();
}

lb_I_String* lbDBReportProperties::getTextLine(int line, char* name) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	
	*key = itoa(line);
	
	if (textlines->getUAPString(*&key, *&value) != ERR_NONE) return NULL;
	
	value++;
	
	return value.getPtr();
}

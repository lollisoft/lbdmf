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
/*...e*/

#ifndef OSX
#ifndef LINUX
#include <wx/repwrt.h>
#endif
#endif


#include <wxWrapperDLL.h>
#include <lbDatabaseReport.h>


/*...slbDBReportAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBReportAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDBReportAction, lbDBReportAction)

lbErrCodes LB_STDCALL lbDBReportAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDBReportAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbDBReportAction::lbDBReportAction() {
	ref = STARTREF;
	myActionID = NULL;
	report = NULL;
}

lbDBReportAction::~lbDBReportAction() {
	_CL_LOG << "lbDBReportAction::~lbDBReportAction() called." LOG_
	free(myActionID);

	if (report != NULL) { 
		_CL_LOG << "Destroy a report..." LOG_
		report->destroy();
	}
}

void LB_STDCALL lbDBReportAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDBReportAction::setActionID(char* id) {
	free(myActionID);
	
	if ((id != NULL) && (strlen(id) > 0)) {
		myActionID = strdup(id);
	} else {
		_CL_LOG << "Error: Got an invalid action ID!" LOG_
	}
}

/*...svoid LB_STDCALL lbDBReportAction\58\\58\openReport\40\lb_I_String\42\ reportname\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDBReportAction::openReport(lb_I_String* reportname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;

	if (report != NULL) {
		#ifdef bla
		
		_CL_VERBOSE << "Show previously created form." LOG_
	
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("source Form");
		params->getUAPString(*&parameter, *&masterForm);
		
		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();
		
		report->setName(reportname->charrep(), parameter->charrep());

		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
		UAP(lb_I_GUI, gui, __FILE__, __LINE__)
		
		meta->getGUI(&gui);

		// ??
		//lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		//detailForm->setForm(f, *&params);
		
		report->update();
		#endif
		
		report->show();	
	} else {
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

		parameter->setData("DBName");
		params->getUAPString(*&parameter, *&DBName);
		parameter->setData("DBUser");
		params->getUAPString(*&parameter, *&DBUser);
		parameter->setData("DBPass");
		params->getUAPString(*&parameter, *&DBPass);
		parameter->setData("source Form");

		/* This form contains the data for the report.
		 *
		 * Either the single row, or the query string.
		 */

		params->getUAPString(*&parameter, *&masterForm); 
		
		parameter->setData("source field");
		params->getUAPString(*&parameter, *&SourceFieldName);
		parameter->setData("source value");
		params->getUAPString(*&parameter, *&SourceFieldValue);
		parameter->setData("application");
		params->getUAPString(*&parameter, *&app);

/*...sGet the SQL query based on formular name\44\ application name\46\:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

		// Do I only print the report for current row (SourceFieldValue) ?

		// This report needs it's parent form. (Unsave cast)
		//lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

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
						strlen(reportname->charrep())+1);
		
		buffer[0] = 0;
		
		sprintf(buffer, b, user->charrep(), app->charrep(), reportname->charrep());
		
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

		_CL_LOG << "Try to open report '" << reportname->charrep() << "'." LOG_

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

				UAP(lb_I_Query, query1, __FILE__, __LINE__)

				query1 = database->getQuery(0);

				err = query1->query(buffer);
/*...e*/
				
				if (err == ERR_NONE) {
/*...sTake result as the SQL query parameter for the report data:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl, __FILE__, __LINE__)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query1->first();
					
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
/*...sTry load the report and make basic setup:88:*/
						UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
						
						sql = query1->getAsString(1);

						pl = PM->getFirstMatchingPlugin("lb_I_DatabaseReport", "GUI");
						
						uk = pl->getImplementation();
						
						UAP(lb_I_DatabaseReport, DBReport, __FILE__, __LINE__)
						QI(uk, lb_I_DatabaseReport, DBReport, __FILE__, __LINE__)
						
						DBReport++;
						
						report = DBReport.getPtr();

						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						
						// Name also is the identifer for the report configuration.
						
						report->setName(reportname->charrep(), parameter->charrep());

						/* Set the other information of master / detail form here
						
						   There is a problem for forms, if the foreign key is not
						   shown in it. In that case the relation could not full filled
						   by the add action.
						   
						   The only way may be any kind of temporal default value.
						*/

						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui, __FILE__, __LINE__)

						meta->getGUI(&gui);

						report->setFrame(gui->getFrame());
						
						/* Here it would be better to preset the where clause columns
						   and values. Then the internal proccess of building the report
						   could be done only once. */
						
						// As a sample, here the reservations for customer with id = 4
						// should be printed.
						//report->addCondition("kundenid", "4");
						
						SourceFieldName->trim();
						
						if (strcmp(SourceFieldName->charrep(), "") != 0)
							report->addAndCondition(SourceFieldName->charrep(), SourceFieldValue->charrep());
						
						report->init(sql->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());
/*...e*/
						
						// Get the related table for the source field
						
						report->show();
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

/*...svoid LB_STDCALL lbDBReportAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDBReportAction::execute(lb_I_Parameter* params) {
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
			_CL_LOG << "Open report in while loop." LOG_
/*...sFor each row open the report with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();

			openReport(*&what, *&params);
			
			err = query->next();
/*...e*/
		}
		
		if (err == WARN_DB_NODATA) {
			_CL_LOG << "Open report in WARN_DB_NODATA." LOG_
/*...sOpen the report with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			
			what = query->getAsString(1);
			what->trim();
			
			openReport(*&what, *&params);
/*...e*/
		}
	}
}
/*...e*/
/*...e*/

/*...sclass lbPluginDatabaseReport implementation:0:*/
/*...slbPluginDatabaseReport:0:*/
class lbPluginDatabaseReport : public virtual lb_I_PluginImpl {
public:
	lbPluginDatabaseReport();
	
	virtual ~lbPluginDatabaseReport();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbReport, __FILE__, __LINE__)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseReport)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseReport, lbPluginDatabaseReport)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseReport\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseReport::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDatabaseReport::setData(...) called.\n" LOG_

	if (dbReport == NULL) {
		_CL_VERBOSE << "ERROR: Cloning database report plugin without an instance to the report it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseReport::lbPluginDatabaseReport() {
	_CL_VERBOSE << "lbPluginDatabaseReport::lbPluginDatabaseReport() called.\n" LOG_
	dbReport = NULL;
	ref = STARTREF;
}

lbPluginDatabaseReport::~lbPluginDatabaseReport() {
	_CL_VERBOSE << "lbPluginDatabaseReport::~lbPluginDatabaseReport() called.\n" LOG_
}

void LB_STDCALL lbPluginDatabaseReport::initialize() {
}
	
bool LB_STDCALL lbPluginDatabaseReport::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseReport\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseReport::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lb_I_Unknown* LB_STDCALL lbPluginDatabaseReport::peekImplementation() called." LOG_

	if (dbReport == NULL) {
		lbDatabaseReport* _dbReport = new lbDatabaseReport();
		_dbReport->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_dbReport, lb_I_Unknown, dbReport, __FILE__, __LINE__)
	} else {
		_CL_VERBOSE << "lbPluginDatabaseReport::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return dbReport.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseReport\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseReport::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lb_I_Unknown* LB_STDCALL lbPluginDatabaseReport::getImplementation() called." LOG_
	
	if (dbReport == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDatabaseReport* _dbReport = new lbDatabaseReport();
		_dbReport->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(_dbReport, lb_I_Unknown, dbReport, __FILE__, __LINE__)
	}
	
	lb_I_Unknown* r = dbReport.getPtr();
	dbReport == NULL;
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseReport::releaseImplementation() {
}
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseReport)
        ADD_INTERFACE(lb_I_DatabaseReport)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseReport, lbDatabaseReport)

/*...sColumn positions:0:*/
#define   LPI6      4.23
#define   COL1X     0
#define   COL2X     13
#define   COL3X     54
#define   COL4X     80
#define   COL5X     111
#define   COL6X     150
#define   COL1WID   12
#define   COL2WID   40
#define   COL3WID   15
#define   COL4WID   30
#define   COL5WID   30
#define   COL6WID   40
#define   COLHDRY   18
#define   COLY      25
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseReport\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseReport::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbDatabaseReport::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseReport\58\\58\lbDatabaseReport\40\\41\:0:*/
lbDatabaseReport::lbDatabaseReport() {
	ref = STARTREF;
	frame = NULL;
	ReportName = NULL;
	ReportFileName = NULL;
	untranslated_ReportName = NULL;
	hasConditions = false;
	
	_CL_LOG << "lbDatabaseReport::lbDatabaseReport() called." LOG_
}
/*...e*/

/*...slbDatabaseReport\58\\58\\126\lbDatabaseReport\40\\41\:0:*/
lbDatabaseReport::~lbDatabaseReport() {
	_CL_LOG << "lbDatabaseReport::~lbDatabaseReport() called." LOG_
}
/*...e*/

void LB_STDCALL lbDatabaseReport::destroy() {
}

void LB_STDCALL lbDatabaseReport::setFrame(lb_I_Unknown* _frame) {
	lb_wxFrame* __frame = (lb_wxFrame*) _frame;
	frame = __frame->getPeer();
}

/*...svoid LB_STDCALL lbDatabaseReport\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabaseReport::init(char* SQLString, char* DBName, char* DBUser, char* DBPass) {
	_CL_LOG << "lbDatabaseReport::init('" << 
			SQLString << "', '" << 
			DBName << "', '" << 
			DBUser << "', '*****') for '" << untranslated_ReportName << "' called." LOG_

	int colstepHDR = 41;

#ifdef OSX
	int colstep = 30;
#endif
#ifndef OSX
	int colstep = 40;
#endif
	
	wxLogNull		logNull;

	wxFont			fntBig(  12, wxDECORATIVE, wxITALIC, wxBOLD, true );
	wxFont			fntSmall( 6, wxSWISS,      wxNORMAL, wxNORMAL     );
	wxFont			fntHdr(  10, wxSWISS,      wxNORMAL, wxBOLD, true );

	wxReportWriter* pReport = new wxReportWriter(0, wxT("Test Report"), wxPoint(10,10), wxSize( 100, 100 ) );
	pReport->SetPath( wxT(".") );


/*...sHeader:8:*/
	// -----------------------
	//  HEADER (on each page)
	// -----------------------

	pObj = new wxReportObj(  0,  0, 100, 30 );
	pObj->SetBitmap( wxT("PLG.png") );
	pReport->AddHeaderObj( pObj );

	pObj = new wxReportObj( 70, 7, 50, 20 );
	pObj->SetData( wxString(untranslated_ReportName) );
	pObj->SetFont( &fntBig );
	pReport->AddHeaderObj( pObj );

	pObj = new wxReportObj( 120, 7, 50, 20 );
	pObj->SetPgNum( wxT("Page") );
	pObj->SetRightAlign();
	pReport->AddHeaderObj( pObj );
/*...e*/

	// Column header

	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, query, __FILE__, __LINE__)
	
	database->init();
	
	database->connect(DBName, DBUser, DBPass);
	
	query = database->getQuery(0);
	
	lbErrCodes err;
	err = query->query(SQLString);

	if ((hasConditions) && (err == ERR_NONE)) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, newQuery)
		
		bool isChar = query->getColumnType(AndConditionColumn->charrep()) == lb_I_Query::lbDBColumnChar;
		
		// Could not set whole string to lower case, because there may be a case where
		// the case sensity of columns is relevant.
		
		char* temp = NULL;

		char* order = strstr(SQLString, "order");
		
		if (order) {
			char* temp = strdup(order);
			order[0] = 0;
		}
		
		*newQuery = SQLString;
		*newQuery += " where ";
		*newQuery += AndConditionColumn->charrep();

		if (isChar) 
			*newQuery += " = '";
		else
			*newQuery += " = ";

		*newQuery += AndConditionValue->charrep();

		if (isChar) 
			*newQuery += "'";

		if (temp) {
			*newQuery += " ";
			*newQuery += temp;
			
			free(temp);
		}
			
		query = database->getQuery(0);
		
		_CL_LOG << "SQL string: " << newQuery->charrep() LOG_ 
		
		err = query->query(newQuery->charrep());
	} else {
		_CL_LOG << "SQL string: " << SQLString LOG_
	}
	
	if (err == ERR_NONE) {
/*...sBuild the report:16:*/
/*...sBuild up header:32:*/
		int cols = query->getColumns();

		// Alloc the value array
		
		strValue = new wxString* [cols];

		for (int i = 1; i <= cols; i++) {
			pObj = new wxReportObj( colstepHDR * i - colstepHDR, COLHDRY, colstepHDR, 5 );
			pObj->SetData(query->getColumnName(i));
			pObj->SetFont( &fntHdr );
			pObj->SetRightAlign();
			pReport->AddHeaderObj( pObj );
			
			strValue[i-1] = new wxString;
		}
/*...e*/

/*...sFOOTER \40\on each page\41\:32:*/
		// -----------------------
		//  FOOTER (on each page)
		// -----------------------
		pObj = new wxReportObj( 0, 12, 170, 0 );
		pObj->SetLine();
		pReport->AddFooterObj( pObj );

		pObj = new wxReportObj( 0, 8, 110, 20 );
		pObj->SetData( wxT("lbDMF Reportwriter") );
		pObj->SetFont( &fntSmall );
		pReport->AddFooterObj( pObj );

		pObj = new wxReportObj( 120, 8, 50, 20 );
		pObj->SetPgNum( wxT("Page") );
		pObj->SetFont( &fntSmall );
		pObj->SetRightAlign();
		pReport->AddFooterObj( pObj );

		pObj = new wxReportObj( 60, 8, 60, 20 );
		pObj->SetRepDate();
		pObj->SetFont( &fntSmall );
		pObj->SetRightAlign();
		pReport->AddFooterObj( pObj );
/*...e*/
	
	
		// -----------------------
		//  MISC
		// -----------------------
		pReport->SetDateFormat( wxT("%d.%m.%Y  %H:%M:%S") );
		pReport->SetDate( wxDateTime::Now() );
		pReport->SetUser( wxT("Lothar Behrens") );
		pReport->SetInfo( wxT("A Test Report") );
								
		pReport->DefineSection();

		pObj = new wxReportObj( colstep * 1 - colstep, COLY, colstep, 6 );
		pObj->SetRef( strValue[0] );
		pObj->SetIncrements( 0.0, LPI6 );
		pObj->SetRightAlign();
		pReport->AddDataObj( pObj );
	
		for (int i = 2; i <= cols; i++) {
			pObj = new wxReportObj( (colstep * i - colstep) + 1, COLY, colstep, 6 );
			pObj->SetRef( strValue[i-1] );
			pObj->SetIncrements( 0.0, LPI6 );
			pObj->SetRightAlign();
			pReport->AddDataObj( pObj );
		}
	
		err = query->first();

		pReport->BeginDataSection();

/*...sAll lines exept last:32:*/
		while (err == ERR_NONE) {
			for (int i = 1; i < cols; i++) {
				UAP(lb_I_String, value, __FILE__, __LINE__)
			
				value = query->getAsString(i);
			
				// -----------------------
				//  DATA...
				// -----------------------
				
				printf("%s|", value->charrep());
				
				*(strValue[i-1]) = value->charrep();
			}
			
			UAP(lb_I_String, value, __FILE__, __LINE__)
			
			value = query->getAsString(cols);
			
			// -----------------------
			//  DATA...
			// -----------------------
			
			printf("%s\n", value->charrep());
			
			*(strValue[cols-1]) = value->charrep();
			
			pReport->SaveData();
			
			err = query->next();
		}
/*...e*/
		
/*...sLast line:32:*/
		if (err == WARN_DB_NODATA) {
			for (int i = 1; i <= cols; i++) {
				UAP(lb_I_String, value, __FILE__, __LINE__)
			
				value = query->getAsString(i);
			
				// -----------------------
				//  DATA...
				// -----------------------

				*(strValue[i-1]) = value->charrep();
				
			}
			
			pReport->SaveData();
		}
/*...e*/
		
		for (int i = 1; i < cols; i++) {
			delete strValue[cols-1];
		}

		delete [] strValue;
/*...e*/
	} else {
		_CL_LOG << "Error: Query returns no data!" LOG_
	}

	pReport->HorizLine();
				
	pReport->FinishSection();

	pReport->FinishReport();
		
	ReportFileName = strdup(pReport->FinalDestination().c_str());

	_CL_LOG << "Created a report file: '" << ReportFileName << "'" LOG_

	delete pReport;
	pReport = NULL;
}
/*...e*/

void LB_STDCALL lbDatabaseReport::addAndCondition(char* column, char* value) {
	// This is for simplicy only.

	hasConditions = true;
	
	if (AndConditionColumn == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, AndConditionColumn)
		REQUEST(manager.getPtr(), lb_I_String, AndConditionValue)
	}
	
	*AndConditionColumn = column;
	*AndConditionValue = value;
}

void LB_STDCALL lbDatabaseReport::update() {

}

/*...svoid LB_STDCALL lbDatabaseReport\58\\58\show\40\\41\:0:*/
void LB_STDCALL lbDatabaseReport::show() {
	_CL_LOG << "Try to show the report..." LOG_
	wxReportWriter* pReport = new wxReportWriter(
		frame,
		ReportFileName,
		wxPoint(10,10),
		wxSize( 100, 100 ) );
	
	pReport->SetupReport( ReportFileName );
	pReport->PrintPreview();
	
}
/*...e*/

void LB_STDCALL lbDatabaseReport::print() {
//	pReport->Print();
//	pReport->FinishReport();
}

/*...slbErrCodes LB_STDCALL lbDatabaseReport\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseReport::setName(char const * name, char const * appention) {
	free(ReportName);
	free(untranslated_ReportName);
		
	char* temp = strdup(_trans((char*) name));

	if (appention) {
		ReportName = (char*) malloc(1+strlen(temp)+strlen(appention));
		untranslated_ReportName = (char*) malloc(1+strlen(name)+strlen(appention));
	} else {
		ReportName = (char*) malloc(1+strlen(temp));
		untranslated_ReportName = (char*) malloc(1+strlen(name));
	}
	
	ReportName[0] = 0;
	strcat(ReportName, temp);
	if (appention) strcat(ReportName, appention);
	free(temp);
		
	untranslated_ReportName[0] = 0;
	strcat(untranslated_ReportName, name);
	if (appention) strcat(untranslated_ReportName, appention);
		
	return ERR_NONE;
}
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

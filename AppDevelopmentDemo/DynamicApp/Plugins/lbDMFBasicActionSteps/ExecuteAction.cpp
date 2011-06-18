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
/*...e*/

#include <ExecuteAction.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbExecuteAction)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbExecuteAction, lbExecuteAction)

lbErrCodes LB_STDCALL lbExecuteAction::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbExecuteAction::setData(lb_I_Unknown* uk) not implemented." LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbExecuteAction::lbExecuteAction() {
	ref = STARTREF;
	myActionID = -1;
}

lbExecuteAction::~lbExecuteAction() {
}

void LB_STDCALL lbExecuteAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbExecuteAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbExecuteAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
}

void LB_STDCALL lbExecuteAction::setParameter(lb_I_ActionStep_Parameters* myParams) {
	replacers = myParams;
}

/** \brief Execute an application.
 * This function starts an external application. Using external applications enhance the functionality of this application by not touching
 * the application.
 *
 * A sample to start an external application on Mac OS X is a report engine. Using OpenRPT from xTuple the action definition looks like this:
 *
 * actions entry:
 * 208568;11;"Formulare dieser Anwendung drucken";"anwendungid";"";1
 *
 * action type entry:
 * 208567;15;"CreateReport";"instanceOflbExecuteAction";"lbDatabaseForm"
 *
 * action step entry
 * 208569;33;"Print";1;"/Applications/xTuple/rptrender.app/Contents/MacOS/rptrender -databaseURL=pgsql://vmhost:5432/lbdmf -username=dba -passwd=trainres -loadfromdb={ReportName} -printerName={PrinterName} -printpreview -close -param=filter:int={anwendungid}";15;11
 *
 * action step parameter entries:
 * 208586;25;"PrinterName";"vmhost";"lb_I_String";"A description ...";33
 * 208587;26;"ReportName";"Formulare";"lb_I_String";"A description ...";33
 *
 * The used report must be defined in the report table. The best is to use OpenRPT to design it.
 * The report table must be created manually yet and looks like this:
 *
 * -- Table: report
 *
 * -- DROP TABLE report;
 *
 * CREATE TABLE report
 * (
 * report_id integer NOT NULL DEFAULT nextval(('report_report_id_seq'::text)::regclass),
 * report_name text,
 * report_sys boolean,
 * report_source text,
 * report_descrip text,
 * report_grade integer NOT NULL,
 * report_loaddate timestamp without time zone,
 * CONSTRAINT report_pkey PRIMARY KEY (report_id)
 * )
 * WITH (OIDS=TRUE);
 * ALTER TABLE report OWNER TO dba;
 * GRANT ALL ON TABLE report TO dba;
 * COMMENT ON TABLE report IS 'Report definition information';
 *
 * -- Index: report_name_grade_idx
 *
 * -- DROP INDEX report_name_grade_idx;
 *
 * CREATE UNIQUE INDEX report_name_grade_idx
 * ON report
 * USING btree
 * (report_name, report_grade);
 */
long LB_STDCALL lbExecuteAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbExecuteAction::execute()" LOG_
	
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
			UAP_REQUEST(getModuleInstance(), lb_I_String, s)
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)
			
			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();
			
			*msg = "Execute application (";
			*msg += What->charrep();
			*msg += ")";
			
			meta->setStatusText("Info", msg->charrep());
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			
			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";
			
			
			*s = What->charrep();
			
			// Replaces a placeholder that belongs to value from the form (SourceFieldValue)
			What->replace(rep->charrep(), SourceFieldValue->charrep());
			
			
			if (replacers != NULL) {
				// Build up the required parameters that may occur in What
				int I = 0;
				while (replacers->hasMoreActionStepParameters()) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, value)
					UAP_REQUEST(getModuleInstance(), lb_I_String, name)
					
					UAP(lb_I_String, valueSubstituted)
					
					replacers->setNextActionStepParameter();
					
					*name = replacers->getActionStepParameterName();
					*value = replacers->getActionStepParameterValue();
					
					_LOG << "Prepare parameter " << name->charrep() << " with value " << value->charrep() << " for application." LOG_
					
					params->setUAPString(*&name, *&value);
				}
				
				What->substitutePlaceholder(*&params);
				
				_LOG << "Replaced placeholders for execution command: " << What->charrep() LOG_
			}
			
			//\todo Implement an execute if not yet done.
			long r = 0; //wxExecute(What->charrep()); // probably add parameters for filter:  -param=anwendungid:{anwendungid}
			
			if (r != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, name)
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				
				*name = "result";
				*value = "0";
				
				params->setUAPString(*&name, *&value);
			}
			
			return -1;
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
		return 0;
	}
	UAP(lb_I_Query, query)
	
	
	
	database->init();
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
	
	query = database->getQuery("lbDMF", 0);
	
	char buf[] = "select what from action_steps where id = %d order by a_order_nr";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);
	
	UAP(lb_I_Database, db)
	dbbackend = meta->getSystemDatabaseBackend();
	
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
		return 0;
	}
	db->init();
	if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
		return 0;
	}
	
	if (query->query(q) == ERR_NONE) {
		
		lbErrCodes err = query->first();
		
		while(err == ERR_NONE) {
			/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(getModuleInstance(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();
			
			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";
			
			what->replace(rep->charrep(), SourceFieldValue->charrep());
			
			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();

			if ((err = q->query(what->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += what->charrep();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
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
			
			what->replace(rep->charrep(), SourceFieldValue->charrep());
			
			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();

			if (q->query(what->charrep(), false) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += what->charrep();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
			}
			q->enableFKCollecting();
			/*...e*/
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
		
		ID->setData(myActionID);
		
		*msg = "lbExecuteAction::execute(";
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
	return -1;
}

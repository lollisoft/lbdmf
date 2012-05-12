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

#include <lbSqlQueryAction.h>

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
	
	myActionID = -1;
	
	;
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

void LB_STDCALL lbSQLQueryAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
}

void LB_STDCALL lbSQLQueryAction::setParameter(lb_I_ActionStep_Parameters* myParams) {

}

long LB_STDCALL lbSQLQueryAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbSQLQueryAction::execute()" LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFormName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(getModuleInstance(), lb_I_String, app)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)

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
				return 0;
			}
			db->init();
			if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
				meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
				return 0;
			}

			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";

			UAP_REQUEST(getModuleInstance(), lb_I_String, s)
			*s = What->charrep();

			s->replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*What = s->charrep();

			if ((err = q->query(What->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s->charrep();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
			}
			q->enableFKCollecting();

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
		free(q);
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

			UAP_REQUEST(getModuleInstance(), lb_I_String, s)
			*s = what->charrep();

			s->replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s->charrep();
			if ((err = q->query(what->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s->charrep();
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
			UAP_REQUEST(getModuleInstance(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";

			UAP_REQUEST(getModuleInstance(), lb_I_String, s)
			*s = what->charrep();

			s->replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s->charrep();
			if (q->query(what->charrep(), false) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s->charrep();
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
	return -1;
}
/*...e*/
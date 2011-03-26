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

#include <lbDatabaseForm.h>

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
bool LB_STDCALL lbDetailFormAction::openDetailForm(lb_I_String* formularname, lb_I_Parameter* params) {
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

	UAP(lb_I_GUI, gui)
	meta->getGUI(&gui);

	UAP(lb_I_DatabaseForm, df)
	df = gui->findDBForm(formularname->charrep());

	if (df == NULL) {
		_LOG << "Detailform '" << formularname->charrep() << "' nicht gefunden. Setze variable zur√ºck." LOG_
		detailForm = NULL;
	}

	if (df != detailForm) {
		// The form may physically another instance.
		detailForm = df.getPtr();
	}

	if (detailForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_

		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();

		detailForm->setName(formularname->charrep(), parameter->charrep());

		_LOG << "Search the masterform '" << masterForm->charrep() << "'." LOG_

		lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		if (f == NULL) {
			_LOG << "Error: Bail out, no master form found." LOG_
			return false;
		}

		detailForm->setMasterForm(f, *&params);

		detailForm->updateFromMaster();
		gui->showForm(formularname->charrep());
	} else {
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
							return false;
						}
						detailForm = form.getPtr();
						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						form->setName(formularname->charrep(), parameter->charrep());
						_LOG << "Search the masterform '" << masterForm->charrep() << "'." LOG_
						f = gui->findDBForm(masterForm->charrep());
						if (f == NULL) {
							_LOG << "Error: Bail out, no master form found." LOG_

							if (detailForm != NULL) {
								// Cleanup
								detailForm->destroy();
							}

							return false;
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
						return true;
					}
				}
				meta->setStatusText("Info", "Did not found detailform.");
				return false;
			}
		}

		// - old database variant -

		_LOG << "Open detail form the old database way." LOG_

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
			return false;
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
							return false;
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

							return false;
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
						return true;
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
	return false;
}
/*...e*/

void LB_STDCALL lbDetailFormAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {

}

void LB_STDCALL lbDetailFormAction::setParameter(lb_I_ActionStep_Parameters* myParams) {

}


/*...svoid LB_STDCALL lbDetailFormAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
long LB_STDCALL lbDetailFormAction::execute(lb_I_Parameter* params) {
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
	return -1;
}
/*...e*/
/*...e*/

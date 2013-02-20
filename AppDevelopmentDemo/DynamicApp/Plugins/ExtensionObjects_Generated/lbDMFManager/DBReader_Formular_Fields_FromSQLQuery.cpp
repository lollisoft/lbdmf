
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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/
#include <lbInterfaces-lbDMFManager.h>
#include <DBReader_Formular_Fields_FromSQLQuery.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_FieldsDBReaderExtension_BuildFromFormularParameter, Formular_FieldsDBReaderExtension_BuildFromFormularParameter)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_FieldsDBReaderExtension_BuildFromFormularParameter)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Formular_FieldsDBReaderExtension_BuildFromFormularParameter::Formular_FieldsDBReaderExtension_BuildFromFormularParameter() {
	_CL_VERBOSE << "Formular_FieldsDBReaderExtension_BuildFromFormularParameter::Formular_FieldsDBReaderExtension_BuildFromFormularParameter() called." LOG_
}

Formular_FieldsDBReaderExtension_BuildFromFormularParameter::~Formular_FieldsDBReaderExtension_BuildFromFormularParameter() {
	_CL_VERBOSE << "Formular_FieldsDBReaderExtension_BuildFromFormularParameter::~Formular_FieldsDBReaderExtension_BuildFromFormularParameter() called." LOG_
}

lbErrCodes LB_STDCALL Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Fields, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOwningObject() owning parameter is not a lb_I_Formular_Fields." LOG_
		}
	} else {
		_LOG << "Error: Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Formular_FieldsDBReaderExtension_BuildFromFormularParameter::setOperator() called with a NULL pointer." LOG_
	}
}

char* LB_STDCALL lookupParameter(lb_I_ApplicationParameter* from, const char* name, long ApplicationID) {
	from->finishIteration();
	
	while (from->hasMoreElements()) {
		from->setNextElement();
		if (from->get_anwendungid() == ApplicationID && strcmp(from->get_parametername(), name) == 0)
			return from->get_parametervalue();
	}
	_LOG << "lbDynamicApplication::getParameter(...) Error: Parameter not found." LOG_
	return NULL;
}

void LB_STDCALL Formular_FieldsDBReaderExtension_BuildFromFormularParameter::execute() {
	lbErrCodes err = ERR_NONE;
	bool showMessage = false;
	UAP_REQUEST(getModuleInstance(), lb_I_String, messageText)
	UAP(lb_I_Query, q)

	_LOG << "Formular_FieldsDBReaderExtension_BuildFromFormularParameter::execute() called." LOG_
	
	if (db == NULL) {
		_LOG << "Formular_FieldsDBReaderExtension_BuildFromFormularParameter::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	UAP(lb_I_ApplicationParameter, appParams)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
    UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, document)
	UAP(lb_I_Unknown, uk)

	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")

	dbOp->setContextNamespace("DatabaseInputStreamVisitor");
	dbOp->visit(*&appParams); // Do an additional load of application parameters. This avoids much code changes.

	uk = metaapp->getActiveDocument();

	if (uk == NULL) {
		_LOG << "Error: Expected an 'active document' here!" LOG_
		return;
	}

    QI(uk, lb_I_Parameter, document)


	/// \todo There is a problem when using Sqlite database wrapper and the cursor emulation.

	/*
	 * The where clause would propably replaced wrongly by the ID = 1 where clause.
	 */

	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();
	// Get all formulars, even one is custom
	if (q->query("select id, anwendungid from formulare") != ERR_NONE) {
		_LOG << "Error: Access to formular table failed. Read formulars would be skipped." LOG_
		return;
	}

	err = q->first();

	while (err == ERR_NONE) {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Long, AnwendungID)
		UAP(lb_I_Query, query_query)

		UAP_REQUEST(getModuleInstance(), lb_I_String, query)

		FormularID = q->getAsLong(1);
		AnwendungID = q->getAsLong(2);

		query_query = db->getQuery("lbDMF", 0);

		*query = "select parametervalue from formular_parameters where formularid = ";
		*query += FormularID->charrep();

		if (query_query->query(query->charrep()) == ERR_NONE) {
			// Query succeeded
			UAP(lb_I_String, formularquery)
			UAP(lb_I_Query, form_query)

			lbErrCodes qqerr = query_query->first();

			if ((qqerr == ERR_NONE) || (qqerr == WARN_DB_NODATA)) {
				// Get the stored query for the formular with id = FormularID
				formularquery = query_query->getAsString(1);

				UAP(lb_I_Database, customDB)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbname)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbuser)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbpass)

				*dbname = "";
				*dbuser = "";
				*dbpass = "";

///\todo There is a strange bug in overwriting the string anyhow within the call to setStatusText below.
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbbackend)
				UAP_REQUEST(getModuleInstance(), lb_I_String, sysdbbackend)
				
				*sysdbbackend = metaapp->getSystemDatabaseBackend();
				*dbbackend = metaapp->getApplicationDatabaseBackend();

				if (dbbackend->charrep() != NULL && strcmp(dbbackend->charrep(), "") != 0) {
					_LOG << "Info: Have got any AppParams from document used for plugin database backend." LOG_
				} else {
					_LOG << "Info: Have got any AppParams from document used for built in database backend." LOG_
				}

				*dbname = lookupParameter(*&appParams, "DBName", AnwendungID->getData());
				*dbuser = lookupParameter(*&appParams, "DBUser", AnwendungID->getData());
				*dbpass = lookupParameter(*&appParams, "DBPass", AnwendungID->getData());

				metaapp->setStatusText("Info", "Target database is application database ...");

				/************/

				if (strcmp(dbname->charrep(), "lbDMF") == 0) {
					// It is the system database
					if (sysdbbackend->charrep() != NULL && strcmp(sysdbbackend->charrep(), "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, sysdbbackend->charrep(), customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				} else {
					if (dbbackend->charrep() != NULL && strcmp(dbbackend->charrep(), "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend->charrep(), customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				}



				if (customDB == NULL) {
					_LOGERROR << "Error: Could not load database backend, either plugin or built in version. The sysdbbackend value was: " << sysdbbackend->charrep() LOG_
					return;
				}

				customDB->init();
				/************/

				if (dbbackend->charrep() != NULL && strcmp(dbbackend->charrep(), "") != 0) {
					// It is the plugin that currently only supports local Sqlite
					if ((strcmp(dbname->charrep(), "") == 0) || (customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						if (!showMessage) {
							*messageText = "Some of the designed applications do not have access to their databases.";
							showMessage = true;
						} else {
							*messageText += "\n\nDatabase missing: ";
							*messageText += dbname->charrep();
						}

						if (showMessage) {
							metaapp->msgBox("Error", messageText->charrep());
							return;
						}
						return;
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0); // Use retrieved database name
					}
				} else {
					if ((customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						if (!showMessage) {
							*messageText = "Some of the designed applications do not have access to their databases.";
							showMessage = true;
						} else {
							*messageText += "\n\nDatabase missing: ";
							*messageText += dbname->charrep();
						}
						
						if (showMessage) {
							metaapp->msgBox("Error", messageText->charrep());
							return;
						}
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0);
					}
				}


				form_query->enableFKCollecting();
				_LOG << "Execute query '" << formularquery->charrep() << "'" LOG_
				lbErrCodes errQuery = form_query->query(formularquery->charrep());
				_LOG << "Done executing query '" << formularquery->charrep() << "'" LOG_

				if ((errQuery == ERR_NONE) || (errQuery == ERR_DB_NODATA)) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						UAP(lb_I_String, name)
						UAP(lb_I_String, tablename)

						name = form_query->getColumnName(i);
						tablename = form_query->getTableName(name->charrep());

						_LOG << "Check if column " << name->charrep() << " from " << tablename->charrep() << " is a foreign column..." LOG_

						if (form_query->hasFKColumn(name->charrep()) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery("lbDMF", 0);

							_LOG << "Yes, is foreign column." LOG_

							t = form_query->getPKTable(name->charrep());
							c = form_query->getPKColumn(name->charrep());

							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;

							UAP(lb_I_String, T)

							T = form_query->getTableName(name->charrep());

							sprintf(buffer, "select pkname, pktable	from foreignkey_visibledata_mapping "
									"where fkname = '%s' and fktable = '%s'", name->charrep(), T->charrep());

							if (fkpkmapping_query->query(buffer) == ERR_NONE) {
								UAP(lb_I_String, PKName)
								UAP(lb_I_String, PKTable)
								lbErrCodes err = fkpkmapping_query->first();

								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									PKName = fkpkmapping_query->getAsString(1);
									PKTable = fkpkmapping_query->getAsString(2);

									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);

									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Bit", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Float", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "String", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Binary", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											_LOG << "Save the visible column into the internal object model. (" << name->charrep() << " in " << tablename->charrep() << " to " << PKName->charrep() << " in " << PKTable->charrep() << ")" LOG_
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Integer", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								} else {
									_LOG << "Yes, is foreign column, but no mapping defined." LOG_

									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);

									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											owningObject->add("", "", "Bit", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											owningObject->add("", "", "Float", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											owningObject->add("", "", "String", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											owningObject->add("", "", "Binary", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											owningObject->add("", "", "Integer", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							_LOG << "No, is not foreign column." LOG_

							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									owningObject->add("", "", "Bit", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									owningObject->add("", "", "Float", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									owningObject->add("", "", "String", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									owningObject->add("", "", "Binary", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;

								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									owningObject->add("", "", "Integer", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
					}
				} else {
					_LOG << "Error: Query '" << formularquery->charrep() << "' failed!" LOG_
				}
			}
		} else {
			_LOG << "Error: Query '" << query->charrep() << "' failed!" LOG_
		}
		err = q->next();
	}


	if (err == WARN_DB_NODATA) {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Long, AnwendungID)
		UAP(lb_I_Query, query_query)
		UAP_REQUEST(getModuleInstance(), lb_I_String, query)

		query_query = db->getQuery("lbDMF", 0);

		FormularID = q->getAsLong(1);
		AnwendungID = q->getAsLong(2);

		*query = "select parametervalue from formular_parameters where formularid = ";
		*query += FormularID->charrep();

		if (query_query->query(query->charrep()) == ERR_NONE) {
			// Query succeeded
			UAP(lb_I_String, formularquery)
			UAP(lb_I_Query, form_query)

			lbErrCodes qqerr = query_query->first();

			if ((qqerr == ERR_NONE) || (qqerr == WARN_DB_NODATA)) {
				// Get the stored query for the formular with id = FormularID
				formularquery = query_query->getAsString(1);
				
				UAP(lb_I_Database, customDB)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbname)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbuser)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbpass)
				
				*dbname = "";
				*dbuser = "";
				*dbpass = "";
				
				char* dbbackend = metaapp->getApplicationDatabaseBackend();
				char* sysdbbackend = metaapp->getSystemDatabaseBackend();
				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					_LOG << "Info: Have got any AppParams from document used for plugin database backend." LOG_
				} else {
					_LOG << "Info: Have got any AppParams from document used for built in database backend." LOG_
				}
				
				*dbname = lookupParameter(*&appParams, "DBName", AnwendungID->getData());
				*dbuser = lookupParameter(*&appParams, "DBUser", AnwendungID->getData());
				*dbpass = lookupParameter(*&appParams, "DBPass", AnwendungID->getData());
				
				metaapp->setStatusText("Info", "Target database is application database ...");
				
				/************/
				
				if (strcmp(dbname->charrep(), "lbDMF") == 0) {
					// It is the system database
					if (sysdbbackend != NULL && strcmp(sysdbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, sysdbbackend, customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				} else {
					if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				}
				
				
				
				if (customDB == NULL) {
					_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
					return;
				}
				
				customDB->init();
				/************/
				
				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					// It is the plugin that currently only supports local Sqlite
					if ((strcmp(dbname->charrep(), "") == 0) || (customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						if (!showMessage) {
							*messageText = "Some of the designed applications do not have access to their databases.";
							showMessage = true;
						} else {
							*messageText += "\n\nDatabase missing: ";
							*messageText += dbname->charrep();
						}
						
						if (showMessage) {
							metaapp->msgBox("Error", messageText->charrep());
							return;
						}
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0); // Use retrieved database name
					}
				} else {
					if ((customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						if (!showMessage) {
							*messageText = "Some of the designed applications do not have access to their databases.";
							showMessage = true;
						} else {
							*messageText += "\n\nDatabase missing: ";
							*messageText += dbname->charrep();
						}
						
						if (showMessage) {
							metaapp->msgBox("Error", messageText->charrep());
							return;
						}
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0);
					}
				}
				
				form_query->enableFKCollecting();

				lbErrCodes errQuery = form_query->query(formularquery->charrep());

				// The second case will never happen unless the query implementation will return WARN_DB_NODATA and query_query results into no data.
				// There is always a case of no data in the application tables, but there should always meta data available except the SQL of that query is wrong.
				if ((errQuery == ERR_NONE) || (errQuery == ERR_DB_NODATA)) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						UAP(lb_I_String, name)
						UAP(lb_I_String, tablename)

						name = form_query->getColumnName(i);
						tablename = form_query->getTableName(name->charrep());

						_LOG << "Check if column " << name->charrep() << " from " << tablename->charrep() << " is a foreign column..." LOG_

						if (form_query->hasFKColumn(name->charrep()) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery("lbDMF", 0);

							_LOG << "Yes, is foreign column." LOG_

							t = form_query->getPKTable(name->charrep());
							c = form_query->getPKColumn(name->charrep());

							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;

							UAP(lb_I_String, table_name)
							table_name = form_query->getTableName(name->charrep());
							
							sprintf(buffer, "select pkname, pktable	from foreignkey_visibledata_mapping "
									"where fkname = '%s' and fktable = '%s'", name->charrep(), table_name->charrep());

							if (fkpkmapping_query->query(buffer) == ERR_NONE) {
								UAP(lb_I_String, PKName)
								UAP(lb_I_String, PKTable)
								lbErrCodes err = fkpkmapping_query->first();

								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									PKName = fkpkmapping_query->getAsString(1);
									PKTable = fkpkmapping_query->getAsString(2);

									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);

									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Bit", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Float", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "String", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Binary", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											_LOG << "Save the visible column into the internal object model. (" << name->charrep() << " in " << tablename->charrep() << " to " << PKName->charrep() << " in " << PKTable->charrep() << ")" LOG_
											owningObject->add(PKName->charrep(), PKTable->charrep(), "Integer", true, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								} else {
									_LOG << "Yes, is foreign column, but no mapping defined." LOG_

									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);

									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											owningObject->add("", "", "Bit", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											owningObject->add("", "", "Float", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											owningObject->add("", "", "String", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											owningObject->add("", "", "Binary", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											owningObject->add("", "", "Integer", false, name->charrep(), tablename->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							_LOG << "No, is not foreign column." LOG_

							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									owningObject->add("", "", "Bit", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									owningObject->add("", "", "Float", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									owningObject->add("", "", "String", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									owningObject->add("", "", "Binary", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;

								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									owningObject->add("", "", "Integer", false, name->charrep(), tablename->charrep(), FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
					}
				} else {
					_LOG << "Error: Query '" << formularquery->charrep() << "' failed!" LOG_
				}
			}
		} else {
			_LOG << "Error: Query '" << query->charrep() << "' failed!" LOG_
		}
	}
	if (showMessage) {
		metaapp->msgBox("Error", messageText->charrep());
	}
}



class lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter : public lb_I_PluginImpl {
public:
	lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter();
	
	virtual ~lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_FieldsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter, lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter)

lbErrCodes LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter() {
	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter() called.\n" LOG_
}

lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::~lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter() {
	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::~lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {
		Formular_FieldsDBReaderExtension_BuildFromFormularParameter* Formular_FieldsModelExtension = new Formular_FieldsDBReaderExtension_BuildFromFormularParameter();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_FieldsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_FieldsDBReaderExtension_BuildFromFormularParameter* Formular_FieldsModelExtension = new Formular_FieldsDBReaderExtension_BuildFromFormularParameter();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_FieldsModelExtension.getPtr();
	ukFormular_FieldsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_FieldsDBReaderExtension_BuildFromFormularParameter::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_FieldsModelExtension != NULL) {
                ukFormular_FieldsModelExtension--;
                ukFormular_FieldsModelExtension.resetPtr();
        }
}

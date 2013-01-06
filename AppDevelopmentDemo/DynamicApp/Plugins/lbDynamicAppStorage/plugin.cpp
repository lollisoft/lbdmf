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

/*...sclass lbPluginModuleDynamicAppStorage:0:*/
class lbPluginModuleDynamicAppStorage : public lb_I_PluginModule {
public:

	lbPluginModuleDynamicAppStorage();
	virtual ~lbPluginModuleDynamicAppStorage();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	
	void LB_STDCALL install();
	
	/** \brief Checks for availability of a database.
	 * This function does the work to check, if any known database is available.
	 * The check includes testing for an ODBC database named 'lbDMF' and for the
	 * Sqlite version with this name.
	 *
	 * It returns false if no one is available.
	 */
	bool					LB_STDCALL checkForDatabases();
	
	/** \brief Installs a database.
	 * This function installs the database.
	 */
	bool					LB_STDCALL installDatabase();

	DECLARE_PLUGINS()
	
	UAP(lb_I_MetaApplication, meta)
	int _check_for_databases_failure_step;
	
	enum {
		META_DB_FAILURE_SYS_DB_BACKEND = 1,
		META_DB_FAILURE_SYS_DB_INITIALIZE,
		META_DB_FAILURE_SYS_DB_CONNECT,
		META_DB_FAILURE_SYS_DB_SCHEMA, // The schema is not initialized
		META_DB_FAILURE_SYS_DB_SCHEMAINSTALL, // Installation of the schema failed
		META_DB_FAILURE_APP_DB_BACKEND,
		META_DB_FAILURE_APP_DB_INITIALIZE,
		META_DB_FAILURE_APP_DB_CONNECT,
		META_DB_FAILURE_APP_DB_SCHEMA, // The schema is not initialized
		META_DB_FAILURE_APP_DB_SCHEMAINSTALL // Installation of the schema failed
	};
	
	
};
/*...e*/

/*...sclass lbPluginModuleDynamicAppStorage implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleDynamicAppStorage)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleDynamicAppStorage)

BEGIN_PLUGINS(lbPluginModuleDynamicAppStorage)
	ADD_PLUGIN(lbPluginDynamicAppInternalStorage,	lbDynAppInternalFormat)
	ADD_PLUGIN(lbPluginDynamicAppXMLStorage,		lbDynAppXMLFormat)
	ADD_PLUGIN(lbPluginDynamicAppBoUMLImport,		lbDynAppUMLImport)
END_PLUGINS()

/*
 * For each application should be a database setup plugin available.
 *
 * If no
 */
bool LB_STDCALL lbPluginModuleDynamicAppStorage::checkForDatabases() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, sysSchemaQuery)
	UAP(lb_I_Database, database)
	
	UAP(lb_I_Query, appSchemaQuery)
	UAP(lb_I_Database, app_database)
	
	// Currently unimplemented.
	
	// Too unsave now (Sqlite check fails on selecting sysadmin account)
	//return true;
	
	_LOG << "lbPluginModuleDynamicAppStorage::checkForDatabase() called." LOG_
	
	if (_check_for_databases_failure_step == -2) return false; // Failed prior. Outer loop must break.
	
	if (database == NULL) {
		char* dbbackend = meta->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "lb_MetaApplication::checkForDatabases() Using plugin database backend for system database setup test..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "lb_MetaApplication::checkForDatabases() Using built in database backend for system database setup test..." LOG_
		}
		
		if (database == NULL) {
			_LOG << "lb_MetaApplication::checkForDatabases() Error: Could not load database backend for system db, either plugin or built in version." LOG_
			
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
			
			return false;
		}
		if (database->init() != ERR_NONE) {
			_LOG << "lb_MetaApplication::checkForDatabases() Failed to initialize database." LOG_
			
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			
			return false;
		}
	}
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOG << "lb_MetaApplication::checkForDatabases() Failed to connect to system database." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_CONNECT;
		
		return false;
	}
	
	// Check. if the system database schema is initialized.
	sysSchemaQuery = database->getQuery("lbDMF", 0);
	
	if (sysSchemaQuery != NULL) {
		if (sysSchemaQuery->query("select * from \"users\" where \"userid\"='user'") == ERR_NONE) {
			if (((err = sysSchemaQuery->first()) == ERR_NONE) || (err == WARN_DB_NODATA)) {
				return true;
			} else {
				_LOG << "lb_MetaApplication::checkForDatabases() Error: No sysadmin account created." LOG_
				_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_SCHEMA;
				return false;
			}
		} else {
			_LOG << "lb_MetaApplication::checkForDatabases() Error: Query for sysadmin account failed." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_SCHEMA;
			return false;
		}
	} else {
		_LOG << "lb_MetaApplication::checkForDatabases() Error: Could not get query instance for sysadmin account test." LOG_
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
		return false;
	}
	
	return true;
}

bool LB_STDCALL lbPluginModuleDynamicAppStorage::installDatabase() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, sysSchemaQuery)
	UAP(lb_I_Database, database)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, testSQLFile)
	UAP_REQUEST(getModuleInstance(), lb_I_String, initialDatabaseLocation)
	
	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");
	char* home = getenv("HOME");
	
	bool  localInitialisation = false;


	_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() called." LOG_
	
#ifdef WINDOWS
	*testSQLFile = ".\\Database\\lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile->charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = ".\\Database\\";
	} else {
	        *testSQLFile = "..\\Database\\lbDMF-Sqlite-SystemDB.sql";
        	localInitialisation = FileExists(testSQLFile->charrep());
        	if (localInitialisation) {
        		*initialDatabaseLocation = "..\\Database\\";
       		} else {
			_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			return false;
		}
	}
#endif
#ifdef OSX
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile->charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		/// \todo Check if bundle is always as expected.
		// The application could be renamed.
		
		*testSQLFile = "./wxWrapper.app/Contents/Resources/lbDMF-Sqlite-SystemDB.sql";
		if (FileExists(testSQLFile->charrep())) {
			*initialDatabaseLocation = "./wxWrapper.app/Contents/Resources/";
		} else {
			_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
			_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
			return false;
		}
	}
#endif
#ifdef SOLARIS
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile->charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		///\todo Implement correct installation path.
		*testSQLFile = "../Database/lbDMF-Sqlite-SystemDB.sql";
		localInitialisation = FileExists(testSQLFile->charrep());
		if (localInitialisation) {
			*initialDatabaseLocation = "../Database/";
		} else {
			// There is no execution path set on the solaris desktop symbol. Therefore use the development environment at my machine
			*testSQLFile = home;
			*testSQLFile += "/develop/Projects/CPP/Database/lbDMF-Sqlite-SystemDB.sql";
			localInitialisation = FileExists(testSQLFile->charrep());
			if (localInitialisation) {
				*initialDatabaseLocation = home;
				*initialDatabaseLocation += "/develop/Projects/CPP/Database/";
			} else {
				/// \todo Implement lookup of bundle.
				// Try resource directory in bundle.
				_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
				_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
				return false;
			}
		}
	}
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
	*testSQLFile = home;
	*testSQLFile += "/.lbDMF/lbDMF-Sqlite-SystemDB.sql";
	localInitialisation = FileExists(testSQLFile->charrep());
	if (localInitialisation) {
		*initialDatabaseLocation = home;
		*initialDatabaseLocation += "/.lbDMF/";
	} else {
		/// \todo Implement lookup correctly for other cases.
		
		if (FileExists("../Database/lbDMF-Sqlite-SystemDB.sql")) {
			*initialDatabaseLocation = "../Database/";
		} else
			if (FileExists("/usr/share/lbdmf/database/lbDMF-Sqlite-SystemDB.sql")) {
				*initialDatabaseLocation = "/usr/share/lbdmf/database/";
			} else
				if (FileExists("/usr/local/share/lbdmf/database/lbDMF-Sqlite-SystemDB.sql")) {
					*initialDatabaseLocation = "/usr/local/share/lbdmf/database/";
				} else {
					_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Error: Application is not properly installed. Could not find SQL scripts for initial database setup." LOG_
					_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
					return false;
				}
	}
#endif
#endif
#endif
	
	_LOG << "Have path to initial database files: " << initialDatabaseLocation->charrep() LOG_
	
	char* dbbackend = meta->getSystemDatabaseBackend();
	if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
		_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Using plugin database backend for system database setup test..." LOG_
		
        	lbDMFPasswd = getenv("lbDMFPasswd");
        	lbDMFUser   = getenv("lbDMFUser");
		
        	if (!lbDMFUser) lbDMFUser = "dba";
        	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
	} else {
		// Use built in
		REQUEST(getModuleInstance(), lb_I_Database, database)
		_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Using built in database backend for system database setup test..." LOG_
		
	        lbDMFPasswd = getenv("lbDMFPasswd");
	        lbDMFUser   = getenv("lbDMFUser");
		
	        if (!lbDMFUser) lbDMFUser = "dba";
	        if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
	}
	
	if (database == NULL) {
		_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Error: Could not load database backend for system db, either plugin or built in version." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_BACKEND;
		
		return false;
	}

	if (database->init() != ERR_NONE) {
		_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Failed to initialize database." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_INITIALIZE;
		
		return false;
	}
	
	
	if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOG << "lbPluginModuleDynamicAppStorage::installDatabase() Failed to connect to system database. " <<
			"Please set internal default user 'dba' and password 'trainres' or set the environment " <<
			"variables to those used by the database (lbDMFUser, lbDMFPasswd)." LOG_
		
		_check_for_databases_failure_step = META_DB_FAILURE_SYS_DB_CONNECT;
		
		return false;
	}
	
	// Check. if the system database schema is initialized.
	sysSchemaQuery = database->getQuery("lbDMF", 0);
	
	if (sysSchemaQuery != NULL) {
		// Here it goes on with installation.
		UAP(lb_I_String, SQL)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, inputApp)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, inputSys)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, systemDatabaseName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, applicationDatabaseName)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, dataDir)
		*dataDir = initialDatabaseLocation->charrep();
		
		*applicationDatabaseName = dataDir->charrep();
		
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
#ifdef WINDOWS
			*applicationDatabaseName = "..\\Database\\lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef OSX
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef SOLARIS
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			// Create data directory, if not available
			*applicationDatabaseName += "lbDMF-Sqlite-ApplicationDB.sql";
#endif
#endif
#endif
			_LOG << "Apply the SQL file to the lbDMF application database: " << applicationDatabaseName->charrep() LOG_
			inputApp->setFileName(applicationDatabaseName->charrep());
			
			if (!inputApp->open()) {
#ifdef WINDOWS
				// Try the path for a typical Windows installation
				inputApp->setFileName("Database\\lbDMF-Sqlite-ApplicationDB.sql");
				if (!inputApp->open()) {
					meta->msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
#endif
			}
			
			SQL = inputApp->getAsString();
			sysSchemaQuery->skipFKCollecting();
			if (sysSchemaQuery->query(SQL->charrep()) != ERR_NONE) {
				_LOG << "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				return false;
			}
			
			*systemDatabaseName = dataDir->charrep();
			
#ifdef WINDOWS
			*systemDatabaseName = "..\\Database\\lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef OSX
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef SOLARIS
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			*systemDatabaseName += "lbDMF-Sqlite-SystemDB.sql";
#endif
#endif
#endif
			_LOG << "Apply the SQL file to the lbDMF system database: " << systemDatabaseName->charrep() LOG_
		
			inputSys->setFileName(systemDatabaseName->charrep());
			
			if (!inputSys->open()) {
#ifdef WINDOWS
				// Try the path for a typical Windows installation
				inputSys->setFileName("Database\\lbDMF-Sqlite-SystemDB.sql");
				if (!inputSys->open()) {
					_LOG << "lb_MetaApplication::installDatabase() Failed to install initial system database. File not found." LOG_
					meta->msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
#endif
			}
			SQL = inputSys->getAsString();
			sysSchemaQuery->skipFKCollecting();
			if (sysSchemaQuery->query(SQL->charrep()) != ERR_NONE) {
				_LOG << "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				return false;
			}
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_String, systemDatabaseName)
			UAP_REQUEST(getModuleInstance(), lb_I_String, applicationDatabaseName)
			
			char* home = getenv("HOME");
			UAP_REQUEST(getModuleInstance(), lb_I_String, dataDir)
			*dataDir = initialDatabaseLocation->charrep();
			
			*applicationDatabaseName = dataDir->charrep();
			
#ifdef WINDOWS
			*applicationDatabaseName = "..\\Database\\lbDMF-PostgreSQL.sql";
#endif
#ifdef OSX
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#ifdef SOLARIS
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#ifdef LINUX
#ifndef OSX
#ifndef SOLARIS
			*applicationDatabaseName = "lbDMF-PostgreSQL.sql";
#endif
#endif
#endif
			_LOG << "Apply the SQL file to the lbDMF application database: " << applicationDatabaseName->charrep() LOG_

			inputApp->setFileName(applicationDatabaseName->charrep());
			if (!inputApp->open()) {
#ifdef WINDOWS
				inputApp->setFileName("Database\\lbDMF-PostgreSQL.sql");
#endif
				if (!inputApp->open()) {
					_LOG << "lb_MetaApplication::installDatabase() Failed to install initial system database. File not found." LOG_
					meta->msgBox("Info", "Installation of builtin database failed.");
					return false;
				}
			}
			SQL = inputApp->getAsString();
			sysSchemaQuery->skipFKCollecting();
			if (sysSchemaQuery->query(SQL->charrep()) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
				_LOG << "lb_MetaApplication::installDatabase() Failed to install initial system database." LOG_
				*msg = "Installation of system database failed. Check the permissions of the user '";
				*msg += lbDMFUser;
				*msg += "'.";
				meta->msgBox("Info", msg->charrep());
				return false;
			}
			sysSchemaQuery->close();
			database->close();
		}
	}
#ifdef LINUX
	UAP_REQUEST(getModuleInstance(), lb_I_String, installdir)
	home =
#if defined(WINDOWS)
	getenv("USERPROFILE");
#endif
#if defined(UNIX) || defined(LINUX) || defined(OSX)
	getenv("HOME");
#endif
	*installdir = home;
	//*installdir += "/develop/Projects/CPP/Test/GUI/wxWrapper";
	meta->setDirLocation(installdir->charrep());
#endif
	meta->msgBox("Info",
		   "This application is running the first time on this computer,\n"
		   "or your prior configured database is not available anyhow.\n\n"
		   "Please inform your administrator, if the database is not available.\n\n"
		   "Otherwise, you currently work in a local initial database version.\n\n"
		   "And you are automatically logged in as an 'administrator'.\n\n"
		   "For security considerations please change the password for\n"
		   "your user account, wich is currently the default 'user'.\n\n"

		   "Known issues: The prototype doesn't cope with empty tables\n"
		   "when using Sqlite. To overcome this, use a Sqlite database\n"
		   "browser to setup sample data. Using a properly set up ODBC\n"
		   "database (tested is PostgreSQL), no problems are known."
		   );

	// While the plugin get's initialized meta->load() must have been called to enable the following two functions.
	meta->setUserName("user");
	meta->setApplicationName("lbDMF Manager");
	
	meta->setAutoload(true);
	meta->setGUIMaximized(true); // Otherwise the toolbar is bigger than frame width. Default size should be changed.
	meta->save(); // Save, because otherwise the usage of DatabaseLayerGateway gets overwritten by created standard version of first try of loading the file.
	
	return true;
}


lbPluginModuleDynamicAppStorage::lbPluginModuleDynamicAppStorage() {
	_LOG << "lbPluginModuleDynamicAppStorage::lbPluginModuleDynamicAppStorage() called." LOG_
	// Nothing checked yet.
	_check_for_databases_failure_step = -1;

	REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
}

lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() {
	_CL_VERBOSE << "lbPluginModuleDynamicAppStorage::~lbPluginModuleDynamicAppStorage() called." LOG_
}

void LB_STDCALL lbPluginModuleDynamicAppStorage::initialize() {
	_CL_VERBOSE << "lbPluginModuleDynamicAppStorage::initialize() called." LOG_
	enumPlugins();
	
}

void LB_STDCALL lbPluginModuleDynamicAppStorage::install() {
	// The check may have several rounds.
	_LOG << "lbPluginModuleDynamicAppStorage::install() called." LOG_
	while (!checkForDatabases()) {
		if (_check_for_databases_failure_step == -2) break; //
		
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_BACKEND) {
			//meta->msgBox("Error", "No system database backed available. Please check your installation and logfile!");
			meta->setSystemDatabaseBackend("DatabaseLayerGateway");
            meta->setApplicationDatabaseBackend("DatabaseLayerGateway");
            meta->useSystemDatabaseBackend(true);
            meta->useApplicationDatabaseBackend(true);
			
			if (!installDatabase()) {
				meta->msgBox("Error", "Fallback to local database variant failed too!");
				break;
			}
			
			break;
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_INITIALIZE) {
			meta->msgBox("Error", "Initialize system database backend failed. Please check your installation and logfile!");
			
			break;
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_CONNECT) {
            // Assume no database available. Use local Sqlite variant.
            meta->setSystemDatabaseBackend("DatabaseLayerGateway");
            meta->setApplicationDatabaseBackend("DatabaseLayerGateway");
            meta->useSystemDatabaseBackend(true);
            meta->useApplicationDatabaseBackend(true);
			
			if (!installDatabase()) {
				meta->msgBox("Error", "Connect to system database backend failed and fallback to local database variant failed too!");
				break;
			}
		}
		if (_check_for_databases_failure_step == META_DB_FAILURE_SYS_DB_SCHEMA) {
			if (!installDatabase()) {
                if (meta->askYesNo(
							 "The ODBC system database is reachable and a login was successfull,\n"
							 "but is not properly setup. A try to install the database failed.\n\n"
							 "Do you like to use a local Sqlite database instead?"))
                {
                    meta->setSystemDatabaseBackend("DatabaseLayerGateway");
                    meta->setApplicationDatabaseBackend("DatabaseLayerGateway");
                    meta->useSystemDatabaseBackend(true);
                    meta->useApplicationDatabaseBackend(true);
					
                    if (!installDatabase()) {
                        meta->msgBox("Error", "Fallback to local database variant failed too!");
                        _check_for_databases_failure_step = -2;
                    }
                } else {
                    _check_for_databases_failure_step = -2;
                }
			}
		}
	}
	
	if (_check_for_databases_failure_step == -2) {
		meta->msgBox("Error", "Setup of databases, required by this application failed!");
	}
}

lbErrCodes LB_STDCALL lbPluginModuleDynamicAppStorage::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleDynamicAppStorage::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_LOG << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

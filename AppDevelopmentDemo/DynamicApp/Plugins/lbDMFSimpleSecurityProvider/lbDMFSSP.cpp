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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
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

#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef __MINGW32__
#include <direct.h>
#endif

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <lbDMFSSP.h>

IMPLEMENT_FUNCTOR(instanceOflbDMFSSP, lbDMFSSP)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDMFSSP)
	ADD_INTERFACE(lb_I_SecurityProvider)
END_IMPLEMENT_LB_UNKNOWN()


lbDMFSSP::lbDMFSSP() {
	_LOG << "lbDMFSSP::lbDMFSSP() called." LOG_
	_logged_in = false;
	_loading_object_data = false;
	_force_use_database = false;
	_loaded = false;
}

lbDMFSSP::~lbDMFSSP() {
	_CL_LOG << "lbDMFSSP::~lbDMFSSP() called." LOG_
}

lbErrCodes LB_STDCALL lbDMFSSP::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDMFSSP::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

bool LB_STDCALL lbDMFSSP::login(const char* user, const char* pass) {
	return false;
}

lb_I_Unknown*	LB_STDCALL lbDMFSSP::getApplicationModel() {
	
}

long LB_STDCALL lbDMFSSP::getApplicationID() {
	if ((_logged_in) && (Applications->getApplicationCount() > 0)) {
		Applications->selectApplication(LogonApplication->charrep());

		return Applications->getID();
	} else {
		if (!_logged_in) {
			_LOG << "Error: lbDMFSSP::getApplicationID() returns 0, because user is not logged in." LOG_
		}
		if (Applications->getApplicationCount() <= 0) {
			_LOG << "Error: lbDMFSSP::getApplicationID() returns 0, because the application count of Applications is 0." LOG_
		}
		return 0;
	}
}

lb_I_Container* LB_STDCALL lbDMFSSP::getApplications() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_Container, apps)

	if (Applications->getApplicationCount() == 0) {
		// Maybe no data collected in the file yet
		// Fallback to manually read out the applications

		_LOG << "Info: Have no applications in '" << Applications->getClassName() << "'. Create the list from database." LOG_

		UAP(lb_I_Database, database)

		char* dbbackend = meta->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "lb_MetaApplication::getApplications() Using plugin database backend for system database setup test..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)

			if (database == NULL) {
				meta->setSystemDatabaseBackend("DatabaseLayerGateway");
				meta->setApplicationDatabaseBackend("DatabaseLayerGateway");
				meta->useSystemDatabaseBackend(true);
				meta->useApplicationDatabaseBackend(true);

				// A second try here
				char* dbbackend = meta->getSystemDatabaseBackend();
				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
					AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
					_LOG << "lb_MetaApplication::getApplications() Using plugin database backend for system database setup test..." LOG_
				}
				if (database == NULL) {
					meta->msgBox("Error", "Getting application list failed. Even local database backend failed to load.");
					apps++;
					return apps.getPtr();
				}
			}

			_LOG << "lb_MetaApplication::getApplications() Using built in database backend for system database setup test..." LOG_
		}

		UAP(lb_I_Query, sampleQuery)
		database->init();

		const char* lbDMFPasswd = getenv("lbDMFPasswd");
		const char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		if (err != ERR_NONE) {
			_LOG << "Error: No database connection built up. Could not use database logins." LOG_
			apps++;
			return apps.getPtr();
		}

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");

		bool hasDBLoaded = false;

		if (pl != NULL) {
			ukPl = pl->getImplementation();

			if (ukPl != NULL) {
				UAP(lb_I_DatabaseOperation, fOp)
				QI(ukPl, lb_I_DatabaseOperation, fOp)

				if (!fOp->begin("lbDMF", database.getPtr())) {
					_LOG << "FATAL: Failed to start reading application list from database!" LOG_
					apps++;
					return apps.getPtr();
				}

				Applications->accept(*&fOp);

				Users->accept(*&fOp);

				User_Applications->accept(*&fOp);

				fOp->end();

				/// \todo Save on demand or at application end.
				// => Save menu entry, or on property changes.
				//save(); // Late save

				while (Applications->hasMoreApplications()) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, name)
					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, ukName)

					Applications->setNextApplication();

					*name = Applications->getApplicationName();

					QI(name, lb_I_KeyBase, key)
					QI(name, lb_I_Unknown, ukName)

					apps->insert(&ukName, &key);
				}

				Applications->finishApplicationIteration();
				hasDBLoaded = true;
			} else {
				_LOG << "Error: Could not load database stream operator classes!" LOG_
			}
		} else {
			_LOG << "Error: No database stream operation found.!" LOG_
		}

		// A first preload of the applications is ignored yet.

/*...sLoad by direct SQL queries\44\ if all above fails:16:*/
		if (!hasDBLoaded) {
			_LOG << "Info: All streaming operations have been failed. Use database API directly." LOG_
			sampleQuery = database->getQuery("lbDMF", 0);

			char* buffer = (char*) malloc(1000);
			buffer[0] = 0;

			sprintf(buffer,
				"select Anwendungen.name from Anwendungen inner join User_Anwendungen on "
				"Anwendungen.id = User_Anwendungen.anwendungenid "
				"inner join Users on User_Anwendungen.userid = Users.id where "
				"Users.userid = '%s'"
					, LogonUser->charrep());


			sampleQuery->skipFKCollecting();
			sampleQuery->query(buffer);
			sampleQuery->enableFKCollecting();

			free(buffer);

			lbErrCodes err = sampleQuery->first();

/*...sLoop through:40:*/
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

				UAP_REQUEST(getModuleInstance(), lb_I_String, S1)
				UAP(lb_I_KeyBase, key)
				UAP(lb_I_Unknown, uk_S1)

				S1 = sampleQuery->getAsString(1);
				QI(S1, lb_I_KeyBase, key)
				QI(S1, lb_I_Unknown, uk_S1)

				apps->insert(&uk_S1, &key);

				while (err == ERR_NONE) {
					lbErrCodes err = sampleQuery->next();

					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						S1 = sampleQuery->getAsString(1);
						QI(S1, lb_I_KeyBase, key)
						QI(S1, lb_I_Unknown, uk_S1)

						apps->insert(&uk_S1, &key);

						if (err == WARN_DB_NODATA) {
							break;
						}
					}

					if (err == ERR_DB_NODATA) {
					        //box->SetSelection(0);
					        break;
					}
				}

			}
/*...e*/
		}
/*...e*/
	} else {
		if (Users->selectAccount(LogonUser->charrep())) {
			long UID = Users->getID();

			User_Applications->finishRelationIteration();

			while (User_Applications->hasMoreRelations()) {
				User_Applications->setNextRelation();
				Applications->selectApplication(User_Applications->getApplicationID());

				_LOG <<	"Check if user '" << Users->getUserName() <<
							"' has rights on application '" << Applications->getApplicationName() << "'. (" << User_Applications->getApplicationID() << ") " <<
							UID << " = " << User_Applications->getUserID() LOG_

				if (User_Applications->getUserID() == UID) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, S1)
					UAP(lb_I_KeyBase, key)
					UAP(lb_I_Unknown, uk_S1)

					*S1 = Applications->getApplicationName();

					QI(S1, lb_I_KeyBase, key)
					QI(S1, lb_I_Unknown, uk_S1)

					apps->insert(&uk_S1, &key);
				}
			}
		} else {
			_LOG << "Error: Logged in user account is not in data model!" LOG_
		}
	}

	apps++;
	return apps.getPtr();
}

lbErrCodes LB_STDCALL lbDMFSSP::uninitialize() {
	if (User_Applications != NULL) User_Applications--;
	if (Users != NULL) Users--;
	if (Applications != NULL) Applications--;

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDMFSSP::save() {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP(lb_I_Plugin, pl1)
	UAP(lb_I_Unknown, ukPl1)
	pl1 = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");

	if (pl1 == NULL) {
		_LOG << "Error: Need a plugin with an implementation of interface lb_I_FileOperation in namespace OutputStreamVisitor. Cannot save meta application data." LOG_
			return ERR_FILE_WRITE_DEFAULT;
	}

	ukPl1 = pl1->getImplementation();
	UAP(lb_I_FileOperation, fOp1)
	QI(ukPl1, lb_I_FileOperation, fOp1)

#ifdef OSX
	lb_I_GUI* g = NULL;
	getGUI(&g);
	if (g) {
		if (!fOp1->begin("./wxWrapper.app/Contents/Resources/SimpleSecurity.sec")) {
			// Fallback
			if (!fOp1->begin("SimpleSecurity.sec")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_WRITE_DEFAULT;
			}
		}
	} else if (!fOp1->begin("SimpleSecurity.sec")) {
		_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

		return ERR_FILE_WRITE_DEFAULT;
	}
#endif
#ifndef OSX
	if (!fOp1->begin("SimpleSecurity.sec")) {
		_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

		return ERR_FILE_WRITE_DEFAULT;
	}
#endif

	//UAP(lb_I_Unknown, ukAcceptor1)
	//QI(this, lb_I_Unknown, ukAcceptor1)
	//ukAcceptor1->accept(*&fOp1);

	//UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
	//disp->accept(*&fOp1);


	// Save a Users list

	if (Users == NULL) {
			UAP(lb_I_Plugin, pl2)
			UAP(lb_I_Unknown, ukPl2)
			pl2 = PM->getFirstMatchingPlugin("lb_I_UserAccounts", "Model");
			ukPl2 = pl2->getImplementation();
			QI(ukPl2, lb_I_UserAccounts, Users)

			_LOG << "Save default user data ..." LOG_
	}

	if (Users != NULL) {
		_LOG << "lb_MetaApplication::save(): Save Users list." LOG_
		Users->accept(*&fOp1);
	}

	if (Applications == NULL) {
			UAP(lb_I_Plugin, pl3)
			UAP(lb_I_Unknown, ukPl3)
			pl3 = PM->getFirstMatchingPlugin("lb_I_Applications", "Model");
			ukPl3 = pl3->getImplementation();
			QI(ukPl3, lb_I_Applications, Applications)

			_LOG << "Save default application data ..." LOG_
	}

	if (Applications != NULL) {
		_LOG << "lb_MetaApplication::save(): Save Applications list." LOG_
		Applications->accept(*&fOp1);
	}

	if (User_Applications == NULL) {
			UAP(lb_I_Plugin, pl4)
			UAP(lb_I_Unknown, ukPl4)
			pl4 = PM->getFirstMatchingPlugin("lb_I_User_Applications", "Model");
			ukPl4 = pl4->getImplementation();
			QI(ukPl4, lb_I_User_Applications, User_Applications)

			_LOG << "Save default user - application data ..." LOG_
	}

	if (User_Applications != NULL) {
		_LOG << "lb_MetaApplication::save(): Save User_Applications list." LOG_
		User_Applications->accept(*&fOp1);
	}
	fOp1->end();

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDMFSSP::load() {
	lbErrCodes err = ERR_NONE;

	_loading_object_data = true;

	// Get the plugin to read a standard stream based file

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");

	if (pl != NULL) {
		ukPl = pl->getImplementation();

		if (ukPl != NULL) {
			UAP(lb_I_FileOperation, fOp)
			QI(ukPl, lb_I_FileOperation, fOp)

#ifdef OSX
			lb_I_GUI* g = NULL;
			getGUI(&g);
			if (g) {
				if (!fOp->begin("./wxWrapper.app/Contents/Resources/SimpleSecurity.sec")) {
					// Fallback
					if (!fOp->begin("SimpleSecurity.sec")) {
						_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

						return ERR_FILE_READ;
					}
				}
			} else if (!fOp->begin("SimpleSecurity.sec")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_READ;
			}
#endif
#ifndef OSX
			if (!fOp->begin("SimpleSecurity.sec")) {
				_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_

				return ERR_FILE_READ;
			}
#endif

			// Read my data
			//UAP(lb_I_Unknown, ukAcceptor)
			//QI(this, lb_I_Unknown, ukAcceptor)
			//ukAcceptor->accept(*&fOp);

#ifdef IMPLEMENT_NEWSTUFF
			/* Here it seems the best and earliest place to load interceptor configuration.
			 * Before any user could login (except applications without login required), the
			 * interceptors were setup. The interceptors may be registered before the intented
			 * event handler will be registered and thus the interceptor must be stored until
			 * it could be activated.
			 *
			 * A stored interceptor not only needs the name of the event to intercept, but also
			 * the class and the pointer to the methods to be used for interception. Currently I
			 * do not know  how to store the pointer to the method, as I assume it will change on
			 * each application start.
			 *
			 * A plugin must register the interceptors of interest to activate the interception
			 * functionality. The dispatcher should cancel all dispatching calls who have a registered
			 * interceptor that is not fully loaded.
			 */

			//UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
			//disp->accept(*&fOp);
#endif

			//_LOG << "Read property sets from metaapp file..." LOG_
			//REQUEST(getModuleInstance(), lb_I_Parameter, propertySets)
			//propertySets->accept(*&fOp);
			//_LOG << "Done reading property sets. Having " << propertySets->Count() << " sets." LOG_


			UAP(lb_I_Plugin, pl2)
			UAP(lb_I_Unknown, ukPl2)
			pl2 = PM->getFirstMatchingPlugin("lb_I_UserAccounts", "Model");
			ukPl2 = pl2->getImplementation();

			UAP(lb_I_Plugin, pl3)
			UAP(lb_I_Unknown, ukPl3)
			pl3 = PM->getFirstMatchingPlugin("lb_I_Applications", "Model");
			ukPl3 = pl3->getImplementation();

			UAP(lb_I_Plugin, pl4)
			UAP(lb_I_Unknown, ukPl4)
			pl4 = PM->getFirstMatchingPlugin("lb_I_User_Applications", "Model");
			ukPl4 = pl4->getImplementation();

/* Meta application could not know details of the application. Has it forms ?
			UAP(lb_I_Plugin, pl5)
			UAP(lb_I_Unknown, ukPl5)
			pl5 = PM->getFirstMatchingPlugin("lb_I_Applications_Formulars", "Model");
			ukPl5 = pl5->getImplementation();
*/





			QI(ukPl2, lb_I_UserAccounts, Users)
			QI(ukPl3, lb_I_Applications, Applications)
			QI(ukPl4, lb_I_User_Applications, User_Applications)
//			QI(ukPl5, lb_I_Applications_Formulars, ApplicationFormulars)

			// Database read will be forced by login.
			if (!_force_use_database) {
				_LOG << "Read users, applications and user associations from file." LOG_
				// Read an Users list
				ukPl2->accept(*&fOp);
				// Read an Applications list
				ukPl3->accept(*&fOp);
				// Read users applications
				ukPl4->accept(*&fOp);
				// Read applications to formular assoc
//				ukPl5->accept(*&fOp);

				if (Users->getUserCount() == 0) {
					_LOG << "Warning: Users list from file does not contain any data." LOG_
				}
			} else {
				UAP(lb_I_Container, apps)
				apps = getApplications();
			}
			fOp->end();

			_loaded = true;

			return ERR_NONE;
		} else {
			_LOG << "lb_MetaApplication::load() Error: Could not get lb_I_FileOperation plugin !" LOG_
		}
	} else {
		_LOGERROR << "Error: Could not load stream operator classes!" LOG_
	}
	return ERR_FILE_READ;
}
/*...sclass lbPluginDMFSSP implementation:0:*/
/*...slbPluginDMFSSP:0:*/
class lbPluginDMFSSP : public lb_I_PluginImpl {
public:
	lbPluginDMFSSP();

	virtual ~lbPluginDMFSSP();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();

	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Unknown, ukSSP)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDMFSSP)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDMFSSP, lbPluginDMFSSP)

/*...slbErrCodes LB_STDCALL lbPluginDMFSSP\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDMFSSP::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDMFSSP::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDMFSSP::lbPluginDMFSSP() {
	_CL_VERBOSE << "lbPluginDMFSSP::lbPluginDMFSSP() called.\n" LOG_
	
}

lbPluginDMFSSP::~lbPluginDMFSSP() {
	_CL_VERBOSE << "lbPluginDMFSSP::~lbPluginDMFSSP() called.\n" LOG_
}

bool LB_STDCALL lbPluginDMFSSP::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDMFSSP::autorun() {
	lbErrCodes err = ERR_NONE;

	return err;
}

void LB_STDCALL lbPluginDMFSSP::initialize() {
}

bool LB_STDCALL lbPluginDMFSSP::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFSSP\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFSSP::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukSSP == NULL) {
		lbDMFSSP* DMFXslt = new lbDMFSSP();
		
		QI(DMFXslt, lb_I_Unknown, ukSSP)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return ukSSP.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFSSP\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFSSP::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukSSP == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbDMFSSP* xslt = new lbDMFSSP();
		

		QI(xslt, lb_I_Unknown, ukSSP)
	}

	lb_I_Unknown* r = ukSSP.getPtr();
	ukSSP.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDMFSSP::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukSSP != NULL) {
                ukSSP--;
                ukSSP.resetPtr();
        }
}
/*...e*/
/*...e*/


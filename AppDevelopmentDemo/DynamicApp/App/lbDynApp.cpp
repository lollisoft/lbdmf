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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

//#define USE_RDCD_MODEL

#ifdef USE_RDCD_MODEL
/// \todo Move interfaces to public place, where needed.
#include <lbInterfaces-sub-Project.h>
#endif

/*...sLB_DYNAPP_DLL scope:0:*/
#define LB_DYNAPP_DLL
#include <lbdynapp-module.h>
/*...e*/

#include <lbDynApp.h>
/*...e*/

#define AQUIRE_PLUGIN(interface, ns, name, errmsgpart) \
		UAP(lb_I_Plugin, pl##name) \
		UAP(lb_I_Unknown, uk##name) \
		pl##name = PM->getFirstMatchingPlugin(#interface, #ns); \
		if (pl##name != NULL) { \
			uk##name = pl##name->getImplementation(); \
		} else { \
			_LOG << "Warning: No " #errmsgpart " datamodel plugin found." LOG_ \
		} \
		\
		if (uk##name != NULL) { \
			QI(uk##name, interface, name) \
		} else { \
			_LOG << "Warning: No " #errmsgpart " datamodel plugin implementation found." LOG_ \
		}


/*...sclass lb_DynamicApplication:0:*/
class lbDynamicApplication : 
public lb_I_Application,
public lb_I_EventHandler
{
public:
	lbDynamicApplication();
	virtual ~lbDynamicApplication();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	
	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	lbErrCodes LB_STDCALL initialize(char* user = NULL, char* app = NULL);
	lbErrCodes LB_STDCALL uninitialize();
	lbErrCodes LB_STDCALL run();
	lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	lbErrCodes LB_STDCALL setUserName(char* user);
	lbErrCodes LB_STDCALL setApplicationName(char* app);
	
	lb_I_EventManager* LB_STDCALL getEVManager( void );

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	

	/**
	 * \brief The main handler to create dynamic forms
	 */
	lbErrCodes LB_STDCALL getDynamicDBForm(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL exportApplicationToXML(lb_I_Unknown* uk);

	/** \brief Import an UML XMI document as an application configuration. */
	lbErrCodes LB_STDCALL importUMLXMIDocIntoApplication(lb_I_Unknown* uk);
	
	/** \brief Get a custom database form based on type selected in the formular table.
	 * A custom database form could be installed traditionally by placing the module
	 * into the right place and then modify the data structure regarding that database form,
	 *
	 * or by using plugin technology and simply let the plugin let do this work. Therefore
	 * the plugin must either be activated before reading in the configuration.
	 */
	lbErrCodes LB_STDCALL getCustomDBForm(lb_I_Unknown* uk);
	
	/** \brief Print a report over menu/toolbar entry.
	 * A report may be based on a form, thus it's query is the data source.
	 * 
	 * On the other hand, it may be special reports not shown as forms. In that
	 * way, a separate configuration is needed.
	 */
	lbErrCodes LB_STDCALL printReport(lb_I_Unknown* uk);

	/** \brief Use dynamic versions again.
	 *
	 */
	lbErrCodes LB_STDCALL resetCustomDBFormsToDynamic(lb_I_Unknown* uk);

	/** \brief Load database model.
	 * Must be used before exporting to XML.
	 */
	lbErrCodes LB_STDCALL loadDatabaseSchema(lb_I_Unknown* uk);
	
	/** \brief Edit global properties when lbDMF Manager is running.
	 */
	lbErrCodes LB_STDCALL editProperties(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL OnPropertiesDataChange(lb_I_Unknown* uk);

protected:

	/** \brief Load the database forms.
	 */
	void LB_STDCALL activateDBForms(char* user, char* app);

	bool haveLoadedDBModel;

	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Database, database)
	
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
	UAP(lb_I_MetaApplication, metaapp)

#ifdef USE_RDCD_MODEL
	// Model of the dynamic form configuration 
	UAP(lb_I_RDCDModel, model)
#endif
	
	// Preloaded data from database, if plugins are available.
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)

	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)



	char hdsihd[100];
};
/*...e*/
/*...slbDynamicApplication:0:*/
/*...sctors\47\dtors:0:*/
lbDynamicApplication::lbDynamicApplication() {
	ref = STARTREF;
	gui = NULL;
	haveLoadedDBModel = false;
	_CL_LOG << "lbDynamicApplication::lbDynamicApplication() called." LOG_
}

lbDynamicApplication::~lbDynamicApplication() {
	_CL_LOG << "lbDynamicApplication::~lbDynamicApplication() called." LOG_
}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	// Register a dynamic formular creator

// Done while initialiation
//	disp->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, "getDynamicDBForm");

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbDynamicApplication::editProperties(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, appname)
		
	metaapp->getApplicationName(&appname);
	
	if (*appname == "lbDMF Manager") {
		// Build up a preferences object and pass it to the property view
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
		
		// General parameters for this application
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueGeneral)
		
		// Project manager parameters
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueProject)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolProject)
		
		
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
		
		parameter->setData("lbDMF Manager");
		//--------------------------------------------------------
		/*
		 parameterProject->setData("Autoopen last project");
		 boolProject->setData(true);
		 paramProject->setUAPBoolean(*&parameterProject, *&boolProject);
		 */
		
		parameterProject->setData("Target database to import db schema");
		valueProject->setData("CRM");
		paramProject->setUAPString(*&parameterProject, *&valueProject);
		
		parameterProject->setData("Target database user");
		valueProject->setData("dba");
		paramProject->setUAPString(*&parameterProject, *&valueProject);
		
		parameterProject->setData("Target database password");
		valueProject->setData("trainres");
		paramProject->setUAPString(*&parameterProject, *&valueProject);
		
		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramProject, 
													this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);
		
		param->setUAPParameter(*&parameter, *&paramProject);
		
		metaapp->showPropertyPanel(*&param);
	}
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::OnProjectDataChange(lb_I_Unknown* uk) {
	_CL_LOG << "lbDynamicApplication::OnProjectDataChange() called." LOG_
	return ERR_NONE;
}


lbErrCodes LB_STDCALL lbDynamicApplication::loadDatabaseSchema(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	bool isDBAvailable = false;
	UAP(lb_I_DatabaseOperation, fOpDB)
		
	UAP(lb_I_Query, sampleQuery)

	if (database == NULL) {
		REQUEST(manager.getPtr(), lb_I_Database, database)
		database->init();
	}
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOG << "Warning: No system database available." LOG_
	} else {
		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
		if (pl != NULL)	ukPl = pl->getImplementation();
		if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpDB)
			isDBAvailable = fOpDB->begin("lbDMF", database.getPtr());
	}
	
	_CL_LOG << "Load database schema from target database ..." LOG_
		
	if (isDBAvailable) {
		AQUIRE_PLUGIN(lb_I_DBPrimaryKeys, Model, dbPrimaryKeys, "'primary keys'")
		AQUIRE_PLUGIN(lb_I_DBForeignKeys, Model, dbForeignKeys, "'foreign keys'")
		AQUIRE_PLUGIN(lb_I_DBColumns, Model, dbColumns, "'database columns'")
		AQUIRE_PLUGIN(lb_I_DBTables, Model, dbTables, "'database tables'")
		
		UAP(lb_I_Parameter, param)
		UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP(lb_I_KeyBase, key)
		QI(name, lb_I_KeyBase, key)
		
		UAP(lb_I_Unknown, uk)
		uk = metaapp->getActiveDocument();
		QI(uk, lb_I_Parameter, param)
	
		document->setCloning(false);
				
		if (strcmp(appParams->getParameter("DBName", metaapp->getApplicationID()), "lbDMF") == 0) {
			// Is system database
			dbPrimaryKeys->accept(*&fOpDB);
			dbForeignKeys->accept(*&fOpDB);
			dbTables->accept(*&fOpDB);
			dbColumns->accept(*&fOpDB);
			fOpDB->end();
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_Database, customDB)
			UAP(lb_I_DatabaseOperation, fOpCustomDB)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbname)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbuser)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbpass)
			customDB->init();
			
			*dbname = appParams->getParameter("DBName", metaapp->getApplicationID());
			*dbuser = appParams->getParameter("DBUser", metaapp->getApplicationID());
			*dbpass = appParams->getParameter("DBPass", metaapp->getApplicationID());
			
			if ((customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
				_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
			} else {
				pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
				if (pl != NULL)	ukPl = pl->getImplementation();
				if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpCustomDB)
				
				if (fOpCustomDB != NULL) {
					fOpCustomDB->begin(dbname->charrep(), customDB.getPtr());
					
					dbPrimaryKeys->accept(*&fOpCustomDB);
					dbForeignKeys->accept(*&fOpCustomDB);
					dbTables->accept(*&fOpCustomDB);
					dbColumns->accept(*&fOpCustomDB);
					
					fOpCustomDB->end();
				}
			}
		}
		

		if ((dbPrimaryKeys != NULL) && 
			(dbForeignKeys != NULL) && 
			(dbTables != NULL) && 
			(dbColumns != NULL)) {
			
			UAP(lb_I_Unknown, uk)

			*name = "ApplicationData";
			param->getUAPContainer(*&name, *&document);
			
			*name = "DBPrimaryKeys";
			QI(dbPrimaryKeys, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "DBForeignKeys";
			QI(dbForeignKeys, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "DBTables";
			QI(dbTables, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "DBColumns";
			QI(dbColumns, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "ApplicationData";
			param->setUAPContainer(*&name, *&document);
		}		

		haveLoadedDBModel = true;
	}
	return err;
}


lbErrCodes LB_STDCALL lbDynamicApplication::importUMLXMIDocIntoApplication(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}

	metaapp->setStatusText("Info", "Importing from UML (XMI) file ...");

	// Need to ask for the XMI file exported from BoUML
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	UAP(lb_I_InputStream, importfile)
	
	importfile = metaapp->askOpenFileReadStream("xmi");

	// Get the active document and set temporary a different storage handler (xmi import)
	UAP_REQUEST(manager.getPtr(), lb_I_String, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageNamespace)
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
		
	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);
			
		*tempStorageNamespace = "lbDynAppUMLImport";
		document->setUAPString(*&param, *&tempStorageNamespace);
	}

	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");
	
	if (pl == NULL) {
		_LOG << "Error: Could not save dynamic application data. No plugin found." LOG_
		return ERR_FILE_WRITE;
	}
	
	if (pl != NULL) {
		ukPl = pl->getImplementation();
		UAP(lb_I_FileOperation, fOp)
		QI(ukPl, lb_I_FileOperation, fOp)
			
		if (fOp != NULL) {
			bool success = false;
			
			success = fOp->begin(importfile.getPtr()); 
			
			if (success) {
				accept(*&fOp);
				fOp->end();
			} else {
				// No file found. Create one from database...
			}
		}
	}
	return err;
}


/*...sevent handlers\44\ that can be registered:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::exportApplicationToXML(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}
	
	if (haveLoadedDBModel == false) {
		metaapp->setStatusText("Info", "Loading target database schema ...");
		loadDatabaseSchema(NULL);
		if (haveLoadedDBModel == false) {
			metaapp->msgBox("Error", "Failed to load target database schema.\n\nThis is required for XML export.");
			return err;
		}
	}

	metaapp->setStatusText("Info", "Exporting to XML ...");
	
	// Need to derive filename from given application name
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	*filename = LogonApplication->charrep();
	*filename += ".dax"; // Dynamic application forms 
	
	
	// Get the active document and set temporary a different storage handler (dax)
	UAP_REQUEST(manager.getPtr(), lb_I_String, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageNamespace)
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
		
	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);
			
		*tempStorageNamespace = "lbDynAppXMLFormat";
		document->setUAPString(*&param, *&tempStorageNamespace);
	}
	
	
	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "XMLOutputStreamVisitor");
	
	if (pl == NULL) {
		_LOG << "Error: Could not save dynamic application data. No plugin found." LOG_
		return ERR_FILE_WRITE;
	}
	
	if (pl != NULL) {
		ukPl = pl->getImplementation();
		
		UAP(lb_I_FileOperation, fOp)
			
			QI(ukPl, lb_I_FileOperation, fOp)
			
			if (fOp != NULL) {
				bool success = false;
				
				success = fOp->begin(filename->charrep()); 
				
				if (success) {
					accept(*&fOp);
					fOp->end();
				} else {
					// No file found. Create one from database...
				}
			}
	}
	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getCustomDBForm(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}

	if (gui == NULL) {
		metaapp->getGUI(&gui);
	}
	
	metaapp->setStatusText("Info", "Loading custom database formular ...");

	if (gui != NULL) {
		UAP(lb_I_FixedDatabaseForm, dbForm)
		UAP(lb_I_Integer, eventID)
		
		QI(uk, lb_I_Integer, eventID)
		
		char* eventName = eman->reverseEvent(eventID->getData());
		
		if ((forms != NULL) && (forms->getFormularCount() > 0)) {
			forms->finishFormularIteration();
			while (forms->hasMoreFormulars()) {
				forms->setNextFormular();
				
				if (strcmp(forms->getEventName(), eventName) == 0) {
					forms->finishFormularIteration();
					metaapp->setStatusText("Info", "Found the form by reversing event ID ...");
					break;
				}
			}
		}
		
		UAP(lb_I_Query, q)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, typ)
		UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
		q = database->getQuery("lbDMF", 0);
		
		typ->setData(forms->getTyp());
		
		*sql = "SELECT handlerfunctor, handlermodule, handlerinterface, namespace from formulartypen where id = ";
		*sql += typ->charrep();

		_LOG << "Query for custom database formular (" << forms->getName() << "): " << sql->charrep() LOG_
		
		if (q->query(sql->charrep()) == ERR_NONE) {
			
			err = q->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP(lb_I_String, functor)
				UAP(lb_I_String, module)
				UAP(lb_I_String, _interface)
				UAP(lb_I_String, namesp)
				
				functor = q->getAsString(1);
				module = q->getAsString(2);
				_interface = q->getAsString(3);
				namesp = q->getAsString(4);
				
				if (*namesp == "") {
						metaapp->setStatusText("Info", "Error: No namespace stored in the database !");
				} else {
					if (*_interface == "lb_I_FixedDatabaseForm") { 
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						UAP(lb_I_Plugin, pl)
						UAP(lb_I_Unknown, ukPl)
						
						pl = PM->getFirstMatchingPlugin("lb_I_FixedDatabaseForm", namesp->charrep());
						
						if (pl == NULL) {
							return ERR_NONE;
						}
						
						if (pl != NULL) {
							ukPl = pl->getImplementation();
							
							QI(ukPl, lb_I_FixedDatabaseForm, dbForm)

							dbForm = gui->addCustomDBForm(dbForm.getPtr(), forms->getName());
								
							if (dbForm != NULL) {
								dbForm->show();
							} else {
								metaapp->setStatusText("Info", "Error: Database form was not loaded by the GUI !");
							}
						}
					} else {
						metaapp->setStatusText("Info", "Error: Unsupported interface !");
						// Unsupported
					}
				}
			}		
		} else {
			_LOG << "Error: Query to get target formular failed. (" << sql->charrep() << ")" LOG_
			metaapp->setStatusText("Info", "Error: Query to get target formular failed !");
		}
	} else {
		metaapp->setStatusText("Info", "Error: Have no instance of GUI !");
	}
	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::resetCustomDBFormsToDynamic(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	if(database == NULL) {
		REQUEST(manager.getPtr(), lb_I_Database, database)
		database->init();
		
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");
		
		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";
		
		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
	}
	
	UAP(lb_I_Query, sampleQuery)
	sampleQuery = database->getQuery("lbDMF", 0);

	UAP_REQUEST(getModuleInstance(), lb_I_String, q)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	
	id->setData(metaapp->getApplicationID());
	
	*q = "update formulare set typ = 1 where anwendungid = ";
	*q += id->charrep();

	sampleQuery->skipFKCollecting();
	sampleQuery->query(q->charrep());
	sampleQuery->enableFKCollecting();
	

	return err;
}


lbErrCodes LB_STDCALL lbDynamicApplication::getDynamicDBForm(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	if (gui != NULL) {
	        UAP(lb_I_DatabaseForm, dbForm)

/*...sDoc:16:*/
		/*
			To get the data from the database, we do transmit only a few data by uk to this
			function.
			
			It would be only the form id it self. Additionally, we need to check the typ of the
			formular to be really a DynamicDBForm.
			
			If this is ok, we need to load the additional query from a foreign table for that
			typ of form.
			
			At best, this functionality is placed in a separate class.
		*/
/*...e*/

		UAP(lb_I_Integer, eventID)
		UAP(lb_I_Query, sampleQuery)

		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		UAP_REQUEST(manager.getPtr(), lb_I_String, query)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formID)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formName)

		UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

		QI(uk, lb_I_Integer, eventID)

		// Retrieve the event name from their ID

		char* eventName = eman->reverseEvent(eventID->getData());

#ifdef USE_RDCD_MODEL
		if (model != NULL) {
			model->selectFormByEventName(eventName);
			
			dbForm = gui->createDBForm(	model->getFormularName(), 
										model->getFormularQuery(),
										model->getDBName(), 
										model->getDBUser(), 
										model->getDBPass());
			
			if (dbForm != NULL) dbForm->show();
			
		} else {
#endif

		if ((forms != NULL) && (forms->getFormularCount() > 0)) {
			forms->finishFormularIteration();
			while (forms->hasMoreFormulars()) {
				forms->setNextFormular();
				
				if (strcmp(forms->getEventName(), eventName) == 0) {
					forms->finishFormularIteration();
					break;
				}
			}
			
			// appParams->getParameter() changes results to prior issued calls. Do temporaly make copies.
			
			long id = metaapp->getApplicationID();			

			*DBName = appParams->getParameter("DBName", id);
			*DBUser = appParams->getParameter("DBUser", id);
			*DBPass = appParams->getParameter("DBPass", id);

			if (*DBName == "") {
				metaapp->msgBox("Information", "Your local application configuration is out of sync.\n\nPlease activate 'Prefer database configuration' at least for one application restart.\n\nThen restart the application.");
				return err;
			}
		
			dbForm = gui->createDBForm(	forms->getName(),
							formParams->getParameter("query", forms->getFormularID()), 
							DBName->charrep(), 
							DBUser->charrep(), 
							DBPass->charrep());
										
			if (dbForm != NULL) dbForm->show();
		} else {
			// Use old version with direct database queries. This could happen, if no plugin was found, no file was found and couldn't created.
			
			if(database == NULL) {
				REQUEST(manager.getPtr(), lb_I_Database, database)
				database->init();
				
				char* lbDMFPasswd = getenv("lbDMFPasswd");
				char* lbDMFUser   = getenv("lbDMFUser");
				
				if (!lbDMFUser) lbDMFUser = "dba";
				if (!lbDMFPasswd) lbDMFPasswd = "trainres";
				
				database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
			}
			
			sampleQuery = database->getQuery("lbDMF", 0);
			
			char* b =
				"select Formulare.id, Formulare.name from Formulare "
				"inner join Anwendungen on Formulare.anwendungid = Anwendungen.id inner join "
				"User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
				" User_Anwendungen.userid = Users.id where "
				"Users.userid = '%s' and Anwendungen.name = '%s' and "
				"Formulare.eventname = '%s'";
			
			char* buffer = (char*) malloc(strlen(b)+strlen(LogonUser->charrep())+strlen(LogonApplication->charrep())+strlen(eventName)+1);
			
			buffer[0] = 0;
			
			sprintf(buffer, b, LogonUser->charrep(), LogonApplication->charrep(), eventName);
			
			// Get the ID and Name of the intented formular
			
			_CL_LOG << "Logon user is: " << LogonUser->charrep() LOG_
			_CL_LOG << "Logon app is: " << LogonApplication->charrep() LOG_
				
			sampleQuery->query(buffer);
			
			err = sampleQuery->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				formID = sampleQuery->getAsString(1);
				formName = sampleQuery->getAsString(2);
			}
			
			
			//- Internal formular implementation ------------------------------------------------
			
			b =
				"select parametervalue from formular_parameters "
				"where parametername = 'query' and "
				"formularid = %s";
			
			free(buffer);
			
			buffer = (char*) malloc(strlen(b)+strlen(formID->charrep())+1);
			
			buffer[0] = 0;
			
			sprintf(buffer, b, formID->charrep());
			
			UAP(lb_I_Query, formularQuery)
				
			formularQuery = database->getQuery("lbDMF", 0);
			
			// It is an internal formular and I don't distinguish between 
			// different formular implementations yet
			
			formularQuery->skipFKCollecting();
			formularQuery->query(buffer);
			formularQuery->enableFKCollecting();
			
			err = formularQuery->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				query = formularQuery->getAsString(1);
				
				if ((query != NULL) && (query->charrep() == NULL)) {
					_LOG << "Error: Getting SQL query for the formular '" << formID->charrep() << "' failed." LOG_
				} else {
					_LOG << "Have got this query for the form: " << query->charrep() LOG_
				}
			} else {
				_CL_LOG << "Error: Something happens while getting the formular SQL query!" LOG_
			}
			
			b = 
				"select parametername, parametervalue from anwendungs_parameter inner join "
				"anwendungen on anwendungs_parameter.anwendungid = anwendungen.id where "
				"anwendungen.name = '%s'";
			
			free(buffer);
			
			buffer = (char*) malloc(strlen(b)+strlen(LogonApplication->charrep())+1);
			
			buffer[0] = 0;
			
			sprintf(buffer, b, LogonApplication->charrep());
			
			UAP(lb_I_Query, DBConnQuery)
				
			DBConnQuery = database->getQuery("lbDMF", 0);
			
			DBConnQuery->query(buffer);
			
			err = DBConnQuery->first();
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
				
				if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
					parameter = DBConnQuery->getAsString(1);
					
					if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
					if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
					if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
					
					err = DBConnQuery->next();
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						parameter = DBConnQuery->getAsString(1);
						if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
						if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
						if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
					} else {
						_LOG << "Fehler: Konnte DBUser nicht auslesen" LOG_
					}
					
					err = DBConnQuery->next();
					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						parameter = DBConnQuery->getAsString(1);
						if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
						if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
						if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
					} else {
						_LOG << "Fehler: Konnte DBPass nicht auslesen" LOG_
					}
					
				}		
			
			_CL_LOG << "Create a database form for " << formName->charrep() << " with " << query->charrep() LOG_
				
				dbForm = gui->createDBForm(formName->charrep(), query->charrep(), 
										   DBName->charrep(), DBUser->charrep(), DBPass->charrep());
			
			if (dbForm != NULL) dbForm->show();
			
			//- External formular implementation ---------------------------------------------------
			//- Would load an external module and optionally use other parameters from configuratoin
			//--------------------------------------------------------------------------------------
			
			free(buffer);
#ifdef USE_RDCD_MODEL
		}
#endif
}
	} else {
	        COUT << "KundenDetails" << ENDL;
	}

        return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicApplication)
	ADD_INTERFACE(lb_I_Application)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfApplication, lbDynamicApplication)

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::setData(lb_I_Unknown* uk) {
	_LOG << "lbDynamicApplication::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager\42\ LB_STDCALL lbDynamicApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL lbDynamicApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\uninitialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::uninitialize() {
		lbErrCodes err = ERR_NONE;
		
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		// Need to derive filename from given application name
		UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
		*filename = LogonApplication->charrep();
		*filename += ".daf"; // Dynamic application forms 


		// Get the active document and set temporary a different storage handler (daf)
		UAP_REQUEST(manager.getPtr(), lb_I_String, param)
		UAP_REQUEST(manager.getPtr(), lb_I_String, StorageInterface)
		UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)
		UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageInterface)
		UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageNamespace)
		UAP(lb_I_Unknown, ukDoc)
		UAP(lb_I_Parameter, document)
		ukDoc = metaapp->getActiveDocument();
		QI(ukDoc, lb_I_Parameter, document)

		if (document != NULL) {
			*param = "StorageDelegateNamespace";
			document->getUAPString(*&param, *&StorageNamespace);
			
			*tempStorageNamespace = "lbDynAppInternalFormat";
			document->setUAPString(*&param, *&tempStorageNamespace);
		}
		
		/// \todo Move storing procedure to a storage handler.

		pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");
		
		if (pl == NULL) {
			_LOG << "Error: Could not save dynamic application data. No plugin found." LOG_
			return ERR_FILE_WRITE;
		}
		
		if (pl != NULL) {
			ukPl = pl->getImplementation();
				
			UAP(lb_I_FileOperation, fOp)

			QI(ukPl, lb_I_FileOperation, fOp)
			
			if (fOp != NULL) {
				bool success = false;
				
				success = fOp->begin(filename->charrep()); 
			
				if (success) {
					accept(*&fOp);
					fOp->end();
					_LOG << "Saved application data to " << filename->charrep() << "." LOG_
				} else {
				// No file found. Create one from database...
				}
			}
		}

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::initialize(char* user, char* app) {
	_CL_LOG << "lbDynamicApplication::initialize(...) called." LOG_	
	// To be implemented in a separate application module
	lbErrCodes err = ERR_NONE;
	int unused;

	// Get the event manager
	
	lb_I_Module* m = *&manager;
	
	REQUEST(m, lb_I_EventManager, eman)
		
	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());
	
	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}
	
	// Save user and app internally
	
	if (user == NULL) {
        _CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonUser)
		}
	LogonUser->setData(user);
	
	if (app == NULL) {
        _CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
	} else
		if (LogonApplication == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
		}
	LogonApplication->setData(app);
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
		
	// Need to derive filename from given application name
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	*filename = LogonApplication->charrep();
	*filename += ".daf"; // Dynamic application forms 
	
	bool isFileAvailable = false;
	bool isDBAvailable = false;
	bool DBOperation = false;
	
	UAP(lb_I_FileOperation, fOp)
	UAP(lb_I_DatabaseOperation, fOpDB)

	_CL_LOG << "Try to find a lb_I_FileOperation plugin ..." LOG_
	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");
	
	if (pl != NULL)	{
		_CL_LOG << "Found one ..." LOG_
		ukPl = pl->getImplementation();
	} else {
		_LOG << "No lb_I_FileOperation plugin available." LOG_	
	}
	
	if (ukPl != NULL) QI(ukPl, lb_I_FileOperation, fOp)
	if (fOp == NULL) {
		_LOG << "Error: Found a lb_I_FileOperation plugin via PM->getFirstMatchingPlugin(...), but QI failed." LOG_
	} else {
		isFileAvailable = fOp->begin(filename->charrep()); 
	}

	UAP(lb_I_Query, sampleQuery)
	if (database == NULL) {
		REQUEST(manager.getPtr(), lb_I_Database, database)
		database->init();
	}
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	

	if (!isFileAvailable || metaapp->getLoadFromDatabase()) {
		if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
			_LOG << "Warning: No system database available." LOG_
		} else {
			pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
			if (pl != NULL)	ukPl = pl->getImplementation();
			if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpDB) 
			if (fOpDB != NULL) {
				UAP(lb_I_ApplicationParameter, appParams)
				AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")
			
				if (fOpDB->begin("lbDMF", database.getPtr())) {
					_LOG << "System database is available. Read database connection parameters from there." LOG_
					appParams->accept(*&fOpDB);
					fOpDB->end();
				} else {
					// System database is not available
					UAP(lb_I_Formulars, forms)
					UAP(lb_I_Formular_Fields, formularfields)
					UAP(lb_I_Column_Types, columntypes)
					UAP(lb_I_FormularParameter, formParams)
					UAP(lb_I_Formular_Actions, formActions)
					UAP(lb_I_Actions, appActions)
					UAP(lb_I_Action_Steps, appActionSteps)
					UAP(lb_I_Action_Types, appActionTypes)
					UAP(lb_I_DBTables, dbTables)
					UAP(lb_I_DBColumns, dbColumns)
					UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
					UAP(lb_I_DBForeignKeys, dbForeignKeys)

					UAP(lb_I_Reports, reports)
					UAP(lb_I_ReportParameters, reportparams)
					UAP(lb_I_ReportElements, reportelements)
					UAP(lb_I_ReportElementTypes, reportelementtypes)
					UAP(lb_I_ReportTexts, reporttextblocks)
					
					if (isFileAvailable) {
						AQUIRE_PLUGIN(lb_I_Reports, Model, reports, "'database report'")
						AQUIRE_PLUGIN(lb_I_ReportParameters, Model, reportparams, "'database report parameter'")
						AQUIRE_PLUGIN(lb_I_ReportElements, Model, reportelements, "'database report elements'")
						AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, reportelementtypes, "'database report element types'")
						AQUIRE_PLUGIN(lb_I_ReportTexts, Model, reporttextblocks, "'database report text blocks'")
						AQUIRE_PLUGIN(lb_I_Column_Types, Model, columntypes, "'column types'")
						AQUIRE_PLUGIN(lb_I_Actions, Model, appActions, "'actions'")
						AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, formActions, "'formular actions'")
						AQUIRE_PLUGIN(lb_I_Action_Types, Model, appActionTypes, "'action types'")
						AQUIRE_PLUGIN(lb_I_Action_Steps, Model, appActionSteps, "'action steps'")
						AQUIRE_PLUGIN(lb_I_Formulars, Model, forms, "'formulars'")
						AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, formularfields, "'formular fields'")
						AQUIRE_PLUGIN(lb_I_FormularParameter, Model, formParams, "'formular parameters'")
						
						
						metaapp->setStatusText("Info", "Preload application data from file ...");
						
						reports->accept(*&fOp);
						reportparams->accept(*&fOp);
						reportelements->accept(*&fOp);
						reportelementtypes->accept(*&fOp);
						reporttextblocks->accept(*&fOp);
						
						forms->accept(*&fOp);
						formularfields->accept(*&fOp);
						columntypes->accept(*&fOp);
						formActions->accept(*&fOp);
						formParams->accept(*&fOp);
						appParams->accept(*&fOp);
						appActions->accept(*&fOp);
						appActionTypes->accept(*&fOp);
						appActionSteps->accept(*&fOp);
						fOp->end();
					} else {
						// FATAL: No system database and no file.
						metaapp->msgBox("Fatal", "No system database has been setup and no previously created file is available.");
						return ERR_NONE;
					}
				}
			
				// If the applications database is not the system database, also connect to that database too. 
				if (strcmp(appParams->getParameter("DBName", metaapp->getApplicationID()), "lbDMF") != 0) {
					UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
					UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
					UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)
					
					*DBName = appParams->getParameter("DBName", metaapp->getApplicationID());
					*DBUser = appParams->getParameter("DBUser", metaapp->getApplicationID());
					*DBPass = appParams->getParameter("DBPass", metaapp->getApplicationID());
					
					if ((database != NULL) && (database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE)) {
						_LOG << "Warning: No application database available. (DBName=" << DBName->charrep() << ", DBUser=" << DBUser->charrep() << ", ApplicationID=" << metaapp->getApplicationID() << ")" LOG_
					}				
				}
				
				// Pass the applications ODBC database name.
				isDBAvailable = fOpDB->begin(appParams->getParameter("DBName", metaapp->getApplicationID()), database.getPtr());			
				DBOperation = true;
			}
		}
	}
	

		
	
	
	_CL_LOG << "Load application settings from file or database ..." LOG_

		if (isFileAvailable || isDBAvailable) {
			/*...sLoad from file or database:16:*/
			/*...sInitialize plugin based document models:32:*/
			AQUIRE_PLUGIN(lb_I_Reports, Model, reports, "'database report'")
			AQUIRE_PLUGIN(lb_I_ReportParameters, Model, reportparams, "'database report parameter'")
			AQUIRE_PLUGIN(lb_I_ReportElements, Model, reportelements, "'database report elements'")
			AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, reportelementtypes, "'database report element types'")
			AQUIRE_PLUGIN(lb_I_ReportTexts, Model, reporttextblocks, "'database report text blocks'")
			AQUIRE_PLUGIN(lb_I_Column_Types, Model, columntypes, "'column types'")
			AQUIRE_PLUGIN(lb_I_Actions, Model, appActions, "'actions'")
			AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, formActions, "'formular actions'")
			AQUIRE_PLUGIN(lb_I_Action_Types, Model, appActionTypes, "'action types'")
			AQUIRE_PLUGIN(lb_I_Action_Steps, Model, appActionSteps, "'action steps'")
			AQUIRE_PLUGIN(lb_I_Formulars, Model, forms, "'formulars'")
			AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, formularfields, "'formular fields'")
			AQUIRE_PLUGIN(lb_I_FormularParameter, Model, formParams, "'formular parameters'")
			AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")
			
			/*...e*/
			
			
			// Only this part is how to load the data. So here I have to set the correct handler for the load delegation routine.
			
			// Loading the application related data succeeded. Put these into a parameter object for reference.
			
			UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
			UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
			UAP_REQUEST(manager.getPtr(), lb_I_String, name)
			UAP_REQUEST(manager.getPtr(), lb_I_String, value)
			UAP(lb_I_KeyBase, key)
			QI(name, lb_I_KeyBase, key)
			
			param->setCloning(false);
			document->setCloning(false);
			
			*name = "StorageDelegateInterface";
			*value = "lb_I_Streamable";
			param->setUAPString(*&name, *&value);
			
			*name = "StorageDelegateNamespace";
			*value = "DynamicAppXMLStorage";
			param->setUAPString(*&name, *&value);
			
			if (!DBOperation && 
				(reports != NULL) && 
				(reportparams != NULL) && 
				(reportelements != NULL) && 
				(reportelementtypes != NULL) && 
				(reporttextblocks != NULL) && 
				(forms != NULL) && 
				(formularfields != NULL) && 
				(formParams != NULL) && 
				(appActions != NULL) && 
				(appActionSteps != NULL) && 
				(appActionTypes != NULL) && 
				(appParams != NULL)) {
				_LOG << "Load application data from file ..." LOG_
				metaapp->setStatusText("Info", "Load application data from file ...");
				
				reports->accept(*&fOp);
				reportparams->accept(*&fOp);
				reportelements->accept(*&fOp);
				reportelementtypes->accept(*&fOp);
				reporttextblocks->accept(*&fOp);
				
				forms->accept(*&fOp);
				formularfields->accept(*&fOp);
				columntypes->accept(*&fOp);
				formActions->accept(*&fOp);
				formParams->accept(*&fOp);
				appParams->accept(*&fOp);
				appActions->accept(*&fOp);
				appActionTypes->accept(*&fOp);
				appActionSteps->accept(*&fOp);
			}
			
			if ((metaapp->getLoadFromDatabase() || !isFileAvailable) && DBOperation && 
				(reports != NULL) && 
				(reportparams != NULL) && 
				(reportelements != NULL) && 
				(reportelementtypes != NULL) && 
				(reporttextblocks != NULL) && 
				(forms != NULL) && 
				(formularfields != NULL) && 
				(formParams != NULL) && 
				(appActions != NULL) && 
				(appActionSteps != NULL) && 
				(appActionTypes != NULL) && 
				(appParams != NULL)) {
				_LOG << "Load application data from database ..." LOG_
				metaapp->setStatusText("Info", "Load application data from database ...");
				
				reports->accept(*&fOpDB);
				reportparams->accept(*&fOpDB);
				reportelements->accept(*&fOpDB);
				reportelementtypes->accept(*&fOpDB);
				reporttextblocks->accept(*&fOpDB);
				
				forms->accept(*&fOpDB);
				formularfields->accept(*&fOpDB);
				columntypes->accept(*&fOpDB);
				formActions->accept(*&fOpDB);
				formParams->accept(*&fOpDB);
				appParams->accept(*&fOpDB);
				appActions->accept(*&fOpDB);
				appActionTypes->accept(*&fOpDB);
				appActionSteps->accept(*&fOpDB);
			}
			
			if (!DBOperation) fOp->end();
			if (DBOperation) fOpDB->end();
				
				if ((forms != NULL) && 
					(reports != NULL) && 
					(reportparams != NULL) && 
					(reportelements != NULL) && 
					(reportelementtypes != NULL) && 
					(reporttextblocks != NULL) && 
					(formularfields != NULL) && 
					(formParams != NULL) && 
					(appActions != NULL) && 
					(appActionSteps != NULL) && 
					(appActionTypes != NULL) && 
					(appParams != NULL)) {
					
					UAP(lb_I_Unknown, uk)
					
					
					*name = "Reports";
					QI(reports, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "Reportparams";
					QI(reportparams, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "Reportelements";
					QI(reportelements, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "Reportelementtypes";
					QI(reportelementtypes, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "Reporttextblocks";
					QI(reporttextblocks, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					
					
					*name = "Formulars";
					QI(forms, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "FormularFields";
					QI(formularfields, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "ColumnTypes";
					QI(columntypes, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "FormActions";
					QI(formActions, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "FormParams";
					QI(formParams, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "AppParams";
					QI(appParams, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "AppActions";
					QI(appActions, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "AppAction_Steps";
					QI(appActionSteps, lb_I_Unknown, uk)
						document->insert(&uk, &key);
					
					*name = "AppActionTypes";
					QI(appActionTypes, lb_I_Unknown, uk)
						document->insert(&uk, &key);
				}		
				
				*name = "ApplicationData";
				param->setUAPContainer(*&name, *&document);
				
				param++;
				metaapp->setActiveDocument(*&param);
				
				int id = metaapp->getApplicationID();
				
				_LOG << "Test for application ID: " << id LOG_
					
				// Test if the lbDynamicAppStorage plugin is available. If so, add a menu entry for application export.
					
				UAP(lb_I_Plugin, plDynamicAppStorageXMLFormat)
				UAP(lb_I_Unknown, ukPlDynamicAppStorageXMLFormat)

				UAP(lb_I_Plugin, plDynamicAppStorageUMLXMIImport)
				UAP(lb_I_Unknown, ukPlDynamicAppStorageUMLXMIImport)
					
				plDynamicAppStorageXMLFormat = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", "lbDynAppXMLFormat");
				if (plDynamicAppStorageXMLFormat != NULL) {
					ukPlDynamicAppStorageXMLFormat = plDynamicAppStorageXMLFormat->getImplementation();
					
					if (eman->resolveEvent("evtExportApplicationToXML", unused) == ERR_EVENT_NOTREGISTERED) {
						eman->registerEvent("evtExportApplicationToXML", unused);
						
						dispatcher->addEventHandlerFn(this, 
													  (lbEvHandler) &lbDynamicApplication::exportApplicationToXML, "evtExportApplicationToXML");
						
						metaapp->addMenuEntry(_trans("&File"), "export Application to XML", "evtExportApplicationToXML", "");
					}
				}

				UAP_REQUEST(getModuleInstance(), lb_I_String, appname)
		
				metaapp->getApplicationName(&appname);
	
				if (*appname == "lbDMF Manager") {
					
					plDynamicAppStorageUMLXMIImport = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", "lbDynAppUMLImport");
					if (plDynamicAppStorageUMLXMIImport != NULL) {
						ukPlDynamicAppStorageUMLXMIImport = plDynamicAppStorageUMLXMIImport->getImplementation();
						
						if (eman->resolveEvent("importUMLXMIDocIntoApplication", unused) == ERR_EVENT_NOTREGISTERED) {
							eman->registerEvent("importUMLXMIDocIntoApplication", unused);
							
							dispatcher->addEventHandlerFn(this, 
														  (lbEvHandler) &lbDynamicApplication::importUMLXMIDocIntoApplication, "importUMLXMIDocIntoApplication");
							
							metaapp->addMenuEntry(_trans("&File"), "import Application from UML (as XMI file)", "importUMLXMIDocIntoApplication", "");
							
							// Possibly here I should add additional property fields such as target database name (ODBC name), user and password.
							
							
							if (eman->resolveEvent("editProperties", unused) == ERR_EVENT_NOTREGISTERED) {
								eman->registerEvent("editProperties", unused);
								dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::editProperties, "editProperties");
								metaapp->addMenuEntry("Edit", "&edit Properties" , "editProperties", "");
							}
							
							editProperties(NULL);
						}
					}
					
				}				
				/*...e*/
		} else {
		// No file found. Create one from database...
	}
	
	_CL_LOG << "Begin setup menu ..." LOG_
		
	/*
	 Select all events, that are configured and register it.
	 */
	
	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
	
	activateDBForms(user, app);
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, editMenu)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menuEntry)
	
	*editMenu = _trans("&Edit");
	*menuEntry = _trans("Set all forms back to dynamic");
	
	eman->registerEvent("resetCustomDBFormsToDynamic", unused);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::resetCustomDBFormsToDynamic, "resetCustomDBFormsToDynamic");
	metaapp->addMenuEntry(editMenu->charrep(), menuEntry->charrep(), "resetCustomDBFormsToDynamic", "");

	
	return ERR_NONE;
}

void LB_STDCALL lbDynamicApplication::activateDBForms(char* user, char* app) {
	UAP(lb_I_Query, sampleQuery)
	bool toolbaradded = false;
	int unused;
	sampleQuery = database->getQuery("lbDMF", 0);	
	
	char* b =
		"select Formulare.eventname, Formulare.menuname, Formulare.toolbarimage, Formulare.typ from Formulare inner join "
		"anwendungen_formulare on anwendungen_formulare.formularid = formulare.id inner join "
		"Anwendungen on anwendungen_formulare.anwendungid = Anwendungen.id inner join "
		"User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		"User_Anwendungen.userid = Users.id where "
		"Users.userid = '%s' and Anwendungen.name = '%s' order by Formulare.menuorder";
	
	char* buffer = (char*) malloc(strlen(b)+strlen(user)+strlen(app)+1);
	
	sprintf(buffer, b, user, app);
	
	if (sampleQuery == NULL) printf("NULL pointer !\n");
	
	_CL_LOG << "lbDynamicApplication::Initialize('" << user << "', '" << app << "');" LOG_
	_CL_LOG << "Query: " << buffer LOG_
		
	sampleQuery->skipFKCollecting();
	sampleQuery->query(buffer);
	sampleQuery->enableFKCollecting();
	
	char* ed = strdup(_trans("&Edit"));
	
	char* menu = strdup(_trans(app));
	
	metaapp->addMenuBar(menu, ed);
	
	free(ed);
	free(menu);
	free(buffer);

	
	lbErrCodes DBerr = sampleQuery->first();
	if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
		UAP(lb_I_String, EventName)
		UAP(lb_I_String, MenuName)
		UAP(lb_I_String, ToolBarImage)
		UAP(lb_I_Long, Typ)
		
		EventName = sampleQuery->getAsString(1);
		MenuName = sampleQuery->getAsString(2);
		ToolBarImage = sampleQuery->getAsString(3);
		Typ = sampleQuery->getAsLong(4);
		
		if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {
			
			eman->registerEvent(EventName->charrep(), unused);
			
			if (Typ->getData() == 1L)
				dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());
			else
				dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getCustomDBForm, EventName->charrep());
			
			metaapp->addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");
			
			if (strcmp(ToolBarImage->charrep(), "") != 0) {
				if (toolbaradded == false) {
					metaapp->addToolBar(app);
					toolbaradded = true;
				}
				
				ToolBarImage->trim();
				
				metaapp->addToolBarButton(app, MenuName->charrep(), EventName->charrep(), ToolBarImage->charrep());
			}
			
		} else {
			_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
		}
		
		if (DBerr == WARN_DB_NODATA) return;
		if (DBerr == ERR_DB_NODATA) return;
#define TRUE 1
		while (TRUE) {
			/*...sget rest of menu entries:24:*/
			UAP(lb_I_String, EventName)
			UAP(lb_I_String, MenuName)
			UAP(lb_I_String, ToolBarImage)
			UAP(lb_I_Long, Typ)

			DBerr = sampleQuery->next();
			
			if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
				EventName = sampleQuery->getAsString(1);
				MenuName = sampleQuery->getAsString(2);
				ToolBarImage = sampleQuery->getAsString(3);
				Typ = sampleQuery->getAsLong(4);
				
				if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent(EventName->charrep(), unused);
					
				if (Typ->getData() == 1L)
					dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());
				else
					dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getCustomDBForm, EventName->charrep());
					
				metaapp->addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");
					
				if (strcmp(ToolBarImage->charrep(), "") != 0) {
					if (toolbaradded == false) {
						metaapp->addToolBar(app);
						toolbaradded = true;
					}
						
					ToolBarImage->trim();
						
					metaapp->addToolBarButton(app, MenuName->charrep(), EventName->charrep(), ToolBarImage->charrep());
				}
					
				} else {
					_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
				}
				if (DBerr == WARN_DB_NODATA) break;
			}
			if (DBerr == ERR_DB_NODATA) break;
			/*...e*/
		}
		
	} else {
		_CL_LOG << "Error: No forms are defined for application." LOG_
	}
}


/*...e*/
lbErrCodes LB_STDCALL lbDynamicApplication::getUserName(lb_I_String** user) {
	if (LogonUser == NULL) (*user)->setData("");
	else (*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getApplicationName(lb_I_String** app) {
	if (LogonApplication == NULL) (*app)->setData("");
	else (*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL lbDynamicApplication::setUserName(char* user) {
	if (LogonUser == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::setApplicationName(char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


// This starts the main application

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);	
#endif
	return ERR_NONE;
}
/*...e*/

/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
                	
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

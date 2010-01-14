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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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

    lbErrCodes LB_STDCALL save();
    lbErrCodes LB_STDCALL load();

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

	lb_I_Unknown* LB_STDCALL getUnknown();
	
	/**
	 * \brief The main handler to create dynamic forms
	 */
	lbErrCodes LB_STDCALL getDynamicDBForm(lb_I_Unknown* uk);

	/**
	 * \brief Export the application model as XML file.
	 */
	lbErrCodes LB_STDCALL exportApplicationToXML(lb_I_Unknown* uk);

	/**
	 * \brief Export the application model into XML memory block.
	 *
	 * This is achieved by providing a lb_I_OutputStream instance
	 * with the flag set to buffer.
	 */
	lbErrCodes LB_STDCALL exportApplicationToXMLBuffer(lb_I_Unknown* uk);

	/** \brief Import an UML XMI document as an application configuration. */
	lbErrCodes LB_STDCALL importUMLXMIDocIntoApplication(lb_I_Unknown* uk);

	/** \brief Export XML formatted application configuration as an UML XMI document. */
	lbErrCodes LB_STDCALL exportApplicationConfigurationToUMLXMIDoc(lb_I_Unknown* uk);

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

	/** \brief Setup the systemdatabase.
	 *
	 * This function is used to initialize the system database with the devault content.
	 * Depending on the used database system, there would be done different steps.
	 */
	lbErrCodes LB_STDCALL setupSystemDatabase(lb_I_Unknown* uk);

	/** \brief This function should be used to execute a SQL query.
	 * The SQL query is executed against the currently active database of the running application.
	 * Thus, when DatabaseLayerGateway is activated, the Sqlite database backend is used for that
	 * SQL query. 
	 */
	lbErrCodes LB_STDCALL executeQueryFromFile(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL overwriteDatabase(lb_I_Unknown* uk);
protected:

	/** \brief Load the database forms.
	 */
	void LB_STDCALL activateDBForms(char* user, char* app);

	void LB_STDCALL loadDataFromActiveDocument();
	void LB_STDCALL saveDataToActiveDocument();

	bool haveLoadedDBModel;
	UAP(lb_I_String, lastExportedApp)

	bool _overwriteDatabase;

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

	/// \brief Dirty flag.
	bool dirty;

	// Preloaded data from database, if plugins are available.
	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
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
	
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
	UAP(lb_I_Action_Parameters, appActionParameters)
	UAP(lb_I_ActionStep_Parameters, appActionStepParameters)
	

	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)


	UAP(lb_I_String, GeneralDBSchemaname)

	UAP(lb_I_String, UMLImportTargetDBName)
	UAP(lb_I_String, UMLImportTargetDBUser)
	UAP(lb_I_String, UMLImportTargetDBPass)

	UAP(lb_I_String, DatabaseSettingNamespace)
	UAP(lb_I_Boolean, UsePlugin)

	/// \brief The import file
	UAP(lb_I_FileLocation, XMIFileUMLProject)
	/// \brief The export file
	UAP(lb_I_FileLocation, XMIFileUMLProjectExport)

	/** \brief Import settings file
	 *
	 * This file get's written each time an UML import happens. With the settings file it is possible to control the way of import.
	 * For sample the system database may be an ODBC PostgreSQL or a Sqlite database backend (for now), thus the settings file
	 * will contain that information before the transformation begins.
	 */
	UAP(lb_I_FileLocation, XSLFileImportSettings)
	UAP(lb_I_FileLocation, XSLFileExportSettings)
	UAP(lb_I_FileLocation, XSLFileSystemDatabase)
	UAP(lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP(lb_I_FileLocation, XSLFileUMLExport)
	//UAP(lb_I_Boolean, UseOtherXSLFile)


	char hdsihd[100];
};
/*...e*/
/*...slbDynamicApplication:0:*/
/*...sctors\47\dtors:0:*/
lbDynamicApplication::lbDynamicApplication() {
	ref = STARTREF;
	gui = NULL;

	_overwriteDatabase = false;
	
	dirty = false;

	haveLoadedDBModel = false;
	_CL_LOG << "lbDynamicApplication::lbDynamicApplication() called." LOG_

	REQUEST(getModuleInstance(), lb_I_String, lastExportedApp)
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)
	REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)

	REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	//REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProjectExport)

	XMIFileUMLProject->setData("");
	XMIFileUMLProjectExport->setData("");
	XSLFileImportSettings->setData("");
	XSLFileExportSettings->setData("");
	XSLFileSystemDatabase->setData("");
	XSLFileApplicationDatabase->setData("");

	*GeneralDBSchemaname = "public";

	*lastExportedApp = "";
}

lbDynamicApplication::~lbDynamicApplication() {
	_CL_LOG << "lbDynamicApplication::~lbDynamicApplication() called." LOG_
}
/*...e*/

lb_I_Unknown* LB_STDCALL lbDynamicApplication::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
}

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	// Register a dynamic formular creator

// Done while initialiation
//	disp->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, "getDynamicDBForm");

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbDynamicApplication::overwriteDatabase(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_overwriteDatabase = !_overwriteDatabase;

	//if (_overwriteDatabase) metaapp->toggleEvent("overwriteDatabase");
	
	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::executeQueryFromFile(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_InputStream, is)

	is = metaapp->askOpenFileReadStream("sql|txt");	

	if (is == NULL) return err;

	UAP(lb_I_Query, sampleQuery)
	UAP(lb_I_Database, sqldb)
	if (database == NULL) {
		char* dbbackend = metaapp->getApplicationDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, sqldb, "'database plugin'")
			_LOG << "lbDynamicApplication::initialize(): Using plugin database backend ..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, sqldb)
			_LOG << "lbDynamicApplication::initialize(): Using built in database backend ..." LOG_
		}

		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
		database->init();
	}

	char* DBName = strdup(appParams->getParameter("DBName", metaapp->getApplicationID())); 
	char* DBPass = strdup(appParams->getParameter("DBPass", metaapp->getApplicationID())); 
	char* DBUser = strdup(appParams->getParameter("DBUser", metaapp->getApplicationID()));
	
	if (sqldb->connect(DBName, DBName, DBUser, DBPass) == ERR_NONE) {
		UAP(lb_I_String, sql)
		UAP_REQUEST(getModuleInstance(), lb_I_String, sqlmod)
		sampleQuery = sqldb->getQuery(DBName, 0);
		is->open();
		sql = is->getAsString();
		*sqlmod = "--Skip rewrite\n";
		*sqlmod += sql->charrep();
		if (sampleQuery->query(sqlmod->charrep()) != ERR_NONE) {
			metaapp->msgBox("Error", "SQL query failed.");
			return err;
		}
	}

	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::editProperties(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, appname)

	metaapp->getApplicationName(&appname);

	// Guard, if this function is called accidently, but unintented.
	if (*appname == "lbDMF Manager") {
		// Build up a preferences object and pass it to the property view
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)

		// General parameters for this application
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolGeneral)

		// Project manager parameters
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueProject)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolProject)

		// XSL import definitions
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramUMLExport)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolXSL)


		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)

		parameter->setData("UML import settings");
		//--------------------------------------------
		/*
		 parameterXSL->setData("Ask for other XSL files");
		 boolXSL->setData(UseOtherXSLFile->getData());
		 paramXSL->setUAPBoolean(*&parameterXSL, *&boolXSL);
		 */
		parameterXSL->setData("XMI UML input file");
		fileXSL->setData(XMIFileUMLProject->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		parameterXSL->setData("XSL file for import settings");
		fileXSL->setData(XSLFileImportSettings->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		parameterXSL->setData("XSL file for system database");
		fileXSL->setData(XSLFileSystemDatabase->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		parameterXSL->setData("XSL file for application database");
		fileXSL->setData(XSLFileApplicationDatabase->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramXSL,
												  this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);

		param->setUAPParameter(*&parameter, *&paramXSL);

		parameter->setData("UML export settings");
		//--------------------------------------------
		/*
		 parameterXSL->setData("Ask for other XSL files");
		 boolXSL->setData(UseOtherXSLFile->getData());
		 paramXSL->setUAPBoolean(*&parameterXSL, *&boolXSL);
		 */
		parameterXSL->setData("XMI UML export file");
		fileXSL->setData(XMIFileUMLProjectExport->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		parameterXSL->setData("XSL file for export settings");
		fileXSL->setData(XSLFileExportSettings->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		parameterXSL->setData("XSL file for UML export");
		fileXSL->setData(XSLFileUMLExport->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramUMLExport,
												  this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);

		param->setUAPParameter(*&parameter, *&paramUMLExport);

		parameter->setData("Application Database settings");
		//--------------------------------------

		parameterGeneral->setData("Use plugin");
		boolGeneral->setData(UsePlugin->getData());
		paramGeneral->setUAPBoolean(*&parameterGeneral, *&boolGeneral);

		parameterGeneral->setData("DB plugin namespace");
		valueGeneral->setData(DatabaseSettingNamespace->charrep());
		paramGeneral->setUAPString(*&parameterGeneral, *&valueGeneral);

		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramGeneral,
													this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);

		param->setUAPParameter(*&parameter, *&paramGeneral);

		parameter->setData("lbDMF Manager Import Definitions");
		//--------------------------------------------------------

		parameterProject->setData("DB Name");
		valueProject->setData(UMLImportTargetDBName->charrep());
		paramProject->setUAPString(*&parameterProject, *&valueProject);

		parameterProject->setData("DB User");
		valueProject->setData(UMLImportTargetDBUser->charrep());
		paramProject->setUAPString(*&parameterProject, *&valueProject);

		parameterProject->setData("DB Password");
		valueProject->setData(UMLImportTargetDBPass->charrep());
		paramProject->setUAPString(*&parameterProject, *&valueProject);

		parameterProject->setData("DB Schemaname");
		valueProject->setData(GeneralDBSchemaname->charrep());
		paramProject->setUAPString(*&parameterProject, *&valueProject);

		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramProject,
													this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);

		param->setUAPParameter(*&parameter, *&paramProject);



		metaapp->showPropertyPanel(*&param);
	} else {
		// XSL import definitions
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramUMLExport)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)

		// Build up a preferences object and pass it to the property view
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)

		// General parameters for this application
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueGeneral)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolGeneral)

		// Project manager parameters
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterProject)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueProject)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolProject)


		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)

		parameter->setData("Application Database settings");

		parameterGeneral->setData("Use plugin");
		boolGeneral->setData(UsePlugin->getData());
		paramGeneral->setUAPBoolean(*&parameterGeneral, *&boolGeneral);

		parameterGeneral->setData("DB plugin namespace");
		valueGeneral->setData(DatabaseSettingNamespace->charrep());
		paramGeneral->setUAPString(*&parameterGeneral, *&valueGeneral);

		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramGeneral,
													this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);

		param->setUAPParameter(*&parameter, *&paramGeneral);

		parameter->setData("UML export settings");
		//--------------------------------------------
		/*
		 parameterXSL->setData("Ask for other XSL files");
		 boolXSL->setData(UseOtherXSLFile->getData());
		 paramXSL->setUAPBoolean(*&parameterXSL, *&boolXSL);
		 */
		parameterXSL->setData("XMI UML export file");
		fileXSL->setData(XMIFileUMLProjectExport->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);
		
		parameterXSL->setData("XSL file for export settings");
		fileXSL->setData(XSLFileExportSettings->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);
		
		parameterXSL->setData("XSL file for UML export");
		fileXSL->setData(XSLFileUMLExport->getData());
		paramUMLExport->setUAPFileLocation(*&parameterXSL, *&fileXSL);
		
		metaapp->registerPropertyChangeEventGroup(	parameter->charrep(), *&paramUMLExport,
												  this, (lbEvHandler) &lbDynamicApplication::OnPropertiesDataChange);
		
		param->setUAPParameter(*&parameter, *&paramUMLExport);
		
		metaapp->showPropertyPanel(*&param);
	}

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::setupSystemDatabase(lb_I_Unknown* uk) {
	metaapp->msgBox("Info", "Setup application repository now.");
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::OnPropertiesDataChange(lb_I_Unknown* uk) {
	_CL_LOG << "lbDynamicApplication::OnProjectDataChange() called." LOG_

	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)

	if (param != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)

		UAP(lb_I_KeyBase, key)

		name->setData("name");
		param->getUAPString(*&name, *&parameterName);

		name->setData("value");
		param->getUAPString(*&name, *&value);

		QI(parameterName, lb_I_KeyBase, key)

		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB Name") == 0) {
					*UMLImportTargetDBName = value->charrep();
		}

		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB User") == 0) {
					*UMLImportTargetDBUser = value->charrep();
		}

		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB Password") == 0) {
					*UMLImportTargetDBPass = value->charrep();
		}
		
		if (strcmp(key->charrep(), "UML import settingsXMI UML input file") == 0) {
			XMIFileUMLProject->setData(value->charrep());
		}
		
		if (strcmp(key->charrep(), "UML export settingsXMI UML export file") == 0) {
			XMIFileUMLProjectExport->setData(value->charrep());
		}
		
		if (strcmp(key->charrep(), "UML export settingsXSL file for UML export") == 0) {
			XSLFileUMLExport->setData(value->charrep());
		}

		// This is propably not usefull in the configuration ---------------------------------
		if (strcmp(key->charrep(), "Application Database settingsUse plugin") == 0) {
					value->toLower();
					if (strcmp(value->charrep(), "true") == 0) {
						UsePlugin->setData(true);
					} else {
						UsePlugin->setData(false);
					}
		}

		if (strcmp(key->charrep(), "Application Database settingsDB plugin namespace") == 0) {
					*DatabaseSettingNamespace = value->charrep();
		}
		//------------------------------------------------------------------------------------

		if (strcmp(key->charrep(), "lbDMF Manager Import DefinitionsDB Schemaname") == 0) {
					*GeneralDBSchemaname = value->charrep();
		}
/*
		if (strcmp(key->charrep(), "UML import settingsAsk for other XSL files") == 0) {
					value->toLower();
					if (strcmp(value->charrep(), "true") == 0) {
						UseOtherXSLFile->setData(true);
					} else {
						UseOtherXSLFile->setData(false);
					}
		}
*/
		if (strcmp(key->charrep(), "UML import settingsXSL file for import settings") == 0) {
			XSLFileImportSettings->setData(value->charrep());
		}

		if (strcmp(key->charrep(), "UML import settingsXSL file for system database") == 0) {
			XSLFileSystemDatabase->setData(value->charrep());
		}

		if (strcmp(key->charrep(), "UML import settingsXSL file for application database") == 0) {
			XSLFileApplicationDatabase->setData(value->charrep());
		}

		if (strcmp(key->charrep(), "UML export settingsXSL file for export settings") == 0) {
			XSLFileExportSettings->setData(value->charrep());
		}

		_LOG << "User has changed a property for dynamic application: " << key->charrep() << " = " << value->charrep() LOG_
	} else {
		_LOG << "ERROR: Could not decode parameter structure!" LOG_
	}


	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)

	if (document != NULL) {
		*paramname = "XSLFileUMLExport";
		document->setUAPFileLocation(*&paramname, *&XSLFileUMLExport);
		*paramname = "XSLFileImportSettings";
		document->setUAPFileLocation(*&paramname, *&XSLFileImportSettings);
		*paramname = "XSLFileExportSettings";
		document->setUAPFileLocation(*&paramname, *&XSLFileExportSettings);
		*paramname = "XSLFileSystemDatabase";
		document->setUAPFileLocation(*&paramname, *&XSLFileSystemDatabase);
		*paramname = "XSLFileApplicationDatabase";
		document->setUAPFileLocation(*&paramname, *&XSLFileApplicationDatabase);
		*paramname = "XMIFileUMLProject";
		document->setUAPFileLocation(*&paramname, *&XMIFileUMLProject);
		*paramname = "XMIFileUMLProjectExport";
		document->setUAPFileLocation(*&paramname, *&XMIFileUMLProjectExport);
		*paramname = "UMLImportDBName";
		document->setUAPString(*&paramname, *&UMLImportTargetDBName);
		*paramname = "UMLImportDBUser";
		document->setUAPString(*&paramname, *&UMLImportTargetDBUser);
		*paramname = "UMLImportDBPass";
		document->setUAPString(*&paramname, *&UMLImportTargetDBPass);
		*paramname = "GeneralDBSchemaname";
		document->setUAPString(*&paramname, *&GeneralDBSchemaname);
		*paramname = "DatabaseSettingNamespace";
		document->setUAPString(*&paramname, *&DatabaseSettingNamespace);

		saveDataToActiveDocument();
	}

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, temp_params)

	*paramname = "GeneralDBSchemaname";
	temp_params->setUAPString(*&paramname, *&GeneralDBSchemaname);
	*paramname = "UMLImportDBName";
	temp_params->setUAPString(*&paramname, *&UMLImportTargetDBName);
	*paramname = "UMLImportDBUser";
	temp_params->setUAPString(*&paramname, *&UMLImportTargetDBUser);
	*paramname = "UMLImportDBPass";
	temp_params->setUAPString(*&paramname, *&UMLImportTargetDBPass);
	*paramname = "DatabaseSettingNamespace";
	temp_params->setUAPString(*&paramname, *&DatabaseSettingNamespace);
	*paramname = "UsePlugin";
	temp_params->setUAPBoolean(*&paramname, *&UsePlugin);
	//*paramname = "UseOtherXSLFile";
	//temp_params->setUAPBoolean(*&paramname, *&UseOtherXSLFile);
	*paramname = "XSLFileImportSettings";
	temp_params->setUAPFileLocation(*&paramname, *&XSLFileImportSettings);
	*paramname = "XSLFileExportSettings";
	temp_params->setUAPFileLocation(*&paramname, *&XSLFileExportSettings);
	*paramname = "XSLFileSystemDatabase";
	temp_params->setUAPFileLocation(*&paramname, *&XSLFileSystemDatabase);
	*paramname = "XSLFileApplicationDatabase";
	temp_params->setUAPFileLocation(*&paramname, *&XSLFileApplicationDatabase);
	*paramname = "XMIFileUMLProject";
	temp_params->setUAPFileLocation(*&paramname, *&XMIFileUMLProject);
	*paramname = "XMIFileUMLProjectExport";
	temp_params->setUAPFileLocation(*&paramname, *&XMIFileUMLProjectExport);

	*paramname = "XSLFileUMLExport";
	temp_params->setUAPFileLocation(*&paramname, *&XSLFileUMLExport);

	metaapp->delPropertySet("DynamicAppDefaultSettings");
	metaapp->addPropertySet(*&temp_params, "DynamicAppDefaultSettings");

	//metaapp->setActiveDocument(*&document);

	return ERR_NONE;
}


lbErrCodes LB_STDCALL lbDynamicApplication::loadDatabaseSchema(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	bool isDBAvailable = false;
	UAP(lb_I_DatabaseOperation, fOpDB)

	_LOG << "lbDynamicApplication::loadDatabaseSchema() called." LOG_

	UAP(lb_I_Query, sampleQuery)

	if (database == NULL) {
		char* dbbackend = metaapp->getSystemDatabaseBackend();
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
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}

		database->init();
	}

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
		_LOG << "Warning: No system database available." LOG_
/// \todo Implement fallback to Sqlite3.
		metaapp->msgBox("Warning", "No system database available.");
	} else {
		pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
		if (pl != NULL)	ukPl = pl->getImplementation();
		if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpDB)
			isDBAvailable = fOpDB->begin("lbDMF", database.getPtr());
	}

	_CL_LOG << "Load database schema from target database ..." LOG_

	metaapp->setStatusText("Info", "Begin fetching schema ...");


	if (isDBAvailable) {
		AQUIRE_PLUGIN(lb_I_DBPrimaryKeys, Model, dbPrimaryKeys, "'primary keys'")
		AQUIRE_PLUGIN(lb_I_DBForeignKeys, Model, dbForeignKeys, "'foreign keys'")
		AQUIRE_PLUGIN(lb_I_DBColumns, Model, dbColumns, "'database columns'")
		AQUIRE_PLUGIN(lb_I_DBTables, Model, dbTables, "'database tables'")
		AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, formularfields, "'formular fields'")

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

		// Get the application ID, that would be stored inside the XML document
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
		*name = "SaveApplicationID";
		param->getUAPInteger(*&name, *&AppID);
		_LOG << "Have to save application ID = " << AppID->charrep() << ", database = " << appParams->getParameter("DBName", AppID->getData()) LOG_

		*lastExportedApp = AppID->charrep();

		if (strcmp(appParams->getParameter("DBName", AppID->getData()), "lbDMF") == 0) {
			// Is system database
			metaapp->setStatusText("Info", "Target database is system database ...");

			_LOG << "lbDynamicApplication::loadDatabaseSchema(lb_I_Unknown* uk) Using system database." LOG_
			formularfields->accept(*&fOpDB);
			metaapp->setStatusText("Info", "Reading primary keys ...");
			dbPrimaryKeys->accept(*&fOpDB);
			metaapp->setStatusText("Info", "Reading foreign keys ...");
			dbForeignKeys->accept(*&fOpDB);
			metaapp->setStatusText("Info", "Reading tables ...");
			dbTables->accept(*&fOpDB);
			metaapp->setStatusText("Info", "Reading columns ...");
			dbColumns->accept(*&fOpDB);
			fOpDB->end();
		} else {
			UAP(lb_I_Database, customDB)
			UAP(lb_I_Database, custom_formularfieldsDB)
			UAP(lb_I_DatabaseOperation, fOpCustomDB)
			UAP(lb_I_DatabaseOperation, fOpCustomformularfieldsDB)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbname)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbuser)
			UAP_REQUEST(getModuleInstance(), lb_I_String, dbpass)


			/************/
			char* dbbackend = metaapp->getApplicationDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, customDB, "'database plugin'")
				_LOG << "Using plugin database backend for loading database application schema..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, customDB)
				_LOG << "Using built in database backend for loading database application schema..." LOG_
			}

			if (customDB == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
			}

			customDB->init();
			/************/

			_LOG << "lbDynamicApplication::loadDatabaseSchema(lb_I_Unknown* uk) Using custom database." LOG_

			*dbname = appParams->getParameter("DBName", AppID->getData());
			*dbuser = appParams->getParameter("DBUser", AppID->getData());
			*dbpass = appParams->getParameter("DBPass", AppID->getData());

			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

			*msg = "Target database is application database (";
			*msg += dbname->charrep();
			*msg += ") ...";
			metaapp->setStatusText("Info", msg->charrep());

			if ((customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
				_LOG << "Fatal: No custom database available. Cannot read database model for custom application! (" << dbname->charrep() << ", " << dbuser->charrep() << ")" LOG_
/// \todo Implement fallback to Sqlite3.
				metaapp->msgBox("Fatal", "No custom database available. Cannot read database model for custom application!");
			} else {
				pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
				if (pl != NULL)	ukPl = pl->getImplementation();
				if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpCustomDB)

				pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
				if (pl != NULL)	ukPl = pl->getImplementation();
				if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpCustomformularfieldsDB)

				if (fOpCustomDB != NULL) {
					_LOG << "Reading custom configuration from " << dbname->charrep() << "." LOG_
					fOpCustomDB->begin(dbname->charrep(), customDB.getPtr());

					/************/
					char* dbbackend = metaapp->getSystemDatabaseBackend();
					if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, custom_formularfieldsDB, "'database plugin'")
						_LOG << "Using plugin database backend for loading database system schema..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, custom_formularfieldsDB)
						_LOG << "Using built in database backend for loading database system schema..." LOG_
					}

					if (custom_formularfieldsDB == NULL) {
						_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
						return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
					}

					if ((custom_formularfieldsDB != NULL) && (custom_formularfieldsDB->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
						_LOG << "Fatal: No system database available. Cannot read formular fields model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						metaapp->msgBox("Fatal", "No system database available. Cannot read formular fields model for custom application!");
						fOpCustomDB->end();
						return ERR_DB_CONNECT;
					}

					custom_formularfieldsDB->init();
					/************/

					if (fOpCustomformularfieldsDB != NULL) {
						fOpCustomformularfieldsDB->begin(dbname->charrep(), custom_formularfieldsDB.getPtr());
						formularfields->accept(*&fOpCustomformularfieldsDB);
					}
					metaapp->setStatusText("Info", "Reading primary keys ...");
					dbPrimaryKeys->accept(*&fOpCustomDB);
					metaapp->setStatusText("Info", "Reading foreign keys ...");
					dbForeignKeys->accept(*&fOpCustomDB);
					metaapp->setStatusText("Info", "Reading tables ...");
					dbTables->accept(*&fOpCustomDB);
					metaapp->setStatusText("Info", "Reading columns ...");
					dbColumns->accept(*&fOpCustomDB);

					fOpCustomDB->end();
				}
			}
		}

		metaapp->setStatusText("Info", "Storing fetched data into internal data model ...");

		if ((dbPrimaryKeys != NULL) &&
			(dbForeignKeys != NULL) &&
			(dbTables != NULL) &&
			(dbColumns != NULL)) {

			UAP(lb_I_Unknown, uk)

			param->setCloning(false);

			*name = "ApplicationData";
			param->getUAPContainer(*&name, *&document);

			metaapp->setStatusText("Info", "Storing formularfields ...");

			*name = "FormularFields";
			QI(formularfields, lb_I_Unknown, uk)
			// The container allows multiple entries by key.
			/// \todo Look at other places too.
			if (document->exists(&key) == 1) document->remove(&key);
			document->insert(&uk, &key);

			metaapp->setStatusText("Info", "Storing primary keys ...");

			*name = "DBPrimaryKeys";
			QI(dbPrimaryKeys, lb_I_Unknown, uk)
			if (document->exists(&key) == 1) document->remove(&key);
			document->insert(&uk, &key);

			metaapp->setStatusText("Info", "Storing foreign keys ...");

			*name = "DBForeignKeys";
			QI(dbForeignKeys, lb_I_Unknown, uk)
			if (document->exists(&key) == 1) document->remove(&key);
			document->insert(&uk, &key);

			metaapp->setStatusText("Info", "Storing tables ...");

			*name = "DBTables";
			QI(dbTables, lb_I_Unknown, uk)
			if (document->exists(&key) == 1) document->remove(&key);
			document->insert(&uk, &key);

			metaapp->setStatusText("Info", "Storing columns ...");

			*name = "DBColumns";
			QI(dbColumns, lb_I_Unknown, uk)
			if (document->exists(&key) == 1) document->remove(&key);
			document->insert(&uk, &key);

			*name = "ApplicationData";
			param->setUAPContainer(*&name, *&document);
		}

		haveLoadedDBModel = true;
	}
	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::exportApplicationConfigurationToUMLXMIDoc(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}

	metaapp->setStatusText("Info", "Exporting to UML (XMI) file ...");

	// Need to ask for the XMI file to be exported from XML

	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	UAP(lb_I_InputStream, exportfile)

	if (XMIFileUMLProjectExport->charrep() == NULL) {
		XMIFileUMLProjectExport->setData("");
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
	*ts = XMIFileUMLProjectExport->charrep();
	ts->trim();
	XMIFileUMLProjectExport->setData(ts->charrep());

	if (strcmp(XMIFileUMLProject->charrep(), "") == 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		exportfile = metaapp->askOpenFileReadStream("xmi");
		XMIFileUMLProject->setData((char*) exportfile->getFileName());
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolXSL)

		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)

		parameter->setData("UML export settings");
		//--------------------------------------------

		parameterXSL->setData("XMI UML export file");
		fileXSL->setData(XMIFileUMLProject->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		params->setUAPParameter(*&parameter, *&paramXSL);
		metaapp->showPropertyPanel(*&params);
	} else {
		REQUEST(getModuleInstance(), lb_I_OutputStream, exportfile)
		exportfile->setFileName(XMIFileUMLProjectExport->getData());
	}

	// Get the active document and set temporary a different storage handler (xmi import)
	UAP_REQUEST(manager.getPtr(), lb_I_String, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageNamespace)

	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)

	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);

		*tempStorageNamespace = "lbDynAppUMLImport";
		document->setUAPString(*&param, *&tempStorageNamespace);

		// The export needs the current application ID.
		AppID->setData(metaapp->getApplicationID());
		*param = "SaveApplicationID";
		document->setUAPInteger(*&param, *&AppID);
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)
		*overwrite = (_overwriteDatabase) ? "yes" : "no";
		*param = "overwriteDatabase";
		document->setUAPString(*&param, *&overwrite);
	}

	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");

	if (pl == NULL) {
		_LOG << "Error: Could not export dynamic application data. No plugin found." LOG_
		return ERR_FILE_WRITE;
	}

	if (pl != NULL) {
		ukPl = pl->getImplementation();
		UAP(lb_I_FileOperation, fOp)
		QI(ukPl, lb_I_FileOperation, fOp)

		if (fOp != NULL) {
			bool success = false;

			success = fOp->begin(exportfile.getPtr());

			if (success) {
				accept(*&fOp);
				fOp->end();
			} else {
				// No file found. Create one from database...
			}
		}
	}

	metaapp->setStatusText("Info", "");

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

	if (XMIFileUMLProject->charrep() == NULL) {
		XMIFileUMLProject->setData("");
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
	*ts = XMIFileUMLProject->charrep();
	ts->trim();
	XMIFileUMLProject->setData(ts->charrep());

	if (strcmp(XMIFileUMLProject->charrep(), "") == 0) {
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		importfile = metaapp->askOpenFileReadStream("xmi");
		XMIFileUMLProject->setData((char*) importfile->getFileName());
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_String, valueXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)
		UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolXSL)

		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)

		parameter->setData("lbDMF Manager Import Definitions");
		//--------------------------------------------

		parameterXSL->setData("XMI UML input file");
		fileXSL->setData(XMIFileUMLProject->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);

		params->setUAPParameter(*&parameter, *&paramXSL);
		metaapp->showPropertyPanel(*&params);
	} else {
		REQUEST(getModuleInstance(), lb_I_InputStream, importfile)
		importfile->setFileName(XMIFileUMLProject->getData());
	}


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
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)
		*overwrite = (_overwriteDatabase) ? "yes" : "no";
		*param = "overwriteDatabase";
		document->setUAPString(*&param, *&overwrite);
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
				dirty = true; /// \todo Detect if really made dirty.
			} else {
				// No file found. Create one from database...
			}
		}
	}
	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::exportApplicationToXMLBuffer(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)
	if (param == NULL) {
		metaapp->msgBox("Error", "Failed to export datamodel as XML into buffer.\n\nNo parameter of type lb_I_Parameter provided to store the result as memorybuffer parameter.\nThis is a software developer error.");
		return err;
	}

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)

	*name = "SaveApplicationID";
	document->getUAPInteger(*&name, *&AppID);
    _LOG << "Export application " << AppID->charrep() << " to XML buffer." LOG_

	if (dirty) {
		dirty = false;
		bool b = metaapp->usingApplicationDatabaseBackend();
		metaapp->useApplicationDatabaseBackend(true);
		load();
		metaapp->useApplicationDatabaseBackend(b);

    	ukDoc = metaapp->getActiveDocument();
		QI(ukDoc, lb_I_Parameter, document)
		
		// Restore important parameters. Passing parameters this way is not that good.
		document->setUAPInteger(*&name, *&AppID);
	}

	document->setCloning(false);

	if ((haveLoadedDBModel == false) || (strcmp(lastExportedApp->charrep(), AppID->charrep()) != 0)) {
		metaapp->setStatusText("Info", "Loading target database schema ...");
		loadDatabaseSchema(NULL);
		if (haveLoadedDBModel == false) {
			metaapp->msgBox("Error", "Failed to load target database schema.\n\nThis is required for XML export.");
			return err;
		}
	}

	metaapp->setStatusText("Info", "Exporting XML to memory buffer");

	UAP_REQUEST(manager.getPtr(), lb_I_OutputStream, exportfile)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)
	UAP_REQUEST(manager.getPtr(), lb_I_String, tempStorageNamespace)

	// Get the active document and set temporary a different storage handler (dax)

	if (document != NULL) {
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(getModuleInstance(), lb_I_Container, doc)
		doc->setCloning(false);
		*name = "StorageDelegateNamespace";
		document->getUAPString(*&name, *&StorageNamespace);

		*tempStorageNamespace = "lbDynAppXMLFormat";
		document->setUAPString(*&name, *&tempStorageNamespace);

		*name = "ApplicationData";
		document->getUAPContainer(*&name, *&doc);
		*name = "AppParams";
		QI(name, lb_I_KeyBase, key)
		uk = doc->getElement(&key);
		QI(uk, lb_I_ApplicationParameter, appParams)

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

				// Need to derive filename from given application name
				UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
				*filename = LogonApplication->charrep();
				*filename += ".dax"; // Dynamic application forms

				exportfile->writeToBuffer(true);

				// Only required if file is used after code generation
				//exportfile->setFileName(filename->charrep());

				success = fOp->begin(exportfile.getPtr());

				if (success) {
					accept(*&fOp);
					fOp->end();
				} else {
					// No file found. Create one from database...
				}

				UAP(lb_I_String, buffer)


				buffer = exportfile->getAsString();

				_LOG << "Have got XML memory file: " << buffer->charrep() LOG_
				
				*name = "memorybuffer";
				param->setUAPString(*&name, *&buffer);

				*name = "filename";
				param->setUAPString(*&name, *&filename);
			}
	}
	return err;
}

/*...sevent handlers\44\ that can be registered:0:*/
/// \todo Create a handler that writes the XML stuff in a predefined output stream.
lbErrCodes LB_STDCALL lbDynamicApplication::exportApplicationToXML(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	// Need to derive filename from given application name
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	*filename = LogonApplication->charrep();
	*filename += ".dax"; // Dynamic application forms

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}

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

		*param = "SaveApplicationID";
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
		AppID->setData(metaapp->getApplicationID());
		document->setUAPInteger(*&param, *&AppID);
	}

	if (haveLoadedDBModel == false) {
		metaapp->setStatusText("Info", "Loading target database schema ...");
		/** \todo Create an event for formulars that store actually selected entry.
		 * To be read here for desision what schema should be loaded.
		 */
		loadDatabaseSchema(NULL);
		if (haveLoadedDBModel == false) {
			metaapp->msgBox("Error", "Failed to load target database schema.\n\nThis is required for XML export.");
			return err;
		}
	}

	metaapp->setStatusText("Info", "Exporting to XML ...");

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

		if (forms == NULL) {
			metaapp->msgBox("Error", "Forms object not loaded.");
			return err;
		}

		typ->setData(forms->getTyp());

		*sql = "SELECT handlerfunctor, handlermodule, handlerinterface, namespace from formulartypen where namespace = '";
		*sql += "FixedDBForm_";
		*sql += forms->getName();
		*sql += "'";

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
								metaapp->setStatusText("Info", "Database form created. Ready.");
							} else {
								metaapp->setStatusText("Info", "Error: Database form was not loaded by the GUI !");
							}
						}
					} else {
						metaapp->setStatusText("Info", "Error: Unsupported interface !");
						// Unsupported
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
		char* dbbackend = metaapp->getSystemDatabaseBackend();
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
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
/// \todo Implement fallback to Sqlite3.
			metaapp->msgBox("Warning", "No system database available.");
			return ERR_DB_CONNECT;
		}
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

			*formName = forms->getName();

			if (*formName == "") {
				_LOG << "Error: Datamodel does not return formular name!" LOG_
			} else {
				_LOG << "GUI->createDBForm() with name '" << formName->charrep() << "' will be called." LOG_
			}

			dbForm = gui->createDBForm(	formName->charrep(),
							formParams->getParameter("query", forms->getFormularID()),
							DBName->charrep(),
							DBUser->charrep(),
							DBPass->charrep());

			if (dbForm != NULL) dbForm->show();
		} else {
			// Use old version with direct database queries. This could happen, if no plugin was found, no file was found and couldn't created.

			if(database == NULL) {
				char* dbbackend = metaapp->getSystemDatabaseBackend();
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
					return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
				}

				database->init();

				char* lbDMFPasswd = getenv("lbDMFPasswd");
				char* lbDMFUser   = getenv("lbDMFUser");

				if (!lbDMFUser) lbDMFUser = "dba";
				if (!lbDMFPasswd) lbDMFPasswd = "trainres";

				if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
/// \todo Implement fallback to Sqlite3.
					metaapp->msgBox("Warning", "No system database available.");
					return ERR_DB_CONNECT;
				}
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

				//*formName = forms->getName();
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

	_CL_LOG << "lbDynamicApplication::uninitialize() called." LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	// Need to derive filename from given application name
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	*filename = "";
#ifdef OSX
	lb_I_GUI* g = NULL;
	meta->getGUI(&g);
	if (g) {
		*filename += "./wxWrapper.app/Contents/Resources/";
	}
#endif
	*filename += LogonApplication->charrep();
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

	if (ukDoc != NULL) {
		QI(ukDoc, lb_I_Parameter, document)

		if (document != NULL) {
			*param = "StorageDelegateNamespace";
			document->getUAPString(*&param, *&StorageNamespace);

			*tempStorageNamespace = "lbDynAppInternalFormat";
			document->setUAPString(*&param, *&tempStorageNamespace);

			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_KeyBase, key)
			UAP_REQUEST(getModuleInstance(), lb_I_Container, ApplicationData)
			ApplicationData->setCloning(false);

			QI(name, lb_I_KeyBase, key)

			// Get the container that stores the application data
			*name = "ApplicationData";
			document->getUAPContainer(*&name, *&ApplicationData);

			// Store the current values into the container

			*name = "UMLImportTargetDBName";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(UMLImportTargetDBName, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "UMLImportTargetDBUser";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "UMLImportTargetDBPass";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "DatabaseSettingNamespace";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "UsePlugin";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(UsePlugin, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);


			*name = "XSLFileUMLExport";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XSLFileUMLExport, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "XSLFileImportSettings";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XSLFileImportSettings, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "XSLFileExportSettings";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XSLFileExportSettings, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "XSLFileSystemDatabase";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "XSLFileApplicationDatabase";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "XMIFileUMLProject";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XMIFileUMLProject, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);
			
			*name = "XMIFileUMLProjectExport";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);
			
			//*name = "UseOtherXSLFile";
			//if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			//QI(UseOtherXSLFile, lb_I_Unknown, uk)
			//ApplicationData->insert(&uk, &key);

			*name = "GeneralDBSchemaname";
			if (ApplicationData->exists(&key) == 1) ApplicationData->remove(&key);
			QI(GeneralDBSchemaname, lb_I_Unknown, uk)
			ApplicationData->insert(&uk, &key);

			*name = "ApplicationData";
			document->setUAPContainer(*&name, *&ApplicationData);
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
	}

	if (database == NULL) {
		char* dbbackend = metaapp->getSystemDatabaseBackend();
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
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}

	}

	database->close();

	_CL_LOG << "lbDynamicApplication::uninitialize() leaving." LOG_

	return ERR_NONE;
}
/*...e*/

//#define USE_OLD_INITIALIZE

lbErrCodes LB_STDCALL lbDynamicApplication::save() {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::load() {
    lbErrCodes err = ERR_NONE;
    int unused = -1;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	/* Before the application is loaded, it should be checked, if any database system is available.
	 * If not, at least a local Sqlite database should be setup with the use of the UML import feature.
	 */

	_LOG << "lbDynamicApplication::initialize('" << LogonUser->charrep() << "', '" << LogonApplication->charrep() << "') called." LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	// Need to derive filename from given application name
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	*filename = "";
#ifdef OSX
	lb_I_GUI* g = NULL;
	meta->getGUI(&g);
	if (g) {
		*filename += "./wxWrapper.app/Contents/Resources/";
	}
#endif
	*filename += LogonApplication->charrep();
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
		char* dbbackend = metaapp->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "lbDynamicApplication::initialize(): Using plugin database backend ..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "lbDynamicApplication::initialize(): Using built in database backend ..." LOG_
		}

		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
		database->init();
	}

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	if (!isFileAvailable || metaapp->getLoadFromDatabase()) {

		// File for current application is not available. Assume the MetaApp.mad file is too old.
		bool b = metaapp->getLoadFromDatabase();
		metaapp->setLoadFromDatabase(true);
		metaapp->load();
		metaapp->setLoadFromDatabase(b);
		metaapp->setApplicationName(LogonApplication->charrep());

		if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
/// \todo Implement fallback to Sqlite3 database.
			metaapp->msgBox("Error", "No system database available!");

// Not really reachable when module not loaded.

/*
			if (eman->resolveEvent("evtsetupSystemDatabase", unused) == ERR_EVENT_NOTREGISTERED) {
				eman->registerEvent("evtsetupSystemDatabase", unused);

				dispatcher->addEventHandlerFn(this,
											  (lbEvHandler) &lbDynamicApplication::setupSystemDatabase, "evtsetupSystemDatabase");

				metaapp->addMenuEntry(_trans("&File"), "Initially setup Application repository", "evtsetupSystemDatabase", "");
			}
*/
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
#ifndef USE_OLD_INITIALIZE
					UAP_REQUEST(manager.getPtr(), lb_I_Container, document)

					param->setCloning(false);
					document->setCloning(false);

					UAP(lb_I_Unknown, uk)
					UAP(lb_I_KeyBase, key)
					metaapp->setStatusText("Info", "Preload application data from file ...");

					*name = "StorageDelegateNamespace";
					*value = "lbDynAppInternalFormat";
					param->setUAPString(*&name, *&value);

					accept(*&fOp);

					loadDataFromActiveDocument();
#endif
#ifdef USE_OLD_INITIALIZE
					// System database is not available
					UAP(lb_I_Applications_Formulars, ApplicationFormulars)
					UAP(lb_I_Formulars, forms)
					UAP(lb_I_Formular_Fields, formularfields)
					UAP(lb_I_Column_Types, columntypes)
					UAP(lb_I_FormularParameter, formParams)
					UAP(lb_I_Formular_Actions, formActions)
					UAP(lb_I_Actions, appActions)
					UAP(lb_I_Action_Steps, appActionSteps)
					UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
					UAP(lb_I_Action_Parameters, appActionParameters)
					UAP(lb_I_ActionStep_Parameters, appActionStepParameters)
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
						AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, ApplicationFormulars, "'formular to application assoc'")
						AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, appActionStepTransitions, "'action step transitions'")
						AQUIRE_PLUGIN(lb_I_Action_Parameters, Model, appActionParameters, "'action parameters'")
						AQUIRE_PLUGIN(lb_I_ActionStep_Parameters, Model, appActionStepParameters, "'action step parameters'")


						metaapp->setStatusText("Info", "Preload application data from file ...");

						*name = "StorageDelegateNamespace";
						*value = "lbDynAppInternalFormat";
						param->setUAPString(*&name, *&value);

						reports->accept(*&fOp);
						reportparams->accept(*&fOp);
						reportelements->accept(*&fOp);
						reportelementtypes->accept(*&fOp);
						reporttextblocks->accept(*&fOp);

						ApplicationFormulars->accept(*&fOp);
						forms->accept(*&fOp);
						formularfields->accept(*&fOp);
						columntypes->accept(*&fOp);
						formActions->accept(*&fOp);
						formParams->accept(*&fOp);
						appParams->accept(*&fOp);
						appActions->accept(*&fOp);
						appActionTypes->accept(*&fOp);
						appActionSteps->accept(*&fOp);
						appActionStepTransitions->accept(*&fOp);
						appActionParameters->accept(*&fOp);
						appActionStepParameters->accept(*&fOp);
						fOp->end();
					} else {
						// FATAL: No system database and no file.
						metaapp->msgBox("Fatal", "No system database has been setup and no previously created file is available.");
						return ERR_NONE;
					}
#endif // USE_OLD_INITIALIZE
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
/// \todo Implement fallback to Sqlite3 database.
						_LOG << "Warning: No application database available. (DBName=" << DBName->charrep() << ", DBUser=" << DBUser->charrep() << ", ApplicationID=" << metaapp->getApplicationID() << ")" LOG_
						// This can lock the application in Mac OS X
						// Maybe due to the splash sscreen
						if (DBName->charrep() == NULL) 
							metaapp->msgBox("Error", "No application database available. DBName = NULL. Please check your application parameter definition.");
						else {
							UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
							*msg = "No application database available. DBName = '";
							*msg += DBName->charrep();
							*msg += "'. Please check your application parameter definition.";
							metaapp->msgBox("Error", msg->charrep());
						}
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
#ifdef USE_OLD_INITIALIZE
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
		AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, ApplicationFormulars, "'formular to application assoc'")
		AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, appActionStepTransitions, "'action step transitions'")
		AQUIRE_PLUGIN(lb_I_Action_Parameters, Model, appActionParameters, "'action parameters'")
		AQUIRE_PLUGIN(lb_I_ActionStep_Parameters, Model, appActionStepParameters, "'action step parameters'")
#endif
/*...e*/


		// Only this part is how to load the data. So here I have to set the correct handler for the load delegation routine.

		// Loading the application related data succeeded. Put these into a parameter object for reference.

		//UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
		//UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		//UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
		UAP(lb_I_KeyBase, key)
		QI(name, lb_I_KeyBase, key)

		param->setCloning(false);
		document->setCloning(false);

		*name = "StorageDelegateInterface";
		*value = "lb_I_Streamable";
		param->setUAPString(*&name, *&value);

#ifndef USE_OLD_INITIALIZE
		if (!DBOperation) {
			_LOG << "Load application data from file ..." LOG_
			metaapp->setStatusText("Info", "Load application data from file ...");

			*name = "StorageDelegateNamespace";
			*value = "lbDynAppInternalFormat";
			param->setUAPString(*&name, *&value);
			param++;
			metaapp->setActiveDocument(*&param);

			accept(*&fOp);

			loadDataFromActiveDocument();
		}
#endif
#ifdef USE_OLD_INITIALIZE
		if (!DBOperation &&
			(ApplicationFormulars != NULL) &&
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
			(appActionStepTransitions != NULL) &&
			(appActionParameters != NULL) &&
			(appActionStepParameters != NULL) &&
			(appActionTypes != NULL) &&
			(appParams != NULL)) {
			_LOG << "Load application data from file ..." LOG_
			metaapp->setStatusText("Info", "Load application data from file ...");

			*name = "StorageDelegateNamespace";
			*value = "lbDynAppInternalFormat";
			param->setUAPString(*&name, *&value);

			//accept(*&fOp);


			reports->accept(*&fOp);
			reportparams->accept(*&fOp);
			reportelements->accept(*&fOp);
			reportelementtypes->accept(*&fOp);
			reporttextblocks->accept(*&fOp);

			ApplicationFormulars->accept(*&fOp);
			forms->accept(*&fOp);
			formularfields->accept(*&fOp);
			columntypes->accept(*&fOp);
			formActions->accept(*&fOp);
			formParams->accept(*&fOp);
			appParams->accept(*&fOp);
			appActions->accept(*&fOp);
			appActionTypes->accept(*&fOp);
			appActionSteps->accept(*&fOp);
			appActionStepTransitions->accept(*&fOp);
			appActionParameters->accept(*&fOp);
			appActionStepParameters->accept(*&fOp);
		}
#endif
#ifndef USE_OLD_INITIALIZE
		if ((metaapp->getLoadFromDatabase() || !isFileAvailable) && DBOperation) {
			_LOG << "Load application data from database ..." LOG_
			metaapp->setStatusText("Info", "Load application data from database ...");

			*name = "StorageDelegateNamespace";
			*value = "lbDynAppInternalFormat";
			param->setUAPString(*&name, *&value);

			param++;
			metaapp->setActiveDocument(*&param);

			accept(*&fOpDB);

			loadDataFromActiveDocument();
		}
#endif
#ifdef USE_OLD_INITIALIZE
		if ((metaapp->getLoadFromDatabase() || !isFileAvailable) && DBOperation &&
			(ApplicationFormulars != NULL) &&
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
			(appActionStepTransitions != NULL) &&
			(appActionParameters != NULL) &&
			(appActionStepParameters != NULL) &&
			(appActionTypes != NULL) &&
			(appParams != NULL)) {
			_LOG << "Load application data from database ..." LOG_
			metaapp->setStatusText("Info", "Load application data from database ...");

			*name = "StorageDelegateNamespace";
			*value = "lbDynAppInternalFormat";
			param->setUAPString(*&name, *&value);

			//accept(*&fOpDB);


			reports->accept(*&fOpDB);
			reportparams->accept(*&fOpDB);
			reportelements->accept(*&fOpDB);
			reportelementtypes->accept(*&fOpDB);
			reporttextblocks->accept(*&fOpDB);

			ApplicationFormulars->accept(*&fOpDB);
			forms->accept(*&fOpDB);
			formularfields->accept(*&fOpDB);
			columntypes->accept(*&fOpDB);
			formActions->accept(*&fOpDB);
			formParams->accept(*&fOpDB);
			appParams->accept(*&fOpDB);
			appActions->accept(*&fOpDB);
			appActionTypes->accept(*&fOpDB);
			appActionSteps->accept(*&fOpDB);
			appActionStepTransitions->accept(*&fOpDB);
			appActionParameters->accept(*&fOpDB);
			appActionStepParameters->accept(*&fOpDB);
		}
#endif // USE_OLD_INITIALIZE
		if (!DBOperation) fOp->end();
		if (DBOperation) fOpDB->end();

#ifdef USE_OLD_INITIALIZE
		if ((forms != NULL) &&
			(ApplicationFormulars != NULL) &&
			(reports != NULL) &&
			(reportparams != NULL) &&
			(reportelements != NULL) &&
			(reportelementtypes != NULL) &&
			(reporttextblocks != NULL) &&
			(formularfields != NULL) &&
			(formParams != NULL) &&
			(appActions != NULL) &&
			(appActionSteps != NULL) &&
			(appActionStepTransitions != NULL) &&
			(appActionParameters != NULL) &&
			(appActionStepParameters != NULL) &&
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



			*name = "FormularApplications";
			QI(ApplicationFormulars, lb_I_Unknown, uk)
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
			
			*name = "appActionStepTransitions";
			QI(appActionStepTransitions, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "appActionParameters";
			QI(appActionParameters, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "appActionStepParameters";
			QI(appActionStepParameters, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
		}

		*name = "ApplicationData";
		param->setUAPContainer(*&name, *&document);

		param++;
		metaapp->setActiveDocument(*&param);
#endif
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

		_LOG << "Load the following application '" << appname->charrep() << "'." LOG_

		if (*appname == "lbDMF Manager") {

			// Only lbDMF Manager should enable import functionality, because this is logically the designer.

			plDynamicAppStorageUMLXMIImport = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", "lbDynAppUMLImport");
			if (plDynamicAppStorageUMLXMIImport != NULL) {
				ukPlDynamicAppStorageUMLXMIImport = plDynamicAppStorageUMLXMIImport->getImplementation();

				if (eman->resolveEvent("exportApplicationToXMLBuffer", unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent("exportApplicationToXMLBuffer", unused);

					dispatcher->addEventHandlerFn(this,
												  (lbEvHandler) &lbDynamicApplication::exportApplicationToXMLBuffer, "exportApplicationToXMLBuffer");

				}

				if (eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent("exportApplicationConfigurationToUMLXMIDoc", unused);

					dispatcher->addEventHandlerFn(this,
												  (lbEvHandler) &lbDynamicApplication::exportApplicationConfigurationToUMLXMIDoc, "exportApplicationConfigurationToUMLXMIDoc");

					metaapp->addMenuEntry(_trans("&File"), "export Application to UML (as XMI file)", "exportApplicationConfigurationToUMLXMIDoc", "");
				}

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

					UAP_REQUEST(getModuleInstance(), lb_I_String, param)
					UAP(lb_I_Unknown, ukDoc)
					UAP(lb_I_Parameter, document)
					ukDoc = metaapp->getActiveDocument();
					QI(ukDoc, lb_I_Parameter, document)

/*
					if (document != NULL) {
						*param = "UMLImportDBName";
						document->setUAPString(*&param, *&UMLImportTargetDBName);
						*param = "UMLImportDBUser";
						document->setUAPString(*&param, *&UMLImportTargetDBUser);
						*param = "UMLImportDBPass";
						document->setUAPString(*&param, *&UMLImportTargetDBPass);
					}
*/
					editProperties(NULL);
				}
			}
		} else {
			if (metaapp->isPropertyPaneLayoutLeft()) metaapp->showPropertyPanel();
			if (metaapp->isPropertyPaneLayoutFloating()) metaapp->showPropertyPanel();

			plDynamicAppStorageUMLXMIImport = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", "lbDynAppUMLImport");
			if (plDynamicAppStorageUMLXMIImport != NULL) {
				ukPlDynamicAppStorageUMLXMIImport = plDynamicAppStorageUMLXMIImport->getImplementation();
				
				if (eman->resolveEvent("exportApplicationToXMLBuffer", unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent("exportApplicationToXMLBuffer", unused);
						
					dispatcher->addEventHandlerFn(this,
												  (lbEvHandler) &lbDynamicApplication::exportApplicationToXMLBuffer, "exportApplicationToXMLBuffer");
				}
			}
			
			if (eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused) == ERR_EVENT_NOTREGISTERED) {
				eman->registerEvent("exportApplicationConfigurationToUMLXMIDoc", unused);

				dispatcher->addEventHandlerFn(this,
											  (lbEvHandler) &lbDynamicApplication::exportApplicationConfigurationToUMLXMIDoc, "exportApplicationConfigurationToUMLXMIDoc");

				metaapp->addMenuEntry(_trans("&File"), "export Application to UML (as XMI file)", "exportApplicationConfigurationToUMLXMIDoc", "");
			}
			editProperties(NULL);
		}
/*...e*/
	} else {
		// No file found. Create one from database...
	}

    return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::initialize(char* user, char* app) {
	_CL_LOG << "lbDynamicApplication::initialize(...) called." LOG_
	// To be implemented in a separate application module
	lbErrCodes err = ERR_NONE;
	int unused;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)

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

    load();

	_CL_LOG << "Begin setup menu ..." LOG_

	/*
	 Select all events, that are configured and register it.
	 */

	activateDBForms(user, app);

	UAP_REQUEST(getModuleInstance(), lb_I_String, editMenu)
	UAP_REQUEST(getModuleInstance(), lb_I_String, menuEntry)

	*editMenu = _trans("&Edit");
	*menuEntry = _trans("Set all forms back to dynamic");
	eman->registerEvent("resetCustomDBFormsToDynamic", unused);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::resetCustomDBFormsToDynamic, "resetCustomDBFormsToDynamic");
	metaapp->addMenuEntry(editMenu->charrep(), menuEntry->charrep(), "resetCustomDBFormsToDynamic", "");

	*editMenu = _trans("&Edit");
	*menuEntry = _trans("Execute SQL query");
	eman->registerEvent("executeQueryFromFile", unused);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::executeQueryFromFile, "executeQueryFromFile");
	metaapp->addMenuEntry(editMenu->charrep(), menuEntry->charrep(), "executeQueryFromFile", "");
	
	*editMenu = _trans("&Edit");
	*menuEntry = _trans("overwrite database while import");
	eman->registerEvent("overwriteDatabase", unused);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::overwriteDatabase, "overwriteDatabase");
	metaapp->addMenuEntryCheckable(editMenu->charrep(), menuEntry->charrep(), "overwriteDatabase", "");
	
	return ERR_NONE;
}

void LB_STDCALL lbDynamicApplication::saveDataToActiveDocument() {
    lbErrCodes err = ERR_NONE;
    UAP_REQUEST(getModuleInstance(), lb_I_String, name)
    UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

    UAP(lb_I_Parameter, param)
    UAP(lb_I_Unknown, uk)
    UAP(lb_I_KeyBase, key)
    QI(name, lb_I_KeyBase, key)

    document->setCloning(false);

    uk = metaapp->getActiveDocument();
    QI(uk, lb_I_Parameter, param)

    *name = "ApplicationData";
    param->getUAPContainer(*&name, *&document);


    *name = "UMLImportTargetDBName";
	QI(UMLImportTargetDBName, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "UMLImportTargetDBUser";
	QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "UMLImportTargetDBPass";
	QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "DatabaseSettingNamespace";
	QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
/*
    *name = "UsePlugin";
	QI(UsePlugin, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
*/
    *name = "UsePlugin";
	QI(UsePlugin, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
	_LOG << "Have UsePlugin switch from active document: " << UsePlugin->charrep() LOG_


    *name = "XSLFileUMLExport";
	QI(XSLFileUMLExport, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "XSLFileImportSettings";
	QI(XSLFileImportSettings, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "XSLFileExportSettings";
	QI(XSLFileExportSettings, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "XSLFileSystemDatabase";
	QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    *name = "XSLFileApplicationDatabase";
	QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);

    //*name = "UseOtherXSLFile";
	//QI(UseOtherXSLFile, lb_I_Unknown, uk)
	//if (document->exists(&key) == 1) document->remove(&key);
    //document->insert(&uk, &key);

    *name = "XMIFileUMLProject";
	QI(XMIFileUMLProject, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
	
    *name = "XMIFileUMLProjectExport";
	QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
	
    *name = "GeneralDBSchemaname";
	QI(GeneralDBSchemaname, lb_I_Unknown, uk)
	if (document->exists(&key) == 1) document->remove(&key);
    document->insert(&uk, &key);
}

void LB_STDCALL lbDynamicApplication::loadDataFromActiveDocument() {
    lbErrCodes err = ERR_NONE;
    UAP_REQUEST(getModuleInstance(), lb_I_String, name)
    UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

    UAP(lb_I_Parameter, param)
    UAP(lb_I_Unknown, uk)
    UAP(lb_I_KeyBase, key)
    QI(name, lb_I_KeyBase, key)

    document->setCloning(false);

    uk = metaapp->getActiveDocument();

	if (uk == NULL) {
		_LOG << "Error: Expected an 'active document' here!" LOG_
		return;
	}

    QI(uk, lb_I_Parameter, param)

    *name = "ApplicationData";
    param->getUAPContainer(*&name, *&document);

    *name = "AppParams";
    uk = document->getElement(&key);
    QI(uk, lb_I_ApplicationParameter, appParams)

    *name = "Formulars";
    uk = document->getElement(&key);
    QI(uk, lb_I_Formulars, forms)

    *name = "FormParams";
    uk = document->getElement(&key);
    QI(uk, lb_I_FormularParameter, formParams)

    *name = "FormularApplications";
    uk = document->getElement(&key);
    QI(uk, lb_I_Applications_Formulars, ApplicationFormulars)


	// Read out application settings

    *name = "UMLImportTargetDBName";
    uk = document->getElement(&key);
	UMLImportTargetDBName->setData(*&uk);

    *name = "UMLImportTargetDBUser";
    uk = document->getElement(&key);
	UMLImportTargetDBUser->setData(*&uk);

    *name = "UMLImportTargetDBPass";
    uk = document->getElement(&key);
	UMLImportTargetDBPass->setData(*&uk);

    *name = "DatabaseSettingNamespace";
    uk = document->getElement(&key);
	DatabaseSettingNamespace->setData(*&uk);

    *name = "UsePlugin";
    uk = document->getElement(&key);
	UsePlugin->setData(*&uk);
	_LOG << "Have UsePlugin switch from active document: " << UsePlugin->charrep() LOG_


    *name = "XSLFileUMLExport";
    uk = document->getElement(&key);
	XSLFileUMLExport->setData(*&uk);

    *name = "XSLFileImportSettings";
    uk = document->getElement(&key);
	XSLFileImportSettings->setData(*&uk);

    *name = "XSLFileExportSettings";
    uk = document->getElement(&key);
	XSLFileExportSettings->setData(*&uk);

    *name = "XSLFileSystemDatabase";
    uk = document->getElement(&key);
	XSLFileSystemDatabase->setData(*&uk);

    *name = "XSLFileApplicationDatabase";
    uk = document->getElement(&key);
	XSLFileApplicationDatabase->setData(*&uk);

    //*name = "UseOtherXSLFile";
    //uk = document->getElement(&key);
	//UseOtherXSLFile->setData(*&uk);

    *name = "XMIFileUMLProject";
    uk = document->getElement(&key);
	XMIFileUMLProject->setData(*&uk);
	
    *name = "XMIFileUMLProjectExport";
    uk = document->getElement(&key);
	XMIFileUMLProjectExport->setData(*&uk);
	
    *name = "GeneralDBSchemaname";
    uk = document->getElement(&key);
	if (uk != NULL) GeneralDBSchemaname->setData(*&uk);


	// UML import routines currently rely on this.

	*name = "XSLFileUMLExport";
	param->setUAPFileLocation(*&name, *&XSLFileUMLExport);
	*name = "XSLFileImportSettings";
	param->setUAPFileLocation(*&name, *&XSLFileImportSettings);
	*name = "XSLFileExportSettings";
	param->setUAPFileLocation(*&name, *&XSLFileExportSettings);
	*name = "XSLFileSystemDatabase";
	param->setUAPFileLocation(*&name, *&XSLFileSystemDatabase);
	*name = "XSLFileApplicationDatabase";
	param->setUAPFileLocation(*&name, *&XSLFileApplicationDatabase);
	*name = "XMIFileUMLProject";
	param->setUAPFileLocation(*&name, *&XMIFileUMLProject);
	*name = "XMIFileUMLProjectExport";
	param->setUAPFileLocation(*&name, *&XMIFileUMLProjectExport);
	*name = "UMLImportDBName";
	param->setUAPString(*&name, *&UMLImportTargetDBName);
	*name = "UMLImportDBUser";
	param->setUAPString(*&name, *&UMLImportTargetDBUser);
	*name = "UMLImportDBPass";
	param->setUAPString(*&name, *&UMLImportTargetDBPass);

	*name = "GeneralDBSchemaname";
	param->setUAPString(*&name, *&GeneralDBSchemaname);

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, temp_params)

	*name = "XSLFileUMLExport";
	temp_params->setUAPFileLocation(*&name, *&XSLFileUMLExport);
	*name = "UMLImportDBName";
	temp_params->setUAPString(*&name, *&UMLImportTargetDBName);
	*name = "UMLImportDBUser";
	temp_params->setUAPString(*&name, *&UMLImportTargetDBUser);
	*name = "UMLImportDBPass";
	temp_params->setUAPString(*&name, *&UMLImportTargetDBPass);
	*name = "DatabaseSettingNamespace";
	temp_params->setUAPString(*&name, *&DatabaseSettingNamespace);
	*name = "UsePlugin";
	temp_params->setUAPBoolean(*&name, *&UsePlugin);
	//*name = "UseOtherXSLFile";
	//temp_params->setUAPBoolean(*&name, *&UseOtherXSLFile);
	*name = "XSLFileImportSettings";
	temp_params->setUAPFileLocation(*&name, *&XSLFileImportSettings);
	*name = "XSLFileExportSettings";
	temp_params->setUAPFileLocation(*&name, *&XSLFileExportSettings);
	*name = "XSLFileSystemDatabase";
	temp_params->setUAPFileLocation(*&name, *&XSLFileSystemDatabase);
	*name = "XSLFileApplicationDatabase";
	temp_params->setUAPFileLocation(*&name, *&XSLFileApplicationDatabase);
	*name = "XMIFileUMLProject";
	temp_params->setUAPFileLocation(*&name, *&XMIFileUMLProject);
	*name = "XMIFileUMLProjectExport";
	temp_params->setUAPFileLocation(*&name, *&XMIFileUMLProjectExport);

	*name = "GeneralDBSchemaname";
	temp_params->setUAPString(*&name, *&GeneralDBSchemaname);


	metaapp->addPropertySet(*&temp_params, "DynamicAppDefaultSettings");

    if (forms == NULL) _LOG << "Error: forms is NULL." LOG_
}

void LB_STDCALL lbDynamicApplication::activateDBForms(char* user, char* app) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	_LOG << "Load application formulars of '" << app << "' with ID = '" << meta->getApplicationID() << "' for user '" << user << "'." LOG_

	if ((forms != NULL) && (ApplicationFormulars != NULL)) {
		UAP_REQUEST(getModuleInstance(), lb_I_Long, AppID)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, AppIDComp)
		int unused;
		bool toolbaradded = false;
		AppID->setData(meta->getApplicationID());

		_LOG << "Load the formulars by document ..." LOG_

		char* ed = strdup(_trans("&Edit"));
		char* menu = strdup(_trans(app));
		metaapp->addMenuBar(menu, ed);
		free(ed);
		free(menu);

		ApplicationFormulars->finishRelationIteration();
		while (ApplicationFormulars->hasMoreRelations()) {
			ApplicationFormulars->setNextRelation();
			AppIDComp->setData(ApplicationFormulars->getApplicationID());

			_LOG << "Check formular ID = '" << ApplicationFormulars->getFormularID() << "' and their application ID = '" << ApplicationFormulars->getApplicationID() << "'." LOG_

			if (AppIDComp->equals(*&AppID)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, EventName)
				UAP_REQUEST(getModuleInstance(), lb_I_String, MenuName)
				UAP_REQUEST(getModuleInstance(), lb_I_String, ToolBarImage)
				UAP_REQUEST(getModuleInstance(), lb_I_Long, Typ)

				long FormID = ApplicationFormulars->getFormularID();
				forms->selectFormular(FormID);

				*EventName = forms->getEventName();
				*MenuName = forms->getMenuName();
				*ToolBarImage = forms->getToolbarImage();
				Typ->setData(forms->getTyp());

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
			}
		}
		ApplicationFormulars->finishRelationIteration();
	} else {
		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		UAP(lb_I_Query, sampleQuery)
		bool toolbaradded = false;
		int unused;

		_LOG << "Load the formulars by database access (fallback) ..." LOG_

		if (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			meta->msgBox("Error", "Failed to connect to required system database. (No local file available)");
			_LOG << "Error: Failed to get a connection to the system database." LOG_
			return;
		}

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

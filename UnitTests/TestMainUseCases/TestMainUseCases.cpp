#include "../MiniCppUnit/MiniCppUnit.hxx"

#include <lbConfigHook.h>
#include <signal.h>

#define DONT_USE_LBDMF_EXCEPTIONS

#ifdef WINDOWS
#define LOGFILE "\\myLog.log"
#endif

#ifdef LINUX
#define LOGFILE "/myLog.log"
#endif

#include <UIWrapper.h>

class TestMainUseCases : public TestFixture<TestMainUseCases>
{
public:
	TEST_FIXTURE( TestMainUseCases )
	{
		#ifdef WINDOWS
		setLogDirectory(".\\custom_logdir");
		#endif
		#ifdef LINUX
		setLogDirectory("./custom_logdir");
		#endif

		//TEST_CASE(test_Delegated_Action_lbDMFXslt_stopping_because_not_LoggedIn)
		
		//TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting)
		//TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting_with_badxsl)
		//TEST_CASE(test_Delegated_Action_lbDMFXslt_import_SecondStageUMLModel)
		
		//TEST_CASE(test_Delegated_Action_lbDMFXslt_import_InitialUMLModel)

		// require a new functionality to reload applications. This is because each test  runs their own application instance.
		
		TEST_CASE(test_Reload_Different_Application)
		
		TEST_CASE(test_Delegated_Action_lbDMFXslt_reimport_ModifiedInitialUMLModel)
		TEST_CASE(test_Delegated_Action_lbDMFXslt_export_InitialModelAsXMI2)
		
/*
		TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting_failure)
		TEST_CASE(test_Delegated_Action_lbWriteStringToFile)
		TEST_CASE(test_Delegated_Action_lbReadTextFileToString)
		TEST_CASE(test_Delegated_Action_lbGetIdForFormValue)
		TEST_CASE(test_Delegated_Action_lbXSLTTransformer)
*/
	}

	void test_Delegated_Action_lbDMFXslt_import_SecondStageUMLModel( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_import_SecondStageUMLModel");
	
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSettingsFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSystemFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslApplicationFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XmiFile)
		
		*XslSystemFile = getenv("DEVROOT");
		*XmiFile = getenv("DEVROOT");
		*XslSettingsFile = getenv("DEVROOT");
		
		ASSERT_EQUALS(true, XslSystemFile != NULL)
		ASSERT_EQUALS(true, XslSystemFile->charrep() != NULL)
		
		*XslSystemFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\importUML-SystemDB.xsl";
		*XslApplicationFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\importUML-ApplicationDB.xsl";
		*XslSettingsFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\XMISettings.xmi";
		*XmiFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\SecondStageModels\\lbDMF Manager.xmi";

		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		disp->setEventManager(eman.getPtr());

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");
		
		ASSERT_EQUALS(true, action != NULL)
		
		PM->initialize();
		PM->runInstallers();

		// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", true);

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");

		meta->fireEvent("writeXMISettings");
		meta->firePropertyChangeEvent("UML import settingsSystem database backend type", "Sqlite");
		meta->firePropertyChangeEvent("UML import settingsApplication database backend type", "Sqlite");

		#ifdef WINDOWS
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", XslSystemFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", XslApplicationFile->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", XslSystemFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", XslApplicationFile->charrep());
		#endif
		
		int unused;
		
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("importUMLXMIDocIntoApplication", unused))

		setLogActivated(true);
		meta->fireEvent("importUMLXMIDocIntoApplication");
		setLogActivated(false);
	}

	void ChangeProperty(const char* _name, const char* _value)
	{
        lbErrCodes err = ERR_NONE;
		
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

        // Get name of changed property
        const char* PropertyName = _name;

        const char* PropValue = _value;

        UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
        UAP_REQUEST(getModuleInstance(), lb_I_String, name)
        UAP_REQUEST(getModuleInstance(), lb_I_String, value)
        UAP_REQUEST(getModuleInstance(), lb_I_Integer, evId)

        int PropertyEvent;

        eman->resolveEvent(PropertyName, PropertyEvent);

        name->setData("eventId");
        evId->setData(PropertyEvent);
        param->setUAPInteger(*&name, *&evId);

        name->setData("value");
        value->setData(PropValue);
        param->setUAPString(*&name, *&value);

        name->setData("name");
        value->setData(PropertyName);
        param->setUAPString(*&name, *&value);

        UAP(lb_I_Unknown, uk)
        QI(param, lb_I_Unknown, uk)

        UAP_REQUEST(getModuleInstance(), lb_I_String, result)
        UAP(lb_I_Unknown, uk_result)
        QI(result, lb_I_Unknown, uk_result)

		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		dispatcher->setEventManager(eman.getPtr());

        dispatcher->dispatch(PropertyEvent, uk.getPtr(), &uk_result);
	}
	
	void import_Initial_TestModel(lb_I_SimulatedApplication* UI, const char* modelFile, const char* dbname) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSettingsFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSystemFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslApplicationFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XmiFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, CRUISECONTROL)
		
		
		*CRUISECONTROL = getenv("CRUISECONTROL");
		
		*XslSystemFile = getenv("DEVROOT");
		*XslApplicationFile = getenv("DEVROOT");
		*XmiFile = getenv("DEVROOT");
		*XslSettingsFile = getenv("DEVROOT");
		
		ASSERT_EQUALS(true, XslSystemFile != NULL)
		ASSERT_EQUALS(true, XslSystemFile->charrep() != NULL)
		
		if (*CRUISECONTROL == "yes")
		{
// Checked out stuff is directly in workspace directory (without /Projects/CPP)
#ifdef WINDOWS		
		*XslSystemFile += "\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1_2_2_lbDMFSQLScript.xsl";
		*XslApplicationFile += "\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1.2_2SQLScript.xsl";
		*XslSettingsFile += "\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\XMISettings.xsl";
		*XmiFile += "\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\InitialModels\\";
#endif

#ifndef WINDOWS		
		*XslSystemFile += "/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/xmi1_2_2_lbDMFSQLScript.xsl";
		*XslApplicationFile += "/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/xmi1.2_2SQLScript.xsl";
		*XslSettingsFile += "/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/XMISettings.xsl";
		*XmiFile += "/AppDevelopmentDemo/DynamicApp/UMLSamples/InitialModels/";
#endif
		}
		else
		{
#ifdef WINDOWS		
		*XslSystemFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1_2_2_lbDMFSQLScript.xsl";
		*XslApplicationFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1.2_2SQLScript.xsl";
		*XslSettingsFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\XMISettings.xsl";
		*XmiFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\InitialModels\\";
#endif

#ifndef WINDOWS		
		*XslSystemFile += "/Projects/CPP/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/xmi1_2_2_lbDMFSQLScript.xsl";
		*XslApplicationFile += "/Projects/CPP/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/xmi1.2_2SQLScript.xsl";
		*XslSettingsFile += "/Projects/CPP/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/XMISettings.xsl";
		*XmiFile += "/Projects/CPP/AppDevelopmentDemo/DynamicApp/UMLSamples/InitialModels/";
#endif
		}

		*XmiFile += modelFile;

		ASSERT_EQUALS(true, FileExists(XmiFile->charrep()))

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		disp->setEventManager(eman.getPtr());

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");
		
		ASSERT_EQUALS(true, action != NULL)
		
		meta->firePropertyChangeEvent("UML import settingsSystem database backend type", "Sqlite");
		meta->firePropertyChangeEvent("UML import settingsApplication database backend type", "Sqlite");
		
		#ifdef WINDOWS
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", XslSystemFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", XslApplicationFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXMI UML input file", XmiFile->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", XslSystemFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", XslApplicationFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXMI UML input file", XmiFile->charrep());
		#endif
		
		int unused;
		
		ChangeProperty("Application Database settingsDB Name", dbname);

		
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("importUMLXMIDocIntoApplication", unused))

		meta->fireEvent("importUMLXMIDocIntoApplication");
	}
	
	void export_XMI2_Model(lb_I_SimulatedApplication* UI, const char* modelFile)
	{
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSettingsFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslExportFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XmiFile)
		
		*XslSettingsFile = getenv("DEVROOT");
		*XslExportFile = getenv("DEVROOT");
		//*XmiFile = getenv("DEVROOT");
	
		*XslSettingsFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\DMFToXMI\\XMISettings.xsl";
		*XslExportFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\DMFToXMI\\gen_DMFToXMI.xsl";

		//*XmiFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\InitialModels\\";
		*XmiFile = modelFile;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		disp->setEventManager(eman.getPtr());

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");
		
		ASSERT_EQUALS(true, action != NULL)
		
		//meta->firePropertyChangeEvent("UML import settingsSystem database backend type", "Sqlite");
		//meta->firePropertyChangeEvent("UML import settingsApplication database backend type", "Sqlite");
		
		#ifdef WINDOWS
		meta->firePropertyChangeEvent("UML export settingsXMI UML export file", XmiFile->charrep());
		meta->firePropertyChangeEvent("UML export settingsXSL file for export settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML export settingsXSL file for UML export", XslExportFile->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML export settingsXMI UML export file", XmiFile->charrep());
		meta->firePropertyChangeEvent("UML export settingsXSL file for export settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML export settingsXSL file for UML export", XslExportFile->charrep());
		#endif
		
		int unused;
		
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused))

		meta->fireEvent("exportApplicationConfigurationToUMLXMIDoc");
	}
	
	lbErrCodes FireEvent(const char* name)
	{
		lbErrCodes err = ERR_NONE;
		int eventID = -1;
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, param)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

		eman->resolveEvent((const char*) name, eventID);
		dispatcher->setEventManager(eman.getPtr());

		param->setData(eventID);

		UAP(lb_I_Unknown, uk)
		QI(param, lb_I_Unknown, uk)

		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		UAP(lb_I_Unknown, uk_result)
		QI(result, lb_I_Unknown, uk_result)

		return dispatcher->dispatch(eventID, uk.getPtr(), &uk_result);
	}
	
	void test_Reload_Different_Application( void )
	{
		puts("test_Reload_Different_Application");

		remove("CDKatalog.db3");
		remove("CRM.db3");
		remove("lbDMF.db3");
		remove("lbDMF Manager.daf");
		remove("MetaApp.mad");

		ASSERT_EQUALS(false, FileExists("CDKatalog.db3"))
		
		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		// Answer the ODBC failure question with yes (Sqlite instead)
		myUIWrapper->addAnswer("yes", true);

		puts("Initialize plugin system");
		PM->initialize();
		puts("Run plugin installers");
		PM->runInstallers();

		// Be sure to not autoload
		puts("Load meta application");
		meta->load();
		meta->setAutoload(false);
		puts("Initialize meta application");
		meta->initialize("user", "lbDMF Manager");

		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		puts("Load application lbDMF Manager");
		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");
		
		puts("Export application model to UML XMI file");
		ASSERT_EQUALS(ERR_NONE, FireEvent("exportApplicationConfigurationToUMLXMIDoc"))

		puts("Unload application");
		meta->unloadApplication();
	
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

		int unused;

		// The registered events must also be unregistered.
		ASSERT_EQUALS(ERR_EVENT_NOTREGISTERED, eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused))
		ASSERT_EQUALS(ERR_EVENT_NOTREGISTERED, eman->resolveEvent("exportApplicationToXMLBuffer", unused))
		ASSERT_EQUALS(ERR_EVENT_NOTREGISTERED, eman->resolveEvent("importUMLXMIDocIntoApplication", unused))

		puts("Export application model to UML XMI file");
		ASSERT_EQUALS(ERR_DISPATCH_FAILS, FireEvent("exportApplicationConfigurationToUMLXMIDoc"))
		
		puts("Export application to buffer");
		ASSERT_EQUALS(ERR_DISPATCH_FAILS, FireEvent("exportApplicationToXMLBuffer"))

		puts("Import CDKatalog");
		ASSERT_EQUALS(ERR_DISPATCH_FAILS, FireEvent("importUMLXMIDocIntoApplication"))

		puts("Load CDKatalog");
		meta->loadApplication("user", "CDKatalog");

		meta->unloadApplication();
}
	
	/* This test tries to verify adding a column and then removing another column in a table.
	 * First the target database is validated and then, not yet, the application definition tables will be validated.
	 */
	void test_Delegated_Action_lbDMFXslt_reimport_ModifiedInitialUMLModel( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_reimport_ModifiedInitialUMLModel");

		const char* dbname = "CDKatalog";
		
		remove("CDKatalog.db3");
		remove("CRM.db3");
		remove("lbDMF.db3");
		remove("lbDMF Manager.daf");
		remove("MetaApp.mad");

		ASSERT_EQUALS(false, FileExists("CDKatalog.db3"))

		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		PM->initialize();
		PM->runInstallers();
	

			// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		//setLogActivated(true);
		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");
		//setLogActivated(false);

	
		ChangeProperty("Application Database settingsDB Name", dbname);
		ChangeProperty("UML import settingsSystem database backend type", "Sqlite");
		ChangeProperty("UML import settingsApplication database backend type", "Sqlite");

		meta->fireEvent("writeXMISettings");

		puts("Import No:1");

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", false);

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", false);

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", true);

		UAP(lb_I_Database, db)
        AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, "DatabaseLayerGateway", db, "'database plugin'")
		ASSERT_EQUALS( true, db.getPtr() != NULL );
		ASSERT_EQUALS( ERR_NONE, db->connect(dbname, dbname, "dba", "trainres"));

		import_Initial_TestModel(*&myUIWrapper, "CDKatalogStartTest.xmi", dbname);

		// These tests will fail at least on Linux. To be investigated later.
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "CREATE TABLE SQLITETEST (col1 int PRIMARY KEY, col2 DATETIME, col3 text)"))
		ASSERT_EQUALS(ERR_DB_NODATA, CheckBySQLQuery(*&db, dbname, "INSERT INTO SQLITETEST (col2, col3) values(date('now'), 'Test')"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "SELECT * FROM SQLITETEST"))

		// Table must exist
		ASSERT_EQUALS(ERR_DB_NODATA, CheckBySQLQuery(*&db, dbname, "select * from 'CD'"))
		
		// Test fails because metainformation could not be gathered. This is because aggregated columns have no associated columns :-)
		ASSERT_EQUALS(ERR_DB_QUERYFAILED, CheckBySQLQuery(*&db, dbname, "select 'Titel', 'Laenge', 'ReleaseDatum' from 'CD'"))
		
		// Missing column ReleaseDatum
		ASSERT_EQUALS(ERR_DB_NODATA, CheckBySQLQuery(*&db, dbname, "insert into 'CD' ('Titel', 'Laenge', 'ReleaseDatum') values ('Titel', 0, date('now'))"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select * from 'CD'"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select Titel, Laenge, ReleaseDatum from 'CD'"))
		
		ASSERT_EQUALS(true, CheckBySQLQuery(*&db, "lbDMF", "SELECT parametervalue from formular_parameters where formularid = (select id from formulare where name = 'CD')", 1, 1, 
		"select \"Titel\", \"Laenge\", \"ReleaseDatum\", \"Track\"  from \"CD\" order by \"ID\""))

		meta->fireEvent("overwriteDatabase");
		
		puts("Import No:2");

		import_Initial_TestModel(*&myUIWrapper, "CDKatalogAddedDescription.xmi", dbname);

		ASSERT_EQUALS(ERR_DB_NODATA, CheckBySQLQuery(*&db, dbname, "insert into 'CD' ('Titel', 'Laenge') values ('Titel', 0)"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select * from 'CD'"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select Titel, Laenge, ReleaseDatum, Description from 'CD'"))
		
		ASSERT_EQUALS(true, CheckBySQLQuery(*&db, "lbDMF", "SELECT parametervalue from formular_parameters where formularid = (select id from formulare where name = 'CD')", 1, 1, 
		"select \"Titel\", \"Laenge\", \"ReleaseDatum\", \"Track\" , \"Description\" from \"CD\" order by \"ID\""))

		puts("Import No:3");

		// Uncomment to gather logs (with generated SQL sqripts and other logs)
		//setLogActivated(true);
		import_Initial_TestModel(*&myUIWrapper, "CDKatalogThenRemovedReleaseDate.xmi", dbname);
		//setLogActivated(false);

		ASSERT_EQUALS(ERR_DB_NODATA, CheckBySQLQuery(*&db, dbname, "insert into 'CD' ('Titel', 'Laenge') values ('Titel', 0)"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select * from 'CD'"))

		// Check that ReleaseDatum is failing, thus no more present
		ASSERT_EQUALS(ERR_DB_QUERYFAILED, CheckBySQLQuery(*&db, dbname, "select Titel, Laenge, ReleaseDatum, Description from 'CD'"))
		ASSERT_EQUALS(ERR_NONE, CheckBySQLQuery(*&db, dbname, "select Titel, Laenge, Description from 'CD'"))

		UAP(lb_I_Database, db1)
		AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, "DatabaseLayerGateway", db1, "'database plugin'")

		// Ensure that the SQL query has really changed to the last imported definition
		
		ASSERT_EQUALS(true, CheckBySQLQuery(*&db, "lbDMF", "SELECT parametervalue from formular_parameters where formularid = (select id from formulare where name = 'CD')", 1, 1, 
		"select \"Titel\", \"Laenge\", \"Track\" , \"Description\" from \"CD\" order by \"ID\""))
		
		// Export the last application model into a XML file
		meta->fireEvent("evtExportApplicationToXML");
		
		meta->unloadApplication();
	}
	
	void test_Delegated_Action_lbDMFXslt_export_InitialModelAsXMI2( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_export_InitialModelAsXMI2");

		const char* dbname = "CDKatalog";

		remove("CDKatalog.db3");
		remove("CRM.db3");
		remove("lbDMF.db3");
		remove("lbDMF Manager.daf");
		remove("MetaApp.mad");
		remove("CDKatalogStartTest_XMI2.xmi");

		ASSERT_EQUALS(false, FileExists("CDKatalog.db3"))

		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

		PM->initialize();
		PM->runInstallers();
	

			// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		// Application behaviour saves the state for overwriteDatabase. Thus reseting it here is required.
		meta->delPropertySet("CodeGenMenuSettings");
		
		//setLogActivated(true);
		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");
		//setLogActivated(false);

	
		ChangeProperty("Application Database settingsDB Name", dbname);
		ChangeProperty("UML import settingsSystem database backend type", "Sqlite");
		ChangeProperty("UML import settingsApplication database backend type", "Sqlite");

		meta->fireEvent("writeXMISettings");

		puts("Import No:1");

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", true);

		UAP(lb_I_Database, db)
        AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, "DatabaseLayerGateway", db, "'database plugin'")
		ASSERT_EQUALS( true, db.getPtr() != NULL );
		ASSERT_EQUALS( ERR_NONE, db->connect(dbname, dbname, "dba", "trainres"));

		// Why was here a true if it were deleted?
		ASSERT_EQUALS(false, FileExists("CDKatalog.db3"))
				
		int unused;
		int unused1;
		
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused))
		
		import_Initial_TestModel(*&myUIWrapper, "CDKatalogStartTest.xmi", dbname);

		meta->unloadApplication();
		meta->uninitialize();
		meta->load();
		meta->setAutoload(false);

		ASSERT_EQUALS(ERR_EVENT_NOTREGISTERED, eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused))
		
		meta->initialize("user", dbname);

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))
	
		meta->loadApplication("user", dbname);
		
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("exportApplicationConfigurationToUMLXMIDoc", unused1))

		// Are the ID's really equal?
		//ASSERT_EQUALS(unused, unused1)
		
		export_XMI2_Model(*&myUIWrapper, "CDKatalogStartTest_XMI2.xmi");

		meta->unloadApplication();
	}
	
	lbErrCodes CheckBySQLQuery(lb_I_Database* db, const char* dbName, const char* SQL) {
		UAP(lb_I_Query, query)

		query = db->getQuery(dbName, 0);
		ASSERT_EQUALS( true, query != NULL);

		lbErrCodes err = query->query(SQL, false);
		
		return err;
	}
	
	bool CheckBySQLQuery(lb_I_Database* db, const char* dbName, const char* SQL, int row, int column, const char* equals_to) {
		UAP(lb_I_Query, query)

		query = db->getQuery(dbName, 0);
		ASSERT_EQUALS( true, query != NULL);

		lbErrCodes err = query->query(SQL, false);
		
		if (err == ERR_NONE)
		{
			err = query->first();
			
			while (row-- > 0 && ((err = query->next()) == ERR_NONE) || err == WARN_DB_NODATA)
			;
			
			UAP(lb_I_String, col)
			
			col = query->getAsString(column);
		
			printf("Query is \%s\n", col->charrep());
	
			return *col == equals_to;
		}
		
		return err;
	}
	
	void test_Delegated_Action_lbDMFXslt_import_InitialUMLModel( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_import_InitialUMLModel");
	
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSettingsFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslSystemFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XslApplicationFile)
		UAP_REQUEST(getModuleInstance(), lb_I_String, XmiFile)
		
		*XslSystemFile = getenv("DEVROOT");
		*XslApplicationFile = getenv("DEVROOT");
		*XmiFile = getenv("DEVROOT");
		*XslSettingsFile = getenv("DEVROOT");
		
		ASSERT_EQUALS(true, XslSystemFile != NULL)
		ASSERT_EQUALS(true, XslSystemFile->charrep() != NULL)
		
		*XslSystemFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1_2_2_lbDMFSQLScript.xsl";
		*XslApplicationFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\xmi1.2_2SQLScript.xsl";
		*XslSettingsFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\XSLT_Templates\\XMIToDMF\\XMISettings.xmi";
		*XmiFile += "\\Projects\\CPP\\AppDevelopmentDemo\\DynamicApp\\UMLSamples\\InitialModels\\CDKatalog.xmi";

		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		disp->setEventManager(eman.getPtr());

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");
		
		ASSERT_EQUALS(true, action != NULL)
		
		PM->initialize();
		PM->runInstallers();

		// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", true);

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		//setLogActivated(true);
		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");
		//setLogActivated(false);

		meta->fireEvent("writeXMISettings");
		meta->firePropertyChangeEvent("UML import settingsSystem database backend type", "Sqlite");
		meta->firePropertyChangeEvent("UML import settingsApplication database backend type", "Sqlite");
		
		#ifdef WINDOWS
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", XslSettingsFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", XslSystemFile->charrep());
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", XslApplicationFile->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl");
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", "../../../AppDevelopment/DynamicApp/ModelExchange/PostbooksUML2.xmi");
		#endif
		
		int unused;
		
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("importUMLXMIDocIntoApplication", unused))

		//setLogActivated(true);
		meta->fireEvent("importUMLXMIDocIntoApplication");
		//setLogActivated(false);
		meta->msgBox("Test", "Test Message");
	}
	
	void test_Delegated_Action_lbDMFXslt_selfexporting_with_badxsl( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_selfexporting_with_badxsl");
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");

		ASSERT_EQUALS(true, action != NULL)
		
		PM->initialize();
		PM->runInstallers();


		// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		myUIWrapper->addAnswer("no", false);
		myUIWrapper->addAnswer("yes", false);
		myUIWrapper->addAnswer("yes", true);

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		UAP(lb_I_Container, applications)

		applications = meta->getApplications();

		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");

		// Setup the configuration that is needed for this test

        UAP_REQUEST(getModuleInstance(), lb_I_String, path)
        UAP_REQUEST(getModuleInstance(), lb_I_String, File)

		*path = ".";

		#ifdef WINDOWS
		*File = path->charrep();
		*File += "\\";
		*File += "XMISettings.xsl";
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", File->charrep());
		*File = path->charrep();
		*File += "\\";
		*File += "template.xsl";
		meta->firePropertyChangeEvent("UML export settingsXSL file for UML export", File->charrep());
		*File = path->charrep();
		*File += "\\lbDMFManager.xmi";
		meta->firePropertyChangeEvent("UML export settingsXMI UML export file", File->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl");
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", "../../../AppDevelopment/DynamicApp/ModelExchange/PostbooksUML2.xmi");
		#endif


		writeBadXsl("template-bad.xsl");
		
		myUIWrapper->addAnswer("yes", true);
		myUIWrapper->setFileAnswer("template-bad.xsl");
		int nextStep1 = action->execute(*&params);

		// Test for a 'linear action'
		ASSERT_EQUALS(0, nextStep1)
	}

	void test_Delegated_Action_lbDMFXslt_selfexporting( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_selfexporting");
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Database, tempDB) // Preload this module
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP(lb_I_DelegatedAction, action)

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");

		ASSERT_EQUALS(true, action != NULL)
		
		PM->initialize();
		PM->runInstallers();


		// Use an UI wrapper to fake answers.
		UAP(lb_I_SimulatedApplication, myUIWrapper)
		myUIWrapper = new UIWrapper();
		
        myUIWrapper->initialize();

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		//setLogActivated(true);
		
		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		UAP(lb_I_Container, applications)

		applications = meta->getApplications();

		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");

		// Setup the configuration that is needed for this test

        UAP_REQUEST(getModuleInstance(), lb_I_String, path)
        UAP_REQUEST(getModuleInstance(), lb_I_String, File)

		*path = ".";

		#ifdef WINDOWS
		*File = path->charrep();
		*File += "\\";
		*File += "XMISettings.xsl";
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", File->charrep());
		*File = path->charrep();
		*File += "\\";
		*File += "template.xsl";
		meta->firePropertyChangeEvent("UML export settingsXSL file for UML export", File->charrep());
		*File = path->charrep();
		*File += "\\lbDMFManager.xmi";
		meta->firePropertyChangeEvent("UML export settingsXMI UML export file", File->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl");
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", "../../../AppDevelopment/DynamicApp/ModelExchange/PostbooksUML2.xmi");
		#endif


		writeGoodXsl("template-good.xsl");
		
		myUIWrapper->addAnswer("yes", true);
		myUIWrapper->setFileAnswer("template-good.xsl");
		int nextStep1 = action->execute(*&params);

		// Test for a 'linear action'
		ASSERT_EQUALS(-1, nextStep1)
	}

	
	
public:
	void setUp()
	{
#ifdef __MINGW32__
		signal(SIGSEGV, sig_handler);
		signal(SIGABRT, sig_handler);
#endif
#ifdef LINUX
		signal(SIGSEGV, sig_handler);
		signal(SIGBUS, sig_handler);
#endif
#ifdef OSX
		signal(SIGABRT, sig_handler);
		signal(SIGTRAP, sig_handler);
		signal(SIGSEGV, sig_handler);
		signal(SIGTERM, sig_handler);
		signal(SIGBUS, sig_handler);
#endif
	}

	void tearDown()
	{
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->unloadApplication();
	}

	void makePluginName(char* path, char* module, char*& result) {
		char* pluginDir = NULL;

		#ifndef WINDOWS
		pluginDir = (char*) malloc(strlen(path)+1);
		pluginDir[0] = 0;
		strcat(pluginDir, path);
		#endif

		#ifdef WINDOWS
		// Overwrites hardcoded path
		pluginDir = getenv("PLUGIN_DIR");
		if (pluginDir == NULL) {
			pluginDir = (char*) malloc(strlen(path)+1);
			pluginDir[0] = 0;
			strcat(pluginDir, path);
		} else {
			pluginDir = strdup(pluginDir);
		}
		#endif

/*...sBuild up pluginModule:64:*/
		char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2+4);
		pluginModule[0] = 0;
		strcat(pluginModule, pluginDir);
#ifdef WINDOWS
		strcat(pluginModule, "\\");
		strcat(pluginModule, module);
		strcat(pluginModule, ".dll");
#endif
#ifdef LINUX
		strcat(pluginModule, "/");
		strcat(pluginModule, module);
		strcat(pluginModule, ".so");
#endif
#ifndef LINUX
#ifdef OSX
		strcat(pluginModule, "/");
		strcat(pluginModule, module);
		strcat(pluginModule, ".so");
#endif
#endif
/*...e*/

		result = pluginModule;
		free(pluginDir);
	}

	lb_I_String* readStringFromFile(char* filename) {
		UAP(lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, iStream)
		
		iStream->setFileName(filename);
		
		iStream->open();
		
		s = iStream->getAsString();
		iStream->close();
		
		s++;
		return s.getPtr();
	}
	
	void writeStringToFile(char* filename, lb_I_String* s) {
		UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(filename);
		oStream->setBinary();
		oStream->open();
		
		*oStream << s->charrep();
		
		oStream->close();
	}
	
	void writeGoodXsl(char* filename) {
		UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(filename);
		if (oStream->open()) {
			oStream->setBinary();
			*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
			*oStream << "<xsl:output method=\"text\" indent=\"no\"/>\n";
			
			*oStream << "</xsl:stylesheet>\n";
			oStream->close();
		}
	}
	
	void writeGoodXsl(char* filename, char* _template) {
		UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(filename);
		if (oStream->open()) {
			oStream->setBinary();
			*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
			*oStream << "<xsl:output method=\"text\" indent=\"no\"/>\n";
			
			if (_template != NULL) *oStream << _template;
			
			*oStream << "</xsl:stylesheet>\n";
			oStream->close();
		}
	}

	void writeBadXsl(char* filename) {
		UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(filename);
		if (oStream->open()) {
			oStream->setBinary();
			*oStream << ".\n";
			*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
			*oStream << "<xsl:output method=\"text\" indent=\"no\"/>\n";
			
			*oStream << "</xsl:stylesheet>\n";
			oStream->close();
		}
	}
	
	lb_I_DelegatedAction* getActionDelegate(char* _module, char* name) {
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_String, file)

#ifdef WINDOWS
		setLogDirectory(".\\Actions");
#endif
#ifdef LINUX
		setLogDirectory("./Actions");
#endif

#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_String, module)
		UAP(lb_I_Unknown, result)
		UAP(lb_I_String, pluginPath)

		ASSERT_EQUALS(true, getModuleInstance() != NULL)

		char* pluginModule = NULL;
		char* ah = (char*) malloc(strlen(PREFIX)+strlen(name)+1);
		ah[0] = 0;
		strcat(ah, PREFIX);
		strcat(ah, name);

		pluginPath = PM->getPluginDirectory();

		*module = _module;

		makePluginName(pluginPath->charrep(), module->charrep(), pluginModule);

		if (getModuleInstance()->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
			printf("Error: Plugin not found. (%s)\n", pluginModule);
		}

		free(pluginModule);
		pluginModule = NULL;

		ASSERT_EQUALS(true, result != NULL)

		

		UAP(lb_I_DelegatedAction, action)
		QI(result, lb_I_DelegatedAction, action)
		action++;
		return action.getPtr();
	}

	bool LoadSettings()
	{
		return true;
	}
};



DECLARE_FIXTURE( TestMainUseCases )

__attribute__ ((constructor)) void ct() {
	USE_FIXTURE( TestMainUseCases )
}


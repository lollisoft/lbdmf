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
		//TEST_CASE(test_Delegated_Action_lbDMFXslt_stopping_because_not_LoggedIn)
		TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting)
/*
		TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting_failure)
		TEST_CASE(test_Delegated_Action_lbWriteStringToFile)
		TEST_CASE(test_Delegated_Action_lbReadTextFileToString)
		TEST_CASE(test_Delegated_Action_lbGetIdForFormValue)
		TEST_CASE(test_Delegated_Action_lbXSLTTransformer)
*/
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
		UIWrapper* myUIWrapper = new UIWrapper();
		
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
		
		myUIWrapper->setAnswer("yes");
		myUIWrapper->setFileAnswer("template-good.xsl");
		int nextStep1 = action->execute(*&params);

		// Crashes in the next test as probably old event handlers get called.
		//meta->uninitialize();

		// Test for a 'linear action'
		ASSERT_EQUALS(-1, nextStep1)
		
		meta->unloadApplication();
		//meta->uninitialize();
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


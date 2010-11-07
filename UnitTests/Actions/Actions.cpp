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

class UIWrapper : public lb_I_Application,
public lb_I_EventHandler
{
public:
	lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	lbErrCodes LB_STDCALL setUserName(char* user);
	lbErrCodes LB_STDCALL setApplicationName(char* app);
    lbErrCodes LB_STDCALL save();
    lbErrCodes LB_STDCALL load();
	lbErrCodes LB_STDCALL initialize(char* user = NULL, char* app = NULL);
	lbErrCodes LB_STDCALL uninitialize();
	lbErrCodes LB_STDCALL run();
	lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	lb_I_EventManager* LB_STDCALL getEVManager( void );


	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	lb_I_Unknown* LB_STDCALL getUnknown();


	lbErrCodes LB_STDCALL askYesNo(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL setStatusText(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL askOpenFileReadStream(lb_I_Unknown* uk);

	void LB_STDCALL setAnswer(char* what);
	void LB_STDCALL setFileAnswer(char* what);

public:
	UIWrapper();
	virtual ~UIWrapper();

	DECLARE_LB_UNKNOWN()

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)

	UAP(lb_I_String, answer)
	UAP(lb_I_String, fileanswer)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(UIWrapper)
	ADD_INTERFACE(lb_I_Application)
END_IMPLEMENT_LB_UNKNOWN()

//IMPLEMENT_FUNCTOR(instanceOfApplication, UIWrapper)

UIWrapper::UIWrapper() {
	ref = STARTREF;
	gui = NULL;
	REQUEST(getModuleInstance(), lb_I_String, answer)
	REQUEST(getModuleInstance(), lb_I_String, fileanswer)
	printf("Instance of lb_I_Application created\n");
	_LOG << "Instance of lb_I_Application created" LOG_
}

UIWrapper::~UIWrapper() {
	_LOG << "Instance of lb_I_Application destroyed" LOG_
}

void LB_STDCALL UIWrapper::setFileAnswer(char* what) {
	*fileanswer = what;
}

void LB_STDCALL UIWrapper::setAnswer(char* what) {
	*answer = what;
}

lbErrCodes LB_STDCALL UIWrapper::askOpenFileReadStream(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, filepath)
	UAP_REQUEST(manager.getPtr(), lb_I_String, defaultdir)
	UAP_REQUEST(manager.getPtr(), lb_I_String, after)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("extension");
	param->getUAPString(*&parameter, *&name);

	//"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png"

	printf("Choose a file. Default directory: %s, Name: %s\n", defaultdir->charrep(), name->charrep());

	parameter->setData("result");
	filepath->setData(fileanswer->charrep());
	param->setUAPString(*&parameter, *&filepath);

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::setStatusText(lb_I_Unknown* uk) {
        lbErrCodes err = ERR_DISPATCH_PARAMETER_WRONG;
        UAP(lb_I_Parameter, params)

        QI(uk, lb_I_Parameter, params)

        if (params != NULL) {
                UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
                UAP_REQUEST(manager.getPtr(), lb_I_String, name)
				UAP_REQUEST(manager.getPtr(), lb_I_String, value)
				UAP_REQUEST(manager.getPtr(), lb_I_String, CallYield)

                *parameter = "Name";
                params->getUAPString(*&parameter, *&name);
                *parameter = "Value";
                params->getUAPString(*&parameter, *&value);
				*parameter = "CallYield";
				params->getUAPString(*&parameter, *&CallYield);

				printf("Status: %s\n", value->charrep());

                err = ERR_NONE;
        }

        return err;
}

lbErrCodes LB_STDCALL UIWrapper::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)

	UAP(lb_I_Parameter, param)

	if (manager == NULL) {
		printf("manager is NULL.\n");
	}

	QI(uk, lb_I_Parameter, param)

	parameter->setData("msg");
	param->getUAPString(*&parameter, *&msg);

	printf("Question: %s\n", msg->charrep());

    parameter->setData("result");
    result->setData(answer->charrep());
    param->setUAPString(*&parameter, *&result);

    COUT << ENDL;

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::registerEventHandler(lb_I_Dispatcher* disp) {
	lb_I_EventHandler* eh = (lb_I_EventHandler*) this;

	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::askYesNo, "askYesNo");
//	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::setStatusText, "setStatusText");
	disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::askOpenFileReadStream, "askOpenFileReadStream");


	return ERR_NONE;
}

lb_I_Unknown* LB_STDCALL UIWrapper::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
	uk++;
	return uk.getPtr();
}

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setData(lb_I_Unknown* uk) {
	_LOG << "lbApplication::setData() has not been implemented" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager\42\ LB_STDCALL lbApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL UIWrapper::getEVManager( void ) {
	return NULL;
}
/*...e*/

lbErrCodes LB_STDCALL UIWrapper::save() {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::load() {
    return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::uninitialize() {
	return ERR_NONE;
}
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::initialize(char* user, char* app) {

	// To be implemented in a separate application module

	int askYesNo;
	int setStatusText;
	int askOpenFileReadStream;

	// Get the event manager

	REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	eman->registerEvent("askYesNo", askYesNo);
	printf("Registered event ID=%d for askYesNo.\n", askYesNo);
//	eman->registerEvent("setStatusText", setStatusText);
//	printf("Registered event ID=%d for setStatusText.\n", setStatusText);
	eman->registerEvent("askOpenFileReadStream", askOpenFileReadStream);
	printf("Registered event ID=%d for askOpenFileReadStream.\n", askOpenFileReadStream);

	dispatcher->setEventManager(eman.getPtr());
	registerEventHandler(dispatcher.getPtr());
	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL UIWrapper::getUserName(lb_I_String** user) {
	(*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::getApplicationName(lb_I_String** app) {
	(*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL UIWrapper::setUserName(char* user) {
	if (LogonUser == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::setApplicationName(char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);
#endif
	return ERR_NONE;
}



class TestActions : public TestFixture<TestActions>
{
public:
	TEST_FIXTURE( TestActions )
	{
		TEST_CASE(test_Delegated_Action_lbDMFXslt_stopping_because_not_LoggedIn)
		TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting)
		TEST_CASE(test_Delegated_Action_lbDMFXslt_selfexporting_failure)
		TEST_CASE(test_Delegated_Action_lbWriteStringToFile)
		TEST_CASE(test_Delegated_Action_lbReadTextFileToString)
		TEST_CASE(test_Delegated_Action_lbXSLTTransformer)
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
		UAP(lb_I_Module, manager)
		UAP(lb_I_Unknown, result)
		UAP(lb_I_String, pluginPath)

		manager = getModuleInstance();

		ASSERT_EQUALS(true, manager != NULL)

		char* pluginModule = NULL;
		char* ah = (char*) malloc(strlen(PREFIX)+strlen(name)+1);
		ah[0] = 0;
		strcat(ah, PREFIX);
		strcat(ah, name);

		pluginPath = PM->getPluginDirectory();

		*module = _module;

		makePluginName(pluginPath->charrep(), module->charrep(), pluginModule);

		if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
			printf("Error: Plugin not found. (%s)\n", pluginModule);
		}

		free(pluginModule);
		pluginModule = NULL;

		ASSERT_EQUALS(true, result != NULL)

		result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);

		UAP(lb_I_DelegatedAction, action)
		QI(result, lb_I_DelegatedAction, action)
		action++;
		return action.getPtr();
	}

	void test_Delegated_Action_lbWriteStringToFile( void ) {
		puts("test_Delegated_Action_lbWriteStringToFile");
		
		lbErrCodes err = ERR_NONE;

		// They are registered as event handlers
		
		//UAP(lb_I_DelegatedAction, action)
		//action = getActionDelegate("lbFileOperationsPlugin", "instanceOflbWriteStringToFile");
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, source)
		UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)

		*name = "source";
		*source = "Test";
		params->setUAPString(*&name, *&source);
		
		*name = "filename";
		*filename = "Test.txt";
		params->setUAPString(*&name, *&filename);
		
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->initialize();

		if (PM->beginEnumPlugins()) {
			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = PM->nextPlugin();
				if (pl == NULL) break;
				pl->autorun();
			}
		}
		
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Unknown, uk_result)
		QI(params, lb_I_Unknown, uk)
		
		disp->dispatch("writeStringToFile", *&uk, &uk_result);
		
		//int nextStep1 = action->execute(*&params);

		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		
		*name = "result";
		params->getUAPString(*&name, *&result);

		
		UAP(lb_I_String, test)
		
		test = readStringFromFile("Test.txt");
		
		ASSERT_EQUALS( true, *test == "Test")
		
		// No hard failure
		//ASSERT_EQUALS(-1, nextStep1)
		
		// Success = 1, Failure = 0
		ASSERT_EQUALS("1", result->charrep())
	}
	
	void test_Delegated_Action_lbReadTextFileToString( void ) {
		puts("test_Delegated_Action_lbReadTextFileToString");
	
		lbErrCodes err = ERR_NONE;
		
		// They are registered as event handlers
		
		//UAP(lb_I_DelegatedAction, action)
		//action = getActionDelegate("lbFileOperationsPlugin", "instanceOflbReadTextFileToString");
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, target)
		UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		
		*name = "target";
		*target = "";
		params->setUAPString(*&name, *&target);
		
		*name = "filename";
		*filename = "Test.txt";
		params->setUAPString(*&name, *&filename);
		
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->initialize();
		
		if (PM->beginEnumPlugins()) {
			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = PM->nextPlugin();
				if (pl == NULL) break;
				pl->autorun();
			}
		}

		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Unknown, uk_result)
		QI(params, lb_I_Unknown, uk)
		
		disp->dispatch("readFileToString", *&uk, &uk_result);

		//int nextStep1 = action->execute(*&params);
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		
		*name = "result";
		params->getUAPString(*&name, *&result);
		
		
		*name = "target";
		params->getUAPString(*&name, *&target);
		
		// No hard failure
		//ASSERT_EQUALS(-1, nextStep1)

		printf("Text is '%s'\n", target->charrep());
		
		ASSERT_EQUALS( true, *target == "Test" )
		
		// Success = 1, Failure = 0
		ASSERT_EQUALS("1", result->charrep())
	}
	
	void test_Delegated_Action_lbXSLTTransformer( void ) {
		puts("test_Delegated_Action_lbXSLTTransformer");
		
		lbErrCodes err = ERR_NONE;
		
		// They are registered as event handlers
		
		//UAP(lb_I_DelegatedAction, action)
		//action = getActionDelegate("lbFileOperationsPlugin", "instanceOflbReadTextFileToString");
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, source)
		UAP_REQUEST(getModuleInstance(), lb_I_String, stylesheet)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		
		*name = "source";
		*source = "";
		
		*source += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		*source += "<Customers>";
		*source += "	<Customer name='Boss' vorname='Hugo'>";
		*source += "	</Customer>";
		*source += "</Customers>";

		writeStringToFile("Text.xml", *&source);
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, myTemplate)
		
		*myTemplate = "";
		*myTemplate += "<xsl:template match=\"text()|@*\">";
		*myTemplate += "<xsl:value-of select=\".\"/>";
		*myTemplate += "</xsl:template>";
		*myTemplate += "<xsl:template match=\"text()|@*\"/>";
		*myTemplate += "";

		*myTemplate += "<xsl:template match=\"//Customers/Customer\">";
		*myTemplate += "<xsl:value-of select=\"./@name\"/>, <xsl:value-of select=\"./@vorname\"/>";
		*myTemplate += "</xsl:template>";


		*source = "Text.xml";
		
		params->setUAPString(*&name, *&source);
		
		*name = "stylesheet";
		*stylesheet = "Style.xsl";
		params->setUAPString(*&name, *&stylesheet);
		
		writeGoodXsl(stylesheet->charrep(), myTemplate->charrep());
		
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->initialize();
		
		if (PM->beginEnumPlugins()) {
			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = PM->nextPlugin();
				if (pl == NULL) break;
				pl->autorun();
			}
		}
		
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Unknown, uk_result)
		QI(params, lb_I_Unknown, uk)
		
		setLogActivated(true);
		disp->dispatch("transformXSLT", *&uk, &uk_result);
		setLogActivated(false);
		
		//int nextStep1 = action->execute(*&params);
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		UAP_REQUEST(getModuleInstance(), lb_I_String, stepoutput)
		
		
		*name = "result";
		params->getUAPString(*&name, *&result);
		
		*name = "stepoutput";
		params->getUAPString(*&name, *&stepoutput);
		
		// No hard failure
		//ASSERT_EQUALS(-1, nextStep1)
		
		printf("Text is '%s'\n", stepoutput->charrep());
		
		ASSERT_EQUALS( true, *stepoutput == "Boss, Hugo" )
		
		// Success = 1, Failure = 0
		ASSERT_EQUALS("1", result->charrep())
	}

	void test_Delegated_Action_lbDMFXslt_selfexporting( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_selfexporting");
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP(lb_I_DelegatedAction, action)

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");

		ASSERT_EQUALS(true, action != NULL)
		setLogActivated(false);
		PM->initialize();

		// Use an UI wrapper to fake answers.
		UIWrapper* myUIWrapper = new UIWrapper();
		myUIWrapper->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
        myUIWrapper->initialize();

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

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

		myUIWrapper->setAnswer("yes");
		myUIWrapper->setFileAnswer("template-good.xsl");
		int nextStep1 = action->execute(*&params);

		// Crashes in the next test as probably old event handlers get called.
		//meta->uninitialize();

		// Test for a 'linear action'
		ASSERT_EQUALS(-1, nextStep1)
	}

	void test_Delegated_Action_lbDMFXslt_selfexporting_failure( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_selfexporting_failure");
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP(lb_I_DelegatedAction, action)

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");

		ASSERT_EQUALS(true, action != NULL)
		setLogActivated(false);
		PM->initialize();

		// Use an UI wrapper to fake answers.
		UIWrapper* myUIWrapper = new UIWrapper();
		myUIWrapper->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
        myUIWrapper->initialize();

		// Be sure to not autoload
		meta->load();
		meta->setAutoload(false);
		meta->initialize("user", "lbDMF Manager");

		ASSERT_EQUALS(true, meta->login("user", "TestUser"))

		UAP(lb_I_Container, applications)

		applications = meta->getApplications();

		// Must not logged in to load
		if (!meta->getAutoload() && meta->getApplicationID() == 0) meta->loadApplication("user", "lbDMF Manager");

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

		myUIWrapper->setAnswer("yes");
		myUIWrapper->setFileAnswer("template-fail.xsl");
		int nextStep1 = action->execute(*&params);

		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, result)

		*name = "result";
		params->getUAPString(*&name, *&result);

		meta->uninitialize();

		// No hard failure
		ASSERT_EQUALS(-1, nextStep1)

		// Success = 1, Failure = 0
		//ASSERT_EQUALS("1", result->charrep())
		ASSERT_EQUALS("0", result->charrep())
	}

	void test_Delegated_Action_lbDMFXslt_stopping_because_not_LoggedIn( void )
	{
		puts("test_Delegated_Action_lbDMFXslt_stopping_because_not_LoggedIn");
		UAP(lb_I_DelegatedAction, action)

		action = getActionDelegate("lbDMFXslt", "instanceOflbDMFXslt");

		ASSERT_EQUALS(true, action != NULL)

		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)

		//action->setParameter(*&parameter);
		int nextStep = action->execute(*&params);

		// Test for a 'stop action'
		ASSERT_EQUALS(0, nextStep)
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


	bool LoadSettings()
	{
		return true;
	}
};





REGISTER_FIXTURE( TestActions );

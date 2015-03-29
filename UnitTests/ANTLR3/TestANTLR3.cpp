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

class TestANTLR3 : public TestFixture<TestANTLR3>
{
public:
	TEST_FIXTURE( TestANTLR3 )
	{
		#ifdef WINDOWS
		setLogDirectory(".\\custom_logdir");
		#endif
		#ifdef LINUX
		setLogDirectory("./custom_logdir");
		#endif

		TEST_CASE(test_LoadAntlr3Plugin)
		TEST_CASE(test_LoadParseUILanguage)
	}

	void test_LoadAntlr3Plugin( void )
	{
		puts("test_LoadAntlr3Plugin");

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

		PM->initialize();
		PM->runInstallers();

	    if (PM->beginEnumPlugins()) {

    	while (true) {
        	UAP(lb_I_Plugin, pl)
        	pl = PM->nextPlugin();
        	if (pl == NULL) break;
        	    pl->autorun();
        	}
    	}

		int unused;
	
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("parse", unused))
	}

	void test_LoadParseUILanguage( void )
	{
		puts("test_LoadParseUILanguage");

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

		PM->initialize();
		PM->runInstallers();
	
	    if (PM->beginEnumPlugins()) {

    	while (true) {
        	UAP(lb_I_Plugin, pl)
        	pl = PM->nextPlugin();
        	if (pl == NULL) break;
        	    pl->autorun();
        	}
    	}

		int unused;
	
		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

		UAP_REQUEST(getModuleInstance(), lb_I_String, language)
		UAP_REQUEST(getModuleInstance(), lb_I_String, sourcecode)
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, parseparameters)
		UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
		UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name

		*language = "UILanguage";
		*sourcecode = "2 + 4 * 5";
	
		*paramName = "language";
		parseparameters->setUAPString(*&paramName, *&language);
		*paramName = "sourcecode";
		parseparameters->setUAPString(*&paramName, *&sourcecode);

		UAP(lb_I_Unknown, ukparameters)
		lb_I_Unknown* result;

		QI(parseparameters, lb_I_Unknown, ukparameters)

		dispatcher->dispatch("parse", *&ukparameters, &result);
	
	
		ASSERT_EQUALS(ERR_NONE, eman->resolveEvent("parse", unused))
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

	bool LoadSettings()
	{
		return true;
	}
};



DECLARE_FIXTURE( TestANTLR3 )

__attribute__ ((constructor)) void ct() {
	USE_FIXTURE( TestANTLR3 )
}


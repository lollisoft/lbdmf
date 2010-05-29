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
};

BEGIN_IMPLEMENT_LB_UNKNOWN(UIWrapper)
	ADD_INTERFACE(lb_I_Application)
END_IMPLEMENT_LB_UNKNOWN()

//IMPLEMENT_FUNCTOR(instanceOfApplication, UIWrapper)

UIWrapper::UIWrapper() {
	ref = STARTREF;
	gui = NULL;
	printf("Instance of lb_I_Application created\n");
	_LOG << "Instance of lb_I_Application created" LOG_
}

UIWrapper::~UIWrapper() {
	_LOG << "Instance of lb_I_Application destroyed" LOG_
}


lbErrCodes LB_STDCALL UIWrapper::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	printf("lbErrCodes LB_STDCALL UIWrapper::askYesNo(lb_I_Unknown* uk) called.\n");
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


	printf("Console dialog:\n\n%s\n\n", msg->charrep());

	if (strcmp(msg->charrep(), "Hallo UnitTests") == 0) {
		printf("y");
	    parameter->setData("result");
		result->setData("yes");
		param->setUAPString(*&parameter, *&result);
		COUT << ENDL;
		return err;
	}

	char c = ' ';

    setvbuf(stdin, &c, _IONBF, 1);
    while ( c != 'y' &&
            c != 'Y' &&
            c != 'n' &&
            c != 'N') {
        fread(&c, 1, 1, stdin);
    }


    switch (c) {
        case 'y':
        case 'Y':
            parameter->setData("result");
            result->setData("yes");
            param->setUAPString(*&parameter, *&result);
            break;
        default:
            parameter->setData("result");
            result->setData("no");
            param->setUAPString(*&parameter, *&result);
    }

    COUT << ENDL;

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::registerEventHandler(lb_I_Dispatcher* disp) {
	char* evName = strdup("askYesNo"); // Otherwise Open Watcom gets a pointer of 0xFFFFFFFF

	lb_I_EventHandler* eh = (lb_I_EventHandler*) this;

	lbErrCodes err = disp->addEventHandlerFn(eh, (lbEvHandler) &UIWrapper::askYesNo, evName);
	free(evName);
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

	// Get the event manager

	REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	eman->registerEvent("askYesNo", askYesNo);
	printf("Registered event ID=%d for askYesNo.\n", askYesNo);

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


class BaseDevelopmentLogger : public TestFixture<BaseDevelopmentLogger>
{
public:
	TEST_FIXTURE( BaseDevelopmentLogger )
	{
		TEST_CASE(test_Log_creating_logdirectory)
		TEST_CASE(test_Log_Instanciating)
		TEST_CASE(test_Log_Initially_disabled)
		TEST_CASE(test_Log_Log_a_Line)
		TEST_CASE(test_Log_Log_disabling)
	}

	void test_Log_Initially_disabled( void )
	{
		puts("test_Log_Initially_disabled");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		*s = getLogDirectory();
		*s += LOGFILE;

		remove(s->charrep());
		ASSERT_EQUALS(false, FileExists(s->charrep()))

		_LOG << "Log a line." LOG_
		ASSERT_EQUALS(false, FileExists(s->charrep()))
	}

	void test_Log_Log_disabling( void )
	{
		puts("test_Log_Log_disabling");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		_LOG << "Log a line." LOG_
		*s = getLogDirectory();
		*s += LOGFILE;
		ASSERT_EQUALS(true, FileExists(s->charrep()))
		remove(s->charrep());
		ASSERT_EQUALS(false, FileExists(s->charrep()))
		setLogActivated(false);
		_LOG << "Log a line." LOG_
		ASSERT_EQUALS(false, FileExists(s->charrep()))
		// Let the file stay after the test.
		setLogActivated(true);
		_LOG << "Unittests have been finished." LOG_
		setLogActivated(false);
	}

	void test_Log_creating_logdirectory( void )
	{
		puts("test_Log_creating_logdirectory");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_String, file)
#ifdef WINDOWS
		setLogDirectory(".\\custom_logdir");
#endif
#ifdef LINUX
		setLogDirectory("./custom_logdir");
#endif
		*s = getLogDirectory();
		*file = getLogDirectory();

		*file += LOGFILE;
		remove(file->charrep());

		deleteDirectory(s->charrep());

		ASSERT_EQUALS(false, DirectoryExists(s->charrep()))
		setLogActivated(true);
		_LOG << "Log a line" LOG_
		setLogActivated(false);
		ASSERT_EQUALS(true, DirectoryExists(s->charrep()))
	}

	void test_Log_Instanciating( void )
	{
		puts("test_Log_Instanciating");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Log, log)
		*s = getLogDirectory();
		*s += LOGFILE;

		log->setCustomLogFile(s->charrep());
		ASSERT_EQUALS( true, log.getPtr() != NULL );
	}

	void test_Log_Log_a_Line( void )
	{
		puts("test_Log_Log_a_Line");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		setLogActivated(true);
		_LOG << "Log a line." LOG_
		*s = getLogDirectory();
		*s += LOGFILE;

		ASSERT_EQUALS(true, FileExists(s->charrep()))
		//remove(s->charrep());
		printf("%s\n", s->charrep());
		//ASSERT_EQUALS(false, FileExists(s->charrep()))
	}

public:
	void setUp()
	{
#ifdef __MINGW__
#endif
#ifdef LINUX
		signal(SIGSEGV, sig_handler);
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





class BaseDevelopmentString : public TestFixture<BaseDevelopmentString>
{
public:
	TEST_FIXTURE( BaseDevelopmentString )
	{
		TEST_CASE(test_Instanciate_lbString)
		TEST_CASE(test_lbString_Initialized_properly)
		TEST_CASE(test_lbString_trim)
		TEST_CASE(test_lbString_replace)
		TEST_CASE(test_lbString_toLower)
		TEST_CASE(test_lbString_stristr)
		TEST_CASE(test_lbString_setDataNULL)
		TEST_CASE(test_lbString_getData)
		TEST_CASE(test_lbString_setDataWithUnknownLong)
		TEST_CASE(test_lbString_setDataWithUnknownNULL)
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

	void test_lbString_setDataWithUnknownLong( void )
	{
		puts("test_lbString_setDataWithUnknownLong");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
		UAP(lb_I_Unknown, uk)
		QI(l, lb_I_Unknown, uk)
		l->setData(10);
		s->setData(*&uk);

		ASSERT_EQUALS( true, s->charrep() != NULL );
		ASSERT_EQUALS( true, *s == "" );
	}

	void test_lbString_setDataWithUnknownNULL( void )
	{
		puts("test_lbString_setDataWithUnknownNULL");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		lb_I_Unknown* uk = NULL;
		s->setData(uk);

		ASSERT_EQUALS( true, s->charrep() != NULL );
		ASSERT_EQUALS( true, *s == "" );
	}

	void test_lbString_setDataNULL( void )
	{
		lbErrCodes err = ERR_NONE;
		puts("test_lbString_setDataNULL");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
		UAP(lb_I_Unknown, ukTest)
		UAP(lb_I_Unknown, ukTestNULL)
		QI(l, lb_I_Unknown, ukTest)

		s->setData((char*) NULL);

		ASSERT_EQUALS( true, s->charrep() != NULL );
		ASSERT_EQUALS( true, *s == "" );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, s->setData(*&ukTest) );
		ASSERT_EQUALS( ERR_NONE, s->setData(*&ukTestNULL) );
	}

	void test_lbString_getData( void )
	{
		puts("test_lbString_getData");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		char* data = s->getData();

		//ASSERT_EQUALS( true, data != NULL );
		ASSERT_EQUALS( true, strcmp(data, "") == 0 );
	}

	void test_lbString_toLower( void )
	{
		puts("test_lbString_toLower");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		*s = "LALA";

		s->toLower();

		ASSERT_EQUALS( true, *s == "lala" );
	}

	void test_lbString_stristr( void )
	{
		puts("test_lbString_stristr");
		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		*result = s->stristr("left_inner_rigth", "inner");

		ASSERT_EQUALS( true, *result == "inner_rigth" );
	}

	void test_Instanciate_lbString( void )
	{
		puts("test_Instanciate_lbString");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		ASSERT_EQUALS( true, s.getPtr() != NULL );
	}

	void test_lbString_Initialized_properly( void )
	{
		puts("test_lbString_Initialized_properly");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		ASSERT_EQUALS( true, s->charrep() != NULL );
		ASSERT_EQUALS( true, *s == "" );
	}

	void test_lbString_trim( void )
	{
		puts("test_lbString_trim");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		*s = " lala ";

		s->trim();

		ASSERT_EQUALS( true, *s == " lala" );
	}

	void test_lbString_replace( void )
	{
		puts("test_lbString_replace");
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		*s = " lala ";

		s->replace(" ", "");

		ASSERT_EQUALS( true, *s == "lala" );
	}

	bool LoadSettings()
	{
		return true;
	}
};





class BaseDevelopmentContainer : public TestFixture<BaseDevelopmentContainer>
{
public:
	TEST_FIXTURE( BaseDevelopmentContainer )
	{
		TEST_CASE(test_Instanciate_lbContainer)
		TEST_CASE(test_lbContainer_InsertString_with_Integer_Key)
		TEST_CASE(test_lbContainer_lookup_byKey)
	}

	void test_Instanciate_lbContainer( void )
	{
		puts("test_Instanciate_lbContainer");
		UAP_REQUEST(getModuleInstance(), lb_I_Container, c)

		ASSERT_EQUALS( true, c.getPtr() != NULL );
	}

	void test_lbContainer_lookup_byKey( void )
	{
		lbErrCodes err = ERR_NONE;
		puts("test_lbContainer_lookup_byKey");
		UAP_REQUEST(getModuleInstance(), lb_I_Container, c)
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

		ASSERT_EQUALS( true, c.getPtr() != NULL );


		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		QI(s, lb_I_Unknown, uk)
		QI(i, lb_I_KeyBase, key)
		
		*s = "Testvalue1";
		i->setData(1);
		c->insert(&uk, &key);
		*s = "Testvalue2";
		i->setData(2);
		c->insert(&uk, &key);
		*s = "Testvalue3";
		i->setData(3);
		c->insert(&uk, &key);
		*s = "Testvalue4";
		i->setData(4);
		c->insert(&uk, &key);
		*s = "Testvalue5";
		i->setData(5);
		c->insert(&uk, &key);

		ASSERT_EQUALS( 5, c->Count() );

		UAP(lb_I_Unknown, uk1)

		uk1 = c->getElement(&key);

		ASSERT_EQUALS( true, uk1 != NULL );

		i->setData(0);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 == NULL );
		i->setData(5);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 != NULL );
		i->setData(4);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 != NULL );
		i->setData(3);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 != NULL );
		i->setData(2);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 != NULL );
		i->setData(1);
		uk1 = c->getElement(&key);
		ASSERT_EQUALS( true, uk1 != NULL );
	}

	void test_lbContainer_InsertString_with_Integer_Key( void )
	{
		lbErrCodes err = ERR_NONE;
		puts("test_lbContainer_InsertString_with_Integer_Key");
		UAP_REQUEST(getModuleInstance(), lb_I_Container, c)
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

		ASSERT_EQUALS( true, c.getPtr() != NULL );


		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		QI(s, lb_I_Unknown, uk)
		QI(i, lb_I_KeyBase, key)
		
		*s = "Testvalue";
		i->setData(20);

		c->insert(&uk, &key);

		ASSERT_EQUALS( 1, c->Count() );
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

class BaseDevelopmentEventManager : public TestFixture<BaseDevelopmentEventManager>
{
public:
	TEST_FIXTURE( BaseDevelopmentEventManager )
	{
		TEST_CASE(test_Instanciate_lbEventmanager)
		TEST_CASE(test_lbEventmanager_Register_Event)
		TEST_CASE(test_lbEventmanager_Resolve_Event)
		TEST_CASE(test_UIWrapper_Initializing)
	}

	void test_UIWrapper_Initializing( void )
	{
		puts("test_UIWrapper_Initializing");

		// Use an UI wrapper to fake answers.
		UIWrapper* myUIWrapper = new UIWrapper();
		myUIWrapper->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
		myUIWrapper->initialize();
		
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)


		parameter->setData("msg");
		value->setData("Hallo UnitTests");
		param->setUAPString(*&parameter, *&value);

		UAP(lb_I_Unknown, uk)
		QI(param, lb_I_Unknown, uk)

		UAP_REQUEST(getModuleInstance(), lb_I_String, result)
		UAP(lb_I_Unknown, uk_result)
		QI(result, lb_I_Unknown, uk_result)

		UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
		dispatcher->setEventManager(eman.getPtr());

		int evId = 0;

		eman->resolveEvent("askYesNo", evId);

		ASSERT_EQUALS( false, evId == 0 );
		err = dispatcher->dispatch("askYesNo", uk.getPtr(), &uk_result);

		ASSERT_EQUALS( ERR_NONE, err );

		// Got a name of the file. Create an input stream.

		parameter->setData("result");
		param->getUAPString(*&parameter, *&value);

		ASSERT_EQUALS( 0,  strcmp(value->charrep(), "yes") );
	}

	void test_Instanciate_lbEventmanager( void )
	{
		puts("test_Instanciate_lbEventmanager");
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, em)

		ASSERT_EQUALS( true, em.getPtr() != NULL );
	}

	void test_lbEventmanager_Register_Event( void )
	{
		lbErrCodes err = ERR_NONE;
		puts("test_lbEventmanager_Register_Event");
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, em)

		int id;
		int id_resolve;
		char* eventName = "TestEvent";

		ASSERT_EQUALS( true, em.getPtr() != NULL );

		em->registerEvent(eventName, id);
		em->resolveEvent(eventName, id_resolve);

		ASSERT_EQUALS( id, id_resolve );
	}

	void test_lbEventmanager_Resolve_Event( void )
	{
		lbErrCodes err = ERR_NONE;
		puts("test_lbEventmanager_Resolve_Event");
		UAP_REQUEST(getModuleInstance(), lb_I_EventManager, em)

		int id;
		int id_resolve;
		char* eventName = "TestEvent";

		ASSERT_EQUALS( true, em.getPtr() != NULL );

		em->registerEvent(eventName, id);
		em->resolveEvent(eventName, id_resolve);
		ASSERT_EQUALS( id, id_resolve );

		id_resolve = 0;

		em->resolveEvent("lala", id_resolve);
		ASSERT_EQUALS( true, id_resolve != id);
		ASSERT_EQUALS( true, id_resolve == 0);

		char* resolved = em->reverseEvent(id);

		ASSERT_EQUALS( 0, strcmp("TestEvent", resolved) );
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


class BaseDevelopmentMetaApplication : public TestFixture<BaseDevelopmentMetaApplication>
{
public:
	TEST_FIXTURE( BaseDevelopmentMetaApplication )
	{
		TEST_CASE(test_Instanciate_lbMetaApplication)
		TEST_CASE(test_lbMetaApplication_getActiveDocument_not_available_because_not_logged_in)
		TEST_CASE(test_lbMetaApplication_login_failure_because_not_initialized)
	}

	void test_lbMetaApplication_login_failure_because_not_initialized( void )
	{
		puts("test_lbMetaApplication_login_failure_because_not_initialized");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, m)

		ASSERT_EQUALS( true, m->login("user", "TestUser") == false );
	}

	void test_lbMetaApplication_getActiveDocument_not_available_because_not_logged_in( void )
	{
		puts("test_lbMetaApplication_getActiveDocument_not_available_because_not_logged_in");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, m)
		UAP(lb_I_Unknown, uk)

		uk = m->getActiveDocument();

		ASSERT_EQUALS( true, uk == NULL );
	}

	void test_Instanciate_lbMetaApplication( void )
	{
		puts("test_Instanciate_lbMetaApplication");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, m)

		ASSERT_EQUALS( true, m != NULL );
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





class BaseDevelopmentDatabase : public TestFixture<BaseDevelopmentDatabase>
{
public:
	TEST_FIXTURE( BaseDevelopmentDatabase )
	{
		TEST_CASE(test_Instantiate)
		TEST_CASE(test_SQLSERVER_setUser)
		TEST_CASE(test_SQLSERVER_setDB)
		TEST_CASE(test_login_SQLSERVER_UnitTest_failure)
		TEST_CASE(test_login_SQLSERVER_UnitTest)
		TEST_CASE(test_createTable_SQLSERVER_UnitTest)
		TEST_CASE(test_SQLSERVER_listTables)

		TEST_CASE(test_PostgreSQL_setUser)
		TEST_CASE(test_PostgreSQL_setDB)
		TEST_CASE(test_login_PostgreSQL_UnitTest_failure)
		TEST_CASE(test_login_PostgreSQL_UnitTest)
		TEST_CASE(test_PostgreSQL_createTable_PostgreSQL_UnitTest)
		TEST_CASE(test_PostgreSQL_listTables)
	}


public:
	void setUp()
	{
#ifdef __MINGW32__
		signal(SIGSEGV, sig_handler);
		signal(SIGABRT, sig_handler);
#endif
#ifdef LINUX
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

	void test_PostgreSQL_setUser( void )
	{
		puts("test_PostgreSQL_setUser");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setUser(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setUser("lala"));
	}

	void test_PostgreSQL_setDB( void )
	{
		puts("test_PostgreSQL_setDB");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setDB(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setDB("lala"));
	}

	void test_PostgreSQL_listTables( void )
	{
		puts("test_PostgreSQL_listTables");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestPostgreSQL", 0);

		ASSERT_EQUALS( true, query != NULL);

		ASSERT_EQUALS( ERR_NONE, query->query(
			"CREATE TABLE test ("
			"	id serial,"
			"	Name char(100)"
			")"
			, false));

		UAP(lb_I_Container, tables)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP(lb_I_Parameter, SomeBaseSettings)
		SomeBaseSettings = meta->getPropertySet("DynamicAppDefaultSettings");

		UAP_REQUEST(getModuleInstance(), lb_I_String, schema)


		if (SomeBaseSettings != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)

			*name = "GeneralDBSchemaname";
			*schema = "public";
			SomeBaseSettings->setUAPString(*&name, *&schema);
			meta->addPropertySet(*&SomeBaseSettings, "DynamicAppDefaultSettings");
		}


		tables = db->getTables("UnitTestPostgreSQL");

		int count = tables->Count();

		ASSERT_EQUALS( ERR_NONE, query->query(
			"DROP TABLE test"
			, false));

		ASSERT_EQUALS( 1, count);

		db->close();
	}

	void test_PostgreSQL_createTable_PostgreSQL_UnitTest( void )
	{
		puts("test_PostgreSQL_createTable_PostgreSQL_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestPostgreSQL", 0);

		ASSERT_EQUALS( true, query != NULL);

		lbErrCodes err1 = query->query(
			"CREATE TABLE test ("
			"	id serial,"
			"	Name char(100)"
			")"
			, false);

		lbErrCodes err2 = query->query(
			"DROP TABLE test"
			, false);

		ASSERT_EQUALS( ERR_NONE, err1);

		ASSERT_EQUALS( ERR_NONE, err1);

		db->close();
	}

	void test_login_PostgreSQL_UnitTest_failure( void )
	{
		puts("test_PostgreSQL_login_PostgreSQL_UnitTest_failure");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_DB_CONNECT, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trallala"));

		db->close();
	}

	void test_login_PostgreSQL_UnitTest( void )
	{
		puts("test_PostgreSQL_login_PostgreSQL_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trainres"));

		db->close();
	}


	void test_SQLSERVER_setUser( void )
	{
		puts("test_SQLSERVER_setUser");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setUser(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setUser("lala"));
	}

	void test_SQLSERVER_setDB( void )
	{
		puts("test_SQLSERVER_setDB");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setDB(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setDB("lala"));
	}

	void test_SQLSERVER_listTables( void )
	{
		puts("test_SQLSERVER_listTables");
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestSQLSERVER", 0);

		ASSERT_EQUALS( true, query != NULL)

		// Drop the table in case it exists.
		query->query("DROP TABLE [dbo].[test]", false);

		query->query(
			"CREATE TABLE [dbo].[test] ("
			"	id int identity(1,1) NOT NULL,"
			"	Name nchar(100)"
			")", false);

		UAP(lb_I_Container, tables)
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP(lb_I_Parameter, SomeBaseSettings)
		SomeBaseSettings = meta->getPropertySet("DynamicAppDefaultSettings");

		UAP_REQUEST(getModuleInstance(), lb_I_String, schema)

		if (SomeBaseSettings != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)

			*name = "GeneralDBSchemaname";
			*schema = "dbo";
			SomeBaseSettings->setUAPString(*&name, *&schema);
			meta->addPropertySet(*&SomeBaseSettings, "DynamicAppDefaultSettings");
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			REQUEST(getModuleInstance(), lb_I_Parameter, SomeBaseSettings)

			*name = "GeneralDBSchemaname";
			*schema = "dbo";
			SomeBaseSettings->setUAPString(*&name, *&schema);
			meta->addPropertySet(*&SomeBaseSettings, "DynamicAppDefaultSettings");
		}

		tables = db->getTables("UnitTestSQLSERVER");

		int count = tables->Count();

		ASSERT_EQUALS( 1, count);

		UAP(lb_I_Parameter, param)
		UAP_REQUEST(getModuleInstance(), lb_I_String, tableName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Unknown, uk)
		uk = tables->getElementAt(1);
		QI(uk, lb_I_Parameter, param)
		
		*name = "TableName";
		param->getUAPString(*&name, *&tableName);

		query->query("DROP TABLE [dbo].[test]", false);

		ASSERT_EQUALS( "test", tableName->charrep());

		db->close();
	}

	void test_createTable_SQLSERVER_UnitTest( void )
	{
		puts("test_createTable_SQLSERVER_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestSQLSERVER", 0);

		ASSERT_EQUALS( true, query != NULL);

		lbErrCodes err1 = query->query(
			"CREATE TABLE [dbo].[test] ("
			"	id int identity(1,1) NOT NULL,"
			"	Name nchar(100)"
			")"
			, false);

		lbErrCodes err2 = query->query(
			"DROP TABLE [dbo].[test]"
			, false);

		ASSERT_EQUALS( ERR_NONE, err1);

		ASSERT_EQUALS( ERR_NONE, err2);

		db->close();
	}

	void test_login_SQLSERVER_UnitTest_failure( void )
	{
		puts("test_login_SQLSERVER_UnitTest_failure");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );
		ASSERT_EQUALS( ERR_DB_CONNECT, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trallala"));
		
		db->close();
	}

	void test_login_SQLSERVER_UnitTest( void )
	{
		puts("test_login_SQLSERVER_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		db->close();
	}

	void test_Instantiate( void )
	{
		puts("test_Instantiate");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );
		db->init();
	}


	bool LoadSettings()
	{
		return true;
	}
};








REGISTER_FIXTURE( BaseDevelopmentLogger );
REGISTER_FIXTURE( BaseDevelopmentString );
REGISTER_FIXTURE( BaseDevelopmentContainer );
REGISTER_FIXTURE( BaseDevelopmentMetaApplication );
REGISTER_FIXTURE( BaseDevelopmentDatabase );
REGISTER_FIXTURE( BaseDevelopmentEventManager );

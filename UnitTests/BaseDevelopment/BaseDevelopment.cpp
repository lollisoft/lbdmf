#include "../MiniCppUnit/MiniCppUnit.hxx"

#include <lbConfigHook.h>
#include <signal.h>

#define DONT_USE_LBDMF_EXCEPTIONS

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
		*s += "\\myLog.log";

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
		*s += "\\myLog.log";
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

		setLogDirectory(".\\custom_logdir");

		*s = getLogDirectory();
		*file = getLogDirectory();

		*file += "\\myLog.log";
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
		*s += "\\myLog.log";

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
		*s += "\\myLog.log";

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





class BaseDevelopmentDatabase : public TestFixture<BaseDevelopmentDatabase>
{
public:
	TEST_FIXTURE( BaseDevelopmentDatabase )
	{
		TEST_CASE(test_Instanciate_lbDatabase)
		TEST_CASE(test_Instanciate_lbDatabase_setUser)
		TEST_CASE(test_Instanciate_lbDatabase_setDB)
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

	void test_Instanciate_lbDatabase( void )
	{
		puts("test_Instanciate_lbDatabase");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );
	}


	void test_Instanciate_lbDatabase_setUser( void )
	{
		puts("test_Instanciate_lbDatabase_setUser");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setUser(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setUser("lala"));
	}

	void test_Instanciate_lbDatabase_setDB( void )
	{
		puts("test_Instanciate_lbDatabase_setDB");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setDB(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setDB("lala"));
	}

	bool LoadSettings()
	{
		return true;
	}
};









REGISTER_FIXTURE( BaseDevelopmentLogger );
REGISTER_FIXTURE( BaseDevelopmentString );
REGISTER_FIXTURE( BaseDevelopmentDatabase );

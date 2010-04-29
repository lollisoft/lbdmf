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





class BaseDevelopmentMetaApplication : public TestFixture<BaseDevelopmentMetaApplication>
{
public:
	TEST_FIXTURE( BaseDevelopmentMetaApplication )
	{
		TEST_CASE(test_Instanciate_lbMetaApplication)
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

	void test_Instanciate_lbMetaApplication( void )
	{
		puts("test_Instanciate_lbMetaApplication");
		lbErrCodes err = ERR_NONE;

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, m)

		ASSERT_EQUALS( true, m != NULL );
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
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_setUser)
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_setDB)
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest_failure)
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest)
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_createTable_SQLSERVER_UnitTest)
		TEST_CASE(test_Instanciate_lbDatabase_SQLSERVER_listTables)

		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_setUser)
		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_setDB)
		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest_failure)
		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest)
		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_createTable_PostgreSQL_UnitTest)
		TEST_CASE(test_Instanciate_lbDatabase_PostgreSQL_listTables)
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

	void test_Instanciate_lbDatabase_PostgreSQL_setUser( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_setUser");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setUser(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setUser("lala"));
	}

	void test_Instanciate_lbDatabase_PostgreSQL_setDB( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_setDB");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setDB(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setDB("lala"));
	}

	void test_Instanciate_lbDatabase_PostgreSQL_listTables( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_listTables");
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

	void test_Instanciate_lbDatabase_PostgreSQL_createTable_PostgreSQL_UnitTest( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_createTable_PostgreSQL_UnitTest");
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

		ASSERT_EQUALS( ERR_NONE, query->query(
			"DROP TABLE test"
			, false));

		db->close();
	}

	void test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest_failure( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest_failure");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_DB_CONNECT, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trallala"));

		db->close();
	}

	void test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest( void )
	{
		puts("test_Instanciate_lbDatabase_PostgreSQL_login_PostgreSQL_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestPostgreSQL", "UnitTestPostgreSQL", "dba", "trainres"));

		db->close();
	}


	void test_Instanciate_lbDatabase_SQLSERVER_setUser( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_setUser");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setUser(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setUser("lala"));
	}

	void test_Instanciate_lbDatabase_SQLSERVER_setDB( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_setDB");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_ILLEGAL_PARAMETER, db->setDB(NULL));
		ASSERT_EQUALS( ERR_NONE, db->setDB("lala"));
	}

	void test_Instanciate_lbDatabase_SQLSERVER_listTables( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_listTables");
		lbErrCodes err = ERR_NONE;
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestSQLSERVER", 0);

		query->query(
			"CREATE TABLE [dbo].[test] ("
			"	id int identity(1,1) NOT NULL,"
			"	Name nchar(100)"
			")");

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

		UAP(lb_I_Parameter, param)
		UAP_REQUEST(getModuleInstance(), lb_I_String, tableName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Unknown, uk)
		uk = tables->getElementAt(1);
		QI(uk, lb_I_Parameter, param)
		
		*name = "TableName";
		param->getUAPString(*&name, *&tableName);

		query->query("DROP TABLE [dbo].[test]");

		ASSERT_EQUALS( 1, count);
		ASSERT_EQUALS( "test", tableName->charrep());

		db->close();
	}

	void test_Instanciate_lbDatabase_SQLSERVER_createTable_SQLSERVER_UnitTest( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_createTable_SQLSERVER_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		UAP(lb_I_Query, query)

		query = db->getQuery("UnitTestSQLSERVER", 0);

		ASSERT_EQUALS( true, query != NULL);

		ASSERT_EQUALS( ERR_NONE, query->query(
			"CREATE TABLE [dbo].[test] ("
			"	id int identity(1,1) NOT NULL,"
			"	Name nchar(100)"
			")"
			, false));

		ASSERT_EQUALS( ERR_NONE, query->query(
			"DROP TABLE [dbo].[test]"
			, false));

		db->close();
	}

	void test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest_failure( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest_failure");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_DB_CONNECT, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trallala"));

		db->close();
	}

	void test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest( void )
	{
		puts("test_Instanciate_lbDatabase_SQLSERVER_login_SQLSERVER_UnitTest");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );

		ASSERT_EQUALS( ERR_NONE, db->connect("UnitTestSQLSERVER", "UnitTestSQLSERVER", "dba", "trainres"));

		db->close();
	}

	void test_Instanciate_lbDatabase( void )
	{
		puts("test_Instanciate_lbDatabase");
		UAP_REQUEST(getModuleInstance(), lb_I_Database, db)

		ASSERT_EQUALS( true, db.getPtr() != NULL );
	}


	bool LoadSettings()
	{
		return true;
	}
};








REGISTER_FIXTURE( BaseDevelopmentLogger );
REGISTER_FIXTURE( BaseDevelopmentString );
REGISTER_FIXTURE( BaseDevelopmentMetaApplication );
REGISTER_FIXTURE( BaseDevelopmentDatabase );

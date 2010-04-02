#include "../MiniCppUnit/MiniCppUnit.hxx"

#include <lbConfigHook.h>

#define DONT_USE_LBDMF_EXCEPTIONS

void sig_handler(int signr) {
#ifdef __MINGW__
#endif
#ifdef LINUX
	switch (signr) {
		case SIGSEGV:
			FAIL("SIGSEGV happened.");
			break;
		case SIGBUS:
			FAIL("SIGBUS happened.");
			break;
		default:
			break;
	}
#endif
}

class BaseDevelopment : public TestFixture<BaseDevelopment>
  {
  public:
      TEST_FIXTURE( BaseDevelopment )
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
		  puts("test_lbString_setDataNULL");
		  UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		  
		  s->setData((char*) NULL);
		  
		  ASSERT_EQUALS( true, s->charrep() != NULL );
		  ASSERT_EQUALS( true, *s == "" );
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

REGISTER_FIXTURE( BaseDevelopment );


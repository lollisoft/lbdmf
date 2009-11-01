#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "strtest.h"


class StringTest_impl : virtual public StringTest_skel
{
public:
  StringTest_impl()
  {
  };
  void m1( const char* s )
  {
    cout << "m1(): " << s << endl;
  };
  void m2( char*& s )
  {
    s = CORBA::string_dup( "Hallo" );
  };
  void m3( const char* s )
  {
    cout << "m3(): " << s << endl;
  };
  char *m4( char*& s )
  {
    cout << "m4(): " << s << endl;
    CORBA::String_var tmp = s; // Consume old string
    s = CORBA::string_dup( "abc" );
    return CORBA::string_dup( "def" );
  };
  char *m5( char*& s )
  {
    s = CORBA::string_dup( "abc" );
    return CORBA::string_dup( "def" );
  };
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  StringTest_impl* server = new StringTest_impl;
  CORBA::String_var ref = orb->object_to_string( server );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( ref );
#endif
  StringTest_var client = StringTest::_narrow( obj );

  client->m1( "Hallo" );
  
  CORBA::String_var s;
  client->m2( s.out() );
  cout << "Result is " << s.in() << endl;

  client->m3( "1234567" );

  CORBA::String_var res;
  char *in_out = CORBA::string_dup( "xyz" );
  
  res = client->m4( in_out );
  cout << res.in() << endl;
  cout << in_out << endl << endl;
  CORBA::string_free( in_out );
  
  CORBA::String_var out;
  res = client->m5( out.out() );
  cout << res.in() << endl;
  cout << out.in() << endl;
  CORBA::release( server );
}

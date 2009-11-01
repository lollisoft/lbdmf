#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "typedef.h"


class foo_impl : virtual public foo_skel
{
public:
  foo_impl()
  {
  };
  void bar1( const char* s )
  {
    cout << s << endl << endl;
  };
  void bar2( L l )
  {
    cout << l << endl << endl;
  };
  void bar3( const S& s )
  {
    cout << s.a << endl;
    cout << s.b << endl;
  };
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  foo_impl* server = new foo_impl;
  CORBA::String_var ref = orb->object_to_string( server );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( ref );
#endif
  foo_var client = foo::_narrow( obj );

  client->bar1( "Hallo" );
  client->bar2( 100 );

  foo::S fooS;
  fooS.a = 100;
  fooS.b = 'A';
  client->bar3( fooS );
  CORBA::release( server );
}

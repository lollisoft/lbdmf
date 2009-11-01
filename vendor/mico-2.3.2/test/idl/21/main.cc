#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "union.h"


class foo_impl : virtual public foo_skel
{
public:
  foo_impl()
  {
  };
  void bar( const U& v1, U*& v2, U2& v3 )
  {
    if( v1._d() == 3 )
      cout << v1.z() << endl;
    v2 = new U;
    v2->x( 1234 );
    v3.y( 42 );
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

  U v1;
  U_var v2;
  U2 v3;

  v1.z( (const char *) "Hello" );

  client->bar( v1, v2, v3 );

  if( v2->_d() == 1 )
    cout << v2->x() << endl;
  if( v3._d() == B )
    cout << v3.y() << endl;

  CORBA::release( server );
}

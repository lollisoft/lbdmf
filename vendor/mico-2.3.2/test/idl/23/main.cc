#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "a.h"


class foo_impl : virtual public A::foo_skel
{
public:
  foo_impl()
  {
  };
  void bar( const A::BSSeq& s )
  {
    for( CORBA::ULong i = 0; i < s.length(); i++ )
      cout << i << ": " << s[ i ].x << endl;
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
  A::foo_var client = A::foo::_narrow( obj );

  A::BSSeq s;
  s.length( 3 );
  s[ 0 ].x = 33;
  s[ 1 ].x = 22;
  s[ 2 ].x = 11;

  client->bar( s );

  CORBA::release( server );
}

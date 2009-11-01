#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "recursion.h"


class foo_impl : virtual public foo_skel
{
public:
  foo_impl()
  {
  };
  void bar( const S& s )
  {
    print_S( s, 0 );
  };
  void print_S( const S& s, int indent )
  {
    for( int i = 0; i < indent; i++ )
      cout << " ";
    cout << s.name.in() << endl;
    indent += 2;
    if( s.left.length() == 1 )
      print_S( s.left[ 0 ], indent );
    if( s.right.length() == 1 )
      print_S( s.right[ 0 ], indent );
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
  
  S s, s_left;

  s_left.name = (const char *) "Child left";
  
  s.name = (const char *) "Root";
  s.left.length( 1 );
  s.left[ 0 ] = s_left;
  
  client->bar( s );

  CORBA::release( server );
}

#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "objref.h"


class foo_impl : virtual public foo_skel
{
public:
  foo_impl()
  {
  };
  void hello( const char * s )
  {
    cout << "Hello " << s << endl;
  };
};


class bar_impl : virtual public bar_skel
{
public:
  bar_impl()
  {
  };
  foo_ptr run( foo_ptr obj )
  {
    obj->hello( "Sima" );
    return foo::_duplicate( obj );
  };
  void run1( ObjectAlias_ptr obj )
  {
    foo_var f = foo::_narrow( obj );
    assert( !CORBA::is_nil( f ) );
    f->hello( "Sima 2" );
  };
  void run2( const S& s )
  {
    cout << s.x << endl;
    s.obj->hello( "World" );
  };
  void run3( const fooSeq& seq )
  {
    for( int i = 0; i < seq.length(); i++ ) {
      cout << "[" << i << "]" << endl;
      seq[ i ]->hello( "Berkeley" );
    }
  }
};


int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  foo_impl* foo_obj = new foo_impl;
  bar_impl* bar_obj = new bar_impl;
  
  CORBA::String_var foo_ref = orb->object_to_string( foo_obj );
  CORBA::String_var bar_ref = orb->object_to_string( bar_obj );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( foo_ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( foo_ref );
#endif
  foo_var foo_client = foo::_narrow( obj );

#ifdef FORCE_MARSHALLING
  obj = new CORBA::Object( new CORBA::IOR( bar_ref ) );
#else
  obj = orb->string_to_object( bar_ref );
#endif
  bar_var bar_client = bar::_narrow( obj );

  foo_var res = bar_client->run( foo_client );
  res->hello( "Test" );

  bar_client->run1( foo_client );
  
  S s;
  s.x = 42;
  s.obj = foo_client;
  bar_client->run2( s );

  fooSeq seq;
  seq.length( 2 );
  seq[ 0 ] = foo_client;
  seq[ 1 ] = foo_client;
  bar_client->run3( seq );
  CORBA::release( foo_obj );
  CORBA::release( bar_obj );
}

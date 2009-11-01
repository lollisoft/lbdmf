#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "attribute.h"


class foo_impl : virtual public foo_skel
{
private:
  CORBA::Long a1;
  CORBA::Char a2;
  
public:
  foo_impl()
  {
    a1 = 4711;
  };
  CORBA::Long attr1()
  {
    return a1;
  };
  CORBA::Char attr2()
  {
    return a2;
  }
  void attr2( CORBA::Char c )
  {
    a2 = c;
  }
};


int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  foo_impl* foo_obj = new foo_impl;
  
  CORBA::String_var foo_ref = orb->object_to_string( foo_obj );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( foo_ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( foo_ref );
#endif
  foo_var foo_client = foo::_narrow( obj );

  cout << foo_client->attr1() << endl;
  foo_client->attr2( 'C' );
  cout << foo_client->attr2() << endl;
  CORBA::release( foo_obj );
}

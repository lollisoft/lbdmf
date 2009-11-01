#define FORCE_MARSHALLING

#include <iostream.h>

// These #includes need to be done manually if
// MICO_NO_TOPLEVEL_MODULES is defined
#include <CORBA-SMALL.h>
#include <mico/template_impl.h>



#define MICO_NO_TOPLEVEL_MODULES

// Get module M
#define MICO_MODULE_M
MICO_NAMESPACE_DECL M {
  #include "module.h"
};
#undef MICO_MODULE_M

// Get module M2
#define MICO_MODULE_M2
MICO_NAMESPACE_DECL M2 {
  #include "module.h"
};
#undef MICO_MODULE_M2

// Get global definitions in module.h
#define MICO_MODULE__GLOBAL
#include "module.h"
#undef MICO_MODULE__GLOBAL
#undef MICO_NO_TOPLEVEL_MODULES



class foo_impl : virtual public M::foo_skel
{
public:
  foo_impl()
  {
  };
  void bar( E e )
  {
    cout << e << endl << endl;
  };
};


class foo2_impl : virtual public M2::foo_skel
{
public:
  foo2_impl()
  {
  };
  void bar( M::foo::E e )
  {
    cout << e << endl << endl;
  };
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  foo_impl* server = new foo_impl;
  foo2_impl* server2 = new foo2_impl;
  
  CORBA::String_var ref = orb->object_to_string( server );
  CORBA::String_var ref2 = orb->object_to_string( server2 );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( ref );
#endif
  M::foo_var client = M::foo::_narrow( obj );

#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj2 = new CORBA::Object( new CORBA::IOR( ref2 ) );
#else
  CORBA::Object_var obj2 = orb->string_to_object( ref2 );
#endif
  M2::foo_var client2 = M2::foo::_narrow( obj2 );

  client->bar( M::foo::B );
  client2->bar( M::foo::C );
  CORBA::release( server );
  CORBA::release( server2 );
}

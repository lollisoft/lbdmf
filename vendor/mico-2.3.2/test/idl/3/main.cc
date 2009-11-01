#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "calc.h"


class Calc_impl : virtual public Calc_skel
{
public:
  Calc_impl()
  {
  };
  void add( CORBA::Short x, CORBA::Short y, CORBA::Long& z )
  {
    z = x + y;
  };
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  Calc_impl* server = new Calc_impl;
  CORBA::String_var ref = orb->object_to_string( server );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( ref );
#endif
  Calc_var client = Calc::_narrow( obj );

  CORBA::Long a;
  client->add( 3, 4, a );
  cout << "Sum is " << a << endl;
  CORBA::release( server );
}

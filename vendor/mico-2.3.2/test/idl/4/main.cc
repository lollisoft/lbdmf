#define FORCE_MARSHALLING

#include <CORBA-SMALL.h>
#include "calc.h"


class Calc_impl : virtual public Calc_skel
{
private:
  CORBA::Long _total;

public:
  Calc_impl()
  {
    _total = 0;
  };
  void add( CORBA::Long x )
  {
    _total += x;
  };
  CORBA::Long total()
  {
    return _total;
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
  client->add( 3 );
  client->add( 4 );

  CORBA::Long z;
  z = client->total();
  cout << "Sum is " << z << endl;
  CORBA::release( server );
}

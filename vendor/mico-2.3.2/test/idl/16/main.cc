#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "forward.h"


class A_impl : virtual public A_skel
{
private:
  int counter;
public:
  A_impl()
  {
    counter = 0;
  };
  void op( B_ptr b )
  {
    cout << "A::op() [" << counter++ << "]" << endl;
    if( counter < 3 )
      //XXX b->op( _this() );
      b->op( A::_duplicate( this ) );
  };
};


class B_impl : virtual public B_skel
{
private:
  int counter;
public:
  B_impl()
  {
    counter = 0;
  };
  void op( A_ptr a )
  {
    cout << "B::op() [" << counter++ << "]" << endl;
    if( counter < 3 )
      //XXX a->op( _this() );
      a->op( B::_duplicate( this ) );
  };
};


int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  A_impl* a_obj = new A_impl;
  B_impl* b_obj = new B_impl;
  
  CORBA::String_var a_ref = orb->object_to_string( a_obj );
  CORBA::String_var b_ref = orb->object_to_string( b_obj );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( a_ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( a_ref );
#endif
  A_var a_client = A::_narrow( obj );

#ifdef FORCE_MARSHALLING
  obj = new CORBA::Object( new CORBA::IOR( b_ref ) );
#else
  obj = orb->string_to_object( b_ref );
#endif
  B_var b_client = B::_narrow( obj );

  a_client->op( b_client );
  //b_client->op( a_client );
  
  CORBA::release( a_obj );
  CORBA::release( b_obj );
}

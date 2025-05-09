#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "new-types.h"
#include <mico/util.h>


class A_impl : virtual public A_skel
{
public:
  A_impl()
  {
  };
  CORBA::LongDouble m1( CORBA::LongDouble x,
			CORBA::LongDouble &y,
			CORBA::LongDouble &z )
  {
    y = x + z;
    z = y;
    return z;
  };
  Fixed m2( Fixed x, Fixed& y, Fixed& z )
  {
    y = x + z;
    z = y;
    return z;
  }
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  A_impl* server = new A_impl;
  CORBA::String_var ref = orb->object_to_string( server );
  
  //----------------------------------------------------------------
  
  // client side
#ifdef FORCE_MARSHALLING
  CORBA::Object_var obj = new CORBA::Object( new CORBA::IOR( ref ) );
#else
  CORBA::Object_var obj = orb->string_to_object( ref );
#endif
  A_var client = A::_narrow( obj );

  CORBA::LongDouble lx, ly, lz, lr;
  lx = 1;
  lz = 2;
  lr = client->m1( lx, ly, lz );
  cout << ly << endl;
  cout << lz << endl;
  cout << lr << endl;
  
  A::Fixed fx, fy, fz, fr;
  fx = (CORBA::LongDouble) 1;
  fz = (CORBA::LongDouble) 2;
  fr = client->m2( fx, fy, fz );
  cout << fy << endl;
  cout << fz << endl;
  cout << fr << endl;
  
  CORBA::release( server );

  cout << "---------------------" << endl;
  cout << wide_c << endl;
  for( size_t i = 0; i < xwcslen( wide_s ); i++ )
    cout << wide_s[ i ] << " ";
  cout << endl;
  cout << f1 << endl;
  cout << f2 << endl;
  cout << l << endl;
  cout << ll << endl;
  cout << ull << endl;

  CORBA::Any a;
  S s1, s2;
  s1.m1 = L'A';
  s1.m2 = CORBA::wstring_dup( L"abc" );
  s1.m3 = CORBA::wstring_dup( L"def" );
  s1.m4 = FixedTmpl<5,2>( (CORBA::LongDouble) 123.45 );
  s1.m5 = 1;
  s1.m6 = 2;
  s1.m7 = 3;
  a <<= s1;
  a >>= s2;
  assert( s1.m1 == s2.m1 );
  assert( s1.m2 == s2.m2 );
  assert( s1.m3 == s2.m3 );
  assert( s1.m4 == s2.m4 );
  assert( s1.m5 == s2.m5 );
  assert( s1.m6 == s2.m6 );
  assert( s1.m7 == s2.m7 );
}

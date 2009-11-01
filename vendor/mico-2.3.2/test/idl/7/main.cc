#define FORCE_MARSHALLING

#include <iostream.h>
#include <CORBA-SMALL.h>
#include "struct.h"


class foo_impl : virtual public foo_skel
{
public:
  foo_impl()
  {
  };
  S bar( const S& s1, S& s2, S& s3 )
  {
    cout << s1.a << endl;
    cout << s1.b << endl;
    cout << s1.c << endl << endl;

    cout << s3.a << endl;
    cout << s3.b << endl;
    cout << s3.c << endl << endl;

    s2 = s3;
    s3 = s1;
    return s1;
  };
  S2 *bar1( const S2& s1, S2*& s2, S2& s3 )
  {
    cout << s1.a.in() << endl;
    cout << s1.x.a << endl;
    cout << s1.x.b << endl;
    cout << s1.x.c << endl << endl;

    cout << s3.a.in() << endl;
    cout << s3.x.a << endl;
    cout << s3.x.b << endl;
    cout << s3.x.c << endl << endl;

    s2 = new S2;
    *s2 = s3;
    s3 = s1;

    S2* res = new S2;
    *res = s1;
    return res;
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
  
  {
    S s1;
    S s2;
    S s3;
    S res;
    
    s1.a = 47;
    s1.b = 11;
    s1.c = 'S';
    
    s3.a = 58;
    s3.b = 22;
    s3.c = 'T';
    
    res = client->bar( s1, s2, s3 );

    cout << s2.a << endl;
    cout << s2.b << endl;
    cout << s2.c << endl << endl;

    cout << s3.a << endl;
    cout << s3.b << endl;
    cout << s3.c << endl << endl;
    cout << res.a << endl;
    cout << res.b << endl;
    cout << res.c << endl << endl;
  }
  
  {
    S2     s1;
    S2_var s2;
    S2     s3;
    S2_var res;
    
    s1.a = (const char *) "Hallo";
    s1.x.a = 47;
    s1.x.b = 11;
    s1.x.c = 'S';
    
    s3.a = (const char *) "Test";
    s3.x.a = 58;
    s3.x.b = 22;
    s3.x.c = 'T';
    
    res = client->bar1( s1, s2, s3 );

    cout << s2->a.in() << endl;
    cout << s2->x.a << endl;
    cout << s2->x.b << endl;
    cout << s2->x.c << endl << endl;

    cout << s3.a.in() << endl;
    cout << s3.x.a << endl;
    cout << s3.x.b << endl;
    cout << s3.x.c << endl << endl;

    cout << res->a.in() << endl;
    cout << res->x.a << endl;
    cout << res->x.b << endl;
    cout << res->x.c << endl << endl;
  }
  CORBA::release( server );
}

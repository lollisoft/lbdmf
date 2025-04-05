#include <CORBA-SMALL.h>
#include "account.h"


class Account_impl : virtual public Account_skel
{
private:
  CORBA::Long _current_balance;

public:
  Account_impl()
  {
    _current_balance = 0;
  };
  void deposit( CORBA::ULong amount )
  {
    _current_balance += amount;
  };
  void withdraw( CORBA::ULong amount )
  {
    _current_balance -= amount;
  };
  CORBA::Long balance()
  {
    return _current_balance;
  };
};



int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );

  // server side
  Account_impl* server = new Account_impl;
  CORBA::String_var ref = orb->object_to_string( server );
  cout << "Server reference: " << ref.in() << endl;
  
  //----------------------------------------------------------------------
  
  // client side
  CORBA::Object_var obj = orb->string_to_object( ref );
  Account_var client = Account::_narrow( obj );

  client->deposit( 700 );
  client->withdraw( 250 );
  cout << "Balance is " << client->balance() << endl;

  // We don't need the server object any more. This code belongs
  // to the server implementation
  CORBA::release( server );
  return 0;
}

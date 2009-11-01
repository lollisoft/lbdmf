#include <CORBA-SMALL.h>
#include "account.h"
#include <mico/CosNaming.h>

int main( int argc, char *argv[] )
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  CORBA::Object_var nobj =
    orb->resolve_initial_references ("NameService");
  assert (! CORBA::is_nil (nobj));
  
  CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow (nobj);
  CosNaming::Name name;
  name.length (1);
  name[0].id = CORBA::string_dup ("myAccount");
  name[0].kind = CORBA::string_dup ("");
  
  CORBA::Object_var obj;

#ifdef HAVE_EXCEPTIONS
  try {
    obj = nc->resolve (name);
  }
  catch (CosNaming::NamingContext::NotFound_catch &exc) {
    cerr << "NotFound exception" << endl;
  }
  catch (CosNaming::NamingContext::CannotProceed_catch &exc) {
    cerr << "CannotProceed exception" << endl;
  }
  catch (CosNaming::NamingContext::InvalidName_catch &exc) {
    cerr << "InvalidName exception" << endl;
  }
#else
  obj = nc->resolve (name);
#endif
  Account_var client = Account::_narrow( obj );

  client->deposit( 100 );
  client->deposit( 100 );
  client->deposit( 100 );
  client->deposit( 100 );
  client->deposit( 100 );
  client->withdraw( 240 );
  client->withdraw( 10 );
  cout << "Balance is " << client->balance() << endl;
  
  return 0;
}

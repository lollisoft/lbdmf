#include <CORBA-SMALL.h>
#include <mico/CosNaming.h>
#include <mico/PropertyService.h>

#include "bank.h"

void show_any (const CORBA::Any& a)  /* more Infos: MICO-Doc., chapter 5.2 */
{
  char *str;
  Bank::Account account;

  if (a >>= str) {
    cout << "(Any's type: char *)" << endl;
    cout << "    " << str << endl;
  }

  if (a >>= account) {
    cout << "(Any's type: Bank::Account)" << endl;
    cout << "    first_name: " << account.first_name << endl;
    cout << "          name: " << account.name << endl;
    cout << "       balance: " << account.balance << endl;
  }
}

int main(int argc, char *argv [])
{

  /*
   * ORB initialization
   */

  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  /*
   * Use the NameService to bind the CartoonsPropertySet
   */

  CORBA::Object_var nobj =
    orb->resolve_initial_references ("NameService");
  assert (! CORBA::is_nil (nobj));
  
  CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow (nobj);
  CosNaming::Name name;
  name.length (1);
  name[0].id = CORBA::string_dup ("CartoonsPropertySet");
  name[0].kind = CORBA::string_dup ("");
  
  CORBA::Object_var obj;

#ifdef HAVE_EXCEPTIONS
  try {
    obj = nc->resolve (name);
  } catch (...) {
      cerr << "NameService raised exception!" << endl;
      exit (1);
  }          
#else
  obj = nc->resolve (name);
#endif

  PropertyService::PropertySet_var cartoons_property_set =
      PropertyService::PropertySet::_narrow (obj);
 
  /*
   * Get number of Properties.
   */

  CORBA::ULong number = cartoons_property_set->get_number_of_properties ();

  cout << "Number of defined Properties: " << number << endl;

  /*
   * Get all Properties.
   */

  PropertyService::Properties_var properties;
  PropertyService::PropertiesIterator_var iterator;

  cartoons_property_set->get_all_properties ((CORBA::ULong) 10, properties,
                                             iterator);

  for (CORBA::ULong i=0; i < number; i++) {
    cout << i+1 << ". " << properties[i].property_name << ": ";
    show_any (properties[i].property_value);
  }

  return 0;
}

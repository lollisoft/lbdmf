#include "abstract.h"
#include "abstract_impl.h"

class Example_impl :
  virtual public POA_Example,
  virtual public PortableServer::RefCountServantBase
{
public:
  void display (Describable_ptr);
};

void
Example_impl::display (Describable_ptr d)
{
  CORBA::String_var s = d->get_description ();
  cout << s << endl;
}

class Account_impl :
  virtual public POA_Account,
  virtual public PortableServer::RefCountServantBase
{
public:
  char * get_description ();
};

char *
Account_impl::get_description ()
{
  return CORBA::string_dup ("Account");
}

int
main (int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");

  /*
   * Register factories.
   */

  CORBA::ValueFactoryBase_var vf = new Currency_Factory;
  orb->register_value_factory ("IDL:Currency:1.0", vf);

  /*
   * Initialize POA
   */

  CORBA::Object_var po = orb->resolve_initial_references ("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow (po);
  PortableServer::POAManager_var mgr = poa->the_POAManager ();

  /*
   * Activate the two servers
   */

  PortableServer::ServantBase_var s1 = new Account_impl;
  PortableServer::ServantBase_var s2 = new Example_impl;
  CORBA::Object_var o1 = s1->_this ();
  CORBA::Object_var o2 = s2->_this ();

  mgr->activate ();
  orb->run ();

  /*
   * Shutdown (never reached)
   */

  poa->destroy (TRUE, TRUE);
  return 0;
}

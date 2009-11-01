#include "custom_impl.h"

CORBA::Long
CustomValue_impl::value ()
{
  return 42;
}

void
CustomValue_impl::marshal (CORBA::DataOutputStream * os)
{
  cout << "custom marshaller" << endl;
  os->write_boolean (TRUE);
  os->write_short (42);
  os->write_string ("Hello World");
}

CORBA::ValueBase *
CustomValue_impl::unmarshal (CORBA::DataInputStream * is)
{
  cout << "custom unmarshaller" << endl;
  CORBA::Boolean b = is->read_boolean ();
  CORBA::Short s = is->read_short ();
  CORBA::String_var v = is->read_string ();
  assert (b == TRUE && s == 42 && strcmp (v.in(), "Hello World") == 0);
  return this;
}


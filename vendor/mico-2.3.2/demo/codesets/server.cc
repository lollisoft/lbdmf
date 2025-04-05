#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include "hello.h"

class Hello_impl : virtual public Hello_skel {
public:
    char *hello (const char *s)
    {
	cout << s << endl;
	return CORBA::string_dup (s);
    }
};

int
main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new Hello_impl;

    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    orb->run ();
    return 0;
}

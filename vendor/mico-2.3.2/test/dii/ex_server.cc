#include <CORBA.h>
#include <unistd.h>
#include <signal.h>
#include "ex.h"
#include <iostream.h>

class SomeIface_impl : virtual public SomeIface_skel {
public:
    void f ()
    {
	SomeExcept ex;
	ex.msg = (const char *)"foobar";
	mico_throw (ex);
    }
};

int main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new SomeIface_impl;
    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    orb->run ();
    return 0;
}

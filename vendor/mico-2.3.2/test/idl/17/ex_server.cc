#include <CORBA.h>
#include <unistd.h>
#include <signal.h>
#include "ex.h"
#include <iostream.h>

class Calc_impl : virtual public Calc_skel {
public:
    void m ()
    {
	ex1 ex;
	ex.msg = (const char *)"foobar";
	mico_throw (ex);
    }
};

int main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new Calc_impl;
    boa->impl_is_ready (0);
    orb->run ();
    return 0;
}

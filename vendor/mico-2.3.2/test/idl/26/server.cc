#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <unistd.h>
#include <signal.h>
#include <iostream.h>

#include "base_impl.h"

int main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new base_impl;
    boa->impl_is_ready (0);
    orb->run ();
    return 0;
}

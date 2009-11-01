#include <iostream.h>

#include <CORBA-SMALL.h>
#include "derived_impl.h"

int main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    assert (argc == 2);
    CORBA::Object_var obj = orb->bind ("IDL:base:1.0", argv[1]);
    assert( !CORBA::is_nil( obj ) );
    base_var client = base::_narrow (obj);
    assert( !CORBA::is_nil( client ) );
    derived_var test = new derived_impl;
    client->m( test );
    base_var ret_base = client->m();
    assert( !CORBA::is_nil( ret_base ) );
    derived_var ret_derived = derived::_narrow( ret_base );
    assert( !CORBA::is_nil( ret_derived ) );
}

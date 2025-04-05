#include <CORBA-SMALL.h>
#include "hello.h"

int main( int argc, char *argv[] )
{
    // ORB initialization
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    // client side
    assert (argc == 2);
    CORBA::Object_var obj = orb->bind ("IDL:Hello:1.0", argv[1]);
    assert (!CORBA::is_nil (obj));
    Hello_var client = Hello::_narrow( obj );

    client->hello ("hello");
#ifndef PERMETHOD
    client->exit();
#endif

    return 0;
}

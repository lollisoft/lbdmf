#include "ex.h"
#include <iostream.h>

int main (int argc, char *argv[])
{
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    assert (argc == 2);
    CORBA::Object_var obj = orb->bind ("IDL:Calc:1.0", argv[1]);
    Calc_var client = Calc::_narrow (obj);

    try {
	client->m();
    } catch (Calc::ex1_catch &ex) {
	cout << "ex1: " << ex->msg.in() << endl;
    }
    return 0;
}

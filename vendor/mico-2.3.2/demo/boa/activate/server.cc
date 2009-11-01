#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>
#include "hello.h"

/*
 * Account implementation
 */

class Hello_impl : virtual public Hello_skel {
public:
    Hello_impl ()
    {
    }

    void exit ()
    {
        CORBA::BOA_var boa = _boa();
        CORBA::ORB_var orb = _orb();
	/*
	 * beware: while calling deactivate_impl() we can get
	 * recursive invocations to the Account methods ...
  	 */
#ifdef SHARED
        boa->deactivate_impl (CORBA::ImplementationDef::_nil());
#else
	boa->deactivate_obj (0);
#endif
	orb->shutdown (TRUE);
    }

    void hello (const char *s)
    {
       cout << s << endl;
    }
};

int main( int argc, char *argv[] )
{
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");
    
    (void)new Hello_impl;

#ifdef SHARED
    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
#else
    boa->obj_is_ready (0, 0);
#endif
    orb->run ();
    cout << "shutdown" << endl;

    return 0;
}

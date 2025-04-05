/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#define MICO_CONF_IMR
#define MICO_CONF_INTERCEPT
#include <CORBA-SMALL.h>
#include <iostream.h>
#include "hello.h"

CORBA::ORB_var the_orb;
CORBA::BOA_var the_boa;

class Hello_impl : virtual public Hello_skel {
public:
    void hello ()
    {
	CORBA::BOA_var boa = _boa();
	CORBA::Principal_var princ =
	    boa->get_principal (this, CORBA::Environment::_nil());

	char *s;
	CORBA::Any_var a;

	a = princ->get_property ("auth-method");
	a >>= s;
	cout << "authentication method: " << s << endl;

	a = princ->get_property ("peer-address");
	a >>= s;
	cout << "peer address: " << s << endl;

	a = princ->get_property ("ssl-cipher");
	a >>= s;
	cout << "cipher: " << s << endl;

	a = princ->get_property ("ssl-x509-issuer");
	a >>= s;
	cout << "issuer: " << s << endl;

	a = princ->get_property ("ssl-x509-subject");
	a >>= s;
	cout << "subject: " << s << endl;

	// ... or, to get individual fields of X509 names:

	a = princ->get_property ("ssl-x509-subject:CN");
	a >>= s;
	cout << "subject's name: " << s << endl;

	a = princ->get_property ("ssl-x509-subject:Email");
	a >>= s;
	cout << "subject's email: " << s << endl;
    }
};

/*
 * a simple access checker using interceptors.
 */
class AccessChecker : public Interceptor::ServerInterceptor {
public:
    Interceptor::Status
    initialize_request (Interceptor::LWServerRequest_ptr req,
			CORBA::Environment_ptr env)
    {
	CORBA::Object_var obj = req->target ();
	CORBA::Principal_var p = the_boa->get_principal (obj, env);

	CORBA::Any_var a = p->get_property ("ssl-x509-subject:CN");
	char *name;

	/*
	 * try changing "Roemer" to some other name to verify that
	 * the access check works ...
	 */
	if (!(a >>= name) || strcmp (name, "Roemer")) {
	    // permission denied ...
	    env->exception (new CORBA::NO_PERMISSION);
	    return Interceptor::INVOKE_ABORT;
	}
	// ok ...
	return Interceptor::INVOKE_CONTINUE;
    }
};

int
main (int argc, char *argv[])
{
    AccessChecker ac;
    ac.activate (0);

    the_orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    the_boa = the_orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new Hello_impl;

    the_boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    the_orb->run ();

    return 0;
}

#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>
#include "account.h"

/*
 * Account implementation
 */

class Account_impl : virtual public Account_skel {
    CORBA::Long _current_balance;
    CORBA::Long _calls;
public:
    Account_impl ()
    {
        _calls = 0;
        _current_balance = 0;
    }

    Account_impl (CORBA::Object_ptr obj)
        : Account_skel (obj)
    {
        cout << "restoring id " << obj->_ident() << endl;
        _calls = 0;
        ifstream inp (obj->_ident());
        assert (inp);
        inp >> _current_balance;
    }

    CORBA::Boolean _save_object ()
    {
        cout << "saving id " << _ident() << endl;
        ofstream out (_ident());
        assert (out);
        out << _current_balance;
	return TRUE;
    }

    CORBA::ImplementationDef_ptr find_impl (const char *name)
    {
	CORBA::Object_var obj =
	    _orbnc()->resolve_initial_references ("ImplementationRepository");
	assert (!CORBA::is_nil (obj));

	CORBA::ImplRepository_var imr = CORBA::ImplRepository::_narrow (obj);
	assert (!CORBA::is_nil (imr));

	CORBA::ImplRepository::ImplDefSeq_var impls = imr->find_by_name (name);
	assert (impls->length() > 0);
	return CORBA::ImplementationDef::_duplicate (impls[(CORBA::ULong)0]);
    }

    void check_exit ()
    {
        if (++_calls == 3) {
            CORBA::BOA_var boa = _boa();
            CORBA::ORB_var orb = _orb();

	    const char *newname = !strcmp (boa->impl_name(), "Account1")
		? "Account2" : "Account1";
	    CORBA::ImplementationDef_var impl = find_impl (newname);
	    /*
	     * beware: while calling change_implementation() we can get
	     * recursive invocations to the Account methods ...
	     */
            boa->change_implementation (this, impl);
	    /*
	     * now there is no object left in this implementation
	     */
	    boa->deactivate_impl (CORBA::ImplementationDef::_nil());
	    orb->shutdown (TRUE);
        }
    }
  
    void deposit( CORBA::ULong amount )
    {
        _current_balance += amount;
        check_exit ();
    }

    void withdraw( CORBA::ULong amount )
    {
        _current_balance -= amount;
        check_exit ();
    }
    
    CORBA::Long balance()
    {
        check_exit ();
        return _current_balance;
    }
};

/*
 * Account object restorer
 */

class AccountLoader : public CORBA::BOAObjectRestorer {
public:
    CORBA::Boolean restore (CORBA::Object_ptr obj)
    {
        if (!strcmp (obj->_repoid(), "IDL:Account:1.0")) {
            (void)new Account_impl (obj);
            return TRUE;
        }
        cout << "cannot restore " << obj->_repoid() << " objects" << endl;
        return FALSE;
    }
};


int main( int argc, char *argv[] )
{
    AccountLoader loader;
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    if (!boa->restoring() && !strcmp (boa->impl_name(), "Account1")) {
	cout << "creating ... " << endl;
        (void)new Account_impl;
    }
    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    orb->run ();

    return 0;
}

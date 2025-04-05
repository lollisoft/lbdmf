#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>
#include "account.h"

class Account_impl : virtual public Account_skel {
    CORBA::Long _current_balance;
    CORBA::Long _calls;
public:
    Account_impl()
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

    void check_exit ()
    {
        if (++_calls == 5) {
            CORBA::BOA_var boa = _boa();
            CORBA::ORB_var orb = _orb();
	    /*
	     * beware: while calling deactivate_obj() we can get
	     * recursive invocations to the Account methods ...
	     */
            boa->deactivate_obj (this);
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

class Bank_impl : virtual public Bank_skel {
    AccountSeq accounts;
public:
    Bank_impl ()
    {
    }
    Account_ptr create ()
    {
        CORBA::BOA_var boa = _boa();
	CORBA::ORB_var orb = _orb();

	/*
	 * create new account and deactivate to move it to a separate
	 * server.
	 */
        Account_ptr acc = new Account_impl;
        boa->deactivate_obj (acc);

	/*
	 * now create a stub for the object so we can still access
	 * it from within this process (if you do not need access
	 * to the newly created account from within this process
	 * you could just return Account::_duplicate (acc) here).
	 */
	CORBA::String_var ref = orb->object_to_string (acc);
	CORBA::release (acc);
	CORBA::Object_var obj = orb->string_to_object (ref);
	acc = Account::_narrow (obj);
	/*
	 * now acc is a stub for the account object in the other server.
	 * save the stub so we can access it later.
	 */
	accounts.length (accounts.length()+1);
	accounts[accounts.length()-1] = acc;

        return Account::_duplicate (acc);
    }
    void deposit_all_accounts (CORBA::ULong amount)
    {
	for (CORBA::ULong i = 0; i < accounts.length(); ++i)
	    accounts[i]->deposit (amount);
    }
};


class AccountLoader : public CORBA::BOAObjectRestorer {
public:
    CORBA::Boolean restore (CORBA::Object_ptr obj)
    {
        if (!strcmp (obj->_repoid(), "IDL:Account:1.0")) {
            (void)new Account_impl (obj);
            return TRUE;
        }
	/*
	 * Bank objects are transient because _save_object() is not
	 * implementent for them. so we won't be asked to restore them
	 */
        cout << "cannot restore " << obj->_repoid() << " objects" << endl;
        return FALSE;
    }
};


int main( int argc, char *argv[] )
{
    AccountLoader loader;
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    if (!boa->restoring()) {
	cout << "creating ... " << endl;
        Bank *b = new Bank_impl;
	boa->obj_is_ready (b, 0);
    } else {
	boa->obj_is_ready (0, 0);
    }
    orb->run();
    return 0;
}

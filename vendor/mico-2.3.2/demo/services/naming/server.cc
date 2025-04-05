#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <fstream.h>
#include <unistd.h>
#include "account.h"
#include <mico/CosNaming.h>

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
//        cout << "restoring id " << obj->_ident() << endl;
        _calls = 0;
        ifstream inp (obj->_ident());
        assert (inp);
        inp >> _current_balance;
    }

    CORBA::Boolean _save_object ()
    {
//        cout << "saving id " << _ident() << endl;
        ofstream out (_ident());
        assert (out);
        out << _current_balance;
	return TRUE;
    }

    void check_exit ()
    {
        if (++_calls > 5) {
            CORBA::ORB_var orb = _orb();
            CORBA::BOA_var boa = _boa();
	    /*
	     * beware: while calling deactivate_impl() we can get
	     * recursive invocations to the Account methods ...
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
//        cout << "cannot restore " << obj->_repoid() << " objects" << endl;
        return FALSE;
    }
};


int main( int argc, char *argv[] )
{
  AccountLoader loader;
  CORBA::ORB_var orb = CORBA::ORB_init( argc, argv, "mico-local-orb" );
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");
  
  if (!boa->restoring()) {
    cerr << "creating ..." << endl;
    Account_ptr acc = new Account_impl ();

    CORBA::Object_var nsobj =
      orb->resolve_initial_references ("NameService");
    assert (! CORBA::is_nil (nsobj));
  
    CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (nsobj);

    CosNaming::Name name;
    name.length (1);
    name[0].id = CORBA::string_dup ("myAccount");
    name[0].kind = CORBA::string_dup ("");

    cerr << "binding name ..." << endl;
    nc->bind (name, acc);
  }
  boa->impl_is_ready (CORBA::ImplementationDef::_nil());
  orb->run ();

  return 0;
}

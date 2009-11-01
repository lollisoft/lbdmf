#include <CORBA.h>
#include <string.h>
#include <iostream.h>
#include <mico/template_impl.h>

class CalcImpl : public CORBA::DynamicImplementation {
public:
    CalcImpl ();
    virtual void invoke (CORBA::ServerRequest_ptr svreq,
			 CORBA::Environment &env);
    virtual CORBA::Long add (CORBA::Long x, CORBA::Long y);
};

CalcImpl::CalcImpl ()
{
    CORBA::ImplementationDef_var impl = _find_impl ("IDL:Calc:1.0", "Calc");
    assert (!CORBA::is_nil (impl));

    _create_ref (CORBA::BOA::ReferenceData(),
		 CORBA::InterfaceDef::_nil(),
		 impl,
		 "IDL:Calc:1.0");
}

void
CalcImpl::invoke (CORBA::ServerRequest_ptr svreq, CORBA::Environment &env)
{
    if (!strcmp (svreq->op_name(), "add")) {
	// create argument list
	CORBA::NVList_ptr args;
	_orbnc()->create_list (0, args);

	// fill in NamedValue's
	// XXX must set TypeCode's, too ...
	args->add (CORBA::ARG_IN);
	args->add (CORBA::ARG_IN);
	args->add (CORBA::ARG_OUT);

	// get IN param values
	svreq->params (args);

	// get parameters
	CORBA::Long x;
	*args->item(0)->value() >>= x;
	CORBA::Long y;
	*args->item(1)->value() >>= y;

	// call user code
	CORBA::Long z = add (x, y);

	// set result
	*args->item(2)->value() <<= "hello world";
	CORBA::Any *res = new CORBA::Any;
	*res <<= z;
	svreq->result (res);
    }
}

CORBA::Long
CalcImpl::add (CORBA::Long x, CORBA::Long y)
{
    cout << "add " << x << " " << y << endl;
    return x + y;
}

int
main (int argc, char *argv[])
{
    // client side
    CORBA::ORB_ptr orb = CORBA::ORB_init (argc, argv, "mico-local-orb");

    // server side
    CalcImpl impl;

    CORBA::Object_ptr obj = orb->bind ("IDL:Calc:1.0", "local:");
    assert (!CORBA::is_nil (obj));

    CORBA::Request_ptr req = obj->_request ("add");
    req->add_in_arg() <<= (CORBA::Long)1L;
    req->add_in_arg() <<= (CORBA::Long)2L;
    req->add_out_arg ();
    req->invoke ();
    CORBA::Long z;
    *req->result()->value() >>= z;
    cout << "result: " << z << endl;

    char *str;
    *req->arguments()->item(2)->value() >>= str;
    cout << str << endl;

    CORBA::release (req);
    CORBA::release (obj);
    return 0;
}

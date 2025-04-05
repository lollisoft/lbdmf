#include <CORBA.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/template_impl.h>

class CalcImpl : public CORBA::DynamicImplementation {
public:
    CalcImpl ();
    virtual void invoke (CORBA::ServerRequest_ptr svreq,
			 CORBA::Environment &env);
    virtual CORBA::Long add (CORBA::Long x, CORBA::Long y, CORBA::Context_ptr);
};

CalcImpl::CalcImpl ()
{
    CORBA::ImplementationDef_var impl = _find_impl ("IDL:Calc:1.0", "Calc1");
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
	args->item(0)->value()->set_type (CORBA::_tc_long);
	args->add (CORBA::ARG_IN);
	args->item(1)->value()->set_type (CORBA::_tc_long);
	args->add (CORBA::ARG_OUT);
	args->item(2)->value()->set_type (CORBA::_tc_string);

	// get IN param values
	svreq->params (args);

	// get parameters
	CORBA::Long x;
	*args->item(0)->value() >>= x;
	CORBA::Long y;
	*args->item(1)->value() >>= y;

	// call user code
	CORBA::Long z = add (x, y, svreq->ctx());

	// set result
	*args->item(2)->value() <<= "hello world";
	CORBA::Any *res = new CORBA::Any;
	*res <<= z;
	svreq->result (res);
    }
}

CORBA::Long
CalcImpl::add (CORBA::Long x, CORBA::Long y, CORBA::Context_ptr ctx)
{
    CORBA::NVList_var vals;
    ctx->get_values ("", 0, "*", vals);
    for (CORBA::ULong i = 0; i < vals->count(); ++i) {
	char *s;
	CORBA::Boolean r = (*vals->item(i)->value() >>= s);
	assert (r);
	cout << vals->item(i)->name() << ": " << s << endl;
    }
    return x + y;
}

int
main (int argc, char *argv[])
{
    CORBA::ORB_ptr orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_ptr boa = orb->BOA_init (argc, argv, "mico-local-boa");

    (void)new CalcImpl;

    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    orb->run ();
    return 0;
}

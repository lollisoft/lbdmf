#include <CORBA.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/template_impl.h>


// variable length struct
struct SV {
    CORBA::String_var s;
};
typedef TVarVar<SV> SV_var;

class __stc_SV : public CORBA::StaticTypeInfo {
    typedef SV T;
public:
    StaticValueType create () const
    { return (StaticValueType)new T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new T (*(T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(T *)d = *(T *)s; }
    void free (StaticValueType v) const
    { delete (T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	return
	    dc.struct_begin() &&
	    CORBA::_stc_string->demarshal (dc, &((T *)v)->s.inout()) &&
	    dc.struct_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	ec.struct_begin();
	CORBA::_stc_string->marshal (ec, &((T *)v)->s.inout());
	ec.struct_end();
    }
};

CORBA::StaticTypeInfo *_stc_SV = new __stc_SV;



// fixed length struct
struct SF {
    CORBA::Long l;
};
typedef TFixVar<SF> SF_var;

class __stc_SF : public CORBA::StaticTypeInfo {
    typedef SF T;
public:
    StaticValueType create () const
    { return (StaticValueType)new T; }
    StaticValueType copy (const StaticValueType v) const
    { return (StaticValueType)new T (*(T *)v); }
    void assign (StaticValueType d, const StaticValueType s) const
    { *(T *)d = *(T *)s; }
    void free (StaticValueType v) const
    { delete (T *)v; }
    CORBA::Boolean demarshal (CORBA::DataDecoder &dc, StaticValueType v) const
    {
	return
	    dc.struct_begin() &&
	    CORBA::_stc_long->demarshal (dc, &((T *)v)->l) &&
	    dc.struct_end();
    }
    void marshal (CORBA::DataEncoder &ec, StaticValueType v) const
    {
	ec.struct_begin();
	CORBA::_stc_long->marshal (ec, &((T *)v)->l);
	ec.struct_end();
    }
};

CORBA::StaticTypeInfo *_stc_SF = new __stc_SF;




class CalcImpl : public CORBA::StaticImplementation {
public:
    CalcImpl ();
    virtual void invoke (CORBA::StaticServerRequest_ptr svreq,
			 CORBA::Environment &env);
    virtual CORBA::Long add (CORBA::Long x, CORBA::Long y,
			     char *&, CORBA::Context_ptr);

    virtual SV *variable (const SV &in, SV &inout, SV *&out);
    virtual SF fixed (const SF &in, SF &inout, SF &out);
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
CalcImpl::invoke (CORBA::StaticServerRequest_ptr svreq,
		  CORBA::Environment &env)
{
    if (!strcmp (svreq->op_name(), "add")) {
	CORBA::Long x, y, res;
	CORBA::String_var str;

	/*
         * create StaticAny's for arguments and result
         *
         * general rule for the second argument is:
         * - pass pointer to base types and sequence
         * - pass pointer to char* for strings
         * - pass pointer to wchar_t* for wstrings
         * - pass pointer to Object_ptr for objects
         * - pass pointer to Context_ptr, Principal_ptr,
         *   TypeCode_ptr for pseudo objects
         *
         * the second argument to StaticAny constructor is
         * void *, so you have to be careful: the compiler wont
         * detect type errors.
         *
         * StaticAny does not free any storage, it just keeps
         * pointers to the passed arguments, so everything can
         * be allocated on the stack, avoiding expensive heap
         * allocations.
         */
        
	CORBA::StaticAny x_any (CORBA::_stc_long, &x);
	CORBA::StaticAny y_any (CORBA::_stc_long, &y);
	CORBA::StaticAny res_any (CORBA::_stc_long, &res);
	CORBA::StaticAny str_any (CORBA::_stc_string, &str.out());

	/*
         * register StaticAny's with StaticRequest
         *
         * StaticRequest only keeps pointers to the StaticAny's
         * and wont free them.
         */
         
	svreq->add_in_arg (&x_any);
	svreq->add_in_arg (&y_any);
	svreq->add_out_arg (&str_any);
	svreq->set_result (&res_any);

	// fill in arguments will values from request
	if (!svreq->read_args())
	    return;

	/*
         * call user code, exception handling is the same
         * as for the DSI
         */
#ifdef HAVE_EXCEPTIONS
	try {
#endif
	    res = add (x, y, str.out(), svreq->ctx());
#ifdef HAVE_EXCEPTIONS
	} catch (CORBA::SystemException_catch &ex) {
	    svreq->set_exception (ex->_clone());
	    // no return here ...
	} catch (...) {
	    assert (0);
	}
#endif

        /*
         * since the StaticAny keeps pointers to the real
         * arguments you do not need to write back result
         * and out arguments to the according StaticAny's
         * here...
         */

        // write out arguments and result into request
	svreq->write_results();
	return;
    }

    if (!strcmp (svreq->op_name(), "fixed")) {
	SF in;
	SF out;
	SF inout;
	SF _res;

	CORBA::StaticAny _in (_stc_SF, &in);
	CORBA::StaticAny _inout (_stc_SF, &inout);
	CORBA::StaticAny _out (_stc_SF, &out);
	CORBA::StaticAny __res (_stc_SF, &_res);

	svreq->add_in_arg (&_in);
	svreq->add_inout_arg (&_inout);
	svreq->add_out_arg (&_out);
	svreq->set_result (&__res);

	if (!svreq->read_args())
	    return;

#ifdef HAVE_EXCEPTIONS
	try {
#endif
	    _res = fixed (in, inout, out);
#ifdef HAVE_EXCEPTIONS
	} catch (CORBA::SystemException_catch &ex) {
	    svreq->set_exception (ex->_clone());
	    // no return here ...
	} catch (...) {
	    assert (0);
	}
#endif
	svreq->write_results();
	return;
    }

    if (!strcmp (svreq->op_name(), "variable")) {
	SV in;
	SV inout;
	SV_var out;
	SV_var _res;

	CORBA::StaticAny _in (_stc_SV, &in);
	CORBA::StaticAny _inout (_stc_SV, &inout);
	CORBA::StaticAny _out (_stc_SV);
	CORBA::StaticAny __res (_stc_SV);

	svreq->add_in_arg (&_in);
	svreq->add_inout_arg (&_inout);
	svreq->add_out_arg (&_out);
	svreq->set_result (&__res);

	if (!svreq->read_args())
	    return;

#ifdef HAVE_EXCEPTIONS
	try {
#endif
	    _res = variable (in, inout, out);
	    /*
	     * for variable length out params and return values
	     * the called methods allocates the storage, so we can 
	     * tell the static any the addresses only after the user
	     * code has been called
	     */
	    _out.value (_stc_SV, &out.inout());
	    __res.value (_stc_SV, &_res.inout());
#ifdef HAVE_EXCEPTIONS
	} catch (CORBA::SystemException_catch &ex) {
	    svreq->set_exception (ex->_clone());
	    // no return here ...
	} catch (...) {
	    assert (0);
	}
#endif
	svreq->write_results();
    }
}

CORBA::Long
CalcImpl::add (CORBA::Long x, CORBA::Long y, char *&str,
               CORBA::Context_ptr ctx)
{
    CORBA::NVList_var vals;
    ctx->get_values ("", 0, "*", vals);
    for (CORBA::ULong i = 0; i < vals->count(); ++i) {
	char *s;
	CORBA::Boolean r = (*vals->item(i)->value() >>= s);
	assert (r);
	cout << vals->item(i)->name() << ": " << s << endl;
    }

    str = CORBA::string_dup ("hello world");
    return x + y;
}

SF
CalcImpl::fixed (const SF &in, SF &inout, SF &out)
{
    cout << in.l << endl << inout.l << endl << endl;
    out = inout;
    inout = in;
    return in;
}

SV *
CalcImpl::variable (const SV &in, SV &inout, SV *&out)
{
    cout << in.s.in() << endl << inout.s.in() << endl << endl;
    out = new SV (inout);
    inout = in;
    return new SV (in);
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

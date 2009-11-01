#include <CORBA.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/template_impl.h>
#include <mico/throw.h>

int
main (int argc, char *argv[])
{
    CORBA::ORB_ptr orb = CORBA::ORB_init (argc, argv, "mico-local-orb");

    CORBA::Object_var obj = orb->bind ("IDL:Calc:1.0");
    if (CORBA::is_nil (obj)) {
	cerr << "cannot bind to diiserver" << endl;
	cerr << "use -ORBBindAddr options to specify default bind addresses"
	     << endl;
	return 1;
    }

    CORBA::Any any;
    CORBA::Context_var ctx, ctx2;
    orb->get_default_context (ctx);

    ctx->create_child ("child", ctx2);

    any <<= "aa";
    ctx->set_one_value ("aa", any);

    any <<= "ab";
    ctx->set_one_value ("ab", any);

    any <<= "bb";
    ctx->set_one_value ("bb", any);

    any <<= "aa-child";
    ctx2->set_one_value ("aa", any);

    CORBA::Request_var req = obj->_request ("add");
    req->ctx (ctx2);
    req->contexts()->add ("a*");
    req->add_in_arg() <<= (CORBA::Long)1;
    req->add_in_arg() <<= (CORBA::Long)2;
    req->add_out_arg ();
    req->arguments()->item(2)->value()->set_type (CORBA::_tc_string);
    req->result()->value()->set_type (CORBA::_tc_long);

    req->invoke ();
    if (req->env()->exception())
	mico_throw (*req->env()->exception());

    CORBA::Long z;
    *req->result()->value() >>= z;
    cout << "result: " << z << endl;

    char *str;
    *req->arguments()->item(2)->value() >>= str;
    cout << str << endl;

    return 0;
}

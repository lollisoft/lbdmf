#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <qlabel.h>
#include <mico/qtmico.h>
#include "hello.h"

// Implementation of the Hello class //////////////////

QLabel* h;

class Hello_impl : virtual public Hello_skel {
public:
    Hello_impl():Hello_skel()
    { 
    }
    Hello_impl (CORBA::Object_ptr obj) : Hello_skel (obj)
    {
	cout << "restoring id " << obj->_ident() << endl;
    }
    void hello(const char *s)
    {
	h->setText(s);
    }
    CORBA::Boolean _save_object ()
    {
        return TRUE;
    }
};

class HelloLoader : public CORBA::BOAObjectRestorer {
public:
    CORBA::Boolean restore (CORBA::Object_ptr obj)
    {
        if (!strcmp (obj->_repoid(), "IDL:Hello:1.0")) {
            new Hello_impl (obj);
            return TRUE;
        }
        cout << "cannot restore " << obj->_repoid() << " objects" << endl;
        return FALSE;
    }
};

//---------------------------------------------------------------------------

int main( int argc, char **argv )
{
    HelloLoader loader;
    CApp a(argc,argv);

    // some qt pow wow ///////////////////////////////////////////////////

    h = new QLabel();

    h->setCaption( "QT meets MICO (hello server)" );
    h->setFont( QFont("times",32,QFont::Bold) );       	// default font
    h->setBackgroundColor( white );			// default bg color
    h->setAlignment( AlignCenter );			// default alignment
    h->setFixedSize(300,50);
    a.setMainWidget( h );
    h->show();

    // Create Server Object /////////////////////////////////////////////

    if (!a.boa->restoring()) {
	(void)new Hello_impl();
    }

    // run loop /////////////////////////////////////////////////////////

    // do not call a.boa->impl_is_ready() instead!
    a.impl_is_ready (CORBA::ImplementationDef::_nil());
    a.run ();
}

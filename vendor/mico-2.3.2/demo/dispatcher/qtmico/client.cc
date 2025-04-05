#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#ifdef HAVE_QLINEEDIT_H
#include <qlineedit.h>
#else
#include <qlined.h>
#endif
#include "hello.h"
#include <mico/qtmico.h>

Hello_var hello_client;

class HelloClientWidget : public QLineEdit {
    Q_OBJECT
public:
    HelloClientWidget() 
    {
	connect((QLineEdit*)this, SIGNAL(returnPressed()),
		this, SLOT(send()) );
    }
    ~HelloClientWidget() 
    {
    }
private slots:
    send()
    {
	hello_client->hello(text());
	setText("");
	setText("");
    }
};

int main (int argc, char *argv[])
{
    CApp a(argc,argv);

    // MICO stuff
    assert (argc == 2);
    CORBA::Object_var obj = a.orb->bind ("IDL:Hello:1.0", argv[1]);
    if (CORBA::is_nil (obj))
    {
	cerr << "cannot bind to " << argv[1] << endl;
	return 1;
    }
    hello_client = Hello::_narrow (obj);
    HelloClientWidget h;
    a.setMainWidget( &h );
    h.setFont( QFont("times",32,QFont::Bold) );		// default font
    h.setBackgroundColor( white );			// default bg color
    h.setFixedSize(300,50);
    h.show();
    a.exec();
    return 0;
}

#include "client.moc"

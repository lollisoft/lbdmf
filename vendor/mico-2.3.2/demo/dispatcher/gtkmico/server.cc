#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include <mico/gtkmico.h>
#include <gtk/gtk.h>
#include "hello.h"

GtkWidget *entry;

class MyCallback : public CORBA::DispatcherCallback {
public:
    void callback (CORBA::Dispatcher *disp, Event ev) 
    {
	gtk_entry_set_text (GTK_ENTRY (entry), "");
    }
};

class Hello_impl : virtual public Hello_skel {
public:
    void hello (const char *s)
    {
	gtk_entry_set_text (GTK_ENTRY (entry), s);
    }
};

void
quit_cb (GtkWidget *w, gpointer data)
{
    exit (0);
}

int
main (int argc, char *argv[])
{
    /*
     * MICO initialization
     */
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

    /*
     * GTK initialization
     */

    gtk_init (&argc, &argv);

    /*
     * Use GTK dispatcher
     */
    orb->dispatcher (new GtkDispatcher ());
    orb->dispatcher ()->tm_event (new MyCallback (), 5000);

    /*
     * MICO stuff
     */
    (void)new Hello_impl;

    /*
     * GTK stuff
     */
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    // entry

    entry = gtk_entry_new ();
    gtk_entry_set_text (GTK_ENTRY(entry), "Text from client");
    gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);
    gtk_widget_show (entry);

    // quit button

    GtkWidget *button = gtk_button_new_with_label("quit");
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
    gtk_widget_show (button);

    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (quit_cb), NULL);
    
    gtk_widget_show (window);

    boa->impl_is_ready (CORBA::ImplementationDef::_nil());
    orb->run ();

    return 0;
}

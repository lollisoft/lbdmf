#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <fstream.h>
#include "tty.h"    /* tty.h wurde aus 'tty.idl' generiert */



/*  Objekt-Implementation fuer das Interface tty.
 *  Die Klasse tty_skel wurde vom IDL-Compiler generiert.
 */

class tty_impl : virtual public tty_skel   {
   ofstream f;            // private Daten dieser Objekt-Impl.
public:
   tty_impl(char* fname) :f(fname)  {}               // Konstruktor
   ~tty_impl()                      { f.close();}    // Destruktor

   // die in "tty.idl" versprochene Operation:
   void print(const char* msg)   {
         f << msg << endl; f.flush(); }
};



int main(int argc, char* argv[])   {
  CORBA::ORB_var  orb;
  CORBA::BOA_var  boa;
  tty_impl        *obj_impl;

        // Initialisierung
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");
  boa= orb->BOA_init(argc, argv, "mico-local-boa");

        // Objekt-Implementation erzeugen
  obj_impl= new tty_impl("/dev/tty");

        // Objekt-Referenz (als String) ausgeben
  cout << "Objekt-Referenz dieser tty-Implementation:" << endl;
  cout << "\t" << orb->object_to_string(obj_impl) << endl;
  cout.flush();
 
        // Warten auf Klienten
  boa->impl_is_ready (CORBA::ImplementationDef::_nil());
  orb->run ();

  return 0;
}


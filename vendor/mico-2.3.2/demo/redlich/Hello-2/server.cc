#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <fstream.h>
#include "tty.h"           /* wurde aus 'tty.idl' generiert */



/*
 *  Typ einer Objekt-Implementation. Seine Instanzen besitzen
 *  das in "tty.idl" definierte Interface 'tty'.
 */

class tty_impl : virtual public tty_skel   {
   ofstream f;            // private Daten dieser Objekt-Impl.
public:
   tty_impl(char* fname) :f(fname)  {}
   ~tty_impl()                      { f.close();}

        // Ab hier werden die in "tty.idl" versprochenen
        // Operationen bereitgestellt:
  void print(const char* msg) {
        f << msg << "\n"; f.flush(); }
};



/*
 * Dieser Server stellt genau eine Objekt-Impl. bereit:
 */

int main(int argc, char* argv[])   {
  CORBA::ORB_var  orb;
  CORBA::BOA_var  boa;
  tty_impl        *obj_impl;

        // Initialisierung:
  orb = CORBA::ORB_init(argc, argv, "mico-local-orb");
  boa = orb->BOA_init (argc, argv, "mico-local-boa");

        // Objekt-Implementation erzeugen ....
  obj_impl= new tty_impl("/dev/tty");

        // ... und Obj-Ref (als String) ausgeben:
  cout << "Objekt-Referenz dieser 'tty'-Implementation:\n";
  cout << "\t" << orb->object_to_string(obj_impl) << "\n";
  cout.flush();
 
        // Warten auf Klienten
  boa->impl_is_ready (CORBA::ImplementationDef::_nil());
  orb->run ();
  return 0;
}

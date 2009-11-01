#include <fstream.h>
#include <CORBA-SMALL.h>
#include "tty.h"    /* tty.h wurde aus 'tty.idl' generiert */


int main(int argc, char* argv[])   {
  tty_var         tty_obj;
  CORBA::ORB_var  orb;
  char            objref_str[1024];

        // Initialisierung
  orb = CORBA::ORB_init(argc, argv, "mico-local-orb");

        // Objekt-Referenz erfragen
  cout << "Vom tty-Server bekanntgegebene Objekt-Referenz: ";
  cin  >> objref_str;

        // Rueckverwandlung des Strings in eine Obj-Ref
  tty_obj= tty::_narrow(orb->string_to_object(objref_str));

        // tty_obj zur Ausgabe von "Hello World!" veranlassen
  tty_obj->print("Hello World!");

  return 0;
}


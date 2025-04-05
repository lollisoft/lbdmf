#include <fstream.h>
#include <CORBA-SMALL.h>
#include "tty.h"           /* wurde aus 'tty.idl' generiert */


/*
 * Client
 */


int main(int argc, char* argv[])   {
  CORBA::ORB_var  orb;
  tty_var         tty_obj;
  char            objref_str[1024];

        // Initialisierung
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");

        // Objekt-Referenz erfragen
  cout << "Vom tty-Server bekanntgegebene Objekt-Referenz: ";
  cin  >> objref_str;

        // Rueckverwandlung des Strings in eine Obj-Ref
  tty_obj= tty::_narrow(orb->string_to_object(objref_str));

        // tty_obj zur Ausgabe von "Hello World\n" veranlassen
  tty_obj->print("Hello World");

  return 0;
}


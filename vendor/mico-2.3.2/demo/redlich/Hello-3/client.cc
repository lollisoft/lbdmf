#include <fstream.h>
#include <CORBA-SMALL.h>
#include "tty.h"
#include "ttyplus.h"


int main(int argc, char* argv[])   {
  ttyplus_var     ttyplus_obj;
  CORBA::ORB_var  orb;
  char            objref_str[1024];

        // Initialisierung
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");

        // Objekt-Referenz erfragen
  cout << "Vom ttyplus-Server bekanntgegebene Objekt-Referenz: ";
  cin  >> objref_str;

        // Rueckverwandlung des Strings in eine Obj-Ref
  ttyplus_obj= ttyplus::_narrow(orb->string_to_object(objref_str));

  cout << "TTY hat derzeit "
       << ttyplus_obj->columns()     // Zugriff auf Attribut
       << " Spalten" << endl;

  cout << "Neue Spaltenzahl: ";      // Spaltenzahl einstellen
  CORBA::Short i; cin >> i;
  ttyplus_obj->columns(i);    // Veraendern des Attributwertes

  ttyplus_obj->clrscr();      // Operation ausfuehren

  cout << "Bitte Text eingeben!" << endl;
  cout << "Zeile mit Punkt an 1. Stelle -> Ende" << endl;
  char buf[256];
  do {                          // noch ein Attribut-Zugriff:
        cout << "Zeile " << ttyplus_obj->lines() << ": ";
        cin >> buf;
        ttyplus_obj->print(buf);        // Operation benutzen
  } while (buf[0]!='.');

  return 0;
}


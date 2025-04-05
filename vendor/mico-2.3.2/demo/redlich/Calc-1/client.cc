#include <fstream.h>
#include <CORBA-SMALL.h>
#include "calc.h"        /* wurde aus 'calc.idl' generiert */


/*
 * einfache Funktion zum Einlesen eines 'Calc1::calc::complex'
 * Format: (1.2,3.4)     '(' kann bereits gelesen worden sein
 */


istream &operator >> (istream &f, Calc1::calc::complex &z)  {
   char dummy;

   f >> dummy; if (dummy!='(') f.putback(dummy);
   f >> z.r >> dummy >> z.i >> dummy;
   return f;
}


int main(int argc, char* argv[])   {
  Calc1::calc_var       calc_obj;
  Calc1::calc::complex  z, tmp;
  CORBA::ORB_var        orb;

        // Initialisierung:
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");

        // Objekt-Referenz erfragen:
  char objref_str[1024];
  cout << "Vom calc-Server bereitgestellte Objekt-Referenz: ";
  cin  >> objref_str;

        // Rueckverwandlung des Strings in eine Obj-Ref:
  calc_obj= Calc1::calc::_narrow(
                   orb->string_to_object(objref_str));

  cout << "Eingabe einer Zahl  z.B.: (1.0,2.3)\n";
  cout << "Operation ausloesen z.B.: +(1.0,2.3)\n";
  cout << "Unterstuetzte Operationen: + * /\n";
  cout << "Ende: .<ENTER>\n";

  z.r= z.i= 0.0;
  calc_obj->setValue(z);

  char c;
  do {
        cout << "(" << z.r << "," << z.i << "): ";
        cin >> c;

        switch (c)  {
        case '(': cin >> z;   calc_obj->setValue(z); break;
        case '+': cin >> tmp; z= calc_obj->add(tmp); break;
        case '*': cin >> tmp; calc_obj->mult(tmp,z); break;
        case '/': cin >> z;   calc_obj->div(z);      break;
        default:  c= '.';  // -> terminieren
        }
   } while (c!='.'  &&  !cin.eof());
   cout << "Ende\n";

  return 0;
}


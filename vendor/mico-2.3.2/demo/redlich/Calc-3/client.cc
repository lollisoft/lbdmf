#include <fstream.h>
#include <stdlib.h>
#include <CORBA-SMALL.h>
#include "calc.h"


istream &operator >> (istream &f, Calc3::calc::complex &z)  {
   char dummy;

   f >> dummy; if (dummy!='(') f.putback(dummy);
   f >> z.r >> dummy >> z.i >> dummy;
   return f;
}



int main(int argc, char* argv[])   {
  Calc3::calc_var       calc_obj;
  Calc3::calc::complex  z, tmp;
  CORBA::ORB_var        orb;

        // Initialisierung:
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");

        // Objekt-Referenz erfragen:
  char objref_str[1024];
  cout << "Vom calc-Server bereitgestellte Obj-Ref: ";
  cin  >> objref_str;

  CORBA::Object_var obj;

  try {  // versuchen wir's ...
      obj= orb->string_to_object(objref_str);
  }
  catch (CORBA::SystemException_catch& ex1)      {
    // Behandle die spezielle CORBA-Systemexception INV_IDENT
    if( CORBA::INV_IDENT *ex2 = CORBA::INV_IDENT::EXCEPTION_DOWNCAST( ex1 ) ) {
      cerr << "so sieht keine Obj-Ref aus!" << endl;
      exit(1);
    } else {
      // Behandle alle uebrigen CORBA-Systemexceptions
      cerr << "string_to_object() ging schief" << endl;
      exit(1);
    }
  }

  	// Ist das Objekt auch vom richtigen Typ?
  calc_obj= Calc3::calc::_narrow(obj);
  if (CORBA::is_nil(calc_obj))	{
      cerr << "narrow() ging schief" << endl;
      exit(1);
  }

  cout << "Eingabe einer Zahl  z.B.:  (1.0,2.3)" << endl;
  cout << "Operation ausloesen z.B.: +(1.0,2.3)" << endl;
  cout << "Ende: .<ENTER>" << endl;

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
     case '/': cin >> z;
               try {   // hier koennte ein Fehler auftreten:
                   calc_obj->div(z);
               }
               catch (Calc3::calc::MyException_catch &myEx)  {
                   cout << "Fehler: " << myEx->reason.in() << endl;
                   z.r= z.i= 0; calc_obj->setValue(z);
               }
               break;

     default:  c= '.';  // -> terminieren
     }
   } while (c!='.'  &&  !cin.eof());
   cout << "Ende" << endl;

   return 0;
}


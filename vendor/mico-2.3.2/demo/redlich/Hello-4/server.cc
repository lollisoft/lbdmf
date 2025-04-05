#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <fstream.h>
#include "tty.h"
#include "ttyplus.h"


class tty_impl : virtual public Hello3::tty_skel,
                 virtual public Hello4::ttyplus_skel  {
   ofstream   f;
   long       ln;
   int        max_col;

public:
   tty_impl(char* fname) :f(fname) { ln= 1; max_col= 80; }
   ~tty_impl()                     { f.close();}


   void  columns(CORBA::Short n)  {
            max_col= n; }

   CORBA::Short  columns(void)  {
            return max_col; }

   CORBA::Long  lines(void)  {
            return ln; }

   void  clrscr(void) {
            for (int i= 10; --i>=0; f << endl);
            f.flush(); }

   void  print(const char* msg)	  {
            for (int col=0; msg[col]; f << msg[col++])  {
		 if (((col+1) % max_col) == 0)  {
			f << endl; ++ln;
		 }
	    }
            f << endl; f.flush(); ++ln; }
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

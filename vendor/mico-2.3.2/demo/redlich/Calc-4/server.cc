#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <iostream.h>
#include "calc.h"



    ///////////////////////////////////////////////////////////
    // Die nachfolgende Klasse stellt die benoetigten
    // Operationen WIRKLICH bereit:
    ///////////////////////////////////////////////////////////

struct OldComplex {  // alter Datentyp 'complex'
   double i;      // nicht kompatibel zu 'Calc4::calc::complex'
   double r;
};



class calc_impl {
   OldComplex value;

   void copy(OldComplex& dst, const OldComplex& src)  {
        dst.r= src.r; dst.i= src.i; }

public:
   void setValue(const OldComplex& z)  {
        copy(value,z);  }

   OldComplex add(const OldComplex& z)  {
        value.r += z.r;
        value.i += z.i;
        return value;   }

   void mult(const OldComplex& z, OldComplex& r)  {
        OldComplex tmp;

        tmp.r= value.r*z.r - value.i*z.i;
        tmp.i= value.r*z.i + value.i*z.r;
        copy(value, tmp);
	copy(r, tmp); }

   void div(OldComplex& z)  {
        OldComplex tmp;
        double  d=  z.r*z.r + z.i*z.i;

        tmp.r= (value.r*z.r + value.i*z.i) / d;
        tmp.i= (value.i*z.r - value.r*z.i) / d;
        copy(value, tmp);
	copy(z, tmp); }
};


   ////////////////////////////////////////////////////////////
   // Die Klasse calc_delegate tritt gegenueber CORBA als
   // Objekt-Implementation auf. In Wahrheit delegiert sie
   // jedoch die Operations-Aufrufe an eine Instanz von calc_i
   ////////////////////////////////////////////////////////////

class calc_delegate : virtual public Calc4::calc_skel   {
  calc_impl*   true_impl;

  void cpy(OldComplex &o, const complex &c) {o.r=c.r; o.i=c.i;}
  void cpy(complex &c, const OldComplex &o) {c.r=o.r; c.i=o.i;}

public:
   calc_delegate(calc_impl* impl_ptr)  { true_impl= impl_ptr; }

   void setValue(const complex& z) {
        OldComplex oz; cpy(oz,z); // Typ des Arguments konvert.
        true_impl->setValue(oz);
   }

   complex add(const complex& z) {
        OldComplex oz; cpy(oz,z);
        OldComplex oresult= true_impl->add(oz);
        complex result; cpy(result, oresult);
        return result;
   }

   void mult(const complex& z, complex& result)  {
        OldComplex oresult, oz; cpy(oz,z);
        true_impl->mult(oz,oresult);
        cpy(result,oresult);
   }

   void div(complex& z)  {
        OldComplex oz; cpy(oz,z);
        true_impl->div(oz);
        cpy(z,oz);
   }
};


   ////////////////////////////////////////////////////////////
   //  main()
   ////////////////////////////////////////////////////////////

int main(int argc, char* argv[])   {
  CORBA::ORB_var  orb;
  CORBA::BOA_var  boa;
  calc_delegate   *obj_impl;

        // Initialisierung:
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");
  boa= orb->BOA_init(argc, argv, "mico-local-boa");

  obj_impl= new calc_delegate(new calc_impl);

  cout << "Objekt-Referenz dieser 'calc'-Implementation:\n";
  cout << "\t" << orb->object_to_string(obj_impl) << "\n";
  cout.flush();

        // Warten auf Klienten
  boa->impl_is_ready (CORBA::ImplementationDef::_nil());
  orb->run ();

  return 0;
}


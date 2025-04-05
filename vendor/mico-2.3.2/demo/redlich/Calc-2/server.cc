#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <fstream.h>
#include "calc.h"



class calc_impl : virtual public Calc2::calc_skel   {
   complex      value;

   void copy(complex& dst, const complex& src)  {
        dst.r= src.r; dst.i= src.i; }
                        
public:
   void setValue(const complex& z)  {
        copy(value,z);  }

   complex add(const complex& z)  {
        value.r += z.r;
        value.i += z.i;
        return value;   }

   void mult(const complex& z, complex& result)  {
        complex tmp;

        tmp.r= value.r*z.r - value.i*z.i;
        tmp.i= value.r*z.i + value.i*z.r;
        copy(value, tmp);
	copy(result, tmp); }

   void div(complex& z)  {
        complex tmp;
        double  d=  z.r*z.r + z.i*z.i;

        tmp.r= (value.r*z.r + value.i*z.i) / d;
        tmp.i= (value.i*z.r - value.r*z.i) / d;
        copy(value, tmp);
	copy(z, tmp); }
};



int main(int argc, char* argv[])   {
  CORBA::ORB_var  orb;
  CORBA::BOA_var  boa;
  calc_impl       *obj_impl;

        // Initialisierung:
  orb= CORBA::ORB_init(argc, argv, "mico-local-orb");
  boa= orb->BOA_init(argc, argv, "mico-local-boa");

  obj_impl= new calc_impl;

  cout << "Objekt-Referenz dieser 'calc'-Implementation:\n";
  cout << "\t" << orb->object_to_string(obj_impl) << "\n";
  cout.flush();

        // Warten auf Klienten
  boa->impl_is_ready (CORBA::ImplementationDef::_nil());
  orb->run ();

  return 0;
}

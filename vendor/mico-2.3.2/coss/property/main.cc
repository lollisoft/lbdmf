/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#define MICO_CONF_IMR
#include <CORBA-SMALL.h>
#include <mico/CosNaming.h>
#include <mico/PropertyService_impl.h>
#include <mico/util.h>

void usage (const char *progname)
{
  cerr << "usage: " << progname << " [<options>]" << endl;
  cerr << "possible <options> are:" << endl;
  cerr << "    --regname1 <naming service name for property set factory>"
       << endl;
  cerr << "    --regname2 <naming service name for property set def factory>"
       << endl;
  exit (1);
}

void register_ns (CORBA::ORB_ptr orb, const char *_name, CORBA::Object_ptr obj)
{
  CORBA::ORB::ObjectIdList_var svlist = orb->list_initial_services ();
  {
      CORBA::ULong i;
      for (i = 0; i < svlist->length(); ++i) {
	  if (!strcmp (svlist[i].in(), "NameService"))
	      break;
      }
      if (i == svlist->length())
	  return;
  }
  CORBA::Object_var nsobj =
      orb->resolve_initial_references ("NameService");

  assert (! CORBA::is_nil (nsobj));
  
  CosNaming::NamingContext_var nc = 
      CosNaming::NamingContext::_narrow (nsobj);

  CosNaming::Name name;
  name.length (1);
  name[0].id = _name;
  name[0].kind = (const char *)"";

#ifdef HAVE_EXCEPTIONS
  try {
      nc->rebind (name, obj);
  } catch (...) {
      cerr << "Cannot register with name service !" << endl;
      exit (1);
  }
#else
  nc->rebind (name, obj);
#endif
}

int main (int argc, char *argv[])
{
  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  string regname1 = "PropertySetFactory";
  string regname2 = "PropertySetDefFactory";

  MICOGetOpt::OptMap opts;
  opts["--regname1"] = "arg-expected";
  opts["--regname2"] = "arg-expected";

  MICOGetOpt opt_parser (opts);
  if (!opt_parser.parse (argc, argv))
    usage (argv[0]);

  for (MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
       i != opt_parser.opts().end(); ++i) {
    string arg = (*i).first;
    string val = (*i).second;

    if (arg == "--regname1") {
      regname1 = val;
    } else if (arg == "--regname2") {
      regname2 = val;
    } else {
      usage( argv[ 0 ] );
    }
  }

  PropertyService::PropertySetFactory_ptr factory1 =
      new PropertySetFactory_impl;
  register_ns (orb, regname1.c_str(), factory1);

  PropertyService::PropertySetDefFactory_ptr factory2 =
      new PropertySetDefFactory_impl;
  register_ns (orb, regname2.c_str(), factory2);

  boa->impl_is_ready (CORBA::ImplementationDef::_nil ());
  orb->run ();
  return 0;
}

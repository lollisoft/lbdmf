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
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/CosNaming.h>
#include "CosEvent_impl.h"

void sighandler (int sig)
{
  EventChannelFactory_impl::_shutdown ();
}

void usage (const char *progname)
{
  cerr << "usage: " << progname << " [<options>]" << endl;
  cerr << "possible <options> are:" << endl;
  cerr << "    --regname <naming service name>" << endl;
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
  signal (SIGINT, sighandler);
#if 0
  /*
   * when exiting micod sends all running servers a SIGTERM. that is
   * we can't save on SIGTERM ...
   */
  signal (SIGTERM, sighandler);
#endif
  // create loader for persistent state 
  EventChannelLoader loader;

  // ORB initialization
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::BOA_var boa = orb->BOA_init (argc, argv, "mico-local-boa");

  string regname = "EventChannelFactory";

  MICOGetOpt::OptMap opts;
  opts["--regname"] = "arg-expected";

  MICOGetOpt opt_parser (opts);
  if (!opt_parser.parse (argc, argv))
    usage (argv[0]);

  for (MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
       i != opt_parser.opts().end(); ++i) {
    string arg = (*i).first;
    string val = (*i).second;

    if (arg == "--regname") {
      regname = val;
    } else {
      usage( argv[ 0 ] );
    }
  }

  if (!boa->restoring ()) {
    SimpleEventChannelAdmin::EventChannelFactory_ptr factory =
      new EventChannelFactory_impl ();
    register_ns (orb, regname.c_str(), factory);
  }

  boa->impl_is_ready (CORBA::ImplementationDef::_nil ());
  orb->run ();
  return 0;
}

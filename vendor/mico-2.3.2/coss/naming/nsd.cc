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
#define MICO_CONF_POA

#include <CORBA-SMALL.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <iostream.h>
#include <fstream.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include "Naming_impl.h"


static CORBA::ORB_ptr orb;

/*
 * A Servant Manager for NamingContext
 */

class NamingManager : public virtual POA_PortableServer::ServantActivator
{
public:
  PortableServer::Servant incarnate (const PortableServer::ObjectId & oid,
				     PortableServer::POA_ptr poa)
  {
    CORBA::String_var name = PortableServer::ObjectId_to_string (oid);
    NamingContext_impl * nc = new NamingContext_impl;
    NamingContext_impl::svmap[nc] = nc;
    nc->restore (name.in());
    return nc;
  }
  void etherealize (const PortableServer::ObjectId & oid,
		    PortableServer::POA_ptr poa,
		    PortableServer::Servant serv,
		    CORBA::Boolean cleanup_in_progress,
		    CORBA::Boolean remaining_activations)
  {
    CORBA::String_var name = PortableServer::ObjectId_to_string (oid);
    NamingContext_impl::ServantMap::iterator it =
      NamingContext_impl::svmap.find (serv);
    assert (it != NamingContext_impl::svmap.end());

    NamingContext_impl * nc = (*it).second;
    NamingContext_impl::svmap.erase (it);

    nc->save (name.in());
    nc->_remove_ref ();
  }
};

void sighandler (int sig)
{
  if (!CORBA::is_nil (orb)) {
    orb->shutdown (TRUE);
  }
}

void usage (const char *progname)
{
  cerr << "usage: " << progname << " [<options>]" << endl;
  cerr << "possible <options> are:" << endl;
  cerr << "    --help" << endl;
  cerr << "    --ior <IOR ref file>" << endl;
  exit (1);
}

int main (int argc, char *_argv[])
{
  orb = CORBA::ORB::_nil ();
  signal (SIGINT, sighandler);
  signal (SIGTERM, sighandler);

  /*
   * prevent a bind() to naming service...
   * also add -POAImplName if missing...
   */

  const char * implname = NULL;
  char **argv = new char*[argc+2+2+1];

  for (int i=0; i<argc; ++i) {
    if (strcmp (_argv[i], "-POAImplName") == 0 && i+1<argc) {
      implname = _argv[i+1];
    }
    argv[i] = _argv[i];
  }

  if (!implname) {
    argv[argc++] = "-POAImplName";
    argv[argc++] = "NameService";
  }

  argv[argc++] = "-ORBNamingAddr";
  argv[argc++] = "";

  argv[argc] = 0;

  // ORB initialization
  orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
  CORBA::Object_var po = orb->resolve_initial_references ("RootPOA");
  PortableServer::POA_var RootPOA = PortableServer::POA::_narrow (po);
  PortableServer::POAManager_var RootMgr = RootPOA->the_POAManager ();

  MICOGetOpt::OptMap opts;
  opts["--help"] = "";
  opts["--ior"]  = "arg-expected";

  MICOGetOpt opt_parser (opts);
  if (!opt_parser.parse (argc, argv))
    usage (argv[0]);

  string reffile;

  {
  for (MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
       i != opt_parser.opts().end(); ++i) {
    string arg = (*i).first;
    string val = (*i).second;

    if (arg == "--ior") {
      reffile = val;
    } else if (arg == "--help") {
      usage (argv[0]);
    } else {
      usage (argv[0]);
    }
  }
  }
  if (argc != 1) {
    usage (argv[0]);
  }

  /*
   * We create two new Persistent POAs. One for the root NamingContext
   * with the USER_ID policy so that we can select the `NameService' id,
   * and one for all child contexts with the SYSTEM_ID policy
   */

  CORBA::PolicyList pl;
  pl.length (2);
  pl[0] = RootPOA->create_lifespan_policy (PortableServer::PERSISTENT);
  pl[1] = RootPOA->create_id_assignment_policy (PortableServer::USER_ID);
  PortableServer::POA_var rcpoa =
    RootPOA->create_POA ("NameService",
			 PortableServer::POAManager::_nil (),
			 pl);
  PortableServer::POAManager_var rcmgr = rcpoa->the_POAManager ();

  pl[1] = RootPOA->create_request_processing_policy (PortableServer::USE_SERVANT_MANAGER);
  PortableServer::POA_var ncpoa =
    RootPOA->create_POA ("NamingContexts", rcmgr.in(), pl);

  /*
   * Create Root Naming Context
   */

  NamingContextExt_impl * root =
    new NamingContextExt_impl (orb, ncpoa.in(), implname);

  /*
   * Restore persistent state
   */

  root->restore ("-root");

  /*
   * Activate
   */

  PortableServer::ObjectId_var rncid =
    PortableServer::string_to_ObjectId ("NameService");
  rcpoa->activate_object_with_id (rncid.in(), root);

  if (reffile.length() > 0) {
    ofstream out (reffile.c_str());
    if (!out) {
      cerr << "error: cannot open output file " << reffile.c_str() << endl;
    }
    else {
      CORBA::Object_var nsobj = rcpoa->servant_to_reference (root);
      CORBA::String_var nsior = orb->object_to_string (nsobj);
      out << nsior.in() << endl;
      out.close ();
    }
  }

  /*
   * Register our ServantManager
   */

  NamingManager * nm = new NamingManager;
  PortableServer::ServantManager_var smgr = nm->_this ();
  ncpoa->set_servant_manager (smgr.in());

  /*
   * Go Active
   */

  rcmgr->activate ();
  RootMgr->activate ();
  orb->run ();

  /*
   * Shutting down.
   */

  RootPOA->destroy (TRUE, TRUE);
  root->save ("-root");
  nm->_remove_ref ();
  root->_remove_ref ();
  CORBA::release (orb);

  return 0;
}

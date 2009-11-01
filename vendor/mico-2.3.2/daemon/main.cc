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

#include <sys/types.h>
#include <signal.h>
#include <iostream.h>
#include <fstream.h>
#include <CORBA.h>
#include <mico/util.h>
#include <mico/template_impl.h>
#include "mediator.h"
#include "poamediator.h"

CORBA::ORB_ptr orb;
CORBA::BOA_ptr boa;
CORBA::OAMediator_ptr med;
POAMediatorImpl * pmd;
string thedb;

int
save_imr (const char *fn)
{
    ofstream out (fn);
    if (!out) {
	cerr << "error: cannot open output file " << fn << endl;
	return 1;
    }
    CORBA::Object_var obj =
      orb->resolve_initial_references ("ImplementationRepository");
    CORBA::ImplRepository_var imr = CORBA::ImplRepository::_narrow (obj);

    /*
     * Save Imr entries
     */

    CORBA::ImplRepository::ImplDefSeq_var impls = imr->find_all();
    CORBA::ULong length=0;

    for (CORBA::ULong i0 = 0; i0<impls->length(); ++i0) {
      CORBA::String_var s = impls[i0]->command();
      if (strlen (s) > 0) {
	length++;
      }
    }

    out << length << endl;

    for (CORBA::ULong i = 0; i < impls->length(); ++i) {
	CORBA::String_var s = impls[i]->command();
	if (strlen (s) > 0) {
	    // it is not an automatically created entry
	    s = impls[i]->tostring();
	    out << s.in() << endl;
	}
    }

    return 0;
}

int
restore_imr (const char *fn)
{
    ifstream in (fn);
    if (!in) {
	cerr << "warning: cannot open input file " << fn << endl;
	return 1;
    }
    CORBA::Object_var obj =
      orb->resolve_initial_references ("ImplementationRepository");
    CORBA::ImplRepository_var imr = CORBA::ImplRepository::_narrow (obj);

    /*
     * Restore Imr entries
     */

    char line[10000];
    if (in.getline(line, sizeof (line)).eof()) {
      return 0;
    }

    CORBA::ULong entries = atoi (line);

    for (CORBA::ULong i=0; i<entries; i++) {
      if (in.getline (line, sizeof (line)).eof()) {
	break;
      }
      CORBA::ImplementationDef_var impl = imr->restore (line);
      assert (!CORBA::is_nil (impl));
    }

    return 0;
}

void
sighandler (int sig)
{
    if (!CORBA::is_nil (pmd)) {
      pmd->shutdown_server ();
    }
    orb->shutdown (TRUE);
    if (thedb.length() > 0)
	save_imr (thedb.c_str());
    if (!CORBA::is_nil (med))
	CORBA::release (med);
    if (!CORBA::is_nil (pmd))
	CORBA::release (pmd);
    signal (sig, SIG_DFL);
    raise (sig);
}

void
usage (const char *progname)
{
    cerr << "usage: " << progname << " [<options>]" << endl;
    cerr << "possible <options> are:" << endl;
    cerr << "    --help" << endl;
    cerr << "    --forward" << endl;
    cerr << "    --db <database file>" << endl;
    cerr << "    --ior <IOR ref file>" << endl;
    exit (1);
}

int
main (int argc, char *argv[])
{
    CORBA::Boolean forward_opt = FALSE;

    orb = CORBA::ORB_init (argc, argv, "mico-local-orb");
    boa = orb->BOA_init (argc, argv, "mico-local-boa");

#ifdef _WINDOWS
    MICO::UnixProcess::win32_process_init();
#endif

    MICOGetOpt::OptMap opts;
    opts["--help"]    = "";
    opts["--forward"] = "";
    opts["--db"]      = "arg-expected";
    opts["--ior"]     = "arg-expected";

    MICOGetOpt opt_parser (opts);
    if (!opt_parser.parse (argc, argv))
	usage (argv[0]);

    string reffile;

    for (MICOGetOpt::OptVec::const_iterator i = opt_parser.opts().begin();
	 i != opt_parser.opts().end(); ++i) {
	string arg = (*i).first;
	string val = (*i).second;

	if (arg == "--db") {
	    thedb = val;
	} else if (arg == "--forward") {
	    forward_opt = TRUE;
	} else if (arg == "--ior") {
	    reffile = val;
	} else if (arg == "--help") {
	    usage (argv[0]);
	} else {
	    usage (argv[0]);
	}
    }
    if (argc != 1) {
	usage (argv[0]);
    }

    pmd = new POAMediatorImpl (orb, forward_opt);
    med = new MediatorImpl (forward_opt);

    if (thedb.length() > 0)
	restore_imr (thedb.c_str());

    if (reffile.length() > 0) {
      CORBA::Object_var obj = orb->resolve_initial_references ("ImplementationRepository");
      ofstream out (reffile.c_str());
      if (!out) {
	cerr << "error: cannot open output file " << reffile.c_str() << endl;
      }
      else {
	CORBA::String_var pmior = orb->object_to_string (obj);
	out << pmior.in() << endl;
	out.close ();
      }
    }

    signal (SIGTERM, sighandler);
    signal (SIGINT, sighandler);
#ifndef _WINDOWS
    signal (SIGHUP, sighandler);
#endif

    orb->run ();
    // notreached
    return 0;
}

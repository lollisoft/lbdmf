/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1998 Frank Pilhofer
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

#include <CORBA.h>
#include <mico/impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>
#include <mico/template_impl.h>
#include "poamediator.h"

/*
 * ----------------------------------------------------------------------
 * The POA Mediator
 *
 * Persistent POAs connect here using create_impl(). The POA tells us
 * its IOR Template, which contains its address. We return our IOR. The
 * POA then produces object references pointing to us on its own. The
 * Objectkey of such references starts with the unique identifier for
 * that server followed by ':'.
 * When we receive an invocation for such a reference, we construct a
 * new object reference by taking the POAs IOR template plus the object
 * key, and forward the invocation.
 * ----------------------------------------------------------------------
 */

/*
 * Helpers
 */

POAMediatorImpl::SvInf::SvInf ()
{
  pstate = Inactive;
  proc = NULL;
}

/*
 * ----------------------------------------------------------------------
 * POAMediatorImpl
 * ----------------------------------------------------------------------
 */

POAMediatorImpl::POAMediatorImpl (CORBA::ORB_ptr _orb, CORBA::Boolean _forward)
  : invqueue (this, _orb)
{
  orb = _orb;
  forward = _forward;
  myior = orb->ior_template()->stringify();

  CORBA::Object_var obj =
    orb->resolve_initial_references ("ImplementationRepository");
  imr = CORBA::ImplRepository::_narrow (obj);

  // make sure that IIOPProxy is asked first. otherwise we would
  // end up in an endless loop invoking ourselves because has_object()
  // doesnt detect whether we are passed a local or remote object.
  orb->register_oa (this, OAPriorityRemote-1);
}

POAMediatorImpl::~POAMediatorImpl ()
{
  orb->unregister_oa (this);

  MapSvInf::iterator it;

  for (it = svmap.begin(); it != svmap.end(); it++) {
    if ((*it).second.proc) {
      delete (*it).second.proc;
    }
  }
}

/*
 * POA Mediator interface
 */

char *
POAMediatorImpl::create_impl (const char * svid, const char * ior)
{
  svmap[svid].ior = CORBA::IOR (ior);
  return CORBA::string_dup (myior.c_str());
}

void
POAMediatorImpl::activate_impl (const char * svid)
{
  svmap[svid].pstate = Active;

  /*
   * perform pending invocations
   */

  invqueue.exec_later();
}

void
POAMediatorImpl::deactivate_impl (const char * svid)
{
  SvInf &inf = svmap[svid];
  inf.pstate = Inactive;
  assert (inf.proc);
  inf.proc->detach ();
  delete inf.proc;
  inf.proc = 0;
}

CORBA::Boolean
POAMediatorImpl::force_activation (CORBA::ImplementationDef_ptr impl)
{
  CORBA::String_var svid = impl->name ();
  SvInf &inf = svmap[svid.in()];
  if (inf.pstate == Failed) {
    inf.pstate = Inactive;
  }
  return create_server (svid);
}

/*
 * Try to start up a server
 */

CORBA::Boolean
POAMediatorImpl::create_server (const char * svid)
{
  SvInf &inf = svmap[svid];

  if (inf.pstate == Started || inf.pstate == Active) {
    return TRUE;
  }

  /*
   * If the server is in the Failed state, we employ a similar strategy
   * as init does. We refuse to restart a server within 30 seconds after
   * its failure. Note that the Failed state is only entered if the server
   * crashes prior to its activation.
   * Without this 30 sec pause, the request that started the server would
   * be a ping of death, causing permanent restart.
   * We assume that the server has been fixed after the pause.
   * This can be overridden (i.e. restart a server before 30 secs have
   * elapsed) by using `imr activate'
   */

  if (inf.pstate == Failed) {
    OSMisc::TimeVal curtime = OSMisc::gettime();
    if ((curtime.tv_sec - inf.failed) < 30) {
      // less than 30 secs elapsed since first failure
      return FALSE;
    }
    inf.pstate = Inactive;
  }

  assert (inf.pstate == Inactive);

  /*
   * Look up entry in Implementation Repository
   */

  if (CORBA::is_nil (imr)) {
    return FALSE;
  }

  CORBA::ImplRepository::ImplDefSeq_var impls = imr->find_by_name (svid);
  if (impls->length() == 0)
    return FALSE;

  CORBA::ImplementationDef_var idv =
    CORBA::ImplementationDef::_duplicate (impls[(CORBA::ULong)0]);

  /*
   * Construct command line
   */

  CORBA::String_var s = idv->command();
  string command = (const char *) s;

  command += " -POAImplName ";
  command += svid;

  s = orb->object_to_string (imr);
  command += " -ORBImplRepoIOR ";
  command += s;

  CORBA::Object_var obj =
    orb->resolve_initial_references ("InterfaceRepository");
  s = orb->object_to_string (obj);
  command += " -ORBIfaceRepoIOR ";
  command += s;

  s = orb->object_to_string (this);
  command += " -POARemoteIOR ";
  command += s;

  inf.pstate = Started;
  inf.proc = new MICO::UnixProcess (command.c_str(), this);

  return inf.proc->run();
}

/*
 * OA Interface
 */

const char *
POAMediatorImpl::get_oaid () const
{
    return "mico-poa-mediator";
}

CORBA::Boolean
POAMediatorImpl::has_object (CORBA::Object_ptr obj)
{
  /*
   * Extract Objectkey from IOR. It starts with the POAImplName.
   * Take care of escaped slashes.
   */

  const CORBA::Octet * key;
  CORBA::Long length, i, j;

  if (CORBA::is_nil (obj) || !obj->_ior() || !obj->_ior()->profile()) {
    return FALSE;
  }

  key = obj->_ior()->profile()->objectkey (length);

  if (!key || length < 0) {
    return FALSE;
  }

  for (i=0, j=0; i<length; i++) {
    if (key[i] == '\\') {
      j++;
    }
    else if (key[i] == '/' && (j%2) == 0) {
      break;
    }
    else {
      j = 0;
    }
  }

  string svid;

  for (j=0; j<i; j++) {
    if (key[j] == '\\') {
      j++;
    }
    svid += key[j];
  }

  /*
   * Look up ServerId in Map
   */

  MapSvInf::iterator it = svmap.find (svid);

  if (it == svmap.end()) {
    return FALSE;
  }

  return TRUE;
}

CORBA::Boolean
POAMediatorImpl::is_local () const
{
    return FALSE;
}

CORBA::Boolean
POAMediatorImpl::invoke (MsgId id, CORBA::Object_ptr obj,
			 CORBA::ORBRequest *req,
			 CORBA::Principal_ptr pr,
			 CORBA::Boolean response_exp)
{
  /*
   * Extract Objectkey from IOR. It starts with the POAImplName.
   */

  const CORBA::Octet * key;
  CORBA::Long length, i, j;

  assert (!CORBA::is_nil (obj) && obj->_ior() && obj->_ior()->profile());
  key = obj->_ior()->profile()->objectkey (length);
  assert (key);

  for (i=0, j=0; i<length; i++) {
    if (key[i] == '\\') {
      j++;
    }
    else if (key[i] == '/' && (j%2) == 0) {
      break;
    }
    else {
      j = 0;
    }
  }

  string svid;

  for (j=0; j<i; j++) {
    if (key[j] == '\\') {
      j++;
    }
    svid += key[j];
  }

  /*
   * Look up ServerId in Map
   */

  MapSvInf::iterator it = svmap.find (svid);

  if (it == svmap.end()) {
    /*
     * Server has disappeared? Oh well.
     */
    CORBA::OBJECT_NOT_EXIST ex;
    req->set_out_args (&ex);
    orb->answer_invoke (id, CORBA::InvokeSysEx,
			CORBA::Object::_nil(), req);
    return TRUE;
  }

  /*
   * Is Server active?
   */

  if ((*it).second.pstate != Active) {
    /*
     * No? Restart it.
     */
    if (!create_server (svid.c_str())) {
      /*
       * failed.
       */
      CORBA::OBJECT_NOT_EXIST ex;
      req->set_out_args (&ex);
      orb->answer_invoke (id, CORBA::InvokeSysEx,
			  CORBA::Object::_nil(), req);
      return TRUE;
    }

    /*
     * Server has been started, but is not active yet. We must queue
     * the request until the server announces its readiness by calling
     * activate_impl().
     */

    invqueue.add (new MICO::ReqQueueRec (id, req, obj, pr, response_exp));
    return TRUE;
  }

  /*
   * Construct remote object reference
   */

  CORBA::IOR * ior = new CORBA::IOR ((*it).second.ior);
  ior->objectkey ((CORBA::Octet *) key, length);
  ior->objid (obj->_ior()->objid());

  CORBA::Object_var remote_ref = new CORBA::Object (ior);
  remote_ref->_setup_domains (CORBA::Object::_nil());

  if (response_exp && forward) {
    // forward to server ...
    orb->answer_invoke (id, CORBA::InvokeForward,
			remote_ref, req);
    return TRUE;
  }
  /*
   * do the invocation (on the remote object)
   */

  MsgId orbid = orb->new_msgid();

  if (response_exp) {
    requests[orbid] = id;
  }

  orb->invoke_async (remote_ref, req, pr, response_exp, this, orbid);
  return TRUE;
}

CORBA::Boolean
POAMediatorImpl::bind (MsgId id, const char *repoid,
		       const CORBA::ORB::ObjectTag &tag,
		       CORBA::Address *addr)
{
  if (addr && !addr->is_local()) {
    return FALSE;
  }

  /*
   * Search the Implementation Repository for a POA entry that serves
   * the given Repository Id
   */

  CORBA::ImplRepository::ImplDefSeq_var ims =
      imr->find_by_repoid_tag (repoid, tag);

  /*
   * Make sure that all available servers are active. Start them if
   * necessary. Queue request until all servers are up.
   */

  CORBA::Boolean queue = FALSE;
  CORBA::ULong count = 0;

  for (CORBA::ULong i=0; i<ims->length(); i++) {
    if (ims[i]->mode() != CORBA::ImplementationDef::ActivatePOA) {
      continue;
    }

    count++;

    SvInf &inf = svmap[ims[i]->name()];

    if (inf.pstate != Active) {
      if (!create_server (ims[i]->name())) {
	orb->answer_bind (id, CORBA::LocateUnknown,
			  CORBA::Object::_nil());
	return TRUE;
      }

      queue = TRUE;
    }
  }

  if (count == 0) {
    /*
     * No servers available
     */
    return FALSE;
  }

  if (queue) {
    invqueue.add (new MICO::ReqQueueRec (id, repoid, tag));
    return TRUE;
  }

  /*
   * Try all active servers in our map
   */

  MapSvInf::iterator it;
  
  /*
   * allocate slots for all bind requests, so that we can decide in
   * the callback() whether there are more outstanding requests or
   * not.
   */

  vector<MsgId> msgids;
  for (it = svmap.begin(); it != svmap.end(); it++) {
    if ((*it).second.pstate != Active) {
      continue;
    }
    msgids.push_back (orb->new_msgid());
    requests[msgids.back()] = id;
  }

  /*
   * now send the requests
   */

  for (it = svmap.begin(); it != svmap.end(); it++) {
    if ((*it).second.pstate != Active) {
      continue;
    }

    CORBA::Address * addr = (CORBA::Address *) (*it).second.ior.addr();
    assert (addr);

    assert (msgids.size() > 0);
    MsgId orbid = _orbnc()->bind_async (repoid, tag, addr, this,
					msgids.back());
    msgids.pop_back();
    assert (orbid != 0);
  }

  return TRUE;
}

CORBA::Boolean
POAMediatorImpl::locate (MsgId id, CORBA::Object_ptr)
{
  orb->answer_locate (id, CORBA::LocateHere, CORBA::Object::_nil());
  return TRUE;
}

CORBA::Object_ptr
POAMediatorImpl::skeleton (CORBA::Object_ptr)
{
  return CORBA::Object::_nil ();
}

void
POAMediatorImpl::cancel (MsgId id)
{
  int again = 1;
  while (again) {
    again = 0;
    MapIdId::iterator i;
    for (i = requests.begin(); i != requests.end(); ++i) {
      if ((*i).second == id) {
	orb->cancel ((*i).first);
	requests.erase (i);
	again = 1;
	break;
      }
    }
  }
}

void
POAMediatorImpl::shutdown_server ()
{
  /*
   * Signal servers
   */

  for (MapSvInf::iterator it = svmap.begin(); it != svmap.end(); it++) {
    if (((*it).second.pstate == Started || (*it).second.pstate == Active) &&
        (*it).second.proc != 0) {
      (*it).second.proc->terminate ();
    }
  }

  /*
   * Wait for callbacks to arrive
   */

  CORBA::Boolean waiting;
  OSMisc::TimeVal t1 = OSMisc::gettime ();
  OSMisc::TimeVal t2;

  do {
    waiting = FALSE;

    for (MapSvInf::iterator it = svmap.begin(); it != svmap.end(); it++) {
      if ((*it).second.pstate == Active && (*it).second.proc != 0) {
	waiting = TRUE;
      }
    }

    if (waiting) {
      orb->perform_work ();
    }
    t2 = OSMisc::gettime();
  }
  while (waiting && (t2.tv_sec - t1.tv_sec < 60));
}

void
POAMediatorImpl::shutdown (CORBA::Boolean wait_for_completion)
{
  invqueue.fail();
  orb->answer_shutdown (this);
}

void
POAMediatorImpl::answer_invoke (CORBA::ULong, CORBA::Object_ptr,
				CORBA::ORBRequest *, CORBA::InvokeStatus)
{
  assert (0);
}

/*
 * ORB Callback
 */

void
POAMediatorImpl::callback (CORBA::ORB_ptr orb, MsgId id,
			   CORBA::ORBCallback::Event ev)
{
  switch (ev) {
  case CORBA::ORBCallback::Invoke:
    {
      // an invocation completed ...
      CORBA::ORBRequest *req;
      CORBA::Object_var obj;
      CORBA::InvokeStatus stat = orb->get_invoke_reply (id, obj, req);

      MapIdId::iterator i = requests.find (id);
      assert (i != requests.end());

      orb->answer_invoke ((*i).second, stat, obj, req);
      requests.erase (i);
    }
    break;

  case CORBA::ORBCallback::Bind:
    {
      // a bind completed ...
      CORBA::Object_var obj;
      CORBA::LocateStatus stat = orb->get_bind_reply (id, obj);

      MapIdId::iterator i = requests.find (id);
      assert (i != requests.end());

      MsgId id2 = (*i).second;
      requests.erase (i);

      if (stat == CORBA::LocateHere) {
	// found matching object ...
	orb->answer_bind (id2, stat, obj);
	// cancel all binds resulting from the same bind "broadcast"
	cancel (id2);
      } else {
	/*
	 * not found, see if there are more outstanding requests
	 * from the same bind "broadcast" ...
	 */
	for (i = requests.begin(); i != requests.end(); ++i) {
	  if ((*i).second == id2)
	    break;
	}

	if (i == requests.end()) {
	  // ... its the last bind request; answer anyway
	  orb->answer_bind (id2, stat, obj);
	}

	// ignore, there are more outstanding bind requests ...
      }
    }
    break;

  default:
    assert (0);
  }
}

/*
 * Process Callback
 */

void
POAMediatorImpl::callback (MICO::Process * proc,
			   MICO::ProcessCallback::Event ev)
{
  /*
   * Find appropriate server
   */

  MapSvInf::iterator it;
  for (it = svmap.begin(); it != svmap.end(); it++) {
    if ((*it).second.proc == proc) {
      break;
    }
  }

  assert (it != svmap.end());

  /*
   * What's happened?
   */

  switch (ev) {
  case MICO::ProcessCallback::Exited:
    if ((*it).second.pstate == Active) {
      (*it).second.pstate = Inactive;
      delete (*it).second.proc;
      (*it).second.proc = 0;
    }
    else if ((*it).second.pstate == Started) {
      OSMisc::TimeVal ct = OSMisc::gettime();
      cerr << "*** server exited abnormally or could not be run:" << endl
	   << "    name: " << (*it).first << endl;
      (*it).second.pstate = Failed;
      (*it).second.failed = ct.tv_sec;

      /*
       * Fail pending requests
       */

      invqueue.exec_later();
    }
    break;

  default:
    assert (0);
  }
}

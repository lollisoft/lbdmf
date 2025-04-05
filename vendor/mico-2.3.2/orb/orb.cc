/*
 *  MICO --- a free CORBA implementation
 *  Copyright (C) 1997-98 Kay Roemer & Arno Puder
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Send comments and/or bug reports to:
 *                 mico@informatik.uni-frankfurt.de
 */

#include <CORBA.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/os-net.h>
#include <mico/imr_impl.h>
#include <mico/ir_impl.h>
#include <mico/impl.h>
#include <mico/ssl.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/poa_impl.h>
#include <mico/dynany_impl.h>
#ifdef _WINDOWS
#include <mico/process_impl.h>
#endif
#include <mico/throw.h>
#include <algorithm>
#ifdef USE_MEMTRACE
#include <mico/memtrace.h>
#endif

/************************** misc dtors ****************************/


CORBA::ObjectAdapter::~ObjectAdapter ()
{
}

CORBA::ORBCallback::~ORBCallback ()
{
}


/************************** ORBRequest ****************************/


CORBA::ORBRequest::~ORBRequest ()
{
}


/************************* ORBInvokeRecord ***************************/


CORBA::ORBInvokeRec::ORBInvokeRec ()
{
    _have_result = FALSE;
    _type = RequestUnknown;
    _obj = 0;
    _target = 0;
    _principal = 0;
    _req = 0;
}

void
CORBA::ORBInvokeRec::init_invoke (ORB_ptr orb, MsgId id,
				  Object_ptr o, ORBRequest *r,
				  Principal_ptr pr,
				  Boolean response,
				  ORBCallback *callback, ObjectAdapter *oa)
{
    _have_result = FALSE;
    _type = RequestInvoke;

    _orb = orb;
    _myid = id;
    _obj = Object::_nil();
    _target = Object::_duplicate (o);
    _req = CORBA::ORBRequest::_duplicate (r);
    _principal = Principal::_duplicate (pr);
    _response_expected = response;
    _addr = 0;
    _adapter = oa;
    _cb = callback;
}

void
CORBA::ORBInvokeRec::init_bind (ORB_ptr orb, MsgId id, const char *repo,
				const OctetSeq &tag, Address *a,
				ORBCallback *callback, ObjectAdapter *oa)
{
    _have_result = FALSE;
    _type = RequestBind;
    
    _orb = orb;
    _myid = id;
    _obj = Object::_nil();
    _target = Object::_nil();
    _req = CORBA::ORBRequest::_nil();
    _principal = Principal::_nil();
    _response_expected = TRUE;
    _repoid = repo;
    _addr = a;
    _adapter = oa;
    _cb = callback;
    _objtag = tag;
}

void
CORBA::ORBInvokeRec::init_locate (ORB_ptr orb, MsgId id, Object_ptr o,
				  ORBCallback *callback, ObjectAdapter *oa)
{
    _have_result = FALSE;
    _type = RequestLocate;
    
    _orb = orb;
    _myid = id;
    _obj = Object::_nil();
    _target = Object::_duplicate (o);
    _req = CORBA::ORBRequest::_nil();
    _principal = Principal::_nil();
    _response_expected = TRUE;
    _addr = 0;
    _adapter = oa;
    _cb = callback;
}

CORBA::ORBInvokeRec::~ORBInvokeRec ()
{
    // if caller needs the object then he must _duplicate() it
    CORBA::release (_obj);
    CORBA::release (_target);
    CORBA::release (_principal);
    CORBA::release (_req);
}

void
CORBA::ORBInvokeRec::free ()
{
    CORBA::release (_obj);
    CORBA::release (_target);
    CORBA::release (_principal);
    CORBA::release (_req);

    _have_result = FALSE;
    _type = RequestUnknown;
    _obj = 0;
    _target = 0;
    _principal = 0;
    _req = 0;
}

void
CORBA::ORBInvokeRec::redo ()
{
    assert (_adapter);
    assert (!_have_result);

    switch (_type) {
    case RequestInvoke:
        // fallback to initial location ...
        _target->_unforward();
	_adapter->invoke (_myid, _target, _req, _principal,
			  _response_expected);
	break;

    case RequestLocate:
	_adapter->locate (_myid, _target);
	break;

    case RequestBind:
	_adapter->bind (_myid, _repoid.c_str(), _objtag, _addr);
	break;

    default:
        assert (0);
    }
}

void
CORBA::ORBInvokeRec::set_answer_invoke (InvokeStatus state,
					Object_ptr o,
					ORBRequest *r)
{
    assert (_type == RequestInvoke);
    assert (!_have_result);

    _have_result = TRUE;
    _invoke_stat = state;

    switch (state) {
    case InvokeOk:
    case InvokeUsrEx:
    case InvokeSysEx:
        if (!_req->copy_out_args (r)) {
            CORBA::MARSHAL ex;
            _req->set_out_args (&ex);
            _invoke_stat = InvokeSysEx;
        }
	break;

    case InvokeForward:
	_obj = Object::_duplicate (o);
	break;

    default:
	assert (0);
    }
}

void
CORBA::ORBInvokeRec::set_answer_bind (LocateStatus state, Object_ptr o)
{
    assert (_type == RequestBind);
    assert (!_have_result);

    _have_result = TRUE;
    _locate_stat = state;

    switch (state) {
    case LocateForward:
    case LocateUnknown:
	break;

    case LocateHere:
	_obj = Object::_duplicate (o);
	break;

    default:
	assert (0);
    }
}

void
CORBA::ORBInvokeRec::set_answer_locate (LocateStatus state, Object_ptr o)
{
    assert (_type == RequestLocate);
    assert (!_have_result);

    _have_result = TRUE;
    _locate_stat = state;

    switch (state) {
    case LocateHere:
    case LocateUnknown:
	break;

    case LocateForward:
	_obj = Object::_duplicate (o);
	break;

    default:
	assert (0);
    }
}

CORBA::Boolean
CORBA::ORBInvokeRec::get_answer_invoke (InvokeStatus &state, Object_ptr &o,
					ORBRequest *&r)
{
    assert (_type == RequestInvoke);
    if (!_have_result)
        return FALSE;

    o = _obj;
    state = _invoke_stat;
    r = _req;
    return TRUE;
}

CORBA::Boolean
CORBA::ORBInvokeRec::get_answer_bind (LocateStatus &state, Object_ptr &o)
{
    assert (_type == RequestBind);
    if (!_have_result)
        return FALSE;

    o = _obj;
    state = _locate_stat;
    return TRUE;
}

CORBA::Boolean
CORBA::ORBInvokeRec::get_answer_locate (LocateStatus &state, Object_ptr &o)
{
    assert (_type == RequestLocate);
    if (!_have_result)
        return FALSE;

    o = _obj;
    state = _locate_stat;
    return TRUE;
}


/**************************** ORB *********************************/


CORBA::ORB::ORB (int &argc, char **argv, const char *rcfile)
{
    _disp = new MICO::SelectDispatcher ();
    _theid = 1;
    _rcfile = rcfile;
    _wait_for_completion = FALSE;
    _is_running = FALSE;
    _is_stopped = TRUE;
    _is_shutdown = FALSE;

    _cache_used = FALSE;
    _cache_rec = new ORBInvokeRec;

    _tmpl = new IOR;
}

CORBA::ORB::~ORB ()
{
    delete _cache_rec;
    delete _disp;
    delete _tmpl;

    map<MsgId, ORBInvokeRec *, less<MsgId> >::iterator i;
    for (i = _invokes.begin(); i != _invokes.end(); ++i)
	delete (*i).second;
}

/*
 * iioploc://[<addrlist>][/<URL-encoded-object-key>]
 */

CORBA::Object_ptr
CORBA::ORB::iioploc_to_object (const char * str)
{
  string iioploc (str);
  size_t pos = iioploc.find ("//");

  if (strncmp (str, "iioploc:", 8) != 0 || pos != 8) {
    mico_throw (BAD_PARAM());
  }

  string addresses;
  Octet * key;
  ULong len;

  size_t pos2 = iioploc.find ('/', pos+2);

  if (pos2 != (size_t) -1) {
    addresses = iioploc.substr (pos+2, pos2-pos-2);
    key = mico_url_decode (iioploc.substr(pos2+1).c_str(), len);
  }
  else {
    addresses = iioploc.substr (pos+2);
    len = 0;
    key = NULL;
  }

  if (addresses.length() == 0) {
    addresses = MICO::InetAddress::hostname();
  }

  IOR * ior = new IOR;
  ULong profiles=0;

  while (addresses.length()) {
    string version, host, port;

    if ((pos = addresses.find(',')) == (size_t) -1) {
      host = addresses;
      addresses = "";
    }
    else {
      host = addresses.substr (0, pos);
      addresses = addresses.substr (pos+1);
    }

    if ((pos = host.find ('@')) != (size_t) -1) {
      version = host.substr (0, pos);
      host = host.substr (pos+1);
    }
    else {
      version = "1.0";
    }

    if ((pos = host.find (':')) != (size_t) -1) {
      port = host.substr (pos+1);
      host = host.substr (0, pos);
    }
    else {
      port = "9999"; // XXX not fixed yet
    }

    if (host.length() == 0) {
      host = MICO::InetAddress::hostname();
    }

    if ((pos = version.find ('.')) == (size_t) -1) {
      mico_throw (BAD_PARAM());
    }

    UShort portno = atoi (port.c_str());
    UShort major, minor;

    major = (UShort) atoi (version.c_str());
    minor = (UShort) atoi (version.c_str() + pos + 1);

    // add profile

    MICO::InetAddress * addr = new MICO::InetAddress (host.c_str(), portno);

    if (!addr->valid()) {
      delete addr;
      mico_throw (BAD_PARAM());
    }

    MICO::IIOPProfile * prof = new MICO::IIOPProfile (key, len, *addr,
						      MultiComponent(),
						      major*256+minor);

    ior->add_profile (prof);
    delete addr;
    profiles++;
  }

  CORBA::string_free ((char *) key);

  if (!profiles) {
    delete ior;
    mico_throw (BAD_PARAM());
  }    

  return ior_to_object (ior);
}

/*
 * iiopname://<addr>,<addr>[/<URL-encoded-object-key>]
 */

CORBA::Object_ptr
CORBA::ORB::iiopname_to_object (const char * str)
{
  string iiopname (str);
  size_t pos = iiopname.find ("//");

  if (strncmp (str, "iiopname:", 9) != 0 || pos != 9) {
    mico_throw (BAD_PARAM());
  }

  string addresses;
  string key;

  size_t pos2 = iiopname.find ('/', pos+2);

  if (pos2 != (size_t) -1) {
    addresses = iiopname.substr (pos+2, pos2-pos-2);
    key = iiopname.substr (pos2+1);
  }
  else {
    addresses = iiopname.substr (pos+2);
  }

  string nsloc = "iioploc://";
  nsloc += addresses;
  nsloc += '/';
  nsloc += "NameService";

  Object_var nsobj = string_to_object (nsloc.c_str());

  if (CORBA::is_nil (nsobj)) {
    return Object::_nil ();
  }

  /*
   * Empty key represents the root NamingContext itself
   */

  if (key.length() == 0) {
    return Object::_duplicate (nsobj);
  }

  /*
   * Ask Naming Service by DII. That saves a couple of kBs
   * by not needing to compile in the stubs
   */

  Request_var req = nsobj->_request ("resolve_str");
  *(req->arguments()->add(ARG_IN)->value()) <<= key.c_str();
  req->set_return_type (CORBA::_tc_Object);
  MICO_CATCHANY (req->invoke ());

  if (req->env()->exception()) {
    return Object::_nil ();
  }

  Object_var res;
  if (!(req->return_value() >>= CORBA::Any::to_object (res, NULL)))
    mico_throw (BAD_PARAM());

  IOR * ior = new IOR (*res->_ior());
  return ior_to_object (ior);
}

/*
 * file://[hostname]<full path name>
 */

CORBA::Object_ptr
CORBA::ORB::file_to_object (const char * str)
{
  string filename (str);
  size_t pos = filename.find ("//");

  if (strncmp (str, "file:", 5) != 0 || pos != 5) {
    mico_throw (BAD_PARAM());
  }

  size_t pos2 = filename.find ('/', pos+2);
  if (pos2 == (size_t) -1) {
    mico_throw (BAD_PARAM());
  }

  string host = filename.substr (pos+2, pos2-pos-2);
  filename = filename.substr (pos2);

  if (host.length() > 0 &&
      strcmp (host.c_str(), "localhost") != 0 &&
      strcmp (host.c_str(), "127.0.0.1") != 0) {
    MICO::InetAddress i1 (host.c_str(), 0);
    MICO::InetAddress i2 ("localhost", 0);
    if (!i1.valid() || !i2.valid() || i1.compare (i2) != 0) {
      mico_throw (BAD_PARAM());
    }
  }

  CORBA::ULong len;
  CORBA::String_var fn =
    (char *) mico_url_decode (filename.c_str(), len);
  string ntfn (fn.in(), len);

  ifstream in (ntfn.c_str());
  string data;
  char buf[257];
  int count;

  while (in.good() && !in.eof()) {
    count = in.read (buf, 256).gcount();
    buf[count] = '\0';
    data += buf;
  }

  while (data.length() &&
	 (data[data.length()-1] == '\r' || data[data.length()-1] == '\n')) {
    data.resize (data.length()-1);
  }

  return string_to_object (data.c_str());
}

/*
 * http://host[:port][<abs_path>]
 */

CORBA::Object_ptr
CORBA::ORB::http_to_object (const char * str)
{
  string url (str);
  size_t pos = url.find ("//");
  string host, port, abs_path;

  if (pos != 5) {
    mico_throw (BAD_PARAM());
  }

  size_t pos2 = url.find ('/', pos+2);

  if (pos2 != (size_t) -1) {
    abs_path = url.substr (pos2);
    host = url.substr (pos+2, pos2-pos-2);
  }
  else {
    abs_path = "/";
    host = url;
  }

  if ((pos = host.find (':')) != (size_t) -1) {
    port = host.substr (pos+1);
    host = host.substr (0, pos-1);
  }
  else {
    port = "80";
  }

  UShort portno = atoi (port.c_str());

  MICO::InetAddress * addr = new MICO::InetAddress (host.c_str(), portno);

  if (!addr->valid()) {
    delete addr;
    mico_throw (BAD_PARAM());
  }

  CORBA::Transport * trans = addr->make_transport ();

  if (!trans || trans->bad() || !trans->connect(addr)) {
    delete trans;
    delete addr;
    mico_throw (BAD_PARAM());
  }

  delete addr;

  /*
   * For simplicity, speak HTTP/0.9
   */

  if (trans->write ("GET ", 4) != 4 ||
      trans->write ((void *) abs_path.c_str(),
		    abs_path.length()) != abs_path.length() ||
      trans->write ("\r\n\r\n", 4) != 4) {
    delete trans;
    mico_throw (BAD_PARAM());
  }

  /*
   * Read response
   */

  string data;
  char buf[257];

  while (!trans->eof() && !trans->bad()) {
    CORBA::Long got = trans->read (buf, 256);
    if (got > 0) {
      buf[got] = '\0';
      data += buf;
    }
  }

  if (trans->bad()) {
    delete trans;
    mico_throw (BAD_PARAM());
  }

  delete trans;

  while (data.length() &&
	 (data[data.length()-1] == '\r' || data[data.length()-1] == '\n')) {
    data.resize (data.length()-1);
  }

  return string_to_object (data.c_str());
}

char *
CORBA::ORB::object_to_string (Object_ptr obj)
{
    MICO_OBJ_CHECK (this);

    if (CORBA::is_nil (obj)) {
	CORBA::IOR ior;
	return CORBA::string_dup (ior.stringify().c_str());
    }

    MICO_OBJ_CHECK2 (obj, CORBA::OBJECT_NOT_EXIST());

    if (!obj->_ior())
	// locality constrained object
	mico_throw (MARSHAL());
    return CORBA::string_dup (obj->_ior()->stringify().c_str());
}

CORBA::Object_ptr
CORBA::ORB::string_to_object (const char *str)
{
    MICO_OBJ_CHECK (this);

    if (!str)
	mico_throw (CORBA::BAD_PARAM());

    if (strncmp (str, "IOR:", 4) == 0) {
	IOR *ior = new IOR;
	if (!ior->from_string (str)) {
	    delete ior;
	    mico_throw (CORBA::BAD_PARAM());
	}
	return ior_to_object (ior);
    } else if (strncmp (str, "iioploc:", 8) == 0) {
	return iioploc_to_object (str);
    } else if (strncmp (str, "iiopname:", 9) == 0) {
	return iiopname_to_object (str);
    } else if (strncmp (str, "file:", 5) == 0) {
        return file_to_object (str);
    } else if (strncmp (str, "http:", 5) == 0) {
        return http_to_object (str);
    } else {
	mico_throw (CORBA::BAD_PARAM());
	// to make some compilers happy
	return Object::_nil();
    }
}

CORBA::Object_ptr
CORBA::ORB::ior_to_object (IOR *ior)
{
    if (!ior->profile()) {
	delete ior;
	return CORBA::Object::_nil();
    }

    Object_var obj = new Object (ior);
    obj->_setup_domains (CORBA::Object::_nil());

    ObjectAdapter *oa = get_oa (obj);
    if (oa && oa->is_local ()) {
	CORBA::Object_var skel = oa->skeleton (obj);
	if (!CORBA::is_nil (skel)) {
	    return Object::_duplicate (skel);
	}
    }
    return Object::_duplicate (obj);
}

CORBA::Boolean
CORBA::ORB::is_impl (Object_ptr obj)
{
    ObjectAdapter *oa = get_oa (obj);
    if (!oa || !oa->is_local()) {
      return FALSE;
    }
    CORBA::Object_var skel = oa->skeleton (obj);
    return obj == skel;
}

const char *
CORBA::ORB::rcfile()
{
    return _rcfile.c_str();
}

char *
CORBA::ORB::tag_to_string (const ObjectTag &oid)
{
    string s;

    for (CORBA::ULong i = 0; i < oid.length(); ++i) {
	assert ((CORBA::Octet)oid[i]);
	s += (char)(CORBA::Octet)oid[i];
    }
    return CORBA::string_dup (s.c_str());
}

CORBA::ORB::ObjectTag *
CORBA::ORB::string_to_tag (const char *s)
{
    CORBA::ULong len = strlen (s);

    CORBA::ORB::ObjectTag *oid = new CORBA::ORB::ObjectTag;
    oid->length (len);

    for (CORBA::ULong i = 0; i < len; ++i) {
        (*oid)[i] = (CORBA::Octet) s[i];
    }
    return oid;
}

void
CORBA::ORB::create_list (Long len, NVList_ptr &res)
{
    if (len < 0)
	mico_throw (CORBA::BAD_PARAM());

    res = new NVList (len);
}

void
CORBA::ORB::create_operation_list (OperationDef_ptr op, NVList_ptr &res)
{
    res = new NVList (0);
    ParDescriptionSeq_var params = op->params();
    for (CORBA::ULong i = 0; i < params->length(); ++i) {
	switch (params[i].mode) {
	case PARAM_IN:
	    res->add(ARG_IN)->value()->set_type (params[i].type);
	    break;
	case PARAM_OUT:
	    res->add(ARG_OUT)->value()->set_type (params[i].type);
	    break;
	case PARAM_INOUT:
	    res->add(ARG_INOUT)->value()->set_type (params[i].type);
	    break;
	default:
	    assert (0);
	}
    }
}

void
CORBA::ORB::create_named_value (NamedValue_ptr &res)
{
    res = new NamedValue;
}

void
CORBA::ORB::create_exception_list (ExceptionList_ptr &res)
{
    res = new ExceptionList;
}

void
CORBA::ORB::create_context_list (ContextList_ptr &res)
{
    res = new ContextList;
}

void
CORBA::ORB::create_environment (Environment_ptr &res)
{
    res = new Environment;
}

void
CORBA::ORB::get_default_context (Context_ptr &res)
{
    res = new Context ("");
}

void
CORBA::ORB::get_default_domain_manager (DomainManager_ptr &dm)
{
    MICO_OBJ_CHECK (this);

    if (CORBA::is_nil (_def_manager)) {
	_def_manager = new MICO::DomainManager_impl;

	// install default policies ...
	MICOPolicy::TransportPrefPolicy::ProfileTagSeq prefs;
	prefs.length (6);

	prefs[0] = CORBA::IORProfile::TAG_INTERNET_IOP;
	prefs[1] = CORBA::IORProfile::TAG_UNIX_IOP;
	prefs[2] = CORBA::IORProfile::TAG_UDP_IOP;
	prefs[3] = CORBA::IORProfile::TAG_SSL_INTERNET_IOP;
	prefs[4] = CORBA::IORProfile::TAG_SSL_UNIX_IOP;
	prefs[5] = CORBA::IORProfile::TAG_SSL_UDP_IOP;

	MICOPolicy::TransportPrefPolicy_var tpp =
	    new MICO::TransportPrefPolicy_impl (prefs);

	_def_manager->set_domain_policy (tpp);
    }
    dm = CORBA::DomainManager::_duplicate (_def_manager);
}

CORBA::Boolean
CORBA::ORB::get_service_information (
    CORBA::ServiceType service_type,
    CORBA::ServiceInformation *& service_information)
{
    return FALSE;
}

void
CORBA::ORB::send_multiple_requests_oneway (const RequestSeq &req)
{
    for (CORBA::ULong i = 0; i < req.length(); ++i) {
	req[i]->send_oneway ();
    }
}

void
CORBA::ORB::send_multiple_requests_deferred (const RequestSeq &req)
{
    for (CORBA::ULong i = 0; i < req.length(); ++i) {
	req[i]->send_deferred ();
    }
}

CORBA::Boolean
CORBA::ORB::poll_next_response ()
{
    MICO_OBJ_CHECK (this);

    ORBInvokeRec *rec;
    ORBRequest *orbreq;

    if (_cache_used) {
      if (_cache_rec->request_type() == RequestInvoke &&
	  _cache_rec->completed() &&
	  !strcmp (_cache_rec->request()->type(), "local")) {
	return TRUE;
      }
    }

    for (InvokeMap::iterator i = _invokes.begin(); i != _invokes.end(); ++i) {
	rec = (*i).second;
	orbreq = rec->request ();
	if (rec->request_type() == RequestInvoke &&
	    rec->completed() &&
	    !strcmp (orbreq->type(), "local")) {
	    // found a local request that has completed
	    return TRUE;
	}
    }
    return FALSE;
}

void
CORBA::ORB::get_next_response (Request_ptr &req)
{
    MICO_OBJ_CHECK (this);

    ORBInvokeRec *rec;
    ORBRequest *orbreq;

    if (_cache_used) {
      if (_cache_rec->request_type() == RequestInvoke &&
	  _cache_rec->completed() &&
	  !strcmp (_cache_rec->request()->type(), "local")) {
	req = Request::_duplicate (((MICO::LocalRequest *)(_cache_rec->request()))->request());
	return;
      }
    }

    for (InvokeMap::iterator i = _invokes.begin(); i != _invokes.end(); ++i) {
	rec = (*i).second;
	orbreq = rec->request ();
	if (rec->request_type() == RequestInvoke &&
	    rec->completed() &&
	    !strcmp (orbreq->type(), "local")) {
	    // found a local request that has completed
	    req = Request::_duplicate (
		((MICO::LocalRequest *)orbreq)->request());
	    return;
	}
    }
    req = Request::_nil();
}

void
CORBA::ORB::do_shutdown ()
{
    if (!_is_shutdown) {
	_is_shutdown = 1;

	if (_wait_for_completion)
	    _shutting_down_adapters = _adapters;

	// work on copy in case OA's unregister ifself during shutdown ...
	OAVec adapters_copy = _adapters;
        for (ULong i = 0; i < adapters_copy.size(); ++i) {
	    adapters_copy[i]->shutdown (_wait_for_completion);
	}
	if (_wait_for_completion) {
	    while (_shutting_down_adapters.size() > 0)
		_disp->run (FALSE);
	}
        _is_shutdown = 2;
    }
}

CORBA::Boolean
CORBA::ORB::work_pending ()
{
    if (_is_shutdown > 1)
        mico_throw (CORBA::BAD_INV_ORDER (4, CORBA::COMPLETED_NO));

    // if !stopped run() has been called and cares for events ...
    return !_disp->idle();
}

void
CORBA::ORB::perform_work ()
{
    if (_is_shutdown > 1)
        mico_throw (CORBA::BAD_INV_ORDER (4, CORBA::COMPLETED_NO));

    _disp->run (FALSE);
}

void
CORBA::ORB::run ()
{
    assert (!_is_running);
    _is_running = TRUE;
    _is_stopped = FALSE;
    while (!_is_stopped)
	_disp->run (FALSE);

    do_shutdown ();
}

void
CORBA::ORB::answer_shutdown (ObjectAdapter *oa)
{
    for (ULong i = 0; i < _shutting_down_adapters.size(); ++i) {
	if (_shutting_down_adapters[i] == oa) {
	    _shutting_down_adapters.erase (_shutting_down_adapters.begin()+i);
	    break;
	}
    }
}

void
CORBA::ORB::shutdown (Boolean wait)
{
    _wait_for_completion = wait;
    _is_stopped = TRUE;

    // if run() has been called it will perform the shutdown,
    // otherwise do it right now...
    if (!_is_running)
	do_shutdown();
}

void
CORBA::ORB::destroy ()
{
    // XXX shutdown and destroy ORB; calling ORB_init() afterwards
    // must create a new ORB instance
}

CORBA::BOA_ptr
CORBA::ORB::BOA_init (int &argc, char **argv, const char *_id)
{
    string id = _id;

    MICOGetOpt::OptMap opts;
    opts["-OAId"] = "arg-expected";

    MICOGetOpt opt_parser (opts);
    if (!opt_parser.parse (rcfile(), TRUE))
	mico_throw (CORBA::INITIALIZE());
    if (!opt_parser.parse (argc, argv, TRUE))
	mico_throw (CORBA::INITIALIZE());
    const MICOGetOpt::OptVec &o = opt_parser.opts();

    for (MICOGetOpt::OptVec::const_iterator i0 = o.begin(); i0 != o.end(); ++i0) {
	string arg = (*i0).first;
	string val = (*i0).second;
	if (arg == "-OAId") {
	    if (id.length() == 0)
		id = val;
	}
    }

    for (ULong i1 = 0; i1 < _adapters.size(); ++i1) {
	if (!strcmp (id.c_str(), _adapters[i1]->get_oaid()))
	    return CORBA::BOA::_duplicate ((MICO::BOAImpl *)_adapters[i1]);
    }
    if (id.length() > 0 && strcmp ("mico-local-boa", id.c_str())) {
	MICODebug::instance()->printer()
	    << "ORB::BOA_init(): unknown OA id: " << id << endl;
	mico_throw (CORBA::INITIALIZE());
    }
    CORBA::BOA_ptr boa = new MICO::BOAImpl (this, argc, argv);

    // make sure iface and impl repository are active ...
    Object_var obj;
#if 0
    obj = resolve_initial_references ("InterfaceRepository");
#endif
    obj = resolve_initial_references ("LocalImplementationRepository");
    return CORBA::BOA::_duplicate (boa);
}

CORBA::BOA_ptr
CORBA::ORB::BOA_instance (const char *id, Boolean create)
{
    for (ULong i = 0; i < _adapters.size(); ++i) {
	if (!strcmp (id, _adapters[i]->get_oaid()))
	    return CORBA::BOA::_duplicate ((MICO::BOAImpl *)_adapters[i]);
    }
    if (!create)
	return BOA::_nil();
    int argc = 0;
    char *argv = 0;
    return BOA_init (argc, &argv, id);
}

CORBA::ORB::ObjectIdList *
CORBA::ORB::list_initial_services ()
{
    MICO_OBJ_CHECK (this);

    ObjectIdList_ptr idlist = new ObjectIdList;
    idlist->length (_init_refs.size());

    int j;
    InitialRefMap::iterator i;
    for (j = 0, i = _init_refs.begin(); i != _init_refs.end(); ++i, ++j)
	(*idlist)[j] = (*i).first.c_str();

    if (!_init_refs.count ("ImplementationRepository")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"ImplementationRepository";
    }
    if (!_init_refs.count ("LocalImplementationRepository")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"LocalImplementationRepository";
    }
    if (!_init_refs.count ("InterfaceRepository")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"InterfaceRepository";
    }
    if (!_init_refs.count ("RootPOA")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"RootPOA";
    }
    if (!_init_refs.count ("POACurrent")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"POACurrent";
    }
    if (!_init_refs.count ("DynAnyFactory")) {
	idlist->length (j+1);
	(*idlist)[j++] = (const char *)"DynAnyFactory";
    }
    return idlist;
}

CORBA::Object_ptr
CORBA::ORB::resolve_initial_references (const char *id)
{
    MICO_OBJ_CHECK (this);

    InitialRefMap::iterator i = _init_refs.find (id);

    if (i == _init_refs.end()) {
        if (_default_init_ref.length() > 0) {
	  string loc = _default_init_ref;
	  loc += '/';
	  loc += id;
	  CORBA::Object_ptr res = string_to_object (loc.c_str());
	  if (!CORBA::is_nil (res)) {
	    return res;
	  }
	}

	if (!strcmp (id, "ImplementationRepository")) {
	    _init_refs[id] = new ImplRepository_impl;
	} else if (!strcmp (id, "LocalImplementationRepository")) {
            CORBA::Object_var o = resolve_initial_references (
                "ImplementationRepository");
            if (!is_impl (o))
                o = new ImplRepository_impl;
	    _init_refs[id] = o._retn();
	} else if (!strcmp (id, "InterfaceRepository")) {
	    _init_refs[id] = new Repository_impl;
	} else if (!strcmp (id, "RootPOA")) {
	  PortableServer::POA_var rootpoa = new MICOPOA::POA_impl (this);
	} else if (!strcmp (id, "POACurrent")) {
	  // RootPOA initializes POACurrent
	  PortableServer::POA_var rootpoa = new MICOPOA::POA_impl (this);
	} else if (!strcmp (id, "DynAnyFactory")) {
	  _init_refs[id] = new DynAnyFactory_impl;
	} else {
	    MICODebug::instance()->debugger()
		<< "ORB::resolve_initial_references(): bad id: " << id << endl;
	    mico_throw (CORBA::ORB::InvalidName());
	}
	i = _init_refs.find (id);
    }
    return Object::_duplicate ((*i).second);
}

CORBA::Boolean
CORBA::ORB::set_initial_reference (const char *id, Object_ptr obj)
{
    _init_refs[id] = CORBA::Object::_duplicate (obj);
    return TRUE;
}

CORBA::Boolean
CORBA::ORB::set_default_initial_reference (const char * url)
{
  _default_init_ref = url;
  return TRUE;
}

CORBA::TypeCode_ptr
CORBA::ORB::create_struct_tc (const char *rep_id,
			      const char *name,
			      const StructMemberSeq &members)
{
    return TypeCode::create_struct_tc (rep_id, name, members);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_union_tc (const char *rep_id,
			     const char *name,
			     TypeCode_ptr disc_type,
			     const UnionMemberSeq &members)
{
    return TypeCode::create_union_tc (rep_id, name, disc_type, members);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_enum_tc (const char *rep_id,
			    const char *name,
			    const EnumMemberSeq &members)
{
    return TypeCode::create_enum_tc (rep_id, name, members);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_exception_tc (const char *rep_id,
				 const char *name,
				 const StructMemberSeq &mems)
{
    return TypeCode::create_exception_tc (rep_id, name, mems);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_alias_tc (const char *rep_id,
			     const char *name,
			     TypeCode_ptr orig_type)
{
    return TypeCode::create_alias_tc (rep_id, name, orig_type);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_interface_tc (const char *rep_id, const char *name)
{
    return TypeCode::create_interface_tc (rep_id, name);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_string_tc (ULong bound)
{
    return TypeCode::create_string_tc (bound);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_wstring_tc (ULong bound)
{
    return TypeCode::create_wstring_tc (bound);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_fixed_tc (UShort digits, Short scale)
{
    return TypeCode::create_fixed_tc (digits, scale);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_sequence_tc (ULong bound, TypeCode_ptr el_type)
{
    return TypeCode::create_sequence_tc (bound, el_type);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_recursive_sequence_tc (ULong bound, ULong offset)
{
    return TypeCode::create_recursive_sequence_tc (bound, offset);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_array_tc (ULong length, TypeCode_ptr el_type)
{
    return TypeCode::create_array_tc (length, el_type);
}


CORBA::TypeCode_ptr
CORBA::ORB::create_value_tc (const char *rep_id, const char *name,
			     ValueModifier mod,
			     TypeCode_ptr concrete_base,
			     const ValueMemberSeq &members)
{
    return TypeCode::create_value_tc (rep_id, name, mod,
				      concrete_base, members);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_value_box_tc (const char *rep_id,
				 const char *name,
				 TypeCode_ptr boxed_type)
{
    return TypeCode::create_value_box_tc (rep_id, name, boxed_type);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_native_tc (const char *rep_id,
			      const char *name)
{
    return TypeCode::create_native_tc (rep_id, name);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_recursive_tc (const char *rep_id)
{
    return TypeCode::create_recursive_tc (rep_id);
}

CORBA::TypeCode_ptr
CORBA::ORB::create_abstract_interface_tc (const char *rep_id,
					  const char *name)
{
    return TypeCode::create_abstract_interface_tc (rep_id, name);
}

CORBA::ObjectAdapter *
CORBA::ORB::get_oa (Object_ptr o)
{
    for (ULong i0 = 0; i0 < _adapters.size(); ++i0) {
	if (_adapters[i0]->has_object (o))
	    return _adapters[i0];
    }
    return NULL;
}

CORBA::ORB::MsgId
CORBA::ORB::new_msgid ()
{
    if (_theid == 0)
        _theid = 1;
    return _theid++;
}

CORBA::ORBInvokeRec *
CORBA::ORB::create_invoke ()
{
    if (!_cache_used) {
	_cache_used = TRUE;
	return _cache_rec;
    }
    return new ORBInvokeRec;
}

void
CORBA::ORB::add_invoke (ORBInvokeRec *rec)
{
    if (rec == _cache_rec)
	return;

    _invokes[rec->id()] = rec;
}

CORBA::ORBInvokeRec *
CORBA::ORB::get_invoke (MsgId id)
{
    if (_cache_used && _cache_rec->id() == id)
	return _cache_rec;

    map<MsgId, ORBInvokeRec *, less<MsgId> >::iterator i;
    i = _invokes.find (id);
    if (i == _invokes.end())
	return NULL;
    return (*i).second;
}

void
CORBA::ORB::del_invoke (MsgId id)
{
    if (_cache_used && _cache_rec->id() == id) {
	_cache_rec->free();
	_cache_used = FALSE;
	return;
    }

    map<MsgId, ORBInvokeRec *, less<MsgId> >::iterator i;
    i = _invokes.find (id);
    if (i != _invokes.end()) {
	delete (*i).second;
	_invokes.erase (i);
    }
}

void
CORBA::ORB::dispatcher (Dispatcher *new_disp)
{
    if (new_disp) {
	// move the pending events from disp to _disp
	_disp->move (new_disp);
    }
    if (_disp) {
	delete _disp;
    }
    _disp = new_disp;
}

void
CORBA::ORB::register_oa (ObjectAdapter *oa, CORBA::UShort prio)
{
    OAVec::iterator i = _adapters.end();
    if (_adapters.size() > 0) {
	do {
	    --i;
	    if (prio < (*i)->priority()) {
		++i;
		break;
	    }
	} while (i != _adapters.begin());
    }
    oa->priority (prio);
    _adapters.insert (i, oa);
}

void
CORBA::ORB::unregister_oa (ObjectAdapter *oa)
{
    for (ULong i = 0; i < _adapters.size(); ) {
	if (_adapters[i] == oa)
	    _adapters.erase (_adapters.begin() + i);
	else
	    ++i;
    }
}

CORBA::Boolean
CORBA::ORB::builtin_invoke (MsgId msgid, Object_ptr obj,
                            ORBRequest *req, Principal_ptr pr)
{
    /*
     * _non_existent is the only special one, _implementation, _interface,
     * and _is_a are just passed through to the OA.
     */
    if (!strcmp (req->op_name(), "_non_existent")) {
        if (!get_oa (obj)) {
            Any res;
            res <<= Any::from_boolean (TRUE);
	    NVList nv;
            if (!req->set_out_args (&res, &nv)) {
                CORBA::MARSHAL ex;
                req->set_out_args (&ex);
                answer_invoke (msgid, InvokeSysEx, Object::_nil(), req);
            } else {
                answer_invoke (msgid, InvokeOk, Object::_nil(), req);
            }
            return TRUE;
        }
    }
    return FALSE;
}

CORBA::ORB::MsgId
CORBA::ORB::invoke_async (Object_ptr obj,
			  ORBRequest *req,
			  Principal_ptr pr,
			  Boolean response_exp,
			  ORBCallback *cb,
			  MsgId msgid)
{
    if (msgid == 0)
	msgid = new_msgid();
    ORBInvokeRec *rec = 0;
    if (response_exp) {
        rec = create_invoke();
	rec->init_invoke (this, msgid, obj, req, pr, response_exp, cb);
        add_invoke (rec);
    }

    if (!builtin_invoke (msgid, obj, req, pr)) {
        ObjectAdapter *oa = get_oa (obj);
	if (!oa) {
            CORBA::OBJECT_NOT_EXIST ex;
	    req->set_out_args (&ex);
	    answer_invoke (msgid, InvokeSysEx, Object::_nil(), req);
	    return msgid;
	}
        if (response_exp)
            rec->oa (oa);
        oa->invoke (msgid, obj, req, pr, response_exp);
    }
    return response_exp ? msgid : 0;
}

CORBA::ORB::MsgId
CORBA::ORB::locate_async (Object_ptr obj, ORBCallback *cb, MsgId msgid)
{
    ObjectAdapter *oa = get_oa (obj);
    if (msgid == 0)
	msgid = new_msgid();
    ORBInvokeRec *rec = create_invoke();
    rec->init_locate (this, msgid, obj, cb, oa);
    add_invoke (rec);

    if (!oa) {
        answer_locate (msgid, LocateUnknown, Object::_nil());
    } else {
        oa->locate (msgid, obj);
    }
    return msgid;
}

CORBA::ORB::MsgId
CORBA::ORB::bind_async (const char *repoid,
			const ObjectTag &oid,
			Address *addr, ORBCallback *cb,
			MsgId msgid)
{
    if (msgid == 0)
	msgid = new_msgid();
    ORBInvokeRec *rec = create_invoke();
    rec->init_bind (this, msgid, repoid, oid, addr, cb);
    add_invoke (rec);
    for (ULong i = 0; i < _adapters.size(); ++i) {
	rec->oa (_adapters[i]);
        if (_adapters[i]->bind (msgid, repoid, rec->tag(), addr))
	    return msgid;
    }
    answer_bind (msgid, LocateUnknown, Object::_nil());
    return msgid;
}

CORBA::InvokeStatus
CORBA::ORB::invoke (Object_ptr &obj, ORBRequest *req,
		    Principal_ptr pr, Boolean reply_exp)
{
    MsgId id = invoke_async (obj, req, pr, reply_exp);
    if (!reply_exp)
	return InvokeOk;
    assert (id != 0);
    CORBA::Boolean r = wait (id);
    assert (r);
    ORBRequest *dummy;
    return get_invoke_reply (id, obj, dummy);
}

CORBA::LocateStatus
CORBA::ORB::locate (Object_ptr &obj)
{
    MsgId id = locate_async (obj);
    CORBA::Boolean r = wait (id);
    assert (r);
    return get_locate_reply (id, obj);
}

CORBA::LocateStatus
CORBA::ORB::bind (const char *repoid, const ObjectTag &oid,
		  Address *addr, Object_ptr &obj)
{
    MsgId id = bind_async (repoid, oid, addr);
    if (id == 0)
	return LocateUnknown;
    CORBA::Boolean r = wait (id);
    assert (r);
    return get_bind_reply (id, obj);
}

CORBA::Object_ptr
CORBA::ORB::bind (const char *repoid, const ObjectTag &oid, const char *addr)
{
    vector<string> *addrs, _addrs;
    if (addr) {
	// use given address
	_addrs.push_back (addr);
	addrs = &_addrs;
    } else {
	// use default addresses
	addrs = &_bindaddrs;
    }

    Address *a;
    for (mico_vec_size_type i = 0; i < addrs->size(); ++i) {
	a = Address::parse ((*addrs)[i].c_str());
	if (a) {
	    Object_ptr obj;
	    LocateStatus s = bind (repoid, oid, a, obj);
	    delete a;
	    if (s == LocateHere)
		return obj;
	} else {
	    MICODebug::instance()->printer()
		<< "ORB::bind(): bad address: " << (*addrs)[i] << endl;
	}
    }
    return Object::_nil();
}

CORBA::Object_ptr
CORBA::ORB::bind (const char *repoid, const char *addr)
{
    return bind (repoid, ObjectTag(), addr);
}

void
CORBA::ORB::cancel (MsgId id)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (rec) {
        if (rec->oa())
            rec->oa()->cancel (id);
	del_invoke (id);
    }
}

CORBA::Long
CORBA::ORB::wait (vector<MsgId> &ids, Long tmout)
{
    Timeout t (_disp, tmout);
    ORBInvokeRec *rec;

    while (42) {
	vector<MsgId> ready;
	for (mico_vec_size_type i = 0; i < ids.size(); ++i) {
	    rec = get_invoke (ids[i]);
	    if (!rec || rec->completed())
		ready.push_back (ids[i]);
	}
	if (ready.size() > 0) {
	    ids = ready;
	    return ids.size();
	}
	if (t.done())
	    return 0;
	_disp->run (FALSE);
    }
}

CORBA::Boolean
CORBA::ORB::wait (MsgId id, Long tmout)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (tmout == 0) {
      if (!rec || rec->completed()) {
	return TRUE;
      }
    }

    Timeout t (_disp, tmout);

    while (42) {
        if (!rec || rec->completed())
	    return TRUE;
	if (t.done())
	    return FALSE;
	_disp->run (FALSE);
        rec = get_invoke (id);
    }
}

CORBA::InvokeStatus
CORBA::ORB::get_invoke_reply (MsgId id, Object_ptr &obj, ORBRequest *&r)
{
    ORBInvokeRec *rec = get_invoke (id);
    assert (rec);

    InvokeStatus state;
    Object_ptr o;
    CORBA::Boolean ret = rec->get_answer_invoke (state, o, r);
    assert (ret);
    obj = Object::_duplicate (o);
    del_invoke (id);
    return state;
}

CORBA::LocateStatus
CORBA::ORB::get_locate_reply (MsgId id, Object_ptr &obj)
{
    ORBInvokeRec *rec = get_invoke (id);
    assert (rec);

    LocateStatus state;
    Object_ptr o;
    CORBA::Boolean r = rec->get_answer_locate (state, o);
    assert (r);
    obj = Object::_duplicate (o);
    del_invoke (id);
    return state;
}

CORBA::LocateStatus
CORBA::ORB::get_bind_reply (MsgId id, Object_ptr &obj)
{
    ORBInvokeRec *rec = get_invoke (id);
    assert (rec);

    LocateStatus state;
    Object_ptr o;
    CORBA::Boolean r = rec->get_answer_bind (state, o);
    assert (r);
    obj = Object::_duplicate (o);
    del_invoke (id);
    return state;
}

void
CORBA::ORB::answer_invoke (MsgId id, InvokeStatus stat, Object_ptr obj,
			   ORBRequest *req)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (rec) {
	rec->set_answer_invoke (stat, obj, req);
	if (rec->callback())
	    rec->callback()->callback (this, rec->id(), ORBCallback::Invoke);
    }
}

void
CORBA::ORB::answer_bind (MsgId id, LocateStatus stat, Object_ptr obj)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (rec) {
	rec->set_answer_bind (stat, obj);
	if (rec->callback())
	    rec->callback()->callback (this, rec->id(), ORBCallback::Bind);
    }
}

void
CORBA::ORB::answer_locate (MsgId id, LocateStatus stat, Object_ptr obj)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (rec) {
	rec->set_answer_locate (stat, obj);
	if (rec->callback())
	    rec->callback()->callback (this, rec->id(), ORBCallback::Locate);
    }
}

CORBA::RequestType
CORBA::ORB::request_type (MsgId id)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (!rec)
	return RequestUnknown;
    return rec->request_type ();
}

void
CORBA::ORB::redo_request (MsgId id)
{
    ORBInvokeRec *rec = get_invoke (id);
    if (rec) {
	rec->redo();
    } else {
	MICODebug::instance()->tracer()
	    << "ORB::redo_request: no such request " << id << endl;
    }
}

CORBA::ImplementationDef_ptr
CORBA::ORB::get_impl (Object_ptr obj)
{
    // [12-17]
    Request_var req = obj->_request ("_implementation");
    req->result()->value()->set_type (CORBA::_tc_ImplementationDef);
    MICO_CATCHANY (req->invoke ());
    if (req->env()->exception())
        mico_throw (*req->env()->exception());
    ImplementationDef_ptr impl;
    CORBA::Boolean r = (*req->result()->value() >>= impl);
    assert (r);
    return ImplementationDef::_duplicate (impl);
}

CORBA::InterfaceDef_ptr
CORBA::ORB::get_iface (Object_ptr obj)
{
    // [12-17]
    Request_var req = obj->_request ("_interface");
    req->result()->value()->set_type (CORBA::_tc_InterfaceDef);
    MICO_CATCHANY(req->invoke ());
    if (req->env()->exception())
        mico_throw (*req->env()->exception());
    InterfaceDef_ptr iface;
    CORBA::Boolean r = (*req->result()->value() >>= iface);
    assert (r);
    return InterfaceDef::_duplicate (iface);
}

CORBA::Boolean
CORBA::ORB::is_a (Object_ptr obj, const char *repo_id)
{
    // XXX this assumes RepoIds are globally unique
    if (*obj->_repoid()) {
      string key = string(obj->_repoid()) + "$" + repo_id;
      list<string>::iterator i;
      for (i = _isa_cache.begin(); i != _isa_cache.end(); ++i) {
        if (*i == key)
	  break;
      }
      if (i != _isa_cache.end()) {
        _isa_cache.erase (i);
        _isa_cache.push_front (key);
        return TRUE;
      }
    }

    // [12-17]
    Request_var req = obj->_request ("_is_a");
    req->add_in_arg ("logical_type_id") <<= repo_id;
    req->result()->value()->set_type (CORBA::_tc_boolean);
    MICO_CATCHANY(req->invoke ());
    if (req->env()->exception())
        mico_throw (*req->env()->exception());
    Boolean res;
    CORBA::Boolean r = (*req->result()->value() >>= Any::to_boolean (res));
    assert (r);

    if (res) {
      if (!*obj->_repoid()) {
	obj->_ior()->objid (repo_id);
      }
      else {
	string key = string(obj->_repoid()) + "$" + repo_id;
        _isa_cache.push_front (key);
        // XXX CACHE size = 50
        if (_isa_cache.size() > 50)
	  _isa_cache.pop_back();
      }
    }
    return res;
}

CORBA::Boolean
CORBA::ORB::non_existent (Object_ptr obj)
{
    // [12-17]
    Request_var req = obj->_request ("_non_existent");
    req->result()->value()->set_type (CORBA::_tc_boolean);
    MICO_CATCHANY(req->invoke ());
    Boolean res;
    if (req->env()->exception()) {
        // an exceptions means we cannot contact the object ...
        res = TRUE;
    } else {
        CORBA::Boolean r = (*req->result()->value() >>= Any::to_boolean (res));
	assert (r);
    }
    return res;
}


/*********************** ORB initialization **************************/


static CORBA::ORB_ptr orb_instance = CORBA::ORB::_nil();

CORBA::ORB_ptr
CORBA::ORB_instance (const char *id, Boolean create)
{
    if (strcmp ("mico-local-orb", id)) {
	MICODebug::instance()->printer()
	    << "ORB_instance(): unknown ORB id: " << id << endl;
	mico_throw (CORBA::INITIALIZE());
    }
    if (create && CORBA::is_nil (orb_instance)) {
	int argc = 0;
	char *argv = 0;
	return ORB_init (argc, &argv, id);
    }
    return ORB::_duplicate (orb_instance);
}

CORBA::ORB_ptr
CORBA::ORB_init (int &argc, char **argv, const char *_id)
{
    OSNet::sock_init();

    Exception::_init ();
    Codeset::_init ();
    MICOPOA::_init ();
#ifdef HAVE_SSL
    MICOSSL::_init ();
#endif
#ifdef _WINDOWS
    OSMisc::_init();
    MICO::UnixProcess::_init();
#endif
    Boolean run_iiop_server = TRUE;
    Boolean run_iiop_proxy = TRUE;
    Boolean iiop_blocking = FALSE;
    CORBA::Address *fwproxyaddr = 0;
    string imr_ior, imr_addr;
    string ir_ior, ir_addr;
    string naming_ior, naming_addr;
    string trading_ior, trading_addr;
    ULong debug_level = 0;
    vector<string> bindaddrs, iiopaddrs;
    string rcfile = "~/.micorc";
    string id = _id;
    bool memtrace = false;
    vector<string> InitRefs;
    string DefInitRef;

    const char *rc = getenv ("MICORC");
    if (rc)
        rcfile = rc;

    // look for config file name ...
    {
	MICOGetOpt::OptMap opts;
	opts["-ORBConfFile"] = "arg-expected";

	MICOGetOpt opt_parser (opts);

	if (!opt_parser.parse (argc, argv, TRUE))
	    mico_throw (CORBA::INITIALIZE());
	const MICOGetOpt::OptVec &o = opt_parser.opts();

	MICOGetOpt::OptVec::const_iterator i;
	for (i = o.begin(); i != o.end(); ++i) {
	    string arg = (*i).first;
	    string val = (*i).second;
	    if (arg == "-ORBConfFile") {
		rcfile = val;
	    }
	}
    }

    MICOGetOpt::OptMap opts;
    opts["-ORBNoIIOPServer"]  = "";
    opts["-ORBNoIIOPProxy"]   = "";
    opts["-ORBIIOPAddr"]      = "arg-expected";
    opts["-ORBIIOPProxy"]     = "arg-expected";
    opts["-ORBIIOPBlocking"]  = "";
    opts["-ORBId"]            = "arg-expected";
    opts["-ORBImplRepoIOR"]   = "arg-expected";
    opts["-ORBImplRepoAddr"]  = "arg-expected";
    opts["-ORBIfaceRepoIOR"]  = "arg-expected";
    opts["-ORBIfaceRepoAddr"] = "arg-expected";
    opts["-ORBNamingIOR"]     = "arg-expected";
    opts["-ORBNamingAddr"]    = "arg-expected";
    opts["-ORBTradingIOR"]    = "arg-expected";
    opts["-ORBTradingAddr"]   = "arg-expected";
    opts["-ORBDebugLevel"]    = "arg-expected";
    opts["-ORBBindAddr"]      = "arg-expected";
    opts["-ORBInitRef"]       = "arg-expected";
    opts["-ORBDefaultInitRef"]= "arg-expected";
    opts["-ORBMemTrace"]      = "";
    opts["-ORBNoResolve"]     = "";

    MICOGetOpt opt_parser (opts);
    if (!opt_parser.parse (rcfile.c_str(), TRUE))
	mico_throw (CORBA::INITIALIZE());
    if (!opt_parser.parse (argc, argv, TRUE))
	mico_throw (CORBA::INITIALIZE());
    const MICOGetOpt::OptVec &o = opt_parser.opts ();

    for (MICOGetOpt::OptVec::const_iterator i = o.begin(); i != o.end(); ++i) {
	string arg = (*i).first;
	string val = (*i).second;
	if (arg == "-ORBNoIIOPServer") {
	    run_iiop_server = FALSE;
	} else if (arg == "-ORBNoIIOPProxy") {
	    run_iiop_proxy = FALSE;
	} else if (arg == "-ORBIIOPAddr") {
	    iiopaddrs.push_back (val);
        } else if (arg == "-ORBIIOPProxy") {
          fwproxyaddr = Address::parse (val.c_str());
        } else if (arg == "-ORBIIOPBlocking") {
          iiop_blocking = TRUE;
	} else if (arg == "-ORBId") {
	    if (id.length() == 0)
		id = val;
	} else if (arg == "-ORBImplRepoIOR") {
	    imr_ior = val;
	} else if (arg == "-ORBImplRepoAddr") {
	    imr_addr = val;
	} else if (arg == "-ORBIfaceRepoIOR") {
	    ir_ior = val;
	} else if (arg == "-ORBIfaceRepoAddr") {
	    ir_addr = val;
	} else if (arg == "-ORBNamingIOR") {
	    naming_ior = val;
	} else if (arg == "-ORBNamingAddr") {
	    naming_addr = val;
	} else if (arg == "-ORBTradingIOR") {
	    trading_ior = val;
	} else if (arg == "-ORBTradingAddr") {
	    trading_addr = val;
	} else if (arg == "-ORBDebugLevel") {
	    debug_level = atoi (val.c_str());
	} else if (arg == "-ORBBindAddr") {
	    bindaddrs.push_back (val);
	} else if (arg == "-ORBInitRef") {
	    InitRefs.push_back (val);
	} else if (arg == "-ORBDefaultInitRef") {
	    DefInitRef = val;
	} else if (arg == "-ORBMemTrace") {
	    memtrace = true;
	} else if (arg == "-ORBNoResolve") {
	    MICO::InetAddress::resolve (FALSE);
	}
    }

    // create Debugger
    if (CORBA::is_nil (orb_instance))
	new MICODebug (debug_level);
    
    if (id.length() > 0 && strcmp ("mico-local-orb", id.c_str())) {
	MICODebug::instance()->printer()
	    << "ORB_init(): unknown ORB id: " << id << endl;
	mico_throw (CORBA::INITIALIZE());
    }

    if (!CORBA::is_nil (orb_instance))
	return ORB::_duplicate (orb_instance);

    // create ORB
    orb_instance = new ORB (argc, argv, rcfile.c_str());

    // interceptors
    CORBA::Boolean retval =
	Interceptor::InitInterceptor::_exec_initialize (orb_instance,
							"mico-local-orb",
							argc, argv);
    // XXX what to do on error ??
    if (!retval)
	mico_throw (CORBA::INITIALIZE());

    // set default bind addresses
    orb_instance->bindaddrs (bindaddrs);

    // create IIOP client
    MICO::IIOPProxy::block (iiop_blocking);
    if (run_iiop_proxy) {
	new MICO::IIOPProxy (orb_instance);
    }

    // create IIOP server
    if (run_iiop_server) {
	MICO::IIOPServer *server = new MICO::IIOPServer (orb_instance);
	for (mico_vec_size_type i = 0; i < iiopaddrs.size(); ++i) {
	    Address *addr = Address::parse (iiopaddrs[i].c_str());
	    if (!addr) {
		MICODebug::instance()->printer()
		    << "ORB_init(): bad address: " << iiopaddrs[i] << endl;
		mico_throw (CORBA::INITIALIZE());
	    }
	    if (!server->listen (addr, fwproxyaddr))
		mico_throw (CORBA::INITIALIZE());
	    delete addr;
	}
	if (iiopaddrs.size() == 0) {
	    server->listen ();
	}
    } else {
	orb_instance->ior_template()->add_profile (
	    new MICO::LocalProfile ((Octet *)"", 1));
    }

    // connect to / create implementation repository
    Object_var imr;
    if (imr_ior.length() > 0) {
	imr = orb_instance->string_to_object (imr_ior.c_str());
    } else if (imr_addr.length() > 0) {
	imr = orb_instance->bind ("IDL:omg.org/CORBA/ImplRepository:1.0",
				  imr_addr.c_str());
        if (CORBA::is_nil (imr)) {
            MICODebug::instance()->printer()
                << "warning: cannot bind to Implementation Repository at "
                << imr_addr.c_str() << "." << endl
                << "warning: will use a local Implementation Repository"
                << endl;
        }
    }
    if (!CORBA::is_nil (imr)) {
	orb_instance->set_initial_reference ("ImplementationRepository", imr);
    }

    // connect to / create interface repository
    Object_var ir;
    if (ir_ior.length() > 0) {
	ir = orb_instance->string_to_object (ir_ior.c_str());
    } else if (ir_addr.length() > 0) {
	ir = orb_instance->bind ("IDL:omg.org/CORBA/Repository:1.0",
				 ir_addr.c_str());
        if (CORBA::is_nil (ir)) {
            MICODebug::instance()->printer()
                << "warning: cannot bind to Interface Repository at "
                << ir_addr.c_str() << "." << endl
                << "warning: will use a local Interface Repository" << endl;
        }
    }
    if (!CORBA::is_nil (ir)) {
	orb_instance->set_initial_reference ("InterfaceRepository", ir);
    }

    // connect to naming service
    Object_var naming;
    if (naming_ior.length() > 0) {
	naming = orb_instance->string_to_object (naming_ior.c_str());
    } else if (naming_addr.length() > 0) {
	CORBA::ORB::ObjectTag_var tag = CORBA::ORB::string_to_tag ("NameService");
	naming = orb_instance->bind ("IDL:omg.org/CosNaming/NamingContext:1.0",
				     tag.in(), naming_addr.c_str());
        if (CORBA::is_nil (naming)) {
            MICODebug::instance()->printer()
                << "warning: cannot bind to Naming Service at "
                << naming_addr.c_str() << "." << endl;
        }
    }
    if (!CORBA::is_nil (naming)) {
	orb_instance->set_initial_reference ("NameService", naming);
    }

    // connect to trading service
    Object_var trading;
    if (trading_ior.length() > 0) {
	trading = orb_instance->string_to_object (trading_ior.c_str());
    } else if (trading_addr.length() > 0) {
	trading = orb_instance->bind ("IDL:omg.org/CosTrading/Lookup:1.0",
				     trading_addr.c_str());
        if (CORBA::is_nil (trading)) {
            MICODebug::instance()->printer()
                << "warning: cannot bind to Trading Service at "
                << trading_addr.c_str() << "." << endl;
        }
    }
    if (!CORBA::is_nil (trading)) {
	orb_instance->set_initial_reference ("TradingService", trading);
    }

    // Resolve -ORBInitRefs (must do that after connecting to NameService)
    for (CORBA::ULong iref=0; iref<InitRefs.size(); iref++) {
      string id, loc;
      size_t pos = InitRefs[iref].find ('=');
      if (pos == (size_t) -1) {
	mico_throw (CORBA::INITIALIZE());
      }
      id = InitRefs[iref].substr (0, pos);
      loc = InitRefs[iref].substr (pos+1, (size_t) -1);
      CORBA::Object_var iro = orb_instance->string_to_object (loc.c_str());
      if (CORBA::is_nil (iro)) {
	MICODebug::instance()->printer()
	  << "warning: cannot bind to " << id.c_str()
	  << " at " << loc.c_str() << endl;
      }
      else {
	orb_instance->set_initial_reference (id.c_str(), iro.in());
      }
    }

    if (DefInitRef.length()) {
      orb_instance->set_default_initial_reference (DefInitRef.c_str());
    }

    // Register factories for standard valuetypes
    ValueFactoryBase_var svf = new StringValue_Factory;
    ValueFactoryBase_var wsvf = new WStringValue_Factory;
    orb_instance->register_value_factory ("IDL:omg.org/CORBA/StringValue:1.0",
					  svf);
    orb_instance->register_value_factory ("IDL:omg.org/CORBA/WStringValue:1.0",
					  wsvf);
    
#ifdef USE_MEMTRACE
    if (argc > 0 && argv != NULL && *argv != NULL) {
      MemTrace_Init (*argv, (memtrace) ? MEMTRACE_REPORT_ON_EXIT : 0);
      MemTrace_Flush ();
    }
#else
    if (memtrace) {
      MICODebug::instance()->printer()
	<< "warning: MemTrace not available" << endl;
    }
#endif	    

    return CORBA::ORB::_duplicate (orb_instance);
}

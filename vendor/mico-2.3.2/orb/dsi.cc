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

#define MICO_CONF_IMR
#define MICO_CONF_IR

#include <CORBA-SMALL.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/intercept.h>
#include <mico/template_impl.h>
#include <mico/util.h>


CORBA::ImplementationBase::ImplementationBase ()
{
    _morb = ORB_instance ("mico-local-orb");
    _mboa = _morb->BOA_instance ("mico-local-boa");
}

CORBA::ImplementationBase::~ImplementationBase ()
{
    _dispose_ref ();
    CORBA::release (_morb);
    CORBA::release (_mboa);
}

void
CORBA::ImplementationBase::_create_ref (
    const BOA::ReferenceData &id,
    InterfaceDef_ptr interf,
    ImplementationDef_ptr im,
    const char *repoid)
{
    Object_var p = _mboa->create (id, interf, im, this, repoid);
    assert (!CORBA::is_nil (p));
    Object::operator= (*(Object_ptr)p);
}

void
CORBA::ImplementationBase::_restore_ref (
    Object_ptr orig_obj,
    const BOA::ReferenceData &id,
    InterfaceDef_ptr interf,
    ImplementationDef_ptr im)
{
    Object_var p = _mboa->restore (orig_obj, id, interf, im, this);
    assert (!CORBA::is_nil (p));
    Object::operator= (*(Object_ptr)p);
}

void
CORBA::ImplementationBase::_dispose_ref ()
{
    _mboa->dispose (this);
}

const char *
CORBA::ImplementationBase::_impl_name (const char *)
{
    return _mboa->impl_name();
}

CORBA::ImplementationDef_ptr
CORBA::ImplementationBase::_find_impl (const char *repoid, const char *name)
{
    name = _impl_name (name);

    CORBA::Object_var obj =
	_morb->resolve_initial_references ("ImplementationRepository");
    assert (!CORBA::is_nil (obj));

    CORBA::ImplRepository_var imr = ImplRepository::_narrow (obj);
    assert (!CORBA::is_nil (imr));

    obj = _morb->resolve_initial_references ("LocalImplementationRepository");

    CORBA::ImplRepository_var local_imr = ImplRepository::_narrow (obj);
    assert (!CORBA::is_nil (local_imr));

    CORBA::ImplRepository::ImplDefSeq_var impls = imr->find_by_name (name);
    CORBA::ImplementationDef_var impl;

    if (impls->length() == 0)
        impls = local_imr->find_by_name (name);

    if (impls->length() > 0) {
        MICODebug::instance()->tracer()
            << "found impl repository entry: " << name << endl;

        impl = CORBA::ImplementationDef::_duplicate (impls[(CORBA::ULong)0]);
        CORBA::ImplementationDef::ObjectInfoList_var objs = impl->objs();
        CORBA::ULong i;
        for (i = 0; i < objs->length(); ++i) {
            if (!strcmp (repoid, objs[i].repoid.in()))
                break;
        }
        if (i == objs->length()) {
            MICODebug::instance()->tracer()
                << "adding repo id: " << repoid << endl;

            objs->length (objs->length()+1);
            objs[objs->length()-1].repoid = CORBA::string_dup (repoid);
            impl->objs (objs.in());
        }
    } else {
        MICODebug::instance()->tracer()
            << "creating impl repository entry: " << name << endl;

        CORBA::ImplementationDef::ObjectInfoList objs;
        objs.length (1);
        objs[0].repoid = CORBA::string_dup (repoid);

        impl = local_imr->create (
            CORBA::ImplementationDef::ActivatePersistent,
            objs, name, "");
    }
    return CORBA::ImplementationDef::_duplicate (impl);
}

CORBA::InterfaceDef_ptr
CORBA::ImplementationBase::_find_iface (const char *repoid)
{
    CORBA::Object_var obj =
	_orbnc()->resolve_initial_references ("InterfaceRepository");
    assert (!CORBA::is_nil (obj));

    CORBA::Repository_var ir = Repository::_narrow (obj);
    assert (!CORBA::is_nil (ir));

    CORBA::Contained_var contained = ir->lookup_id (repoid);
    if (CORBA::is_nil (contained))
	return CORBA::InterfaceDef::_nil();

    CORBA::InterfaceDef_var iface = CORBA::InterfaceDef::_narrow (contained);
    assert (!CORBA::is_nil (iface));
    return CORBA::InterfaceDef::_duplicate (iface);
}

CORBA::Boolean
CORBA::ImplementationBase::_save_object ()
{
    /*
     * FALSE means the object is transient, i.e. it won't be restored
     * later
     */
    return FALSE;
}

CORBA::BOA_ptr
CORBA::ImplementationBase::_boa ()
{
    return CORBA::BOA::_duplicate (_mboa);
}

CORBA::ORB_ptr
CORBA::ImplementationBase::_orbnc ()
{
    // no _duplicate() returned
    return _morb;
}

CORBA::ORB_ptr
CORBA::ImplementationBase::_orb ()
{
    return CORBA::ORB::_duplicate (_morb);
}

CORBA::Object_ptr
CORBA::ImplementationBase::_this ()
{
    return CORBA::Object::_duplicate (this);
}


/************************** ServerRequestBase ***************************/


CORBA::ServerRequestBase::~ServerRequestBase ()
{
}


/************************ DynamicImplementation *************************/


CORBA::DynamicImplementation::DynamicImplementation ()
{
}

CORBA::DynamicImplementation::~DynamicImplementation ()
{
}

CORBA::ServerRequestBase_ptr
CORBA::DynamicImplementation::make_request (CORBA::ORBRequest *req,
					    CORBA::Object_ptr obj,
					    CORBA::ULong msgid,
					    CORBA::ObjectAdapter *oa,
					    CORBA::Principal_ptr pr)
{
    return new ServerRequest (req, obj, msgid, oa, pr);
}

void
CORBA::DynamicImplementation::doinvoke (ServerRequestBase_ptr req,
					Environment &env)
{
    invoke ((ServerRequest_ptr)req, env);
}


/***************************** ServerRequest ***************************/


CORBA::ServerRequest::ServerRequest (ORBRequest *r, Object_ptr o,
                                     MsgId id, CORBA::ObjectAdapter *oa,
				     CORBA::Principal_ptr pr)
    : _oa (oa), _msgid (id),
      _obj(Object::_duplicate (o)),
      _req(ORBRequest::_duplicate (r)),
      _env (pr)
{
    _aborted = FALSE;
    _dir_params = NVList::_nil();
    _context = Context::_nil();
    _iceptreq = Interceptor::ServerInterceptor::_create_request (
	_obj, r->op_name(), *r->context(), this);
}

CORBA::ServerRequest::~ServerRequest ()
{
    if (!_canceled) {
        if (!_aborted && !Interceptor::ServerInterceptor::
            _exec_before_marshal ((Interceptor::LWServerRequest_ptr)_iceptreq,
                                  &_env)) {
            _aborted = TRUE;
        }

        // copy back out args and result into ORBRequest
        set_out_args();

        // tell OA we are done
        CORBA::InvokeStatus stat = CORBA::InvokeOk;
        if (exception()) {
            if (CORBA::SystemException::EXCEPTION_DOWNCAST (exception())) {
                stat = CORBA::InvokeSysEx;
            } else {
                stat = CORBA::InvokeUsrEx;
            }
        }
        _oa->answer_invoke (_msgid, _obj, _req, stat);

        if (!_aborted && !Interceptor::ServerInterceptor::
            _exec_finish_request ((Interceptor::LWServerRequest_ptr)_iceptreq,
                                  &_env)) {
            // XXX how to abort the request here???
        }
    }

    CORBA::release (_dir_params);
    CORBA::release (_context);
    CORBA::release (_iceptreq);
    CORBA::release (_obj);
    CORBA::release (_req);
}

// begin CORBA 2.2 mapping [20.26.1]
const char *
CORBA::ServerRequest::operation ()
{
  return _req->op_name();
}

void
CORBA::ServerRequest::arguments (NVList_ptr & p)
{
  params (p);
}

void
CORBA::ServerRequest::set_result (const Any & val)
{
  _res = new CORBA::Any (val);
}

void
CORBA::ServerRequest::set_exception (const Any & val)
{
  _res = 0;
  _env.exception (Exception::_decode ((Any &) val));
  assert (_env.exception());
}
// end CORBA 2.2 mapping; ctx () as below

const char *
CORBA::ServerRequest::op_name ()
{
    return _req->op_name();
}

CORBA::OperationDef_ptr
CORBA::ServerRequest::op_def ()
{
    InterfaceDef_var iface = _obj->_get_interface ();
    assert (!CORBA::is_nil (iface));

    Contained_var cont = iface->lookup ((char *)op_name());
    assert (!CORBA::is_nil (cont));

    OperationDef_ptr opdef = OperationDef::_narrow (cont);
    assert (!CORBA::is_nil (opdef));

    return opdef;
}

CORBA::Context_ptr
CORBA::ServerRequest::ctx ()
{
    assert (!CORBA::is_nil (_dir_params));
    return _context;
}

CORBA::Boolean
CORBA::ServerRequest::params (NVList_ptr p)
{
    assert (CORBA::is_nil (_dir_params));
    _dir_params = p;

    if (!Interceptor::ServerInterceptor::
	_exec_initialize_request ((Interceptor::LWServerRequest_ptr)_iceptreq,
				  &_env)) {
	_aborted = TRUE;
	return FALSE;
    }

    if (!_req->get_in_args (_dir_params, _context)) {
        MICODebug::instance()->debugger()
            << "cannot decode args" << endl;
        exception (new CORBA::MARSHAL());
        _aborted = TRUE;
        return FALSE;
    }

    if (!Interceptor::ServerInterceptor::
	_exec_after_unmarshal ((Interceptor::LWServerRequest_ptr)_iceptreq,
			       &_env)) {
	_aborted = TRUE;
	return FALSE;
    }
    return TRUE;
}

void
CORBA::ServerRequest::result (Any *val)
{
    _env.clear ();
    _res = val;
}

CORBA::Environment_ptr
CORBA::ServerRequest::environment ()
{
    return &_env;
}

void
CORBA::ServerRequest::exception (Any *val)
{
    _res = 0;
    _env.exception (Exception::_decode (*val));
    assert (_env.exception());
    delete val;
}

void
CORBA::ServerRequest::exception (Exception *except)
{
    _env.exception (except);
}

CORBA::Exception *
CORBA::ServerRequest::exception ()
{
    // maybe _nil(), overship maintained by ServerRequest
    return _env.exception();
}

CORBA::Any *
CORBA::ServerRequest::result ()
{
    // maybe 0, overship maintained by ServerRequest
    return _res;
}

CORBA::NVList_ptr
CORBA::ServerRequest::arguments ()
{
    // maybe _nil(), overship maintained by ServerRequest
    return _dir_params;
}

void
CORBA::ServerRequest::set_out_args ()
{

    if (_env.exception()) {
        _req->set_out_args (_env.exception());
    } else if (!CORBA::is_nil (_dir_params)) {
	if (!_req->set_out_args (_res, _dir_params)) {
            MICODebug::instance()->debugger()
                << "cannot set out args" << endl;
            CORBA::MARSHAL ex (0, CORBA::COMPLETED_YES);
            _req->set_out_args (&ex);
        }
    }
}

CORBA::ORBRequest *
CORBA::ServerRequest::request ()
{
    return _req;
}

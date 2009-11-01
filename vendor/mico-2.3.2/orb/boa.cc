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
#include <algorithm>
#include <mico/impl.h>
#include <mico/intercept.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>


/******************************* BOA ******************************/


CORBA::BOA::~BOA ()
{
}


/************************ BOAObjectRestorer **************************/


/*
 * BOAObjectRestorer is now implemented using Interceptors. New code should
 * use the interceptors directly ...
 */

class BOAInterceptImpl : public Interceptor::BOAInterceptor {
    CORBA::BOAObjectRestorer *_restorer;
public:
    BOAInterceptImpl (CORBA::BOAObjectRestorer *r)
	: _restorer (r)
    {}

    Interceptor::Status restore (CORBA::Object_ptr obj)
    {
	return _restorer->restore (obj)
	    ? Interceptor::INVOKE_BREAK
	    : Interceptor::INVOKE_CONTINUE;
    }

    Interceptor::Status bind (const char *repoid,
			      const CORBA::ORB::ObjectTag &tag)
    {
	return _restorer->bind (repoid, tag)
	    ? Interceptor::INVOKE_BREAK
	    : Interceptor::INVOKE_CONTINUE;
    }
};

CORBA::BOAObjectRestorer::BOAObjectRestorer ()
{
    Interceptor::Root_ptr rp;

    rp = new BOAInterceptImpl (this);
    rp->activate (0);
    _boa_interceptor = rp;
}

CORBA::BOAObjectRestorer::~BOAObjectRestorer ()
{
    CORBA::release (_boa_interceptor);
}

CORBA::Boolean
CORBA::BOAObjectRestorer::restore (CORBA::Object_ptr)
{
    return FALSE;
}

CORBA::Boolean
CORBA::BOAObjectRestorer::bind (const char *repoid,
                                const CORBA::ORB::ObjectTag &tag)
{
    return FALSE;
}


/************************* ObjectRecord ***************************/


MICO::ObjectRecord::ObjectRecord (CORBA::Object_ptr local_obj,
				  const CORBA::BOA::ReferenceData &refdata,
				  CORBA::InterfaceDef_ptr ifc,
				  CORBA::ImplementationDef_ptr im,
				  CORBA::ImplementationBase *sk)
{
    _local_obj = local_obj;
    _remote_obj = CORBA::Object::_duplicate (local_obj);
    _id = refdata;
    _iface = CORBA::InterfaceDef::_duplicate (ifc);
    _impl = CORBA::ImplementationDef::_duplicate (im);
    _skel = sk;
    _save = TRUE;
    _state = BOAActive;
    _persistent = FALSE;
}

MICO::ObjectRecord::ObjectRecord (CORBA::Object_ptr local_obj,
				  CORBA::Object_ptr remote_obj,
				  const CORBA::BOA::ReferenceData &refdata,
				  CORBA::InterfaceDef_ptr ifc,
				  CORBA::ImplementationDef_ptr im,
				  CORBA::ImplementationBase *sk)
{
    _local_obj = local_obj;
    _remote_obj = remote_obj;
    _id = refdata;
    _iface = CORBA::InterfaceDef::_duplicate (ifc);
    _impl = CORBA::ImplementationDef::_duplicate (im);
    _skel = sk;
    _save = TRUE;
    _state = BOAActive;
    _persistent = FALSE;
}

MICO::ObjectRecord::~ObjectRecord ()
{
    CORBA::release (_local_obj);
    CORBA::release (_remote_obj);
    CORBA::release (_iface);
    CORBA::release (_impl);
    // XXX skel ??
}

CORBA::BOA::ReferenceData *
MICO::ObjectRecord::id ()
{
    return &_id;
}

CORBA::ImplementationDef_ptr
MICO::ObjectRecord::impl ()
{
    return _impl;
}

void
MICO::ObjectRecord::impl (CORBA::ImplementationDef_ptr im)
{
    CORBA::release (_impl);
    _impl = CORBA::ImplementationDef::_duplicate (im);
}

CORBA::InterfaceDef_ptr
MICO::ObjectRecord::iface ()
{
    return _iface;
}

void
MICO::ObjectRecord::iface (CORBA::InterfaceDef_ptr ifc)
{
    CORBA::release (_iface);
    _iface = CORBA::InterfaceDef::_duplicate (ifc);
}

CORBA::Object_ptr
MICO::ObjectRecord::local_obj ()
{
    return _local_obj;
}

CORBA::Object_ptr
MICO::ObjectRecord::remote_obj ()
{
    return _remote_obj;
}

CORBA::ImplementationBase *
MICO::ObjectRecord::skel ()
{
    return _skel;
}

void
MICO::ObjectRecord::skel (CORBA::ImplementationBase *sk)
{
    _skel = sk;
}

void
MICO::ObjectRecord::save (CORBA::Boolean save)
{
    _save = save;
}

CORBA::Boolean
MICO::ObjectRecord::save () const
{
    return _save;
}

void
MICO::ObjectRecord::persistent (CORBA::Boolean p)
{
    _persistent = p;
}

CORBA::Boolean
MICO::ObjectRecord::persistent () const
{
    return _persistent;
}

void
MICO::ObjectRecord::state (BOAState state)
{
    _state = state;
}

MICO::BOAState
MICO::ObjectRecord::state () const
{
    return _state;
}


/************************** BOAServImpl ****************************/


MICO::BOAServImpl::BOAServImpl (BOAImpl *__boa)
{
    _boa = __boa;
}

MICO::BOAServImpl::~BOAServImpl ()
{
}

void
MICO::BOAServImpl::restore_request (const CORBA::OAServer::ObjSeq &objs)
{
    for (CORBA::ULong i = 0; i < objs.length(); ++i)
	_boa->restore_internal (objs[i]);
}

void
MICO::BOAServImpl::obj_inactive (CORBA::Object_ptr obj)
{
    ObjectRecord *rec = _boa->get_record (obj);
    if (rec) {
	assert (rec->state() == BOAShutdown);
	rec->state (BOAInactive);
    }
}

void
MICO::BOAServImpl::impl_inactive ()
{
    assert (_boa->_state == BOAShutdown);
    _boa->_state = BOAInactive;
}


/**************************** BOAImpl ******************************/

#ifdef _WINDOWS
// error/OK?
#pragma warning( disable : 4355)
#endif

MICO::BOAImpl::BOAImpl (CORBA::ORB_ptr theorb, int &argc, char **argv)
    : _queue (this, theorb)
{
    _restoring = FALSE;
    _state = BOAActive;
    _active_obj = CORBA::Object::_nil();
    _curr_environ = CORBA::Environment::_nil();
    _amode = CORBA::ImplementationDef::ActivatePersistent;
    _oasrv_id = 0;
    _queue_count = 0;

    _orb = theorb;
    _theid = 0;
    _orb->register_oa (this, OAPriorityLocal);

    vector<CORBA::Octet> hostid = MICO::InetAddress::hostid();
    CORBA::ULong pid = OSMisc::getpid();
    _id_template[0] = 'B';
    _id_template[1] = 'O';
    _id_template[2] = 'A';
    _id_template[3] = hostid[0];
    _id_template[4] = hostid[1];
    _id_template[5] = hostid[2];
    _id_template[6] = hostid[3];
    _id_template[7] = (CORBA::Octet)(pid >> 24);
    _id_template[8] = (CORBA::Octet)(pid >> 16);
    _id_template[9] = (CORBA::Octet)(pid >> 8);
    _id_template[10] = (CORBA::Octet)(pid);

    string remote_ior;
    string remote_addr;
    typedef vector<string> vec_of_string;
    vec_of_string restore_iors;
    MICOGetOpt::OptMap opts;
    opts["-OARemoteIOR"]  = "arg-expected";
    opts["-OARemoteAddr"] = "arg-expected";
    opts["-OARestoreIOR"] = "arg-expected";
    opts["-OAImplName"]   = "arg-expected";
    opts["-OAServerId"]   = "arg-expected";

    MICOGetOpt opt_parser (opts);
    CORBA::Boolean r = opt_parser.parse ("~/.micorc", TRUE);
    assert (r);
    r = opt_parser.parse (argc, argv, TRUE);
    assert (r);
    const MICOGetOpt::OptVec &o = opt_parser.opts();

    for (MICOGetOpt::OptVec::const_iterator i = o.begin(); i != o.end(); ++i) {
	string arg = (*i).first;
	string val = (*i).second;
	if (arg == "-OARemoteIOR") {
	    remote_ior = val;
	} else if (arg == "-OARemoteAddr") {
	    remote_addr = val;
	} else if (arg == "-OARestoreIOR") {
            restore_iors.push_back (val);
	} else if (arg == "-OAServerId") {
	    _oasrv_id = atoi (val.c_str());
        } else if (arg == "-OAImplName") {
	    _impl_name = val;
	}
    }

    // connect to OA mediator
    _oamed = CORBA::OAMediator::_nil();
    _oasrv = CORBA::OAServer::_nil();
    CORBA::Object_var obj = CORBA::Object::_nil();
    if (remote_ior.length() > 0) {
	obj = _orb->string_to_object (remote_ior.c_str());
	assert (!CORBA::is_nil (obj));
    } else if (remote_addr.length() > 0) {
	obj = _orb->bind ("IDL:omg.org/CORBA/OAMediator:1.0",
			  remote_addr.c_str());
	assert (!CORBA::is_nil (obj));
    }
    if (!CORBA::is_nil (obj)) {
	_oamed = CORBA::OAMediator::_narrow (obj);
	assert (!CORBA::is_nil (_oamed));
    }

    if (!CORBA::is_nil (_oamed)) {
	/*
	 * create OAServer object. there is a special case in
	 * create() which makes this object a local one.
	 */
	_oasrv = new BOAServImpl (this);
	
	// register with mediator
	CORBA::ImplementationDef_var impl = find_impl ();
	_amode = impl->mode();
	_oamed->create_impl (impl, _oasrv, _oasrv_id);
    }

    // restore saved objects ...
    if (restore_iors.size() > 0) {
	_restoring = TRUE;
	for (mico_vec_size_type i = 0; i < restore_iors.size(); ++i) {
	    obj = _orb->string_to_object (restore_iors[i].c_str());
	    assert (!CORBA::is_nil (obj));
	    restore_internal (obj);
	}
    }
    // ask for more objects to restore
    if (!CORBA::is_nil (_oamed)) {
        CORBA::OAMediator::ObjSeq_var robjs =
	    _oamed->get_restore_objs (_oasrv_id);

        if (robjs->length() > 0) {
            _restoring = TRUE;
            for (CORBA::ULong i = 0; i < robjs->length(); ++i)
		restore_internal (robjs[i]);
        }
    }
}

MICO::BOAImpl::~BOAImpl ()
{
    _orb->unregister_oa (this);
    for (MapObjRec::iterator i0 = _lobjs.begin(); i0 != _lobjs.end(); ++i0) {
	ObjectRecord *rec = (*i0).second;
	delete rec;
    }

    // unload shlibs
    for (ListShlib::iterator i1 = _shlibs.begin(); i1 != _shlibs.end(); ++i1)
	// XXX call (*i)->exit() ??? 
	delete *i1;

    /*
     * the ObjectRecords in the robjs map are just pointers to the
     * ObjectRecords in the lobjs map, so do not delete them...
     */
    CORBA::release (_oamed);
    CORBA::release (_oasrv);
}

void
MICO::BOAImpl::add_record (ObjectRecord *rec)
{
    _lobjs[rec->local_obj()] = rec;
    if (!CORBA::is_nil (_oamed))
	_robjs[rec->remote_obj()] = rec;
}

MICO::ObjectRecord *
MICO::BOAImpl::get_record (CORBA::Object_ptr o)
{
    MapObjRec::iterator i = _lobjs.find (o);
    if (i != _lobjs.end())
	return (*i).second;

    if (CORBA::is_nil (_oamed))
	return 0;
    /*
     * take a shortcut for local invocations, i.e. bypass the
     * BOA deamon...
     */
    i = _robjs.find (o);
    return i != _robjs.end() ? (*i).second : 0;
}

void
MICO::BOAImpl::del_record (CORBA::Object_ptr o)
{
    MapObjRec::iterator i = _lobjs.find (o);
    if (i != _lobjs.end()) {
	if (!CORBA::is_nil (_oamed))
	    _robjs.erase ((*i).second->remote_obj());
        // deleting an ObjectRecord can result in a recursive call to
        // del_record (because ImplementationDef's have an ObjectRecord,
        // too) and can thus invalidate the iterator. so we have to first
        // erase and then delete ...
	ObjectRecord *orec = (*i).second;
	_lobjs.erase (i);
        delete orec;
	return;
    }

    // object not found if standalone ...
    assert (!CORBA::is_nil (_oamed));

    if ((i = _robjs.find (o)) != _robjs.end()) {
	_lobjs.erase ((*i).second->local_obj());
        // deleting an ObjectRecord can change the map ...
	ObjectRecord *orec = (*i).second;
	_robjs.erase (i);
	delete orec;
	return;
    }

    // object not found ...
    assert (0);
}

void
MICO::BOAImpl::del_all_records ()
{
    while (_lobjs.size()) {
        // deleting an ObjectRecord can change the map ...
        MapObjRec::iterator i = _lobjs.begin();
	ObjectRecord *orec = (*i).second;
        _lobjs.erase (i);
        delete orec;
    }
    _robjs.erase (_robjs.begin(), _robjs.end());
}

CORBA::ImplementationDef_ptr
MICO::BOAImpl::find_impl ()
{
    CORBA::Object_var obj =
	orb()->resolve_initial_references ("ImplementationRepository");
    assert (!CORBA::is_nil (obj));

    CORBA::ImplRepository_var imr = CORBA::ImplRepository::_narrow (obj);
    assert (!CORBA::is_nil (imr));

    CORBA::ImplRepository::ImplDefSeq_var impls =
	imr->find_by_name (impl_name());
    if (impls->length() == 0)
	return CORBA::ImplementationDef::_nil();
    return CORBA::ImplementationDef::_duplicate (impls[(CORBA::ULong)0]);
}

CORBA::Object_ptr
MICO::BOAImpl::find_obj ()
{
    MapObjRec::iterator i = _lobjs.begin();
    if (i == _lobjs.end())
	return CORBA::Object::_nil();
    ObjectRecord *rec = (*i).second;
    return rec->remote_obj();
}

void
MICO::BOAImpl::unique_id (vector<CORBA::Octet> &id)
{
    id.insert (id.end(), _id_template, _id_template + sizeof (_id_template));

    if (++_theid == 0)
	_theid = 1;

    CORBA::ULong l = _theid;
    while (l) {
	id.push_back ((CORBA::Octet)l);
	l >>= 8;
    }
}

void
MICO::BOAImpl::queue ()
{
    ++_queue_count;
}

void
MICO::BOAImpl::unqueue ()
{
    assert (_queue_count > 0);
    if (--_queue_count == 0)
	_queue.exec_later ();
}

CORBA::Boolean
MICO::BOAImpl::must_queue (MsgId id)
{
    if (_queue_count > 0)
        return TRUE;
    if (_queue.size() == 0)
        return FALSE;
    if (_queue.iscurrent (id))
        return FALSE;
    /*
     * there are still invocations in the queue, queue to preserve
     * invocation oder
     */
    return TRUE;
}

CORBA::Boolean
MICO::BOAImpl::is_active_object (CORBA::Object_ptr obj)
{
    if (CORBA::is_nil (obj) && CORBA::is_nil (_active_obj))
	return TRUE;
    if (CORBA::is_nil (obj) || CORBA::is_nil (_active_obj))
	return FALSE;
    return _active_obj->_is_equivalent (obj);
}

CORBA::Object_ptr
MICO::BOAImpl::create (const ReferenceData &id,
		       CORBA::InterfaceDef_ptr interf,
		       CORBA::ImplementationDef_ptr impl,
		       CORBA::ImplementationBase *skel,
		       const char *repoid)
{
    vector<CORBA::Octet> key;
    unique_id (key);

    CORBA::IOR *ior = new CORBA::IOR (*_orb->ior_template());
    ior->objectkey (&key[0], key.size());

    assert (repoid);
    ior->objid (repoid);

    CORBA::Object_ptr obj = new CORBA::Object (ior);
    // XXX dont know the object that creates this object...
    obj->_setup_domains (CORBA::Object::_nil());

    ObjectRecord *rec;

#if 1
    /*
     * interfaces derived from other interfaces will call create()
     * for each of the base interfaces (which is a bug). here is
     * a workaround that removes the entries for the base interfaces.
     */
    if (skel && skel->_ior())
	dispose (skel);
#endif

    CORBA::Boolean retval = Interceptor::BOAInterceptor::_exec_create (obj);
    // XXX what to do on error ??
    assert (retval);

    if (CORBA::is_nil (_oamed) || CORBA::is_nil (_oasrv)) {
	/*
	 * we are standalone or OAServer hasn't been created yet
	 */
	rec = new ObjectRecord (obj, id, interf, impl, skel);
	add_record (rec);
    } else {
	/*
	 * register with BOA daemon. he will tell us his object reference,
	 * which we will store in the newly generated object, so subsequent
	 * invocations will go over the daemon.
	 */
	queue ();

        CORBA::Object_ptr remote_obj;
	_oamed->create_obj (obj, id, remote_obj, _oasrv_id);
	assert (!CORBA::is_nil (remote_obj));
	_oamed->activate_obj (remote_obj, _oasrv_id);

	rec = new ObjectRecord (obj, remote_obj, id, interf, impl, skel);
	add_record (rec);

	unqueue ();
    }

    return CORBA::Object::_duplicate (rec->remote_obj());
}

CORBA::Boolean
MICO::BOAImpl::restoring ()
{
    return _restoring;
}

void
MICO::BOAImpl::restore_internal (CORBA::Object_ptr orig)
{
    vector<CORBA::Octet> key;
    unique_id (key);

    CORBA::IOR *ior = new CORBA::IOR (*_orb->ior_template());
    ior->objectkey (&key[0], key.size());

    ior->objid (orig->_repoid());

    CORBA::Object_ptr obj = new CORBA::Object (ior);
    ObjectRecord *rec;

    assert (!CORBA::is_nil (_oamed));

    /*
     * register with BOA daemon: tell him our new local object reference.
     * we receive a (possibly different) remote object reference,
     * which we will store in the newly generated object, so subsequent
     * invocations will go over the daemon.
     */
    queue ();

    ReferenceData_var id;
    CORBA::Object_var remote_obj = CORBA::Object::_duplicate (orig);
    _oamed->restore_obj (obj, remote_obj, id, _oasrv_id);
    assert (!CORBA::is_nil (remote_obj));
    _oamed->activate_obj (remote_obj, _oasrv_id);

    rec = new ObjectRecord (obj, remote_obj._retn(), id.in(),
			    CORBA::InterfaceDef::_nil(),
			    CORBA::ImplementationDef::_nil(),
			    (CORBA::ImplementationBase *)0);
    add_record (rec);

    unqueue ();
}

CORBA::Object_ptr
MICO::BOAImpl::restore (CORBA::Object_ptr orig,
			const ReferenceData &_id,
			CORBA::InterfaceDef_ptr interf,
			CORBA::ImplementationDef_ptr impl,
			CORBA::ImplementationBase *skel)
{
    ObjectRecord *rec = get_record (orig);
    assert (rec);
    assert (!CORBA::is_nil (_oamed));

    rec->iface (interf);
    rec->impl (impl);
    rec->skel (skel);

    return CORBA::Object::_duplicate (rec->remote_obj());
}

void
MICO::BOAImpl::dispose (CORBA::Object_ptr o)
{
    ObjectRecord *rec = get_record (o);

    if (rec) {
        if (is_active_object (o))
            _active_obj = CORBA::Object::_nil();

	if (CORBA::is_nil (_oamed) || rec->local_obj() == rec->remote_obj()) {
	    del_record (o);
	} else {
            /*
	     * make sure Any::copy_any does not release object again
	     * during DII invocation to daemon by erasing object from
	     * object table before making the call.
	     */
            CORBA::Object_var obj =
                new CORBA::Object (new CORBA::IOR (*o->_ior()));
	    del_record (o);
	    _oamed->dispose_obj (obj, _oasrv_id);
        }
    }
}

CORBA::ORB_ptr
MICO::BOAImpl::orb ()
{
    return _orb;
}

CORBA::BOA::ReferenceData *
MICO::BOAImpl::get_id (CORBA::Object_ptr o)
{
    ObjectRecord *rec = get_record (o);
    assert (rec);
    return new ReferenceData (*rec->id ());
}

CORBA::Principal_ptr
MICO::BOAImpl::get_principal (CORBA::Object_ptr o, CORBA::Environment_ptr env)
{
    if (!CORBA::is_nil (env))
	return CORBA::Principal::_duplicate (env->principal ());
    if (!CORBA::is_nil (_curr_environ))
	return CORBA::Principal::_duplicate (_curr_environ->principal());
    return CORBA::Principal::_nil();
}

void
MICO::BOAImpl::shutdown_obj (CORBA::Object_ptr obj)
{
    assert (_queue_count == 0);
    _queue.exec_now();

    if (CORBA::is_nil (_oamed))
	return;
    
    _oamed->deactivate_obj (obj, _oasrv_id);

    while (42) {
	ObjectRecord *rec = get_record (obj);
	if (!rec) {
	    // object has been released inbetween
	    break;
	}
	if (rec->state() == BOAInactive)
	    // all buffered invocations done
	    break;
	_orb->dispatcher()->run (FALSE);
    }
}

void
MICO::BOAImpl::shutdown_impl ()
{
    assert (_queue_count == 0);
    _queue.exec_now();

    if (CORBA::is_nil (_oamed))
	return;
    
    _oamed->deactivate_impl (_oasrv_id);

    while (42) {
	if (_state == BOAInactive)
	    // all buffered invocations done
	    break;
	_orb->dispatcher()->run (FALSE);
    }
}

void
MICO::BOAImpl::change_implementation (CORBA::Object_ptr o,
				      CORBA::ImplementationDef_ptr im)
{
    // XXX works only with BOA daemon
    assert (!CORBA::is_nil (_oamed));
    assert (!CORBA::is_nil (im));

    ObjectRecord *rec = get_record (o);
    assert (rec);

    if (rec->state() == BOAActive) {
	rec->state (BOAShutdown);

	shutdown_obj (o);
	save_object (rec);
	
	_oamed->migrate_obj (o, _oasrv_id, im);

	dispose_object (rec);
	del_record (o);
    }
}

void
MICO::BOAImpl::impl_is_ready (CORBA::ImplementationDef_ptr im)
{
    if (!CORBA::is_nil (_oamed)) {
        /*
         * beware: before returning from here the first invocations
         * might already arrive
         */
	_oamed->activate_impl (_oasrv_id);
    }
}

void
MICO::BOAImpl::deactivate_impl (CORBA::ImplementationDef_ptr im)
{
    if (_state == BOAActive) {
	_state = BOAShutdown;

	shutdown_impl ();
	save_objects ();

	// must dispose before deactivating!
	dispose_objects ();

	if (!CORBA::is_nil (_oamed))
	    _oamed->dispose_impl (_oasrv_id);

	del_all_records ();
    }
}

void
MICO::BOAImpl::obj_is_ready (CORBA::Object_ptr o,
			     CORBA::ImplementationDef_ptr im)
{
    if (CORBA::is_nil (o)) {
	o = find_obj ();
    }

    _active_obj = o;

    if (!CORBA::is_nil (_oamed)) {
        /*
         * beware: before returning from here the first invocations
         * might already arrive
         */
	_oamed->activate_impl (_oasrv_id);
    }
}

void
MICO::BOAImpl::deactivate_obj (CORBA::Object_ptr o)
{
    if (CORBA::is_nil (o)) {
	o = _active_obj;
        //assert (!CORBA::is_nil (o));
    }

    if (is_active_object (o)) {
        // deactivate whole implementation
        if (_state == BOAActive) {
            _state = BOAShutdown;

            shutdown_impl ();
            save_objects ();

            // must dispose before deactivating!
            dispose_objects ();

            if (!CORBA::is_nil (_oamed))
                _oamed->dispose_impl (_oasrv_id);

	    del_all_records ();
        }
    } else {
        // deactivate one object
        assert (!CORBA::is_nil (o));

        ObjectRecord *rec = get_record (o);
        assert (rec);

        if (rec->state() == BOAActive) {
            rec->state (BOAShutdown);
	
            shutdown_obj (o);
            save_object (rec);

            if (!CORBA::is_nil (_oamed))
                _oamed->orphan_obj (o, _oasrv_id);

            dispose_object (rec);

            del_record (o);
        }
    }
}

const char *
MICO::BOAImpl::get_oaid () const
{
    return "mico-local-boa";
}

CORBA::Boolean
MICO::BOAImpl::has_object (CORBA::Object_ptr o)
{
    CORBA::IORProfile *prof;
    if (CORBA::is_nil (o) || !o->_ior() || !(prof = o->_ior()->profile()))
        return FALSE;

    CORBA::Long objkeylen;
    const CORBA::Octet *objkey = prof->objectkey (objkeylen);
    if (objkeylen >= sizeof (_id_template) &&
	!memcmp (objkey, _id_template, sizeof (_id_template)))
	return TRUE;

    if (!CORBA::is_nil (_oamed) && objkeylen >= 3 && !memcmp (objkey, "OAD", 3))
	return _robjs.count (o) > 0;
	
    return FALSE;
}

CORBA::Boolean
MICO::BOAImpl::is_local () const
{
    return TRUE;
}

CORBA::ImplementationDef_ptr
MICO::BOAImpl::get_impl (CORBA::Object_ptr o)
{
    ObjectRecord *rec = get_record (o);
    assert (rec);
    CORBA::Boolean r = load_object (rec);
    assert (r);
    return rec->impl ();
}

CORBA::InterfaceDef_ptr
MICO::BOAImpl::get_iface (CORBA::Object_ptr o)
{
    ObjectRecord *rec = get_record (o);
    assert (rec);
    CORBA::Boolean r = load_object (rec);
    assert (r);
    if (CORBA::is_nil (rec->iface())) {
	rec->iface (rec->skel()->_find_iface (rec->local_obj()->_repoid()));
    }
    return rec->iface ();
}

CORBA::Boolean
MICO::BOAImpl::is_builtin_invoke (const char *opname)
{
    if (opname[0] != '_')
	return FALSE;
    return
	!strcmp (opname, "_interface") ||
	!strcmp (opname, "_implementation") ||
	!strcmp (opname, "_is_a") ||
	!strcmp (opname, "_non_existent");
}

void
MICO::BOAImpl::builtin_invoke (CORBA::Object_ptr o,
			       CORBA::ServerRequest_ptr svreq,
			       CORBA::Principal_ptr pr)
{
    // [12-17]
    if (!strcmp (svreq->op_name(), "_interface")) {
	CORBA::NVList_ptr args;
	_orb->create_list (0, args);
	if (svreq->params (args)) {
            CORBA::Any *res = new CORBA::Any;
            *res <<= get_iface (o);
            svreq->result (res);
        }
	return;
    }
    if (!strcmp (svreq->op_name(), "_implementation")) {
	CORBA::NVList_ptr args;
	_orb->create_list (0, args);
	if (svreq->params (args)) {
            CORBA::Any *res = new CORBA::Any;
            *res <<= get_impl (o);
            svreq->result (res);
        }
	return;
    }
    if (!strcmp (svreq->op_name(), "_is_a")) {
	CORBA::NVList_ptr args;
	_orb->create_list (0, args);
	args->add (CORBA::ARG_IN);
	args->item(0)->value()->set_type (CORBA::_tc_string);
	if (svreq->params (args)) {
            char *repoid;
            CORBA::Boolean r = (*args->item(0)->value() >>= repoid);
            assert (r);

            ObjectRecord *rec = get_record (o);
            assert (rec);
            r = load_object (rec);
            assert (r);
            CORBA::Boolean isa = rec->skel()->_is_a (repoid);

            CORBA::Any *res = new CORBA::Any;
            *res <<= CORBA::Any::from_boolean (isa);
            svreq->result (res);
        }
	return;
    }
    if (!strcmp (svreq->op_name(), "_non_existent")) {
	CORBA::NVList_ptr args;
	_orb->create_list (0, args);
	if (svreq->params (args)) {
            CORBA::Any *res = new CORBA::Any;
            *res <<= CORBA::Any::from_boolean (FALSE);
            svreq->result (res);
        }
	return;
    }
}

CORBA::Boolean
MICO::BOAImpl::invoke (MsgId msgid,
		       CORBA::Object_ptr o,
		       CORBA::ORBRequest *req,
		       CORBA::Principal_ptr pr,
		       CORBA::Boolean response_exp)
{
    if (must_queue (msgid)) {
	_queue.add (new MICO::ReqQueueRec (msgid, req, o, pr, response_exp));
	return TRUE;
    }
    /*
     * ServerRequest dtor will call answer_invoke().
     * this way an object implementation can _duplicate() a ServerRequest
     * to defer completion of a request.
     */
    ObjectRecord *rec = get_record (o);
    if ((_state != BOAActive || !rec || rec->state() != BOAActive) &&
	!CORBA::is_nil (_oamed) &&
	(!rec || !_oasrv->_is_equivalent (rec->local_obj()))) {
	// forward back to mediator ...

	CORBA::Long objkeylen;
	const CORBA::Octet *objkey =
	    o->_ior()->profile()->objectkey (objkeylen);

	CORBA::OAMediator::RefData key;
	key.length (objkeylen);
	memcpy (&key[0], objkey, objkeylen);

	queue();
	CORBA::Object_var fwd_obj = _oamed->get_remote_object (key);
	unqueue();
	assert (!CORBA::is_nil (fwd_obj));

	_orb->answer_invoke (msgid, CORBA::InvokeForward, fwd_obj, req);
	return TRUE;
    }
    if (!rec) {
	/*
	 * object has been deleted inbetween the call to has_object()
	 * and now, because we had to queue the invocation ...
	 */
        CORBA::OBJECT_NOT_EXIST ex;
	req->set_out_args (&ex);
	_orb->answer_invoke (msgid, CORBA::InvokeSysEx,
			     CORBA::Object::_nil(), req);
	return TRUE;
    }

    if (is_builtin_invoke (req->op_name())) {
	CORBA::ServerRequest_var svreq
	    = new CORBA::ServerRequest (req, o, msgid, this, pr);

	builtin_invoke (o, svreq, pr);
    } else {
	CORBA::Boolean r = load_object (rec);
	assert (r);
	CORBA::ImplementationBase *skel = rec->skel ();
	assert (skel);

	CORBA::ServerRequestBase_var svreq
	    = skel->make_request (req, o, msgid, this, pr);
        /*
	 * XXX setting _curr_env is a hack to enable method
	 * implementations to call get_principal (..., Environment::_nil()),
	 * because they do not have access to the environment. see also
	 * get_principal().  will cause problems if multiple methods
	 * are executed concurrently (ie in case of multi-threading).
	 */
	_curr_environ = svreq->environment();
	skel->doinvoke (svreq, *svreq->environment());
	_curr_environ = CORBA::Environment::_nil();
    }
    return TRUE;
}

void
MICO::BOAImpl::answer_invoke (MsgId msgid,
                              CORBA::Object_ptr obj,
                              CORBA::ORBRequest *req,
			      CORBA::InvokeStatus stat)
{
    _orb->answer_invoke (msgid, stat, CORBA::Object::_nil(), req);

    if (_amode == CORBA::ImplementationDef::ActivatePerMethod) {
	// shutdown per-method servers after one (non-builtin) invocation
	if (!is_builtin_invoke (req->op_name()))
	    _orb->shutdown (TRUE);
    }
}

CORBA::Boolean
MICO::BOAImpl::activate (const char *repoid)
{
    CORBA::Object_var obj =
	_orb->resolve_initial_references ("ImplementationRepository");
    CORBA::ImplRepository_var imr = CORBA::ImplRepository::_narrow (obj);
    assert (!CORBA::is_nil (imr));

    CORBA::ImplRepository::ImplDefSeq_var ims = imr->find_by_repoid (repoid);

    for (CORBA::ULong i = 0; i < ims->length(); ++i) {
	if (ims[i]->mode() == CORBA::ImplementationDef::ActivateLibrary) {
	    CORBA::String_var name = ims[i]->command();

	    // found one, see if its already loaded ...
	    ListShlib::iterator j;
	    for (j = _shlibs.begin(); j != _shlibs.end(); ++j) {
		if (!strcmp ((*j)->name(), name))
		    break;
	    }
	    if (j != _shlibs.end())
		// already loaded, try next
		continue;

	    // load it
	    MICODebug::instance()->tracer()
		<< "BOA: loading shlib " << name.in() << endl;

	    MICO::SharedLib *shlib = new UnixSharedLib (name);
	    if (!*shlib) {
		MICODebug::instance()->printer()
		    << "BOA: could not load shlib " << name.in() << ": "
		    << shlib->error() << endl;
		delete shlib;
		continue;
	    }

	    /*
	     * register it. even if initialization fails we will not
	     * unload it, because when binding next time we would
	     * load it again, see it fails and unload it again ...
	     * furthermore unloading could cause dangling pointers
	     * if the shlib already registered objects.
	     */
	    _shlibs.push_back (shlib);

	    if (!shlib->init ()) {
		MICODebug::instance()->printer()
		    << "BOA: could not init shlib " << name.in() << endl;
		continue;
	    }
	    return TRUE;
	}
    }
    return FALSE;
}

CORBA::Boolean
MICO::BOAImpl::dobind (MsgId msgid, const char *repoid,
		       const CORBA::ORB::ObjectTag &oid,
		       CORBA::Address *addr)
{
    for (MapObjRec::iterator i=_lobjs.begin(); i != _lobjs.end(); ++i) {
	ObjectRecord *rec = (*i).second;
	// XXX do a more flexible repoid comparision ...
	if (!strcmp (repoid, rec->local_obj()->_repoid()) &&
	    (oid.length() == 0 || oid == *rec->id())) {
	    CORBA::Boolean r = load_object (rec);
	    assert (r);
	    _orb->answer_bind (msgid, CORBA::LocateHere, rec->skel());
	    return TRUE;
	}
    }
    return FALSE;
}

CORBA::Boolean
MICO::BOAImpl::bind (MsgId msgid, const char *repoid,
		     const CORBA::ORB::ObjectTag &oid,
		     CORBA::Address *addr)
{
    if (addr && !addr->is_local())
	// not a local object
	return FALSE;

    if (must_queue (msgid)) {
	_queue.add (new MICO::ReqQueueRec (msgid, repoid, oid));
	return TRUE;
    }

    queue();
    while (42) {
	if (dobind (msgid, repoid, oid, addr)) {
	    unqueue();
	    return TRUE;
	}

	// if nothing found try loading a shared object and repeat search
	if (!activate (repoid))
	    break;
    }

    CORBA::Boolean ret = Interceptor::BOAInterceptor::_exec_bind (repoid, oid);

    if (ret && dobind (msgid, repoid, oid, addr)) {
	unqueue();
	return TRUE;
    }
    unqueue();

    return FALSE;
}

CORBA::Boolean
MICO::BOAImpl::locate (MsgId msgid, CORBA::Object_ptr o)
{
    _orb->answer_locate (msgid, CORBA::LocateHere, CORBA::Object::_nil());
    return TRUE;
}

CORBA::Object_ptr
MICO::BOAImpl::skeleton (CORBA::Object_ptr o)
{
    ObjectRecord *rec = get_record (o);
    if (!rec)
	return CORBA::Object::_nil();
    CORBA::Boolean r = load_object (rec);
    assert (r);
    return CORBA::Object::_duplicate (rec->skel ());
}

void
MICO::BOAImpl::cancel (MsgId msgid)
{
}

void
MICO::BOAImpl::shutdown (CORBA::Boolean wait_for_completion)
{
    if (_amode == CORBA::ImplementationDef::ActivatePerMethod)
	// automatically deactivate per-method server object
	deactivate_obj (CORBA::Object::_nil());

    save_objects ();
    dispose_objects();

    // XXX how to wait for completion ??
    _orb->answer_shutdown (this);
}

const char *
MICO::BOAImpl::impl_name ()
{
    if (_impl_name.length() == 0) {
        // generate a unique impl name ...
        _impl_name = InetAddress::hostname ();
	_impl_name += ":";
        _impl_name += xdec (OSMisc::getpid());
    }
    return _impl_name.c_str();
}

void
MICO::BOAImpl::save_objects ()
{
    for (MapObjRec::iterator i = _lobjs.begin(); i != _lobjs.end(); ++i) {
	ObjectRecord *rec = (*i).second;
	save_object (rec);
    }
}

void
MICO::BOAImpl::save_object (ObjectRecord *rec)
{
    if (rec->skel() && rec->save() && rec->local_obj() != rec->remote_obj()) {
        rec->persistent (rec->skel()->_save_object());
	rec->save (FALSE);
    }
}

void
MICO::BOAImpl::dispose_objects ()
{
    for (MapObjRec::iterator i = _lobjs.begin(); i != _lobjs.end(); ++i) {
	ObjectRecord *rec = (*i).second;
	dispose_object (rec);
    }
}

void
MICO::BOAImpl::dispose_object (ObjectRecord *rec)
{
    if (rec->skel() && rec->local_obj() != rec->remote_obj()) {
        CORBA::Boolean r = rec->save();
	assert (!r);
	if (!rec->persistent() && !CORBA::is_nil (_oamed)) {
	    _oamed->dispose_obj (rec->remote_obj(), _oasrv_id);
	}
    }
}

CORBA::Boolean
MICO::BOAImpl::load_object (ObjectRecord *rec)
{
    if (rec->skel())
	return TRUE;

    /*
     * XXX this may lead to infinite recursion if the object loader
     * code (indirectly) makes calls to ORB/BOA methods (e.g.
     * ORB::string_to_object()) that result in a call to load_object()
     * for the same object.
     */
    queue ();
    CORBA::Boolean ret;
    ret = Interceptor::BOAInterceptor::_exec_restore (rec->remote_obj());
    unqueue ();

    if (!ret)
	return FALSE;

    return !!rec->skel();
}

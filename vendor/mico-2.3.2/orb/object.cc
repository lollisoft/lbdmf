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

#include <CORBA-SMALL.h>
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/throw.h>
#ifdef USE_MEMTRACE
#include <mico/memtrace.h>
#endif


/*************************** MagicChecker ****************************/


void
CORBA::MagicChecker::_check () const
{
    if (!this || magic != MICO_OBJ_MAGIC) {
#ifdef USE_MEMTRACE
	MemTrace_SelfTrace (stderr);
#endif
	mico_throw (BAD_PARAM());
    }
}

void
CORBA::MagicChecker::_check (const CORBA::Exception &ex) const
{
    if (!this || magic != MICO_OBJ_MAGIC) {
#ifdef USE_MEMTRACE
	MemTrace_SelfTrace (stderr);
#endif
	((CORBA::Exception&)ex)._raise();
    }
}

CORBA::Boolean
CORBA::MagicChecker::_check_nothrow () const
{
    if (!this || magic != MICO_OBJ_MAGIC) {
	MICODebug::instance()->printer() <<
	    "invalid object reference" << endl;
#ifdef USE_MEMTRACE
	MemTrace_SelfTrace (stderr);
#endif
	return FALSE;
    }
    return TRUE;
}


/************************* ServerlessObject **************************/


CORBA::ServerlessObject::~ServerlessObject ()
{
}

void
CORBA::ServerlessObject::_ref ()
{
    _check ();
    ++refs;
}

CORBA::Boolean
CORBA::ServerlessObject::_deref ()
{
    return _check_nothrow() && --refs <= 0;
}

CORBA::Long
CORBA::ServerlessObject::_refcnt () const
{
    _check ();
    return refs;
}


/****************************** Object *******************************/


#ifdef HAVE_NAMESPACE
namespace CORBA {
    CORBA::Object_ptr OBJECT_NIL = 0;
}
#else
CORBA::Object_ptr CORBA::OBJECT_NIL = 0;
#endif


// consumes IOR* argument
CORBA::Object::Object (IOR *i)
{
    ior = i;
    fwd_ior = 0;
    orb = CORBA::ORB_instance ("mico-local-orb");
    assert (orb);
}

CORBA::Object::Object (const Object &o)
{
    ior = o.ior ? new IOR (*o.ior) : 0;
    fwd_ior = o.fwd_ior ? new IOR (*o.fwd_ior) : 0;
    orb = CORBA::ORB::_duplicate (o.orb);
    _managers = o._managers;
    _policies = o._policies;
}

CORBA::Object &
CORBA::Object::operator= (const Object &o)
{
    MICO_OBJ_CHECK (this);

    if (this != &o) {
	if (ior)
	    delete ior;
	ior = o.ior ? new IOR (*o.ior) : 0;
	if (fwd_ior)
	    delete fwd_ior;
	fwd_ior = o.fwd_ior ? new IOR (*o.fwd_ior) : 0;
	CORBA::release (orb);
	orb = CORBA::ORB::_duplicate (o.orb);
	_managers = o._managers;
	_policies = o._policies;
    }
    return *this;
}

CORBA::Object::~Object ()
{
    if (ior)
        delete ior;
    if (fwd_ior)
        delete fwd_ior;
    CORBA::release (orb);
}

void
CORBA::Object::_forward (CORBA::Object_ptr o)
{
    assert (!CORBA::is_nil (o) && o->ior);
    if (fwd_ior)
	delete fwd_ior;
    fwd_ior = new IOR (*o->ior);
}

void
CORBA::Object::_unforward ()
{
    if (fwd_ior) {
	delete fwd_ior;
	fwd_ior = 0;
    }
}

void
CORBA::Object::_setup_domains (CORBA::Object_ptr parent)
{
    if (CORBA::is_nil (parent)) {
	CORBA::DomainManager_var def_manager;
	orb->get_default_domain_manager (def_manager);

	_managers.length (1);

	CORBA::Policy_var p =
	    def_manager->_get_policy (CORBA::SecConstruction);
	assert (!CORBA::is_nil (p));

	CORBA::ConstructionPolicy_var cp =
	    CORBA::ConstructionPolicy::_narrow (p);

	if (cp->constr_policy (this)) {
	    _managers[0] = def_manager->copy();
	} else {
	    _managers[0] = def_manager._retn();
	}
    } else {
	CORBA::DomainManagerList_var dml = parent->_get_domain_managers();
	_managers.length (dml->length());

	for (CORBA::ULong i = 0; i < dml->length(); ++i) {
	    CORBA::Policy_var p =
		dml[i]->_get_policy (CORBA::SecConstruction);
	    assert (!CORBA::is_nil (p));

	    CORBA::ConstructionPolicy_var cp =
		CORBA::ConstructionPolicy::_narrow (p);

	    if (cp->constr_policy (this)) {
		_managers[i] = CORBA::DomainManager::_duplicate (dml[i]);
	    } else {
		_managers[i] = dml[i]->copy();
	    }
	}
    }
}

const char *
CORBA::Object::_ident ()
{
    IORProfile *prof = _ior()->profile (IORProfile::TAG_ANY);
    assert (prof);
    Long len;
    const Octet *key = prof->objectkey (len);
    ident = "";
    for (int i = 0; i < len; ++i) {
	ident += mico_to_xdigit ((key[i] >> 4) & 0xf);
	ident += mico_to_xdigit (key[i] & 0xf);
    }
    return ident.c_str();
}

void *
CORBA::Object::_narrow_helper (const char *)
{
    return NULL;
}

CORBA::ImplementationDef_ptr
CORBA::Object::_get_implementation ()
{
    return _orbnc()->get_impl (this);
}

CORBA::InterfaceDef_ptr
CORBA::Object::_get_interface ()
{
    MICO_OBJ_CHECK2 (this, CORBA::OBJECT_NOT_EXIST());

    return _orbnc()->get_iface (this);
}

void
CORBA::Object::_create_request (Context_ptr ctx,
				const char *op,
				NVList_ptr args,
				NamedValue_ptr result,
				Request_ptr &request,
				Flags flags)
{
    request = new Request (this, ctx, op, args, result, flags);
}

void
CORBA::Object::_create_request (Context_ptr ctx,
				const char *op,
				NVList_ptr args,
				NamedValue_ptr result,
				ExceptionList_ptr elist,
				ContextList_ptr clist,
				Request_ptr &request,
				Flags flags)
{
    request = new Request (this, ctx, op, args, result, elist, clist, flags);
}

CORBA::Request_ptr
CORBA::Object::_request (const char *op)
{
    return new Request (this, op);
}

CORBA::Policy_ptr
CORBA::Object::_get_policy (PolicyType policy_type)
{
    // look at this objects's policies
    for (CORBA::ULong i0 = 0; i0 < _policies.length(); ++i0) {
	if (_policies[i0]->policy_type() == policy_type)
	    return CORBA::Policy::_duplicate (_policies[i0]);
    }
    // look at domain manager policies
    for (CORBA::ULong i1 = 0; i1 < _managers.length(); ++i1) {
	CORBA::Policy_ptr p = _managers[i1]->_get_policy (policy_type);
	if (!CORBA::is_nil (p))
	    return p;
    }
    mico_throw (CORBA::BAD_PARAM());
    return CORBA::Policy::_nil();
}

CORBA::DomainManagerList *
CORBA::Object::_get_domain_managers ()
{
    return new DomainManagerList (_managers);
}

CORBA::Object_ptr
CORBA::Object::_set_policy_overrides (const PolicyList &policies,
				      SetOverrideType set_add)
{
    CORBA::Object_ptr nobj = new CORBA::Object (*this);
    switch (set_add) {
    case CORBA::SET_OVERRIDE:
	nobj->_policies = policies;
	break;

    case CORBA::ADD_OVERRIDE: {
	for (CORBA::ULong i = 0; i < policies.length(); ++i) {
	    CORBA::ULong j;
	    for (j = 0; j < nobj->_policies.length(); ++j) {
		if (nobj->_policies[j]->policy_type() ==
		      policies[i]->policy_type()) {
		    nobj->_policies[j] =
			CORBA::Policy::_duplicate (policies[i]);
		    break;
		}
	    }
	    if (j == nobj->_policies.length()) {
		nobj->_policies.length (j+1);
		nobj->_policies[j] = CORBA::Policy::_duplicate (policies[i]);
	    }
	}
	break;
    }
    default:
	assert (0);
    }
    return nobj;
}

CORBA::Boolean
CORBA::Object::_is_a (const char *repoid)
{
    MICO_OBJ_CHECK2 (this, CORBA::OBJECT_NOT_EXIST());

    // check some trivial cases first
    if (!strcmp (repoid, "IDL:omg.org/CORBA/Object:1.0"))
	return TRUE;
    if (!strcmp (repoid, _repoid()))
	return TRUE;

    // try IDL compiler generated narrowing support
    if (_narrow_helper (repoid))
	return TRUE;

    return _is_a_remote (repoid);
}

CORBA::Boolean
CORBA::Object::_is_a_remote (const char *repoid)
{
    // only ask remote if we are a stub
    if (_orbnc()->is_impl (this))
	return FALSE;
    return _orbnc()->is_a (this, repoid);
}

CORBA::Boolean
CORBA::Object::_non_existent ()
{
    if (CORBA::is_nil (this))
	return FALSE;

    if (!_check_nothrow())
	return TRUE;

    return _orbnc()->non_existent (this);
}

CORBA::Boolean
CORBA::Object::_is_equivalent (Object_ptr o)
{
    if (CORBA::is_nil (this) && CORBA::is_nil (o))
	return TRUE;

    if (!CORBA::is_nil (this))
	MICO_OBJ_CHECK2 (this, CORBA::OBJECT_NOT_EXIST());

    if (!CORBA::is_nil (o))
	MICO_OBJ_CHECK2 (o, CORBA::OBJECT_NOT_EXIST());

    if (CORBA::is_nil (this) || CORBA::is_nil (o))
	return FALSE;

    if (this == o)
	return TRUE;
    return *_ior() == *o->_ior();
}

CORBA::ULong
CORBA::Object::_hash (ULong max)
{
    MICO_OBJ_CHECK2 (this, CORBA::OBJECT_NOT_EXIST());

    string s = _ior()->stringify();
    return mico_string_hash (s.c_str(), max);
}

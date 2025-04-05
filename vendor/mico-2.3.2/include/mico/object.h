// -*- c++ -*-
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

#ifndef __mico_object_h__
#define __mico_object_h__

// base class for all serverless objects
class ServerlessObject : public MagicChecker {
    Long refs;
public:
    virtual ~ServerlessObject ();

    void _ref ();
    Boolean _deref ();
    Long _refcnt () const;

    static ServerlessObject* _nil ()
    {
	return 0;
    }
    static ServerlessObject* _duplicate (ServerlessObject *o)
    {
	if (o)
	    o->_ref();
	return o;
    }
protected:
    ServerlessObject ()
    { refs = 1; }

    ServerlessObject (const ServerlessObject &so)
        : MICO_SCOPE (CORBA,MagicChecker) (so)
    { refs = 1; }

    ServerlessObject &operator= (const ServerlessObject &)
    { return *this; }
};

typedef ServerlessObject *ServerlessObject_ptr;
typedef ObjVar<ServerlessObject> ServerlessObject_var;

MICO_INLINE_FCT_DECL void release (ServerlessObject *o)
{
    if (o && o->_deref())
	delete o;
}

MICO_INLINE_FCT_DECL Boolean is_nil (ServerlessObject *o)
{
    return !o;
}


// forward declarations from policy.idl
class Policy;
typedef Policy *Policy_ptr;
typedef ObjVar<Policy> Policy_var;
typedef IfaceSequenceTmpl<CORBA::Policy_var,CORBA::Policy_ptr> PolicyList;

class DomainManager;
typedef DomainManager *DomainManager_ptr;
typedef ObjVar<DomainManager> DomainManager_var;
typedef IfaceSequenceTmpl<CORBA::DomainManager_var,CORBA::DomainManager_ptr> DomainManagerList;

typedef CORBA::ULong PolicyType;

enum SetOverrideType {
    SET_OVERRIDE,
    ADD_OVERRIDE
};

// object, base class for all serverbased objects
class Object : public ServerlessObject {
    IOR *ior;
    IOR *fwd_ior;
    ORB_ptr orb;
    string ident;
protected:
    DomainManagerList _managers;
    PolicyList _policies;
public:
    ImplementationDef *_get_implementation ();
    InterfaceDef *_get_interface ();

    void _create_request (Context_ptr ctx,
			  const char *operation,
			  NVList_ptr arg_list,
			  NamedValue_ptr result,
			  Request_ptr &request,
			  Flags req_flags);

    void _create_request (Context_ptr ctx,
			  const char *operation,
			  NVList_ptr arg_list,
			  NamedValue_ptr result,
			  ExceptionList_ptr,
			  ContextList_ptr,
			  Request_ptr &request,
			  Flags req_flags);

    Request_ptr _request (const char *operation);

    Policy_ptr _get_policy (PolicyType policy_type);
    DomainManagerList *_get_domain_managers ();
    Object_ptr _set_policy_overrides (const PolicyList &policies,
				      SetOverrideType set_add);

    // begin-not-in-appendix
    Boolean _is_a (const char *logical_type_id);
    Boolean _is_a_remote (const char *logical_type_id);
    Boolean _non_existent ();
    Boolean _is_equivalent (Object_ptr);
    ULong _hash (ULong max);
    // end-not-in-appendix

    // begin-mico-extension
    Object (IOR * = 0);
    Object (const Object &);
    Object &operator= (const Object &);
    virtual ~Object ();

    void _setup_domains (CORBA::Object_ptr parent);

    void _forward (CORBA::Object_ptr);
    void _unforward ();
    Boolean _is_forwarded ()
    { return !!fwd_ior; }

    ORB_ptr _orbnc ()
    { return orb; }

    IOR *_ior ()
    { return fwd_ior ? fwd_ior : ior; }

    const char *_repoid ()
    { return ior->objid(); }

    const char *_ident ();
    virtual void *_narrow_helper (const char *repoid);
    // end-mico-extension

    static Object_ptr _duplicate (Object_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static Object_ptr _nil ()
    {
	return 0;
    }
};

typedef ObjVar<Object> Object_var;

MICO_EXPORT_VAR_DECL Object_ptr OBJECT_NIL;

// Generic prototype for narrow helper functions
typedef bool (*Narrow_proto) (Object_ptr);

#endif // __mico_object_h__

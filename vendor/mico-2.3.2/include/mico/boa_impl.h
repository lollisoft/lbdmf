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

#ifndef __mico_boa_impl_h__
#define __mico_boa_impl_h__

class BOAServImpl;

enum BOAState {
    BOAActive,
    BOAShutdown,
    BOAInactive
};

class ObjectRecord {
    CORBA::BOA::ReferenceData _id;
    CORBA::ImplementationDef * _impl;
    CORBA::InterfaceDef * _iface;
    CORBA::Object_ptr _local_obj;
    CORBA::Object_ptr _remote_obj;
    CORBA::ImplementationBase *_skel;
    CORBA::Boolean _save;
    // changed for CDK
    BOAState _state;
    CORBA::Boolean _persistent;
public:

    ObjectRecord (CORBA::Object_ptr local, const CORBA::BOA::ReferenceData &,
		  CORBA::InterfaceDef *, CORBA::ImplementationDef *,
		  CORBA::ImplementationBase * = NULL);
    ObjectRecord (CORBA::Object_ptr local, CORBA::Object_ptr remote,
		  const CORBA::BOA::ReferenceData &,
		  CORBA::InterfaceDef *, CORBA::ImplementationDef *,
		  CORBA::ImplementationBase * = NULL);
    ~ObjectRecord ();

    CORBA::BOA::ReferenceData *id ();

    CORBA::ImplementationDef *impl ();
    void impl (CORBA::ImplementationDef *);

    CORBA::InterfaceDef *iface ();
    void iface (CORBA::InterfaceDef *);

    CORBA::Object_ptr local_obj ();
    CORBA::Object_ptr remote_obj ();

    CORBA::ImplementationBase *skel ();
    void skel (CORBA::ImplementationBase *);

    void save (CORBA::Boolean);
    CORBA::Boolean save () const;

    void persistent (CORBA::Boolean);
    CORBA::Boolean persistent () const;

    void state (BOAState);
    BOAState state () const;
};

struct BOAObjKey {
    const CORBA::Octet *key;
    CORBA::Long len;

    BOAObjKey (CORBA::Object_ptr o)
    {
        key = o->_ior()->profile()->objectkey (len);
    }
    BOAObjKey ()
    {
    }
};

class BOAImpl : public CORBA::BOA, public CORBA::ObjectAdapter {
    struct objcomp : binary_function<const BOAObjKey &, const BOAObjKey &, bool> {
	bool operator() (const BOAObjKey &k1, const BOAObjKey &k2) const
	{
	    if (k1.len != k2.len)
		return k1.len < k2.len;
	    return mico_key_compare (k1.key, k2.key, k1.len) < 0;
	}
    };
    typedef map<BOAObjKey, ObjectRecord *, objcomp> MapObjRec;
    typedef list<MICO::SharedLib *> ListShlib;

    MapObjRec _lobjs, _robjs;
    ListShlib _shlibs;
    CORBA::ORB_ptr _orb;
    CORBA::ULong _theid;
    CORBA::OAMediator *_oamed;
    CORBA::OAServer *_oasrv;
    CORBA::OAMediator::ServerId _oasrv_id;
    CORBA::Object_ptr _active_obj;
    CORBA::ImplementationDef::ActivationMode _amode;
    string _impl_name;
    CORBA::Boolean _restoring;
    BOAState _state;
    CORBA::Environment_ptr _curr_environ;
    MICO::RequestQueue _queue;
    CORBA::Long _queue_count;
    CORBA::Octet _id_template[11];

    void queue ();
    void unqueue ();
    CORBA::Boolean must_queue (MsgId);
    CORBA::ImplementationDef *find_impl ();
    CORBA::Object_ptr find_obj ();
    void add_record (ObjectRecord *);
    ObjectRecord *get_record (CORBA::Object_ptr);
    void del_record (CORBA::Object_ptr);
    void del_all_records ();
    void unique_id (vector<CORBA::Octet> &id);
    CORBA::Boolean is_builtin_invoke (const char *opname);
    void builtin_invoke (CORBA::Object_ptr,
			 CORBA::ServerRequest_ptr,
			 CORBA::Principal_ptr);
    CORBA::Boolean activate (const char *repoid);
    void shutdown_obj (CORBA::Object_ptr);
    void shutdown_impl ();
    void restore_internal (CORBA::Object_ptr);

    CORBA::Boolean dobind (MsgId, const char *repoid,
			   const CORBA::ORB::ObjectTag &,
			   CORBA::Address *addr);

    CORBA::Boolean is_active_object (CORBA::Object_ptr obj);
public:
    BOAImpl (CORBA::ORB_ptr, int &argc, char **argv);
    ~BOAImpl ();

    CORBA::Object_ptr create (const ReferenceData &,
			      CORBA::InterfaceDef *,
			      CORBA::ImplementationDef *,
			      CORBA::ImplementationBase * = NULL,
			      const char *repoid = 0);
    // begin-mico-extension
    CORBA::Boolean restoring ();
    CORBA::Object_ptr restore (CORBA::Object_ptr,
    			       const ReferenceData &,
    			       CORBA::InterfaceDef *,
    			       CORBA::ImplementationDef *,
    			       CORBA::ImplementationBase *);
    CORBA::ORB_ptr orb ();
    const char *impl_name ();
    void save_objects ();
    void save_object (ObjectRecord *rec);
    void dispose_objects ();
    void dispose_object (ObjectRecord *rec);
    CORBA::Boolean load_object (ObjectRecord *rec);
    void answer_invoke (MsgId, CORBA::Object_ptr,
                        CORBA::ORBRequest *,
                        CORBA::InvokeStatus);
    // end-mico-extension
    void dispose (CORBA::Object_ptr);
    ReferenceData *get_id (CORBA::Object_ptr);
    void change_implementation (CORBA::Object_ptr,
    				CORBA::ImplementationDef *);
    CORBA::Principal_ptr get_principal (CORBA::Object_ptr,
    					CORBA::Environment_ptr);
    
    void impl_is_ready (CORBA::ImplementationDef *);
    void deactivate_impl (CORBA::ImplementationDef *);
    void obj_is_ready (CORBA::Object_ptr, CORBA::ImplementationDef *);
    void deactivate_obj (CORBA::Object_ptr);
    
    
    const char *get_oaid () const;
    CORBA::Boolean has_object (CORBA::Object_ptr);
    CORBA::Boolean is_local () const;
    
    CORBA::ImplementationDef *get_impl (CORBA::Object_ptr);
    CORBA::InterfaceDef *get_iface (CORBA::Object_ptr);
    
    CORBA::Boolean invoke (MsgId, CORBA::Object_ptr,
    			   CORBA::ORBRequest *,
    			   CORBA::Principal_ptr,
    			   CORBA::Boolean response_exp = TRUE);
    CORBA::Boolean bind (MsgId, const char *repoid,
    			 const CORBA::ORB::ObjectTag &,
    			 CORBA::Address *addr);
    CORBA::Boolean locate (MsgId, CORBA::Object_ptr);
    CORBA::Object_ptr skeleton (CORBA::Object_ptr);
    void cancel (MsgId);
    void shutdown (CORBA::Boolean wait_for_completion);

    friend class BOAServImpl;
};

class BOAServImpl : virtual public CORBA::OAServer_skel {
    BOAImpl *_boa;
public:
    BOAServImpl (BOAImpl *boa);
    ~BOAServImpl ();

    void restore_request (const CORBA::OAServer::ObjSeq &objs);
    void obj_inactive (CORBA::Object_ptr obj);
    void impl_inactive ();
};

#endif // __mico_boa_impl_h__

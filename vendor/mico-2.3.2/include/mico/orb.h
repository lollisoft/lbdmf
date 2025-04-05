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

#ifndef __mico_orb_h__
#define __mico_orb_h__


class ObjectAdapter;
//class ORBRequest;
struct ORBCallback;

typedef ORBRequest *ORBRequest_ptr;
typedef ObjVar<ORBRequest> ORBRequest_var;


class ORBInvokeRec {
public:
    typedef ULong MsgId;
private:
    MsgId _myid;
    RequestType _type;
    Boolean _have_result;
    Object_ptr _obj;
    Object_ptr _target;
    Principal_ptr _principal;
    Boolean _response_expected;
    string _repoid;
    InvokeStatus _invoke_stat;
    LocateStatus _locate_stat;
    ObjectAdapter *_adapter;
    ORBRequest *_req;
    ORBCallback *_cb;
    ORB_ptr _orb;
    OctetSeq _objtag;
    Address *_addr;
public:
    ORBInvokeRec ();
    virtual ~ORBInvokeRec ();

    void free();

    void init_invoke (ORB_ptr, MsgId, Object_ptr target,
		      ORBRequest *, Principal_ptr pr,
		      Boolean response_expected,
		      ORBCallback *, ObjectAdapter * = 0);

    void init_locate (ORB_ptr, MsgId, Object_ptr,
		      ORBCallback *, ObjectAdapter * = 0);

    void init_bind (ORB_ptr, MsgId, const char *,
		    const OctetSeq &tag, Address *, ORBCallback *,
		    ObjectAdapter * = 0);

    MsgId id () const
    { return _myid; }

    Boolean completed () const
    { return _have_result; }

    ObjectAdapter *oa ()
    { return _adapter; }

    void oa (ObjectAdapter *oa)
    { _adapter = oa; }
    
    RequestType request_type ()
    { return _type; }

    ORBRequest *request ()
    { return _req; }

    const OctetSeq &tag () const
    { return _objtag; }

    ORBCallback *callback ()
    { return _cb; }

    void redo ();

    void set_answer_invoke (InvokeStatus, Object_ptr, ORBRequest *);
    void set_answer_bind (LocateStatus, Object_ptr);
    void set_answer_locate (LocateStatus, Object_ptr);

    Boolean get_answer_invoke (InvokeStatus &, Object_ptr &, ORBRequest *&);
    Boolean get_answer_bind (LocateStatus &, Object_ptr &);
    Boolean get_answer_locate (LocateStatus &, Object_ptr &);
};



class ORB : public ServerlessObject {
public:
    typedef CORBA::ULong MsgId;
private:
    typedef vector<ObjectAdapter *> OAVec;
    typedef map<MsgId, ORBInvokeRec *, less<MsgId> > InvokeMap;
    typedef map<string, Object_var, less<string> > InitialRefMap;
    typedef map<string, ValueFactoryBase_var, less<string> > ValueFactoryMap;

    string _default_init_ref;
    list<string> _isa_cache;
    vector<string> _bindaddrs;
    OAVec _adapters;
    InvokeMap _invokes;
    Dispatcher *_disp;
    IOR *_tmpl;
    MsgId _theid;
    InitialRefMap _init_refs;
    string _rcfile;
    DomainManager_var _def_manager;
    ValueFactoryMap _value_facs;
    Boolean _is_running;
    Boolean _is_shutdown;
    Boolean _is_stopped;
    Boolean _wait_for_completion;
    OAVec _shutting_down_adapters;

    ORBInvokeRec *_cache_rec;
    CORBA::Boolean _cache_used;

    ObjectAdapter *get_oa (Object_ptr);
    ORBInvokeRec *create_invoke ();
    void add_invoke (ORBInvokeRec *);
    ORBInvokeRec *get_invoke (MsgId);
    void del_invoke (MsgId);

    void do_shutdown ();

    CORBA::Object_ptr iioploc_to_object (const char *);
    CORBA::Object_ptr iiopname_to_object (const char *);
    CORBA::Object_ptr file_to_object (const char *);
    CORBA::Object_ptr http_to_object (const char *);

    Boolean builtin_invoke (MsgId, Object_ptr,
                            ORBRequest *, Principal_ptr);
public:
    typedef IfaceSequenceTmpl<Request_var,Request_ptr> RequestSeq;
    typedef TSeqVar<RequestSeq> RequestSeq_var;

    typedef OctetSeq ObjectTag;
    typedef TSeqVar<ObjectTag> ObjectTag_var;

    ORB (int &argc, char **argv, const char *rcfile);
    virtual ~ORB ();

    char *object_to_string (Object_ptr);
    Object_ptr string_to_object (const char *);
    Object_ptr ior_to_object (IOR *);
    Boolean is_impl (Object_ptr);
    const char *rcfile();

    static char *tag_to_string (const ObjectTag &);
    static ObjectTag *string_to_tag (const char *);

    void create_list (Long, NVList_ptr &);
    void create_operation_list (OperationDef *,
				NVList_ptr &);
    void create_named_value (NamedValue_ptr &);
    void create_exception_list (ExceptionList_ptr &);
    void create_context_list (ContextList_ptr &);
    void create_environment (Environment_ptr &);
    
    void get_default_context (Context_ptr &);

    // mico-extension
    void get_default_domain_manager (DomainManager_ptr &);

    CORBA::Boolean get_service_information (
	CORBA::ServiceType service_type,
	CORBA::ServiceInformation *& service_information);

    void send_multiple_requests_oneway (const RequestSeq &);
    void send_multiple_requests_deferred (const RequestSeq &);
    Boolean poll_next_response ();
    void get_next_response (Request_ptr &);

    Boolean work_pending ();
    void perform_work ();
    void run ();
    void shutdown (Boolean wait_for_completion);
    void destroy ();

    typedef char *OAid;
    BOA_ptr BOA_init (int &argc, char **argv, const char *boa_id = "");
    BOA_ptr BOA_instance (const char *id, Boolean create=TRUE);

    typedef CORBA::ORB_InvalidName InvalidName;
    typedef CORBA::ORB_InvalidName_catch InvalidName_catch;

    typedef char *ObjectId;
    typedef StringSequenceTmpl<String_var> ObjectIdList;
    typedef ObjectIdList *ObjectIdList_ptr;
    typedef TSeqVar<ObjectIdList> ObjectIdList_var;

    ObjectIdList_ptr list_initial_services ();
    Object_ptr resolve_initial_references (const char *id);
    Boolean set_initial_reference (const char *id, Object_ptr obj);
    Boolean set_default_initial_reference (const char *);

    virtual TypeCode_ptr create_struct_tc (const char *rep_id,
					   const char *name,
					   const StructMemberSeq &);
    virtual TypeCode_ptr create_union_tc (const char *rep_id,
					  const char *name,
					  TypeCode_ptr disc_type,
					  const UnionMemberSeq &);
    virtual TypeCode_ptr create_enum_tc (const char *rep_id,
					 const char *name,
					 const EnumMemberSeq &);
    virtual TypeCode_ptr create_exception_tc (const char *rep_id,
					      const char *name,
					      const StructMemberSeq &);
    virtual TypeCode_ptr create_alias_tc (const char *rep_id,
					  const char *name,
					  TypeCode_ptr orig_type);
    virtual TypeCode_ptr create_interface_tc (const char *rep_id,
					      const char *name);
    virtual TypeCode_ptr create_string_tc (ULong bound);
    virtual TypeCode_ptr create_wstring_tc (ULong bound);
    virtual TypeCode_ptr create_fixed_tc (UShort digits, Short scale);
    virtual TypeCode_ptr create_sequence_tc (ULong bound,
					     TypeCode_ptr el_type);
    virtual TypeCode_ptr create_recursive_sequence_tc (ULong bound,
						       ULong offset);
    virtual TypeCode_ptr create_array_tc (ULong length,
					  TypeCode_ptr el_type);
    virtual TypeCode_ptr create_value_tc (const char *rep_id, const char *name,
					  ValueModifier mod,
					  TypeCode_ptr concrete_base,
					  const ValueMemberSeq &members);
    virtual TypeCode_ptr create_value_box_tc (const char *rep_id,
					      const char *name,
					      TypeCode_ptr boxed_type);
    virtual TypeCode_ptr create_native_tc (const char *rep_id,
					   const char *name);
    virtual TypeCode_ptr create_recursive_tc (const char *rep_id);
    virtual TypeCode_ptr create_abstract_interface_tc (const char *rep_id,
						       const char *name);

    // begin-value
    ValueFactory register_value_factory (const char *repoid,
					 ValueFactory factory);
    void unregister_value_factory (const char *repoid);
    ValueFactory lookup_value_factory (const char *repoid);
    // end-value

    CORBA::Policy_ptr create_policy (CORBA::PolicyType type,
				     const CORBA::Any &any);

    // begin-mico-extension
    const vector<string> &bindaddrs () const
    {
	return _bindaddrs;
    }
    void bindaddrs (const vector<string> &b)
    {
	_bindaddrs = b;
    }

    void dispatcher (Dispatcher *);
    Dispatcher *dispatcher ()
    {
	return _disp;
    }
    IOR *ior_template ()
    {
	return _tmpl;
    }

    void register_oa (ObjectAdapter *, CORBA::UShort prio);
    void unregister_oa (ObjectAdapter *);

    MsgId new_msgid ();
    
    MsgId invoke_async (Object_ptr, ORBRequest *, Principal_ptr,
			Boolean rply = TRUE, ORBCallback * = 0,
			MsgId = 0);
    MsgId locate_async (Object_ptr, ORBCallback * = 0, MsgId = 0);
    MsgId bind_async (const char *repoid, const ObjectTag &,
		      Address *, ORBCallback * = 0, MsgId = 0);

    InvokeStatus invoke (Object_ptr &, ORBRequest *, Principal_ptr,
			 Boolean rply = TRUE);
    LocateStatus locate (Object_ptr &);
    LocateStatus bind (const char *repoid, const ObjectTag &,
		       Address *, Object_ptr &);
    Object_ptr bind (const char *repoid, const char *addr = 0);
    Object_ptr bind (const char *repoid, const ObjectTag &,
		     const char *addr = 0);

    void    cancel (MsgId);
    Boolean wait (MsgId, Long tmout = -1);
    Long    wait (vector<MsgId> &, Long tmout = -1);

    void answer_invoke (MsgId, InvokeStatus, Object_ptr, ORBRequest *);
    void answer_bind (MsgId, LocateStatus, Object_ptr);
    void answer_locate (MsgId, LocateStatus, Object_ptr);
    void answer_shutdown (ObjectAdapter *);

    InvokeStatus get_invoke_reply (MsgId, Object_ptr &, ORBRequest *&);
    LocateStatus get_locate_reply (MsgId, Object_ptr &);
    LocateStatus get_bind_reply (MsgId, Object_ptr &);

    RequestType request_type (MsgId);
    void redo_request (MsgId);

    ImplementationDef    *get_impl (Object_ptr);
    InterfaceDef         *get_iface (Object_ptr);
    Boolean               is_a (Object_ptr, const char *repoid);
    Boolean               non_existent (Object_ptr);
    // end-mico-extension

    static ORB_ptr _duplicate (ORB_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static ORB_ptr _nil ()
    {
	return 0;
    }
};

typedef ObjVar<ORB> ORB_var;


// ORB initialization
typedef char *ORBid;
MICO_EXPORT_FCT_DECL ORB_ptr ORB_init (int &argc, char **argv,
				       const char *id = "");
MICO_EXPORT_FCT_DECL ORB_ptr ORB_instance (const char *id, Boolean create=TRUE);


class ObjectAdapter {
    CORBA::UShort _prio;
public:
    typedef CORBA::ULong MsgId;

    enum {
	OAPriorityMin = 0,
	OAPriorityRemote = 100,
	OAPriorityLocal = 200,
	OAPriorityMax = 0xffff
    };

    CORBA::UShort priority () const
    {
	return _prio;
    }
    void priority (CORBA::UShort p)
    {
	_prio = p;
    }

    virtual const char *get_oaid () const = 0;
    virtual Boolean has_object (Object_ptr) = 0;
    virtual Boolean is_local () const = 0;

    virtual Boolean invoke (MsgId, Object_ptr, ORBRequest *,
			    Principal_ptr, Boolean response_exp = TRUE) = 0;
    virtual Boolean bind (MsgId, const char *repoid,
			  const ORB::ObjectTag &,
			  Address *addr) = 0;
    virtual Boolean locate (MsgId, Object_ptr) = 0;
    virtual Object_ptr skeleton (Object_ptr) = 0;
    virtual void cancel (MsgId) = 0;
    virtual void shutdown (Boolean wait_for_completion) = 0;

    virtual void answer_invoke (CORBA::ULong, CORBA::Object_ptr,
				CORBA::ORBRequest *,
				CORBA::InvokeStatus) = 0;

    virtual ~ObjectAdapter ();
};

#endif // __mico_orb_h__

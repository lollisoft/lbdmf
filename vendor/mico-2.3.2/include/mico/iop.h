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

#ifndef __mico_iop_h__
#define __mico_iop_h__


class GIOPCodec;

class GIOPInContext {
    CORBA::DataDecoder *_dc;
    CORBA::Buffer *_buf;
    CORBA::Boolean _delete_buf;
public:
    GIOPInContext (GIOPCodec *, CORBA::Buffer *,
		   CORBA::CodesetConv *csc = 0,
		   CORBA::CodesetConv *wcsc = 0);
    ~GIOPInContext ();
    void converters (CORBA::CodesetConv *csc, CORBA::CodesetConv *wcsc);
    CORBA::DataDecoder *dc()
    { return _dc; }

    void buffer (CORBA::Buffer *);
    CORBA::DataDecoder *_retn();
};

class GIOPOutContext {
    CORBA::DataEncoder *_ec;
    CORBA::Buffer *_buf;
    CORBA::Boolean _delete_buf;
public:
    GIOPOutContext (GIOPCodec *, CORBA::CodesetConv *csc = 0,
		    CORBA::CodesetConv *wcsc = 0);
    GIOPOutContext (CORBA::DataEncoder *);
    ~GIOPOutContext ();
    void converters (CORBA::CodesetConv *csc, CORBA::CodesetConv *wcsc);
    CORBA::DataEncoder *ec()
    { return _ec; }

    void reset ();

    CORBA::Buffer *_retn();
};

#define GIOP_BYTEORDER_BIT 1
#define GIOP_FRAGMENT_BIT 2

class GIOPCodec;
typedef GIOPCodec *GIOPCodec_ptr;
typedef ObjVar<GIOPCodec> GIOPCodec_var;

class GIOPCodec : public CORBA::ServerlessObject {
    CORBA::DataDecoder *_dc_proto;
    CORBA::DataEncoder *_ec_proto;
    CORBA::ULong _headerlen;
    CORBA::ULong _size_offset;
    CORBA::UShort _giop_ver;

    CORBA::ULong put_header (GIOPOutContext &out, CORBA::GIOP::MsgType);
    void put_size (GIOPOutContext &out, CORBA::ULong key);
    void put_contextlist (GIOPOutContext &out,
			  const CORBA::IOP::ServiceContextList &ctx,
			  CORBA::Boolean codesets = FALSE);
    void put_target (GIOPOutContext &out, CORBA::Object_ptr obj);
    CORBA::Boolean put_args (GIOPOutContext &out, CORBA::ORBRequest *,
			     CORBA::Boolean inp);

    CORBA::Boolean get_contextlist (GIOPInContext &in,
				    CORBA::IOP::ServiceContextList &ctx,
				    CORBA::Boolean codesets = FALSE);
    CORBA::Boolean get_target (GIOPInContext &in, CORBA::Object_ptr obj);
public:
    GIOPCodec (CORBA::DataDecoder *dc, CORBA::DataEncoder *ec);
    ~GIOPCodec ();

    CORBA::DataDecoder *dc_proto()
    { return _dc_proto; }

    CORBA::DataEncoder *ec_proto()
    { return _ec_proto; }

    CORBA::UShort version () const
    { return _giop_ver; }

    CORBA::ULong header_length ()
    { return _headerlen; }

    CORBA::Boolean put_invoke_request (GIOPOutContext &out,
				       CORBA::ULong req_id,
				       CORBA::Octet response_flags,
				       CORBA::Object_ptr obj,
				       CORBA::ORBRequest *req,
				       CORBA::Principal_ptr pr);

    CORBA:: Boolean put_invoke_reply (GIOPOutContext &out,
				      CORBA::ULong req_id,
				      CORBA::GIOP::ReplyStatusType,
				      CORBA::Object_ptr obj,
				      CORBA::ORBRequest *req);

    CORBA::Boolean put_invoke_reply_offset (GIOPOutContext &out,
					    CORBA::ORBRequest *req);

    CORBA::Boolean put_cancel_request (GIOPOutContext &out,
				       CORBA::ULong req_id);

    CORBA::Boolean put_locate_request (GIOPOutContext &out,
				       CORBA::ULong req_id,
				       CORBA::Object_ptr obj);

    CORBA::Boolean put_locate_reply (GIOPOutContext &out,
				     CORBA::ULong req_id,
				     CORBA::GIOP::LocateStatusType,
				     CORBA::Object_ptr obj);

    CORBA::Boolean put_bind_request (GIOPOutContext &out,
				     CORBA::ULong req_id,
				     const char *repoid,
				     const CORBA::ORB::ObjectTag &);

    CORBA::Boolean put_bind_reply (GIOPOutContext &out,
				   CORBA::ULong req_id,
				   CORBA::GIOP::LocateStatusType,
				   CORBA::Object_ptr obj);

    CORBA::Boolean put_close_msg (GIOPOutContext &out);

    CORBA::Boolean put_error_msg (GIOPOutContext &out);

    CORBA::Boolean get_header (GIOPInContext &in, CORBA::GIOP::MsgType &,
			       CORBA::ULong &sz, CORBA::Octet &flags);
    CORBA::Boolean check_header (GIOPInContext &in, CORBA::GIOP::MsgType &,
				 CORBA::ULong &sz, CORBA::Octet &flags);

    CORBA::Boolean get_invoke_request (GIOPInContext &in,
				       CORBA::ULong &req_id,
				       CORBA::Octet &response_flags,
				       CORBA::Object_ptr obj,
				       CORBA::ORBRequest * &req,
				       CORBA::Principal_ptr pr);


    CORBA::Boolean get_invoke_reply1 (GIOPInContext &in,
				      CORBA::ULong &req_id,
				      CORBA::GIOP::ReplyStatusType &,
				      CORBA::IOP::ServiceContextList &ctx);

    CORBA::Boolean get_invoke_reply2 (GIOPInContext &in,
				      CORBA::ULong req_id,
				      CORBA::GIOP::ReplyStatusType,
				      CORBA::Object_ptr &obj,
				      CORBA::ORBRequest *req,
				      CORBA::IOP::ServiceContextList &ctx);

    CORBA::Boolean get_cancel_request (GIOPInContext &in,
				       CORBA::ULong &req_id);

    CORBA::Boolean get_locate_request (GIOPInContext &in,
				       CORBA::ULong &req_id,
				       CORBA::Object_ptr obj);

    CORBA::Boolean get_locate_reply (GIOPInContext &in,
				     CORBA::ULong &req_id,
				     CORBA::GIOP::LocateStatusType &,
				     CORBA::Object_ptr &obj);

    CORBA::Boolean get_bind_request (GIOPInContext &in,
				     char *& repoid,
				     CORBA::ORB::ObjectTag &);

    CORBA::Boolean get_bind_reply (GIOPInContext &in,
				   CORBA::GIOP::LocateStatusType &,
				   CORBA::Object_ptr &obj);

    CORBA::Boolean get_close_msg (GIOPInContext &in);

    CORBA::Boolean get_error_msg (GIOPInContext &in);

    CORBA::Boolean get_fragment_header (GIOPInContext &in,
					CORBA::ULong &req_id,
					CORBA::Boolean &has_id);


    static GIOPCodec_ptr _duplicate (GIOPCodec_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static GIOPCodec_ptr _nil ()
    {
	return 0;
    }
};


class GIOPRequest : public CORBA::ORBRequest {
    string _opname;

    CORBA::DataDecoder *_idc;
    CORBA::ULong _istart;

    CORBA::DataEncoder *_oec;
    CORBA::DataDecoder *_odc;
    CORBA::ULong _ostart;
    CORBA::Buffer _obuf;

    GIOPCodec_ptr _codec;

    CORBA::Boolean _is_except;
public:
    GIOPRequest (const char *op, CORBA::DataDecoder *indata, GIOPCodec *);
    ~GIOPRequest ();
    
    const char *op_name();
    
    CORBA::Boolean get_in_args (CORBA::NVList_ptr iparams,
                                CORBA::Context_ptr &ctx);
    CORBA::Boolean get_in_args (StaticAnyList *iparams,
                                CORBA::Context_ptr &ctx);
    CORBA::Boolean get_in_args (CORBA::DataEncoder *);
    
    CORBA::Boolean get_out_args (CORBA::Any *res, CORBA::NVList_ptr oparams,
                                 CORBA::Exception *&ex);
    CORBA::Boolean get_out_args (CORBA::StaticAny *res, StaticAnyList *oparams,
                                 CORBA::Exception *&ex);
    CORBA::Boolean get_out_args (CORBA::DataEncoder *,
                                 CORBA::Boolean &is_except);
    
    CORBA::Boolean set_out_args (CORBA::Any *res, CORBA::NVList_ptr oparams);
    CORBA::Boolean set_out_args (CORBA::StaticAny *res,
                                 StaticAnyList *oparams);
    void set_out_args (CORBA::Exception *ex);
    CORBA::Boolean set_out_args (CORBA::DataDecoder *,
                                 CORBA::Boolean is_except);

    CORBA::Boolean copy_out_args (CORBA::ORBRequest *);
    CORBA::Boolean copy_in_args (CORBA::ORBRequest *);
    
    const char *type ();
    CORBA::ByteOrder input_byteorder ();
    CORBA::ByteOrder output_byteorder ();
    CORBA::Codeset::CodesetId csid ();
    CORBA::Codeset::CodesetId wcsid ();

    static GIOPRequest* _nil ()
    {
	return 0;
    }
    static GIOPRequest* _duplicate (GIOPRequest *o)
    {
	if (o)
	    o->_ref();
	return o;
    }
};


class GIOPSimpleProf : public CORBA::IORProfile {
public:
    CORBA::Octet *_objkey;
    CORBA::ULong _length;
public:
    GIOPSimpleProf ();
    GIOPSimpleProf (const GIOPSimpleProf &);
    ~GIOPSimpleProf ();
    GIOPSimpleProf &operator= (const GIOPSimpleProf &);

    void encode (CORBA::DataEncoder &) const;
    const CORBA::Address *addr () const;
    ProfileId id () const;
    ProfileId encode_id () const;
    void objectkey (CORBA::Octet *, CORBA::Long length);
    const CORBA::Octet *objectkey (CORBA::Long &length) const;
    CORBA::Boolean reachable ();
    void print (ostream &) const;
    
    CORBA::IORProfile *clone () const;
    CORBA::Long compare (const CORBA::IORProfile &) const;
    CORBA::Boolean operator== (const CORBA::IORProfile &) const;
    CORBA::Boolean operator< (const CORBA::IORProfile &) const;
};


struct GIOPConnCallback;

class GIOPConn : public CORBA::TransportCallback,
		 public CORBA::DispatcherCallback {
    CORBA::Dispatcher *_disp;
    CORBA::Transport *_transp;
    list<CORBA::Buffer *> _outbufs;
    CORBA::Buffer *_inbufs;
    CORBA::Buffer *_inbuf, *_infrag;
    CORBA::ULong _inlen;
    CORBA::Octet _inflags;
    GIOPConnCallback *_cb;
    GIOPCodec_ptr _codec;
    CORBA::ORB_ptr _orb;
    CORBA::Long _refcnt;
    CORBA::Long _idle_tmout;
    CORBA::Boolean _have_tmout;
    CORBA::Boolean _have_wselect;
    GIOPInContext _inctx;

    void check_idle ();
    void check_busy ();

    void do_write ();
public:
    void do_read ();

    GIOPConn (CORBA::ORB_ptr, CORBA::Transport *, GIOPConnCallback *,
	      GIOPCodec *, CORBA::Long tmout = 0);
    virtual ~GIOPConn ();

    virtual void callback (CORBA::Transport *,
			   CORBA::TransportCallback::Event);
    virtual void callback (CORBA::Dispatcher *,
			   CORBA::DispatcherCallback::Event);

    void ref ();
    CORBA::Boolean deref (CORBA::Boolean all = FALSE);

    void output (CORBA::Buffer *);
    CORBA::Buffer *input ();
    void flush ();
    CORBA::Boolean check_events ();

    CORBA::Transport *transport ()
    { return _transp; }

    GIOPCodec *codec ()
    { return _codec; }

    void cancel (CORBA::ULong reqid);
    void buffering (CORBA::Boolean dobuffering);
};

struct GIOPConnCallback {
    enum Event { InputReady, Closed, Idle };
    virtual CORBA::Boolean callback (GIOPConn *, Event) = 0;
    virtual ~GIOPConnCallback ();
};


class IIOPProxyInvokeRec {
public:
    typedef CORBA::ULong MsgId;
    typedef CORBA::Codeset::CodesetId CodesetId;
private:
    MsgId _id;
    GIOPConn *_conn;
    CORBA::ORBRequest *_req;
    CodesetId _csid;
    CodesetId _wcsid;
public:
    IIOPProxyInvokeRec ()
    {}

    ~IIOPProxyInvokeRec ()
    {}

    void free ()
    {}

    void init (MsgId id, GIOPConn *conn, CORBA::ORBRequest *req = 0,
	       CodesetId cs = 0, CodesetId wcs = 0)
    {
	_id = id;
	_conn = conn;
	_req = req;
	_csid = cs;
	_wcsid = wcs;
    }

    GIOPConn *conn () const
    { return _conn; }

    CORBA::ORBRequest *request () const
    { return _req; }

    CodesetId csid () const
    { return _csid; }

    CodesetId wcsid () const
    { return _wcsid; }

    MsgId id () const
    { return _id; }
};

class IIOPProxy : public CORBA::ObjectAdapter, public GIOPConnCallback {
    typedef map<MsgId, IIOPProxyInvokeRec *, less<MsgId> > MapIdConn;

    struct addrcomp :
	binary_function<const CORBA::Address *, const CORBA::Address *, bool> {
	bool operator() (const CORBA::Address *a1,
			 const CORBA::Address *a2) const
	{ return a1->compare (*a2) < 0; }
    };
    typedef map<const CORBA::Address *, GIOPConn *, addrcomp> MapAddrConn;
    typedef vector<CORBA::IORProfile::ProfileId> ProfIdVec;

    ProfIdVec _valid_profiles;
    MapIdConn _ids;
    MapAddrConn _conns;
    CORBA::ORB_ptr _orb;

    IIOPProxyInvokeRec *_cache_rec;
    CORBA::Boolean _cache_used;

    static CORBA::Boolean _isblocking;

    CORBA::Boolean get_codeset_ids (CORBA::Object_ptr,
				    CORBA::Codeset::CodesetId &csid,
				    CORBA::Codeset::CodesetId &wcsid);

    IIOPProxyInvokeRec *create_invoke ();
    IIOPProxyInvokeRec *get_invoke (MsgId id);
    void add_invoke (IIOPProxyInvokeRec *rec);
    void del_invoke (MsgId id);
    void abort_invoke (MsgId id);
    void redo_invoke (MsgId id);

    GIOPConn *make_conn (CORBA::Object_ptr);
    GIOPConn *make_conn (const CORBA::Address *, CORBA::Boolean create = TRUE);
    void kill_conn (GIOPConn *, CORBA::Boolean redo = FALSE);
    void conn_error (GIOPConn *, CORBA::Boolean send_error = TRUE);

    CORBA::Boolean handle_input (GIOPConn *);
    void exec_invoke_reply (GIOPInContext &, CORBA::ULong req_id,
			    CORBA::GIOP::ReplyStatusType,
			    CORBA::Object_ptr, CORBA::ORBRequest *,
			    GIOPConn *conn);
    CORBA::Boolean handle_invoke_reply (GIOPConn *conn, GIOPInContext &);
    CORBA::Boolean handle_locate_reply (GIOPConn *conn, GIOPInContext &);
public:
    IIOPProxy (CORBA::ORB_ptr);
    ~IIOPProxy ();

    static void block (CORBA::Boolean b)
    {
	_isblocking = b;
    }
    static CORBA::Boolean isblocking ()
    {
	return _isblocking;
    }
    
    const char *get_oaid () const;
    CORBA::Boolean has_object (CORBA::Object_ptr);
    CORBA::Boolean is_local () const;
    
    CORBA::Boolean invoke (MsgId, CORBA::Object_ptr,
    			   CORBA::ORBRequest *,
    			   CORBA::Principal_ptr,
    			   CORBA::Boolean repsonse_exp);
    CORBA::Boolean bind (MsgId, const char *repoid,
    			 const CORBA::ORB::ObjectTag &,
    			 CORBA::Address *addr);
    CORBA::Boolean locate (MsgId, CORBA::Object_ptr);
    CORBA::Object_ptr skeleton (CORBA::Object_ptr);
    void cancel (MsgId);
    void shutdown (CORBA::Boolean wait_for_completion);
    
    void answer_invoke (CORBA::ULong, CORBA::Object_ptr,
    			CORBA::ORBRequest *,
    			CORBA::InvokeStatus);
    
    CORBA::Boolean callback (GIOPConn *, GIOPConnCallback::Event);
};


class IIOPServerInvokeRec {
public:
    typedef CORBA::ULong MsgId;
private:
    CORBA::ORBRequest *_req;
    CORBA::Object_ptr _obj;
    CORBA::Principal_ptr _pr;
    MsgId _orbid, _reqid;
    GIOPConn *_conn;
public:
    IIOPServerInvokeRec ();
    ~IIOPServerInvokeRec ();
    void free ();

    void init_invoke (GIOPConn *conn, MsgId reqid, MsgId orbid,
		      CORBA::ORBRequest *req, CORBA::Object_ptr obj,
		      CORBA::Principal_ptr pr);
    void init_locate (GIOPConn *conn, MsgId reqid, MsgId orbid,
		      CORBA::Object_ptr obj);

    CORBA::ORBRequest *req()
    { return _req; }

    MsgId orbid()
    { return _orbid; }

    void orbid (MsgId id)
    { _orbid = id; }

    MsgId reqid()
    { return _reqid; }

    GIOPConn *conn()
    { return _conn; }
};

class IIOPServer : public CORBA::ObjectAdapter,
		   public CORBA::ORBCallback, public GIOPConnCallback,
		   public CORBA::TransportServerCallback {
    typedef CORBA::ULong MsgId;
    typedef map<MsgId, IIOPServerInvokeRec *, less<MsgId> > MapIdConn;
    typedef list<GIOPConn *> ListConn;
    typedef vector<CORBA::TransportServer *> VecTranspServ;

    VecTranspServ _tservers;
    ListConn _conns;
    MapIdConn _orbids;
    CORBA::ORB_ptr _orb;

    IIOPServerInvokeRec *_cache_rec;
    CORBA::Boolean _cache_used;

    IIOPServerInvokeRec *create_invoke();
    IIOPServerInvokeRec *get_invoke_reqid (MsgId, GIOPConn *conn);
    IIOPServerInvokeRec *get_invoke_orbid (MsgId);
    void add_invoke (IIOPServerInvokeRec *);
    void del_invoke_reqid (MsgId, GIOPConn *conn);
    void del_invoke_orbid (MsgId);
    void abort_invoke_orbid (MsgId);

    void kill_conn (GIOPConn *);
    void conn_error (GIOPConn *, CORBA::Boolean send_error = TRUE);
    void conn_closed (GIOPConn *);

    CORBA::Boolean handle_input (GIOPConn *);
    MsgId exec_invoke_request (GIOPInContext &, CORBA::Object_ptr,
			       CORBA::ORBRequest *,
			       CORBA::Principal_ptr, CORBA::Boolean resp_exp,
			       GIOPConn *conn,
			       MsgId msgid);
    CORBA::Boolean handle_invoke_request (GIOPConn *conn, GIOPInContext &);
    CORBA::Boolean handle_locate_request (GIOPConn *conn, GIOPInContext &);
    CORBA::Boolean handle_cancel_request (GIOPConn *conn, GIOPInContext &);

    void handle_invoke_reply (MsgId msgid);
    void handle_locate_reply (MsgId msgid);
    void handle_bind_reply (MsgId msgid);
public:
    IIOPServer (CORBA::ORB_ptr);
    ~IIOPServer ();

    CORBA::Boolean listen (CORBA::Address *, CORBA::Address *);
    CORBA::Boolean listen ();

    // ObjectAdapter methods
    const char *get_oaid () const;
    CORBA::Boolean has_object (CORBA::Object_ptr);
    CORBA::Boolean is_local () const;
    
    CORBA::Boolean invoke (MsgId, CORBA::Object_ptr,
    			   CORBA::ORBRequest *,
    			   CORBA::Principal_ptr,
    			   CORBA::Boolean repsonse_exp);
    CORBA::Boolean bind (MsgId, const char *repoid,
    			 const CORBA::ORB::ObjectTag &,
    			 CORBA::Address *addr);
    CORBA::Boolean locate (MsgId, CORBA::Object_ptr);
    CORBA::Object_ptr skeleton (CORBA::Object_ptr);
    void cancel (MsgId);
    void shutdown (CORBA::Boolean wait_for_completion);
    
    void answer_invoke (CORBA::ULong, CORBA::Object_ptr,
    			CORBA::ORBRequest *,
    			CORBA::InvokeStatus);

		       
    void callback (CORBA::ORB_ptr, MsgId, CORBA::ORBCallback::Event);
    CORBA::Boolean callback (GIOPConn *, GIOPConnCallback::Event);
    void callback (CORBA::TransportServer *,
		   CORBA::TransportServerCallback::Event);
};

#endif // __mico_iop_h__

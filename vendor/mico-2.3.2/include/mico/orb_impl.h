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

#ifndef __mico_orb_impl_h__
#define __mico_orb_impl_h__

class LocalRequest : public CORBA::ORBRequest {
    CORBA::Request_ptr _req;
    CORBA::Boolean _have_except;
    CORBA::Boolean _have_result;
public:
    LocalRequest ();
    LocalRequest (CORBA::Request_ptr);
    ~LocalRequest ();
    
    const char *op_name();
    
    CORBA::Boolean get_in_args (CORBA::NVList_ptr iparams,
                                CORBA::Context_ptr &ctx);
    CORBA::Boolean get_in_args (StaticAnyList *iparams,
                                CORBA::Context_ptr &ctx);
    CORBA::Boolean get_in_args (CORBA::DataEncoder *);
    
    CORBA::Boolean get_out_args (CORBA::Any *res,
                                 CORBA::NVList_ptr oparams,
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

    CORBA::Request_ptr request ();

    static LocalRequest* _nil ()
    {
	return 0;
    }
    static LocalRequest* _duplicate (LocalRequest *o)
    {
	if (o)
	    o->_ref();
	return o;
    }
};


class ReqQueueRec {
public:
    typedef CORBA::ULong MsgId;
private:
    CORBA::RequestType _type;
    string _repoid;
    CORBA::ORBRequest *_request;
    CORBA::Object_ptr _obj;
    CORBA::Principal_ptr _pr;
    MsgId _id;
    CORBA::Boolean _response_exp;
    CORBA::ORB::ObjectTag _tag;
public:
    ReqQueueRec (MsgId id, CORBA::ORBRequest *, CORBA::Object_ptr,
		 CORBA::Principal_ptr, CORBA::Boolean resp); // invoke
    ReqQueueRec (MsgId id, const char *repoid,
		 const CORBA::ORB::ObjectTag &); // bind
    ReqQueueRec (MsgId id, CORBA::Object_ptr obj); // locate
    ~ReqQueueRec ();

    void exec (CORBA::ObjectAdapter *, CORBA::ORB_ptr);
    void fail (CORBA::ObjectAdapter *, CORBA::ORB_ptr);

    CORBA::Object_ptr target ();
    MsgId id () const
    { return _id; }
};

class RequestQueue : public CORBA::DispatcherCallback {
public:
    typedef CORBA::ULong MsgId;
private:
    typedef list<ReqQueueRec *> InvokeList;
    MsgId _current_id;
    InvokeList _invokes;
    CORBA::ObjectAdapter *_oa;
    CORBA::ORB_ptr _orb;
public:
    RequestQueue (CORBA::ObjectAdapter *, CORBA::ORB_ptr);
    ~RequestQueue ();

    void add (ReqQueueRec *);
    void exec_now ();
    void exec_later ();
    void exec_stop ();
    void fail ();
    void clear ();

    CORBA::Boolean iscurrent (MsgId id) const
    { return _current_id && id == _current_id; }

    CORBA::ULong size () const
    { return _invokes.size(); }

    // dispatcher callback
    virtual void callback (CORBA::Dispatcher *,
			   CORBA::DispatcherCallback::Event);
};

#endif // __mico_orb_impl_h__

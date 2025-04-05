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

#ifndef __mico_dsi_h__
#define __mico_dsi_h__

class ObjectAdapter;
class ORBRequest;

class ServerRequestBase : public CORBA::ServerlessObject {
protected:
    CORBA::Boolean _canceled;
public:
    ServerRequestBase ()
        : _canceled (FALSE)
    {}
    virtual ~ServerRequestBase ();

    virtual CORBA::Environment_ptr environment () = 0;
    void cancel ()
    { _canceled = TRUE; }

    static ServerRequestBase_ptr _duplicate (ServerRequestBase_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static ServerRequestBase_ptr _nil ()
    {
	return 0;
    }
};

typedef ObjVar<ServerRequestBase> ServerRequestBase_var;


class ImplementationBase : virtual public CORBA::Object {
protected:
    ORB_ptr _morb;
    BOA_ptr _mboa;
public:
    ImplementationBase ();
    virtual ~ImplementationBase ();

    virtual CORBA::Boolean _save_object ();
    ORB_ptr _orb ();
    ORB_ptr _orbnc ();

    virtual void _create_ref (const BOA::ReferenceData &, InterfaceDef *,
			      ImplementationDef *, const char *repoid);
    virtual void _restore_ref (Object_ptr orig, const BOA::ReferenceData &,
			       InterfaceDef *, ImplementationDef *);
    virtual void _dispose_ref ();
    virtual const char *_impl_name (const char *);

    ImplementationDef *_find_impl (const char *repoid, const char *name);
    InterfaceDef *_find_iface (const char *repoid);
    
    BOA_ptr _boa ();
    Object_ptr _this ();

    virtual ServerRequestBase_ptr make_request (ORBRequest *,
						CORBA::Object_ptr,
						CORBA::ULong,
						CORBA::ObjectAdapter *,
						CORBA::Principal_ptr) = 0;

    virtual void doinvoke (ServerRequestBase_ptr request,
			   Environment &env) = 0;
};

/*
 * XXX CORBA spec says all methods may throw SystemException (18-6) ...
 *
 * memory management:
 * - ServerRequest owns res and except, even dir_params (the NVList
 *   passed to params()) is freed by ServerRequest [18-6]
 * - params() must always be called by DIR exactly once [14-26]
 */
class ServerRequest : public ServerRequestBase {
    typedef CORBA::ULong MsgId;
    CORBA::ObjectAdapter *_oa;
    MsgId _msgid;
    Object_ptr _obj;
    ORBRequest *_req;
    NVList_ptr _dir_params;
    Context_ptr _context;
    Any_var _res;
    Environment _env;
    ServerlessObject_ptr _iceptreq;
    CORBA::Boolean _aborted;
public:
    // begin-mico-extension
    ServerRequest (ORBRequest *req, Object_ptr obj, MsgId msgid,
                   CORBA::ObjectAdapter *oa, CORBA::Principal_ptr);
    ~ServerRequest ();

    ORBRequest *request ();
    void set_out_args ();
    NVList_ptr arguments ();
    Any *result ();
    Exception *exception ();
    Environment_ptr environment ();
    // end-mico-extension

    // CORBA 2.2 mapping [20.36.1]
    const char * operation ();
    void arguments (NVList_ptr &);
    void set_result (const Any &);
    void set_exception (const Any &);
    // Context_ptr ctx () as below

    const char *op_name ();
    OperationDef_ptr op_def ();
    Context_ptr ctx ();
    CORBA::Boolean params (NVList_ptr params);
    void result (Any *val);
    void exception (Any *val);
    void exception (Exception *ex);

    static ServerRequest_ptr _duplicate (ServerRequest_ptr o)
    {
	if (o)
	    o->_ref();
	return o;
    }
    static ServerRequest_ptr _nil ()
    {
	return 0;
    }
};

typedef ObjVar<ServerRequest> ServerRequest_var;


// base class for all object implementations. constructor creates
// object reference and registers with BOA.
class DynamicImplementation : virtual public ImplementationBase {
public:
    DynamicImplementation ();
    virtual ~DynamicImplementation ();


    virtual ServerRequestBase_ptr make_request (ORBRequest *,
						CORBA::Object_ptr,
						CORBA::ULong,
						CORBA::ObjectAdapter *,
						CORBA::Principal_ptr);
    virtual void doinvoke (ServerRequestBase_ptr request,
			   Environment &env);
    virtual void invoke (ServerRequest_ptr request,
			 Environment &env) = 0;
};


#endif // __mico_dsi_h__

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
#include <mico/util.h>
#include <mico/impl.h>
#include <mico/template_impl.h>


/**************************** ReqQueueRec ***************************/


MICO::ReqQueueRec::ReqQueueRec (MsgId id, CORBA::ORBRequest *req,
				CORBA::Object_ptr obj,
				CORBA::Principal_ptr pr,
				CORBA::Boolean resp)
{
    _id = id;
    _request = CORBA::ORBRequest::_duplicate (req);
    _obj = CORBA::Object::_duplicate (obj);
    _pr = CORBA::Principal::_duplicate (pr);
    _response_exp = resp;
    _type = CORBA::RequestInvoke;
}

MICO::ReqQueueRec::ReqQueueRec (MsgId id, const char *repoid,
				const CORBA::ORB::ObjectTag &tag)
{
    _id = id;
    _repoid = repoid;
    _request = CORBA::ORBRequest::_nil();
    _obj = CORBA::Object::_nil();
    _pr = CORBA::Principal::_nil();
    _type = CORBA::RequestBind;
    _tag = tag;
}

MICO::ReqQueueRec::ReqQueueRec (MsgId id, CORBA::Object_ptr obj)
{
    _id = id;
    _request = CORBA::ORBRequest::_nil();
    _obj = CORBA::Object::_duplicate (obj);
    _pr = CORBA::Principal::_nil();
    _type = CORBA::RequestLocate;
}

MICO::ReqQueueRec::~ReqQueueRec ()
{
    CORBA::release (_request);
    CORBA::release (_obj);
    CORBA::release (_pr);
}

void
MICO::ReqQueueRec::exec (CORBA::ObjectAdapter *oa, CORBA::ORB_ptr orb)
{
    switch (_type) {
    case CORBA::RequestInvoke:
        oa->invoke (_id, _obj, _request, _pr, _response_exp);
        break;

    case CORBA::RequestBind:
        if (!oa->bind (_id, _repoid.c_str(), _tag, 0)) {
	    orb->answer_bind (_id, CORBA::LocateUnknown,
			      CORBA::Object::_nil());
	}
        break;

    case CORBA::RequestLocate:
        oa->locate (_id, _obj);
        break;

    default:
        assert (0);
    }
}

void
MICO::ReqQueueRec::fail (CORBA::ObjectAdapter *oa, CORBA::ORB_ptr orb)
{
    switch (_type) {
    case CORBA::RequestInvoke: {
        CORBA::COMM_FAILURE ex (0, CORBA::COMPLETED_MAYBE);
	_request->set_out_args (&ex);
	orb->answer_invoke (_id, CORBA::InvokeSysEx,
			    CORBA::Object::_nil(), _request);
        break;
    }
    case CORBA::RequestBind:
        orb->answer_bind (_id, CORBA::LocateUnknown,
			  CORBA::Object::_nil());
        break;

    case CORBA::RequestLocate:
        orb->answer_locate (_id, CORBA::LocateUnknown,
			    CORBA::Object::_nil());
        break;

    default:
        assert (0);
    }
}

CORBA::Object_ptr
MICO::ReqQueueRec::target ()
{
    return _obj;
}


/****************************** RequestQueue ****************************/


MICO::RequestQueue::RequestQueue (CORBA::ObjectAdapter *oa,
				  CORBA::ORB_ptr orb)
    : _oa (oa), _orb (orb), _current_id (0)
{
}

MICO::RequestQueue::~RequestQueue ()
{
    clear ();
    exec_stop ();
}

void
MICO::RequestQueue::add (ReqQueueRec *r)
{
    _invokes.push_back (r);
}

void
MICO::RequestQueue::exec_now ()
{
    // reissue pending invokes ...
    set<MsgId, less<MsgId> > seen;
    while (_invokes.size() > 0) {
	ReqQueueRec *inv = _invokes.front();
        _current_id = inv->id();
	if (seen.count (_current_id))
	    break;
	seen.insert (_current_id);
        _invokes.pop_front();
        /*
         * if invoke cannot be executed yet mediator will install
         * new ReqQueueRec ...
         */
	inv->exec (_oa, _orb);
	delete inv;
    }
    _current_id = 0;
}

void
MICO::RequestQueue::exec_later ()
{
    // schedule reexecution of pending requests ...
    if (_invokes.size() > 0) {
	_orb->dispatcher()->remove (this, CORBA::Dispatcher::Timer);
	_orb->dispatcher()->tm_event (this, 0 /* zero timeout */);
    }
}

void
MICO::RequestQueue::exec_stop ()
{
    _orb->dispatcher()->remove (this, CORBA::Dispatcher::Timer);
}

void
MICO::RequestQueue::fail ()
{
    // make pending invokes fail ...
    int sz = _invokes.size();
    while (--sz >= 0 && _invokes.size() > 0) {
        ReqQueueRec *inv = _invokes.front();
        _invokes.pop_front();

	inv->fail (_oa, _orb);
	delete inv;
    }
}

void
MICO::RequestQueue::clear ()
{
    for (InvokeList::iterator i = _invokes.begin(); i != _invokes.end(); ++i)
	delete *i;
    _invokes.erase (_invokes.begin(), _invokes.end());
}

void
MICO::RequestQueue::callback (CORBA::Dispatcher *,
			      CORBA::DispatcherCallback::Event ev)
{
    if (ev == CORBA::Dispatcher::Timer)
        exec_now ();
}

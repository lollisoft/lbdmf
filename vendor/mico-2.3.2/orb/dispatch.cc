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
#include <errno.h>
#include <iostream.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>
#include <mico/os-net.h>


/**************************** misc dtors *******************************/


CORBA::Dispatcher::~Dispatcher ()
{
}

CORBA::DispatcherCallback::~DispatcherCallback ()
{
}


/****************************** Timeout *********************************/


CORBA::Timeout::Timeout (Dispatcher *d, Long tm)
    : _ready (tm == 0), _disp (d), _have_tmout (FALSE)
{
    if (tm > 0) {
	_have_tmout = TRUE;
	_disp->tm_event (this, tm);
    }
}

CORBA::Timeout::~Timeout ()
{
    if (_have_tmout)
	_disp->remove (this, Dispatcher::Timer);
}

void
CORBA::Timeout::callback (Dispatcher *d, Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Timer:
	_have_tmout = FALSE;
        _ready = TRUE;
	break;

    case CORBA::Dispatcher::Moved:
	_disp = d;
	break;
    }
}


/************************** SelectDispatcher *****************************/

class SignalBlocker {
    OSMisc::SigState _sigs;
    bool _blocked;
public:
    void block ()
    {
	if (!_blocked) {
	    _blocked = true;
	    OSMisc::block_sigs (_sigs);
	}
    }
    void unblock ()
    {
	if (_blocked) {
	    _blocked = false;
	    OSMisc::restore_sigs (_sigs);
	}
    }
    SignalBlocker ()
    {
	_blocked = false;
	block();
    }
    ~SignalBlocker ()
    {
	unblock();
    }
};

MICO::SelectDispatcher::SelectDispatcher ()
    : last_update (0), init (TRUE), locked (0), modified (FALSE)
{
    FD_ZERO (&curr_wset);
    FD_ZERO (&curr_rset);
    FD_ZERO (&curr_xset);
    fd_max = 0;
}

MICO::SelectDispatcher::~SelectDispatcher ()
{
    list<FileEvent>::iterator i;
    for (i = fevents.begin(); i != fevents.end(); ++i)
	(*i).cb->callback (this, Remove);

    list<TimerEvent>::iterator j;
    for (j = tevents.begin(); j != tevents.end(); ++j)
	(*j).cb->callback (this, Remove);
}

CORBA::Long
MICO::SelectDispatcher::gettime () const
{
  OSMisc::TimeVal ct = OSMisc::gettime();
  return ct.tv_sec*1000+ct.tv_usec/1000;
}

void
MICO::SelectDispatcher::sleeptime (OSMisc::TimeVal &tm)
{
    if (tevents.size() == 0) {
	// wdh: changed sleeptime to 1 second
 	tm.tv_sec =  1; //10; 
	tm.tv_usec = 0;
	return;
    }
    update_tevents();
    CORBA::Long t = (tevents.front().delta > 0 ? tevents.front().delta : 0);

    tm.tv_sec = t / 1000L;
    tm.tv_usec = (t % 1000L) * 1000L;
}

void
MICO::SelectDispatcher::update_fevents ()
{
    modified = TRUE;

    FD_ZERO (&curr_rset);
    FD_ZERO (&curr_wset);
    FD_ZERO (&curr_xset);
    fd_max = 0;

    list<FileEvent>::iterator i;
    for (i = fevents.begin(); i != fevents.end(); ++i) {
	if (!(*i).deleted) {
	    switch ((*i).event) {
	    case Read:
		FD_SET ((*i).fd, &curr_rset);
		break;
	    case Write:
		FD_SET ((*i).fd, &curr_wset);
		break;
	    case Except:
		FD_SET ((*i).fd, &curr_xset);
		break;
	    default:
		assert (0);
	    }
            if ((*i).fd > fd_max)
                fd_max = (*i).fd;
	}
    }
}

void
MICO::SelectDispatcher::update_tevents ()
{
    CORBA::Long curr = gettime();
    if (init || tevents.size() == 0 || curr - last_update < 0) {
	last_update = curr;
	init = FALSE;
    } else {
	tevents.front().delta -= (curr - last_update);
	last_update = curr;
    }
}

void
MICO::SelectDispatcher::handle_tevents ()
{
    SignalBlocker __sb;

    if (tevents.size() == 0)
	return;

    update_tevents ();
    while (tevents.size() > 0 && tevents.front().delta <= 0) {
	TimerEvent t = tevents.front();
	tevents.pop_front();
	if (tevents.size() > 0)
	    tevents.front().delta += t.delta;

	__sb.unblock();
	t.cb->callback (this, t.event);
	__sb.block();

	update_tevents ();
    }
}

void
MICO::SelectDispatcher::handle_fevents (FDSet &rset, FDSet &wset, FDSet &xset)
{
    // already signal safe because of lock()/unlock()

    lock ();
    list<FileEvent>::iterator i;

    for (i = fevents.begin(); i != fevents.end(); ++i) {
	if (!(*i).deleted) {
	    switch ((*i).event) {
	    case Read:
		if (FD_ISSET ((*i).fd, &rset))
		    (*i).cb->callback (this, Read);
		break;
	    case Write:
		if (FD_ISSET ((*i).fd, &wset))
		    (*i).cb->callback (this, Write);
		break;
	    case Except:
		if (FD_ISSET ((*i).fd, &xset))
		    (*i).cb->callback (this, Except);
		break;
	    default:
		assert (0);
	    }
	}
    }
    unlock ();
}

void
MICO::SelectDispatcher::lock ()
{
    if (!locked)
	modified = FALSE;
    ++locked;
}

void
MICO::SelectDispatcher::unlock ()
{
    if (--locked > 0)
	return;
    assert (locked == 0);

    if (modified) {
	list<FileEvent>::iterator i, next;
	for (i = fevents.begin(); i != fevents.end(); i = next) {
	    next = i;
	    ++next;
	    if ((*i).deleted)
		fevents.erase (i);
	}
    }
}

CORBA::Boolean
MICO::SelectDispatcher::islocked () const
{
    return locked > 0;
}

void
MICO::SelectDispatcher::rd_event (CORBA::DispatcherCallback *cb,
				  CORBA::Long fd)
{
    SignalBlocker __sb;

    fevents.push_back (FileEvent (Read, fd, cb));
    update_fevents ();
}

void
MICO::SelectDispatcher::wr_event (CORBA::DispatcherCallback *cb,
				  CORBA::Long fd)
{
    SignalBlocker __sb;

    fevents.push_back (FileEvent (Write, fd, cb));
    update_fevents ();
}

void
MICO::SelectDispatcher::ex_event (CORBA::DispatcherCallback *cb,
				  CORBA::Long fd)
{
    SignalBlocker __sb;

    fevents.push_back (FileEvent (Except, fd, cb));
    update_fevents ();
}

void
MICO::SelectDispatcher::tm_event (CORBA::DispatcherCallback *cb,
				  CORBA::ULong tmout)
{
    SignalBlocker __sb;

    assert ((CORBA::Long)tmout >= 0);
    TimerEvent t (Timer, tmout, cb);

    update_tevents ();
    list<TimerEvent>::iterator i;
    for (i = tevents.begin(); i != tevents.end(); ++i) {
	if ((*i).delta <= t.delta) {
	    t.delta -= (*i).delta;
	} else {
	    (*i).delta -= t.delta;
	    break;
	}
    }
    tevents.insert (i, t);
}

void
MICO::SelectDispatcher::remove (CORBA::DispatcherCallback *cb, Event e)
{
    SignalBlocker __sb;

    if (e == All || e == Timer) {
	list<TimerEvent>::iterator i, next;
	for (i = tevents.begin(); i != tevents.end(); i = next) {
	    next = i;
	    ++next;
	    if ((*i).cb == cb) {
		CORBA::Long delta = (*i).delta;
		if (next != tevents.end())
		    (*next).delta += delta;
		tevents.erase (i);
	    }
	}
    }
    if (e == All || e == Read || e == Write || e == Except) {
	list<FileEvent>::iterator i, next;
	for (i = fevents.begin(); i != fevents.end(); i = next) {
	    next = i;
	    ++next;
	    if ((*i).cb == cb && (e == All || (*i).event == e)) {
		if (islocked()) {
		    (*i).deleted = TRUE;
		} else {
		    fevents.erase (i);
		}
	    }
	}
	update_fevents ();
    }
}

void
MICO::SelectDispatcher::run (CORBA::Boolean infinite)
{
    FDSet rset, wset, xset;
    OSMisc::TimeVal tm;

    do {
	{
	    SignalBlocker __sb;

	    rset = curr_rset;
	    wset = curr_wset;
	    xset = curr_xset;
	    sleeptime (tm);
	}

	int r = ::select (fd_max+1,
			  (select_addr_t)&rset,
			  (select_addr_t)&wset,
			  (select_addr_t)&xset,
			  &tm);
	assert (r >= 0 || errno == EINTR || errno == EAGAIN ||
                errno == EWOULDBLOCK);

	if (r > 0)
	    handle_fevents (rset, wset, xset);
	handle_tevents ();
    } while (infinite);
}

void
MICO::SelectDispatcher::move (CORBA::Dispatcher *disp)
{
    SignalBlocker __sb;

    assert (!islocked());

    list<FileEvent>::iterator i;
    for (i = fevents.begin(); i != fevents.end(); ++i) {
	switch ((*i).event) {
	case Read:
            (*i).cb->callback (disp, CORBA::Dispatcher::Moved);
	    disp->rd_event ((*i).cb, (*i).fd);
	    break;
	case Write:
            (*i).cb->callback (disp, CORBA::Dispatcher::Moved);
	    disp->wr_event ((*i).cb, (*i).fd);
	    break;
	case Except:
            (*i).cb->callback (disp, CORBA::Dispatcher::Moved);
	    disp->ex_event ((*i).cb, (*i).fd);
	    break;
	default:
	    break;
	}
    }
    fevents.erase (fevents.begin(), fevents.end());
    update_fevents ();

    update_tevents ();
    CORBA::Long tmout = 0;
    list<TimerEvent>::iterator j;
    for (j = tevents.begin(); j != tevents.end(); ++j) {
	tmout += (*j).delta;
	if (tmout < 0)
	    tmout = 0;
        (*j).cb->callback (disp, CORBA::Dispatcher::Moved);
	disp->tm_event ((*j).cb, tmout);
    }
    tevents.erase (tevents.begin(), tevents.end());
}

CORBA::Boolean
MICO::SelectDispatcher::idle () const
{
  SignalBlocker __sb;
  FDSet rset, wset, xset;
  OSMisc::TimeVal tm;

  /*
   * Any pending file events?
   */

  if (fevents.size() > 0) {
    rset = curr_rset;
    wset = curr_wset;
    xset = curr_xset;
    tm.tv_sec = 0;
    tm.tv_usec = 0;

    int r = ::select (fd_max+1,
		      (select_addr_t)&rset,
		      (select_addr_t)&wset,
		      (select_addr_t)&xset,
		      &tm);
    assert (r >= 0 || errno == EINTR || errno == EAGAIN ||
            errno == EWOULDBLOCK);

    if (r > 0) {
      return FALSE;
    }
  }

  /*
   * No? Then what about pending timer events?
   */

  if (tevents.size()) {
    // Discard const for update_tevents()
    ((SelectDispatcher *) this)->update_tevents ();
    if (tevents.front().delta <= 0) {
      return FALSE;
    }
  }

  /*
   * Then we're idle ...
   */

  return TRUE;
}

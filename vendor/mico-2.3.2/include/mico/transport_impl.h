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

#ifndef __mico_transport_impl_h__
#define __mico_transport_impl_h__

	
	
class SelectDispatcher : public CORBA::Dispatcher {
    typedef fd_set FDSet;

    struct FileEvent {
	Event event;
	CORBA::Long fd;
	CORBA::DispatcherCallback *cb;
	CORBA::Boolean deleted;

	FileEvent () {}
	FileEvent (Event _ev, CORBA::Long _fd, CORBA::DispatcherCallback *_cb)
	    : event(_ev), fd(_fd), cb(_cb), deleted(FALSE)
	{}
    };
    struct TimerEvent {
	Event event;
	CORBA::Long delta;
	CORBA::DispatcherCallback *cb;

	TimerEvent () {}
	TimerEvent (Event _ev, CORBA::Long _delta,
		    CORBA::DispatcherCallback *_cb)
	    : event(_ev), delta(_delta), cb(_cb)
	{}
    };

    list<FileEvent> fevents;
    list<TimerEvent> tevents;

    CORBA::Long last_update;
    CORBA::Boolean init;
    CORBA::Long locked;
    CORBA::Boolean modified;
    FDSet curr_wset, curr_rset, curr_xset;
    CORBA::Long fd_max;

    void lock ();
    void unlock ();
    CORBA::Boolean islocked () const;

    CORBA::Long gettime () const;
    void update_tevents ();
    void handle_tevents ();
    void handle_fevents (FDSet &rset, FDSet &wset, FDSet &xset);
    void update_fevents ();
    void sleeptime (OSMisc::TimeVal &);
public:
    SelectDispatcher ();
    virtual ~SelectDispatcher ();
    virtual void rd_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void wr_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void ex_event (CORBA::DispatcherCallback *, CORBA::Long fd);
    virtual void tm_event (CORBA::DispatcherCallback *, CORBA::ULong tmout);
    virtual void remove (CORBA::DispatcherCallback *, Event);
    virtual void move (CORBA::Dispatcher *);
    virtual void run (CORBA::Boolean infinite = TRUE);
    virtual CORBA::Boolean idle () const;
};


class TCPTransport : public CORBA::Transport,
		     public CORBA::DispatcherCallback {
    CORBA::Dispatcher *rdisp, *wdisp;
    CORBA::TransportCallback *rcb, *wcb;
    CORBA::Long fd;
    CORBA::Boolean ateof;
    string err;
    InetAddress local_addr, peer_addr;
    CORBA::Boolean is_blocking;
    CORBA::Boolean is_buffering;
public:
    TCPTransport (CORBA::Long fd = -1);
    ~TCPTransport ();
    
    void rselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void wselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    CORBA::Boolean connect (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    void buffering (CORBA::Boolean dobuffering = TRUE);
    CORBA::Boolean isbuffering ();
    CORBA::Boolean isreadable ();
    
    CORBA::Long read (void *, CORBA::Long len);
    CORBA::Long write (const void *, CORBA::Long len);
    
    const CORBA::Address *addr ();
    const CORBA::Address *peer ();
    
    CORBA::Boolean eof () const;
    CORBA::Boolean bad () const;
    string errormsg () const;
};


class TCPTransportServer : public CORBA::TransportServer,
			   public CORBA::DispatcherCallback {
    CORBA::Dispatcher *adisp;
    CORBA::TransportServerCallback *acb;
    CORBA::Long fd;
    string err;
    InetAddress local_addr;
    CORBA::Boolean listening;
    void listen ();
    CORBA::Boolean is_blocking;
public:
    TCPTransportServer ();
    ~TCPTransportServer ();
    
    void aselect (CORBA::Dispatcher *,
    		  CORBA::TransportServerCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    
    CORBA::Transport *accept ();
    const CORBA::Address *addr ();
    
    CORBA::Boolean bad () const;
    string errormsg () const;
};


class UDPTransport : public CORBA::Transport,
		     public CORBA::DispatcherCallback {
    CORBA::Dispatcher *rdisp, *wdisp;
    CORBA::TransportCallback *rcb, *wcb;
    CORBA::Long fd;
    string err;
    InetAddress local_addr, peer_addr;
    CORBA::Boolean is_blocking;
    CORBA::Buffer dgram;
    CORBA::Boolean is_established;
    CORBA::Boolean is_connected;
    CORBA::Boolean is_bound;
    struct sockaddr_in *peer_sin, *addr_sin;

    CORBA::Long collect_replies (CORBA::Long tmout);
public:
    UDPTransport (CORBA::Long fd = -1);
    ~UDPTransport ();
    
    void rselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void wselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    CORBA::Boolean connect (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    CORBA::Boolean isreadable ();
    
    CORBA::Long read (void *, CORBA::Long len);
    CORBA::Long write (const void *, CORBA::Long len);
    
    const CORBA::Address *addr ();
    const CORBA::Address *peer ();
    
    CORBA::Boolean eof () const;
    CORBA::Boolean bad () const;
    string errormsg () const;

    CORBA::Boolean bind_server (const CORBA::Address *);
    CORBA::Boolean connect_server (const CORBA::Address *);
    CORBA::Long read_dgram (CORBA::Buffer &buf);
};


class UDPTransportServer : public CORBA::TransportServer,
			   public CORBA::DispatcherCallback {
    CORBA::Dispatcher *adisp;
    CORBA::TransportServerCallback *acb;
    CORBA::Long fd;
    string err;
    InetAddress local_addr;
    CORBA::Boolean is_blocking;
    CORBA::Boolean is_bound;
    struct sockaddr_in *addr_sin;
public:
    UDPTransportServer ();
    ~UDPTransportServer ();
    
    void aselect (CORBA::Dispatcher *,
    		  CORBA::TransportServerCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    
    CORBA::Transport *accept ();
    const CORBA::Address *addr ();
    
    CORBA::Boolean bad () const;
    string errormsg () const;
};


#ifdef HAVE_SYS_UN_H
class UnixTransport : public CORBA::Transport,
		      public CORBA::DispatcherCallback {
    CORBA::Dispatcher *rdisp, *wdisp;
    CORBA::TransportCallback *rcb, *wcb;
    CORBA::Long fd;
    CORBA::Boolean ateof;
    string err;
    UnixAddress local_addr, peer_addr;
    CORBA::Boolean is_blocking;
public:
    UnixTransport (CORBA::Long fd = -1);
    ~UnixTransport ();
    
    void rselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void wselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    CORBA::Boolean connect (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    CORBA::Boolean isreadable ();
    
    CORBA::Long read (void *, CORBA::Long len);
    CORBA::Long write (const void *, CORBA::Long len);
    
    const CORBA::Address *addr ();
    const CORBA::Address *peer ();
    
    CORBA::Boolean eof () const;
    CORBA::Boolean bad () const;
    string errormsg () const;
};


class UnixTransportServer : public CORBA::TransportServer,
			    public CORBA::DispatcherCallback {
    CORBA::Dispatcher *adisp;
    CORBA::TransportServerCallback *acb;
    CORBA::Long fd;
    string err;
    UnixAddress local_addr;
    CORBA::Boolean listening;
    void listen ();
    CORBA::Boolean is_blocking;
public:
    UnixTransportServer ();
    ~UnixTransportServer ();
    
    void aselect (CORBA::Dispatcher *,
    		  CORBA::TransportServerCallback *);
    void callback (CORBA::Dispatcher *, CORBA::Dispatcher::Event);
    
    CORBA::Boolean bind (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    
    CORBA::Transport *accept ();
    const CORBA::Address *addr ();
    
    CORBA::Boolean bad () const;
    string errormsg () const;
};
#endif // HAVE_SYS_UN_H

#endif // __mico_transport_impl_h__

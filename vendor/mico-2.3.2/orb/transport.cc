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
#include <string.h>
#include <errno.h>
#include <iostream.h>

#include <mico/os-net.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>


/**************************** misc dtors *******************************/


CORBA::TransportCallback::~TransportCallback ()
{
}

CORBA::TransportServer::~TransportServer ()
{
}

CORBA::TransportServerCallback::~TransportServerCallback ()
{
}


/*************************** Transport *******************************/


CORBA::Transport::~Transport ()
{
}

CORBA::Long
CORBA::Transport::read (Buffer &b, Long len)
{
    b.resize (len);
    Long r = read (b.buffer()+b.wpos(), len);
    if (r > 0)
	b.wseek_rel (r);
    return r;
}

CORBA::Long
CORBA::Transport::write (Buffer &b, Long len, Boolean eat)
{
    assert (len <= b.length());
    Long r = write (b.buffer()+b.rpos(), len);
    if (r > 0 && eat)
	b.rseek_rel (r);
    return r;
}

void
CORBA::Transport::buffering (CORBA::Boolean)
{
}

CORBA::Boolean
CORBA::Transport::isbuffering ()
{
    return FALSE;
}

CORBA::Principal_ptr
CORBA::Transport::get_principal ()
{
    return new CORBA::Principal (this);
}


/************************** TCPTransport *****************************/


MICO::TCPTransport::TCPTransport (CORBA::Long thefd)
{
    fd = thefd;
    if (fd < 0) {
	fd = ::socket (PF_INET, SOCK_STREAM, 0);
	assert (fd >= 0);
    }
    OSNet::sock_block (fd, TRUE);
    OSNet::sock_ndelay (fd, TRUE);

    is_blocking = TRUE;
    is_buffering = FALSE;
    rdisp = wdisp = 0;
    rcb = wcb = 0;
    ateof = FALSE;
}

MICO::TCPTransport::~TCPTransport ()
{
    if (rdisp && rcb) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb->callback (this, CORBA::TransportCallback::Remove);
    }
    if (wdisp && wcb) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb->callback (this, CORBA::TransportCallback::Remove);
    }
    OSNet::sock_close (fd);
}

void
MICO::TCPTransport::rselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    if (rcb && rdisp) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb = 0;
    }
    if (cb) {
	disp->rd_event (this, fd);
	rdisp = disp;
	rcb = cb;
    }
}

void
MICO::TCPTransport::wselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    if (wcb && wdisp) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb = 0;
    }
    if (cb) {
	disp->wr_event (this, fd);
	wdisp = disp;
	wcb = cb;
    }
}

void
MICO::TCPTransport::callback (CORBA::Dispatcher *disp,
			      CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (rcb);
	rcb->callback (this, CORBA::TransportCallback::Read);
	break;
    case CORBA::Dispatcher::Write:
	assert (wcb);
	wcb->callback (this, CORBA::TransportCallback::Write);
	break;
    case CORBA::Dispatcher::Remove:
	wdisp = rdisp = 0;
	wcb = rcb = 0;
	break;
    case CORBA::Dispatcher::Moved:
        wdisp = rdisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::TCPTransport::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet"));
    InetAddress *ia = (InetAddress *)a;

    struct sockaddr_in sin = ia->sockaddr();
    CORBA::Long r = ::bind (fd, (socket_addr_t)&sin, sizeof (sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::TCPTransport::connect (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet"));
    InetAddress *ia = (InetAddress *)a;

    struct sockaddr_in sin = ia->sockaddr();
    CORBA::Long r = ::connect (fd, (socket_addr_t)&sin, sizeof (sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::TCPTransport::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_INET, SOCK_STREAM, 0);
    assert (fd >= 0);

    OSNet::sock_ndelay (fd, TRUE);

    if (rdisp && rcb)
	rdisp->remove (this, CORBA::Dispatcher::Read);
    if (wdisp && wcb)
	wdisp->remove (this, CORBA::Dispatcher::Write);

    is_buffering = FALSE;
    is_blocking = TRUE;
    rdisp = wdisp = 0;
    rcb = wcb = 0;
    ateof = FALSE;
}

void
MICO::TCPTransport::block (CORBA::Boolean doblock)
{
    if (!!is_blocking != !!doblock) {
	is_blocking = doblock;
	OSNet::sock_block (fd, doblock);
    }
}

CORBA::Boolean
MICO::TCPTransport::isblocking ()
{
    return is_blocking;
}

void
MICO::TCPTransport::buffering (CORBA::Boolean dobuffering)
{
    if (!!is_buffering != !!dobuffering) {
	is_buffering = dobuffering;
	OSNet::sock_ndelay (fd, !dobuffering);
    }
}

CORBA::Boolean
MICO::TCPTransport::isbuffering ()
{
    return is_buffering;
}

CORBA::Boolean
MICO::TCPTransport::isreadable ()
{
    fd_set rset;
    struct timeval tm;

    FD_ZERO (&rset);
    FD_SET (fd, &rset);

    tm.tv_sec = 0;
    tm.tv_usec = 0;

    int r = ::select (fd+1, (select_addr_t)&rset, 0, 0, &tm);
    return r > 0;
}

CORBA::Long
MICO::TCPTransport::read (void *_b, CORBA::Long len)
{
    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (todo > 0) {
	CORBA::Long r = OSNet::sock_read (fd, b, todo);
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
                todo != len)
		break;
	    err = xstrerror (errno);
	    return r;
	} else if (r == 0) {
	    ateof = TRUE;
	    break;
	}
	b += r;
	todo -= r;
    }
    return len - todo;
}

CORBA::Long
MICO::TCPTransport::write (const void *_b, CORBA::Long len)
{
    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (todo > 0) {
	CORBA::Long r = OSNet::sock_write (fd, b, todo);
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
                todo != len)
		break;
	    err = xstrerror (errno);
	    return r;
	} else if (r == 0) {
	    break;
	}
	b += r;
	todo -= r;
    }
    return len - todo;
}

const CORBA::Address *
MICO::TCPTransport::addr ()
{
    struct sockaddr_in sin;
    socket_size_t sz = sizeof (sin);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&sin, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return 0;
    }
    local_addr.sockaddr (sin);
    return &local_addr;
}

const CORBA::Address *
MICO::TCPTransport::peer ()
{
    struct sockaddr_in sin;
    socket_size_t sz = sizeof (sin);
    CORBA::Long r = ::getpeername (fd, (socket_addr_t)&sin, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
        // XXX allow for peer() after disconnect ...
	//return 0;
    } else {
        peer_addr.sockaddr (sin);
    }
    return &peer_addr;
}

CORBA::Boolean
MICO::TCPTransport::bad () const
{
    return err.length() > 0;
}

CORBA::Boolean
MICO::TCPTransport::eof () const
{
    return ateof;
}

string
MICO::TCPTransport::errormsg () const
{
    return err;
}


/************************ TCPTransportServer **************************/


MICO::TCPTransportServer::TCPTransportServer ()
{
    OSNet::sock_init();

    fd = ::socket (PF_INET, SOCK_STREAM, 0);
    assert (fd >= 0);

    is_blocking = TRUE;

    OSNet::sock_reuse (fd, TRUE);

    listening = FALSE;
    adisp = 0;
    acb = 0;
}

MICO::TCPTransportServer::~TCPTransportServer ()
{
    if (adisp && acb) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb->callback (this, CORBA::TransportServerCallback::Remove);
    }
    OSNet::sock_close (fd);
}

void
MICO::TCPTransportServer::listen ()
{
    if (!listening) {
	int r = ::listen (fd, 10);
	assert (r == 0);
	listening = TRUE;
    }
}

void
MICO::TCPTransportServer::aselect (CORBA::Dispatcher *disp,
				   CORBA::TransportServerCallback *cb)
{
    if (acb && adisp) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb = 0;
    }
    if (cb) {
	listen ();
	disp->rd_event (this, fd);
	adisp = disp;
	acb = cb;
    }
}

void
MICO::TCPTransportServer::callback (CORBA::Dispatcher *disp,
				    CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (acb);
	acb->callback (this, CORBA::TransportServerCallback::Accept);
	break;
    case CORBA::Dispatcher::Remove:
	acb = 0;
	adisp = 0;
	break;
    case CORBA::Dispatcher::Moved:
        adisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::TCPTransportServer::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet"));
    InetAddress *ia = (InetAddress *)a;

    struct sockaddr_in sin = ia->sockaddr();
    CORBA::Long r = ::bind (fd, (socket_addr_t)&sin, sizeof (sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::TCPTransportServer::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_INET, SOCK_STREAM, 0);
    assert (fd >= 0);

    is_blocking = TRUE;

    OSNet::sock_reuse (fd, TRUE);

    if (adisp && acb)
	adisp->remove (this, CORBA::Dispatcher::Read);

    listening = FALSE;
    adisp = 0;
    acb = 0;
}

void
MICO::TCPTransportServer::block (CORBA::Boolean doblock)
{
    if (!!is_blocking != !!doblock) {
	is_blocking = doblock;
	OSNet::sock_block (fd, doblock);
    }
}

CORBA::Boolean
MICO::TCPTransportServer::isblocking ()
{
    return is_blocking;
}

CORBA::Transport *
MICO::TCPTransportServer::accept ()
{
    listen ();
    CORBA::Long newfd = ::accept (fd, 0, 0);
    if (newfd < 0) {
        OSNet::set_errno();
	if (errno != EWOULDBLOCK && errno != EAGAIN)
	    err = xstrerror (errno);
	return 0;
    }
    return new TCPTransport (newfd);
}

const CORBA::Address *
MICO::TCPTransportServer::addr ()
{
    struct sockaddr_in sin;
    socket_size_t sz = sizeof (sin);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&sin, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return 0;
    }
    local_addr.sockaddr (sin);
    return &local_addr;
}

CORBA::Boolean
MICO::TCPTransportServer::bad () const
{
    return err.length() > 0;
}

string
MICO::TCPTransportServer::errormsg () const
{
    return err;
}


/************************** UDPTransport *****************************/


#define UDP_MAGIC_CREQ ((char *)"CREQ-EjAQBgNVBAcTCUZyYW5rZnVyd")
#define UDP_MAGIC_CREP ((char *)"CREP-EjAQBgNVBAcTCUZyYW5rZnVyd")
#define UDP_MAGIC_SIZE 30

MICO::UDPTransport::UDPTransport (CORBA::Long thefd)
{
    fd = thefd;
    if (fd < 0) {
	fd = ::socket (PF_INET, SOCK_DGRAM, 0);
	assert (fd >= 0);
    }
    OSNet::sock_block (fd, TRUE);
    OSNet::sock_broadcast (fd, TRUE);

    is_blocking = TRUE;
    rdisp = wdisp = 0;
    rcb = wcb = 0;
    is_established = FALSE;
    is_connected = FALSE;
    is_bound = FALSE;
    peer_sin = new sockaddr_in;
    addr_sin = new sockaddr_in;
}

MICO::UDPTransport::~UDPTransport ()
{
    if (rdisp && rcb) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb->callback (this, CORBA::TransportCallback::Remove);
    }
    if (wdisp && wcb) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb->callback (this, CORBA::TransportCallback::Remove);
    }
    OSNet::sock_close (fd);
    delete peer_sin;
    delete addr_sin;
}

void
MICO::UDPTransport::rselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    if (rcb && rdisp) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb = 0;
    }
    if (cb) {
	disp->rd_event (this, fd);
	rdisp = disp;
	rcb = cb;
    }
}

void
MICO::UDPTransport::wselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    if (wcb && wdisp) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb = 0;
    }
    if (cb) {
	disp->wr_event (this, fd);
	wdisp = disp;
	wcb = cb;
    }
}

void
MICO::UDPTransport::callback (CORBA::Dispatcher *disp,
			      CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (rcb);
	rcb->callback (this, CORBA::TransportCallback::Read);
	break;
    case CORBA::Dispatcher::Write:
	assert (wcb);
	wcb->callback (this, CORBA::TransportCallback::Write);
	break;
    case CORBA::Dispatcher::Remove:
	wdisp = rdisp = 0;
	wcb = rcb = 0;
	break;
    case CORBA::Dispatcher::Moved:
        wdisp = rdisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::UDPTransport::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet-dgram"));
    InetAddress *ia = (InetAddress *)a;

    // remember the bind address, since some systems will
    // return a different address from getsockname() when
    // we bind to a broadcast address
    *addr_sin = ia->sockaddr();
    is_bound = TRUE;

    CORBA::Long r = ::bind (fd, (socket_addr_t)addr_sin, sizeof (*addr_sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::UDPTransport::bind_server (const CORBA::Address *a)
{
    // server sockets can reuse port numbers
    OSNet::sock_reuse (fd, TRUE);
    return bind (a);
}

CORBA::Long
MICO::UDPTransport::collect_replies (CORBA::Long tmout)
{
    CORBA::Buffer b;
    CORBA::Long replies = 0;
    while (42) {
	fd_set rset;
	struct timeval tm;

	FD_ZERO (&rset);
	FD_SET (fd, &rset);

	tm.tv_sec  = tmout / 1000L;
	tm.tv_usec = (tmout % 1000L) * 1000L;

	int r = ::select (fd+1, (select_addr_t)&rset, 0, 0, &tm);
	if (r == 0) {
	    // timeout
	    break;
	}
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR || errno == EAGAIN)
		continue;
	    assert (0);
	}
	r = read_dgram (b);
	if (r == 0)
	    continue;
	if (r != UDP_MAGIC_SIZE)
	    assert (0);
	if (strncmp ((char *)b.buffer(), UDP_MAGIC_CREP, UDP_MAGIC_SIZE))
	    assert (0);
	++replies;
    }
    return replies;
}

CORBA::Boolean
MICO::UDPTransport::connect (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet-dgram"));
    InetAddress *ia = (InetAddress *)a;

    // do not really connect here, otherwise we dont get replies
    // if peer_addr is a broadcast or multicast address
    *peer_sin = ia->sockaddr();
    is_connected = TRUE;

    CORBA::Long retries = 5;
    while (--retries >= 0) {
	if (write (UDP_MAGIC_CREQ, UDP_MAGIC_SIZE) != UDP_MAGIC_SIZE)
	    assert (0);
	if (collect_replies (300 /*ms*/) > 0)
	    break;
    }
    if (retries < 0) {
	err = "timeout";
	is_connected = FALSE;
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::UDPTransport::connect_server (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet-dgram"));
    InetAddress *ia = (InetAddress *)a;

    struct sockaddr_in sin = ia->sockaddr();
    CORBA::Long r = ::connect (fd, (socket_addr_t)&sin, sizeof (sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::UDPTransport::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_INET, SOCK_DGRAM, 0);
    assert (fd >= 0);

    OSNet::sock_broadcast (fd, TRUE);

    if (rdisp && rcb)
	rdisp->remove (this, CORBA::Dispatcher::Read);
    if (wdisp && wcb)
	wdisp->remove (this, CORBA::Dispatcher::Write);

    is_blocking = TRUE;
    rdisp = wdisp = 0;
    rcb = wcb = 0;
    is_established = FALSE;
    is_connected = FALSE;
    is_bound = FALSE;
}

void
MICO::UDPTransport::block (CORBA::Boolean doblock)
{
    if (!!is_blocking != !!doblock) {
	is_blocking = doblock;
	OSNet::sock_block (fd, doblock);
    }
}

CORBA::Boolean
MICO::UDPTransport::isblocking ()
{
    return is_blocking;
}

CORBA::Boolean
MICO::UDPTransport::isreadable ()
{
    fd_set rset;
    struct timeval tm;

    FD_ZERO (&rset);
    FD_SET (fd, &rset);

    tm.tv_sec = 0;
    tm.tv_usec = 0;

    int r = ::select (fd+1, (select_addr_t)&rset, 0, 0, &tm);
    return r > 0;
}

CORBA::Long
MICO::UDPTransport::read_dgram (CORBA::Buffer &buf)
{
    // XXX somehow get real dgram size ...
    CORBA::ULong dgram_size = 10000;
    buf.reset (dgram_size);
	
    while (42) {
	CORBA::Long r = OSNet::sock_read (fd, buf.buffer(), dgram_size);
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
	    // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN)
		return 0;
	    err = xstrerror (errno);
	    return r;
	}
	buf.wseek_rel (r);
	return r;
    }
    // notreached
    return 0;
}

CORBA::Long
MICO::UDPTransport::read (void *b, CORBA::Long len)
{
    if (dgram.length() == 0) {
	while (42) {
	    CORBA::Long r = read_dgram (dgram);
	    if (r <= 0)
		return r;
	    if (is_established || r != UDP_MAGIC_SIZE)
		break;
	    if (!strncmp((char*)dgram.buffer(),UDP_MAGIC_CREP,UDP_MAGIC_SIZE))
		// ignore late connect replies
		continue;
	    if (!strncmp((char*)dgram.buffer(),UDP_MAGIC_CREQ,UDP_MAGIC_SIZE)){
		// peer resent connect request, but reply was lost
		if (write (UDP_MAGIC_CREP, UDP_MAGIC_SIZE) != UDP_MAGIC_SIZE)
		    assert (0);
		continue;
	    }
	    break;
	}
	is_established = TRUE;
    }
    if (len > dgram.length())
	len = dgram.length();
    if (!dgram.get (b, len))
	assert (0);

    return len;
}

CORBA::Long
MICO::UDPTransport::write (const void *_b, CORBA::Long len)
{
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (42) {
	CORBA::Long r;
	if (is_connected) {
	    r = OSNet::sock_write_to (fd, b, len,
				      (struct sockaddr *)peer_sin,
				      sizeof (*peer_sin));
	} else {
	    r = OSNet::sock_write (fd, b, len);
	}
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN)
		return 0;
	    err = xstrerror (errno);
	}
	return r;
    }
    // notreached
    return 0;
}

const CORBA::Address *
MICO::UDPTransport::addr ()
{
    struct sockaddr_in sin;
    socket_size_t sz = sizeof (sin);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&sin, &sz);
    if (r < 0) {
        OSNet::set_errno();
        err = xstrerror (errno);
        return 0;
    }
    local_addr.family (MICO::InetAddress::DGRAM);
    if (is_bound) {
        local_addr.sockaddr (*addr_sin);
        local_addr.port (ntohs (sin.sin_port));
    } else {
        local_addr.sockaddr (sin);
    }
    return &local_addr;
}

const CORBA::Address *
MICO::UDPTransport::peer ()
{
    if (is_connected) {
	peer_addr.family (MICO::InetAddress::DGRAM);
        peer_addr.sockaddr (*peer_sin);
    } else {
	struct sockaddr_in sin;
	socket_size_t sz = sizeof (sin);
	CORBA::Long r = ::getpeername (fd, (socket_addr_t)&sin, &sz);
	if (r < 0) {
            OSNet::set_errno();
	    err = xstrerror (errno);
	    return 0;
	} else {
	    peer_addr.family (MICO::InetAddress::DGRAM);
	    peer_addr.sockaddr (sin);
	}
    }
    return &peer_addr;
}

CORBA::Boolean
MICO::UDPTransport::bad () const
{
    return err.length() > 0;
}

CORBA::Boolean
MICO::UDPTransport::eof () const
{
    return FALSE;
}

string
MICO::UDPTransport::errormsg () const
{
    return err;
}


/************************ UDPTransportServer **************************/


MICO::UDPTransportServer::UDPTransportServer ()
{
    OSNet::sock_init();

    fd = ::socket (PF_INET, SOCK_DGRAM, 0);
    assert (fd >= 0);

    OSNet::sock_reuse (fd, TRUE);

    is_blocking = TRUE;
    is_bound = FALSE;

    adisp = 0;
    acb = 0;
    addr_sin = new sockaddr_in;
}

MICO::UDPTransportServer::~UDPTransportServer ()
{
    if (adisp && acb) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb->callback (this, CORBA::TransportServerCallback::Remove);
    }
    OSNet::sock_close (fd);
    delete addr_sin;
}

void
MICO::UDPTransportServer::aselect (CORBA::Dispatcher *disp,
				   CORBA::TransportServerCallback *cb)
{
    if (acb && adisp) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb = 0;
    }
    if (cb) {
	disp->rd_event (this, fd);
	adisp = disp;
	acb = cb;
    }
}

void
MICO::UDPTransportServer::callback (CORBA::Dispatcher *disp,
				    CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (acb);
	acb->callback (this, CORBA::TransportServerCallback::Accept);
	break;
    case CORBA::Dispatcher::Remove:
	acb = 0;
	adisp = 0;
	break;
    case CORBA::Dispatcher::Moved:
        adisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::UDPTransportServer::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "inet-dgram"));
    InetAddress *ia = (InetAddress *)a;

    // remember the bind address, since some systems will
    // return a different address from getsockname() when
    // we bind to a broadcast address
    *addr_sin = ia->sockaddr();
    is_bound = TRUE;

    CORBA::Long r = ::bind (fd, (socket_addr_t)addr_sin, sizeof (*addr_sin));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::UDPTransportServer::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_INET, SOCK_DGRAM, 0);
    assert (fd >= 0);

    OSNet::sock_reuse (fd, TRUE);

    is_blocking = TRUE;
    is_bound = FALSE;

    if (adisp && acb)
	adisp->remove (this, CORBA::Dispatcher::Read);

    adisp = 0;
    acb = 0;
}

void
MICO::UDPTransportServer::block (CORBA::Boolean doblock)
{
    if (!!is_blocking != !!doblock) {
	is_blocking = doblock;
	OSNet::sock_block (fd, doblock);
    }
}

CORBA::Boolean
MICO::UDPTransportServer::isblocking ()
{
    return is_blocking;
}

CORBA::Transport *
MICO::UDPTransportServer::accept ()
{
    struct sockaddr_in sin;
    CORBA::Octet b[UDP_MAGIC_SIZE+1];
    CORBA::Long r = OSNet::sock_read_from (fd, b, UDP_MAGIC_SIZE+1,
					   (struct sockaddr *)&sin,
					   sizeof (sin));
    if (r < 0) {
        OSNet::set_errno();
	if (errno == EINTR)
	    return 0;
	// Cygnus CDK sometimes returns errno 0 when read would block
	if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN)
	    return 0;
	err = xstrerror (errno);
	return 0;
    } else if (r == 0) {
	return 0;
    }

    // we will also receive data broadcasts/multicasts, ignore them
    // if they are not connect requests ...
    if (r != UDP_MAGIC_SIZE)
	return 0;
    if (strncmp ((char *)b, UDP_MAGIC_CREQ, UDP_MAGIC_SIZE))
	return 0;

    UDPTransport *t = new UDPTransport;
    if (!t->bind_server (addr()))
	assert (0);

    InetAddress raddr (sin, InetAddress::DGRAM);
    if (!t->connect_server (&raddr))
	assert (0);

    if (t->write (UDP_MAGIC_CREP, UDP_MAGIC_SIZE) != UDP_MAGIC_SIZE)
	assert (0);

    return t;
}

const CORBA::Address *
MICO::UDPTransportServer::addr ()
{
    struct sockaddr_in sin;
    socket_size_t sz = sizeof (sin);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&sin, &sz);
    if (r < 0) {
        OSNet::set_errno();
        err = xstrerror (errno);
        return 0;
    }
    local_addr.family (MICO::InetAddress::DGRAM);
    if (is_bound) {
        local_addr.sockaddr (*addr_sin);
        local_addr.port (ntohs (sin.sin_port));
    } else {
        local_addr.sockaddr (sin);
    }
    return &local_addr;
}

CORBA::Boolean
MICO::UDPTransportServer::bad () const
{
    return err.length() > 0;
}

string
MICO::UDPTransportServer::errormsg () const
{
    return err;
}


/************************** UnixTransport ****************************/


#ifdef HAVE_SYS_UN_H
MICO::UnixTransport::UnixTransport (CORBA::Long thefd)
{
    fd = thefd;
    if (fd < 0) {
	fd = ::socket (PF_UNIX, SOCK_STREAM, 0);
	assert (fd >= 0);
    }
    OSNet::sock_block (fd, TRUE);

    is_blocking = TRUE;
    rdisp = wdisp = 0;
    rcb = wcb = 0;
    ateof = FALSE;
}

MICO::UnixTransport::~UnixTransport ()
{
    if (rdisp && rcb) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb->callback (this, CORBA::TransportCallback::Remove);
    }
    if (wdisp && wcb) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb->callback (this, CORBA::TransportCallback::Remove);
    }
    OSNet::sock_close (fd);
}

void
MICO::UnixTransport::rselect (CORBA::Dispatcher *disp,
			      CORBA::TransportCallback *cb)
{
    if (rcb && rdisp) {
	rdisp->remove (this, CORBA::Dispatcher::Read);
	rdisp = 0;
	rcb = 0;
    }
    if (cb) {
	disp->rd_event (this, fd);
	rdisp = disp;
	rcb = cb;
    }
}

void
MICO::UnixTransport::wselect (CORBA::Dispatcher *disp,
			      CORBA::TransportCallback *cb)
{
    if (wcb && wdisp) {
	wdisp->remove (this, CORBA::Dispatcher::Write);
	wdisp = 0;
	wcb = 0;
    }
    if (cb) {
	disp->wr_event (this, fd);
	wdisp = disp;
	wcb = cb;
    }
}

void
MICO::UnixTransport::callback (CORBA::Dispatcher *disp,
			       CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (rcb);
	rcb->callback (this, CORBA::TransportCallback::Read);
	break;
    case CORBA::Dispatcher::Write:
	assert (wcb);
	wcb->callback (this, CORBA::TransportCallback::Write);
	break;
    case CORBA::Dispatcher::Remove:
	wdisp = rdisp = 0;
	wcb = rcb = 0;
	break;
    case CORBA::Dispatcher::Moved:
        wdisp = rdisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::UnixTransport::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "unix"));
    UnixAddress *ua = (UnixAddress *)a;

    // XXX should do that after the socket is destroyed ...
    ::unlink (ua->filename());

    struct sockaddr_un una = ua->sockaddr();
    CORBA::Long r = ::bind (fd, (socket_addr_t)&una, sizeof (una));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICO::UnixTransport::connect (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "unix"));
    UnixAddress *ua = (UnixAddress *)a;

    struct sockaddr_un una = ua->sockaddr();
    CORBA::Long r = ::connect (fd, (socket_addr_t)&una, sizeof (una));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::UnixTransport::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_UNIX, SOCK_STREAM, 0);
    is_blocking = TRUE;
    assert (fd >= 0);

    if (rdisp && rcb)
	rdisp->remove (this, CORBA::Dispatcher::Read);
    if (wdisp && wcb)
	wdisp->remove (this, CORBA::Dispatcher::Write);

    rdisp = wdisp = 0;
    rcb = wcb = 0;
    ateof = FALSE;
}

void
MICO::UnixTransport::block (CORBA::Boolean doblock)
{
    is_blocking = doblock;
    OSNet::sock_block (fd, doblock);
}

CORBA::Boolean
MICO::UnixTransport::isblocking ()
{
    return is_blocking;
}

CORBA::Boolean
MICO::UnixTransport::isreadable ()
{
    fd_set rset;
    struct timeval tm;

    FD_ZERO (&rset);
    FD_SET (fd, &rset);

    tm.tv_sec = 0;
    tm.tv_usec = 0;

    int r = ::select (fd+1, (select_addr_t)&rset, 0, 0, &tm);
    return r > 0;
}

CORBA::Long
MICO::UnixTransport::read (void *_b, CORBA::Long len)
{
    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (todo > 0) {
	CORBA::Long r = OSNet::sock_read (fd, b, todo);
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
                todo != len)
		break;
	    err = xstrerror (errno);
	    return r;
	} else if (r == 0) {
	    ateof = TRUE;
	    break;
	}
	b += r;
	todo -= r;
    }
    return len - todo;
}

CORBA::Long
MICO::UnixTransport::write (const void *_b, CORBA::Long len)
{
    CORBA::Long todo = len;
    CORBA::Octet *b = (CORBA::Octet *)_b;

    while (todo > 0) {
	CORBA::Long r = OSNet::sock_write (fd, b, todo);
	if (r < 0) {
            OSNet::set_errno();
	    if (errno == EINTR)
		continue;
            // Cygnus CDK sometimes returns errno 0 when read would block
	    if (errno == 0 || errno == EWOULDBLOCK || errno == EAGAIN ||
                todo != len)
		break;
	    err = xstrerror (errno);
	    return r;
	} else if (r == 0) {
	    break;
	}
	b += r;
	todo -= r;
    }
    return len - todo;
}

const CORBA::Address *
MICO::UnixTransport::addr ()
{
    struct sockaddr_un una;
    socket_size_t sz = sizeof (una);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&una, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return 0;
    }
    local_addr.sockaddr (una);
    return &local_addr;
}

const CORBA::Address *
MICO::UnixTransport::peer ()
{
    struct sockaddr_un una;
    socket_size_t sz = sizeof (una);
    CORBA::Long r = ::getpeername (fd, (socket_addr_t)&una, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
        // allow for peer() after disconnect ...
	//return 0;
    } else {
        peer_addr.sockaddr (una);
    }
    return &peer_addr;
}

CORBA::Boolean
MICO::UnixTransport::bad () const
{
    return err.length() > 0;
}

CORBA::Boolean
MICO::UnixTransport::eof () const
{
    return ateof;
}

string
MICO::UnixTransport::errormsg () const
{
    return err;
}


/************************ UnixTransportServer **************************/


MICO::UnixTransportServer::UnixTransportServer ()
{
    fd = ::socket (PF_UNIX, SOCK_STREAM, 0);
    is_blocking = TRUE;
    assert (fd >= 0);
    listening = FALSE;
    adisp = 0;
    acb = 0;
}

MICO::UnixTransportServer::~UnixTransportServer ()
{
    if (adisp && acb) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb->callback (this, CORBA::TransportServerCallback::Remove);
    }
    OSNet::sock_close (fd);
}

void
MICO::UnixTransportServer::listen ()
{
    if (!listening) {
	int r = ::listen (fd, 10);
	assert (r == 0);
	listening = TRUE;
    }
}

void
MICO::UnixTransportServer::aselect (CORBA::Dispatcher *disp,
				    CORBA::TransportServerCallback *cb)
{
    if (acb && adisp) {
	adisp->remove (this, CORBA::Dispatcher::Read);
	adisp = 0;
	acb = 0;
    }
    if (cb) {
	listen ();
	disp->rd_event (this, fd);
	adisp = disp;
	acb = cb;
    }
}

void
MICO::UnixTransportServer::callback (CORBA::Dispatcher *disp,
				     CORBA::Dispatcher::Event ev)
{
    switch (ev) {
    case CORBA::Dispatcher::Read:
	assert (acb);
	acb->callback (this, CORBA::TransportServerCallback::Accept);
	break;
    case CORBA::Dispatcher::Remove:
	acb = 0;
	adisp = 0;
	break;
    case CORBA::Dispatcher::Moved:
        adisp = disp;
        break;
    default:
	assert (0);
    }
}

CORBA::Boolean
MICO::UnixTransportServer::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "unix"));
    UnixAddress *ua = (UnixAddress *)a;

    // XXX should do that after the socket is destroyed ...
    ::unlink (ua->filename());

    struct sockaddr_un una = ua->sockaddr();
    CORBA::Long r = ::bind (fd, (socket_addr_t)&una, sizeof (una));
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return FALSE;
    }
    return TRUE;
}

void
MICO::UnixTransportServer::close ()
{
    OSNet::sock_close (fd);
    fd = ::socket (PF_UNIX, SOCK_STREAM, 0);
    is_blocking = TRUE;
    assert (fd >= 0);

    if (adisp && acb)
	adisp->remove (this, CORBA::Dispatcher::Read);

    listening = FALSE;
    adisp = 0;
    acb = 0;
}

void
MICO::UnixTransportServer::block (CORBA::Boolean doblock)
{
    is_blocking = doblock;
    OSNet::sock_block (fd, doblock);
}

CORBA::Boolean
MICO::UnixTransportServer::isblocking ()
{
    return is_blocking;
}

CORBA::Transport *
MICO::UnixTransportServer::accept ()
{
    listen ();
    CORBA::Long newfd = ::accept (fd, 0, 0);
    if (newfd < 0) {
        OSNet::set_errno();
	if (errno != EWOULDBLOCK && errno != EAGAIN)
	    err = xstrerror (errno);
	return 0;
    }
    return new UnixTransport (newfd);
}

const CORBA::Address *
MICO::UnixTransportServer::addr ()
{
    struct sockaddr_un una;
    socket_size_t sz = sizeof (una);
    CORBA::Long r = ::getsockname (fd, (socket_addr_t)&una, &sz);
    if (r < 0) {
        OSNet::set_errno();
	err = xstrerror (errno);
	return 0;
    }
    local_addr.sockaddr (una);
    return &local_addr;
}

CORBA::Boolean
MICO::UnixTransportServer::bad () const
{
    return err.length() > 0;
}

string
MICO::UnixTransportServer::errormsg () const
{
    return err;
}

#endif // HAVE_SYS_UN_H

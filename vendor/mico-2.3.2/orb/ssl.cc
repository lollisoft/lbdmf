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

#include <stdlib.h>
#include <string.h>
#include <CORBA-SMALL.h>
#include <mico/util.h>
#include <mico/impl.h>
#include <mico/intercept.h>
#include <mico/ssl.h>
#include <mico/template_impl.h>

#ifdef HAVE_SSL


// -ORBSSL* options
static MICOGetOpt::OptVec SSL_options;


/***************************** BIO methods ****************************/

extern "C" {
    typedef long (*ssl_long_t) ();
    typedef int (*ssl_int_t) ();
}

static int
mico_bio_new (BIO *b)
{
    b->init = 0;
    b->num = 0;
    b->ptr = 0;
    b->flags = 0;
    return 1;
}

static int
mico_bio_free (BIO *b)
{
    if (!b)
	return 0;
    if (b->shutdown) {
	if (b->init) {
	    CORBA::Transport *t = (CORBA::Transport *)b->ptr;
	    assert (t);
	    t->close ();
	}
	b->init = 0;
	b->flags = 0;
    }
    return 1;
}

static int
mico_bio_read (BIO *b, char *out, int len)
{
    int ret = 0;
    if (out) {
	CORBA::Transport *t = (CORBA::Transport *)b->ptr;
	assert (t);

	ret = t->read (out, len);
	BIO_clear_retry_flags (b);
	if (ret <= 0) {
	    if (ret != len && !t->eof())
		BIO_set_retry_read (b);
	}
    }
    return ret;
}

static int
mico_bio_write (BIO *b, char *in, int len)
{
    int ret;

    CORBA::Transport *t = (CORBA::Transport *)b->ptr;
    assert (t);

    ret = t->write (in, len);
    BIO_clear_retry_flags (b);
    if (ret <= 0) {
	if (ret != len && !t->eof())
	    BIO_set_retry_write (b);
    }
    return ret;
}

static int
mico_bio_puts (BIO *b, char *out)
{
    return mico_bio_write (b, out, strlen (out));
}

static long
mico_bio_ctrl (BIO *b, int cmd, long num, char *ptr)
{
    long ret = 1;

    switch (cmd) {
    case BIO_CTRL_RESET:
	ret = 0;
	break;

    case BIO_CTRL_INFO:
	ret = 0;
	break;

    case BIO_CTRL_SET:
	b->ptr = ptr;
	b->num = 0;
	b->shutdown = (int)num;
	b->init = 1;
	break;

    case BIO_CTRL_GET:
	if (b->init) {
	    if (!ptr)
		ret = 0;
	    else
		*(char **)ptr = (char *)b->ptr;
	} else {
	    ret = -1;
	}
	break;

    case BIO_CTRL_GET_CLOSE:
	ret = b->shutdown;
	break;

    case BIO_CTRL_SET_CLOSE:
	b->shutdown = (int)num;
	break;

    case BIO_CTRL_PENDING:
    case BIO_CTRL_WPENDING:
	ret = 0;
	break;

    case BIO_CTRL_FLUSH:
    case BIO_CTRL_DUP:
	break;

    default:
	ret = 0;
	break;
    }
    return ret;
}


static BIO_METHOD mico_bio_methods = {
    BIO_TYPE_MEM, "mico_bio",
    (ssl_int_t)  mico_bio_write,
    (ssl_int_t)  mico_bio_read,
    (ssl_int_t)  mico_bio_puts,
    (ssl_int_t)  0, // mico_bio_gets
    (ssl_long_t) mico_bio_ctrl,
    (ssl_int_t)  mico_bio_new,
    (ssl_int_t)  mico_bio_free
};

static BIO_METHOD *BIO_mico ()
{
    return &mico_bio_methods;
}


/*************************** SSLAddress ****************************/


MICOSSL::SSLAddress::SSLAddress (CORBA::Address *a)
{
    // consume a
    _addr = a;
}

MICOSSL::SSLAddress::SSLAddress (const SSLAddress &a)
{
    _addr = a._addr->clone();
}

MICOSSL::SSLAddress &
MICOSSL::SSLAddress::operator= (const SSLAddress &a)
{
    delete _addr;
    _addr = a._addr->clone();
    return *this;
}

MICOSSL::SSLAddress::~SSLAddress ()
{
    delete _addr;
}

string
MICOSSL::SSLAddress::stringify () const
{
    return string("ssl:") + _addr->stringify();
}

const char *
MICOSSL::SSLAddress::proto () const
{
    return "ssl";
}

CORBA::Transport *
MICOSSL::SSLAddress::make_transport () const
{
    return new SSLTransport (this);
}

CORBA::TransportServer *
MICOSSL::SSLAddress::make_transport_server () const
{
    return new SSLTransportServer (this);
}

CORBA::IORProfile *
MICOSSL::SSLAddress::make_ior_profile (CORBA::Octet *key,
				       CORBA::ULong keylen,
				       const CORBA::MultiComponent &mc) const
{
    return new SSLProfile (key, keylen, *this, mc);
}

CORBA::Boolean
MICOSSL::SSLAddress::is_local () const
{
    return _addr->is_local();
}

CORBA::Address *
MICOSSL::SSLAddress::clone () const
{
    return new SSLAddress (*this);
}

const CORBA::Address *
MICOSSL::SSLAddress::content () const
{
    return _addr;
}

void
MICOSSL::SSLAddress::content (CORBA::Address *a)
{
    delete _addr;
    // consume a
    _addr = a;
}

CORBA::Long
MICOSSL::SSLAddress::compare (const CORBA::Address &a) const
{
    CORBA::Long r = strcmp (proto(), a.proto());
    if (r)
	return r;
    const SSLAddress &he = (SSLAddress &)a;
    return _addr->compare (*he._addr);
}

CORBA::Boolean
MICOSSL::SSLAddress::operator== (const CORBA::Address &a) const
{
    return compare (a) == 0;
}

CORBA::Boolean
MICOSSL::SSLAddress::operator< (const CORBA::Address &a) const
{
    return compare (a) < 0;
}


/*************************** SSLAddressParser *************************/


MICOSSL::SSLAddressParser::SSLAddressParser ()
{
    CORBA::Address::register_parser (this);
}

MICOSSL::SSLAddressParser::~SSLAddressParser ()
{
    CORBA::Address::unregister_parser (this);
}

CORBA::Address *
MICOSSL::SSLAddressParser::parse (const char *str, const char *) const
{
    CORBA::Address *a = CORBA::Address::parse (str);
    if (!a)
	return 0;

    return new SSLAddress (a);
}

CORBA::Boolean
MICOSSL::SSLAddressParser::has_proto (const char *p) const
{
    return !strcmp ("ssl", p);
}

static MICOSSL::SSLAddressParser ssl_address_parser;


/************************** SSLTransport *****************************/


#ifdef HAVE_NAMESPACE
namespace MICOSSL {
  int SSLTransport::_ssl_verify_depth = 0;
  SSL_CTX *SSLTransport::_ssl_ctx = 0;
};
#else
int MICOSSL::SSLTransport::_ssl_verify_depth = 0;
SSL_CTX *MICOSSL::SSLTransport::_ssl_ctx = 0;
#endif

MICOSSL::SSLTransport::SSLTransport (const SSLAddress *a, CORBA::Transport *t)
{
    _transp = t ? t : a->content()->make_transport();
    _local_addr = (SSLAddress *)a->clone();
    _peer_addr = (SSLAddress *)a->clone();

    CORBA::Boolean r = setup_ctx();
    assert (r);

    _bio = BIO_new (BIO_mico());
    assert (_bio);
    BIO_ctrl (_bio, BIO_CTRL_SET, 0, (char *)_transp);

    _ssl = SSL_new (_ssl_ctx);
    SSL_set_bio (_ssl, _bio, _bio);

    _rcb = _wcb = 0;
}

MICOSSL::SSLTransport::~SSLTransport ()
{
    CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
    _transp->rselect (orb->dispatcher(), 0);
    _transp->wselect (orb->dispatcher(), 0);
    _rcb = _wcb = 0;

    // XXX what if shutdown cannot be sent immediately ???
    SSL_shutdown (_ssl);

    SSL_free (_ssl);
    // BIO is freed in SSL_free()
    delete _transp;
    delete _local_addr;
    delete _peer_addr;
}

int
MICOSSL::SSLTransport::ssl_verify_callback (int ok, X509_STORE_CTX *ctx)
{
    int error = X509_STORE_CTX_get_error (ctx);
    int depth = X509_STORE_CTX_get_error_depth (ctx);

    if (!ok) {
	MICODebug::instance()->printer()
	    << "SSL verify error: " << X509_verify_cert_error_string (error)
	    << endl;
	// XXX
	if (_ssl_verify_depth <= depth) {
	    ok = 1;
	} else {
	    ok = 0;
	}
    }
    return ok;
}

CORBA::Boolean
MICOSSL::SSLTransport::setup_ctx ()
{
    if (_ssl_ctx)
	return TRUE;

    const char *cert = 0, *key = 0, *cafile = 0, *capath = 0, *cipher = 0;
    int verify = SSL_VERIFY_NONE;

    const MICOGetOpt::OptVec &o = SSL_options;
    for (MICOGetOpt::OptVec::const_iterator i = o.begin(); i != o.end(); ++i) {
	const string &arg = (*i).first;
	const string &val = (*i).second;
	if (arg == "-ORBSSLverify") {
	    verify = SSL_VERIFY_PEER;
	    _ssl_verify_depth = atoi ((char *)val.c_str());
	} else if (arg == "-ORBSSLcert") {
	    cert = val.c_str();
	} else if (arg == "-ORBSSLkey") {
	    key = val.c_str();
	} else if (arg == "-ORBSSLCApath") {
	    capath = val.c_str();
	} else if (arg == "-ORBSSLCAfile") {
	    cafile = val.c_str();
	} else if (arg == "-ORBSSLcipher") {
	    cipher = val.c_str();
	}
    }

    if (!cipher)
	cipher = getenv ("SSL_CIPHER");
    if (!cert)
	cert = "default.pem";
    if (!key)
	key = cert;

    SSLeay_add_ssl_algorithms ();
    _ssl_ctx = SSL_CTX_new (SSLv23_method());

    if (cipher)
	SSL_CTX_set_cipher_list (_ssl_ctx, (char *)cipher);
    SSL_CTX_set_verify (_ssl_ctx, verify, (ssl_int_t)ssl_verify_callback);

    SSL_CTX_set_client_CA_list (_ssl_ctx,
				SSL_load_client_CA_file ((char *)cert));

    if (SSL_CTX_use_certificate_file (_ssl_ctx, (char *)cert,
				      SSL_FILETYPE_PEM) <= 0) {
	MICODebug::instance()->printer()
	    << "cannot set SSL certificate file: " << cert << endl;
	return FALSE;
    }
    if (SSL_CTX_use_PrivateKey_file (_ssl_ctx, (char *)key,
				     SSL_FILETYPE_PEM) <= 0) {
	MICODebug::instance()->printer()
	    << "cannot set SSL private key file: " << key << endl;
	return FALSE;
    }
    if (SSL_CTX_check_private_key (_ssl_ctx) <= 0) {
	MICODebug::instance()->printer()
	    << "bad private key" << endl;
	return FALSE;
    }

    SSL_load_error_strings ();

    int ret = SSL_CTX_load_verify_locations (_ssl_ctx, (char *)cafile,
                                             (char *)capath);
    
    if ((!ret && (capath || cafile)) ||
	!SSL_CTX_set_default_verify_paths (_ssl_ctx)) {
	MICODebug::instance()->printer()
	    << "cannot set SSL verify locations" << endl;
	return FALSE;
    }
    return TRUE;
}

void
MICOSSL::SSLTransport::rselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    _rcb = cb;
    _transp->rselect (disp, cb ? this : 0);
}

void
MICOSSL::SSLTransport::wselect (CORBA::Dispatcher *disp,
			     CORBA::TransportCallback *cb)
{
    _wcb = cb;
    _transp->wselect (disp, cb ? this : 0);
}

void
MICOSSL::SSLTransport::callback (CORBA::Transport *, Event ev)
{
    switch (ev) {
    case CORBA::TransportCallback::Read:
	_rcb->callback (this, ev);
	break;

    case CORBA::TransportCallback::Write:
	_wcb->callback (this, ev);
	break;

    case CORBA::TransportCallback::Remove:
	if (_rcb)
	    _rcb->callback (this, ev);
	if (_wcb)
	    _wcb->callback (this, ev);
	_rcb = _wcb = 0;
	break;
    }
}

CORBA::Boolean
MICOSSL::SSLTransport::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "ssl"));
    SSLAddress *sa = (SSLAddress *)a;

    CORBA::Boolean r = _transp->bind (sa->content());
    if (!r) {
	_err = _transp->errormsg();
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICOSSL::SSLTransport::connect (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "ssl"));
    SSLAddress *sa = (SSLAddress *)a;

    CORBA::Boolean blocking = _transp->isblocking();
    _transp->block (TRUE);
    CORBA::Boolean r = _transp->connect (sa->content());
    if (!r) {
	_err = _transp->errormsg();
        _transp->block (blocking);
	return FALSE;
    }
#if SSLEAY_VERSION_NUMBER >= 0x0900
    SSL_set_connect_state (_ssl);
#endif
    int i = SSL_connect (_ssl);
    _transp->block (blocking);
    if (i <= 0) {
	_err = "SSL active connection setup failed";
	return FALSE;
    }
    return TRUE;
}

CORBA::Boolean
MICOSSL::SSLTransport::accept ()
{
    CORBA::Boolean blocking = _transp->isblocking();
    _transp->block (TRUE);
    int i = SSL_accept (_ssl);
    _transp->block (blocking);
    if (i <= 0) {
	_err = "SSL passive connection setup failed";
	return FALSE;
    }
    return TRUE;
}

void
MICOSSL::SSLTransport::close ()
{
    // XXX what if shutdown cannot be sent immediately ???
    SSL_shutdown (_ssl);
    SSL_set_connect_state (_ssl);
    _transp->close ();
}

void
MICOSSL::SSLTransport::block (CORBA::Boolean doblock)
{
    _transp->block (doblock);
}

CORBA::Boolean
MICOSSL::SSLTransport::isblocking ()
{
    return _transp->isblocking();
}

CORBA::Boolean
MICOSSL::SSLTransport::isreadable ()
{
    // XXX if transport is readable that doesnt mean that SSL_read()
    // can read something ...
    return _transp->isreadable();
}

CORBA::Long
MICOSSL::SSLTransport::read (void *_b, CORBA::Long len)
{
    int i = SSL_read (_ssl, (char *)_b, len);
    if (i < 0)
	_err = _transp->errormsg();
    return i;
}

CORBA::Long
MICOSSL::SSLTransport::write (const void *_b, CORBA::Long len)
{
    int i = SSL_write (_ssl, (char *)_b, len);
    if (i < 0)
	_err = _transp->errormsg();
    return i;
}

const CORBA::Address *
MICOSSL::SSLTransport::addr ()
{
    _local_addr->content (_transp->addr()->clone());
    return _local_addr;
}

const CORBA::Address *
MICOSSL::SSLTransport::peer ()
{
    _peer_addr->content (_transp->peer()->clone());
    return _peer_addr;
}

CORBA::Boolean
MICOSSL::SSLTransport::bad () const
{
    return _err.length() > 0;
}

CORBA::Boolean
MICOSSL::SSLTransport::eof () const
{
    return _transp->eof();
}

string
MICOSSL::SSLTransport::errormsg () const
{
    return _err;
}

CORBA::Principal_ptr
MICOSSL::SSLTransport::get_principal ()
{
    return new SSLPrincipal (SSL_get_peer_certificate (_ssl),
			     SSL_get_cipher (_ssl), this);
}


/************************ SSLTransportServer **************************/


MICOSSL::SSLTransportServer::SSLTransportServer (const SSLAddress *a)
{
    _server = a->content()->make_transport_server();
    _local_addr = (SSLAddress *)a->clone();
    _acb = 0;
}

MICOSSL::SSLTransportServer::~SSLTransportServer ()
{
    CORBA::ORB_var orb = CORBA::ORB_instance ("mico-local-orb");
    _server->aselect (orb->dispatcher(), 0);
    _acb = 0;

    delete _server;
    delete _local_addr;
}

void
MICOSSL::SSLTransportServer::aselect (CORBA::Dispatcher *disp,
				   CORBA::TransportServerCallback *cb)
{
    _acb = cb;
    _server->aselect (disp, cb ? this : 0);
}

void
MICOSSL::SSLTransportServer::callback (CORBA::TransportServer *, Event ev)
{
    switch (ev) {
    case CORBA::TransportServerCallback::Accept:
	_acb->callback (this, ev);
	break;

    case CORBA::TransportServerCallback::Remove:
	_acb->callback (this, ev);
	_acb = 0;
	break;
    }
}

CORBA::Boolean
MICOSSL::SSLTransportServer::bind (const CORBA::Address *a)
{
    assert (!strcmp (a->proto(), "ssl"));
    SSLAddress *sa = (SSLAddress *)a;

    if (!_server->bind (sa->content())) {
        _err = _server->errormsg();
        return FALSE;
    }
    return TRUE;
}

void
MICOSSL::SSLTransportServer::close ()
{
    _server->close ();
}

void
MICOSSL::SSLTransportServer::block (CORBA::Boolean doblock)
{
    _server->block (doblock);
}

CORBA::Boolean
MICOSSL::SSLTransportServer::isblocking ()
{
    return _server->isblocking();
}

CORBA::Transport *
MICOSSL::SSLTransportServer::accept ()
{
    CORBA::Transport *t = _server->accept();
    if (!t)
        return 0;
    SSLTransport *st = new SSLTransport (_local_addr, t);
    st->accept ();
    return st;
}

const CORBA::Address *
MICOSSL::SSLTransportServer::addr ()
{
    _local_addr->content (_server->addr()->clone());
    return _local_addr;
}

CORBA::Boolean
MICOSSL::SSLTransportServer::bad () const
{
    return _err.length() > 0;
}

string
MICOSSL::SSLTransportServer::errormsg () const
{
    return _err;
}


/****************************** SSLProfile *****************************/

/*
 * the next function is the only one that has to be changed
 * to add support for SSL over a new low level transport.
 */

static CORBA::IORProfile::ProfileId
tag_to_ssltag (CORBA::IORProfile::ProfileId tag)
{
    switch (tag) {
    case CORBA::IORProfile::TAG_INTERNET_IOP:
        return CORBA::IORProfile::TAG_SSL_INTERNET_IOP;
    case CORBA::IORProfile::TAG_UNIX_IOP:
        return CORBA::IORProfile::TAG_SSL_UNIX_IOP;
    case CORBA::IORProfile::TAG_UDP_IOP:
        return CORBA::IORProfile::TAG_SSL_UDP_IOP;
    default:
        assert (0);
    }
    return 0;
}

MICOSSL::SSLProfile::SSLProfile (CORBA::Octet *o, CORBA::ULong l,
				 const SSLAddress &ia,
				 const CORBA::MultiComponent &mc)
    : _myaddr (ia)
{
    // copy port from IIOP profile to SSLComponent
    CORBA::UShort port = 0;
    if (strcmp (_myaddr.content()->proto(), "inet") == 0)
	port = ((MICO::InetAddress *)_myaddr.content())->port();

    CORBA::MultiComponent mc2 (mc);
    mc2.add_component (new SSLComponent (port));

    _prof = ia.content()->make_ior_profile (o, l, mc2);
}

MICOSSL::SSLProfile::SSLProfile (CORBA::IORProfile *ior, const SSLAddress &ia)
    : _myaddr (ia)
{
    _prof = ior;

    // use port from SSLComponent instead of port from IIOP profile ...
    if (strcmp (_myaddr.content()->proto(), "inet") == 0) {
	assert (ior->id() == CORBA::IORProfile::TAG_INTERNET_IOP);
	CORBA::MultiComponent *mc = ior->components();
	CORBA::Component *c =
	    mc->component (CORBA::Component::TAG_SSL_SEC_TRANS);
	assert (c);
	CORBA::UShort port =  ((SSLComponent *)c)->port();
	((MICO::InetAddress *)_myaddr.content())->port (port);
    }
}

MICOSSL::SSLProfile::SSLProfile (const SSLProfile &ip)
    : _myaddr (ip._myaddr)
{
    _prof = ip._prof->clone();
}

MICOSSL::SSLProfile::~SSLProfile ()
{
    delete _prof;
}

MICOSSL::SSLProfile &
MICOSSL::SSLProfile::operator= (const SSLProfile &ip)
{
    if (this != &ip) {
        delete _prof;
        _prof = ip._prof->clone();
        _myaddr = ip._myaddr;
    }
    return *this;
}

void
MICOSSL::SSLProfile::encode (CORBA::DataEncoder &ec) const
{
    _prof->encode (ec);
}

const CORBA::Address *
MICOSSL::SSLProfile::addr () const
{
    return &_myaddr;
}

MICOSSL::SSLProfile::ProfileId
MICOSSL::SSLProfile::id () const
{
    return tag_to_ssltag (_prof->id());
}

MICOSSL::SSLProfile::ProfileId
MICOSSL::SSLProfile::encode_id () const
{
    return _prof->id();
}

void
MICOSSL::SSLProfile::objectkey (CORBA::Octet *o, CORBA::Long l)
{
    _prof->objectkey (o, l);
}

const CORBA::Octet *
MICOSSL::SSLProfile::objectkey (CORBA::Long &l) const
{
    return _prof->objectkey (l);
}

CORBA::Boolean
MICOSSL::SSLProfile::reachable ()
{
    return _prof->reachable ();
}

void
MICOSSL::SSLProfile::print (ostream &o) const
{
    o << "SSL ";
    _prof->print (o);
}

CORBA::IORProfile *
MICOSSL::SSLProfile::clone () const
{
    return new SSLProfile (*this);
}

CORBA::Long
MICOSSL::SSLProfile::compare (const CORBA::IORProfile &p) const
{
    if (p.id() != id())
	return (CORBA::Long)id() - (CORBA::Long)p.id();

    const SSLProfile &sp = (const SSLProfile &)p;

    CORBA::Long r = _myaddr.compare (sp._myaddr);
    if (r)
	return r;

    return _prof->compare (*sp._prof);
}

CORBA::Boolean
MICOSSL::SSLProfile::operator== (const CORBA::IORProfile &p) const
{
    return compare (p) == 0;
}

CORBA::Boolean
MICOSSL::SSLProfile::operator< (const CORBA::IORProfile &p) const
{
    return compare (p) < 0;
}


/*************************** SSLProfileDecoder *************************/


/*
 * unfortunately SSL does not have its own IOR profile, but is
 * part of the IIOP profile. Therefore we cannot use our own
 * profile decoder (the below code) but have to insert special
 * checks into the IIOP profile decoder code. Except this
 * unavoidable uglyness the SSL code is completely independent
 * from the rest of MICO.
 */

#if 0
MICOSSL::SSLProfileDecoder::SSLProfileDecoder ()
{
    CORBA::IORProfile::register_decoder (this);
}

MICOSSL::SSLProfileDecoder::~SSLProfileDecoder ()
{
    CORBA::IORProfile::unregister_decoder (this);
}

CORBA::IORProfile *
MICOSSL::SSLProfileDecoder::decode (CORBA::DataDecoder &dc, ProfileId pid,
                                 CORBA::ULong len) const
{
    ProfileId orig_pid = ssltag_to_tag (pid);
    CORBA::IORProfile *ior =
        CORBA::IORProfile::decode_body (dc, orig_pid, len);
    if (!ior)
        return 0;

    SSLAddress sa (ior->addr()->clone());
    return new SSLProfile (ior, sa);
}

CORBA::Boolean
MICOSSL::SSLProfileDecoder::has_id (MICOSSL::SSLProfile::ProfileId id) const
{
    return supported_ssltag (id);
}

static MICOSSL::SSLProfileDecoder ssl_ior_decoder;
#endif

/***************************** SSLPrincipal **************************/


MICOSSL::SSLPrincipal::SSLPrincipal (X509 *peer, const char *cipher,
                                     CORBA::DataDecoder &dc,
                                     CORBA::Transport *t)
    : CORBA::Principal (dc, t), _peer (peer),
      _ssl_cipher (cipher ? cipher : "")
{
}

MICOSSL::SSLPrincipal::SSLPrincipal (X509 *peer, const char *cipher,
                                     CORBA::Transport *t)
    : CORBA::Principal (t), _peer (peer), _ssl_cipher (cipher ? cipher : "")
{
}

MICOSSL::SSLPrincipal::~SSLPrincipal ()
{
    if (_peer)
	X509_free (_peer);
}

CORBA::Principal::PropertyNameList_ptr
MICOSSL::SSLPrincipal::list_properties ()
{
    PropertyNameList_ptr pl = MICO_SCOPE(CORBA,Principal)::list_properties ();
    CORBA::ULong olen = pl->length();
    pl->length (olen+3);

    (*pl)[olen++] = (const char *)"ssl-x509-subject";
    (*pl)[olen++] = (const char *)"ssl-x509-issuer";
    (*pl)[olen++] = (const char *)"ssl-cipher";

    return pl;
}

string
MICOSSL::SSLPrincipal::get_x509_entry (X509_NAME *name, const char *entry)
{
    const char *cp = strchr (entry, ':');
    if (!cp) {
	char *cp = X509_NAME_oneline (name, NULL, 0);
	string s = cp;
	::free (cp);
	return s;
    }
    int nid = OBJ_txt2nid ((char *)cp+1);
    if (nid == NID_undef)
	return string();

    char buf[1000];
    if (X509_NAME_get_text_by_NID (name, nid, buf, sizeof (buf)) < 0)
	return string();

    return string (buf);
}

CORBA::Any*
MICOSSL::SSLPrincipal::get_property (const char *prop_name)
{
    if (!strcmp ("auth-method", prop_name)) {
	CORBA::Any *a = new CORBA::Any;
	*a <<= "ssl";
	return a;
    }
    if (!strncmp ("ssl-x509-subject", prop_name, strlen("ssl-x509-subject"))) {
	CORBA::Any *a = new CORBA::Any;
	if (_peer) {
	    string s = get_x509_entry (X509_get_subject_name (_peer),
				       prop_name);
	    *a <<= s.c_str();
	} else {
	    *a <<= "";
	}
	return a;
    }
    if (!strncmp ("ssl-x509-issuer", prop_name, strlen ("ssl-x509-issuer"))) {
	CORBA::Any *a = new CORBA::Any;
	if (_peer) {
	    string s = get_x509_entry (X509_get_issuer_name (_peer),
				       prop_name);
	    *a <<= s.c_str();
	} else {
	    *a <<= "";
	}
	return a;
    }
    if (!strcmp ("ssl-cipher", prop_name)) {
	CORBA::Any *a = new CORBA::Any;
	*a <<= _ssl_cipher.c_str();
	return a;
    }
    return MICO_SCOPE(CORBA,Principal)::get_property (prop_name);
}


/***************************** SSLComponent **************************/


MICOSSL::SSLComponent::SSLComponent (
    CORBA::UShort port,
    Security::AssociationOptions target_supports,
    Security::AssociationOptions target_requires)
    : _target_supports (target_supports),
      _target_requires (target_requires),
      _port (port)
{
}

MICOSSL::SSLComponent::~SSLComponent ()
{
}

void
MICOSSL::SSLComponent::encode (CORBA::DataEncoder &ec) const
{
    ec.struct_begin();
    {
	// MICO_SSL_VB_COMPAT ...
	if (sizeof (Security::AssociationOptions) == sizeof (CORBA::ULong)) {
	    ec.put_ulong ((CORBA::ULong&)_target_supports);
	    ec.put_ulong ((CORBA::ULong&)_target_requires);
	} else {
	    ec.put_ushort ((CORBA::UShort&)_target_supports);
	    ec.put_ushort ((CORBA::UShort&)_target_requires);
	}
	ec.put_ushort (_port);
    }
    ec.struct_end();
}

CORBA::Component::ComponentId
MICOSSL::SSLComponent::id () const
{
    return TAG_SSL_SEC_TRANS;
}

void
MICOSSL::SSLComponent::print (ostream &o) const
{
  o << " SSL:"
    << " supports 0x" << hex << _target_supports
    << " requires 0x" << hex << _target_requires
    << " port " << dec << _port << endl;
}

CORBA::Component *
MICOSSL::SSLComponent::clone () const
{
    return new SSLComponent (*this);
}

CORBA::Long
MICOSSL::SSLComponent::compare (const CORBA::Component &c) const
{
    if (id() != c.id())
	return (CORBA::Long)id() - (CORBA::Long)c.id();

    const SSLComponent &sc = (const SSLComponent &)c;

    CORBA::Long r = (CORBA::Long)_port - (CORBA::Long)sc._port;
    if (r)
	return r;

    r = (CORBA::Long)_target_supports - (CORBA::Long)sc._target_supports;
    if (r)
	return r;

    return (CORBA::Long)_target_requires - (CORBA::Long)sc._target_requires;
}

CORBA::Boolean
MICOSSL::SSLComponent::operator== (const CORBA::Component &c) const
{
    return compare (c) == 0;
}

CORBA::Boolean
MICOSSL::SSLComponent::operator< (const CORBA::Component &c) const
{
    return compare (c) < 0;
}


/************************** SSLComponentDecoder ************************/


MICOSSL::SSLComponentDecoder::SSLComponentDecoder ()
{
    CORBA::Component::register_decoder (this);
}

MICOSSL::SSLComponentDecoder::~SSLComponentDecoder ()
{
    CORBA::Component::unregister_decoder (this);
}

#define check(exp) if (!(exp)) return 0;

CORBA::Component *
MICOSSL::SSLComponentDecoder::decode (CORBA::DataDecoder &dc,
				      ComponentId id, CORBA::ULong len) const
{
    Security::AssociationOptions target_supports, target_requires;
    CORBA::UShort port;

    check (dc.struct_begin ());
    {
        // MICO_SSL_VB_COMPAT ...
	if (sizeof (Security::AssociationOptions) == sizeof (CORBA::ULong)) {
	    check (dc.get_ulong ((CORBA::ULong&)target_supports));
	    check (dc.get_ulong ((CORBA::ULong&)target_requires));
	} else {
	    check (dc.get_ushort ((CORBA::UShort&)target_supports));
	    check (dc.get_ushort ((CORBA::UShort&)target_requires));
	}
	check (dc.get_ushort (port));
    }
    check (dc.struct_end ());

    return new SSLComponent (port, target_supports, target_requires);
}

#undef check

CORBA::Boolean
MICOSSL::SSLComponentDecoder::has_id (ComponentId id) const
{
    return id == CORBA::Component::TAG_SSL_SEC_TRANS;
}

static MICOSSL::SSLComponentDecoder ssl_component_decoder;


/***************************** Initialization **************************/


static class SSLInit : public Interceptor::InitInterceptor {
public:
    SSLInit ()
        : MICO_SCOPE(Interceptor,InitInterceptor) (0)
    {
    }
    Interceptor::Status initialize (CORBA::ORB_ptr orb,
				    const char *orbid,
				    int &argc, char *argv[])
    {
	MICOGetOpt::OptMap opts;
	opts["-ORBSSLverify"]     = "arg-expected";
	opts["-ORBSSLcert"]       = "arg-expected";
	opts["-ORBSSLkey"]        = "arg-expected";
	opts["-ORBSSLCApath"]     = "arg-expected";
	opts["-ORBSSLCAfile"]     = "arg-expected";
	opts["-ORBSSLcipher"]     = "arg-expected";

	MICOGetOpt opt_parser (opts);
	CORBA::Boolean r = opt_parser.parse (orb->rcfile(), TRUE);
	assert (r);
	r = opt_parser.parse (argc, argv, TRUE);
	assert (r);
	SSL_options = opt_parser.opts ();

	return Interceptor::INVOKE_CONTINUE;
    }
} __ssl_init;

void
MICOSSL::_init ()
{
  __ssl_init;
}

#endif // HAVE_SSL

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

#ifndef __mico_ssl_h__
#define __mico_ssl_h__

#ifdef HAVE_SSL

#include <mico/ssliop.h>

#ifdef HAVE_OPENSSL_SSL_H
#include <openssl/objects.h>
#include <openssl/crypto.h>
#include <openssl/buffer.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#else
#include <objects.h>
#include <crypto.h>
#include <buffer.h>
#include <bio.h>
#include <ssl.h>
#include <x509.h>
#endif

MICO_NAMESPACE_DECL MICOSSL {

MICO_EXPORT_DECL void _init ();

class SSLAddress;
class SSLTransport;
class SSLTransportServer;
class SSLProfile;
class SSLPrincipal;
typedef SSLPrincipal *SSLPrincipal_ptr;


class SSLPrincipal : public CORBA::Principal {
    X509 *_peer;
    string _ssl_cipher;

    static string get_x509_entry (X509_NAME *name, const char *entry);
public:
    SSLPrincipal (X509 *peer, const char *cipher, CORBA::DataDecoder &,
                  CORBA::Transport * = 0);
    SSLPrincipal (X509 *peer, const char *cipher, CORBA::Transport * = 0);
    ~SSLPrincipal ();
    
    PropertyNameList_ptr list_properties ();
    CORBA::Any* get_property (const char *prop_name);
};


class SSLAddress : public CORBA::Address {
    CORBA::Address *_addr;
public:
    SSLAddress (CORBA::Address *a);
    SSLAddress (const SSLAddress &);
    SSLAddress &operator= (const SSLAddress &a);
    ~SSLAddress ();
    
    string stringify () const;
    const char *proto () const;
    CORBA::Transport *make_transport () const;
    CORBA::TransportServer *make_transport_server () const;
    CORBA::IORProfile *make_ior_profile (
	CORBA::Octet *, CORBA::ULong, const CORBA::MultiComponent &) const;
    CORBA::Boolean is_local () const;
    
    CORBA::Address *clone () const;
    
    CORBA::Long compare (const CORBA::Address &) const;
    CORBA::Boolean operator== (const CORBA::Address &) const;
    CORBA::Boolean operator< (const CORBA::Address &) const;

    const CORBA::Address *content() const;
    void content (CORBA::Address *);
};

class SSLAddressParser : public CORBA::AddressParser {
public:
    SSLAddressParser ();
    ~SSLAddressParser ();
    CORBA::Address *parse (const char *, const char *) const;
    CORBA::Boolean has_proto (const char *) const;
};


class SSLProfile : public CORBA::IORProfile {
    CORBA::IORProfile *_prof;
    SSLAddress _myaddr;
public:
    SSLProfile (CORBA::Octet *objkey, CORBA::ULong length,
		const SSLAddress &, const CORBA::MultiComponent &);
    SSLProfile (CORBA::IORProfile *ior, const SSLAddress &);
    SSLProfile (const SSLProfile &);
    ~SSLProfile ();
    SSLProfile &operator= (const SSLProfile &);

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

#if 0
class SSLProfileDecoder : public CORBA::IORProfileDecoder {
public:
    SSLProfileDecoder ();
    ~SSLProfileDecoder ();
    CORBA::IORProfile *decode (CORBA::DataDecoder &, ProfileId,
    			       CORBA::ULong) const;
    CORBA::Boolean has_id (ProfileId) const;
};
#endif


class SSLComponent : public CORBA::Component {
    Security::AssociationOptions _target_supports;
    Security::AssociationOptions _target_requires;
    CORBA::UShort _port;
public:
    SSLComponent (CORBA::UShort port,
		  Security::AssociationOptions target_supports = 0,
		  Security::AssociationOptions target_requires = 0);
    ~SSLComponent ();
    
    void encode (CORBA::DataEncoder &) const;
    ComponentId id () const;
    void print (ostream &) const;
    
    CORBA::Component *clone () const;
    CORBA::Long compare (const CORBA::Component &) const;
    CORBA::Boolean operator== (const CORBA::Component &) const;
    CORBA::Boolean operator< (const CORBA::Component &) const;

    CORBA::UShort port () const
    { return _port; }

    Security::AssociationOptions target_supports () const
    { return _target_supports; }

    Security::AssociationOptions target_requires () const
    { return _target_requires; }
};

class SSLComponentDecoder : public CORBA::ComponentDecoder {
public:
    SSLComponentDecoder ();
    ~SSLComponentDecoder ();
    
    CORBA::Component *decode (CORBA::DataDecoder &,
    			      ComponentId, CORBA::ULong) const;
    CORBA::Boolean has_id (ComponentId) const;
};


class SSLTransport : public CORBA::Transport,
		     public CORBA::TransportCallback {
    CORBA::Transport *_transp;
    SSLAddress *_local_addr, *_peer_addr;
    BIO *_bio;
    SSL *_ssl;
    string _err;
    CORBA::TransportCallback *_rcb, *_wcb;

    static CORBA::Boolean setup_ctx ();

    static SSL_CTX *_ssl_ctx;
    static int _ssl_verify_depth;
    static int ssl_verify_callback (int ok, X509_STORE_CTX *);

    void callback (CORBA::Transport *, Event);
public:
    SSLTransport (const SSLAddress *, CORBA::Transport * = 0);
    ~SSLTransport ();
    
    void rselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    void wselect (CORBA::Dispatcher *, CORBA::TransportCallback *);
    
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

    CORBA::Boolean accept ();

    CORBA::Principal_ptr get_principal ();
};


class SSLTransportServer : public CORBA::TransportServer,
			   public CORBA::TransportServerCallback {
    CORBA::TransportServer *_server;
    SSLAddress *_local_addr;
    string _err;
    CORBA::TransportServerCallback *_acb;

    void callback (CORBA::TransportServer *, Event);
public:
    SSLTransportServer (const SSLAddress *);
    ~SSLTransportServer ();
    
    void aselect (CORBA::Dispatcher *,
    		  CORBA::TransportServerCallback *);
    
    CORBA::Boolean bind (const CORBA::Address *);
    void close ();
    void block (CORBA::Boolean doblock = TRUE);
    CORBA::Boolean isblocking ();
    
    CORBA::Transport *accept ();
    const CORBA::Address *addr ();
    
    CORBA::Boolean bad () const;
    string errormsg () const;
};

}; // namespace SSL

#endif // HAVE_SSL
#endif // __mico_ssl_h__

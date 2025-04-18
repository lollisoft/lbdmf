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

#ifndef __mico_ior_impl_h__
#define __mico_ior_impl_h__


class LocalProfile : public CORBA::IORProfile {
    string host;
    CORBA::Long pid;
    CORBA::Octet *objkey;
    CORBA::ULong length;
    LocalAddress myaddr;
    ProfileId tagid;
public:
    LocalProfile (CORBA::Octet *objkey, CORBA::ULong length,
		  ProfileId = TAG_LOCAL,
		  const char *host = 0, CORBA::Long pid = -1);
    LocalProfile (const LocalProfile &);
    ~LocalProfile ();
    LocalProfile &operator= (const LocalProfile &);

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

class LocalProfileDecoder : public CORBA::IORProfileDecoder {
    CORBA::IORProfile::ProfileId tagid;
public:
    LocalProfileDecoder (CORBA::IORProfile::ProfileId
#ifndef _WINDOWS
			 = CORBA::IORProfile::TAG_LOCAL
#endif
			 );
    ~LocalProfileDecoder ();
    CORBA::IORProfile *decode (CORBA::DataDecoder &,
			       ProfileId, CORBA::ULong) const;
    CORBA::Boolean has_id (ProfileId) const;
};


class IIOPProfile : public CORBA::IORProfile {
    CORBA::Octet *objkey;
    CORBA::ULong length;
    MICO::InetAddress myaddr;
    CORBA::MultiComponent comps;
    ProfileId tagid;
    CORBA::UShort version;
public:
    IIOPProfile (CORBA::Octet *objkey, CORBA::ULong length,
		 const InetAddress &,
		 const CORBA::MultiComponent & = CORBA::MultiComponent(),
		 CORBA::UShort version = 0x0100,
		 ProfileId = TAG_INTERNET_IOP);
    IIOPProfile (const IIOPProfile &);
    ~IIOPProfile ();
    IIOPProfile &operator= (const IIOPProfile &);

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
    
    CORBA::MultiComponent *components()
    { return &comps; }
};

class IIOPProfileDecoder : public CORBA::IORProfileDecoder {
    CORBA::IORProfile::ProfileId tagid;
    MICO::InetAddress::Family family;
public:
    IIOPProfileDecoder (CORBA::IORProfile::ProfileId
#ifndef _WINDOWS
			= CORBA::IORProfile::TAG_INTERNET_IOP
#endif
			, MICO::InetAddress::Family
#ifndef _WINDOWS
			= MICO::InetAddress::STREAM
#endif
		);
    ~IIOPProfileDecoder ();
    CORBA::IORProfile *decode (CORBA::DataDecoder &, ProfileId,
			       CORBA::ULong) const;
    CORBA::Boolean has_id (ProfileId) const;
};


#ifdef HAVE_SYS_UN_H
class UIOPProfile : public CORBA::IORProfile {
    string host;
    CORBA::Octet *objkey;
    CORBA::ULong length;
    UnixAddress myaddr;
    ProfileId tagid;
    CORBA::MultiComponent comps;
    CORBA::UShort version;
public:
    UIOPProfile (CORBA::Octet *objkey, CORBA::ULong length,
		 const UnixAddress &,
		 const CORBA::MultiComponent &,
		 CORBA::UShort version = 0x0100,
		 ProfileId = TAG_UNIX_IOP,
		 const char *host = 0);
    UIOPProfile (const UIOPProfile &);
    ~UIOPProfile ();
    UIOPProfile &operator= (const UIOPProfile &);

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

class UIOPProfileDecoder : public CORBA::IORProfileDecoder {
    CORBA::IORProfile::ProfileId tagid;
public:
    UIOPProfileDecoder (CORBA::IORProfile::ProfileId
			= CORBA::IORProfile::TAG_UNIX_IOP);
    ~UIOPProfileDecoder ();
    CORBA::IORProfile *decode (CORBA::DataDecoder &, ProfileId,
    			       CORBA::ULong) const;
    CORBA::Boolean has_id (ProfileId) const;
};
#endif // HAVE_SYS_UN_H


class MultiCompProfile : public CORBA::IORProfile {
    CORBA::MultiComponent _mc;
    ProfileId _tagid;
public:
    MultiCompProfile (const CORBA::MultiComponent &mc,
		      ProfileId tagid = TAG_MULTIPLE_COMPONENTS);
    MultiCompProfile (const MultiCompProfile &);
    ~MultiCompProfile ();
    MultiCompProfile &operator= (const MultiCompProfile &);

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

    CORBA::MultiComponent *components();
};

class MultiCompProfileDecoder : public CORBA::IORProfileDecoder {
    CORBA::IORProfile::ProfileId _tagid;
public:
    MultiCompProfileDecoder (CORBA::IORProfile::ProfileId
#ifndef _WINDOWS
			     = CORBA::IORProfile::TAG_MULTIPLE_COMPONENTS
#endif
			     );
    ~MultiCompProfileDecoder ();
    CORBA::IORProfile *decode (CORBA::DataDecoder &,
    			       ProfileId, CORBA::ULong) const;
    CORBA::Boolean has_id (ProfileId) const;
};


class UnknownProfile : public CORBA::IORProfile {
    ProfileId tagid;
    vector<CORBA::Octet> tagdata;
public:
    UnknownProfile (ProfileId id);
    UnknownProfile (const UnknownProfile &);
    ~UnknownProfile ();
    UnknownProfile &operator= (const UnknownProfile &);

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

    static UnknownProfile *decode (CORBA::DataDecoder &,
				   ProfileId id, CORBA::ULong len);
};


class UnknownComponent : public CORBA::Component {
    ComponentId tagid;
    vector<CORBA::Octet> tagdata;
public:
    UnknownComponent (ComponentId id, CORBA::Octet * = 0,
                      CORBA::ULong len = 0);
    UnknownComponent (const UnknownComponent &);
    ~UnknownComponent ();
    UnknownComponent &operator= (const UnknownComponent &);

    void encode (CORBA::DataEncoder &) const;
    ComponentId id () const;
    void print (ostream &) const;
    
    CORBA::Component *clone () const;
    CORBA::Long compare (const CORBA::Component &) const;
    CORBA::Boolean operator== (const CORBA::Component &) const;
    CORBA::Boolean operator< (const CORBA::Component &) const;

    static UnknownComponent *decode (CORBA::DataDecoder &,
                                     ComponentId id, CORBA::ULong len);
};

#endif // __mico_ior_impl_h__

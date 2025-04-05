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

#ifndef __mico_codeset_impl_h__
#define __mico_codeset_impl_h__


class UniCodesetConv : public CORBA::CodesetConv {
protected:
    UniCodesetConv ();
    UniCodesetConv (const UniCodesetConv &);
    UniCodesetConv (CORBA::Codeset *, CORBA::Codeset *);

    static CORBA::Boolean supported_csid (CORBA::Codeset::CodesetId);

    CORBA::Long convert (const char *from, CORBA::ULong len,
			 char *to);
public:
    ~UniCodesetConv ();

    static CORBA::CodesetConv *create (CORBA::Codeset *from,
				       CORBA::Codeset *to);
    static CORBA::Boolean can_convert (CORBA::Codeset::CodesetId from,
				       CORBA::Codeset::CodesetId to);

    CORBA::CodesetConv *clone () const;
    /*
     * both from and to codesets can be byte oriented and non byte oriented.
     * there is one convert() method for each of those four combinations.
     */
    CORBA::Long encode (const CORBA::Char *from, CORBA::ULong len,
			CORBA::DataEncoder &to,
			CORBA::Boolean terminate = TRUE);
    CORBA::Long encode (const CORBA::WChar *from, CORBA::ULong len,
			CORBA::DataEncoder &to,
			CORBA::Boolean terminate = TRUE);
    CORBA::Long decode (CORBA::DataDecoder &from, CORBA::ULong len,
			CORBA::WChar *to,
			CORBA::Boolean terminate = TRUE);
    CORBA::Long decode (CORBA::DataDecoder &from, CORBA::ULong len,
			CORBA::Char *to,
			CORBA::Boolean terminate = TRUE);
};


class CodesetConvDB {
public:
    typedef CORBA::Codeset::CodesetId CodesetId;
    typedef CORBA::ULongLong KeyType;
    typedef map<KeyType, CORBA::CodesetConv *, less<KeyType> > MapIdConv;
private:
    MapIdConv _converters;
public:
    CodesetConvDB ();
    ~CodesetConvDB ();

    CORBA::CodesetConv *find (CodesetId from, CodesetId to);
    CORBA::CodesetConv *reverse (CORBA::CodesetConv *);
};


class CodesetComponent : public CORBA::Component {
public:
    typedef CORBA::ULong CodeSetId;
private:
    CodeSetId _native_cs;
    CodeSetId _native_wcs;
    vector<CodeSetId> _conv_cs;
    vector<CodeSetId> _conv_wcs;
    CodeSetId _selected_cs;
    CodeSetId _selected_wcs;
public:
    CodesetComponent ();
    CodesetComponent (CodeSetId native_cs, CodeSetId native_wcs,
                      const vector<CodeSetId> &conv_cs,
                      const vector<CodeSetId> &conv_wcs);
    CodesetComponent (const CodesetComponent &csc);
    ~CodesetComponent ();
    
    void encode (CORBA::DataEncoder &) const;
    ComponentId id () const;
    void print (ostream &) const;
    
    CORBA::Component *clone () const;
    CORBA::Long compare (const CORBA::Component &) const;
    CORBA::Boolean operator== (const CORBA::Component &) const;
    CORBA::Boolean operator< (const CORBA::Component &) const;

    CodeSetId selected_cs ();
    CodeSetId selected_wcs ();
};


class CodesetComponentDecoder : public CORBA::ComponentDecoder {
public:
    CodesetComponentDecoder ();
    ~CodesetComponentDecoder ();
    
    CORBA::Component *decode (CORBA::DataDecoder &,
    			      ComponentId, CORBA::ULong) const;
    CORBA::Boolean has_id (ComponentId) const;
};

#endif // __mico_codeset_impl_h__

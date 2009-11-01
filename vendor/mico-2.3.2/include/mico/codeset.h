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

#ifndef __mico_codeset_h__
#define __mico_codeset_h__

class Codeset {
public:
    typedef CORBA::ULong CodesetId;
    typedef CORBA::UShort CharsetId;

    enum { MAX_CHARSETS = 5 };

    struct Info {
	CodesetId id;
	CORBA::UShort codepoint_size;
	CORBA::UShort max_codepoints;
	CharsetId charsets[MAX_CHARSETS];
	const char *desc;
	const char *name;
    };

    enum SpecialCS {
	_SpecialMin,
	NativeCS = 0,
	NativeWCS,
	FallbackCS,
	FallbackWCS,
	DefaultCS,
	DefaultWCS,
	_SpecialMax
    };
private:
    static CORBA::Boolean _disabled;
    static Codeset *_special[_SpecialMax];
    Info *_info;

    Codeset ();
    Codeset (Info *);
public:
    static void disable (CORBA::Boolean d)
    { _disabled = d; }

    static CORBA::Boolean disabled ()
    { return _disabled; }

    Codeset (const Codeset &);
    ~Codeset ();

    static void _init ();

    static Info *_find_info (CodesetId);
    static Info *_find_info (const char *);

    static Codeset *create (CodesetId);
    static Codeset *create (const char *);

    static Codeset *special_cs (SpecialCS);
    static void set_special_cs (SpecialCS, Codeset *);

    CORBA::Boolean is_compatible (const Codeset *) const;
    CORBA::Boolean is_compatible (CodesetId) const;

    CodesetId id () const
    { return _info->id; }

    const char *name () const
    { return _info->name; }

    const char *desc () const
    { return _info->desc; }

    CORBA::UShort codepoint_size () const
    { return _info->codepoint_size; }

    CORBA::UShort max_codepoints () const
    { return _info->max_codepoints; }

    CORBA::ULong guess_size (CORBA::ULong nchars) const
    { return (nchars+1) * _info->max_codepoints; }
};


class CodesetConv {
protected:
    Codeset *_from;
    Codeset *_to;

    CodesetConv ();
    CodesetConv (const CodesetConv &);
    CodesetConv (Codeset *, Codeset *);
public:
    virtual ~CodesetConv ();

    static CodesetConv *create (Codeset *from, Codeset *to);
    static Boolean can_convert (Codeset::CodesetId from,
				Codeset::CodesetId to);

    Codeset *from ()
    { return _from; }

    Codeset *to ()
    { return _to; }

    virtual CodesetConv *clone () const;
    /*
     * both from and to codesets can be byte oriented and non byte oriented.
     * there is one convert() method for each of those four combinations.
     */
    virtual CORBA::Long encode (const CORBA::Char *from, CORBA::ULong len,
				CORBA::DataEncoder &to,
				CORBA::Boolean terminate = TRUE);
    virtual CORBA::Long encode (const CORBA::WChar *from, CORBA::ULong len,
				CORBA::DataEncoder &to,
				CORBA::Boolean terminate = TRUE);
    virtual CORBA::Long decode (CORBA::DataDecoder &from, CORBA::ULong len,
				CORBA::WChar *to,
				CORBA::Boolean terminate = TRUE);
    virtual CORBA::Long decode (CORBA::DataDecoder &from, CORBA::ULong len,
				CORBA::Char *to,
				CORBA::Boolean terminate = TRUE);
};

#endif // __mico_codeset_h__

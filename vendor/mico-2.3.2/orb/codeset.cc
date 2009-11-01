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
#include <mico/util.h>
#include <mico/impl.h>
#include <mico/intercept.h>
#include <mico/template_impl.h>

#include <mico/code_set_registry.h>


#ifdef HAVE_NAMESPACE
namespace CORBA {
  CORBA::Codeset *Codeset::_special[CORBA::Codeset::_SpecialMax] = { 0 };
  CORBA::Boolean Codeset::_disabled = FALSE;
};
#else
CORBA::Codeset *CORBA::Codeset::_special[CORBA::Codeset::_SpecialMax] = { 0 };
CORBA::Boolean CORBA::Codeset::_disabled = FALSE;
#endif

CORBA::Codeset::Codeset()
{
    assert (0);
}

CORBA::Codeset::Codeset (Info *info)
{
    _info = info;
}

CORBA::Codeset::Codeset (const Codeset &cs)
{
    _info = cs._info;
}

CORBA::Codeset::~Codeset()
{
}

CORBA::Codeset::Info *
CORBA::Codeset::_find_info (CodesetId id)
{
    for (int i = 0; _osf_cs_reg[i].id; ++i) {
	if (id == _osf_cs_reg[i].id)
	    return &_osf_cs_reg[i];
    }
    return 0;
}

CORBA::Codeset::Info *
CORBA::Codeset::_find_info (const char *pat)
{
    for (int i = 0; _osf_cs_reg[i].id; ++i) {
	if (mico_fnmatch (_osf_cs_reg[i].desc, pat))
	    return &_osf_cs_reg[i];
    }
    return 0;
}

CORBA::Codeset *
CORBA::Codeset::create (CodesetId id)
{
    Info *i = _find_info (id);
    if (!i)
	return 0;
    return new Codeset (i);
}

CORBA::Codeset *
CORBA::Codeset::create (const char *pat)
{
    Info *i = _find_info (pat);
    if (!i)
	return 0;
    return new Codeset (i);
}

CORBA::Codeset *
CORBA::Codeset::special_cs (SpecialCS csid)
{
    assert (_SpecialMin <= csid && csid < _SpecialMax);
    return _special[csid];
}

void
CORBA::Codeset::set_special_cs (SpecialCS csid, Codeset *cs)
{
    assert (_SpecialMin <= csid && csid < _SpecialMax);
    _special[csid] = cs;
}

CORBA::Boolean
CORBA::Codeset::is_compatible (const Codeset *cs) const
{
    // we assume that charset ids are sorted in ascending order
    const CharsetId *cp1 = _info->charsets;
    const CharsetId *cp2 = cs->_info->charsets;

    // they are compatible if they have at least one charset in common
    while (*cp1 && *cp2) {
	if (*cp1 < *cp2)
	    ++cp1;
	else if (*cp1 > *cp2)
	    ++cp2;
	else
	    return TRUE;
    }
    return FALSE;
}

CORBA::Boolean
CORBA::Codeset::is_compatible (CodesetId id) const
{
    Info *i = _find_info (id);
    if (!i)
	return FALSE;

    Codeset cs (i);

    return is_compatible (&cs);
}


//-----------------


CORBA::CodesetConv::CodesetConv ()
{
    assert (0);
}

CORBA::CodesetConv::CodesetConv (Codeset *f, Codeset *t)
{
    _from = f;
    _to = t;
}

CORBA::CodesetConv::CodesetConv (const CodesetConv &csc)
{
    _from = new Codeset (*csc._from);
    _to = new Codeset (*csc._to);
}

CORBA::CodesetConv::~CodesetConv ()
{
    delete _from;
    delete _to;
}

CORBA::CodesetConv *
CORBA::CodesetConv::create (Codeset *f, Codeset *t)
{
    if (f->id() == t->id())
	return new CodesetConv (f, t);
    return MICO::UniCodesetConv::create (f, t);
}

CORBA::Boolean
CORBA::CodesetConv::can_convert (Codeset::CodesetId from,
				 Codeset::CodesetId to)
{
    if (from == to)
	return TRUE;
    return MICO::UniCodesetConv::can_convert (from, to);
}

CORBA::CodesetConv *
CORBA::CodesetConv::clone () const
{
    return new CodesetConv (*this);
}

CORBA::Long
CORBA::CodesetConv::encode (const CORBA::Char *f, CORBA::ULong len,
			    CORBA::DataEncoder &t, CORBA::Boolean terminate)
{
    switch (_from->codepoint_size()) {
    case 1: {
	t.put_octets (f, len);
	if (terminate)
	    t.put_octet (0);
	break;
    }
    case 2: {
	for (CORBA::Long i = len; --i >= 0; )
	    t.put_ushort ((CORBA::UShort)*f++);
	if (terminate)
	    t.put_ushort (0);
	break;
    }
    case 3:
    case 4: {
	for (CORBA::Long i = len; --i >= 0; )
	    t.put_ulong ((CORBA::ULong)*f++);
	if (terminate)
	    t.put_ulong (0);
	break;
    }
    default:
	assert (0);
    }
    // number of codepoints written
    return len + !!terminate;
}

CORBA::Long
CORBA::CodesetConv::encode (const CORBA::WChar *f, CORBA::ULong len,
			    CORBA::DataEncoder &t, CORBA::Boolean terminate)
{
    switch (_from->codepoint_size()) {
    case 1: {
	for (CORBA::Long i = len; --i >= 0; )
	    t.put_octet ((CORBA::Char)*f++);
	if (terminate)
	    t.put_octet (0);
	break;
    }
    case 2: {
	for (CORBA::Long i = len; --i >= 0; )
	    t.put_ushort ((CORBA::UShort)*f++);
	if (terminate)
	    t.put_ushort (0);
	break;
    }
    case 3:
    case 4: {
	for (CORBA::Long i = len; --i >= 0; )
	    t.put_ulong ((CORBA::ULong)*f++);
	if (terminate)
	    t.put_ulong (0);
	break;
    }
    default:
	assert (0);
    }
    // number of codepoints written
    return len + !!terminate;
}

CORBA::Long
CORBA::CodesetConv::decode (CORBA::DataDecoder &f, CORBA::ULong len,
			    CORBA::Char *t, CORBA::Boolean terminate)
{
    switch (_from->codepoint_size()) {
    case 1: {
	if (!f.get_octets (t, len))
	    return -1;
	if (terminate)
	    t[len] = 0;
	break;
    }
    case 2: {
	CORBA::UShort us;
	for (CORBA::Long i = len; --i >= 0; ) {
	    if (!f.get_ushort (us))
		return -1;
	    *t++ = (CORBA::Char)us;
	}
	if (terminate)
	    *t = 0;
	break;
    }
    case 3:
    case 4: {
	CORBA::ULong ul;
	for (CORBA::Long i = len; --i >= 0; ) {
	    if (!f.get_ulong (ul))
		return -1;
	    *t++ = (CORBA::Char)ul;
	}
	if (terminate)
	    *t = 0;
	break;
    }
    default:
	assert (0);
    }
    // number of codepoints read
    return len;
}

CORBA::Long
CORBA::CodesetConv::decode (CORBA::DataDecoder &f, CORBA::ULong len,
			    CORBA::WChar *t, CORBA::Boolean terminate)
{
    switch (_from->codepoint_size()) {
    case 1: {
	CORBA::Octet ch;
	for (CORBA::Long i = len; --i >= 0; ) {
	    if (!f.get_octet (ch))
		return -1;
	    *t++ = (CORBA::WChar)ch;
	}
	if (terminate)
	    *t = 0;
	break;
    }
    case 2: {
	CORBA::UShort us;
	for (CORBA::Long i = len; --i >= 0; ) {
	    if (!f.get_ushort (us))
		return -1;
	    *t++ = (CORBA::WChar)us;
	}
	if (terminate)
	    *t = 0;
	break;
    }
    case 3:
    case 4: {
	CORBA::ULong ul;
	for (CORBA::Long i = len; --i >= 0; ) {
	    if (!f.get_ulong (ul))
		return -1;
	    *t++ = (CORBA::WChar)ul;
	}
	if (terminate)
	    *t = 0;
	break;
    }
    default:
	assert (0);
    }
    // number of codepoints read
    return len;
}


//-----------------


#include "uni_conversion.h"
#include "uni_strtypes.h"
#include "uni_errors.h"

MICO::UniCodesetConv::UniCodesetConv ()
{
    assert (0);
}

MICO::UniCodesetConv::UniCodesetConv (CORBA::Codeset *f, CORBA::Codeset *t)
    : CORBA::CodesetConv (f, t)
{
}

MICO::UniCodesetConv::UniCodesetConv (const UniCodesetConv &csc)
    : CORBA::CodesetConv (csc)
{
}

MICO::UniCodesetConv::~UniCodesetConv ()
{
}

CORBA::Boolean
MICO::UniCodesetConv::supported_csid (CORBA::Codeset::CodesetId csid)
{
    switch (csid) {
    case C_ISO8859_1:
    case C_ISO8859_2:
    case C_ISO8859_3:
    case C_ISO8859_4:
    case C_ISO8859_5:
    case C_ISO8859_6:
    case C_ISO8859_7:
    case C_ISO8859_8:
    case C_ISO8859_9:
    case C_ISO8859_10:
    case C_IBM_437:
    case C_IBM_850:
    case C_IBM_852:
    case C_IBM_860:
    case C_IBM_863:
    case C_IBM_865:
    case C_UCS4:
    case C_UTF16:
    case C_UTF8:
    case (uni_ulong)C_WIN31_LATIN1:
    case (uni_ulong)C_ASCII7:
    case (uni_ulong)C_EBCDIC:
    case (uni_ulong)C_MACINTOSH:
    case (uni_ulong)C_KOI8_R:
    case (uni_ulong)C_UTF7:
    case (uni_ulong)C_HTML3:
	return TRUE;
    default:
	return FALSE;
    }
}

CORBA::CodesetConv *
MICO::UniCodesetConv::create (CORBA::Codeset *f, CORBA::Codeset *t)
{
    if (can_convert (f->id(), t->id()))
	return new UniCodesetConv (f, t);
    return 0;
}

CORBA::Boolean
MICO::UniCodesetConv::can_convert (CORBA::Codeset::CodesetId from,
				   CORBA::Codeset::CodesetId to)
{
    return supported_csid (from) && supported_csid (to);
}

CORBA::CodesetConv *
MICO::UniCodesetConv::clone () const
{
    return new UniCodesetConv (*this);
}

CORBA::Long
MICO::UniCodesetConv::convert (const char *f, CORBA::ULong len, char *t)
{
    if (_from->id() == C_UTF8) {
	CORBA::ULong chars = len, utf_read = 0, written = 0;

	CORBA::Long ret = uni_fromUTF8 (t, f, &chars, &utf_read, _to->id(),
					C_LINE_LF, &written);

	if (ret != C_OK) {
	    MICODebug::instance()->debugger()
		<< "codeset conversion error in stage 1" << endl;
	    return -1;
	}
	return written;
    }

    if (_to->id() == C_UTF8) {
	CORBA::ULong written = 0;

	CORBA::Long ret = uni_toUTF8 (t, f, len, _from->id(),
				      C_LINE_LF, &written);

	if (ret != C_OK) {
	    MICODebug::instance()->debugger()
		<< "codeset conversion error in stage 2" << endl;
	    return -1;
	}
	return written;
    }

    // UTF8 has max 6 code points per char
#ifdef __GNUG__
    char tmp[len*6+1];
#else
    CORBA::String_var tmp = CORBA::string_alloc (len*6);
#endif

    CORBA::ULong chars, utf_read, written;
    CORBA::Long ret = uni_toUTF8 (tmp, f,
				  len, _from->id(), C_LINE_LF, &chars);

    if (ret != C_OK) {
	MICODebug::instance()->debugger()
	    << "codeset conversion error in stage 3" << endl;
	return -1;
    }

    ret = uni_fromUTF8 (t, tmp, &chars, &utf_read, _to->id(),
			C_LINE_LF, &written);

    if (ret != C_OK) {
	MICODebug::instance()->debugger()
	    << "codeset conversion error in stage 4" << endl;
	return -1;
    }
    return written;
}

CORBA::Long
MICO::UniCodesetConv::encode (const CORBA::Char *f, CORBA::ULong len,
			      CORBA::DataEncoder &t, CORBA::Boolean terminate)
{
    char *from, *to, *cp;

    CORBA::ULong flen = _from->codepoint_size();
    if (flen == 3)
	flen = 4;
    flen *= len;

#ifdef __GNUG__
    char _f[flen+1];
#else
    CORBA::String_var _f;
    if (_from->codepoint_size() != 1)
	_f = CORBA::string_alloc (flen);
#endif

    switch (_from->codepoint_size()) {
    case 1:
	from = (char *)f;
	break;
    case 2:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 2)
	    *(CORBA::UShort *)cp = (CORBA::UShort)*f++;
	}
	break;
    case 3:
    case 4:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 4)
	    *(CORBA::ULong *)cp = (CORBA::ULong)*f++;
	}
	break;
    default:
	assert (0);
    }

    CORBA::ULong tlen = _to->codepoint_size();
    if (tlen == 3)
	tlen = 4;
    tlen *= len * _to->max_codepoints();

#ifdef __GNUG__
    char _t[tlen+1];
#else
    CORBA::String_var _t;
    if (_to->codepoint_size() != 1)
	_t = CORBA::string_alloc (tlen);
#endif

    if (_to->codepoint_size() == 1) {
	t.buffer()->resize (tlen+1);
	to = (char *)(t.buffer()->buffer() + t.buffer()->wpos());
    } else
	to = (char*) _t;

    CORBA::Long written = convert (from, flen, to);
    if (written < 0)
	return written;
    if (!terminate)
	--written;

    switch (_to->codepoint_size()) {
    case 1:
	t.buffer()->wseek_rel (written);
	break;
    case 2:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 2)
	    t.put_ushort (*(CORBA::UShort *)cp);
	}
	break;
    case 3:
    case 4:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 4)
	    t.put_ulong (*(CORBA::ULong *)cp);
	}
	break;
    default:
	assert (0);
    }

    return written;
}

CORBA::Long
MICO::UniCodesetConv::encode (const CORBA::WChar *f, CORBA::ULong len,
			      CORBA::DataEncoder &t, CORBA::Boolean terminate)
{
    char *cp, *from;

    CORBA::ULong flen = _from->codepoint_size();
    if (flen == 3)
	flen = 4;
    flen *= len;

#ifdef __GNUG__
    char _f[flen+1];
#else
    CORBA::String_var _f;
    if (_from->codepoint_size() < 3)
	_f = CORBA::string_alloc (flen);
#endif

    switch (_from->codepoint_size()) {
    case 1:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; ++cp)
	    *cp = (CORBA::Char)*f++;
	}
	break;
    case 2:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 2)
	    *(CORBA::UShort *)cp = (CORBA::UShort)*f++;
	}
	break;
    case 3:
    case 4:
	from = (char *)f;
	break;
    default:
	assert (0);
    }

    CORBA::ULong tlen = _to->codepoint_size();
    if (tlen == 3)
	tlen = 4;
    tlen *= len * _to->max_codepoints();

#ifdef __GNUG__
    char _t[tlen+1];
#else
    CORBA::String_var _t = CORBA::string_alloc (tlen);
#endif

    CORBA::Long written = convert (from, flen, _t);
    if (written < 0)
	return written;
    if (!terminate)
	--written;

    switch (_to->codepoint_size()) {
    case 1:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; ++cp)
	    t.put_octet (*(CORBA::Char *)cp);
	}
	break;
    case 2:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 2)
	    t.put_ushort (*(CORBA::UShort *)cp);
	}
	break;
    case 3:
    case 4:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 4)
	    t.put_ulong (*(CORBA::ULong *)cp);
	}
	break;
    default:
	assert (0);
    }

    return written;
}

CORBA::Long
MICO::UniCodesetConv::decode (CORBA::DataDecoder &f, CORBA::ULong len,
			      CORBA::Char *t, CORBA::Boolean terminate)
{
    char *cp, *from, *to;

    CORBA::ULong flen = _from->codepoint_size();
    if (flen == 3)
	flen = 4;
    flen *= len;

#ifdef __GNUG__
    char _f[flen+1];
#else
    CORBA::String_var _f;
    if (_from->codepoint_size() != 1)
	_f = CORBA::string_alloc (flen);
#endif

    switch (_from->codepoint_size()) {
    case 1:
	from = (char *)f.buffer()->data();
	if (f.buffer()->length() < len)
	    return -1;
	// XXX make sure seeked over data is still valid
	f.buffer()->rseek_rel (len);
	break;
    case 2:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 2) {
	    if (!f.get_ushort (*(CORBA::UShort *)cp))
	      return -1;
	  }
	}
	break;
    case 3:
    case 4:
        from = cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 4)
	    if (!f.get_ulong (*(CORBA::ULong *)cp))
	      return -1;
	}
	break;
    default:
	assert (0);
    }

    CORBA::ULong tlen = _to->codepoint_size();
    if (tlen == 3)
	tlen = 4;
    tlen *= len * _to->max_codepoints();

#ifdef __GNUG__
    char _t[tlen+1];
#else
    CORBA::String_var _t;
    if (_to->codepoint_size() != 1)
	_t = CORBA::string_alloc (tlen);
#endif

    if (_to->codepoint_size() == 1)
	to = (char *)t;
    else
	to = (char*) _t;

    CORBA::Long written = convert (from, flen, to);
    if (written < 0)
	return written;
    if (!terminate)
	--written;

    switch (_to->codepoint_size()) {
    case 1:
	break;
    case 2:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 2)
	    *t++ = (CORBA::Char)*(CORBA::UShort *)cp;
	}
	break;
    case 3:
    case 4:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 4)
	    *t++ = (CORBA::Char)*(CORBA::ULong *)cp;
	}
	break;
    default:
	assert (0);
    }

    return written;
}

CORBA::Long
MICO::UniCodesetConv::decode (CORBA::DataDecoder &f, CORBA::ULong len,
			      CORBA::WChar *t, CORBA::Boolean terminate)
{
    char *cp, *to;

    CORBA::ULong flen = _from->codepoint_size();
    if (flen == 3)
	flen = 4;
    flen *= len;

#ifdef __GNUG__
    char _f[flen+1];
#else
    CORBA::String_var _f = CORBA::string_alloc (flen);
#endif

    switch (_from->codepoint_size()) {
    case 1:
        cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; ++cp) {
	    if (!f.get_octet (*(CORBA::Octet *)cp))
	      return -1;
	  }
	}
	break;
    case 2:
        cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 2) {
	    if (!f.get_ushort (*(CORBA::UShort *)cp))
	      return -1;
	  }
	}
	break;
    case 3:
    case 4:
        cp = (char*) _f;
        {
	  for (CORBA::Long i = len; --i >= 0; cp += 4)
	    if (!f.get_ulong (*(CORBA::ULong *)cp))
	      return -1;
	}
	break;
    default:
	assert (0);
    }

    CORBA::ULong tlen = _to->codepoint_size();
    if (tlen == 3)
	tlen = 4;
    tlen *= len * _to->max_codepoints();

#ifdef __GNUG__
    char _t[tlen+1];
#else
    CORBA::String_var _t;
    if (_to->codepoint_size() < 3)
	_t = CORBA::string_alloc (tlen);
#endif

    if (_to->codepoint_size() >= 3)
	to = (char *)t;
    else
	to = (char*) _t;

    CORBA::Long written = convert (_f, flen, to);
    if (written < 0)
	return written;
    if (!terminate)
	--terminate;

    switch (_to->codepoint_size()) {
    case 1:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; )
	    *t++ = *cp++;
	}
	break;
    case 2:
        cp = (char*) _t;
        {
	  for (CORBA::Long i = written; --i >= 0; cp += 2)
	    *t++ = (CORBA::WChar)*(CORBA::UShort *)cp;
	}
	break;
    case 3:
    case 4:
	break;
    default:
	assert (0);
    }

    return written;
}


//-----------------


MICO::CodesetConvDB::CodesetConvDB ()
{
}

MICO::CodesetConvDB::~CodesetConvDB ()
{
}

CORBA::CodesetConv *
MICO::CodesetConvDB::find (CodesetId from, CodesetId to)
{
    KeyType key = from;
    key <<= 32;
    key += to;

    MapIdConv::iterator i = _converters.find (key);
    if (i != _converters.end())
	return (*i).second;

    CORBA::Codeset *cl = CORBA::Codeset::create (from);
    if (!cl)
	return 0;
    CORBA::Codeset *sv = CORBA::Codeset::create (to);
    if (!sv) {
	delete cl;
	return 0;
    }
    CORBA::CodesetConv *conv = CORBA::CodesetConv::create (cl, sv);
    if (!conv) {
	delete cl;
	delete sv;
	return 0;
    }
    _converters[key] = conv;

    return conv;
}

CORBA::CodesetConv *
MICO::CodesetConvDB::reverse (CORBA::CodesetConv *conv)
{
    if (!conv)
	return 0;

    KeyType key = conv->to()->id();
    key <<= 32;
    key += conv->from()->id();

    MapIdConv::iterator i = _converters.find (key);
    if (i != _converters.end())
	return (*i).second;

    CORBA::Codeset *cl = new CORBA::Codeset (*conv->to());
    CORBA::Codeset *sv = new CORBA::Codeset (*conv->from());

    CORBA::CodesetConv *rconv = CORBA::CodesetConv::create (cl, sv);
    if (!rconv) {
	delete cl;
	delete sv;
	return 0;
    }
    _converters[key] = rconv;

    return rconv;
}


//-----------------


MICO::CodesetComponent::CodesetComponent ()
    : _native_cs (0), _native_wcs (0),
      _selected_cs (0), _selected_wcs (0)
{
}

MICO::CodesetComponent::CodesetComponent (CodeSetId native_cs,
					  CodeSetId native_wcs,
					  const vector<CodeSetId> &conv_cs,
					  const vector<CodeSetId> &conv_wcs)
    : _native_cs (native_cs), _native_wcs (native_wcs),
      _conv_cs (conv_cs), _conv_wcs (conv_wcs),
      _selected_cs (0), _selected_wcs (0)
{
}

MICO::CodesetComponent::CodesetComponent (const CodesetComponent &csc)
    : _native_cs (csc._native_cs), _native_wcs (csc._native_wcs),
      _conv_cs (csc._conv_cs), _conv_wcs (csc._conv_wcs),
      _selected_cs (csc._selected_cs), _selected_wcs (csc._selected_wcs)
{
}

MICO::CodesetComponent::~CodesetComponent ()
{
}

void
MICO::CodesetComponent::encode (CORBA::DataEncoder &ec) const
{
    // CodeSetComponentInfo
    ec.struct_begin();
    {
	// ForCharData
	ec.struct_begin();
	{
	    // native_code_set
	    ec.put_ulong (_native_cs);
	    // conversion_code_sets
	    ec.seq_begin (_conv_cs.size());
	    for (mico_vec_size_type i = 0; i < _conv_cs.size(); ++i)
		ec.put_ulong (_conv_cs[i]);
	    ec.seq_end ();
	}
	ec.struct_end();

	// ForWcharData
	ec.struct_begin();
	{
	    // native_code_set
	    ec.put_ulong (_native_wcs);
	    // conversion_code_sets
	    ec.seq_begin (_conv_wcs.size());
	    for (mico_vec_size_type i = 0; i < _conv_wcs.size(); ++i)
		ec.put_ulong (_conv_wcs[i]);
	    ec.seq_end ();
	}
	ec.struct_end();
    }
    ec.struct_end();
}

CORBA::Component::ComponentId
MICO::CodesetComponent::id () const
{
    return TAG_CODE_SETS;
}

void
MICO::CodesetComponent::print (ostream &o) const
{
  CORBA::Codeset::Info * nci = CORBA::Codeset::_find_info (_native_cs);
  CORBA::Codeset::Info * nwi = CORBA::Codeset::_find_info (_native_wcs);

  o << "Native Codesets:" << endl;
  o << "              normal: ";

  if (nci) {
    o << nci->desc << endl;
  }
  else {
    o << "0x" << hex << _native_cs << endl;
  }

  o << "                wide: ";

  if (nwi) {
    o << nwi->desc << endl;
  }
  else {
    o << "0x" << hex << _native_wcs << endl;
  }

  if (_conv_cs.size() > 0) {
    o << "              Other Codesets: " << endl;
    for (mico_vec_size_type i = 0; i < _conv_cs.size(); i++) {
      nci = CORBA::Codeset::_find_info (_conv_cs[i]);
      o << "                      ";
      if (nci) {
	o << nci->desc << endl;
      }
      else {
	o << "0x" << hex << _conv_cs[i] << endl;
      }
    }
  }

  if (_conv_wcs.size() > 0) {
    o << "              Other Wide Codesets: " << endl;
    for (mico_vec_size_type i = 0; i < _conv_wcs.size(); i++) {
      nwi = CORBA::Codeset::_find_info (_conv_wcs[i]);
      o << "                      ";
      if (nwi) {
	o << nwi->desc << endl;
      }
      else {
	o << "0x" << hex << _conv_wcs[i] << endl;
      }
    }
  }
}

CORBA::Component *
MICO::CodesetComponent::clone () const
{
    return new CodesetComponent (*this);
}

CORBA::Long
MICO::CodesetComponent::compare (const CORBA::Component &c) const
{
    if (id() != c.id())
	return (CORBA::Long)id() - (CORBA::Long)c.id();

    CodesetComponent &csc = (CodesetComponent &)c;

    if (_native_cs != csc._native_cs)
	return (CORBA::Long)_native_cs - (CORBA::Long)csc._native_cs;

    if (_native_wcs != csc._native_wcs)
	return (CORBA::Long)_native_wcs - (CORBA::Long)csc._native_wcs;

    CORBA::Long r = mico_vec_compare (_conv_cs, csc._conv_cs);
    if (r)
	return r;

    return mico_vec_compare (_conv_wcs, csc._conv_wcs);
}

CORBA::Boolean
MICO::CodesetComponent::operator== (const CORBA::Component &c) const
{
    return compare (c) == 0;
}

CORBA::Boolean
MICO::CodesetComponent::operator< (const CORBA::Component &c) const
{
    return compare (c) < 0;
}

MICO::CodesetComponent::CodeSetId
MICO::CodesetComponent::selected_cs ()
{
    if (_selected_cs)
	return _selected_cs;

    CodeSetId cl_nat =
	CORBA::Codeset::special_cs (CORBA::Codeset::NativeCS)->id();

    CodeSetId sv_nat = _native_cs;
    /*
     * this is a workaround for a bug in VB, which specifies
     * a native code set 0 and no conversion code sets
     */
    if (!_native_cs && !_conv_cs.size())
	sv_nat = CORBA::Codeset::special_cs(CORBA::Codeset::DefaultCS)->id();

    // same native code sets?
    if (sv_nat == cl_nat) {
	_selected_cs = cl_nat;
	return _selected_cs;
    }
    // can client convert its native code set to servers native code set?
    if (CORBA::CodesetConv::can_convert (cl_nat, sv_nat)) {
	_selected_cs = sv_nat;
	return _selected_cs;
    }
    // can server convert clients native code set to its native code set?
    for (mico_vec_size_type i = 0; i < _conv_cs.size(); ++i) {
	if (cl_nat == _conv_cs[i]) {
	    _selected_cs = cl_nat;
	    return _selected_cs;
	}
    }
    /*
     * is there an intermediate code set client and server can convert
     * their native code sets to? favor server preferences.
     */
    {
      for (mico_vec_size_type i = 0; i < _conv_cs.size(); ++i) {
	if (CORBA::CodesetConv::can_convert (cl_nat, _conv_cs[i])) {
	  _selected_cs = _conv_cs[i];
	  return _selected_cs;
	}
      }
    }
    // use fallback code set
    _selected_cs =
	CORBA::Codeset::special_cs(CORBA::Codeset::FallbackCS)->id();
    return _selected_cs;
}

MICO::CodesetComponent::CodeSetId
MICO::CodesetComponent::selected_wcs ()
{
    if (_selected_wcs)
	return _selected_wcs;

    CodeSetId cl_nat =
	CORBA::Codeset::special_cs (CORBA::Codeset::NativeWCS)->id();

    CodeSetId sv_nat = _native_wcs;
    /*
     * this is a workaround for a bug in VB, which specifies
     * a native code set 0 and no conversion code sets
     */
    if (!_native_wcs && !_conv_wcs.size())
	sv_nat = CORBA::Codeset::special_cs(CORBA::Codeset::DefaultWCS)->id();

    // same native code sets?
    if (sv_nat == cl_nat) {
	_selected_wcs = cl_nat;
	return _selected_wcs;
    }
    // can client convert its native code set to servers native code set?
    if (CORBA::CodesetConv::can_convert (cl_nat, sv_nat)) {
	_selected_wcs = sv_nat;
	return _selected_wcs;
    }
    // can server convert clients native code set to its native code set?
    for (mico_vec_size_type i = 0; i < _conv_wcs.size(); ++i) {
	if (cl_nat == _conv_wcs[i]) {
	    _selected_wcs = cl_nat;
	    return _selected_wcs;
	}
    }
    /*
     * is there an intermediate code set client and server can convert
     * their native code sets to? favor server preferences.
     */
    {
      for (mico_vec_size_type i = 0; i < _conv_wcs.size(); ++i) {
	if (CORBA::CodesetConv::can_convert (cl_nat, _conv_wcs[i])) {
	  _selected_wcs = _conv_wcs[i];
	  return _selected_wcs;
	}
      }
    }
    // use fallback code set
    _selected_wcs =
	CORBA::Codeset::special_cs(CORBA::Codeset::FallbackWCS)->id();
    return _selected_wcs;
}


//-----------------


MICO::CodesetComponentDecoder::CodesetComponentDecoder ()
{
    CORBA::Component::register_decoder (this);
}

MICO::CodesetComponentDecoder::~CodesetComponentDecoder ()
{
    CORBA::Component::unregister_decoder (this);
}

#define check(exp) if (!(exp)) return 0;

CORBA::Component *
MICO::CodesetComponentDecoder::decode (CORBA::DataDecoder &dc,
				       ComponentId, CORBA::ULong) const
{
    CodesetComponent::CodeSetId native_cs, native_wcs;
    vector<CodesetComponent::CodeSetId> conv_cs, conv_wcs;
    CORBA::ULong len;

    // CodeSetComponentInfo
    check (dc.struct_begin());
    {
	// ForCharData
	check (dc.struct_begin());
	{
	    // native_code_set
	    check (dc.get_ulong (native_cs));
	    // conversion_code_sets
	    check (dc.seq_begin (len));
	    CORBA::ULong cs;
	    for (CORBA::ULong i = 0; i < len; ++i) {
		check (dc.get_ulong (cs));
		conv_cs.push_back (cs);
	    }
	    check (dc.seq_end ());
	}
	check (dc.struct_end());

	// ForWcharData
	check (dc.struct_begin());
	{
	    // native_code_set
	    check (dc.get_ulong (native_wcs));
	    // conversion_code_sets
	    check (dc.seq_begin (len));
	    CORBA::ULong cs;
	    for (CORBA::ULong i = 0; i < len; ++i) {
		check (dc.get_ulong (cs));
		conv_wcs.push_back (cs);
	    }
	    check (dc.seq_end ());
	}
	check (dc.struct_end());
    }
    check (dc.struct_end());

    return new CodesetComponent (native_cs, native_wcs, conv_cs, conv_wcs);
}

#undef check

CORBA::Boolean
MICO::CodesetComponentDecoder::has_id (ComponentId id) const
{
    return id == CORBA::Component::TAG_CODE_SETS;
}

static MICO::CodesetComponentDecoder codeset_component_decoder;


//-----------------


static class CodesetInit : public Interceptor::InitInterceptor {
public:
    CodesetInit ()
        : MICO_SCOPE(Interceptor,InitInterceptor) (0)
    {
    }
    Interceptor::Status initialize (CORBA::ORB_ptr orb,
				    const char *orbid,
				    int &argc, char *argv[])
    {
	MICOGetOpt::OptMap opts;
	opts["-ORBNativeCS"]   = "arg-expected";
	opts["-ORBNativeWCS"]  = "arg-expected";
	opts["-ORBNoCodeSets"] = "";

	MICOGetOpt opt_parser (opts);
	CORBA::Boolean r = opt_parser.parse (orb->rcfile(), TRUE);
	assert (r);
	r = opt_parser.parse (argc, argv, TRUE);
	assert (r);

	const char *cs_name = 0;
	const char *wcs_name = 0;
	CORBA::Boolean disable = FALSE;

	const MICOGetOpt::OptVec &o = opt_parser.opts();
	MICOGetOpt::OptVec::const_iterator i;
	for (i = o.begin(); i != o.end(); ++i) {
	    const string &arg = (*i).first;
	    const string &val = (*i).second;
	    if (arg == "-ORBNativeCS") {
		cs_name = val.c_str();
	    } else if (arg == "-ORBNativeWCS") {
		wcs_name = val.c_str();
	    } else if (arg == "-ORBNoCodeSets") {
		disable = TRUE;
	    }
	}

	CORBA::Codeset::disable (disable);

	// native char code set
	if (!cs_name)
	    cs_name = "*8859-1*";

	CORBA::Codeset *cs = CORBA::Codeset::create (cs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown native char code set: " << cs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::NativeCS, cs);

	// native wide char code set
	if (!wcs_name)
	    wcs_name = "*UTF-16*";

	cs = CORBA::Codeset::create (wcs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown native wide char code set: " << wcs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::NativeWCS, cs);

	// default char code set
	cs_name = "*8859-1*";
	cs = CORBA::Codeset::create (cs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown default char code set: " << cs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::DefaultCS, cs);

	// default wide char code set (spec says there is no default ...)
	cs_name = "*UTF-16*";
	cs = CORBA::Codeset::create (cs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown default wide char code set: " << cs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::DefaultWCS, cs);

	// fallback char code set
	cs_name = "*UTF-8*";
	cs = CORBA::Codeset::create (cs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown fallback char code set: " << cs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::FallbackCS, cs);

	// fallback wide char code set
	cs_name = "*UTF-16*";
	cs = CORBA::Codeset::create (cs_name);
	if (!cs) {
	    MICODebug::instance()->printer()
		<< "unknown fallback wide char code set: " << cs_name << endl;
	    assert (0);
	}
	CORBA::Codeset::set_special_cs (CORBA::Codeset::FallbackWCS, cs);


	// install code set info in ior template
	if (!disable) {
	    MICO::MultiCompProfile *mcp =
		new MICO::MultiCompProfile (CORBA::MultiComponent());

	    mcp->components()->add_component (new MICO::CodesetComponent (
		CORBA::Codeset::special_cs(CORBA::Codeset::NativeCS)->id(),
		CORBA::Codeset::special_cs(CORBA::Codeset::NativeWCS)->id(),
		vector<MICO::CodesetComponent::CodeSetId>(),
		vector<MICO::CodesetComponent::CodeSetId>()));
	    orb->ior_template()->add_profile (mcp);
	}

	return Interceptor::INVOKE_CONTINUE;
    }
} __cs_init;

void
CORBA::Codeset::_init ()
{
  __cs_init;
}

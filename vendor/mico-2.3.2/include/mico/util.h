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

#ifndef __mico_util_h__
#define __mico_util_h__

#include <ctype.h>
#include <iostream.h>
#include <fstream.h>
#include <CORBA.h>
#include <mico/os-misc.h>


class MICODebug {
    CORBA::ULong _level;
    ostream *_out;
    ostream *_null;
    static MICODebug *_instance;
public:
    MICODebug (const string &file, CORBA::ULong level = 0);
    MICODebug (CORBA::ULong level = 0);
    ~MICODebug ();

    void level (CORBA::ULong);
    CORBA::ULong level () const;

    ostream &printer ();
    ostream &debugger ();
    ostream &tracer ();
    ostream &dumper ();

    static MICODebug *instance ();
};


class MICOGetOpt {
public:
    typedef map<string, string, less<string> > OptMap;
    typedef vector<pair<string,string> > OptVec;
private:
    OptMap _in_opts;
    OptVec _out_opts;

    CORBA::Boolean parse (const vector<string> &args, vector<int> &erase,
			  CORBA::Boolean ignore = FALSE);
public:
    MICOGetOpt (const OptMap &opts);
    ~MICOGetOpt ();

    CORBA::Boolean parse (int &argc, char *argv[],
			  CORBA::Boolean ignore = FALSE);
    CORBA::Boolean parse (const vector<string> &args,
			  CORBA::Boolean ignore = FALSE);
    CORBA::Boolean parse (const string &filename,
			  CORBA::Boolean ignore = FALSE);

    const OptVec &opts () const;
};

template<class V>
inline CORBA::Long
mico_vec_compare (V v1, V v2)
{
    int len = v1.size() < v2.size() ? v1.size() : v2.size();
    for (int i = 0; i < len; ++i) {
	if (v1[i] < v2[i])
	    return -1;
	if (v2[i] < v1[i])
	    return 1;
    }
    return v1.size() - v2.size();
}

static inline CORBA::Long
mico_key_compare (const CORBA::Octet *k1, const CORBA::Octet *k2,
		  CORBA::Long len)
{
    while (--len >= 0) {
	if (*k1 != *k2)
	    return (CORBA::Long)*k1 - (CORBA::Long)*k2;
	++k1;
	++k2;
    }
    return 0;
}


static inline CORBA::Octet
mico_from_xdigit (CORBA::Octet c)
{
    c = tolower (c);
    assert (isxdigit (c));
    return isdigit (c) ? c - '0' : c - 'a' + 10;
}

static inline CORBA::Octet
mico_to_xdigit (CORBA::Octet o)
{
    static const char *xdigits = "0123456789abcdef";
    assert (o < 16);
    return xdigits[o];
}

extern void mico_ieee2float (CORBA::Octet ieee[4], CORBA::Float &f);
extern void mico_float2ieee (CORBA::Octet ieee[4], CORBA::Float  f);
extern void mico_ieee2double (CORBA::Octet ieee[8], CORBA::Double &f);
extern void mico_double2ieee (CORBA::Octet ieee[8], CORBA::Double  f);
extern void mico_ieee2ldouble (CORBA::Octet ieee[16], CORBA::LongDouble &f);
extern void mico_ldouble2ieee (CORBA::Octet ieee[16], CORBA::LongDouble  f);
extern CORBA::Boolean mico_fnmatch (const char *repoid, const char *patt);

extern string xstrerror (int);
extern string xdec (int);
extern string xdec (long);
extern string xdec (OSMisc::longlong);
extern string xdec (unsigned int);
extern string xdec (unsigned long);
extern string xdec (OSMisc::ulonglong);

extern size_t xwcslen (const wchar_t *);
extern int xwcscmp (const wchar_t *, const wchar_t *);
extern wchar_t *xwcscpy (wchar_t *, const wchar_t *);
extern wchar_t *xwcsncpy (wchar_t *, const wchar_t *, size_t);

extern char * mico_url_encode (const CORBA::Octet *, CORBA::ULong);
extern CORBA::Octet * mico_url_decode (const char *, CORBA::ULong &);

#ifndef __MINGW32__
extern 
#endif
CORBA::ULong mico_string_hash (const char *s, CORBA::ULong max);

#ifndef HAVE_STRERROR_PROTO
extern "C" char *strerror (int);
#endif

#ifndef HAVE_GETHOSTNAME_PROTO
extern "C" int gethostname (char *, size_t);
#endif

#ifndef HAVE_FINITE_PROTO
extern "C" int finite (double);
#endif

#ifndef HAVE_FTIME_PROTO
extern "C" int ftime (struct timeb *);
#endif

#endif // __mico_util_h__

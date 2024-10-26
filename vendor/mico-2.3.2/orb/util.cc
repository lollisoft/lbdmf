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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <algorithm>
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>
#include <mico/impl.h>
#include <mico/template_impl.h>
#include <mico/util.h>
#include <mico/os-misc.h>
#include <mico/os-math.h>
#ifdef USE_MEMTRACE
#include <mico/memtrace.h>
#endif

/******************************* assert *******************************/


void
mico_assert (const char *file, int line)
{
    cout << file << ":" << line << ": assertion failed" << endl;
#ifdef USE_MEMTRACE
    MemTrace_SelfTrace (stderr);
#endif
    abort ();
}


/****************************** strerror ******************************/


#ifndef HAVE_STRERROR
extern "C" {

    extern char *sys_errlist[];
    extern int sys_nerr;

    char *
    strerror (int err)
    {
	assert (err >= 0 && err < sys_nerr);
	return sys_errlist[err];
    }
}
#endif

string
xstrerror (int err)
{
    char *cp = strerror (err);

    if (cp)
        return string(cp);

    // Cygnus CDK returnes (char *)0 for some errnos
    string lasterr;
    lasterr = "error ";
    lasterr += xdec (errno);
    return lasterr;
}

string
xdec (int i)
{
    ostrstream ostr;
    ostr << i << ends;

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

string
xdec (long i)
{
    ostrstream ostr;
    ostr << i << ends;

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

string
xdec (OSMisc::longlong i)
{
    ostrstream ostr;
#ifdef _WINDOWS
    ostr << long(i) << ends;   //XXX
#else
    ostr << i << ends;
#endif

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

string
xdec (unsigned int i)
{
    ostrstream ostr;
    ostr << i << ends;

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

string
xdec (unsigned long i)
{
    ostrstream ostr;
    ostr << i << ends;

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

string
xdec (OSMisc::ulonglong i)
{
    ostrstream ostr;

#ifdef _WINDOWS
#ifdef __MINGW32__
    ostr << i << ends;
#else
    ostr << unsigned long(i) << ends; //XXX
#endif
#else
    ostr << i << ends;
#endif

    string s = ostr.str();
    ostr.rdbuf()->freeze (0);
    return s;
}

size_t
xwcslen (const wchar_t *s)
{
    size_t len = 0;
    while (*s++)
	++len;
    return len;
}

int
xwcscmp (const wchar_t *s1, const wchar_t *s2)
{
    while (*s1 && *s1 == *s2) {
	++s1; ++s2;
    }
    if (*s1 == *s2)
	return 0;
    if (*s1 < *s2)
	return -1;
    return 1;
}

wchar_t *
xwcscpy (wchar_t *_d, const wchar_t *s)
{
    wchar_t *d = _d;

    while ((*d++ = *s++))
	;
    return _d;
}

wchar_t *
xwcsncpy (wchar_t *_d, const wchar_t *s, size_t n)
{
    wchar_t *d = _d;

    int i = (int)n;
    while (--i >= 0 && (*d++ = *s++))
	;
    return _d;
}

char *
mico_url_encode (const CORBA::Octet * ptr, CORBA::ULong len)
{
  string res;

  for (CORBA::ULong i=0; i<len; i++) {
    // US-ASCII alphanumeric characters are not escaped
    if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') ||
	(*ptr >= '0' && *ptr <= '9')) {
      res += *ptr++;
      continue;
    }
    // Also not escaped
    switch (*ptr) {
    case ';':
    case '/':
    case ':':
    case '?':
    case '@':
    case '&':
    case '=':
    case '+':
    case '$':
    case ',':
    case '-':
    case '.':
    case '!':
    case '~':
    case '*':
    case '\'':
    case '(':
    case ')':
      res += *ptr++;
      break;

    default:
      {
	CORBA::Octet x = *ptr++;
	res += '%';
	res += (char) mico_to_xdigit (x>>4);
	res += (char) mico_to_xdigit (x&15);
      }
    }
  }

  return CORBA::string_dup (res.c_str());
}

CORBA::Octet *
mico_url_decode (const char * ptr, CORBA::ULong & len)
{
  CORBA::Octet * str = (CORBA::Octet *) CORBA::string_alloc (strlen (ptr));
  CORBA::Octet * res = str;
  
  len = 0;

  while (*ptr) {
    if (*ptr == '%') {
      if ((ptr[1] < '0' || ptr[1] > '9') && (ptr[1] < 'a' || ptr[1] > 'f') ||
	  (ptr[2] < '0' || ptr[2] > '9') && (ptr[2] < 'a' || ptr[2] > 'f')) {
	CORBA::string_free ((char *) str);
	return NULL;
      }
      *res = (char) (mico_from_xdigit(ptr[1])<<4 | mico_from_xdigit(ptr[2]));
      ptr += 3;
    }
    else {
      *res = *ptr++;
    }
    res++;
    len++;
  }

  return str;
}

CORBA::ULong
mico_string_hash (const char *s, CORBA::ULong max)
{
    if (max == 0)
	return 0;

    CORBA::ULong g, v = 0;
    while (*s) {
	v = (v << 4) + *s++;
	if ((g = v & 0xf0000000)) {
	    v = v ^ (g >> 24);
	    v = v ^ g;
	}
    }
    return v % max;
}


/************************** MethodDispatcher **************************/


CORBA::InterfaceDispatcher::~InterfaceDispatcher ()
{
}

CORBA::MethodDispatcher::~MethodDispatcher ()
{
    for (mico_vec_size_type i = 0; i < _dispatcher.size(); ++i)
	delete _dispatcher[i];
}

void
CORBA::MethodDispatcher::register_dispatcher (InterfaceDispatcher *disp)
{
    _dispatcher.push_back (disp);
}

void
CORBA::MethodDispatcher::invoke (CORBA::ServerRequest_ptr _req,
				 CORBA::Environment &_env)
{
    for (mico_vec_size_type i=0; i < _dispatcher.size(); ++i) {
	if (_dispatcher[i]->dispatch (_req, _env))
	    return;
    }
    _req->exception (new BAD_OPERATION);
}


/*********************** StaticMethodDispatcher ************************/


CORBA::StaticInterfaceDispatcher::~StaticInterfaceDispatcher ()
{
}

CORBA::StaticMethodDispatcher::~StaticMethodDispatcher ()
{
    for (mico_vec_size_type i = 0; i < _dispatcher.size(); ++i)
	delete _dispatcher[i];
}

void
CORBA::StaticMethodDispatcher::
                    register_dispatcher (StaticInterfaceDispatcher *disp)
{
    _dispatcher.push_back (disp);
}

void
CORBA::StaticMethodDispatcher::invoke (CORBA::StaticServerRequest_ptr _req,
				       CORBA::Environment &_env)
{
    for (mico_vec_size_type i=0; i < _dispatcher.size(); ++i) {
	if (_dispatcher[i]->dispatch (_req, _env))
	    return;
    }
    _req->set_exception (new BAD_OPERATION);
    _req->write_results();
}


/***************************** MICODebug ******************************/


MICODebug *MICODebug::_instance = 0;

MICODebug::MICODebug (const string &file, CORBA::ULong level)
{
    assert (!_instance);
    _instance = this;

    _level = level;
    _out = new ofstream (file.c_str());
    _null = new ofstream ("/dev/null");

    assert (_out);
    assert (_null);
}

MICODebug::MICODebug (CORBA::ULong level)
{
    assert (!_instance);
    _instance = this;

    _level = level;
    _out = &cerr;
    _null = new ofstream ("/dev/null");

    assert (_null);
}

MICODebug::~MICODebug ()
{
    _instance = 0;

    if (_out != &cerr)
	delete _out;
    delete _null;
}

void
MICODebug::level (CORBA::ULong l)
{
    _level = l;
}

CORBA::ULong
MICODebug::level () const
{
    return _level;
}

ostream &
MICODebug::printer ()
{
    return *_out;
}

ostream &
MICODebug::debugger ()
{
    return _level > 0 ? *_out : *_null;
}

ostream &
MICODebug::tracer ()
{
    return _level > 1 ? *_out : *_null;
}

ostream &
MICODebug::dumper ()
{
    return _level > 2 ? *_out : *_null;
}

MICODebug *
MICODebug::instance ()
{
    assert (_instance);
    return _instance;
}


/***************************** MICODebug ******************************/


MICOGetOpt::MICOGetOpt (const OptMap &opts)
    : _in_opts (opts)
{
}

MICOGetOpt::~MICOGetOpt ()
{
}

CORBA::Boolean
MICOGetOpt::parse (int &argc, char *argv[], CORBA::Boolean ignore)
{
    vector<int> erase;
    vector<string> args;

    int i;
    for (i = 1; i < argc; ++i)
	args.push_back (argv[i]);
    if (!parse (args, erase, ignore))
	return FALSE;

    int nargc = 0;
    for (i = 0; i < argc; ++i) {
	if (erase.size() > 0 && i == erase[0]+1) {
	    erase.erase (erase.begin());
	} else {
	    argv[nargc++] = argv[i];
	}
    }
    if (nargc < argc)
	argv[nargc] = 0;
    argc = nargc;

    return TRUE;
}

CORBA::Boolean
MICOGetOpt::parse (const vector<string> &argv, vector<int> &erase,
		   CORBA::Boolean ignore)
{
    for (mico_vec_size_type i = 0; i < argv.size(); ++i) {
	string arg = argv[i];
	if (arg == "--") {
	    erase.push_back (i);
	    break;
	}
	if (!ignore && (arg.size() == 0 || arg[0] != '-')) {
	    break;
	}
	OptMap::const_iterator it = _in_opts.find (arg);
	if (it == _in_opts.end()) {
	    int pos = 0;
	    if (arg.length() > 2) {
		// -Oval ??
		arg = arg.substr (0, 2);
		pos = 2;
		it = _in_opts.find (arg);
	    }
	    if (it == _in_opts.end() && (pos = argv[i].find ("=")) > 0) {
		// --long-opt=something ??
		arg = argv[i].substr (0, pos);
		++pos;
		it = _in_opts.find (arg);
	    }
	    if (it != _in_opts.end()) {
		if ((*it).second.length() == 0) {
		    cerr << "unexpected argument for option " << arg << endl;
		    return FALSE;
		}
		_out_opts.push_back (make_pair (arg, argv[i].substr (pos)));
		erase.push_back (i);
	    } else if (!ignore) {
		cerr << "unknown option: " << argv[i] << endl;
		return FALSE;
	    }
	} else {
	    erase.push_back (i);
	    if ((*it).second.length() > 0) {
		// -O val
		// --long-opt val
		if (++i == argv.size()) {
		    cerr << "missing argument for option " << arg << endl;
		    return FALSE;
		}
		_out_opts.push_back (make_pair (arg, argv[i]));
		erase.push_back (i);
	    } else {
		// -O
		// --long-opt
		_out_opts.push_back (make_pair (arg, string("")));
	    }
	}
    }
    return TRUE;
}

CORBA::Boolean
MICOGetOpt::parse (const vector<string> &argv, CORBA::Boolean ignore)
{
    vector<int> erase;
    return parse (argv, erase, ignore);
}

CORBA::Boolean
MICOGetOpt::parse (const string &_filename, CORBA::Boolean ignore)
{
    string fn = _filename;

    if (fn[0] == '~') {
        char *s = getenv ("HOME");
        if (!s) {
            return TRUE;
        }
        string home = s;
        fn.replace (0, 1, home);
    }
    ifstream in (fn.c_str());
    if (!in)
	return TRUE;

    char line[10000], *lptr, *tok;
    vector<string> argv;

    while (42) {
	if (in.getline(line, sizeof(line)).eof())
	    break;
	if (!line[0])
	    continue;
	lptr = line;
	while ((tok = ::strtok (lptr, " \t"))) {
	    if (lptr && *tok == '#')
		break;
	    argv.push_back (tok);
	    lptr = 0;
	}
    }
    return parse (argv, ignore);
}

const MICOGetOpt::OptVec &
MICOGetOpt::opts () const
{
    return _out_opts;
}


/************************** repo id matcher ***************************/


CORBA::Boolean
mico_fnmatch (const char *s, const char *p)
{
    register int scc;
    int ok, lc;
    int c, cc;

    for (;;) {
	scc = *s++ & 0177;
	switch ((c = *p++)) {
	case '[':
	    ok = 0;
	    lc = 077777;
	    while ((cc = *p++)) {
		if (cc == ']') {
		    if (ok)
			break;
		    return FALSE;
		}
		if (cc == '-') {
		    if (lc <= scc && scc <= *p++)
			ok++;
		} else
		    if (scc == (lc = cc))
			ok++;
	    }
	    if (cc == 0)
		if (ok)
		    p--;
		else
		    return FALSE;
	    continue;
	    
	case '*':
	    if (!*p)
		return TRUE;
	    s--;
	    do {
		if (mico_fnmatch(s, p))
		    return TRUE;
	    } while (*s++);
	    return FALSE;
			
	case 0:
	    return (scc == 0);

	default:
	    if (c != scc)
		return FALSE;
	    continue;

	case '?':
	    if (scc == 0)
		return FALSE;
	    continue;
	}
    }
}


/****************************** Process ******************************/


MICO::Process::~Process ()
{
}

MICO::ProcessCallback::~ProcessCallback ()
{
}


/***************************** SharedLib ******************************/


CORBA::Boolean
MICO::SharedLib::init ()
{
#ifdef HAVE_EXPLICIT_CTORS
    void (*gblctor) () = (void (*) ())symbol ("_GLOBAL__DI");
    assert (gblctor);
    (*gblctor) ();
#endif
    CORBA::Boolean (*initfn) (const char *) =
	(CORBA::Boolean (*) (const char *))symbol ("mico_module_init");
    if (!initfn)
	return FALSE;
    return (*initfn) (MICO_VERSION);
}

void
MICO::SharedLib::exit ()
{
    void (*exitfn) () = (void (*) ())symbol ("mico_module_exit");
    if (exitfn)
	(*exitfn) ();
#ifdef HAVE_EXPLICIT_CTORS
    void (*gbldtor) () = (void (*) ())symbol ("_GLOBAL__DD");
    assert (gbldtor);
    (*gbldtor) ();
#endif
}

MICO::SharedLib::~SharedLib ()
{
}


/********************** Floating point converters *********************/


struct IeeeLDouble {
#ifdef HAVE_BYTEORDER_BE
    unsigned int s : 1;
    unsigned int e : 15;
    unsigned int f1 : 16;
    unsigned int f2 : 32;
    unsigned int f3 : 32;
    unsigned int f4 : 32;
#else
    unsigned int f4 : 32;
    unsigned int f3 : 32;
    unsigned int f2 : 32;
    unsigned int f1 : 16;
    unsigned int e : 15;
    unsigned int s : 1;
#endif
};

#define LDBL_EXP_BITS  15
#define LDBL_EXP_BIAS  16384
#define LDBL_EXP_MAX   ((1L << LDBL_EXP_BITS) - 1 - LDBL_EXP_BIAS)
#define LDBL_EXP_MIN   (1 - LDBL_EXP_BIAS)
#define LDBL_FRC1_BITS 16
#define LDBL_FRC2_BITS (LDBL_FRC1_BITS+32)
#define LDBL_FRC3_BITS (LDBL_FRC2_BITS+32)
#define LDBL_FRC_BITS  (LDBL_FRC3_BITS+32)

struct IeeeDouble {
#ifdef HAVE_BYTEORDER_BE
    unsigned int s : 1;
    unsigned int e : 11;
    unsigned int f1 : 20;
    unsigned int f2 : 32;
#else
    unsigned int f2 : 32;
    unsigned int f1 : 20;
    unsigned int e : 11;
    unsigned int s : 1;
#endif
};

#define DBL_EXP_BITS  11
#define DBL_EXP_BIAS  1023
#define DBL_EXP_MAX   ((1L << DBL_EXP_BITS) - 1 - DBL_EXP_BIAS)
#define DBL_EXP_MIN   (1 - DBL_EXP_BIAS)
#define DBL_FRC1_BITS 20
#define DBL_FRC2_BITS 32
#define DBL_FRC_BITS  (DBL_FRC1_BITS + DBL_FRC2_BITS)

struct IeeeFloat {
#ifdef HAVE_BYTEORDER_BE
    unsigned int s : 1;
    unsigned int e : 8;
    unsigned int f : 23;
#else
    unsigned int f : 23;
    unsigned int e : 8;
    unsigned int s : 1;
#endif
};

#define FLT_EXP_BITS 8
#define FLT_EXP_BIAS 127
#define FLT_EXP_MAX  ((1L << FLT_EXP_BITS) - 1 - FLT_EXP_BIAS)
#define FLT_EXP_MIN  (1 - FLT_EXP_BIAS)
#define FLT_FRC_BITS 23


void
mico_ieee2ldouble (CORBA::Octet ieee[16], CORBA::LongDouble &d)
{
    IeeeLDouble &ie = (IeeeLDouble &)*ieee;

    if (ie.e == 0) {
	if (ie.f1 == 0 && ie.f2 == 0 && ie.f3 == 0 && ie.f4 == 0) {
	    // zero
	    d = 0.0;
	} else {
	    // denormalized number
	    d  = ldexpl ((long double)ie.f1, -LDBL_FRC1_BITS + LDBL_EXP_MIN);
	    d += ldexpl ((long double)ie.f2, -LDBL_FRC2_BITS + LDBL_EXP_MIN);
	    d += ldexpl ((long double)ie.f3, -LDBL_FRC3_BITS + LDBL_EXP_MIN);
	    d += ldexpl ((long double)ie.f4, -LDBL_FRC_BITS  + LDBL_EXP_MIN);
	    if (ie.s)
		d = -d;
	}
    } else if (ie.e == LDBL_EXP_MAX + LDBL_EXP_BIAS) {
	if (ie.f1 == 0 && ie.f2 == 0 && ie.f3 == 0 && ie.f4 == 0) {
	    // +/- infinity
	    d = OSMath::infinityl (ie.s);
	} else {
	    // not a number
	    d = OSMath::nanl ();
	}
    } else {
	// normalized number
	d = ldexpl (ldexpl ((long double)ie.f1, -LDBL_FRC1_BITS) +
		    ldexpl ((long double)ie.f2, -LDBL_FRC2_BITS) +
		    ldexpl ((long double)ie.f3, -LDBL_FRC3_BITS) +
		    ldexpl ((long double)ie.f4, -LDBL_FRC_BITS) +
                    1.0,
		    ie.e - LDBL_EXP_BIAS);
	if (ie.s)
	    d = -d;
    }
}

void
mico_ldouble2ieee (CORBA::Octet ieee[16], CORBA::LongDouble d)
{
    IeeeLDouble &ie = (IeeeLDouble &)*ieee;

    if (OSMath::is_nanl (d)) {
	// XXX not a number (what is signaling NAN ???)
	ie.s = 0;
	ie.e = LDBL_EXP_MAX + LDBL_EXP_BIAS;
	ie.f1 = 1;
	ie.f2 = 1;
	ie.f3 = 1;
	ie.f4 = 1;
    } else if (OSMath::is_infinityl (d)) {
	// +/- infinity
	ie.s = (d < 0);
	ie.e = LDBL_EXP_MAX + LDBL_EXP_BIAS;
	ie.f1 = 0;
	ie.f2 = 0;
	ie.f3 = 0;
	ie.f4 = 0;
    } else if (d == 0.0) {
	// zero
	ie.s = 0;
	ie.e = 0;
	ie.f1 = 0;
	ie.f2 = 0;
	ie.f3 = 0;
	ie.f4 = 0;
    } else {
	// finite number
	int exp;
	long double frac = frexpl (fabsl (d), &exp);

	while (frac < 1.0 && exp >= LDBL_EXP_MIN) {
	    frac = ldexpl (frac, 1);
	    --exp;
	}
	if (exp < LDBL_EXP_MIN) {
	    // denormalized number (or zero)
	    frac = ldexpl (frac, exp - LDBL_EXP_MIN);
	    exp = 0;
	} else {
	    // normalized number
	    assert (1.0 <= frac && frac < 2.0);
	    assert (LDBL_EXP_MIN <= exp && exp <= LDBL_EXP_MAX);

	    exp += LDBL_EXP_BIAS;
            frac -= 1.0;
	}
	ie.s = (d < 0);
	ie.e = exp;
	ie.f1 = (unsigned long)ldexpl (frac, LDBL_FRC1_BITS);
	ie.f2 = (unsigned long)ldexpl (frac, LDBL_FRC2_BITS);
	ie.f3 = (unsigned long)ldexpl (frac, LDBL_FRC3_BITS);
	ie.f4 = (unsigned long)ldexpl (frac, LDBL_FRC_BITS);
    }
}

void
mico_ieee2double (CORBA::Octet ieee[8], CORBA::Double &d)
{
    IeeeDouble &ie = (IeeeDouble &)*ieee;

    if (ie.e == 0) {
	if (ie.f1 == 0 && ie.f2 == 0) {
	    // zero
	    d = 0.0;
	} else {
	    // denormalized number
	    d  = ldexp ((double)ie.f1, -DBL_FRC1_BITS + DBL_EXP_MIN);
	    d += ldexp ((double)ie.f2, -DBL_FRC_BITS  + DBL_EXP_MIN);
	    if (ie.s)
		d = -d;
	}
    } else if (ie.e == DBL_EXP_MAX + DBL_EXP_BIAS) {
	if (ie.f1 == 0 && ie.f2 == 0) {
	    // +/- infinity
	    d = OSMath::infinity (ie.s);
	} else {
	    // not a number
	    d = OSMath::nan ();
	}
    } else {
	// normalized number
	d = ldexp (ldexp ((double)ie.f1, -DBL_FRC1_BITS) +
		   ldexp ((double)ie.f2, -DBL_FRC_BITS) +
		   1.0,
		   ie.e - DBL_EXP_BIAS);
	if (ie.s)
	    d = -d;
    }
}

void
mico_double2ieee (CORBA::Octet ieee[8], CORBA::Double d)
{
    IeeeDouble &ie = (IeeeDouble &)*ieee;

    if (OSMath::is_nan (d)) {
	// XXX not a number (what is signaling NAN ???)
	ie.s = 0;
	ie.e = DBL_EXP_MAX + DBL_EXP_BIAS;
	ie.f1 = 1;
	ie.f2 = 1;
    } else if (OSMath::is_infinity (d)) {
	// +/- infinity
	ie.s = (d < 0);
	ie.e = DBL_EXP_MAX + DBL_EXP_BIAS;
	ie.f1 = 0;
	ie.f2 = 0;
    } else if (d == 0.0) {
	// zero
	ie.s = 0;
	ie.e = 0;
	ie.f1 = 0;
	ie.f2 = 0;
    } else {
	// finite number
	int exp;
	double frac = frexp (fabs (d), &exp);

	while (frac < 1.0 && exp >= DBL_EXP_MIN) {
	    frac = ldexp (frac, 1);
	    --exp;
	}
	if (exp < DBL_EXP_MIN) {
	    // denormalized number (or zero)
	    frac = ldexp (frac, exp - DBL_EXP_MIN);
	    exp = 0;
	} else {
	    // normalized number
	    assert (1.0 <= frac && frac < 2.0);
	    assert (DBL_EXP_MIN <= exp && exp <= DBL_EXP_MAX);

	    exp += DBL_EXP_BIAS;
	    frac -= 1.0;
	}
	ie.s = (d < 0);
	ie.e = exp;
	ie.f1 = (unsigned long)ldexp (frac, DBL_FRC1_BITS);
	ie.f2 = (unsigned long)ldexp (frac, DBL_FRC_BITS);
    }
}

void
mico_ieee2float (CORBA::Octet ieee[4], CORBA::Float &f)
{
    IeeeFloat &ie = (IeeeFloat &)*ieee;

    if (ie.e == 0) {
	if (ie.f == 0) {
	    // zero
	    f = 0.0;
	} else {
	    // denormalized number
	    f = ldexp ((double)ie.f, -FLT_FRC_BITS + FLT_EXP_MIN);
	    if (ie.s)
		f = -f;
	}
    } else if (ie.e == FLT_EXP_MAX + FLT_EXP_BIAS) {
	if (ie.f == 0) {
	    // +/- infinity
	    f = OSMath::infinity (ie.s);
	} else {
	    // not a number
	    f = OSMath::nan ();
	}
    } else {
	// normalized number
	f = ldexp (ldexp ((double)ie.f, -FLT_FRC_BITS) + 1.0,
		   ie.e - FLT_EXP_BIAS);
	if (ie.s)
	    f = -f;
    }
}

void
mico_float2ieee (CORBA::Octet ieee[4], CORBA::Float f)
{
    IeeeFloat &ie = (IeeeFloat &)*ieee;

    if (OSMath::is_nan (f)) {
	// XXX not a number (what is signaling NAN ???)
	ie.s = 0;
	ie.e = FLT_EXP_MAX + FLT_EXP_BIAS;
	ie.f = 1;
    } else if (OSMath::is_infinity (f)) {
	// +/- infinity
	ie.s = (f < 0);
	ie.e = FLT_EXP_MAX + FLT_EXP_BIAS;
	ie.f = 0;
    } else if (f == 0.0) {
	// zero
	ie.s = 0;
	ie.e = 0;
	ie.f = 0;
    } else {
	// finite number
	int exp;
	double frac = frexp (fabs (f), &exp);

	while (frac < 1.0 && exp >= FLT_EXP_MIN) {
	    frac = ldexp (frac, 1);
	    --exp;
	}
	if (exp < FLT_EXP_MIN) {
	    // denormalized number (or zero)
	    frac = ldexp (frac, exp - FLT_EXP_MIN);
	    exp = 0;
	} else {
	    // normalized number
	    assert (1.0 <= frac && frac < 2.0);
	    assert (FLT_EXP_MIN <= exp && exp <= FLT_EXP_MAX);

	    exp += FLT_EXP_BIAS;
	    frac -= 1.0;
	}
	ie.s = (f < 0);
	ie.e = exp;
	ie.f = (unsigned long)ldexp (frac, FLT_FRC_BITS);
    }
}

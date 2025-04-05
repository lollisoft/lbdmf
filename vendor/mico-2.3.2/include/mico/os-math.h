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

#ifndef __mico_os_math_h__
#define __mico_os_math_h__

#ifdef _WINDOWS

#include <math.h>
#include <limits>
#include <fpieee.h>

struct OSMath {
    static MICO_Double infinity (MICO_Boolean neg)
    {
	static MICO_Double minus_inf = 0, plus_inf = 0;
	if (plus_inf == 0) {
	    plus_inf = numeric_limits<double>::infinity();
	    minus_inf = -plus_inf;
	}
	return neg ? minus_inf : plus_inf;
    }

    static MICO_Double nan ()
    {
	static MICO_Double not_a_number = 0;
	if (not_a_number == 0) {
	    not_a_number = numeric_limits<double>::quiet_NaN();
	}
	return not_a_number;
    }

    static MICO_Boolean is_infinity (MICO_Double d)
    {
	if (!_finite (d) && !_isnan (d)) 
	    return TRUE;
	else
	    return FALSE;
    }

    static MICO_Boolean is_nan (MICO_Double d)
    {
	if (_isnan (d))
	    return TRUE;
	else 
	    return FALSE;
    }

    static MICO_LongDouble infinityl (MICO_Boolean neg)
    {
	static MICO_LongDouble minus_inf = 0, plus_inf = 0;
	if (plus_inf == 0) {
	    plus_inf = numeric_limits<long double>::infinity();
	    minus_inf = -plus_inf;
	}
	return neg ? minus_inf : plus_inf;
    }

    static MICO_LongDouble nanl ()
    {
	static MICO_LongDouble not_a_number = 0;
	if (not_a_number == 0) {
	    not_a_number = numeric_limits<long double>::quiet_NaN();
	}
	return not_a_number;
    }

    static MICO_Boolean is_infinityl (MICO_LongDouble d)
    {
	if (!_finite (d) && !_isnan (d)) 
	    return TRUE;
	else
	    return FALSE;
    }

    static MICO_Boolean is_nanl (MICO_LongDouble d)
    {
	if (_isnan (d))
	    return TRUE;
	else 
	    return FALSE;
    }
};

#else // _WINDOWS

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#if !defined(__GNUG__) || !defined(__sgi)
// conflict for initstate ()
#include <math.h>
#endif

#ifdef HAVE_FLOAT_H
#include <float.h>
#endif
#ifdef HAVE_IEEEFP_H
#include <ieeefp.h>
#endif
#ifdef HAVE_SUNMATH_H
#include <sunmath.h>
#endif

#include <mico/lmath.h>

class OSMath {
    static MICO_Double _infinity;
    static MICO_LongDouble _long_infinity;
    static MICO_Double _notanumber;
    static MICO_LongDouble _long_notanumber;
public:
    static MICO_Double infinity (MICO_Boolean neg)
    {
#if defined(HAVE_INFNAN)
	return infnan (neg ? -ERANGE : ERANGE);
#else
	if (_infinity == 0) {
	    sigset_t fpe;
	    sigemptyset (&fpe);
	    sigaddset (&fpe, SIGFPE);
	    sigprocmask (SIG_BLOCK, &fpe, NULL);
	    // XXX assumption: +/- 1/0 == +/- infinity
	    _infinity = -1 / floor (0.1);
	    sigprocmask (SIG_UNBLOCK, &fpe, NULL);
	}
	return neg ? -_infinity : _infinity;
#endif
    }

    static MICO_Double nan ()
    {
#if defined(HAVE_INFNAN)
	return infnan (0);
#else
	if (_notanumber == 0) {
	    sigset_t fpe;
	    sigemptyset (&fpe);
	    sigaddset (&fpe, SIGFPE);
	    sigprocmask (SIG_BLOCK, &fpe, NULL);
	    // XXX assumption: arcsin (2.0) == NAN
	    _notanumber = asin (2.0);
	    sigprocmask (SIG_UNBLOCK, &fpe, NULL);
	}
	return _notanumber;
#endif
    }

    static MICO_Boolean is_infinity (MICO_Double d)
    {
#if defined(HAVE_ISINF)
	return isinf (d);
#elif defined(HAVE_FINITE) && defined(HAVE_ISNAN)
	return !finite (d) && !isnan (d);
#else
	return d == infinity (TRUE) || d == infinity (FALSE);
#endif
    }

    static MICO_Boolean is_nan (MICO_Double d)
    {
#if defined(HAVE_ISNAN)
	return isnan (d);
#else
	// d == mk_nan() does not work ...
	assert (0);
#endif
    }

    static MICO_LongDouble infinityl (MICO_Boolean neg)
    {
#if defined(HAVE_INFNANL)
	return infnanl (neg ? -ERANGE : ERANGE);
#else
	if (_long_infinity == 0) {
	    sigset_t fpe;
	    sigemptyset (&fpe);
	    sigaddset (&fpe, SIGFPE);
	    sigprocmask (SIG_BLOCK, &fpe, NULL);
	    // XXX assumption: +/- 1/0 == +/- infinity
	    _long_infinity = (long double)-1 / floor (0.1);
	    sigprocmask (SIG_UNBLOCK, &fpe, NULL);
	}
	return neg ? -_long_infinity : _long_infinity;
#endif
    }

    static MICO_LongDouble nanl ()
    {
#if defined(HAVE_INFNANL)
	return infnanl (0);
#else
	if (_long_notanumber == 0) {
	    sigset_t fpe;
	    sigemptyset (&fpe);
	    sigaddset (&fpe, SIGFPE);
	    sigprocmask (SIG_BLOCK, &fpe, NULL);
	    // XXX assumption: arcsin (2.0) == NAN
	    _long_notanumber = asinl (2.0);
	    sigprocmask (SIG_UNBLOCK, &fpe, NULL);
	}
	return _long_notanumber;
#endif
    }

    static MICO_Boolean is_infinityl (MICO_LongDouble d)
    {
#if defined(HAVE_ISINFL)
	return isinfl (d);
#else
	return d == infinityl (TRUE) || d == infinityl (FALSE);
#endif
    }

    static MICO_Boolean is_nanl (MICO_LongDouble d)
    {
#if defined(HAVE_ISNANL)
	return isnanl (d);
#else
	// d == mk_nan() does not work ...
	assert (0);
#endif
    }
};

#endif // _WINDOWS

#endif // __mico_os_math_h__

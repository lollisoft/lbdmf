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

#include <CORBA-SMALL.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <iomanip.h>
#include <mico/template_impl.h>

CORBA::Buffer::Buffer (void *b)
{
    // readonly buffer with given contents
    _len = _wptr = 0x7fffffff;
    _rptr = 0;
    _ralignbase = _walignbase = 0;
    _buf = (Octet *)b;
    _readonly = TRUE;
}

CORBA::Buffer::Buffer (ULong sz)
{
    // read/write buffer with given initial size
    if (sz < MINSIZE)
        sz = MINSIZE;
    _buf = alloc (sz);
    _len = sz;
    _rptr = _wptr = 0;
    _ralignbase = _walignbase = 0;
    _readonly = FALSE;
}

CORBA::Buffer::Buffer (const Buffer &b)
{
    _buf = alloc (b._len);
    memcpy (_buf, b._buf, b._len);
    _len = b._len;
    _rptr = b._rptr;
    _wptr = b._wptr;
    _ralignbase = b._ralignbase;
    _walignbase = b._walignbase;
    _readonly = FALSE;
}

CORBA::Buffer::~Buffer ()
{
    if (!_readonly)
        free (_buf);
}

CORBA::Buffer &
CORBA::Buffer::operator= (const Buffer &b)
{
    if (this != &b) {
	assert (!_readonly && !b._readonly);
	free (_buf);
	_buf = alloc (b._len);
	memcpy (_buf, b._buf, b._len);
	_len = b._len;
	_rptr = b._rptr;
	_wptr = b._wptr;
	_ralignbase = b._ralignbase;
	_walignbase = b._walignbase;
    }
    return *this;
}

CORBA::Boolean
CORBA::Buffer::operator== (const Buffer &b)
{
    assert (!_readonly && !b._readonly);
    return length() == b.length() && !memcmp (data(), b.data(), length());
}

CORBA::Octet *
CORBA::Buffer::alloc (ULong sz)
{
    Octet *b = (Octet *)::malloc (sz);
    assert (b);
    return b;
}

CORBA::Octet *
CORBA::Buffer::realloc (Octet *b, ULong osz, ULong nsz)
{
    Octet *nb = (Octet *)::realloc ((void *)b, nsz);
    assert (nb);
    return nb;
}

void
CORBA::Buffer::free (Octet *b)
{
    ::free ((void *)b);
}

void
CORBA::Buffer::reset (ULong sz)
{
    _rptr = 0;
    _ralignbase = _walignbase = 0;
    if (!_readonly) {
        _wptr = 0;
        if (sz < MINSIZE)
            sz = MINSIZE;
        if (_len < sz) {
	    free (_buf);
            _buf = alloc (sz);
            _len = sz;
        }
    }
}

void
CORBA::Buffer::resize (ULong needed)
{
    assert (!_readonly);
    if (_wptr + needed > _len) {
        ULong nlen = (_len < RESIZE_THRESH)
            ? (2*_len)
            : (_len + RESIZE_INCREMENT);
        if (_wptr + needed > nlen)
            nlen = _wptr + needed;
	_buf = realloc (_buf, _len, nlen);
        _len = nlen;
    }
}

CORBA::Boolean
CORBA::Buffer::ralign (ULong modulo)
{
    assert (modulo >= 1);
    assert (_rptr >= _ralignbase);
    ULong r = (_rptr - _ralignbase) + modulo - 1;
    r -= r % modulo;
    r += _ralignbase;
    if (r > _wptr)
	return FALSE;
    _rptr = r;
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::peek (void *b, ULong blen)
{
    if (_wptr - _rptr < blen)
        return FALSE;
    memcpy (b, &_buf[_rptr], blen);
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::peek (Octet &o)
{
    if (_wptr == _rptr)
        return FALSE;
    o = _buf[_rptr];
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get (Octet &o)
{
    if (_wptr == _rptr)
        return FALSE;
    o = _buf[_rptr++];
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get (void *b, ULong l)
{
    if (_wptr - _rptr < l)
	return FALSE;
    memcpy (b, &_buf[_rptr], l);
    _rptr += l;
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get1 (void *p)
{
    if (_wptr == _rptr)
        return FALSE;
    *(Octet *)p = _buf[_rptr++];
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get2 (void *p)
{
    assert (_rptr >= _ralignbase);
    ULong r = ((_rptr - _ralignbase + 1) & ~1L) + _ralignbase;
    if (r+2 > _wptr)
	return FALSE;
    _rptr = r;
    // assume that pointers can be cast to long
    if (!((_rptr | (long)p)&1)) {
	*(CORBA::Short *)p = (CORBA::Short &)_buf[_rptr];
	_rptr += 2;
    } else {
	*((Octet * &)p)++ = _buf[_rptr++];
	*(Octet *)p = _buf[_rptr++];
    }
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get4 (void *p)
{
    assert (_rptr >= _ralignbase);
    ULong r = ((_rptr - _ralignbase + 3) & ~3L) + _ralignbase;
    if (r+4 > _wptr)
	return FALSE;
    _rptr = r;
    if (!((_rptr | (long)p)&3)) {
	*(CORBA::Long *)p = (CORBA::Long &)_buf[_rptr];
	_rptr += 4;
    } else {
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*(Octet *)p = _buf[_rptr++];
    }
    return TRUE;
}

CORBA::Boolean
CORBA::Buffer::get8 (void *p)
{
    assert (_rptr >= _ralignbase);
    ULong r = ((_rptr - _ralignbase + 7) & ~7L) + _ralignbase;
    if (r+8 > _wptr)
	return FALSE;
    _rptr = r;
    if (!((_rptr | (long)p)&7)) {
	*(CORBA::LongLong *)p = (CORBA::LongLong &)_buf[_rptr];
	_rptr += 8;
    } else {
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*(Octet *)p = _buf[_rptr++];
    }
    return TRUE;
}

// get 16 bytes with 8 byte alignment
CORBA::Boolean
CORBA::Buffer::get16 (void *p)
{
    assert (_rptr >= _ralignbase);
    ULong r = ((_rptr - _ralignbase + 7) & ~7L) + _ralignbase;
    if (r+16 > _wptr)
	return FALSE;
    _rptr = r;
    if (!((_rptr | (long)p)&7)) {
	*((CORBA::LongLong * &)p)++ = (CORBA::LongLong &)_buf[_rptr];
	_rptr += 8;
	*(CORBA::LongLong *)p = (CORBA::LongLong &)_buf[_rptr];
	_rptr += 8;
    } else {
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*((Octet * &)p)++ = _buf[_rptr++];
	*(Octet *)p = _buf[_rptr++];
    }
    return TRUE;
}

void
CORBA::Buffer::walign (ULong modulo)
{
    assert (!_readonly);
    assert (modulo >= 1);
    assert (_wptr >= _walignbase);
    ULong w = (_wptr - _walignbase) + modulo - 1;
    w -= w % modulo;
    w += _walignbase;
    resize (w - _wptr);
    while (_wptr < w)
	_buf[_wptr++] = 0;
}

void
CORBA::Buffer::replace (const void *o, ULong blen)
{
    assert (!_readonly);
    reset (blen);
    memcpy (&_buf[_wptr], o, blen);
    _wptr += blen;
}

void
CORBA::Buffer::replace (Octet o)
{
    assert (!_readonly);
    reset (1);
    _buf[_wptr++] = o;
}

void
CORBA::Buffer::put (const void *o, ULong l)
{
    assert (!_readonly);
    if (_wptr + l > _len)
	resize (l);
    memcpy (&_buf[_wptr], o, l);
    _wptr += l;
}

void
CORBA::Buffer::put (Octet o)
{
    assert (!_readonly);
    if (_wptr + 1 > _len)
	resize (1);
    _buf[_wptr++] = o;
}

void
CORBA::Buffer::put1 (const void *p)
{
    assert (!_readonly);
    if (_wptr == _len)
	resize (1);
    _buf[_wptr++] = *(const Octet *)p;
}

void
CORBA::Buffer::put2 (const void *p)
{
    assert (!_readonly && _wptr >= _walignbase);
    if (_wptr+3 > _len)
	resize (3);
    CORBA::Octet *b = _buf + _wptr;
    if ((_wptr - _walignbase) & 1L)
	*b++ = 0;
    if (!(((long)b | (long)p)&1)) {
	*((CORBA::Short *&)b)++ = *(const CORBA::Short *)p;
    } else {
	*b++ = *((const Octet * &)p)++;
	*b++ = *(const Octet *)p;
    }
    _wptr = b - _buf;
}

void
CORBA::Buffer::put4 (const void *p)
{
    assert (!_readonly && _wptr >= _walignbase);
    if (_wptr+7 > _len)
	resize (7);
    CORBA::Octet *b = _buf + _wptr;
    switch ((_wptr - _walignbase) & 3L) {
    case 1: *b++ = 0;
    case 2: *b++ = 0;
    case 3: *b++ = 0;
    }
    if (!(((long)b | (long)p)&3)) {
	*((CORBA::Long * &)b)++ = *(const CORBA::Long *)p;
    } else {
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *(const Octet *)p;
    }
    _wptr = b - _buf;
}

void
CORBA::Buffer::put8 (const void *p)
{
    assert (!_readonly && _wptr >= _walignbase);
    if (_wptr+15 > _len)
	resize (15);
    CORBA::Octet *b = _buf + _wptr;
    switch ((_wptr - _walignbase) & 7L) {
    case 1: *b++ = 0;
    case 2: *b++ = 0;
    case 3: *b++ = 0;
    case 4: *b++ = 0;
    case 5: *b++ = 0;
    case 6: *b++ = 0;
    case 7: *b++ = 0;
    }
    if (!(((long)b | (long)p)&7)) {
	*((CORBA::LongLong *&)b)++ = *(const CORBA::LongLong *)p;
    } else {
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *(const Octet *)p;
    }
    _wptr = b - _buf;
}

// put 16 bytes with 8 byte alignment
void
CORBA::Buffer::put16 (const void *p)
{
    assert (!_readonly && _wptr >= _walignbase);
    if (_wptr+23 > _len)
	resize (23);
    CORBA::Octet *b = _buf + _wptr;
    switch ((_wptr - _walignbase) & 7L) {
    case 1: *b++ = 0;
    case 2: *b++ = 0;
    case 3: *b++ = 0;
    case 4: *b++ = 0;
    case 5: *b++ = 0;
    case 6: *b++ = 0;
    case 7: *b++ = 0;
    }
    if (!(((long)b | (long)p)&7)) {
	*((CORBA::LongLong *&)b)++ = *((const CORBA::LongLong * &)p)++;
	*((CORBA::LongLong *&)b)++ = *(const CORBA::LongLong *)p;
    } else {
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *((const Octet * &)p)++;
	*b++ = *(const Octet *)p;
    }
    _wptr = b - _buf;
}

void
CORBA::Buffer::dump (ostream &o) const
{
    o << "--" << endl;
    o << "rptr = " << _rptr << endl;
    o << "ralign = " << _ralignbase << endl;
    o << "wptr = " << _wptr << endl;
    o << "walign = " << _walignbase << endl;

    for (CORBA::ULong i = _rptr, cnt = 0; i < _wptr; ++i, ++cnt) {
        if (cnt == 16) {
            o << endl;
            cnt = 0;
        }
        char b[5];
        sprintf (b, "%2x ", _buf[i] & 0xff);
        o << b;
    }
    o << endl;
}

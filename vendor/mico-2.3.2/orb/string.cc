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
#ifndef _WINDOWS
#include <string.h>
#endif
#include <iostream.h>
#include <mico/util.h>
#include <mico/template_impl.h>


/************************* String support **************************/


CORBA::String_var::String_var ()
{
    // initializing the string here saves a lot of code elsewhere:
    // structs, unions, sequences, arrays and valuetypes all require
    // that their string members are initialized to the empty string
    str_backup = str = CORBA::string_dup ("");
    _autofree = TRUE;
}

CORBA::String_var::String_var (Boolean autofree)
{
    // initializing the string here saves a lot of code elsewhere:
    // structs, unions, sequences, arrays and valuetypes all require
    // that their string members are initialized to the empty string
    str_backup = str = CORBA::string_dup ("");
    _autofree = autofree;
}

CORBA::String_var::String_var (char *s)
{
    str_backup = str = s;
    _autofree = TRUE;
}

CORBA::String_var::String_var (const char *s)
{
    str_backup = str = CORBA::string_dup (s);
    _autofree = TRUE;
}

CORBA::String_var::String_var (const String_var &s)
{
    str_backup = str = CORBA::string_dup (s.str);
    _autofree = TRUE;
}

void
CORBA::String_var::check ()
{
    if (str != str_backup) {
	if (_autofree)
	    CORBA::string_free (str_backup);
	str_backup = str;
    }
}

CORBA::String_var::~String_var ()
{
    check ();
    CORBA::string_free (str);
}

CORBA::String_var &
CORBA::String_var::operator= (char *s)
{
    check ();
    CORBA::string_free (str);
    str_backup = str = s;
    return *this;
}

CORBA::String_var &
CORBA::String_var::operator= (const char *s)
{
    check ();
    CORBA::string_free (str);
    str_backup = str = CORBA::string_dup (s);
    return *this;
}

CORBA::String_var &
CORBA::String_var::operator= (const String_var &s)
{
    if (this != &s) {
	check ();
	CORBA::string_free (str);
	str_backup = str = CORBA::string_dup (s.str);
    }
    return *this;
}

CORBA::Boolean
CORBA::String_var::operator== (const String_var &s) const
{
    if (!s.str || !str)
        return !s.str && !str;
    return !strcmp (s.str, str);
}

char *
CORBA::String_var::_retn ()
{
    check();
    char *s = str;
    str = str_backup = 0;
    return s;
}

const char *
CORBA::String_var::in () const
{
    return str;
}

char *&
CORBA::String_var::out ()
{
    check();
    return str;
}

char *&
CORBA::String_var::inout ()
{
    check();
    return str;
}


char *
CORBA::string_alloc (ULong len)
{
    char *s = new char[len+1];
    s[0] = 0;
    return s;
}

char *
CORBA::string_dup (const char *s2)
{
    if (!s2)
        return 0;
    char *s = new char[strlen (s2) + 1];
    strcpy (s, s2);
    return s;
}

char *
CORBA::string_ndup (const char *s2, ULong len)
{
    if (!s2)
        return 0;
    char *s = new char[len+1];
    strncpy (s, s2, len);
    s[len] = 0;
    return s;
}

void
CORBA::string_free (char *s)
{
    if (s)
        delete[] s;
}


/************************* WString support **************************/


CORBA::WString_var::WString_var ()
{
    // initializing the string here saves a lot of code elsewhere:
    // structs, unions, sequences, arrays and valuetypes all require
    // that their string members are initialized to the empty string
    str_backup = str = CORBA::wstring_dup (L"");
    _autofree = TRUE;
}

CORBA::WString_var::WString_var (Boolean autofree)
{
    // initializing the string here saves a lot of code elsewhere:
    // structs, unions, sequences, arrays and valuetypes all require
    // that their string members are initialized to the empty string
    str_backup = str = CORBA::wstring_dup (L"");
    _autofree = autofree;
}

CORBA::WString_var::WString_var (wchar_t *s)
{
    str_backup = str = s;
    _autofree = TRUE;
}

CORBA::WString_var::WString_var (const wchar_t *s)
{
    str_backup = str = CORBA::wstring_dup (s);
    _autofree = TRUE;
}

CORBA::WString_var::WString_var (const WString_var &s)
{
    str_backup = str = CORBA::wstring_dup (s.str);
    _autofree = TRUE;
}

void
CORBA::WString_var::check ()
{
    if (str != str_backup) {
	if (_autofree)
	    CORBA::wstring_free (str_backup);
	str_backup = str;
    }
}

CORBA::WString_var::~WString_var ()
{
    check ();
    CORBA::wstring_free (str);
}

CORBA::WString_var &
CORBA::WString_var::operator= (wchar_t *s)
{
    check ();
    CORBA::wstring_free (str);
    str_backup = str = s;
    return *this;
}

CORBA::WString_var &
CORBA::WString_var::operator= (const wchar_t *s)
{
    check ();
    CORBA::wstring_free (str);
    str_backup = str = CORBA::wstring_dup (s);
    return *this;
}

CORBA::WString_var &
CORBA::WString_var::operator= (const WString_var &s)
{
    if (this != &s) {
	check ();
	CORBA::wstring_free (str);
	str_backup = str = CORBA::wstring_dup (s.str);
    }
    return *this;
}

CORBA::Boolean
CORBA::WString_var::operator== (const WString_var &s) const
{
    if (!s.str || !str)
        return !s.str && !str;
    return !xwcscmp (s.str, str);
}

wchar_t *
CORBA::WString_var::_retn ()
{
    check();
    wchar_t *s = str;
    str = str_backup = 0;
    return s;
}

const wchar_t *
CORBA::WString_var::in () const
{
    return str;
}

wchar_t *&
CORBA::WString_var::out ()
{
    check();
    return str;
}

wchar_t *&
CORBA::WString_var::inout ()
{
    check();
    return str;
}


wchar_t *
CORBA::wstring_alloc (ULong len)
{
    wchar_t *s = new wchar_t[len+1];
    s[0] = 0;
    return s;
}

wchar_t *
CORBA::wstring_dup (const wchar_t *s2)
{
    if (!s2)
        return 0;
    wchar_t *s = new wchar_t[xwcslen (s2) + 1];
    xwcscpy (s, s2);
    return s;
}

wchar_t *
CORBA::wstring_ndup (const wchar_t *s2, ULong len)
{
    if (!s2)
        return 0;
    wchar_t *s = new wchar_t[len+1];
    xwcsncpy (s, s2, len);
    s[len] = 0;
    return s;
}

void
CORBA::wstring_free (wchar_t *s)
{
    if (s)
        delete[] s;
}

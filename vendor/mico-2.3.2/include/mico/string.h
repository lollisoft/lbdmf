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

#ifndef __mico_string_h__
#define __mico_string_h__

class String_var {
    char *str;
    char *str_backup;
    Boolean _autofree;
    void check ();
public:
    String_var ();
    String_var (Boolean autofree);
    String_var (char *);
    String_var (const char *);
    String_var (const String_var &);
    ~String_var ();

    String_var &operator= (char *);
    String_var &operator= (const char *);
    String_var &operator= (const String_var &);
    // begin-mico-extension
    Boolean operator== (const String_var &s) const;
    // end-mico-extension

    void autofree (Boolean val)
    { _autofree = val; }

    /*
     * XXX non conformant to [16-11], but needed for out/inout parameter
     * passing, see [16-45].
     */
    // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
    operator const char * () const
    {
        return str;
    }

#ifdef USE_CORBA_2_1
    operator char* ()
    {
        return str;
    }
#else
    operator char*& ()
    {
        check();
        return str;
    }
#endif // USE_CORBA_2_1

#else // HAVE_CONST_OVERLOAD

#ifdef USE_CORBA_2_1
    operator char* ()
    {
        return str;
    }
#else
    operator char*& () const
    {
        /*
         * with this operator we support passing a String_var as an
         * out/inout parameter where char *& is expected. The callee
         * gets a reference to this->str and may change the pointer.
         * to avoid memory leaks we keep a backup of this->str in
         * this->str_backup and regularly check whether str != str_backup.
         * If so we free str_backup and set str_backup to str.
         * BEWARE: this works only if between two changes of this->str
         * operator char*&() is called, which is usually the case, e.g.:
         *    void f (out string s);       // IDL
         *
         *    String_var s;                // C++
         *    for (int i = 0; i < 10; ++i)
         *        f (s);
         */
        ((String_var *)this)->check();
        return (char *&)str;
    }
#endif // USE_CORBA_2_1
#endif // HAVE_CONST_OVERLOAD

    char &operator[] (ULong idx)
    { return str[idx]; }

    char operator[] (ULong idx) const
    { return str[idx]; }

    const char *in () const;
    char *&out ();
    char *&inout ();
    char * _retn ();
};

typedef String_var String_out;

MICO_EXPORT_FCT_DECL char *string_alloc (ULong len);
MICO_EXPORT_FCT_DECL char *string_dup (const char *);
MICO_EXPORT_FCT_DECL char *string_ndup (const char *, ULong len);
MICO_EXPORT_FCT_DECL void string_free (char *);


class WString_var {
    wchar_t *str;
    wchar_t *str_backup;
    Boolean _autofree;
    void check ();
public:
    WString_var ();
    WString_var (Boolean autofree);
    WString_var (wchar_t *);
    WString_var (const wchar_t *);
    WString_var (const WString_var &);
    ~WString_var ();

    WString_var &operator= (wchar_t *);
    WString_var &operator= (const wchar_t *);
    WString_var &operator= (const WString_var &);
    // begin-mico-extension
    Boolean operator== (const WString_var &s) const;
    // end-mico-extension

    void autofree (Boolean val)
    { _autofree = val; }

    /*
     * XXX non conformant to [16-11], but needed for out/inout parameter
     * passing, see [16-45].
     */
    // g++ const overload problem
#ifdef HAVE_CONST_OVERLOAD
    operator const wchar_t * () const
    {
        return str;
    }
    operator wchar_t*& ()
    {
        check();
        return str;
    }
#else
    operator wchar_t*& () const
    {
        /*
         * with this operator we support passing a String_var as an
         * out/inout parameter where char *& is expected. The callee
         * gets a reference to this->str and may change the pointer.
         * to avoid memory leaks we keep a backup of this->str in
         * this->str_backup and regularly check whether str != str_backup.
         * If so we free str_backup and set str_backup to str.
         * BEWARE: this works only if between two changes of this->str
         * operator char*&() is called, which is usually the case, e.g.:
         *    void f (out string s);       // IDL
         *
         *    String_var s;                // C++
         *    for (int i = 0; i < 10; ++i)
         *        f (s);
         */
        ((WString_var *)this)->check();
        return (wchar_t *&)str;
    }
#endif

    wchar_t &operator[] (ULong idx)
    { return str[idx]; }

    wchar_t operator[] (ULong idx) const
    { return str[idx]; }

    const wchar_t *in () const;
    wchar_t *&out ();
    wchar_t *&inout ();
    wchar_t * _retn ();
};

typedef WString_var WString_out;

MICO_EXPORT_FCT_DECL wchar_t *wstring_alloc (ULong len);
MICO_EXPORT_FCT_DECL wchar_t *wstring_dup (const wchar_t *);
MICO_EXPORT_FCT_DECL wchar_t *wstring_ndup (const wchar_t *, ULong len);
MICO_EXPORT_FCT_DECL void wstring_free (wchar_t *);

#endif // __mico_string_h__

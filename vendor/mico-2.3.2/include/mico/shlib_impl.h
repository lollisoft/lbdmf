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

#ifndef __mico_shlib_impl_h__
#define __mico_shlib_impl_h__


class UnixSharedLib : public MICO::SharedLib {
    void *_handle;
    string _error;
    string _name;
public:
    UnixSharedLib (const char *name);
    virtual ~UnixSharedLib ();

    virtual void *symbol (const char *);
    virtual const char *error ();
    virtual operator CORBA::Boolean ();

    virtual const char *name ();
};

#endif // __mico_shlib_impl_h__

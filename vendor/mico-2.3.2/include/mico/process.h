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

#ifndef __mico_process_h__
#define __mico_process_h__

class Process;

struct ProcessCallback {
    enum Event { Exited };
    virtual void callback (Process *, Event) = 0;
    virtual ~ProcessCallback ();
};

class Process {
public:
    virtual ~Process ();
    virtual CORBA::Boolean run () = 0;
    virtual CORBA::Boolean exited () = 0;
    virtual CORBA::Boolean exit_status () = 0;
    virtual void terminate () = 0;
    virtual void detach () = 0;
    virtual operator CORBA::Boolean () = 0;
};


#endif // __mico_process_h__

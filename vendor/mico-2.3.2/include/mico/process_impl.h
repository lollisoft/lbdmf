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

#ifndef __mico_process_impl_h__
#define __mico_process_impl_h__
#ifdef _WINDOWS
#include <winbase.h>
#endif



class UnixProcess : public MICO::Process, public CORBA::DispatcherCallback {

    CORBA::Long _exit_status;
    CORBA::Boolean _detached;
    MICO::ProcessCallback *_cb;
    string _args;
#ifdef _WINDOWS
#define OSWIN_MAXPROCS 128
    HANDLE _hProcess;
    static HANDLE MICO::UnixProcess::s_childprocs[OSWIN_MAXPROCS+1];
    static DWORD s_childpids[OSWIN_MAXPROCS+1];
    static int s_numofchildren;
    static void process_died(DWORD pid);
    static unsigned int __stdcall wait_thread_func (VOID *arg);
    static HANDLE s_waitthread;
    static int s_stop_waiting;

    HANDLE hRequestExitEvent;
    static unsigned int __stdcall ThreadExitFunc(VOID *arg);
    
    DWORD _pid;
#else
    CORBA::Long _pid;
#endif
    typedef list<UnixProcess *> ListProcess;
    static ListProcess _procs;

    static void signal_handler (int sig);
public:
#ifdef _WINDOWS
    static void _init();
    static void win32_process_init();
#endif
    UnixProcess (const char *cmd, MICO::ProcessCallback * = 0);
    virtual ~UnixProcess ();

    virtual CORBA::Boolean run ();
    virtual CORBA::Boolean exited ();
    virtual CORBA::Boolean exit_status ();
    virtual void terminate ();
    virtual void detach ();
    virtual operator CORBA::Boolean ();

    virtual void callback (CORBA::Dispatcher *,
			   CORBA::DispatcherCallback::Event);
};

#endif // __mico_process_impl_h__

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

#ifndef __mico_os_misc_h__
#define __mico_os_misc_h__

#ifdef _WINDOWS
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <io.h>
#include <process.h>


struct OSMisc {
    static void _init()
    {
        SignalMutex= CreateMutex (NULL, FALSE, NULL);
    }
    typedef __int64 longlong;
    typedef unsigned __int64 ulonglong;
    static HANDLE SignalMutex;

#if 0    
    struct TimeVal {
      MICO_Long tv_sec;
      MICO_Long tv_usec;
    };
#else
    typedef struct timeval TimeVal;
#endif

    static TimeVal gettime ()
    {
      struct _timeb timebuffer;
      _ftime( &timebuffer );
      TimeVal ct;
      ct.tv_sec  = timebuffer.time;
      ct.tv_usec = timebuffer.millitm * 1000;
      return ct;
    }

    enum AccessMode {
	ACCESS_READ = 0,
	ACCESS_WRITE = 0,
	ACCESS_EXEC = 0
    };

    static MICO_Long access (const char *file, AccessMode md)
    {
	return ::_access (file, md);
    }

    static MICO_Long getpid ()
    {
	return ::_getpid();
    }

    static FILE *popen (const char *cmd, const char *mode)
    {
	return ::_popen (cmd, mode);
    }

    static void pclose (FILE *fp)
    {
	::_pclose (fp);
    }

    typedef short SigState;

    static void block_sigs (SigState &)
    {
        WaitForSingleObject( SignalMutex, INFINITE );
    }

    static void restore_sigs (SigState &)
    {
        ReleaseMutex( SignalMutex);
    }
};

#else // _WINDOWS

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>

#ifdef __CYGWIN32__
extern "C" int gettimeofday (struct timeval *, struct timezone *);
#endif

struct OSMisc {
    typedef long long longlong;
    typedef unsigned long long ulonglong;

    static void _init()
    {
    }

    typedef struct timeval TimeVal;

    static TimeVal gettime ()
    {
      struct timeval tv;
#ifdef HAVE_GETTIMEOFDAY_TWOARGS
      gettimeofday (&tv, NULL);
#else
      gettimeofday (&tv);
#endif
      return tv;
    }

    enum AccessMode {
	ACCESS_READ = R_OK,
	ACCESS_WRITE = W_OK,
	ACCESS_EXEC = X_OK
    };

    static MICO_Long access (const char *file, AccessMode md)
    {
	return ::access (file, md);
    }

    static MICO_Long getpid ()
    {
	return ::getpid();
    }

    static FILE *popen (const char *cmd, const char *mode)
    {
	return ::popen (cmd, mode);
    }

    static void pclose (FILE *fp)
    {
	::pclose (fp);
    }

    typedef sigset_t SigState;

    static void block_sigs (SigState &osigs)
    {
        SigState sigs;
        sigemptyset (&sigs);
        // XXX ...
        sigaddset (&sigs, SIGCHLD);
	sigprocmask (SIG_BLOCK, &sigs, &osigs);
    }

    static void restore_sigs (SigState &osigs)
    {
	sigprocmask (SIG_SETMASK, &osigs, NULL);
    }
};

#endif

#endif // __mico_os_misc_h__

/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2025  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Odenwaldstr. 14

            63150 Heusenstamm (germany)
*/
/*...e*/

#ifndef LB_TOOLS
#define LB_TOOLS

#ifdef _MSC_VER

#pragma warning( disable: 4275 )

#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include <lbInterfaces.h>

/*...sLB_CLASSES_DLL scope:0:*/
#include <lbclasses-module.h>
/*...e*/

/*...stypedef lbMutexError:0:*/
typedef enum
{
  LB_MUTEX_NO_ERROR = 0,
  LB_MUTEX_ERROR
} lbMutexError;
/*...e*/

/*...sclass lbMutex:0:*/

class lbMutex : public lb_I_Mutex
{
public:
	lbMutex();
	virtual ~lbMutex();
	
	DECLARE_LB_UNKNOWN()
	
	virtual void createMutex(int name);
	virtual void deleteMutex(int name);
	virtual void enter();
	virtual void release();
private:
	
	int    MyMutexNumber;
	
#ifdef WINDOWS
	HANDLE mutex;
#endif
#ifdef __WXGTK__
	int    mutex;
#endif
#ifdef OSX
	int    mutex;
#endif
};
/*...e*/

/*...sclass lbCritSect\44\ lbLock:0:*/
class lbLock;

class lbCritSect : public lb_I_CriticalSection {
public:
	lbCritSect();
	virtual ~lbCritSect();

	DECLARE_LB_UNKNOWN()

protected:
	lbErrCodes enter();
	lbErrCodes leave();
	
	void* critsect;	
	
	friend class lbLock;
};

class lbLock : public lb_I_Lock {
public:
	lbLock();
	virtual ~lbLock();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL with(lb_I_CriticalSection* _cso, char* _name);

protected:
	lbLock(const lbLock&) 
	{ 
		name = NULL; 
		cso = NULL; 
		instance_counted = 0;
		lastQIFile = miniString();
		lastQILine = 0;
		lastSMFile = miniString();
		lastSMLine = 0;
		
		debug_macro = 0;
	}

	char* name;
	lb_I_CriticalSection* cso;
};
/*...e*/


class lbThreadInternal; // For various operating systems

/*...sclass lbThread:0:*/
class lbThread : public lb_I_Thread {
public:
	lbThread();
	virtual ~lbThread();

	DECLARE_LB_UNKNOWN()
	
	lb_I_ThreadImplementation* LB_STDCALL getThreadImplementation();	
	lbErrCodes LB_STDCALL setThreadImplementation(lb_I_ThreadImplementation* impl);

	lbErrCodes LB_STDCALL create();

	lbErrCodes LB_STDCALL run(); 
	lbErrCodes LB_STDCALL stop();
	
	lbErrCodes LB_STDCALL pause();
	lbErrCodes LB_STDCALL resume();

	/**
	 * Call this function once a process
	 */
	int LB_STDCALL OnInit();
	
	/**
	 * Cleanup at process end
	 */
	void LB_STDCALL OnExit();
	
	/**
	 * Main thread routine.
	 */
	static DWORD WinThreadStart(lbThread *thread);

private:
//	HANDLE lb_hThread;	
	DWORD  lb_ThreadId;

        // no copy ctor/assignment operator
        lbThread(const lbThread&);
        lbThread& operator=(const lbThread&);

        friend class lbThreadInternal;

        // the (platform-dependent) thread class implementation
        lbThreadInternal *pThreadImpl;	

	UAP(lb_I_ThreadImplementation, _impl)
        
        static int threadCount;
};


DECLARE_FUNCTOR(instanceOflbCritSect)
DECLARE_FUNCTOR(instanceOflbLock)
DECLARE_FUNCTOR(instanceOflbThread)

/*...e*/
#endif

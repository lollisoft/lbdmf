/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <stdio.h>

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#include <iostream>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbthread.h>

IMPLEMENT_FUNCTOR(instanceOflbCritSect, lbCritSect)
IMPLEMENT_FUNCTOR(instanceOflbLock, lbLock)
IMPLEMENT_FUNCTOR(instanceOflbThread, lbThread)


int lbThread::threadCount = 0;

#ifdef __WXGTK__
/*...sPV haeder:0:*/
#define SEM_READKEY  20001
#define SEM_WRITEKEY 20002

#define P(id) pv(id, -1)
#define V(id) pv(id, 1)

#ifdef bla // Was in haeder
extern int sem_anfordid;
extern int sem_antwortid;


extern int helper(int mutex);

extern void pv(int id, int operation);
extern void initsem(int client);
extern void deletesem(int id);
#endif
/*...e*/
/*...sPV code:0:*/
int sem_anfordid, sem_antwortid;

int helper(int name)
{
	return semctl(name, 0, SETVAL, (int)1);
}

void deletesem(int id)
{
	if (semctl(id, 0, IPC_RMID, (int)1) == -1) {
		perror("semctl-Fehler (delete)");
		exit(1);
	}				
}

void initsem(int client)
{
	if (client == 0) { // Server init
		/*
			Einrichten und Setzen eines Semaphors für Lese-Msg-Queue
		*/

		if ((sem_anfordid = semget(SEM_READKEY, 1, S_IRWXU|S_IRWXG|S_IRWXO | IPC_CREAT | IPC_EXCL)) == -1) {
			perror("semget failed");
			exit(1);
		}	
		if (semctl(sem_anfordid, 0, SETVAL, (int)1) == -1) {
			perror("semctl-Fehler (Lese-Msg-Queue)");
			exit(1);
		}				

		/*
			Einrichten und Setzen eines Semaphors für Schreib-Msg-Queue
		*/

		if ((sem_antwortid = semget(SEM_WRITEKEY, 1, S_IRWXU|S_IRWXG|S_IRWXO | IPC_CREAT | IPC_EXCL)) == -1) {
			perror("semget failed");
			exit(1);
		}	
		if (semctl(sem_antwortid, 0, SETVAL, (int)1) == -1) {
			perror("semctl-Fehler (Schreib-Msg-Queue)");
			exit(1);
		}				
	}
	else { // Client init
		/*
			Einrichten und Setzen eines Semaphors für Lese-Msg-Queue
		*/

		if ((sem_anfordid = semget(SEM_READKEY, 0, 0)) == -1) {
			perror("Open semaphore failed");
			exit(1);
		}	

		if ((sem_antwortid = semget(SEM_WRITEKEY, 0, 0)) == -1) {
			perror("Open semaphore failed");
			exit(1);
		}	
	}
}
/*...e*/
#endif

BEGIN_IMPLEMENT_LB_UNKNOWN(lbMutex)
ADD_INTERFACE(lb_I_Mutex)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbMutex:0:*/
lbMutex::lbMutex()
{
	ref = STARTREF;
}

lbMutex::~lbMutex()
{
	deleteMutex(MyMutexNumber);	
}

lbErrCodes lbMutex::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	return err;
}

/*...sdeleteMutex:0:*/
void lbMutex::deleteMutex(int name)
{
#ifdef WINDOWS
        CloseHandle(mutex);
#endif
#ifdef __WXGTK__
        int HandlePrefix = 20000;
        deletesem(HandlePrefix+name);
#endif
}
/*...e*/
/*...screateMutex:0:*/
void lbMutex::createMutex(int name)
{
	MyMutexNumber = name;

/*...sWINDOWS:0:*/
#ifdef WINDOWS

        char number[10];
        char _name[80] = "lbMutex";
        itoa(name, number, 10);
        strcat(_name, number);
        
        mutex = ::CreateMutex(0, FALSE, _name);

#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
        int HandlePrefix = 20000;

        if ((mutex = semget(HandlePrefix+name, 1, S_IRWXU |
                                                  S_IRWXG |
                                                  S_IRWXO | 
                                                  IPC_CREAT |
                                                  IPC_EXCL)) == -1)
        {
                perror("semget failed - use open");
                
                if ((mutex = semget(HandlePrefix+name, 0, 0)) == -1)
                {
                        perror("Open semaphore failed");
                        exit(1);
                }
                return;
        }       
        
        if (helper(mutex) == -1) 
        {
                perror("semctl error - exit");
                exit(1);
        }
#endif
/*...e*/
}
/*...e*/

/*...senter:0:*/
void lbMutex::enter()
{
#ifdef WINDOWS
        WaitForSingleObject(mutex, INFINITE);
#endif
#ifdef __WXGTK__
        P(mutex);
#endif
}
/*...e*/
/*...srelease:0:*/
void lbMutex::release()
{
#ifdef WINDOWS
        ReleaseMutex(mutex);
#endif
#ifdef __WXGTK__
        V(mutex);
#endif
} 
/*...e*/
/*...e*/

/*...slbCritSect:0:*/
//#define USE_CRITICAL_SECTION

BEGIN_IMPLEMENT_LB_UNKNOWN(lbCritSect)
ADD_INTERFACE(lb_I_CriticalSection)
END_IMPLEMENT_LB_UNKNOWN()

///\todo Implement
lbCritSect::lbCritSect() {
	ref = STARTREF;
}

lbCritSect::~lbCritSect() {
}

lbErrCodes lbCritSect::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	return err;
}

lbErrCodes lbCritSect::enter() {
	return ERR_NONE;
}

lbErrCodes lbCritSect::leave() {
	return ERR_NONE;
}
/*...e*/

/*...slbLock:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbLock)
ADD_INTERFACE(lb_I_Lock)
END_IMPLEMENT_LB_UNKNOWN()


lbLock::lbLock() {
	ref = STARTREF;
	cso = NULL;
}

lbErrCodes lbLock::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	return err;
}

void lbLock::with(lb_I_CriticalSection* _cso, char* _name) {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//COUT << "lbLock::lbLock(...) enter critical section: " << _name << ENDL;
_CL_VERBOSE << "lbLock::lbLock(...) enter critical section" LOG_
#endif
/*...e*/
	_cso->enter();
	cso = _cso;
	name = strdup(_name);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_VERBOSE << "lbLock::lbLock(...) entered" LOG_
//COUT << "lbLock::lbLock(...) entered" << ENDL;
#endif
/*...e*/
#endif
}

lbLock::~lbLock() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//COUT << "lbLock::~lbLock(...) leave critical section: " << name << ENDL;
_CL_VERBOSE << "lbLock::~lbLock(...) leave critical section" LOG_
#endif
/*...e*/
	if (cso) cso->leave();
	if (name) free(name);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//COUT << "lbLock::~lbLock(...) leaved" << ENDL;
_CL_VERBOSE << "lbLock::~lbLock(...) leaved" LOG_
#endif
/*...e*/
#endif	
}
/*...e*/

/*...slbThreadInternal:0:*/

// TLS index of the slot where we store the pointer to the current thread
static DWORD s_tlsThisThread = 0xFFFFFFFF;
static DWORD s_idMainThread = 0;

#ifdef OSX
#define HANDLE int
#endif

/*...sclass lbThreadInternal:0:*/
class lbThreadInternal {
public:
    lbThreadInternal()
    {
        lb_hThread = 0;
    }

    // create a new (suspended) thread (for the given thread object)
    lbErrCodes Create(lbThread *thread);
	
    // suspend/resume/terminate
    lbErrCodes suspend();
    lbErrCodes resume();
    // thread state

    // thread handle and id
    HANDLE getHandle() const { 
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
        
        _LOG << "lbThreadInternal::getHandle returns " << (lb_hThread == NULL) ? "NULL" : "Not NULL" LOG_
#endif
/*...e*/
    	return lb_hThread; 
    }
    DWORD  getId() const { 
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
    	_CL_VERBOSE << "lbThreadInternal::getId called" LOG_
#endif
/*...e*/
    	return lb_ThreadId; 
    }

    // thread function
    static DWORD WinThreadStart(lbThread *thread);

private:
    HANDLE        lb_hThread;    // handle of the thread
    DWORD         lb_ThreadId;  // thread id
};
/*...e*/

/*...slbThreadInternal\58\\58\Create\40\lbThread \42\thread\41\:0:*/
lbErrCodes lbThreadInternal::Create(lbThread *thread) {
    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\suspend\40\\41\:0:*/
lbErrCodes lbThreadInternal::suspend() {
    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\resume\40\\41\:0:*/
lbErrCodes lbThreadInternal::resume() {
    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\WinThreadStart\40\lbThread \42\thread\41\:0:*/
DWORD lbThreadInternal::WinThreadStart(lbThread *thread)
{
	DWORD ret = 0;
    return ret;
}
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbThread)
ADD_INTERFACE(lb_I_Thread)
END_IMPLEMENT_LB_UNKNOWN()


/*...slbThread:0:*/
lbThread::lbThread() {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOGENABLE("lbThread::lbThread()");
#endif
/*...e*/
	if (threadCount == 0) {

/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
		_CL_VERBOSE << "lbThread::lbThread(): OnInit() must be called" LOG_
#endif
/*...e*/
		if (OnInit() == 0) {
			_CL_VERBOSE << "lbThread::lbThread could not init module" LOG_
		} else {
			threadCount++;
		}
	}
	pThreadImpl = new lbThreadInternal();
}

lbThread::~lbThread() {
	if (threadCount == 0) {
		_CL_VERBOSE << "lbThread::~lbThread(): Fatal error, threadCount error. Module may not be initialized - ignoring OnExit()" LOG_
	} else {
		threadCount--;
		_CL_VERBOSE << "lbThread::~lbThread() calling OnExit()" LOG_
		OnExit();
		_CL_VERBOSE << "lbThread::~lbThread() called OnExit()" LOG_
	}
	if (pThreadImpl != NULL) delete pThreadImpl;
}

lbErrCodes lbThread::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	return err;
}

lb_I_ThreadImplementation* LB_STDCALL lbThread::getThreadImplementation() {
	_impl++;
	return _impl.getPtr();
}

lbErrCodes LB_STDCALL lbThread::setThreadImplementation(lb_I_ThreadImplementation* impl) {
	_impl = impl;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbThread::create() {
  lbErrCodes err;
/*...sCreate if needed:2:*/
  if (pThreadImpl == NULL) _LOG << "lbThread::create() Error: Have a NULL pointer (pThreadImpl)!" LOG_
  if (pThreadImpl->getHandle() == NULL) {
/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	_CL_VERBOSE << "lbThread::run will create a new thread" LOG_
#endif
/*...e*/

/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	if (this == NULL) {
		_CL_VERBOSE << "lbThreadInternal::Create: Got a null pointer (this)." LOG_
	}
#endif
/*...e*/

  	if ((err = pThreadImpl->Create(this)) != ERR_NONE) {
		_CL_VERBOSE << "lbThread::run creation of thread failed" LOG_
		return err;
  	}
  } else printf("Creation of thread not needed\n");
/*...e*/
  return err;
}

lbErrCodes LB_STDCALL lbThread::run() {
  lbErrCodes err;
/*...sLet it run:2:*/
  if ((err = pThreadImpl->resume()) != ERR_NONE) {
	printf("lbThread::resume failed\n");
  }
/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
_CL_VERBOSE << "lbThread::resume done" LOG_
#endif
/*...e*/
  return err;
/*...e*/
}

lbErrCodes LB_STDCALL lbThread::stop() {
	_CL_VERBOSE << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

lbErrCodes LB_STDCALL lbThread::pause() {
	_CL_VERBOSE << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

lbErrCodes LB_STDCALL lbThread::resume() {
	_CL_VERBOSE << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

/*...e*/
/*...slbThreadModule:0:*/
/*...sint lbThread\58\\58\OnInit\40\\41\:0:*/
int lbThread::OnInit()
{
    return 1;
}
/*...e*/

/*...svoid lbThread\58\\58\OnExit\40\\41\:0:*/
void lbThread::OnExit()
{
}
/*...e*/
/*...e*/

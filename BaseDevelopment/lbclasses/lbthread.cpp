/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <stdio.h>

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#include <iostream.h>

#include <lbInterfaces.h>
#include <lbthread.h>
#include <lbConfigHook.h>

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

/*...slbMutex:0:*/
lbMutex::lbMutex()
{
}

lbMutex::~lbMutex()
{
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

#ifdef WINDOWS

/*...slbCritSect:0:*/
//#define USE_CRITICAL_SECTION

lbCritSect::lbCritSect() {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbCritSect::lbCritSect() called" LOG_
//cout << "lbCritSect::lbCritSect() called" << endl;
#endif
/*...e*/
	critsect = new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbCritSect::lbCritSect() leave" << endl;
_CL_LOG << "lbCritSect::lbCritSect() leave" LOG_
#endif
/*...e*/
}

lbCritSect::~lbCritSect() {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbCritSect::~lbCritSect() called" << endl << flush;
_CL_LOG << "lbCritSect::~lbCritSect() called" LOG_
#endif
/*...e*/
	DeleteCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbCritSect::~lbCritSect() leave" << endl;
_CL_LOG << "lbCritSect::~lbCritSect() leave" LOG_
#endif
/*...e*/
}

lbErrCodes lbCritSect::enter() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbCritSect::enter() called" LOG_
//cout << "lbCritSect::enter() called" << endl;
#endif
/*...e*/
	EnterCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbCritSect::enter() leave" << endl;	
_CL_LOG << "lbCritSect::enter() leave" LOG_
#endif
/*...e*/
#endif
	return ERR_NONE;
}

lbErrCodes lbCritSect::leave() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbCritSect::leave() called" LOG_
//cout << "lbCritSect::leave() called" << endl;
#endif
/*...e*/
	LeaveCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbCritSect::leave() leave" LOG_
//cout << "lbCritSect::leave() leave" << endl;
#endif
/*...e*/
#endif
	return ERR_NONE;
}
/*...e*/

/*...slbLock:0:*/
lbLock::lbLock(lbCritSect& _cso, char* _name) {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbLock::lbLock(...) enter critical section: " << _name << endl;
_CL_LOG << "lbLock::lbLock(...) enter critical section" LOG_
#endif
/*...e*/
	_cso.enter();
	cso = &_cso;
	name = strdup(_name);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbLock::lbLock(...) entered" LOG_
//cout << "lbLock::lbLock(...) entered" << endl;
#endif
/*...e*/
#endif
}

lbLock::~lbLock() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbLock::~lbLock(...) leave critical section: " << name << endl;
_CL_LOG << "lbLock::~lbLock(...) leave critical section" LOG_
#endif
/*...e*/
	cso->leave();
	delete[] name;
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
//cout << "lbLock::~lbLock(...) leaved" << endl;
_CL_LOG << "lbLock::~lbLock(...) leaved" LOG_
#endif
/*...e*/
#endif	
}
/*...e*/

/*...slbThreadInternal:0:*/

// TLS index of the slot where we store the pointer to the current thread
static DWORD s_tlsThisThread = 0xFFFFFFFF;
static DWORD s_idMainThread = 0;

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
    	_CL_LOG << "lbThreadInternal::getId called" LOG_
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
/*...sTHREAD_VERBOSE:0:*/
	#ifdef THREAD_VERBOSE
	_CL_LOG << "lbThreadInternal::Create called" LOG_
	if (thread == NULL) {
		printf("lbThreadInternal::Create: Got a null pointer.\n");
	}
	#endif
/*...e*/
    lb_hThread = ::CreateThread
                  (
                    NULL,                               // default security
                    0,                                  // default stack size
                    (LPTHREAD_START_ROUTINE)            // thread entry point
                    lbThreadInternal::WinThreadStart,   //
                    (LPVOID)thread,                     // parameter
                    CREATE_SUSPENDED,                   // flags
                    &lb_ThreadId                        // [out] thread id
                  );
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
    _LOG << "Thread with id " << lb_ThreadId << " created" LOG_
#endif
/*...e*/

    if ( lb_hThread == NULL )
    {
    	// Do some logging
    	_CL_LOG << "lbThreadInternal: Could not create a thread" LOG_

        return LB_THREAD_ERROR;
    }

    // lb_ThreadId must be associated with the current clt
    
    if ( ::SetThreadPriority(lb_hThread, THREAD_PRIORITY_NORMAL) == 0 )
    {
    	_CL_LOG << "lbThreadInternal: Could not set ThreadPriority" LOG_
    	return LB_THREAD_ERROR;
    }
    
    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\suspend\40\\41\:0:*/
lbErrCodes lbThreadInternal::suspend() {
    DWORD nSuspendCount = ::SuspendThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        _LOG << "lbThreadInternal: Can not suspend thread" LOG_

        return LB_THREAD_ERROR;
    }

//    m_state = STATE_PAUSED;

    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\resume\40\\41\:0:*/
lbErrCodes lbThreadInternal::resume() {
    DWORD nSuspendCount = ::ResumeThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        _LOG << "lbThreadInternal: Can not resume thread" LOG_

        return LB_THREAD_ERROR;
    }

/*...sVERBOSE:0:*/
#ifdef NOVERBOSE
    printf("lbThreadInternal::resume, thread resumed\n");
#endif
/*...e*/

//    m_state = STATE_RUNNING;

    return ERR_NONE;
}
/*...e*/

/*...slbThreadInternal\58\\58\WinThreadStart\40\lbThread \42\thread\41\:0:*/
DWORD lbThreadInternal::WinThreadStart(lbThread *thread)
{
    // store the thread object in the TLS
/*...sTHREAD_VERBOSE:0:*/
    #ifdef THREAD_VERBOSE
    _LOG << "lbThreadInternal::WinThreadStart: Do NOT store thread in tls" LOG_
    #endif    
/*...e*/
#define bla    
/*...sbla:0:*/
#ifdef bla
    _LOG << "lbThreadInternal::WinThreadStart called" LOG_
    if ( !::TlsSetValue(s_tlsThisThread, thread) )
    {
        _LOG << "lbThreadInternal::WinThreadStart, Can not start thread: error writing TLS." LOG_

        return (DWORD)-1;
    }
#endif
/*...e*/
#undef bla
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbThreadInternal::WinThreadStart: Calling (DWORD)thread->Entry()" LOG_
#endif
/*...e*/

    if (thread == NULL) {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbThreadInternal::WinThreadStart: Null pointer: thread" LOG_
#endif
/*...e*/
    }
    
    DWORD ret = (DWORD)thread->Entry();

/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
_CL_LOG << "lbThreadInternal::WinThreadStart: Returning from (DWORD)thread->Entry()\n" LOG_
#endif
/*...e*/

    //thread->p_ThreadImpl->SetState(STATE_EXITED);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
    _LOG << "lbThreadInternal: Do not call OnExit()" LOG_
#endif
/*...e*/
    //thread->OnExit();

    delete thread;

    return ret;
}
/*...e*/
/*...e*/

#endif
#ifdef WINDOWS
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
		_CL_LOG << "lbThread::lbThread(): OnInit() must be called" LOG_
#endif
/*...e*/
		if (OnInit() == 0) {
			_CL_LOG << "lbThread::lbThread could not init module" LOG_
		} else {
			threadCount++;
		}
	}
	pThreadImpl = new lbThreadInternal();
}

lbThread::~lbThread() {
	if (threadCount == 0) {
		_CL_LOG << "lbThread::~lbThread(): Fatal error, threadCount error. Module may not be initialized - ignoring OnExit()" LOG_
	} else {
		threadCount--;
		_CL_LOG << "lbThread::~lbThread() calling OnExit()" LOG_
		OnExit();
		_CL_LOG << "lbThread::~lbThread() called OnExit()" LOG_
	}
	if (pThreadImpl != NULL) delete pThreadImpl;
}

lbErrCodes LB_STDCALL lbThread::create() {
  lbErrCodes err;
/*...sCreate if needed:2:*/
  if (pThreadImpl == NULL) _LOG << "lbThread::create() Error: Have a NULL pointer (pThreadImpl)!" LOG_
  if (pThreadImpl->getHandle() == NULL) {
/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	_CL_LOG << "lbThread::run will create a new thread" LOG_
#endif
/*...e*/

/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	if (this == NULL) {
		_CL_LOG << "lbThreadInternal::Create: Got a null pointer (this)." LOG_
	}
#endif
/*...e*/

  	if ((err = pThreadImpl->Create(this)) != ERR_NONE) {
		_CL_LOG << "lbThread::run creation of thread failed" LOG_
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
_CL_LOG << "lbThread::resume done" LOG_
#endif
/*...e*/
  return err;
/*...e*/
}

lbErrCodes LB_STDCALL lbThread::stop() {
	_CL_LOG << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

lbErrCodes LB_STDCALL lbThread::pause() {
	_CL_LOG << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

lbErrCodes LB_STDCALL lbThread::resume() {
	_CL_LOG << "Error: Not implemented" LOG_
	return LB_THREAD_ERROR;
}

/*...e*/
/*...slbThreadModule:0:*/
/*...sint lbThread\58\\58\OnInit\40\\41\:0:*/
int lbThread::OnInit()
{
    // allocate TLS index for storing the pointer to the current thread
    s_tlsThisThread = ::TlsAlloc();
    if ( s_tlsThisThread == 0xFFFFFFFF )
    {
        // in normal circumstances it will only happen if all other
        // TLS_MINIMUM_AVAILABLE (>= 64) indices are already taken - in other
        // words, this should never happen
        _LOG << "Thread module initialization failed: impossible to allocate index in thread local storage" LOG_

        return 0;
    }
    // main thread doesn't have associated wxThread object, so store 0 in the
    // TLS instead
    if ( !::TlsSetValue(s_tlsThisThread, (LPVOID)0) )
    {
        ::TlsFree(s_tlsThisThread);
        s_tlsThisThread = 0xFFFFFFFF;

        _LOG << "Thread module initialization failed: can not store value in thread local storage" LOG_

        return 0;
    }

/*...sbla:0:*/
#ifdef bla
    s_critsectWaitingForGui = new wxCriticalSection();

    s_critsectGui = new wxCriticalSection();
    s_critsectGui->Enter();
#endif
/*...e*/

    // no error return for GetCurrentThreadId()
    s_idMainThread = ::GetCurrentThreadId();

    return 1;
}
/*...e*/

/*...svoid lbThread\58\\58\OnExit\40\\41\:0:*/
void lbThread::OnExit()
{
#ifdef THREAD_VERBOSE
_CL_LOG << "lbThread::OnExit() called" LOG_
#endif
    if ( !::TlsFree(s_tlsThisThread) )
    {
        _LOG << "lbThreadModule::OnExit: TlsFree failed." LOG_
    }
#ifdef THREAD_VERBOSE
_CL_LOG << "lbThread::OnExit() leave" LOG_
#endif
/*...sbla:0:*/
#ifdef bla
    if ( s_critsectGui )
    {
        s_critsectGui->Leave();
        delete s_critsectGui;
        s_critsectGui = NULL;
    }
    wxDELETE(s_critsectWaitingForGui);
#endif
/*...e*/
}
/*...e*/
/*...e*/

#endif
/*...sextern C begin:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/

DWORD DLLEXPORT LB_STDCALL lbGetCurrentThreadId() {
#ifdef WINDOWS
	return ::GetCurrentThreadId();
#else
//#error "Only Windows target is supported"
#endif
}

DWORD DLLEXPORT LB_STDCALL lbGetCurrentProcessId() {
#ifdef WINDOWS
	return ::GetCurrentProcessId();
#else
//#error "Only Windows target is supported"
#endif
}

/*...sextern C end:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

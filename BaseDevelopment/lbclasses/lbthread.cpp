#define LB_CONTAINER_DLL

#include <lbInclude.h>

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

/*...sDeleteMutex:0:*/
void lbMutex::DeleteMutex(int name)
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
/*...sCreateMutex:0:*/
void lbMutex::CreateMutex(int name)
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

/*...sEnter:0:*/
void lbMutex::Enter()
{
#ifdef WINDOWS
        WaitForSingleObject(mutex, INFINITE);
#endif
#ifdef __WXGTK__
        P(mutex);
#endif
}
/*...e*/
/*...sRelease:0:*/
void lbMutex::Release()
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

lbCritSect::lbCritSect() {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbCritSect::lbCritSect() called");
cout << "lbCritSect::lbCritSect() called" << endl;
#endif
/*...e*/
	critsect = new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbCritSect::lbCritSect() leave" << endl;
LOG("lbCritSect::lbCritSect() leave");
#endif
/*...e*/
}

lbCritSect::~lbCritSect() {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbCritSect::~lbCritSect() called" << endl << flush;
LOG("lbCritSect::~lbCritSect() called");
#endif
/*...e*/
	DeleteCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbCritSect::~lbCritSect() leave" << endl;
LOG("lbCritSect::~lbCritSect() leave");
#endif
/*...e*/
}

lbErrCodes lbCritSect::enter() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbCritSect::enter() called");
cout << "lbCritSect::enter() called" << endl;
#endif
/*...e*/
	EnterCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbCritSect::enter() leave" << endl;	
LOG("lbCritSect::enter() leave");
#endif
/*...e*/
#endif
	return ERR_NONE;
}

lbErrCodes lbCritSect::leave() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbCritSect::leave() called");
cout << "lbCritSect::leave() called" << endl;
#endif
/*...e*/
	LeaveCriticalSection((CRITICAL_SECTION*)critsect);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbCritSect::leave() leave");
cout << "lbCritSect::leave() leave" << endl;
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
cout << "lbLock::lbLock(...) enter critical section: " << _name << endl;
LOG("lbLock::lbLock(...) enter critical section");
#endif
/*...e*/
	_cso.enter();
	cso = &_cso;
	name = strdup(_name);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbLock::lbLock(...) entered");
cout << "lbLock::lbLock(...) entered" << endl;
#endif
/*...e*/
#endif
}

lbLock::~lbLock() {
#ifdef USE_CRITICAL_SECTION
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbLock::~lbLock(...) leave critical section: " << name << endl;
LOG("lbLock::~lbLock(...) leave critical section");
#endif
/*...e*/
	cso->leave();
	delete[] name;
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
cout << "lbLock::~lbLock(...) leaved" << endl;
LOG("lbLock::~lbLock(...) leaved");
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
    lbThreadError Create(lbThread *thread);
	
    // suspend/resume/terminate
    lbThreadError suspend();
    lbThreadError resume();
    // thread state

    // thread handle and id
    HANDLE getHandle() const { 
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
        char buf[100];
        
        sprintf(buf, "lbThreadInternal::getHandle returns %s" , (lb_hThread == NULL) ? "NULL" : "Not NULL");
        LOG(buf);
#endif
/*...e*/
    	return lb_hThread; 
    }
    DWORD  getId() const { 
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
    	LOG("lbThreadInternal::getId called");
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
lbThreadError lbThreadInternal::Create(lbThread *thread) {
/*...sTHREAD_VERBOSE:0:*/
	#ifdef THREAD_VERBOSE
	LOG("lbThreadInternal::Create called");
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
    char buf[100];
    sprintf(buf, "Thread with id %d created", lb_ThreadId);
    LOG(buf);
    printf(buf);
    printf("\n");
#endif
/*...e*/

    if ( lb_hThread == NULL )
    {
    	// Do some logging
    	LOG("lbThreadInternal: Could not create a thread");

        return LB_THREAD_ERROR;
    }

    // lb_ThreadId must be associated with the current clt
    
    if ( ::SetThreadPriority(lb_hThread, THREAD_PRIORITY_NORMAL) == 0 )
    {
    	LOG("lbThreadInternal: Could not set ThreadPriority");
    	return LB_THREAD_ERROR;
    }
    
    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\suspend\40\\41\:0:*/
lbThreadError lbThreadInternal::suspend() {
    DWORD nSuspendCount = ::SuspendThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        LOG("lbThreadInternal: Can not suspend thread");

        return LB_THREAD_ERROR;
    }

//    m_state = STATE_PAUSED;

    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\resume\40\\41\:0:*/
lbThreadError lbThreadInternal::resume() {
    DWORD nSuspendCount = ::ResumeThread(lb_hThread);
    if ( nSuspendCount == (DWORD)-1 )
    {
        LOG("lbThreadInternal: Can not resume thread");

        return LB_THREAD_ERROR;
    }

/*...sVERBOSE:0:*/
#ifdef NOVERBOSE
    printf("lbThreadInternal::resume, thread resumed\n");
#endif
/*...e*/

//    m_state = STATE_RUNNING;

    return LB_THREAD_NO_ERROR;
}
/*...e*/

/*...slbThreadInternal\58\\58\WinThreadStart\40\lbThread \42\thread\41\:0:*/
DWORD lbThreadInternal::WinThreadStart(lbThread *thread)
{
    // store the thread object in the TLS
/*...sTHREAD_VERBOSE:0:*/
    #ifdef THREAD_VERBOSE
    LOG("lbThreadInternal::WinThreadStart: Do NOT store thread in tls");    
    #endif    
/*...e*/
#define bla    
/*...sbla:0:*/
#ifdef bla
    LOG("lbThreadInternal::WinThreadStart called");
    if ( !::TlsSetValue(s_tlsThisThread, thread) )
    {
        LOG("lbThreadInternal::WinThreadStart, Can not start thread: error writing TLS.");

        return (DWORD)-1;
    }
#endif
/*...e*/
#undef bla
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbThreadInternal::WinThreadStart: Calling (DWORD)thread->Entry()");
printf("lbThreadInternal::WinThreadStart: Calling (DWORD)thread->Entry()\n");
#endif
/*...e*/

    if (thread == NULL) {
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbThreadInternal::WinThreadStart: Null pointer: thread");
printf("lbThreadInternal::WinThreadStart: Null pointer: thread\n");
#endif
/*...e*/
    }
    
    DWORD ret = (DWORD)thread->Entry();

/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
LOG("lbThreadInternal::WinThreadStart: Returning from (DWORD)thread->Entry()\n");
printf("lbThreadInternal::WinThreadStart: Returning from (DWORD)thread->Entry()\n");
#endif
/*...e*/

    //thread->p_ThreadImpl->SetState(STATE_EXITED);
/*...sTHREAD_VERBOSE:0:*/
#ifdef THREAD_VERBOSE
    LOG("lbThreadInternal: Do not call OnExit()");
#endif
/*...e*/
    //thread->OnExit();

    delete thread;

    return ret;
}
/*...e*/
/*...e*/
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
		LOG("lbThread::lbThread(): OnInit() must be called");
#endif
/*...e*/
		if (OnInit() == 0) {
			LOG("lbThread::lbThread could not init module");
		} else {
			threadCount++;
		}
	}
	pThreadImpl = new lbThreadInternal();
}

lbThread::~lbThread() {
	if (threadCount == 0) {
		LOG("lbThread::~lbThread(): Fatal error, threadCount error. Module may not be initialized - ignoring OnExit()");
	} else {
		threadCount--;
		LOG("lbThread::~lbThread() calling OnExit()");
		OnExit();
		LOG("lbThread::~lbThread() called OnExit()");
	}
	if (pThreadImpl != NULL) delete pThreadImpl;
}

lbThreadError lbThread::create() {
  lbThreadError err;
/*...sCreate if needed:2:*/
  if (pThreadImpl == NULL) LOG("lbThread::create() Error: Have a NULL pointer (pThreadImpl)!");
  if (pThreadImpl->getHandle() == NULL) {
/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	printf("lbThread::run will create a new thread\n");
	LOG("lbThread::run will create a new thread");
#endif
/*...e*/

/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
	if (this == NULL) {
		printf("lbThreadInternal::Create: Got a null pointer (this).\n");
	}
#endif
/*...e*/

  	if ((err = pThreadImpl->Create(this)) != LB_THREAD_NO_ERROR) {
		printf("lbThread::run creation of thread failed\n");
		LOG("lbThread::run creation of thread failed");
		return err;
  	}
  } else printf("Creation of thread not needed\n");
/*...e*/
  return err;
}

lbThreadError lbThread::run() {
  lbThreadError err;
/*...sLet it run:2:*/
  if ((err = pThreadImpl->resume()) != LB_THREAD_NO_ERROR) {
	printf("lbThread::resume failed\n");
  }
/*...sTHREAD_VERBOSE:2:*/
#ifdef THREAD_VERBOSE
printf  ("lbThread::resume done");
LOG  ("lbThread::resume done");
#endif
/*...e*/
  return err;
/*...e*/
}

lbThreadError lbThread::stop() {
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
        LOG("Thread module initialization failed: impossible to allocate index in thread local storage");

        return 0;
    }
    // main thread doesn't have associated wxThread object, so store 0 in the
    // TLS instead
    if ( !::TlsSetValue(s_tlsThisThread, (LPVOID)0) )
    {
        ::TlsFree(s_tlsThisThread);
        s_tlsThisThread = 0xFFFFFFFF;

        LOG("Thread module initialization failed: can not store value in thread local storage");

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
LOG("lbThread::OnExit() called");
#endif
    if ( !::TlsFree(s_tlsThisThread) )
    {
        LOG("lbThreadModule::OnExit: TlsFree failed.");
    }
#ifdef THREAD_VERBOSE
LOG("lbThread::OnExit() leave");
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

DWORD lbGetCurrentThreadId() {
#ifdef WINDOWS
	return ::GetCurrentThreadId();
#else
#error "Only Windows target is supported"
#endif
}

DWORD lbGetCurrentProcessId() {
#ifdef WINDOWS
	return ::GetCurrentProcessId();
#else
#error "Only Windows target is supported"
#endif
}

#define LB_TOOLS_DLL

#include <lbInclude.h>

int lbThread::threadCount = 0;

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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        char buf[100];
        
        sprintf(buf, "lbThreadInternal::getHandle returns %s" , (lb_hThread == NULL) ? "NULL" : "Not NULL");
        LOG(buf);
#endif
/*...e*/
    	return lb_hThread; 
    }
    DWORD  getId() const { 
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
/*...sVERBOSE:0:*/
	#ifdef VERBOSE
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
#ifdef VERBOSE
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
/*...sVERBOSE:0:*/
    #ifdef VERBOSE
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbThreadInternal::WinThreadStart: Calling (DWORD)thread->Entry()");
printf("lbThreadInternal::WinThreadStart: Calling (DWORD)thread->Entry()\n");
#endif
/*...e*/

    if (thread == NULL) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbThreadInternal::WinThreadStart: Null pointer: thread");
printf("lbThreadInternal::WinThreadStart: Null pointer: thread\n");
#endif
/*...e*/
    }
    
    DWORD ret = (DWORD)thread->Entry();

/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbThreadInternal::WinThreadStart: Returning from (DWORD)thread->Entry()\n");
printf("lbThreadInternal::WinThreadStart: Returning from (DWORD)thread->Entry()\n");
#endif
/*...e*/

    //thread->p_ThreadImpl->SetState(STATE_EXITED);
    LOG("lbThreadInternal: Do not call OnExit()");
    //thread->OnExit();

    delete thread;

    return ret;
}
/*...e*/
/*...e*/
/*...slbThread:0:*/
lbThread::lbThread() {
LOGENABLE("lbThread::lbThread()");
	if (threadCount == 0) {
#ifdef VERBOSE
		LOG("lbThread::lbThread(): OnInit() must be called");
#endif
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
		OnExit();
	}
	if (pThreadImpl != NULL) delete pThreadImpl;
}

lbThreadError lbThread::create() {
  lbThreadError err;
/*...sCreate if needed:2:*/
  if (pThreadImpl->getHandle() == NULL) {
/*...sVERBOSE:2:*/
#ifdef VERBOSE
	printf("lbThread::run will create a new thread\n");
	LOG("lbThread::run will create a new thread");
#endif
/*...e*/

/*...sVERBOSE:2:*/
#ifdef VERBOSE
	if (this == NULL) {
		printf("lbThreadInternal::Create: Got a null pointer (this).\n");
	}
#endif
/*...e*/

  	if ((err = pThreadImpl->Create(this)) != LB_THREAD_NO_ERROR) {
/*...sVERBOSE:2:*/
#ifdef VERBOSE
	printf("lbThread::run creation of thread failed\n");
	LOG("lbThread::run creation of thread failed");
#endif
/*...e*/
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
/*...sVERBOSE:2:*/
#ifdef VERBOSE
	printf("lbThread::resume failed\n");
#endif
/*...e*/
  }
/*...sVERBOSE:2:*/
#ifdef VERBOSE
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
    if ( !::TlsFree(s_tlsThisThread) )
    {
        LOG("lbThreadModule::OnExit: TlsFree failed.");
    }

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


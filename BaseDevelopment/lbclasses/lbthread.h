#ifndef LB_TOOLS
#define LB_TOOLS

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_CONTAINER_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...stypedef lbMutexError:0:*/
typedef enum
{
  LB_MUTEX_NO_ERROR = 0,
  LB_MUTEX_ERROR
} lbMutexError;
/*...e*/

/*...stypedef lbThreadError:0:*/
typedef enum
{
  LB_THREAD_NO_ERROR = 0,
  LB_THREAD_ERROR
} lbThreadError;
/*...e*/

/*...sclass DLLEXPORT lbMutex:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

class DLLEXPORT lbMutex
{
public:
        lbMutex();
        virtual ~lbMutex();

        void CreateMutex(int name);
        void DeleteMutex(int name);
        void Enter();
        void Release();
private:

#ifdef WINDOWS
        HANDLE mutex;
#endif
#ifdef __WXGTK__
        int    mutex;
        int    _name;
#endif
};
/*...e*/



class DLLEXPORT lbLock;

class DLLEXPORT lbCritSect {
public:
	lbCritSect();
	virtual ~lbCritSect();

private:
	//lbCritSect(const lbCritSect&) {}

protected:
	lbErrCodes enter();
	lbErrCodes leave();
	
	void* critsect;	
	
	friend class lbLock;
};

class DLLEXPORT lbLock {
public:
	lbLock(lbCritSect& _cso, char* _name);
	virtual ~lbLock();
private:
	lbLock() {}
	lbLock(const lbLock&) {}

	char* name;
	lbCritSect* cso;
};

class lbThreadInternal; // For various operating systems

/*...sclass DLLEXPORT lbThread:0:*/
class DLLEXPORT lbThread {
public:
	lbThread();
	virtual ~lbThread();
	

	lbThreadError create();

	lbThreadError run(); 
	lbThreadError stop();
	
	lbThreadError pause();
	lbThreadError resume();

	/**
	 * Call this function once a process
	 */
	int OnInit();
	
	/**
	 * Cleanup at process end
	 */
	void OnExit();
	
	/**
	 * Implementation of a specific thread must implement this
	 */
//	static DWORD WinThreadStart(lbThread *thread);

protected:

	// entry point for the thread - called by Run() and executes in the context
	// of this thread.
	virtual void *Entry() = 0;

private:
//	HANDLE lb_hThread;	
	DWORD  lb_ThreadId;

        // no copy ctor/assignment operator
        lbThread(const lbThread&);
        lbThread& operator=(const lbThread&);

        friend class lbThreadInternal;

        // the (platform-dependent) thread class implementation
        lbThreadInternal *pThreadImpl;	
        
        static int threadCount;
};



/*...e*/

#ifdef __cplusplus
extern "C" {
#endif

DWORD DLLEXPORT lbGetCurrentThreadId();
DWORD DLLEXPORT lbGetCurrentProcessId();

#ifdef __cplusplus
}
#endif


#endif

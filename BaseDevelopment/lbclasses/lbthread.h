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

#ifdef WINDOWS
#include <windows.h>
#endif

#include <lbInterfaces.h>

/*...stypedef lbMutexError:0:*/
typedef enum
{
  LB_MUTEX_NO_ERROR = 0,
  LB_MUTEX_ERROR
} lbMutexError;
/*...e*/

/*...sclass DLLEXPORT lbMutex:0:*/

class lbMutex : public lb_I_Mutex
{
public:
        lbMutex();
        virtual ~lbMutex();

        virtual void createMutex(int name);
        virtual void deleteMutex(int name);
        virtual void enter();
        virtual void release();
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

/*...sclass lbCritSect\44\ lbLock:0:*/
class DLLEXPORT lbLock;

class lbCritSect : public lb_I_CriticalSection {
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

class lbLock : public lb_I_Lock {
public:
	lbLock(lbCritSect& _cso, char* _name);
	virtual ~lbLock();
protected:
	lbLock() {}
	lbLock(const lbLock&) {}

	char* name;
	lbCritSect* cso;
};
/*...e*/


class lbThreadInternal; // For various operating systems

/*...sclass DLLEXPORT lbThread:0:*/
class DLLEXPORT lbThread : public lb_I_Thread {
public:
	lbThread();
	virtual ~lbThread();
	

	virtual lbErrCodes LB_STDCALL create();

	virtual lbErrCodes LB_STDCALL run(); 
	virtual lbErrCodes LB_STDCALL stop();
	
	virtual lbErrCodes LB_STDCALL pause();
	virtual lbErrCodes LB_STDCALL resume();

	/**
	 * Call this function once a process
	 */
	int LB_STDCALL OnInit();
	
	/**
	 * Cleanup at process end
	 */
	void LB_STDCALL OnExit();
	
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

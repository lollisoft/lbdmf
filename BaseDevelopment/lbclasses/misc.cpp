/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.10 $
 * $Name:  $
 * $Id: misc.cpp,v 1.10 2001/08/18 07:34:48 lolli Exp $
 * $Log: misc.cpp,v $
 * Revision 1.10  2001/08/18 07:34:48  lolli
 * Current version runs again. Module management is not ready.
 *
 * Revision 1.9  2001/07/11 16:04:35  lolli
 * First version of module management that hold's a little stresstest
 *
 * Revision 1.8  2001/05/04 17:16:25  lolli
 * Use of MACRO DECLARE_FUNCTOR works.
 * Removed unused code
 *
 * Revision 1.7  2001/05/01 15:51:52  lolli
 * First instance could be loaded over the new module management
 *
 * Revision 1.6  2001/04/13 07:39:29  lolli
 * Commit for backup
 *
 * Revision 1.5  2001/03/14 20:52:51  lolli
 * Compiles and links now, but it will not run
 *
 * Revision 1.4  2000/11/14 22:40:52  lolli
 * Minor changes
 *
 * Revision 1.3  2000/10/20 06:07:56  lolli
 * test1
 *
 * Revision 1.2  2000/10/20 06:04:08  lolli
 * test
 *
 * Revision 1.1  2000/07/06 06:20:10  lolli
 * Readded (possibly to new location)
 *
 * Revision 1.7  2000/03/16 08:58:07  lolli
 * Version crashes
 *
 * Revision 1.6  2000/01/18 21:13:17  lolli
 * Current version
 *
 * Revision 1.5  1999/12/01 20:00:48  lolli
 * direct logging activated again
 *
 * Revision 1.4  1999/10/12 06:37:30  Lothar_Behrens
 * Added logging and a log class, lb_sleep changed
 *
 **************************************************************/
/*...e*/

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#include <iostream.h>
#include <stdio.h>
#include <time.h>

//#include <lbInclude.h>

#include <stdarg.h>
#include <windows.h>
//#include <windef.h>
//#include <winbase.h>

#include <lbInterfaces.h>
#include <lbConfigHook.h>
#include <lbThread.h>
#include <lb_misc.h>

/*...sclass lbLog:0:*/
class lbLog : public lb_I_Log {

/*...spublic:0:*/
public:

    lbLog();
    lbLog(int l);

    virtual ~lbLog() {}
/*...e*/


    DECLARE_LB_UNKNOWN()

/*...slb_I_Log:0:*/
    virtual void LB_STDCALL log(const char *msg, long line, char* file);

    virtual void LB_STDCALL logdirect(const char *msg, char *f, int level);
    
    virtual void LB_STDCALL log(int log);

    virtual void LB_STDCALL enable(char *where);
    
    virtual void LB_STDCALL disable(char *where);
    
    virtual void LB_STDCALL event_begin(char *event);

    virtual void LB_STDCALL event_end(char *event);

    virtual void LB_STDCALL setPrefix(char* p);
/*...e*/

/*...sprivate:0:*/
    private:

    static char prefix[100];
    static int level;    
    static int doLog;
    static int firstlog;
    static clock_t start_time, end_time;
    static char lastevent[100];
    static int beinlog;
    static char f[100];
    static lb_I_Mutex* mutex;
/*...e*/

};
/*...e*/

#ifndef LOG_DEFINED
#define LOG_DEFINED

int lbLog::level = 0;
int lbLog::firstlog = 0;
int lbLog::beinlog = 0;
char lbLog::f[100];
clock_t lbLog::start_time, lbLog::end_time;
int lbLog::doLog = FALSE;
char lbLog::prefix[100];
lb_I_Mutex* lbLog::mutex;

//lb_I_CritSect sect;

/*...sbla:0:*/
#ifdef bla
lbErrCodes DLLEXPORT LB_STDCALL instanceOfLogger(lb_I_Unknown*& uk) {
        CL_LOG("instanceOfLogger() called and will create the requested instance");
        
        lbLog* logger = new lbLog();
        uk = NULL;
        
        if (logger->queryInterface("lb_I_Unknown", (void**) &uk) != ERR_NONE) {
                CL_LOG("Failed to create unknown reference to instance of lbLog!");
                return ERR_FUNCTOR;
        }
        
        return ERR_NONE;
}
#endif
/*...e*/

IMPLEMENT_FUNCTOR(instanceOfLogger, lbLog)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLog)
        ADD_INTERFACE(lb_I_Log)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLog::setData(lb_I_Unknown* uk) {
        CL_LOG("lbLog::setData(...) not implemented yet");
        return ERR_NOT_IMPLEMENTED;
}


/*...slbLog\58\\58\lbLog\40\\41\:0:*/
lbLog::lbLog() {
//lbLock lbLock(sect);
	manager = NULL;
	printf("Try to log direct\n");
        strcpy(f, "c:\\log\\wsmaster.log");
        printf("Created formatted string\n");
        logdirect("lbLog::lbLog(): Creating mutex for logfile", f, level);
	printf("Logged\n");
        if (firstlog == 0) {
        	printf("Create mutex\n");
                mutex = new lbMutex();
                mutex->createMutex(LB_LOGFILE_MUTEX);
        	printf("Created\n");
        }

        firstlog = 1;
        doLog = 1;

	char buf[100] = "";
	printf("Leave ctor\n");
}
/*...e*/
/*...slbLog\58\\58\lbLog\40\int l\41\:0:*/
lbLog::lbLog(int l) {
//lbLock lbLock(sect);
        strcpy(f, "c:\\log\\wsmaster.log");
//        logdirect("lbLog::lbLog(int l): Creating mutex for logfile", f, level);

        if (firstlog == 0) {
                mutex = new lbMutex();
                mutex->createMutex(LB_LOGFILE_MUTEX);
        }

        firstlog = 1;
        doLog = l;
        CL_LOG("lbLog::lbLog(): Creating mutex for logfile");
    }
/*...e*/
/*...slbLog\58\\58\logdirect\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbLog::logdirect(const char *msg, char *f, int level) {
                FILE *fp;
                fp = fopen( f, "a" );
                if( fp != NULL ) {
                        char buf[100];
                        buf[0] = 0;
                        
                        int l = level;
                        
                        while (l > 0) {
                                sprintf(buf, "%s%s", buf, "    ");
                                l--;
                        }
                        
                        fprintf( fp, "Thread %d\t:%s%s%s\n", lbGetCurrentThreadId(), prefix, buf, msg);
                }
        
                fclose( fp );
}
/*...e*/
/*...slbLog\58\\58\log\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbLog::log(const char *msg, long line, char* file) {
//lbLock lbLock(sect, "lbLockSection");
printf("Called lbLog::log(...)\n");
        if (firstlog == 0) lbLog log = lbLog();
printf("Enter mutex\n");
        mutex->enter(); 
printf("Entered mutex\n");
        
        if (doLog == TRUE) {
                char *m = (char*) malloc(strlen(msg)+sizeof(line)+strlen(file)+10);

                sprintf(m, "%s: %d - %s", file, line, msg);
                printf("Call logdirect\n");
                logdirect(m, f, level);
                printf("Called logdirect\n");
                free(m);
        }
        mutex->release();
printf("Released mutex\n");
}
/*...e*/
/*...slbLog\58\\58\log\40\int log\41\:0:*/
void LB_STDCALL lbLog::log(int log) {
        if (firstlog == 0) lbLog log = lbLog();
        doLog = log;
}
/*...e*/
/*...slbLog\58\\58\setPrefix\40\char\42\ p\41\:0:*/
void LB_STDCALL lbLog::setPrefix(char* p) {
//cout << "lbLog::setPrefix(char* p) called" << endl;
        {
                //lbLock lbLock(sect, "lbLockSection");
                strcpy(prefix, p);
        }
}
/*...e*/
/*...slbLog\58\\58\enable\40\char \42\where\41\:0:*/
void LB_STDCALL lbLog::enable(char *where) {
        char buf[100];
        doLog = TRUE;
        
        if (firstlog == 0) lbLog log = lbLog();
        
        mutex->enter();

        sprintf(buf, "Log is enabled at %s", where);
//      level++;
        logdirect(buf, f, level);
//      level++;
        
        mutex->release();
}
/*...e*/
/*...slbLog\58\\58\disable\40\char \42\where\41\:0:*/
void LB_STDCALL lbLog::disable(char *where) {
        char buf[100];
        
        if (firstlog == 0) lbLog log = lbLog();
        
        mutex->enter();
        
        if (level <= 0) {
                logdirect("lbLog: Function sequence error. Disable called before enable!", f, 0);
                return;
        }
        
        doLog = FALSE;
        sprintf(buf, "Log is disabled at %s", where);
//      level--;
        logdirect(buf, f, level);
//      level--;

        mutex->release();
}
/*...e*/
/*...slbLog\58\\58\event_begin\40\char \42\event\41\:0:*/
void LB_STDCALL lbLog::event_begin(char *event) {
        if (firstlog == 0) lbLog log = lbLog();
        if (doLog == TRUE) {
            beinlog = 1;
            start_time = clock();

            CL_LOG(event);
    }
}
/*...e*/
/*...slbLog\58\\58\event_end\40\char \42\event\41\:0:*/
void LB_STDCALL lbLog::event_end(char *event) {
        char buf[100];
        if (firstlog == 0) lbLog log = lbLog();

        if (doLog == TRUE) {
                beinlog = 0;
                end_time = clock();
        
                FILE *fp;

                if ((end_time - start_time) > 5)
                {
                        fp = fopen( f, "a" );
                        if( fp != NULL ) {
                                // rest of code goes here
        
                                fprintf( fp, "Message %s: Duration\tProcess\t%d\t%u\n",
                                event, GetCurrentProcessId(), end_time - start_time);
                        }
                        fclose( fp );
                }
        }
    }
/*...e*/


#endif // LOG_DEFINED

#ifdef __WXGTK__
void delay(long mikrosek)
{
        struct timeval timeout;

        timeout.tv_sec = mikrosek / 1000000;
        timeout.tv_usec = mikrosek % 1000000;
        select (0, NULL, NULL, NULL, &timeout);
}
#endif


void lb_sleep(int ms)
{
#ifdef WINDOWS
        ::Sleep(ms);
#endif
#ifdef __WXGTK__
        delay(ms * 1000);
#endif
}

/**************************************************************
 * $Locker:  $
 * $Revision: 1.1 $
 * $Name:  $
 * $Id: lb_misc.h,v 1.1 2000/07/06 06:19:40 lolli Exp $
 * $Log: lb_misc.h,v $
 * Revision 1.1  2000/07/06 06:19:40  lolli
 * Readded (possibly to new location)
 *
 * Revision 1.6  2000/03/16 08:58:07  lolli
 * Version crashes
 *
 * Revision 1.5  2000/01/18 21:13:17  lolli
 * Current version
 *
 * Revision 1.4  1999/10/12 06:34:47  Lothar_Behrens
 * Added logging / and a new class for debug via log
 *
 **************************************************************/

#ifndef _MISC_
#define _MISC_

#include <time.h>
#include <string.h>
#include <iostream.h>
#include <stdio.h>

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

#ifdef __cplusplus
extern "C" {
#endif

void DLLEXPORT lb_sleep(int ms);
#ifdef __cplusplus
}
#endif

#define TRUE 1
#define FALSE 0

class lbMutex;

class DLLEXPORT lbLog {

public:

    lbLog();
    lbLog(int l);

    static void log(const char *msg, long line, char* file);

    static void logdirect(const char *msg, char *f, int level);
    
    static void log(int log);

    static void enable(char *where);
    
    static void disable(char *where);
    
    static void event_begin(char *event);

    static void event_end(char *event);

    static void setPrefix(char* p);

    private:

    static char prefix[100];
    static int level;    
    static int doLog;
    static int firstlog;
    static clock_t start_time, end_time;
    static char lastevent[100];
    static int beinlog;
    static char f[100];
    static lbMutex* mutex;
};

#define LOG(msg)	 lbLog::log(msg, __LINE__, __FILE__)
#define LOGENABLE        lbLog::enable
#define LOGDISABLE       lbLog::disable
#define LOGSTART         lbLog::event_begin
#define LOGEND           lbLog::event_end
#define LOGPREFIX(a)     lbLog::setPrefix(a)

extern lbCritSect sect;

#endif

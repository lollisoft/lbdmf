/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.2 $
 * $Name:  $
 * $Id: lb_misc.h,v 1.2 2001/02/06 20:38:18 lolli Exp $
 * $Log: lb_misc.h,v $
 * Revision 1.2  2001/02/06 20:38:18  lolli
 * Commit for backup the data
 *
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
/*...e*/

#ifndef _MISC_
#define _MISC_

/*...sincludes:0:*/
#include <time.h>
#include <string.h>
#include <iostream.h>
#include <stdio.h>
/*...e*/

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

/*...sifdef __cplusplus:0:*/
#ifdef __cplusplus
extern "C" {
#endif
/*...e*/
void DLLEXPORT lb_sleep(int ms);
/*...sendif __cplusplus:0:*/
#ifdef __cplusplus
}
#endif
/*...e*/

#define TRUE 1
#define FALSE 0

class lbMutex;

/*...sclass lbLog:0:*/
class DLLEXPORT lbLog : public lb_I_Log {

/*...spublic:0:*/
public:

    lbLog();
    lbLog(int l);

    void log(const char *msg, long line, char* file);

    void logdirect(const char *msg, char *f, int level);
    
    void log(int log);

    void enable(char *where);
    
    void disable(char *where);
    
    void event_begin(char *event);

    void event_end(char *event);

    void setPrefix(char* p);
/*...e*/

/*...sprivate:0:*/
    private:

    char prefix[100];
    int level;    
    int doLog;
    int firstlog;
    clock_t start_time, end_time;
    char lastevent[100];
    int beinlog;
    char f[100];
    lbMutex* mutex;
/*...e*/

/*...slb_I_Log:0:*/
/*...e*/


};
/*...e*/


extern lbCritSect sect;

#endif

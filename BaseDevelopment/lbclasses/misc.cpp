/**************************************************************
 * $Locker:  $
 * $Revision: 1.3 $
 * $Name:  $
 * $Id: misc.cpp,v 1.3 2000/10/20 06:07:56 lolli Exp $
 * $Log: misc.cpp,v $
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

#define LB_CONTAINER_DLL

#include <iostream.h>
#include <stdio.h>
#include <lbInclude.h>
int lbLog::level = 0;
int lbLog::firstlog = 0;
int lbLog::beinlog = 0;
char lbLog::f[100];
clock_t lbLog::start_time, lbLog::end_time;
int lbLog::doLog = FALSE;
char lbLog::prefix[100];
lbMutex* lbLog::mutex;

lbCritSect sect;

lbLog::lbLog() {
//lbLock lbLock(sect);
        strcpy(f, "c:\\log\\wsmaster.log");
//        logdirect("lbLog::lbLog(): Creating mutex for logfile", f, level);

	if (firstlog == 0) {
        	mutex = new lbMutex();
        	mutex->CreateMutex(LB_LOGFILE_MUTEX);
        }

        firstlog = 1;
        doLog = 1;
	LOG("lbLog::lbLog(): Creating mutex for logfile");
    }
    
lbLog::lbLog(int l) {
//lbLock lbLock(sect);
        strcpy(f, "c:\\log\\wsmaster.log");
//        logdirect("lbLog::lbLog(int l): Creating mutex for logfile", f, level);

	if (firstlog == 0) {
        	mutex = new lbMutex();
        	mutex->CreateMutex(LB_LOGFILE_MUTEX);
        }

        firstlog = 1;
        doLog = l;
        LOG("lbLog::lbLog(): Creating mutex for logfile");
    }

void lbLog::logdirect(const char *msg, char *f, int level) {
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

void lbLog::log(const char *msg, long line, char* file) {
//lbLock lbLock(sect, "lbLockSection");
	if (firstlog == 0) lbLog log = lbLog();

	mutex->Enter();	
	
	if (doLog == TRUE) {
		char *m = (char*) malloc(strlen(msg)+sizeof(line)+strlen(file)+10);

		sprintf(m, "%s: %d - %s", file, line, msg);
		logdirect(m, f, level);
		free(m);
	}
	mutex->Release();
}

void lbLog::log(int log) {
	if (firstlog == 0) lbLog log = lbLog();
	doLog = log;
}

void lbLog::setPrefix(char* p) {
//cout << "lbLog::setPrefix(char* p) called" << endl;
	{
		lbLock lbLock(sect, "lbLockSection");
		strcpy(prefix, p);
	}
}

void lbLog::enable(char *where) {
	char buf[100];
	doLog = TRUE;
	
	if (firstlog == 0) lbLog log = lbLog();
	
	mutex->Enter();

	sprintf(buf, "Log is enabled at %s", where);
//	level++;
	logdirect(buf, f, level);
//	level++;
	
	mutex->Release();
}

void lbLog::disable(char *where) {
	char buf[100];
	
	if (firstlog == 0) lbLog log = lbLog();
	
	mutex->Enter();
	
	if (level <= 0) {
		logdirect("lbLog: Function sequence error. Disable called before enable!", f, 0);
		return;
	}
	
	doLog = FALSE;
	sprintf(buf, "Log is disabled at %s", where);
//	level--;
	logdirect(buf, f, level);
//	level--;

	mutex->Release();
}

void lbLog::event_begin(char *event) {
	if (firstlog == 0) lbLog log = lbLog();
	if (doLog == TRUE) {
            beinlog = 1;
            start_time = clock();

            LOG(event);
    }
}

void lbLog::event_end(char *event) {
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

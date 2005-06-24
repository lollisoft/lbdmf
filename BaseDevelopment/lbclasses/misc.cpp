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

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.39 $
 * $Name:  $
 * $Id: misc.cpp,v 1.39 2005/06/24 23:09:49 lollisoft Exp $
 * $Log: misc.cpp,v $
 * Revision 1.39  2005/06/24 23:09:49  lollisoft
 * Changes to build with new wxWidgets version 2.6.1.
 * Added fallback to hardcoded settings, if no environment
 * variables are found. Logging changed to reside in a
 * $(HOME)/log directory.
 *
 * GUI application build process enhanced to also make the
 * bundle. App runs from clicking on the desktop icon.
 *
 * Revision 1.38  2005/05/10 20:20:38  lollisoft
 * Include files changed to be more actially language compilant
 *
 * Revision 1.37  2005/05/04 22:07:34  lollisoft
 * _CL_LOG replaced with _CL_VERBOSE
 *
 * Revision 1.36  2005/05/03 21:11:35  lollisoft
 * Try using logger class as singleton.
 *
 * Revision 1.35  2005/05/01 01:12:36  lollisoft
 * Found a really big memory leak. It happens due to missing setup of ref variable
 * in lbFunctorEntity class of lbModule.cpp.
 *
 * Due to the fact, that I use this class for each instance retrival, it wasted
 * much memory. More: See documentation in that class.
 *
 * Revision 1.34  2005/03/31 09:02:45  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.33  2005/01/24 22:49:30  lollisoft
 * Logging is unclean...
 *
 * Revision 1.32  2005/01/23 13:43:05  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.31  2005/01/22 11:52:24  lollisoft
 * Removed log messages
 *
 * Revision 1.30  2005/01/21 14:56:44  lollisoft
 * Removed some unused log messages
 *
 * Revision 1.29  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.28  2003/08/16 18:07:00  lollisoft
 * Added my new address due to move
 *
 * Revision 1.27  2003/04/28 20:33:43  lollisoft
 * Moved back to watcom
 *
 * Revision 1.26  2002/12/29 16:05:10  lolli
 * Intent to go public
 *
 * Revision 1.25  2002/12/09 19:37:42  lolli
 * removed debugging messages
 *
 * Revision 1.24  2002/12/08 23:22:56  lothar
 * Possible bug was in the usage of realloc
 *
 * Revision 1.23  2002/12/08 17:07:23  lothar
 * More tries to run under linux
 *
 * Revision 1.22  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.21  2002/10/17 17:34:44  lolli
 * Use of _CL_VERBOSE macro
 *
 * Revision 1.20  2002/10/11 17:20:59  lolli
 * Before CL_LOG change
 *
 * Revision 1.19  2002/10/08 16:00:29  lolli
 * Logging macro works now also for misc.cpp
 *
 * Revision 1.18  2002/10/04 17:11:55  lolli
 * Whats wrong ?
 *
 * Revision 1.17  2002/10/04 16:53:14  lolli
 * Replaced old LOG macro with the new
 * _CL_VERBOSE << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.16  2002/09/19 19:34:14  lolli
 * Buggy version - only, if menu is really created
 *
 * Revision 1.15  2002/04/15 18:24:33  lolli
 * Huge changes - works good
 *
 * Revision 1.14  2002/02/25 06:15:35  lolli
 * Much changes
 * Program seems to run, but performance is very slow
 *
 * Revision 1.13  2001/12/12 18:44:09  lothar
 * Test group users under linux
 *
 * Revision 1.12  2001/12/12 17:12:45  lothar
 * Hehe - runs on linux
 *
 * Revision 1.11  2001/10/04 19:28:34  lolli
 * Current version seems to work good (without big memory holes)
 *
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

#define __MISC

/*...sIncludes:0:*/
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <stdarg.h>
#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            
#include <stdlib.h>
#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>
#include <lbInterfaces.h>

#include <lbthread.h>
#include <lb_misc.h>
#include <fstream>
/*...e*/

#ifndef  LOG_DEFINED
#define  LOG_DEFINED

/*...sclass lbLog:0:*/
class lbLog : public lb_I_Log {

/*...spublic:0:*/
public:

    lbLog();
    lbLog(int l);

    virtual ~lbLog() { 
    	if (logmessage != NULL) {
    		free(logmessage);
    		logmessage = NULL;
    	}
    }
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
    
    
    virtual lb_I_Log& LB_STDCALL operator<< (const int i);
    virtual lb_I_Log& LB_STDCALL operator<< (const char c);
    virtual lb_I_Log& LB_STDCALL operator<< (const char* string);
/*...e*/

/*...sprivate:0:*/
    private:

	void LB_STDCALL realloc(int add_size);

    static char prefix[100];
    static int level;    
    static int doLog;
    static int firstlog;
    static clock_t start_time, end_time;
    static char lastevent[100];
    static int beinlog;
    static char f[PATH_MAX];
    static lb_I_Mutex* mutex;
    static char* logmessage;
    static int lastsize;
/*...e*/

};
/*...e*/


int lbLog::level = 0;
int lbLog::firstlog = 0;
int lbLog::beinlog = 0;
char lbLog::f[PATH_MAX];
char* lbLog::logmessage = NULL;
int lbLog::lastsize = 0;
clock_t lbLog::start_time, lbLog::end_time;
int lbLog::doLog = FALSE;
char lbLog::prefix[100];
lb_I_Mutex* lbLog::mutex;

//lb_I_CritSect sect;

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfLogger, lbLog)
#ifdef bla
/*...s:0:*/
lbErrCodes DLLEXPORT LB_FUNCTORCALL instanceOfLogger(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { 

	lbErrCodes err = ERR_NONE; 
        lbLog* instance = new lbLog(); 
        *uk = NULL; 
        instance->setFurtherLock(0); 
        if (m != NULL) { 
        	instance->setModuleManager(m, __FILE__, __LINE__); 
        } else { 
        	_CL_VERBOSE << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_ 
        } 
        
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { 
                _CL_VERBOSE << "Failed to create unknown reference to instance of " << 
                "lbLog" << ". Errcode is " << err LOG_ 
                if (err == ERR_STATE_FURTHER_LOCK) { 
                	_CL_VERBOSE << "ERR_STATE_FURTHER_LOCK" LOG_ 
                	return err; 
                } 
                return ERR_FUNCTOR; 
        } 

        return ERR_NONE; 
} 

/*...e*/
#endif

#ifdef __cplusplus
}
#endif            

// Logging macro does not work recursively
//#undef _CL_VERBOSE
//#define _CL_VERBOSE cerr
//#undef LOG_
//#define LOG_ << ""; }

BEGIN_IMPLEMENT_LB_UNKNOWN(lbLog)
        ADD_INTERFACE(lb_I_Log)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbLog::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbLog::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbLog\58\\58\lbLog\40\\41\:0:*/
lbLog::lbLog() {
//lbLock lbLock(sect);
		ref = STARTREF;
		manager = NULL;
        
		f[0] = 0;
		strcat(f, getLogDirectory());
#if defined (LINUX) || defined (OSX) || defined (UNIX)
		strcat(f, "/");
#endif
#if defined (WINDOWS)
		strcat(f, "\\");
#endif
		strcat(f, LOGFILE);
		
		
        logdirect("lbLog::lbLog(): Creating mutex for logfile\n", f, level);
        if (firstlog == 0) {
                mutex = new lbMutex();
                mutex->createMutex(LB_LOGFILE_MUTEX);
        }

        firstlog = 1;
        doLog = 1;
        logmessage = NULL;
        lastsize = 0;
        _CL_VERBOSE << "lbLog::lbLog() leaving" LOG_
}
/*...e*/
/*...slbLog\58\\58\lbLog\40\int l\41\:0:*/
lbLog::lbLog(int l) {
//lbLock lbLock(sect);
	logmessage = NULL;
	lastsize = 0;
	strcpy(f, LOGFILE);
//        logdirect("lbLog::lbLog(int l): Creating mutex for logfile", f, level);

        if (firstlog == 0) {
                mutex = new lbMutex();
                mutex->createMutex(LB_LOGFILE_MUTEX);
        }

        firstlog = 1;
        doLog = l;
        _CL_VERBOSE << "lbLog::lbLog(): Creating mutex for logfile" LOG_
	printf("lbLog::lbLog(int l) leaving\n");
    }
/*...e*/
/*...slbLog\58\\58\logdirect\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbLog::logdirect(const char *msg, char *f, int level) {
	logMessage(msg, f, level);
}
/*...e*/
/*...slbLog\58\\58\log\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbLog::log(const char *msg, long line, char* file) {
//lbLock lbLock(sect, "lbLockSection");

_CL_VERBOSE << "Do log a line..." LOG_

        if (firstlog == 0) {
        	lbLog log;// = lbLog();
        }
        mutex->enter(); 
        
        if (doLog == TRUE) {
    		printf("Malloc heap for logging message\n");
                char *m = (char*) malloc(strlen(msg)+sizeof(line)+strlen(file)+10);

                sprintf(m, "%s: %d - %s", file, line, msg);
                logdirect(m, f, level);
		printf("Freeing it\n");
                free((void*) m);
		printf("Have freed up memory of logging message\n");
        }
        mutex->release();
_CL_VERBOSE << "Done log a line..." LOG_
}
/*...e*/
/*...slbLog\58\\58\log\40\int log\41\:0:*/
void LB_STDCALL lbLog::log(int log) {
        if (firstlog == 0) {
        	lbLog log;// = lbLog();
        }
        doLog = log;
}
/*...e*/
/*...slbLog\58\\58\setPrefix\40\char\42\ p\41\:0:*/
void LB_STDCALL lbLog::setPrefix(char* p) {
//COUT << "lbLog::setPrefix(char* p) called" << ENDL;
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
        
        if (firstlog == 0) {
        	lbLog log;// = lbLog();
        }
        
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
        
        if (firstlog == 0) {
        	lbLog log;// = lbLog();
        }
        
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
        if (firstlog == 0) {
        	lbLog log;// = lbLog();
        }
        if (doLog == TRUE) {
            beinlog = 1;
            start_time = clock();

            _CL_VERBOSE << event LOG_
    }
}
/*...e*/
/*...slbLog\58\\58\event_end\40\char \42\event\41\:0:*/
void LB_STDCALL lbLog::event_end(char *event) {
       char buf[100];
       if (firstlog == 0) {
        	lbLog log;// = lbLog();
       }

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
                                event, lbGetCurrentProcessId(), end_time - start_time);
                        }
                        fclose( fp );
                }
        }
    }
/*...e*/

/**
 * My new - possible bugfree - log system
 */
 
void LB_STDCALL lbLog::realloc(int add_size) {
	if (logmessage == NULL) {
		char* buf = (char*) malloc(add_size);
		buf[0] = 0;
		logmessage = buf;
		//logmessage = (char*) ::realloc((void*) logmessage, add_size);
		lastsize = add_size;
	} else {
		char* buf = (char*) malloc(lastsize+add_size);
		buf[0] = 0;
		buf = strcpy(buf, logmessage);
		free(logmessage);
		logmessage = buf;
		//logmessage = (char*) ::realloc((void*) logmessage, lastsize+add_size);
		lastsize += add_size;
	}
} 
 
lb_I_Log& LB_STDCALL lbLog::operator<< (/*lb_I_Log* logger,*/ const int i) {
	char s[1000] = "";
	realloc(strlen(itoa(i)) + 1);
	lastsize = lastsize + strlen(itoa(i)) + 1;
	strcat(logmessage, itoa(i));
	return *this;
}
lb_I_Log& LB_STDCALL lbLog::operator<< (/*lb_I_Log* logger,*/ const char c) {
        realloc(lastsize + 2);
        lastsize = lastsize + 2;
        char add[2] = "";
        add[0] = c;
        strcat(logmessage, add);
        if (c == '\n') {
        	logdirect(logmessage, f, 0);
        	free(logmessage);
        	logmessage = NULL;
        	lastsize = 0;
        }
	return *this;
}

lb_I_Log& LB_STDCALL lbLog::operator<< (/*lb_I_Log* logger,*/ const char* string) {
	if (string != NULL) {
		realloc(lastsize+strlen(string) + 10);
		lastsize = lastsize + strlen(string) + 10;
		strcat(logmessage, string);
		
		if (strcmp(string, "\n") == 0) {
			logdirect(logmessage, f, 0);
			free(logmessage);
			logmessage = NULL;
			lastsize = 0;
		}
	} else {
		
	}
	return *this;
}


#endif //  LOG_DEFINED

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




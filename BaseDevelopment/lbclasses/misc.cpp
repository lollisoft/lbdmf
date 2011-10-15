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
			Ginsterweg 4

			65760 Eschborn (germany)
*/
/*...e*/

/*...sRevision history:0:*/
/**************************************************************
* $Locker:  $
* $Revision: 1.55 $
* $Name:  $
* $Id: misc.cpp,v 1.55 2011/10/15 13:14:05 lollisoft Exp $
* $Log: misc.cpp,v $
* Revision 1.55  2011/10/15 13:14:05  lollisoft
* Decided to make a hash cut and removed stuff that everywhere was the cause for crashes on Mac.
* Currently the code crashes on windows, but lets see how it is working on Mac.
*
* Revision 1.54  2011/09/25 09:30:14  lollisoft
* Many bugfixes like missing variable initialization. Used CppCheck for this to get rid of the random crashes.
* Only lbHook, lbModule, lbclasses and the Basetypes regression test (including headers and interfaces) are
* fixed. Other modules will follow.
*
* Revision 1.53  2011/06/18 17:29:55  lollisoft
* Changed all char* to const char* where a corresponding warning was generated.
*
* Revision 1.52  2011/02/27 10:30:36  lollisoft
* Changed all copyright entries addresses to match my current postal address.
*
* Revision 1.51  2011/01/16 21:44:42  lollisoft
* Removed printf code in LOG function.
*
* Revision 1.50  2010/04/25 21:37:09  lollisoft
* Successfully ported lbHook to MINGW compiler. There were only two issues
* I have identified: The enum problem as reported from Michal Necasek having
* different sizes and the interface ordering to be equal to implementing class
* declaration. But this only belongs to my UnitTest code yet.
*
* Aim of this is the ability to mix in MINGW modules for features Open Watcom
* didn't support yet and let me do this with minimal effort.
*
* Revision 1.49  2009/12/06 19:20:16  lollisoft
* Modified build process to use precompiled files.
* Corrected the long build time problem. It is located in the _LOG macro.
* Updated wxPropgrid to 1.4.9.1 and updated building against wxMSW 2.8.10.
*
* Build works, but running the application fails with not properly initialized error.
* (0xc0000005)
*
* Also updated the iss files for the new planned release.
*
* Revision 1.48  2009/03/04 17:40:07  lollisoft
* Added missing includes for openSuSE 11.1 version (GCC).
*
* Revision 1.47  2007/04/22 13:36:42  lollisoft
* Removed lb_sleep.
*
* Revision 1.46  2007/01/15 23:37:30  lollisoft
* Changed code that valgrind mentioned as using uninitialized variable in boolean expression
*
* Revision 1.45  2005/12/11 19:14:23  lollisoft
* Release changes for 0.6.0. Added todo entries.
*
* Revision 1.44  2005/12/02 00:28:43  lollisoft
* Deleting a row works for some tests. Deleting data in join queries is not tested
* and would propably not work. This is at least due to lack of creating a delete
* statement per related table.
*
* Now this deleting also includes the ability to reopen the query as needed.
* Form code is adopted to the case if there are no peek aheads are done
* while fetching new data.
*
* Code cleanup would be done later.
*
* Revision 1.43  2005/11/11 22:51:30  lollisoft
* Memory leaks removed. There are currently only 4 chunks leaky.
* These may be false positives, because one of them is an allocated
* wxMenu instance, I have not to delete after adding it to a wxMenuBar.
* wxMenuBar gets an owner (see wxWidgets documentation).
*
* Revision 1.42  2005/11/06 19:25:33  lollisoft
* All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
*
* Revision 1.41  2005/10/31 09:59:01  lollisoft
* Added support for mpatrol library, but it is deactivated. Use DEBUG_MEMORY=yes to activate it.
*
* Revision 1.40  2005/06/27 10:32:10  lollisoft
* Mostly changes to conio.h conflicts while XCode build
*
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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CLASSES_DLL
#include <lbclasses-module.h>
/*...e*/

#define __MISC

/*...sIncludes:0:*/

#include <iostream>
#include <stdio.h>
#include <time.h>

#ifdef _MSC_VER
#define PATH_MAX 512
#endif

#include <stdarg.h>
#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            
#include <stdlib.h>
	//#include <conio.h>
#include <limits.h>
#ifdef __cplusplus
}      
#endif            

#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbthread.h>
#include <lb_misc.h>
#include <fstream>
/*...e*/

#ifndef  LOG_DEFINED
#define  LOG_DEFINED

/*...sclass lbLog:0:*/
/// \brief Logging implementation. \todo Separate file to a base class.
class lbLog : public lb_I_Log {
public:
	virtual void LB_STDCALL logdirect(const char *msg, const char *f, int level);

	/*...slb_I_Log:0:*/
	virtual void LB_STDCALL log(const char *msg, long line, const char* file);
	virtual void LB_STDCALL log(int log);
	virtual void LB_STDCALL enable(const char *where);
	virtual void LB_STDCALL disable(const char *where);
	virtual void LB_STDCALL event_begin(const char *event);
	virtual void LB_STDCALL event_end(const char *event);
	virtual void LB_STDCALL setPrefix(const char* p);
	virtual lb_I_Log& LB_STDCALL operator<< (const int i);
	virtual lb_I_Log& LB_STDCALL operator<< (const long i);
	virtual lb_I_Log& LB_STDCALL operator<< (const char c);
	virtual lb_I_Log& LB_STDCALL operator<< (const char* string);
	virtual void LB_STDCALL setCustomLogFile(const char* name);
	/*...e*/

	DECLARE_LB_UNKNOWN()

	/*...spublic:0:*/
public:

	lbLog();
	lbLog(int l);

	virtual ~lbLog() { 
		if (logmessage != NULL) {
			free(logmessage);
			logmessage = NULL;
		}
		
		if (mutex) { 
			delete mutex;
		}
	}
	/*...e*/

	/*...sprivate:0:*/
private:

	void LB_STDCALL _realloc(int add_size);

	static char prefix[100];
	static int level;    
	static int doLog;
	static int firstlog;
	static clock_t start_time, end_time;
	static char lastevent[100];
	static int beinlog;
	static char f[PATH_MAX];
	static lbMutex* mutex;
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
lbMutex* lbLog::mutex;

//lb_I_CritSect sect;

#ifdef __cplusplus
extern "C" {       
#endif            

	IMPLEMENT_FUNCTOR(instanceOfLogger, lbLog)

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
	
	
	
	further_lock = 1;
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
	
	
	further_lock = 1;
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
void LB_STDCALL lbLog::logdirect(const char *msg, const char *f, int level) {
	logMessage(msg, f, level);
}
/*...e*/
void LB_STDCALL lbLog::setCustomLogFile(const char* name) {
	f[0] = 0;
	strcat(f, name);
}
/*...slbLog\58\\58\log\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbLog::log(const char *msg, long line, const char* file) {
	//lbLock lbLock(sect, "lbLockSection");

	_CL_VERBOSE << "Do log a line..." LOG_

	if (firstlog == 0) {
		lbLog log;// = lbLog();
	}
	mutex->enter(); 
	
	if (doLog == TRUE) {
		char *m = (char*) malloc(strlen(msg)+sizeof(line)+strlen(file)+10);

		sprintf(m, "%s: %ld - %s", file, line, msg);
		logdirect(m, f, level);
		free((void*) m);
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
void LB_STDCALL lbLog::setPrefix(const char* p) {
	//COUT << "lbLog::setPrefix(char* p) called" << ENDL;
	{
		//lbLock lbLock(sect, "lbLockSection");
		strcpy(prefix, p);
	}
}
/*...e*/
/*...slbLog\58\\58\enable\40\char \42\where\41\:0:*/
void LB_STDCALL lbLog::enable(const char *where) {
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
void LB_STDCALL lbLog::disable(const char *where) {
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
void LB_STDCALL lbLog::event_begin(const char *event) {
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
void LB_STDCALL lbLog::event_end(const char *event) {
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
				
				fprintf( fp, "Message %s: Duration\tProcess\t%ld\t%lu\n",
				event, lbGetCurrentProcessId(), end_time - start_time);
				fclose( fp );
			}
		}
	}
}
/*...e*/

/**
* My new - possible bugfree - log system
*/

void LB_STDCALL lbLog::_realloc(int add_size) {
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
	_realloc(strlen(itoa(i)) + 1);
	lastsize = lastsize + strlen(itoa(i)) + 1;
	strcat(logmessage, itoa(i));
	return *this;
}
lb_I_Log& LB_STDCALL lbLog::operator<< (/*lb_I_Log* logger,*/ const long i) {
	char buf[20];
	int len;
	sprintf(buf, "%ld", i);
	len = strlen(buf);
	_realloc(len + 1);
	lastsize = lastsize + len + 1;
	strcat(logmessage, buf);
	return *this;
}
lb_I_Log& LB_STDCALL lbLog::operator<< (/*lb_I_Log* logger,*/ const char c) {
	_realloc(lastsize + 2);
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
		_realloc(lastsize+strlen(string) + 10);
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


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
//#include <memory.h>
//#include <conio.h>

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


#ifndef  OUTPUTSTREAM_DEFINED
#define  OUTPUTSTREAM_DEFINED

/*...sclass lbOutputStream:0:*/
/// \brief Logging implementation. \todo Separate file to a base class.
class lbOutputStream : public lb_I_OutputStream {

/*...spublic:0:*/
public:

    lbOutputStream();

    virtual ~lbOutputStream() { 
    	if (logmessage != NULL) {
    		free(logmessage);
    		logmessage = NULL;
    	}
    	
    	if (mutex) { 
    		delete mutex;
    	}
		if (!isOpen) {
			fclose(fout);
		}
	}
/*...e*/


    DECLARE_LB_UNKNOWN()

/*...slb_I_OutputStream:0:*/
	void LB_STDCALL setFileName(char* name);

    virtual void LB_STDCALL logdirect(const char *msg, char *f, int level);
    
    virtual lb_I_OutputStream& LB_STDCALL operator<< (const int i);
    virtual lb_I_OutputStream& LB_STDCALL operator<< (const char c);
    virtual lb_I_OutputStream& LB_STDCALL operator<< (const char* string);
/*...e*/

/*...sprivate:0:*/
    private:

	void LB_STDCALL _realloc(int add_size);

    char f[PATH_MAX];
    lbMutex* mutex;
    char* logmessage;
    int lastsize;
	FILE*	fout;
	bool	isOpen;
/*...e*/

};
/*...e*/

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfOutputStream, lbOutputStream)

#ifdef __cplusplus
}
#endif            

// Logging macro does not work recursively
//#undef _CL_VERBOSE
//#define _CL_VERBOSE cerr
//#undef LOG_
//#define LOG_ << ""; }

BEGIN_IMPLEMENT_LB_UNKNOWN(lbOutputStream)
        ADD_INTERFACE(lb_I_OutputStream)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbOutputStream::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbOutputStream::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbOutputStream\58\\58\lbOutputStream\40\\41\:0:*/
lbOutputStream::lbOutputStream() {
//lbLock lbLock(sect);
		ref = STARTREF;
		manager = NULL;
		fout = NULL;
		isOpen = false;
        
		f[0] = 0;
		
        if (mutex == NULL) {
                mutex = new lbMutex();
                mutex->createMutex(LB_OUTPUTFILE_MUTEX);
        }

        logmessage = NULL;
        lastsize = 0;
}
/*...e*/
/*...slbOutputStream\58\\58\logdirect\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbOutputStream::logdirect(const char *msg, char *f, int level) {
	if (!isOpen) {
		fout = fopen(f, "a");
		if (!fout) {
			_CL_LOG << "ERROR: Input file not found!" LOG_
			return;
		}
		isOpen = true;
	}
	
	char buf[1000] = "";
	buf[0] = 0;
	
	int l = level;
	
	while (l > 0) {
		sprintf(buf, "%s%s", buf, "\t");
		l--;
	}
	
#ifdef WINDOWS                        
	fprintf( fout, "%s%s", buf, msg);
#endif
#if defined (OSX) || defined (LINUX) || defined(UNIX)
	fprintf( fout, "%s%s", buf, msg);
#endif						
}
/*...e*/
/**
 * My new - possible bugfree - log system
 */

void LB_STDCALL lbOutputStream::setFileName(char* name) {
	f[0] = 0;
	strncpy(f, name, PATH_MAX-1);
}
 
void LB_STDCALL lbOutputStream::_realloc(int add_size) {
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
 
lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (/*lb_I_OutputStream* logger,*/ const int i) {
	char s[1000] = "";
	_realloc(strlen(itoa(i)) + 1);
	lastsize = lastsize + strlen(itoa(i)) + 1;
	strcat(logmessage, itoa(i));
	return *this;
}
lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (/*lb_I_OutputStream* logger,*/ const char c) {
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

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (/*lb_I_OutputStream* logger,*/ const char* string) {
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


#endif //  OUTPUTSTREAM_DEFINED

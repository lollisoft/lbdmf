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
#include <iostream.h>
#include <stdio.h>
#include <time.h>
#include <fstream.h>

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
    	
	    	close();
	}
/*...e*/


    DECLARE_LB_UNKNOWN()

/*...slb_I_OutputStream:0:*/
	void LB_STDCALL setFileName(char* name);
	bool LB_STDCALL open();
	bool LB_STDCALL close();

	void LB_STDCALL logdirect(const char *msg, char *f, int level);
    
	lb_I_OutputStream& LB_STDCALL operator<< (const int i);
	lb_I_OutputStream& LB_STDCALL operator<< (const char c);
	lb_I_OutputStream& LB_STDCALL operator<< (const char* string);
/*...e*/

/*...sprivate:0:*/
    private:

	void LB_STDCALL _realloc(int add_size);

	char f[PATH_MAX];
	lbMutex* mutex;
	char* logmessage;
	int pre_lastsize;
	int lastsize;
	FILE*	fout;
	bool	isOpen;
	int	offset;

	ofstream* _ostream;

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
	_ostream = NULL;
}
/*...e*/
/*...slbOutputStream\58\\58\logdirect\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbOutputStream::logdirect(const char *msg, char *f, int level) {
}
/*...e*/

void LB_STDCALL lbOutputStream::setFileName(char* name) {
	f[0] = 0;
	strncpy(f, name, PATH_MAX-1);
}

bool LB_STDCALL lbOutputStream::close() {
	if (isOpen) {
		_ostream->close();
		delete _ostream;
		isOpen = false;
	}
	return true;
}
bool LB_STDCALL lbOutputStream::open() {
	if (!isOpen) {
		_ostream = new ofstream(f);
	}
	isOpen = true;
	return true;
}
 
void LB_STDCALL lbOutputStream::_realloc(int add_size) {
} 
 
lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const int i) {
	if (!isOpen) return *this;

	*_ostream << i;
	
	return *this;
}
lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const char c) {
	if (!isOpen) return *this;

	*_ostream << c;

	return *this;
}

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const char* string) {
	if (!isOpen) return *this;

	std::string s(string);

	*_ostream << endl << s << endl; 	

	return *this;
}


#endif //  OUTPUTSTREAM_DEFINED

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
#include <fstream>
#include <stdio.h>
#include <time.h>

#ifdef __WATCOMC__
#include <string.hpp>
#endif

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
#include <fstream.h>
/*...e*/

#ifndef  ISTREAM_DEFINED
#define  ISTREAM_DEFINED

/*...sclass lbInputStream:0:*/
class lbInputStream : public lb_I_InputStream {

/*...spublic:0:*/
public:

    lbInputStream();

    virtual ~lbInputStream() { 
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

/*...slb_I_InputStream:0:*/

	void LB_STDCALL setFileName(char* name);
	const char* LB_STDCALL getFileName();
	bool LB_STDCALL open();
	bool LB_STDCALL close();
	
	bool LB_STDCALL read();
    
	lb_I_InputStream& LB_STDCALL operator>> (int& i);
	lb_I_InputStream& LB_STDCALL operator>> (char& c);
	lb_I_InputStream& LB_STDCALL operator>> (char*& string);
/*...e*/

/*...sprivate:0:*/
	private:

	void LB_STDCALL _realloc(int add_size);

	char f[PATH_MAX];
	static lbMutex* mutex;
	char* logmessage;
	int lastsize;
	FILE*	fin;
	bool	isOpen;
	
	void*	readBuffer;
	int	max_readBufferSize;
	int	readBufferSize;
	int	offset;
	ifstream* _istream;

/*...e*/

};
/*...e*/


lbMutex* lbInputStream::mutex;

//lb_I_CritSect sect;

#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOfInputStream, lbInputStream)

#ifdef __cplusplus
}
#endif            

// Logging macro does not work recursively
//#undef _CL_VERBOSE
//#define _CL_VERBOSE cerr
//#undef LOG_
//#define LOG_ << ""; }

BEGIN_IMPLEMENT_LB_UNKNOWN(lbInputStream)
	ADD_INTERFACE(lb_I_Stream)
        ADD_INTERFACE(lb_I_InputStream)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbInputStream::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbInputStream::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbInputStream\58\\58\lbInputStream\40\\41\:0:*/
lbInputStream::lbInputStream() {
//lbLock lbLock(sect);
	ref = STARTREF;
	manager = NULL;
	fin = NULL;
	readBuffer = NULL;
	readBufferSize = 0;
	offset = 0;
	max_readBufferSize = 100;
	isOpen = false;
        f[0] = 0;

	_istream = NULL;
		
	if (mutex == NULL) {
                mutex = new lbMutex();
                mutex->createMutex(LB_INPUTFILE_MUTEX);
        }

        logmessage = NULL;
        lastsize = 0;
}
/*...e*/
void LB_STDCALL lbInputStream::setFileName(char* name) {
	f[0] = 0;
	strncpy(f, name, PATH_MAX-1);
}

const char* LB_STDCALL lbInputStream::getFileName() {
	return f;
}

bool LB_STDCALL lbInputStream::close() {
	if (isOpen) {
		_istream->close();
		delete _istream;
		isOpen = false;
	}

	return true;
}

bool LB_STDCALL lbInputStream::open() {
	if (!isOpen) {
		_istream = new ifstream(f);
	}

	isOpen = true;
	return true;
}

bool LB_STDCALL lbInputStream::read() {
	return false;
}
void LB_STDCALL lbInputStream::_realloc(int add_size) {
} 
 
lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (int& i) {
	if (!isOpen) return *this;

	*_istream >> i;

	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char& c) {
	if (!isOpen) return *this;

	*_istream >> c;
	
	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char*& _string) {
	char* buf = NULL;
	int size = 0;

#ifndef __WATCOMC__
	std::string s;	
#endif
#ifdef __WATCOMC__
	String s;	
#endif
	
	_istream->ignore(1, '\n');
#ifndef __WATCOMC__ 
	getline(*_istream, s);
#endif
#ifdef __WATCOMC__ 
	*_istream >> s;
#endif
	if (_string != NULL) free(_string);

	_string = strdup(s.c_str());

	return *this;
}


#endif //  ISTREAM_DEFINED


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

#ifndef  ISTREAM_DEFINED
#define  ISTREAM_DEFINED

/*...sclass lbInputStream:0:*/
/// \brief Logging implementation. \todo Separate file to a base class.
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

bool LB_STDCALL lbInputStream::close() {
	if (isOpen) {
		fflush(fin);
		fclose(fin);
		isOpen = false;
	}
	return true;
}

bool LB_STDCALL lbInputStream::open() {
	fin = fopen(f, "rb");
	if (!fin) {
		_CL_LOG << "ERROR: Input file not found!" LOG_
		return false;
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

	fread(&i, sizeof(i), 1, fin);
	
	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char& c) {
	if (!isOpen) return *this;

	fread(&c, sizeof(c), 1, fin);
	
	return *this;
}

lb_I_InputStream& LB_STDCALL lbInputStream::operator>> (char*& string) {
	char* buf = NULL;
	int size = 0;
	
	fread(&size, sizeof(size), 1, fin);
	
	buf = (char*) malloc(size);
	
	fread(buf, size, 1, fin);

	if (string != NULL) free(string);

	string = buf;
	
	return *this;
}


#endif //  ISTREAM_DEFINED


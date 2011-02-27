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
#include <fstream>

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
#include <limits.h>
#ifdef __cplusplus
}      
#endif            

#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
//#include <lbInterfaces.h>

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
			
	    	close();
	}
/*...e*/


    DECLARE_LB_UNKNOWN()

/*...slb_I_OutputStream:0:*/

	void LB_STDCALL writeToBuffer(bool _buffer);
	lb_I_String* LB_STDCALL getAsString();

	void LB_STDCALL setFileName(char* name);
	const char* LB_STDCALL getFileName();
	bool LB_STDCALL open();
	bool LB_STDCALL close();

	void LB_STDCALL logdirect(const char *msg, char *f, int level);

	lb_I_OutputStream& LB_STDCALL operator<< (const int i);
	lb_I_OutputStream& LB_STDCALL operator<< (const long i);
	lb_I_OutputStream& LB_STDCALL operator<< (const bool b);
	lb_I_OutputStream& LB_STDCALL operator<< (const char c);
	lb_I_OutputStream& LB_STDCALL operator<< (const char* string);

	void LB_STDCALL setBinary();
    
/*...e*/

/*...sprivate:0:*/
    private:

	void LB_STDCALL _realloc(int add_size);

	char f[PATH_MAX];
	char* logmessage;
	int pre_lastsize;
	int lastsize;
	FILE*	fout;
	bool	isOpen;
	int	offset;

	std::ofstream* _ostream;
	bool _binary;

	bool _writeToBuffer;
	UAP(lb_I_String, buffer)

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
	ADD_INTERFACE(lb_I_Stream)
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
		
        logmessage = NULL;
        lastsize = 0;
	_ostream = NULL;
	_binary = false;
	
	_writeToBuffer = false;
	REQUEST(getModuleInstance(), lb_I_String, buffer)
}
/*...e*/
/*...slbOutputStream\58\\58\logdirect\40\\46\\46\\46\\41\:0:*/
void LB_STDCALL lbOutputStream::logdirect(const char *msg, char *f, int level) {
}
/*...e*/

void LB_STDCALL lbOutputStream::writeToBuffer(bool _buffer) {
	_writeToBuffer = _buffer;
}

lb_I_String* LB_STDCALL lbOutputStream::getAsString() {
	buffer++;
	return buffer.getPtr();
}


void LB_STDCALL lbOutputStream::setBinary() {
	_binary = true;
}

void LB_STDCALL lbOutputStream::setFileName(char* name) {
	f[0] = 0;
	strncpy(f, name, PATH_MAX-1);
}

const char* LB_STDCALL lbOutputStream::getFileName() {
	return f;
}

bool LB_STDCALL lbOutputStream::close() {
	if (_writeToBuffer) return true;
	if (isOpen) {
		_ostream->close();
		delete _ostream;
		isOpen = false;
	}
	return true;
}
bool LB_STDCALL lbOutputStream::open() {
	if (_writeToBuffer) {
		isOpen = true;
		return true;
	}
	if (!isOpen) {
		_ostream = new std::ofstream(f);
		isOpen = _ostream->is_open();
	}
	return isOpen;
}
 
void LB_STDCALL lbOutputStream::_realloc(int add_size) {
} 
 
lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const int i) {
	if (!isOpen) return *this;

	if (_writeToBuffer) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, toBuffer)
		toBuffer->setData(i);
		
		if (_binary) {
			*buffer += toBuffer->charrep();
		} else {
			*buffer += toBuffer->charrep();
			*buffer += "\n";		
		}
		return *this;
	}

	if (_binary)
		*_ostream << i;
	else
		*_ostream << i << ENDL;
	
	return *this;
}

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const long i) {
	if (!isOpen) return *this;

	if (_writeToBuffer) {
		UAP_REQUEST(getModuleInstance(), lb_I_Long, toBuffer)
		toBuffer->setData(i);
		
		if (_binary) {
			*buffer += toBuffer->charrep();
		} else {
			*buffer += toBuffer->charrep();
			*buffer += "\n";		
		}
		return *this;
	}

	if (_binary)
		*_ostream << i;
	else
		*_ostream << i << ENDL;
	
	return *this;
}

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const bool b) {
	if (!isOpen) return *this;

	int _b;
	if (b == true) 
		_b = 1;
	else
		_b = 0;

	if (_writeToBuffer) {
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, toBuffer)
		toBuffer->setData(_b);
		
		if (_binary) {
			*buffer += toBuffer->charrep();
		} else {
			*buffer += toBuffer->charrep();
			*buffer += "\n";		
		}
		return *this;
	}
		
	if (_binary)
		*_ostream << _b;
	else
		*_ostream << _b << ENDL;	
	
	return *this;
}

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const char c) {
	if (!isOpen) return *this;

	if (_writeToBuffer) {
		char temp[2] = "";
		temp[0] = c;
		if (_binary) {
			*buffer += temp;
		} else {
			*buffer += temp;
			*buffer += "\n";		
		}
		return *this;
	}

	if (_binary)
		*_ostream << c;
	else
		*_ostream << c << ENDL;
	return *this;
}

lb_I_OutputStream& LB_STDCALL lbOutputStream::operator<< (const char* string) {
	if (!isOpen) return *this;

#ifndef __WATCOMC__
	std::string s(string);
#endif
#ifdef __WATCOMC__
	String s(string);
#endif

	if (_writeToBuffer) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, toBuffer)
		toBuffer->setData(string);
		
		if (_binary) {
			*buffer += toBuffer->charrep();
		} else {
			*buffer += toBuffer->charrep();
			*buffer += "\n";		
		}
		return *this;
	}

	if (strlen(string) == 0) {
		if (!_binary) *_ostream << 1 << ENDL;
		if (_binary)
			*_ostream << " ";
		else
			*_ostream << " " << ENDL;
		
		return *this;
	}

	if (!_binary) *_ostream << strlen(string) << ENDL;
	if (_binary)
		*_ostream << s;
	else
		*_ostream << s << ENDL;
		
	return *this;
}


#endif //  OUTPUTSTREAM_DEFINED

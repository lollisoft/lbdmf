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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <conio.h>
	
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

class lb_I_Dummy {
public:
	virtual lbErrCodes LB_STDCALL release(const char* file, int line) = 0;
	virtual char* LB_STDCALL getCreationLoc() const = 0;
	virtual int LB_STDCALL deleteState() = 0;
	virtual void LB_STDCALL setDebug(long i) = 0;
	virtual int LB_STDCALL getRefCount() = 0;
	virtual char const* LB_STDCALL getClassName() = 0;
	virtual void LB_STDCALL setModuleManager(lb_I_Module* m, const char* file, int line) = 0;
	virtual lb_I_Module*   LB_STDCALL getModuleManager() = 0;
	virtual lbErrCodes LB_STDCALL queryInterface(const char* name, void** unknown, const char* file, int line) const = 0;
	virtual char const* LB_STDCALL _queryInterface(const char* name, void** unknown, const char* file, int line) = 0;
	virtual lb_I_Unknown* LB_STDCALL clone(const char* file, int line) const = 0;
	virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u) = 0;
	virtual void LB_STDCALL accept(lb_I_Aspect* v) = 0;
	virtual void LB_STDCALL traceObject() const = 0;
};

class UAPiDummy {
	
public:
	UAPiDummy() {
		_autoPtr = NULL;
		_line = __LINE__;
		_file = strdup(__FILE__);
		attachedClassName = NULL;
		allowDelete = 1;
		locked = false;
		initialized = false;
	}
	
	UAPiDummy(const UAPiDummy& _ref) {
		char const* empty = "";
		attachedClassName = NULL;
		initialized = false;
		allowDelete = 1;
		locked = false;
		if ((_ref != NULL) && (_ref->getClassName() != NULL))
			attachedClassName = strdup(_ref->getClassName());
		else
			attachedClassName = strdup(empty);
		if (_file != NULL) free(_file);
		_file = NULL;
		if (_ref._file != NULL) {
			_file = (char*) strdup(_ref._file);
		}
		_line = _ref._line;
		_autoPtr = NULL;
	}
	UAPiDummy& operator=(const UAPiDummy& _ref) {
		if (this == &_ref) return *this;
		allowDelete = 1;
		locked = false;
		char const* empty = "";
		if (_file != NULL) free(_file);
		_file = NULL;
		if (_ref._file != NULL) {
			_file = (char*) strdup(_ref._file);
		}
		if (attachedClassName) {
			free(attachedClassName);
		}
		initialized = false;
		if ((_ref != NULL) && (_ref->getClassName() != NULL))
			attachedClassName = strdup(_ref->getClassName());
		else
			attachedClassName = strdup(empty);
		_line = _ref._line;
		_autoPtr = _ref._autoPtr;
		return *this;
	}
	
	virtual ~UAPiDummy() {
		if (_autoPtr != NULL) {
			UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Destruct on invalid object pointer")
			if (allowDelete != 1) {
				if (_autoPtr->deleteState() == 1) {
					if (isLogActivated()) printf("Error: Instance would be deleted, but it's not allowed !!n");
				}
			}
			if (_line == -1) {
			}
			_autoPtr->release(_file, _line);
			_autoPtr = NULL;
		}
		if (attachedClassName != NULL) free(attachedClassName);
		if (_file) free(_file);
	}
	void LB_STDCALL setFile(char const* __file) {
		if (_file != NULL) {
			free(_file);
		}
		if (__file != NULL) {
			_file = (char*) strdup(__file);
		} else {
			_CL_LOG << "Error: Setting file parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_
			_file = strdup(__FILE__);
		}
	}
	void LB_STDCALL setLine(int __line) {
		if (__line == -1) {
			_CL_LOG << "Error: Setting line parameter is empty! (macro is " << __FILE__ << ", " << __LINE__ LOG_
			_line = __LINE__;
		} else {
			_line = __line;
		}
	}
	
	lb_I_Dummy* LB_STDCALL getPtr() const {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: getPtr() on invalid object pointer")
		return _autoPtr;
	}
	void LB_STDCALL lock() {
		locked = true;
	}
	void LB_STDCALL resetPtr() {
		_autoPtr = NULL;
	}
	void LB_STDCALL setPtr(lb_I_Dummy*& source) {
		if (locked) return;
		if (_autoPtr != NULL) {
			_CL_LOG << "Error: UAP object still initialized!" LOG_
		}
		_autoPtr = source;
	}
	
	lb_I_Dummy& LB_STDCALL operator * () {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator * () on invalid object pointer")
		return *_autoPtr;
	}
	lb_I_Dummy* LB_STDCALL operator -> () const {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer")
		if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) {
			char const* className = _autoPtr->getClassName();
			int len = strlen(className)+1;
			initialized = true;
			if (attachedClassName != NULL) free(attachedClassName);
			attachedClassName = (char*) malloc(len);
			attachedClassName[0] = 0;
			strcpy(attachedClassName, className);
		}
		return _autoPtr;
	}
	lb_I_Dummy* LB_STDCALL operator -> () {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: Operate on invalid object pointer")
		if ((initialized == false) && (_autoPtr != NULL) && (_autoPtr->getClassName() != NULL)) {
			char const* className = _autoPtr->getClassName();
			int len = strlen(className)+1;
			initialized = true;
			if (attachedClassName != NULL) free(attachedClassName);
			attachedClassName = (char*) malloc(len);
			attachedClassName[0] = 0;
			strcpy(attachedClassName, className);
		}
		return _autoPtr;
	}
	UAPiDummy& LB_STDCALL operator++(int) {
		lb_I_Dummy* temp = NULL;
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator++ on invalid object pointer")
		_autoPtr->queryInterface((char*) "lb_I_Dummy", (void**) &temp, (char*) __FILE__, __LINE__);
		return *this;
	}
	UAPiDummy& LB_STDCALL operator--(int) {
		lb_I_Dummy* temp = NULL;
		if (_autoPtr == NULL) return *this;
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator-- on invalid object pointer")
		if (_autoPtr->release((char*) __FILE__, __LINE__) == ERR_RELEASED) _autoPtr = NULL;
		return *this;
	}
	lb_I_Dummy ** LB_STDCALL operator & () {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator& on invalid object pointer")
		return &_autoPtr;
	}
	
	lb_I_Dummy* LB_STDCALL operator = (lb_I_Dummy* autoPtr) {
		if (*this == autoPtr) return this->_autoPtr;
		if (locked) return this->_autoPtr;
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid old object pointer")
		if (_autoPtr != NULL) {
			_autoPtr->release(__FILE__, __LINE__);
		}
		_autoPtr = autoPtr;
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator = on invalid new object pointer")
		if (attachedClassName) {
			free(attachedClassName);
		}
		if ((autoPtr != NULL) && (autoPtr->getClassName() != NULL))
			attachedClassName = strdup(autoPtr->getClassName());
		else
			attachedClassName = strdup("");
		return this->_autoPtr;
	}
	int LB_STDCALL operator == (const lb_I_Dummy* b) const {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer")
		return _autoPtr == b;
	}
	int LB_STDCALL operator == (const UAPiDummy& b) const {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator == on invalid object pointer")
		return *this == b;
	}
	int LB_STDCALL operator != (const lb_I_Dummy* b) const {
		UAP_CHECKPOINTER_INVALID(_autoPtr, "FATAL: operator != on invalid object pointer")
		return _autoPtr != b;
	}
	void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; }
	
protected:
	lb_I_Dummy* _autoPtr;
	mutable int _line;
	mutable char* _file;
	mutable int allowDelete;
	mutable bool initialized;
	mutable bool locked;
	mutable char* attachedClassName;
};

int main(int argc, char *argv[]) {
	
	for (int i = 0; i < 100000; i++) {
		UAPiDummy dummy;
	}
	
	return 0;
}

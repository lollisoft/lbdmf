/*...sLicense:0:*/
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

            40235 D�sseldorf (germany)
*/
/*...e*/

#ifdef _MSC_VER

#pragma warning( disable: 4275 )
#pragma warning( disable: 4101 )
#pragma warning( disable: 4102 )
#pragma warning( disable: 4172 )
#pragma warning( disable: 4251 )

#endif

#ifdef __WATCOMC__
#pragma warning 14 9;
#endif

/*...sdocu:0:*/
/**
 * For all Interfaces are factories needed. How should I design these
 * factories ?
 */
 
/*...e*/

/*...sbasics:0:*/
/*...sincludes and definitions:0:*/
/**
 * All classes, that anounce callbacks, must implement the interface for
 * lb_I_CallbackManager. The callback manager did not need to handle its
 * own table, more it may delegate this to the static (singleton) handler.
 */


#ifndef __LB_INTERFACES__
#define __LB_INTERFACES__

#include <lbErrcodes.h>

//#define LB_STDCALL

#ifndef FALSE
#define FALSE false
#endif

#ifndef _MSC_VER
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   #define LB_STDCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
  #endif
 #endif

 #ifndef LB_FUNCTORCALL
  #ifdef WINDOWS
   #define LB_FUNCTORCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_FUNCTORCALL
  #endif
 #endif
#endif

#ifdef _MSC_VER
 #ifndef LB_STDCALL
  #ifdef WINDOWS
   #define LB_STDCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_STDCALL
  #endif
 #endif

 #ifndef LB_FUNCTORCALL
  #ifdef WINDOWS
   #define LB_FUNCTORCALL __cdecl
  #endif
  #ifndef WINDOWS
   #define LB_FUNCTORCALL
  #endif
 #endif
#endif

#ifdef __WATCOMC__
#define LB_DLLEXPORT __declspec(dllexport)
#endif

#ifndef __WATCOMC__
#define LB_DLLEXPORT __declspec(dllexport)
#endif

#ifdef __WATCOMC__
#define LB_DLLIMPORT __declspec(dllimport)
#endif

#ifndef __WATCOMC__
#define LB_DLLIMPORT __declspec(dllimport)
#endif

#ifndef DLLEXPORT
// Default to import. Modules redefine this in general.
#ifdef WINDOWS
#define DLLEXPORT
#endif
#ifdef LINUX
#define DLLEXPORT
#endif
#endif

#ifndef __BASE_TYPES_DEFINED__
#define __BASE_TYPES_DEFINED__
/*...sbase types:0:*/
#ifndef __WATCOMC__
#ifndef _MSC_VER
typedef unsigned short byte;
typedef unsigned short u_short;
#endif
#endif
#ifdef __POWERPP
typedef unsigned short byte;
typedef unsigned short u_short;
#endif

typedef unsigned long DWORD;

typedef unsigned short LB_DATA;
typedef unsigned short u_short;
/*...e*/
#endif // __BASE_TYPES_DEFINED__

class lb_I_CallbackTarget;
class lb_I_ProtocolTarget;

#include <lbInterfaces-sub-transfer.h>
/*...e*/

/*...sforward class decl\39\s:0:*/
/**
 * The base interface, that currently implements only release.
 * A query interface should be added. But is M$'s solution usable ?
 */
 
class lb_I_gcManager;
class lb_I_Unknown;
class lb_I_Module;

class lb_I_Container;
class lb_I_Event;
class lb_I_EventSink;

class lb_I_Dispatcher;
class lb_I_EventManager;
class lb_I_EventHandler;

class lb_I_ConfigObject;

class lb_I_Frame;
/*...e*/

/*...scallback \47\ handler typedefs:0:*/
/**
 * This is a base class for all callback able objects
 */
///////////////////////////////////////////////////////////////
// Type for lb protocol callback functions. This should be an interface.
typedef lbErrCodes (lb_I_ProtocolTarget::*lbProtocolCallback)( lb_I_Transfer_Data const &, lb_I_Transfer_Data&);
typedef lbErrCodes (lb_I_CallbackTarget::*lbMemberCallback)( const char* handlername, lb_I_Transfer_Data&);



typedef lbErrCodes (lb_I_EventSink::*lb_I_EventCallback)(lb_I_Unknown* question, lb_I_Unknown* answer); 

typedef lbErrCodes (LB_STDCALL lb_I_EventHandler::*lbEvHandler)(lb_I_Unknown* uk);
/*...e*/

/*
	CL_LOG("Releasing instance"); \
*/
/*...sdefine RELEASE\40\instance\41\:0:*/
#define RELEASE(instance) \
	{ lbErrCodes err; \
		if ((err = instance->release(__FILE__, __LINE__)) != ERR_NONE) { \
			if (err == ERR_REFERENCE_COUNTING ) { \
				_CL_LOG << "RELEASE(...) Reference count mismatch at " << __LINE__ << " in " << __FILE__ LOG_ \
			} else { \
			} \
		} else { \
			instance = NULL; \
		} \
	}

/*...e*/
/*...sdefine RELEASE_1\40\instance\44\ __MACRO_FILE__\44\ __MACRO_LINE__\41\:0:*/
#define RELEASE_1(instance, __MACRO_FILE__, __MACRO_LINE__) \
	{ lbErrCodes err; \
		if ((err = instance->release(#__MACRO_FILE__, __MACRO_LINE__)) != ERR_NONE) { \
			if (err == ERR_REFERENCE_COUNTING ) { \
				printf("Error in reference counting (%s in %s, %d)!\n", #instance, #__MACRO_FILE__, __MACRO_LINE__); \
				if (__MACRO_FILE__ != NULL) { \
				_CL_LOG << "RELEASE_1(...) Reference count mismatch at " << __MACRO_LINE__ << " in " << #__MACRO_FILE__ << " for instance " << instance->getClassName() LOG_ \
				} \
			} else { \
			} \
		} \
	}

/*...e*/
/*...sdefine QI\40\source\44\ interface\44\ target\44\ file\44\ line\41\:0:*/
#define QI(source, interface, target, file, line) \
	target.setFile(file); \
	target.setLine(line); \
	{ \
		char* iface = strdup(#interface); \
	 	err = source->queryInterface(iface, (void**) &target, file, line); \
	 	free(iface); \
	 	iface = NULL; \
	}

#define _QI(source, interface, target) \
	target.setFile(file); \
	target.setLine(line); \
 	err = source->queryInterface(#interface, (void**) &target, __FILE__, __LINE__);
/*...e*/
/*...e*/

// UNKNOWN_AUTO_PTR was tested, use it.

#define USE_UAP

	/* setData must check the type of this ! */
	/* = may also be possible */
/*...sclass lb_I_Unknown:0:*/
#define STARTREF 0


/*...sclass lb_I_Unknown:0:*/
class lb_I_Unknown {
protected:
	lb_I_Unknown() {}
	virtual ~lb_I_Unknown() {}

private:
	lb_I_Unknown& operator=(const lb_I_Unknown& rhs);
	lb_I_Unknown* operator=(const lb_I_Unknown* rhs);
	
public:
	virtual lbErrCodes LB_STDCALL release(char* file, int line) = 0;
	/**
	 * This function indicates, if the object will be deleted on a call
	 * of release().
	 */
	virtual char* LB_STDCALL getCreationLoc() const = 0;
	virtual int LB_STDCALL deleteState() = 0;
	virtual void LB_STDCALL setDebug(int i) = 0;
	virtual int LB_STDCALL getRefCount() = 0;
	virtual char* LB_STDCALL getClassName() = 0;

	virtual void LB_STDCALL setModuleManager(lb_I_Module* m, char* file, int line) = 0;
	virtual lb_I_Module*   LB_STDCALL getModuleManager() = 0;
		
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line) = 0;

	/**
	 * This is an attempt to resolve any dangling references. As yet tried, a release on another
	 * place don't help, because the reference ID would include the place of creation.
	 *
	 * (__FILE__, __LINE__)
	 *
	 * With the help of UAP, it may be possible, because it can hold such an ID for each reference.
	 */
	virtual char* LB_STDCALL _queryInterface(char* name, void** unknown, char* file, int line) = 0;
        
/*...sdoc:0:*/
        /**
         * This was used yet for put an object in a container. After inserting the object
         * into the container, there are two instances (not two references).
         * So the cloning is generaly a good way to make copies of an object.
         *
         * But remark:	The cloned object returned is not the instance in general.
         *		It is the *FIRST* lb_I_Unknown* reference to it.
         *		Putting an object in a container, you have your instance
         *		with the same reference count as before.
         *		
         *		The clone() method does not and is not able to make deep clones.
         *		It does not know how !
         *
         *		It creates a new instance with the normal constructor. But it calls
         *		the method setData with the this pointer.
         *		You must provide this method to be able to make a copy of your data.
	 *
         *
         *		return uk;
         */
/*...e*/
        virtual lb_I_Unknown* LB_STDCALL clone(char* file, int line) const = 0;
        virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u) = 0;

//friend class lb_I_gcManager;	
};
/*...e*/

/*...sAutoPointer:0:*/
/**
 * Is it possible to create an automatic pointer without templates ?
 * An Unknown auto pointer.
 */

#define UAP(interface, Unknown_Reference, file, line) \
		class UAP##Unknown_Reference { \
\
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	_line = -1; \
	        	_file = NULL; \
	        	allowDelete = 1; \
		} \
		\
		UAP##Unknown_Reference(const UAP##Unknown_Reference& _ref) { \
			_file = NULL; \
			if (_ref._file) { \
				_file = new char [strlen(_ref._file) + 1]; \
				_file = strcpy(_file, _ref._file); \
			} \
			_line = _ref._line; \
		} \
		void operator=(const UAP##Unknown_Reference& _ref) { \
			if (_file != NULL) { \
				delete [] _file; \
				if (_ref._file) { \
					_file = new char [strlen(_ref._file) + 1]; \
					_file = strcpy(_file, _ref._file); \
				} \
			} \
			_line = _ref._line; \
		} \
		\
		virtual ~UAP##Unknown_Reference() { \
			if (_autoPtr != NULL) { \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						printf("Error: Instance would be deleted, but it's not allowed !!\n"); \
					} \
				} \
				if (_line == -1) { \
				} \
				RELEASE_1(_autoPtr, _file, _line); \
				if (_file) delete [] _file; \
			} \
		} \
		void LB_STDCALL setFile(char* __file) { \
			if (_file != NULL) { \
				delete [] _file; \
				_file = NULL; \
			} \
			if (__file != NULL) { \
				_file = new char [strlen(__file) + 1]; \
				_file = strcpy(_file, __file); \
			} \
		} \
		void LB_STDCALL setLine(int __line) { \
			_line = __line; \
		} \
		\
		interface* LB_STDCALL getPtr() const { return _autoPtr; } \
		void LB_STDCALL setPtr(interface*& source) { \
			if (_autoPtr != NULL) { \
				_CL_LOG << "Error: UAP object still initialized!" LOG_ \
			} \
			_autoPtr = source; \
		} \
		\
		interface& LB_STDCALL operator * () { \
		return *_autoPtr; } \
		interface* LB_STDCALL operator -> () const { \
			if (_autoPtr == NULL) { \
			} \
			return _autoPtr; \
		} \
		interface* LB_STDCALL operator -> () { \
			if (_autoPtr == NULL) { \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator++(int) { \
			interface* temp = NULL; \
			_autoPtr->queryInterface(#interface, (void**) &temp, file, line); \
			return *this; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator--(int) { \
			interface* temp = NULL; \
			if (_autoPtr->release(file, line) == ERR_RELEASED) _autoPtr = NULL; \
			return *this; \
		} \
		interface ** LB_STDCALL operator & () { \
			return &_autoPtr; \
		} \
		\
		UAP##Unknown_Reference& LB_STDCALL operator = (interface* autoPtr) { \
			_autoPtr = autoPtr; \
			return *this; \
		} \
		int LB_STDCALL operator == (const interface* b) const { \
			return _autoPtr == b; \
		} \
		int LB_STDCALL operator != (const interface* b) const { \
			return _autoPtr != b; \
		} \
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
	        int _line; \
	        char* _file; \
	        int allowDelete; \
		}; \
	\
        interface* _UAP##Unknown_Reference; \
        UAP##Unknown_Reference Unknown_Reference;


/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
#define UNKNOWN_AUTO_PTR(interface, Unknown_Referene) \
	interface* Unknown_Referene = NULL; \
	UAP UAP##Unknown_Referene((lb_I_Unknown**) &Unknown_Referene);
#endif
/*...e*/
/*...e*/
/*...sDebug AutoPointer:0:*/
/**
 * Is it possible to create an automatic pointer without templates ?
 * An Unknown auto pointer.
 */

#define DEBUG_UAP(interface, Unknown_Reference, file, line) \
		class UAP##Unknown_Reference { \
\
		private: \
		UAP##Unknown_Reference(UAP##Unknown_Reference& from) { \
		} \
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	_line = -1; \
	        	_file = strdup(""); \
	        	allowDelete = 1; \
		} \
		UAP##Unknown_Reference(const UAP##Unknown_Reference& _ref) { \
	        	_file = NULL; \
		        if (_ref._file) { \
		                _file = new char [strlen(_ref._file) + 1]; \
		                _file = strcpy(_file, _ref._file); \
		        } \
		        _line = _ref._line; \
		} \
		void operator=(const UAP##Unknown_Reference& _ref) { \
		        if (_file != NULL) { \
		                delete [] _file; \
		                if (_ref._file) { \
		                        _file = new char [strlen(_ref._file) + 1]; \
		                        _file = strcpy(_file, _ref._file); \
		                } \
		        } \
		        _line = _ref._line; \
		} \
		\
		virtual ~UAP##Unknown_Reference() { \
			if (_autoPtr != NULL) { \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						_CL_LOG << "Error: Instance would be deleted, but it's not allowed !!" LOG_ \
					} \
				} \
				if (_line == -1) { \
					_CL_LOG << "Warning: No reference has been taken in " << #Unknown_Reference << " at " << _line << " (UAP is in " << file << " at " << line LOG_ \
				} \
				RELEASE_1(_autoPtr, _file, _line); \
			} \
			free(_file); \
		} \
		void LB_STDCALL setFile(char* __file) { \
			if (__file != NULL) _file = strdup(__file); \
		} \
		void LB_STDCALL setLine(int __line) { \
			_line = __line; \
		} \
		\
		interface* LB_STDCALL getPtr() const { return _autoPtr; } \
		void LB_STDCALL setPtr(interface*& source) { \
			if (_autoPtr != NULL) { \
				_CL_LOG << "Error: UAP object still initialized!" LOG_ \
			} \
			_autoPtr = source; \
		} \
		\
		interface& LB_STDCALL operator * () { \
		_LOG << "Warning: Using reference to UAP pointer in " << file << " at " <<  line LOG_ \
		return *_autoPtr; } \
		interface* LB_STDCALL operator -> () const { \
			if (_autoPtr == NULL) { \
				_CL_LOG << "Error: UAP pointer (" << #Unknown_Reference << ") for interface " << #interface << " is NULL!" LOG_ \
			} \
			return _autoPtr; \
		} \
		interface* LB_STDCALL operator -> () { \
			if (_autoPtr == NULL) { \
				_CL_LOG << "Error: UAP pointer (" << #Unknown_Reference << ") for interface " << #interface << " is NULL!" LOG_ \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator++(int) { \
			interface* temp = NULL; \
			_autoPtr->queryInterface(#interface, (void**) &temp, file, line); \
			return *this; \
		} \
		UAP##Unknown_Reference& LB_STDCALL operator--(int) { \
			interface* temp = NULL; \
			if (_autoPtr->release(file, line) == ERR_RELEASED) _autoPtr = NULL; \
			return *this; \
		} \
		interface ** LB_STDCALL operator & () { \
			return &_autoPtr; \
		} \
		\
		UAP##Unknown_Reference& LB_STDCALL operator = (interface* autoPtr) { \
			_autoPtr = autoPtr; \
			return *this; \
		} \
		int LB_STDCALL operator == (const interface* b) const { \
			return _autoPtr == b; \
		} \
		int LB_STDCALL operator != (const interface* b) const { \
			return _autoPtr != b; \
		} \
		void LB_STDCALL setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
	        int _line; \
	        char* _file; \
	        int allowDelete; \
		}; \
	\
        interface* _UAP##Unknown_Reference; \
        UAP##Unknown_Reference Unknown_Reference;


/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
#define UNKNOWN_AUTO_PTR(interface, Unknown_Referene) \
	interface* Unknown_Referene = NULL; \
	UAP UAP##Unknown_Referene((lb_I_Unknown**) &Unknown_Referene);
#endif
/*...e*/
/*...e*/

/*...sREQUEST Use this for a predefined UAP\46\:0:*/
// Use this for a predefined UAP. It will automatically deleted, if scope is gone.
#define REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
  	mm->request(#interface, &uk##variable); \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
	uk##variable.setFile(__FILE__); \
	uk##variable.setLine(__LINE__);

#define DEBUG_REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
	printf("Step 1\n"); \
  	mm->request(#interface, &uk##variable); \
	printf("Step 2\n"); \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
	printf("Step 3\n"); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__); \
	printf("Step 4\n"); \
	uk##variable.setFile(__FILE__); \
	printf("Step 5\n"); \
	uk##variable.setLine(__LINE__);

/*...e*/

/*...sUAP_REQUEST Use this for an stack like environment\46\:0:*/
// Use this for an stack like environment. It will automatically deleted, if scope is gone.
#define UAP_REQUEST(mm, interface, variable) \
  	UAP(lb_I_Unknown, uk##variable, __FILE__, __LINE__) \
  	if (mm->request(#interface, &uk##variable) == ERR_MODULE_NO_INTERFACE) _CL_LOG << "Error: Interface not defined" LOG_ \
  	UAP(interface, variable, __FILE__, __LINE__) \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__);

/*...e*/

/*...s\35\define STATIC_REQUEST\40\mm\44\ interface\44\ variable\41\:0:*/
/**
 * This is an replacement for a normal pointer. It has one reference, that you can use.
 * But you must release it yourself, or put it to a UAP in any scope.
 */
#define STATIC_REQUEST(mm, interface, variable) \
  	lb_I_Unknown* uk##variable; \
  	mm->request(#interface, &uk##variable); \
  	_CL_LOG << "STATIC_REQUEST: Have an instance" LOG_ \
  	interface* variable; \
  	uk##variable->setModuleManager(mm, __FILE__, __LINE__); \
  	_CL_LOG << "STATIC_REQUEST: Set module manager" LOG_ \
  	uk##variable->queryInterface(#interface, (void**) &variable, __FILE__, __LINE__);

/*...e*/

/*...s\35\define DECLARE_LB_UNKNOWN\40\\41\:0:*/

#define DECLARE_LB_UNKNOWN() \
private: \
	UAP(lb_I_Module, manager, __FILE__, __LINE__) \
	int ref; \
	lb_I_Unknown* data; \
	int debug_macro; \
	int further_lock; \
protected: \
public: \
	virtual void 		LB_STDCALL setFurtherLock(int state) { further_lock = state; } \
	virtual void 		LB_STDCALL setModuleManager(lb_I_Module* m, char* file, int line); \
	virtual lb_I_Module*    LB_STDCALL getModuleManager(); \
	virtual void 		LB_STDCALL resetRefcount(); \
	virtual void 		LB_STDCALL setDebug(int i = 1) { debug_macro = i; } \
	virtual lbErrCodes 	LB_STDCALL release(char* file, int line); \
	virtual char* 		LB_STDCALL getClassName(); \
	virtual char*           LB_STDCALL getCreationLoc() const; \
	virtual int 		LB_STDCALL deleteState(); \
	virtual char* 		LB_STDCALL _queryInterface(char* name, void** unknown, char* file, int line); \
	virtual lbErrCodes 	LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line); \
	virtual lb_I_Unknown* 	LB_STDCALL clone(char* file, int line) const; \
	virtual lbErrCodes 	LB_STDCALL setData(lb_I_Unknown* u); \
	virtual int 		LB_STDCALL getRefCount() { return ref; }

/*...e*/

/*...sBEGIN_IMPLEMENT_LB_UNKNOWN:0:*/


#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
char* LB_STDCALL classname::_queryInterface(char* name, void** unknown, char* file, int line) { \
	char* ID = new char[strlen(name)+strlen(#classname)+strlen(file)+1]; \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		return ""; \
	} \
	\
	return ID; \
} \
lb_I_Module* LB_STDCALL classname::getModuleManager() { \
		lbErrCodes err = ERR_NONE; \
		UAP(lb_I_Module, _mm, __FILE__, __LINE__) \
		if (manager == NULL) { \
			_CL_LOG << "Error: Can't return module manager. Call setModuleManager(...) on me first!" LOG_ \
			return NULL; \
		} \
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__) \
		return _mm.getPtr(); \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	if (m == NULL) { \
		_CL_LOG << "Error: Set module manager with a NULL pointer in " << #classname << " while setModuleManager(...)!" LOG_ \
		return; \
	} \
	\
	further_lock = 0; \
	if (debug_macro == 1) { \
		_CL_LOG << "Warning: setModuleManager() must be enhanced by module manager use" LOG_ \
	} \
	if (m != manager.getPtr()) { \
	    if (m != NULL) m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	} \
	manager.setLine(__LINE__); \
	manager.setFile(__FILE__); \
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		manager->notify_create(this, #classname, datei, line); \
	} else { \
		_CL_LOG << "Error: Query interface failed for manager in " << #classname << " while setModuleManager(...)!" LOG_ \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("Have no manager - location can't be found"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
        ref--; \
        if (strcmp("lb_EventManager", #classname) == 0) { \
        	_CL_LOG << "lb_EventManager::release() called" LOG_ \
        } \
	char ptr[20] = ""; \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			manager->notify_destroy(this, #classname, file, line); \
        			delete this; \
        			return ERR_RELEASED; \
        		} \
        		else { \
        			printf("Error: Instance %s has been deleted prior!\n", #classname); \
        			_CL_LOG << "Error: Instance has been deleted prior!" LOG_ \
        		} \
        	} \
        	return ERR_NONE; \
        } \
        if (ref < STARTREF) { \
        	_CL_LOG << "Error: Reference count of instance " << ptr << " of object type " << #classname << " is less than " << STARTREF << " (" << ref << ") !!!" LOG_ \
        	return ERR_REFERENCE_COUNTING; \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	classname* cloned = new classname(); \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) _CL_LOG << #classname << "::clone() can't be used because manager is a NULL pointer!" LOG_ \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
		lb_I_Unknown* that = (lb_I_Unknown*) cloned; \
	        manager->notify_add(that, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	_CL_LOG << "Module manager was not set!" LOG_ \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		_CL_LOG << "Cloned object has %d references" << uk->getRefCount() LOG_ \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char iFaces[1000] = ""; \
	char _classname[100] = #classname; \
	if (further_lock == 1) { \
		_CL_LOG <<"Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!" LOG_ \
		return ERR_STATE_FURTHER_LOCK; \
	} \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
	strcat(iFaces, "lb_I_Unknown, "); \
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
                	lb_I_Unknown* that = (lb_I_Unknown*) this; \
                	if (strcmp(_classname, "lbModule") == 0) { \
                		_CL_LOG << "Register reference for " << _classname << \
                		" in " << file << " at " << line LOG_ \
                	} \
		        manager->notify_add(that, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	_CL_LOG << "Lock object due to missing manager!" LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

/*...e*/
/*...sBEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN:0:*/


#define BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
char* LB_STDCALL classname::_queryInterface(char* name, void** unknown, char* file, int line) { \
	char* ID = new char[strlen(name)+strlen(#classname)+strlen(file)+1]; \
	ID[0] = 0; \
	strcat(ID, name); \
	strcat(ID, #classname); \
	strcat(ID, file); \
	lbErrCodes err = ERR_NONE; \
	if ((err = queryInterface(name, unknown, file, line)) != ERR_NONE) { \
		_CL_LOG <<"Error: queryInterface failed (in _queryInterface)!" LOG_ \
		return ""; \
	} \
	\
	return ID; \
} \
lb_I_Module* LB_STDCALL classname::getModuleManager() { \
		lbErrCodes err = ERR_NONE; \
		UAP(lb_I_Module, _mm, __FILE__, __LINE__) \
		if (manager == NULL) { \
			_CL_LOG << "Error: Can't return module manager. Call setModuleManager(...) on me first!" LOG_ \
			return NULL; \
		} \
		QI(manager, lb_I_Module, _mm, __FILE__, __LINE__) \
		return _mm.getPtr(); \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	if (m == NULL) { \
		_CL_LOG << "Error: Set module manager with a NULL pointer in " << #classname << " while setModuleManager(...)!" LOG_ \
		return; \
	} \
	\
	further_lock = 0; \
	if (debug_macro == 1) { \
		_CL_LOG << "Warning: setModuleManager() must be enhanced by module manager use" LOG_ \
	} \
	if (m != manager.getPtr()) { \
	    if (m != NULL) m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	} \
	manager.setLine(__LINE__); \
	manager.setFile(__FILE__); \
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		manager->notify_create(this, #classname, datei, line); \
	} else { \
		_CL_LOG << "Error: Query interface failed for manager in " << #classname << " while setModuleManager(...)!" LOG_ \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() const { \
	char buf[20] = ""; \
	sprintf(buf, "%p", (void*) this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("Have no manager - location can't be found"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
        ref--; \
        if (strcmp("lb_EventManager", #classname) == 0) { \
        	_CL_LOG << "lb_EventManager::release() called" LOG_ \
        } \
	char ptr[20] = ""; \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			manager->notify_destroy(this, #classname, file, line); \
        			printf("WARNING: Refcount goes to %d. Singleton instances can't be destroyed by release.\n", STARTREF); \
        			ref++; \
        			return ERR_RELEASED; \
        		} \
        		else \
        			_CL_LOG << "Error: Instance has been deleted prior!" LOG_ \
        	} \
        	return ERR_NONE; \
        } \
        if (ref < STARTREF) { \
        	_CL_LOG << "Error: Reference count of instance " << ptr << " of object type " << #classname << " is less than " << STARTREF << " (" << ref << ") !!!" LOG_ \
        	return ERR_REFERENCE_COUNTING; \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	classname* cloned = new classname(); \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) _CL_LOG << #classname << "::clone() can't be used because manager is a NULL pointer!" LOG_ \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting interface" LOG_ \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
		lb_I_Unknown* that = (lb_I_Unknown*) cloned; \
	        manager->notify_add(that, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	_CL_LOG << "Module manager was not set!" LOG_ \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		_CL_LOG << "Error while getting unknown interface of cloned object" LOG_ \
	} \
\
	if (uk->getRefCount() > 1) { \
		_CL_LOG << "Cloned object has %d references" << uk->getRefCount() LOG_ \
	} \
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char iFaces[1000] = ""; \
	char _classname[100] = #classname; \
	if (further_lock == 1) { \
		_CL_LOG <<"Error: Object has been locked due to missing module manager (call setModuleManager(...) on me first)!" LOG_ \
		return ERR_STATE_FURTHER_LOCK; \
	} \
	if (unknown == NULL) { \
		_CL_LOG << "Error: Got NULL pointer reference while queryInterface() called for " << \
		name << " ! Did you coded it this way: (void**) &variable ?" LOG_ \
	} \
\
	strcat(iFaces, "lb_I_Unknown, "); \
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		_CL_LOG << "Reference count error in queryInterface (" #classname ")" LOG_ \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
                	lb_I_Unknown* that = (lb_I_Unknown*) this; \
                	if (strcmp(_classname, "lbModule") == 0) { \
                		_CL_LOG << "Register reference for " << _classname << \
                		" in " << file << " at " << line LOG_ \
                	} \
		        manager->notify_add(that, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	_CL_LOG << "Lock object due to missing manager!" LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

/*...e*/

#define ADD_INTERFACE(interfaceName) \
	buf[0] = 0; \
\
	if ((strlen(iFaces)+strlen(#interfaceName)) > 1000) { \
		_CL_LOG << "String size exceeds fixed len!" LOG_ \
	} \
	strcat(iFaces, #interfaceName ", "); \
        if (strcmp(name, #interfaceName) == 0) { \
                ref++; \
                *unknown = (interfaceName*) this; \
                if (manager != NULL) { \
                	interfaceName* that = (interfaceName*) this; \
                	manager->notify_add(that, _classname, file, line); \
                } \
		else { \
		        setFurtherLock(1); \
		        _CL_LOG << "Error: QueryInterface can't add a reference. No manager. File: " << \
		        file << ", Line: " << line LOG_ \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

#define END_IMPLEMENT_LB_UNKNOWN() \
	_CL_LOG << "Error: Requested interface '" << name << "' not found! File: " << file << " Line: " << line LOG_ \
	return ERR_NONE; \
}

/*...e*/

/*...sstandard functor:0:*/
/**
 * Base of all instances - the functor
 */

extern "C" { 
typedef lbErrCodes (LB_FUNCTORCALL *T_pLB_GET_UNKNOWN_INSTANCE) (lb_I_Unknown**, lb_I_Module* m, char* file, int line);
}

/**
 * Idea: To ensure, that the object gets the module manager, it is locked until
 * setModuleManager is called with a correct value.
 * queryInterface can at first time do it's work, store the data, that has to
 * be stored in module manager and lock the instance for further use.
 */

#define DECLARE_FUNCTOR(name) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line); \
}
#define IMPLEMENT_FUNCTOR(name, clsname) \
extern "C" { \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
        clsname* instance = new clsname(); \
        *uk = NULL; \
        instance->setFurtherLock(0); \
        if (m != NULL) { \
        	instance->setModuleManager(m, __FILE__, __LINE__); \
        } else { \
        	_CL_LOG << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_ \
        } \
        \
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
                _CL_LOG << "Failed to create unknown reference to instance of " << \
                #clsname << ". Errcode is " << err LOG_ \
                if (err == ERR_STATE_FURTHER_LOCK) { \
                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
                	return err; \
                } \
                return ERR_FUNCTOR; \
        } \
\
        return ERR_NONE; \
} \
}

#define DECLARE_SINGLETON_FUNCTOR(name) \
extern "C" { \
extern lb_I_Unknown* name##_singleton; \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line); \
} 
#define IMPLEMENT_SINGLETON_FUNCTOR(name, clsname) \
extern "C" { \
lb_I_Unknown* name##_singleton = NULL; \
lbErrCodes DLLEXPORT LB_FUNCTORCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
	if (name##_singleton == NULL) { \
	        clsname* instance = new clsname(); \
	        *uk = NULL; \
	        char buf[100] = ""; \
	        track_Object(instance, "IMPLEMENT_SINGLETON_FUNCTOR - Instantiating"); \
	        \
	        instance->setFurtherLock(0); \
	        if (m != NULL) { \
	        	instance->setModuleManager(m, __FILE__, __LINE__); \
	        } else { \
	        	if (strcmp(instance->getClassName(), "lbModule") != 0) { \
	        		_CL_LOG << "Error: Functor gets no manager. This is only possible for a manager it self." LOG_ \
	        	} \
	        } \
	        \
	        name##_singleton = instance; \
	        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } else { \
	        track_Object(name##_singleton, "IMPLEMENT_SINGLETON_FUNCTOR - queryInterface()"); \
	        if ((err = name##_singleton->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
	                _CL_LOG << "Failed to create unknown reference to singleton instance of " << \
	                #clsname << ". Errcode is " << err LOG_ \
	                if (err == ERR_STATE_FURTHER_LOCK) { \
	                	_CL_LOG << "ERR_STATE_FURTHER_LOCK" LOG_ \
	                	return err; \
	                } \
	                return ERR_FUNCTOR; \
	        } \
        } \
\
        return ERR_NONE; \
} \
}
/*...e*/

/*...sclass lb_I_Reference:0:*/
class lb_I_Reference : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL set(lb_I_Unknown* r) = 0;
	virtual lbErrCodes LB_STDCALL get(lb_I_Unknown*& r) = 0;
};
/*...e*/

/*...sclass lb_I_gcManager:0:*/
class lb_I_gcManager {
protected:
	lb_I_gcManager() {}
	virtual ~lb_I_gcManager() {}
	
public:
	virtual lbErrCodes toTrash(lb_I_Unknown * inst) = 0;
};
/*...e*/

// What about exceptions ?

/*...sclass lb_I_Exception:0:*/
class lb_I_Exception {
public:
	virtual lbErrCodes getMessage(char*& msg) = 0;
};
/*...e*/
/*...sclass lb_I_ErrorDescription:0:*/
class lb_I_ErrorDescription {// Every interface may produce errors
public:
	virtual lbErrCodes getLastError(char* description, int len) = 0;
};
/*...e*/


/*...sdocu  lb_I_Requestable:0:*/
/**
 * lb_I_Requestable is intented to implement a class that can be called
 * for any requests. This may be the 'Meta' Application.
 * The Meta Application did not need to provide an interface for dispatching.
 * This is because, the client of Meta *must* not call any dispatchning -
 * members.
 */
/*...e*/
/*...sclass lb_I_Requestable:0:*/
class lb_I_Requestable {
public:
	virtual lbErrCodes LB_STDCALL initialize() = 0;
	virtual lbErrCodes LB_STDCALL request(const char* request, lb_I_Unknown** result) = 0;
	virtual lbErrCodes LB_STDCALL uninitialize() = 0;
};
/*...e*/

/*...sclass lb_I_CallbackManager:0:*/
class lb_I_CallbackManager {
public:
/*...sdocu:0:*/
	
	/**
	 * Implement this in your class implementing callback handling
	 */
	
	 
/*...e*/
	virtual lbErrCodes addCallbackHandler(const char* handlername, lbMemberCallback cbFn) = 0;
	virtual lbErrCodes delCallbackHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackDispatcher dispatches over names:0:*/
class lb_I_CallbackDispatcher {
public:
	virtual lbErrCodes dispatch(const char* request, lb_I_Transfer_Data& result) = 0;
};
/*...e*/
/*...sclass lb_I_CallbackTarget:0:*/
class lb_I_CallbackTarget {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */
	  
/*...e*/
	virtual lbErrCodes registerCallbacks() = 0; 
};
/*...e*/

/*...sdocu:0:*/
/**
 * This interface must be used to register or deregister
 * protocol callbacks, if an implementation is a callback target.
 */

/*...e*/
/*...sclass lb_I_ProtocolManager:0:*/
class lb_I_ProtocolManager {
public:
/*...sdocu:0:*/
	
	/**
	 * Implement this in your class implementing callback handling
	 */
	
	 
/*...e*/
	virtual lbErrCodes addProtocolHandler(const char* handlername, lbProtocolCallback cbFn) = 0;
	virtual lbErrCodes delProtocolHandler(const char* handlername) = 0;
};
/*...e*/
/*...sclass lb_I_ProtocolDispatcher dispatches over protocol haeder:0:*/
class lb_I_ProtocolDispatcher {
public:
	virtual lbErrCodes dispatch(const lb_I_Transfer_Data& request, lb_I_Transfer_Data& result) = 0;
};
/*...e*/
/*...sdocu:0:*/
/**
 * This is used by a server instance, that implements some protocols.
 */
/*...e*/
/*...sclass lb_I_ProtocolTarget:0:*/
class lb_I_ProtocolTarget {
public:
/*...sdocu:0:*/

	/**
	 * Implement this in the derived class for your functions
	 * to be called back.
	 */
	  
/*...e*/
	virtual lbErrCodes registerProtocols() = 0; 
};
/*...e*/

/*...sclass lb_I_EventConnector:0:*/
// An Application
class lb_I_EventConnector {
public:
	virtual lbErrCodes LB_STDCALL getConnectorEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSource:0:*/
// A Menu ??
class lb_I_EventSource {
public:
	virtual lbErrCodes LB_STDCALL getSourceEventList(lb_I_Container* c) = 0;
};
/*...e*/
/*...sclass lb_I_EventSink:0:*/
// A Frame ??
class lb_I_EventSink {
public:
	virtual lb_I_EventCallback LB_STDCALL getEventFunction(char* name) = 0;
	virtual lbErrCodes LB_STDCALL Connect(char* evName, lb_I_EventCallback evFn) = 0;
	virtual lbErrCodes LB_STDCALL getSinkEventList(lb_I_Container* c) = 0;

	/**
	 * The events are compareable, that is, the connector says the same events
	 * than the sink. If that is so, then the registration will succeed.
	 * 
	 * But what is about the event source. When and where are these created ?
	 */
	virtual lbErrCodes LB_STDCALL registerEvents(lb_I_EventConnector* object) = 0;
	
	/**
	 * This function will be called in the scope of application initializion.
	 * That is in an instance of lb_I_EventConnector. This instance says wich
	 * events should be implemented. This events are registered before and then
	 * the event source can be made.
	 */
	virtual lbErrCodes LB_STDCALL createEventsource(lb_I_EventConnector* object) = 0;
	virtual lb_I_Unknown* LB_STDCALL getEventsource(lb_I_EventConnector* object) = 0;	
	
};
/*...e*/

/*...sclass lb_I_EventMapper:0:*/
class lb_I_EventMapper : public lb_I_Unknown {
public:
	/**
	 * If handler is NULL, then the event manager knows, that the requesting
	 * instance has a dispatcher and therefore handles it self. You must register
	 * the dispatcher after all requested id's for your events.
	 */
	virtual lbErrCodes LB_STDCALL setEvent(char* name, lbEvHandler handler = NULL) = 0;
	/**
	 * Get the id back.
	 */
	virtual int LB_STDCALL getID() = 0;

protected:
	virtual char* LB_STDCALL getName() = 0;
	virtual void LB_STDCALL setID(int id) = 0;
	
	friend class lb_I_EventManager;
};
/*...e*/

//	virtual lbErrCodes LB_STDCALL setDiapatcher(lb_I_Dispatcher* disp) = 0;
//	virtual lb_I_Dispatcher* LB_STDCALL getDispatcher() = 0;
	
/*...sclass lb_I_EventManager:0:*/
/**
 * Register symbolic events and get an id,
 * unregister registered events.
 */
class lb_I_EventManager : public lb_I_Unknown {
public:

	/**
	 * The implementation of this interface is in the GUI server, so it is the place
	 * to hold the event management.
	 */
	virtual lbErrCodes LB_STDCALL registerEvent(char* EvName, int & EvNr) = 0;
	virtual lbErrCodes LB_STDCALL resolveEvent(char* EvName, int & evNr) = 0;

protected:


	friend class lb_I_Dispatcher;
};
/*...e*/
/*...sclass lb_I_EvHandler:0:*/
class lb_I_EvHandler : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) = 0;
	virtual lbEvHandler LB_STDCALL getHandler() = 0;
	virtual lb_I_EventHandler* LB_STDCALL getHandlerInstance() = 0;
		
	virtual lbErrCodes LB_STDCALL call(lb_I_Unknown* evData, lb_I_Unknown** evResult) = 0; 
};
/*...e*/

/*...sclass lb_I_DispatchRequest:0:*/
class lb_I_DispatchRequest : public lb_I_Unknown {
public:
	virtual lbErrCodes LB_STDCALL setRequestName(char* name) = 0;
};
/*...e*/
/*...sclass lb_I_DispatchResponce:0:*/
class lb_I_DispatchResponce : public lb_I_Unknown {
public:
	virtual int LB_STDCALL isOk() = 0;
};
/*...e*/
/*...sclass lb_I_Dispatcher:0:*/
class lb_I_Dispatcher : public lb_I_Unknown {
public:

	virtual lbErrCodes LB_STDCALL setEventManager(lb_I_EventManager* EvManager) = 0;
	
/*...sevent handler management:8:*/

	/**
	 * Register an event handler function under it's name. If the name is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName) = 0;
	
	/**
	 * Register an event handler function under it's id. If the id is not registered, the
	 * function will fail. The dispatcher is not responsible for registering event names or id's.
	 */
	virtual lbErrCodes LB_STDCALL addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) = 0;
/*...e*/
	
/*...scascade management:8:*/
	/**
	 * Add a dispatcher, if it is not my self (singleton). This enables cascaded
	 * dispatching and complete replacement of a dispatcher.
	 */
	virtual lbErrCodes LB_STDCALL addDispatcher(lb_I_Dispatcher* disp) = 0;
	
	virtual lbErrCodes LB_STDCALL delDispatcher(lb_I_Dispatcher* disp) = 0;
/*...e*/

/*...sdispatching:8:*/
	/**
	 * Any dispatch function should provided with the information of what type to be dispatched.
	 * An input is required - possibly NULL.
	 * A result will be generated, if succeeded.
	 *
	 */
	virtual lbErrCodes LB_STDCALL dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;
	virtual lbErrCodes LB_STDCALL dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) = 0;
	
	/**
	 * lb_I_DispatchRequest variant. Parameter contains all needed data for the dispatch request.
	 */
	 
	virtual lb_I_DispatchResponce* LB_STDCALL dispatch(lb_I_DispatchRequest* req) = 0; 
/*...e*/
};
/*...e*/

/*...sclass lb_I_EventHandler:0:*/
/**
 *
 */
class lb_I_EventHandler {
public:
	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp) = 0;
};
/*...e*/

class lb_I_DatabaseForm;

/*...sclass lb_I_Form:0:*/
class lb_I_Form : public lb_I_Unknown  {
public:

	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) = 0;

	virtual void LB_STDCALL show() = 0;
};
/*...e*/
/*...sclass lb_I_GUI:0:*/
/**
 * It seems, that this is the factory class for any GUI elements. It also knows about any instance.
 */
class lb_I_GUI :
public lb_I_Unknown
{
public:
	
/*...sCreation functions:8:*/
	/**
	 * Creation functions
	 */
	virtual lb_I_Unknown* LB_STDCALL createFrame() = 0;
	virtual lb_I_Unknown* LB_STDCALL createMenu() = 0;
	virtual lb_I_Unknown* LB_STDCALL createMenuBar() = 0;
	virtual lb_I_Unknown* LB_STDCALL createMenuEntry() = 0;

	virtual lb_I_DatabaseForm* LB_STDCALL createDBForm(char* formName, char* queryString) = 0;
/*...e*/
/*...sGetter functions:8:*/
	/**
	 * Getter functions
	 */
	 
	virtual lb_I_Frame* LB_STDCALL getFrame() = 0; 
/*...e*/
/*...sMenu manipulation:8:*/
	/**
	 * Menu manipulation based on current position. The members
	 * deleates this calls to the lb_I_GUI instance.
	 */
	 
	virtual lbErrCodes LB_STDCALL deactivateMenuEntry() = 0;
	virtual lbErrCodes LB_STDCALL activateMenuEntry() = 0;

	/**
	 * This enables the manipulation of any main menus and the addition of
	 * main menus.
	 */	
	virtual lbErrCodes LB_STDCALL gotoMenuRoot() = 0;
	
	/**
	 * Go to any menu entry, to manipulate at this position
	 */
	virtual lbErrCodes LB_STDCALL gotoMenuEntry(char* entry) = 0;
	
	/**
	 * Insert after the current position
	 */
	virtual lbErrCodes LB_STDCALL insertMenuEntry(lb_I_Unknown* entry) = 0;
	
	/**
	 * Add an entry at the current position (insert before)
	 */
	
	virtual lbErrCodes LB_STDCALL addMenuEntry(lb_I_Unknown* entry) = 0; 
/*...e*/



/*
 * This will fasten up the current sample. It is not really needed to use
 * parameter based dispatching, if the target GUI interface provides the desired
 * functionality.
 *
 * So here, the GUI interface should provide some primitives handling code in its
 * interface.
 * 
 * These are buttons, labels, textfields, menus and so on.
 *
 * The handling code should include creation, removement, hiding and so on.
 */
/*...sfunctions that had been implemented in metaapplication:0:*/

	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	virtual lbErrCodes LB_STDCALL addMenuBar(char* name) = 0;

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(char* name) = 0;
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) = 0;
/*...e*/



	
	/**
	 * Let the GUI server show a dialog box
	 */
	virtual lbErrCodes LB_STDCALL msgBox(char* windowTitle, char* msg) = 0;

	/**
	 * We do not implement a dispatcher here, but we need one
	 */
	virtual lbErrCodes LB_STDCALL setDispatcher(lb_I_Dispatcher* disp) = 0;	
};
/*...e*/
/*...sclass lb_I_Frame:0:*/
/**
 * It seems, that this is the factory class for any GUI elements. It also knows about any instance.
 */
class lb_I_Frame :
public lb_I_Unknown
{
public:
	virtual lb_I_Unknown* LB_STDCALL createFrame() = 0;
//	virtual lbErrCodes registerEvent(char* evName, int evType, frame->getDispatcherFn())

};
/*...e*/
/*...sclass lb_I_wxGUI:0:*/
class lb_I_wxGUI : public lb_I_GUI {
public:
};
/*...e*/
/*...sclass lb_I_MetaApplication:0:*/
class lb_I_MetaApplication : public lb_I_Unknown {
public:

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* gui) = 0;
	virtual lbErrCodes LB_STDCALL Initialize() = 0;
	virtual lbErrCodes LB_STDCALL run() = 0;
	
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** gui) = 0;
	
	/**
	 * Get access to the main event manager, so all parts can initialize event handlers
	 * and then initialize Actors for still initialized event handlers.
	 */
	virtual lb_I_EventManager* getEVManager() = 0;



	/**
	 * Basic functions to be used for a UI application
	 */

	virtual lbErrCodes LB_STDCALL addMenuBar(char* name) = 0;
	virtual lbErrCodes LB_STDCALL addMenu(char* name) = 0;
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL) = 0;
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h) = 0;
	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h) = 0;
};
/*...e*/

class lb_I_Plugin;
class lb_I_PluginImpl;
class lb_I_String;

/*
 * The plugin manager should handle automatic loading of exsisting plugins and optionally
 * unload plugins by a plugin management dialog.
 */
/*...sclass lb_I_PluginManager:0:*/
class lb_I_PluginManager : public lb_I_Unknown {
public:

	/**
	 * Starts listing of plugins.
	 */
	virtual bool LB_STDCALL beginEnumPlugins() = 0;
	
	/**
	 * Gets the next plugin handle instance. This does not
	 * load an instance of the plugin implementation.
	 *
	 * To finally use the plugin, you must attach to it.
	 */
	virtual lb_I_Plugin* LB_STDCALL nextPlugin() = 0;
	
	/**
	 * Attach the plugin implementation to the plugin handle.
	 * After attaching the plugin, you will be able to init
	 * the plugin via the initialize() function.
	 */
	virtual bool LB_STDCALL attach(lb_I_Plugin* toAttach) = 0;
	
	/** 
	 * Detach it. If it returns true, it could be destroyed or
	 * stored permanently for replacing with other implementation.
	 */
	virtual bool LB_STDCALL detach(lb_I_Plugin* toAttach) = 0;
};
/*...e*/

/*
 * The plugin module is a class per module, that should list all included plugins for one
 * module. This should be similar to the BEGIN_IMPLEMENT_UNKNOWN and ADD_INTERFACE macros.
 */
/*...sclass lb_I_PluginModule:0:*/
class lb_I_PluginModule : public lb_I_Unknown {
public:
	/**
	 * Get the list of plugins for the current plugin module.
	 */
	virtual lb_I_Container* LB_STDCALL getPlugins() = 0;
	
	/**
	 * This function must be called once per instance of this
	 * module. It internally generates the list of plugins
	 * implemented in this module.
	 */
	virtual void LB_STDCALL initialize() = 0;

protected:
	/**
	 * Used internally in the macros to build the plugin list.
	 */
	virtual void LB_STDCALL enumPlugins() = 0;
};


#define DECLARE_PLUGINS() \
	virtual lb_I_Container* LB_STDCALL getPlugins(); \
	virtual void LB_STDCALL enumPlugins(); \
	UAP(lb_I_Container, Plugins, __FILE__, __LINE__)

#define BEGIN_PLUGINS(cls) \
lb_I_Container* cls::getPlugins() { \
	Plugins++; \
	return Plugins.getPtr(); \
} \
void LB_STDCALL cls::enumPlugins() { \
	lbErrCodes err = ERR_NONE; \
	REQUEST(manager.getPtr(), lb_I_Container, Plugins)

#define ADD_PLUGIN(plugin, scope) \
	UAP_REQUEST(manager.getPtr(), lb_I_Plugin, P##plugin##scope) \
	P##plugin##scope->setName(#plugin); \
	P##plugin##scope->setScope(#scope); \
	UAP_REQUEST(manager.getPtr(), lb_I_String, s##plugin##scope) \
	UAP(lb_I_KeyBase, Key##plugin##scope, __FILE__, __LINE__) \
	UAP(lb_I_Unknown, ukPlugin##plugin##scope, __FILE__, __LINE__) \
	s##plugin##scope->setData(#plugin); \
	QI(s##plugin##scope, lb_I_KeyBase, Key##plugin##scope, __FILE__, __LINE__) \
	QI(P##plugin##scope, lb_I_Unknown, ukPlugin##plugin##scope, __FILE__, __LINE__) \
	Plugins->insert(&ukPlugin##plugin##scope, &Key##plugin##scope); \


#define END_PLUGINS() }

/*...e*/

/*
 * Interface for single plugin. This should be a wrapper to the plugin implementation.
 */
/*...sclass lb_I_Plugin:0:*/
class lb_I_Plugin : public lb_I_Unknown {
public:

	/**
	 * Initialize the plugin. This function can only be called, if it has been
	 * attached by the plugin manager. If this hasn't been made, nothing happens.
	 */
	virtual void LB_STDCALL initialize() = 0;

	/**
	 * The plugin must know of the plugin manager to self detach at cleanup due to
	 * release calls.
	 * This function is called prior to setAttached.
	 */
	virtual void LB_STDCALL setPluginManager(lb_I_PluginManager* plM) = 0; 

	/**
	 * Called by attach/detach function from plugin manager.
	 * If the parameter is NULL, the plugin should uninitialize before
	 * really detaching.
	 */
	virtual void LB_STDCALL setAttached(lb_I_PluginImpl* impl = NULL) = 0;

	/**
	 * This function should uninitialize all handlers, that are registered.
	 */
	virtual void LB_STDCALL uninitialize() = 0;

	/**
	 * Set the name of the module where the plugin is in.
	 */
	virtual void LB_STDCALL setModule(char* module) = 0;
	
	/**
	 * Set the name of the plugin. This would be the functor name for
	 * an instance of the plugin.
	 */
	virtual void LB_STDCALL setName(char* name) = 0;
	
	/**
	 * The scope identifies the area of usage. If the scope is GUI, it
	 * would only be usable in graphical user environment. If it is UI,
	 * it would be usable in textual user interfaces as well. If it is
	 * NONE, it could also be used in non user interface centric apps.
	 *
	 * This means, propably a server, where no user interaction is available.
	 */
	virtual void LB_STDCALL setScope(char* scope) = 0;
	
	
	virtual char* LB_STDCALL getModule() = 0;
	virtual char* LB_STDCALL getName() = 0;
	virtual char* LB_STDCALL getScope() = 0;
	
};
/*...e*/

/*...sclass lb_I_PluginImpl:0:*/
class lb_I_PluginImpl : public lb_I_Unknown {
public:

	virtual void LB_STDCALL initialize() = 0;
};
/*...e*/



#include <lbInterfaces-sub-xml.h>
#include <lbInterfaces-sub-classes.h>	
#include <lbInterfaces-sub-db.h>
#include <lbInterfaces-sub-wxWrapper.h>

#endif // __LB_INTERFACES__

/*...sdocu:0:*/
/**
 * For all Interfaces are factories needed. How should I design these
 * factories ?
 */
 
/*...e*/

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

#ifndef LB_STDCALL
#ifdef WINDOWS
#define LB_STDCALL __cdecl
#endif
#ifndef WINDOWS
#define LB_STDCALL
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
#define DLLEXPORT
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


/**
 * This is a base class for all callback able objects
 */
///////////////////////////////////////////////////////////////
// Type for lb protocol callback functions. This should be an interface.
typedef lbErrCodes (lb_I_ProtocolTarget::*lbProtocolCallback)( lb_I_Transfer_Data const &, lb_I_Transfer_Data&);
typedef lbErrCodes (lb_I_CallbackTarget::*lbMemberCallback)( const char* handlername, lb_I_Transfer_Data&);

/**
 * The base interface, that currently implements only release.
 * A query interface should be added. But is M$'s solution usable ?
 */
 
class lb_I_gcManager;
class lb_I_Unknown;
class lb_I_Module;

/*
	CL_LOG("Releasing instance"); \
*/
/*...sdefine RELEASE\40\instance\41\:0:*/
#define RELEASE(instance) \
	{ lbErrCodes err; \
		if ((err = instance->release(__FILE__, __LINE__)) != ERR_NONE) { \
			if (err == ERR_REFERENCE_COUNTING ) { \
				printf("Reference count mismatch at %d in %s\n", __LINE__, __FILE__); \
				getch(); \
			} else { \
			} \
		} else { \
			instance = NULL; \
		} \
	}
/*...e*/
/*...sdefine RELEASE_1\40\instance\44\ __MACRO_LINE__\44\ __MACRO_FILE__\41\:0:*/
#define RELEASE_1(instance, __MACRO_FILE__, __MACRO_LINE__) \
	{ lbErrCodes err; \
		if ((err = instance->release(__MACRO_FILE__, __MACRO_LINE__)) != ERR_NONE) { \
			if (err = ERR_REFERENCE_COUNTING ) { \
				printf("Reference count mismatch at %d in %s\n", __MACRO_LINE__, #__MACRO_FILE__); \
			} else { \
			} \
		} \
	}
/*...e*/
/*...sdefine QI\40\source\44\ interface\44\ target\44\ file\44\ line\41\:0:*/
#define QI(source, interface, target, file, line) \
 	err = source->queryInterface(#interface, (void**) target, file, line);
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
	
public:
	virtual lbErrCodes LB_STDCALL release(char* file, int line) = 0;
	/**
	 * This function indicates, if the object will be deleted on a call
	 * of release().
	 */
	virtual char* LB_STDCALL getCreationLoc() = 0;
	virtual int LB_STDCALL deleteState() = 0;
	virtual void LB_STDCALL setDebug(int i) = 0;
	virtual int LB_STDCALL getRefCount() = 0;
	virtual char* LB_STDCALL getClassName() = 0;

	virtual void LB_STDCALL setModuleManager(lb_I_Module* m, char* file = __FILE__, int line = __LINE__) = 0;
	
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line) = 0;
        
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
 */
/*...sbla \40\geht nicht\41\:0:*/
#ifdef bla
class UAP {
public:
	UAP(lb_I_Unknown *& autoPtr) {
                _autoPtr = autoPtr;
        }
        virtual ~UAP() { RELEASE(_autoPtr); }
protected:
lb_I_Unknown* _autoPtr;
};
#endif
/*...e*/

#define UAP(interface, Unknown_Reference, file, line) \
		class UAP##Unknown_Reference { \
		public: \
	        UAP##Unknown_Reference() { \
	        	_autoPtr = NULL; \
	        	allowDelete = 1; \
		} \
		virtual ~UAP##Unknown_Reference() { \
			if (_autoPtr != NULL) { \
				if (allowDelete != 1) { \
					if (_autoPtr->deleteState() == 1) { \
						CL_LOG("Error: Instance would be deleted, but it's not allowed !!"); \
					} \
				} \
				RELEASE(_autoPtr); \
			} \
		} \
		\
		interface* getPtr() const { return _autoPtr; } \
		void setPtr(interface*& source) { \
			if (_autoPtr != NULL) { \
				CL_LOG("Error: UAP object still initialized!"); \
			} \
			_autoPtr = source; \
		} \
		\
		interface& operator * () { return *_autoPtr; } \
		interface* operator -> () const { \
			if (_autoPtr == NULL) { \
				char buf[1000] = ""; \
				sprintf(buf, "Error: UAP pointer (%s) for interface %s is NULL!", #Unknown_Reference, #interface); \
				CL_LOG(buf); \
			} \
			return _autoPtr; \
		} \
		interface* operator -> () { \
			if (_autoPtr == NULL) { \
				char buf[1000] = ""; \
				sprintf(buf, "Error: UAP pointer (%s) for interface %s is NULL!", #Unknown_Reference, #interface); \
				CL_LOG(buf); \
			} \
			char ptr[20] = ""; \
			sprintf(ptr, "%x", _autoPtr); \
			if (strcmp(ptr, "cdcdcdcd") == 0) { \
			        CL_LOG("Error: Uninitialized pointer will be used!"); \
			} \
			return _autoPtr; \
		} \
		UAP##Unknown_Reference& operator++(int) { \
			interface* temp = NULL; \
			_autoPtr->queryInterface(#interface, (void**) &temp, file, line); \
			return *this; \
		} \
		interface ** operator & () { \
			return &_autoPtr; \
		} \
		\
		UAP##Unknown_Reference& operator = (interface* autoPtr) { \
			char ptr[20] = ""; \
			sprintf(ptr, "%x", autoPtr); \
			if (strcmp(ptr, "cdcdcdcd") == 0) { \
				CL_LOG("Error: Uninitialized pointer will be set!"); \
				_autoPtr = NULL; \
			} else _autoPtr = autoPtr; \
			return *this; \
		} \
		int operator == (const interface* b) const { \
			return _autoPtr == b; \
		} \
		int operator != (const interface* b) const { \
			return _autoPtr != b; \
		} \
		void setDelete(int _allow) { allowDelete = _allow; } \
		\
		protected: \
	        interface* _autoPtr; \
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
	virtual void 		LB_STDCALL setModuleManager(lb_I_Module* m, char* file = __FILE__, int line = __LINE__); \
	virtual void 		LB_STDCALL resetRefcount(); \
	virtual void 		LB_STDCALL setDebug(int i = 1) { debug_macro = i; } \
	virtual lbErrCodes 	LB_STDCALL release(char* file, int line); \
	virtual char* 		LB_STDCALL getClassName(); \
	virtual char*           LB_STDCALL getCreationLoc(); \
	virtual int 		LB_STDCALL deleteState(); \
	virtual lbErrCodes 	LB_STDCALL queryInterface(char* name, void** unknown, char* file, int line); \
	virtual lb_I_Unknown* 	LB_STDCALL clone(char* file, int line) const; \
	virtual lbErrCodes 	LB_STDCALL setData(lb_I_Unknown* u); \
	virtual int 		LB_STDCALL getRefCount() { return ref; }

#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
char* LB_STDCALL classname::getClassName() { \
	return #classname; \
} \
\
void LB_STDCALL classname::setModuleManager(lb_I_Module* m, char* file, int line) { \
	if (m == NULL) { \
		printf("Error: Set module manager with a NULL pointer!"); \
		return; \
	} \
	\
	further_lock = 0; \
	if (debug_macro == 1) { \
		CL_LOG("Warning: setModuleManager() must be enhanced by module manager use"); \
	} \
	m->queryInterface("lb_I_Module", (void**) &manager, file, line); \
	\
	if (manager != NULL) { \
		char *datei = strrchr(file, '\\'); \
		if (datei == NULL) \
			datei = file; \
		else \
			datei++; \
		manager->notify_create(this, #classname, datei, line); \
	} \
} \
\
void LB_STDCALL classname::resetRefcount() { ref = STARTREF; } \
int LB_STDCALL classname::deleteState() { \
	return (ref-1 == STARTREF) ? 1 : 0; \
} \
char*      LB_STDCALL classname::getCreationLoc() { \
	char buf[20] = ""; \
	sprintf(buf, "%x", this); \
	if (manager != NULL) return manager->getCreationLoc(buf); \
	return strdup("No location stored"); \
} \
lbErrCodes LB_STDCALL classname::release(char* file, int line) { \
        ref--; \
        char addr[20] = ""; \
        \
	sprintf(addr, "%x", this); \
        if (manager != NULL) { \
        	manager->notify_release(this, #classname, file, line); \
        } \
	\
        if (ref == STARTREF) { \
        	if (manager != NULL) { \
        		if (manager->can_delete(this, #classname) == 1)	{ \
        			delete this; \
        		} \
        		else \
        			CL_LOG("Error: Instance has been deleted prior!"); \
        	} \
        	return ERR_NONE; \
        } \
        char buf[1000] = ""; \
        if (ref < STARTREF) { \
        	sprintf(buf, "Error: Reference count of instance %x of object type %s is less than %d (%d) !!!", this, #classname, STARTREF, ref); \
        	CL_LOG(buf); \
        	getch(); \
        	return ERR_REFERENCE_COUNTING; \
        } \
        return ERR_INSTANCE_STILL_USED; \
} \
\
lb_I_Unknown* LB_STDCALL classname::clone(char* file, int line) const { \
\
	classname* cloned = new classname(); \
	char ptr[20] = ""; \
	sprintf(ptr, "%x", cloned); \
	cloned->setDebug(0); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	cloned->setFurtherLock(0); \
	if (manager == NULL) CL_LOG(#classname "::clone() can't be used because manager is a NULL pointer!"); \
	cloned->setModuleManager(manager.getPtr(), file, line); \
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned, file, line) != ERR_NONE) { \
		CL_LOG("Error while getting interface"); \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	cloned->resetRefcount(); \
	\
	if (manager != NULL) { \
	        manager->notify_add(cloned, cloned->getClassName(), file, line); \
	} \
        else \
		if (debug_macro == 1) { \
                	CL_LOG("Module manager was not set!"); \
		} \
	\
	lb_I_Unknown* uk = NULL; \
	if (uk_cloned->queryInterface("lb_I_Unknown", (void**) &uk, file, line) != ERR_NONE) { \
		CL_LOG("Error while getting interface"); \
	} \
\
	return uk; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown, char* file, int line) { \
	char buf[1000] = ""; \
	char iFaces[1000] = ""; \
	char _classname[100] = #classname; \
\
	char ptr[10] = ""; \
	sprintf(ptr, "%x", this); \
	if (further_lock == 1) { \
		CL_LOG("Error: Object has been locked due to missing module manager!"); \
		return ERR_STATE_FURTHER_LOCK; \
	} \
	if (unknown == NULL) { \
		sprintf(buf, "Error: Got NULL pointer reference while queryInterface() called for %s !", name); \
		CL_LOG(buf); \
	} \
\
	strcat(iFaces, "lb_I_Unknown, "); \
        if (strcmp(name, "lb_I_Unknown") == 0) { \
        	if (ref < STARTREF) { \
        		CL_LOG("Reference count error in queryInterface (" #classname ")"); \
        	} \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                if (manager != NULL) { \
		        manager->notify_add(this, _classname, file, line); \
		} \
		else { \
	        	setFurtherLock(1); \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

#define ADD_INTERFACE(interfaceName) \
	buf[0] = 0; \
\
	if ((strlen(iFaces)+strlen(#interfaceName)) > 1000) { \
		CL_LOG("String size exceeds fixed len!"); \
	} \
	strcat(iFaces, #interfaceName ", "); \
        if (strcmp(name, #interfaceName) == 0) { \
                ref++; \
                *unknown = (interfaceName*) this; \
                if (manager != NULL) { \
                	manager->notify_add(this, _classname, file, line); \
                } \
		else { \
		        setFurtherLock(1); \
	        	return ERR_STATE_FURTHER_LOCK; \
		} \
                return ERR_NONE; \
        }

#define END_IMPLEMENT_LB_UNKNOWN() \
	buf[0] = 0; \
	sprintf(buf, "Error: Requested interface '%s' not found!", name); \
	CL_LOG(buf); \
	return ERR_NONE; \
}
/* Das geht im Makro nicht:
//	printf("Checked interfaces: %s\n", iFaces); \
\
*/
/*...e*/

/**
 * Base of all instances - the functor
 */
 
typedef lbErrCodes (LB_STDCALL *T_pLB_GET_UNKNOWN_INSTANCE) (lb_I_Unknown**, lb_I_Module* m, char* file, int line);

/**
 * Idea: To ensure, that the object gets the module manager, it is locked until
 * setModuleManager is called with a correct value.
 * queryInterface can at first time do it's work, store the data, that has to
 * be stored in module manager and lock the instance for further use.
 */
/*...sstandard functor:0:*/

#define DECLARE_FUNCTOR(name) \
lbErrCodes DLLEXPORT LB_STDCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line);

#define IMPLEMENT_FUNCTOR(name, clsname) \
lbErrCodes DLLEXPORT LB_STDCALL name(lb_I_Unknown** uk, lb_I_Module* m, char* file, int line) { \
\
	lbErrCodes err = ERR_NONE; \
        clsname* instance = new clsname(); \
        *uk = NULL; \
        char buf[100] = ""; \
        \
        instance->setFurtherLock(0); \
        if (m != NULL) instance->setModuleManager(m); \
        \
        if ((err = instance->queryInterface("lb_I_Unknown", (void**) uk, file, line)) != ERR_NONE) { \
                CL_LOG("Failed to create unknown reference to instance of "#clsname"!"); \
                if (err == ERR_STATE_FURTHER_LOCK) return err; \
                return ERR_FUNCTOR; \
        } \
\
        return ERR_NONE; \
}

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

class lb_I_String;

#include <lbInterfaces-sub-xml.h>
#include <lbInterfaces-sub-classes.h>	

#endif // __LB_INTERFACES__

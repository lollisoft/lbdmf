/*...sdocu:0:*/
/**
 * For all Interfaces are factories needed. How should I design these
 * factories ?
 */
 
/*...e*/

/**
 * All classes, that anounce callbacks, must implement the interface for
 * lb_I_CallbackManager. The callback manager did not need to handle its
 * own table, more it may delegate this to the static (singleton) handler.
 */


#ifndef __LB_INTERFACES__
#define __LB_INTERFACES__

#include <lbErrCodes.h>

//#define LB_STDCALL

#ifndef LB_STDCALL
#define LB_STDCALL __stdcall
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

typedef unsigned short LB_DATA;
typedef unsigned short u_short;
/*...e*/
#endif // __BASE_TYPES_DEFINED__

class lb_I_CallbackTarget;
class lb_I_ProtocolTarget;

#include <lbInterfaces-sub-transfer.h>


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
 

	/* setData must check the type of this ! */
	/* = may also be possible */
/*...sclass lb_I_Unknown:0:*/
#define STARTREF 0

class lb_I_Unknown {
public:
	lb_I_Unknown() {}
	virtual ~lb_I_Unknown() {}

	virtual lbErrCodes LB_STDCALL release() = 0;
	
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown) = 0;
        
        /**
         * This was used yet for put an object in a container. After inserting the object
         * into the container, there are two instances (not two references).
         * So the cloning is generaly a good way to make copies of an object.
         */
        virtual lb_I_Unknown* LB_STDCALL clone() const = 0;
        virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u) = 0;

//friend class lb_I_gcManager;	
};

#define DECLARE_LB_UNKNOWN() \
private: \
	int ref; \
public: \
	virtual lbErrCodes LB_STDCALL release(); \
	virtual lbErrCodes LB_STDCALL queryInterface(char* name, void** unknown); \
	virtual lb_I_Unknown* LB_STDCALL clone() const; \
	virtual lbErrCodes LB_STDCALL setData(lb_I_Unknown* u);

#define BEGIN_IMPLEMENT_LB_UNKNOWN(classname) \
lbErrCodes LB_STDCALL classname::release() { \
        ref--; \
        if (ref == STARTREF) delete this; \
        return ERR_NONE; \
} \
\
lb_I_Unknown* classname::clone() const { \
\
	classname* cloned = new classname(); \
	lb_I_Unknown* uk_this; \
\
	lb_I_Unknown* uk_cloned = NULL; \
\
	if (cloned->queryInterface("lb_I_Unknown", (void**) &uk_cloned) != ERR_NONE) { \
		CL_LOG("Error while getting interface"); \
	} \
\
	uk_cloned->setData((lb_I_Unknown*) this); \
\
	return uk_cloned; \
\
} \
\
lbErrCodes LB_STDCALL classname::queryInterface(char* name, void** unknown) { \
        if (strcmp(name, "lb_I_Unknown") == 0) { \
                ref++; \
                *unknown = (lb_I_Unknown*) this; \
                return ERR_NONE; \
        }

#define ADD_INTERFACE(interfaceName) \
        if (strcmp(name, #interfaceName) == 0) { \
                ref++; \
                *unknown = (interfaceName*) this; \
                return ERR_NONE; \
        }

#define END_IMPLEMENT_LB_UNKNOWN() \
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
	virtual lbErrCodes initialize() = 0;
	virtual lbErrCodes request(const char* request, lb_I_Unknown*& result) = 0;
	virtual lbErrCodes uninitialize() = 0;
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

#include <lbInterfaces-sub-classes.h>	
#include <lbInterfaces-sub-xml.h>

#endif // __LB_INTERFACES__

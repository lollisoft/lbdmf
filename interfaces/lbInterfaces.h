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

class lb_I_CallbackTarget;
class lb_I_ProtocolTarget;

/**
 * This is a base class for all callback able objects
 */
///////////////////////////////////////////////////////////////
// Type for lb protocol callback functions. This should be an interface.
typedef lbErrCodes (lb_I_ProtocolTarget::*lbProtocolCallback)( lb_Transfer_Data, lb_Transfer_Data&);
typedef lbErrCodes (lb_I_CallbackTarget::*lbMemberCallback)( const char* handlername, lb_Transfer_Data&);

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
class lb_I_Requestable : public lb_I_ErrorDescription {
public:
	virtual lbErrCodes initialize() = 0;
	virtual lbErrCodes request(const char* request, lb_Transfer_Data& result) = 0;
	virtual lbErrCodes release() = 0;
};
/*...e*/

/*...sclass lb_I_CallbackManager:0:*/
class lb_I_CallbackManager : public lb_I_ErrorDescription {
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
class lb_I_CallbackDispatcher : public lb_I_ErrorDescription {
public:
	virtual lbErrCodes dispatch(const char* request, lb_Transfer_Data& result) = 0;
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
class lb_I_ProtocolManager : public lb_I_ErrorDescription {
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
class lb_I_ProtocolDispatcher : public lb_I_ErrorDescription {
public:
	virtual lbErrCodes dispatch(lb_Transfer_Data request, lb_Transfer_Data& result) = 0;
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
	

#endif // __LB_INTERFACES__

#ifndef LB_APPCS
#define LB_APPCS

/*...sdefine DLLEXPORT:0:*/
#undef DLLEXPORT

#ifdef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/


/*...sclass lbConnection:0:*/
class lbConnection : public lbObject {
public:
	lbConnection(char* host, int _pid, int _tid);
	virtual ~lbConnection();
	
	/**
	 * Abstract functions
	 */
	void setType();
	lbObject* clone() const;
	
	char* hostname;
	int pid;
	int tid;
};
/*...e*/

class lbAppServer;

#ifdef bla
/*...sObject thunking implementation:0:*/
/**
 * Object thunking implementation
 */


/*...sDocu:0:*/
// Declarations added here will be included at the top of the .HPP file

///////////////////////////////////////////////////////////////////////////////
//
//   1999 Herbert Menke
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely
//
//     If you find any bugs in this software or 
//     you have any suggestions for extension, 
//     please send a mail to me:
//
//     Herbert Menke
//     Goetheallee 21
//     D 53225 Bonn
//     E-Mail: h.menke@gmx.de
//
///////////////////////////////////////////////////////////////////////////////
//
//  Version  Date        Remarks
//   1.00    05.11.1998  Initial Version created
//   1.01    10.03.1999  Minor bugs fixed
//                       thunk code optimized
//                       Interface changed
//   1.02    04.04.1999  thunk for rtl callback added
///////////////////////////////////////////////////////////////////////////////
// Object Thunking
//
// Using a class member function as a callback function is not trivial, 
// since a class member function must be passed as an implicit pointer 
// to the object it is associated with. 
// Object thunking is a method to associate a callback with an object. 
// Borland's OWL uses this scheme to use the window callback procedure 
// as a member callback function
//
// Object Thunking creates a thunk( a dynamically piece of code) that adds 
// the this pointer on the stack and jumps to the member function.
//
// The following code is used for the stdcall thunk:
//
//  push eax                  ; increase stack
//  mov  eax, thisPointer     ; load thispointer
//  xchg eax, 4[esp]          ; exchange thispointer and return address
//  xchg [esp], eax           ; save return address
//  push callBackPointer      ; push callbackpointer
//  ret                       ; jmp with ret to member callback
//
// The following code is used for the rtl thunk:
//
//  push ecx                  ; ecx must be saved
//  push edx                  ; push second parameter
//  push eax                  ; push first parameter
//  push thispointer          ; push thispointer
//  mov  eax,callback         ; load address of member callback
//  call eax                  ; and call method
//  pop ecx                   ; restore ecx
//  ret                       ; and back

// The class WObjectThunk provides the object thunking method for the 
// Power++ component library.
//
// For more info read "Object Thunking.Rtf"
/*...e*/



/////////////////////////////////////////////////////////////////////////
// Typedef for rtl callback functions qsort, bsearch, lsearch and lfind
typedef int (* WRtlCallBack )(const void *, const void *);

///////////////////////////////////////////////////////////////
// Type for member callback functions
typedef void * __stdcall (lbAppServer::*WMemberCallBack)( void *);




///////////////////////////////////////////////////////////////
// Helper macro
#define WMemberCallBackCast( __cls, __mcb )              \
        static_cast< void * (lbAppServer::*)( void * ) >(    \
        reinterpret_cast< void * (__cls::*)( void * ) >( \
        &__cls::__mcb ) )


#if !defined( __WObjectThunk_declspec )
#define __WObjectThunk_declspec
#endif

class __WObjectThunk_declspec WObjectThunk
{

    public:
        // add your public instance data here
    private:
        // add your private instance data here
    protected:
        // add your protected instance data here

    public:
        WObjectThunk();

    public:
/*...sDocu:8:*/
        //
        // Create method
        //

        // creates the thunk and returns it as a void * pointer, that should 
        // be used as the callback parameter for Windows Enumeration- and 
        // Callback functions.

        // object	                is the object to which the callback applies. 
        //                        This is almost always the class that receives 
        //                        the callback; therefore, the argument is commonly this.
        // callbackMemberFunction is the pointer to the class member callback function. 
        //                        Use the WMemberCallBackCast macro to generate a callback 
        //                        pointer to function. 
        //                        The use is according to the WEventHandlerCast macro.
        // createRtlCallback      if true a thunk for the watcom runtime library callback
        //                        function is created. Only for use with qsort, bsearch,
        //                        lsearch and lfind
/*...e*/

        static void * Create(lbObject * object, WMemberCallBack callbackMemberFunction, BOOL createRtlCallback = FALSE );

    public:
/*...sDocu:8:*/
        //
        // Destroy method
        //

        // destroys the thunk and frees the memory used for the thunk.

        // thunkCode	is the pointer to the thunk, that was returned by the Create method.
        //
        // The return value is true, if the thunk was destroyed.
/*...e*/

        static BOOL Destroy( void * thunkCode );

};
/*...e*/
#endif

/**
 * This is a base class for all servers
 */
///////////////////////////////////////////////////////////////
// Type for lb member callback functions
typedef lbErrCodes (lbAppServer::*lbMemberEvent)( lb_Transfer_Data, lb_Transfer_Data&);

/*...sclass DLLEXPORT lbAppServer:0:*/
class DLLEXPORT lbAppServer {
public:
	lbAppServer();
	virtual ~lbAppServer();

	/**
	 * Checks, if the parameters (hostname, pid and tid) are available.
	 * Then it checks, if tid is as key available in connections container.
	 * If all succeeds, 1 is returned.
	 */
	int isConnected(lb_Transfer_Data &request);

/*...sFunctions needed to encapsulate the transfer class:8:*/
	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	lbErrCodes waitForRequest(lbTransfer* _clt, lb_Transfer_Data &request);
	
	lbErrCodes handleRequest(lb_Transfer_Data request, lb_Transfer_Data &result);
	                  
	lbErrCodes answerRequest(lbTransfer* _clt, lb_Transfer_Data result);
/*...e*/

	int run(); // called from main or thread

	// Called from HandleRequest()
#ifdef bla
//Now handled by registered dispatch handlers
/*...svirtual lbErrCodes _request\40\lb_Transfer_Data request\44\ lb_Transfer_Data \38\result\41\ \61\ 0\59\:8:*/
	/**
	 * _service is called by HandleRequest.
	 */
	virtual lbErrCodes _request(lb_Transfer_Data request, 
	                     lb_Transfer_Data &result) = 0;
/*...e*/
#endif
	
	// Called from run() and gives a lbTransfer instance
/*...svirtual lbErrCodes _connected\40\lbTransfer _clt\41\ \61\ 0\59\:8:*/
	/**
	 * Implement this for your connected state. It is called per request.
	 * I mean, that a socket connection has been opened and the
	 * function is being called. So I am able to put in more logic
	 * before and after the call of this function, like an 
	 * authentication, or a load checking an the ability to react.
	 * You can do what you want in your implementation, but you have
	 * to call the three functions for waiting for, handling and sending
	 * back an answer from the request.
	 * If you do nothig, because you don't need, you don't need to write
	 * a server.
	 * By letting you have to implement this function, you will be able
	 * to do your own stuff between the stages of a request. You may add
	 * some dispatching stuff to divide your service. I will be able to
	 * add some overhead to the request packets like encryption or so.
	 */
	virtual lbErrCodes _connected(lbTransfer* _clt) = 0; 
/*...e*/

/*...sDispatch handling:8:*/
	virtual lbErrCodes _registerServices() = 0;
	lbErrCodes addServiceHandler(const char* handlername, 
	                             lbMemberEvent cbFn);
/*...e*/
	
/*...svirtual char\42\ getServiceName\40\\41\ \61\ 0\59\:8:*/
	/**
	 * Implement your "servername"
	 */
	virtual char* getServiceName() = 0;
/*...e*/

protected:

	/**
	 * User management
	 */
	int addToUserList(lb_Transfer_Data request);
	int removeFromUserList(lb_Transfer_Data request);
	int AuthUser(char* user, char* passwd);

	lbErrCodes makeProtoErrAnswer(lb_Transfer_Data &result, char* msg, char* where);

/*...sSecure dataextractors:8:*/
	lbErrCodes requestString(lb_Transfer_Data& request, 
	                         char* ident, 
	                         char*& data);

	lbErrCodes requestString(lb_Transfer_Data& request, 
	                         char* ident);
	                         
	lbErrCodes requestInteger(lb_Transfer_Data& request,
				 char* ident,
				 int& data);

	lbErrCodes requestULong(lb_Transfer_Data& request,
				 char* ident,
				 unsigned long& data);
/*...e*/

/*...sProtohandler:8:*/
	// Connection is handled by 
	// User wishes to disconnect. This must be a request, because server
	// is in a thread handling requests in a loop till disconnect request
	// comes from user.
	
	lbErrCodes HandleDisconnect(	lb_Transfer_Data request,
					lb_Transfer_Data & result);

	// First request must be this. If not, no requests are handled.					
	lbErrCodes HandleConnect(	lb_Transfer_Data request,
					lb_Transfer_Data & result);


/*...e*/
	
	int initTransfer(char* host_servicename);

	lbErrCodes dispatch(lb_Transfer_Data request, lb_Transfer_Data & result);

	lbTransfer *transfer;	
	lbComponentDictionary *connections;	
	
	// This table stores the functions to be dispatched to
	lbComponentDictionary *dispatchTable;
};
/*...e*/

//typedef lbErrCodes (__export T_p_DispatchHandler)(lb_Transfer_Data request, lb_Transfer_Data& result);


/*...sclass lbDispatchFn:0:*/
class lbDispatchFn : public lbObject {
public:
	lbDispatchFn(const char* service, lbMemberEvent fn);
	virtual ~lbDispatchFn();
	
	/**
	 * Abstract functions
	 */
	void setType();
	lbObject* clone() const;
	
	lbMemberEvent getFn();
	
	lbMemberEvent dispFn;
};
/*...e*/


/**
 * Base class for all distributed objects. This class can't be instanciated
 * directly. Use lbAppBusClient instead. Also deletion is inhibed. Use
 * dismiss() instead.
 */
/*...sclass DLLEXPORT lbAppClient:0:*/
class DLLEXPORT lbAppClient : public lbObject {
private:
	lbAppClient();
        lbAppClient(lbTransfer* clConn);
        virtual ~lbAppClient();
        
        /**
         * Only lbAppBusClient should be able to create and delete instances
         * of client connections to a specific server
         */
        void* operator new(size_t size);
        void operator delete(void* ptr);
public:

        lbObject* requestObject(const char* type, const char* name);

	/**
	 * Use this function to indicate, that this instance is no longer
	 * in your use.
	 */
	void dismiss();
	
	// lbAppBusClient must be able to create objects of this class
	friend class lbAppBusClient;
	
protected:
	
	/**
	 * lbAppClient's can not instantiated directly. lbAppBusClient does
	 * this. Also it sets its instance pointer here.
	 */
	void setAppBusClient(lbAppBusClient* _AppBusClient);

	lbAppBusClient* AppBusClient;
	
	lbTransfer* clientConnection;
};
/*...e*/

#endif //LB_APPCS

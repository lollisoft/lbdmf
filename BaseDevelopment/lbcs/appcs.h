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

/**
 * Interface fÅr ein Objekt, das das Ziel eines Requests
 * darstellt. Mit diesem Interface kann man an das Objekt
 * Anfragen stellen.
 */
class lb_I_Requestable; 

class lbAppServer;


/*...sclass lbDispatchProto:0:*/
class lbDispatchProto : public lbObject {
public:
	lbDispatchProto(const char* service, lbProtocolCallback fn);
	virtual ~lbDispatchProto();
	
	/**
	 * Abstract functions
	 */
	void setType();
	lbObject* clone() const;
	
	lbProtocolCallback getProto();
	
	lbProtocolCallback dispProto;
};
/*...e*/

/*...sclass DLLEXPORT lbAppServer:0:*/
class DLLEXPORT lbAppServer : 
/*...sDerives from:24:*/
			public lb_I_ProtocolManager,    // Implemented here
			public lb_I_ProtocolDispatcher, // Implemented here
			public lb_I_ProtocolTarget      // Implemented in derived class, not here
/*...e*/
			 {
public:
	lbAppServer();
	virtual ~lbAppServer();
/*...sint isConnected\40\lb_Transfer_Data \38\request\41\\59\:8:*/
	/**
	 * Checks, if the parameters (hostname, pid and tid) are available.
	 * Then it checks, if tid is as key available in connections container.
	 * If all succeeds, 1 is returned and the request would be done.
	 */
	int isConnected(lb_Transfer_Data &request);
/*...e*/
protected:
/*...sFunctions needed to encapsulate the transfer class:8:*/
	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	lbErrCodes waitForRequest(lbTransfer* _clt, lb_Transfer_Data &request);
	
	lbErrCodes handleRequest(lb_Transfer_Data request, lb_Transfer_Data &result);
	                  
	lbErrCodes answerRequest(lbTransfer* _clt, lb_Transfer_Data result);
/*...e*/
public:
	int run(); // called from main or thread

	/**
	 * Called from run() and gives a lbTransfer instance.
	 * This is no longer abstract, because this 'baseclass'
	 * does all the server stuff for now.
	 * A derived server must only make visible its handles
	 * to this base class.
	 */
	 
/*...slbErrCodes _connected\40\lbTransfer _clt\41\\59\:8:*/
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
	lbErrCodes _connected(lbTransfer* _clt); 
/*...e*/

protected:
/*...sImplement interfaces dispatch\44\ add and del protocol handler:8:*/
	lbErrCodes dispatch(lb_Transfer_Data request, lb_Transfer_Data & result);
	lbErrCodes addProtocolHandler(const char* handlername, lbProtocolCallback cbFn);
	lbErrCodes delProtocolHandler(const char* handlername);
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

/*...svars:8:*/
	lbTransfer *transfer;	
	lbComponentDictionary *connections;	
	
	// Dispatch table for registered protocol handlers
	lbComponentDictionary *dispatchTable;
/*...e*/
};
/*...e*/

/*...sclass lbDispatchFn:0:*/
class lbDispatchFn : public lbObject {
public:
	lbDispatchFn(const char* service, lbMemberCallback fn);
	virtual ~lbDispatchFn();
	
	/**
	 * Abstract functions
	 */
	void setType();
	lbObject* clone() const;
	
	lbMemberCallback getFn();
	
	lbMemberCallback dispFn;
};
/*...e*/


/**
 * Base class for all distributed objects. This class can't be instanciated
 * directly. Use lbAppBusClient instead. Also deletion is inhibed. Use
 * dismiss() instead.
 */
/*...sclass DLLEXPORT lbAppClient:0:*/
class DLLEXPORT lbAppClient : public 
			lbObject, 
			lb_I_Requestable,
			lb_I_CallbackManager,
			lb_I_CallbackDispatcher,
			lb_I_CallbackTarget		
			{
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

/*...sImplement the interfaces:8:*/
	lbErrCodes getLastError(char* description, int len);
	lbErrCodes initialize();
	lbErrCodes request(const char* request, lb_Transfer_Data& result);
	lbErrCodes release();
	lbErrCodes addCallbackHandler(const char* handlername, lbMemberCallback callbackFn);
	lbErrCodes delCallbackHandler(const char* handlername);
	lbErrCodes dispatch(const char* request, lb_Transfer_Data& result);
/*...e*/


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

	// Dispatch table for registered member callbacks
	lbComponentDictionary *dispatchTable;
};
/*...e*/

#endif //LB_APPCS

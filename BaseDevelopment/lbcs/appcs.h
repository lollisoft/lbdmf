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
 * This is a base class for all servers
 */

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
/*...svirtual lbErrCodes _request\40\lb_Transfer_Data request\44\ lb_Transfer_Data \38\result\41\ \61\ 0\59\:8:*/
	/**
	 * _service is called by HandleRequest.
	 */
	virtual lbErrCodes _request(lb_Transfer_Data request, 
	                     lb_Transfer_Data &result) = 0;
/*...e*/
	
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

	// Connection is handled by 
	// User wishes to disconnect. This must be a request, because server
	// is in a thread handling requests in a loop till disconnect request
	// comes from user.
	
	lbErrCodes HandleDisconnect(	lb_Transfer_Data request,
					lb_Transfer_Data & result);

	// First request must be this. If not, no requests are handled.					
	lbErrCodes HandleConnect(	lb_Transfer_Data request,
					lb_Transfer_Data & result);
	
	int initTransfer(char* host_servicename);

	lbTransfer *transfer;	
	lbComponentDictionary *connections;	
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

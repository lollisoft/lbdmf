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

/**
 * This is a base class for all servers
 */

/*...sclass DLLEXPORT lbAppServer:0:*/
class DLLEXPORT lbAppServer {
public:
	lbAppServer();
	virtual ~lbAppServer();


/*...sFunctions needed to encapsulate the transfer class:8:*/
	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	int waitForRequest(lbTransfer* _clt, lb_Transfer_Data &request);
	
	int handleRequest(lb_Transfer_Data request, lb_Transfer_Data &result);
	                  
	int answerRequest(lbTransfer* _clt, lb_Transfer_Data result);
/*...e*/

	int run(); // called from main or thread

	// Called from HandleRequest()
/*...svirtual int _request\40\lb_Transfer_Data request\44\ lb_Transfer_Data \38\result\41\ \61\ 0\59\:8:*/
	/**
	 * _service is called by HandleRequest.
	 */
	virtual int _request(lb_Transfer_Data request, 
	                     lb_Transfer_Data &result) = 0;
/*...e*/
	
	// Called from run() and gives a lbTransfer instance
/*...svirtual int _connected\40\lbTransfer _clt\41\ \61\ 0\59\:8:*/
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
	virtual int _connected(lbTransfer* _clt) = 0; 
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

	int initTransfer(char* host_servicename);

	lbTransfer *transfer;		
};
/*...e*/

/**
 * Base class for all distributed objects. This class can't be instanciated
 * directly. Use lbAppBusClient instead. Also deletion is inhibed. Use
 * dismiss() instead.
 */
/*...sclass DLLEXPORT lbAppClient:0:*/
class DLLEXPORT lbAppClient {
private:
        lbAppClient();
        virtual ~lbAppClient();
        
        /**
         * Only lbAppBusClient should be able to create and delete instances
         * of client connections to a specific server
         */
        void* operator new(size_t size);
        void operator delete(void* ptr);
public:

/*
        void Connect(const char* application);
        void Disconnect();
*/
        lbObject* requestObject(const char* type, const char* name);

	/**
	 * Use this function to indicate, that this instance is no longer
	 * in your use.
	 */
	void dismiss();
	
	// lbAppBusClient must be able to create objects of this class
	friend class lbAppBusClient;
};
/*...e*/

#endif //LB_APPCS

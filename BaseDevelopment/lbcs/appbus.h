#ifndef LB_APPBUS
#define LB_APPBUS

#undef DLLEXPORT

/*...s\35\ifdef APPCS_DLL:0:*/
#ifdef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif
/*...e*/

/*...s\35\ifndef APPCS_DLL:0:*/
#ifndef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...slbAppBus:0:*/
class DLLEXPORT lbTransfer;

class DLLEXPORT lbAppBus {

public:
	lbAppBus();
	virtual ~lbAppBus();

	lbTransfer* getServerConnection(const char* server);

protected:

	char* bus_master_adr;
	u_short bus_master_port;
};
/*...e*/

/*...slbAppBusClient:0:*/

class DLLEXPORT lbAppBusClient : public lbAppBus {
public:
	lbAppBusClient();
	virtual ~lbAppBusClient();

	/**
	 * Make this client visible to the bus
	 */
	void AnounceClient();
	
	/**
	 * Remove the client from the bus
	 */
	void RemoveClient();
};
/*...e*/

/*...slbAppBusServer:0:*/
class lb_Transfer_Data;
class DLLEXPORT lbAppBusServer : public lbAppBus {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();

	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	int waitForRequest(lb_Transfer_Data & request);
	
	int handleRequest(char * servertype, 
	                  lb_Transfer_Data request, 
	                  lb_Transfer_Data & result);
	                  
	int answerRequest(lb_Transfer_Data result);

	/**
	 * Call this function in your main application or your thread.
	 */

	int run();

	/**
	 * Implement this for your request.
	 * It is called per request.
	 */
	 
	virtual int _request(char * servertype,
	                     lb_Transfer_Data request,
	                     lb_Transfer_Data & result) = 0; 

	/**
	 * Implement this for your service.
	 * It is called per run()
	 */
	virtual int _service() = 0;

	lbTransfer *transfer;		
};
/*...e*/
#endif

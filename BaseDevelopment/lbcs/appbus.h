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
class DLLEXPORT lbAppClient;

/**
 * This defines the properties for both AppBus classes (Client and Server)
 */
class DLLEXPORT lbAppBus {

public:
	lbAppBus();
	virtual ~lbAppBus();

protected:

	char* bus_master_adr;
	u_short bus_master_port;
};
/*...e*/

/*...slbAppBusClient:0:*/

class DLLEXPORT lbAppBusClient : public lbAppBus,
				 public lbAppClient {
public:

	/**
	 * Initialize a connection to the appbus server.
	 * Later this is a local dispatcher.
	 */
	lbAppBusClient();
	virtual ~lbAppBusClient();

	virtual void setType();
	virtual lbObject* clone() const;

	lbErrCodes registerCallbacks();

/*...sclient handling:8:*/
	/**
	 * The AppBusClient searches the server behind the scope. He is
	 * doing this by asking the AppBusServer about the server with
	 * that scope. Then the AppBusClient creates the desired client-
	 * connection object.
	 */
	lbAppClient* getClientInstance(char* scope);
	int release(lbAppClient*& cl) { delete cl; cl = NULL; return 1; }
/*...e*/

	int AnounceUser(char* user, char* passwd);
	int Echo(char* msg);

	int Connect();
	int Disconnect();

protected:
	/**
	 * Make this client visible to the bus
	 */
	int AnounceClient(); // Called by ctor
	
	/**
	 * Remove the client from the bus
	 */
	void RemoveClient(); // Called by dtor
	

	// user_info stores the username and password for reanouncement
	lb_Transfer_Data* user_info;
	// client_info stores the data for the host
	lb_Transfer_Data* client_info;
	
	/**
	 * This should be a singleton of a connection to the
	 * AppBus server.
	 */
	static lbTransfer* ABSConnection;
	static int instanceCount;
	static char* curruser;
	int connected;
};
/*...e*/

/*...slbAppBusServer:0:*/
class lb_Transfer_Data;
class DLLEXPORT lbAppBusServer :
				 public lbAppBus,
                                 public lbAppServer 
                                 {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();

	char* getServiceName();	

	lbErrCodes getLastError(char* description, int len);
	
	/**
	 * This function registers services implemented here.
	 * So all requests must have a service prefix in its
	 * lb_Transfer_Data container. If this is not happen,
	 * the request can't dispatched anywhere !
	 */
	lbErrCodes registerProtocols();
	
			
protected:

/*...sHandleEcho \40\a simple echo server \45\ just a test\41\:8:*/
	// Handle a appbus server specific request
	lbErrCodes HandleEcho(	lb_Transfer_Data request,
				lb_Transfer_Data & result);
/*...e*/
/*...sUserAnouncement \40\a user logs in\41\:8:*/
	// This let the client authenticate by user
	int UserAnouncement(lb_Transfer_Data request,
			    lb_Transfer_Data & result);
/*...e*/

	/**
	 * Further services should be registered by a function.
	 * This function has to be implemented by the class 
	 */

	lbComponentDictionary connections;	
};
/*...e*/
#endif

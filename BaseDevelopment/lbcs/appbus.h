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

class DLLEXPORT lbAppBusClient : public lbAppBus {
public:

	/**
	 * Initialize a connection to the appbus server.
	 * Later this is a local dispatcher.
	 */
	lbAppBusClient();
	virtual ~lbAppBusClient();

	/**
	 * The AppBusClient searches the server behind the scope. He is
	 * doing this by asking the AppBusServer about the server with
	 * that scope. Then the AppBusClient creates the desired client-
	 * connection object.
	 */
	lbAppClient* getClientInstance(char* scope);
	int release(lbAppClient*& cl) { delete cl; cl = NULL; return 1; }

	int AnounceUser(char* user, char* passwd);

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
	static char curruser[100];
	static int instanceCount;
};
/*...e*/

/*...slbAppBusServer:0:*/
class lb_Transfer_Data;
class DLLEXPORT lbAppBusServer : public lbAppBus,
                                 public lbAppServer {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();

	char* getServiceName();	

	int _connected(lbTransfer* _clt);
	
	
	int _request(	lb_Transfer_Data request,
			lb_Transfer_Data & result);
			
protected:
	// This let the client authenticate by user
	int UserAnouncement(lb_Transfer_Data request,
			    lb_Transfer_Data & result);
};
/*...e*/
#endif

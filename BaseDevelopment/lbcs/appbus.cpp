#define APPCS_DLL

#include <lbInclude.h>
#include <conio.h>

/*...slbAppBus\58\\58\lbAppBus\40\\41\:0:*/
lbAppBus::lbAppBus() {
/*
	bus_master_adr = strdup("127.0.0.1");
	bus_master_port = 5000;
*/
/*...sVERBOSE:0:*/
#ifdef APPBUS_VERBOSE
LOGENABLE("lbAppBus::lbAppBus()");
#endif
/*...e*/
}
/*...e*/
/*...slbAppBus\58\\58\\126\lbAppBus\40\\41\:0:*/
lbAppBus::~lbAppBus() {
//	if (!bus_master_adr) delete[] bus_master_adr;
}
/*...e*/

/*...sHelper functions:0:*/
/**
 * Helper functions
 */


 
char* sendConnect(lbTransfer & transfer) {
	lb_Transfer_Data result;
	lb_Transfer_Data request;
	char *temp;
	char msg[1000];

	transfer.gethostname(temp);
/*...sAPPBUS_VERBOSE:0:*/
#ifdef APPBUS_VERBOSE
	sprintf(msg, "sendConnect(lbTransfer & transfer): Send a connect request from host %s", temp);
	LOG(msg);
#endif	
/*...e*/
	request.add("Connect");
	request.add("Requesthost");
	request.add(temp);
	
	// More data may be user name, password...
	
/*...sAPPBUS_VERBOSE:0:*/
#ifdef APPBUS_VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) sending request");
#endif
/*...e*/
	transfer << request;
/*...sAPPBUS_VERBOSE:0:*/
#ifdef APPBUS_VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) recieving result");
#endif
/*...e*/
	transfer >> result;
/*...sAPPBUS_VERBOSE:0:*/
#ifdef APPBUS_VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) got result");
#endif
/*...e*/

#ifdef APPBUS_VERBOSE
	LOG("Sending connection packet failed!");
#endif
	return "error";
}

/*...e*/

/*...slbAppBusClient:0:*/

lbTransfer* lbAppBusClient::ABSConnection = NULL;
int lbAppBusClient::instanceCount = 0;
char* lbAppBusClient::curruser = NULL;

/*...slbAppBusClient\58\\58\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::lbAppBusClient() {
	// Set up a connection
cout << "Init lbAppBusClient" << endl;	
	if (ABSConnection == NULL) {
	/**
	 * Initialize the tcp connection...
	 */
	
		ABSConnection = new lbTransfer;
		ABSConnection->init("//anakin/busmaster");
	}

	if (instanceCount == 0) {
		cout << "Call Connect()" << endl;
		Connect();
		
		//AnounceClient();
		curruser = NULL;
	}
cout << "Initialized" << endl;	
	instanceCount++;
}
/*...e*/

/**
 * Destroys also the client server
 */
/*...slbAppBusClient\58\\58\\126\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::~lbAppBusClient() {
cout << "Cleanup Appbus client" << endl;	
	if (instanceCount == 0) {
LOG("lbAppBusClient::~lbAppBusClient() Delete ABSConnection");
		// Disconnect from AppBusServer
		delete ABSConnection;
		ABSConnection = NULL;
	}

	instanceCount--;
}
/*...e*/
/*...slbAppBusClient\58\\58\setType\40\\41\:0:*/
void lbAppBusClient::setType() {
	OTyp = LB_APPBUSCLIENT;
}
/*...e*/
/*...slbAppBusClient\58\\58\clone\40\\41\:0:*/
lbObject* lbAppBusClient::clone() const {
	lbAppBusClient* cloned = new lbAppBusClient();
	
	return (lbObject*) cloned;
}
/*...e*/
/*...slbAppBusClient\58\\58\getClientInstance\40\char\42\ scope\41\:0:*/
lbAppClient* lbAppBusClient::getClientInstance(char* scope) {
	/**
	 * Create a client transfer instance to a known server by appbus.
	 */

	lbAppClient *cl = NULL;
	
	
	lb_Transfer_Data request;
	lb_Transfer_Data result;
	
	request.add("getServer");
	request.add(scope);
	
	*ABSConnection << request;
	*ABSConnection >> result;
	
	/**
	 * Create the client with the needed data here.
	 */

	if (cl == NULL) LOG("lbAppBusClient::getClientInstance(...) returns a NULL pointer !!!");
	return cl;
}
/*...e*/

lbErrCodes lbAppBusClient::registerCallbacks() {
	return ERR_NONE;
}

/**
 * Make the client known by the busmaster
 */
/*...slbAppBusClient\58\\58\AnounceClient\40\\41\:0:*/
int lbAppBusClient::AnounceClient() {
	char* answer;
	char buf[100] = "";
	lb_Transfer_Data result;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
LOG("lbAppBusClient::AnounceClient() called");
#endif
/*...e*/
	lb_Transfer_Data client;

/*...ssetup protokol:0:*/
		client.add("AnounceClient");
		client.add("Host");
		client.add("anakin");
		client.add("PID");
		client.add(lbGetCurrentProcessId());
		client.add("TID");
		client.add(lbGetCurrentThreadId());
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
		while(client.hasMorePackets()) {
			pLB_TRANSFER_DATA data = client.getNextPacket();
			sprintf(buf, "Datapaket's address is %p", (void*) data);
		}
#endif
/*...e*/
/*...e*/
//cout << "lbAppBusClient::AnounceClient() sends " << client.getPacketCount() << " packets" << endl;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() Sending the data");        
#endif
/*...e*/
        *ABSConnection << client;
        //cout << "AppBus Client now waits for answer..." << endl;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() ready to get answer");        
#endif
/*...e*/
        *ABSConnection >> result;
	// Handle the request
	int count = result.getPacketCount();
        //cout << "Returned data (packet count: " << count << ") is:" << endl;        

	result.resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result.getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result.get(buffer);

				printf("Char value = %s\n", buffer); 
				
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				
				break;
		}
			
		result.incrementPosition();
	}
                
        return 1;
}
/*...e*/

/*...sint lbAppBusClient\58\\58\AnounceUser\40\char\42\ user\44\ char\42\ passwd\41\:0:*/
int lbAppBusClient::AnounceUser(char* user, char* passwd) {
	lb_Transfer_Data result;
	char *temp;
	char msg[100];

/*...sprepare proto:8:*/
	if (curruser == NULL) {
		LOG("First call to Anounce user");
		//cout << "First call to Anounce user" << endl;
		curruser = strdup(user);
		ABSConnection->gethostname(temp);
		user_info = new lb_Transfer_Data();
		
	        user_info->add("AnounceUser");
	        user_info->add("User");
	        user_info->add(user);
	        user_info->add("Passwd");
	        user_info->add(passwd);
	} else {
		// Lookup user and use its user_info instance
		LOG("Reuse Anounced user");
	}
/*...e*/
	
	*ABSConnection << *user_info;
	*ABSConnection >> result;
	
	return 1;	
}
/*...e*/
/*...sint lbAppBusClient\58\\58\Echo\40\char\42\ msg\41\:0:*/
int lbAppBusClient::Echo(char* msg) {
	lb_Transfer_Data result;
	char *temp;

	lb_Transfer_Data data;
	
	data.add("Echo");
	data.add(msg);

	*ABSConnection << data;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    LOG("Error in sending echo data");
	*ABSConnection >> result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    LOG("Error in recieving echo answer");
	
/*...shandle result:8:*/
	// Handle the request
	int count = result.getPacketCount();
        //cout << "Returned data (packet count: " << count << ") is:" << endl;        

	result.resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result.getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result.get(buffer);
				//printf("Char value = %s\n", buffer); 
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				break;
		}
		result.incrementPosition();
	}
/*...e*/

	return 1;	
}
/*...e*/

/**
 * getClientList() returns a list of clients known by the server.
 *
 * A client object from the list is an instance of lbRemoteClient .
 */

/*...slbAppBusClient\58\\58\Connect:0:*/
int lbAppBusClient::Connect() {
	char* answer;
	char buf[100] = "";
	lb_Transfer_Data result;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
LOG("lbAppBusClient::AnounceClient() called");
#endif
/*...e*/
	lb_Transfer_Data client;

/*...ssetup protokol:0:*/
		client.add("Connect");
		client.add("Host");
		client.add("anakin");
		client.add("Pid");
		client.add(lbGetCurrentProcessId());
		client.add("Tid");
		client.add(lbGetCurrentThreadId());
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
		while(client.hasMorePackets()) {
			pLB_TRANSFER_DATA data = client.getNextPacket();
			sprintf(buf, "Datapaket's address is %p", (void*) data);
		}
#endif
/*...e*/
/*...e*/
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() Sending the data");        
#endif
/*...e*/
        *ABSConnection << client;
        //cout << "AppBus Client now waits for answer..." << endl;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() ready to get answer");        
#endif
/*...e*/
        *ABSConnection >> result;

	// Handle the request
	int count = result.getPacketCount();
        //cout << "Returned data (packet count: " << count << ") is:" << endl;        

	result.resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result.getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result.get(buffer);

				//printf("Char value = %s\n", buffer); 
				
				if (strcmp(buffer, "Accept") == 0) {
					//cout << "Connected successfull" << endl;
					connected = 1;
					return 1;
				} else {
					//cout << "Connection failed!" << endl;
					connected = 0;
					return 0;
				}
				
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				
				break;
		}
			
		result.incrementPosition();
	}
                
        return 1;
}
/*...e*/
/*...slbAppBusClient\58\\58\Disconnect:0:*/
int lbAppBusClient::Disconnect() {
	char* answer;
	char buf[100] = "";
	lb_Transfer_Data result;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
LOG("lbAppBusClient::AnounceClient() called");
#endif
/*...e*/
	lb_Transfer_Data client;

/*...ssetup protokol:0:*/
		client.add("Disconnect");
		client.add("Host");
		client.add("anakin");
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
		while(client.hasMorePackets()) {
			pLB_TRANSFER_DATA data = client.getNextPacket();
			sprintf(buf, "Datapaket's address is %p", (void*) data);
		}
#endif
/*...e*/
/*...e*/
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() Sending the data");        
#endif
/*...e*/
        *ABSConnection << client;
        //cout << "AppBus Client now waits for answer..." << endl;
/*...sAPPBUS_CLT_VERBOSE:0:*/
#ifdef APPBUS_CLT_VERBOSE
	LOG("lbAppBusClient::AnounceClient() ready to get answer");        
#endif
/*...e*/
        *ABSConnection >> result;

	// Handle the request
	int count = result.getPacketCount();
        //cout << "Returned data (packet count: " << count << ") is:" << endl;        

	result.resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result.getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result.get(buffer);

				//printf("Char value = %s\n", buffer); 
				
				if (strcmp(buffer, "Succeed") == 0) {
					//cout << "Disconnected successfull" << endl;
					connected = 0;
					return 1;
				} else {
					//cout << "Disconnection failed!" << endl;
					return 0;
				}
				
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				
				break;
		}
			
		result.incrementPosition();
	}
                
        return 1;
}
/*...e*/
/*...e*/

/*...slbAppBusServer:0:*/
/*...slbAppBusServer\58\\58\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::lbAppBusServer() {
	//cout << "lbAppBusServer::lbAppBusServer() called" << endl;
}
/*...e*/

/*...slbAppBusServer\58\\58\\126\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::~lbAppBusServer() {
}
/*...e*/

/*...slbAppBusServer\58\\58\getServiceName\40\\41\:0:*/
char* lbAppBusServer::getServiceName() {
	return "localhost/busmaster";
}
/*...e*/

#ifdef bla
/*...slbAppBusServer\58\\58\_request\40\lb_Transfer_Data request\44\ lb_Transfer_Data \38\ result\41\:0:*/
lbErrCodes lbAppBusServer::_request(lb_Transfer_Data request, lb_Transfer_Data & result) {
	lbErrCodes rc = ERR_NONE;
	// Do what you want with this request
/*...sAPPBUS_SVR_VERBOSE:0:*/
#ifdef APPBUS_SVR_VERBOSE
LOGENABLE("lbAppBusServer::_request()");
LOG("lbAppBusServer::_request(): Handle a request");
#endif
/*...e*/
	// Handle the request
	int count = request.getPacketCount();

	char buf[100];
/*...sAPPBUS_SVR_VERBOSE:0:*/
#ifdef APPBUS_SVR_VERBOSE
	sprintf(buf, "lbAppBusServer::_request(): Packetcount = %d", count);
	printf("%s\n", buf);
	LOG(buf);
#endif		
/*...e*/

	request.resetPositionCount();
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		request.getPacketType(type);

		switch (type) {
/*...sLB_CHAR \45\\62\ dispatch to known commands:24:*/
			case LB_CHAR:
				// This does not increment the position count
				request.get(buffer);
				
				if (strcmp(buffer, "Disconnect") == 0)
					return HandleDisconnect(request, result);
				else
				if (strcmp(buffer, "Echo") == 0)
					return HandleEcho(request, result);
				else 
				{
				    LOG("LB_CHAR -> dispatch: Can handle 'Disconnect' yet");
				    return ERR_APPBUS_DISPATCH;
				}
				break;
				
/*...e*/
			default:
/*...sError:24:*/
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				
				result.add("Deny request");
				result.add("Description");
				result.add("Can't dispatch this type of request");
				
				return ERR_APPBUS_DISPATCH_HAEDER;
				
				break;
/*...e*/
		}
	}
	//cout << "GlobalAppServer::_request(): Request handled" << endl;
/*...sAPPBUS_SVR_VERBOSE:0:*/
//#ifdef APPBUS_SVR_VERBOSE
	LOG("GlobalAppServer::_request(): Request handled");
//#endif
/*...e*/
	return rc;                              
}
/*...e*/
/*...slbAppBusServer\58\\58\_connected\40\lbTransfer\42\ _clt\41\:0:*/
#ifdef bla
lbErrCodes lbAppBusServer::_connected(lbTransfer* _clt) {

	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rcout = ERR_NONE;
	lbErrCodes rc_handler = ERR_NONE; 
	
	// This objects must be clean for each request!

	lb_Transfer_Data request(1);
	lb_Transfer_Data result(1);	
	
/*...sHandle connection:8:*/

	do {
	  request.deleteAll();
	  result.deleteAll();
	
	  if ((rcin = waitForRequest(_clt, request)) != ERR_NONE) {
	    LOG("waitForRequest(_clt, request) failed");
	  } else {
            if ((rc_handler = dispatch(request, result)) != ERR_NONE) {
			LOG("handleRequest(request, result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lbTransfer* _clt) Request handled, send answer");
#endif
/*...e*/
		if ((rcout = answerRequest(_clt, result)) != ERR_NONE) {
			LOG("answerRequest(_clt, result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lbTransfer* _clt) Answer sent");
#endif
/*...e*/
	}

	/**
	 * Request is set correctly, because loop is entered at least once.
	 * So it is possible to handle a disconnect request here.
	 */
	} while ((isConnected(request) == 1) // Must disconnect before closing transfer 
		&& (rcin == ERR_NONE) // Recieving failed
		&& (rcout == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rcout != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
/*...e*/

	return rc;
}
#endif
/*...e*/
#endif

lbErrCodes lbAppBusServer::getLastError(char* description, int len) {
	strncpy(description, "", len);

	return ERR_NONE;
}
/*...slbAppBusServer\58\\58\registerProtocols\40\\41\:0:*/
lbErrCodes lbAppBusServer::registerProtocols() {


        addProtocolHandler("Echo", 
                          (lbProtocolCallback) lbAppBusServer::HandleEcho);
        
        
	return ERR_NONE;
}
/*...e*/


// Implemented 
/*...slbAppBusServer\58\\58\HandleEcho\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppBusServer::HandleEcho(lb_Transfer_Data request,
          			      lb_Transfer_Data & result) {
	LB_PACKET_TYPE type;
	char *echostring = NULL;
	unsigned long pid = 0;
	unsigned long tid = 0;
	char buf[100];

/*...sEcho proto:0:*/
/*
	add("Echo")
	add("Your echo message");
*/
/*...e*/

	if (requestString(request, "Echo", echostring) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: Echo parameter not sent",
				   "lbAppServer::HandleEcho(...)");
		cout << "Fehler ..." << endl;
		return ERR_APPBUS_ECHO;
	}


	result.add("Echoed");
	result.add(echostring);
cout << "Echo this: " << echostring << endl;
	return ERR_NONE;
}
/*...e*/
	
/*...e*/

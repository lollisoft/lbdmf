#define APPCS_DLL

#include <lbInclude.h>

/*...slbAppBus\58\\58\lbAppBus\40\\41\:0:*/
lbAppBus::lbAppBus() {
/*
	bus_master_adr = strdup("127.0.0.1");
	bus_master_port = 5000;
*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
	char msg[100];

	transfer.gethostname(temp);

	sprintf(msg, "sendConnect(lbTransfer & transfer): Send a connect request from host %s", temp);
	LOG(msg);
	
	request.add("Connect");
	request.add("Requesthost");
	request.add(temp);
	
	// More data may be user name, password...
	
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) sending request");
#endif
/*...e*/
	transfer << request;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) recieving result");
#endif
/*...e*/
	transfer >> result;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("AppBus: sendConnect(lbTransfer & transfer) got result");
#endif
/*...e*/


	LOG("Sending connection packet failed!");
	return "error";
}

/*...e*/


/*...slbAppBusClient:0:*/
lbTransfer* lbAppBusClient::ABSConnection = NULL;
char lbAppBusClient::curruser[] = "";
int lbAppBusClient::instanceCount = 0;

/*...slbAppBusClient\58\\58\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::lbAppBusClient() {
	// Set up a connection
	
	if (ABSConnection == NULL) {
		ABSConnection = new lbTransfer;
		ABSConnection->init("//anakin/busmaster");
	}
	
	instanceCount++;
}
/*...e*/

/**
 * Destroys also the client server
 */
/*...slbAppBusClient\58\\58\\126\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::~lbAppBusClient() {
	instanceCount--;
	
	if (instanceCount == 0) {
		// Disconnect from AppBusServer
		delete ABSConnection;
		ABSConnection = NULL;
	}
}
/*...e*/

lbAppClient* lbAppBusClient::getClientInstance(char* scope) {
	return new lbAppClient();
}

/**
 * Make the client known by the busmaster
 */
/*...slbAppBusClient\58\\58\AnounceClient\40\\41\:0:*/
int lbAppBusClient::AnounceClient() {
	char* answer;
	lb_Transfer_Data result;


	client_info = new lb_Transfer_Data();
/*
	client_info->add("AnounceClient");
	client_info->add("Host");
	client_info->add(hostname);
	client_info->add("PID");
	client_info->add(pid);
	client_info->add("TID");
	client_info->add(tid);
*/
        *ABSConnection << *client_info;
        
        *ABSConnection >> result;
                
        return 1;
}
/*...e*/

/*...sint lbAppBusClient\58\\58\AnounceUser\40\char\42\ user\44\ char\42\ passwd\41\:0:*/
int lbAppBusClient::AnounceUser(char* user, char* passwd) {
	lb_Transfer_Data result;
	char *temp;
	char msg[100];


	if (strcmp(user, curruser) == 0) {
		// data still be reusable
	} else {
		strcpy(curruser, user);
		ABSConnection->gethostname(temp);
		user_info = new lb_Transfer_Data();
		
	        user_info->add("AnounceUser");
	        user_info->add("User");
	        user_info->add(user);
	        user_info->add("Passwd");
	        user_info->add(passwd);
	}

	*ABSConnection << *user_info;

	*ABSConnection >> result;
	
	return 1;	
}
/*...e*/

/**
 * getClientList() returns a list of clients known by the server.
 *
 * A client object from the list is an instance of lbRemoteClient .
 */
/*...slbAppBusClient\58\\58\getClientList\40\\41\:0:*/
/*...e*/
/*...e*/

/*...slbAppBusServer:0:*/
/*...slbAppBusServer\58\\58\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::lbAppBusServer() {
	cout << "lbAppBusServer::lbAppBusServer() called" << endl;
}
/*...e*/

/*...slbAppBusServer\58\\58\\126\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::~lbAppBusServer() {
}
/*...e*/

/*...sbla:0:*/
#ifdef bla
/*...slbAppBusServer\58\\58\waitForRequest\40\lb_Transfer_Data \38\ request\41\:0:*/
int lbAppBusServer::waitForRequest(lb_Transfer_Data & request) 
{
	*transfer >> request;
	char buf[100];
	
	sprintf(buf, "lbAppBusServer::waitForRequest(): Got a request with %d packets", request.getPacketCount());
	LOG(buf);
	
	return 0;
}
/*...e*/
	
/*...slbAppBusServer\58\\58\handleRequest\40\\46\\46\\46\\41\:0:*/
int lbAppBusServer::handleRequest(char * servertype, 
                  lb_Transfer_Data request, 
                  lb_Transfer_Data & result)
{// Dispatching were possible here with servertype...
	return _request(servertype, request, result);
}
/*...e*/
	                  
/*...slbAppBusServer\58\\58\answerRequest\40\lb_Transfer_Data result\41\:0:*/
int lbAppBusServer::answerRequest(lb_Transfer_Data result) 
{
	*transfer << result;
	return 0;
}
/*...e*/
#endif
/*...e*/

/*...slbAppBusServer\58\\58\getServiceName\40\\41\:0:*/
char* lbAppBusServer::getServiceName() {
	return "localhost/busmaster";
}
/*...e*/

/*...slbAppBusServer\58\\58\_request\40\lb_Transfer_Data request\44\ lb_Transfer_Data \38\ result\41\:0:*/
int lbAppBusServer::_request(lb_Transfer_Data request, lb_Transfer_Data & result) {
	// Do what you want with this request
LOGENABLE("lbAppBusServer::_request()");
LOG("lbAppBusServer::_request(): Handle a request");
	// Handle the request
	int count = request.getPacketCount();

	char buf[100];
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
			case LB_CHAR:
				request.get(buffer);

/*...sVERBOSE:32:*/
				#ifdef VERBOSE
				printf("Char value = %s\n", buffer); 
				sprintf(msg, "Char value = %s", buffer); 
				LOG(msg);
				#endif
/*...e*/
/*...sbla:32:*/
#ifdef bla				
				if (strcmp(buffer, "login") == 0) {
					int res = login(request, result);
					
					if (res == 1) 
						isLoggedIn = TRUE;
					else
						isLoggedIn = FALSE;
						
					return res;
				}
				
				if (strcmp(buffer, "logout") == 0) {
					int res = logout(request, result);
					
					isLoggedIn = FALSE;
					
					return res;
				}

				if (isLoggedIn == TRUE) 
					return handleAuthRequest(request, result);
#endif
/*...e*/
				
				break;
				
			default:
				printf("Unknown packet type!\n"); 
				LOG("Unknown packet type!"); 
				break;
		}
			
		request.incrementPosition();
	}
	LOG("GlobalAppServer::_request(): Request handled");
	return 1;                              
	return 0;
}
/*...e*/
/*...slbAppBusServer\58\\58\_connected\40\lbTransfer\42\ _clt\41\:0:*/
int lbAppBusServer::_connected(lbTransfer* _clt) {
	lb_Transfer_Data request;
	lb_Transfer_Data result;	

	waitForRequest(_clt, request);

	handleRequest(request, result);

	answerRequest(_clt, result);
	
	return 0;
}
/*...e*/
/*...e*/

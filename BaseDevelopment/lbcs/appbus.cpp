#define APPCS_DLL

#include <lbInclude.h>

/*...slbAppBus\58\\58\lbAppBus\40\\41\:0:*/
lbAppBus::lbAppBus() {
/*
	bus_master_adr = strdup("127.0.0.1");
	bus_master_port = 5000;
*/
LOGENABLE("lbAppBus::lbAppBus()");

}
/*...e*/
/*...slbAppBus\58\\58\\126\lbAppBus\40\\41\:0:*/
lbAppBus::~lbAppBus() {
//	if (!bus_master_adr) delete[] bus_master_adr;
}
/*...e*/
/*...slbAppBus\58\\58\getServerConnection\40\const char\42\ server\41\:0:*/
lbTransfer* lbAppBus::getServerConnection(const char* server) {
	return NULL;
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


/**
 * Creates also a client server to be able to implement callback
 * and so on.
 */
/*...slbAppBusClient\58\\58\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::lbAppBusClient() {
}
/*...e*/

/**
 * Destroys also the client server
 */
/*...slbAppBusClient\58\\58\\126\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::~lbAppBusClient() {
}
/*...e*/

/**
 * Make the client known by the busmaster
 */
/*...slbAppBusClient\58\\58\AnounceClient\40\\41\:0:*/
void lbAppBusClient::AnounceClient() {
	lbTransfer transfer;
	char* answer;

	/**
	 * Connect to the busmaster port.
	 */
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbAppBusClient::AnounceClient(): call transfer.init(\"//anakin/busmaster\");");
#endif
/*...e*/
	transfer.init("//anakin/busmaster");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbAppBusClient::AnounceClient(): sendConnect(transfer)");
#endif
/*...e*/
	answer = strdup(sendConnect(transfer));
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbAppBusClient::AnounceClient(): sendConnect(transfer) done");
#endif
/*...e*/
	if (strcmp(answer, "error") != 0) {
		
	} else {
		// Log error
		LOG("lbAppBus: Error while trying to connect to the server");
	}
}
/*...e*/

/**
 * getClientList() returns a list of clients known by the server.
 *
 * A client object from the list is an instance of lbRemoteClient .
 */
/*...slbAppBusClient\58\\58\getClientList\40\\41\:0:*/
/*...e*/

/*...slbAppBusServer:0:*/
/*...slbAppBusServer\58\\58\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::lbAppBusServer() {
}
/*...e*/

/*...slbAppBusServer\58\\58\\126\lbAppBusServer\40\\41\:0:*/
lbAppBusServer::~lbAppBusServer() {
}
/*...e*/

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

/*...slbAppBusServer\58\\58\run\40\\41\:0:*/
int lbAppBusServer::run() { 
	LOG("lbAppServer::run() called");

        LOG("lbAppServer::run(): Initialize lbTransfer object");
        transfer = new lbTransfer();
        transfer->init("localhost/busmaster");
        LOG("lbAppServer::run(): Initialized");

	while (1) {
		transfer->accept();

		if(_service() == 0) return 0; 
	}
}
/*...e*/
/*...e*/

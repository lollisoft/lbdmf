#define APPCS_DLL

#include <lbInclude.h>

/*...slbAppBus\58\\58\lbAppBus\40\\41\:0:*/
lbAppBus::lbAppBus() {
/*
	bus_master_adr = strdup("127.0.0.1");
	bus_master_port = 5000;
*/
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

	LOG("sendConnect(lbTransfer & transfer): Send a connect request");

	request.add("Connect");

	transfer << request;
	transfer >> result;

	LOG("Sending connection packet failed!");
	return "error";
}
/*...e*/

/*...slbAppBusClient\58\\58\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::lbAppBusClient() {
}
/*...e*/
/*...slbAppBusClient\58\\58\\126\lbAppBusClient\40\\41\:0:*/
lbAppBusClient::~lbAppBusClient() {
}
/*...e*/
/*...slbAppBusClient\58\\58\AnounceClient\40\\41\:0:*/
void lbAppBusClient::AnounceClient() {
	lbTransfer transfer;
	char* answer;

	/**
	 * Connect to the busmaster port.
	 */
	
	transfer.init("//anakin/busmaster");
LOG("lbAppBusClient::AnounceClient(): sendConnect(transfer)");
	answer = strdup(sendConnect(transfer));
LOG("lbAppBusClient::AnounceClient(): sendConnect(transfer) done");
	if (strcmp(answer, "error") != 0) {
		
	} else {
		// Log error
		LOG("lbAppBus: Error while trying to connect to the server");
	}
}
/*...e*/


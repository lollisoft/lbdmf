#define APPCS_DLL

#include <string.h>
#include <lbInclude.h>

/*...sRemoteAppReq:0:*/
/*...sRemoteAppReq\58\\58\RemoteAppReq\40\\41\:0:*/
RemoteAppReq::RemoteAppReq() {
	issue = NULL;
	parameter = NULL;
}
/*...e*/
/*...sRemoteAppReq\58\\58\\126\RemoteAppReq\40\\41\:0:*/
RemoteAppReq::~RemoteAppReq() {
}
/*...e*/
/*...sRemoteAppReq\58\\58\setIssue\40\char\42\ what\41\:0:*/
void RemoteAppReq::setIssue(char* what) {
	issue = strdup(what);
}
/*...e*/
/*...sRemoteAppReq\58\\58\setValue\40\const char\42\ param\41\:0:*/
void RemoteAppReq::setValue(const char* param) {
	parameter = strdup(param);
}
/*...e*/
/*...e*/
/*...sRemoteAppRes:0:*/
/*...sRemoteAppRes\58\\58\RemoteAppRes\40\\41\:0:*/
RemoteAppRes::RemoteAppRes() {
//	LOGVERBOSE("RemoteAppRes::RemoteAppRes() called");
}
/*...e*/
/*...sRemoteAppRes\58\\58\\126\RemoteAppRes\40\\41\:0:*/
RemoteAppRes::~RemoteAppRes() {
//	LOGVERBOSE("RemoteAppRes::~RemoteAppRes() called");
}
/*...e*/
/*...sRemoteAppRes\58\\58\isError\40\\41\:0:*/
int RemoteAppRes::isError() {
	return 0;
}
/*...e*/
/*...sRemoteAppRes\58\\58\reportError\40\\41\:0:*/
void RemoteAppRes::reportError() {
	LOG("There is an error result arrived!");
}
/*...e*/
/*...sRemoteAppRes\58\\58\getResultName\40\\41\:0:*/
char* RemoteAppRes::getResultName() {
	return "A result";
}
/*...e*/
/*...sRemoteAppRes\58\\58\getEntries\40\\41\:0:*/
int RemoteAppRes::getEntries() {
	return 3;
}
/*...e*/
/*...sRemoteAppRes\58\\58\getEntryName\40\int i\41\:0:*/
char* RemoteAppRes::getEntryName(int i) {
// Moved to server later:
	switch (i) {
		case 1:
			// Mainmenu File
			return "&File";
		case 2:
			// Mainmenu Edit
			return "&Edit";
		case 3:
			// Mainmenu Help
			return "&Help";
		default:
			break;
	}
	LOG("RemoteAppRes::getEntryName(int) no name found");
	return "No name found";
}
/*...e*/
/*...e*/

/*...slbAppServer:0:*/
/*...slbAppServer\58\\58\lbAppServer\40\\41\:0:*/
lbAppServer::lbAppServer() {
	LOGENABLE("lbAppServer::lbAppServer()");
/*
	LOG("lbAppServer::lbAppServer(): Initialize lbTransfer object");
	transfer = new lbTransfer();
	transfer->init("localhost/busmaster");
	LOG("lbAppServer::lbAppServer(): Initialized");
*/
}
/*...e*/
/*...slbAppServer\58\\58\\126\lbAppServer\40\\41\:0:*/
lbAppServer::~lbAppServer() {
}
/*...e*/
/*...slbAppServer\58\\58\send \40\const RemoteAppRes\38\ res\41\:0:*/
// This sends a result to the client
void lbAppServer::send (const RemoteAppRes& res) {
}
/*...e*/
/*...slbAppServer\58\\58\recv \40\RemoteAppReq\38\ req\41\:0:*/
// Wait for a request
void lbAppServer::recv (RemoteAppReq& req) {
LOGENABLE("lbAppServer::recv (RemoteAppReq& req)");
	lb_Transfer_Data transferItem;
LOG("lbAppServer::recv (RemoteAppReq& req): Get any data");	
	if (transfer != NULL) {
	LOG("lbAppServer::recv (RemoteAppReq& req): Transfer is not null - do work");

		*transfer >> transferItem;

	LOG("lbAppServer::recv (RemoteAppReq& req): Transfer is not null - done work");
	}
	else LOG("lbAppServer::recv (RemoteAppReq& req): transfer is null");
LOG("lbAppServer::recv (RemoteAppReq& req): Got any data");	
}
/*...e*/
/*...slbAppServer\58\\58\run\40\\41\:0:*/
int lbAppServer::run() { 
	LOG("lbAppServer::run() called");

        LOG("lbAppServer::run(): Initialize lbTransfer object");
        transfer = new lbTransfer();
        transfer->init("localhost/busmaster");
        LOG("lbAppServer::run(): Initialized");

	return _service(); 
};
/*...e*/


// Threads, that should be started by the application

/*...slbAppServer\58\\58\ConnectThread\40\\41\ Waits for connections and then starts Servive:0:*/
/*...e*/
/*...slbAppServer\58\\58\ServiceThread\40\\41\:0:*/
/*...e*/


/*...e*/
/*...slbAppClient:0:*/
/*...slbAppClient\58\\58\lbAppClient\40\\41\:0:*/
lbAppClient::lbAppClient() {
	LOGENABLE("lbAppClient::lbAppClient()");
}
/*...e*/
/*...slbAppClient\58\\58\\126\lbAppClient\40\\41\:0:*/
lbAppClient::~lbAppClient() {
}
/*...e*/
/*...slbAppClient\58\\58\Connect\40\const char\42\ application\41\:0:*/
void lbAppClient::Connect(const char* application) {
/*...sVars:8:*/
	lb_Transfer_Data request;
	lb_Transfer_Data reply;
	lbAppBusClient bus;
	lbAppServer* app_server = NULL;
	lbTransfer* transferClient = NULL;
/*...e*/
/*...sDoc:8:*/
	/**
	 * The bus is the global software interconnection facility.
	 * A server can connect it self to the bus with AnounceServer().
	 * The client then anounces it self to get a handle like a house number.
	 * With this handle all further communication will be invoked.
	 *
	 * The Target for any anouncements must be configured by a configuration file.
	 */
/*...e*/

/*...sVERBOSE:8:*/
#ifdef VERBOSE
LOG("lbAppClient::Connect(const char* application): Announce me as client");
#endif
/*...e*/

	bus.AnounceClient(); // Announce me as a new application on the bus
	
/*...sDoc:8:*/
	/**
	 * Get an application object, that should be on the bus.
	 * Here we first need the application server, from whom we get all
	 * further information.
	 *
	 * A lbTransfer object is returned to communicate directly
	 * with this server. The app bus is no more used here.
	 */
/*...e*/

	transferClient = bus.getServerConnection("AppServer");

	request.add("Connect");
	request.add(application);

	*transferClient << request; // No explicit send is needed:
	*transferClient >> reply;   // It is done here, because status is "have a request" -> send it and get reply
/*...sbla:8:*/
/*
	if (reply.isError()) {
		reply.reportError();
	}
*/
/*...e*/
/*...sDoc:8:*/
	/**
	 * Now the reply will contain a handle for the connection. Use this handle in the connected
	 * state.
	 */
/*...e*/
}
/*...e*/
/*...slbAppClient\58\\58\Disconnect\40\\41\:0:*/
void lbAppClient::Disconnect() {
}
/*...e*/
/*...slbAppClient\58\\58\requestObject\40\const char\42\ name\41\:0:*/
RemoteAppRes& lbAppClient::requestObject(const char* name) {
	/**
	 * The result depends on the name given by the parameter.
	 * Simply, this is only a forwarding of the request (to anywhere).
	 */
	
	RemoteAppRes *res = new RemoteAppRes();
	return *res;
}
/*...e*/
/*...e*/

/*...sbla:0:*/
#ifdef bla
RemoteAppRes& lbAppClient::subObject(const RemoteAppRes& res, const char* name) {
	/**
	 * Get the base request name and send it as a base request to the server
	 */
	PushBaseReq(res.getName());
	//RemoteAppRes *r = get
	PopBaseReq(res.getName());
	//return requestObject(name);
}
#endif
/*...e*/


#define APPCS_DLL

#include <string.h>
#include <lbInclude.h>

/*...sclass lbAppServerThread:0:*/
class lbAppServerThread : public lbThread {
public:
	lbAppServerThread(lbTransfer* _clt, lbAppServer* _server);
	
	virtual ~lbAppServerThread();
	
protected:
	void* Entry();
	lbTransfer* clt;
	lbAppServer* server;
};

/*...svoid\42\ lbAppServerThread\58\\58\Entry\40\\41\:0:*/
void* lbAppServerThread::Entry() {

	server->_connected(clt);
	
	return NULL;
}
/*...e*/

/*...slbAppServerThread\58\\58\lbAppServerThread\40\lbTransfer\42\ _clt\44\ lbAppServer\42\ _server\41\:0:*/
lbAppServerThread::lbAppServerThread(lbTransfer* _clt, lbAppServer* _server) {
	clt = _clt;
	server = _server;
}
/*...e*/

/*...slbAppServerThread\58\\58\\126\lbAppServerThread\40\\41\:0:*/
lbAppServerThread::~lbAppServerThread() {
}
/*...e*/

/*...e*/


/*...slbAppServer:0:*/
/*...slbAppServer\58\\58\lbAppServer\40\\41\:0:*/
lbAppServer::lbAppServer() {
	LOGENABLE("lbAppServer::lbAppServer()");
/*...sdead code:0:*/
/*
	LOG("lbAppServer::lbAppServer(): Initialize lbTransfer object");
	transfer = new lbTransfer();
	transfer->init("localhost/busmaster");
	LOG("lbAppServer::lbAppServer(): Initialized");
*/
/*...e*/
}
/*...e*/
/*...slbAppServer\58\\58\\126\lbAppServer\40\\41\:0:*/
lbAppServer::~lbAppServer() {
}
/*...e*/


/*...slbAppServer\58\\58\run\40\\41\:0:*/
int lbAppServer::run() { 
	cout << "lbAppServer::run() called" << endl;
	LOG("lbAppServer::run() called");

        LOG("lbAppServer::run(): Initialize lbTransfer object");
	if (initTransfer(getServiceName()) == 0) {
		LOG("lbAppServer::run(): Error, failed to initialize transfer");
		return 0;
	}
        LOG("lbAppServer::run(): Initialized");
        cout << "initTransfer(getServiceName()); called" << endl;

	// Here should be called the function listen() (Not in initTransfer())

	// Here should be started a thread, that do this
	while (1) {
		/**
		 * Like socket accept returns a client socket, here I have to
		 * get a client transfer object. A client transfer object can
		 * only created by the accept method, because the state at this
		 * point.
		 */
		lbTransfer* clt;
		cout << "Wait for a connection" << endl;
		if (transfer->accept(clt) == 0) 
		{
			LOG("lbAppServer::run() error while accepting on a socket");
			return 0;
		}
		cout << "Got a connection" << endl;
		/**
		 * here I can begin a thread with is calling _connected.
		 * Like the documentation from Win32 System Services p366.
		 * But the new client socket must be associated to that 
		 * thread, because
		 */
		
		lbAppServerThread* thread = new lbAppServerThread(clt, this);
		cout << "Create a thread for the connection" << endl;
		thread->create();
		cout << "Run the thread" << endl;
		thread->run();
	}
}
/*...e*/

/*...slbAppServer\58\\58\waitForRequest\40\lbTransfer\42\ _clt\44\ lb_Transfer_Data \38\ request\41\:0:*/
int lbAppServer::waitForRequest(lbTransfer* _clt, lb_Transfer_Data & request) 
{
	*_clt >> request;
	char buf[100];
	
	sprintf(buf, "lbAppServer::waitForRequest(): Got a request with %d packets", request.getPacketCount());
	LOG(buf);
	
	return 0;
}
/*...e*/
	
/*...slbAppServer\58\\58\handleRequest\40\\46\\46\\46\\41\:0:*/
int lbAppServer::handleRequest(lb_Transfer_Data request, 
                               lb_Transfer_Data & result)
{// Dispatching were possible here with servertype...
	return _request(request, result);
}
/*...e*/
	                  
/*...slbAppServer\58\\58\answerRequest\40\lbTransfer\42\ _clt\44\ lb_Transfer_Data result\41\:0:*/
int lbAppServer::answerRequest(lbTransfer* _clt, lb_Transfer_Data result) 
{
	*_clt << result;
	return 0;
}
/*...e*/

int lbAppServer::initTransfer(char* host_servicename) {
	cout << "lbAppServer::initTransfer(char* host_servicename) called" << endl;
	transfer = new lbTransfer();
	cout << "Created instance of lbTransfer" << endl;
	transfer->init(host_servicename);
	
	return 1;
}

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
#ifdef bla
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

	//bus.AnounceClient(); // Announce me as a new application on the bus
	
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
#endif
/*...e*/
/*...slbAppClient\58\\58\Disconnect\40\\41\:0:*/
#ifdef bla
void lbAppClient::Disconnect() {
}
#endif
/*...e*/
/*...slbAppClient\58\\58\requestObject\40\const char\42\ name\41\:0:*/
lbObject* lbAppClient::requestObject(const char* type, const char* name) {
	/**
	 * The result depends on the name given by the parameter.
	 * Simply, this is only a forwarding of the request (to anywhere).
	 */
	
	lbString object;
	object.setData("Test");
	
	return object.clone();
}
/*...e*/
/*...slbAppClient\58\\58\delete\40\void\42\ ptr\41\:0:*/
void lbAppClient::operator delete(void* ptr) {
	::delete ptr;
}
/*...e*/
/*...slbAppClient\58\\58\operator new\40\size_t size\41\:0:*/
void* lbAppClient::operator new(size_t size) {
	if (size == sizeof(lbAppClient)) return malloc(size);
	return NULL;
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


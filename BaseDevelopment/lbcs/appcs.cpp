/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    The author of this work will be reached by e-Mail or paper mail.
    e-Mail: lothar.behrens@lollisoft.de
    p-Mail: Lothar Behrens
            Rosmarinstr. 3
            
            40235 DÅsseldorf (germany)
*/
/*...e*/
#define APPCS_DLL

#include <string.h>
#include <conio.h>
#include <lbInclude.h>
//#include <lbInterfaces.h>

/*...slbAppServerThread:0:*/
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
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOGENABLE("lbAppServerThread::Entry()");
	LOG("lbAppServerThread::Entry(): Do request");
#endif
/*...e*/
	server->_connected(clt);
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOG("lbAppServerThread::Entry(): Done request");
#endif
/*...e*/
	//COUT << "lbAppServerThread::Entry(): Done request" << ENDL;	
	return NULL;
}
/*...e*/

/*...slbAppServerThread\58\\58\lbAppServerThread\40\lbTransfer\42\ _clt\44\ lbAppServer\42\ _server\41\:0:*/
lbAppServerThread::lbAppServerThread(lbTransfer* _clt, lbAppServer* _server) {
	/*
		Check if the given transfer client has valid data
	*/
	
	if (_clt == NULL) {
		LOG("lbAppServerThread::lbAppServerThread(...) Error: Have a NULL pointer!");
	}
	else
	if (_clt->isValid() == 1) {
		clt = _clt;
		server = _server;
	} else {
		LOG("lbAppServerThread::lbAppServerThread(...) Error: Got an invalid lbTransfer client object!");
		clt = _clt;
		server = _server;
	}
}
/*...e*/

/*...slbAppServerThread\58\\58\\126\lbAppServerThread\40\\41\:0:*/
lbAppServerThread::~lbAppServerThread() {
	COUT << "lbAppServerThread::~lbAppServerThread() called" << ENDL;
}
/*...e*/

/*...e*/

/*...slbDispatchFn \40\Container for a registered function handler\41\:0:*/
lbDispatchFn::lbDispatchFn(const char* service, lbMemberCallback fn) {
	dispFn = fn;
}

lbDispatchFn::~lbDispatchFn() {
}

void lbDispatchFn::setType() {
	OTyp = LB_APPCLIENT_DISPATCH_FN;
}

lbObject* lbDispatchFn::clone() const {
	lbDispatchFn *clone = new lbDispatchFn("", dispFn);
	return clone;
}
	
lbMemberCallback lbDispatchFn::getFn() {
	return dispFn;
}
/*...e*/

/*...slbDispatchProto \40\Container for a registered protocol handler\41\:0:*/
lbDispatchProto::lbDispatchProto(const char* service, lbProtocolCallback fn) {
	dispProto = fn;
}

lbDispatchProto::~lbDispatchProto() {
}

void lbDispatchProto::setType() {
	OTyp = LB_APPSERVER_DISPATCH_PROTO;
}

lbObject* lbDispatchProto::clone() const {
	lbDispatchProto *clone = new lbDispatchProto("", dispProto);
	return clone;
}
	
lbProtocolCallback lbDispatchProto::getProto() {
	return dispProto;
}
/*...e*/

/*...slbConnection:0:*/
lbConnection::lbConnection(char* host, int _pid, int _tid) {
	hostname = strdup(host);
	pid = _pid;
	tid = _tid;
}

lbConnection::~lbConnection() {
	free(hostname);
}

void lbConnection::setType() {
	OTyp = LB_CONNECTION;
}

lbObject* lbConnection::clone() const {
	lbConnection* cloned = new lbConnection(hostname, pid, tid);
	
	return (lbObject*) cloned;
}
/*...e*/

/*...slbAppServer:0:*/
/*...slbAppServer\58\\58\lbAppServer\40\\41\:0:*/
lbAppServer::lbAppServer() {
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOGENABLE("lbAppServer::lbAppServer()");
#endif
/*...e*/
/*...sdead code:0:*/
/*
	LOG("lbAppServer::lbAppServer(): Initialize lbTransfer object");
	transfer = new lbTransfer();
	transfer->init("localhost/busmaster");
	LOG("lbAppServer::lbAppServer(): Initialized");
*/
/*...e*/

    connections = new lbComponentDictionary();
    dispatchTable = new lbComponentDictionary();
}
/*...e*/
/*...slbAppServer\58\\58\\126\lbAppServer\40\\41\:0:*/
lbAppServer::~lbAppServer() {
	delete dispatchTable;
}
/*...e*/
/*...slbAppServer\58\\58\initTransfer\40\char\42\ host_servicename\41\:0:*/
int lbAppServer::initTransfer(char* host_servicename) {
	//COUT << "lbAppServer::initTransfer(char* host_servicename) called" << ENDL;
	transfer = new lbTransfer();
	//COUT << "Created instance of lbTransfer" << ENDL;
	transfer->init(host_servicename);

	/**
	 * Register all servives, the derived class may have implemented
	 */
        lbErrCodes err = registerProtocols();
	
	return 1;
}
/*...e*/

// Secure data extractors
/*...slbAppServer\58\\58\requestString\40\request\44\ ident\41\:0:*/
lbErrCodes lbAppServer::requestString(lb_Transfer_Data& request,
	                	          char* ident) {
char* buffer = NULL;
	if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
	
	request.incrementPosition();

	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\requestString\40\request\44\ ident\44\ data\41\:0:*/
lbErrCodes lbAppServer::requestString(lb_Transfer_Data& request,
	                	          char* ident,
        		                  char*& data) {
char* buffer = NULL;
	if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
char msg[100] = "";	

	if (strcmp(buffer, ident) != 0) {
		LOG("Error: Identifer not wanted");
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
	
	request.incrementPosition();

	if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		LOG("Error: Requested buffer is not of type LB_CHAR");
		return ERR_APP_SERVER_REQUEST_CHAR;
	}

	if (buffer != NULL) 
		data = buffer;
	else {
		LOG("lbAppServer::requestString(...) Error: Could not get real data (NULL pointer)!");
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
	
	request.incrementPosition();
	
	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\requestInteger\40\request\44\ ident\44\ data\41\:0:*/
lbErrCodes lbAppServer::requestInteger(lb_Transfer_Data& request,
	                	          char* ident,
        		                  int& data) {
char* buffer = NULL;
	if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}
	
	request.incrementPosition();

	if (request.get(data) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}

	request.incrementPosition();

	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\requestULong\40\request\44\ ident\44\ data\41\:0:*/
lbErrCodes lbAppServer::requestULong(lb_Transfer_Data& request,
	                	          char* ident,
        		                  unsigned long& data) {
char* buffer = NULL;
	if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}
	
	request.incrementPosition();

	if (request.get(data) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_INTEGER;
	}

	request.incrementPosition();

	return ERR_NONE;
}
/*...e*/

// Main server
/*...slbAppServer\58\\58\run\40\\41\:0:*/
int lbAppServer::run() { 
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOG("lbAppServer::run() called");
        LOG("lbAppServer::run(): Initialize lbTransfer object");
#endif
/*...e*/
	char srvname[100] = "";
	strcpy(srvname, getServiceName());



	if (initTransfer(srvname) == 0) {
		LOG("lbAppServer::run(): Error, failed to initialize transfer");
		return 0;
	}
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
        LOG("lbAppServer::run(): Initialized");
#endif        
/*...e*/

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
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
		LOG("lbAppServer::run(): Wait for a client connection");
#endif		
/*...e*/


		if (transfer == NULL) LOG("lbAppServer::run() Error: transfer object pointer is NULL!");
		COUT << "Wait for connection..." << ENDL;
		if (transfer->accept(clt) == 0) 
		{
			LOG("lbAppServer::run() error while accepting on a socket");
			return 0;
		}

		/**
		 * here I can begin a thread with is calling _connected.
		 * Like the documentation from Win32 System Services p366.
		 * But the new client socket must be associated to that 
		 * thread, because
		 */
		lbAppServerThread* thread = new lbAppServerThread(clt, this);
		thread->create();
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE		
		LOG("lbAppServer::run() Got a connection, Handle it in thread...");
#endif
/*...e*/
		thread->run();
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE		
		LOG("lbAppServer::run() Thread is running...");
#endif
/*...e*/
	}
}
/*...e*/
/*...slbAppServer\58\\58\_connected\40\lbTransfer\42\ _clt\41\:0:*/
lbErrCodes lbAppServer::_connected(lbTransfer* _clt) {

	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rCOUT = ERR_NONE;
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
		if ((rCOUT = answerRequest(_clt, result)) != ERR_NONE) {
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
		&& (rCOUT == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rCOUT != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
/*...e*/

	return rc;
}
/*...e*/



// Request handler
/*...slbAppServer\58\\58\waitForRequest\40\lbTransfer\42\ _clt\44\ lb_Transfer_Data \38\ request\41\:0:*/
lbErrCodes lbAppServer::waitForRequest(lbTransfer* _clt, lb_Transfer_Data & request) 
{
	*_clt >> request;
	
	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while waiting for request");
	    return ERR_APP_SERVER_WAIT_REQUEST;
	}
	
	char buf[100];
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
	sprintf(buf, "lbAppServer::waitForRequest(): Got a request with %d packets", request.getPacketCount());
	LOG(buf);
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\dispatch\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::dispatch(lb_Transfer_Data request, 
                                 lb_Transfer_Data & result)
{// Dispatching were possible here with servertype...

lbErrCodes rc = ERR_NONE;

	/**
	 * One server thread is created for one client process. But this
	 * will not allow to use the server. Each client must also request
	 * for a connection to give the server the anilitiy from wich thread
	 * a further request is from. So the server can block one thread from
	 * other thread using one request.
	 */
	if (isConnected(request) == 0) {
		rc = HandleConnect(request, result);
		LOG("Handled a nonconnected request");
		return rc;
	}
	else {
		char* buffer = NULL;
		if (request.get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
			return ERR_APP_SERVER_REQUEST_CHAR;
		} else {

			// Block here for dynamic dispatch handling		
			lbDispatchProto* proto = (lbDispatchProto*) dispatchTable->getElement(lbStringKey(buffer));
		
			if (proto != NULL) {
				rc = (this->*((lbProtocolCallback) (proto->getProto()))) (request, result);
			} else {
				LOG("Can not dispatch unknown request");
				rc = ERR_APP_SERVER_DISPATCH;
			}
			
		}
	
		return rc;
	}
}
/*...e*/
/*...slbAppServer\58\\58\answerRequest\40\lbTransfer\42\ _clt\44\ lb_Transfer_Data result\41\:0:*/
lbErrCodes lbAppServer::answerRequest(lbTransfer* _clt, lb_Transfer_Data result) 
{
	// Need a little delay till client may be ready to recieve data...
//LOG("This pause is needed ???");
//	lb_sleep(1000);

	*_clt << result;

	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while sending request");
	    return ERR_APP_SERVER_SEND_REQUEST;
	}


	return ERR_NONE;
}
/*...e*/

// Handler management

/*...slbAppServer\58\\58\addProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::addProtocolHandler(const char* handlername, 
                                          lbProtocolCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	if (dispatchTable->exists(lbStringKey(handlername)) == 0) {
		if ((err = dispatchTable->insert(lbDispatchProto(handlername, cbFn), 
		                      lbStringKey(handlername))) != ERR_NONE) {
			LOG("Could not add handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service previously added");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/
/*...slbAppServer\58\\58\delProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::delProtocolHandler(const char* handlername) {
	lbErrCodes err = ERR_NONE;

	if (dispatchTable->exists(lbStringKey(handlername)) == 1) {
		if ((err = dispatchTable->remove(lbStringKey(handlername))) != ERR_NONE) {
			LOG("Could not remove handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service not registered");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/


// Proto handler
/*...slbAppServer\58\\58\HandleConnect\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::HandleConnect(lb_Transfer_Data request,
          				 lb_Transfer_Data & result) {
/*...sAPPBUS_SVR_VERBOSE:0:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppServer::HandleConnect(...) called");
#endif
/*...e*/
	LB_PACKET_TYPE type;
	char *clienthost = NULL;
	unsigned long pid = 0;
	unsigned long tid = 0;

/*...sConnect proto:0:*/
/*
	add("Connect")
	add("Host") // your hostname
	add(your host)
	add("Pid")
	add(your pid)
	add("Tid")
	add(your tid")
*/
/*...e*/

/*...srequest data:8:*/
	if (requestString(request, "Connect") != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No Connect request", 
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (requestString(request, "Host", clienthost) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No Hostname in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (requestULong(request, "Pid", pid) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No pid in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}

	if (requestULong(request, "Tid", tid) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No tid in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
/*...e*/

	//COUT << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid << ENDL;
	
	if (connections->exists(lbKeyUL(tid)) == 0) {
		result.add("Accept");

		lbConnection conn(clienthost, pid, tid);
		lbKeyUL key(tid);
		connections->insert(conn, key);
	} else {
		result.add("Deny");
		result.add("Already connected");
		LOG("lbAppServer::HandleConnect(...) Error: already connected!");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
//COUT << "lbAppServer::HandleConnect(...) Succeeded" << ENDL;	
	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\HandleDisconnect\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::HandleDisconnect(lb_Transfer_Data request,
          				 lb_Transfer_Data & result) {
/*...sAPPBUS_SVR_VERBOSE:0:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppServer::HandleConnect(...) called");
#endif
/*...e*/
	LB_PACKET_TYPE type;
	char *clienthost = NULL;
	int pid = 0;
	int tid = 0;

/*
	add("Disconnect")
	add("Host") // your hostname
	add(your host)
	add("Pid")
	add(your pid)
	add("Tid")
	add(your tid")
*/

/*...srequest data:8:*/
	if (requestString(request, "Disconnect") != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No Connect request", 
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (requestString(request, "Host", clienthost) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No Hostname in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (requestInteger(request, "Pid", pid) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No pid in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}

	if (requestInteger(request, "Tid", tid) != ERR_NONE) {
		makeProtoErrAnswer(result, 
				   "Error: No tid in request",
				   "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
/*...e*/

	//COUT << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid << ENDL;
	
	result.add("Accept");
	result.add(clienthost);
	
	return ERR_NONE;
}
/*...e*/

// Helpers
/*...slbAppServer\58\\58\isConnected\40\\46\\46\\46\\41\:0:*/
int lbAppServer::isConnected(lb_Transfer_Data &request) {

	if (connections->exists(lbKeyUL(request.clientTid)) == 1) {
		return 1;
	}
	
	return 0;
}
/*...e*/
/*...slbAppServer\58\\58\makeProtoErrAnswer\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::makeProtoErrAnswer(lb_Transfer_Data &result, char* msg, char* where) {
	char buf[100];
	result.add("Error");
	result.add(msg);
	
	sprintf(buf, "%s Cause: %s", where, msg);
	LOG(buf);
	
	return ERR_NONE;
}
/*...e*/
/*...e*/

/*...slbAppClient:0:*/
/*...slbAppClient\58\\58\lbAppClient\40\\41\:0:*/
lbAppClient::lbAppClient() {
	clientConnection = NULL;
	AppBusClient = NULL;
}
/*...e*/
/*...slbAppClient\58\\58\lbAppClient\40\lbTransfer \42\ clConn\41\:0:*/
lbAppClient::lbAppClient(lbTransfer* clConn) {
#ifdef APPCS_VERBOSE
	LOGENABLE("lbAppClient::lbAppClient()");
#endif
	clientConnection = clConn;
}
/*...e*/
/*...slbAppClient\58\\58\\126\lbAppClient\40\\41\:0:*/
lbAppClient::~lbAppClient() {
COUT << "Cleanup lbAppClient" << ENDL;
}
/*...e*/
/*...slbAppClient\58\\58\requestObject\40\const char\42\ name\41\:0:*/
lbObject* lbAppClient::requestObject(const char* type, const char* name) {
	/**
	 * The result depends on the name given by the parameter.
	 * Simply, this is only a forwarding of the request (to anywhere).
	 */

	/**
	 * Setup request.
	 */
	

	return NULL; //object.clone();
}
/*...e*/
/*...slbAppClient\58\\58\delete\40\void\42\ ptr\41\:0:*/
void lbAppClient::operator delete(void* ptr) {
	LOG("lbAppClient::operator delete(void* ptr) called");
	::delete ptr;
}
/*...e*/
/*...slbAppClient\58\\58\operator new\40\size_t size\41\:0:*/
void* lbAppClient::operator new(size_t size) {
	LOG("lbAppClient::operator new(size_t size) called");
	
	if (size == sizeof(lbAppClient)) return malloc(size);
	return NULL;
}
/*...e*/

// Handler management

/*...slbAppClient\58\\58\addCallbackHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppClient::addCallbackHandler(const char* handlername, 
                                          lbMemberCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	if (dispatchTable->exists(lbStringKey(handlername)) == 0) {
		if ((err = dispatchTable->insert(lbDispatchFn(handlername, cbFn), 
		                      lbStringKey(handlername))) != ERR_NONE) {
			LOG("Could not add handler");
			err = ERR_APP_CLIENT_ADDHANDLER;
		}
	} else {
		LOG("Request previously added");
		err = ERR_APP_CLIENT_ADDHANDLER;
	}
	return err;
}
/*...e*/

lbErrCodes lbAppClient::dispatch(const char* request, lb_Transfer_Data& result) {
	return ERR_NONE;
}

lbErrCodes lbAppClient::getLastError(char* description, int len) {
	return ERR_NONE;
}

lbErrCodes lbAppClient::delCallbackHandler(const char* handlername) {
	return ERR_NONE;
}

lbErrCodes lbAppClient::initialize() {
	return ERR_NONE;
}

lbErrCodes lbAppClient::request(const char* request, lb_Transfer_Data& result) {
	return ERR_NONE;
}

lbErrCodes lbAppClient::release() {
	return ERR_NONE;
}

void lbAppClient::setAppBusClient(lbAppBusClient* _AppBusClient) {
	AppBusClient = _AppBusClient;
}
/*...e*/

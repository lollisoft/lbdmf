#define APPCS_DLL

#include <string.h>
#include <conio.h>
#include <lbInclude.h>

#ifdef bla
/*...sObject thunking implementation:0:*/
struct WCallBackInfo
{
  WMemberCallBack memberCallBack;
  lbObject       * object;
};
    
DWORD GetCallBackPointer
(
  const WCallBackInfo * info
);

#pragma aux  GetCallBackPointer   = \
  " call dword ptr[ eax ]         " \
  parm [eax];

DWORD GetThisPointer
(
  const WCallBackInfo * info
);

#pragma aux  GetThisPointer    = \
  " mov eax, 0xc[edx]          " \ 
  " add eax, 0x4[edx]          " \
  parm [edx] ;


#define POP_EAX   BYTE( 0x58 )
#define PUSH_EAX  BYTE( 0x50 )
#define PUSH_ECX  BYTE( 0x51 )
#define PUSH_EDX  BYTE( 0x52 )
#define PUSH_32   BYTE( 0x68 )
#define JMP_EAX1  BYTE( 0xff )
#define JMP_EAX2  BYTE( 0xe0 )
#define JMP_32    BYTE( 0xe9 )
#define MOV_EDX   BYTE( 0xba )
#define MOV_EAX   BYTE( 0xb8 )
#define JMP_EAX   USHORT( 0xe0ff )


/////////////////////////////////////////////////////////////////////////
#pragma pack( push, 1 )

struct WThunkCode
{
  BYTE   code1[2];
  DWORD  thisPointer;
  BYTE   code2[8];
  DWORD  callBackPointer;
  BYTE   code3[2];
};


struct WRtlThunkCode
{
  BYTE   code1[4];
  DWORD  thisPointer;
  BYTE   code2[1];
  DWORD  callBackPointer;
  BYTE   code3[4];
};

#pragma pack ( pop )


static const BYTE m_codePattern[ sizeof(WThunkCode) ] =
{
  0x50,                          //  0 push eax
  0xb8, 0x00, 0x00, 0x00, 0x00,  //  1 mov  eax, thisPointer
  0x87, 0x44, 0x24, 0x04,        //  6 xchg eax, 4[esp]
  0x87, 0x04, 0x24,              // 10 xchg [esp], eax
  0x68, 0x00, 0x00, 0x00, 0x00,  // 13 push callBackPointer
  0xc3,                          // 18 ret
  0x90,                          // 19 nop
};

static const BYTE m_codeRtlPattern[ sizeof(WRtlThunkCode) ] =
{
  0x51,             //  0 push ecx
  0x52,             //  1 push edx
  0x50,             //  2 push eax
  0x68, 0, 0, 0, 0, //  3 push thispointer
  0xb8, 0, 0, 0, 0, //  8 mov  eax,callback
  0xff, 0xD0,       // 13 call eax
  0x59,             // 15 pop ecx
  0xc3,             // 16 ret
};



//  Include definitions for resources.


WObjectThunk::WObjectThunk()
{

}

void * WObjectThunk::Create(lbObject * object, WMemberCallBack callbackMemberFunction, BOOL createRtlCallback )
{
//  WTraceFunction();
  //////////////////////////////////////////////////

  if( object )
  {
    WCallBackInfo info;

    info.memberCallBack   = callbackMemberFunction;
    info.object           = object;

    if( createRtlCallback )
    {
      WRtlThunkCode * code   = new WRtlThunkCode;

      if( code )
      {
        ///////////////////////////////////////
        // fill the thunk code piece 

        memcpy( code, m_codeRtlPattern, sizeof( WRtlThunkCode ) );
        code->thisPointer     = GetThisPointer( &info );
        code->callBackPointer = GetCallBackPointer( &info );
      }  
      return code;
    }
    else
    {
      WThunkCode * code   = new WThunkCode;

      if( code )
      {
        ///////////////////////////////////////
        // fill the thunk code piece 

        memcpy( code, m_codePattern, sizeof( WThunkCode ) );
        code->thisPointer     = GetThisPointer( &info );
        code->callBackPointer = GetCallBackPointer( &info );

      }
      return code;
    }  
  }
  return NULL;
}

BOOL WObjectThunk::Destroy( void * thunkCode )
{
//  WTraceFunction();
  //////////////////////////////////////////////////

  if( thunkCode )
  {
    if( *(BYTE *)thunkCode == PUSH_ECX )
    {
      WRtlThunkCode * code = (WRtlThunkCode *)thunkCode;

      delete code;
      return TRUE;
    }

    else if ( *(BYTE *)thunkCode == PUSH_EAX )
    {
      WThunkCode * code = (WThunkCode *)thunkCode;

      delete code;
      return TRUE;
    }
    else 
      LOG("Unknown ThunkCode");
      //WAssertEx( false, "Unknown ThunkCode" );
  }
  return FALSE;
}

/*...e*/
#endif

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
	//cout << "lbAppServerThread::Entry(): Done request" << endl;	
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
	cout << "lbAppServerThread::~lbAppServerThread() called" << endl;
}
/*...e*/

/*...e*/

/*...slbDispatchFn \40\Container for a registered handler\41\:0:*/
lbDispatchFn::lbDispatchFn(const char* service, lbMemberEvent fn) {
	dispFn = fn;
}

lbDispatchFn::~lbDispatchFn() {
}

void lbDispatchFn::setType() {
	OTyp = LB_APPSERVER_DISPATCH_FN;
}

lbObject* lbDispatchFn::clone() const {
	lbDispatchFn *clone = new lbDispatchFn("", dispFn);
	return clone;
}
	
lbMemberEvent lbDispatchFn::getFn() {
	return dispFn;
}
/*...e*/

/*...slbConnection:0:*/
lbConnection::lbConnection(char* host, int _pid, int _tid) {
	hostname = strdup(host);
	pid = _pid;
	tid = _tid;
}

lbConnection::~lbConnection() {
	delete[] hostname;
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
	//cout << "lbAppServer::initTransfer(char* host_servicename) called" << endl;
	transfer = new lbTransfer();
	//cout << "Created instance of lbTransfer" << endl;
	transfer->init(host_servicename);

	/**
	 * Register all servives, the derived class may have implemented
	 */
        lbErrCodes err = _registerServices();
	
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
		cout << "Wait for connection..." << endl;
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
/*...slbAppServer\58\\58\handleRequest\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::handleRequest(lb_Transfer_Data request, 
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
			lbDispatchFn* fn = (lbDispatchFn*) dispatchTable->getElement(lbStringKey(buffer));
		
			if (fn != NULL) {
				rc = (this->*((lbMemberEvent) (fn->getFn()))) (request, result);
			} else {
				LOG("Can not dispatch this request");
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

/*...slbAppServer\58\\58\addServiceHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::addServiceHandler(const char* handlername, 
                                          lbMemberEvent cbFn) {
	lbErrCodes err = ERR_NONE;

	if (dispatchTable->exists(lbStringKey(handlername)) == 0) {
		if ((err = dispatchTable->insert(lbDispatchFn(handlername, cbFn), 
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

	//cout << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid << endl;
	
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
//cout << "lbAppServer::HandleConnect(...) Succeeded" << endl;	
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

	//cout << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid << endl;
	
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
cout << "Cleanup lbAppClient" << endl;
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
	
	lb_Transfer_Data request;
	lb_Transfer_Data result;
	 
	request.add("requestObject");
	request.add("type");
	request.add(type);
	request.add("name");
	request.add(name);	 
	
	*clientConnection << request;
	*clientConnection >> result;
	
	lbString object;
	object.setData("Test");
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
LOG("lbAppClient::requestObject(...) Creates currently only an lbString");
#endif
/*...e*/

	return object.clone();
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

void lbAppClient::setAppBusClient(lbAppBusClient* _AppBusClient) {
	AppBusClient = _AppBusClient;
}
/*...e*/

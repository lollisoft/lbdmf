#include "module.h"
#include <signal.h>
/*...sinclude:0:*/
/*...sifdef WINDOWS:0:*/
#ifdef WINDOWS
#include <windows.h>
#include <winsock.h>
#include <conio.h>
#endif // WINDOWS
/*...e*/

#include <iostream.h>
#include <lbInclude.h>

/*...s\35\ifdef __WXGTK__:0:*/
#ifdef __WXGTK__
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <curses.h>
#endif // __WXGTK__
/*...e*/
/*...e*/

lbCritSect socketSection;

lbMutex sendMutex;
lbMutex recvMutex;


/*...sclass lbSocketModule:0:*/
class lbSocketModule {
public:
	lbSocketModule() {
		sendMutex.CreateMutex(LB_SEND_MUTEX);
		recvMutex.CreateMutex(LB_RECV_MUTEX);
	}
	virtual ~lbSocketModule() {
		cout << "Deinit socket module" << endl;
	}
};
/*...e*/

int lbSocket::sockUse = 0;

lbSocketModule sockModule; // Module initializion

/*...sclass lbMutexLocker:0:*/
class lbMutexLocker {
public:
	lbMutexLocker(lbMutex m) {
		mutex = m;
		mutex.Enter();
	}
	
	virtual ~lbMutexLocker() {
		mutex.Release();
	}
	
	lbMutex mutex;
};
/*...e*/

/*...sLogWSAError\40\char\42\ msg\41\:0:*/
int LogWSAError(char* msg) {
	lbLock lock(socketSection, "Socket");
	char buf[100] = "";
	char _buf[100] = "Socket error (%d) at '%s'";
	int lastError = WSAGetLastError();
	
	if (strlen(_buf)+strlen(msg) >99) {	
		LOG("LogWSAError(char* msg) Error: Buffer overflow");
		return 0;
	} else {	
		sprintf(buf, "Socket error (%d) at '%s'", lastError, msg);
		LOG(buf);
	}
	
	return lastError;
}
/*...e*/

lbErrCodes mapWSAErrcode(int lastError, int isServer) {

	return ERR_SOCKET_UNKNOWN;
}


lbSocket::lbSocket() {
	lbLock lock(socketSection, "socketSection");
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOGENABLE("lbSocket::lbSocket()");
#endif
/*...e*/

	startupflag = 0;
	sockUse++;
}

/*...slbSocket\58\\58\lbSocket\40\const lbSocket\38\ s\41\:0:*/
lbSocket::lbSocket(const lbSocket& s) {
	lbLock lock(socketSection, "socketSection");	
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	LOG("lbSocket::lbSocket(const lbSocket& s) called");
#endif
/*...e*/
	/*WSADATA*/ 	Data = s.Data;
	/*SOCKADDR_IN*/ serverSockAddr = s.serverSockAddr;
	/*SOCKADDR_IN*/ clientSockAddr = s.clientSockAddr;
	/*SOCKET*/ 	serverSocket = s.serverSocket;
	/*SOCKET*/	clientSocket = s.clientSocket;
	/*int*/		status = s.status;
	/*int*/		addrLen = s.addrLen; //=sizeof(SOCKADDR_IN);

	/*unsigned long*/ 
			destAddr = s.destAddr; // for client init

	/*int*/		startupflag = s.startupflag;
}
/*...e*/

lbSocket::~lbSocket() {
	cout << "lbSocket::~lbSocket() called" << endl;
	LOG("lbSocket::~lbSocket() called");
	
	if (lbSockState == LB_SOCK_CONNECTED) close();
	sockUse--;
	
	if (sockUse == 0) {
		if (WSACleanup() == SOCKET_ERROR) {
			LOG("Winsock library could not be unloaded - how ever?");
			cout << "Winsock library could not be unloaded - how ever?" << endl;
		}
	}
}

/*...slbSocket\58\\58\isValid\40\\41\:0:*/
int lbSocket::isValid() {
	int numread = 0;
	u_long pendingBytes = 0L;
	char buf[MAXBUFLEN] = "";
//lbLock lock(socketSection, "socketSection");

pendingBytes++;
return 1;

	if (_isServer == 1) {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		LOG("lbSocket::isValid() called on server");
		#endif
/*...e*/
		// Let the server blocking
		//pendingBytes++;
		numread = ::ioctlsocket(clientSocket, FIONREAD, (u_long FAR*)&pendingBytes);
		
//		numread = ::recv(clientSocket, buf, MAXBUFLEN, MSG_PEEK);
		if (numread == SOCKET_ERROR) {
			LogWSAError("lbSocket::isValid() Failed by server");
			return 0;
		}
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		LOG("lbSocket::isValid() leaving on server");
		#endif
/*...e*/
	} else {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		LOG("lbSocket::isValid() called on client");
		#endif
/*...e*/
		numread = ::ioctlsocket(serverSocket, FIONREAD, (u_long FAR*)&pendingBytes);
//		numread = ::recv(serverSocket, buf, MAXBUFLEN, MSG_PEEK);
		if (numread == SOCKET_ERROR) {
			LogWSAError("lbSocket::isValid() Failed by client");
			return 0;
		}
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		LOG("lbSocket::isValid() leaving on client");
		#endif
/*...e*/
	}
	
	if (pendingBytes > 0L) {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		char buf[100] = "";
		sprintf(buf, "lbSocket::isValid() Ok. Have %d bytes of data pending", pendingBytes);
		LOG(buf);
		#endif
/*...e*/
	} else {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		LOG("lbSocket::isValid() leave with no data");	
		#endif
/*...e*/
		return 0;
	}
/*...sSOCKET_VERBOSE:0:*/
	#ifdef SOCKET_VERBOSE
	LOG("lbSocket::isValid() leave with data");	
	#endif
/*...e*/
	return 1;
}
/*...e*/

/*...slbSocket\58\\58\neagleOff\40\SOCKET s\41\:0:*/
lbErrCodes lbSocket::neagleOff(SOCKET s) {
	int opt = 1;

        if (::setsockopt(s, 
               IPPROTO_TCP, 
               TCP_NODELAY, 
               (char*)(&opt), 
               sizeof(int)) != 0)
        {
        	LOG("Error: NeagleOff failed");
        	return ERR_SOCKET_NEAGLEOFF;
        }
        
        return ERR_NONE;
}
/*...e*/

/*...slbSocket\58\\58\connect\40\\41\:0:*/
int lbSocket::connect()
{
      if (lbSockState == LB_SOCK_CONNECTED) {
      	LOG("lbSocket::connect(): ERROR: Illegal state for this function");
      	return 0;
      }
#ifdef WINDOWS
      status=::connect(serverSocket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
      if (status == SOCKET_ERROR)
      {
        LOG("lbSocket::connect(): ERROR: connect to unsuccessful");
        status=closesocket(serverSocket);
        if (status == SOCKET_ERROR)
          LOG("lbSocket::connect(): ERROR: closesocket unsuccessful");
        status=WSACleanup();
        if (status == SOCKET_ERROR)
          LOG("lbSocket::connect(): ERROR: WSACleanup unsuccessful");
        return 0;  
      }
#endif
#ifdef __WXGTK__
      status=::connect(serverSocket, (sockaddr*) &serverSockAddr, sizeof(serverSockAddr));
      if (status < 0)
      {
#ifdef bla
        close();
#endif
        return 0;
      }
#endif
      return 1;
}
/*...e*/
/*...slbSocket\58\\58\close\40\\41\:0:*/
int lbSocket::close()
{
#ifdef __WXGTK__
        status=::shutdown(serverSocket, 2);
        if (status < 0)
        {
          cerr << "ERROR: closesocket unsuccessful" << endl;
          return 0;
        }
#endif
#ifdef WINDOWS
	if(_isServer == 1)
		status=::closesocket(serverSocket);
	else
		status=::closesocket(clientSocket);	
#endif
        return 1;
}
/*...e*/
/*...slbSocket\58\\58\listen\40\\41\:0:*/
int lbSocket::listen()
{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOGENABLE("lbSocket::listen()");
#endif
/*...e*/

    lbSockState = LB_SOCK_LISTENING;


      if (lbSockState == LB_SOCK_CONNECTED) {
      	LOG("lbSocket::listen(): ERROR: Illegal state for this function");
      	return 0;
      }
    /* allow the socket to take connections */
#ifdef WINDOWS
    status=::listen(serverSocket, 1);
    if (status == SOCKET_ERROR)
      LOG("lbSocket::listen(): ERROR: listen unsuccessful");
#endif
#ifdef __WXGTK__
    status=::listen(serverSocket, 1);
    if (status < 0)
      LOG("lbSocket::listen(): ERROR: listen unsuccessful");
#endif


    return 1;
}
/*...e*/
/*...slbSocket\58\\58\accept\40\lbSocket\42\\38\ s\41\:0:*/
lbErrCodes lbSocket::accept(lbSocket *& s)
{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOGENABLE("lbSocket::accept(lbSocket *& s)");
#endif
/*...e*/
      if (lbSockState == LB_SOCK_CONNECTED) {
      	LOG("lbSocket::accept(lbSocket** s): ERROR: Illegal state for this function");
      	return ERR_SOCKET_STATE;
      }
/*...sWINDOWS:0:*/
#ifdef WINDOWS
    /* accept the connection request when one
       is received */
    clientSocket=::accept(serverSocket, (LPSOCKADDR) &clientSockAddr, &addrLen);
    if (clientSocket == SOCKET_ERROR) LOG("Error while accepting on socket");

#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
    clientSocket=::accept(serverSocket, (sockaddr*) &clientSockAddr, &addrLen); 
#endif
/*...e*/

    if (neagleOff(clientSocket) != ERR_NONE) LOG("Error: Subsequent");

    if (clientSocket == INVALID_SOCKET) {
    	s = NULL;
    	LOG("lbSocket::accept(lbSocket** s): Created clientSocket is invalid");
    	return ERR_SOCKET_CLIENT_S_INVALID;
    }
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE    
    LOG("lbSocket::accept(lbSocket*& s): Create a new lbSocket for the client");    
#endif
/*...e*/
    s = new lbSocket();
    s->setSockConnection(clientSocket);
    
    // Be secure clientSocket of this instance is INVALID_SOCKET
    
    clientSocket = INVALID_SOCKET;
    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::accept(lbSocket*& s): Created");
#endif
/*...e*/

    // This socket can never be in connected state
    //lbSockState = LB_SOCK_CONNECTED;

    return ERR_NONE;
}
/*...e*/
/*...slbSocket\58\\58\bind\40\\41\:0:*/
int lbSocket::bind()
{
#ifdef WINDOWS
    /* associate the socket with the address */
    status=::bind(serverSocket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
    if (status == SOCKET_ERROR)
      LOG("lbSocket::bind(): ERROR: bind unsuccessful");
#endif
#ifdef __WXGTK__
    status=::bind(serverSocket, (sockaddr*) &serverSockAddr, sizeof(serverSockAddr));
    if (status < 0)
      LOG("lbSocket::bind(): ERROR: bind unsuccessful");
#endif
    return 1;  
}
/*...e*/
/*...slbSocket\58\\58\socket\40\\41\:0:*/
int lbSocket::socket()
{
#ifdef WINDOWS
  /* create a socket */
  serverSocket=::socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == INVALID_SOCKET) {
    LogWSAError("lbSocket::socket(): ERROR: socket unsuccessful");
    return 0;
  }  


  if (neagleOff(serverSocket) != ERR_NONE) LOG("Error: Subsequent");


#endif
#ifdef __WXGTK__
  serverSocket=::socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
    LOG("lbSocket::socket(): ERROR: socket unsuccessful");
#endif

  return 1;  
}
/*...e*/

/*...slbSocket\58\\58\setSockConnection\40\SOCKET s\41\:0:*/
int lbSocket::setSockConnection(SOCKET s) {
	lbSockState = LB_SOCK_CONNECTED;
	clientSocket = s;
        clBackup = clientSocket;
	_isServer = 1;
	return 1;
}
/*...e*/

/*...slbSocket\58\\58\gethostname\40\char \42\ \38\ name\41\:0:*/
int lbSocket::gethostname(char * & name) {
	char buf[100];
	
	::gethostname(buf, sizeof(buf));
	
	if (strlen(buf) > 0) {
		name = strdup(buf);
		return 1;
	}
	
	return 0;
}
/*...e*/

/*...slbSocked\58\\58\inet_addrFromString\40\char\42\ addr\41\:0:*/
unsigned long lbSocket::inet_addrFromString(char* w) {
    struct hostent *hep;
    unsigned long my_addr;
    char *p;
    hep = gethostbyname(w);

    if ((!hep) || (hep->h_addrtype != AF_INET || !hep->h_addr_list[0])) {
        fprintf(stderr, "Cannot resolve host name %s --- exiting!\n", w);
        exit(1);
    }

    if (hep->h_addr_list[1]) {
        fprintf(stderr, "Host %s has multiple addresses ---\n", w);
        fprintf(stderr, "you must choose one explicitly for use as\n");
        fprintf(stderr, "a virtual host.  Exiting!!!\n");
        exit(1);
    }

    return ((struct in_addr *) (hep->h_addr))->s_addr;
}
/*...e*/


/*...slbSocket\58\\58\startup\40\\41\:0:*/
int lbSocket::startup()
{
#ifdef WINDOWS
	if (startupflag == 0) {
		/* initialize the Windows Socket DLL */
		status=WSAStartup(MAKEWORD(1, 1), &Data);
		if (status != 0) 
		  LOG("lbSocket::startup(): ERROR: WSAStartup unsuccessful");
		/* zero the sockaddr_in structure */
		memset(&serverSockAddr, 0, sizeof(serverSockAddr));
		startupflag = 1;
	}
#endif
#ifdef __WXGTK__
#endif
  return 1;
}
/*...e*/
/*...slbSocket\58\\58\reinit\40\char \42\mysockaddr\41\:0:*/
void lbSocket::reinit(char *mysockaddr)
{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::reinit(char *mysockaddr): This function should not be used");
#endif
/*...e*/
#ifdef WINDOWS
  if (strcmp(mysockaddr, "") == 0)
  {
  #ifdef bla 
    SOCKET s;
    accept(s);
  #endif 
  }
  else
  {
    connect();
  }
#endif
#ifdef __WXGTK__
  if (strcmp(mysockaddr, "") == 0)
  {
    if (__isServer == 1)
    {
      //listen();
    
      accept();
    }
    else printf("Error, socket was server, not client!\n");
  }
  else
  {
    if (_isServer == 0)
    {
      accept();
      connect();
    }
    else printf("Error, socket was client, not server!\n");
  }
#endif
}
/*...e*/
/*...slbSocket\58\\58\initSymbolic\40\char\42\ host\44\ char\42\ service\41\:0:*/
void lbSocket::initSymbolic(char* host, char* service) {
	char msg[100];
	int serverMode = 0;
	startup();
	//cout << "Initialize for host '" << host << "'" << endl;
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	sprintf(msg, "void lbSocket::initSymbolic(char* host, char* service): Init for %s %s", host, service);
	LOG(msg);	
#endif
/*...e*/
	if (strcmp(host, "localhost") == 0)
	{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
		LOG("lbSocket::initSymbolic(char* host, char* service): Socket initializing as server");
#endif
/*...e*/
		serverMode = 1;
	}
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	 else {

		LOG("lbSocket::initSymbolic(char* host, char* service): Socket initializing as client");

	}
#endif
/*...e*/
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE	
	LOG("lbSocket::initSymbolic(char* host, char* service) called");
#endif
/*...e*/
	
	servent* s = getservbyname(service, NULL);
 
/*...sStruct definition:0:*/
 /*
 struct hostent { 
     char FAR *       h_name; 
     char FAR * FAR * h_aliases; 
     short            h_addrtype; 
     short            h_length; 
     char FAR * FAR * h_addr_list; 
 };
 */
/*...e*/

	if(s == NULL) LOG("lbSocket::initSymbolic(char* host, char* service): No service entry found");
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
 	sprintf(msg, "Got hostaddress: %d", inet_addrFromString(host));
 	LOG(msg);
#endif
/*...e*/
 	u_short port = s->s_port;
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	sprintf(msg, "lbSocket::init(char* hostaddr, char* port) with %s %d calling", host, port);
	LOG(msg); 
#endif
/*...e*/
 	init((serverMode == 1) ? 0 : inet_addrFromString(host), port);
}
/*...e*/
/*...slbSocket\58\\58\init\40\unsigned long mysockaddr\44\ u_short port\41\:0:*/
void lbSocket::init( unsigned long mysockaddr, u_short port)
{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::init( unsigned long mysockaddr, u_short port) called");
#endif
/*...e*/
  char buf[100];
  (mysockaddr == 0) ? _isServer = 1 : _isServer = 0;

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  addrLen=sizeof(SOCKADDR_IN);

  startup();    

  if (_isServer == 0)
  {// Address given, assume this as client initialition
    /* convert IP address into in_addr form */
    destAddr= mysockaddr; // inet_addr(...)
    /* copy destAddr into sockaddr_in structure */
    memcpy(&serverSockAddr.sin_addr, &destAddr, sizeof(destAddr));
  }
    
  /* specify the port portion of the address */
  serverSockAddr.sin_port=htons(port);
  /* specify the address family as Internet */
  serverSockAddr.sin_family=AF_INET;

  if (_isServer == 1)
  {// No address given, server can be connected from all
    /* specify that the address does not matter */
    serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::init( unsigned long mysockaddr, u_short port): Initializing as server");
#endif
/*...e*/
  }

  socket();

  if (_isServer == 1)
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) bind...");
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) listen...");
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connect...");
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connected");
#endif
/*...e*/
  }
#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
  addrLen=sizeof(sockaddr);

  if (_isServer == 1)
  {// Address given, assume this as client initialition
    /* convert IP address into in_addr form */
    destAddr=inet_addr(mysockaddr);
    /* copy destAddr into sockaddr_in structure */
    memcpy(&serverSockAddr.sin_addr, &destAddr, sizeof(destAddr));
  }
    
  /* specify the port portion of the address */
  serverSockAddr.sin_port=htons(port);
  /* specify the address family as Internet */
  serverSockAddr.sin_family=AF_INET;

  if (_isServer == 1)
  {// No address given, server can be connected from all
    /* specify that the address does not matter */
    serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  }

  socket();

  if (_isServer == 1)
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) bind...");
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) listen...");
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connect...");
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connected");
#endif
/*...e*/
  }
#endif
/*...e*/
#undef VERBOSE
}
/*...e*/


/*...slbSocket\58\\58\sendInteger\40\int i\41\:0:*/
lbErrCodes lbSocket::sendInteger(int i) {
	lbErrCodes err = ERR_NONE;
	char buf[MAXBUFLEN];
	itoa(i, buf, 10);

	if ((err = send_charbuf(buf, strlen(buf))) == ERR_NONE)
	{
		return err;
	} else {
		LOG("lbSocket: Error while sending an integer");
		return err;
	}
}
/*...e*/
/*...slbSocket\58\\58\recvInteger\40\int\38\ i\41\:0:*/
lbErrCodes lbSocket::recvInteger(int& i) {
	lbErrCodes err = ERR_NONE;
	char buf[MAXBUFLEN];
        // Wait for a datapacket
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::recvInteger(): Enter");
#endif
/*...e*/

	if ((err = recv_charbuf(buf)) == ERR_NONE) {
		int number = atoi(buf);
		i = number;
	} else {
		LOG("lbSocket: Error while recieving an integer");
	}
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::recvInteger(): Leave");
#endif
/*...e*/
	return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\void\42\ buf\44\ int \38\ len\41\:0:*/
lbErrCodes lbSocket::recv(void* buf, int & len) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::recv(void* buf, int & len): Enter");
#endif
/*...e*/

//LOG("Enter recv");
//    lbMutexLocker mlock(recvMutex);
    
    lbErrCodes err = ERR_NONE;
    int numrcv = 0;
    char* bufpos = (char*) buf;
    int lastError = 0;

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  while (isValid() == 0) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  	LOG("lbSocket::recv(...) Failed while isValid() check!");
#endif
/*...e*/
  	lb_sleep(100);
  } 
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  LOG("lbSocket::recv(...) Have valid data");
#endif
/*...e*/

    if (_isServer == 1)
    {
      if (clBackup != clientSocket) LOG("Error, socket variable has been changed since got from accept");

// Empfange Packetgr”áe
    numrcv=::recv(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) LOG("Error: Packet size not sent correctly");

      numrcv=::recv(clientSocket, bufpos, len, NO_FLAGS_SET);
    }  
    if (_isServer == 0)
    {
// Empfange Packetgr”áe
    numrcv=::recv(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) LOG("Error: Packet size not sent correctly");
     
      numrcv=::recv(serverSocket, bufpos, len, NO_FLAGS_SET);
    }
         
/*...shandle any error:0:*/
    if (numrcv == SOCKET_ERROR) {
        char msg[100] = "";
        if (_isServer == 1) {
	   err = ERR_SOCKET_CLOSE_SERVER;
	   strcpy(msg, "lbSocket::recv(void* buf, int & len) server");
	}
        else {      
           err = ERR_SOCKET_CLOSE_CLIENT;
	   strcpy(msg, "lbSocket::recv(void* buf, int & len) client");
	}

        lastError = LogWSAError(msg);
        
        return err;
    }
/*...e*/


/*...shandle 0 recv or error:0:*/
    if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
    {
      if (_isServer == 0)
      	LOG("lbSocket::recv(void* buf, int & len): Connection terminated by server.");
      else
      	LOG("lbSocket::recv(void* buf, int & len): Connection terminated by client.");	

      status= closesocket( (_isServer==0) ? clientSocket : serverSocket);

      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG"ERROR: WSACleanup unsuccessful");
#endif        
      return err;
    }
/*...e*/
#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
  if (_isServer == 1)
    numrcv=::recv(clientSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
  if (_isServer == 0)
    numrcv=::recv(serverSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);

    if ((numrcv == 0) || (numrcv < 0))
    {
#ifdef bla
        close();
        status=WSACleanup();
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
#endif
      return 0;
    }
#endif
/*...e*/

    len = numrcv;    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOG("lbSocket::recv(void* buf, int & len): Leave");
#endif
/*...e*/
    return err;
}
/*...e*/
/*...slbSocket\58\\58\send\40\void\42\ buf\44\ int len\41\:0:*/
lbErrCodes lbSocket::send(void *buf, int len)
{
lbErrCodes err = ERR_NONE;
int lastError = 0;
char msg[100];
char *bufpos = (char*) buf;
int numsnt = 0;
//LOG("Enter send");
//lbMutexLocker mlock(sendMutex);

#ifdef WINDOWS
if (_isServer == 0) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/

// Sende Packetgr”áe
    numsnt=::send(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) LOG("Error: Packet size not sent correctly");

    numsnt=::send(serverSocket, bufpos, len, NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/
// Sende Packetgr”áe
    numsnt=::send(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) LOG("Error: Packet size not sent correctly");

    numsnt=::send(clientSocket, bufpos, len, NO_FLAGS_SET);
}
  
    if ((numsnt != len) && (numsnt == SOCKET_ERROR))
    {
      if (_isServer == 0) {
	      lastError = LogWSAError("lbSocket::send(...) client");
      } else {
	      lastError = LogWSAError("lbSocket::send(...) server");
      }


      char msg[100] = "";
      sprintf(msg, "lbSocket::send(void *buf, int len) Error: numsnt(%d) != len(%d)", numsnt, len);
      LOG(msg);
      LOG("lbSocket::send(void *buf, int len): Connection terminated");
      status=closesocket((_isServer == 1) ? serverSocket : clientSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
      return err;  
    } else if (numsnt != len) {
    		LOG("lbSocket::send(void* buf, int len) Error: Could not send all data at once!");
	}
#endif
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
   int numsnt = 0;

	if (_isServer == 0)
    	numsnt=::send(serverSocket,
        	        buf, len + 1,
            	    NO_FLAGS_SET);
	if (_isServer == 1)
    	numsnt=::send(clientSocket,
        	        buf, len + 1,
            	    NO_FLAGS_SET);
                
    if (numsnt != len + 1)
    {
#ifdef bla      
      close();
      status=WSACleanup();
      if (status < 0)
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
#endif
      return 0;  
    }
#endif
/*...e*/

/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    LOG("lbSocket::send(char *buf, int len) returning");
#endif
/*...e*/

    return err;
}
/*...e*/

/*...slbSocket\58\\58\recv_charbuf\40\char \42\buf\41\:0:*/
lbErrCodes lbSocket::recv_charbuf(char *buf)
{
    lbErrCodes err = ERR_NONE;
    int lastError = 0;
    // Wait for a datapacket
    int numrcv = 0;
    int len = 0; // Packet len haeder
    
//LOG("Enter recv");    
//    lbMutexLocker mlock(recvMutex);
    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
char msg[100];
sprintf(msg, "lbSocket::recv_charbuf(char *buf) enter");
LOG(msg);
#endif
/*...e*/

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  while (isValid() == 0) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  	LOG("lbSocket::recv_charbuf(...) Failed while isValid() check!");
#endif
/*...e*/
  	lb_sleep(100);
  } 
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  LOG("lbSocket::recv_charbuf(...) Have valid data");
#endif
/*...e*/

/*...sserver:0:*/
  if (_isServer == 1) {

// Empfange Packetgr”áe
    numrcv=::recv(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) LOG("Error: Packet size not recv correctly");
      
    numrcv=::recv(clientSocket, buf,
      len, NO_FLAGS_SET);
  }
/*...e*/
  
/*...sclient:0:*/
  if (_isServer == 0) {
// Empfange Packetgr”áe
    numrcv=::recv(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) LOG("Error: Packet size not recv correctly");
  
    numrcv=::recv(serverSocket, buf,
      len, NO_FLAGS_SET);
  }    
/*...e*/

    if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
    {
      if (_isServer == 0)
      	lastError = LogWSAError("recv_charbuf(char *buf) server");
      else
      	lastError = LogWSAError("recv_charbuf(char *buf) client");

      status= closesocket( (_isServer==0) ? clientSocket : serverSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
#endif        
      return ERR_SOCKET_RECV;//err;
    }
#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
  if (_isServer == 1)
    numrcv=::recv(clientSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
  if (_isServer == 0)
    numrcv=::recv(serverSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);

    if ((numrcv == 0) || (numrcv < 0))
    {
#ifdef bla
        close();
        status=WSACleanup();
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
#endif
      return 0;
    }
#endif
/*...e*/

/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
sprintf(msg, "lbSocket::recv_charbuf(char *buf) Leave");
LOG(msg);
#endif
/*...e*/
    
    return err;
}
/*...e*/
/*...slbSocket\58\\58\send_charbuf\40\char \42\buf\44\ int len\41\:0:*/
lbErrCodes lbSocket::send_charbuf(char *buf, int len)
{
lbErrCodes err = ERR_NONE;
int lastError = 0;
char msg[100];
#ifdef WINDOWS
   int numsnt;
   len++;
//LOG("Enter send");
//   lbMutexLocker mlock(sendMutex);

if (_isServer == 0) {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/

// Sende Packetgr”áe
    numsnt=::send(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) LOG("Error: Packet size not sent correctly");
    		
// Sende Packet    		
    numsnt=::send(serverSocket,
                buf, len,
                NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/

// Sende Packetgr”áe
    numsnt=::send(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) LOG("Error: Packet size not sent correctly");

    numsnt=::send(clientSocket,
                buf, len,
                NO_FLAGS_SET);
}
                
                
    if (numsnt == SOCKET_ERROR) LOG("lbSocket::send_charbuf(char *buf, int len) Error: Got SOCKET_ERROR");            
    if ((numsnt != len) && (numsnt == SOCKET_ERROR))
    {
      if (_isServer == 0) {
        lastError = LogWSAError("send_charbuf(...) client");
      } else {
        lastError = LogWSAError("send_charbuf(...) server");
      }
      
      err = mapWSAErrcode(lastError, _isServer);
      
      LOG("lbSocket::send_charbuf(char *buf, int len): Connection terminated");
      status=closesocket(serverSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
      return err;  
    } else if (numsnt != len) {
	    	char msg[100] = "";
	    	sprintf(msg, "Sent only %d bytes from %d bytes", numsnt, len);
	    	LOG(msg);
    	
	    	LOG("lbSocket::send_charbuf(char *buf, int len) Error: Could not send all data at once!");
	    }
#endif
#ifdef __WXGTK__
   int numsnt = 0;

	if (_isServer == 0)
    	numsnt=::send(serverSocket,
        	        buf, len,
            	    NO_FLAGS_SET);
	if (_isServer == 1)
    	numsnt=::send(clientSocket,
        	        buf, len,
            	    NO_FLAGS_SET);
                
    if (numsnt != len)
    {
#ifdef bla      
      close();
      status=WSACleanup();
      if (status < 0)
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
#endif
      return err;  
    }
#endif

/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    if (_isServer == 0) LOG("Client: lbSocket::send_charbuf(char *buf, int len) returning");
    if (_isServer == 1) LOG("Server: lbSocket::send_charbuf(char *buf, int len) returning");
#endif
/*...e*/

    return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\lb_Transfer_Data \38\ data\41\:0:*/
lbErrCodes lbSocket::recv(lb_Transfer_Data & data) {
	int i;
LOG("lbSocket::recv(lb_Transfer_Data & data) Not implemented!");	
	if (recvInteger(i) == 1) {
	}

	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbSocket\58\\58\send\40\lb_Transfer_Data \38\ data\41\:0:*/
lbErrCodes lbSocket::send(lb_Transfer_Data & data) {
LOG("lbSocket::recv(lb_Transfer_Data & data) Not implemented!");	
	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/


#include "module.h"
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

lbSocket::lbSocket() {
LOGENABLE("lbSocket::lbSocket()");
	startupflag = 0;
}
/*...slbSocket\58\\58\connect\40\\41\:0:*/
int lbSocket::connect()
{
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
        return 1;
}
/*...e*/
/*...slbSocket\58\\58\listen\40\\41\:0:*/
int lbSocket::listen()
{
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
/*...slbSocket\58\\58\accept\40\\41\:0:*/
int lbSocket::accept()
{
#ifdef WINDOWS
    /* accept the connection request when one
       is received */
    clientSocket=::accept(serverSocket, (LPSOCKADDR) &clientSockAddr, &addrLen);
#endif
#ifdef __WXGTK__
    clientSocket=::accept(serverSocket, (sockaddr*) &clientSockAddr, &addrLen); 
#endif
    return 1;
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
  if (serverSocket == INVALID_SOCKET)
    LOG("lbSocket::socket(): ERROR: socket unsuccessful");
#endif
#ifdef __WXGTK__
  serverSocket=::socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
    LOG("lbSocket::socket(): ERROR: socket unsuccessful");
#endif
  return 1;  
}
/*...e*/

int lbSocket::gethostname(char * & name) {
	char buf[100];
	
	::gethostname(buf, sizeof(buf));
	
	if (strlen(buf) > 0) {
		name = strdup(buf);
		return 1;
	}
	
	return 0;
}

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
		if (status != 0) LOG("lbSocket::startup(): ERROR: WSAStartup unsuccessful");
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
#ifdef WINDOWS
  if (strcmp(mysockaddr, "") == 0)
  {
    accept();
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	sprintf(msg, "void lbSocket::initSymbolic(char* host, char* service): Init for %s %s", host, service);
	LOG(msg);	
#endif
/*...e*/
	if (strcmp(host, "localhost") == 0)
	{
		LOG("Socket initializing as server");
		serverMode = 1;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE	
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
 	sprintf(msg, "Got hostaddress: %d", inet_addrFromString(host));
 	LOG(msg);
#endif
/*...e*/
 	u_short port = s->s_port;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
#ifdef VERBOSE
LOG("lbSocket::init( unsigned long mysockaddr, u_short port): Initializing as server");
#endif
/*...e*/
  }

  socket();

  if (_isServer == 1)
  {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) bind...");
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) listen...");
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connect...");
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) bind...");
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) listen...");
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connect...");
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    LOG("lbSocket::init(char *mysockaddr, u_short port) connected");
#endif
/*...e*/
  }
#endif
/*...e*/
}
/*...e*/


/*...slbSocket\58\\58\sendInteger\40\int i\41\:0:*/
int lbSocket::sendInteger(int i) {
	char buf[MAXBUFLEN];

	itoa(i, buf, 10);

	if (send_charbuf(buf, strlen(buf)) == 1)
	{
		return 1;
	} else {
		LOG("lbSocket: Error while sending an integer");
		return 0;
	}
}
/*...e*/
/*...slbSocket\58\\58\recvInteger\40\int\38\ i\41\:0:*/
int lbSocket::recvInteger(int& i) {
	char buf[MAXBUFLEN];
        // Wait for a datapacket
#ifdef VERBOSE
LOG("lbSocket::recvInteger(): Enter");
#endif

	if (recv_charbuf(buf) == 1) {
		int number = atoi(buf);
		i = number;
	} else {
		LOG("lbSocket: Error while recieving an integer");
		return 0;
	}
#ifdef VERBOSE
LOG("lbSocket::recvInteger(): Enter");
#endif
	return 1;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\void\42\ buf\44\ int \38\ len\41\:0:*/
int lbSocket::recv(void* buf, int & len) {
#ifdef VERBOSE
LOG("lbSocket::recv(void* buf, int & len): Enter");
#endif

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  if (_isServer == 1)
    numrcv=::recv(clientSocket, (char*) buf,
      len, NO_FLAGS_SET);
      
  if (_isServer == 0)
    numrcv=::recv(serverSocket, (char*) buf,
      len, NO_FLAGS_SET);
      
    if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
    {
      LOG("Connection terminated.");
      status=closesocket(clientSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG"ERROR: WSACleanup unsuccessful");
#endif        
      return 0;
    }
#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
  if (_isServer == 1)
    numrcv=::recv(clientSocket, buf,
      len, NO_FLAGS_SET);
      
  if (_isServer == 0)
    numrcv=::recv(serverSocket, buf,
      len, NO_FLAGS_SET);

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
#ifdef VERBOSE
LOG("lbSocket::recv(void* buf, int & len): Leave");
#endif
    return 1;
}
/*...e*/
/*...slbSocket\58\\58\send\40\void\42\ buf\44\ int len\41\:0:*/
int lbSocket::send(void *buf, int len)
{
char msg[100];
#ifdef WINDOWS
   int numsnt;

if (_isServer == 0) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/
    numsnt=::send(serverSocket,
                (char const*) buf, len + 1,
                NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/
    numsnt=::send(clientSocket,
                (char const*) buf, len + 1,
                NO_FLAGS_SET);
}
                
    if (numsnt != len + 1)
    {
      LOG("lbSocket::send(void *buf, int len): Connection terminated");
      status=closesocket(serverSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
      return 0;  
    }
#endif
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

/*...sVERBOSE:0:*/
#ifdef VERBOSE
    if (_isServer == 0) LOG("Client: lbSocket::send_charbuf(char *buf, int len) returning");
    if (_isServer == 1) LOG("Server: lbSocket::send_charbuf(char *buf, int len) returning");
#endif
/*...e*/

    return 1;
}
/*...e*/

/*...slbSocket\58\\58\recv_charbuf\40\char \42\buf\41\:0:*/
int lbSocket::recv_charbuf(char *buf)
{
    // Wait for a datapacket
#ifdef VERBOSE
char msg[100];
sprintf(msg, "lbSocket::recv_charbuf(char *buf) Enter");
LOG(msg);
#endif

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  if (_isServer == 1)
    numrcv=::recv(clientSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
  if (_isServer == 0)
    numrcv=::recv(serverSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
    if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
    {
      LOG("Connection terminated.");
      status=closesocket(clientSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
#endif        
      return 0;
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

#ifdef VERBOSE
sprintf(msg, "lbSocket::recv_charbuf(char *buf) Leave");
LOG(msg);
#endif
    
    return 1;
}
/*...e*/
/*...slbSocket\58\\58\send_charbuf\40\char \42\buf\44\ int len\41\:0:*/
int lbSocket::send_charbuf(char *buf, int len)
{
char msg[100];
#ifdef WINDOWS
   int numsnt;

if (_isServer == 0) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/
    numsnt=::send(serverSocket,
                buf, len + 1,
                NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    LOG(msg);
#endif
/*...e*/
    numsnt=::send(clientSocket,
                buf, len + 1,
                NO_FLAGS_SET);
}
                
    if (numsnt != len + 1)
    {
      LOG("lbSocket::send_charbuf(char *buf, int len): Connection terminated");
      status=closesocket(serverSocket);
      if (status == SOCKET_ERROR)
        LOG("ERROR: closesocket unsuccessful");
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        LOG("ERROR: WSACleanup unsuccessful");
      return 0;  
    }
#endif
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

/*...sVERBOSE:0:*/
#ifdef VERBOSE
    if (_isServer == 0) LOG("Client: lbSocket::send_charbuf(char *buf, int len) returning");
    if (_isServer == 1) LOG("Server: lbSocket::send_charbuf(char *buf, int len) returning");
#endif
/*...e*/

    return 1;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\lb_Transfer_Data \38\ data\41\:0:*/
int lbSocket::recv(lb_Transfer_Data & data) {
	int i;
	
	if (recvInteger(i) == 1) {
	}

	return 1;
}
/*...e*/
/*...slbSocket\58\\58\send\40\lb_Transfer_Data \38\ data\41\:0:*/
int lbSocket::send(lb_Transfer_Data & data) {
	return 1;
}
/*...e*/


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
        LOG("lbSocket::connect(): ERROR: connect unsuccessful");
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
    if (isServer == 1)
    {
      //listen();
    
      accept();
    }
    else printf("Error, socket was server, not client!\n");
  }
  else
  {
    if (isServer == 0)
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
	
	if (strcmp(host, "localhost") == 0)
		serverMode = 1;
LOG("lbSocket::initSymbolic(char* host, char* service) called");

	hostent *entry = gethostbyname(host);
	
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

 	if (entry == NULL) LOG("lbSocket::initSymbolic(char* host, char* service): No host address found");
	if ((entry != NULL) && (entry->h_addr_list == NULL)) LOG("lbSocket::initSymbolic(char* host, char* service): Host list is a NULL pointer!");

	if(s == NULL) LOG("lbSocket::initSymbolic(char* host, char* service): No service entry found");

 	char* hostaddr = strdup(entry->h_addr_list[0]);
 	u_short port = s->s_port;

LOG("lbSocket::init(char* hostaddr, char* port) calling");
 
 	init((serverMode == 1) ? "" : hostaddr, port);

LOG("lbSocket::init(char* hostaddr, char* port) called");
}
/*...e*/
/*...slbSocket\58\\58\init\40\char \42\mysockaddr\44\ u_short port\41\:0:*/
void lbSocket::init(char *mysockaddr, u_short port)
{
  if (strcmp(mysockaddr, "") != 0)
    isServer = 0;
  else
    isServer = 1;

#ifdef WINDOWS
  addrLen=sizeof(SOCKADDR_IN);

  startup();    

  if (strcmp(mysockaddr, "") != 0)
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

  if (strcmp(mysockaddr, "") == 0)
  {// No address given, server can be connected from all
    /* specify that the address does not matter */
    serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  }

  socket();

  if (strcmp(mysockaddr, "") == 0)
  {
    bind();
    
    listen();
    
    accept();
  }
  else
  {
    connect();
  }
#endif
#ifdef __WXGTK__
  addrLen=sizeof(sockaddr);

  if (strcmp(mysockaddr, "") != 0)
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

  if (strcmp(mysockaddr, "") == 0)
  {// No address given, server can be connected from all
    /* specify that the address does not matter */
    serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
  }

  socket();

  if (strcmp(mysockaddr, "") == 0)
  {
    bind();
    
    listen();
    
    accept();
  }
  else
  {
    connect();
  }
#endif
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

	if (recv_charbuf(buf) == 1) {
		int number = atoi(buf);
		i = number;
	} else {
		LOG("lbSocket: Error while recieving an integer");
		return 0;
	}
	return 1;
}
/*...e*/
/*...slbSocket\58\\58\recv_charbuf\40\char \42\buf\41\:0:*/
int lbSocket::recv_charbuf(char *buf)
{
#ifdef WINDOWS
  if (isServer == 1)
    numrcv=::recv(clientSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
  if (isServer == 0)
    numrcv=::recv(serverSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
    if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
    {
      cout << "Connection terminated." << endl;
      status=closesocket(clientSocket);
      if (status == SOCKET_ERROR)
        cerr << "ERROR: closesocket unsuccessful" << endl;
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
#endif        
      //getch();
      return 0;
    }
#endif
#ifdef __WXGTK__
  if (isServer == 1)
    numrcv=::recv(clientSocket, buf,
      MAXBUFLEN, NO_FLAGS_SET);
      
  if (isServer == 0)
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
    return 1;
}
/*...e*/
/*...slbSocket\58\\58\send_charbuf\40\char \42\buf\44\ int len\41\:0:*/
int lbSocket::send_charbuf(char *buf, int len)
{
#ifdef WINDOWS
   int numsnt;

if (isServer == 0)
    numsnt=::send(serverSocket,
                buf, len + 1,
                NO_FLAGS_SET);
if (isServer == 1)
    numsnt=::send(clientSocket,
                buf, len + 1,
                NO_FLAGS_SET);
                
    if (numsnt != len + 1)
    {
      LOG("lbSocket::send_charbuf(char *buf, int len): Connection terminated");
      status=closesocket(serverSocket);
      if (status == SOCKET_ERROR)
        cerr << "ERROR: closesocket unsuccessful" << endl;
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        cerr << "ERROR: WSACleanup unsuccessful" << endl;
      return 0;  
    }
#endif
#ifdef __WXGTK__
   int numsnt = 0;

	if (isServer == 0)
    	numsnt=::send(serverSocket,
        	        buf, len + 1,
            	    NO_FLAGS_SET);
	if (isServer == 1)
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


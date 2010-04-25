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
			Heinrich-Scheufelen-Platz 2
 
			73252 Lenningen (germany)
 */
/*...e*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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

#include <iostream>
#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...s\35\ifdef __WXGTK__:0:*/
#ifdef __WXGTK__
#include <lbinclude.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <curses.h>
#endif // __WXGTK__
/*...e*/

/*...s\35\ifdef __WXGTK__:0:*/
#ifdef OSX
#ifdef __cplusplus
extern "C" {      
#endif            
#include <lbinclude.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
//#include <curses.h>
	
	
	
#ifdef __cplusplus
}      
#endif            
#endif // OSX
/*...e*/

#include <lbInterfaces.h>

#include <lbthread.h>
#include <socket.h>

#define LB_TRANSFER_DLL
#include <lbtransfer-module.h>
/*...e*/


IMPLEMENT_FUNCTOR(instanceOflbSocket, lbSocket)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbSocket)
	ADD_INTERFACE(lb_I_Socket)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbSocket::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbSocket::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

#define LB_SEND_MUTEX 1001
#define LB_RECV_MUTEX 1002
#define socketSection 1003



/*...sclass lbSocketModule:0:*/
class lbSocketModule {
public:
	lbSocketModule() {
		sendMutex = new lbMutex();
		recvMutex = new lbMutex();
		sendMutex->createMutex(LB_SEND_MUTEX);
		recvMutex->createMutex(LB_RECV_MUTEX);
	}
	virtual ~lbSocketModule() {
		COUT << "Deinit socket module" << ENDL;
	}
private:
	
	lbMutex* sendMutex;
	lbMutex* recvMutex;

};
/*...e*/

int lbSocket::sockUse = 0;

lbSocketModule sockModule; // Module initializion

/*...sclass lbMutexLocker:0:*/
class lbMutexLocker {
public:
	lbMutexLocker(lbMutex m) {
		mutex = m;
		mutex.enter();
	}
	
	virtual ~lbMutexLocker() {
		mutex.release();
	}
	
	lbMutex mutex;
};
/*...e*/

/*...sLogWSAError\40\char\42\ msg\41\:0:*/
#ifdef WINDOWS
int LogWSAError(char* msg) {
/// \todo Implement lock
	//lbLock lock(socketSection, "Socket");
	char buf[100] = "";
	char _buf[100] = "Socket error (%d) at '%s'";
	int lastError = WSAGetLastError();

	if ((lastError != 10054) && // Not a "Connection reset by peer"
	    (lastError != 10061)    // Not a "Connection refused" (on client I think)
	   ) { 
/*...slog it:8:*/
	  if (strlen(_buf)+strlen(msg) >99) {	
		  _LOG << "LogWSAError(char* msg) Error: Buffer overflow" LOG_
		  return 0;
	  } else {	
		  sprintf(buf, "Socket error (%d) at '%s'", lastError, msg);
		  _LOG << buf LOG_
	  }
/*...e*/
	}
	
	return lastError;
}
#endif
/*...e*/

lbErrCodes mapWSAErrcode(int lastError, int isServer) {

	return ERR_SOCKET_UNKNOWN;
}


lbSocket::lbSocket() {
/// \todo Implement lock
	//lbLock lock(socketSection, "socketSection");
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOGENABLE("lbSocket::lbSocket()");
#endif
/*...e*/

#ifdef WINDOWS
	startupflag = 0;
#endif
	sockUse++;
}

/*...slbSocket\58\\58\lbSocket\40\const lbSocket\38\ s\41\:0:*/
lbSocket::lbSocket(const lbSocket& s) {
/// \todo Implement lock
	//lbLock lock(socketSection, "socketSection");
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	_LOG << "lbSocket::lbSocket(const lbSocket& s) called" LOG_
#endif
/*...e*/
#ifdef WINDOWS	
	/*WSADATA*/ 	Data = s.Data;
	/*int*/		startupflag = s.startupflag;
#endif
	/*SOCKADDR_IN*/ serverSockAddr = s.serverSockAddr;
	/*SOCKADDR_IN*/ clientSockAddr = s.clientSockAddr;
	/*SOCKET*/ 	serverSocket = s.serverSocket;
	/*SOCKET*/	clientSocket = s.clientSocket;
	/*int*/		status = s.status;
	/*int*/		addrLen = s.addrLen; //=sizeof(SOCKADDR_IN);

	/*unsigned long*/ 
			destAddr = s.destAddr; // for client init

}
/*...e*/

lbSocket::~lbSocket() {
	COUT << "lbSocket::~lbSocket() called" << ENDL;
	_LOG << "lbSocket::~lbSocket() called" LOG_
	
	if (lbSockState == LB_SOCK_CONNECTED) close();
	sockUse--;
#ifdef WINDOWS	
	if (sockUse == 0) {
		if (WSACleanup() == SOCKET_ERROR) {
			_LOG << "Winsock library could not be unloaded - how ever?" LOG_
			COUT << "Winsock library could not be unloaded - how ever?" << ENDL;
		}
	}
#endif
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
		_LOG << "lbSocket::isValid() called on server" LOG_
		#endif
/*...e*/
		// Let the server blocking
		//pendingBytes++;
#ifdef WINDOWS		
		numread = ::ioctlsocket(clientSocket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
		
#ifdef LINUX
#ifndef OSX
		numread = ::ioctl (clientSocket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
#endif
		
#ifdef OSX
		numread = ::ioctl (clientSocket, FIONREAD, &pendingBytes);
#endif
		
//		numread = ::recv(clientSocket, buf, MAXBUFLEN, MSG_PEEK);
		
		if (numread == -1) {
			_LOG << "lbSocket::isValid() Failed by server" LOG_
			return 0;
		}
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::isValid() leaving on server" LOG_
		#endif
/*...e*/
	} else {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::isValid() called on client" LOG_
		#endif
/*...e*/
#ifdef WINDOWS		
		numread = ::ioctlsocket(serverSocket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
		
#ifdef LINUX
#ifndef OSX
		numread = ::ioctl (serverSocket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
#endif
		
#ifdef OSX
		numread = ::ioctl (serverSocket, FIONREAD, &pendingBytes);
#endif
		//		numread = ::recv(serverSocket, buf, MAXBUFLEN, MSG_PEEK);
		if (numread == -1) {
			_LOG << "lbSocket::isValid() Failed by client" LOG_
			return 0;
		}
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::isValid() leaving on client" LOG_
		#endif
/*...e*/
	}
	
	if (pendingBytes > 0L) {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		char buf[100] = "";
		sprintf(buf, "lbSocket::isValid() Ok. Have %d bytes of data pending", pendingBytes);
		_LOG << buf LOG_
		#endif
/*...e*/
	} else {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::isValid() leave with no data" LOG_
		#endif
/*...e*/
		return 0;
	}
/*...sSOCKET_VERBOSE:0:*/
	#ifdef SOCKET_VERBOSE
	_LOG << "lbSocket::isValid() leave with data" LOG_
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
        	_LOG << "Error: NeagleOff failed" LOG_
        	return ERR_SOCKET_NEAGLEOFF;
        }
        
        return ERR_NONE;
}
/*...e*/

/*...slbSocket\58\\58\connect\40\\41\:0:*/
int lbSocket::connect()
{
      if (lbSockState == LB_SOCK_CONNECTED) {
      	_LOG << "lbSocket::connect(): ERROR: Illegal state for this function" LOG_
      	return 0;
      }
#ifdef WINDOWS
      status=::connect(serverSocket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
      if (status == SOCKET_ERROR)
      {
        _LOG << "lbSocket::connect(): ERROR: connect to unsuccessful" LOG_
        status=closesocket(serverSocket);
        if (status == SOCKET_ERROR)
          _LOG << "lbSocket::connect(): ERROR: closesocket unsuccessful" LOG_
        status=WSACleanup();
        if (status == SOCKET_ERROR)
          _LOG << "lbSocket::connect(): ERROR: WSACleanup unsuccessful" LOG_
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
      lbSockState = LB_SOCK_CONNECTED;
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
          cerr << "ERROR: closesocket unsuccessful" << ENDL;
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
      	_LOG << "lbSocket::listen(): ERROR: Illegal state for this function" LOG_
      	return 0;
      }
    /* allow the socket to take connections */
#ifdef WINDOWS
    status=::listen(serverSocket, 1);
    if (status == SOCKET_ERROR)
      _LOG << "lbSocket::listen(): ERROR: listen unsuccessful" LOG_
#endif
#ifdef __WXGTK__
    status=::listen(serverSocket, 1);
    if (status < 0)
      _LOG << "lbSocket::listen(): ERROR: listen unsuccessful" LOG_
#endif


    return 1;
}
/*...e*/
/*...slbSocket\58\\58\accept\40\lbSocket\42\\38\ s\41\:0:*/
lb_I_Socket* lbSocket::accept()
{
    lb_I_Socket* s = NULL;

/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
LOGENABLE("lbSocket::accept(lbSocket *& s)");
#endif
/*...e*/
      if (lbSockState == LB_SOCK_CONNECTED) {
      	_LOG << "lbSocket::accept(lbSocket** s): ERROR: Illegal state for this function" LOG_
      	return NULL; //ERR_SOCKET_STATE;
      }
/*...sWINDOWS:0:*/
#ifdef WINDOWS
    /* accept the connection request when one
       is received */
    clientSocket=::accept(serverSocket, (LPSOCKADDR) &clientSockAddr, &addrLen);
    if (clientSocket == SOCKET_ERROR) _LOG << "Error while accepting on socket" LOG_

#endif
/*...e*/
/*...s__WXGTK__:0:*/
#ifdef __WXGTK__
    clientSocket=::accept(serverSocket, (sockaddr*) &clientSockAddr, &addrLen); 
#endif
/*...e*/

    if (neagleOff(clientSocket) != ERR_NONE) _LOG << "Error: Subsequent" LOG_

    if (clientSocket == -1) {
    	_LOG << "lbSocket::accept(lbSocket** s): Created clientSocket is invalid" LOG_
    	return NULL; //ERR_SOCKET_CLIENT_S_INVALID;
    }
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE    
    _LOG << "lbSocket::accept(lbSocket*& s): Create a new lbSocket for the client" LOG_
#endif
/*...e*/
    lbSocket* socket = new lbSocket();
    socket->setSockConnection(clientSocket);
    
    // Be secure clientSocket of this instance is INVALID_SOCKET
    
    clientSocket = -1;
    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::accept(lbSocket*& s): Created" LOG_
#endif
/*...e*/

    // This socket can never be in connected state
    //lbSockState = LB_SOCK_CONNECTED;

    socket->queryInterface("lb_I_Socket", (void**) &s, __FILE__, __LINE__);

    return s;
}
/*...e*/
/*...slbSocket\58\\58\bind\40\\41\:0:*/
int lbSocket::bind()
{
#ifdef WINDOWS
    /* associate the socket with the address */
    status=::bind(serverSocket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
    if (status == SOCKET_ERROR)
      _LOG << "lbSocket::bind(): ERROR: bind unsuccessful" LOG_
#endif
#ifdef __WXGTK__
    status=::bind(serverSocket, (sockaddr*) &serverSockAddr, sizeof(serverSockAddr));
    if (status < 0)
      _LOG << "lbSocket::bind(): ERROR: bind unsuccessful" LOG_
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


  if (neagleOff(serverSocket) != ERR_NONE) _LOG << "Error: Subsequent" LOG_


#endif
#ifdef __WXGTK__
  serverSocket=::socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
    _LOG << "lbSocket::socket(): ERROR: socket unsuccessful" LOG_
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

/*...slbSocket\58\\58\gethostname\40\\41\:0:*/
char* lbSocket::gethostname() {
	static char buf[100];
	
	::gethostname(buf, sizeof(buf));
	
	return buf;
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
		  _LOG << "lbSocket::startup(): ERROR: WSAStartup unsuccessful" LOG_
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
_LOG << "lbSocket::reinit(char *mysockaddr): This function should not be used" LOG_
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
	//COUT << "Initialize for host '" << host << "'" << ENDL;
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	sprintf(msg, "void lbSocket::initSymbolic(char* host, char* service): Init for %s %s", host, service);
	_LOG << msg LOG_
#endif
/*...e*/
	if (strcmp(host, "localhost") == 0)
	{
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::initSymbolic(char* host, char* service): Socket initializing as server" LOG_
#endif
/*...e*/
		serverMode = 1;
	}
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	 else {

		_LOG << "lbSocket::initSymbolic(char* host, char* service): Socket initializing as client" LOG_

	}
#endif
/*...e*/
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE	
	_LOG << "lbSocket::initSymbolic(char* host, char* service) called" LOG_
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

	if(s == NULL) _LOG << "lbSocket::initSymbolic(char* host, char* service): No service entry found" LOG_
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
 	sprintf(msg, "Got hostaddress: %d", inet_addrFromString(host));
 	_LOG << msg LOG_
#endif
/*...e*/
 	u_short port = s->s_port;
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
	sprintf(msg, "lbSocket::init(char* hostaddr, char* port) with %s %d calling", host, port);
	_LOG << msg LOG_
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
_LOG << "lbSocket::init( unsigned long mysockaddr, u_short port) called" LOG_
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
_LOG << "lbSocket::init( unsigned long mysockaddr, u_short port): Initializing as server" LOG_
#endif
/*...e*/
  }

  socket();

  if (_isServer == 1)
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) bind..." LOG_
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) listen..." LOG_
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connect..." LOG_
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connected" LOG_
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
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) bind..." LOG_
#endif
/*...e*/
    bind();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) listen..." LOG_
#endif
/*...e*/
    listen();
  }
  else
  {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connect..." LOG_
#endif
/*...e*/
    connect();
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connected" LOG_
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
	sprintf(buf, "%d", i);

	if ((err = send_charbuf(buf, strlen(buf))) == ERR_NONE)
	{
		return err;
	} else {
		_LOG << "lbSocket: Error while sending an integer" LOG_
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
_LOG << "lbSocket::recvInteger(): Enter" LOG_
#endif
/*...e*/

	if ((err = recv_charbuf(buf)) == ERR_NONE) {
		int number = atoi(buf);
		i = number;
	} else {
		_LOG << "lbSocket: Error while recieving an integer" LOG_
	}
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
_LOG << "lbSocket::recvInteger(): Leave" LOG_
#endif
/*...e*/
	return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\void\42\ buf\44\ int \38\ len\41\:0:*/
lbErrCodes lbSocket::recv(void* buf, int & len) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
_LOG << "lbSocket::recv(void* buf, int & len): Enter" LOG_
#endif
/*...e*/

//_LOG << "Enter recv" LOG_
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
  	_LOG << "lbSocket::recv(...) Failed while isValid() check!" LOG_
#endif
/*...e*/
  	lb_sleep(100);
  } 
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  _LOG << "lbSocket::recv(...) Have valid data" LOG_
#endif
/*...e*/

    if (_isServer == 1)
    {
      if (clBackup != clientSocket) _LOG << "Error, socket variable has been changed since got from accept" LOG_

// Empfange Packetgr��e
    numrcv=::recv(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_

      numrcv=::recv(clientSocket, bufpos, len, NO_FLAGS_SET);
    }  
    if (_isServer == 0)
    {
// Empfange Packetgr��e
    numrcv=::recv(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
     
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
      	_LOG << "lbSocket::recv(void* buf, int & len): Connection terminated by server." LOG_
      else
      	_LOG << "lbSocket::recv(void* buf, int & len): Connection terminated by client." LOG_

      status= closesocket( (_isServer==0) ? clientSocket : serverSocket);

      if (status == SOCKET_ERROR)
        _LOG << "ERROR: closesocket unsuccessful" LOG_
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: WSACleanup unsuccessful" LOG_
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
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return 0;
    }
#endif
/*...e*/

    len = numrcv;    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
_LOG << "lbSocket::recv(void* buf, int & len): Leave" LOG_
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
//_LOG << "Enter send" LOG_
//lbMutexLocker mlock(sendMutex);

#ifdef WINDOWS
if (_isServer == 0) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    _LOG << msg LOG_
#endif
/*...e*/

// Sende Packetgr��e
    numsnt=::send(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_

    numsnt=::send(serverSocket, bufpos, len, NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    _LOG << msg LOG_
#endif
/*...e*/
// Sende Packetgr��e
    numsnt=::send(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_

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
      _LOG << msg LOG_
      _LOG << "lbSocket::send(void *buf, int len): Connection terminated" LOG_
      status=closesocket((_isServer == 1) ? serverSocket : clientSocket);
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: closesocket unsuccessful" LOG_
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: WSACleanup unsuccessful" LOG_
      return err;  
    } else if (numsnt != len) {
    		_LOG << "lbSocket::send(void* buf, int len) Error: Could not send all data at once!" LOG_
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
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return 0;  
    }
#endif
/*...e*/

/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    _LOG << "lbSocket::send(char *buf, int len) returning" LOG_
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

    if (lbSockState != LB_SOCK_CONNECTED) {
      _LOG << "Error: Can not recieve on unconnected socket" LOG_
      return ERR_SOCKET_UNCONNECTED;
    }
    
//_LOG << "Enter recv" LOG_
//    lbMutexLocker mlock(recvMutex);
    
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
char msg[100];
sprintf(msg, "lbSocket::recv_charbuf(char *buf) enter");
_LOG << msg LOG_
#endif
/*...e*/

/*...sWINDOWS:0:*/
#ifdef WINDOWS
  while (isValid() == 0) {
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  	_LOG << "lbSocket::recv_charbuf(...) Failed while isValid() check!" LOG_
#endif
/*...e*/
  	lb_sleep(100);
  } 
/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
  _LOG << "lbSocket::recv_charbuf(...) Have valid data" LOG_
#endif
/*...e*/

/*...sserver:0:*/
  if (_isServer == 1) {

// Empfange Packetgr��e
    numrcv=::recv(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) _LOG << "Error: Packet size not recv correctly" LOG_
      
    numrcv=::recv(clientSocket, buf,
      len, NO_FLAGS_SET);
  }
/*...e*/
  
/*...sclient:0:*/
  if (_isServer == 0) {
// Empfange Packetgr��e
    numrcv=::recv(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numrcv != sizeof(len)) _LOG << "Error: Packet size not recv correctly" LOG_
  
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

      if (_isServer == 1) {
        if (lbSockState == LB_SOCK_CONNECTED) {
          // lbSocket is serverside and was connected yet
          status = closesocket(clientSocket);
        }
      }
      else
        status = closesocket(serverSocket);


      if (status == SOCKET_ERROR)
        _LOG << "ERROR: closesocket unsuccessful" LOG_
#ifdef AUTOCLEANUP        
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: WSACleanup unsuccessful" LOG_
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
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return 0;
    }
#endif
/*...e*/

/*...sSOCKET_VERBOSE:0:*/
#ifdef SOCKET_VERBOSE
sprintf(msg, "lbSocket::recv_charbuf(char *buf) Leave");
_LOG << msg LOG_
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
//_LOG << "Enter send" LOG_
//   lbMutexLocker mlock(sendMutex);

if (_isServer == 0) {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Client: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    _LOG << msg LOG_
#endif
/*...e*/

// Sende Packetgr��e
    numsnt=::send(serverSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
    		
// Sende Packet    		
    numsnt=::send(serverSocket,
                buf, len,
                NO_FLAGS_SET);
}
if (_isServer == 1) {
/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    sprintf(msg, "Server: lbSocket::send_charbuf(char *buf='%s', int len) called", buf);
    _LOG << msg LOG_
#endif
/*...e*/

// Sende Packetgr��e
    numsnt=::send(clientSocket,
    		(char*)&len, sizeof(len),
    		NO_FLAGS_SET);

    if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_

    numsnt=::send(clientSocket,
                buf, len,
                NO_FLAGS_SET);
}
                
                
    if (numsnt == SOCKET_ERROR) _LOG << "lbSocket::send_charbuf(char *buf, int len) Error: Got SOCKET_ERROR" LOG_
    if ((numsnt != len) && (numsnt == SOCKET_ERROR))
    {
      if (_isServer == 0) {
        lastError = LogWSAError("send_charbuf(...) client");
      } else {
        lastError = LogWSAError("send_charbuf(...) server");
      }
      
      err = mapWSAErrcode(lastError, _isServer);
      
      _LOG << "lbSocket::send_charbuf(char *buf, int len): Connection terminated" LOG_
      status=closesocket(serverSocket);
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: closesocket unsuccessful" LOG_
      status=WSACleanup();
      if (status == SOCKET_ERROR)
        _LOG << "ERROR: WSACleanup unsuccessful" LOG_
      return err;  
    } else if (numsnt != len) {
	    	char msg[100] = "";
	    	sprintf(msg, "Sent only %d bytes from %d bytes", numsnt, len);
	    	_LOG << msg LOG_
    	
	    	_LOG << "lbSocket::send_charbuf(char *buf, int len) Error: Could not send all data at once!" LOG_
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
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return err;  
    }
#endif

/*...sVERBOSE:0:*/
#ifdef SOCKET_VERBOSE
    if (_isServer == 0) _LOG << "Client: lbSocket::send_charbuf(char *buf, int len) returning" LOG_
    if (_isServer == 1) _LOG << "Server: lbSocket::send_charbuf(char *buf, int len) returning" LOG_
#endif
/*...e*/

    return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\lb_I_Transfer_Data\42\ data\41\:0:*/
lbErrCodes lbSocket::recv(lb_I_Transfer_Data* data) {
	int i;
_LOG << "lbSocket::recv(lb_Transfer_Data & data) Not implemented!" LOG_
	if (recvInteger(i) == 1) {
	}

	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbSocket\58\\58\send\40\lb_I_Transfer_Data\42\ data\41\:0:*/
lbErrCodes lbSocket::send(lb_I_Transfer_Data* data) {
_LOG << "lbSocket::recv(lb_Transfer_Data & data) Not implemented!" LOG_
	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/


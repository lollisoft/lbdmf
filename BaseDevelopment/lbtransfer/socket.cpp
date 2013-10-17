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
			Ginsterweg 4
 
			65760 Eschborn (germany)
 */
/*...e*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <lbtransfer-module.h>
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

/*...s\35\ifdef LINUX:0:*/
#ifdef LINUX
#ifndef OSX
//#include <lbinclude.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
//#include <curses.h>
#endif
#endif // LINUX
/*...e*/

/*...s\35\ifdef LINUX:0:*/
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
	
#ifdef WINDOWS
	startupflag = 0;
#endif
	sockUse++;
	socket = 0;
	_isServer = 0;
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
	/*SOCKET*/ 	socket = s.socket;
	/*int*/		status = s.status;
	/*int*/		addrLen = s.addrLen; //=sizeof(SOCKADDR_IN);

	/*unsigned long*/ 
			destAddr = s.destAddr; // for client init

}
/*...e*/

lbSocket::~lbSocket() {
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
#ifdef bla
	if (_isServer == 1) {
/*...sSOCKET_VERBOSE:0:*/
		#ifdef SOCKET_VERBOSE
		_LOG << "lbSocket::isValid() called on server" LOG_
		#endif
/*...e*/
		// Let the server blocking
		//pendingBytes++;
#ifdef WINDOWS		
		numread = ::ioctlsocket(socket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
		
#ifdef LINUX
#ifndef OSX
		numread = ::ioctl (socket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
#endif
		
#ifdef OSX
		numread = ::ioctl (socket, FIONREAD, &pendingBytes);
#endif
		
//		numread = ::recv(socket, buf, MAXBUFLEN, MSG_PEEK);
		
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
		numread = ::ioctlsocket(socket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
		
#ifdef LINUX
#ifndef OSX
		numread = ::ioctl (socket, FIONREAD, (u_long FAR*)&pendingBytes);
#endif
#endif
		
#ifdef OSX
		numread = ::ioctl (socket, FIONREAD, &pendingBytes);
#endif
		//		numread = ::recv(socket, buf, MAXBUFLEN, MSG_PEEK);
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
#endif
}
/*...e*/

/*...slbSocket\58\\58\neagleOff\40\SOCKET s\41\:0:*/
lbErrCodes lbSocket::neagleOff(SOCKET s) {
	int opt = 1;

	
	if (::setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)(&opt), sizeof(int)) != 0)
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
		close();
      }
#ifdef WINDOWS
      status=::connect(socket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
      if (status == SOCKET_ERROR)
      {
        _LOG << "lbSocket::connect(): ERROR: connect to unsuccessful" LOG_
        status=closesocket(socket);
        if (status == SOCKET_ERROR)
          _LOG << "lbSocket::connect(): ERROR: closesocket unsuccessful" LOG_
        status=WSACleanup();
        if (status == SOCKET_ERROR)
          _LOG << "lbSocket::connect(): ERROR: WSACleanup unsuccessful" LOG_
        return 0;  
      }
#endif
#ifdef LINUX
      status=::connect(socket, (sockaddr*) &serverSockAddr, sizeof(serverSockAddr));
      if (status < 0)
      {
		  _LOG << "Error: Could not connect to server." LOG_
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
#ifdef LINUX
        status=::close(socket);
        if (status < 0)
        {
          _CL_LOG << "ERROR: closesocket unsuccessful, try close." LOG_;
			status = ::close(socket);
			
          return 0;
        }
#endif
#ifdef WINDOWS
	status=::closesocket(socket);
#endif
	lbSockState = LB_SOCK_CLOSED;
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
    status=::listen(socket, 1);
    if (status == SOCKET_ERROR)
      _LOG << "lbSocket::listen(): ERROR: listen unsuccessful" LOG_
#endif
#ifdef LINUX
    status=::listen(socket, 1);
    if (status < 0)
      _LOG << "lbSocket::listen(): ERROR: listen unsuccessful" LOG_
#endif


    return 1;
}
/*...e*/
/*...slbSocket\58\\58\accept\40\lbSocket\42\\38\ s\41\:0:*/
lb_I_Socket* lbSocket::accept()
{
	// Mac OS X problems. Maybe http://shoe.bocks.com/net/ helps
    lb_I_Socket* s = NULL;

      if (lbSockState == LB_SOCK_CONNECTED) {
      	_LOG << "lbSocket::accept(lbSocket** s): ERROR: Illegal state for this function" LOG_
      	return NULL; //ERR_SOCKET_STATE;
      }
/*...sWINDOWS:0:*/
#ifdef WINDOWS
    /* accept the connection request when one
       is received */
	   
    SOCKET accept_socket=::accept(socket, (LPSOCKADDR) &clientSockAddr, &addrLen);
    if (accept_socket == INVALID_SOCKET) {
		_LOG << "Error while accepting on socket" LOG_
		return NULL;
	}
	
#endif
/*...e*/
/*...sLINUX:0:*/
#ifdef LINUX
    int accept_socket=::accept(socket, (sockaddr*) &clientSockAddr, (socklen_t*)&addrLen); 
    if (accept_socket == -1) {
		_LOG << "Error while accepting on socket" LOG_
// Where are the definitions?
/*		
		switch (errno) {
			case EBADF:
				_LOG << "socket is not a valid file descriptor." LOG_ 
				break;
			case ECONNABORTED: 
				_LOG << "The connection to socket has been aborted." LOG_ 
				break;
			case EFAULT: 
				_LOG << "The address parameter is not in a writable part of the user address space." LOG_ 
				break;
			case EINTR: 
				_LOG << "The accept() system call was terminated by a signal." LOG_ 
				break;
			case EINVAL: 
				_LOG << "socket is unwilling to accept connections." LOG_ 
				break;
			case EMFILE: 
				_LOG << "The per-process descriptor table is full." LOG_ 
				break;
			case ENFILE: 
				_LOG << "The system file table is full." LOG_ 
				break;
			case ENOMEM: 
				_LOG << "Insufficient memory was available to complete the operation." LOG_ 
				break;
			case ENOTSOCK: 
				_LOG << "socket references a file type other than a socket." LOG_ 
				break;
			case EOPNOTSUPP: 
				_LOG << "socket is not of type SOCK_STREAM and thus does not accept connections." LOG_ 
				break;
			case EWOULDBLOCK: 
				_LOG << "socket is marked as non-blocking and no connections are present to be accepted." LOG_ 
				break;
			default:
				_LOG << "Unknown error code." LOG_ 
				break;
		}
*/
		return NULL;
	}
#endif
/*...e*/

    if (neagleOff(accept_socket) != ERR_NONE) {
		_LOG << "Error: Can not activate TCP_NODELAY" LOG_
	}
	
    if (accept_socket == -1) {
    	_LOG << "lbSocket::accept(lbSocket** s): Created socket is invalid" LOG_
    	return NULL; //ERR_SOCKET_CLIENT_S_INVALID;
    }

    lbSocket* client_socket = new lbSocket();
	
    client_socket->setSockConnection(accept_socket); // Where are the other passed values (clientSockAddr, addrLen)
    
    // This socket can never be in connected state
    //lbSockState = LB_SOCK_CONNECTED;

    client_socket->queryInterface("lb_I_Socket", (void**) &s, __FILE__, __LINE__);

    return s;
}
/*...e*/
/*...slbSocket\58\\58\bind\40\\41\:0:*/
int lbSocket::bind()
{
#ifdef WINDOWS
    /* associate the socket with the address */
    status=::bind(socket, (LPSOCKADDR) &serverSockAddr, sizeof(serverSockAddr));
    if (status == SOCKET_ERROR)
      _LOG << "lbSocket::bind(): ERROR: bind unsuccessful" LOG_
#endif
#ifdef LINUX
    status=::bind(socket, (sockaddr*) &serverSockAddr, sizeof(serverSockAddr));
    if (status < 0)
      _LOG << "lbSocket::bind(): ERROR: bind unsuccessful" LOG_
#endif
    return 1;  
}
/*...e*/
/*...slbSocket\58\\58\socket\40\\41\:0:*/
int lbSocket::create_socket()
{
#ifdef WINDOWS
	/* create a socket */
	socket=::socket(AF_INET, SOCK_STREAM, 0);

	if (socket == INVALID_SOCKET) {
		LogWSAError("lbSocket::socket(): ERROR: socket unsuccessful");
		return 0;
	}  
	
	
	if (neagleOff(socket) != ERR_NONE) _LOG << "Error: Subsequent" LOG_
		
		
#endif
#ifdef LINUX
	socket=::socket(AF_INET, SOCK_STREAM, 0);
	
	if (socket < 0) {
		_LOG << "lbSocket::socket(): ERROR: socket unsuccessful" LOG_
	}
	
	if (neagleOff(socket) != ERR_NONE) _LOG << "Error: Subsequent" LOG_
#endif
		
		return 1;  
}
/*...e*/

/*...slbSocket\58\\58\setSockConnection\40\SOCKET s\41\:0:*/
int lbSocket::setSockConnection(SOCKET s) {
	lbSockState = LB_SOCK_CONNECTED;
	socket = s;
    clBackup = socket;
	//_isServer = 1;
	// A bug in detecting correct socket - hotfix
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
    struct hostent *hep = NULL;
	struct sockaddr_in address;
    unsigned long my_addr;
    char *p;
    hep = gethostbyname(w);

	if (hep == NULL) {
		_LOG << "Error: Could not get host name structure hostent!" LOG_
		exit(1);
	}
	
	
    if (hep)
    {
		struct in_addr a;
        _LOG << "Hostname: " << hep->h_name LOG_

		// As of: http://msdn.microsoft.com/en-us/library/windows/desktop/ms738552%28v=vs.85%29.aspx
		char **pAlias;
		for (pAlias = hep->h_aliases; *pAlias != 0; pAlias++) {
            _LOG << "Host alias: " << *pAlias LOG_
		}
		// Endless loop if _LOG is disabled!!
        //while (*hep->h_aliases)
        //    _LOG << "Host alias: " << *hep->h_aliases++ LOG_
        if (*hep->h_addr_list)
        {
            memcpy((char *) &a, *hep->h_addr_list, sizeof(a));
            _LOG << "Host address: " << inet_ntoa(a) LOG_
			return a.s_addr;
        }
    }
	_LOG << "Error: No IP address found." LOG_
	return 0;
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
#ifdef LINUX
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
#ifdef LINUX
  if (strcmp(mysockaddr, "") == 0)
  {
    if (_isServer == 1)
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
bool lbSocket::initSymbolic(char* host, char* service) {
	char msg[100];
	int serverMode = 0;
	startup();
	_LOG << "Initialize for host '" << host << "' and port '" << service << "'" LOG_

	if (strcmp(host, "localhost") == 0)
	{
		serverMode = 1;
	} else {
		_LOG << "lbSocket::initSymbolic(char* host, char* service): Socket initializing as client" LOG_
	}
	
	servent* s = getservbyname(service, NULL);

	if(s == NULL) {
		_LOG << "lbSocket::initSymbolic(char* host, char* service): No service entry found" LOG_
		return false;
	}

 	u_short port = s->s_port;
	if (serverMode == 1) {
		_LOG << "Listening on port " << ntohs(port) << "..." LOG_
	} else {
		_LOG << "Opening port " << ntohs(port) << "..." LOG_
	}

 	init((serverMode == 1) ? 0 : inet_addrFromString(host), ntohs(port)); // In the function htons is used.
	return true;
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
  }

  create_socket();

  if (_isServer == 1)
  {
    bind();
    listen();
  }
  else
  {
    connect();
  }
#endif
/*...e*/
/*...sLINUX:0:*/
#ifdef LINUX
  addrLen=sizeof(sockaddr);

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
  }

  create_socket();

  if (_isServer == 1)
  {
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) bind..." LOG_
    bind();
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) listen..." LOG_
    listen();
  }
  else
  {
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connect..." LOG_
    connect();
    _LOG << "lbSocket::init(char *mysockaddr, u_short port) connected" LOG_
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

	if ((err = send_charbuf(buf, strlen(buf)))  == ERR_NONE)
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

	if ((err = recv_charbuf(buf)) == ERR_NONE) {
		int number = atoi(buf);
		i = number;
	} else {
		_LOG << "lbSocket: Error while recieving an integer" LOG_
	}
	return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\void\42\ buf\44\ int \38\ len\41\:0:*/
lbErrCodes lbSocket::recv(void* buf, short & len) {
//_LOG << "Enter recv" LOG_
//    lbMutexLocker mlock(recvMutex);
    
    lbErrCodes err = ERR_NONE;
    int numrcv = 0;
    char* bufpos = (char*) buf;
    int lastError = 0;
	short nlen;

/*...sWINDOWS:0:*/
#ifdef WINDOWS

    if (_isServer == 1)
    {
		if (clBackup != socket) _LOG << "Error, socket variable has been changed since got from accept" LOG_

		// Get the buffer size
		numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);
		len = ntohs(nlen);
		if (numrcv != sizeof(nlen)) _LOG << "Error: Packet size not sent correctly" LOG_

		numrcv=::recv(socket, bufpos, len, NO_FLAGS_SET);
    }  
    if (_isServer == 0)
    {
		// Get the buffer size
		numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);
		len = ntohs(nlen);

		if (numrcv != sizeof(nlen)) _LOG << "Error: Packet size not sent correctly" LOG_
     
		numrcv=::recv(socket, bufpos, len, NO_FLAGS_SET);
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

      status= closesocket(socket);

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
/*...sLINUX:0:*/
#ifdef LINUX
    if (_isServer == 1)
    {
		if (clBackup != socket) _LOG << "Error, socket variable has been changed since got from accept" LOG_

		// Get the buffer size
		numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);
		len = ntohs(nlen);
		if (numrcv != sizeof(nlen)) _LOG << "Error: Packet size not sent correctly" LOG_

		numrcv=::recv(socket, bufpos, len, NO_FLAGS_SET);
    }  
    if (_isServer == 0)
    {
		// Get the buffer size
		numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);
		len = ntohs(nlen);

		if (numrcv != sizeof(nlen)) _LOG << "Error: Packet size not sent correctly" LOG_
     
		numrcv=::recv(socket, bufpos, len, NO_FLAGS_SET);
    }

    if ((numrcv == 0) || (numrcv < 0))
    {
#ifdef bla
        close();
        status=WSACleanup();
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return ERR_NONE;
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
lbErrCodes lbSocket::send(void *buf, short len)
{
	lbErrCodes err = ERR_NONE;
	int lastError = 0;
	char msg[100];
	char *bufpos = (char*) buf;
	int numsnt = 0;
	short nlen = htons(len);
	//_LOG << "Enter send" LOG_
	//lbMutexLocker mlock(sendMutex);
	
#ifdef WINDOWS
	if (_isServer == 0) {
		
		// Sende Packetgr”áe
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
			
		numsnt=::send(socket, bufpos, len, NO_FLAGS_SET);
	}
	if (_isServer == 1) {
		// Sende Packetgr”áe
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
			
		numsnt=::send(socket, bufpos, len, NO_FLAGS_SET);
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
		status=closesocket(socket);
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
/*...sLINUX:0:*/
#ifdef LINUX
	numsnt = 0;
	
	if (_isServer == 0) {
		
		// Sende Packetgr”áe
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
			
		numsnt=::send(socket, bufpos, len, NO_FLAGS_SET);
	}
	if (_isServer == 1) {
		// Sende Packetgr”áe
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
			
		numsnt=::send(socket, bufpos, len, NO_FLAGS_SET);
	}
	
    if (numsnt != len)
    {
#ifdef bla      
		close();
		status=WSACleanup();
		if (status < 0)
			cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
		return ERR_NONE;  
    }
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
    short nlen = 0; // Packet len haeder

    if (lbSockState != LB_SOCK_CONNECTED) {
      _LOG << "Error: Can not recieve on unconnected socket" LOG_
      return ERR_SOCKET_UNCONNECTED;
    }

/*...sWINDOWS:0:*/
#ifdef WINDOWS
/*...sserver:0:*/
  if (_isServer == 1) {
// Get the packet size of the next recv
    numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);

	if (numrcv != sizeof(nlen)) 
		_LOG << "Error: Packet size not recv correctly. Have got " << numrcv << " but expected " << (int) sizeof(nlen) LOG_
      
    numrcv=::recv(socket, buf, ntohs(nlen), NO_FLAGS_SET);
  }
/*...e*/
  
/*...sclient:0:*/
  if (_isServer == 0) {
    // Get the packet size of the next recv
    numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);

    if (numrcv != sizeof(nlen)) 
		_LOG << "Error: Packet size not recv correctly. Have got " << numrcv << " but expected " << (int) sizeof(nlen) LOG_
  
    numrcv=::recv(socket, buf, ntohs(nlen), NO_FLAGS_SET);
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
          status = closesocket(socket);
        }
      }
      else
        status = closesocket(socket);


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
/*...sLINUX:0:*/
#ifdef LINUX
/*...sserver:0:*/
  if (_isServer == 1) {
// Get the packet size of the next recv
    numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);

	if (numrcv != sizeof(nlen)) 
		_LOG << "Error: Packet size not recv correctly. Have got " << numrcv << " but expected " << (int) sizeof(nlen) LOG_
      
    numrcv=::recv(socket, buf, ntohs(nlen), NO_FLAGS_SET);
  }
/*...e*/
  
/*...sclient:0:*/
  if (_isServer == 0) {
    // Get the packet size of the next recv
    numrcv=::recv(socket, (char*)&nlen, sizeof(nlen), NO_FLAGS_SET);

    if (numrcv != sizeof(nlen)) 
		_LOG << "Error: Packet size not recv correctly. Have got " << numrcv << " but expected " << (int) sizeof(nlen) LOG_
  
    numrcv=::recv(socket, buf, ntohs(nlen), NO_FLAGS_SET);
  }    
/*...e*/

    if ((numrcv == 0) || (numrcv < 0))
    {
#ifdef bla
        close();
        status=WSACleanup();
        cerr << "ERROR: WSACleanup unsuccessful" << ENDL;
#endif
      return ERR_NONE;
    }
#endif
/*...e*/
    
    return err;
}
/*...e*/
/*...slbSocket\58\\58\send_charbuf\40\char \42\buf\44\ int len\41\:0:*/
lbErrCodes lbSocket::send_charbuf(char *buf, short len)
{
	lbErrCodes err = ERR_NONE;
	int lastError = 0;
	char msg[100];
	short nlen = 0;
	
	len++;
	nlen = htons(len);

#ifdef WINDOWS
	int numsnt;
	//_LOG << "Enter send" LOG_
	//   lbMutexLocker mlock(sendMutex);
	
	if (_isServer == 0) {

		// Send packet size
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
    		
		// Send packet		
		numsnt=::send(socket, buf, len, NO_FLAGS_SET);
	}
	if (_isServer == 1) {
		// Send packet size
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) _LOG << "Error: Packet size not sent correctly" LOG_
			
		// Send packet		
		numsnt=::send(socket, buf, len, NO_FLAGS_SET);
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
			status=closesocket(socket);
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
#ifdef LINUX
	int numsnt = 0;
	
	if (_isServer == 0) {
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
		
		if (numsnt != sizeof(len)) 
			_LOG << "Error: Packet size not sent correctly" LOG_

		numsnt=::send(socket, buf, len, NO_FLAGS_SET);
	}
	
	if (_isServer == 1) {
		numsnt=::send(socket, (char*)&nlen, sizeof(len), NO_FLAGS_SET);
	
		if (numsnt != sizeof(len)) 
			_LOG << "Error: Packet size not sent correctly" LOG_

		numsnt=::send(socket, buf, len, NO_FLAGS_SET);
	}	
#endif
	return err;
}
/*...e*/

/*...slbSocket\58\\58\recv\40\lb_I_Transfer_Data\42\ data\41\:0:*/
lbErrCodes lbSocket::recv(lb_I_Transfer_Data* data) {
	int i;
_LOG << "lbSocket::recv(lbTransferData & data) Not implemented!" LOG_
	if (recvInteger(i) == 1) {
	}

	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/
/*...slbSocket\58\\58\send\40\lb_I_Transfer_Data\42\ data\41\:0:*/
lbErrCodes lbSocket::send(lb_I_Transfer_Data* data) {
_LOG << "lbSocket::recv(lbTransferData & data) Not implemented!" LOG_
	return ERR_SOCKET_NOT_IMPLEMENTED;
}
/*...e*/


/*****************************************************************************
 (C)opyright 1999,      Lothar Behrens
 ***************************************************************************** 
 MODULE: socket.h
 *****************************************************************************
 Class interface to Sockets
 *****************************************************************************/

#ifndef _LB_SOCKET_
#define _LB_SOCKET_



#undef DLLEXPORT

#ifdef LB_SOCKET_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef LB_SOCKET_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#ifdef __WXGTK__
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXBUFLEN 256
#define NO_FLAGS_SET 0
#define PORT (u_short) 44965
#endif //__WXGTK__

#ifdef WINDOWS
#include <windows.h>
#include <winsock.h>

#define NO_FLAGS_SET 0

#define PORT (u_short) 44965
#define MAXBUFLEN 256
#endif //WINDOWS


class lb_Transfer_Data;

// In DLL lbTransfer DLLEXPORT must be ""

class lbSocket {
public:
        lbSocket();
        ~lbSocket() {}

	int gethostname(char* &name);

	void initSymbolic(char *host, char* service);
        void init(unsigned long mysockaddr, u_short port = PORT);
        void reinit(char *mysockaddr="");

	int isServer() { return _isServer; }

	int recvInteger(int& i);
	int sendInteger(int i);
	
	int send(void* buf, int len);		

	/**
	 * Buffer must be allocated.
	 */	
	int recv(void* buf, int & len);
		
        int recv_charbuf(char *buf);
        int send_charbuf(char *buf, int len);

		/**
		 * Send and recieve a data buffer and automatically split off to
		 * the max amount of packet size.
		 */
		int recv(lb_Transfer_Data & data);
		int send(lb_Transfer_Data & data);

        int accept();

private:

        int startup();
        int bind();
        int listen();
        int socket();
	int close();
        int connect();

	unsigned long inet_addrFromString(char* addr);


#ifdef WINDOWS

  WSADATA Data;
  SOCKADDR_IN serverSockAddr;
  SOCKADDR_IN clientSockAddr;
  SOCKET serverSocket;
  SOCKET clientSocket;
  int status;
  int addrLen; //=sizeof(SOCKADDR_IN);
  int numrcv;

  unsigned long destAddr; // for client init

	int startupflag;

#endif //WINDOWS        
#ifdef __WXGTK__
  int serverSocket;
  int clientSocket;
  struct sockaddr_in serverSockAddr;
  struct sockaddr_in clientSockAddr;
  int status;
  int addrLen; //=sizeof(SOCKADDR_IN);
  int numrcv;
  
  unsigned long destAddr; // for client init
#endif
  int _isServer;
};

#endif // _LB_SOCKET_

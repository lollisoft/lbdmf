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
            
            40235 D�sseldorf (germany)
*/
/*...e*/
/*****************************************************************************
 (C)opyright 1999,      Lothar Behrens
 ***************************************************************************** 
 MODULE: socket.h
 *****************************************************************************
 Class interface to Sockets
 *****************************************************************************/

#ifndef _LB_SOCKET_
#define _LB_SOCKET_



/*...sDLLEXPORT:0:*/
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
/*...e*/


/*...sinclude:0:*/
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
/*...e*/

enum LB_SOCK_STATE {
	LB_SOCK_UNINITIALIZED,
	LB_SOCK_CONNECTED,
	LB_SOCK_CLOSED,
	LB_SOCK_LISTENING
};

class lb_Transfer_Data;

// In DLL lbTransfer DLLEXPORT must be ""

class lbSocket {
public:
        lbSocket();
	lbSocket(const lbSocket& s);
        virtual ~lbSocket();
        
	/**
	 * Is this object valid ?
	 */
	int isValid();

	static int gethostname(char* &name);

	void initSymbolic(char *host, char* service);
        void reinit(char *mysockaddr="");

	lbErrCodes neagleOff(SOCKET s);

	int isServer() { return _isServer; }

	lbErrCodes recvInteger(int& i);
	lbErrCodes sendInteger(int i);
	
	lbErrCodes send(void* buf, int len);		

	/**
	 * Buffer must be allocated.
	 */	
	lbErrCodes recv(void* buf, int & len);
		
        lbErrCodes recv_charbuf(char *buf);
        lbErrCodes send_charbuf(char *buf, int len);

	/**
	 * Send and recieve a data buffer and automatically split off to
	 * the max amount of packet size.
	 */
	lbErrCodes recv(lb_Transfer_Data & data);
	lbErrCodes send(lb_Transfer_Data & data);


	/**
	 * Like the lbTransfer, here I must provide a lbSocket as a result.
	 * At this time you have to delete the instance after use.
	 */
        lbErrCodes accept(lbSocket *& s);

private:
	// These functions must not be locket
        int startup();
        void init(unsigned long mysockaddr, u_short port = PORT);
        int bind();
        int listen();
        int socket();
	int close();
        int connect();
        int setSockConnection(SOCKET s);

	unsigned long inet_addrFromString(char* addr);
	
	lbMutex* mutex;

	static int sockUse;

#ifdef WINDOWS

  WSADATA Data;
  SOCKADDR_IN serverSockAddr;
  SOCKADDR_IN clientSockAddr;
  SOCKET serverSocket;
  SOCKET clientSocket;
  SOCKET clBackup;
  int status;
  int addrLen; //=sizeof(SOCKADDR_IN);

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
  LB_SOCK_STATE lbSockState;
};

#endif // _LB_SOCKET_

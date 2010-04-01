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
/*****************************************************************************
 (C)opyright 1999,      Lothar Behrens
 ***************************************************************************** 
 MODULE: socket.h
 *****************************************************************************
 Class interface to Sockets
 *****************************************************************************/

#ifndef _LB_SOCKET_
#define _LB_SOCKET_



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

#ifdef OSX
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXBUFLEN 256
#define NO_FLAGS_SET 0
#define PORT (u_short) 44965

// Mac is missing the definition
typedef u_int   SOCKET;

#endif //OSX


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

class lbSocket : public lb_I_Socket {
public:
        lbSocket();
		lbSocket(const lbSocket& s);
        virtual ~lbSocket();


		DECLARE_LB_UNKNOWN()
        
	/**
	 * Is this object valid ?
	 */
	int LB_STDCALL isValid();

	char* LB_STDCALL gethostname();

	void LB_STDCALL initSymbolic(char *host, char* service);
        void LB_STDCALL reinit(char *mysockaddr="");

	int LB_STDCALL isServer() { return _isServer; }

	lbErrCodes LB_STDCALL recvInteger(int& i);
	lbErrCodes LB_STDCALL sendInteger(int i);
	
	lbErrCodes LB_STDCALL send(void* buf, int len);		

	/**
	 * Buffer must be allocated.
	 */	
	lbErrCodes LB_STDCALL recv(void* buf, int & len);
		
        lbErrCodes LB_STDCALL recv_charbuf(char *buf);
        lbErrCodes LB_STDCALL send_charbuf(char *buf, int len);

	/**
	 * Send and recieve a data buffer and automatically split off to
	 * the max amount of packet size.
	 */
	lbErrCodes LB_STDCALL recv(lb_I_Transfer_Data* data);
	lbErrCodes LB_STDCALL send(lb_I_Transfer_Data* data);


	/**
	 * Like the lbTransfer, here I must provide a lbSocket as a result.
	 * At this time you have to delete the instance after use.
	 */
        lb_I_Socket* LB_STDCALL accept();

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
	lbErrCodes LB_STDCALL neagleOff(SOCKET s);

	unsigned long inet_addrFromString(char* addr);
	
	lbMutex* mutex;

	lbCritSect* socketSection;
	
	
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
#ifdef OSX
	int serverSocket;
	int clientSocket;
	int clBackup;
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


DECLARE_FUNCTOR(instanceOflbSocket)

#endif // _LB_SOCKET_

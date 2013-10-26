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

#include <conio.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
#include <lbinclude.h>
#include <signal.h>

#include <lbInterfaces.h>

#include <socket.h>

#define LB_TRANSFER_DLL
#include <lbtransfer-module.h>
#include <transfer.h>


#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOflbTransfer, lbTransfer)
	
#ifdef __cplusplus
}
#endif


void handler(int sig) {
	_CL_LOG << "Oops" LOG_;
}

/*...sclass lbTransferModule:0:*/
class lbTransferModule {
public:
        lbTransferModule() {
                signal(SIGINT, handler);
#ifndef LINUX
#ifndef OSX
                signal(SIGBREAK, handler);
#endif
#endif
                signal(SIGABRT, handler);
                signal(SIGSEGV, handler);
                signal(SIGTERM, handler);
                signal(SIGILL, handler);
        }
        virtual ~lbTransferModule() {
                COUT << "Deinit transfer module" << ENDL;
        }
};
/*...e*/

lbTransferModule transModule; // Module initializion


/*...slbTransfer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbTransfer)
	ADD_INTERFACE(lb_I_Transfer)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbTransfer::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbTransfer::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


/*...slbTransfer\58\\58\lbTransfer\40\\41\:0:*/
lbTransfer::lbTransfer() {
	
	// Moved to init(...)
	//REQUEST(getModuleInstance(), lb_I_Socket, sock)
	laststate = 1;
	connected = 0;
	state = LB_STATE_UNINITIALIZED;

	REQUEST(getModuleInstance(), lb_I_String, hostName)
	REQUEST(getModuleInstance(), lb_I_String, portName)

}
/*...e*/
/*...slbTransfer\58\\58\\126\lbTransfer\40\\41\:0:*/
lbTransfer::~lbTransfer() {
        _CL_VERBOSE << "lbTransfer::~lbTransfer() called." LOG_
}
/*...e*/
/*...slbTransfer\58\\58\init\40\char \42\target\41\:0:*/
/**
 * A target has this format: //machine/service/...
 *
 * The machine name has to be resolved to a IP address
 * A service has to be resolved to a port number
 */
lbErrCodes lbTransfer::init(char *target, bool asServer) {
        u_short port;
        char *machine = NULL;
        char *service = NULL;
        char *subservice = NULL;

	char* pch = NULL;
		
	if (target == NULL) {
		_LOG << "Reinit with last known parameters." LOG_
		machine = hostName->charrep();
		service = portName->charrep();
	} else {
		_LOG << "lbTransfer::init(" << target << ") called." LOG_

		char* copytarget = NULL;
			
		copytarget = strdup(target);
			
		pch = strtok(copytarget, "/");

		if (pch != NULL) {
			machine = strdup(pch);
			pch = strtok(NULL, "/");
		}

		if (pch != NULL) {
			service = strdup(pch);
			pch = strtok(NULL, "/");
		} else {
			service = strdup(target);
		}

		//if (pch != NULL) {
		//	subservice = strdup(pch);
		//	pch = strtok(NULL, "/");
		//}
			
		if (service == NULL) {
			_LOG << "lbTransfer::init(char *target): Service name couldn't retrieved from target string!" LOG_
			// Handle error
		}
	
		if (machine == NULL) {
			_LOG << "lbTransfer::init(char *target): Machine name couldn't retrieved from target string!" LOG_
		}
			
		*hostName = machine;
		*portName = service;
	}
		

        if (subservice == NULL) {
		/**
		 * machine is the computername. Service is the name of a service
		 * mapped to a port.
		 */
		
		if (sock != NULL) {
			_LOG << "Error: The socket instance must be NULL before calling init(...)." LOG_
		}
		
		REQUEST(getModuleInstance(), lb_I_Socket, sock)
				 
		if (!sock->initSymbolic(machine, service)) {
			_LOG << "Initialization of socket failed." LOG_
			return ERR_SOCKET_INIT;
		}
        } else {
                _LOG << "Subservices currently not supported" LOG_
                // Handle special cases with subservices
        }
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbTransfer::close() {
	if (sock != NULL) {
		sock->close();
	}
}

int lbTransfer::isValid() {
        return sock->isValid();
}

int lbTransfer::isConnected() {
        return connected;
}

/*...sdata types:0:*/
/*
LB_INT,
LB_CHAR,
LB_SHORT,
LB_LONG,
LB_USHORT,
LB_ULONG,
LB_VOID,

LB_OBJECT,
*/
/*...e*/

/*...schar\42\ getStringFromEnumeration\40\LB_PACKET_TYPE type\41\:0:*/
char* getStringFromEnumeration(LB_PACKET_TYPE type) {
        if (type == PACKET_LB_CHAR) return "PACKET_LB_CHAR";
        if (type == PACKET_LB_INT) return "PACKET_LB_INT";
        if (type == PACKET_LB_SHORT) return "PACKET_LB_SHORT";
        if (type == PACKET_LB_LONG) return "PACKET_LB_LONG";
        if (type == PACKET_LB_USHORT) return "PACKET_LB_USHORT";
        if (type == PACKET_LB_ULONG) return "PACKET_LB_ULONG";
        if (type == PACKET_LB_VOID) return "PACKET_LB_VOID";
        if (type == PACKET_LB_OBJECT) return "PACKET_LB_OBJECT";
        return "PACKET_LB_INVALIDTYPE";
}
/*...e*/

/*...sLB_PACKET_TYPE getEnumerationFromString\40\char\42\ typeAsString\41\:0:*/
LB_PACKET_TYPE getEnumerationFromString(char* typeAsString) {
	if (typeAsString == NULL) {
        	return PACKET_LB_INVALIDTYPE;
	}
	if (strcmp(typeAsString, "PACKET_LB_CHAR") == 0) return PACKET_LB_CHAR;
        if (strcmp(typeAsString, "PACKET_LB_INT") == 0) return PACKET_LB_INT;
        if (strcmp(typeAsString, "PACKET_LB_SHORT") == 0) return PACKET_LB_SHORT;
        if (strcmp(typeAsString, "PACKET_LB_LONG") == 0) return PACKET_LB_LONG;
        if (strcmp(typeAsString, "PACKET_LB_USHORT") == 0) return PACKET_LB_USHORT;
        if (strcmp(typeAsString, "PACKET_LB_ULONG") == 0) return PACKET_LB_ULONG;
        if (strcmp(typeAsString, "PACKET_LB_VOID") == 0) return PACKET_LB_VOID;
        if (strcmp(typeAsString, "PACKET_LB_OBJECT") == 0) return PACKET_LB_OBJECT;
        return PACKET_LB_INVALIDTYPE;
}
/*...e*/

/*...sProtocol helper:0:*/
/*...slbTransfer\58\\58\resetServerStateMachine\40\\41\:0:*/
int lbTransfer::resetServerStateMachine() {
        char* buf = NULL;
        
        if (sock->send_charbuf("reset", strlen("reset")+1) == 0) {
                _LOG << "lbSocket: Panic, can't send reset comando to server" LOG_
                return 0;
        }

        if (sock->recv_charbuf(buf) == 0) { 
                _LOG << "lbSocket: Panic, can't reset server's statemachine" LOG_
		if (buf != NULL)
			free(buf);
                return 0;
        }

        if (strcmp(buf, "ok") != 0) {
                _LOG << "lbSocket: Server state error, reset comando don't be answered with 'ok'" LOG_
		if (buf != NULL)
			free(buf);
                return 0;
        }
	if (buf != NULL)
		free(buf);
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\sendDatatype\40\char\42\ type\41\:0:*/
lbErrCodes lbTransfer::sendDatatype(char* type) {
        if (sock->send_charbuf(type, strlen(type)+1) != ERR_NONE) {
                _LOG << "lbTransfer::sendDatatype(char* type): Failed to send packet type information" LOG_
                return ERR_TRANSFER_SEND_DATATYPE;
        }
        return ERR_NONE;
}
/*...e*/
/*...slbTransfer\58\\58\waitforAnswer\40\char\42\ answer\41\:0:*/
int lbTransfer::waitforAnswer(char* answer) {
        char* buf = NULL;

        if (sock->recv_charbuf(buf) != ERR_NONE)  {
		_LOGERROR << "lbSocket: Failed to get any answer" LOG_
		if (buf != NULL)
			free(buf);
		return 0;
        }

        if (strcmp(buf, "Protokol error") == 0) {
		_LOGERROR << "Got an error in protokol flow" LOG_
	}
		
        if (strcmp(buf, answer) != 0) {
                _LOGERROR << "lbSocket: Incorrect answer '" << buf << "'." LOG_
                //resetServerStateMachine();
		if (buf != NULL)
			free(buf);
                return 0;
        }
	if (buf != NULL)
		free(buf);
        return 1;
}
/*...e*/
/*...slbTransfer\58\\58\sendString\40\char\42\ type\41\:0:*/
int lbTransfer::sendString(char* type) {
        if (sock->send_charbuf(type, strlen(type)) != ERR_NONE) {
                _LOG << "lbTransfer::sendString(char* type): Failed to send simple string" LOG_
                return 0;
        }
        return 1;
}
/*...e*/
/*...slbTransfer\58\\58\sendDataCount\40\int c\41\:0:*/
int lbTransfer::sendDataCount(int c) {
        if (sendString("DataCount") == 0) return 0;

        if (waitforAnswer("ok") == 0) return 0;

        if (sock->sendInteger(c) != ERR_NONE) {
                _LOGERROR << "lbTransfer: Could not send integer value" LOG_
                resetServerStateMachine();
                return 0;
        }

        if (waitforAnswer("Datacount ok") == 0) {
				_LOGERROR << "lbTransfer::sendDataCount(int c): Error, answer not got" LOG_
                return 0;
        }
        return 1;       
}
/*...e*/
/*...slbTransfer\58\\58\sendBuffer\40\byte\42\ buf\44\ int len\41\:0:*/
int lbTransfer::sendBuffer(byte* buf, int len) {
        if (sendString("Datablock") == 0) {
                _LOGERROR << "lbTransfer: Could not send 'Datablock' message" LOG_
                resetServerStateMachine();
                return 0;
        }

        if (waitforAnswer("ok") == 0) {
				_LOGERROR << "Could not get answer 'ok' after sending 'Datablock'" LOG_
                return 0;
        }

/*...sSend buffersize:8:*/
        // Get the size of the packet for memory allocation (if possible)
	if (sock->sendInteger(len) != ERR_NONE) {
		_LOGERROR << "Socket send integer failed." LOG_
		return 0;       
	}
	
	if (waitforAnswer("ok") == 0) {
		_LOGERROR << "waitforAnswer('ok') failed." LOG_
		return 0;
	}
/*...e*/
        int peaces = len / MAXBUFLEN;
        byte * currbufferpos = buf;
        

        // target knows multiple packets from buffersize > MAXBUFLEN !
        for (int i = 0; i < peaces; i++) {

			if (sock->send((void* )currbufferpos, MAXBUFLEN) != ERR_NONE) 
                {
                        _LOGERROR << "lbTransfer::sendBuffer(byte* buf, int len) failed" LOG_
                        return 0;
                }
                currbufferpos = currbufferpos + MAXBUFLEN;
                if (waitforAnswer("Peace ok") == 0) 
                {
                        _LOGERROR << "lbTransfer::sendBuffer(byte* buf, int len) waiting for 'Peace ok' failed" LOG_
                        return 0;
                }
        }
        
        // Send remaining

        //currbufferpos = currbufferpos + (len-peaces*MAXBUFLEN);

        if (sock->send((void* )currbufferpos, (len-peaces*MAXBUFLEN)) != ERR_NONE) 
        {
			_LOGERROR << "Send buffer part failed" LOG_
			return 0;
        }

        if (waitforAnswer("Buffer ok") == 0) {
			_LOGERROR << "Got incorrect answer" LOG_
			return 0;
        }

        return 1;
}

/*...e*/

/*...slbTransfer\58\\58\waitForString\40\char\42\ \38\ string\41\:0:*/
int lbTransfer::waitForString(char* & string) {
	char* buf = NULL;

	if (sock->recv_charbuf(buf) != ERR_NONE)
	{
		_LOGERROR << "lbSocket: Failed to get any data while waiting for a string" LOG_
		if (buf != NULL)
			free(buf);
		return 0;
	}  
	string = strdup(buf);
        
	if (buf != NULL)
		free(buf);
	return 1;  
}
/*...e*/
/*...slbTransfer\58\\58\waitForBuffer\40\byte \42\ \38\ buffer\44\ int \38\ len\41\:0:*/
int lbTransfer::waitForBuffer(byte * & buffer, int & len) {
        int buflen;     

        if (waitforAnswer("Datablock") == 0) {
                _LOGERROR << "Could not get 'Datablock' identifer" LOG_
                return 0;
        }

        if (sendString("ok") == 0) {
                _LOGERROR << "lbTransfer::waitForBuffer(...) Error: Sending 'ok' after recieving 'Datablock'" LOG_
                return 0;
        }

/*...sGet buffersize:8:*/
        // Get the size of the packet for memory allocation (if possible)
        if (sock->recvInteger(buflen) != ERR_NONE) {
                _LOGERROR << "lbTransfer::waitForBuffer(...) Error: Could not get buffer size" LOG_
                return 0;       
        }

	if (sendString("ok") == 0) {
                _LOGERROR << "lbTransfer::waitForBuffer(...) Error: Could not send 'ok' after recieving buffer size" LOG_
                return 0;
        }
/*...e*/
        len = buflen;

        buffer = (byte*) malloc(buflen);

        int peaces = buflen / MAXBUFLEN;
        byte * currbufferpos = buffer;

        // target knows multiple packets from buffersize > MAXBUFLEN !

	/*...sRecieving all packets except the last:0:*/
        for (int i = 0; i < peaces; i++) {
                short gotBuflen = MAXBUFLEN;
                if (sock->recv((void* )currbufferpos, gotBuflen) != ERR_NONE) {
                        _LOGERROR << "sock->recv((void* )currbufferpos, gotBuflen) failed" LOG_
                        return 0;
                }

                currbufferpos = currbufferpos + MAXBUFLEN;
				
		
		
                if (sendString("Peace ok") == 0) {
                        _LOGERROR << "Cannot send answer 'Peace ok'" LOG_
                        return 0;
                }
        }
/*...e*/
        
        // Recv remaining
//      currbufferpos = currbufferpos + (buflen-peaces*MAXBUFLEN);
        short wanted_peace_size = (buflen-peaces*MAXBUFLEN);
        
        /* // Done in recv self
        if (sock->isValid() == 0) {
                _LOG << "lbTransfer::waitForBuffer(...) Error: Can't get data from an invalid socket!" LOG_
                return 0;
        }
        */
        
        if (sock->recv((void* )currbufferpos, wanted_peace_size) != ERR_NONE) {
                _LOGERROR << "Can't get buffer" LOG_
                return 0;
        }

        if (sendString("Buffer ok") == 0) {
                _LOGERROR << "Can't send back 'ok'" LOG_
                return 0;
        }

        return 1;       
}
/*...e*/


/*...slbTransfer\58\\58\waitForDataCount\40\int \38\ c\41\:0:*/
int lbTransfer::waitForDataCount(int & c) {
	if (waitforAnswer("DataCount") == 0) {
		_LOGERROR << "waitforAnswer('DataCount') failed" LOG_
		return 0;
	}
	if (sendString("ok") == 0) {
		_LOGERROR << "sendString('ok') failed" LOG_
		return 0;
	}
	if (sock->recvInteger(c) != ERR_NONE) {
		_LOGERROR << "recvInteger(c) failed" LOG_
		return 0;
	}
	if (sendString("Datacount ok") == 0) {
		_LOGERROR << "sendString('Datacount ok') failed" LOG_
		return 0;
	}
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\waitForDatatype\40\char\42\ \38\ result\41\:0:*/
lbErrCodes lbTransfer::waitForDatatype(char* &result) {
	char* buf = NULL;
	lbErrCodes err = ERR_NONE;
        
	if ((err = sock->recv_charbuf(buf)) != ERR_NONE)
	{
		switch (err) {
			case ERR_SOCKET_CLOSED:
				err = ERR_TRANSFER_ENDED;
				break;
			default:
				_LOG << "lbSocket: Failed to get any datatype" LOG_
				err = ERR_TRANSFER_FAILED;
		}
		result = '\0';
	}
	else
		result = strdup(buf);

	if (buf != NULL)
		free(buf);
	
        return err;
}
/*...e*/
/*...e*/

int lbTransfer::gethostname(lb_I_String* name) {
	if (name != NULL)
		*name = sock->gethostname();
	return 0;
}

/*...slbTransfer\58\\58\getLastError\40\\41\:0:*/
lbErrCodes lbTransfer::getLastError() {
        return lastError;
}
/*...e*/


/*...slbTransfer\58\\58\setSockConnection\40\lb_I_Socket\42\ s\41\:0:*/
int lbTransfer::setSockConnection(lb_I_Socket* s) {
        state = LB_STATE_CONNECTED;
		if (sock != NULL) {
			_LOG << "lbTransfer::setSockConnection() overwrites another socket instance!" LOG_
		}
        sock = s;
        connected = 1;  
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\accept\40\\41\:0:*/
lb_I_Transfer* lbTransfer::accept() {
	if (state == LB_STATE_CONNECTED) {
		_LOG << "lbTransfer::accept(lbTransfer*& t) State error: Accept can not be called!" LOG_
		return NULL;
	}
    
    _CL_LOG << "Waiting for a connection..." LOG_
	UAP(lb_I_Socket, s)

	if (sock == NULL) {
		_LOG << "lbTransfer::accept(lbTransfer*& t) Error: Internal sock instance points to NULL!" LOG_
		return NULL;
	}

	s = sock->accept();
	if (s != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_Transfer, t)
                 
		// t cannot call accept or those functions that
		// are outside of connected state
                
		s++;// accept does not use UAP
		t->setSockConnection(s.getPtr());
		t++;
		return t.getPtr();
	} else {
		_LOG << "lbTransfer::accept(lb_I_Transfer* t): Error, failed to accept on serversocket" LOG_
		return NULL;
	}
}
/*...e*/

/*...slbTransfer\58\\58\operator\60\\60\ \40\lb_I_Transfer_Data\42\ req\41\:0:*/
void lbTransfer::operator<< (lb_I_Transfer_Data* req) {
        if (laststate == 1)
                laststate = send(req);
        else
                _LOG << "Transfer: There was a previous error. Could not send any more" LOG_
}
/*...e*/
/*...slbTransfer\58\\58\operator\62\\62\ \40\lb_I_Transfer_Data\42\ res\41\:0:*/
void lbTransfer::operator>> (lb_I_Transfer_Data* res) {
        if (laststate == 1) {
                laststate = recv(res);
                if (laststate != 1) 
					_LOG << "Error in recv, here should throw be the best" LOG_
        }
        else
                _LOG << "Transfer: There was a previous error. Could not recieve any more" LOG_
}
/*...e*/

/*...slbTransfer\58\\58\send\40\lb_I_Transfer_Data\42\ data\41\:0:*/
int lbTransfer::send(lb_I_Transfer_Data* data) {
	lastError = ERR_NONE;

	if (!data->isServerSide()) {
/*...sClient sends internal data:0:*/
		DWORD cP = data->getClientPid();
		DWORD cT = data->getClientTid();
		char* h  = data->getClientHost();
		_LOG << "Client sends the additional data (" << h << ", Pid=" << (int) cP << ", Tid=" << (int) cT LOG_

		if (sendBuffer((byte*) &cP, sizeof(DWORD)) == 0) {
			_LOGERROR << "lbTransfer::send(...) Error: Could not send internal pid" LOG_
			return 0;
		}
		if (waitforAnswer("Got buffer") == 0) {
			_LOGERROR << "Could not get answer 'Got buffer'" LOG_
			return 0;
		}
		if (sendBuffer((byte*) &cT, sizeof(DWORD)) == 0) {
			_LOGERROR << "lbTransfer::send(...) Error: Could not send internal tid" LOG_
			return 0;
		}
		if (waitforAnswer("Got buffer") == 0) {
			_LOGERROR << "Could not get answer 'Got buffer'" LOG_
			return 0;
		}
		if (sendString(h) == 0) {
			_LOGERROR << "lbTransfer::send(...) Error: Could not send internal client hostname" LOG_
			return 0;
		}       
        if (waitforAnswer("ok") == 0) {
			_LOGERROR << "lbTransfer::send(...) Error: Did not get an ok." LOG_
			return 0;
		}
/*...e*/
	}

	if (sendDatatype("lbTransferData") != ERR_NONE) {
		_LOGERROR << "Failed to send data type information" LOG_
		lastError = ERR_TRANSFER_FAILED;
		return 0;
	}

	if (waitforAnswer("Datatype ok") == 0) {
		_LOGERROR << "Failed to wait for Datatype ok" LOG_
		lastError = ERR_TRANSFER_FAILED;
		return 0;
	}


	if (sendDataCount(data->getPacketCount()) == 0) {
		_LOGERROR << "Failed to send number of protocol packets" LOG_
		lastError = ERR_TRANSFER_FAILED;
		return 0;
	}

	data->resetPositionCount(); // Ensure starting an iteration
	while (data->hasMorePackets() == 1) {
		pLB_TRANSFER_DATA pData = data->getNextPacket();

		
		if (pData == NULL) {
			lastError = ERR_TRANSFER_NULLPTR;
			_LOGERROR << "lbTransfer::send(const lbTransferData & data): Error, can't send buffer. Null pointer exception." LOG_
			return 0;
		} else {
			if (sendString(getStringFromEnumeration(pData->packet_type)) == 0) {
				_LOGERROR << "getStringFromEnumeration() failed." LOG_
				lastError = ERR_TRANSFER_FAILED;
				return 0;
			}
			if (waitforAnswer("ok") == 0) {
				_LOGERROR << "waitforAnswer('ok') failed." LOG_
				lastError = ERR_TRANSFER_FAILED;
				return 0;
			}
			if (sendBuffer((byte*) &(pData->data), pData->packet_size) == 0) {
				_LOGERROR << "lbTransfer: Could not send data buffer" LOG_
				lastError = ERR_TRANSFER_FAILED;
				//resetServerStateMachine();
				return 0;
			}
			if (waitforAnswer("Got buffer") == 0) {
				_LOGERROR << "Could not get answer 'Got buffer'" LOG_
				lastError = ERR_TRANSFER_FAILED;
				return 0;
			}
		}
	}

	return 1;
}
/*...e*/
/*...slbTransfer\58\\58\recv\40\lb_I_Transfer_Data\42\ data\41\:0:*/
int lbTransfer::recv(lb_I_Transfer_Data* data) {
	char* result = NULL;
	int len;
	void* buf = NULL;
	lbErrCodes err = ERR_NONE;

	if (data->isServerSide()) {
/*...sServerside recieves internal data :16:*/

        if (waitForBuffer((byte*&) buf, len) == 0) {
                _LOGERROR << "lbTransfer::recv(...) Error: Could not recv internal pid" LOG_
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        char* h;

		data->setClientPid(*(DWORD*)buf);
        delete buf;

        if (sendString("Got buffer") == 0) {
                _LOGERROR << "Could not get answer 'Got buffer'" LOG_
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }
        
        if (waitForBuffer((byte*&) buf, len) == 0) {
                _LOGERROR << "lbTransfer::send(...) Error: Could not send internal tid" LOG_
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }
        
        data->setClientTid(*(DWORD*)buf);
        delete buf;

        if (sendString("Got buffer") == 0) {
                _LOGERROR << "Could not get answer 'Got buffer'" LOG_
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        if (waitForString(h) == 0) {
                _LOGERROR << "lbTransfer::send(...) Error: Could not send internal client hostname" LOG_
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }       
        data->setClientHost(h);

        if (sendString("ok") == 0) {
			_LOGERROR << "lbTransfer::send(...) Error: Could not send 'ok'." LOG_
			lastError = ERR_TRANSFER_FAILED;
			return 0;
        }

/*...e*/
	}

	if ((err = waitForDatatype(result)) == ERR_NONE) {
		if (strcmp(result, "lbTransferData") == 0)
		{// Got correct datatype
/*...sget it:16:*/
			int count = 0;
			lbTransferData temp;
			int len;
            
			if (sendString("Datatype ok") == 0) {
				lastError = ERR_TRANSFER_FAILED;
				return 0;
			}
           
/*...swaitForDataCount:28:*/
			if (waitForDataCount(count) == 0) {
				_LOGERROR << "waitForDataCount(count) Error: No packet count" LOG_
				fprintf(stderr, "Waiting for packet count: Results in an error\n");
				lastError = ERR_TRANSFER_FAILED;
				return 0;
			}
/*...e*/
/*...sGet all packets:28:*/
            while (count != 0) {
                count--;
                int ptypelen = sizeof(LB_PACKET_TYPE);
                LB_PACKET_TYPE type;
                char* typeAsString = NULL;
                if (waitForString(typeAsString) == 0) {
                        _LOGERROR << "lbTransfer::send(...) Error: Could not get packet type information!" LOG_
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;
                }
                type = getEnumerationFromString(typeAsString);
                
                if (type != PACKET_LB_INVALIDTYPE) {
                        if (sendString("ok") == 0) {
								_LOGERROR << "lbTransfer::send(...) Error: Could not send 'ok'!" LOG_
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
                } else { 
                        if (sendString("Protokol error") == 0) {
							_LOGERROR << "Failed to send 'Protocol error'!" LOG_
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
                }
                if (waitForBuffer((byte* &) buf, len) == 0) {
                        _LOGERROR << "waitForBuffer((byte* &) buf, len) Error: Waiting for buffer failed!" LOG_
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;       
                }

                data->add(buf, len, type);
                if (sendString("Got buffer") == 0) {
                        _LOGERROR << "Could not get answer 'Got buffer'" LOG_
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;
                }
            }

/*...e*/
/*...e*/
          } else {
                lastError = ERR_TRANSFER_FAILED;
                _LOGERROR << "lbTransfer::recv(...) Error: Currently only 'lbTransferData' is supported" LOG_
                return 0;
          }
        } else {
                lastError = ERR_TRANSFER_FAILED;
                _LOGERROR << "lbTransfer::recv(lbTransferData & data): Could not get any data type" LOG_
                return 0;
        }

        return 1;
}
/*...e*/
/*...e*/

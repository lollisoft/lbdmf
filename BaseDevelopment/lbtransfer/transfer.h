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
            
            40235 Duesseldorf (germany)
*/
/*...e*/
#ifndef LB_TRANSFER
#define LB_TRANSFER

/*...sDLLEXPORT:0:*/
#undef DLLEXPORT


#ifdef MODULE_EXPORT

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif

#ifndef MODULE_EXPORT

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

#include <lbInterfaces-sub-transfer.h>

class lbComponentDictionary;
class lbSocket;

enum LB_TRANSFER_STATE {
	LB_STATE_UNINITIALIZED,
	LB_STATE_CONNECTED,
};

/*...slbTransferDataObject:0:*/
/**
 * This class is needed for the container
 */
class lbTransferDataObject : public lbObject {
public:
	lbTransferDataObject();
	virtual ~lbTransferDataObject();

	void setData(pLB_TRANSFER_DATA pData);
	pLB_TRANSFER_DATA getData() const;

private:
	void setType();
	lbObject* clone() const;

	pLB_TRANSFER_DATA data;
};
/*...e*/
/*...slb_Transfer_Data:0:*/
/**
 * This class represents the buffer to be send over a socket. A object of type lbObject
 * should be able to created over a constructor with a parameter of this type. 
 */
class DLLEXPORT lb_Transfer_Data : public
					lb_I_Transfer_Data
{

public:
	lb_Transfer_Data(int _serverside=0);
	virtual ~lb_Transfer_Data();
        
        lb_Transfer_Data(const lb_I_Transfer_Data & t);

	lb_I_Transfer_Data& assign(lb_I_Transfer_Data const & t);

	/**
	 * Packet functions to form packets fit to internet packet size.
	 * Use hasMorePackets() for the while 
	 */

	int hasMorePackets() const;
	pLB_TRANSFER_DATA getNextPacket() const;

	int getPacketCount() const;
	LB_PACKET_TYPE getNextPacketType();

	int addPacket(pLB_TRANSFER_DATA data);

	int resetPositionCount();
	int incrementPosition();
	int getPacketType(LB_PACKET_TYPE & type);

	int deleteAll();

/*...ssetters:8:*/
	/**
	 * Data member operations
	 */

	void add(int i);
	void add(const char* c);
	void add(short s);
	void add(long l);
	void add(unsigned short us);
	void add(unsigned long ul);
	void add(const void* buf, int len);
/*...e*/

/*...sgetters:8:*/
	lbErrCodes get(int& i);
	lbErrCodes get(char* & c);
	lbErrCodes get(short & s);
	lbErrCodes get(long & l);
	lbErrCodes get(unsigned short & us);
	lbErrCodes get(unsigned long & ul);

	lbErrCodes get(void* & v, int & len);
/*...e*/
	
	/**
	 * The really function who is adding
	 */
	void add(const void* buf, int len, LB_PACKET_TYPE type);


	/**
	 * Use dictionary yet
	 */
	lbComponentDictionary* elements;
	lbComponentDictionary* elementscopy;
	
	int packet_count;
	int currentPos;
	int ref;
public:	
	char *clientHost;
	DWORD clientPid;
	DWORD clientTid;
	int serverside;
};
/*...e*/
/*...slbTransfer:0:*/
class DLLEXPORT lbTransfer {
public:
	lbTransfer();
	virtual ~lbTransfer();

	/**
	 * The target parameter is build up like an internet address.
	 * Exsample: //anakin/service/subservice
	 */
	void init(char *target);

	int isConnected();

	/**
	 * Got a connection...
	 */
	int accept(lbTransfer*& t);

	void operator<< (const lb_Transfer_Data& req);
	void operator>> (lb_Transfer_Data& res);

	/**
	 * This function allows checking for validness of this instance
	 */
	int isValid();

	int gethostname(char* &name);
	
	lbErrCodes getLastError();
private:
	lbTransfer(lbTransfer* t);

	int recv(lb_Transfer_Data & data);
	int send(const lb_Transfer_Data & data);

	int setSockConnection(lbSocket* s);


	int resetServerStateMachine();
	lbErrCodes sendDatatype(char* type);
	int waitforAnswer(char* answer);
	int sendDataCount(int c);
	int sendBuffer(byte* buf, int len);
	int sendString(char* type);
	int waitForString(char* & string);
	int waitForDataCount(int & c);
	lbErrCodes waitForDatatype(char* & result);
	int waitForBuffer(byte * & buffer, int & len);

	lbSocket* sock;
	int laststate;
	int connected;
	
	LB_TRANSFER_STATE state;
	
	lbErrCodes lastError;
	
	/**
	 * This authentification parameters are initialized once per
	 * thread. Then it is used when ever data is transferred.
	 */
	char AuthUser[100];
	char AuthPass[100];
};
/*...e*/

#endif // LB_TRANSFER

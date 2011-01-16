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

IMPLEMENT_FUNCTOR(instanceOflbTransferData, lbTransferData)
	
#ifdef __cplusplus
}
#endif            

/*...slbTransferData:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbTransferData)
	ADD_INTERFACE(lb_I_Transfer_Data)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbTransferData::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Transfer_Data, transferCopy)
	QI(uk, lb_I_Transfer_Data, transferCopy)
	_CL_LOG << "lbErrCodes LB_STDCALL lbTransferData::setData() called." LOG_
	if (transferCopy != NULL) {
		assign(*transferCopy);
	}
	
	return ERR_NOT_IMPLEMENTED;
}

lbTransferData::lbTransferData() {
	ref = STARTREF;
}

void LB_STDCALL lbTransferData::setServerSide(int _serverside) {
	lbErrCodes err = ERR_NONE;
	REQUEST(getModuleInstance(), lb_I_Container, elements)
	REQUEST(getModuleInstance(), lb_I_Integer, intKey)
	REQUEST(getModuleInstance(), lb_I_String, clientHost)

	QI(intKey, lb_I_KeyBase, key)
	
	//elements = new lbComponentDictionary();
	//*elementscopy = elements->clone(__FILE__, __LINE__);

	elements->deleteAll();
        
	resetPositionCount();
	packet_count = 0;
	ref = 0;
	serverside=_serverside;

	UAP_REQUEST(getModuleInstance(), lb_I_Socket, s)

	*clientHost = s->gethostname();
	clientPid = lbGetCurrentProcessId();
	clientTid = lbGetCurrentThreadId();
}

/*...slbTransferData\58\\58\\126\lbTransferData\40\\41\:0:*/
lbTransferData::~lbTransferData() {
        if (elements != NULL) {
                //delete elements;
        }

        //if (clientHost != NULL) free(clientHost);
}
/*...e*/

/*...slbTransferData\58\\58\lbTransferData\40\const lbTransferData \38\ t\41\:0:*/
lbTransferData::lbTransferData(const lb_I_Transfer_Data & t) {
        elements = ((lbTransferData&) t).elements;
//        elementscopy = ((lbTransferData&) t).elementscopy;

        packet_count = ((lbTransferData&) t).packet_count;
        currentPos = ((lbTransferData&) t).currentPos;

        if (((lbTransferData&) t).clientHost != NULL)
                *clientHost = t.getClientHost();
        else
                *clientHost = "No host given!";

        clientPid = t.getClientPid();
        clientTid = t.getClientTid();
        serverside = 0;
        if (t.isServerSide()) serverside = 1;
        ref++;
}
/*...e*/

/*...slbTransferData\58\\58\assign \40\const lb_I_Transfer_Data \38\ t\41\:0:*/
lb_I_Transfer_Data& lbTransferData::assign (const lb_I_Transfer_Data & t) {
	_LOG << "lb_I_Transfer_Data& lbTransferData::assign (const lb_I_Transfer_Data & t) called." LOG_
	elements = ((lbTransferData&) t).elements;
	//elementscopy = ((lbTransferData&) t).elementscopy;

	packet_count = t.getPacketCount();
	currentPos = t.getCurrentPos();

	if (t.getClientHost() != NULL)
		*clientHost = t.getClientHost();
	else
		*clientHost = "No host given!";

	clientPid = t.getClientPid();
	clientTid = t.getClientTid();
	serverside = 0;
	if (t.isServerSide()) serverside = 1;
	
	resetPositionCount();
	
	while (hasMorePackets() == 1) {
		pLB_TRANSFER_DATA pData = getNextPacket();
		_LOG << "Copied a protocol packet of type " << getStringFromEnumeration(pData->packet_type) LOG_
	}	
	resetPositionCount();
	
	return *this;
}
/*...e*/

/*...slbTransferData\58\\58\hasMorePackets\40\\41\:0:*/
int lbTransferData::hasMorePackets() const {
        return elements->hasMoreElements();
}
/*...e*/
/*...slbTransferData\58\\58\addPacket\40\pLB_TRANSFER_DATA mydata\41\:0:*/
int lbTransferData::addPacket(pLB_TRANSFER_DATA data) {
        return 0;
}
/*...e*/
/*...slbTransferData\58\\58\getNextPacket\40\\41\:0:*/
pLB_TRANSFER_DATA lbTransferData::getNextPacket() const {
	lbErrCodes err = ERR_NONE;
	char msg[100] = "";
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Transfer_DataObject, o)
	uk = elements->nextElement();
	QI(uk, lb_I_Transfer_DataObject, o)       
	if (o->getTransferData() == NULL)
		_LOG << "lbTransferDataObject contains no data!" LOG_

	//_LOG << "pLB_TRANSFER_DATA lbTransferData::getNextPacket() returns a packet of type " << getStringFromEnumeration(o->getTransferData()->packet_type) LOG_
		
	return o->getTransferData();
}
/*...e*/
int lbTransferData::getCurrentPos() const {
	return currentPos;
}
/*...slbTransferData\58\\58\getPacketCount\40\\41\:0:*/
int lbTransferData::getPacketCount() const {
	return packet_count;
}
/*...e*/

/*...slbTransferData\58\\58\resetPositionCount\40\\41\:0:*/
int lbTransferData::resetPositionCount() {
	currentPos = 1;
	elements->finishIteration();
	return 1;
}
/*...e*/
/*...slbTransferData\58\\58\incrementPosition\40\\41\:0:*/
int lbTransferData::incrementPosition() {
	currentPos++;
	return (currentPos > packet_count) ? 0 : 1;
}
/*...e*/
/*...slbTransferData\58\\58\getPacketType\40\LB_PACKET_TYPE \38\ type\41\:0:*/
int lbTransferData::getPacketType(LB_PACKET_TYPE & type) {
	lbErrCodes err = ERR_NONE;
	char buf[100] = "";
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey)
	UAP(lb_I_KeyBase, k)
	integerKey->setData(currentPos);
	QI(integerKey, lb_I_KeyBase, k)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Transfer_DataObject, o)
        
	uk = elements->getElement(&k);
	if (uk == NULL) {
		_LOG << "Error: Failed to get element " << currentPos << ". Have " << elements->Count() << " elements." LOG_
		return 0;
	}
	
	QI(uk, lb_I_Transfer_DataObject, o)
        
	if (o == NULL) 
		_LOG << "lbTransferData::getPacketType() Error, can't get packet type from a NULL pointer object" LOG_
        
	type = o->getTransferData()->packet_type;
        
	if (strcmp(getStringFromEnumeration(type), "PACKET_LB_INVALIDTYPE") == 0)
		_LOG << "lbTransferData::getPacketType() got a type of " << type LOG_
		
	/// \todo Why yet ever 1 ?
	return 1;
}
/*...e*/
LB_PACKET_TYPE lbTransferData::getNextPacketType() {
	return PACKET_LB_INVALIDTYPE;
}
/*...slbTransferData\58\\58\deleteAll\40\\41\:0:*/
int lbTransferData::deleteAll() {
        int rc = 0;
        if (elements != NULL) {
                elements->deleteAll();
                rc = 1;
        } else {
                _LOG << "lbTransferData::deleteAll() failed because elements is a NULL pointer!" LOG_
        }

        resetPositionCount();
        packet_count = 0;
        return rc;
}
/*...e*/

/*...slbTransferData\58\\58\requestString\40\ident\41\:0:*/
lbErrCodes lbTransferData::requestString(char* ident) {
	char* buffer = NULL;
	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}

	if (strcmp(buffer, ident) != 0) {
		_LOG << "Error: Expected parameter '" << ident << "' but got '" << buffer << "'" LOG_
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
	
	incrementPosition();

	return ERR_NONE;
}
/*...e*/
/*...slbTransferData\58\\58\requestString\40\ident\44\ data\41\:0:*/
lbErrCodes lbTransferData::requestString(char* ident, char*& data) {
char* buffer = NULL;

	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

char msg[100] = "";	

	if (strcmp(buffer, ident) != 0) {
		_LOG << "Error: Identifer not wanted. Expected parameter '" << ident << "' but got '" << buffer << "'" LOG_
		return ERR_TRANSFER_PROTOCOL;
	}
	
	incrementPosition();

	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		_LOG << "Error: Requested buffer is not of type LB_CHAR" LOG_
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

	if (buffer != NULL) 
		data = buffer;
	else {
		_LOG << "lbTransferData::requestString(...) Error: Could not get real data (NULL pointer)!" LOG_
		return ERR_TRANSFER_NULLPTR;
	}
	
	incrementPosition();
	
	return ERR_NONE;
}
/*...e*/
/*...slbTransferData\58\\58\requestInteger\40\ident\44\ data\41\:0:*/
lbErrCodes lbTransferData::requestInteger(char* ident, int& data) {
char* buffer = NULL;

	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_TRANSFER_PROTOCOL;
	}
	
	incrementPosition();

	if (get(data) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

	incrementPosition();

	return ERR_NONE;
}
/*...e*/
/*...slbTransferData\58\\58\requestULong\40\ident\44\ data\41\:0:*/
lbErrCodes lbTransferData::requestULong(char* ident, unsigned long& data) {
char* buffer = NULL;

	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_TRANSFER_PROTOCOL;
	}
	
	incrementPosition();

	if (get(data) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

	incrementPosition();

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lbTransferData::makeProtoErrAnswer(char* msg, char* where) {
	add("Error");
	add(msg);
	
	_LOG << where << ". Cause: " << msg LOG_

	return ERR_NONE;
}

/*...slbTransferData setters:0:*/
/*...slbTransferData\58\\58\add\40\const char\42\ c\41\:0:*/
void LB_STDCALL lbTransferData::add(const char* c) {
        if (c != NULL) {
                int len = strlen(c)+1;// '\0' at the end must also be in buffer
                
                add((void*) c, len, PACKET_LB_CHAR);
        }
}
/*...e*/
/*...slbTransferData\58\\58\add\40\const void\42\ buf\44\ int len\41\:0:*/
void LB_STDCALL lbTransferData::add(const void* buf, int len) {
        if (buf != NULL) {
                add((void*) buf, len, PACKET_LB_VOID);
        }
}
/*...e*/
/*...slbTransferData\58\\58\add\40\int i\41\:0:*/
void LB_STDCALL lbTransferData::add(int i) {
        int len = sizeof(i);
        
        add((void*) &i, len, PACKET_LB_INT);
}
/*...e*/
/*...slbTransferData\58\\58\add\40\unsigned long ul\41\:0:*/
void LB_STDCALL lbTransferData::add(unsigned long ul) {
        int len = sizeof(ul);
        
        add((void*) &ul, len, PACKET_LB_ULONG);
}
/*...e*/
void LB_STDCALL lbTransferData::add(short s) {
}
void LB_STDCALL lbTransferData::add(long l) {
}
void LB_STDCALL lbTransferData::add(unsigned short us) {
}
/*...e*/

/*...slbTransferData getters:0:*/
/*...slbErrCodes lbTransferData\58\\58\get\40\int\38\ i\41\:0:*/
lbErrCodes LB_STDCALL lbTransferData::get(int& i) {
	lbErrCodes err = ERR_NONE;
	LB_PACKET_TYPE type;
        
	getPacketType(type);
        
	if (type == PACKET_LB_INT) {
		intKey->setData(currentPos);
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Transfer_DataObject, o)
		uk = elements->getElement(&key);
		QI(uk, lb_I_Transfer_DataObject, o)

		pLB_TRANSFER_DATA trans = o->getTransferData();
                
		//c = (char*) malloc(trans->packet_size);
		memcpy(&i, (void const*) &(trans->data), trans->packet_size);
		return ERR_NONE;
	} else {
		_LOG << "lbTransferData::get() called with wrong attempt of data type! Type requested is PACKET_LB_CHAR but have " << getStringFromEnumeration(type) LOG_
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}
}
/*...e*/
/*...slbErrCodes lbTransferData\58\\58\get\40\unsigned long\38\ ul\41\:0:*/
lbErrCodes LB_STDCALL lbTransferData::get(unsigned long& ul) {
	lbErrCodes err = ERR_NONE;
	LB_PACKET_TYPE type;
        
	getPacketType(type);
        
	if (type == PACKET_LB_ULONG) {
		intKey->setData(currentPos);
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Transfer_DataObject, o)
		uk = elements->getElement(&key);
		QI(uk, lb_I_Transfer_DataObject, o)

		memcpy(&ul, (void const*) &(o->getTransferData()->data), 
		o->getTransferData()->packet_size);
		return ERR_NONE;
	} else {
		_LOG << "lbTransferData::get() called with wrong attempt of data type! Type requested is PACKET_LB_CHAR but have " << getStringFromEnumeration(type) LOG_
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}
}
/*...e*/
/*...slbErrCodes lbTransferData\58\\58\get\40\char\42\ \38\ c\41\:0:*/
lbErrCodes LB_STDCALL lbTransferData::get(char* & c) {
	lbErrCodes err = ERR_NONE;
	LB_PACKET_TYPE type;
        
	getPacketType(type);
        
	if (type == PACKET_LB_CHAR) {
		intKey->setData(currentPos);
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Transfer_DataObject, o)
		uk = elements->getElement(&key);
		QI(uk, lb_I_Transfer_DataObject, o)
                
		c = (char*) malloc(o->getTransferData()->packet_size);
		memcpy(c, (void const*) &(o->getTransferData()->data), 
		o->getTransferData()->packet_size);
		return ERR_NONE;
	} else {
		_LOG << "lbTransferData::get() called with wrong attempt of data type! Type requested is PACKET_LB_CHAR but have " << getStringFromEnumeration(type) LOG_
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}
}
/*...e*/
/*...slbErrCodes lbTransferData\58\\58\get\40\void\42\ \38\ v\44\ int \38\ len\41\:0:*/
lbErrCodes LB_STDCALL lbTransferData::get(void* & v, int & len) {
	lbErrCodes err = ERR_NONE;
	LB_PACKET_TYPE type;

	getPacketType(type);

	if (type == PACKET_LB_VOID) {
		intKey->setData(currentPos);
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Transfer_DataObject, o)
		uk = elements->getElement(&key);
		QI(uk, lb_I_Transfer_DataObject, o)

		v = (char*) malloc(o->getTransferData()->packet_size);
		memcpy(v, (void const*) &(o->getTransferData()->data),
		o->getTransferData()->packet_size);
		return ERR_NONE;
	} else {
		_LOG << "lbTransferData::get() called with wrong attempt of data type! Type requested is PACKET_LB_CHAR but have " << getStringFromEnumeration(type) LOG_
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}
}
/*...e*/
lbErrCodes LB_STDCALL lbTransferData::get(short & s) {
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbTransferData::get(long & l) {
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbTransferData::get(unsigned short & us) {
	return ERR_NOT_IMPLEMENTED;
}

/*...e*/


/**
 * The really function who is adding. This function begins with an index
 * of 1.
 */
/*...slbTransferData\58\\58\add\40\const void\42\ buf\44\ int len\44\ LB_PACKET_TYPE type\41\:0:*/
// This should not longer be verbose

void lbTransferData::add(const void* buf, int len, LB_PACKET_TYPE type) {
	lbErrCodes err = ERR_NONE;

	//_LOG << "Creating a packet of type " << getStringFromEnumeration(type) LOG_
	
/// \todo Implement lock
	//lbLock lock(*transferSection, "transferSection");

	char msg[100];
	pLB_TRANSFER_DATA data;

	if (buf != NULL) {
		int datalen = sizeof(LB_TRANSFER_DATA);

		int resultlen = datalen + len;

		data = (pLB_TRANSFER_DATA) malloc(resultlen);
		if (data == NULL) {
			_LOG << "Could not allocate memory" LOG_
			return;
		}

		data->packet_size = len;
		data->packet_type = type;
		data->packet_no = ++packet_count;
		memcpy(&(data->data), buf, len);
		UAP_REQUEST(manager.getPtr(), lb_I_Transfer_DataObject, o)
		o->setTransferData(data);

		if (o->getTransferData() == NULL) {
			_LOG << "lbTransferDataObject::add(): Error, add does not work correctly!" LOG_
		} else {
			if (o->getTransferData()->packet_type != type) {
				_LOG << "Fatal. Datatype could not be stored in the packet structure or not retrieved back from the lb_I_Transfer_DataObject instance!" LOG_
			}
		}
				
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(manager.getPtr(), lb_I_Integer,  integerkey)
		integerkey->setData(packet_count);
		QI(integerkey, lb_I_KeyBase, key)

		if (elements->exists(&key) == 1) {
			_LOG << "lbTransferData::add(...) Error: Creating key for packetcount (prior in list)" LOG_
		}

		UAP(lb_I_Unknown, uk)
		QI(o, lb_I_Unknown, uk)
		elements->insert(&uk, &key);

		if (elements->exists(&key) == 0) {
			_LOG << "lbTransferData::add(...): Error, add could not insert object" LOG_
		} else {
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Transfer_DataObject, e)
			uk = elements->getElement(&key);
			QI(uk, lb_I_Transfer_DataObject, e)
                        
			if (e != NULL) {
				if (e->getTransferData() == NULL) {
					_LOG << "lbTransferData::add(...): Error, lbTransferDataObject has no data!" LOG_
				} else {
					if (e->getTransferData()->packet_type != type) {
						_LOG << "Fatal. Datatype is not equal after getting it back from the container!" LOG_
					}
				}
			}
		}
                //packet_count++;
	}
}
//#undef TRANSFER_VERBOSE
/*...e*/
/*...e*/
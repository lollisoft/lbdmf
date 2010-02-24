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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include "module.h"

#include <conio.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif
#include <lbinclude.h>
#include <signal.h>

#include <lbInterfaces.h>

#include <socket.h>


#include <transfer.h>


#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_FUNCTOR(instanceOflbTransfer, lbTransfer)
IMPLEMENT_FUNCTOR(instanceOflbTransferDataObject, lbTransferDataObject)
IMPLEMENT_FUNCTOR(instanceOflb_Transfer_Data, lb_Transfer_Data)
	
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
#ifndef OSX
                signal(SIGBREAK, handler);
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

BEGIN_IMPLEMENT_LB_UNKNOWN(lb_Transfer_Data)
	ADD_INTERFACE(lb_I_Transfer_Data)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_Transfer_Data::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lb_Transfer_Data::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbTransfer)
	ADD_INTERFACE(lb_I_Transfer)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbTransfer::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbTransfer::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

BEGIN_IMPLEMENT_LB_UNKNOWN(lbTransferDataObject)
	ADD_INTERFACE(lb_I_Transfer_DataObject)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbTransferDataObject::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbTransferDataObject::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbTransferDataObject:0:*/
lbTransferDataObject::lbTransferDataObject() {
        setType();
}

lbTransferDataObject::~lbTransferDataObject() {
}

void lbTransferDataObject::setType() {
        OTyp = LB_DATA_TRANSFER_OBJECT;
}
#ifdef USE_CLONE
lbObject* lbTransferDataObject::clone() const {
        lbLock lock(*transferSection, "transferSection");
        
        char msg[100] = "";
        lbTransferDataObject* o = new lbTransferDataObject();
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
        LOG("lbTransferDataObject::clone() called");
#endif
/*...e*/
        pLB_TRANSFER_DATA pData = (pLB_TRANSFER_DATA) malloc(getData()->packet_size + sizeof(LB_TRANSFER_DATA));
        memcpy(pData, getData(), getData()->packet_size + sizeof(LB_TRANSFER_DATA));
        
        o->setData(pData);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        sprintf(msg, "Cloned lbTransferDataObject (pData) to address %p", (void*) pData);
        LOG(msg);
#endif  
/*...e*/
        return o;
}
#endif

void lbTransferDataObject::setTransferData(pLB_TRANSFER_DATA pData) {
        mydata = pData;
        if (mydata == NULL) LOG("lbTransferDataObject::setData(): Error, data pointer is null");
}

pLB_TRANSFER_DATA lbTransferDataObject::getTransferData() const {
        if (mydata == NULL) LOG("lbTransferDataObject::getData(): Error, data pointer is null");
        return mydata;
}
/*...e*/
/*...slb_Transfer_Data:0:*/
/*...slb_Transfer_Data\58\\58\lb_Transfer_Data\40\\41\:0:*/
lb_Transfer_Data::lb_Transfer_Data(int _serverside) {
	lbErrCodes err = ERR_NONE;
	REQUEST(manager.getPtr(), lb_I_Container, elements)
	REQUEST(manager.getPtr(), lb_I_Integer, intKey)
	REQUEST(manager.getPtr(), lb_I_String, clientHost)
	
	QI(intKey, lb_I_KeyBase, key)
	
        //elements = new lbComponentDictionary();
        //*elementscopy = elements->clone(__FILE__, __LINE__);

        elements->deleteAll();
        
        packet_count = 0;
        ref = 0;
        serverside=_serverside;

	UAP_REQUEST(manager.getPtr(), lb_I_Socket, s)

        *clientHost = s->gethostname();
        clientPid = lbGetCurrentProcessId();
        clientTid = lbGetCurrentThreadId();
}

/*...e*/
/*...slb_Transfer_Data\58\\58\\126\lb_Transfer_Data\40\\41\:0:*/
lb_Transfer_Data::~lb_Transfer_Data() {
        if (elements != NULL) {
                //delete elements;
        }

        //if (clientHost != NULL) free(clientHost);
}
/*...e*/

/*...slb_Transfer_Data\58\\58\lb_Transfer_Data\40\const lb_Transfer_Data \38\ t\41\:0:*/
lb_Transfer_Data::lb_Transfer_Data(const lb_I_Transfer_Data & t) {
        elements = ((lb_Transfer_Data&) t).elements;
//        elementscopy = ((lb_Transfer_Data&) t).elementscopy;

        packet_count = ((lb_Transfer_Data&) t).packet_count;
        currentPos = ((lb_Transfer_Data&) t).currentPos;

        if (((lb_Transfer_Data&) t).clientHost != NULL)
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

/*...slb_Transfer_Data\58\\58\assign \40\const lb_I_Transfer_Data \38\ t\41\:0:*/
lb_I_Transfer_Data& lb_Transfer_Data::assign (const lb_I_Transfer_Data & t) {
        elements = ((lb_Transfer_Data&) t).elements;
        //elementscopy = ((lb_Transfer_Data&) t).elementscopy;

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
        return *this;
}
/*...e*/

/*...slb_Transfer_Data\58\\58\hasMorePackets\40\\41\:0:*/
int lb_Transfer_Data::hasMorePackets() const {
        return elements->hasMoreElements();
}
/*...e*/
/*...slb_Transfer_Data\58\\58\addPacket\40\pLB_TRANSFER_DATA mydata\41\:0:*/
int lb_Transfer_Data::addPacket(pLB_TRANSFER_DATA data) {
        return 0;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getNextPacket\40\\41\:0:*/
pLB_TRANSFER_DATA lb_Transfer_Data::getNextPacket() const {
	lbErrCodes err = ERR_NONE;
        char msg[100] = "";
        UAP(lb_I_Unknown, uk)
        UAP(lb_I_Transfer_DataObject, o)
        uk = elements->nextElement();
        QI(uk, lb_Transfer_DataObject, o)       
        if (o->getTransferData() == NULL) LOG("lbTransferDataObject contains no data!");

/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
        sprintf(msg, "lb_Transfer_Data::getNextPacket() returns this address: %p", (void*) (o->getData()));
        LOG(msg);
#endif
/*...e*/
        
        return o->getTransferData();
}
/*...e*/
int lb_Transfer_Data::getCurrentPos() const {
	return currentPos;
}
/*...slb_Transfer_Data\58\\58\getPacketCount\40\\41\:0:*/
int lb_Transfer_Data::getPacketCount() const {
        return packet_count;
}
/*...e*/

/*...slb_Transfer_Data\58\\58\resetPositionCount\40\\41\:0:*/
int lb_Transfer_Data::resetPositionCount() {
        currentPos = 1;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        LOG("lb_Transfer_Data::resetPositionCount() called");
#endif
/*...e*/
        return 1;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\incrementPosition\40\\41\:0:*/
int lb_Transfer_Data::incrementPosition() {
        currentPos++;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
        LOG("lb_Transfer_Data::incrementPosition() called");    
#endif
/*...e*/
        return (currentPos > packet_count) ? 0 : 1;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getPacketType\40\LB_PACKET_TYPE \38\ type\41\:0:*/
int lb_Transfer_Data::getPacketType(LB_PACKET_TYPE & type) {
	lbErrCodes err = ERR_NONE;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
        char msg[100];
        sprintf(msg, "Lookup element for key %d", currentPos);
        LOG(msg);
#endif
/*...e*/
        char buf[100] = "";
        UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerKey)
        UAP(lb_I_KeyBase, k)
        integerKey->setData(currentPos);
        QI(integerKey, lb_I_KeyBase, k)
        UAP(lb_I_Unknown, uk)
        UAP(lb_I_Transfer_DataObject, o)
        
        uk = elements->getElement(&k);
        QI(uk, lb_I_Transfer_DataObject, o)
        
        if (o == NULL) LOG("lb_Transfer_Data::getPacketType() Error, can't get packet type from a NULL pointer object");
        
        type = o->getTransferData()->packet_type;
        
        /// \todo Why yet ever 1 ?
        return 1;
}
/*...e*/
LB_PACKET_TYPE lb_Transfer_Data::getNextPacketType() {
	return PACKET_LB_INVALIDTYPE;
}
/*...slb_Transfer_Data\58\\58\deleteAll\40\\41\:0:*/
int lb_Transfer_Data::deleteAll() {
        int rc = 0;
        if (elements != NULL) {
                elements->deleteAll();
                rc = 1;
        } else {
                LOG("lb_Transfer_Data::deleteAll() failed because elements is a NULL pointer!");
        }

        resetPositionCount();
        packet_count = 0;
        return rc;
}
/*...e*/

/*...slb_Transfer_Data\58\\58\requestString\40\ident\41\:0:*/
lbErrCodes lb_Transfer_Data::requestString(char* ident) {
char* buffer = NULL;
	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}

	if (strcmp(buffer, ident) != 0) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	}
	
	incrementPosition();

	return ERR_NONE;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\requestString\40\ident\44\ data\41\:0:*/
lbErrCodes lb_Transfer_Data::requestString(char* ident, char*& data) {
char* buffer = NULL;

	if (get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_TRANSFER_DATA_INCORRECT_TYPE;
	}

char msg[100] = "";	

	if (strcmp(buffer, ident) != 0) {
		_LOG << "Error: Identifer not wanted" LOG_
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
		_LOG << "lb_Transfer_Data::requestString(...) Error: Could not get real data (NULL pointer)!" LOG_
		return ERR_TRANSFER_NULLPTR;
	}
	
	incrementPosition();
	
	return ERR_NONE;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\requestInteger\40\ident\44\ data\41\:0:*/
lbErrCodes lb_Transfer_Data::requestInteger(char* ident, int& data) {
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
/*...slb_Transfer_Data\58\\58\requestULong\40\ident\44\ data\41\:0:*/
lbErrCodes lb_Transfer_Data::requestULong(char* ident, unsigned long& data) {
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

lbErrCodes LB_STDCALL lb_Transfer_Data::makeProtoErrAnswer(char* msg, char* where) {
	add("Error");
	add(msg);
	
	_LOG << where << "Cause: " << msg LOG_

	return ERR_NONE;
}

/*...slb_Transfer_Data setters:0:*/
/*...slb_Transfer_Data\58\\58\add\40\const char\42\ c\41\:0:*/
void LB_STDCALL lb_Transfer_Data::add(const char* c) {
        if (c != NULL) {
                int len = strlen(c)+1;// '\0' at the end must also be in buffer
                
                add((void*) c, len, PACKET_LB_CHAR);
        }
}
/*...e*/
/*...slb_Transfer_Data\58\\58\add\40\const void\42\ buf\44\ int len\41\:0:*/
void LB_STDCALL lb_Transfer_Data::add(const void* buf, int len) {
        if (buf != NULL) {
                add((void*) buf, len, PACKET_LB_VOID);
        }
}
/*...e*/
/*...slb_Transfer_Data\58\\58\add\40\int i\41\:0:*/
void LB_STDCALL lb_Transfer_Data::add(int i) {
        int len = sizeof(i);
        
        add((void*) &i, len, PACKET_LB_INT);
}
/*...e*/
/*...slb_Transfer_Data\58\\58\add\40\unsigned long ul\41\:0:*/
void LB_STDCALL lb_Transfer_Data::add(unsigned long ul) {
        int len = sizeof(ul);
        
        add((void*) &ul, len, PACKET_LB_ULONG);
}
/*...e*/
void LB_STDCALL lb_Transfer_Data::add(short s) {
}
void LB_STDCALL lb_Transfer_Data::add(long l) {
}
void LB_STDCALL lb_Transfer_Data::add(unsigned short us) {
}
/*...e*/

/*...slb_Transfer_Data getters:0:*/
/*...slbErrCodes lb_Transfer_Data\58\\58\get\40\int\38\ i\41\:0:*/
lbErrCodes LB_STDCALL lb_Transfer_Data::get(int& i) {
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
                LOG("lb_Transfer_Data::get() called with wrong attempt of data type!");
                return ERR_TRANSFER_DATA_INCORRECT_TYPE;
        }
}
/*...e*/
/*...slbErrCodes lb_Transfer_Data\58\\58\get\40\unsigned long\38\ ul\41\:0:*/
lbErrCodes LB_STDCALL lb_Transfer_Data::get(unsigned long& ul) {
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
                LOG("lb_Transfer_Data::get() called with wrong attempt of data type!");
                return ERR_TRANSFER_DATA_INCORRECT_TYPE;
        }
}
/*...e*/
/*...slbErrCodes lb_Transfer_Data\58\\58\get\40\char\42\ \38\ c\41\:0:*/
lbErrCodes LB_STDCALL lb_Transfer_Data::get(char* & c) {
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
                LOG("lb_Transfer_Data::get() called with wrong attempt of data type!");
                return ERR_TRANSFER_DATA_INCORRECT_TYPE;
        }
}
/*...e*/
/*...slbErrCodes lb_Transfer_Data\58\\58\get\40\void\42\ \38\ v\44\ int \38\ len\41\:0:*/
lbErrCodes LB_STDCALL lb_Transfer_Data::get(void* & v, int & len) {
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
        } else return ERR_TRANSFER_DATA_INCORRECT_TYPE;
}
/*...e*/
lbErrCodes LB_STDCALL lb_Transfer_Data::get(short & s) {
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lb_Transfer_Data::get(long & l) {
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lb_Transfer_Data::get(unsigned short & us) {
	return ERR_NOT_IMPLEMENTED;
}

/*...e*/


/**
 * The really function who is adding. This function begins with an index
 * of 1.
 */
/*...slb_Transfer_Data\58\\58\add\40\const void\42\ buf\44\ int len\44\ LB_PACKET_TYPE type\41\:0:*/
// This should not longer be verbose

void lb_Transfer_Data::add(const void* buf, int len, LB_PACKET_TYPE type) {
	lbErrCodes err = ERR_NONE;
	
        lbLock lock(*transferSection, "transferSection");
//#define TRANSFER_VERBOSE      
        char msg[100];
        pLB_TRANSFER_DATA data;

/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lb_Transfer_Data::add() called");
#endif
/*...e*/
        if (buf != NULL) {
                int datalen = sizeof(LB_TRANSFER_DATA);

                int resultlen = datalen + len;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "lb_Transfer_Data::add() adds a LB_TRANSFER_DATA object with size = %d", resultlen);
LOG(msg);
#endif
/*...e*/
                data = (pLB_TRANSFER_DATA) malloc(resultlen);
                if (data == NULL) {
                        LOG("Could not allocate memory");
                        return;
                }
                data->packet_size = len;
                
                data->packet_type = type;
                data->packet_no = ++packet_count;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "Do memcpy from %p to %", (void*) buf, (void*) (data->data));
LOG(msg);
#endif
/*...e*/
                memcpy(&(data->data), buf, len);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Done memcpy");
#endif
/*...e*/
                UAP_REQUEST(manager.getPtr(), lb_I_Transfer_DataObject, o)
                o->setTransferData(data);

                if (o->getTransferData() == NULL) {
                  _LOG << "lbTransferDataObject::add(): Error, add does not work correctly!" LOG_
                } else {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
                  sprintf(msg, "lbTransferDataObject has it's data pointer at %p", (void*) (o.getData()));
                  LOG(msg);
#endif  
/*...e*/
                }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE         
                sprintf(msg, "Create key with number %d", packet_count);
                LOG(msg);
#endif
/*...e*/
		UAP(lb_I_KeyBase, key)
                UAP_REQUEST(manager.getPtr(), lb_I_Integer,  integerkey)
                integerkey->setData(packet_count);
                QI(integerkey, lb_I_KeyBase, key)
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Created");         
#endif
/*...e*/
/*
                sprintf(msg, "Address of elements now is 0x%p", (void*) elements);
                LOG(msg);
                if ((void*)elements != (void*)elementscopy) 
                  LOG("Error: elements pointer has been overwritten!");
*/
                if (elements->exists(&key) == 1) {
                        LOG("lb_Transfer_Data::add(...) Error: Creating key for packetcount (prior in list)");
                }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lb_Transfer_Data::add(...) Checked key for packet count nonexistence in list");
#endif
/*...e*/
		UAP(lb_I_Unknown, uk)
		QI(o, lb_I_Unknown, uk)
                elements->insert(&uk, &key);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Inserted");
#endif          
/*...e*/
                if (elements->exists(&key) == 0) {
                  _LOG << "lb_Transfer_Data::add(...): Error, add could not insert object" LOG_
                } else {
                	UAP(lb_I_Unknown, uk)
                	UAP(lb_I_Transfer_DataObject, e)
                        uk = elements->getElement(&key);
                        QI(uk, lb_I_Transfer_DataObject, e)
                        
                        if (e != NULL) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                                sprintf(msg, "lb_Transfer_Data::add() Have added this address: %p", (void*) (e->getData()));
                                LOG(msg);
#endif                  
/*...e*/
                                if (e->getTransferData() == NULL) {
                                  _LOG << "lb_Transfer_Data::add(...): Error, lbTransferDataObject has no data!" LOG_
                        	}
                        }
                }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE         
LOG("Checked");
#endif
/*...e*/
                //packet_count++;
        }
}
//#undef TRANSFER_VERBOSE
/*...e*/
/*...e*/
/*...slbTransfer:0:*/
/*...slbTransfer\58\\58\lbTransfer\40\\41\:0:*/
lbTransfer::lbTransfer() {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOGENABLE("lbTransfer::lbTransfer()");
#endif
/*...e*/
        sock = new lbSocket();
        laststate = 1;
        connected = 0;
        state = LB_STATE_UNINITIALIZED;
}
/*...e*/
/*...slbTransfer\58\\58\\126\lbTransfer\40\\41\:0:*/
lbTransfer::~lbTransfer() {
        COUT << "lbTransfer::~lbTransfer() called" << ENDL;
}
/*...e*/
/*...slbTransfer\58\\58\init\40\char \42\target\41\:0:*/
/**
 * A target has this format: //machine/service/...
 *
 * The machine name has to be resolved to a IP address
 * A service has to be resolved to a port number
 */
void lbTransfer::init(char *target) {
        u_short port;
        char *mysockaddr;
        char token[100];
        char *machine;
        char *service;
        char *subservice;
        char prefix[100];
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::init(char *target) called");
#endif
/*...e*/
        strcpy(token, strtok(target, "/"));
        machine = strdup(token);
        strcpy(token, strtok(NULL, "/"));
        service = strdup(token);
//COUT << "Check for service" << ENDL;
        if (service == NULL) {
                LOG("lbTransfer::init(char *target): Service name couldn't retrieved from target string!");
                // Handle error
        }
//COUT << "Check for machine" << ENDL;
        if (machine == NULL) {
                LOG("lbTransfer::init(char *target): Machine name couldn't retrieved from target string!");
        }

        subservice = strtok(NULL, "/");

        if (subservice == NULL) {
                /**
                 * machine is the computername. Service is the name of a service
                 * mapped to a port.
                 */
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
char buf[100];
sprintf(buf, "void lbTransfer::init(char *target): sock->initSymbolic(%s, %s);", machine, service);
LOG(buf);
#endif
/*...e*/
                //COUT << "Init with symbolic name" << ENDL;

                sock->initSymbolic(machine, service);
                //strcpy(prefix, (sock->isServer() == 1) ? "Server: " : "Client: ");
                //LOGPREFIX(prefix);
        } else {
                LOG("Subservices currently not supported");
                // Handle special cases with subservices
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        LOG("lbTransfer::init(char *target): lbTransfer has been initialized");
#endif  
/*...e*/
}
/*...e*/

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
        if (strcmp(typeAsString, "PACKET_LB_CHAR") == 0) {
/*...sTRANSFER_VERBOSE:0:*/
        #ifdef TRANSFER_VERBOSE
                LOG("getEnumerationFromString(...) returns LB_CHAR");
        #endif
/*...e*/
                return PACKET_LB_CHAR;
        }
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
        char buf[100];
        
        if (sock->send_charbuf("reset", strlen("reset")) == 0) {
                LOG("lbSocket: Panic, can't send reset comando to server");
                return 0;
        }

        if (sock->recv_charbuf(buf) == 0) { 
                LOG("lbSocket: Panic, can't reset server's statemachine");
                return 0;
        }

        if (strcmp(buf, "ok") != 0) {
                LOG("lbSocket: Server state error, reset comando don't be answered with 'ok'");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        LOG("lbTransfer: Reseting server statemachine sucseeded");
#endif
/*...e*/
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\sendDatatype\40\char\42\ type\41\:0:*/
lbErrCodes lbTransfer::sendDatatype(char* type) {
        if (sock->send_charbuf(type, strlen(type)+1) != ERR_NONE) {
                LOG("lbTransfer::sendDatatype(char* type): Failed to send packet type information");
                return ERR_TRANSFER_SEND_DATATYPE;
        }
        return ERR_NONE;
}
/*...e*/
/*...slbTransfer\58\\58\waitforAnswer\40\char\42\ answer\41\:0:*/
int lbTransfer::waitforAnswer(char* answer) {
        char buf[MAXBUFLEN];
        char msg[100];
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(buf, "waitforAnswer('%s') called", answer);
LOG(buf);
#endif
/*...e*/
        if (sock->recv_charbuf(buf) != ERR_NONE)  {
                LOG("lbSocket: Failed to get any answer");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "Got answer '%s'", buf);
LOG(msg);
#endif  
/*...e*/
        if (strcmp(buf, "Protokol error") == 0) 
                LOG("Got an error in protokol flow");

        if (strcmp(buf, answer) != 0) {
                sprintf(msg, "lbSocket: Incorrect answer '%s'.", buf);
                LOG(msg);
                //resetServerStateMachine();
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("waitforAnswer(char* answer) returning");   
fprintf(stderr, "waitforAnswer(): Got correct answer '%s'\n", answer);
#endif
/*...e*/
        return 1;
}
/*...e*/
/*...slbTransfer\58\\58\sendString\40\char\42\ type\41\:0:*/
int lbTransfer::sendString(char* type) {
        if (sock->send_charbuf(type, strlen(type)+1) != ERR_NONE) {
                LOG("lbTransfer::sendString(char* type): Failed to send simple string");
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
                LOG("lbTransfer: Could not send integer value");
                resetServerStateMachine();
                return 0;
        }

        if (waitforAnswer("Datacount ok") == 0) {
        LOG("lbTransfer::sendDataCount(int c): Error, answer not got");
                return 0;
        }
        return 1;       
}
/*...e*/
/*...slbTransfer\58\\58\sendBuffer\40\byte\42\ buf\44\ int len\41\:0:*/
int lbTransfer::sendBuffer(byte* buf, int len) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::sendBuffer(void* buf, int len) Enter");
#endif
/*...e*/
        if (sendString("Datablock") == 0) {
                LOG("lbTransfer: Could not send 'Datablock' message");
                resetServerStateMachine();
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::sendBuffer(void* buf, int len) waitforAnswer('ok')");
#endif
/*...e*/
        if (waitforAnswer("ok") == 0) {
        LOG("Could not get answer 'ok' after sending 'Datablock'");
                return 0;
        }

/*...sSend buffersize:8:*/
        // Get the size of the packet for memory allocation (if possible)
        if (sock->sendInteger(len) != ERR_NONE) return 0;       
        if (waitforAnswer("ok") == 0) return 0;
/*...e*/
        int peaces = len / MAXBUFLEN;
        byte * currbufferpos = buf;
        char msg[100];
        

        // target knows multiple packets from buffersize > MAXBUFLEN !
        for (int i = 0; i < peaces; i++) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                if (i == 0) LOG("Sending subsequent packets");
#endif
/*...e*/
                if (sock->send((void* )currbufferpos, MAXBUFLEN) != ERR_NONE) 
                {
                        LOG("lbTransfer::sendBuffer(byte* buf, int len) failed");
                        return 0;
                }
                currbufferpos = currbufferpos + MAXBUFLEN;
                if (waitforAnswer("Peace ok") == 0) 
                {
                        LOG("lbTransfer::sendBuffer(byte* buf, int len) waiting for 'Peace ok' failed");
                        return 0;
                }
        }
        
        // Send remaining
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Send remaining");
#endif
/*...e*/
        //currbufferpos = currbufferpos + (len-peaces*MAXBUFLEN);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        sprintf(msg, "Sending this buffer: '%s'", (char*) currbufferpos);
        LOG(msg);
#endif
/*...e*/
        if (sock->send((void* )currbufferpos, (len-peaces*MAXBUFLEN)) != ERR_NONE) 
        {
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Wait for answer 'Buffer Ok'");
#endif
/*...e*/
        if (waitforAnswer("Buffer ok") == 0) {
                LOG("Got incorrect answer");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::sendBuffer(byte* buf, int len) returning with success");
#endif
/*...e*/
        return 1;
}

/*...e*/

/*...slbTransfer\58\\58\waitForString\40\char\42\ \38\ string\41\:0:*/
int lbTransfer::waitForString(char* & string) {
        char buf[MAXBUFLEN];

        if (sock->recv_charbuf(buf) != ERR_NONE)
        {
          LOG("lbSocket: Failed to get any data while waiting for a string");
          return 0;
        }  
        string = strdup(buf);
        
        return 1;  
}
/*...e*/
/*...slbTransfer\58\\58\waitForBuffer\40\byte \42\ \38\ buffer\44\ int \38\ len\41\:0:*/
int lbTransfer::waitForBuffer(byte * & buffer, int & len) {
        char buf[MAXBUFLEN];
        char msg[100];
        int buflen;     
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::waitForBuffer(void * & buffer, int & len) Enter");
#endif
/*...e*/
        if (waitforAnswer("Datablock") == 0) {
                LOG("Could not get 'Datablock' identifer");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("sendString('ok')");
#endif
/*...e*/
        if (sendString("ok") == 0) {
                LOG("lbTransfer::waitForBuffer(...) Error: Sending 'ok' after recieving 'Datablock'");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("sock->recv_charbuf((char*) buf)");
#endif
/*...e*/
/*...sGet buffersize:8:*/
        // Get the size of the packet for memory allocation (if possible)
        if (sock->recvInteger(buflen) != ERR_NONE) {
                LOG("lbTransfer::waitForBuffer(...) Error: Could not get buffer size");
                return 0;       
        }
        
        if (sendString("ok") == 0) {
                LOG("lbTransfer::waitForBuffer(...) Error: Could not send 'ok' after recieving buffer size");
                return 0;
        }
/*...e*/
        len = buflen;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "Got a buffersize of %d bytes", len);
LOG(msg);
#endif  
/*...e*/
        buffer = (byte*) malloc(buflen);

        int peaces = buflen / MAXBUFLEN;
        byte * currbufferpos = buffer;

/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "Calculated values: peaces = %d, currbufferpos = %p", peaces, (void*) currbufferpos);
LOG(msg);
#endif
/*...e*/

        // target knows multiple packets from buffersize > MAXBUFLEN !
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Begin reciefing buffer");
#endif
/*...e*/
/*...sRecieving all packets except the last:0:*/
        for (int i = 0; i < peaces; i++) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
        if (i == 0) LOG("Recieving subsequent packets");
#endif
/*...e*/
                int gotBuflen = MAXBUFLEN;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::waitForBuffer(...) Recv peace");
#endif
/*...e*/
                if (sock->recv((void* )currbufferpos, gotBuflen) != ERR_NONE) {
                        LOG("sock->recv((void* )currbufferpos, gotBuflen) failed");
                        return 0;
                }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE 
                sprintf(msg, "Wanted buflen: %d. Got this: %d", buflen, gotBuflen);
                LOG(msg);
#endif          
/*...e*/
                currbufferpos = currbufferpos + MAXBUFLEN;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Send 'ok'");
#endif
/*...e*/
                if (sendString("Peace ok") == 0) {
                        LOG("Cannot send answer 'Peace ok'");
                        return 0;
                }
        }
/*...e*/
        
        // Recv remaining
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Recieving remaining");     
#endif
/*...e*/
//      currbufferpos = currbufferpos + (buflen-peaces*MAXBUFLEN);
        int wanted_peace_size = (buflen-peaces*MAXBUFLEN);
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "Calculated values: peaces = %d, currbufferpos = %p, torecv = %d", peaces, (void*) currbufferpos, wanted_peace_size);
LOG(msg);
#endif
/*...e*/
        
        /* // Done in recv self
        if (sock->isValid() == 0) {
                LOG("lbTransfer::waitForBuffer(...) Error: Can't get data from an invalid socket!");
                return 0;
        }
        */
        
        if (sock->recv((void* )currbufferpos, wanted_peace_size) != ERR_NONE) {
                LOG("Can't get buffer");
                return 0;
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
char gotbuffer[100];
strncpy(gotbuffer, (char*)buffer, len);
gotbuffer[len] = 0;

sprintf(msg, "Returning '%s', len is %d", gotbuffer, wanted_peace_size);
LOG(msg);
#endif
/*...e*/
        if (sendString("Buffer ok") == 0) {
                LOG("Can't send back 'ok'");
                return 0;
        }

/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::waitForBuffer(void * & buffer, int & len) Leave");
#endif
/*...e*/
        return 1;       
}
/*...e*/


/*...slbTransfer\58\\58\waitForDataCount\40\int \38\ c\41\:0:*/
int lbTransfer::waitForDataCount(int & c) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("waitForDataCount() Enter");
#endif
/*...e*/
        if (waitforAnswer("DataCount") == 0) return 0;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("Got 'DataCount' identifer");
#endif
/*...e*/
        if (sendString("ok") == 0) return 0;
        if (sock->recvInteger(c) != ERR_NONE) return 0;
        if (sendString("Datacount ok") == 0) return 0;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("waitForDataCount() Leave");
#endif
/*...e*/
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\waitForDatatype\40\char\42\ \38\ result\41\:0:*/
lbErrCodes lbTransfer::waitForDatatype(char* &result) {
        static char buf[MAXBUFLEN];
        lbErrCodes err = ERR_NONE;
        
        if ((err = sock->recv_charbuf(buf)) != ERR_NONE)
        {
                switch (err) {
                        case ERR_SOCKET_CLOSED:
                                err = ERR_TRANSFER_ENDED;
                                break;
                        default:
                                LOG("lbSocket: Failed to get any datatype");
                                err = ERR_TRANSFER_FAILED;
                }
                result = '\0';
        } else result = strdup(buf);
        
        return err;
}
/*...e*/
/*...e*/

int lbTransfer::gethostname(lb_I_String* name) {
	if (name != NULL) *name = sock->gethostname();
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
        sock = s;
        connected = 1;  
        return 1;
}
/*...e*/

/*...slbTransfer\58\\58\accept\40\\41\:0:*/
lb_I_Transfer* lbTransfer::accept() {
        if (state == LB_STATE_CONNECTED) {
                LOG("lbTransfer::accept(lbTransfer*& t) State error: Accept can not be called!");
                return NULL;
        }
        fprintf(stderr, "Waiting for a connection...\n");
        UAP(lb_I_Socket, s)

        if (sock == NULL) {
        	_LOG << "lbTransfer::accept(lbTransfer*& t) Error: Internal sock instance points to NULL!" LOG_
        	return NULL;
	}
	
        s = sock->accept();	
        if (s != NULL) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                LOG("lbTransfer::accept(lbTransfer*& t): Create a lbTransfer object for the connected client");
#endif
/*...e*/
               UAP_REQUEST(getModuleInstance(), lb_I_Transfer, t)
                 
                if (s == NULL) {
                        LOG("t->setSockConnection(s) Error: s is a NULL pointer!"); 
                        return 0;
                }
                
                // t cannot call accept or those functions that
                // are outside of connected state
                
                t->setSockConnection(s.getPtr());
                t++;
                return t.getPtr();
        } else {
                LOG("lbTransfer::accept(lb_I_Transfer* t): Error, failed to accept on serversocket");
                return NULL;
        }
}
/*...e*/

/*...slbTransfer\58\\58\operator\60\\60\ \40\lb_I_Transfer_Data\42\ req\41\:0:*/
void lbTransfer::operator<< (lb_I_Transfer_Data* req) {
        if (laststate == 1)
                laststate = send(req);
        else
                LOG("Transfer: There was a previous error. Could not send any more");
}
/*...e*/
/*...slbTransfer\58\\58\operator\62\\62\ \40\lb_I_Transfer_Data\42\ res\41\:0:*/
void lbTransfer::operator>> (lb_I_Transfer_Data* res) {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOGENABLE("lbTransfer::operator>> (lb_Transfer_Data& res) called");
#endif
/*...e*/
        if (laststate == 1) {
                laststate = recv(res);
                if (laststate != 1) LOG("Error in recv, here should throw be the best");
        }
        else
                LOG("Transfer: There was a previous error. Could not recieve any more");
}
/*...e*/

/*...slbTransfer\58\\58\send\40\lb_I_Transfer_Data\42\ data\41\:0:*/
int lbTransfer::send(lb_I_Transfer_Data* data) {
        char buf[MAXBUFLEN];
        char msg[100];
        lastError = ERR_NONE;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
sprintf(msg, "lbTransfer::send(const lb_Transfer_Data & data): Sending %d packets", data.getPacketCount());     
LOG(msg);
#endif  
/*...e*/

if (!data->isServerSide()) {
/*...sClient sends internal data:0:*/
	DWORD cP = data->getClientPid();
	DWORD cT = data->getClientTid();
	char* h  = data->getClientHost();
        if (sendBuffer((byte*) &cP, sizeof(DWORD)) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal pid");
                return 0;
        }
        if (waitforAnswer("Got buffer") == 0) {
                LOG("Could not get answer 'Got buffer'");
                return 0;
        }
        if (sendBuffer((byte*) &cT, sizeof(DWORD)) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal tid");
                return 0;
        }
        if (waitforAnswer("Got buffer") == 0) {
                LOG("Could not get answer 'Got buffer'");
                return 0;
        }
        if (sendString(h) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal client hostname");
                return 0;
        }       
        if (waitforAnswer("ok") == 0) return 0;
/*...e*/
}

        if (sendDatatype("lb_Transfer_Data") != ERR_NONE) {
                LOG("Failed to send data type information");    
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }
        
/*...sTRANSVER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::send(...) Call waitforAnswer('Datatype ok')");
#endif
/*...e*/
        if (waitforAnswer("Datatype ok") == 0) {
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        if (sendDataCount(data->getPacketCount()) == 0) {
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        while (data->hasMorePackets()) {
                pLB_TRANSFER_DATA pData = data->getNextPacket();
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                sprintf(msg, "Send a packet (pData) with address %p", (void*) pData);
                LOG(msg);
#endif
/*...e*/
                if (pData == NULL) {
                        lastError = ERR_TRANSFER_NULLPTR;
                        LOG("lbTransfer::send(const lb_Transfer_Data & data): Error, can't send buffer. Null pointer exception.");
                        return 0;
                } else {
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                        LOG("Send a packet from LB_TRANSFER_DATA");
                        sprintf(msg, "Try to copy buffer to a char buffer. It's address: %p, it's size %d", (void*) (pData->data), pData->packet_size);
                        LOG(msg);
                        char sendbuffer[100];
                        strncpy(sendbuffer, (char*) &(pData->data), pData->packet_size);
                        sprintf(msg, "Buffer '%s' has been copied", sendbuffer);
                        LOG(msg);
                        // Send the packet type
                        sprintf(msg, "Sending packet type: '%s'", getStringFromEnumeration(pData->packet_type));
                        LOG(msg);
#endif          
/*...e*/
                        if (sendString(getStringFromEnumeration(pData->packet_type)) == 0) {
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                        LOG("lbTransfer::send(...) Wait for 'ok' after sending packet type");
#endif
/*...e*/
                        if (waitforAnswer("ok") == 0) {
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                        LOG("lbTransfer::send(...) Send packet size");
#endif                  
/*...e*/
                        if (sendBuffer((byte*) &(pData->data), pData->packet_size) == 0) {
                                LOG("lbTransfer: Could not send data buffer");
                                lastError = ERR_TRANSFER_FAILED;
                                //resetServerStateMachine();
                                return 0;
                        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
                        LOG("waitforAnswer('Got buffer')");
#endif
/*...e*/
                        if (waitforAnswer("Got buffer") == 0) {
                                LOG("Could not get answer 'Got buffer'");
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE                 
                        LOG("Sent a packet from LB_TRANSFER_DATA");
#endif
/*...e*/
                }
        }
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::send(...) Have sent all packets. Returning with success");
#endif
/*...e*/
        return 1;
}
/*...e*/
/*...slbTransfer\58\\58\recv\40\lb_I_Transfer_Data\42\ data\41\:0:*/
int lbTransfer::recv(lb_I_Transfer_Data* data) {
        char* result = NULL;
        int len;
        void* buf = NULL;
        char msg[100];
        lbErrCodes err = ERR_NONE;
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOGENABLE("lbTransfer::recv(lb_Transfer_Data & data)");
LOG("lbTransfer::recv() Enter");
LOG("lbTransfer::recv(lb_Transfer_Data & data): waitForDatatype(result)...");   
#endif
/*...e*/

	if (data->isServerSide()) {
/*...sServerside recieves internal data :16:*/

        if (waitForBuffer((byte*&) buf, len) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal pid");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        char* h;

	data->setClientPid(*(DWORD*)buf);
        delete buf;

        if (sendString("Got buffer") == 0) {
                LOG("Could not get answer 'Got buffer'");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }
        
        if (waitForBuffer((byte*&) buf, len) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal tid");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }
        
        data->setClientTid(*(DWORD*)buf);
        delete buf;

        if (sendString("Got buffer") == 0) {
                LOG("Could not get answer 'Got buffer'");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

        if (waitForString(h) == 0) {
                LOG("lbTransfer::send(...) Error: Could not send internal client hostname");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }       
        data->setClientHost(h);

        if (sendString("ok") == 0) {
                lastError = ERR_TRANSFER_FAILED;
                return 0;
        }

/*...e*/
	}

        if ((err = waitForDatatype(result)) == ERR_NONE) {
          if (strcmp(result, "lb_Transfer_Data") == 0)
          {// Got correct datatype
/*...sget it:16:*/
            int count = 0;
            lb_Transfer_Data temp;
            int len;
            
            //fprintf(stderr, "Got datatype information of '%s'\n", result);
/*...sTRANSFER_VERBOSE:16:*/
#ifdef TRANSFER_VERBOSE    
            LOG("lbTransfer::recv(lb_Transfer_Data & data): Got wanted datatype");
#endif
/*...e*/
            if (sendString("Datatype ok") == 0) {
                lastError = ERR_TRANSFER_FAILED;
                return 0;
            }
           
            //fprintf(stderr, "Waiting for packet count\n");
           
/*...swaitForDataCount:28:*/
            if (waitForDataCount(count) == 0) {
                LOG("waitForDataCount(count) Error: No packet count");
                fprintf(stderr, "Waiting for packet count: Results in an error\n");
                lastError = ERR_TRANSFER_FAILED;
                return 0;
            }
/*...e*/
/*...sTRANSFER_VERBOSE:16:*/
#ifdef TRANSFER_VERBOSE
            sprintf(msg, "Begin with recieving %d packets", count);
            LOG(msg);
#endif
/*...e*/
/*...sGet all packets:28:*/
#ifdef TRANSFER_VERBOSE
                sprintf(msg, "Have %d packets", count);
                LOG(msg);
#endif
            while (count != 0) {
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE
                sprintf(msg, "Get a packet (%d)", count);
                LOG(msg);
#endif
/*...e*/
                count--;
                int ptypelen = sizeof(LB_PACKET_TYPE);
                LB_PACKET_TYPE type;
                char* typeAsString = NULL;
                if (waitForString(typeAsString) == 0) {
                        LOG("lbTransfer::recv(...) Error: Could not get packet type information!");
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;
                }
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE         
                sprintf(msg, "Got packet type '%s'", typeAsString);
                LOG(msg);
#endif     
/*...e*/
                type = getEnumerationFromString(typeAsString);
                
                if (type != PACKET_LB_INVALIDTYPE) {
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE      
                        LOG("lbTransfer::recv(...) Got a known packet type, accept it with 'ok'");
#endif                  
/*...e*/
                        if (sendString("ok") == 0) {
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
                } else { 
                        if (sendString("Protokol error") == 0) {
                                lastError = ERR_TRANSFER_FAILED;
                                return 0;
                        }
                }
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE 
                LOG("lbTransfer::recv(...) Waiting for buffer");
#endif
/*...e*/
                if (waitForBuffer((byte* &) buf, len) == 0) {
                        LOG("waitForBuffer((byte* &) buf, len) Error: Waiting for buffer failed!");
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;       
                }

/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE
                LOG("lbTransfer::recv(...) Got buffer");
#endif          
/*...e*/
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE
                char b[100];
                
                strncpy(b, (char*)buf, len);
                b[len] = 0;
                
                sprintf(msg, "Got this as buffer '%s'", b);
                LOG(msg);               
                
                sprintf(msg, "Add packet with size = %d to list", len);
                LOG(msg);
                sprintf(msg, "Adding the packet with type '%s'", typeAsString);
                LOG(msg);
#endif          
/*...e*/
                data->add(buf, len, type);
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE
                LOG("lbTransfer::recv(...) Answer with 'Got buffer'");
#endif          
/*...e*/
                if (sendString("Got buffer") == 0) {
                        LOG("Could not get answer 'Got buffer'");
                        lastError = ERR_TRANSFER_FAILED;
                        return 0;
                }
/*...sTRANSFER_VERBOSE:28:*/
#ifdef TRANSFER_VERBOSE         
                LOG("Got a packet");
#endif
/*...e*/
            }

/*...e*/
/*...sTRANSFER_VERBOSE:16:*/
#ifdef TRANSFER_VERBOSE    
            LOG("Ending recieving packets");
#endif
/*...e*/
/*...e*/
          } else {
                lastError = ERR_TRANSFER_FAILED;
                LOG("lbTransfer::recv(...) Error: Currently only 'lb_Transfer_Data' is supported");
                return 0;
          }
        } else {
                lastError = ERR_TRANSFER_FAILED;
                LOG("lbTransfer::recv(lb_Transfer_Data & data): Could not get any data type");
                return 0;
        }

//      fprintf(stderr, "Got a complete lb_Transfer_Data object\n");
/*...sTRANSFER_VERBOSE:0:*/
#ifdef TRANSFER_VERBOSE
LOG("lbTransfer::recv() Leave");        
#endif
/*...e*/
        return 1;
}
/*...e*/
/*...e*/

#include "module.h"

#include <lbInclude.h>

/*...slbTransferDataObject:0:*/
lbTransferDataObject::lbTransferDataObject() {
	setType();
}

lbTransferDataObject::~lbTransferDataObject() {
}

void lbTransferDataObject::setType() {
	OTyp = LB_DATA_TRANSFER_OBJECT;
}

lbObject* lbTransferDataObject::clone() const {
	lbTransferDataObject* o = new lbTransferDataObject();

	pLB_TRANSFER_DATA pData = (pLB_TRANSFER_DATA) malloc(getData()->packet_size + sizeof(LB_TRANSFER_DATA));
	memcpy(pData, getData(), getData()->packet_size + sizeof(LB_TRANSFER_DATA));
	
	o->setData(pData);
	
	return o;
}


void lbTransferDataObject::setData(pLB_TRANSFER_DATA pData) {
	data = pData;
	if (data == NULL) LOG("lbTransferDataObject::setData(): Error, data pointer is null");
}

pLB_TRANSFER_DATA lbTransferDataObject::getData() const {
	if (data == NULL) LOG("lbTransferDataObject::getData(): Error, data pointer is null");
	return data;
}
/*...e*/
/*...slb_Transfer_Data:0:*/
/*...slb_Transfer_Data\58\\58\lb_Transfer_Data\40\\41\:0:*/
lb_Transfer_Data::lb_Transfer_Data() {
	elements = new lbComponentDictionary();
	packet_count = 0;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\\126\lb_Transfer_Data\40\\41\:0:*/
lb_Transfer_Data::~lb_Transfer_Data() {
	if (elements != NULL) delete elements;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\hasMorePackets\40\\41\:0:*/
int lb_Transfer_Data::hasMorePackets() const {
	return elements->hasMoreElements();
}
/*...e*/
/*...slb_Transfer_Data\58\\58\addPacket\40\pLB_TRANSFER_DATA data\41\:0:*/
int lb_Transfer_Data::addPacket(pLB_TRANSFER_DATA data) {
	return 0;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getNextPacket\40\\41\:0:*/
pLB_TRANSFER_DATA lb_Transfer_Data::getNextPacket() const {
	lbTransferDataObject *o = (lbTransferDataObject*) elements->nextElement();
	if (o->getData() == NULL) LOG("lbTransferDataObject contains no data!");
	return o->getData();
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getPacketCount\40\\41\:0:*/
int lb_Transfer_Data::getPacketCount() const {
	return packet_count;
}
/*...e*/

/*...slb_Transfer_Data\58\\58\resetPositionCount\40\\41\:0:*/
int lb_Transfer_Data::resetPositionCount() {
	currentPos = 1;

	return 1;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\incrementPosition\40\\41\:0:*/
int lb_Transfer_Data::incrementPosition() {
	currentPos++;
	
	return (currentPos > packet_count) ? 0 : 1;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getPacketType\40\LB_PACKET_TYPE \38\ type\41\:0:*/
int lb_Transfer_Data::getPacketType(LB_PACKET_TYPE & type) {
	lbTransferDataObject *o;
	
	char msg[100];
	sprintf(msg, "Lookup element for key %d", currentPos);
	LOG(msg);
	
	o = (lbTransferDataObject*) elements->getElement(lbKey(currentPos));
	
	type = o->getData()->packet_type;
	
	return 1;
}
/*...e*/

/*...slb_Transfer_Data setters:0:*/
/*...slb_Transfer_Data\58\\58\add\40\const char\42\ c\41\:0:*/
void lb_Transfer_Data::add(const char* c) {
	if (c != NULL) {
		int len = strlen(c)+1;// '\0' at the end must also be in buffer
		
		add((void*) c, len, LB_CHAR);
	}
}
/*...e*/
/*...slb_Transfer_Data\58\\58\add\40\const void\42\ buf\44\ int len\41\:0:*/
void lb_Transfer_Data::add(const void* buf, int len) {
	if (buf != NULL) {
		add((void*) buf, len, LB_VOID);
	}
}
/*...e*/

/* Not yet implemented
	void add(int i);
	void add(short s);
	void add(long l);
	void add(unsigned short us);
	void add(unsigned long ul);
*/
/*...e*/

/*...slb_Transfer_Data getters:0:*/
int lb_Transfer_Data::get(int& i) {
	LOG("lb_Transfer_Data::get(int& i): Error, this function is not yet implemented !!!");
	return 0;
}

int lb_Transfer_Data::get(char* & c) {
	LB_PACKET_TYPE type;
	
	getPacketType(type);
	
	if (type == LB_CHAR) {
		lbKey key = lbKey(currentPos);
		lbTransferDataObject *o;
		o = (lbTransferDataObject*) elements->getElement(key);
		
		c = (char*) malloc(o->getData()->packet_size);
		memcpy(c, (void const*) &(o->getData()->data), 
		          o->getData()->packet_size);
		return 1;
	} else return 0;
}

int lb_Transfer_Data::get(void* & v, int & len) {
        LB_PACKET_TYPE type;

        getPacketType(type);

        if (type == LB_VOID) {
                lbKey key = lbKey(currentPos);
                lbTransferDataObject *o;
                o = (lbTransferDataObject*) elements->getElement(key);

                v = (char*) malloc(o->getData()->packet_size);
                memcpy(v, (void const*) &(o->getData()->data),
                          o->getData()->packet_size);
                return 1;
        } else return 0;
}
/*...e*/


/**
 * The really function who is adding. This function begins with an index
 * of 1.
 */
/*...slb_Transfer_Data\58\\58\add\40\const void\42\ buf\44\ int len\44\ LB_PACKET_TYPE type\41\:0:*/
void lb_Transfer_Data::add(const void* buf, int len, LB_PACKET_TYPE type) {
	pLB_TRANSFER_DATA data;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lb_Transfer_Data::add() called");
#endif
/*...e*/
	if (buf != NULL) {
		int datalen = sizeof(LB_TRANSFER_DATA);

		int resultlen = datalen + len;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
char msg[100];
sprintf(msg, "lb_Transfer_Data::add() adds a LB_TRANSFER_DATA object with size = %d", resultlen);
LOG(msg);
#endif
/*...e*/
		data = (pLB_TRANSFER_DATA) malloc(resultlen);

		data->packet_size = len;
		data->packet_type = type;
		data->packet_no = ++packet_count;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(msg, "Do memcpy from %x to %x", buf, data->data);
LOG(msg);
#endif
/*...e*/
		memcpy(&(data->data), buf, len);
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Done memcpy");
#endif
/*...e*/
		lbTransferDataObject o;

		o.setData(data);

		if (o.getData() == NULL) 
		  LOG("lbTransferDataObject::add(): Error, add does not work correctly!");

		char msg[100];
		sprintf(msg, "Create key with number %d", packet_count);
		LOG(msg);

		lbKey key = lbKey(packet_count);
		
		elements->insert(o, key);
		
		if (elements->exists(key) == 0)
		  LOG("lb_Transfer_Data::add(...): Error, add could not insert object");
		else {
			lbTransferDataObject *e;
			e = (lbTransferDataObject*) elements->getElement(key);
			
			if (e != NULL) {
				if (e->getData() == NULL)
				  LOG("lb_Transfer_Data::add(...): Error, lbTransferDataObject has no data!");
			}
		}
		//packet_count++;
	}
}
/*...e*/
/*...e*/
/*...slbTransfer:0:*/
/*...slbTransfer\58\\58\lbTransfer\40\\41\:0:*/
lbTransfer::lbTransfer() {
LOGENABLE("lbTransfer::lbTransfer()");
	sock = new lbSocket();
	laststate = 1;
	connected = 0;
}
/*...e*/
/*...slbTransfer\58\\58\\126\lbTransfer\40\\41\:0:*/
lbTransfer::~lbTransfer() {
	if (sock != NULL) delete sock;
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::init(char *target) called");
#endif
/*...e*/
	strcpy(token, strtok(target, "/"));
	machine = strdup(token);
	strcpy(token, strtok(NULL, "/"));
	service = strdup(token);

	if (service == NULL) {
		LOG("lbTransfer::init(char *target): Service name couldn't retrieved from target string!");
		// Handle error
	}

	if (machine == NULL) {
		LOG("lbTransfer::init(char *target): Machine name couldn't retrieved from target string!");
	}

	subservice = strtok(NULL, "/");

	if (subservice == NULL) {
		/**
		 * machine is the computername. Service is the name of a service
		 * mapped to a port.
		 */
/*...sVERBOSE:0:*/
#ifdef VERBOSE
char buf[100];
sprintf(buf, "void lbTransfer::init(char *target): sock->initSymbolic(%s, %s);", machine, service);
LOG(buf);
#endif
/*...e*/
		sock->initSymbolic(machine, service);
		strcpy(prefix, (sock->isServer() == 1) ? "Server: " : "Client: ");
		LOGPREFIX(prefix);
	} else {
		LOG("Subservices currently not supported");
		// Handle special cases with subservices
	}
}
/*...e*/

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

char* getStringFromEnumeration(LB_PACKET_TYPE type) {
	if (type == LB_CHAR) return "LB_CHAR";
	if (type == LB_INT) return "LB_INT";
	if (type == LB_SHORT) return "LB_SHORT";
	if (type == LB_LONG) return "LB_LONG";
	if (type == LB_USHORT) return "LB_USHORT";
	if (type == LB_ULONG) return "LB_ULONG";
	if (type == LB_VOID) return "LB_VOID";
	if (type == LB_OBJECT) return "LB_OBJECT";
	return "LB_INVALIDTYPE";
}

LB_PACKET_TYPE getEnumerationFromString(char* typeAsString) {
	if (strcmp(typeAsString, "LB_CHAR") == 0) {
		LOG("getEnumerationFromString(...) returns LB_CHAR");
		return LB_CHAR;
	}
	if (strcmp(typeAsString, "LB_INT") == 0) return LB_INT;
	if (strcmp(typeAsString, "LB_SHORT") == 0) return LB_SHORT;
	if (strcmp(typeAsString, "LB_LONG") == 0) return LB_LONG;
	if (strcmp(typeAsString, "LB_USHORT") == 0) return LB_USHORT;
	if (strcmp(typeAsString, "LB_ULONG") == 0) return LB_ULONG;
	if (strcmp(typeAsString, "LB_VOID") == 0) return LB_VOID;
	if (strcmp(typeAsString, "LB_OBJECT") == 0) return LB_OBJECT;
	return LB_INVALIDTYPE;
}

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

	LOG("lbTransfer: Reseting server statemachine sucseeded");
	return 1;
}
/*...e*/

/*...slbTransfer\58\\58\sendDatatype\40\char\42\ type\41\:0:*/
int lbTransfer::sendDatatype(char* type) {
	if (sock->send_charbuf(type, strlen(type)+1) == 0) {
		LOG("lbTransfer::sendDatatype(char* type): Failed to send packet type information");
		return 0;
	}
	return 1;
}
/*...e*/
/*...slbTransfer\58\\58\waitforAnswer\40\char\42\ answer\41\:0:*/
int lbTransfer::waitforAnswer(char* answer) {
	char buf[MAXBUFLEN];
	char msg[100];

/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(buf, "waitforAnswer('%s') called", answer);
LOG(buf);
#endif
/*...e*/
	if (sock->recv_charbuf(buf) == 0)  {
		LOG("lbSocket: Failed to get any answer");
		return 0;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(msg, "Got answer '%s'", buf);
LOG(msg);
#endif	
/*...e*/


	if (strcmp(buf, "Protokol error") == 0) LOG("Got an error in protokol flow");

	if (strcmp(buf, answer) != 0) {
		sprintf(msg, "lbSocket: Incorrect answer '%s'. Try to reset state machine", buf);
		LOG(msg);
		resetServerStateMachine();
		return 0;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("waitforAnswer(char* answer) returning");	
#endif
/*...e*/
fprintf(stderr, "waitforAnswer(): Got correct answer '%s'\n", answer);
	return 1;
}
/*...e*/
/*...slbTransfer\58\\58\sendString\40\char\42\ type\41\:0:*/
int lbTransfer::sendString(char* type) {
	if (sock->send_charbuf(type, strlen(type)+1) == 0) {
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

	if (sock->sendInteger(c) == 0) {
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::sendBuffer(void* buf, int len) Enter");
#endif
/*...e*/
	if (sendString("Datablock") == 0) {
		LOG("lbTransfer: Could not send 'Datablock' message");
		resetServerStateMachine();
		return 0;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::sendBuffer(void* buf, int len) waitforAnswer(\"ok\")");
#endif
/*...e*/
	if (waitforAnswer("ok") == 0) {
	LOG("Could not get answer 'ok' after sending 'Datablock'");
		return 0;
	}

/*...sSend buffersize:8:*/
	// Get the size of the packet for memory allocation (if possible)
	if (sock->sendInteger(len) == 0) return 0;	
	if (waitforAnswer("ok") == 0) return 0;
/*...e*/

	int peaces = len / MAXBUFLEN;
	byte * currbufferpos = buf;
	char msg[100];
	

	// target knows multiple packets from buffersize > MAXBUFLEN !
	for (int i = 0; i < peaces; i++) {
	if (i == 0) LOG("Sending subsequent packets");
	
		if (sock->send((void* )currbufferpos, MAXBUFLEN) == 0) return 0;
		currbufferpos = currbufferpos + MAXBUFLEN;
		if (waitforAnswer("Peace ok") == 0) return 0;
	}
	
	// Send remaining
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Send remaining");
#endif
/*...e*/
	//currbufferpos = currbufferpos + (len-peaces*MAXBUFLEN);
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	sprintf(msg, "Sending this buffer: '%s'", (char*) currbufferpos);
	LOG(msg);
#endif
/*...e*/
	if (sock->send((void* )currbufferpos, (len-peaces*MAXBUFLEN)) == 0) return 0;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Wait for answer 'ok'");
#endif
/*...e*/
	if (waitforAnswer("Buffer ok") == 0) {
		LOG("Got incorrect answer");
		return 0;
	}
	return 1;
}
/*...e*/

/*...slbTransfer\58\\58\waitForString\40\char\42\ \38\ string\41\:0:*/
int lbTransfer::waitForString(char* & string) {
	char buf[MAXBUFLEN];

	if (sock->recv_charbuf(buf) == 0)
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
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::waitForBuffer(void * & buffer, int & len) Enter");
#endif
/*...e*/
	if (waitforAnswer("Datablock") == 0) {
		LOG("Could not get 'Datablock' identifer");
		return 0;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("sendString(\"ok\")");
#endif
/*...e*/
	if (sendString("ok") == 0) return 0;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("sock->recv_charbuf((char*) buf)");
#endif
/*...e*/
/*...sGet buffersize:8:*/
	// Get the size of the packet for memory allocation (if possible)
	if (sock->recvInteger(buflen) == 0) return 0;	
	
	if (sendString("ok") == 0) return 0;
/*...e*/
	len = buflen;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(msg, "Got a buffersize of %d bytes", len);
LOG(msg);
#endif	
/*...e*/
	buffer = (byte*) malloc(buflen);

	int peaces = buflen / MAXBUFLEN;
	byte * currbufferpos = buffer;

/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(msg, "Calculated values: peaces = %d, currbufferpos = %x", peaces, currbufferpos);
LOG(msg);
#endif
/*...e*/

	// target knows multiple packets from buffersize > MAXBUFLEN !
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Begin reciefing buffer");
#endif
/*...e*/
	for (int i = 0; i < peaces; i++) {
	if (i == 0) LOG("Recieving subsequent packets");
		int gotBuflen = MAXBUFLEN;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Recv peace");
#endif
/*...e*/
		if (sock->recv((void* )currbufferpos, gotBuflen) == 0) {
			LOG("sock->recv((void* )currbufferpos, gotBuflen) failed");
			return 0;
		}
/*...sVERBOSE:0:*/
#ifdef VERBOSE	
		sprintf(msg, "Wanted buflen: %d. Got this: %d", buflen, gotBuflen);
		LOG(msg);
#endif		
/*...e*/
		currbufferpos = currbufferpos + MAXBUFLEN;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Send 'ok'");
#endif
/*...e*/
		if (sendString("Peace ok") == 0) {
			LOG("Cannot send answer 'Peace ok'");
			return 0;
		}
	}
	
	// Recv remaining
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Recieving remaining");	
#endif
/*...e*/
//	currbufferpos = currbufferpos + (buflen-peaces*MAXBUFLEN);
	int wanted_peace_size = (buflen-peaces*MAXBUFLEN);
/*...sVERBOSE:0:*/
#ifdef VERBOSE
sprintf(msg, "Calculated values: peaces = %d, currbufferpos = %x, torecv = %d", peaces, currbufferpos, (buflen-peaces*MAXBUFLEN));
LOG(msg);
#endif
/*...e*/
	if (sock->recv((void* )currbufferpos, wanted_peace_size) == 0) {
		LOG("Can't get buffer");
		return 0;
	}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
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

/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::waitForBuffer(void * & buffer, int & len) Leave");
#endif
/*...e*/

	return 1;	
}
/*...e*/


/*...slbTransfer\58\\58\waitForDataCount\40\int \38\ c\41\:0:*/
int lbTransfer::waitForDataCount(int & c) {
fprintf(stderr, "waitForDataCount() called\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("waitForDataCount() Enter");
#endif
/*...e*/
	if (waitforAnswer("DataCount") == 0) return 0;
fprintf(stderr, "Got 'DataCount' identifer\n");	
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("Got 'DataCount' identifer");
#endif
/*...e*/
	if (sendString("ok") == 0) return 0;
fprintf(stderr, "Sent 'ok'\n");
	if (sock->recvInteger(c) == 0) return 0;
fprintf(stderr, "Got integer\n");	
	if (sendString("Datacount ok") == 0) return 0;
fprintf(stderr, "Sent 'Datacount ok'\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("waitForDataCount() Leave");
#endif
/*...e*/
	return 1;
}
/*...e*/

/*...slbTransfer\58\\58\waitForDatatype\40\char\42\ \38\ result\41\:0:*/
int lbTransfer::waitForDatatype(char* &result) {
        static char buf[MAXBUFLEN];
        int err;
        
        if ((err = sock->recv_charbuf(buf)) == 0)
        {
                LOG("lbSocket: Failed to get any datatype");
                result = '\0';
        } else result = strdup(buf);
        
        return err;
}
/*...e*/
/*...e*/

int lbTransfer::gethostname(char* &name) {
	return sock->gethostname(name);
}

/*...slbTransfer\58\\58\accept\40\\41\:0:*/
void lbTransfer::accept() {
	fprintf(stderr, "Waiting for a connection...\n");
	sock->accept();
	fprintf(stderr, "Got a connection.");
}
/*...e*/

/*...slbTransfer\58\\58\operator\60\\60\ \40\const lb_Transfer_Data\38\ req\41\:0:*/
void lbTransfer::operator<< (const lb_Transfer_Data& req) {
	if (laststate == 1)
		laststate = send(req);
	else
		LOG("Transfer: There was a previous error. Could not send any more");
}
/*...e*/
/*...slbTransfer\58\\58\operator\62\\62\ \40\lb_Transfer_Data\38\ res\41\:0:*/
void lbTransfer::operator>> (lb_Transfer_Data& res) {
printf("lbTransfer::operator>> (lb_Transfer_Data& res) called\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOGENABLE("lbTransfer::operator>> (lb_Transfer_Data& res) called");
#endif
/*...e*/
	if (laststate == 1)
		laststate = recv(res);
	else
		LOG("Transfer: There was a previous error. Could not recieve any more");
}
/*...e*/

/*...slbTransfer\58\\58\send\40\const lb_Transfer_Data \38\ data\41\:0:*/
int lbTransfer::send(const lb_Transfer_Data & data) {
	char buf[MAXBUFLEN];
	char msg[100];
sprintf(msg, "lbTransfer::send(const lb_Transfer_Data & data): Sending %d packets", data.getPacketCount());	
LOG(msg);
	
	
	if (sendDatatype("lb_Transfer_Data") == 0) return 0;
	if (waitforAnswer("Datatype ok") == 0) return 0;
	if (sendDataCount(data.getPacketCount()) == 0) return 0;

	while (data.hasMorePackets()) {
		pLB_TRANSFER_DATA pData = data.getNextPacket();
/*...sVERBOSE:0:*/
#ifdef VERBOSE
		sprintf(msg, "Send a packet with address %x", pData);
		LOG(msg);
#endif
/*...e*/
		if (pData == NULL) 
			LOG("lbTransfer::send(const lb_Transfer_Data & data): Error, can't send buffer. Null pointer exception.");
		else {
/*...sVERBOSE:0:*/
#ifdef VERBOSE
			LOG("Send a packet from LB_TRANSFER_DATA");
			sprintf(msg, "Try to copy buffer to a char buffer. It's address: %x", pData->data);
			LOG(msg);
			char sendbuffer[100];
			strncpy(sendbuffer, (char*) &(pData->data), pData->packet_size);
			sprintf(msg, "Buffer '%s' has been copied", sendbuffer);
			LOG(msg);
#endif		
/*...e*/
			// Send the packet type
			sprintf(msg, "Sending packet type: '%s'", getStringFromEnumeration(pData->packet_type));
			LOG(msg);
			if (sendString(getStringFromEnumeration(pData->packet_type)) == 0) return 0;
			if (waitforAnswer("ok") == 0) return 0;
			
			if (sendBuffer((byte*) &(pData->data), pData->packet_size) == 0) {
				LOG("lbTransfer: Could not send data buffer");
			resetServerStateMachine();
			return 0;
			}
/*...sVERBOSE:0:*/
#ifdef VERBOSE
			LOG("waitforAnswer('Got buffer')");
#endif
/*...e*/
			if (waitforAnswer("Got buffer") == 0) {
				LOG("Could not get answer 'Got buffer'");
				return 0;
			}
/*...sVERBOSE:0:*/
#ifdef VERBOSE			
			LOG("Sent a packet from LB_TRANSFER_DATA");
#endif
/*...e*/
		}
	}
	return 1;
}
/*...e*/

/*...slbTransfer\58\\58\recv\40\lb_Transfer_Data \38\ data\41\:0:*/
int lbTransfer::recv(lb_Transfer_Data & data) {
	char* result = NULL;
	void* buf = NULL;
        char msg[100];
	int err;

LOGENABLE("lbTransfer::recv(lb_Transfer_Data & data)");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::recv() Enter");
#endif
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::recv(lb_Transfer_Data & data): waitForDatatype(result)...");	
#endif
/*...e*/
	if ((err = waitForDatatype(result)) == 1) {
	  if (strcmp(result, "lb_Transfer_Data") == 0)
	  {// Got correct datatype
	    int count = 0;
	    lb_Transfer_Data temp;
	    int len;
	    
	    fprintf(stderr, "Got datatype information of '%s'\n", result);
/*...sVERBOSE:0:*/
#ifdef VERBOSE	   
	    LOG("lbTransfer::recv(lb_Transfer_Data & data): Got wanted datatype");
#endif
/*...e*/
	    if (sendString("Datatype ok") == 0) return 0;
	   
	    fprintf(stderr, "Waiting for packet count\n");
	   
/*...swaitForDataCount:12:*/
	    if (waitForDataCount(count) == 0) {
	    	fprintf(stderr, "Waiting for packet count: Results in an error\n");
	    	return 0;
	    }
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
	    sprintf(msg, "Begin with recieving %d packets", count);
	    LOG(msg);
#endif
/*...e*/
/*...sGet all packets:12:*/
	    while (count != 0) {
/*...sVERBOSE:12:*/
#ifdef VERBOSE
	        sprintf(msg, "Get a packet (%d)", count);
	        LOG(msg);
#endif
/*...e*/
	        count--;
	        int ptypelen = sizeof(LB_PACKET_TYPE);
	        LB_PACKET_TYPE type;
	        char* typeAsString = NULL;
	        if (waitForString(typeAsString) == 0) return 0;
	        
	        sprintf(msg, "Got packet type '%s'", typeAsString);
	        LOG(msg);
	        
	        type = getEnumerationFromString(typeAsString);
	        
	        if (type != LB_INVALIDTYPE) {
	        	if (sendString("ok") == 0) return 0;
	        } else { 
	        	if (sendString("Protokol error") == 0) return 0;
	        }
	        
		if (waitForBuffer((byte* &) buf, len) == 0) return 0;    	
/*...sVERBOSE:12:*/
#ifdef VERBOSE
		char b[100];
		
		strncpy(b, (char*)buf, len);
		b[len] = 0;
		
		sprintf(msg, "Got this as buffer '%s'", b);
		LOG(msg);		
		
		sprintf(msg, "Add packet with size = %d to list", len);
		LOG(msg);
#endif		
/*...e*/
		data.add(buf, len, type);
/*...sVERBOSE:12:*/
#ifdef VERBOSE
		LOG("Added packet to list");
#endif		
/*...e*/

		if (sendString("Got buffer") == 0) {
			LOG("Could not get answer 'Got buffer'");
			return 0;
		}


/*...sVERBOSE:12:*/
#ifdef VERBOSE		
		LOG("Got a packet");
#endif
/*...e*/
	    }	    
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE	   
	    LOG("Ending recieving packets\n");
#endif
/*...e*/
	  }
	} else LOG("lbTransfer::recv(lb_Transfer_Data & data): Could not get data type");

	fprintf(stderr, "Got a complete lb_Transfer_Data object\n");
/*...sVERBOSE:0:*/
#ifdef VERBOSE
LOG("lbTransfer::recv() Leave");	
#endif
/*...e*/
	return 1;
}
/*...e*/
/*...e*/



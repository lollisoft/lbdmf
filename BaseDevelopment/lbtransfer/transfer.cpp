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

	pLB_TRANSFER_DATA pData = (pLB_TRANSFER_DATA) malloc(getData()->packet_size);
	memcpy(pData, getData(), getData()->packet_size);
	return o;
}


void lbTransferDataObject::setData(pLB_TRANSFER_DATA pData) {
	data = pData;
}

pLB_TRANSFER_DATA lbTransferDataObject::getData() const {
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
	return ((lbTransferDataObject*) elements->nextElement())->getData();
}
/*...e*/
/*...slb_Transfer_Data\58\\58\getPacketCount\40\\41\:0:*/
int lb_Transfer_Data::getPacketCount() const {
	return packet_count;
}
/*...e*/
/*...slb_Transfer_Data\58\\58\add\40\const char\42\ c\41\:0:*/
void lb_Transfer_Data::add(const char* c) {
	char buf[100];
	pLB_TRANSFER_DATA data;

	if (c != NULL) {
		int len = strlen(c);
		int datalen = sizeof(LB_TRANSFER_DATA);

		int resultlen = datalen + len;

		data = (pLB_TRANSFER_DATA) malloc(resultlen);

		data->packet_size = resultlen;
		data->packet_type = LB_CHAR;
		data->packet_no = ++packet_count;

		memcpy(&(data->data), (void*) c, len);

		lbTransferDataObject o;

		o.setData(data);

		elements->insert(o, lbKey(packet_count));
	}
}
/*...e*/
/*...e*/
/*...slbTransfer:0:*/
/*...slbTransfer\58\\58\lbTransfer\40\\41\:0:*/
lbTransfer::lbTransfer() {
printf("lbTransfer::lbTransfer() initializing...\n");
LOGENABLE("lbTransfer::lbTransfer()");
LOG("lbTransfer::lbTransfer() initializing...");
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

printf("lbTransfer::init(char *target) called\n");
LOG("lbTransfer::init(char *target) called");

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
char buf[100];
sprintf(buf, "void lbTransfer::init(char *target): sock->initSymbolic(%s, %s);", machine, service);
LOG(buf);
		sock->initSymbolic(machine, service);
	} else {
		LOG("Subservices currently not supported");
		// Handle special cases with subservices
	}
	LOG("lbTransfer::init(char *target) returns");
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
	
	if (sock->recv_charbuf(buf) == 0)
		LOG("lbSocket: Failed to get any answer");
		
	if (strcmp(buf, answer) != 0) {
		LOG("lbSocket: Incorrect answer. Try to reset state machine");
		resetServerStateMachine();
		return 0;
	}

	return 1;
}
/*...e*/
/*...slbTransfer\58\\58\sendDataCount\40\int c\41\:0:*/
int lbTransfer::sendDataCount(int c) {
	if (sock->send_charbuf("DataCount", strlen("DataCount")+1) == 0) {
		LOG("lbTransfer: Could not send data count information");
	}
	
	if (waitforAnswer("ok") == 0) return 0;

	if (sock->sendInteger(c) == 0) {
		LOG("lbTransfer: Could not send integer value");
		resetServerStateMachine();
		return 0;
	}
	
	if (waitforAnswer("ok") == 0) return 0;

	return 1;	
}
/*...e*/
/*...slbTransfer\58\\58\sendBuffer\40\void\42\ buf\44\ int len\41\:0:*/
int lbTransfer::sendBuffer(void* buf, int len) {
	if (sock->send_charbuf("Datablock", strlen("Datablock")+1) == 0) {
		LOG("lbTransfer: Could not send 'Datablock' message");
		resetServerStateMachine();
		return 0;
	}

	if (waitforAnswer("ok") == 0) return 0;
	
	if (sock->send_charbuf((char*) buf, len) == 0) {
		LOG("lbTransfer: Could not send the data buffer self");
		resetServerStateMachine();
		return 0;
	}

	if (waitforAnswer("ok") == 0) return 0;

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
LOGENABLE("lbTransfer::operator>> (lb_Transfer_Data& res) called");
	if (laststate == 1)
		laststate = recv(res);
	else
		LOG("Transfer: There was a previous error. Could not recieve any more");
}
/*...e*/

/*...slbTransfer\58\\58\send\40\const lb_Transfer_Data \38\ data\41\:0:*/
int lbTransfer::send(const lb_Transfer_Data & data) {
	char buf[MAXBUFLEN];
	
	if (sendDatatype("lb_Transfer_Data") == 0) return 0;

	if (waitforAnswer("Datatype ok") == 0) return 0;

	if (sendDataCount(data.getPacketCount()) == 0) return 0;
	
	while (data.hasMorePackets()) {
		pLB_TRANSFER_DATA pData = data.getNextPacket();
		if (sendBuffer(pData, pData->packet_size) == 0) {
			LOG("lbTransfer: Could not send data buffer");
			resetServerStateMachine();
			return 0;
		}
	}

	return 1;
}
/*...e*/
/*...slbTransfer\58\\58\recv\40\lb_Transfer_Data \38\ data\41\:0:*/
int lbTransfer::recv(lb_Transfer_Data & data) {
	char* result = NULL;
	int err;

LOGENABLE("lbTransfer::recv(lb_Transfer_Data & data)");
LOG("lbTransfer::recv(lb_Transfer_Data & data): waitForDatatype(result)...");	

	if ((err = waitForDatatype(result)) == 1) {
		if (strcmp(result, "lb_Transfer_Data") == 0)
			LOG("lbTransfer::recv(lb_Transfer_Data & data): Got wanted datatype");
	} else LOG("lbTransfer::recv(lb_Transfer_Data & data): Could not get data type");
	
	
	
	
	return 1;
}
/*...e*/
/*...e*/



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

/*...senum LB_PACKET_TYPE:0:*/
typedef enum {
	LB_INVALIDTYPE,
	LB_INT,
	LB_CHAR,
	LB_SHORT,
	LB_LONG,
	LB_USHORT,
	LB_ULONG,
	LB_VOID,

	LB_OBJECT,	// The basic type of lbObject
} LB_PACKET_TYPE;
/*...e*/

typedef byte LB_DATA;

/*...sLB_TRANSFER_DATA:0:*/
typedef struct {
	u_short			packet_no;
	LB_PACKET_TYPE		packet_type;
	u_short			packet_size;
	LB_DATA			data;
} LB_TRANSFER_DATA, * pLB_TRANSFER_DATA;
/*...e*/

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
class DLLEXPORT lb_Transfer_Data {
public:
	lb_Transfer_Data();
	virtual ~lb_Transfer_Data();

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
	int get(int& i);
	int get(char* & c);
	int get(short & s);
	int get(long & l);
	int get(unsigned short & us);
	int get(unsigned long & ul);

	int get(void* & v, int & len);
/*...e*/
	
	/**
	 * The really function who is adding
	 */
	void add(const void* buf, int len, LB_PACKET_TYPE type);


	/**
	 * Use dictionary yet
	 */
	lbComponentDictionary* elements;
	int packet_count;
	int currentPos;
};
/*...e*/
/*...slbTransfer:0:*/
class DLLEXPORT lbTransfer {
public:
	lbTransfer();
	~lbTransfer();

	/**
	 * The target parameter is build up like an internet address.
	 * Exsample: //anakin/service/subservice
	 */
	void init(char *target);

	/**
	 * Got a connection...
	 */
	int accept(lbTransfer*& t);

	void operator<< (const lb_Transfer_Data& req);

	void operator>> (lb_Transfer_Data& res);


	int gethostname(char* &name);
private:
	lbTransfer(lbTransfer* t);

	int recv(lb_Transfer_Data & data);
	int send(const lb_Transfer_Data & data);

	int setSockConnection(lbSocket* s);


	int resetServerStateMachine();
	int sendDatatype(char* type);
	int waitforAnswer(char* answer);
	int sendDataCount(int c);
	int sendBuffer(byte* buf, int len);
	int sendString(char* type);
	int waitForString(char* & string);
	int waitForDataCount(int & c);
	int waitForDatatype(char* & result);
	int waitForBuffer(byte * & buffer, int & len);

	lbSocket* sock;
	int laststate;
	int connected;
	
	LB_TRANSFER_STATE state;
	
	/**
	 * This authentification parameters are initialized once per
	 * thread. Then it is used when ever data is transferred.
	 */
	char AuthUser[100];
	char AuthPass[100];
};
/*...e*/

#endif // LB_TRANSFER

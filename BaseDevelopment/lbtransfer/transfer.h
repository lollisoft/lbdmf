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
	LB_INT,
	LB_CHAR,
	LB_SHORT,
	LB_LONG,
	LB_USHORT,
	LB_ULONG,

	LB_OBJECT,	// The basic type of lbObject
} LB_PACKET_TYPE;
/*...e*/

typedef byte LB_DATA;

/*...sLB_TRANSFER_DATA:0:*/
typedef struct {
	u_short			packet_no;
	LB_PACKET_TYPE	packet_type;
	u_short			packet_size;
	LB_DATA			data;
} LB_TRANSFER_DATA, * pLB_TRANSFER_DATA;
/*...e*/

class lbComponentDictionary;
class lbSocket;

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

	/**
	 * Data member operations
	 */

	void add(int i);
	void add(const char* c);
	void add(short s);
	void add(long l);
	void add(unsigned short us);
	void add(unsigned long ul);

	 /**
	  * Use dictionary yet
	  */

	 lbComponentDictionary* elements;
	 int packet_count;
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

	void operator<< (const lb_Transfer_Data& req);

	void operator>> (lb_Transfer_Data& res);

private:
	int recv(lb_Transfer_Data & data);
	int send(const lb_Transfer_Data & data);

	int resetServerStateMachine();
	int sendDatatype(char* type);
	int waitforAnswer(char* answer);
	int sendDataCount(int c);
	int sendBuffer(void* buf, int len);
	
	int waitForDatatype(char* & result);

	lbSocket* sock;
	int laststate;
	int connected;
};
/*...e*/

#endif // LB_TRANSFER

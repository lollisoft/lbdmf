#ifndef __LB_SUB_TRANSFER__
#define __LB_SUB_TRANSFER__

/*...senum LB_PACKET_TYPE:0:*/
typedef enum {
        PACKET_LB_INVALIDTYPE,
        PACKET_LB_INT,
        PACKET_LB_CHAR,
        PACKET_LB_SHORT,
        PACKET_LB_LONG,
        PACKET_LB_USHORT,
        PACKET_LB_ULONG,
        PACKET_LB_VOID,

        PACKET_LB_OBJECT,       // The basic type of lbObject
} LB_PACKET_TYPE;
/*...e*/

/*...sLB_TRANSFER_DATA:0:*/
typedef struct {
        u_short                 packet_no;
        LB_PACKET_TYPE          packet_type;
        u_short                 packet_size;
        LB_DATA                 data;
} LB_TRANSFER_DATA, * pLB_TRANSFER_DATA;
/*...e*/

/*...sclass lb_I_Transfer_Data:0:*/
class lb_I_Transfer_Data {
protected:
        lb_I_Transfer_Data() {}
        virtual ~lb_I_Transfer_Data() {}
public:

        lb_I_Transfer_Data& operator= (const lb_I_Transfer_Data & t) {
                return assign(t);
        }

        virtual lb_I_Transfer_Data& assign(const lb_I_Transfer_Data & t) = 0;
        
        virtual int hasMorePackets() const = 0;
        virtual pLB_TRANSFER_DATA getNextPacket() const = 0;

        virtual int getPacketCount() const = 0;
        virtual LB_PACKET_TYPE getNextPacketType() = 0;

        virtual int addPacket(pLB_TRANSFER_DATA data) = 0;

        virtual int resetPositionCount() = 0;
        virtual int incrementPosition() = 0;
        virtual int getPacketType(LB_PACKET_TYPE & type) = 0;

        virtual int deleteAll() = 0;

/*...ssetters:8:*/
        /**
         * Data member operations
         */

        virtual void add(int i) = 0;
        virtual void add(const char* c) = 0;
        virtual void add(short s) = 0;
        virtual void add(long l) = 0;
        virtual void add(unsigned short us) = 0;
        virtual void add(unsigned long ul) = 0;
        virtual void add(const void* buf, int len) = 0;
/*...e*/

/*...sgetters:8:*/
        virtual lbErrCodes get(int& i) = 0;
        virtual lbErrCodes get(char* & c) = 0;
        virtual lbErrCodes get(short & s) = 0;
        virtual lbErrCodes get(long & l) = 0;
        virtual lbErrCodes get(unsigned short & us) = 0;
        virtual lbErrCodes get(unsigned long & ul) = 0;

        virtual lbErrCodes get(void* & v, int & len) = 0;
/*...e*/
        
        /**
         * The really function who is adding
         */
        //void add(const void* buf, int len, LB_PACKET_TYPE type);
};
/*...e*/

#endif // __LB_SUB_TRANSFER__

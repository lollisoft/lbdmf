/*...sCopyright:0:*/
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
/**
 *  \file lbInterfaces-sub-transfer.h
 *  Include for data transfer interfaces.
 */
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
/**
 * \brief Protocolbased data transfer.
 */
class lb_I_Transfer_Data : public lb_I_Unknown {
public:

        lb_I_Transfer_Data& LB_STDCALL operator= (const lb_I_Transfer_Data & t) {
                return assign(t);
        }

        virtual lb_I_Transfer_Data& LB_STDCALL assign(const lb_I_Transfer_Data & t) = 0;
        
        virtual int LB_STDCALL hasMorePackets() const = 0;
        virtual pLB_TRANSFER_DATA  LB_STDCALL getNextPacket() const = 0;

        virtual int LB_STDCALL getPacketCount() const = 0;
        virtual LB_PACKET_TYPE LB_STDCALL getNextPacketType() = 0;
        
        virtual int LB_STDCALL getCurrentPos() const = 0;

        virtual int LB_STDCALL addPacket(pLB_TRANSFER_DATA data) = 0;

        virtual int LB_STDCALL resetPositionCount() = 0;
        virtual int LB_STDCALL incrementPosition() = 0;
        virtual int LB_STDCALL getPacketType(LB_PACKET_TYPE & type) = 0;

        virtual int LB_STDCALL deleteAll() = 0;

	virtual bool LB_STDCALL isServerSide() const = 0;
	

	virtual DWORD LB_STDCALL getClientPid() const = 0;
	virtual void LB_STDCALL setClientPid(DWORD _pid) = 0;

	virtual char* LB_STDCALL getClientHost() const = 0;
	virtual void LB_STDCALL setClientHost(char* host) = 0;

	virtual DWORD LB_STDCALL getClientTid() const = 0;
	virtual void LB_STDCALL setClientTid(DWORD _tid) = 0;

        virtual lbErrCodes LB_STDCALL requestString(char* ident, char*& data) = 0;

        virtual lbErrCodes LB_STDCALL requestString(char* ident) = 0;

        virtual lbErrCodes LB_STDCALL requestInteger(char* ident, int& data) = 0;

        virtual lbErrCodes LB_STDCALL requestULong(char* ident, unsigned long& data) = 0;	

	virtual lbErrCodes LB_STDCALL makeProtoErrAnswer(char* msg, char* where) = 0;

/*...ssimple setters:8:*/
        /**
         * Data member operations
         */

        virtual void LB_STDCALL add(int i) = 0;
        virtual void LB_STDCALL add(const char* c) = 0;
        virtual void LB_STDCALL add(short s) = 0;
        virtual void LB_STDCALL add(long l) = 0;
        virtual void LB_STDCALL add(unsigned short us) = 0;
        virtual void LB_STDCALL add(unsigned long ul) = 0;
        virtual void LB_STDCALL add(const void* buf, int len) = 0;
/*...e*/

/*...ssimple getters:8:*/
        virtual lbErrCodes LB_STDCALL get(int& i) = 0;
        virtual lbErrCodes LB_STDCALL get(char* & c) = 0;
        virtual lbErrCodes LB_STDCALL get(short & s) = 0;
        virtual lbErrCodes LB_STDCALL get(long & l) = 0;
        virtual lbErrCodes LB_STDCALL get(unsigned short & us) = 0;
        virtual lbErrCodes LB_STDCALL get(unsigned long & ul) = 0;

        virtual lbErrCodes LB_STDCALL get(void* & v, int & len) = 0;
/*...e*/
        
        /**
         * The really function who is adding
         */
        virtual void LB_STDCALL add(const void* buf, int len, LB_PACKET_TYPE type) = 0;
};
/*...e*/

/*...sclass lb_I_Stream:0:*/
/** \brief Base of streams.
 *
 * This interface currently is used for passing into lb_I_FileOperation.
 */
class lb_I_Stream :
	public lb_I_Unknown
{
public:

	/** \brief Set the filename.
	 *
	 */
	virtual void LB_STDCALL setFileName(char* name) = 0;

	/** \brief Get the filename.
	 *
	 */
	virtual const char* LB_STDCALL getFileName() = 0;

	/** \brief Open the file.
	 *
	 */
	virtual bool LB_STDCALL open() = 0;

	/** \brief Close the file.
	 *
	 */
	virtual bool LB_STDCALL close() = 0;
};
/*...e*/

/*...sclass lb_I_InputStream:0:*/
/**
 * \brief Filebased data reader.
 */
class lb_I_InputStream : 
	public lb_I_Stream {
public:

	virtual lb_I_String* LB_STDCALL getAsString() = 0;

	/** \brief Read an int data type.
	 *
	 */
	virtual lb_I_InputStream& LB_STDCALL operator>> (int& i) = 0;

	/** \brief Read an long data type.
	 *
	 */
	virtual lb_I_InputStream& LB_STDCALL operator>> (long& i) = 0;

	/** \brief Read a bool data type.
	 *
	 */
	virtual lb_I_InputStream& LB_STDCALL operator>> (bool& b) = 0;
   	
	/** \brief Read a char data type.
	 *
	 */
	virtual lb_I_InputStream& LB_STDCALL operator>> (char& c) = 0;
   	
	/** \brief Read a complete string.
	 *
	 */
	virtual lb_I_InputStream& LB_STDCALL operator>> (char*& string) = 0;

};
/*...e*/

/*...sclass lb_I_OutputStream:0:*/
/**
 * \brief Filebased data writer.
 */
class lb_I_OutputStream : 
	public lb_I_Stream {
public:

	virtual void LB_STDCALL writeToBuffer(bool _buffer) = 0;
	virtual lb_I_String* LB_STDCALL getAsString() = 0;

	/** \brief Write an int data type.
	 *
	 */
	virtual lb_I_OutputStream& LB_STDCALL operator<< (const int i) = 0;

	/** \brief Write an long data type.
	 *
	 */
	virtual lb_I_OutputStream& LB_STDCALL operator<< (const long i) = 0;

	/** \brief Write a bool data type.
	 *
	 */
	virtual lb_I_OutputStream& LB_STDCALL operator<< (const bool b) = 0;

	/** \brief Write a char data type.
	 *
	 */
	virtual lb_I_OutputStream& LB_STDCALL operator<< (const char c) = 0;
	
	/** \brief Write a complete string.
	 *
	 */
	virtual lb_I_OutputStream& LB_STDCALL operator<< (const char* string) = 0;
	
	virtual void LB_STDCALL setBinary() = 0;
};
/*...e*/

/** \brief Simple encryption and decryption API.
 */
class lb_I_CryptoStream : 
	public lb_I_Unknown {
	public:
		virtual bool LB_STDCALL setAlgorythm(char* name) = 0;
		virtual lb_I_CryptoStream& LB_STDCALL operator<< (lb_I_String* string) = 0;
		virtual lb_I_CryptoStream& LB_STDCALL operator>> (lb_I_String* string) = 0;
};


/*...sclass lb_I_Streamable:0:*/
/**
 * \brief Interface for loadable and saveable objects.
 *
 * Use this interface, if you implement streamable objects, that do not delegate the operation for different
 * formats. (No lb_I_Unknown base interface)
 */
class lb_I_Streamable {
public:

#ifdef bla
	/**
	 * \brief Supported column types
	 */
	enum lbStreamTypes {
		lb_I_String,
		lb_I_Integer,
		lb_I_Long,
		lb_I_Container
	};
#endif

	/** \brief Set the instance from where the data comes.
	 * A visitor implementation may not contain code to store
	 * or load private data. Using a plugin delegate that would
	 * do the job, this function is used to set hat object has to
	 * be streamed.
	 *
	 * Currently, this is for implementations of the lb_I_Application
	 * interface.
	 *
	 * Application classes would have fully different intentions, thus
	 * one visitor plugin wouldn't capable to handle them even it could
	 * handle parts of it, it couldn't handle the whole. 
	 */
	virtual lbErrCodes LB_STDCALL setOperator(lb_I_Unknown* streamObject) = 0;

	/** \brief Save to a filebased stream.
	 */
	virtual lbErrCodes LB_STDCALL save(lb_I_OutputStream* oStream) = 0;
	
	/** \brief Load from a filebased stream.
	 */
	virtual lbErrCodes LB_STDCALL load(lb_I_InputStream* iStream) = 0;

	/** \brief Save to a database.
	 */
	virtual lbErrCodes LB_STDCALL save(lb_I_Database* oDB) = 0;
	
	/** \brief Load from a database.
	 */
	virtual lbErrCodes LB_STDCALL load(lb_I_Database* iDB) = 0;
};
/*...e*/

/** \brief A separate stream implementation interface.
 *
 * This interface is used to load and store files with delagated storage usage.
 * Done so in my lb_I_Application sample classes.
 *
 * I do not see a nessesary for separate interfaces for different file formats.
 * This could be handled by plugin namespaces.
 */
class lb_I_StandaloneStreamable :
	public lb_I_Unknown,
	public lb_I_Streamable {
	
};

/*...sclass lb_I_Transfer_DataObject:0:*/
class lb_I_Transfer_DataObject : public lb_I_Unknown {
public:

	virtual void LB_STDCALL setTransferData(pLB_TRANSFER_DATA pData) = 0;
	virtual pLB_TRANSFER_DATA LB_STDCALL getTransferData() const = 0;
};
/*...e*/

/*...sclass lb_I_Transfer:0:*/
class lb_I_Transfer : public lb_I_Unknown {
public:
	virtual void LB_STDCALL init(char *target) = 0;

	virtual int LB_STDCALL isConnected() = 0;

	/**
	 * Got a connection...
	 */
	virtual lb_I_Transfer* LB_STDCALL accept() = 0;

	virtual void LB_STDCALL operator<< (lb_I_Transfer_Data* req) = 0;
	virtual void LB_STDCALL operator>> (lb_I_Transfer_Data* res) = 0;

	/**
	 * This function allows checking for validness of this instance
	 */
	virtual int LB_STDCALL isValid() = 0;

	virtual int LB_STDCALL gethostname(lb_I_String* name) = 0;
	
	virtual lbErrCodes LB_STDCALL getLastError() = 0;
	
	virtual int LB_STDCALL setSockConnection(lb_I_Socket* s) = 0;
};

/*...e*/
/*...sclass lb_I_Socket:0:*/
class lb_I_Socket : public lb_I_Unknown
{
public:
        
	/**
	 * Is this object valid ?
	 */
	virtual int LB_STDCALL isValid() = 0;

	virtual char* LB_STDCALL gethostname() = 0;

	virtual bool LB_STDCALL initSymbolic(char *host, char* service) = 0;
    virtual void LB_STDCALL reinit(char *mysockaddr="") = 0;

//	virtual lbErrCodes LB_STDCALL neagleOff(SOCKET s);

	virtual int LB_STDCALL isServer() = 0; //{ return _isServer; }

	virtual lbErrCodes LB_STDCALL recvInteger(int& i) = 0;
	virtual lbErrCodes LB_STDCALL sendInteger(int i) = 0;
	
	virtual lbErrCodes LB_STDCALL send(void* buf, int len) = 0;

	/**
	 * Buffer must be allocated.
	 */	
	virtual lbErrCodes LB_STDCALL recv(void* buf, int & len) = 0;
		
        virtual lbErrCodes LB_STDCALL recv_charbuf(char *buf) = 0;
        virtual lbErrCodes LB_STDCALL send_charbuf(char *buf, int len) = 0;

	/**
	 * Send and recieve a data buffer and automatically split off to
	 * the max amount of packet size.
	 */
	virtual lbErrCodes LB_STDCALL recv(lb_I_Transfer_Data* data) = 0;
	virtual lbErrCodes LB_STDCALL send(lb_I_Transfer_Data* data) = 0;


        virtual lb_I_Socket* LB_STDCALL accept() = 0;
};
/*...e*/

#endif // __LB_SUB_TRANSFER__

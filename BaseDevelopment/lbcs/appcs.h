/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2000-2007  Lothar Behrens (lothar.behrens@lollisoft.de)

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
#ifndef LB_APPCS
#define LB_APPCS

/*...sclass lbConnection:0:*/
/** \brief Connection properties.
 */
class lbConnection {
public:
	lbConnection(char* host, int _pid, int _tid);
	virtual ~lbConnection();
	
	/**
	 * Abstract functions
	 */
	void setType();
	
	char* hostname;
	int pid;
	int tid;
};
/*...e*/

/**
 * Interface fÅr ein Objekt, das das Ziel eines Requests
 * darstellt. Mit diesem Interface kann man an das Objekt
 * Anfragen stellen.
 */
class lb_I_Requestable; 

class lbAppServer;

DECLARE_FUNCTOR(instanceOflbAppServer)

/*...sclass lbDispatchProto:0:*/
/**
 * \brief An attempt to dispatch several protocols over one tcp port.
 */
class lbDispatchProto : public lb_I_DispatchProtocol {
public:
	lbDispatchProto();
	virtual ~lbDispatchProto();
	
	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setProto(const char* _service, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback fn);	
	
	char* LB_STDCALL getServiceName();
	
	lbProtocolCallback LB_STDCALL getProto();
	
	lb_I_ProtocolTarget* LB_STDCALL getProtocolHandlerInstance();

private:
	
	UAP(lb_I_String, service)
	UAP(lb_I_ProtocolTarget, handler)
	lbProtocolCallback dispProto;
};
/*...e*/

/*...sclass lbProtocolManager:0:*/
/** \brief Protocol manager.
 * This class holds all registered protocol based handlers.
 *
 * These then are available in client server applications.
 */
class lbProtocolManager : 
	public lb_I_Unknown,
	public lb_I_ProtocolManager {

public:
	lbProtocolManager();
	virtual ~lbProtocolManager();
	
	DECLARE_LB_UNKNOWN()
	
	lbErrCodes LB_STDCALL addProtocolHandler(const char* handlername, lbProtocolCallback cbFn);
	lbErrCodes LB_STDCALL delProtocolHandler(const char* handlername);	
};
/*...e*/

/*...sclass lbAppServer:0:*/
/** \brief An application server.
 */
class lbAppServer : public lb_I_ApplicationServer
{
public:
	lbAppServer();
	virtual ~lbAppServer();
	
	DECLARE_LB_UNKNOWN()

	void LB_STDCALL autostartServerPlugins(bool start);
	lbErrCodes LB_STDCALL activateServerPlugin(char* name);

	void LB_STDCALL run(); // called from main or thread

	/**
	 * Checks, if the parameters (hostname, pid and tid) are available.
	 * Then it checks, if tid is as key available in connections container.
	 * If all succeeds, 1 is returned and the request would be done.
	 */
	bool LB_STDCALL isConnected(lb_I_Transfer_Data* request);

	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	
	lbErrCodes LB_STDCALL waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* request);
	
	lbErrCodes LB_STDCALL answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result);

	char* LB_STDCALL getServiceName();
	lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr);	                  

	/**
	 * Called from run() and gives a lb_I_Transfer instance.
	 * This is no longer abstract, because this 'baseclass'
	 * does all the server stuff for now.
	 * A derived server must only make visible its handles
	 * to this base class.
	 */
	lbErrCodes _connected(lb_I_Transfer* _clt); 

	lbErrCodes LB_STDCALL dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
	lbErrCodes LB_STDCALL addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback cbFn);
	lbErrCodes LB_STDCALL delProtocolHandler(const char* handlername);
	 
/*...sDoc:0:*/
	/**
	 * Implement this for your connected state. It is called per request.
	 * I mean, that a socket connection has been opened and the
	 * function is being called. So I am able to put in more logic
	 * before and after the call of this function, like an 
	 * authentication, or a load checking an the ability to react.
	 * You can do what you want in your implementation, but you have
	 * to call the three functions for waiting for, handling and sending
	 * back an answer from the request.
	 * If you do nothig, because you don't need, you don't need to write
	 * a server.
	 * By letting you have to implement this function, you will be able
	 * to do your own stuff between the stages of a request. You may add
	 * some dispatching stuff to divide your service. I will be able to
	 * add some overhead to the request packets like encryption or so.
	 */
/*...e*/

protected:

	lbErrCodes LB_STDCALL HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
	lbErrCodes LB_STDCALL HandleDisconnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);

	/**
	 * User management
	 */
	lbErrCodes makeProtoErrAnswer(lb_I_Transfer_Data* result, char* msg, char* where);
	
	int initServerModul(lb_I_ApplicationServerModul* servermodule);

	lb_I_Transfer *transfer;	
	UAP(lb_I_Container, connections)	
	
	// Dispatch table for registered protocol handlers
	UAP(lb_I_Container, dispatchTable)

	/** \brief Loaded server modules. 
	 * Each servermodule has a name. This name is used as identifer in this container.
	 * Also this name is the identifer for the service name used by the client.
	 */
	UAP(lb_I_Container, serverModules)

	/** \brief Thread per module.
	 * Each module defines a port to listen to. (Via the name of the server module)
	 *
	 * So the main thread must wait for all server threads to be ended before it could
	 * exit.
	 */
	UAP(lb_I_Container, serverThreads)
	
	/** \brief Main application server also can handle requests.
	 * Each request is a separate thread. So they would be stored
	 * as running threads in this container.
	 */
	UAP(lb_I_Container, mainThreads)
	
	/** \brief Threads, that have done it's work. */
	UAP(lb_I_Container, freeThreads)
};
/*...e*/

/*...sclass lbDispatchFn:0:*/
/**
 * \brief An attempt to dispatch function calls.
 */
class lbDispatchFn : public lb_I_DispatchFunction {
public:
	lbDispatchFn();
	virtual ~lbDispatchFn();

	DECLARE_LB_UNKNOWN()

	lbErrCodes LB_STDCALL setFunction(const char* service, lb_I_CallbackTarget* handlerInstance, lbMemberCallback fn);
	
	lbMemberCallback LB_STDCALL getFunction();
	
	lb_I_CallbackTarget* LB_STDCALL getHandlerInstance();

	
	/**
	 * Abstract functions
	 */
	void setType();
	
	lbMemberCallback dispFn;
	UAP(lb_I_CallbackTarget, handler)
};
/*...e*/

/*...sclass lbAppClient:0:*/
/**
 * Base class for all distributed objects. This class can't be instanciated
 * directly. Use lbAppBusClient instead. Also deletion is inhibed. Use
 * dismiss() instead.
 */
class lbAppClient : public lb_I_ApplicationClient {
private:
	lbAppClient();
        lbAppClient(lb_I_Transfer* clConn);
        virtual ~lbAppClient();
        
        DECLARE_LB_UNKNOWN()
        
        /**
         * Only lbAppBusClient should be able to create and delete instances
         * of client connections to a specific server
         */
        void* operator new(size_t size);
        void operator delete(void* ptr);
        
public:

        lb_I_Unknown* LB_STDCALL requestObject(const char* type, const char* name);

/*...sImplement the interfaces:8:*/
	lbErrCodes LB_STDCALL getLastError(char* description, int len);
	lbErrCodes LB_STDCALL initialize();
	lbErrCodes LB_STDCALL request(const char* request, lb_I_Transfer_Data* result);
	lbErrCodes LB_STDCALL release();
	lbErrCodes LB_STDCALL addCallbackHandler(const char* handlername, lbMemberCallback callbackFn);
	lbErrCodes LB_STDCALL delCallbackHandler(const char* handlername);
	lbErrCodes LB_STDCALL dispatch(const char* request, lb_I_Transfer_Data* result);
/*...e*/


	/**
	 * Use this function to indicate, that this instance is no longer
	 * in your use.
	 */
	void dismiss();
	
	// lbAppBusClient must be able to create objects of this class
	friend class lbAppBusClient;
	
protected:

	/**
	 * lbAppClient's can not instantiated directly. lbAppBusClient does
	 * this. Also it sets its instance pointer here.
	 */
	void setAppBusClient(lbAppBusClient* _AppBusClient);

	lbAppBusClient* AppBusClient;
	
	lb_I_Transfer* clientConnection;

	// Dispatch table for registered member callbacks
	UAP(lb_I_Container, dispatchTable)
};
/*...e*/

#endif //LB_APPCS

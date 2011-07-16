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
            Ginsterweg 4
            
            65760 Eschborn (germany)
*/
/*...e*/
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <string.h>
#include <conio.h>
//#include <lbInterfaces.h>
//#include <lbInclude.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#define LB_CS_DLL
#include <lbcs-module.h>
#include <appcs.h>


IMPLEMENT_FUNCTOR(instanceOflbAppServer, lbAppServer)

/*...slbProtocolThread:0:*/
class lbProtocolThread : public lb_I_ProtocolThread {
public:
	lbProtocolThread();
	
	virtual ~lbProtocolThread();

	DECLARE_LB_UNKNOWN()

	/** \brief Private function to initialize this thread.
	 * The thread must dispatch the incoming request.
	 */
	lbErrCodes LB_STDCALL init(lb_I_Transfer* _clt, lb_I_ApplicationServerThread* _parentthread);

	lbThreadFunction LB_STDCALL getThreadFunction();
	
	bool LB_STDCALL isFinished();

	void LB_STDCALL ThreadFunction(lb_I_Thread* threadHost);
	
	lbErrCodes waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* request);
	lbErrCodes answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result);
	
	UAP(lb_I_Transfer, clt)
	UAP(lb_I_ApplicationServerThread, parentthread)
	bool finished;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbProtocolThread)
	ADD_INTERFACE(lb_I_ProtocolThread)
END_IMPLEMENT_LB_UNKNOWN()

lbProtocolThread::lbProtocolThread() {
	ref = STARTREF;
	finished = true;
}
/*...slbProtocolThread\58\\58\\126\lbProtocolThread\40\\41\:0:*/
lbProtocolThread::~lbProtocolThread() {
	COUT << "lbProtocolThread::~lbProtocolThread() called" << ENDL;
}
/*...e*/

lbErrCodes LB_STDCALL lbProtocolThread::init(lb_I_Transfer* _clt, lb_I_ApplicationServerThread* _parentthread) {
	parentthread = _parentthread;
	parentthread++;
	clt = _clt;
	clt++;
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbProtocolThread::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbProtocolThread::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbProtocolThread\58\\58\waitForRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\  request\41\:0:*/
lbErrCodes lbProtocolThread::waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data*  request) 
{
	*_clt >> request;
	
	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while waiting for request");
	    return ERR_APP_SERVER_WAIT_REQUEST;
	}
	
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
	char buf[100];
	sprintf(buf, "lbAppServer::waitForRequest(): Got a request with %d packets", request->getPacketCount());
	LOG(buf);
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...slbProtocolThread\58\\58\answerRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\ result\41\:0:*/
lbErrCodes lbProtocolThread::answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result) 
{
	// Need a little delay till client may be ready to recieve data...
//LOG("This pause is needed ???");

	*_clt << result;

	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while sending request");
	    return ERR_APP_SERVER_SEND_REQUEST;
	}


	return ERR_NONE;
}
/*...e*/

/*...svoid\42\ lbProtocolThread\58\\58\ThreadFunction\40\lb_I_Thread\42\ threadHost\41\:0:*/
void lbProtocolThread::ThreadFunction(lb_I_Thread* threadHost) {
	finished = false;

	_LOG << "lbProtocolThread::ThreadFunction(lb_I_Thread* threadHost) called" LOG_
	
	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rCOUT = ERR_NONE;
	lbErrCodes rc_handler = ERR_NONE; 
	
	// This objects must be clean for each request!

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, request) // 1
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result) // 1	
	

	do {
	  request->deleteAll();
	  result->deleteAll();
	
	  if ((rcin = waitForRequest(*&clt, *&request)) != ERR_NONE) {
		_LOG << "waitForRequest(*&clt, *&request) failed" LOG_
	  } else {
            if ((rc_handler = parentthread->dispatch(*&request, *&result)) != ERR_NONE) {
			_LOG << "handleRequest(*&request, *&result) failed" LOG_
		}
			_LOG << "lbAppBusServer::_connected(lb_I_Transfer* _clt) Request handled, send answer" LOG_
		if ((rCOUT = answerRequest(*&clt, *&result)) != ERR_NONE) {
			LOG("answerRequest(clt, *&result) failed");
		}
			_LOG << "lbAppBusServer::_connected(lb_I_Transfer* _clt) Answer sent" LOG_
/*...e*/
	}

	/**
	 * Request is set correctly, because loop is entered at least once.
	 * So it is possible to handle a disconnect request here.
	 */
	} while ((parentthread->isConnected(*&request) == 1) // Must disconnect before closing transfer 
		&& (rcin == ERR_NONE) // Recieving failed
		&& (rCOUT == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rCOUT != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
	
	finished = true;
}
/*...e*/

lbThreadFunction LB_STDCALL lbProtocolThread::getThreadFunction() {
	return (lbThreadFunction) &lbProtocolThread::ThreadFunction;
}

bool LB_STDCALL lbProtocolThread::isFinished() {
	return finished;
}
/*...e*/

// Handles requests of main server
/*...slbAppServerThread:0:*/
class lbAppServerThread : public lb_I_ApplicationServerThread {
public:
	lbAppServerThread();
	
	virtual ~lbAppServerThread();

	DECLARE_LB_UNKNOWN()

	// Private function to initialize this thread.

	lbThreadFunction LB_STDCALL getThreadFunction();
	
	bool LB_STDCALL isFinished();

	lbErrCodes LB_STDCALL init(lb_I_Transfer* _clt, lb_I_ApplicationServer* _server);

protected:

	bool LB_STDCALL isConnected(lb_I_Transfer_Data* request);

#ifdef bla
	/**
	 * Checks, if the parameters (hostname, pid and tid) are available.
	 * Then it checks, if tid is as key available in connections container.
	 * If all succeeds, 1 is returned and the request would be done.
	 */

	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	lbErrCodes waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* request);
	
	lbErrCodes handleRequest(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
	                  
	lbErrCodes answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result);
#endif
	lbErrCodes _connected(lb_I_Transfer* _clt); 

	lbErrCodes LB_STDCALL dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
	lbErrCodes LB_STDCALL addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback cbFn);
	lbErrCodes LB_STDCALL delProtocolHandler(const char* handlername);



	void LB_STDCALL ThreadFunction(lb_I_Thread* threadHost);

	lb_I_Transfer* clt;
	UAP(lb_I_ApplicationServer, server)
	
	
	// Dispatch table for registered protocol handlers
	UAP(lb_I_Container, dispatchTable)
	UAP(lb_I_Transfer, transfer)
	UAP(lb_I_Container, connections)
	
	bool finished;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbAppServerThread)
	ADD_INTERFACE(lb_I_ThreadImplementation)
	ADD_INTERFACE(lb_I_ProtocolDispatcher)
	ADD_INTERFACE(lb_I_Thread)
END_IMPLEMENT_LB_UNKNOWN()

lbAppServerThread::lbAppServerThread() {
	ref = STARTREF;
}

lbErrCodes LB_STDCALL lbAppServerThread::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAppServerThread::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

bool LB_STDCALL lbAppServerThread::isFinished() {
	return finished;
}

/*...svoid\42\ lbAppServerThread\58\\58\ThreadFunction\40\lb_I_Thread\42\ threadHost\41\:0:*/
void lbAppServerThread::ThreadFunction(lb_I_Thread* threadHost) {
	_LOG << "lbAppServerThread::ThreadFunction(lb_I_Thread* threadHost) called" LOG_

	// Here should be called the function listen() (Not in initTransfer())
	
	finished = false;

	UAP(lb_I_Transfer, clt)
		
	if (transfer == NULL) LOG("lbAppServer::run() Error: transfer object pointer is NULL!");
		
	COUT << "Wait for connection..." << ENDL;
		
	if ((clt = transfer->accept()) == 0) 
	{
		LOG("lbAppServer::run() error while accepting on a socket");
		return;
	}
		
	_connected(clt.getPtr());

/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOG("lbAppServerThread::Entry(): Done request");
#endif
/*...e*/
	//COUT << "lbAppServerThread::Entry(): Done request" << ENDL;	
	
	finished = true;
}
/*...e*/

/*...slbErrCodes lbAppServerThread\58\\58\init\40\lb_I_Transfer\42\ _clt\44\ lb_I_ApplicationServer\42\ _server\41\:0:*/
lbErrCodes lbAppServerThread::init(lb_I_Transfer* _clt, lb_I_ApplicationServer* _server) {
	/*
		Check if the given transfer client has valid data
	*/
	_CL_LOG << "lbAppServerThread::init(...) called." LOG_

	if (_clt == NULL) {
		LOG("lbAppServerThread::lbAppServerThread(...) Error: Have a NULL pointer!");
	}
	else
	if (_clt->isValid() == 1) {
		clt = _clt;
		server = _server;
	} else {
		LOG("lbAppServerThread::lbAppServerThread(...) Error: Got an invalid lb_I_Transfer client object!");
		clt = _clt;
		server = _server;
	}
	return ERR_NONE;
}
/*...e*/

/*...slbAppServerThread\58\\58\\126\lbAppServerThread\40\\41\:0:*/
lbAppServerThread::~lbAppServerThread() {
	COUT << "lbAppServerThread::~lbAppServerThread() called" << ENDL;
}
/*...e*/

lbThreadFunction LB_STDCALL lbAppServerThread::getThreadFunction() {
	return (lbThreadFunction) &lbAppServerThread::ThreadFunction;
}

/*...slbAppServerThread\58\\58\_connected\40\lb_I_Transfer\42\ _clt\41\:0:*/
lbErrCodes lbAppServerThread::_connected(lb_I_Transfer* _clt) {

	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rCOUT = ERR_NONE;
	lbErrCodes rc_handler = ERR_NONE; 
	
	// This objects must be clean for each request!

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, request) // 1
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result) // 1	
	
/*...sHandle connection:8:*/

	do {
	  request->deleteAll();
	  result->deleteAll();
	
	  if ((rcin = server->waitForRequest(_clt, *&request)) != ERR_NONE) {
	    LOG("waitForRequest(_clt, *&request) failed");
	  } else {
            if ((rc_handler = server->dispatch(*&request, *&result)) != ERR_NONE) {
			LOG("handleRequest(*&request, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Request handled, send answer");
#endif
/*...e*/
		if ((rCOUT = server->answerRequest(_clt, *&result)) != ERR_NONE) {
			LOG("answerRequest(_clt, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Answer sent");
#endif
/*...e*/
	}

	/**
	 * Request is set correctly, because loop is entered at least once.
	 * So it is possible to handle a disconnect request here.
	 */
	} while ((server->isConnected(*&request) == 1) // Must disconnect before closing transfer 
		&& (rcin == ERR_NONE) // Recieving failed
		&& (rCOUT == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rCOUT != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
/*...e*/

	return rc;
}
/*...e*/
// Request handler

/*...slbAppServerThread\58\\58\isConnected\40\\46\\46\\46\\41\:0:*/
bool LB_STDCALL lbAppServerThread::isConnected(lb_I_Transfer_Data* request) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	UAP(lb_I_KeyBase, keybase)
	QI(key, lb_I_KeyBase, keybase)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, Pid)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Tid)

	Pid->setData(request->getClientPid());
	Tid->setData(request->getClientTid());
		
	*key = request->getClientHost();
	*key += Pid->charrep();
	*key += Tid->charrep();
		
	if (connections->exists(&keybase)) {
		return true;
	}
	
	return false;
}
/*...e*/

#ifdef bla
/*...slbAppServerThread\58\\58\waitForRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\  request\41\:0:*/
lbErrCodes lbAppServerThread::waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data*  request) 
{
	*_clt >> request;
	
	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while waiting for request");
	    return ERR_APP_SERVER_WAIT_REQUEST;
	}
	
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
	char buf[100];
	sprintf(buf, "lbAppServerThread::waitForRequest(): Got a request with %d packets", request->getPacketCount());
	LOG(buf);
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...slbAppServerThread\58\\58\answerRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\ result\41\:0:*/
lbErrCodes lbAppServerThread::answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result) 
{
	// Need a little delay till client may be ready to recieve data...
//LOG("This pause is needed ???");

	*_clt << result;

	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while sending request");
	    return ERR_APP_SERVER_SEND_REQUEST;
	}


	return ERR_NONE;
}
/*...e*/
#endif

/*...slbAppServerThread\58\\58\dispatch\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerThread::dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result)
{// Dispatching were possible here with servertype...

lbErrCodes err = ERR_NONE;

	/**
	 * One server thread is created for one client process. But this
	 * will not allow to use the server. Each client must also request
	 * for a connection to give the server the anilitiy from wich thread
	 * a further request is from. So the server can block one thread from
	 * other thread using one request->
	 */
	char* buffer = NULL;
	if (request->get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	} else {

		// Block here for dynamic dispatch handling
		UAP(lb_I_DispatchProtocol, proto)
		UAP(lb_I_Unknown, uk)
			
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP(lb_I_KeyBase, key)
		QI(s, lb_I_KeyBase, key)
		*s = buffer;
			
		uk = dispatchTable->getElement(&key);
		QI(uk, lb_I_DispatchProtocol, proto)
		
		if (proto != NULL) {
			err = (proto->getProtocolHandlerInstance()->*((lbProtocolCallback) (proto->getProto()))) (request, result);
		} else {
			LOG("Can not dispatch unknown request");
			err = ERR_APP_SERVER_DISPATCH;
		}
		
		return err;
	}
}
/*...e*/
/*...slbAppServerThread\58\\58\addProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerThread::addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, 
                                          lbProtocolCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 0) {
		lbDispatchProto* proto = new lbDispatchProto();
		proto->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
		proto->setProto(handlername, handlerInstance, cbFn);
		UAP(lb_I_Unknown, uk)
		QI(proto, lb_I_Unknown, uk)
	
		if ((err = dispatchTable->insert(&uk, &hkey)) != ERR_NONE) {
			LOG("Could not add handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service previously added");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/
/*...slbAppServerThread\58\\58\delProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerThread::delProtocolHandler(const char* handlername) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 1) {
		if ((err = dispatchTable->remove(&hkey)) != ERR_NONE) {
			LOG("Could not remove handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service not registered");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/

/*...e*/

// Handles requests of child server (server plugin)
/*...slbAppServerChildThread:0:*/
class lbAppServerChildThread : public lb_I_ApplicationServerThread {
public:
	lbAppServerChildThread();
	
	virtual ~lbAppServerChildThread();

	DECLARE_LB_UNKNOWN()

	// Private function to initialize this thread.

	lbThreadFunction LB_STDCALL getThreadFunction();
	
	bool LB_STDCALL isFinished();

	lbErrCodes LB_STDCALL init(lb_I_Transfer* _clt, lb_I_ApplicationServer* _server);

protected:

	/**
	 * Checks, if the parameters (hostname, pid and tid) are available.
	 * Then it checks, if tid is as key available in connections container.
	 * If all succeeds, 1 is returned and the request would be done.
	 */
	bool LB_STDCALL isConnected(lb_I_Transfer_Data* request);

	/**
	 * Functions needed to encapsulate the transfer class
	 */
	 
	lbErrCodes waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* request);
	
	lbErrCodes handleRequest(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
	                  
	lbErrCodes answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result);

	lbErrCodes _connected(lb_I_Transfer* _clt); 

	lbErrCodes LB_STDCALL dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
	lbErrCodes LB_STDCALL addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback cbFn);
	lbErrCodes LB_STDCALL delProtocolHandler(const char* handlername);



	void LB_STDCALL ThreadFunction(lb_I_Thread* threadHost);

	lb_I_Transfer* clt;
	UAP(lb_I_ApplicationServer, server)
	
	
	// Dispatch table for registered protocol handlers
	UAP(lb_I_Container, dispatchTable)
	UAP(lb_I_Transfer, transfer)
	UAP(lb_I_Container, connections)

	UAP(lb_I_Container, subThreads)
	
	bool finished;
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbAppServerChildThread)
	ADD_INTERFACE(lb_I_ApplicationServerThread)
	ADD_INTERFACE(lb_I_ThreadImplementation)
	ADD_INTERFACE(lb_I_ProtocolDispatcher)
	ADD_INTERFACE(lb_I_Thread)
END_IMPLEMENT_LB_UNKNOWN()

lbAppServerChildThread::lbAppServerChildThread() {
	ref = STARTREF;
}

lbErrCodes LB_STDCALL lbAppServerChildThread::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAppServerChildThread::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

bool LB_STDCALL lbAppServerChildThread::isFinished() {
	return finished;
}

/*...svoid lbAppServerChildThread\58\\58\ThreadFunction\40\lb_I_Thread\42\ threadHost\41\:0:*/
void lbAppServerChildThread::ThreadFunction(lb_I_Thread* threadHost) {
	lbErrCodes err = ERR_NONE;
	finished = false;
	int maxThreads = 50;

	while (1) {
		UAP(lb_I_Transfer, clt)

		if (transfer == NULL) LOG("lbAppServer::run() Error: transfer object pointer is NULL!");
		
		_CL_LOG << "lbAppServerChildThread: Wait for connection..." LOG_
		
		if ((clt = transfer->accept()) == 0) 
		{
			LOG("lbAppServer::run() error while accepting on a socket");
			continue;
		}

		UAP(lb_I_Thread, freeThread)

		if (subThreads->Count() < maxThreads)	{
			REQUEST(getModuleInstance(), lb_I_Thread, freeThread)

			lbProtocolThread* threadimpl = new lbProtocolThread();

			threadimpl->setModuleManager(getModuleInstance(), __FILE__, __LINE__);

			threadimpl->init(*&clt, this);

			UAP(lb_I_ThreadImplementation, thread_impl)
			QI(threadimpl, lb_I_ThreadImplementation, thread_impl)
		
			freeThread->setThreadImplementation(*&thread_impl);
	
			freeThread->create();
		} else {
			while (subThreads->Count() == maxThreads) {
				while (subThreads->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					UAP(lb_I_Thread, thread)
					UAP(lb_I_ThreadImplementation, impl)
				
					uk = subThreads->nextElement();
				
					QI(uk, lb_I_Thread, thread)
				
					if (thread != NULL) {
						impl = thread->getThreadImplementation();
						
						if (impl->isFinished()) {
							freeThread = thread.getPtr();
							break;
						}
					}
				}
			}
		}
		
		freeThread->run();
	}

	finished = true;
}
/*...e*/

/*...slbErrCodes lbAppServerChildThread\58\\58\init\40\lb_I_Transfer\42\ _clt\44\ lb_I_ApplicationServer\42\ _server\41\:0:*/
lbErrCodes lbAppServerChildThread::init(lb_I_Transfer* _clt, lb_I_ApplicationServer* _server) {
	/*
		Check if the given transfer client has valid data
	*/
	
	if (_clt == NULL) {
		LOG("lbAppServerChildThread::lbAppServerChildThread(...) Error: Have a NULL pointer!");
	}
	else
	if (_clt->isValid() == 1) {
		clt = _clt;
		server = _server;
	} else {
		LOG("lbAppServerChildThread::lbAppServerChildThread(...) Error: Got an invalid lb_I_Transfer client object!");
		clt = _clt;
		server = _server;
	}
	return ERR_NONE;
}
/*...e*/

/*...slbAppServerChildThread\58\\58\\126\lbAppServerChildThread\40\\41\:0:*/
lbAppServerChildThread::~lbAppServerChildThread() {
	COUT << "lbAppServerChildThread::~lbAppServerChildThread() called" << ENDL;
}
/*...e*/

lbThreadFunction LB_STDCALL lbAppServerChildThread::getThreadFunction() {
	return (lbThreadFunction) &lbAppServerChildThread::ThreadFunction;
}

/*...slbAppServerChildThread\58\\58\_connected\40\lb_I_Transfer\42\ _clt\41\:0:*/
lbErrCodes lbAppServerChildThread::_connected(lb_I_Transfer* _clt) {

	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rCOUT = ERR_NONE;
	lbErrCodes rc_handler = ERR_NONE; 
	
	// This objects must be clean for each request!

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, request) // 1
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result) // 1	
	
/*...sHandle connection:8:*/

	do {
	  request->deleteAll();
	  result->deleteAll();
	
	  if ((rcin = waitForRequest(_clt, *&request)) != ERR_NONE) {
	    LOG("waitForRequest(_clt, *&request) failed");
	  } else {
            if ((rc_handler = dispatch(*&request, *&result)) != ERR_NONE) {
			LOG("handleRequest(*&request, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Request handled, send answer");
#endif
/*...e*/
		if ((rCOUT = answerRequest(_clt, *&result)) != ERR_NONE) {
			LOG("answerRequest(_clt, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Answer sent");
#endif
/*...e*/
	}

	/**
	 * Request is set correctly, because loop is entered at least once.
	 * So it is possible to handle a disconnect request here.
	 */
	} while ((isConnected(*&request) == 1) // Must disconnect before closing transfer 
		&& (rcin == ERR_NONE) // Recieving failed
		&& (rCOUT == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rCOUT != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
/*...e*/

	return rc;
}
/*...e*/
// Request handler
/*...slbAppServerChildThread\58\\58\waitForRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\  request\41\:0:*/
lbErrCodes lbAppServerChildThread::waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data*  request) 
{
	*_clt >> request;
	
	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while waiting for request");
	    return ERR_APP_SERVER_WAIT_REQUEST;
	}
	
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
	char buf[100];
	sprintf(buf, "lbAppServerChildThread::waitForRequest(): Got a request with %d packets", request->getPacketCount());
	LOG(buf);
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...slbAppServerChildThread\58\\58\dispatch\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerChildThread::dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result)
{// Dispatching were possible here with servertype...

lbErrCodes err = ERR_NONE;

	/**
	 * One server thread is created for one client process. But this
	 * will not allow to use the server. Each client must also request
	 * for a connection to give the server the anilitiy from wich thread
	 * a further request is from. So the server can block one thread from
	 * other thread using one request->
	 */
	char* buffer = NULL;
	if (request->get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
		return ERR_APP_SERVER_REQUEST_CHAR;
	} else {

		// Block here for dynamic dispatch handling
		UAP(lb_I_DispatchProtocol, proto)
		UAP(lb_I_Unknown, uk)
			
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)
		UAP(lb_I_KeyBase, key)
		QI(s, lb_I_KeyBase, key)
		*s = buffer;
			
		uk = dispatchTable->getElement(&key);
		QI(uk, lb_I_DispatchProtocol, proto)
		
		if (proto != NULL) {
			err = (proto->getProtocolHandlerInstance()->*((lbProtocolCallback) (proto->getProto()))) (request, result);
		} else {
			LOG("Can not dispatch unknown request");
			err = ERR_APP_SERVER_DISPATCH;
		}
		
		return err;
	}
}
/*...e*/
/*...slbAppServerChildThread\58\\58\answerRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\ result\41\:0:*/
lbErrCodes lbAppServerChildThread::answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result) 
{
	// Need a little delay till client may be ready to recieve data...
//LOG("This pause is needed ???");

	*_clt << result;

	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while sending request");
	    return ERR_APP_SERVER_SEND_REQUEST;
	}


	return ERR_NONE;
}
/*...e*/

/*...slbAppServerChildThread\58\\58\addProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerChildThread::addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, 
                                          lbProtocolCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 0) {
		lbDispatchProto* proto = new lbDispatchProto();
		proto->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
		proto->setProto(handlername, handlerInstance, cbFn);
		UAP(lb_I_Unknown, uk)
		QI(proto, lb_I_Unknown, uk)
	
		if ((err = dispatchTable->insert(&uk, &hkey)) != ERR_NONE) {
			LOG("Could not add handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service previously added");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/
/*...slbAppServerChildThread\58\\58\delProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServerChildThread::delProtocolHandler(const char* handlername) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 1) {
		if ((err = dispatchTable->remove(&hkey)) != ERR_NONE) {
			LOG("Could not remove handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service not registered");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/

/*...slbAppServerChildThread\58\\58\isConnected\40\\46\\46\\46\\41\:0:*/
bool LB_STDCALL lbAppServerChildThread::isConnected(lb_I_Transfer_Data* request) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	UAP(lb_I_KeyBase, keybase)
	QI(key, lb_I_KeyBase, keybase)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, Pid)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Tid)

	Pid->setData(request->getClientPid());
	Tid->setData(request->getClientTid());
		
	*key = request->getClientHost();
	*key += Pid->charrep();
	*key += Tid->charrep();
		
	if (connections->exists(&keybase)) {
		return true;
	}
	
	return false;
}
/*...e*/
/*...e*/

/*...slbDispatchFn \40\Container for a registered function handler\41\:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDispatchFn)
	ADD_INTERFACE(lb_I_DispatchFunction)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbDispatchFn::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbDispatchFn::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


lbDispatchFn::lbDispatchFn() {
	ref = STARTREF;
}

lbDispatchFn::~lbDispatchFn() {
}

lbErrCodes LB_STDCALL lbDispatchFn::setFunction(const char* service, lb_I_CallbackTarget* handlerInstance, lbMemberCallback fn) {
	dispFn = fn;
	handler = handlerInstance;
	return ERR_NONE;
}	

lbMemberCallback LB_STDCALL lbDispatchFn::getFunction() {
	return dispFn;
}

lb_I_CallbackTarget* LB_STDCALL lbDispatchFn::getHandlerInstance() {
	handler++;
	return handler.getPtr();
}
/*...e*/

/*...slbDispatchProto \40\Container for a registered protocol handler\41\:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDispatchProto)
	ADD_INTERFACE(lb_I_DispatchProtocol)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbDispatchProto::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		UAP(lb_I_DispatchProtocol, proto)
		QI(uk, lb_I_DispatchProtocol, proto)
		
		if (proto != NULL) {
			setProto(proto->getServiceName(), proto->getProtocolHandlerInstance(), proto->getProto());
		} else {
			_CL_LOG << "Error: Copying lbDispatchProto instance not possible." LOG_
		}
		
        return ERR_NONE;
}

lbDispatchProto::lbDispatchProto() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_String, service)
}

char* LB_STDCALL lbDispatchProto::getServiceName() {
	if (service == NULL) return "";
	return service->charrep();
}

lbErrCodes LB_STDCALL lbDispatchProto::setProto(const char* _service, lb_I_ProtocolTarget* handlerInstance, lbProtocolCallback fn) {
	*service = _service;
	handler = handlerInstance;
	dispProto = fn;
	return ERR_NONE;
}

lbDispatchProto::~lbDispatchProto() {
}

lb_I_ProtocolTarget* LB_STDCALL lbDispatchProto::getProtocolHandlerInstance() {
	handler++;
	return handler.getPtr();
}

lbProtocolCallback lbDispatchProto::getProto() {
	return dispProto;
}
/*...e*/

/*...slbConnection:0:*/
lbConnection::lbConnection(char* host, int _pid, int _tid) {
	hostname = strdup(host);
	pid = _pid;
	tid = _tid;
}

lbConnection::~lbConnection() {
	free(hostname);
}
/*...e*/

/*...slbProtocolManager:0:*/
/*...e*/

/*...slbAppServer:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbAppServer)
	ADD_INTERFACE(lb_I_ApplicationServer)
	ADD_INTERFACE(lb_I_ProtocolDispatcher)
	ADD_INTERFACE(lb_I_ProtocolTarget)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbAppServer::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAppServer::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbAppServer\58\\58\lbAppServer\40\\41\:0:*/
lbAppServer::lbAppServer() {
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE
	LOGENABLE("lbAppServer::lbAppServer()");
#endif
/*...e*/
/*...sdead code:0:*/
/*
	LOG("lbAppServer::lbAppServer(): Initialize lb_I_Transfer object");
	transfer = new lb_I_Transfer();
	transfer->init("localhost/busmaster");
	LOG("lbAppServer::lbAppServer(): Initialized");
*/
/*...e*/

    REQUEST(getModuleInstance(), lb_I_Container, connections)
    REQUEST(getModuleInstance(), lb_I_Container, dispatchTable)
    
    REQUEST(getModuleInstance(), lb_I_Container, serverThreads)
    REQUEST(getModuleInstance(), lb_I_Container, serverModules)
	
    REQUEST(getModuleInstance(), lb_I_Container, mainThreads)
	
    //Disallow the serverThreads container to copy the threads at insert.
    
    serverThreads->setCloning(false);
    mainThreads->setCloning(false);
}
/*...e*/
/*...slbAppServer\58\\58\\126\lbAppServer\40\\41\:0:*/
lbAppServer::~lbAppServer() {

}
/*...e*/
/*...slbAppServer\58\\58\initServerModul\40\lb_I_ApplicationServerModul\42\ servermodule\41\:0:*/
int lbAppServer::initServerModul(lb_I_ApplicationServerModul* servermodule, char* serverInstance) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Container, protocolHandlers)
	UAP_REQUEST(getModuleInstance(), lb_I_String, servicename)
	UAP(lb_I_KeyBase, servicekey)
	QI(servicename, lb_I_KeyBase, servicekey)

	UAP(lb_I_ApplicationServerThread, thread_impl)
	UAP(lb_I_ThreadImplementation, ti)
	
	setLogActivated(true);
	*servicename = servermodule->getServiceName();
	
	_LOG << "initServerModul() called with " << servicename->charrep() LOG_

#ifndef USE_MULTITHREAD_CODE
	servermodule->registerModul(this, serverInstance);
#endif

#ifdef USE_MULTITHREAD_CODE
	UAP(lb_I_Unknown, ukThread)
	UAP(lb_I_Thread, moduleThread)

	// Create a new module thread, if not yet servicename has been used.

	ukThread = serverThreads->getElement(&servicekey);

	if (ukThread == NULL) {
		REQUEST(getModuleInstance(), lb_I_Thread, moduleThread)
		QI(moduleThread, lb_I_Unknown, ukThread)

		lbAppServerChildThread* impl = new lbAppServerChildThread();
		impl->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
		QI(impl, lb_I_ApplicationServerThread, thread_impl)	
		QI(impl, lb_I_ThreadImplementation, ti)

		moduleThread->setThreadImplementation(ti.getPtr());
		
		serverThreads->insert(&ukThread, &servicekey);
	} else {
		QI(ukThread, lb_I_Thread, moduleThread)
		
		ti = moduleThread->getThreadImplementation();
		QI(ti, lb_I_ApplicationServerThread, thread_impl)
	}

	// Loads all handlers and makes it reachable by the protocol dispatcher.
	servermodule->registerModul(this); 

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer, transf)
	transf->init(servermodule->getServiceName());

	thread_impl->init(*&transf, this);

	// Register all protocol handlers.

	protocolHandlers = servermodule->getPlugins();

	while (protocolHandlers->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_ProtocolTarget, pt)
				
		uk = protocolHandlers->nextElement();
		QI(uk, lb_I_ProtocolTarget, pt)
		
		if (pt != NULL) {
			pt->registerProtocols(this);
		}
	}
#endif
	setLogActivated(false);
	
	return 1;
}
/*...e*/

char* LB_STDCALL lbAppServer::getServiceName() {
	return "localhost/busmaster";
}

lbErrCodes LB_STDCALL lbAppServer::registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance) {
	protoMgr->addProtocolHandler("Connect", this, (lbProtocolCallback) &lbAppServer::HandleConnect);
	protoMgr->addProtocolHandler("Disconnect", this, (lbProtocolCallback) &lbAppServer::HandleDisconnect);
	return ERR_NONE;
}

void LB_STDCALL lbAppServer::autostartServerPlugins(bool start) {

}

lbErrCodes LB_STDCALL lbAppServer::activateServerPlugin(const char* name) {
	return ERR_NONE;
}


// Main server
/*...slbAppServer\58\\58\run\40\\41\:0:*/
void LB_STDCALL lbAppServer::run() {
	_LOG << "lbAppServer::run() called" LOG_
	lbErrCodes err = ERR_NONE;
	char srvname[100] = "";
	
	int maxThreads = 50;

	registerProtocols(this, "BusMaster"); // server instance name not used internally for this class.
		
	// Find all lb_I_ApplicationServerModul implementations.
	// Similar to plugins these are self descriptable.
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	// Therefore the plugin manager needs some new member functions to only
	// find plugin modules with the above interface.
	
	if (PM->beginEnumServerPlugins()) {
        while (true) {
			UAP(lb_I_ApplicationServerModul, plAsm)
			plAsm = PM->nextServerPluginModul();

			if (plAsm == NULL)
				break;

			_CL_LOG << "Found a server module." LOG_
			
			if (plAsm == NULL) {
				_CL_LOG << "Error: Server module not of given type." LOG_
			}
			
			if ((plAsm != NULL) && initServerModul(*&plAsm, "BusMaster") == 0) {
				_CL_LOG << "Error: Failed to initialize server module." LOG_
			}
		}
	}

	_LOG << "lbAppServer::lbAppServer(): Initialize lb_I_Transfer object" LOG_
	REQUEST(getModuleInstance(), lb_I_Transfer, transfer)
	if (transfer->init("localhost/busmaster") != ERR_NONE) {
		_CL_LOG << "Can't initialize communication channel." LOG_
		return;
	}
	_LOG << "lbAppServer::lbAppServer(): Initialized" LOG_
	setLogActivated(true);
	_CL_LOG << "Global application server is started." LOG_
	setLogActivated(false);

	while (1) {
		UAP(lb_I_Transfer, clt)
		

		if (transfer == NULL) {
			_LOG << "lbAppServer::run() Error: transfer object pointer is NULL!" LOG_
			return;
		}
		
		if ((clt = transfer->accept()) == 0) 
		{
			_LOG << "lbAppServer::run() error while accepting on a socket" LOG_
			_CL_LOG << "lbAppServer::run() error while accepting on a socket" LOG_
			return;
		}

		
		
#ifndef USE_MULTITHREAD_CODE
		UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, request)
		UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)

		request->setServerSide(1);
		result->setServerSide(1);

		*clt >> *&request;

		dispatch(*&request, *&result);

		*clt << *&result;
#endif		

#ifdef USE_MULTITHREAD_CODE
		setLogActivated(true);
		_CL_LOG << "Got connection..." LOG_
		setLogActivated(false);

		UAP(lb_I_Thread, freeThread)

		if (mainThreads == NULL) {
			setLogActivated(true);
			_CL_LOG << "Error: No server plugins registered." LOG_
			setLogActivated(false);
			continue;
		}
		setLogActivated(true);
		_CL_LOG << "Handle request." LOG_
		setLogActivated(false);
		
		if (mainThreads->Count() < maxThreads)	{
			REQUEST(getModuleInstance(), lb_I_Thread, freeThread)

			lbAppServerThread* threadimpl = new lbAppServerThread();

			threadimpl->setModuleManager(getModuleInstance(), __FILE__, __LINE__);

			threadimpl->init(*&clt, this);

			UAP(lb_I_ThreadImplementation, thread_impl)
			QI(threadimpl, lb_I_ThreadImplementation, thread_impl)
		
			freeThread->setThreadImplementation(*&thread_impl);
	
			freeThread->create();
		} else {
			while (mainThreads->Count() == maxThreads) {
				while (mainThreads->hasMoreElements()) {
					UAP(lb_I_Unknown, uk)
					UAP(lb_I_Thread, thread)
					UAP(lb_I_ThreadImplementation, impl)
				
					uk = mainThreads->nextElement();
				
					QI(uk, lb_I_Thread, thread)
				
					if (thread != NULL) {
						impl = thread->getThreadImplementation();
						
						if (impl->isFinished()) {
							freeThread = thread.getPtr();
							break;
						}
					}
				}
			}
		} 
		setLogActivated(true);
		_CL_LOG << "Run request." LOG_
		setLogActivated(false);
		freeThread->run();
#endif		
	}
}
/*...e*/

// Handler management

/*...slbAppServer\58\\58\_connected\40\lb_I_Transfer\42\ _clt\41\:0:*/
lbErrCodes lbAppServer::_connected(lb_I_Transfer* _clt) {

	/**
	 * Loop only exit if not ERR_NONE. This can occur
	 * if any communication error has arrived.
	 */

	lbErrCodes rc = ERR_NONE;	 
	lbErrCodes rcin = ERR_NONE;
	lbErrCodes rCOUT = ERR_NONE;
	lbErrCodes rc_handler = ERR_NONE; 
	
	// This objects must be clean for each request!

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, request) // 1
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result) // 1	
	
/*...sHandle connection:8:*/

	do {
	  request->deleteAll();
	  result->deleteAll();
	
		setLogActivated(true);
		_CL_LOG << "Answer request..." LOG_
		setLogActivated(false);
	  if ((rcin = waitForRequest(_clt, *&request)) != ERR_NONE) {
	    LOG("waitForRequest(_clt, *&request) failed");
	  } else {
			setLogActivated(true);
			_CL_LOG << "Dispatch request..." LOG_
			setLogActivated(false);
            if ((rc_handler = dispatch(*&request, *&result)) != ERR_NONE) {
			LOG("handleRequest(*&request, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Request handled, send answer");
#endif
/*...e*/
		setLogActivated(true);
		_CL_LOG << "Answer request..." LOG_
		setLogActivated(false);
		if ((rCOUT = answerRequest(_clt, *&result)) != ERR_NONE) {
			LOG("answerRequest(_clt, *&result) failed");
		}
/*...sAPPBUS_SVR_VERBOSE:8:*/
#ifdef APPBUS_SVR_VERBOSE
LOG("lbAppBusServer::_connected(lb_I_Transfer* _clt) Answer sent");
#endif
/*...e*/
	  }

	/**
	 * Request is set correctly, because loop is entered at least once.
	 * So it is possible to handle a disconnect request here.
	 */
	} while ((isConnected(*&request) == 1) // Must disconnect before closing transfer 
		&& (rcin == ERR_NONE) // Recieving failed
		&& (rCOUT == ERR_NONE)); // Sendback failed

	LOG("Handle connection tests case of ending loop...");
	if (rcin != ERR_NONE)  LOG("Thread will be ended because recieving data has failed");
	if (rCOUT != ERR_NONE) LOG("Thread will be ended because sending data has failed");
	if (rc_handler != ERR_NONE) LOG("Handling request failed");
	LOG("Tested");
/*...e*/

	return rc;
}
/*...e*/
// Request handler
/*...slbAppServer\58\\58\dispatch\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServer::dispatch(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result)
{// Dispatching were possible here with servertype...
	lbErrCodes err = ERR_NONE;

	/**
	 * One server thread is created for one client process. But this
	 * will not allow to use the server. Each client must also request
	 * for a connection to give the server the anilitiy from wich thread
	 * a further request is from. So the server can block one thread from
	 * other thread using one request->
	 */
	if (isConnected(request) == 0) {
		err = HandleConnect(request, result);
		_CL_LOG << "lbAppServer: Handled a nonconnected request." LOG_
		return err;
	}
	else {
		char* buffer = NULL;
		if (request->get(buffer) == ERR_TRANSFER_DATA_INCORRECT_TYPE) {
			return ERR_APP_SERVER_REQUEST_CHAR;
		} else {

			// Block here for dynamic dispatch handling
			UAP(lb_I_DispatchProtocol, proto)
			UAP(lb_I_Unknown, uk)
			
			UAP_REQUEST(getModuleInstance(), lb_I_String, s)
			UAP(lb_I_KeyBase, key)
			QI(s, lb_I_KeyBase, key)
			*s = buffer;
			
			uk = dispatchTable->getElement(&key);
			if (uk == NULL) {
				_LOG << "lbAppServer::dispatch(...) Error: Failed to lookup protocol handler for '" << key->charrep() << "'." LOG_
				return ERR_APP_SERVER_DISPATCH;
			}
			
			QI(uk, lb_I_DispatchProtocol, proto)
		
			if (proto != NULL) {

				err = (proto->getProtocolHandlerInstance()->*((lbProtocolCallback) (proto->getProto()))) (request, result);

			} else {
				_LOG << "lbAppServer: Can not dispatch unknown request." LOG_
				err = ERR_APP_SERVER_DISPATCH;
			}
			
		}
	
		return err;
	}
}
/*...e*/
/*...slbAppServer\58\\58\waitForRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\  request\41\:0:*/
lbErrCodes lbAppServer::waitForRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data*  request) 
{
	*_clt >> request;
	
	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while waiting for request");
	    return ERR_APP_SERVER_WAIT_REQUEST;
	}
	
/*...sAPPCS_VERBOSE:0:*/
#ifdef APPCS_VERBOSE	
	char buf[100];
	sprintf(buf, "lbAppServerThread::waitForRequest(): Got a request with %d packets", request->getPacketCount());
	LOG(buf);
#endif
/*...e*/
	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\answerRequest\40\lb_I_Transfer\42\ _clt\44\ lb_I_Transfer_Data\42\ result\41\:0:*/
lbErrCodes lbAppServer::answerRequest(lb_I_Transfer* _clt, lb_I_Transfer_Data* result) 
{
	// Need a little delay till client may be ready to recieve data...
//LOG("This pause is needed ???");

	*_clt << result;

	if (_clt->getLastError() != ERR_NONE) {
	    LOG("Error while sending request");
	    return ERR_APP_SERVER_SEND_REQUEST;
	}


	return ERR_NONE;
}
/*...e*/

/*...slbAppServer\58\\58\addProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServer::addProtocolHandler(const char* handlername, lb_I_ProtocolTarget* handlerInstance, 
                                          lbProtocolCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 0) {
		lbDispatchProto* proto = new lbDispatchProto();
		proto->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
		proto->setProto(handlername, handlerInstance, cbFn);
		UAP(lb_I_Unknown, uk)
		QI(proto, lb_I_Unknown, uk)
	
		if ((err = dispatchTable->insert(&uk, &hkey)) != ERR_NONE) {
			_LOG << "Could not add handler" LOG_
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		_LOG << "Service previously added" LOG_
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/
/*...slbAppServer\58\\58\delProtocolHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServer::delProtocolHandler(const char* handlername) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_KeyBase, hkey)
	UAP_REQUEST(getModuleInstance(), lb_I_String, h)
	*h = handlername;
	QI(h, lb_I_KeyBase, hkey)

	if (dispatchTable->exists(&hkey) == 1) {
		if ((err = dispatchTable->remove(&hkey)) != ERR_NONE) {
			LOG("Could not remove handler");
			err = ERR_APP_SERVER_ADDHANDLER;
		}
	} else {
		LOG("Service not registered");
		err = ERR_APP_SERVER_ADDHANDLER;
	}
	return err;
}
/*...e*/


// Helpers
/*...slbAppServer\58\\58\isConnected\40\\46\\46\\46\\41\:0:*/
bool LB_STDCALL lbAppServer::isConnected(lb_I_Transfer_Data* request) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	UAP(lb_I_KeyBase, keybase)
	QI(key, lb_I_KeyBase, keybase)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, Pid)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Tid)

	Pid->setData(request->getClientPid());
	Tid->setData(request->getClientTid());
		
	*key = request->getClientHost();
	*key += Pid->charrep();
	*key += Tid->charrep();
	

	
	if (connections->exists(&keybase)) {
		return true;
	}
	
	return false;
}
/*...e*/
/*...slbAppServer\58\\58\makeProtoErrAnswer\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::makeProtoErrAnswer(lb_I_Transfer_Data* result, char* msg, char* where) {
	char buf[100];
	result->add("Error");
	result->add(msg);
	
	sprintf(buf, "%s Cause: %s", where, msg);
	setLogActivated(true);
	_CL_LOG << buf LOG_
	setLogActivated(false);
	
	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\HandleConnect\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppServer::HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
	lbErrCodes err = ERR_NONE;


	
	LB_PACKET_TYPE type;
	char *clienthost = NULL;
	unsigned long pid = 0;
	unsigned long tid = 0;

/*...sConnect proto:0:*/
/*
	add("Connect")
	add("Host") // your hostname
	add(your host)
	add("Pid")
	add(your pid)
	add("Tid")
	add(your tid")
*/
/*...e*/

/*...srequest data:8:*/
	if (request->requestString("Connect") != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No Connect request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (request->requestString("Host", clienthost) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No Hostname in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (request->requestULong("Pid", pid) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No pid in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}

	if (request->requestULong("Tid", tid) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No tid in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
/*...e*/

	UAP_REQUEST(getModuleInstance(), lb_I_String, key)
	UAP(lb_I_KeyBase, keybase)
	QI(key, lb_I_KeyBase, keybase)


	UAP_REQUEST(getModuleInstance(), lb_I_String, Clienthost)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Pid)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Tid)


	Pid->setData(pid);
	Tid->setData(tid);
	*Clienthost = clienthost;
		
		
	*key = clienthost;
	*key += Pid->charrep();
	*key += Tid->charrep();

	if (!connections->exists(&keybase)) {
		_LOG << "Connect client: " << keybase->charrep() LOG_
		result->add("Accept");
		result->add("InstanceName");
		result->add("BusMaster");
		
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, conn)
		UAP_REQUEST(getModuleInstance(), lb_I_String, param)
		UAP(lb_I_Unknown, uk)
		QI(param, lb_I_Unknown, uk)

		*param = "Clienthost";
		conn->setUAPString(*&param, *&Clienthost);
		
		*param = "Pid";
		conn->setUAPLong(*&param, *&Pid);
		
		*param = "Tid";
		conn->setUAPLong(*&param, *&Tid);
		
		connections->insert(&uk, &keybase);
	} else {
		result->add("Deny");
		result->add("Already connected");
		_LOG << "lbAppServer::HandleConnect(...) Error: Client "  << keybase->charrep() << " already connected!" LOG_
		return ERR_APP_SERVER_HANDLECONNECT;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbAppServer\58\\58\HandleDisconnect\40\\46\\46\\46\\41\:0:*/
lbErrCodes lbAppServer::HandleDisconnect(lb_I_Transfer_Data* request,
          				 lb_I_Transfer_Data*  result) {
	LB_PACKET_TYPE type;
	char *clienthost = NULL;
	int pid = 0;
	int tid = 0;

/*
	add("Disconnect")
	add("Host") // your hostname
	add(your host)
	add("Pid")
	add(your pid)
	add("Tid")
	add(your tid")
*/

/*...srequest data:8:*/
	if (request->requestString("Disconnect") != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No Connect request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (request->requestString("Host", clienthost) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No Hostname in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
	
	if (request->requestInteger("Pid", pid) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No pid in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}

	if (request->requestInteger("Tid", tid) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: No tid in request", "lbAppServer::HandleConnect(...)");
		return ERR_APP_SERVER_HANDLECONNECT;
	}
/*...e*/

	setLogActivated(true);
	_CL_LOG << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid LOG_
	setLogActivated(false);
	
	result->add("Accept");
	result->add(clienthost);
	
	return ERR_NONE;
}
/*...e*/
/*...e*/

/*...slbAppClient:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbAppClient)
//	ADD_INTERFACE(lb_I_Requestable)
	ADD_INTERFACE(lb_I_CallbackManager)
	ADD_INTERFACE(lb_I_CallbackDispatcher)
//	ADD_INTERFACE(lb_I_CallbackTarget)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbAppClient::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAppClient::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

/*...slbAppClient\58\\58\lbAppClient\40\\41\:0:*/
lbAppClient::lbAppClient() {
	clientConnection = NULL;
	//AppBusClient = NULL;
}
/*...e*/
/*...slbAppClient\58\\58\lbAppClient\40\lb_I_Transfer \42\ clConn\41\:0:*/
lbAppClient::lbAppClient(lb_I_Transfer* clConn) {
#ifdef APPCS_VERBOSE
	LOGENABLE("lbAppClient::lbAppClient()");
#endif
	clientConnection = clConn;
}
/*...e*/
/*...slbAppClient\58\\58\\126\lbAppClient\40\\41\:0:*/
lbAppClient::~lbAppClient() {
COUT << "Cleanup lbAppClient" << ENDL;
}
/*...e*/
/*...slbAppClient\58\\58\requestObject\40\const char\42\ name\41\:0:*/
lb_I_Unknown* LB_STDCALL lbAppClient::requestObject(const char* type, const char* name) {
	/**
	 * The result depends on the name given by the parameter.
	 * Simply, this is only a forwarding of the request (to anywhere).
	 */

	/**
	 * Setup request->
	 */
	

	return NULL; //object.clone();
}
/*...e*/
/*...slbAppClient\58\\58\delete\40\void\42\ ptr\41\:0:*/
void lbAppClient::operator delete(void* ptr) {
	LOG("lbAppClient::operator delete(void* ptr) called");
	::delete ptr;
}
/*...e*/
/*...slbAppClient\58\\58\operator new\40\size_t size\41\:0:*/
void* lbAppClient::operator new(size_t size) {
	LOG("lbAppClient::operator new(size_t size) called");
	
	if (size == sizeof(lbAppClient)) return malloc(size);
	return NULL;
}
/*...e*/

// Handler management

/*...slbAppClient\58\\58\addCallbackHandler\40\\46\\46\\46\\41\:0:*/
lbErrCodes LB_STDCALL lbAppClient::addCallbackHandler(const char* handlername, 
                                          lbMemberCallback cbFn) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP(lb_I_KeyBase, key)
	QI(s, lb_I_KeyBase, key)
	*s = handlername;

	lbDispatchFn* dfn = new lbDispatchFn();
	dfn->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	UAP(lb_I_Unknown, ukDfn)
	
	dfn->setFunction(handlername, NULL, cbFn);

	QI(dfn, lb_I_Unknown, ukDfn)	

	if (dispatchTable->exists(&key) == 0) {
		if ((err = dispatchTable->insert(&ukDfn, &key)) != ERR_NONE) {
			LOG("Could not add handler");
			err = ERR_APP_CLIENT_ADDHANDLER;
		}
	} else {
		LOG("Request previously added");
		err = ERR_APP_CLIENT_ADDHANDLER;
	}
	return err;
}
/*...e*/

lbErrCodes LB_STDCALL lbAppClient::dispatch(const char* request, lb_I_Transfer_Data* result) {
	return ERR_NONE;
}

lbErrCodes lbAppClient::getLastError(char* description, int len) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbAppClient::delCallbackHandler(const char* handlername) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbAppClient::initialize() {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbAppClient::request(const char* request, lb_I_Transfer_Data* result) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbAppClient::release() {
	return ERR_NONE;
}
/*
void lbAppClient::setAppBusClient(lbAppBusClient* _AppBusClient) {
	AppBusClient = _AppBusClient;
}
 */
/*...e*/

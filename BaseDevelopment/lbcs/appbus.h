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
            
            40235 DÅsseldorf (germany)
*/
/*...e*/
#ifndef LB_APPBUS
#define LB_APPBUS

#undef DLLEXPORT

/*...s\35\ifdef APPCS_DLL:0:*/
#ifdef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllexport)
#endif

#endif
/*...e*/

/*...s\35\ifndef APPCS_DLL:0:*/
#ifndef APPCS_DLL

#ifdef WINDOWS
#define DLLEXPORT __declspec(dllimport)
#endif

#endif
/*...e*/

/*...slbAppBus:0:*/
class DLLEXPORT lbAppClient;

/**
 * This defines the properties for both AppBus classes (Client and Server)
 */
class DLLEXPORT lbAppBus {

public:
	lbAppBus();
	virtual ~lbAppBus();

protected:

	char* bus_master_adr;
	u_short bus_master_port;
};
/*...e*/

/*...slbAppBusClient:0:*/

class DLLEXPORT lbAppBusClient : public lbAppBus,
				 public lbAppClient {
public:

	/**
	 * Initialize a connection to the appbus server.
	 * Later this is a local dispatcher.
	 */
	lbAppBusClient();
	virtual ~lbAppBusClient();

	virtual void setType();
	virtual lbObject* clone() const;

	lbErrCodes registerCallbacks();

/*...sclient handling:8:*/
	/**
	 * The AppBusClient searches the server behind the scope. He is
	 * doing this by asking the AppBusServer about the server with
	 * that scope. Then the AppBusClient creates the desired client-
	 * connection object.
	 */
	lbAppClient* getClientInstance(char* scope);
	int release(lbAppClient*& cl) { delete cl; cl = NULL; return 1; }
/*...e*/

	int AnounceUser(char* user, char* passwd);
	int Echo(char* msg);

	int Connect();
	int Disconnect();

protected:
	/**
	 * Make this client visible to the bus
	 */
	int AnounceClient(); // Called by ctor
	
	/**
	 * Remove the client from the bus
	 */
	void RemoveClient(); // Called by dtor
	

	// user_info stores the username and password for reanouncement
	lb_Transfer_Data* user_info;
	// client_info stores the data for the host
	lb_Transfer_Data* client_info;
	
	/**
	 * This should be a singleton of a connection to the
	 * AppBus server.
	 */
	static lbTransfer* ABSConnection;
	static int instanceCount;
	static char* curruser;
	int connected;
};
/*...e*/

/*...slbAppBusServer:0:*/
class lb_Transfer_Data;
class DLLEXPORT lbAppBusServer :
				 public lbAppBus,
                                 public lbAppServer 
                                 {
public:
	lbAppBusServer();
	virtual ~lbAppBusServer();

	char* getServiceName();	

	lbErrCodes getLastError(char* description, int len);
	
	/**
	 * This function registers services implemented here.
	 * So all requests must have a service prefix in its
	 * lb_Transfer_Data container. If this is not happen,
	 * the request can't dispatched anywhere !
	 */
	lbErrCodes registerProtocols();
	
			
protected:

/*...sHandleEcho \40\a simple echo server \45\ just a test\41\:8:*/
	// Handle a appbus server specific request
	lbErrCodes HandleEcho(	lb_Transfer_Data request,
				lb_Transfer_Data & result);
/*...e*/
/*...sUserAnouncement \40\a user logs in\41\:8:*/
	// This let the client authenticate by user
	int UserAnouncement(lb_Transfer_Data request,
			    lb_Transfer_Data & result);
/*...e*/

	/**
	 * Further services should be registered by a function.
	 * This function has to be implemented by the class 
	 */

	lbComponentDictionary connections;	
};
/*...e*/
#endif

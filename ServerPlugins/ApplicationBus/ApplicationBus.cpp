/*
	Automatically created file. Do not modify.
 */

#include <lbConfigHook.h>

#include <IApplicationBus.h>

/*...sLB_CLASSES_DLL scope:0:*/
#define LB_CS_DLL
#include <lbcs-module.h>
/*...e*/

#include <ApplicationBus.h>

      

IMPLEMENT_FUNCTOR(instanceOfApplicationBus, ApplicationBus)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationBus)
	ADD_INTERFACE(lb_I_ProtocolTarget)
	ADD_INTERFACE(lb_I_ApplicationBus_ProtocolTarget)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL ApplicationBus::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "ApplicationBus::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}


ApplicationBus::ApplicationBus() {
	ref = STARTREF;
	UAP_REQUEST(getModuleInstance(), lb_I_Container, connections)
}

ApplicationBus::~ApplicationBus() {

}

char* ApplicationBus::getServiceName() {
        return "localhost/ApplicationBus";
}

lbErrCodes LB_STDCALL ApplicationBus::registerProtocols(lb_I_ProtocolManager* protoMgr) {
		_LOG << "lbErrCodes LB_STDCALL ApplicationBus::registerProtocols(lb_I_ProtocolManager* protoMgr)" LOG_

        protoMgr->addProtocolHandler("AnounceUser", this, (lbProtocolCallback) &ApplicationBus::_AnounceUser);

        protoMgr->addProtocolHandler("Echo", this, (lbProtocolCallback) &ApplicationBus::_Echo);

        protoMgr->addProtocolHandler("getServices", this, (lbProtocolCallback) &ApplicationBus::_getServices);

        protoMgr->addProtocolHandler("getServiceForProtocol", this, (lbProtocolCallback) &ApplicationBus::_getServiceForProtocol);

        //protoMgr->addProtocolHandler("Disconnect", this, (lbProtocolCallback) &ApplicationBus::HandleDisconnect);
        //protoMgr->addProtocolHandler("Connect", this, (lbProtocolCallback) &ApplicationBus::HandleConnect);

        return ERR_NONE;
}


lbErrCodes ApplicationBus::HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {
	lbErrCodes err = ERR_NONE;

	LB_PACKET_TYPE type;
	char *clienthost = NULL;
	unsigned long pid = 0;
	unsigned long tid = 0;

/*
	add("Connect")
	add("Host") // your hostname
	add(your host)
	add("Pid")
	add(your pid)
	add("Tid")
	add(your tid")
*/

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
		
	if (connections->exists(&keybase)) {
		result->add("Accept");
		
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
		return ERR_APP_SERVER_HANDLECONNECT;
	}
    _CL_LOG << "lbAppServer::HandleConnect(...) Succeeded." LOG_
	return ERR_NONE;
}

lbErrCodes ApplicationBus::HandleDisconnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result) {
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

	_CL_LOG << "Got hostname: " << clienthost << ", pid: " << pid << ", tid: " << tid << "." LOG_
	
	result->add("Accept");
	result->add(clienthost);
	
	return ERR_NONE;
}

void LB_STDCALL ApplicationBus::AnounceUser(char* name, char* password) {
	_LOG << "ApplicationBus::AnounceUser(" << name << ", " << password << ") called." LOG_
}
lbErrCodes LB_STDCALL ApplicationBus::_AnounceUser(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;
char* name;
	    char* password;
	    

	unsigned long pid = 0;
	unsigned long tid = 0;



/*...sEcho proto:0:*/
/*
	add("Echo")
	add("Your echo message");
*/
/*...e*/


    // requestString allocates memory for the parameter
	if (request->requestString("name", name) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: name parameter not sent", "ApplicationBus::AnounceUser(...)");
		return ERR_TRANSFER_PROTOCOL;
	}
	    
    // requestString allocates memory for the parameter
	if (request->requestString("password", password) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: password parameter not sent", "ApplicationBus::AnounceUser(...)");
		return ERR_TRANSFER_PROTOCOL;
	}
	    AnounceUser(name, password);



    return err;
}
      
void LB_STDCALL ApplicationBus::Echo(char* text) {
	_LOG << "ApplicationBus::Echo(" << text << ") called." LOG_
}
lbErrCodes LB_STDCALL ApplicationBus::_Echo(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;


	unsigned long pid = 0;
	unsigned long tid = 0;

	char* text;
	    

/*...sEcho proto:0:*/
/*
	add("Echo")
	add("Your echo message");
*/
/*...e*/

	if (request->requestString("Echo") != ERR_NONE) {
		result->makeProtoErrAnswer("Error: Echo function identifer not sent", "ApplicationBus::Echo(...)");
		return ERR_TRANSFER_PROTOCOL;
	}

    // requestString allocates memory for the parameter
	if (request->requestString("text", text) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: text parameter not sent", "ApplicationBus::Echo(...)");
		return ERR_TRANSFER_PROTOCOL;
	}
	    Echo(text);


	result->add("text");
	result->add(text);
	free(text);
	    

    return err;
}
      
void LB_STDCALL ApplicationBus::getServices(char* services) {

}
lbErrCodes LB_STDCALL ApplicationBus::_getServices(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;


	unsigned long pid = 0;
	unsigned long tid = 0;

char* services;
	    

/*...sEcho proto:0:*/
/*
	add("Echo")
	add("Your echo message");
*/
/*...e*/

getServices(services);


	result->add("services");
	result->add(services);
	free(services);
	    

    return err;
}
      
void LB_STDCALL ApplicationBus::getServiceForProtocol(char* protocol, char* service) {

}
lbErrCodes LB_STDCALL ApplicationBus::_getServiceForProtocol(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result) {
	LB_PACKET_TYPE type;
    lbErrCodes err = ERR_NONE;
char* protocol;
	    

	unsigned long pid = 0;
	unsigned long tid = 0;

char* service;
	    

/*...sEcho proto:0:*/
/*
	add("Echo")
	add("Your echo message");
*/
/*...e*/


    // requestString allocates memory for the parameter
	if (request->requestString("protocol", protocol) != ERR_NONE) {
		result->makeProtoErrAnswer("Error: protocol parameter not sent", "ApplicationBus::getServiceForProtocol(...)");
		return ERR_TRANSFER_PROTOCOL;
	}
	    getServiceForProtocol(protocol, service);


	result->add("service");
	result->add(service);
	free(service);
	    

    return err;
}
      
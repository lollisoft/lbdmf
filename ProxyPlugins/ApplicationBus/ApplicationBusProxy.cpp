
/*
	Automatically created file. Do not modify.
 */

#include <lbConfigHook.h>
#include <lbInterfaces-sub-Project.h>

#undef DLLEXPORT

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif


#include <ApplicationBusProxy.h>

      

IMPLEMENT_FUNCTOR(instanceOfApplicationBusProxy, ApplicationBusProxy)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationBusProxy)
        ADD_INTERFACE(lb_I_ApplicationBus)
END_IMPLEMENT_LB_UNKNOWN()

//lb_I_Transfer* ApplicationBusProxy::ABSConnection = NULL;
//bool ApplicationBusProxy::connected = false;

lbErrCodes LB_STDCALL ApplicationBusProxy::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "ApplicationBusProxy::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

ApplicationBusProxy::ApplicationBusProxy() {
	ref = STARTREF;
	_CL_LOG << "Init ApplicationBusProxy" LOG_
	
    if (ABSConnection == NULL) {
        /**
         * Initialize the tcp connection...
         */

        REQUEST(getModuleInstance(), lb_I_Transfer, ABSConnection)
        
        ABSConnection->init("t43/busmaster");
        Connect();
    }
    _LOG << "ApplicationBusProxy Initialized" LOG_
}

ApplicationBusProxy::~ApplicationBusProxy() {

}

int ApplicationBusProxy::Connect() {
	char* answer;
	char buf[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)
	client->setServerSide(0);
	result->setServerSide(0);

	client->add("Connect");
	client->add("Host");
	client->add("T43");
	client->add("Pid");
	client->add(lbGetCurrentProcessId());
	client->add("Tid");
	client->add(lbGetCurrentThreadId());

	_LOG << "Client sends the packets..." LOG_
    *ABSConnection << *&client;
	_LOG << "Client waits for answer..." LOG_
    *ABSConnection >> *&result;
	_LOG << "Connect returns with an answer..." LOG_
	// Handle the request
	int count = result->getPacketCount();

	result->resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result->getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result->get(buffer);
				
				if (strcmp(buffer, "Accept") == 0) {
					connected = true;
					_LOG << "Connection accepted." LOG_
					return 1;
				} else {
					connected = false;
					_LOG << "Connection failed!" LOG_
					return 0;
				}
				break;
				
			default:
				_LOG << "Unknown packet type!" LOG_
				
				break;
		}
			
		result->incrementPosition();
	}
                
	return 1;
}

int ApplicationBusProxy::Disconnect() {
	char* answer;
	char buf[100] = "";
	lb_I_Transfer_Data* result;

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)

	client->add("Disconnect");
	client->add("Host");
	client->add("anakin");

    *ABSConnection << *&client;
    *ABSConnection >> *&result;

	int count = result->getPacketCount();

	result->resetPositionCount();
		
	while (count--) {
		LB_PACKET_TYPE type;
		int i = 0;
		char *buffer;
		char msg[100];
		result->getPacketType(type);

		switch (type) {
			case PACKET_LB_CHAR:
				result->get(buffer);
				
				if (strcmp(buffer, "Succeed") == 0) {
					_CL_LOG << "Disconnected successfull" LOG_
					connected = 0;
					return 1;
				} else {
					_CL_LOG << "Disconnection failed!" LOG_
					return 0;
				}
				
				break;
				
			default:
				_CL_LOG << "Unknown packet type!" LOG_
				
				break;
		}
			
		result->incrementPosition();
	}
                
    return 1;
}



void LB_STDCALL ApplicationBusProxy::AnounceUser(char* name, char* password) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)

	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
		
    user_info->add("AnounceUser");

    user_info->add("name");
    user_info->add(name);
	    
    user_info->add("password");
    user_info->add(password);
	    
	
	ABSConnection->init(NULL);
	*ABSConnection << *&user_info;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    _LOG << "Error in sending AnounceUser data" LOG_

	*ABSConnection >> *&result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    _LOG << "Error in recieving AnounceUser answer" LOG_
	

	
}
      
void LB_STDCALL ApplicationBusProxy::Echo(char* text) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)

	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)

	user_info->setServerSide(0);
	result->setServerSide(0);

	
    user_info->add("Echo");

    user_info->add("text");
    user_info->add(text);
	    
	ABSConnection->init(NULL);
	*ABSConnection << *&user_info;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    _LOG << "Error in sending Echo data" LOG_

	*ABSConnection >> *&result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    _LOG << "Error in recieving Echo answer" LOG_
	

        if (result->requestString("text", text) != ERR_NONE) {
            _LOG << "Error in recieving parameter from Echo. Parameter 'text' wrong or not given." LOG_
            return;
        } else {
            _CL_LOG << "Parameter result: 'text' = '" << text << "'" LOG_
        }
	    
	
}
      
void LB_STDCALL ApplicationBusProxy::getServices(char* services) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)

	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
		
    user_info->add("getServices");

	ABSConnection->init(NULL);
	*ABSConnection << *&user_info;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    _LOG << "Error in sending getServices data" LOG_

	*ABSConnection >> *&result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    _LOG << "Error in recieving getServices answer" LOG_
	

        if (result->requestString("services", services) != ERR_NONE) {
            _LOG << "Error in recieving parameter from getServices. Parameter 'services' wrong or not given." LOG_
            return;
        } else {
            _CL_LOG << "Parameter 'services' = '" << services << "'" LOG_
        }
	    
	
}
      
void LB_STDCALL ApplicationBusProxy::getServiceForProtocol(char* protocol, char* service) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)

	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
		
    user_info->add("getServiceForProtocol");

    user_info->add("protocol");
    user_info->add(protocol);
	    
	ABSConnection->init(NULL);
	*ABSConnection << *&user_info;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    _LOG << "Error in sending getServiceForProtocol data" LOG_

	*ABSConnection >> *&result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    _LOG << "Error in recieving getServiceForProtocol answer" LOG_
	

        if (result->requestString("service", service) != ERR_NONE) {
            _LOG << "Error in recieving parameter from getServiceForProtocol. Parameter 'service' wrong or not given." LOG_
            return;
        } else {
            _CL_LOG << "Parameter 'service' = '" << service << "'" LOG_
        }
	    
	
}
      

class lbPluginApplicationBusProxy : public lb_I_PluginImpl {
public:
	lbPluginApplicationBusProxy();
	
	virtual ~lbPluginApplicationBusProxy();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationBusProxy)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationBusProxy)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationBusProxy, lbPluginApplicationBusProxy)

lbErrCodes LB_STDCALL lbPluginApplicationBusProxy::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationBusProxy::setData(...) called.\n" LOG_

	if (ukApplicationBusProxy == NULL) {
		_CL_VERBOSE << "ERROR: Cloning ApplicationBusProxy plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginApplicationBusProxy::lbPluginApplicationBusProxy() {
	_CL_VERBOSE << "lbPluginApplicationBusProxy::lbPluginApplicationBusProxy() called.\n" LOG_
	ukApplicationBusProxy = NULL;
	ref = STARTREF;
}

lbPluginApplicationBusProxy::~lbPluginApplicationBusProxy() {
	_CL_LOG << "lbPluginApplicationBusProxy::~lbPluginApplicationBusProxy() called.\n" LOG_
	
	if (ukApplicationBusProxy != NULL) {
		_CL_LOG << "ukApplicationBusProxy is not NULL." LOG_
	}
}

bool LB_STDCALL lbPluginApplicationBusProxy::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationBusProxy::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationBusProxy::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationBusProxy::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationBusProxy\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationBusProxy::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationBusProxy == NULL) {
		ApplicationBusProxy* oApplicationBusProxy = new ApplicationBusProxy();
		oApplicationBusProxy->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
		QI(oApplicationBusProxy, lb_I_Unknown, ukApplicationBusProxy)
	} else {
		_CL_VERBOSE << "lbPluginApplicationBusProxy::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationBusProxy.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationBusProxy\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationBusProxy::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationBusProxy == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationBusProxy* oApplicationBusProxy = new ApplicationBusProxy();
		oApplicationBusProxy->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(oApplicationBusProxy, lb_I_Unknown, ukApplicationBusProxy)
	}
	
	lb_I_Unknown* r = ukApplicationBusProxy.getPtr();
	ukApplicationBusProxy.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginApplicationBusProxy::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukApplicationBusProxy != NULL) {
		ukApplicationBusProxy--;
		ukApplicationBusProxy.resetPtr();
	}
}

    

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
	
	_CL_LOG << "Init ApplicationBusProxy" LOG_
	
	REQUEST(getModuleInstance(), lb_I_String, serverInstance)
	
    if (ABSConnection == NULL) {
        /**
         * Initialize the tcp connection...
         */
		_CL_LOG << "Initialize the tcp connection..." LOG_
        REQUEST(getModuleInstance(), lb_I_Transfer, ABSConnection)
        
		// The name of the lbDMF Busmaster must be defined in hosts or DNS
        ABSConnection->init("localhost/busmaster");
		_CL_LOG << "Connect to localhost/busmaster..." LOG_
        Connect();
		ABSConnection->close();
    }
    _LOG << "ApplicationBusProxy Initialized" LOG_
}

ApplicationBusProxy::~ApplicationBusProxy() {

}

//\todo Remove as it is unused.
int ApplicationBusProxy::Connect() {
	char* answer;
	char buf[100] = "";
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	client->setServerSide(0);
	result->setServerSide(0);
	
	ABSConnection->gethostname(*&temp);
		
	_CL_LOG << "ApplicationBusProxy::Connect() Connects with hostname = " << temp->charrep() LOG_
	
	client->add("Connect");
	client->add("Host");
	client->add("localhost"); //temp->charrep());
	client->add("Pid");
	client->add(lbGetCurrentProcessId());
	client->add("Tid");
	client->add(lbGetCurrentThreadId());

    *ABSConnection << *&client;
    *ABSConnection >> *&result;

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
					_CL_LOG << "Connection accepted." LOG_
					result->incrementPosition();
					result->get(buffer);
					if (strcmp(buffer, "InstanceName") == 0) {
						result->incrementPosition();
						result->get(buffer);
						*serverInstance = buffer;
						_CL_LOG << "Have server instanve = " << serverInstance->charrep() LOG_
						return 1;
					}
				}
				break;
				
			default:
				_CL_LOG << "Unknown packet type!" LOG_
				
				break;
		}
			
		result->incrementPosition();
	}

	_CL_LOG << "Connection failed!" LOG_
	connected = false;
                
	return 0;
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
		

	user_info->setClientPid(lbGetCurrentProcessId());
	user_info->setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance->charrep();
	*requestString += ".ApplicationBus.AnounceUser";
	
	user_info->add(requestString->charrep());

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
	
	
	user_info->setClientPid(lbGetCurrentProcessId());
	user_info->setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance->charrep();
	*requestString += ".ApplicationBus.Echo";
	
	user_info->add(requestString->charrep());
	
    user_info->add("text");
    user_info->add(text);
	
	ABSConnection->init(NULL);
	
	*ABSConnection << *&user_info;
	
	if (ABSConnection->getLastError() != ERR_NONE) {
	    _CL_LOG << "Error in sending Echo data" LOG_
	}
	
	*ABSConnection >> *&result;

	if (ABSConnection->getLastError() != ERR_NONE) {
	    _CL_LOG << "Error in recieving Echo answer" LOG_
	}

	ABSConnection->close();
	
	char* temptext;
	
	if (result->requestString("text", temptext) != ERR_NONE) {
		_CL_LOG << "Error in recieving parameter from Echo. Parameter 'text' wrong or not given." LOG_
		return;
	} else {
		_CL_LOG << "Parameter result: 'text' = '" << temptext << "'" LOG_
		text[0] = 0;
		strcpy(text, temptext);
	}
	
	
}
      
lb_I_String* LB_STDCALL ApplicationBusProxy::findBackend(char* service) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	UAP_REQUEST(getModuleInstance(), lb_I_String, backend)
	
	
	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info->setServerSide(0);
	result->setServerSide(0);
	
	
	user_info->setClientPid(lbGetCurrentProcessId());
	user_info->setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance->charrep();
	*requestString += ".ApplicationBus.findBackend";
	
	user_info->add(requestString->charrep());
	
    user_info->add("service");
    user_info->add(service);
	
	ABSConnection->init(NULL);
	
	*ABSConnection << *&user_info;
	
	if (ABSConnection->getLastError() != ERR_NONE) {
	    _LOG << "Error in sending Echo data" LOG_
	}
	
	*ABSConnection >> *&result;

	if (ABSConnection->getLastError() != ERR_NONE) {
	    _LOG << "Error in recieving Echo answer" LOG_
	}

	ABSConnection->close();
	char* _backend = NULL;
	if (result->requestString("backend", _backend) != ERR_NONE) {
		_LOG << "Error in recieving parameter from Echo. Parameter 'backend' wrong or not given." LOG_
		return NULL;
	} else {
		*backend = _backend;
		free(_backend);
		_CL_LOG << "Server returned backend = " << backend->charrep() LOG_
	}
	backend++;
	return backend.getPtr();
}
      
void LB_STDCALL ApplicationBusProxy::registerBackend(char* backend, char* server) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	
	
	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
	
	user_info->setServerSide(0);
	result->setServerSide(0);
	
	
	user_info->setClientPid(lbGetCurrentProcessId());
	user_info->setClientTid(lbGetCurrentThreadId());

	UAP_REQUEST(getModuleInstance(), lb_I_String, requestString)
	
	*requestString = serverInstance->charrep();
	*requestString += ".ApplicationBus.registerBackend";
	
	user_info->add(requestString->charrep());
	
    user_info->add("backend");
    user_info->add(backend);
	
    user_info->add("server");
	if (server == NULL) {
		user_info->add("");
    } else {
		user_info->add(server);
	}
	
	ABSConnection->init(NULL);
	
	*ABSConnection << *&user_info;
	
	if (ABSConnection->getLastError() != ERR_NONE) {
	    _LOG << "Error in sending registerBackend data" LOG_
	}
	
	*ABSConnection >> *&result;

	if (ABSConnection->getLastError() != ERR_NONE) {
	    _LOG << "Error in recieving registerBackend answer" LOG_
	}

	ABSConnection->close();
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

	void LB_STDCALL setNamespace(const char* _namespace) { }

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

    

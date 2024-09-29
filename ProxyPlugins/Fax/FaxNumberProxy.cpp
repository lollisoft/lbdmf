
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


#include <FaxNumberProxy.h>

      

IMPLEMENT_FUNCTOR(instanceOfFaxNumberProxy, FaxNumberProxy)

BEGIN_IMPLEMENT_LB_UNKNOWN(FaxNumberProxy)
        ADD_INTERFACE(lb_I_FaxNumber)
END_IMPLEMENT_LB_UNKNOWN()

lb_I_Transfer* FaxNumberProxy::ABSConnection = NULL;
bool FaxNumberProxy::connected = false;

lbErrCodes LB_STDCALL FaxNumberProxy::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "FaxNumberProxy::setData(...) not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

FaxNumberProxy::FaxNumberProxy() {
	
	_CL_LOG << "Init FaxNumberProxy" LOG_

    if (ABSConnection == NULL) {
        /**
         * Initialize the tcp connection...
         */

        UAP_REQUEST(getModuleInstance(), lb_I_Transfer, ABSConnection)
        
        UAP_REQUEST(getModuleInstance(), lb_I_ApplicationBus, Busmaster)
        UAP_REQUEST(getModuleInstance(), lb_I_String, connStr)
        *&connStr = Busmaster->findBackend("FaxNumber");
        ABSConnection->init(connStr->charrep());
        
        Connect();
    }
    _CL_LOG << "Initialized" LOG_
}

FaxNumberProxy::~FaxNumberProxy() {

}

int FaxNumberProxy::Connect() {
	char* answer;
	char buf[100] = "";
	lb_I_Transfer_Data* result;

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)

	client->add("Connect");
	client->add("Host");
	client->add("localhost");
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
					return 1;
				} else {
					connected = false;
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

int FaxNumberProxy::Disconnect() {
	char* answer;
	char buf[100] = "";
	lb_I_Transfer_Data* result;

	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, client)

	client->add("Disconnect");
	client->add("Host");
	client->add("localhost");

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



void LB_STDCALL FaxNumberProxy::AskForFaxNumber(lb_I_String* faxnumber) {
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, result)
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)

	ABSConnection->gethostname(*&temp);
	UAP_REQUEST(getModuleInstance(), lb_I_Transfer_Data, user_info)
		
    user_info->add("AskForFaxNumber");

	
	*ABSConnection << *&user_info;
	if (ABSConnection->getLastError() != ERR_NONE) 
	    _LOG << "Error in sending AskForFaxNumber data" LOG_

	*ABSConnection >> *&result;
	if (ABSConnection->getLastError() != ERR_NONE)
	    _LOG << "Error in recieving AskForFaxNumber answer" LOG_

		char* _faxnumber;

    if (result->requestString("faxnumber", _faxnumber) != ERR_NONE) {
        _LOG << "Error in recieving parameter from AskForFaxNumber. Parameter 'faxnumber' wrong or not given." LOG_
        return;
    } else {
        _CL_LOG << "Parameter 'faxnumber' = '" << _faxnumber << "'" LOG_
    }
	    
	*faxnumber = _faxnumber;
	
}
      

class lbPluginFaxNumberProxy : public lb_I_PluginImpl {
public:
	lbPluginFaxNumberProxy();
	
	virtual ~lbPluginFaxNumberProxy();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFaxNumberProxy)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFaxNumberProxy)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFaxNumberProxy, lbPluginFaxNumberProxy)

lbErrCodes LB_STDCALL lbPluginFaxNumberProxy::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFaxNumberProxy::setData(...) called.\n" LOG_

	if (ukFaxNumberProxy == NULL) {
		_CL_VERBOSE << "ERROR: Cloning FaxNumberProxy plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFaxNumberProxy::lbPluginFaxNumberProxy() {
	_CL_VERBOSE << "lbPluginFaxNumberProxy::lbPluginFaxNumberProxy() called.\n" LOG_
	ukFaxNumberProxy = NULL;
	
}

lbPluginFaxNumberProxy::~lbPluginFaxNumberProxy() {
	_CL_LOG << "lbPluginFaxNumberProxy::~lbPluginFaxNumberProxy() called.\n" LOG_
	
	if (ukFaxNumberProxy != NULL) {
		_CL_LOG << "ukFaxNumberProxy is not NULL." LOG_
	}
}

bool LB_STDCALL lbPluginFaxNumberProxy::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFaxNumberProxy::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFaxNumberProxy::initialize() {
}
	
bool LB_STDCALL lbPluginFaxNumberProxy::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFaxNumberProxy\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFaxNumberProxy::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFaxNumberProxy == NULL) {
		FaxNumberProxy* oFaxNumberProxy = new FaxNumberProxy();
	
		QI(oFaxNumberProxy, lb_I_Unknown, ukFaxNumberProxy)
	} else {
		_CL_VERBOSE << "lbPluginFaxNumberProxy::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFaxNumberProxy.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFaxNumberProxy\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFaxNumberProxy::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFaxNumberProxy == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FaxNumberProxy* oFaxNumberProxy = new FaxNumberProxy();
	
		QI(oFaxNumberProxy, lb_I_Unknown, ukFaxNumberProxy)
	}
	
	lb_I_Unknown* r = ukFaxNumberProxy.getPtr();
	ukFaxNumberProxy.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFaxNumberProxy::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukFaxNumberProxy != NULL) {
		ukFaxNumberProxy--;
		ukFaxNumberProxy.resetPtr();
	}
}

    

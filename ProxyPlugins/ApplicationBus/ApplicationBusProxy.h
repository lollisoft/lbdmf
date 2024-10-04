
/*
	Automatically created file. Do not modify.
 */

      

class ApplicationBusProxy
        : public 
		lb_I_Proxy,
        lb_I_ApplicationBus {
      
public:
        ApplicationBusProxy();
        virtual ~ApplicationBusProxy();

        DECLARE_LB_UNKNOWN()

		// Lookup the server for a class name		
		//lb_I_String* LB_STDCALL getServerName(char* applicationName);
		
		// Lookup the service for a class name		
		//lb_I_String* LB_STDCALL getServiceName(char* applicationName);
		
		// Return the server instance for the given class name.
		//lb_I_String* LB_STDCALL getServerInstance(char* className);
      
		void LB_STDCALL AnounceUser(char* name, char* password);
      
		lb_I_String* LB_STDCALL Echo(char* text);
		
		lb_I_String* LB_STDCALL findBackend(char* service);
      
		void LB_STDCALL registerBackend(char* backend, char* server = NULL);
private:
	int Connect();
	int Disconnect();

    bool connected;
	UAP(lb_I_Transfer, ABSConnection)

	// The server instance name required to create a complete request name.
	UAP(lb_I_String, serverInstance)
	
};

DECLARE_FUNCTOR(instanceOfApplicationBusProxy)
    


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

      
      void LB_STDCALL AnounceUser(char* name, char* password);
      
      void LB_STDCALL Echo(char* text);
      
      void LB_STDCALL getServices(char* services);
      
      void LB_STDCALL getServiceForProtocol(char* protocol, char* service);
      

private:
	int Connect();
	int Disconnect();

    bool connected;
	UAP(lb_I_Transfer, ABSConnection)

};

DECLARE_FUNCTOR(instanceOfApplicationBusProxy)
    
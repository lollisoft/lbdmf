
/*
	Automatically created file. Do not modify.
 */

      

class ApplicationBusProxy
        : public lb_I_Proxy,
      
        public lb_I_ApplicationBus {
      
public:
        ApplicationBusProxy();
        virtual ~ApplicationBusProxy();
      


        DECLARE_LB_UNKNOWN()

      
      void LB_STDCALL AnounceUser(PCHAR name, PCHAR password);
      
      void LB_STDCALL Echo(PCHAR& text);
      
      void LB_STDCALL getServices(PCHAR& services);
      
      void LB_STDCALL getServiceForProtocol(PCHAR protocol, PCHAR& service);
      

private:
	int Connect();
	int Disconnect();

    static bool connected;
	static lb_I_Transfer* ABSConnection;

};

DECLARE_FUNCTOR(instanceOfApplicationBusProxy)
    
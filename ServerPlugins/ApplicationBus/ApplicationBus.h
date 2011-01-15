
/*
	Automatically created file. Do not modify.
 */

      


class ApplicationBus
        : public lb_I_ApplicationBus_ProtocolTarget {
      
public:
        ApplicationBus();
        virtual ~ApplicationBus();
        
        DECLARE_LB_UNKNOWN()

        char* LB_STDCALL getServiceName();
        lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr);

      
      lbErrCodes LB_STDCALL _AnounceUser(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL AnounceUser(char* name, char* password);
      
      lbErrCodes LB_STDCALL _Echo(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL Echo(char* text);
      
      lbErrCodes LB_STDCALL _getServices(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL getServices(char* services);
      
      lbErrCodes LB_STDCALL _getServiceForProtocol(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL getServiceForProtocol(char* protocol, char* service);
      
private:
        UAP(lb_I_Container, connections)
        lbErrCodes LB_STDCALL HandleDisconnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
        lbErrCodes LB_STDCALL HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);

};

DECLARE_FUNCTOR(instanceOfApplicationBus)
    
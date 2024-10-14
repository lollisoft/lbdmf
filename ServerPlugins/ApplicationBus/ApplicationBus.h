
/*
        Automatically created file. Do not modify.
 */

      


class ApplicationBus
        : public lb_I_ApplicationBus_ProtocolTarget {
      
public:
        ApplicationBus();
        virtual ~ApplicationBus();
        
        DECLARE_LB_UNKNOWN()

        const char* LB_STDCALL getServiceName();
        lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance);

                lbErrCodes LB_STDCALL _AnounceUser(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
                void LB_STDCALL AnounceUser(char* name, char* password);
      
                lbErrCodes LB_STDCALL _Echo(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
                void LB_STDCALL Echo(char* text);
      
                lbErrCodes LB_STDCALL _findBackend(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
                lb_I_String* LB_STDCALL findBackend(char* services);
      
                lbErrCodes LB_STDCALL _registerBackend(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
                void LB_STDCALL registerBackend(char* backend, char* server);
      
private:
        UAP(lb_I_Container, connections)
        lbErrCodes LB_STDCALL HandleDisconnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
        lbErrCodes LB_STDCALL HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
                
                UAP(lb_I_String, ServerInstance)

};

DECLARE_FUNCTOR(instanceOfApplicationBus)
    

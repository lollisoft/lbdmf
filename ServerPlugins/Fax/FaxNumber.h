
/*
        Automatically created file. Do not modify.
 */

      


class FaxNumber
        : public lb_I_FaxNumber_ProtocolTarget {
      
public:
        FaxNumber();
        virtual ~FaxNumber();
        
        DECLARE_LB_UNKNOWN()

        const char* LB_STDCALL getServiceName();
        lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr, const char* serverInstance);

      
      lbErrCodes LB_STDCALL _AskForFaxNumber(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL AskForFaxNumber(lb_I_String* faxnumber);
      
private:
        UAP(lb_I_Container, connections)
        lbErrCodes LB_STDCALL HandleDisconnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
        lbErrCodes LB_STDCALL HandleConnect(lb_I_Transfer_Data* request, lb_I_Transfer_Data*  result);
                
                UAP(lb_I_String, ServerInstance)
      
};

DECLARE_FUNCTOR(instanceOfFaxNumber)

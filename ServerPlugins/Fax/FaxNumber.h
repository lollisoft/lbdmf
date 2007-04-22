
/*
	Automatically created file. Do not modify.
 */

      


class FaxNumber
        : public lb_I_FaxNumber_ProtocolTarget {
      
public:
        FaxNumber();
        virtual ~FaxNumber();
        
        DECLARE_LB_UNKNOWN()

        char* LB_STDCALL getServiceName();
        lbErrCodes LB_STDCALL registerProtocols(lb_I_ProtocolManager* protoMgr);

      
      lbErrCodes LB_STDCALL _AskForFaxNumber(lb_I_Transfer_Data* request, lb_I_Transfer_Data* result);
      void LB_STDCALL AskForFaxNumber(PCHAR& faxnumber);
      
};

DECLARE_FUNCTOR(instanceOfFaxNumber)
    
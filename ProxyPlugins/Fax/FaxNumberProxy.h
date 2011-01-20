
/*
	Automatically created file. Do not modify.
 */

      

class FaxNumberProxy
        : public lb_I_Proxy,
      
        public lb_I_FaxNumber {
      
public:
        FaxNumberProxy();
        virtual ~FaxNumberProxy();
      


        DECLARE_LB_UNKNOWN()

      
      void LB_STDCALL AskForFaxNumber(lb_I_String* faxnumber);
      

private:
	int Connect();
	int Disconnect();

    static bool connected;
	static lb_I_Transfer* ABSConnection;

};

DECLARE_FUNCTOR(instanceOfFaxNumberProxy)
    
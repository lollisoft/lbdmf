
/*
	Automatically created file. Do not modify.
 */

      

class FaxNumberProxy
        : public lb_I_FaxNumber {
      
public:
        FaxNumberProxy();
        virtual ~FaxNumberProxy();

        DECLARE_LB_UNKNOWN()

        void setServerName(const char* servername, const char* servicename);
      
		void LB_STDCALL AskForFaxNumber(lb_I_String* faxnumber);
      

private:
		int Connect();
		int Disconnect();

		static bool connected;
		static lb_I_Transfer* ABSConnection;

        // The server instance name required to create a complete request name.
        UAP(lb_I_String, serverInstance)
        UAP(lb_I_String, server)
        UAP(lb_I_String, service)
};

DECLARE_FUNCTOR(instanceOfFaxNumberProxy)
    

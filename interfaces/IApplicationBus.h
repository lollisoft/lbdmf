
/** \brief class ApplicationBus.
 * Documentation for ApplicationBus
 */
class lb_I_ApplicationBus :
public lb_I_Unknown {
public:
      
	virtual void LB_STDCALL AnounceUser(char* name, char* password) = 0;
      
	virtual void LB_STDCALL Echo(char* text) = 0;
      
	virtual void LB_STDCALL getServices(char* services) = 0;
      
	virtual void LB_STDCALL getServiceForProtocol(char* protocol, char* service) = 0;
      
};

/** \brief class ApplicationBus_ProtocolTarget.
 * Documentation for ApplicationBus_ProtocolTarget
 */
class lb_I_ApplicationBus_ProtocolTarget :
public lb_I_ProtocolTarget {
public:
      
	virtual void LB_STDCALL AnounceUser(char* name, char* password) = 0;
      
	virtual void LB_STDCALL Echo(char* text) = 0;
      
	virtual void LB_STDCALL getServices(char* services) = 0;
      
	virtual void LB_STDCALL getServiceForProtocol(char* protocol, char* service) = 0;
      
};
		
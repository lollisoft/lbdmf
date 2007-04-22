
/** \brief class ApplicationBus.
 * Documentation for ApplicationBus
 */
class lb_I_ApplicationBus :
public lb_I_Unknown {
public:
      
	virtual void LB_STDCALL AnounceUser(PCHAR name, PCHAR password) = 0;
      
	virtual void LB_STDCALL Echo(PCHAR& text) = 0;
      
	virtual void LB_STDCALL getServices(PCHAR& services) = 0;
      
	virtual void LB_STDCALL getServiceForProtocol(PCHAR protocol, PCHAR& service) = 0;
      
};

/** \brief class ApplicationBus_ProtocolTarget.
 * Documentation for ApplicationBus_ProtocolTarget
 */
class lb_I_ApplicationBus_ProtocolTarget :
public lb_I_ProtocolTarget {
public:
      
	virtual void LB_STDCALL AnounceUser(PCHAR name, PCHAR password) = 0;
      
	virtual void LB_STDCALL Echo(PCHAR& text) = 0;
      
	virtual void LB_STDCALL getServices(PCHAR& services) = 0;
      
	virtual void LB_STDCALL getServiceForProtocol(PCHAR protocol, PCHAR& service) = 0;
      
};
		
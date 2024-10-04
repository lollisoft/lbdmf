
/** \brief class ApplicationBus.
 * Documentation for ApplicationBus
 */
class lb_I_ApplicationBus :
public lb_I_Unknown {
public:
    /** \brief For tests yet only.
	 *
	 */
	virtual void LB_STDCALL AnounceUser(char* name, char* password) = 0;
      
    /** \brief For tests yet only.
	 *
	 */
	virtual lb_I_String* LB_STDCALL Echo(char* text) = 0;
      
    /** \brief Lookup a server backend by given service name.
	 * The service name is usually a class for that a server exists.
	 */
	virtual lb_I_String* LB_STDCALL findBackend(char* service) = 0;
	
	/** \brief Register a backend.
	 * The backend may reside on another host than the busmaster. Then the server name must be provided.
	 */
	virtual void LB_STDCALL registerBackend(char* backend, char* server = NULL) = 0;
};

/** \brief class ApplicationBus_ProtocolTarget.
 * Documentation for ApplicationBus_ProtocolTarget
 */
class lb_I_ApplicationBus_ProtocolTarget :
public lb_I_ProtocolTarget {
public:
      
	virtual void LB_STDCALL AnounceUser(char* name, char* password) = 0;
      
	virtual void LB_STDCALL Echo(char* text) = 0;
      
	virtual lb_I_String* LB_STDCALL findBackend(char* service) = 0;

	virtual void LB_STDCALL registerBackend(char* backend, char* server) = 0;
};
		
UAPDECL(lb_I_ApplicationBus)
UAPDECL(lb_I_ApplicationBus_ProtocolTarget)

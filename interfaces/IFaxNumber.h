
/** \brief class FaxNumber.
 * Documentation for FaxNumber
 */
class lb_I_FaxNumber :
public lb_I_Unknown,
public lb_I_Proxy
{
public:
      
	virtual void LB_STDCALL AskForFaxNumber(lb_I_String* faxnumber) = 0;
      
};

/** \brief class FaxNumber_ProtocolTarget.
 * Documentation for FaxNumber_ProtocolTarget
 */
class lb_I_FaxNumber_ProtocolTarget :
public lb_I_ProtocolTarget {
public:
      
	virtual void LB_STDCALL AskForFaxNumber(lb_I_String* faxnumber) = 0;
      
};
		
UAPDECL(lb_I_FaxNumber)
UAPDECL(lb_I_FaxNumber_ProtocolTarget)

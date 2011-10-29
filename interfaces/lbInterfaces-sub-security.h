class lb_I_SecurityProvider :
	public lb_I_Unknown
{
public:
	/** \brief Login to the application.
	 *
	 * See description of addUserAccount.
	 */
	virtual bool			LB_STDCALL login(const char* user, const char* pass) = 0;
	virtual long 			LB_STDCALL getApplicationID() = 0;
	virtual lb_I_Container*	LB_STDCALL getApplications() = 0;
	virtual lb_I_Unknown*	LB_STDCALL getApplicationModel() = 0;
	
	virtual lbErrCodes 		LB_STDCALL save() = 0;
	virtual lbErrCodes 		LB_STDCALL load() = 0;
	virtual lbErrCodes		LB_STDCALL uninitialize() = 0;
};
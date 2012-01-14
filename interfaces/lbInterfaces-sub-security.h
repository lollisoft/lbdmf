class lb_I_SecurityProvider :
	public lb_I_Unknown
{
public:
	/** \brief Login to the application.
	 */
	virtual bool			LB_STDCALL login(const char* user, const char* pass) = 0;

	/** \brief Set the current application.
	 *  After a successfull login, an application can be set as active. One of the allowed
	 * applications that will be returned by getApplications is a valid application.
	 */
	virtual bool			LB_STDCALL setCurrentApplicationId(long id) = 0;
	
	/** \brief Get the current users application.
	 * This function will return the application the user has looged into at the last time.
	 * There is currently no such mechanism to support running multible applications, thus
	 * logging in to an application will overwrite the last application login information.
	 */
	virtual long 			LB_STDCALL getApplicationID() = 0;

	/** \brief Returns an application list.
	 * The list contains a list of applications (lb_I_String) that the currently logged in
	 * user has access to. The Key in the list is the identifer of the application.
	 */
	virtual lb_I_Container*	LB_STDCALL getApplications() = 0;
	
	/** \brief Returns the application model.
	 * The returned data is reduced to those entries an user has access to.
	 */
	virtual lb_I_Unknown*	LB_STDCALL getApplicationModel() = 0;
	
	/** \brief Returns the name of the application module.
	 * The application module is a DLL or a shared library based on the underlying OS,
	 * but returned is the name only without an extension.
	 */
	virtual lb_I_String*	LB_STDCALL getApplicationModule() = 0;
	
	/** \brief Returns the name of the application functor.
	 * The functor is a C compatible function that returns an instance
	 * of the requested application.
	 */
	virtual lb_I_String*	LB_STDCALL getApplicationFunctor() = 0;
	
	virtual lbErrCodes 		LB_STDCALL save() = 0;
	virtual lbErrCodes 		LB_STDCALL load() = 0;
	virtual lbErrCodes		LB_STDCALL uninitialize() = 0;
};
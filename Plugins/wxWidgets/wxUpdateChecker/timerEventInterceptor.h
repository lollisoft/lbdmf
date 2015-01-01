#ifndef lbTimerEventInterceptor_H
#define lbTimerEventInterceptor_H

class lbTimerEventInterceptor :
public lb_I_DispatchInterceptor {
public:
	lbTimerEventInterceptor();
	virtual ~lbTimerEventInterceptor();
	
	lb_I_String* LB_STDCALL getVendorName();
	
	lb_I_String* LB_STDCALL getDescription();
	lbErrCodes LB_STDCALL initialize();
	
	lbErrCodes LB_STDCALL addInterceptedInstance(lb_I_Unknown* intercepted);
	lbErrCodes LB_STDCALL removeInterceptedInstance(lb_I_Unknown* interceptedInstance);
	
	lbErrCodes OnBeforeTimerEvent(lb_I_Unknown* uk);
	lbErrCodes OnAfterTimerEvent(lb_I_Unknown* uk);
	
	DECLARE_LB_UNKNOWN()
	
private:
	// Actually looks up the matching intercepted instance.
	lb_I_Unknown* LB_STDCALL lookupIntercepted(lb_I_Unknown* uk);
	
	UAP(lb_I_Container, interceptedHandlers)
};

#endif // lbTimerEventInterceptor_H

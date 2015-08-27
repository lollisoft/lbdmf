
/* Base class for fixed database formular header file
 * wxSFDesigner
 */
 
#ifndef PLUGIN_PropertyForm
#define PLUGIN_PropertyForm

class lbPropertyPanelHandler: 
public lb_I_VisitableHelper,
public lb_I_EventHandler
{
public:
	lbPropertyPanelHandler();
	virtual ~lbPropertyPanelHandler();
	
	DECLARE_LB_UNKNOWN()
	
	lbErrCodes				LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	
	lb_I_Unknown*			LB_STDCALL getUnknown();
	
	lbErrCodes				LB_STDCALL showPropertyDialog(lb_I_Unknown* uk);
	lbErrCodes				LB_STDCALL showPropertyPanel(lb_I_Unknown* uk);
	
	lbErrCodes				LB_STDCALL testPropertyDialog(lb_I_Unknown* uk);
};

#endif //PLUGIN_PropertyForm
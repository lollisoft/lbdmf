
/* Implementation class for fixed database formular header file
 * Application: lbDMFManager
 * Formular: Formulare
 */
 
// Generated class for FormularID = 6
class Formulare : public wxSFDesignerBase {
public:
	Formulare();
	virtual ~Formulare();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL init();

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
	
	lbErrCodes LB_STDCALL lbSetFormularFieldMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbSetFormularFieldConnectMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbMouseDown(lb_I_Unknown* uk);	

	lbErrCodes LB_STDCALL lbMouseUp(lb_I_Unknown* uk);
};

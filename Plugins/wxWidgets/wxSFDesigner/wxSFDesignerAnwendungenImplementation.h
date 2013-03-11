
/* Implementation class for fixed database formular header file
 * Application: lbDMFManager
 * Formular: Anwendungen
 */
 

	// Have field anwendungen.
	// Have field anwendungen.
	// Have field anwendungen.
	// Have field anwendungen.
	// Have field anwendungen.


// Generated class for FormularID = 6
class Anwendungen : public wxSFDesignerBase {
public:
	Anwendungen();
	virtual ~Anwendungen();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL init();

	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
	
	lbErrCodes LB_STDCALL lbSetAnwendungenMode(lb_I_Unknown* uk);
	
	lbErrCodes LB_STDCALL lbSetFormulareMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbSetFormulareConnectMode(lb_I_Unknown* uk);

	lbErrCodes LB_STDCALL lbMouseDown(lb_I_Unknown* uk);	

	lbErrCodes LB_STDCALL lbMouseUp(lb_I_Unknown* uk);
	
private:	
	void OnTextChanged(wxSFShapeTextEvent& event);
	
};

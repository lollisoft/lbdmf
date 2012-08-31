class UIWrapper : public lb_I_Application,
public lb_I_EventHandler
{
public:
	lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	lbErrCodes LB_STDCALL setUserName(const char* user);
	lbErrCodes LB_STDCALL setApplicationName(const char* app);
    lbErrCodes LB_STDCALL save();
    lbErrCodes LB_STDCALL load();
	lbErrCodes LB_STDCALL initialize(const char* user = NULL, const char* app = NULL);
	lbErrCodes LB_STDCALL uninitialize();
	lbErrCodes LB_STDCALL run();
	lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	lb_I_EventManager* LB_STDCALL getEVManager( void );


	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	lb_I_Unknown* LB_STDCALL getUnknown();


	lbErrCodes LB_STDCALL askYesNo(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL setStatusText(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL askOpenFileReadStream(lb_I_Unknown* uk);
	lbErrCodes LB_STDCALL showMsgBox(lb_I_Unknown* uk);

	void LB_STDCALL addAnswer(char* what, bool last);
	void LB_STDCALL setFileAnswer(char* what);

public:
	UIWrapper();
	virtual ~UIWrapper();

	DECLARE_LB_UNKNOWN()

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)

	UAP(lb_I_Container, answerList)
	
	UAP(lb_I_String, fileanswer)
	
	int numberOfAnswers;
};

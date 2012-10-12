
/* Base class for fixed database formular header file
 * wxSFDesigner
 */
 
#ifndef PLUGIN_wxSFDesigner
#define PLUGIN_wxSFDesigner

class wxSFDesignerBase :
	public lb_I_Form,
	public wxPanel {
public:
	wxSFDesignerBase();
	virtual ~wxSFDesignerBase();

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);
	char*	   LB_STDCALL getFormName() { return formName; }

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy() {
	    //Destroy();
	};

	void OnDispatch(wxCommandEvent& event);
	void OnImageButtonClick(wxCommandEvent& event);
	void OnMouseMove(wxMouseEvent& evt);

	UAP(lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)
	UAP(lb_I_String, SQLString)
	UAP(lb_I_String, SQLWhere)

	UAP(lb_I_String, _DBName)
	UAP(lb_I_String, _DBUser)
	UAP(lb_I_String, _DBPass)
	
	UAP(lb_I_Container, ComboboxMapperList)
	UAP(lb_I_Container, ImageButtonMapperList)
	
	UAP(lb_I_Container, actions)

	UAP(lb_I_String, app)
	UAP(lb_I_String, masterForm)
	UAP(lb_I_String, detailForm)
	UAP(lb_I_String, SourceFieldName)
	UAP(lb_I_String, SourceFieldValue)
	UAP(lb_I_String, DBName)
	UAP(lb_I_String, DBUser)
	UAP(lb_I_String, DBPass)
	UAP(lb_I_Container, MasterDetailRelationData)

	long l;
	
	wxWindow* firstButton;
	wxWindow* prevButton;
	wxWindow* nextButton;
	wxWindow* lastButton;
	wxWindow* deleteButton;
	wxWindow* addingButton;

	bool allNaviDisabled;	
	bool noDataAvailable;
	bool isAdding;
	bool _created;
	
	char* base_formName;
	char* formName;
	char* untranslated_formName;
};

#endif //PLUGIN_wxSFDesigner
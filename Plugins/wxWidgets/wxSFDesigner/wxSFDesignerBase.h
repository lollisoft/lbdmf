
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

	lb_I_Unknown* LB_STDCALL getUnknown();
	void LB_STDCALL windowIsClosing(lb_I_Window* w);

	lbErrCodes LB_STDCALL setName(char const * name, char const * appention);
	char*	   LB_STDCALL getFormName();
	char*	   LB_STDCALL getName();
		
	lbErrCodes LB_STDCALL addButton(const char* buttonText, const char* evHandler, int x, int y, int w, int h);
	lbErrCodes LB_STDCALL addLabel(const char* text, int x, int y, int w, int h);
	lbErrCodes LB_STDCALL addTextField(const char* name, int x, int y, int w, int h);

	lbErrCodes LB_STDCALL addOwnerDrawn(const char* name, int x, int y, int w, int h);

	void LB_STDCALL create(int parentId);
	int  LB_STDCALL getId() { return GetId(); }

	void LB_STDCALL show() { Show (TRUE); };
	void LB_STDCALL destroy();
		
	char* LB_STDCALL getQuery();

	void LB_STDCALL setFilter(char* filter);
	
	const char* LB_STDCALL getControlValue(char* name);

	int LB_STDCALL getPrimaryColumns();
	
	const char* LB_STDCALL getControlValue(int pos);
	int LB_STDCALL getControls();
	
	lb_I_String* LB_STDCALL getPrimaryColumn(int pos);
	   
	int LB_STDCALL getForeignColumns(char* primaryTable);
	
	lb_I_String* LB_STDCALL getForeignColumn(int pos);
	   
	bool LB_STDCALL isCharacterColumn(char* name);

	char* LB_STDCALL getTableName(char* columnName);
	
	char* LB_STDCALL getColumnName(int pos);

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
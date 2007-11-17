/*
File 			: dblcontrols.h
Use  			: DatabaseLayer Controls Header File
Created By 		: Guru Kathiresan
Create On		: 09/11/2006
Last Modified   : 09/11/2006 7:00 PM
Lincense		: BSD

Contributors	: None.

- License Text -
Copyright (c) 2006, Guru Ramnath Kathiresan
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of Guru Ramnath Kathiresan nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __DBL_DB_CONTROLS_h__
#define __DBL_DB_CONTROLS_h__



//STL Related Includes
#include <vector>
#include <map>
#include <algorithm>

//wx Related Includes
#include <wx/wx.h>
#include "wx/variant.h"
#include <wx/spinctrl.h>
#include <wx/listctrl.h>

//DBL Related Includes
#include "DatabaseLayerException.h"
#include "ResultSetMetaData.h"
#include "DatabaseLayer.h"

const int wxEVT_DBLCONTROL_FIRST = wxEVT_FIRST + 5400;

const wxEventType wxEVT_DBL_CURSORCHANGED	= wxEVT_DBLCONTROL_FIRST + 1;

#define EVT_DBL_CURSORCHANGED(id, fn)	\
	DECLARE_EVENT_TABLE_ENTRY(wxEVT_DBL_CURSORCHANGED, id, -1, \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&fn, \
 	(wxObject*)NULL ),


class IwxDBLControlInterface;

//Global Function
IwxDBLControlInterface* GetCastedObj2(wxWindow *wndows);

//Class Declarations
class wxDBLMetaDataItem;

class wxDBLException 
{
protected:
	wxString m_strError;
	int m_nErrorCode;
public:
	wxDBLException(wxString strError,int ErrorCode) {m_strError = strError; m_nErrorCode = ErrorCode;}
	wxString GetErrorString(){return m_strError;}
	int GetErrorCode(){return m_nErrorCode;}
};

class wxDBLAbstractClassException : public wxDBLException
{
public:
	wxDBLAbstractClassException():wxDBLException(wxT("Abstract Class Error"),0){}
};


typedef std::vector<wxVariant*> wxArrayOfVariant;
typedef wxArrayOfVariant wxDBLRow;
typedef std::vector<wxDBLRow*> wxArrayOfDBLRow;
typedef std::vector<wxDBLMetaDataItem*> wxArrayOfDWMetaDataItem;
typedef std::vector<long> wxArrayOfBookmark;


class wxDBLMetaDataItem
{
public:
    wxString ColumnName;
    int ColumnType;
    int ColumnSize;
    bool IsColumnNull;
};

class wxDBLMetaData : public ResultSetMetaData
{
public:
    ~wxDBLMetaData();

	void SetMetaData(ResultSetMetaData* MetaData);
    virtual int GetColumnType(int i);
    virtual int GetColumnSize(int i);
    virtual wxString GetColumnName(int i);
    virtual int GetColumnCount();
    int IsFieldInList(const wxString &Value);
	void clear(void);

    wxString GetTableForColumn(int) { return wxString(""); }
    wxString GetTableForColumn(wxString) { return wxString(""); }
          

private:
    std::vector<wxDBLMetaDataItem*> m_MetaData;
    std::vector<wxString> m_MetaFields;
};

class IwxDBLControlInterface;

class wxDBLTable
{
private:
    //Private Variables
	DatabaseLayer *m_dbLayer;
    wxArrayOfDBLRow m_Rows;
    wxWindow*m_winHostWindow;
    wxDBLMetaData m_MetaData;
    bool m_bDBOpen;
	bool m_bReadonly;
    int m_nDBCursor;
    wxString m_strTableName;
	wxArrayOfBookmark m_bkBookMarks;

    //FonCursorChanged: TonCursorChanged;
    //Make this as a Event
    //fixme Later void SetonCursorChanged(const Value: TonCursorChanged);

	//Private Functions
    void DoCursorChange();	
	void OnTableOpen(void);

    void DisplayFields(wxDBLRow *Row, wxWindow *ParentWindow);
	void FillControls(wxWindow *ParentWindow);

    void AddRowItem(DatabaseResultSet *ResultSet);
	
	void SetControlsEnable(bool Status,wxWindow *ParentWindow);
	wxVariant* GetValueFromFieldName(const wxString &FieldName);
	void ClearControlsValue(wxWindow *ParentWindow);

//private:
public:
	wxArrayOfDBLRow* GetRows(void) {return &m_Rows;}

public:
	//Public Functions
    wxDBLTable(const wxString TableName,const DatabaseLayer *dbLayer,const wxWindow *HostWindow,bool ReadOnly = false);
	wxDBLTable();

    ~wxDBLTable();

	void SetTableInfo(const wxString TableName,const DatabaseLayer *dbLayer,const wxWindow *HostWindow,bool ReadOnly = false);

    wxString GetTableName(void) {return m_strTableName;}
    void SetTableName(const wxString &TableName) {m_strTableName = TableName;}

    const DatabaseLayer *GetDBObj(void) {return m_dbLayer;}
    void SetDBObj(const DatabaseLayer *dbLayer) {m_dbLayer = (DatabaseLayer *)dbLayer;}

	wxDBLMetaData* GetMetaData(void) {return &m_MetaData;}

    bool Open(const wxString& Where = wxT(""));
    bool Close(void);
	bool IsOpened(void) {return m_bDBOpen;}

	bool IsReadOnly() {return m_bReadonly && m_bDBOpen;}

    wxDBLRow* GetRecord(void);
    bool SetRecord(wxDBLRow* Value);

	//Total Record count
	long GetRecordCount();
	
	//Record Location
	long GetPosition();

	//Record Operation
    bool New(void);
    bool Delete(void);
	bool Edit(void); //new 
	bool Post(void);

	bool First(void);
    bool Next(void);
    bool Prior(void);    
    bool Last(void);
	bool Goto(int Position);

	bool IsFirst(void);
	bool IsLast(void);
	
	bool HasNext(void);
	bool HasPrior(void);
	
	bool IsEmpty();

	//Controls Related
	bool EnableControls(void);
	bool DisableControls(void);
	
	bool SetControlInfo(IwxDBLControlInterface* ctrl);//new
    
	//Book Mark Related
	bool SetBookMark(void);//new
	bool RemoveBookMark(void);//new

	bool GotoBookMark(long bookmark);//new
	long FirstBookMark();//new
	long LastBookMark();//new
	long NextBookMark();//new
	long PreviousBookMark();//new
	bool IsFirstBookMark();//new
	bool IsLastBookMark();//new
	long GetBookMarkCount();//new
	bool IsBookMarkValid(long bookmark);//new

	//Search Records
    bool Find(const wxString& FindText);
	bool FindFirst(const wxString& FindText);//new
	bool FindLast(const wxString& FindText);//new
	bool FindNext(const wxString& FindText);//new
	bool FindPrior(const wxString& FindText);//new
	
	//Lookup

    bool Display(void);
};

class wxDBLControlClassInfo : public wxClassInfo
{
public:
    wxDBLControlClassInfo( wxChar *cName, const wxClassInfo *baseInfo1,
		const wxClassInfo *baseInfo2, 
		int sz)
        :wxClassInfo( cName, baseInfo1, baseInfo2, sz, 0)
    {
    }
};

#define wxDynamicCastHelper(obj, className, mixInClassName) \
	(obj && wxIsKindOf(((wxObject *)(void *)obj), className))? \
	(mixInClassName *)(className *)(void *)obj: \
 obj


#define WXDBBL_DECLARE_DYNAMIC_CLASS(name) \
public:\
	static wxDBLControlClassInfo ms_classInfo;\
	virtual wxClassInfo *GetClassInfo() const; \
   


#define WXDBBL_IMPLEMENT_DYNAMIC_CLASS(name) \
	wxClassInfo *name::GetClassInfo() const \
   { return &ms_classInfo; }				\
	wxDBLControlClassInfo name::ms_classInfo(wxT(#name),NULL,NULL,sizeof(name));\

class IwxDBLControlInterface
{
	
	WXDBBL_DECLARE_DYNAMIC_CLASS(IwxDBLControlInterface);

	//DECLARE_DYNAMIC_CLASS(IwxDBLControlInterface);	

protected:
    wxDBLTable *m_DBTable;
    wxString m_DBFieldName;
	bool m_bFillContainer;
	bool m_bSetUniqueItems;

public:
	IwxDBLControlInterface() {}
	virtual ~IwxDBLControlInterface(){}
    virtual wxString GetDBFieldName(void);
    virtual void SetDBFieldName(const wxString& FieldName);
	virtual wxDBLTable* GetDBTableObj();
	virtual void SetDBTableObj(wxDBLTable* Obj);
	virtual bool IsFillContainer() {return m_bFillContainer;}
	virtual void SetUniqueFillItems(bool Status) {m_bSetUniqueItems = Status;}
	
protected:
	virtual void SeFillContainer(bool Status) {m_bFillContainer = Status;}

public:
	//Virtual Functions
	//*********************************************
	//These functions need to be Pure Virtual,
	//The fucking wx RTTI wouldn't allow me to 
	//make virtual functions if I want to have this
	//class listed in their Class Info
	//*********************************************
    virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);
    virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);	

	virtual void FillWithTableContent(wxDBLTable *Table,int ColumnIdx);
};
	

class wxDBLTextCtrl: public wxTextCtrl,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLTextCtrl)

public:
    wxDBLTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr)
            :wxTextCtrl(parent, id, value, pos, size, style, validator, name) { m_bFillContainer = false;}
    wxDBLTextCtrl():wxTextCtrl(){ m_bFillContainer = false;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);

	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);    
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
};

class wxDBLStaticText: public wxStaticText,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLStaticText)
		
public:
    wxDBLStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxT("staticText"))
		:wxStaticText(parent,id,label,pos,size,style,name) {m_bFillContainer = false; }
    wxDBLStaticText():wxStaticText(){m_bFillContainer = false;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);
	
	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);    
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
};


class wxDBLSpinCtrl: public wxSpinCtrl,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLSpinCtrl)
		
public:
    wxDBLSpinCtrl(wxWindow* parent, wxWindowID id = -1, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_ARROW_KEYS, int min = 0, int max = 100, int initial = 0, const wxString& name = _T("wxSpinCtrl"))
		:wxSpinCtrl(parent,id,value,pos,size,style,0,100,0,name) {m_bFillContainer = false; }
    wxDBLSpinCtrl():wxSpinCtrl(){m_bFillContainer = false;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);
	
	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);    
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
};


class wxDBLComboBox: public wxComboBox,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLComboBox)
		
public:
    wxDBLComboBox(wxWindow* parent, wxWindowID id, const wxString& value = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("comboBox"))
		:wxComboBox(parent,id,value,pos,size,n,choices,style,validator,name) {m_bFillContainer = true; }

    wxDBLComboBox(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("comboBox"))
		:wxComboBox(parent,id,value,pos,size,choices,style,validator,name) {m_bFillContainer = true;}
	
    wxDBLComboBox():wxComboBox(){m_bFillContainer = true;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);
	
	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);   
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
	virtual void FillWithTableContent(wxDBLTable *Table,int ColumnIdx);
};

class wxDBLListBox: public wxListBox,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLListBox)
	DECLARE_EVENT_TABLE()
			
public:
    wxDBLListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("ListBox"))
		:wxListBox(parent,id,pos,size,n,choices,style,validator,name) {m_bFillContainer = true; m_bSetUniqueItems = false; }
	
    wxDBLListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("ListBox"))
		:wxListBox(parent,id,pos,size,choices,style,validator,name) {m_bFillContainer = true;m_bSetUniqueItems = false;;}
	
    wxDBLListBox():wxListBox(){m_bFillContainer = true;m_bSetUniqueItems = false;;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);
	
	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);   
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
	virtual void FillWithTableContent(wxDBLTable *Table,int ColumnIdx);

	//Function for Triggering the Changes
	void OnSelected(wxCommandEvent& event);
};

class wxDBLListCtrl: public wxListCtrl,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLListCtrl)	
	DECLARE_EVENT_TABLE()

private:
	wxArrayString m_ColumnList;
	//Function for Triggering the Changes
	void OnSelected(wxListEvent& event);
	//helper Functions
	int GetSelectedListItem();
	bool SelectListItem(int Row);
	wxString GetListViewColumnText(long row_number, int column );
	bool SetListViewColumnText(long row_number, int column , const wxString &Content);
		
public:
    wxDBLListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("ListCtrl"))
		:wxListCtrl(parent, id, pos, size, style | wxLC_SINGLE_SEL, validator, name) {m_bFillContainer = true;m_bSetUniqueItems = false;}
	
	wxDBLListCtrl():wxListCtrl() {m_bFillContainer = true;m_bSetUniqueItems = false;}

	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);   
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
	virtual void FillWithTableContent(wxDBLTable *Table,int ColumnIdx);
	
	void SetDBColumnList(wxArrayString strArray){ m_ColumnList.Clear(); m_ColumnList = strArray; }
	wxArrayString GetDBColumnList(void) {return m_ColumnList;}
};



class wxDBLCheckBox: public wxCheckBox,public IwxDBLControlInterface
{
private:
	DECLARE_DYNAMIC_CLASS(wxDBLCheckBox)
		
public:
    wxDBLCheckBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& val = wxDefaultValidator, const wxString& name = wxT("checkBox"))
		:wxCheckBox(parent, id,label, pos,size,style,val,name) { m_bFillContainer = false;}
    wxDBLCheckBox():wxCheckBox(){m_bFillContainer = false;}
    //virtual wxString GetDBFieldName(void) = 0;
    //virtual void SetDBFieldName(const wxString& FieldName);
	//virtual wxDBLTable* GetDBTableObj() = 0;
	//virtual void SetDBTableObj(wxDBLTable* Obj);
	
	virtual bool SetDBValue(wxVariant*Value,int Row);
    virtual wxVariant GetDBValue(void);    
	virtual void DBNotifyOnChange(void);
	virtual wxWindow * GetWindowObj(void);
};

#endif //__DBL_DB_CONTROLS_h__
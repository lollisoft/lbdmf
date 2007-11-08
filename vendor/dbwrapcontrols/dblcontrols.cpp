/*
File 			: dblcontrols.cpp
Use  			: DatabaseLayer Controls Implementation File
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

#include "dblcontrols.h"
/*
wxString g_Supported_Controls[] = {"wxDBLTextCtrl","wxDBLStaticText","wxDBLSpinCtrl","wxDBLComboBox","wxDBLCheckBox","wxDBLListBox","wxDBLListCtrl"};
*/
void wxDBLMetaData::SetMetaData(ResultSetMetaData* MetaData)
{
	for (int i =0 ; i < MetaData->GetColumnCount(); ++i)
	{
		wxDBLMetaDataItem* metaItem = new wxDBLMetaDataItem();
		metaItem->ColumnName = MetaData->GetColumnName(i);
		metaItem->ColumnSize = MetaData->GetColumnSize(i);
		metaItem->ColumnType = MetaData->GetColumnType(i);
		m_MetaData.push_back(metaItem);

		//Populate Field Name List for easy lookup
		m_MetaFields.push_back(MetaData->GetColumnName(i).Upper());
	}	
}

wxDBLMetaData::~wxDBLMetaData()
{
	m_MetaFields.empty();
	for (int i =0 ; i < m_MetaData.size(); ++i)
	{
		wxDBLMetaDataItem* metaItem = m_MetaData.at(i);
		delete metaItem;
	}
	m_MetaData.empty();
}

int wxDBLMetaData::GetColumnType(int i) 
{ 
	return m_MetaData.at(i)->ColumnType;
}

int wxDBLMetaData::GetColumnSize(int i) 
{ 
	return m_MetaData.at(i)->ColumnSize;
}

wxString wxDBLMetaData::GetColumnName(int i) 
{ 
	return m_MetaData.at(i)->ColumnName;
}

int wxDBLMetaData::GetColumnCount() 
{
	return  m_MetaData.size();
}

int wxDBLMetaData::IsFieldInList(const wxString &Value)
{	
	std::vector<wxString>::iterator it = std::find(m_MetaFields.begin(), m_MetaFields.end(), Value.Upper());
	if (it == m_MetaFields.end())
		return -1;
	else
		return (it - m_MetaFields.begin());
}

void wxDBLMetaData::clear(void)
{
	for (int i = 0 ;i < m_MetaData.size(); ++i)
	{
		delete m_MetaData[i];
	}
	m_MetaData.clear();
	m_MetaFields.clear();
}

//-----------------
//IMPLEMENT_CLASS0(IwxDBLControlInterface);
WXDBBL_IMPLEMENT_DYNAMIC_CLASS(IwxDBLControlInterface);

wxString IwxDBLControlInterface::GetDBFieldName(void)
{
	return m_DBFieldName;
}

void IwxDBLControlInterface::SetDBFieldName(const wxString& FieldName)
{
	m_DBFieldName = FieldName;
}

wxDBLTable* IwxDBLControlInterface::GetDBTableObj()
{
	return m_DBTable;
}

void IwxDBLControlInterface::SetDBTableObj(wxDBLTable* Obj)
{
	m_DBTable = Obj;
}

bool IwxDBLControlInterface::SetDBValue(wxVariant*Value,int Row)
{
	throw wxDBLAbstractClassException();

	return false;
}
wxVariant IwxDBLControlInterface::GetDBValue(void)
{
	throw wxDBLAbstractClassException();

	return wxVariant();
}
void IwxDBLControlInterface::DBNotifyOnChange(void)
{
	throw wxDBLAbstractClassException();

	return;
}
wxWindow * IwxDBLControlInterface::GetWindowObj(void)
{
	throw wxDBLAbstractClassException();

	return NULL;
}

void IwxDBLControlInterface::FillWithTableContent(wxDBLTable *Table,int ColumnIdx)
{
	throw wxDBLAbstractClassException();	
	return;
}

//-------------------------------------
IMPLEMENT_DYNAMIC_CLASS2(wxDBLTextCtrl, wxTextCtrl,IwxDBLControlInterface) 

bool wxDBLTextCtrl::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		SetValue(wxT("")); 
		this->Enable(false);
	}
	else
	{
		SetValue(Value->GetString()); 
		Enable(true);
		if (m_DBTable->IsReadOnly())
			this->SetEditable(false);
		else
			this->SetEditable(true);
	}

	return true;
}

wxVariant wxDBLTextCtrl::GetDBValue(void)
{
	wxVariant Result = GetValue(); 
	return Result;
}

void wxDBLTextCtrl::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLTextCtrl::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}

//-------------------------------------
IMPLEMENT_DYNAMIC_CLASS2(wxDBLStaticText, wxStaticText,IwxDBLControlInterface) 

bool wxDBLStaticText::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		SetLabel(wxT("")); 
		this->Enable(false);
	}
	else
	{
		SetLabel(Value->GetString()); 
		Enable(true);
	}
	
	return true;
}

wxVariant wxDBLStaticText::GetDBValue(void)
{
	wxVariant Result = GetLabel(); 
	return Result;
}

void wxDBLStaticText::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLStaticText::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}


//-------------------------------------
IMPLEMENT_DYNAMIC_CLASS2(wxDBLSpinCtrl, wxSpinCtrl,IwxDBLControlInterface) 

bool wxDBLSpinCtrl::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		SetValue(wxT("")); 
		this->Enable(false);
	}
	else
	{
		SetValue(Value->GetString()); 
		Enable(true);
	}
	
	return true;
}

wxVariant wxDBLSpinCtrl::GetDBValue(void)
{
	wxVariant Result = (long)GetValue(); 
	return Result;
}

void wxDBLSpinCtrl::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLSpinCtrl::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}


//-------------------------------------
IMPLEMENT_DYNAMIC_CLASS2(wxDBLComboBox, wxComboBox,IwxDBLControlInterface) 

bool wxDBLComboBox::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		SetValue(wxT("")); 
		this->Enable(false);
	}
	else
	{
		SetValue(Value->GetString()); 
		this->SetSelection(Row);
		Enable(true);
		if (m_DBTable->IsReadOnly())
			this->SetEditable(false);
		else
			this->SetEditable(true);
	}
	
	return true;
}

wxVariant wxDBLComboBox::GetDBValue(void)
{
	wxVariant Result = GetValue(); 
	return Result;
}

void wxDBLComboBox::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLComboBox::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}

void wxDBLComboBox::FillWithTableContent(wxDBLTable *Table,int ColumnIdx)
{
	this->Clear();
	if (Table->IsOpened() == false)
		return;
	for (int i = 0 ; i < Table->GetRows()->size(); ++i )
	{
		if (m_bSetUniqueItems == false)
			this->Append(Table->GetRows()->at(i)->at(ColumnIdx)->GetString());
		else
		{
			if (this->FindString(Table->GetRows()->at(i)->at(ColumnIdx)->GetString()) == -1)
				this->Append(Table->GetRows()->at(i)->at(ColumnIdx)->GetString());			
		}
	}
}
//-------------------------------------
//-------------------------------------
BEGIN_EVENT_TABLE(wxDBLListBox,wxListBox)
	EVT_LISTBOX(-1,wxDBLListBox::OnSelected)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS2(wxDBLListBox, wxListBox,IwxDBLControlInterface) 

bool wxDBLListBox::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		Clear();
		this->Enable(false);
	}
	else
	{
		//Clear();
		this->SetSelection(Row);
		Enable(true);			
	}
	
	return true;
}

wxVariant wxDBLListBox::GetDBValue(void)
{
	wxVariant Result; 
	return Result;
}

void wxDBLListBox::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLListBox::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}

void wxDBLListBox::FillWithTableContent(wxDBLTable *Table,int ColumnIdx)
{
	this->Clear();
	if (Table->IsOpened() == false)
		return;
	for (int i = 0 ; i < Table->GetRows()->size(); ++i )
	{
		if (m_bSetUniqueItems == false)
			this->Append(Table->GetRows()->at(i)->at(ColumnIdx)->GetString());
		else
		{
			if (this->FindString(Table->GetRows()->at(i)->at(ColumnIdx)->GetString()) == -1)
				this->Append(Table->GetRows()->at(i)->at(ColumnIdx)->GetString());			
		}
	}
}

void wxDBLListBox::OnSelected(wxCommandEvent& event)
{
	if (GetDBTableObj()->IsOpened() == false)
		return;
	int nSelection = GetSelection();
	if ( nSelection == -1)
		return;
	int nSize = GetDBTableObj()->GetRows()->size();
	if (nSelection < nSize)
	{
		GetDBTableObj()->Goto(nSelection);
	}
	
}
//-------------------------------------
BEGIN_EVENT_TABLE(wxDBLListCtrl,wxListCtrl)
	EVT_LIST_ITEM_SELECTED(-1,OnSelected)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS2(wxDBLListCtrl, wxListCtrl,IwxDBLControlInterface) 

bool wxDBLListCtrl::SetDBValue(wxVariant*Value,int Row)
{
	if ((GetDBTableObj() == NULL) || (GetDBTableObj()->IsOpened() == false ))
	{
		DeleteAllItems();
		this->Enable(false);
	}
	else
	{
		//fixme: Check if the Row exceeds the Table Row Count
		this->SelectListItem(Row);
		Enable(true);			
	}
	
	return true;
}

wxVariant wxDBLListCtrl::GetDBValue(void)
{
	wxVariant Result; 
	return Result;
}

void wxDBLListCtrl::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLListCtrl::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}

void wxDBLListCtrl::FillWithTableContent(wxDBLTable *Table,int ColumnIdx)
{	

	if (Table->IsOpened() == false)
		return;

	int nSelectedPos = this->GetSelectedListItem();
	
	this->Freeze();
	this->DeleteAllItems();	

	wxArrayInt arryValidIdx,arryFieldTypes;
	for (int kk = 0; kk < m_ColumnList.Count() ; ++kk )
	{
		int nPos = GetDBTableObj()->GetMetaData()->IsFieldInList(m_ColumnList.Item(kk));
		if (nPos >= 0 )
			arryValidIdx.Add(nPos);
	}
	
	if (arryValidIdx.GetCount() ==0)
		return;

	for (int i = 0 ; i < GetDBTableObj()->GetRows()->size() ; ++i )
	{	
		this->InsertItem(i,wxT(""));
		for (int k = 0 , j = 0  ; k < arryValidIdx.GetCount() ; ++k )
		{	
			int nDataPosition = arryValidIdx.Item(k);			
			wxString dtStr = GetDBTableObj()->GetRows()->at(i)->at(nDataPosition)->GetString();
			this->SetListViewColumnText(i,j++,dtStr);
		}
	}		
	this->Thaw();
}

void wxDBLListCtrl::OnSelected(wxListEvent& event)
{

	if (GetDBTableObj()->IsOpened() == false)
		return;
	int nSelection = GetSelectedListItem();
	if ( nSelection == -1)
		return;

	int nSize = GetDBTableObj()->GetRows()->size();
	if (nSelection < nSize)
	{
		GetDBTableObj()->Goto(nSelection);
	}
}
//Helper functions
int wxDBLListCtrl::GetSelectedListItem()
{
	long item = -1;
	item = this->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);   
	return item;
}

bool wxDBLListCtrl::SelectListItem(int Row)
{
	bool Result = false;
	if (Row > this->GetItemCount())
	{
		Result = false;
	}
	else
	{
		Result = true;
		this->SetItemState(Row,wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED, wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED);
	}
	return Result;
}


// Returns the text of a cell, at a certain row and column
wxString wxDBLListCtrl::GetListViewColumnText(long row_number, int column )
{
	wxListItem     row_info; 
	wxString       cell_contents_string;
	
	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = column;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;
	
	// Get the info and store it in row_info variable.   
	this->GetItem(row_info );
	
	// Extract the text out that cell
	cell_contents_string = row_info.m_text;
	
	return cell_contents_string;
} 

// Returns the text of a cell, at a certain row and column
bool wxDBLListCtrl::SetListViewColumnText(long row_number, int column , const wxString &Content)
{
	wxListItem     row_info;  
	wxString       cell_contents_string;
	
	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = column;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;
	
	// Get the info and store it in row_info variable.   
	this->GetItem( row_info );
	
	// Extract the text out that cell
	row_info.m_text = Content; 
	
	return this->SetItem(row_info);;
}

//-------------------------------------
IMPLEMENT_DYNAMIC_CLASS2(wxDBLCheckBox, wxCheckBox,IwxDBLControlInterface) 

bool wxDBLCheckBox::SetDBValue(wxVariant*Value,int Row)
{
	if (Value == NULL)
	{
		SetValue(false); 
		this->Enable(false);
	}
	else
	{
		SetValue(Value->GetBool()); 
		Enable(true);
	}
	
	return true;
}

wxVariant wxDBLCheckBox::GetDBValue(void)
{
	wxVariant Result = GetValue(); 
	return Result;
}

void wxDBLCheckBox::DBNotifyOnChange(void)
{
	
}

wxWindow * wxDBLCheckBox::GetWindowObj(void)
{
	return reinterpret_cast<wxWindow *>(this);
}

//-------------------------------------------------

wxDBLTable::wxDBLTable(const wxString TableName,const DatabaseLayer *dbLayer,const wxWindow *HostWindow,bool ReadOnly)
{
    m_strTableName = TableName;
    m_dbLayer = (DatabaseLayer *)dbLayer;
    m_winHostWindow = (wxWindow *)HostWindow;
    m_nDBCursor=-1;
    m_bDBOpen=false;
}

wxDBLTable::wxDBLTable()
{
    m_strTableName = wxT("");
    m_dbLayer = NULL;
    m_winHostWindow = NULL;
    m_nDBCursor=-1;
    m_bDBOpen=false;
}

void wxDBLTable::SetTableInfo(const wxString TableName,const DatabaseLayer *dbLayer,const wxWindow *HostWindow,bool ReadOnly)
{
	if (IsOpened() )
	{
		Close();
	}
    m_strTableName = TableName;
    m_dbLayer = (DatabaseLayer *)dbLayer;
    m_winHostWindow = (wxWindow *)HostWindow;
    m_nDBCursor=-1;
    m_bDBOpen=false;
}

bool wxDBLTable::Close(void)
{
	m_bDBOpen = false;
    m_nDBCursor=-1;
	m_strTableName = wxT("");
	m_bReadonly = true;
	m_bkBookMarks.clear();
    DoCursorChange();
	//Clear Data after we change the state of the controls
    m_Rows.clear();
    m_MetaData.clear();	
	m_winHostWindow = NULL;

    return true;
}

//Total Record count
long wxDBLTable::GetRecordCount()
{
	if (m_bDBOpen == false)
		return -1;
	return m_Rows.size();
}

//Record Location
long wxDBLTable::GetPosition()
{
	return m_nDBCursor;
}


bool wxDBLTable::Open(const wxString& Where)
{
    m_nDBCursor=-1;
    wxString strSQL;
    if (Where.IsEmpty())
        strSQL = wxString::Format(wxT("Select * from %s ; "),GetTableName().c_str());
    else
        strSQL = wxString::Format(wxT("Select * from %s where (%s) ; "),GetTableName().c_str(),Where.c_str());

    DatabaseResultSet *m_ResultSet;
    try
    {
        m_ResultSet = m_dbLayer->RunQueryWithResults(strSQL);
    }
    catch (DatabaseLayerException &dbExcept)
    {
        dbExcept.GetErrorCode();
        return false;
    }


    //DatabaseErrorCheck(m_pDatabase->GetDBLayer());
    if (m_ResultSet)
    {
        //Get the Meta Data and Save it to the internal memory
        ResultSetMetaData *dbMetaData = m_ResultSet->GetMetaData();
        if (dbMetaData == NULL)
        {
            m_dbLayer->CloseResultSet(m_ResultSet);
            return false;
        }
        m_MetaData.SetMetaData(dbMetaData);
        m_ResultSet->CloseMetaData(dbMetaData);

        while (m_ResultSet->Next())
        {
            //DatabaseErrorCheck(pResultSet);
            AddRowItem(m_ResultSet);
        }
        m_dbLayer->CloseResultSet(m_ResultSet);
    }


    if (m_Rows.size() >0)
        m_nDBCursor=0;
    else
        m_nDBCursor=-1;

	m_bDBOpen = true;

	OnTableOpen();
    DoCursorChange();

    return true;
}

wxDBLTable::~wxDBLTable()
{

}

void wxDBLTable::AddRowItem(DatabaseResultSet *ResultSet)
{
    wxDBLRow *dbRow = new wxDBLRow();
    for (int i = 0; i < m_MetaData.GetColumnCount();++i)
    {
        wxVariant *var = new wxVariant();
        switch (m_MetaData.GetColumnType(i))
        {
        case ResultSetMetaData::COLUMN_DATE:
            *var = ResultSet->GetResultDate(i);
            break;
        case ResultSetMetaData::COLUMN_BLOB:
            //var = ResultSet->GetResultBlob(i);
            break;
        case ResultSetMetaData::COLUMN_BOOL:
            *var = ResultSet->GetResultBool(i);
            break;
        case ResultSetMetaData::COLUMN_INTEGER:
            *var= (long)ResultSet->GetResultInt(i);
            break;
        case ResultSetMetaData::COLUMN_STRING:
            *var = ResultSet->GetResultString(i);
            break;
        case ResultSetMetaData::COLUMN_DOUBLE:
            *var = ResultSet->GetResultDouble(i);
            break;
        case ResultSetMetaData::COLUMN_NULL:
            //var = NULL;
            break;
        case ResultSetMetaData::COLUMN_UNKNOWN:
            //var = NULL;
            break;
        default:
            //var = NULL;
            break;
        }

        dbRow->push_back(var);
    }
    m_Rows.push_back(dbRow);

}

wxVariant* wxDBLTable::GetValueFromFieldName(const wxString &FieldName)
{
	if (m_bDBOpen == false)
	{
		return NULL;
	}

    if ((m_nDBCursor==-1) && (m_Rows.size() >= m_nDBCursor))
		return NULL;
	
	int nFPos = m_MetaData.IsFieldInList(FieldName);
	if (nFPos == -1)
	{
		return NULL;
	}
	
	return m_Rows[m_nDBCursor]->at(nFPos);
}

bool wxDBLTable::SetControlInfo(IwxDBLControlInterface* ctrl)
{
	if ((IsEmpty()==true) || (IsOpened() == false) )
	{
		ctrl->SetDBValue(NULL,-1);
		ctrl->GetWindowObj()->Enable(false);
		return false;
	}
	
	wxVariant *Var = GetValueFromFieldName(ctrl->GetDBFieldName());
	if (Var == NULL)
	{
		ctrl->SetDBValue(NULL,-1);
		ctrl->GetWindowObj()->Enable(false);
		return false;
	}
	else
	{
		ctrl->SetDBValue(Var,GetPosition());
		ctrl->GetWindowObj()->Enable(true);
	}
	
	return true;
}

bool wxDBLTable::New(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor!=-1)
    {
        //Implement New Record Addition Code
        DoCursorChange();
    }
    return result;
}

bool wxDBLTable::Delete(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor>0)
    {
        //Implement Delete
        DoCursorChange();
    }
    return result;
}

bool wxDBLTable::Find(const wxString &FindText)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    int from;
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }
    if (m_nDBCursor<(m_Rows.size() -1))
    {
        from = m_nDBCursor+1;
        //Find and Set the DBCursor pos
        //if foundAndSet { DoCursorChange;}
    }
    return result;
}

bool wxDBLTable::IsEmpty()
{
	if ( (m_bDBOpen == false) || (m_nDBCursor == -1) || (m_Rows.size() == 0))
		return true;
	else
		return false;
}

bool wxDBLTable::First(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }
    
	m_nDBCursor = 0;
    result = true;
    DoCursorChange();

    return result;
}

wxDBLRow* wxDBLTable::GetRecord(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    if (m_nDBCursor< 0)
    {
        return NULL;
    }
    if (m_nDBCursor<m_Rows.size())
    {
        //m_nDBCursor = 0;
        return m_Rows.at(m_nDBCursor);
    }
    return NULL;

};

bool wxDBLTable::Last(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }
    if (m_nDBCursor<(m_Rows.size() -1))
    {
        m_nDBCursor = m_Rows.size()-1;
        result = true;
        DoCursorChange();
    }
    return result;
}

bool wxDBLTable::Next(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }

    if (m_nDBCursor<(m_Rows.size() - 1))
    {
        ++m_nDBCursor;
        result = true;
        DoCursorChange();
    }
    return result;
}

bool wxDBLTable::Prior(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }
    if (m_nDBCursor<m_Rows.size())
    {
        --m_nDBCursor;
        result = true;
        DoCursorChange();
    }
    return result;
}

bool wxDBLTable::Goto(int Position)
{
	if ((m_Rows.size() ==0) || (m_nDBCursor ==-1) || (Position > m_Rows.size() -1))
		return false;
	else
	{
		m_nDBCursor = Position;
		DoCursorChange();
		return true;
	}
}

bool wxDBLTable::IsFirst(void)
{
	if ((m_Rows.size() ==0) || (m_nDBCursor !=0))
		return false;
	else
		return true;
}
bool wxDBLTable::IsLast(void)
{
	if ((m_Rows.size() ==0) || (m_nDBCursor != m_Rows.size()-1))
		return false;
	else
		return true;
}

bool wxDBLTable::HasNext(void)
{
	int NextCursorPos = m_nDBCursor + 1;
	if ( (m_bDBOpen == false) || (m_Rows.size() ==0) || (NextCursorPos >= m_Rows.size()))
		return false;
	else
		return true;
}

bool wxDBLTable::HasPrior(void)
{
	int PrevCursorPos = m_nDBCursor - 1;
	if ( (m_bDBOpen == false) || (m_Rows.size() ==0) || (PrevCursorPos < 0))
		return false;
	else
		return true;
}


bool wxDBLTable::SetRecord(wxDBLRow* Row)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    bool result=false;
    if (m_nDBCursor < 0)
    {
        return result;
    }
    if (m_nDBCursor<(m_Rows.size() - 1))
    {
        m_Rows.at(m_nDBCursor) = Row;
        result = true;
        DoCursorChange();
    }
    return result;
}

/*
void DWTable::SetonCursorChanged(const Value: TonCursorChanged)
{
  FonCursorChanged = Value;
}

void DWTable::CursorChanged(NameValues: TStringList;FieldCount:integer)
{
 if assigned(onCursorchanged) then
  onCursorChanged(self,NameValues,FieldCount);
}
*/

void wxDBLTable::OnTableOpen(void)
{
	if (m_winHostWindow == NULL)
		return;
	FillControls(m_winHostWindow);

}

void wxDBLTable::DoCursorChange(void)
{
	if (m_winHostWindow == NULL)
		return;

	if (IsOpened())
	{
		wxDBLRow *CurrentRow = GetRecord();
		DisplayFields(CurrentRow,m_winHostWindow);
	}
	else
	{
		DisableControls();
		ClearControlsValue(m_winHostWindow);
	}
	
    //Call the Function that is subscribed for On Cursor Change
	wxCommandEvent event(wxEVT_DBL_CURSORCHANGED, m_winHostWindow->GetId());
	event.SetEventObject(m_winHostWindow);
	m_winHostWindow->ProcessEvent(event);
}

bool wxDBLTable::EnableControls(void)
{
	SetControlsEnable(true,m_winHostWindow);
	return true;
}

bool wxDBLTable::DisableControls(void)
{
	SetControlsEnable(false,m_winHostWindow);
	return true;
}


void wxDBLTable::SetControlsEnable(bool Status,wxWindow *ParentWindow)
{
    for ( wxWindowList::compatibility_iterator node = ParentWindow->GetChildren().GetFirst();node; node = node->GetNext())
    {
        wxWindow *child = node->GetData();
        if (child->GetChildren().size() > 0 )
        {
            SetControlsEnable(Status, child);
            continue;
        }
        IwxDBLControlInterface *cntrIntf = GetCastedObj2(child);
		if (cntrIntf == NULL)
			continue;
		child->Enable(Status);
    }

	return;
}

void wxDBLTable::ClearControlsValue(wxWindow *ParentWindow)
{
    for ( wxWindowList::compatibility_iterator node = ParentWindow->GetChildren().GetFirst();node; node = node->GetNext())
    {
        wxWindow *child = node->GetData();
        if (child->GetChildren().size() > 0 )
        {
            ClearControlsValue(child);
            continue;
        }
        IwxDBLControlInterface *cntrIntf = GetCastedObj2(child);
		if (cntrIntf == NULL)
			continue;
		cntrIntf->SetDBValue(NULL,-1);
    }
	
	return;
}

IwxDBLControlInterface* GetCastedObj2(wxWindow *wndows)
{
	wxString CName = wndows->GetClassInfo()->GetClassName();
	wxString Base1 = wndows->GetClassInfo()->GetBaseClassName1();
	wxString Base2 = wndows->GetClassInfo()->GetBaseClassName2();
	
	wxString BaseClassName = wxT("IwxDBLControlInterface");
	BaseClassName = BaseClassName.MakeUpper();
	bool bClasFound = false;
	wxString strClassName;
	if (   (CName.CmpNoCase(BaseClassName) == 0)
			|| (Base1.CmpNoCase(BaseClassName) == 0)  
			|| (Base2.CmpNoCase(BaseClassName) == 0 ))
		{
			strClassName = BaseClassName;
			bClasFound = true;
		}
	
	
	if (bClasFound)
	{
		IwxDBLControlInterface *ctrlItem = dynamic_cast<IwxDBLControlInterface *>(wndows);
		wxString dbNameStr = ctrlItem->GetDBFieldName();
		return ctrlItem;
	}
	else
		return NULL;
}

/*
IwxDBLControlInterface* GetCastedObj(wxWindow *wndows)
{
	wxString CName = wndows->GetClassInfo()->GetClassName();
	wxString Base1 = wndows->GetClassInfo()->GetBaseClassName1();
	wxString Base2 = wndows->GetClassInfo()->GetBaseClassName2();
	
	int si = sizeof(g_Supported_Controls) / sizeof(g_Supported_Controls[0]) ;
	
	bool bClasFound = false;
	wxString strClassName;
	for (int i = 0 ; i < si; ++i )
	{
		if (   (CName.CmpNoCase(g_Supported_Controls[i]) == 0)
			|| (Base1.CmpNoCase(g_Supported_Controls[i]) == 0)  
			|| (Base2.CmpNoCase(g_Supported_Controls[i]) == 0 ))
		{
			strClassName = g_Supported_Controls[i];
			bClasFound = true;
			break;
		}
	}

	if (bClasFound)
	{
		IwxDBLControlInterface *ctrlItem;
		if (strClassName.CmpNoCase("wxDBLTextCtrl") == 0)
		{
			wxDBLTextCtrl *txtCtrl = wxDynamicCast(wndows, wxDBLTextCtrl);
			ctrlItem= wxDynamicCast(wndows, wxDBLTextCtrl);
		}
		else if (strClassName.CmpNoCase("wxDBLStaticText") == 0)
		{
			wxDBLStaticText *txtCtrl = wxDynamicCast(wndows, wxDBLStaticText);
			ctrlItem= wxDynamicCast(wndows, wxDBLStaticText);			
		}else if (strClassName.CmpNoCase("wxDBLSpinCtrl") == 0)
		{
			wxDBLSpinCtrl *txtCtrl = wxDynamicCast(wndows, wxDBLSpinCtrl);
			ctrlItem= wxDynamicCast(wndows, wxDBLSpinCtrl);			
		}else if (strClassName.CmpNoCase("wxDBLComboBox") == 0)
		{
			wxDBLComboBox *txtCtrl = wxDynamicCast(wndows, wxDBLComboBox);
			ctrlItem= wxDynamicCast(wndows, wxDBLComboBox);			
		}else if (strClassName.CmpNoCase("wxDBLCheckBox") == 0)
		{
			wxDBLCheckBox *txtCtrl = wxDynamicCast(wndows, wxDBLCheckBox);
			ctrlItem= wxDynamicCast(wndows, wxDBLCheckBox);			
		}else if (strClassName.CmpNoCase("wxDBLListBox") == 0)
		{
			wxDBLListBox *txtCtrl = wxDynamicCast(wndows, wxDBLListBox);
			ctrlItem= wxDynamicCast(wndows, wxDBLListBox);			
		} 		
		else if (strClassName.CmpNoCase("wxDBLListCtrl") == 0)
		{
			wxDBLListCtrl *txtCtrl = wxDynamicCast(wndows, wxDBLListCtrl);
			ctrlItem= wxDynamicCast(wndows, wxDBLListCtrl);			
		} 				
		else
		{
			return NULL;
		}
		return ctrlItem;
	}
	else
		return NULL;
}
*/
void wxDBLTable::DisplayFields(wxDBLRow *Row, wxWindow *ParentWindow)
{
    if (Row->size() < 1)
    {
        return;
    }

    for ( wxWindowList::compatibility_iterator node = ParentWindow->GetChildren().GetFirst();node; node = node->GetNext())
    {
        wxWindow *child = node->GetData();
        if (child->GetChildren().size() > 0 )
        {
            DisplayFields(Row, child);
            continue;
        }
        IwxDBLControlInterface *cntrIntf = GetCastedObj2(child);
        if (cntrIntf == NULL)
            continue;
        if (cntrIntf->GetDBTableObj() == this)
        {
            if (cntrIntf->GetDBFieldName() == wxT(""))
			{
				if (cntrIntf->IsFillContainer())
					cntrIntf->SetDBValue(NULL,GetPosition());
				else 
					cntrIntf->SetDBValue(NULL,-1);
                continue;
			}

			wxString FName = cntrIntf->GetDBFieldName();
            int iPos = m_MetaData.IsFieldInList(cntrIntf->GetDBFieldName());
            if (iPos >= 0)
            {
                cntrIntf->SetDBValue(Row->at(iPos),GetPosition());
            }
			else
			{
				for (int k =0 ; k < m_MetaData.GetColumnCount() ; ++k)
				{
					FName = m_MetaData.GetColumnName(k);
					FName = FName;
				}
				cntrIntf->SetDBValue(NULL,GetPosition());
                continue;
			}
        }
    }

}

void wxDBLTable::FillControls(wxWindow *ParentWindow)
{
    for ( wxWindowList::compatibility_iterator node = ParentWindow->GetChildren().GetFirst();node; node = node->GetNext())
    {
        wxWindow *child = node->GetData();
        if (child->GetChildren().size() > 0 )
        {
            FillControls(child);
            continue;
        }
        IwxDBLControlInterface *cntrIntf = GetCastedObj2(child);
        if (cntrIntf == NULL)
            continue;
        if (cntrIntf->GetDBTableObj() == this)
        {
            if (cntrIntf->GetDBFieldName() == wxT(""))
			{
				if (cntrIntf->IsFillContainer() == false)
					continue;
			}
			
			if (cntrIntf->IsFillContainer() == false)
				continue;

			wxString FName = cntrIntf->GetDBFieldName();
            int iPos = m_MetaData.IsFieldInList(cntrIntf->GetDBFieldName());
            cntrIntf->FillWithTableContent(this,iPos);

        }		
    }	
}


bool wxDBLTable::Display(void)
{
    bool result = false;
    //doCursorChange();
    return result;
}

bool wxDBLTable::Post(void)
{
	if (m_bDBOpen == false)
	{
		throw wxDBLException(wxT("Database not opened."),0);
	}
    return false;
}

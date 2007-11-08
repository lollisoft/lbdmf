//---------------------------------------------------------------------------
//
// Name:        dmTestDlg.cpp
// Author:      Guru Kathiresan
// Created:     11/8/2006 5:53:38 PM
// Description: dmTestDlg class implementation
//
//---------------------------------------------------------------------------

#include "dmTestDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// dmTestDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(dmTestDlg,wxDialog)
	////Manual Code Start
	EVT_DBL_CURSORCHANGED(-1,dmTestDlg::OnDBLTableCursorChange)
	////Manual Code End
	
	EVT_CLOSE(dmTestDlg::OnClose)
	EVT_BUTTON(ID_BTLAST,dmTestDlg::btLastClick)
	EVT_UPDATE_UI(ID_BTLAST,dmTestDlg::btLastUpdateUI)
	EVT_BUTTON(ID_BTPREVIOUS,dmTestDlg::btPreviousClick)
	EVT_UPDATE_UI(ID_BTPREVIOUS,dmTestDlg::btPreviousUpdateUI)
	EVT_BUTTON(ID_BTNEXT,dmTestDlg::btNextClick)
	EVT_UPDATE_UI(ID_BTNEXT,dmTestDlg::btNextUpdateUI)
	EVT_BUTTON(ID_BTFIRST,dmTestDlg::btFirstClick)
	EVT_UPDATE_UI(ID_BTFIRST,dmTestDlg::btFirstUpdateUI)
	EVT_BUTTON(ID_BTCLOSE,dmTestDlg::btCloseClick)
	EVT_UPDATE_UI(ID_BTCLOSE,dmTestDlg::btCloseUpdateUI)
	EVT_BUTTON(ID_BTOPEN,dmTestDlg::btOpenClick)
	EVT_UPDATE_UI(ID_BTOPEN,dmTestDlg::btOpenUpdateUI)
END_EVENT_TABLE()
////Event Table End

dmTestDlg::dmTestDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	m_pdbLayer = NULL;
	CreateGUIControls();	
}

dmTestDlg::~dmTestDlg()
{
} 

void dmTestDlg::CreateGUIControls()
{
	//Do not add custom code here
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_RIGHT | wxALL, 0);

	lbStatus = new wxStaticText(this, ID_LBSTATUS, wxT("DB is Closed"), wxPoint(2,2), wxSize(83, 17), wxST_NO_AUTORESIZE, wxT("lbStatus"));
	lbStatus->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxBOLD, FALSE));
	WxBoxSizer2->Add(lbStatus,0,wxALIGN_RIGHT | wxALL,2);

	WxBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer3, 0, wxALIGN_CENTER | wxALL, 0);

	WxNotebook1 = new wxNotebook(this, ID_WXNOTEBOOK1, wxPoint(0,0),wxSize(431,201));
	WxBoxSizer3->Add(WxNotebook1,0,wxALIGN_CENTER | wxALL,0);

	WxNoteBookPage1 = new wxPanel(WxNotebook1, ID_WXNOTEBOOKPAGE1, wxPoint(4,24), wxSize(423,173));
	WxNotebook1->AddPage(WxNoteBookPage1, wxT("Basic Controls"));

	WxStaticBox1 = new wxStaticBox(WxNoteBookPage1, ID_WXSTATICBOX1, wxT(""), wxPoint(122,5), wxSize(300,163));

	txtName = new wxDBLTextCtrl(WxNoteBookPage1, ID_TXTNAME, wxT("txtName"), wxPoint(181,25), wxSize(236,21), 0, wxDefaultValidator, wxT("txtName"));

	cbWork = new wxDBLCheckBox(WxNoteBookPage1, ID_CBWORK, wxT("Can work over time"), wxPoint(132,113), wxSize(204,17), 0, wxDefaultValidator, wxT("cbWork"));

	wxArrayString arrayStringFor_cbxCity;
	cbxCity = new wxDBLComboBox(WxNoteBookPage1, ID_CBXCITY, wxT("cbxCity"), wxPoint(180,51), wxSize(120,21), arrayStringFor_cbxCity, 0, wxDefaultValidator, wxT("cbxCity"));

	WxStaticText1 = new wxStaticText(WxNoteBookPage1, ID_WXSTATICTEXT1, wxT("Name"), wxPoint(139,25), wxDefaultSize, 0, wxT("WxStaticText1"));

	WxStaticText2 = new wxStaticText(WxNoteBookPage1, ID_WXSTATICTEXT2, wxT("City"), wxPoint(138,51), wxDefaultSize, 0, wxT("WxStaticText2"));

	spcAge = new wxDBLSpinCtrl(WxNoteBookPage1, ID_SPCAGE, wxT("0"), wxPoint(180,79), wxSize(121,22), wxSP_ARROW_KEYS, 0, 100000, 0);

	WxStaticText3 = new wxStaticText(WxNoteBookPage1, ID_WXSTATICTEXT3, wxT("Age"), wxPoint(140,83), wxDefaultSize, 0, wxT("WxStaticText3"));

	WxStaticText4 = new wxStaticText(WxNoteBookPage1, ID_WXSTATICTEXT4, wxT("Phone "), wxPoint(133,143), wxDefaultSize, 0, wxT("WxStaticText4"));

	lbPhone = new wxDBLStaticText(WxNoteBookPage1, ID_LBPHONE, wxT("lbPhone"), wxPoint(212,143), wxDefaultSize, 0, wxT("lbPhone"));

	wxArrayString arrayStringFor_lbNames;
	lbNames = new wxDBLListBox(WxNoteBookPage1, ID_LBNAMES, wxPoint(4,8), wxSize(113,161), arrayStringFor_lbNames, wxLB_SINGLE);

	WxNoteBookPage2 = new wxPanel(WxNotebook1, ID_WXNOTEBOOKPAGE2, wxPoint(4,24), wxSize(423,173));
	WxNotebook1->AddPage(WxNoteBookPage2, wxT("List View"));

	WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer4, 0, wxALIGN_RIGHT | wxALL, 0);

	btOpen = new wxButton(this, ID_BTOPEN, wxT("Open"), wxPoint(5,5), wxSize(60,25), 0, wxDefaultValidator, wxT("btOpen"));
	WxBoxSizer4->Add(btOpen,0,wxALIGN_CENTER | wxALL,5);

	btClose = new wxButton(this, ID_BTCLOSE, wxT("Close"), wxPoint(75,5), wxSize(60,25), 0, wxDefaultValidator, wxT("btClose"));
	WxBoxSizer4->Add(btClose,0,wxALIGN_CENTER | wxALL,5);

	btFirst = new wxButton(this, ID_BTFIRST, wxT("First"), wxPoint(145,5), wxSize(50,25), 0, wxDefaultValidator, wxT("btFirst"));
	WxBoxSizer4->Add(btFirst,0,wxALIGN_CENTER | wxALL,5);

	btNext = new wxButton(this, ID_BTNEXT, wxT("Next"), wxPoint(205,5), wxSize(50,25), 0, wxDefaultValidator, wxT("btNext"));
	WxBoxSizer4->Add(btNext,0,wxALIGN_CENTER | wxALL,5);

	btPrevious = new wxButton(this, ID_BTPREVIOUS, wxT("Previous"), wxPoint(265,5), wxSize(50,25), 0, wxDefaultValidator, wxT("btPrevious"));
	WxBoxSizer4->Add(btPrevious,0,wxALIGN_CENTER | wxALL,5);

	btLast = new wxButton(this, ID_BTLAST, wxT("Last"), wxPoint(325,5), wxSize(50,25), 0, wxDefaultValidator, wxT("btLast"));
	WxBoxSizer4->Add(btLast,0,wxALIGN_CENTER | wxALL,5);

	WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	WxNoteBookPage2->SetSizer(WxBoxSizer5);
	WxNoteBookPage2->SetAutoLayout(true);

	lvAddresses = new wxDBLListCtrl(WxNoteBookPage2, ID_LVADDRESSES, wxPoint(5,5), wxSize(410,155), wxLC_REPORT);
	lvAddresses->InsertColumn(0,wxT("City"),wxLIST_FORMAT_LEFT,120 );
	lvAddresses->InsertColumn(0,wxT("Age"),wxLIST_FORMAT_LEFT,61 );
	lvAddresses->InsertColumn(0,wxT("Name"),wxLIST_FORMAT_LEFT,149 );
	WxBoxSizer5->Add(lvAddresses,1,wxEXPAND | wxALL,5);

	SetTitle(wxT("dblControls - Test"));
	SetIcon(wxNullIcon);
	
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	
	txtName->SetDBFieldName(wxT("txtName"));
	txtName->SetDBTableObj(&m_dblTable);
	
	spcAge->SetDBFieldName(wxT("nAge"));
	spcAge->SetDBTableObj(&m_dblTable);
    	
	cbxCity->SetDBFieldName(wxT("txtCity"));
    cbxCity->SetDBTableObj(&m_dblTable);
	
	lbPhone->SetDBFieldName(wxT("txtPhone"));
	lbPhone->SetDBTableObj(&m_dblTable);

	lbNames->SetDBFieldName(wxT("txtName"));
	lbNames->SetDBTableObj(&m_dblTable);

	wxArrayString strArrayColumnList;
	strArrayColumnList.Add(wxT("txtName"));
	strArrayColumnList.Add(wxT("nAge"));
	strArrayColumnList.Add(wxT("txtCity"));

    lvAddresses->SetDBFieldName(wxT(""));
	lvAddresses->SetDBTableObj(&m_dblTable);
	lvAddresses->SetDBColumnList(strArrayColumnList);

	//SetOnDBCloseUI();
	OpenDB();
	//SetDBControl(&m_dblTable);

}


void dmTestDlg::OpenDB()
{
	if (m_pdbLayer != NULL)
	{
		m_dblTable.Close();
		delete m_pdbLayer;
		m_pdbLayer = NULL;
	}

	m_pdbLayer = new SqliteDatabaseLayer();
	wxString DBFName = wxT("dblsample.db");

	if (wxFileExists(DBFName) == false )
		DBFName = wxT("../dblsample.db");

	if (m_pdbLayer->Open(DBFName) == false)
	{
		m_dblTable.Close();
		delete m_pdbLayer;
		m_pdbLayer = NULL;
		return;
	}
	m_dblTable.SetTableInfo(wxT("dblsample"),m_pdbLayer,this);
	m_dblTable.Open();

}

void dmTestDlg::CloseDB()
{
	if (m_pdbLayer != NULL)
	{
		m_dblTable.Close();
		delete m_pdbLayer;
		m_pdbLayer = NULL;
	}
}

void dmTestDlg::SetDBControl(wxDBLTable *m_dblTable)
{
	

	if (m_dblTable->IsOpened())
		m_dblTable->Close();

	//WxEdit1->SetDBTableObj(m_dblTable);
	//WxEdit1->SetDBFieldName("txtField");

	m_dblTable->Open(wxT(""));
	if (m_dblTable->IsOpened())
	{
		//
	}	
}


void dmTestDlg::SetOnDBOpenUI()
{
	btClose->Enable(true);
	btOpen->Enable(false);
	btLast->Enable(false);
	btPrevious->Enable(false);
	btNext->Enable(false);
	btFirst->Enable(false);
}

void dmTestDlg::SetOnDBCloseUI()
{
	btClose->Enable(false);
	btOpen->Enable(true);
	btLast->Enable(true);
	btPrevious->Enable(true);
	btNext->Enable(true);
	btFirst->Enable(true);
}

void dmTestDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * btFirstClick
 */
void dmTestDlg::btFirstClick(wxCommandEvent& event)
{
	m_dblTable.First();
}

/*
 * btNextClick
 */
void dmTestDlg::btNextClick(wxCommandEvent& event)
{
	m_dblTable.Next();
}

/*
 * btPreviousClick
 */
void dmTestDlg::btPreviousClick(wxCommandEvent& event)
{
	m_dblTable.Prior();
}

/*
 * btLastClick
 */
void dmTestDlg::btLastClick(wxCommandEvent& event)
{
	m_dblTable.Last();
}

/*
 * btOpenClick
 */
void dmTestDlg::btOpenClick(wxCommandEvent& event)
{
	OpenDB();
}

/*
 * btCloseClick
 */
void dmTestDlg::btCloseClick(wxCommandEvent& event)
{
	CloseDB();
}

/*
 * btOpenUpdateUI
 */
void dmTestDlg::btOpenUpdateUI(wxUpdateUIEvent& event)
{
	event.Enable(!m_dblTable.IsOpened());
}

/*
 * btCloseUpdateUI
 */
void dmTestDlg::btCloseUpdateUI(wxUpdateUIEvent& event)
{
	if (m_dblTable.IsOpened() == false)
		event.Enable(false);
	else
		event.Enable(m_dblTable.IsOpened());
}

/*
 * btFirstUpdateUI
 */
void dmTestDlg::btFirstUpdateUI(wxUpdateUIEvent& event)
{
	if (m_dblTable.IsOpened() == false)
		event.Enable(false);
	else
		event.Enable(!m_dblTable.IsFirst());
}

/*
 * btNextUpdateUI
 */
void dmTestDlg::btNextUpdateUI(wxUpdateUIEvent& event)
{
	if (m_dblTable.IsOpened() == false)
		event.Enable(false);
	else
		event.Enable(m_dblTable.HasNext());
}

/*
 * btPreviousUpdateUI
 */
void dmTestDlg::btPreviousUpdateUI(wxUpdateUIEvent& event)
{
	if (m_dblTable.IsOpened() == false)
		event.Enable(false);
	else
		event.Enable(m_dblTable.HasPrior());
}

/*
 * btLastUpdateUI
 */
void dmTestDlg::btLastUpdateUI(wxUpdateUIEvent& event)
{
	if (m_dblTable.IsOpened() == false)
		event.Enable(false);
	else
		event.Enable(!m_dblTable.IsLast());
}

void dmTestDlg::OnDBLTableCursorChange(wxCommandEvent &event)
{
	if (m_dblTable.IsOpened())
		lbStatus->SetLabel(wxString::Format(wxT("Position %d / %d"),m_dblTable.GetPosition()+1,m_dblTable.GetRecordCount()));
	else
		lbStatus->SetLabel(wxString::Format(wxT("DB Closed.")));


	
}

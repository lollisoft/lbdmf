//---------------------------------------------------------------------------
//
// Name:        dmTestDlg.h
// Author:      Guru Kathiresan
// Created:     11/8/2006 5:53:38 PM
// Description: dmTestDlg class declaration
//
//---------------------------------------------------------------------------

#ifndef __DMTESTDLG_h__
#define __DMTESTDLG_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
////Header Include End

#include "DatabaseLayer.h"
#include "DatabaseErrorCodes.h"
#include "DatabaseLayerException.h"

//Controls
#include "dblcontrols.h"


#define USE_SQLITE 1


#if defined(USE_SQLITE)
#include "SqliteDatabaseLayer.h"
#endif

#if defined(USE_FIREBIRD)
#include "FirebirdDatabaseLayer.h"
#endif

#if defined(USE_POSTGRESQL)
#include "PostgresDatabaseLayer.h"
#endif

#if defined(USE_MYSQL)
#include "MysqlDatabaseLayer.h"
#endif


////Dialog Style Start
#undef dmTestDlg_STYLE
#define dmTestDlg_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTHICK_FRAME | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class dmTestDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		dmTestDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("dblControls - Test"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = dmTestDlg_STYLE);
		virtual ~dmTestDlg();
		void btFirstClick(wxCommandEvent& event);
		void btNextClick(wxCommandEvent& event);
		void btPreviousClick(wxCommandEvent& event);
		void btLastClick(wxCommandEvent& event);
		void btOpenClick(wxCommandEvent& event);
		void btCloseClick(wxCommandEvent& event);
		void btOpenUpdateUI(wxUpdateUIEvent& event);
		void btCloseUpdateUI(wxUpdateUIEvent& event);
		void btFirstUpdateUI(wxUpdateUIEvent& event);
		void btNextUpdateUI(wxUpdateUIEvent& event);
		void btPreviousUpdateUI(wxUpdateUIEvent& event);
		void btLastUpdateUI(wxUpdateUIEvent& event);
	
	private:
		//Do not add custom control declarations
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxDBLListCtrl *lvAddresses;
		wxBoxSizer *WxBoxSizer5;
		wxButton *btLast;
		wxButton *btPrevious;
		wxButton *btNext;
		wxButton *btFirst;
		wxButton *btClose;
		wxButton *btOpen;
		wxBoxSizer *WxBoxSizer4;
		wxPanel *WxNoteBookPage2;
		wxDBLListBox *lbNames;
		wxDBLStaticText *lbPhone;
		wxStaticText *WxStaticText4;
		wxStaticText *WxStaticText3;
		wxDBLSpinCtrl *spcAge;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxDBLComboBox *cbxCity;
		wxDBLCheckBox *cbWork;
		wxDBLTextCtrl *txtName;
		wxStaticBox *WxStaticBox1;
		wxPanel *WxNoteBookPage1;
		wxNotebook *WxNotebook1;
		wxBoxSizer *WxBoxSizer3;
		wxStaticText *lbStatus;
		wxBoxSizer *WxBoxSizer2;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_LVADDRESSES = 1229,
			ID_BTLAST = 1221,
			ID_BTPREVIOUS = 1220,
			ID_BTNEXT = 1219,
			ID_BTFIRST = 1218,
			ID_BTCLOSE = 1217,
			ID_BTOPEN = 1216,
			ID_WXNOTEBOOKPAGE2 = 1223,
			ID_LBNAMES = 1199,
			ID_LBPHONE = 1197,
			ID_WXSTATICTEXT4 = 1196,
			ID_WXSTATICTEXT3 = 1195,
			ID_SPCAGE = 1194,
			ID_WXSTATICTEXT2 = 1193,
			ID_WXSTATICTEXT1 = 1192,
			ID_CBXCITY = 1191,
			ID_CBWORK = 1188,
			ID_TXTNAME = 1183,
			ID_WXSTATICBOX1 = 1182,
			ID_WXNOTEBOOKPAGE1 = 1028,
			ID_WXNOTEBOOK1 = 1027,
			ID_LBSTATUS = 1222,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};

	private:
		DatabaseLayer *m_pdbLayer;
		wxDBLTable m_dblTable;

	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void SetOnDBOpenUI();
		void SetOnDBCloseUI();
		void SetDBControl(wxDBLTable *m_dblTable);
		void OpenDB();
		void CloseDB();

	public:
		void OnDBLTableCursorChange(wxCommandEvent &event);
};

#endif

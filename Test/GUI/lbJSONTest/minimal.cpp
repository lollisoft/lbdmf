/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "wx/sstream.h"
#include "wx/protocol/http.h"

#include "wx/jsonreader.h"
#include "wx/jsonval.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "sample.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();// wxOVERRIDE;
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	
	void OnTestJson(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,
	Minimal_TestJson = 1001
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MENU(Minimal_TestJson, MyFrame::OnTestJson)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp);

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame("Minimal wxWidgets App");

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUBAR
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    fileMenu->Append(Minimal_TestJson, "&Test Json\tF2", "Test Json API");
    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#else // !wxUSE_MENUBAR
    // If menus are not available add a button to access the about box
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* aboutBtn = new wxButton(this, wxID_ANY, "About...");
    wxButton* jsonBtn = new wxButton(this, wxID_ANY, "Test Json...");
    aboutBtn->Bind(wxEVT_BUTTON, &MyFrame::OnAbout, this);
    jsonBtn->Bind(wxEVT_BUTTON, &MyFrame::OnTestJson, this);
    sizer->Add(aboutBtn, wxSizerFlags().Center());
    sizer->Add(jsonBtn, wxSizerFlags().Center());
    SetSizer(sizer);
#endif // wxUSE_MENUBAR/!wxUSE_MENUBAR

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
#endif // wxUSE_STATUSBAR
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnTestJson(wxCommandEvent& WXUNUSED(event))
{
	wxJSONValue  lastReleaseInfo;
	wxHTTP get;
	wxString durationPoints;
	wxString releaseInfo;
	wxString releaseMsg;
	int timeout = 10;
	int retry = 5;

	get.SetHeader("Content-type", "text/html; charset=utf-8");
	get.SetTimeout(timeout);

	durationPoints = "Checking for software update. Connection failed. Do a retry ";

	while (!get.Connect(_T("www.lollisoft.de")))
	{
		timeout++;

		SetStatusText(durationPoints);
		durationPoints += ".";
		wxSleep(1);
		
		if (retry-- == 0)
			return;
	}
	
	wxApp::IsMainLoopRunning(); // should return true
	
	// use _T("/") for index.html, index.php, default.asp, etc.
	wxInputStream *httpStream = NULL;
	
	wxString uri = "/updates/lbdmf.json?ostype=Windows&version=1.3.2";
	
	httpStream = get.GetInputStream(uri);
	
	if (get.GetError() == wxPROTO_NOERR)
	{
		wxString res;
		wxStringOutputStream out_stream(&res);
		httpStream->Read(out_stream);
		
		// construct a JSON parser
		wxJSONReader reader;
		int numErrors = reader.Parse( res, &lastReleaseInfo );

		if (numErrors > 0) {
			wxMessageBox("Unable to read update information!");
		} else {
			SetStatusText("Got release information. Parsing ...");
			wxJSONValue releases = lastReleaseInfo["releases"];
			bool isArray = releases.IsArray();

			if (isArray) {
				for ( int i = 0; i < releases.Size(); i++ ) {
					releaseInfo = releases[i]["version"].AsString();
				}
			}

		}
	}
	
	if (releaseInfo == "") {
		releaseMsg = wxString::Format("No version info found\nRunning under %s.", wxGetOsDescription());
	} else {
		releaseMsg = wxString::Format("Version info found: %s\nRunning under %s.", releaseInfo, wxGetOsDescription());
	}
	
    wxMessageBox(releaseMsg, "About wxWidgets minimal sample", wxOK | wxICON_INFORMATION, this);
}
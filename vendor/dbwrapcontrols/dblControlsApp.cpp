//---------------------------------------------------------------------------
//
// Name:        dblControlsApp.cpp
// Author:      Guru Kathiresan
// Created:     11/8/2006 5:53:38 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "dblControlsApp.h"
#include "dmTestDlg.h"

IMPLEMENT_APP(dmTestDlgApp)

bool dmTestDlgApp::OnInit()
{
	dmTestDlg* dialog = new dmTestDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int dmTestDlgApp::OnExit()
{
	return 0;
}

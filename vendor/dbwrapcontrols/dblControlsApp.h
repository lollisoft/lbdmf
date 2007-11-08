//---------------------------------------------------------------------------
//
// Name:        dblControlsApp.h
// Author:      Guru Kathiresan
// Created:     11/8/2006 5:53:38 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __DMTESTDLGApp_h__
#define __DMTESTDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class dmTestDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif

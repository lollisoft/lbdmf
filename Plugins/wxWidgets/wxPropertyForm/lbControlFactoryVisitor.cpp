/*...sLicense:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
 The author of this work will be reached by e-Mail or paper mail.
 e-Mail: lothar.behrens@lollisoft.de
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1.2.1 $
 * $Name:  $
 * $Id: lbControlFactoryVisitor.cpp,v 1.1.2.1 2015/08/27 14:15:20 lollisoft Exp $
 *
 * $Log: lbControlFactoryVisitor.cpp,v $
 * Revision 1.1.2.1  2015/08/27 14:15:20  lollisoft
 * First basic implementation of a property dialog using a visitor factory.
 *
 * Revision 1.1.2.1  2015/07/12 10:05:50  lollisoft
 * Added new property dialog and panel implementations. A first step toward workflow enabled dialogs.
 *
 **************************************************************/
/*...e*/

/*...sincludes:0:*/
#include <lbDMF_wxPrec.h>

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	//#include <conio.h>
	
#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
#include <wx/image.h>
#include <wx/datectrl.h>
#include <wx/file.h>
/*...e*/

//#include "wx/textbox.h"
//#include "childwnd.h"


#include <lbControlFactory.h>


BEGIN_IMPLEMENT_LB_UNKNOWN(lbUIElementFactoryAspect)
	ADD_INTERFACE(lb_I_Aspect)
	ADD_INTERFACE(lb_I_UIElementFactoryAspect)
END_IMPLEMENT_LB_UNKNOWN()

lbUIElementFactoryAspect::lbUIElementFactoryAspect() {
	// Once per form
	sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	// Once per column. If there are more than one columns to be used, create them sequentially and reuse this variable.
	sizerColumn  = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(sizerColumn, 1, wxEXPAND | wxALL, 5);
	
	REQUEST(getModuleInstance(), lb_I_String, currentLabel)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
}

lbUIElementFactoryAspect::~lbUIElementFactoryAspect() {
	
}

lbErrCodes LB_STDCALL lbUIElementFactoryAspect::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbUIElementFactoryAspect::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}


void LB_STDCALL lbUIElementFactoryAspect::visit(lb_I_Integer* i) {
	wxBoxSizer* sizerField = new wxBoxSizer(wxHORIZONTAL);
	wxTextCtrl *text = new wxTextCtrl(parentWindow, -1, i->charrep(), wxPoint(), wxDefaultSize);
	text->SetName(currentName->charrep());
	
	wxStaticText *label = new wxStaticText(parentWindow, -1, currentName->charrep(), wxPoint());
	label->SetName(currentLabel->charrep());
	
	sizerField->Add(label, 1, wxALL|wxADJUST_MINSIZE, 5);
	
	sizerField->Add(text, 1, wxALL, 5);
	
	sizerColumn->Add(sizerField, 0, wxEXPAND | wxALL, 5);
}

void LB_STDCALL lbUIElementFactoryAspect::visit(lb_I_Long*) {

}

void LB_STDCALL lbUIElementFactoryAspect::visit(lb_I_Boolean*) {

}

void LB_STDCALL lbUIElementFactoryAspect::visit(lb_I_String* s) {
	wxBoxSizer* sizerField = new wxBoxSizer(wxHORIZONTAL);
	wxTextCtrl *text = new wxTextCtrl(parentWindow, -1, s->charrep(), wxPoint(), wxDefaultSize);
	text->SetName(currentName->charrep());
	
	wxStaticText *label = new wxStaticText(parentWindow, -1, currentName->charrep(), wxPoint());
	label->SetName(currentLabel->charrep());
	
	sizerField->Add(label, 1, wxALL|wxADJUST_MINSIZE, 5);
	
	sizerField->Add(text, 1, wxALL, 5);
	
	sizerColumn->Add(sizerField, 0, wxEXPAND | wxALL, 5);
}

bool LB_STDCALL lbUIElementFactoryAspect::begin(lb_I_ControlFactory* factory, lb_I_Form* parent) {
	parentWindow = wxWindow::FindWindowById(parent->getId());
	return parentWindow != NULL;
}

void LB_STDCALL lbUIElementFactoryAspect::end() {
	parentWindow->SetAutoLayout(TRUE);
	parentWindow->SetSizer(sizerMain);
    sizerMain->SetSizeHints(parentWindow);
    sizerMain->Fit(parentWindow);
}

void LB_STDCALL lbUIElementFactoryAspect::setCurrentLabel(lb_I_String* label) {
	*currentLabel = label->charrep();
}

void LB_STDCALL lbUIElementFactoryAspect::setCurrentName(lb_I_String* name) {
	*currentName = name->charrep();
}








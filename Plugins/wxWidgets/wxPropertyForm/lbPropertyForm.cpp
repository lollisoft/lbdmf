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
 * $Id: lbPropertyForm.cpp,v 1.1.2.1 2015/07/12 10:05:50 lollisoft Exp $
 *
 * $Log: lbPropertyForm.cpp,v $
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


#include <lbPropertyForm.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPropertyPanel)
ADD_INTERFACE(lb_I_Window)
ADD_INTERFACE(lb_I_Form)
END_IMPLEMENT_LB_UNKNOWN()



IMPLEMENT_FUNCTOR(instanceOflbPropertyPanel, lbPropertyPanel)

/*...slbErrCodes LB_STDCALL lbPropertyPanel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPropertyPanel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPropertyPanel::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbPropertyPanel\58\\58\lbPropertyPanel\40\\41\:0:*/
lbPropertyPanel::lbPropertyPanel()
{
	_CL_LOG << "lbPropertyPanel::lbPropertyPanel() called." LOG_
	
	formName = strdup("Property view");
	untranslated_formName = NULL;
	base_formName = NULL;
	_created = false;
}
/*...e*/
/*...slbPropertyPanel\58\\58\\126\lbPropertyPanel\40\\41\:0:*/
lbPropertyPanel::~lbPropertyPanel() {
	_CL_LOG << "lbPropertyPanel::~lbPropertyPanel() called." LOG_
	
	free (formName);
	free (base_formName);
	free (untranslated_formName);
	_LOG << "lbPropertyPanel::~lbPropertyPanel() ready." LOG_
}
/*...e*/

lb_I_Unknown* LB_STDCALL lbPropertyPanel::getUnknown() {
	char eventName[100] = "";
	lb_I_Unknown* ukp;
	lb_I_EventHandler* evHandler = (lb_I_EventHandler*) this;
	
	sprintf(eventName, "%p , and this is %p.", evHandler, this);
	_LOG << "lbPropertyPanel::getUnknown() called. Instance of lb_I_EventHandler* is " << eventName LOG_
	
	queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
	return ukp;
}

void LB_STDCALL lbPropertyPanel::destroy() {
	if (_created) {
		_LOG << "lbPropertyPanel::destroy() Destroying '" << base_formName << "'" LOG_
		Destroy();
	}
	_created = false;
}

/*...svoid LB_STDCALL lbPropertyPanel\58\\58\create\40\int parentId\41\:0:*/
void LB_STDCALL lbPropertyPanel::create(int parentId) {
	wxWindow* w = FindWindowById(parentId);
	
	Create(w, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "panel");
	SetFocus();
	_created = true;
}
/*...e*/


void LB_STDCALL lbPropertyPanel::init() {
	
}

void LB_STDCALL lbPropertyPanel::init(lb_I_Parameter* parameter) {
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizerColumn  = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizerField = NULL;
	
	UAP(lb_I_Container, parameters)
	
	parameters = parameter->getParameterList();
	
	parameters->finishIteration();
	while (parameters->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_String, parameterName)
		
		uk = parameters->nextElement();
		key = parameters->currentKey();
		
		QI(key, lb_I_String, parameterName)
		
		
	}
}


lbErrCodes LB_STDCALL lbPropertyPanel::registerEventHandler(lb_I_Dispatcher* dispatcher) {
	
	return ERR_NONE;
}

void LB_STDCALL lbPropertyPanel::windowIsClosing(lb_I_Window* w) {

}

lbErrCodes LB_STDCALL lbPropertyPanel::setName(const char* name, const char* appention) {
	if (formName) free(formName);
	if (untranslated_formName) free(untranslated_formName);
	
	_LOG << "lbPropertyPanel::setName(" << name << ", " << ((appention) ? appention : "") << ") called." LOG_
	
	char* transl = _trans((const char*) name);
	
	char* temp = (char*) malloc(strlen(transl)+1);
	temp[0] = 0;
	strcpy(temp, transl);
	
	if (appention) {
		formName = (char*) malloc(1+strlen(temp)+strlen(appention));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name)+strlen(appention));
	} else {
		formName = (char*) malloc(1+strlen(temp));
		
		base_formName = (char*) malloc(1+strlen(name));
		untranslated_formName = (char*) malloc(1+strlen(name));
	}
	
	formName[0] = 0;
	strcat(formName, temp);
	if (appention) strcat(formName, appention);
	free(temp);
	
	untranslated_formName[0] = 0;
	strcat(untranslated_formName, name);
	if (appention) strcat(untranslated_formName, appention);
	
	base_formName[0] = 0;
	strcat(base_formName, name);
	
	return ERR_NONE;
}



//****************************************************



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPropertyDialog)
ADD_INTERFACE(lb_I_Window)
ADD_INTERFACE(lb_I_Form)
END_IMPLEMENT_LB_UNKNOWN()



IMPLEMENT_FUNCTOR(instanceOflbPropertyDialog, lbPropertyDialog)

/*...slbErrCodes LB_STDCALL lbPropertyDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPropertyDialog::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPropertyDialog::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbPropertyPanel\58\\58\lbPropertyPanel\40\\41\:0:*/
lbPropertyDialog::lbPropertyDialog()
: wxDialog(NULL, -1, wxString(_T("Property dialog")), wxDefaultPosition,
		   wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbPropertyDialog::lbPropertyDialog() called." LOG_
	
	panel = new lbPropertyPanel();
	_created = true;
}
/*...e*/
/*...slbPropertyPanel\58\\58\\126\lbPropertyPanel\40\\41\:0:*/
lbPropertyDialog::~lbPropertyDialog() {
	_CL_LOG << "lbPropertyDialog::~lbPropertyDialog() called." LOG_
	
	free (formName);
	free (base_formName);
	free (untranslated_formName);
	_LOG << "lbPropertyDialog::~lbPropertyDialog() ready." LOG_
}
/*...e*/

lb_I_Unknown* LB_STDCALL lbPropertyDialog::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}

void LB_STDCALL lbPropertyDialog::destroy() {
	if (_created) {
		_LOG << "lbPropertyDialog::destroy() Destroying '" << base_formName << "'" LOG_
		Destroy();
	}
	_created = false;
}

/*...svoid LB_STDCALL lbPropertyPanel\58\\58\create\40\int parentId\41\:0:*/
void LB_STDCALL lbPropertyDialog::create(int parentId) {
	_created = true;
}
/*...e*/


void LB_STDCALL lbPropertyDialog::init() {
	
}

void LB_STDCALL lbPropertyDialog::init(lb_I_Parameter* parameter) {
	char prefix[100] = "";
	sprintf(prefix, "%p", this);
	
	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);
	
	
	
	panel->create(this->GetId());
	
	sizerMain->Add(panel, 1, wxEXPAND | wxALL, 5);
	
	panel->init(parameter);
	
	SetName(panel->getFormName());
	
	SetAutoLayout(TRUE);
	
	SetSizer(sizerMain);
	
	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
}

lbErrCodes LB_STDCALL lbPropertyDialog::registerEventHandler(lb_I_Dispatcher* dispatcher) {
	
	return ERR_NONE;
}

void LB_STDCALL lbPropertyDialog::windowIsClosing(lb_I_Window* w) {
	
}

lbErrCodes LB_STDCALL lbPropertyDialog::setName(const char* name, const char* appention) {
	wxString Name = wxString(name)+wxString(appention);
	SetName(Name);
	SetLabel(Name);
	return panel->setName(name, appention);
}







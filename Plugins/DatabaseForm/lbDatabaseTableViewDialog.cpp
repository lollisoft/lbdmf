/*...sLicence:0:*/
/*...sLicence:0:*/
/*...sLicence:0:*/
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens@lollisoft.de)

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
    p-Mail: Lothar Behrens
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

/*...sincludes:0:*/
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

#include <lbConfigHook.h>
#include <lbInterfaces.h>



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

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

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

#include <lbDatabaseForm.h>

/*...sdoc:0:*/
/*
	This database dialog sample uses a fixed query yet.
	It is used as the only dialog from lb_wxGUI::createDBForm(char* formName).
	
	It should be changed in any way, if there are more different sample queries.
	Handling creation and usage of form elements directly in wxDialog failed
	anyhow.
	
	So I decided to use a derivation of it and put the handlers for the navigation
	into this class and use it only by this class.
	
	I am not sure, if it will work if I create more than one dialog. The peoblem
	may be my event handling mechanism.
	
	Here I use the following code to register my handlers:
	
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBFirst, "DatabaseFirst");
	
	It registers the event "DatabaseFirst" for this instance, because the this pointer is used inside
	my dispatching functionality.
	
	The identifer used here - "DatabaseFirst" - is a logical one. To be sure to get a free ID that
	also works inside wxWidgets, eman registers ID's above 5000 - I think.
	
	To get a different ID for the second 'different' dialog - showing other data, It would be the best
	idea to use the following unique things:
	
	process ID, thread ID optional, this pointer and the hostname.
	
	This leads into difficult code to build up the unique identifer, but macros would help.
	
	
	At least:
	
	It would be easy to implement the native wxWidgets event handling mechanism, but then I am not
	able to do a programmatical navigation from outside wxWidgets.
	
	This is only an idea - a remote control at application level.
*/
/*...e*/

/*...slbDatabaseTableViewDialog:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseTableViewDialog)
        ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseTableViewDialog, lbDatabaseTableViewDialog)


/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbDatabaseTableViewDialog::setData(...) not implemented yet" LOG_

#ifdef bla
		UAP(lb_I_DatabaseForm, dbForm)
		QI(uk, lb_I_DatabaseForm, dbForm)
		
		fa = ((lbDatabaseTableViewDialog*) dbForm.getPtr())->fa;
		((lbDatabaseTableViewDialog*) dbForm.getPtr())->fa = NULL;
	
#endif
		
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseTableViewDialog\58\\58\lbDatabaseTableViewDialog\40\\41\:0:*/
lbDatabaseTableViewDialog::lbDatabaseTableViewDialog() 
	: wxDialog(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbDatabaseTableViewDialog::lbDatabaseTableViewDialog() called." LOG_
	ref = STARTREF;
	panel = new lbDatabaseTableViewPanel();
	_created = true;
}
/*...e*/
/*...slbDatabaseTableViewDialog\58\\58\\126\lbDatabaseTableViewDialog\40\\41\:0:*/
lbDatabaseTableViewDialog::~lbDatabaseTableViewDialog() {
	_CL_LOG << "lbDatabaseTableViewDialog::~lbDatabaseTableViewDialog() called." LOG_
}
/*...e*/

void LB_STDCALL lbDatabaseTableViewDialog::create(int parentId) {
	// Don't need a parent
	_created = true;
}

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";
	
	sprintf(eventName, "%pDatabaseFirst", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBFirst, eventName);

	sprintf(eventName, "%pDatabaseNext", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBNext,  eventName);

	sprintf(eventName, "%pDatabasePrev", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBPrev,  eventName);

	sprintf(eventName, "%pDatabaseLast", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBLast,  eventName);
	
	sprintf(eventName, "%pDatabaseAdd", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBAdd,  eventName);
	
	sprintf(eventName, "%pDatabaseDelete", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseTableViewDialog::lbDBDelete,  eventName);
	
	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::init(char* _SQLString, char* DBName, char* DBUser, char* DBPass) {
	char prefix[100] = "";
	sprintf(prefix, "%p", this);

	wxBoxSizer* sizerMain  = new wxBoxSizer(wxVERTICAL);

	panel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

	panel->create(this->GetId());

	sizerMain->Add(panel, 1, wxEXPAND | wxALL, 5);

	panel->init(_SQLString, DBName, DBUser, DBPass);

	SetName(panel->getFormName());

	SetAutoLayout(TRUE);
		
	SetSizer(sizerMain);

	sizerMain->SetSizeHints(this);
	sizerMain->Fit(this);
	
	//Centre();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::setName(char const * name, char const * appention) {
	wxString Name = wxString(name)+wxString(appention);
	SetName(Name);
	return panel->setName(name, appention);
}
/*...e*/

char*      LB_STDCALL lbDatabaseTableViewDialog::getFormName() {
	return panel->getFormName();
}

/*...schar\42\ LB_STDCALL lbDatabaseTableViewDialog\58\\58\getQuery\40\\41\:0:*/
char* LB_STDCALL lbDatabaseTableViewDialog::getQuery() {
	return panel->getQuery();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseTableViewDialog\58\\58\getColumnName\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseTableViewDialog::getColumnName(int pos) {
	return panel->getColumnName(pos);
}
/*...e*/

void LB_STDCALL lbDatabaseTableViewDialog::windowIsClosing(lb_I_Window* w) {
	panel->windowIsClosing(w);
}

/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\setMasterForm\40\lb_I_DatabaseMasterForm\42\ master\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params) {
	panel->setMasterForm(master, params);
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\setDetailForm\40\lb_I_DatabaseMasterForm\42\ detail\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::setDetailForm(lb_I_DatabaseForm* detail, lb_I_Parameter* params) {
	panel->setDetailForm(detail, params);
}
/*...e*/

/*...sint LB_STDCALL lbDatabaseTableViewDialog\58\\58\getControls\40\\41\:0:*/
int LB_STDCALL lbDatabaseTableViewDialog::getControls() {
	return panel->getControls();
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseTableViewDialog\58\\58\getControlValue\40\int pos\41\:0:*/
const char* LB_STDCALL lbDatabaseTableViewDialog::getControlValue(int pos) {
	UAP(lb_I_String, c)
	c = panel->getColumnName(pos);
	return panel->getControlValue(c->charrep());
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseTableViewDialog\58\\58\getControlValue\40\char\42\ name\41\:0:*/
const char* LB_STDCALL lbDatabaseTableViewDialog::getControlValue(char* name) {

	wxString value;

	value = panel->getControlValue(name);
	
	return value.c_str();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\ignoreForeignKeys\40\char\42\ toTable\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::ignoreForeignKeys(char* toTable) {
	panel->ignoreForeignKeys(toTable);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::updateFromMaster() {
	panel->updateFromMaster();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\updateFromDetail\40\\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::updateFromDetail() {
	panel->updateFromDetail();
}
/*...e*/

void  LB_STDCALL lbDatabaseTableViewDialog::reopen() {
	panel->reopen();
}

lbErrCodes  LB_STDCALL lbDatabaseTableViewDialog::close() {
	return panel->close();
}

lbErrCodes  LB_STDCALL lbDatabaseTableViewDialog::open() {
	return panel->open();
}

/*...svoid LB_STDCALL lbDatabaseTableViewDialog\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabaseTableViewDialog::setFilter(char* filter) {
	panel->setFilter(filter);
}
/*...e*/

/*...schar\42\ lbDatabaseTableViewDialog\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
lb_I_String* lbDatabaseTableViewDialog::getTableName(char* columnName) {
	return panel->getTableName(columnName);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBClear() {
	return panel->lbDBClear();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBUpdate() {
	return panel->lbDBUpdate();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBRead() {
	return panel->lbDBRead();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBFirst(lb_I_Unknown* uk) {
	return panel->lbDBFirst(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBNext(lb_I_Unknown* uk) {
	return panel->lbDBNext(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBPrev(lb_I_Unknown* uk) {
	return panel->lbDBPrev(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBLast(lb_I_Unknown* uk) {
	return panel->lbDBLast(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBAdd(lb_I_Unknown* uk) {
	return panel->lbDBAdd(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::lbDBDelete(lb_I_Unknown* uk) {
	return panel->lbDBDelete(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseTableViewDialog\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseTableViewDialog::OnActionButton(lb_I_Unknown* uk) {
	return panel->OnActionButton(uk);
}
/*...e*/

/*...svoid \9\\9\  lbDatabaseTableViewDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseTableViewDialog::OnDispatch(wxCommandEvent& event ) {
	// Dispatcher should be called inside panel
}
/*...e*/
/*...svoid\9\\9\  lbDatabaseTableViewDialog\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseTableViewDialog::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/

/*...sint LB_STDCALL lbDatabaseTableViewDialog\58\\58\getPrimaryColumns\40\\41\:0:*/
int LB_STDCALL lbDatabaseTableViewDialog::getPrimaryColumns()
{
	return panel->getPrimaryColumns();
}
/*...e*/
/*...sint LB_STDCALL lbDatabaseTableViewDialog\58\\58\getForeignColumns\40\char\42\ primaryTable\41\:0:*/
int LB_STDCALL lbDatabaseTableViewDialog::getForeignColumns(char* primaryTable)
{
	return panel->getForeignColumns(primaryTable);
}
/*...e*/
	
lb_I_String* LB_STDCALL lbDatabaseTableViewDialog::getPrimaryColumn(int pos)
{
	return panel->getPrimaryColumn(pos);
}

lb_I_String* LB_STDCALL lbDatabaseTableViewDialog::getForeignColumn(int pos)
{
	return panel->getForeignColumn(pos);
}
	   
bool LB_STDCALL lbDatabaseTableViewDialog::isCharacterColumn(char* name)
{
	return panel->isCharacterColumn(name);
}
/*...e*/

/*...sclass lbPluginDatabaseTableViewDialog implementation:0:*/
/*...slbPluginDatabaseTableViewDialog:0:*/
class lbPluginDatabaseTableViewDialog : public lb_I_PluginImpl {
public:
	lbPluginDatabaseTableViewDialog();
	
	virtual ~lbPluginDatabaseTableViewDialog();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, dbForm)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseTableViewDialog)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseTableViewDialog, lbPluginDatabaseTableViewDialog)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseTableViewDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseTableViewDialog::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl)
	QI(uk, lb_I_PluginImpl, pl)

	dbForm = pl->getImplementation();
*/

	_CL_VERBOSE << "lbPluginDatabaseTableViewDialog::setData(...) called.\n" LOG_

	if (dbForm == NULL) {
		_CL_VERBOSE << "ERROR: Cloning database form plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseTableViewDialog::lbPluginDatabaseTableViewDialog() {
	_CL_VERBOSE << "lbPluginDatabaseTableViewDialog::lbPluginDatabaseTableViewDialog() called.\n" LOG_
	dbForm = NULL;
	ref = STARTREF;
}

lbPluginDatabaseTableViewDialog::~lbPluginDatabaseTableViewDialog() {
	_CL_VERBOSE << "lbPluginDatabaseTableViewDialog::~lbPluginDatabaseTableViewDialog() called.\n" LOG_

	if (dbForm != NULL) {
		_CL_LOG << "dbForm is not NULL." LOG_
		_CL_LOG << "*******************" LOG_
	}
}

void LB_STDCALL lbPluginDatabaseTableViewDialog::initialize() {
}

bool LB_STDCALL lbPluginDatabaseTableViewDialog::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabaseTableViewDialog::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

bool LB_STDCALL lbPluginDatabaseTableViewDialog::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseTableViewDialog\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseTableViewDialog::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {
		lbDatabaseTableViewDialog* dbDialog = new lbDatabaseTableViewDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbDialog, lb_I_Unknown, dbForm)
	} else {
		_CL_VERBOSE << "lbPluginDatabaseTableViewDialog::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return dbForm.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseTableViewDialog\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseTableViewDialog::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDatabaseTableViewDialog* dbDialog = new lbDatabaseTableViewDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(dbDialog, lb_I_Unknown, dbForm)
	}
	
	lb_I_Unknown* r = dbForm.getPtr();
	dbForm.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseTableViewDialog::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (dbForm != NULL) {
		UAP(lb_I_DatabaseForm, form)
		QI(dbForm, lb_I_DatabaseForm, form)
	
		form->destroy();
		
		dbForm.resetPtr();
	}
}
/*...e*/
/*...e*/

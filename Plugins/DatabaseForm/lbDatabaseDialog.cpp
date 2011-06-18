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
            Ginsterweg 4

            65760 Eschborn (germany)
*/
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

	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBFirst, "DatabaseFirst");

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

/*...slbDatabaseDialog:0:*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseDialog)
        ADD_INTERFACE(lb_I_DatabaseForm)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseDialog, lbDatabaseDialog)


/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setData(lb_I_Unknown* uk) {
		lbErrCodes err = ERR_NONE;

        _CL_LOG << "lbDatabaseDialog::setData(...) not implemented yet" LOG_

#ifdef bla
		UAP(lb_I_DatabaseForm, dbForm)
		QI(uk, lb_I_DatabaseForm, dbForm)

		fa = ((lbDatabaseDialog*) dbForm.getPtr())->fa;
		((lbDatabaseDialog*) dbForm.getPtr())->fa = NULL;

#endif

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseDialog\58\\58\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::lbDatabaseDialog()
	: wxDialog(NULL, -1, wxString(_T("Database dialog")), wxDefaultPosition,
	wxDefaultSize, wxRESIZE_BORDER|wxDEFAULT_DIALOG_STYLE)
{
	_CL_LOG << "lbDatabaseDialog::lbDatabaseDialog() called." LOG_
	ref = STARTREF;
	panel = new lbDatabasePanel();
	_created = true;
}
/*...e*/
/*...slbDatabaseDialog\58\\58\\126\lbDatabaseDialog\40\\41\:0:*/
lbDatabaseDialog::~lbDatabaseDialog() {
	_CL_LOG << "lbDatabaseDialog::~lbDatabaseDialog() called." LOG_
}
/*...e*/

void LB_STDCALL lbDatabaseDialog::create(int parentId) {
	// Don't need a parent
	_created = true;
}

lb_I_Unknown* LB_STDCALL lbDatabaseDialog::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\registerEventHandler\40\lb_I_Dispatcher\42\ dispatcher\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::registerEventHandler(lb_I_Dispatcher* dispatcher) {

	char eventName[100] = "";

	sprintf(eventName, "%pDatabaseFirst", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBFirst, eventName);

	sprintf(eventName, "%pDatabaseNext", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBNext,  eventName);

	sprintf(eventName, "%pDatabasePrev", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBPrev,  eventName);

	sprintf(eventName, "%pDatabaseLast", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBLast,  eventName);

	sprintf(eventName, "%pDatabaseAdd", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBAdd,  eventName);

	sprintf(eventName, "%pDatabaseDelete", this);
	dispatcher->addEventHandlerFn(this, (lbEvHandler) &lbDatabaseDialog::lbDBDelete,  eventName);

	return ERR_NONE;
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\init\40\char\42\ SQLString\44\ char\42\ DBName\44\ char\42\ DBUser\44\ char\42\ DBPass\41\:0:*/
void LB_STDCALL lbDatabaseDialog::init(const char* _SQLString, const char* DBName, const char* DBUser, const char* DBPass) {
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

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\setName\40\char const \42\ name\44\ char const \42\ appention\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::setName(char const * name, char const * appention) {
	wxString Name = wxString(name)+wxString(appention);
	SetName(Name);
	SetLabel(Name);
	return panel->setName(name, appention);
}
/*...e*/

char*      LB_STDCALL lbDatabaseDialog::getFormName() {
	return panel->getFormName();
}

char*      LB_STDCALL lbDatabaseDialog::getName() {
	return panel->getName();
}

/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getQuery\40\\41\:0:*/
char* LB_STDCALL lbDatabaseDialog::getQuery() {
	return panel->getQuery();
}
/*...e*/
/*...schar\42\ LB_STDCALL lbDatabaseDialog\58\\58\getColumnName\40\int pos\41\:0:*/
lb_I_String* LB_STDCALL lbDatabaseDialog::getColumnName(int pos) {
	return panel->getColumnName(pos);
}
/*...e*/

void LB_STDCALL lbDatabaseDialog::windowIsClosing(lb_I_Window* w) {
	panel->windowIsClosing(w);
}

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setMasterForm\40\lb_I_DatabaseMasterForm\42\ master\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setMasterForm(lb_I_DatabaseForm* master, lb_I_Parameter* params) {
	panel->setMasterForm(master, params);
}
/*...e*/
/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setDetailForm\40\lb_I_DatabaseMasterForm\42\ detail\44\ lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setDetailForm(lb_I_DatabaseForm* detail, lb_I_Parameter* params) {
	panel->setDetailForm(detail, params);
}
/*...e*/

/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getControls\40\\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getControls() {
	return panel->getControls();
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseDialog\58\\58\getControlValue\40\int pos\41\:0:*/
const char* LB_STDCALL lbDatabaseDialog::getControlValue(int pos) {
	UAP(lb_I_String, c)
	c = panel->getColumnName(pos);
	return panel->getControlValue(c->charrep());
}
/*...e*/
/*...sconst char\42\ LB_STDCALL lbDatabaseDialog\58\\58\getControlValue\40\char\42\ name\41\:0:*/
const char* LB_STDCALL lbDatabaseDialog::getControlValue(const char* name) {

	wxString value;

	value = panel->getControlValue(name);

	return value.c_str();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\ignoreForeignKeys\40\char\42\ toTable\41\:0:*/
void LB_STDCALL lbDatabaseDialog::ignoreForeignKeys(const char* toTable) {
	panel->ignoreForeignKeys(toTable);
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\updateFromMaster\40\\41\:0:*/
void LB_STDCALL lbDatabaseDialog::updateFromMaster() {
	panel->updateFromMaster();
}
/*...e*/

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\updateFromDetail\40\\41\:0:*/
void LB_STDCALL lbDatabaseDialog::updateFromDetail() {
	panel->updateFromDetail();
}
/*...e*/

void  LB_STDCALL lbDatabaseDialog::reopen() {
	panel->reopen();
}

lbErrCodes  LB_STDCALL lbDatabaseDialog::close() {
	return panel->close();
}

lbErrCodes  LB_STDCALL lbDatabaseDialog::open() {
	return panel->open();
}

/*...svoid LB_STDCALL lbDatabaseDialog\58\\58\setFilter\40\char\42\ filter\41\:0:*/
void LB_STDCALL lbDatabaseDialog::setFilter(const char* filter) {
	panel->setFilter(filter);
}
/*...e*/

/*...schar\42\ lbDatabaseDialog\58\\58\getTableName\40\char\42\ columnName\41\:0:*/
lb_I_String* lbDatabaseDialog::getTableName(const char* columnName) {
	return panel->getTableName(columnName);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBClear\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBClear() {
	return panel->lbDBClear();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBUpdate\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBUpdate() {
	return panel->lbDBUpdate();
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBRead\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBRead() {
	return panel->lbDBRead();
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBFirst\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBFirst(lb_I_Unknown* uk) {
	return panel->lbDBFirst(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBNext\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBNext(lb_I_Unknown* uk) {
	return panel->lbDBNext(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBPrev\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBPrev(lb_I_Unknown* uk) {
	return panel->lbDBPrev(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBLast\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBLast(lb_I_Unknown* uk) {
	return panel->lbDBLast(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBAdd\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBAdd(lb_I_Unknown* uk) {
	return panel->lbDBAdd(uk);
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\lbDBDelete\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::lbDBDelete(lb_I_Unknown* uk) {
	return panel->lbDBDelete(uk);
}
/*...e*/

/*...slbErrCodes LB_STDCALL lbDatabaseDialog\58\\58\OnActionButton\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseDialog::OnActionButton(lb_I_Unknown* uk) {
	return panel->OnActionButton(uk);
}
/*...e*/

/*...svoid \9\\9\  lbDatabaseDialog\58\\58\OnDispatch\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnDispatch(wxCommandEvent& event ) {
	// Dispatcher should be called inside panel
}
/*...e*/
/*...svoid\9\\9\  lbDatabaseDialog\58\\58\OnPaint\40\wxCommandEvent\38\ event \41\:0:*/
void lbDatabaseDialog::OnPaint(wxCommandEvent& event ) {

	// Paint an object at the given control






}
/*...e*/

/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getPrimaryColumns\40\\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getPrimaryColumns()
{
	return panel->getPrimaryColumns();
}
/*...e*/
/*...sint LB_STDCALL lbDatabaseDialog\58\\58\getForeignColumns\40\char\42\ primaryTable\41\:0:*/
int LB_STDCALL lbDatabaseDialog::getForeignColumns(const char* primaryTable)
{
	return panel->getForeignColumns(primaryTable);
}
/*...e*/

lb_I_String* LB_STDCALL lbDatabaseDialog::getPrimaryColumn(int pos)
{
	return panel->getPrimaryColumn(pos);
}

lb_I_String* LB_STDCALL lbDatabaseDialog::getForeignColumn(int pos)
{
	return panel->getForeignColumn(pos);
}

bool LB_STDCALL lbDatabaseDialog::isCharacterColumn(const char* name)
{
	return panel->isCharacterColumn(name);
}
/*...e*/

/*...sclass lbPluginDatabaseDialog implementation:0:*/
/*...slbPluginDatabaseDialog:0:*/
class lbPluginDatabaseDialog : public lb_I_PluginImpl {
public:
	lbPluginDatabaseDialog();

	virtual ~lbPluginDatabaseDialog();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseDialog)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseDialog, lbPluginDatabaseDialog)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseDialog\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseDialog::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
/*
	UAP(lb_I_PluginImpl, pl)
	QI(uk, lb_I_PluginImpl, pl)

	dbForm = pl->getImplementation();
*/

	_CL_VERBOSE << "lbPluginDatabaseDialog::setData(...) called.\n" LOG_

	if (dbForm == NULL) {
		_CL_VERBOSE << "ERROR: Cloning database form plugin without an instance to the form it self" LOG_
	}

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseDialog::lbPluginDatabaseDialog() {
	_CL_VERBOSE << "lbPluginDatabaseDialog::lbPluginDatabaseDialog() called.\n" LOG_
	dbForm = NULL;
	ref = STARTREF;
}

lbPluginDatabaseDialog::~lbPluginDatabaseDialog() {
	_CL_VERBOSE << "lbPluginDatabaseDialog::~lbPluginDatabaseDialog() called.\n" LOG_

	if (dbForm != NULL) {
		_CL_LOG << "dbForm is not NULL." LOG_
		_CL_LOG << "*******************" LOG_
	}
}

void LB_STDCALL lbPluginDatabaseDialog::initialize() {
}

bool LB_STDCALL lbPluginDatabaseDialog::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabaseDialog::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

bool LB_STDCALL lbPluginDatabaseDialog::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseDialog\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseDialog::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {
		lbDatabaseDialog* dbDialog = new lbDatabaseDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

		QI(dbDialog, lb_I_Unknown, dbForm)
	} else {
		_CL_VERBOSE << "lbPluginDatabaseDialog::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return dbForm.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseDialog\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseDialog::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (dbForm == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbDatabaseDialog* dbDialog = new lbDatabaseDialog();
		dbDialog->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

		QI(dbDialog, lb_I_Unknown, dbForm)
	}

	lb_I_Unknown* r = dbForm.getPtr();
	dbForm.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseDialog::releaseImplementation() {
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

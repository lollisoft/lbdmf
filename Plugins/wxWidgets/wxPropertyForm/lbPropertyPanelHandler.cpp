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
 * $Revision: 1.1.2.3 $
 * $Name:  $
 * $Id: lbPropertyPanelHandler.cpp,v 1.1.2.3 2015/08/27 14:15:20 lollisoft Exp $
 *
 * $Log: lbPropertyPanelHandler.cpp,v $
 * Revision 1.1.2.3  2015/08/27 14:15:20  lollisoft
 * First basic implementation of a property dialog using a visitor factory.
 *
 * Revision 1.1.2.2  2015/07/12 12:13:54  lollisoft
 * Added new plugin into deployment and code to instantiate the dialog.
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


#include <lbPropertyPanelHandler.h>
#include <lbPropertyForm.h>

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPropertyPanelHandler)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbPropertyPanelHandler::lbPropertyPanelHandler() {
	
}

lbPropertyPanelHandler::~lbPropertyPanelHandler() {
	
}

lb_I_Unknown* lbPropertyPanelHandler::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbPropertyPanelHandler::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbPropertyPanelHandler::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbPropertyPanelHandler::registerEventHandler(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)
	int temp;
	eman->registerEvent("showPropertyDialog", temp);
	eman->registerEvent("showPropertyPanel", temp);
	eman->registerEvent("testPropertyDialog", temp);
	
	disp->addEventHandlerFn(this, (lbEvHandler) &lbPropertyPanelHandler::showPropertyDialog, "showPropertyDialog");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbPropertyPanelHandler::showPropertyPanel, "showPropertyPanel");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbPropertyPanelHandler::testPropertyDialog, "testPropertyDialog");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbPropertyPanelHandler::showPropertyDialog(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for activity
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name

	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";
	
	UAP(lb_I_Parameter, params)
	
	if (uk == NULL) {
		_LOG << "lbPropertyPanelHandler::showPropertyDialog() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbPropertyPanelHandler::showPropertyDialog() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	lbPropertyDialog* pDialog = new lbPropertyDialog();
	
	pDialog->init(*&params);
	
	pDialog->show();

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbPropertyPanelHandler::showPropertyPanel(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, result) // Result for activity
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName) // Parameter name
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramResult) // Parameter name
	
	// Default is failure
	*paramName = "result";
	*paramResult = "result";
	*result = "0";
	
	UAP(lb_I_Parameter, params)
	
	if (uk == NULL) {
		_LOG << "lbPropertyPanelHandler::showPropertyDialog() Did not got an object." LOG_
		params->setUAPString(*&paramName, *&result);
		return ERR_PARAMETER_MISSING;
	}
	
	QI(uk, lb_I_Parameter, params)
	
	if (params == NULL) {
		_LOG << "lbPropertyPanelHandler::showPropertyDialog() Parameter is not of type lb_I_Parameter." LOG_
		params->setUAPString(*&paramResult, *&result);
		return ERR_ILLEGAL_PARAMETER;
	}
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbPropertyPanelHandler::testPropertyDialog(lb_I_Unknown* uk) {
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pString1)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pString2)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pString3)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, pInt1)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, pInt2)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, pInt3)
	
	*pString1 = "Test 1";
	*pString2 = "Test 2";
	*pString3 = "Test 3";
	pInt1->setData(25);
	pInt2->setData(26);
	pInt3->setData(27);
	
	*paramName = "Test Text 1";
	params->setUAPString(*&paramName, *&pString1);
	*paramName = "Test Text 2";
	params->setUAPString(*&paramName, *&pString2);
	*paramName = "Test Text 3";
	params->setUAPString(*&paramName, *&pString3);
	*paramName = "Test Integer 1";
	params->setUAPInteger(*&paramName, *&pInt1);
	*paramName = "Test Integer 2";
	params->setUAPInteger(*&paramName, *&pInt2);
	*paramName = "Test Integer 3";
	params->setUAPInteger(*&paramName, *&pInt3);
	
	
	showPropertyDialog(ukparams.getPtr());
}


class lbPluginPropertyPanelHandler : public lb_I_PluginImpl {
public:
	lbPluginPropertyPanelHandler();
	
	virtual ~lbPluginPropertyPanelHandler();
	
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
	
	UAP(lb_I_Unknown, ukPropertyPanelHandler)
};



BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginPropertyPanelHandler)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginPropertyPanelHandler, lbPluginPropertyPanelHandler)

/*...slbErrCodes LB_STDCALL lbPluginPropertyPanelHandler\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginPropertyPanelHandler::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginPropertyPanelHandler::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginPropertyPanelHandler::lbPluginPropertyPanelHandler() {
	_CL_VERBOSE << "lbPluginPropertyPanelHandler::lbPluginPropertyPanelHandler() called.\n" LOG_
	
}

lbPluginPropertyPanelHandler::~lbPluginPropertyPanelHandler() {
	_CL_VERBOSE << "lbPluginPropertyPanelHandler::~lbPluginPropertyPanelHandler() called.\n" LOG_
}

bool LB_STDCALL lbPluginPropertyPanelHandler::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginPropertyPanelHandler::autorun() {
	lbErrCodes err = ERR_NONE;
	
	lbPropertyPanelHandler* PropertyPanelHandler = new lbPropertyPanelHandler();
	
	QI(PropertyPanelHandler, lb_I_Unknown, ukPropertyPanelHandler) 
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	PropertyPanelHandler->registerEventHandler(*&dispatcher);
	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	
	char* file = strdup(_trans("&File"));
	char* entry = strdup(_trans("Test Property dialog"));
	
	meta->addMenuEntry(file, entry, "testPropertyDialog", "");
	
	free(file);
	free(entry);
	
	
	return err;
}

void LB_STDCALL lbPluginPropertyPanelHandler::initialize() {
}

bool LB_STDCALL lbPluginPropertyPanelHandler::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginPropertyPanelHandler\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginPropertyPanelHandler::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukPropertyPanelHandler == NULL) {
		lbPropertyPanelHandler* PropertyPanelHandler = new lbPropertyPanelHandler();
		
		QI(PropertyPanelHandler, lb_I_Unknown, ukPropertyPanelHandler)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukPropertyPanelHandler.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginPropertyPanelHandler\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginPropertyPanelHandler::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukPropertyPanelHandler == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
		
		lbPropertyPanelHandler* PropertyPanelHandler = new lbPropertyPanelHandler();
		
		
		QI(PropertyPanelHandler, lb_I_Unknown, ukPropertyPanelHandler)
	}
	
	lb_I_Unknown* r = ukPropertyPanelHandler.getPtr();
	ukPropertyPanelHandler.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginPropertyPanelHandler::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (ukPropertyPanelHandler != NULL) {
		ukPropertyPanelHandler--;
		ukPropertyPanelHandler.resetPtr();
	}
}
/*...e*/
/*...e*/


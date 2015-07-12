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
 * $Id: lbControlFactory.cpp,v 1.1.2.1 2015/07/12 10:05:50 lollisoft Exp $
 *
 * $Log: lbControlFactory.cpp,v $
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


class lbControlFactory : 
public lb_I_ControlFactory {
public:
	
	lbControlFactory();
	virtual ~lbControlFactory();
	
	lb_I_Unknown* LB_STDCALL getUnknown();
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* dispatcher);
	
	void			LB_STDCALL setParent(lb_I_Window* parent);
	lb_I_Window*	LB_STDCALL createControl(const char* typeName, const char* name, const char* title);

	DECLARE_LB_UNKNOWN()
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbControlFactory)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbControlFactory::lbControlFactory() {
	
}

lbControlFactory::~lbControlFactory() {
	
}

lb_I_Unknown* lbControlFactory::getUnknown() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	
	QI(this, lb_I_Unknown, uk)
	
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbControlFactory::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_LOG << "lbControlFactory::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbErrCodes LB_STDCALL lbControlFactory::registerEventHandler(lb_I_Dispatcher* disp) {
/*
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, eman)

	int temp;
	eman->registerEvent("showPropertyDialog", temp);
	eman->registerEvent("showPropertyPanel", temp);
	
	disp->addEventHandlerFn(this, (lbEvHandler) &lbControlFactory::showPropertyDialog, "showPropertyDialog");
	disp->addEventHandlerFn(this, (lbEvHandler) &lbControlFactory::showPropertyPanel, "showPropertyPanel");
 */
	return ERR_NONE;
}

void			LB_STDCALL lbControlFactory::setParent(lb_I_Window* parent) {
	
}

lb_I_Window*	LB_STDCALL lbControlFactory::createControl(const char* typeName, const char* name, const char* title) {
	return NULL;
}


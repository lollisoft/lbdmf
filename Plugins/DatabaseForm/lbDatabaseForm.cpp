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



BEGIN_EVENT_TABLE(lbOwnerDrawControl, wxControl)
    EVT_PAINT  (lbOwnerDrawControl::OnPaint)
END_EVENT_TABLE()


BEGIN_IMPLEMENT_LB_UNKNOWN(lbOwnerDrawControl)
        ADD_INTERFACE(lb_I_Control)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbOwnerDrawControl, lbOwnerDrawControl)

lbOwnerDrawControl::lbOwnerDrawControl() : wxControl() {
	ref = STARTREF;
}

lbOwnerDrawControl::~lbOwnerDrawControl() {

}

lbErrCodes LB_STDCALL lbOwnerDrawControl::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbOwnerDrawControl::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbOwnerDrawControl::windowIsClosing(lb_I_Window* w) {
}

void LB_STDCALL lbOwnerDrawControl::init(lb_I_Window* parent) {

	// Not sure, if it is a panel based dialog or a dialog.

	lbDatabasePanel* p = (lbDatabasePanel*) parent;
	Create(p, -1, wxPoint(), wxSize(40,40));
}

void lbOwnerDrawControl::OnPaint(wxPaintEvent &WXUNUSED(event)) {
	wxPaintDC dc(this);
	PrepareDC(dc);

        dc.SetPen(*wxMEDIUM_GREY_PEN);
        for ( int i = 1; i <= 4; i++ )
 	       dc.DrawLine(0, i*10, i*10, 0);
}
/*...e*/

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);

                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:
                	_CL_LOG << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation)
                        {
                                _CL_VERBOSE << "DLL released by system." LOG_
                        }
                        else
                        {
                                _CL_VERBOSE << "DLL released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }

        return TRUE;
}
/*...e*/
#endif

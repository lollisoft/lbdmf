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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
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
#include <malloc.h>
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
/*...e*/

#ifndef OSX
#ifdef LINUX
#include <repwrt.h>
#endif
#ifdef WINDOWS
#include <wx/repwrt.h>
#endif
#endif

#include <lbDatabaseReport.h>

/*...sclass lbPluginModuleDatabaseReport:0:*/
class lbPluginModuleDatabaseReport : public lb_I_PluginModule {
public:

	lbPluginModuleDatabaseReport();
	virtual ~lbPluginModuleDatabaseReport();

	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleDatabaseReport implementation:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lbPluginModuleDatabaseReport)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfPluginModule, lbPluginModuleDatabaseReport)

BEGIN_PLUGINS(lbPluginModuleDatabaseReport)
	ADD_PLUGIN(lbPluginDatabaseReport, GUI)
END_PLUGINS()

//	ADD_PLUGIN(lbOwnerDrawControl, GUI)

lbPluginModuleDatabaseReport::lbPluginModuleDatabaseReport() {
	ref = STARTREF;
}

lbPluginModuleDatabaseReport::~lbPluginModuleDatabaseReport() {
	_CL_VERBOSE << "lbPluginModuleDatabaseReport::~lbPluginModuleDatabaseReport() called." LOG_
}

void LB_STDCALL lbPluginModuleDatabaseReport::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbPluginModuleDatabaseReport::setData(lb_I_Unknown* uk) {
        _LOG << "lbPluginModuleDatabaseReport::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

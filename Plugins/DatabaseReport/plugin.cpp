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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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

#include <repwrt.h>

#include <lbDatabaseReport.h>

/*...sclass lbPluginModuleDatabaseReport:0:*/
class lbPluginModuleDatabaseReport : public lb_I_PluginModule {
public:

	lbPluginModuleDatabaseReport();
	virtual ~lbPluginModuleDatabaseReport();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModuleDatabaseReport implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleDatabaseReport)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleDatabaseReport)

BEGIN_PLUGINS(lbPluginModuleDatabaseReport)
	ADD_PLUGIN(lbPluginDatabaseReport, GUI)
END_PLUGINS()

//	ADD_PLUGIN(lbOwnerDrawControl, GUI)

lbPluginModuleDatabaseReport::lbPluginModuleDatabaseReport() {
	_CL_VERBOSE << "lbPluginModuleDatabaseReport::lbPluginModuleDatabaseReport() called." LOG_
	ref = STARTREF;
}

lbPluginModuleDatabaseReport::~lbPluginModuleDatabaseReport() {
	_CL_VERBOSE << "lbPluginModuleDatabaseReport::~lbPluginModuleDatabaseReport() called." LOG_
}

void LB_STDCALL lbPluginModuleDatabaseReport::initialize() {
	enumPlugins();
}

void LB_STDCALL lbPluginModuleDatabaseReport::install() {

}

lbErrCodes LB_STDCALL lbPluginModuleDatabaseReport::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleDatabaseReport::setData(...) not implemented yet" LOG_
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

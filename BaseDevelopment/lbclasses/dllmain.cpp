/*...sLicence:0:*/
/*
	DMF Distributed Multiplatform Framework (the initial goal of this library)
	This file is part of lbDMF.
	Copyright (C) 2002-2009  Lothar Behrens (lothar.behrens@lollisoft.de)

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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
//#include <lbInterfaces.h>

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef LB_CLASSES_DLL
lb_I_Log *log;
int isInitializing;
#endif

#ifdef OSX

#include <stdio.h>

void _init ()
{
	printf("dlcompat: %s: _init()\n", __FILE__);
}

void _fini ()
{
	printf("dlcompat: %s: _fini()\n", __FILE__);
}

#endif


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		TRMemOpen();
		
		if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);
		
		TRMemSetModuleName(__FILE__);
		
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

#endif

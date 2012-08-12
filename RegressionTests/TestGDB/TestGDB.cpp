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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <conio.h>
	
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <iostream>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...e*/

void DoTest()
{
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		
	meta->msgBox("Test", "Message");	
}

// http://www.google.co.in/#hl=de&sclient=psy-ab&q=gcc+extract+dwarf+info&oq=gcc+extract+dwarf+info&gs_l=serp.3...4852.16604.0.16862.24.23.1.0.0.0.213.2453.15j7j1.23.0...0.0...1c.V9vmdrT3ctk&pbx=1&bav=on.2,or.r_gc.r_pw.r_qf.&fp=1391debd1f706dcc&biw=1920&bih=953
// http://eli.thegreenplace.net/2011/02/07/how-debuggers-work-part-3-debugging-information/
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	
	DoTest();
	
	unHookAll();
	
	return 0;
}

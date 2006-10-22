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
#ifdef _MSC_VER

#pragma warning( disable: 4101 )

#endif
/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {      
#endif            
#ifndef OSX
#include <conio.h>
#endif
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

#include <lbConfigHook.h>
/*...e*/

/*...sDocumentation:0:*/
/** \page Testing DMF plugin environment - Try to find and initialize plugins.
 *
 * \section Introduction
 *
 * This test is intended to show, how to use plugins. A first test is to find and
 * initialize the plugins.
 *
 * \code
int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	
	mm = getModuleInstance();

	_CL_LOG << "Plugin regression tests..." LOG_
	
	UAP_REQUEST(mm, lb_I_PluginManager, PM)

	PM->initialize();

	if (PM->beginEnumPlugins()) {
	
		while (true) {
		
			UAP(lb_I_Plugin, pl)
			
			pl = PM->nextPlugin();
			
			if (pl == NULL) break;

			pl->initialize();
		
		}
	}

	PM->unload();

	unHookAll();

        return 0;
}
 * \endcode
 *
 * \section Details
 *
 * The test also checks the handling of default values.
 *
 */
/*...e*/

lb_I_Unknown* findPluginByInterfaceAndNamespace(char* _interface, char* _namespace) {
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Plugin, pl)
		
	pl = PM->getFirstMatchingPlugin(_interface, _namespace);
	
	_CL_LOG << "References to plugin wrapper instance: " << pl->getRefCount() LOG_
		
	if (pl != NULL) {
       	        uk = pl->getImplementation();
       	        uk++;
	        	        
       	        return uk.getPtr();
       	}
       	return NULL;
}

int main(int argc, char *argv[]) {


	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	bool PMInitialized = false;
	{
	#ifdef WINDOWS
		TRMemOpen();
		TRMemSetModuleName(__FILE__);
	#endif
	
		mm = getModuleInstance();

		UAP(lb_I_Unknown, uk)
		uk = findPluginByInterfaceAndNamespace("lb_I_UserAccounts", "Model");

		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		
		PM->unload();
	}

	mm->release(__FILE__, __LINE__);

	unHookAll();

        return 0;
}

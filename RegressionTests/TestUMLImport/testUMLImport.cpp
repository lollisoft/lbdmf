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
#include <lbConfigHook.h>
/*...e*/

int main(int argc, char *argv[]) {
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	{
		_CL_LOG << "Test UML Import functionality" LOG_
		
		// Preload lbClasses DLL with this line !
		UAP_REQUEST(getModuleInstance(), lb_I_String, s)

		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		PM->initialize();
		
		meta->load();
		
		meta->initialize();
		
		// Need to issue some events to simulate user actions
		
		meta->login("user", "TestUser");
		
		UAP(lb_I_Container, applications)
		
		applications = meta->getApplications();
		
		meta->loadApplication("user", "lbDMF Manager");

		// Setup the configuration that is needed for this test
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl");
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", "../../../AppDevelopment/DynamicApp/ModelExchange/PostbooksUML2.xmi");
		// Simulate menu click
		meta->fireEvent("importUMLXMIDocIntoApplication");

		meta->unloadApplication();

		meta->uninitialize();
		
		PM->unload();
	}
	
	unHookAll();
	
	return 0;
}

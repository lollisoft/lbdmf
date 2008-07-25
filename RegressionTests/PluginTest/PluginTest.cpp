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

{
	lbErrCodes err = ERR_NONE;
	lb_I_Module* mm = NULL;
	bool PMInitialized = false;

#ifdef WINDOWS
	TRMemOpen();
	TRMemSetModuleName(__FILE__);
#endif
	
	mm = getModuleInstance();

	_CL_LOG << "Plugin regression tests..." LOG_

	char answer[100];
	
	COUT << "Do you want to list plugins with plugin manager (y/n) ? ";
	CIN >> answer;

	UAP_REQUEST(mm, lb_I_String, pre)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

/*...sTest list plugins:8:*/
	if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
		UAP_REQUEST(mm, lb_I_PluginManager, PM)
	
		if (PM->beginEnumPlugins()) {
	
			while (true) {
				UAP(lb_I_Plugin, pl)
				pl = PM->nextPlugin();
			
				if (pl == NULL) break;
	
				pl->initialize();
				
				_CL_LOG << "Plugin name: " << pl->getName() LOG_
			}
		}
		
		_CL_LOG << "* Unload plugin manager *" LOG_
		
		PM->unload();
		
		_CL_LOG << "*        Unloaded       *" LOG_
	}
/*...e*/

	COUT << "Do you want to load plugins with plugin manager (y/n) ? ";
	CIN >> answer;

/*...sTest loading single modules:8:*/
	{
		UAP_REQUEST(mm, lb_I_String, pre)

		if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
			UAP_REQUEST(mm, lb_I_PluginManager, PM)
	
			if (PM->beginEnumPlugins()) {
	
				while (true) {
					UAP(lb_I_Plugin, pl)
					pl = PM->nextPlugin();
			
					if (pl == NULL) break;
		
					pl->initialize();
				
					_CL_LOG << "Plugin name: " << pl->getName() << " from " << pl->getModule() << "." LOG_
				
					COUT << "Load (y/n) ? ";
					CIN >> answer;
				
					if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
						UAP(lb_I_Unknown, uk)
					
						uk = pl->getImplementation();
						if (uk != NULL) {
							_CL_LOG << "Loaded: " << uk->getClassName() LOG_
						} else {
							_CL_LOG << "Failed to get plugin implementation." LOG_
						}
					}
				}
			}
			
			_CL_LOG << "* Unload plugin manager *" LOG_
			
			PM->unload();
			
			_CL_LOG << "*        Unloaded       *" LOG_
		}
	}
/*...e*/
	
	COUT << "Do you want to load two plugins with plugin manager (y/n) ? ";
	CIN >> answer;

	UAP(lb_I_Unknown, uk1)
	UAP(lb_I_Unknown, uk2)

/*...sTest loading two modules:8:*/
	if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
		UAP_REQUEST(mm, lb_I_String, pre)

		{
			UAP_REQUEST(mm, lb_I_PluginManager, PM)
	
/*...sLoad first from given list:32:*/
			if (PM->beginEnumPlugins()) {
	
				while (true) {
					setVerbose(false);
					UAP(lb_I_Plugin, pl)
					pl = PM->nextPlugin();
			
					if (pl == NULL) break;
		
					pl->initialize();
				
					_CL_LOG << "Plugin name: " << pl->getName() LOG_
				
					COUT << "Load (y/n) ? ";
					CIN >> answer;
				
					if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
						uk1 = pl->getImplementation();
						if (uk1 != NULL) {
							_CL_LOG << "Loaded: " << uk1->getClassName() LOG_
							setVerbose(true);
							break;
						} else {
							_CL_LOG << "Failed to get plugin implementation." LOG_
						}
					}
					setVerbose(true);
				}
				setVerbose(false);
			}
/*...e*/
			
			_CL_LOG << "Loaded first plugin." LOG_
			
/*...sLoad second from given list:32:*/
			if (PM->beginEnumPlugins()) {
	
				while (true) {
					setVerbose(false);
					UAP(lb_I_Plugin, pl)
					pl = PM->nextPlugin();
			
					if (pl == NULL) break;
		
					pl->initialize();
				
					_CL_LOG << "Plugin name: " << pl->getName() LOG_
				
					COUT << "Load (y/n) ? ";
					CIN >> answer;
				
					if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
						uk2 = pl->getImplementation();
						if (uk2 != NULL) {
							_CL_LOG << "Loaded: " << uk2->getClassName() LOG_
							setVerbose(true);
							break;
						} else {
							_CL_LOG << "Failed to get plugin implementation." LOG_
						}
					}
					setVerbose(true);
				}
				setVerbose(false);
			}
/*...e*/
			
			_CL_LOG << "* Unload plugin manager *" LOG_
			
			_CL_LOG << "*        Unloaded       *" LOG_
		}
		_CL_LOG << "Have the following plugins loaded and plugin manager released:" LOG_
		_CL_LOG << "Plugin 1: " << uk1->getClassName() << " with " << uk1->getRefCount() << " references." LOG_
		_CL_LOG << "Plugin 2: " << uk2->getClassName() << " with " << uk2->getRefCount() << " references." LOG_

		PM->unload();
	}


/*...e*/

	COUT << "Do you want to locale module (y/n) ? ";
	CIN >> answer;
	
	if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
		char* t = "Dynamic sample";
		char* translated = _trans(t);
		
		_CL_LOG << "Translated " << t << " to " << translated LOG_
	}
	
	char repeat[100] = "y";

	COUT << "Do you want to test a plugin module (y/n) ? ";
	CIN >> answer;

	while ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0) && 
	       (strcmp(repeat, "y") == 0) || (strcmp(repeat, "Y") == 0))
	{
/*...sDo loop:16:*/

		char moduleName[100];
		char functorName[100];
	
		if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
			COUT << "Module name: ";
			CIN >> moduleName;
	
			COUT << "Functor: ";
			CIN >> functorName;
		
			UAP(lb_I_Unknown, uk)
			UAP(lb_I_PluginModule, plM)
		
			if (mm->makeInstance(functorName, moduleName, &uk) != ERR_NONE) {
				COUT << "ERROR: Module or functor not found!" << ENDL;
			}
			
			QI(uk, lb_I_PluginModule, plM)
			
			if (plM != NULL) {
			        COUT << "Call initialize of plugin module." << ENDL;
			        plM->setModuleManager(mm, __FILE__, __LINE__);
			        plM->setModule(moduleName);
			        plM->initialize();
			}
		}

		COUT << "Do you want to repeat loading that functor (y/n) ? ";
		CIN >> answer;

		if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0)) {
	                UAP(lb_I_Unknown, uk)
	                UAP(lb_I_PluginModule, plM)

	                if (mm->makeInstance(functorName, moduleName, &uk) != ERR_NONE) {
	                        COUT << "ERROR: Module or functor not found!" << ENDL;
	                }
	                
	                QI(uk, lb_I_PluginModule, plM)
	                
	                if (plM != NULL) {
	                	COUT << "Call initialize of plugin module." << ENDL;
	                	plM->setModuleManager(mm, __FILE__, __LINE__);
	                	plM->setModule(moduleName);
	                	plM->initialize();
	                }
		}

		COUT << "Do you want to repeat (y/n) ? ";
		CIN >> repeat;
/*...e*/
	}

	COUT << "Do you want to find a plugin with interface and namespace (y/n) ? ";
	CIN >> answer;

/*...sDo plugin test with interface and namespace:8:*/
	UAP_REQUEST(getModuleInstance(), lb_I_Container, plugins)
	UAP_REQUEST(getModuleInstance(), lb_I_String, plName)
	UAP(lb_I_KeyBase, plKey)

	while ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0) && 
	       (strcmp(repeat, "y") == 0) || (strcmp(repeat, "Y") == 0))
	{
		char namesp[100] = "";
		char interf[100] = "";

		UAP(lb_I_Unknown, uk)
		
		COUT << "Interface: ";
		CIN >> interf;
		COUT << "Namespace: ";
		CIN >> namesp;

		uk = findPluginByInterfaceAndNamespace(interf, namesp);

	        *plName = uk->getClassName();
	        QI(plName, lb_I_KeyBase, plKey)
		        
	        plugins->insert(&uk, &plKey);
	        _CL_LOG << "Found one: " << uk->getClassName() LOG_	        	        
	        
	        COUT << "Do you want to find another plugin with interface and namespace (y/n) ? ";
	        CIN >> answer;
	}
/*...e*/

	COUT << "Do you want to test problematic plugins (y/n) ? ";
	CIN >> answer;

/*...sproblematic plugins:8:*/
	if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0) &&
	       (strcmp(repeat, "y") == 0) || (strcmp(repeat, "Y") == 0))
	{
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Unknown, uk1)
		
		uk = findPluginByInterfaceAndNamespace("lb_I_User_Applications", "Model");
		uk1 = findPluginByInterfaceAndNamespace("lb_I_User_Applications", "Model");
		
		_CL_LOG << "Loaded problematic plugin. It has " << uk->getRefCount() << " references." LOG_
	}
/*...e*/

	COUT << "Do you want to print names of yet loaded plugins (y/n) ? ";
	CIN >> answer;
	
	if ((strcmp(answer, "y") == 0) || (strcmp(answer, "Y") == 0) &&
	       (strcmp(repeat, "y") == 0) || (strcmp(repeat, "Y") == 0))
	
	while (plugins->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		uk = plugins->nextElement();

		_CL_LOG << "Plugin loaded: " << uk->getClassName() LOG_
	}

	_CL_LOG << "Plugin manager has " << PM->getRefCount() << " references." LOG_

        PM->unload();
        PM--;
        PM.resetPtr();
	
	_CL_LOG << "Unloaded plugins." LOG_
	
	mm->release(__FILE__, __LINE__);

}

	unHookAll();

        return 0;
}

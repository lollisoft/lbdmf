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

/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.57 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.57 2005/04/18 19:04:22 lollisoft Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
 * Revision 1.57  2005/04/18 19:04:22  lollisoft
 * Returning proper error code.
 *
 * Revision 1.56  2005/04/02 09:52:37  lollisoft
 * Put optional parameter into paramater list.
 *
 * Revision 1.55  2005/03/31 08:59:34  lollisoft
 * Copyright text problems under linux.
 *
 * Revision 1.54  2005/03/19 16:40:59  lollisoft
 * Implemented i18n.
 *
 * Revision 1.53  2005/02/20 18:01:23  lollisoft
 * Bugfix due to buffer overflow affecting GUI sample under Linux
 *
 * Revision 1.52  2005/02/20 09:39:33  lollisoft
 * Deactivated unneeded menu entries.
 *
 * Revision 1.51  2005/02/14 16:37:14  lollisoft
 * Much tries to get foreign key handling work under linux. But there might be some magic bugs, that don't let them use
 *
 * Revision 1.50  2005/02/13 09:13:16  lollisoft
 * Using applicationName to load not a hardcoded application
 *
 * Revision 1.49  2005/02/12 15:46:32  lollisoft
 * Changed SQL queries, enabled optional user and password settings via
 * environment.
 *
 * Revision 1.48  2005/02/10 17:02:26  lollisoft
 * Changes for Mac OS X
 *
 * Revision 1.47  2005/02/02 13:30:29  lollisoft
 * Latest changes for version 0.4.1
 *
 * Revision 1.46  2005/01/27 12:53:27  lollisoft
 * Changed SQL query not to use " in it
 *
 * Revision 1.45  2005/01/25 12:54:41  lollisoft
 * Verbose message added
 *
 * Revision 1.44  2005/01/23 13:43:04  lollisoft
 * std:: is only under linux working
 *
 * Revision 1.43  2005/01/23 11:29:27  lollisoft
 * Now the code compiles under SuSE Linux 9.1
 *
 * Revision 1.42  2005/01/21 14:58:47  lollisoft
 * Removed some unused log messages, changed SQL case to lower
 *
 * Revision 1.41  2005/01/05 13:41:36  lollisoft
 * New dynamic application implementation works
 *
 * Revision 1.40  2004/10/09 16:55:07  lollisoft
 * Bugfix for call of pure virtual function. Don't know where it comes from ??
 *
 * Revision 1.39  2004/08/10 18:25:26  lollisoft
 * Lesser logging messages.
 *
 * Revision 1.38  2004/08/01 21:34:03  lollisoft
 * More documentation
 *
 * Revision 1.37  2004/07/18 07:28:25  lollisoft
 * Now the database sample works also under linux. Some bugs solved and minor changes
 *
 * Revision 1.36  2004/07/17 08:47:57  lollisoft
 * Bugfix for MSVC
 *
 * Revision 1.35  2004/07/16 20:24:41  lollisoft
 * Added handler to enter into the debugger
 *
 * Revision 1.34  2004/06/29 16:35:50  lollisoft
 * Removed some log messages
 *
 * Revision 1.33  2004/04/10 17:54:23  lollisoft
 * Current version runs on linux again. There was a bug in additional linux code to strcat to a variable. This variable was given as a parameter and therefore I cannot assume, that I am able to have a big enough buffer for that action. Electric Fence gave me the hint for that bug.
 *
 * Revision 1.32  2004/02/02 23:24:39  lollisoft
 * New label and text field handlers works
 *
 * Revision 1.31  2004/01/24 16:16:57  lollisoft
 * Added support for loading application
 *
 * Revision 1.30  2003/12/13 10:56:25  lollisoft
 * Database improovements and changes in my licence adress.
 * The database part is still not working by updating columns
 *
 * Revision 1.29  2003/08/22 17:38:35  lollisoft
 * Implemented a handler for a button press event and code to demonstrate
 *
 * Revision 1.28  2003/08/16 18:03:25  lollisoft
 * Added my new address due to move
 *
 * Revision 1.27  2003/07/15 22:18:05  lollisoft
 * Removed debug messages, implemented numeric dispatcher and much more
 *
 * Revision 1.26  2003/07/10 21:13:06  lollisoft
 * Adding menu entry implemented
 *
 * Revision 1.25  2003/03/14 16:00:36  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.24  2003/02/17 21:34:34  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.23  2003/02/09 13:22:50  lothar
 * Different log usage
 *
 * Revision 1.22  2003/01/27 21:18:04  lothar
 * Missed STARTREF setup
 *
 * Revision 1.21  2003/01/19 17:31:31  lothar
 * Runs now with MSC
 *
 * Revision 1.20  2003/01/15 22:42:20  lothar
 * Compiles with MSC
 *
 * Revision 1.19  2002/12/29 16:09:29  lothar
 * Intent to go public
 *
 * Revision 1.18  2002/12/12 20:59:38  lothar
 * Now it runs under Linux again
 *
 * Revision 1.17  2002/12/08 17:07:23  lothar
 * More tries to run under linux
 *
 * Revision 1.16  2002/11/29 19:50:26  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.15  2002/11/08 18:53:25  lothar
 * Compiles now (-d1)
 *
 * Revision 1.13  2002/10/04 16:53:11  lothar
 * Replaced old LOG macro with the new
 * _LOG << "text" << integer value LOG_
 * combination. This makes sprintf obsolete.
 *
 * Revision 1.12  2002/10/01 19:22:59  lothar
 * Broken
 *
 * Revision 1.11  2002/09/19 19:34:12  lothar
 * Buggy version - only, if menu is really created
 *
 * Revision 1.10  2002/09/17 04:26:36  lothar
 * First API-Callback works
 *
 * Revision 1.9  2002/09/12 18:34:02  lothar
 * Added some UI wrapper and sub module creation. Cleanup
 *
 * Revision 1.8  2002/09/07 09:57:10  lothar
 * First working callback function
 *
 * Revision 1.7  2002/09/04 17:52:12  lothar
 * Problems with stack cleanup
 *
 * Revision 1.6  2002/08/21 17:59:42  lothar
 * More functions implemented
 *
 * Revision 1.5  2002/08/06 05:41:39  lothar
 * More special Dispatcher and EventManager interface.
 * Empty bodies compiling
 *
 * Revision 1.4  2002/07/23 17:48:55  lothar
 * Current version runs
 *
 * Revision 1.3  2002/04/15 18:24:31  lothar
 * Huge changes - works good
 *
 * Revision 1.2  2002/02/25 06:13:07  lothar
 * Much changes
 * Program seems to run, but performance is very slow
 *
 **************************************************************/
/*...e*/
#define LB_METAAPP_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

/*...sincludes:0:*/


#include <stdio.h>
#include <string.h>
#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

#include <lbmetaapp-module.h>

#include <lbMetaApplication.h>
/*...e*/

/*...sFunctors:0:*/
#ifdef __cplusplus
extern "C" {       
#endif            

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)
IMPLEMENT_FUNCTOR(instanceOfEventMapper, lb_EventMapper)
IMPLEMENT_FUNCTOR(instanceOfEvHandler, lb_EvHandler)

IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDispatcher, lb_Dispatcher)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfEventManager, lb_EventManager)

#ifdef __cplusplus
}
#endif            
/*...e*/


/*...slb_MetaApplication:0:*/
/*...sctors\47\dtors:0:*/
lb_MetaApplication::lb_MetaApplication() {
	ref = STARTREF;
	gui = NULL;
}

lb_MetaApplication::~lb_MetaApplication() {
}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::enterDebugger, "enterDebugger");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler1, "getBasicApplicationInfo");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbEvHandler2, "getMainModuleInfo");
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::lbButtonTestHandler, "Button Test pressed");
	
	// Register a general login functionality
	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::getLoginData, "getLoginData");
	
	return ERR_NONE;
}
/*...e*/

/*...sevent handlers\44\ that can be registered:0:*/

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\enterDebugger\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::enterDebugger(lb_I_Unknown* uk) {
#ifdef WINDOWS
	DebugBreak();
#endif
#ifdef LINUX
	// How do I this under linux ??
#endif
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbEvHandler1\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler1(lb_I_Unknown* uk) {
	_LOG << "lb_MetaApplication::lbEvHandler1() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbEvHandler2\40\lb_I_Unknown\42\ uk\41\ \47\\47\ Show a simple message box:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler2(lb_I_Unknown* uk) {

	if (gui != NULL) {
	        gui->msgBox("Information", "The main module of this application is a DLL and creates a basic functionality.\nThe real application will be loaded from configuraton and then the control\nwill be delegated to it.");
	} else {
	        COUT << "lb_MetaApplication::Initialize() called in console mode" << ENDL;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbButtonTestHandler\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbButtonTestHandler(lb_I_Unknown* uk) {

        if (gui != NULL) {
                gui->msgBox("Information", "Test button has been pressed");
        } else {
                COUT << "lb_MetaApplication::Initialize() called in console mode" << ENDL;
        }

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getLoginData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getLoginData(lb_I_Unknown* uk) {

        if (gui != NULL) {
                UAP(lb_I_Form, loginForm, __FILE__, __LINE__)

                loginForm = gui->createLoginForm();
        } else {
                COUT << "Login form on console not supported" << ENDL;
        }

	return ERR_NONE;
}
/*...e*/
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	_LOG << "lb_MetaApplication::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager \42\ lb_MetaApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager * lb_MetaApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\Initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::Initialize(char* user, char* app) {
/*...sdoc:8:*/
/**
 * At this point should be found the real application. The real one
 * may be defined by an environment variable, that is defined out of
 * a batch file.
 * The variable contains the name of the application, where a xml tag
 * resolves the functor for this application.
 */
/*...e*/

/*...sdispatch integer values:8:*/
	/*
	 * This variable is needed, if this instance also implements a little dispatcher.
	 * It should moved into the class declatation and used in the dispatch functions.
	 */
	int getBasicApplicationInfo;
	int getMainModuleInfo;
	int testPressed;
	int enterDebugger;
	int getLoginData;
/*...e*/

/*...sget the event manager:8:*/
	/**
	 * Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */
	
	lb_I_Module* m = *&manager;
	REQUEST(m, lb_I_EventManager, eman)
/*...e*/
	
/*...sregister some basic events \40\getBasicApplicationInfo\46\\46\\46\\41\ by the event manager:8:*/
	eman->registerEvent("enterDebugger", enterDebugger);
	eman->registerEvent("getBasicApplicationInfo", getBasicApplicationInfo);
	eman->registerEvent("getMainModuleInfo", getMainModuleInfo);
	eman->registerEvent("Button Test pressed", testPressed);

	if (getenv("TARGET_APPLICATION") == NULL) {
		// Need a database configuration based authentication
		eman->registerEvent("getLoginData", getLoginData);
	}
/*...e*/

/*...sget the dispatcher instance:8:*/
	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());
/*...e*/

	registerEventHandler(dispatcher.getPtr());

	// Step 3 (Load sub components, handling menus and else needed for an UI)
	loadSubModules();

/*...ssome docs:8:*/
	/**
	 * After initializion of all event handlers, we need to get up all
	 * GUI accessible handlers - like menus or else.
	 * This class, as an example, provides two handlers
	 * getBasicApplicationInfo and getMainModuleInfo
	 * 
	 * The handler depends on some capabilities:
	 *
	 * 	1. A basic dialog to show text
	 *		This may be a container of capabilities
	 *		 must:SimpleTextDialog
	 *		 optional:PictureElements
	 *
	 * It provides these capabilities:
	 *
	 *	1. An information about menu creation
	 *		This may be a simple string - lb_I_String
	 */


	/**
	 * Init the application (menu, toolbar, accelerators)
	 *
	 * This will be done by the loaded application from the
	 * environment variable (TARGET_APPLICATION)
	 */
/*...e*/
	
	addMenuBar(_trans("&Edit"));

	if (getenv("TARGET_APPLICATION") != NULL) {
		loadApplication("", "");
	}
	
	addMenuBar(_trans("&Help"));

	if (getenv("TARGET_APPLICATION") == NULL) {
		char* login = strdup(_trans("&Login\tCtrl-L"));
		addMenuEntry(_trans("&File"), login, "getLoginData", "");
		free(login);
	}
	
	char* mm = strdup(_trans("MainModule&Info\tCtrl-I"));
	addMenuEntry(_trans("&Help"), mm, "getMainModuleInfo", "");
	free(mm);

#ifdef bla	
/*...sMain module demos and their help:8:*/

	addButton("Press me for test", "Button Test pressed", 10, 30, 100, 20);
	
	int hight = 60;

	addLabel("Label", 115, 30, 100, 20);
	addTextField("TextField", 220, 30, 100, 20);

	for (int n = 1; n <= 7; n++) {
		addButton("|<", "Button Test pressed", 10, hight+n*20+n*5, 100, 20);
		addButton("<<", "Button Test pressed", 115, hight+n*20+n*5, 100, 20);
		addButton(">>", "Button Test pressed", 220, hight+n*20+n*5, 100, 20);
		addButton(">|", "Button Test pressed", 325, hight+n*20+n*5, 100, 20);
	}
/*...e*/
#endif

	return ERR_NONE;
}
/*...e*/


// This starts the main application

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);	
#endif
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::loadSubModules() {
	return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\loadApplication\40\char\42\ user\44\ char\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::loadApplication(char* user, char* application) {
	lbErrCodes err = ERR_NONE;
        char* applicationName = getenv("TARGET_APPLICATION");

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	if (applicationName == NULL) {
		/*
		 * No predefined application without authentication.
		 * Read the configuration from a database.
		 */
		

		UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
		UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

		database->init();
		database->connect("lbDMF", lbDMFUser, lbDMFPasswd);

		sampleQuery = database->getQuery(0);

		char buffer[1000] = "";

		sprintf(buffer,
		        "select Anwendungen.modulename, Anwendungen.functor, Anwendungen.interface from Anwendungen inner join User_Anwendungen on "
		        "Anwendungen.id = User_Anwendungen.anwendungenid "
		        "inner join Users on User_Anwendungen.userid = Users.id where "
		        "Users.userid = '%s' and Anwendungen.name = '%s'"
		                , user, application);

		/*
		 * Decide upon the interface, if this code is capable to handle this application.
		 * First, only handle lb_I_MetaApplication types.
		 */

		sampleQuery->skipFKCollecting();
		sampleQuery->query(buffer);
		sampleQuery->enableFKCollecting();
		

		// Fill up the available applications for that user.
		UAP_REQUEST(manager.getPtr(), lb_I_String, ModuleName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, Functor)

		lbErrCodes DBerr = sampleQuery->first();

		if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {

		        ModuleName = sampleQuery->getAsString(1);
			Functor = sampleQuery->getAsString(2);

		        applicationName = strdup(ModuleName->charrep());

			#ifdef bla
/*...sRead only the first application\46\ More apps are wrong\46\:24:*/
		        while (TRUE) {
		                lbErrCodes err = sampleQuery->next();

		                if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
		                        s1 = sampleQuery->getAsString(1);

		                        printf("Have application '%s'\n", s1->charrep());

		                        box->Append(wxString(s1->charrep()));

		                        if (err == WARN_DB_NODATA) break;
		                }
		        }
/*...e*/
			#endif

		}

		lb_I_Unknown* a = NULL;

		#ifndef LINUX
		        #ifdef __WATCOMC__
		        	#define PREFIX "_"
	        	#endif
			#ifdef _MSC_VER
			        #define PREFIX ""
	        	#endif
		#endif
		#ifdef LINUX
			#define PREFIX ""
		#endif

		char f[100] = "";
		char appl[100] = "";

		strcpy(f, PREFIX);
		strcat(f, Functor->charrep());
		strcpy(appl, applicationName);
		
                #ifdef WINDOWS
                manager->makeInstance(f, appl, &a);
                #endif
                #ifdef LINUX
		strcat(appl, ".so");		
                manager->makeInstance(f, appl, &a);
                #endif
                if (a == NULL) {
                        _LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
                        return ERR_NONE;
                }

		a->setModuleManager(manager.getPtr(), __FILE__, __LINE__);

                QI(a, lb_I_MetaApplication, app, __FILE__, __LINE__)

                if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

                app->setGUI(gui);
                app->Initialize(user, application);

                if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
	} else {

		lb_I_Unknown* a = NULL;

		#ifndef LINUX
			#ifdef __WATCOMC__
				#define PREFIX "_"
			#endif
			#ifdef _MSC_VER
				#define PREFIX ""
			#endif
		#endif
		#ifdef LINUX
			#define PREFIX ""
		#endif

		#ifdef WINDOWS	
		manager->makeInstance(PREFIX "instanceOfApplication", applicationName, &a);
		#endif
		#ifdef LINUX
		char name[80] = "";
		strcpy(name, applicationName);
		strcat(name, ".so");
		manager->makeInstance(PREFIX "instanceOfApplication", name, &a);
		#endif	
		if (a == NULL) {
			_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
			return ERR_NONE;
		}
		
		QI(a, lb_I_MetaApplication, app, __FILE__, __LINE__)

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

		app->setGUI(gui);
		app->Initialize();

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
	}

        return ERR_NONE;
}
/*...e*/

/*...sBasic functions to be used for a UI application:0:*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenuBar\40\char\42\ name\44\ char\42\ after\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuBar(char* name, char* after) {
	lbErrCodes err = ERR_NONE;

/*...sbla:0:*/
/*

	UAP_REQUEST(manager.getPtr(), lb_I_String, string)
	string->setData(name);
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(string, lb_I_Unknown, uk, __FILE__, __LINE__)

	// Avoids GPF while leaving the function
	string++;

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)

	if (uk == NULL) _LOG << "Error: Cannot call with a null pointer!" LOG_

*/
/*...e*/

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)

	parameter->setData("name");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	if (after != NULL) {
		parameter->setData("after");
		value->setData(after);
		param->setUAPString(*&parameter, *&value);

	}


	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)
	
	dispatcher->dispatch("AddMenuBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::addMenu(char* name) {
	return ERR_NONE;
}

/*...slb_MetaApplication\58\\58\addTextField\40\char\42\ name\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addTextField(char* name, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)

        parameter->setData("text");
        value->setData(name);
        param->setUAPString(*&parameter, *&value);

        parameter->setData("x");
        i->setData(x);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("y");
        i->setData(y);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("w");
        i->setData(w);
        param->setUAPInteger(*&parameter, *&i);

        parameter->setData("h");
        i->setData(h);
        param->setUAPInteger(*&parameter, *&i);

        UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
        QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)

        UAP_REQUEST(manager.getPtr(), lb_I_String, result)
        UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
        QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)

        dispatcher->dispatch("AddTextField", uk.getPtr(), &uk_result);

        return err;
}
/*...e*/

/*...slb_MetaApplication\58\\58\addLabel\40\char\42\ text\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addLabel(char* text, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)


	parameter->setData("labeltext");
	value->setData(text);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("x");
	i->setData(x);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("y");
	i->setData(y);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("w");
	i->setData(w);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("h");
	i->setData(h);
	param->setUAPInteger(*&parameter, *&i);

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)
	
	dispatcher->dispatch("AddLabel", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

/*...slb_MetaApplication\58\\58\addButton\40\char\42\ buttonText\44\ char\42\ evHandler\44\ int x\44\ int y\44\ int w\44\ int h\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) {
        lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	
	
	parameter->setData("buttontext");
	value->setData(buttonText);
	param->setUAPString(*&parameter, *&value);
	
	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);
	
	parameter->setData("x");
	i->setData(x);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("y");
	i->setData(y);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("w");
	i->setData(w);
	param->setUAPInteger(*&parameter, *&i);

	parameter->setData("h");
	i->setData(h);
	param->setUAPInteger(*&parameter, *&i);

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)
	
	dispatcher->dispatch("AddButton", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

/*...slb_MetaApplication\58\\58\addMenuEntry\40\char\42\ in_menu\44\ char\42\ entry\44\ char\42\ evHandler\44\ char\42\ afterentry\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	
	
	parameter->setData("menubar");
	value->setData(in_menu);
	param->setUAPString(*&parameter, *&value);
	
	parameter->setData("menuname");
	value->setData(entry);
	param->setUAPString(*&parameter, *&value);

	parameter->setData("handlername");
	value->setData(evHandler);
	param->setUAPString(*&parameter, *&value);
	
	if (afterentry && (strcmp(afterentry, "") != 0)) {
		parameter->setData("after");
		value->setData(afterentry);
		param->setUAPString(*&parameter, *&value);
	}

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	QI(param, lb_I_Unknown, uk, __FILE__, __LINE__)

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result, __FILE__, __LINE__)
	QI(result, lb_I_Unknown, uk_result, __FILE__, __LINE__)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);
	

	return ERR_NONE;
}
/*...e*/
/*...e*/
/*...e*/
/*...slb_EventMapper:0:*/
lb_EventMapper::lb_EventMapper() {
	ref = STARTREF;
	_LOG << "Instance of lb_I_EventMapper created" LOG_
	_name = NULL;
}

lb_EventMapper::~lb_EventMapper() {
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventMapper)
	ADD_INTERFACE(lb_I_EventMapper)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_EventMapper::setData(lb_I_Unknown* uk) {
	_LOG << "lb_EventMapper::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_EventMapper::setEvent(char* name, lbEvHandler handler) {
	_name = strdup(name);
	return ERR_NONE;
}

char* LB_STDCALL lb_EventMapper::getName() {
	if (_name != NULL) return _name;
	return NULL;
}

int LB_STDCALL lb_EventMapper::getID() {
	return _id;
}

void LB_STDCALL lb_EventMapper::setID(int id) {
	_id = id;
}

/*...e*/

/*...slb_EventManager:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventManager)
	ADD_INTERFACE(lb_I_EventManager)
END_IMPLEMENT_LB_UNKNOWN()

lb_EventManager::lb_EventManager() {
	maxEvId = 0;
	ref = STARTREF;
}

lb_EventManager::~lb_EventManager() {
}
	
lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	_LOG << "lb_EventManager::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}

/*...slb_EventManager\58\\58\registerEvent\40\char\42\ EvName\44\ int \38\ EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_EventManager::registerEvent(char* EvName, int & EvNr) {
	lbErrCodes err = ERR_NONE;
	int newId = maxEvId + 1;

/*...sInit containers:8:*/
	if (events == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, events)

		// For housekeeping	
		REQUEST(manager.getPtr(), lb_I_Container, freeIds)
		
		// The reverse
		REQUEST(manager.getPtr(), lb_I_Container, reverse_events)
	}
/*...e*/
	
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringData)
	stringData->setData(EvName);
	
	UAP(lb_I_KeyBase, sk, __FILE__, __LINE__)
	QI(stringData, lb_I_Unknown, sk, __FILE__, __LINE__)
/*...e*/
	
/*...sError handling:8:*/
	if (events == NULL) _LOG << "Nullpointer detected (events)!" LOG_
	if (*&sk == NULL) _LOG << "Nullpointer detected (sk)!" LOG_
	if (events->exists(&sk) == 1) {
		_LOG << "lb_EventManager::registerEvent(): Error: Event schon registriert" LOG_
		return ERR_EVENT_EXISTS;
	}
/*...e*/
/*...sdetermine id:8:*/
	if (freeIds->Count() == 0) {
		maxEvId++;
	} else {
		UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
		UAP(lb_I_KeyBase, key, __FILE__, __LINE__)

		key = freeIds->getKeyAt(freeIds->Count());
		uk = freeIds->getElementAt(freeIds->Count());
		
		freeIds->remove(&key);
			
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		QI(uk, lb_I_Integer, i, __FILE__, __LINE__)

		newId = i->getData();
	}
/*...e*/
/*...sinsert new event:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerData)
	integerData->setData(maxEvId);
	
	UAP(lb_I_Unknown, idata, __FILE__, __LINE__)
	QI(integerData, lb_I_Unknown, idata, __FILE__, __LINE__)

	events->insert(&idata, &sk);
	
	UAP(lb_I_KeyBase, ik, __FILE__, __LINE__)
	QI(integerData, lb_I_Unknown, ik, __FILE__, __LINE__)

	UAP(lb_I_Unknown, sdata, __FILE__, __LINE__)
	QI(stringData, lb_I_Unknown, sdata, __FILE__, __LINE__)
	
	reverse_events->insert(&sdata, &ik);
	
	EvNr = maxEvId;
/*...e*/

	if (events->exists(&sk) != 1) {
		_LOG << "lb_EventManager::registerEvent(): Error: Event could not be registered" LOG_
		return ERR_EVENT_NOTREGISTERED;
	}
	
	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_EventManager::resolveEvent(char* EvName, int & evNr) {
	lbErrCodes err = ERR_NONE;
	
/*...sSetup key \40\get a string\44\ store the char\42\ value and get a key from it\41\:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_String, stringKey)
	stringKey->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	stringKey->setData(EvName);
	
	UAP(lb_I_KeyBase, kk, __FILE__, __LINE__)
	QI(stringKey, lb_I_Unknown, kk, __FILE__, __LINE__)
/*...e*/

/*...sresolve event:8:*/
	if (events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object, __FILE__, __LINE__)
		UAP(lb_I_Integer, i, __FILE__, __LINE__)
		
		object = events->getElement(&kk);
		QI(object, lb_I_Integer, i, __FILE__, __LINE__)
		evNr = i->getData();
	} else {
		_LOG << "Error: Event name not registered: " << EvName LOG_
		return ERR_EVENT_NOTREGISTERED;
	}
/*...e*/

	return ERR_NONE;
}

char* LB_STDCALL lb_EventManager::reverseEvent(int evNr) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, ID)
	ID->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	ID->setData(evNr);
	
	UAP(lb_I_KeyBase, kk, __FILE__, __LINE__)
	QI(ID, lb_I_Unknown, kk, __FILE__, __LINE__)
	
	if (reverse_events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object, __FILE__, __LINE__)
		UAP(lb_I_String, str, __FILE__, __LINE__)
		
		object = reverse_events->getElement(&kk);
		QI(object, lb_I_String, str, __FILE__, __LINE__)
		static char result[100] = "";
		strcpy(result, str->getData());
		
		return result;
	} else {
		_LOG << "Error: Event id not registered: " << evNr LOG_
		return "";
	}
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {

	ref = STARTREF;
}

lb_Dispatcher::~lb_Dispatcher() {
	_LOG << "lb_Dispatcher::~lb_Dispatcher() called" LOG_
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	_LOG << "lb_Dispatcher::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setEventManager\40\lb_I_EventManager\42\ EvManager\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setEventManager(lb_I_EventManager* EvManager) {
	
	evManager = EvManager;
	evManager++;
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName) {
	/*
	 * Create an instance of a function pointer object
	 */
	
	int id = 0;
	evManager->resolveEvent(EvName, id);
	addEventHandlerFn(evHandlerInstance, evHandler, id);	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ int EvNr\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, int EvNr) {
	lbErrCodes err = ERR_NONE;
	
	if (dispatcher == NULL) {
		// Create the instance, that holds the events mapping
		REQUEST(manager.getPtr(), lb_I_Container, dispatcher)
		dispatcher->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	}

	UAP_REQUEST(manager.getPtr(), lb_I_EvHandler, evH)
	evH->setHandler(evHandlerInstance, evHandler);

	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setData(EvNr);

	  UAP(lb_I_KeyBase, k, __FILE__, __LINE__)
	QI(i, lb_I_KeyBase, k, __FILE__, __LINE__)

	    UAP(lb_I_Unknown, e, __FILE__, __LINE__)
	QI(evH, lb_I_Unknown, e, __FILE__, __LINE__)
	if (dispatcher->exists(&k) == 1) {
        	dispatcher->remove(&k);
	}

	if ((err = dispatcher->insert(&e, &k)) != ERR_NONE) _LOG << "Error: Inserting new container element failed" LOG_

	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)

	uk = dispatcher->getElement(&k);
	
	if (uk == NULL) _LOG << "Error: Adding event handler failed (not stored)" LOG_

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	_LOG << "lb_Dispatcher::addDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delDispatcher(lb_I_Dispatcher* disp) {
	_LOG << "lb_Dispatcher::delDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slb_I_DispatchResponce\42\ lb_Dispatcher\58\\58\dispatch\40\lb_I_DispatchRequest\42\ req\41\:0:*/
lb_I_DispatchResponse* lb_Dispatcher::dispatch(lb_I_DispatchRequest* req) {
	_LOG << "lb_Dispatcher::dispatch() called" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\int EvNr\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setData(EvNr);
	
	UAP(lb_I_KeyBase, ik, __FILE__, __LINE__)
	QI(i, lb_I_KeyBase, ik, __FILE__, __LINE__)
	
	
	UAP(lb_I_Unknown, uk, __FILE__, __LINE__)
	UAP(lb_I_EvHandler, ev, __FILE__, __LINE__)
	
	if (dispatcher == NULL) {
		_LOG << "Error: Have no dispatcher" LOG_
	} else {
	
		uk = dispatcher->getElement(&ik);
	
		if (uk == NULL) {
			_LOG << "Error: Could not get the handler from the id" LOG_
			return ERR_DISPATCH_FAILS;
		}
	
		QI(uk, lb_I_EvHandler, ev, __FILE__, __LINE__)

		ev->call(EvData, EvResult);
	}
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\char\42\ EvName\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(char* EvName, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {

	int id = 0;
	lbErrCodes err = ERR_NONE;
	
	evManager->resolveEvent(EvName, id);

	return dispatch(id, EvData, EvResult);
}
/*...e*/
/*...e*/

/*...slb_EvHandler:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EvHandler)
	ADD_INTERFACE(lb_I_EvHandler)
END_IMPLEMENT_LB_UNKNOWN()

lb_EvHandler::lb_EvHandler() {
	ev = NULL;
	ref = STARTREF;
}

lb_EvHandler::~lb_EvHandler() {
}

lbEvHandler LB_STDCALL lb_EvHandler::getHandler() {
	return ev;
}

lbErrCodes LB_STDCALL lb_EvHandler::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_EvHandler, eh, __FILE__, __LINE__)
	QI(uk, lb_I_EvHandler, eh, __FILE__, __LINE__)
	
	setHandler(eh->getHandlerInstance(), eh->getHandler());
	
	return ERR_NONE;
}

lb_I_EventHandler* LB_STDCALL lb_EvHandler::getHandlerInstance() {
	return _evHandlerInstance;
}

lbErrCodes LB_STDCALL lb_EvHandler::setHandler(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler) {
	_evHandlerInstance = evHandlerInstance;
	ev = evHandler;
	return ERR_NONE;
}


lbErrCodes LB_STDCALL lb_EvHandler::call(lb_I_Unknown* evData, lb_I_Unknown** evResult) {
	(_evHandlerInstance->*(lbEvHandler) ev) (evData);
	
	return ERR_NONE;
}
/*...e*/

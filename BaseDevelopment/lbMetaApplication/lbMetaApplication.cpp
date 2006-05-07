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
 * $Revision: 1.88 $
 * $Name:  $
 * $Id: lbMetaApplication.cpp,v 1.88 2006/05/07 07:07:57 lollisoft Exp $
 *
 * $Log: lbMetaApplication.cpp,v $
 * Revision 1.88  2006/05/07 07:07:57  lollisoft
 * Corrected file dialog cancel handling.
 *
 * Revision 1.87  2006/03/28 11:34:04  lollisoft
 * Renamed Initialize to initialize and added unloadApplication for better unloading of the application.
 *
 * Revision 1.86  2006/03/24 17:12:22  lollisoft
 * Added GUI state for maximized or not.
 *
 * Revision 1.85  2006/03/16 08:01:04  lollisoft
 * Added set and getAutorefreshData members to the  lb_I_MetaApplication implementation. Also included that flags in the property panel.
 *
 * Revision 1.84  2006/03/09 09:29:11  lollisoft
 * Catch plugin failure while loading application settings and
 * database connection failure.
 *
 * Revision 1.83  2006/02/22 11:49:57  lollisoft
 * Moved the general part to meta application. wxWrapper does ask for it when left panel will be shown.
 *
 * Revision 1.82  2006/02/21 20:56:30  lollisoft
 * Wrong menu updating.
 *
 * Revision 1.81  2006/02/21 19:35:50  lollisoft
 * Implemented autoload mechanism of last loaded application.
 * It demonstrates the new capabilities operating with files.
 *
 * Revision 1.80  2006/02/19 18:41:35  lollisoft
 * Feedback of properties works good. I am use the
 * dispatcher mechanism to forward the change events
 * on per lb_I_Parameter instance and the category name
 * to a registered handler.
 *
 * So one handler must be capable to recieve values for all
 * elements of one lb_I_Parameter instance.
 *
 * Revision 1.79  2006/02/17 23:57:13  lollisoft
 * Added functionality to pass a bunch of properties to the GUI. This then would be shown in a property window.
 *
 * There are additional changes in various classes to let this
 * work properly.
 *
 * Todo: Implement the unpacking and type detection code
 * for each parameter, mapping to wxPropertyGrid entities
 * and handlers that push back the changes.
 *
 * Revision 1.78  2006/01/30 15:54:14  lollisoft
 * Removed the __FILE__ and __LINE__ parameter usage in UAP and QI.
 * This was an unnessesary thing and makes programming easier.
 *
 * Revision 1.77  2006/01/26 14:03:23  lollisoft
 * Added event en/disable and toggle functions. Also added
 * askYesNo function.
 *
 * Revision 1.76  2006/01/22 13:36:51  lollisoft
 * Reading back an added parameter (result) works.
 *
 * Revision 1.75  2006/01/21 23:48:14  lollisoft
 * Added new member to ask the user for a file.
 *
 * Revision 1.74  2006/01/20 21:30:39  lollisoft
 * Used base class in loadApplication changed to lb_I_Application.
 *
 * Revision 1.73  2005/12/11 19:15:49  lollisoft
 * Release changes for 0.6.0. Added todo entries, removed unused code.
 *
 * Revision 1.72  2005/11/26 18:59:11  lollisoft
 * Minor changes to compile and run under Linux
 *
 * Revision 1.71  2005/11/20 13:39:52  lollisoft
 * Wrong variable name
 *
 * Revision 1.70  2005/11/18 23:41:31  lollisoft
 * More memory leaks have been fixed. There are currently less than 200
 * chunks unfreed, wich may be located in the plugin mechanism.
 *
 * Revision 1.69  2005/11/16 13:17:03  lollisoft
 * Added Memtrack breakpoint counter.
 *
 * Corrected reference count bug by using UAP for 'a' and using preload to
 * delegate unloading of shared library, loaded by loadApplication into
 * destructor.
 *
 * Revision 1.68  2005/11/11 22:51:30  lollisoft
 * Memory leaks removed. There are currently only 4 chunks leaky.
 * These may be false positives, because one of them is an allocated
 * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
 * wxMenuBar gets an owner (see wxWidgets documentation).
 *
 * Revision 1.67  2005/11/06 19:25:33  lollisoft
 * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
 *
 * Revision 1.66  2005/11/02 16:24:28  lollisoft
 * Bug for the program ending crash and the cout crash found. See history in
 * lbDB.cpp.
 *
 * Revision 1.65  2005/10/31 19:37:55  lollisoft
 * This version compiles and ends without a crash at exit. I have added a simple
 * string class to store places of queryInterface calls and setModuleManager calls.
 * This may change the layout to let the application not crash at exit.
 *
 * Revision 1.64  2005/10/31 15:02:04  lollisoft
 * Singleton mismatched to their declaration. Small correction in DllMain.
 *
 * Revision 1.63  2005/06/27 10:32:08  lollisoft
 * Mostly changes to conio.h conflicts while XCode build
 *
 * Revision 1.62  2005/06/20 11:18:46  lollisoft
 * Added interface set/get User and ApplicationName
 *
 * Revision 1.61  2005/05/04 22:09:38  lollisoft
 * Many memory leaks fixed. Changed _CL_LOG to _CL_VERBOSE.
 *
 * Revision 1.60  2005/05/03 21:15:49  lollisoft
 * Better memtrack support
 *
 * Revision 1.59  2005/05/01 21:26:15  lollisoft
 * Added informative filename to show when printing memory leaks.
 *
 * Thanks to the trmem code from Open Watcom.
 *
 * Revision 1.58  2005/05/01 01:12:35  lollisoft
 * Found a really big memory leak. It happens due to missing setup of ref variable
 * in lbFunctorEntity class of lbModule.cpp.
 *
 * Due to the fact, that I use this class for each instance retrival, it wasted
 * much memory. More: See documentation in that class.
 *
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
//#include <lbInterfaces.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX

#ifdef __cplusplus
extern "C" {      
#endif            

//#include <conio.h>

#ifdef __cplusplus
}      
#endif            

#endif

#include <lbConfigHook.h>

#include <lbmetaapp-module.h>

#include <lbMetaApplication.h>
/*...e*/

/*...sFunctors:0:*/
IMPLEMENT_FUNCTOR(instanceOfEventMapper, lb_EventMapper)
IMPLEMENT_FUNCTOR(instanceOfEvHandler, lb_EvHandler)

/// \todo Check if these OS differences are really needed.

#ifdef WINDOWS
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)
#endif
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfEventManager, lb_EventManager)
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfDispatcher, lb_Dispatcher)
#ifdef LINUX
IMPLEMENT_SINGLETON_FUNCTOR(instanceOfMetaApplication, lb_MetaApplication)
#endif

/*...e*/

/*...slb_MetaApplication:0:*/
/*...sctors\47\dtors:0:*/
lb_MetaApplication::lb_MetaApplication() {
	ref = STARTREF;
	gui = NULL;
	moduleName = NULL;

	_autoload = true;
	_autoselect = false;
	_autorefresh = false;
	
	_CL_LOG << "lb_MetaApplication::lb_MetaApplication() called." LOG_
}

lb_MetaApplication::~lb_MetaApplication() {
	_CL_LOG << "lb_MetaApplication::~lb_MetaApplication() called." LOG_
	
	lbErrCodes err = ERR_NONE;

	/*
	 * There must be an unload process of the loaded application's, so that it
	 * will not unloaded in the wrong order when unHookAll is called.
	 *
	 *
	 * Destroy loaded object and manually unload the corresponding module.
	 */

	if (app != NULL) {
		app--;
		app.resetPtr();
	}
	
	_CL_LOG << "Unload module " << moduleName << "." LOG_

	if (moduleName) lbUnloadModule(moduleName);
	
	_CL_LOG << "Unloaded module." LOG_	
	
	free(moduleName);
}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	disp->addEventHandlerFn(this, (lbEvHandler) &lb_MetaApplication::doAutoload, "doAutoload");

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
	_CL_LOG << "lb_MetaApplication::lbEvHandler1() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbEvHandler2\40\lb_I_Unknown\42\ uk\41\ \47\\47\ Show a simple message box:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbEvHandler2(lb_I_Unknown* uk) {

	if (gui != NULL) {
	        gui->msgBox("Information", "The main module of this application is a DLL and creates a basic functionality.\nThe real application will be loaded from configuraton and then the control\nwill be delegated to it.");
	} else {
	        COUT << "lb_MetaApplication::lbEvHandler2() called in console mode" << ENDL;
	}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\lbButtonTestHandler\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::lbButtonTestHandler(lb_I_Unknown* uk) {

        if (gui != NULL) {
                gui->msgBox("Information", "Test button has been pressed");
        } else {
                COUT << "lb_MetaApplication::lbButtonTestHandler() called in console mode" << ENDL;
        }

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getLoginData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getLoginData(lb_I_Unknown* uk) {

        if (gui != NULL) {
                UAP(lb_I_Form, loginForm)

                loginForm = gui->createLoginForm();
        } else {
                COUT << "Login form on console not supported" << ENDL;
        }

	return ERR_NONE;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::doAutoload(lb_I_Unknown* uk) {
	_autoload = !_autoload;
	
	return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_MetaApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_MetaApplication::setData() has not been implemented" LOG_
	
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
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getUserName\40\lb_I_String\42\\42\ user\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getUserName(lb_I_String** user) {
	if (LogonUser == NULL) (*user)->setData("");
	else (*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\getApplicationName\40\lb_I_String\42\\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::getApplicationName(lb_I_String** app) {
	if (LogonApplication == NULL) (*app)->setData("");
	else (*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setUserName\40\char\42\ user\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setUserName(char* user) {
	if ((user == NULL) || strcmp(user, "") == 0) return ERR_NONE;
	 
	if (LogonUser == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\setApplicationName\40\char\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::setApplicationName(char* app) {
	if ((app == NULL) || strcmp(app, "") == 0) return ERR_NONE;

	if (LogonApplication == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager \42\ lb_MetaApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager * lb_MetaApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\Initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
/// \todo Implement autologon settings for last user.
lbErrCodes LB_STDCALL lb_MetaApplication::initialize(char* user, char* appName) {
	lbErrCodes err = ERR_NONE;
/*...sdoc:8:*/
	/**
	* At this point should be found the real application. The real one
	 * may be defined by an environment variable, that is defined out of
	 * a batch file.
	 * The variable contains the name of the application, where a xml tag
	 * resolves the functor for this application.
	 */
/*...e*/
	
	if (user == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonUser)
			LogonUser->setData(user);
		}
	
	if (appName == NULL) {
		_CL_LOG << "lb_MetaApplication::Initialize() appName is NULL" LOG_
	} else
		if (LogonApplication == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
			LogonApplication->setData(appName);
		}
	
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
	int doAutoload;
/*...e*/
	
/*...sget the event manager:8:*/
	/**
		* Registrieren eines Events, der auch auf der GUI Seite bekannt ist.
	 */
	
	lb_I_Module* m = *&manager;
	REQUEST(m, lb_I_EventManager, eman)
/*...e*/
		
/*...sregister some basic events \40\getBasicApplicationInfo\46\\46\\46\\41\ by the event manager:8:*/
		eman->registerEvent("doAutoload", doAutoload);
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
	
	char* temp1 = _trans("&Autoload application\tCtrl-A");
	
	char* mm1 = (char*) malloc(strlen(temp1)+1);
	mm1[0] = 0;
	strcpy(mm1, temp1);
	
	addMenuEntryCheckable(_trans("&Edit"), mm1, "doAutoload", "");
	
	free(mm1);
	
	if (getenv("TARGET_APPLICATION") != NULL) {
		loadApplication("", "");
	}
	
	addMenuBar(_trans("&Help"));
	
	if (getenv("TARGET_APPLICATION") == NULL) {
		char* temp = _trans("&Login\tCtrl-L");
		char* login = (char*) malloc(strlen(temp)+1);
		login[0] = 0;
		strcpy(login, temp);
		
		addMenuEntry(_trans("&File"), login, "getLoginData", "");
		free(login);
	}
	
	char* temp = _trans("MainModule&Info\tCtrl-I");
	
	char* mm = (char*) malloc(strlen(temp)+1);
	mm[0] = 0;
	strcpy(mm, temp);
	
	addMenuEntry(_trans("&Help"), mm, "getMainModuleInfo", "");
	free(mm);
	
	_CL_LOG << "Load properties from file..." LOG_
		
		REQUEST(manager.getPtr(), lb_I_Parameter, myProperties)
		
		// Get the plugin to read a standard stream based file
		
		UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
		
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)
		
		pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");
	
	if (pl != NULL) {
		_CL_LOG << "Try to get an implementation." LOG_
		ukPl = pl->getImplementation();

		if (ukPl != NULL) {
		UAP(lb_I_FileOperation, fOp)
			QI(ukPl, lb_I_FileOperation, fOp)
			
			if (!fOp->begin("MetaApp.mad")) {
				// No file. Try write a default file.
				
				_CL_LOG << "No configuration file available. Write one." LOG_
				
				UAP(lb_I_Plugin, pl1)
				UAP(lb_I_Unknown, ukPl1)
				
				pl1 = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");
				ukPl1 = pl1->getImplementation();
				
				UAP(lb_I_FileOperation, fOp1)
					QI(ukPl1, lb_I_FileOperation, fOp1)
					
					if (!fOp1->begin("MetaApp.mad")) {
						_CL_LOG << "ERROR: Could not write default file for meta application!" LOG_		
						
						return ERR_FILE_WRITE_DEFAULT;
					}
				
				UAP(lb_I_Unknown, ukAcceptor1)
					QI(this, lb_I_Unknown, ukAcceptor1)
					ukAcceptor1->accept(*&fOp1);
				
				fOp1->end();		
				
				if (!fOp->begin("MetaApp.mad")) {
					_CL_LOG << "FATAL: Re read just written default file failed!" LOG_
					return ERR_FILE_READ_DEFAULT;
				}
			}
		
		// Do it as I didn't know the type of my project.
		UAP(lb_I_Unknown, ukAcceptor)
			QI(this, lb_I_Unknown, ukAcceptor)
			ukAcceptor->accept(*&fOp);
		
		fOp->end();
		} else {
			_CL_LOG << "Error: Could not load stream operator classes!" LOG_
		}
	} else {
		_CL_LOG << "Error: Could not load stream operator classes!" LOG_
	}
	
	if (getAutoload() && (LogonUser != NULL) && (LogonApplication != NULL)) {
		if ((strcmp(LogonUser->charrep(), "") != 0) && (strcmp(LogonApplication->charrep(), "") != 0)) {
			_CL_LOG << "Autoload is active and have " << LogonApplication->charrep() << 
			" and " << LogonUser->charrep() << ". Loading..." LOG_
			
			/* loadApplication() does not know, that the parameters are from it self.
			Thus LogonApplication->setData(...) and LogonUser->setData(...) would
			delete it's content.
			
			This is tricky.
			*/ 
			
			char* a = strdup(LogonApplication->charrep());
			char* u = strdup(LogonUser->charrep());
			
			loadApplication(u, a);
			
			free(a);
			free(u);
			
		}
	}
	
	if (getAutoload()) 
		toggleEvent("doAutoload");
	
	
	_CL_LOG << "Loaded properties from file." LOG_
		
		return ERR_NONE;
}
/*...e*/

void	   LB_STDCALL lb_MetaApplication::setGUIMaximized(bool b) {
	_GUIMaximized = b;
}

bool	   LB_STDCALL lb_MetaApplication::getGUIMaximized() {
	return _GUIMaximized;
}

void       LB_STDCALL lb_MetaApplication::setAutoload(bool b) {
	_autoload = b;
}

void       LB_STDCALL lb_MetaApplication::setAutorefreshData(bool b) {
	_autorefresh = b;
}

void       LB_STDCALL lb_MetaApplication::setAutoselect(bool b) {
	_autoselect = b;
}

bool       LB_STDCALL lb_MetaApplication::getAutoload() {
	return _autoload;
}

bool       LB_STDCALL lb_MetaApplication::getAutorefreshData() {
	return _autorefresh;
}

bool       LB_STDCALL lb_MetaApplication::getAutoselect() {
	return _autoselect;
}

lbErrCodes LB_STDCALL lb_MetaApplication::propertyChanged(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Parameter, param)
	QI(uk, lb_I_Parameter, param)
	
	if (param != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP_REQUEST(manager.getPtr(), lb_I_String, parameterName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		
		UAP(lb_I_KeyBase, key)
		
		name->setData("name");
		param->getUAPString(*&name, *&parameterName);
		
		name->setData("value");
		param->getUAPString(*&name, *&value);
		
		QI(parameterName, lb_I_KeyBase, key)
		
		if (strcmp(key->charrep(), "GeneralAutorefresh updated data") == 0) {
				if (strcmp(value->charrep(), "1") == 0) {
					setAutorefreshData(true);
				} else {
					setAutorefreshData(false);
				}
		}
		
		if (strcmp(key->charrep(), "GeneralAutoselect last application") == 0) {
				if (strcmp(value->charrep(), "1") == 0) {
					setAutoselect(true);
				} else {
					setAutoselect(false);
				}
		}
		
		if (strcmp(key->charrep(), "GeneralAutoopen last application") == 0) {
				if (strcmp(value->charrep(), "1") == 0) {
					setAutoload(true);
				} else {
					setAutoload(false);
				}
				toggleEvent("doAutoload");
		}
		
		
	} else {
		_LOG << "ERROR: Could not decode parameter structure!" LOG_
	}
	
	return err;
}

lb_I_Parameter* LB_STDCALL lb_MetaApplication::getParameter() {
	// Build up a preferences object and pass it to the property view
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	
	// General parameters for this application
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramGeneral)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameterGeneral)
	UAP_REQUEST(manager.getPtr(), lb_I_String, valueGeneral)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Boolean, b)


	parameter->setData("General");
	//--------------------------------------------------------
	parameterGeneral->setData("Autoselect last application");
	b->setData(_autoselect);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);
	
	parameterGeneral->setData("Autorefresh updated data");
	b->setData(_autorefresh);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);
	
	parameterGeneral->setData("Autoopen last application");
	b->setData(_autoload);
	paramGeneral->setUAPBoolean(*&parameterGeneral, *&b);

	registerPropertyChangeEventGroup(parameter->charrep(), *&paramGeneral, this, (lbEvHandler) &lb_MetaApplication::propertyChanged);
	
	param->setUAPParameter(*&parameter, *&paramGeneral);
	//--------------------------------------------------------
	param++;

	return param.getPtr();
}


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

lbErrCodes LB_STDCALL lb_MetaApplication::unloadApplication() {
	if (app != NULL) {
		app->uninitialize();
		app--;
		app.resetPtr();
	}
	
	return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\loadApplication\40\char\42\ user\44\ char\42\ app\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::loadApplication(char* user, char* application) {
	lbErrCodes err = ERR_NONE;

        if (user == NULL) {
                _CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
        } else
        if (LogonUser == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonUser)
        }

        LogonUser->setData(user);

        if (application == NULL) {
                _CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
        } else
        if (LogonApplication == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
        }

        LogonApplication->setData(application);


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
		UAP(lb_I_Query, sampleQuery)

		database->init();

		if (database->connect("lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE) {
			_LOG << "Error: Connection to database failed." LOG_
			return ERR_NONE;
		} else {
			
			sampleQuery = database->getQuery(0);
			
			char buffer[1000] = "";
			
			sprintf(buffer,
					"select Anwendungen.modulename, Anwendungen.functor, Anwendungen.interface from Anwendungen inner join User_Anwendungen on "
					"Anwendungen.id = User_Anwendungen.anwendungenid "
					"inner join Users on User_Anwendungen.userid = Users.id where "
					"Users.userid = '%s' and Anwendungen.name = '%s'"
					, LogonUser->charrep(), LogonApplication->charrep());
			
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
				
		        applicationName = (char*) malloc(strlen(ModuleName->charrep())+1);
		        applicationName[0] = 0;
				strcpy(applicationName, ModuleName->charrep());		        
				
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
				
			} else {
				_CL_LOG << "Error: Query to get application data failed. '" << buffer << "'" LOG_
			}
			
			
			UAP(lb_I_Unknown, a)
				
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
			manager->preload(appl);
			manager->makeInstance(f, appl, &a);
#endif
#ifdef LINUX
			strcat(appl, ".so");		
			manager->preload(appl);
			manager->makeInstance(f, appl, &a);
#endif
			if (a == NULL) {
				_CL_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
				return ERR_NONE;
			}
			
			if (moduleName == NULL) {
				moduleName = (char*) malloc(strlen(appl)+1);
				moduleName[0] = 0;
				strcpy(moduleName, appl);
			} else {
				_CL_LOG << "ERROR: Multiple applications not yet supported." LOG_
			}
			
			a->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
			
			QI(a, lb_I_Application, app)
				
            //if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_
				
			app->setGUI(gui);
			app->initialize(user, application);
			
			_CL_LOG << "Meta application has " << app->getRefCount() << " references." LOG_
				
			free(applicationName);
		}

                //if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
	} else {

		UAP(lb_I_Unknown, a)

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
		manager->preload(applicationName);
		manager->makeInstance(PREFIX "instanceOfApplication", applicationName, &a);
		#endif
		#ifdef LINUX
		char name[80] = "";
		strcpy(name, applicationName);
		strcat(name, ".so");
		manager->preload(name);
		manager->makeInstance(PREFIX "instanceOfApplication", name, &a);
		#endif	
		if (a == NULL) {
			_CL_LOG << "ERROR: Application could not be loaded - either not found or not configured." LOG_
			return ERR_NONE;
		}
		
		QI(a, lb_I_MetaApplication, app)

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher is NULL" LOG_

		app->setGUI(gui);
		app->initialize();

		_CL_LOG << "Meta application has " << app->getRefCount() << " references." LOG_

		if (dispatcher.getPtr() == NULL) _LOG << "Error: dispatcher has been set to NULL" LOG_
	}

        return ERR_NONE;
}
/*...e*/

/*...sBasic functions to be used for a UI application:0:*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenuBar\40\char\42\ name\44\ char\42\ after\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuBar(char* name, char* after) {
	lbErrCodes err = ERR_NONE;

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


	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("AddMenuBar", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_MetaApplication\58\\58\addMenu\40\char\42\ name\41\:0:*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenu(char* name) {
	return ERR_NONE;
}
/*...e*/
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

        UAP(lb_I_Unknown, uk)
        QI(param, lb_I_Unknown, uk)

        UAP_REQUEST(manager.getPtr(), lb_I_String, result)
        UAP(lb_I_Unknown, uk_result)
        QI(result, lb_I_Unknown, uk_result)

        dispatcher->dispatch("AddTextField", uk.getPtr(), &uk_result);

        return err;
}
/*...e*/
/*...sbool LB_STDCALL lb_MetaApplication\58\\58\askYesNo\40\char\42\ msg\41\:0:*/
bool LB_STDCALL lb_MetaApplication::askYesNo(char* msg) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)


	parameter->setData("msg");
	value->setData(msg);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("askYesNo", uk.getPtr(), &uk_result);

	// Got a name of the file. Create an input stream.
	
	parameter->setData("result");
	param->getUAPString(*&parameter, *&value);
	
	if (strcmp(value->charrep(), "yes") == 0) return true;
	return false;
}
/*...e*/
lb_I_InputStream* LB_STDCALL lb_MetaApplication::askOpenFileReadStream(char* extentions) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)


	parameter->setData("extention");
	value->setData(extentions);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("askOpenFileReadStream", uk.getPtr(), &uk_result);

	// Got a name of the file. Create an input stream.
	
	parameter->setData("result");
	param->getUAPString(*&parameter, *&value);

	if (strcmp(value->charrep(), "") == 0) return NULL;
	
	_CL_LOG << "Got a file name: " << value->charrep() << "." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_InputStream, s)
	s++;
	s->setFileName(value->charrep());

	return s.getPtr();
}


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

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
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

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("AddButton", uk.getPtr(), &uk_result);

	return err;
}
/*...e*/

lbErrCodes LB_STDCALL lb_MetaApplication::enableEvent(char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	
	
	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("enableEvent", uk.getPtr(), &uk_result);

	return err;
}

lbErrCodes LB_STDCALL lb_MetaApplication::disableEvent(char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	
	
	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("disableEvent", uk.getPtr(), &uk_result);

	return err;
}

lbErrCodes LB_STDCALL lb_MetaApplication::toggleEvent(char* name) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_String, value)
	
	
	parameter->setData("handlername");
	value->setData(name);
	param->setUAPString(*&parameter, *&value);

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)
	
	dispatcher->dispatch("toggleEvent", uk.getPtr(), &uk_result);

	return err;
}

lbErrCodes LB_STDCALL lb_MetaApplication::showPropertyPanel(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Unknown, uk)
	QI(params, lb_I_Unknown, uk)

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("ShowPropertyPanel", uk.getPtr(), &uk_result);

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lb_MetaApplication::registerPropertyChangeEventGroup(char* name, lb_I_Parameter* params, lb_I_EventHandler* target, lbEvHandler handler) {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Container, properties)
	
	properties = params->getParameterList();
	
	int temp;
	
	for (int i = 1; i <= properties->Count(); i++) {
		UAP(lb_I_KeyBase, key)
		UAP_REQUEST(manager.getPtr(), lb_I_String, eventName)
		
		key = properties->getKeyAt(i);
		
		*eventName = name;
		*eventName += key->charrep();
		
		eman->registerEvent(eventName->charrep(), temp);
		dispatcher->addEventHandlerFn(target, handler, eventName->charrep());
	}
	
	return err;
}


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

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);
	

	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lb_MetaApplication::addMenuEntryCheckable(char* in_menu, char* entry, char* evHandler, char* afterentry) {
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

	parameter->setData("checkable");
	value->setData("yes");
	param->setUAPString(*&parameter, *&value);
	
	if (afterentry && (strcmp(afterentry, "") != 0)) {
		parameter->setData("after");
		value->setData(afterentry);
		param->setUAPString(*&parameter, *&value);
	}

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(manager.getPtr(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	dispatcher->dispatch("AddMenuEntry", uk.getPtr(), &uk_result);
	

	return ERR_NONE;

}
/*...e*/
/*...e*/
/*...slb_EventMapper:0:*/
lb_EventMapper::lb_EventMapper() {
	ref = STARTREF;
	_CL_LOG << "Instance of lb_I_EventMapper created" LOG_
	_name = NULL;
}

lb_EventMapper::~lb_EventMapper() {
}




BEGIN_IMPLEMENT_LB_UNKNOWN(lb_EventMapper)
	ADD_INTERFACE(lb_I_EventMapper)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lb_EventMapper::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_EventMapper::setData() has not been implemented" LOG_
	
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
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_EventManager)
	ADD_INTERFACE(lb_I_EventManager)
END_IMPLEMENT_LB_UNKNOWN()

lb_EventManager::lb_EventManager() {
	maxEvId = 0;
	ref = STARTREF;
}

lb_EventManager::~lb_EventManager() {
	_CL_LOG << "lb_EventManager::~lb_EventManager() called." LOG_
}
	
lbErrCodes LB_STDCALL lb_EventManager::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_EventManager::setData() has not been implemented" LOG_
	
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
	
	UAP(lb_I_KeyBase, sk)
	QI(stringData, lb_I_Unknown, sk)
/*...e*/
	
/*...sError handling:8:*/
	if (events == NULL) _CL_LOG << "Nullpointer detected (events)!" LOG_
	if (*&sk == NULL) _CL_LOG << "Nullpointer detected (sk)!" LOG_
	if (events->exists(&sk) == 1) {
		_CL_LOG << "lb_EventManager::registerEvent(): Error: Event schon registriert" LOG_
		return ERR_EVENT_EXISTS;
	}
/*...e*/
/*...sdetermine id:8:*/
	if (freeIds->Count() == 0) {
		maxEvId++;
	} else {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)

		key = freeIds->getKeyAt(freeIds->Count());
		uk = freeIds->getElementAt(freeIds->Count());
		
		freeIds->remove(&key);
			
		UAP(lb_I_Integer, i)
		QI(uk, lb_I_Integer, i)

		newId = i->getData();
	}
/*...e*/
/*...sinsert new event:8:*/
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, integerData)
	integerData->setData(maxEvId);
	
	UAP(lb_I_Unknown, idata)
	QI(integerData, lb_I_Unknown, idata)

	events->insert(&idata, &sk);
	
	UAP(lb_I_KeyBase, ik)
	QI(integerData, lb_I_Unknown, ik)

	UAP(lb_I_Unknown, sdata)
	QI(stringData, lb_I_Unknown, sdata)
	
	reverse_events->insert(&sdata, &ik);
	
	EvNr = maxEvId;
/*...e*/

	if (events->exists(&sk) != 1) {
		_CL_LOG << "lb_EventManager::registerEvent(): Error: Event could not be registered" LOG_
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
	
	UAP(lb_I_KeyBase, kk)
	QI(stringKey, lb_I_Unknown, kk)
/*...e*/

/*...sresolve event:8:*/
	if (events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object)
		UAP(lb_I_Integer, i)
		
		object = events->getElement(&kk);
		QI(object, lb_I_Integer, i)
		evNr = i->getData();
	} else {
		_CL_LOG << "Error: Event name not registered: " << EvName LOG_
		return ERR_EVENT_NOTREGISTERED;
	}
/*...e*/

	return ERR_NONE;
}

char* LB_STDCALL lb_EventManager::reverseEvent(int evNr) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, ID)
	//ID->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	ID->setData(evNr);
	
	UAP(lb_I_KeyBase, kk)
	QI(ID, lb_I_Unknown, kk)
	
	if (reverse_events->exists(&kk) == 1) {
		UAP(lb_I_Unknown, object)
		UAP(lb_I_String, str)
		
		object = reverse_events->getElement(&kk);
		QI(object, lb_I_String, str)
		static char result[100] = "";
		strcpy(result, str->getData());
		
		return result;
	} else {
		_CL_LOG << "Error: Event id not registered: " << evNr LOG_
		return "";
	}
}
/*...e*/
/*...slb_Dispatcher:0:*/
BEGIN_IMPLEMENT_SINGLETON_LB_UNKNOWN(lb_Dispatcher)
	ADD_INTERFACE(lb_I_Dispatcher)
END_IMPLEMENT_LB_UNKNOWN()

lb_Dispatcher::lb_Dispatcher() {
	ref = STARTREF;
}

lb_Dispatcher::~lb_Dispatcher() {
	_CL_LOG << "lb_Dispatcher::~lb_Dispatcher() called." LOG_
	
	if (evManager != NULL) _CL_LOG << "Event manager in dispatcher has " << evManager->getRefCount() << " references." LOG_
	if (dispatcher != NULL) _CL_LOG << "Dispatcher list has " << dispatcher->getRefCount() << " references." LOG_
}

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::setData(lb_I_Unknown* uk) {
	_CL_LOG << "lb_Dispatcher::setData() has not been implemented" LOG_
	
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
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delEventHandlerFn\40\lb_I_EventHandler\42\ evHandlerInstance\44\ lbEvHandler evHandler\44\ char\42\ EvName\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delEventHandlerFn(lb_I_EventHandler* evHandlerInstance, lbEvHandler evHandler, char* EvName) {
	/*
	 * Create an instance of a function pointer object
	 */
	
	int id = 0;
	evManager->resolveEvent(EvName, id);
	//addEventHandlerFn(evHandlerInstance, evHandler, id);	
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

	  UAP(lb_I_KeyBase, k)
	QI(i, lb_I_KeyBase, k)

	    UAP(lb_I_Unknown, e)
	QI(evH, lb_I_Unknown, e)
	if (dispatcher->exists(&k) == 1) {
        	dispatcher->remove(&k);
	}

	if ((err = dispatcher->insert(&e, &k)) != ERR_NONE) _CL_LOG << "Error: Inserting new container element failed" LOG_

	UAP(lb_I_Unknown, uk)

	uk = dispatcher->getElement(&k);
	
	if (uk == NULL) _CL_LOG << "Error: Adding event handler failed (not stored)" LOG_

	return ERR_NONE;
}
/*...e*/

/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\addDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::addDispatcher(lb_I_Dispatcher* disp) {
	_CL_LOG << "lb_Dispatcher::addDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\delDispatcher\40\lb_I_Dispatcher\42\ disp\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::delDispatcher(lb_I_Dispatcher* disp) {
	_CL_LOG << "lb_Dispatcher::delDispatcher() called" LOG_
	return ERR_NONE;
}
/*...e*/
/*...slb_I_DispatchResponce\42\ lb_Dispatcher\58\\58\dispatch\40\lb_I_DispatchRequest\42\ req\41\:0:*/
lb_I_DispatchResponse* lb_Dispatcher::dispatch(lb_I_DispatchRequest* req) {
	_CL_LOG << "lb_Dispatcher::dispatch() called" LOG_
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lb_Dispatcher\58\\58\dispatch\40\int EvNr\44\ lb_I_Unknown\42\ EvData\44\ lb_I_Unknown\42\\42\ EvResult\41\:0:*/
lbErrCodes LB_STDCALL lb_Dispatcher::dispatch(int EvNr, lb_I_Unknown* EvData, lb_I_Unknown** EvResult) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
	i->setData(EvNr);
	
	UAP(lb_I_KeyBase, ik)
	QI(i, lb_I_KeyBase, ik)
	
	
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_EvHandler, ev)
	
	if (dispatcher == NULL) {
		_CL_LOG << "Error: Have no dispatcher" LOG_
	} else {
	
		uk = dispatcher->getElement(&ik);
	
		if (uk == NULL) {
			_CL_LOG << "Error: Could not get the handler from the id" LOG_
			return ERR_DISPATCH_FAILS;
		}
	
		QI(uk, lb_I_EvHandler, ev)

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
	
	UAP(lb_I_EvHandler, eh)
	QI(uk, lb_I_EvHandler, eh)
	
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

#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

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
                        if (situation) _CL_VERBOSE << "DLL released by system." LOG_
                        else           _CL_VERBOSE << "DLL released by program.\n" LOG_
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

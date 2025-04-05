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


class UIWrapper : public lb_I_Application,
public lb_I_EventHandler
{
public:
	UIWrapper();
	virtual ~UIWrapper();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);

    lbErrCodes LB_STDCALL save();
    lbErrCodes LB_STDCALL load();

	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	virtual lbErrCodes LB_STDCALL initialize(const char* user = NULL, const char* app = NULL);
	virtual lbErrCodes LB_STDCALL uninitialize();
	virtual lbErrCodes LB_STDCALL run();
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	virtual lbErrCodes LB_STDCALL setUserName(const char* user);
	virtual lbErrCodes LB_STDCALL setApplicationName(const char* app);

	virtual lb_I_EventManager* LB_STDCALL getEVManager( void );

	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	lb_I_Unknown* LB_STDCALL getUnknown();


	lbErrCodes LB_STDCALL askYesNo(lb_I_Unknown* uk);

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(UIWrapper)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

// Does import, but is executable
//IMPLEMENT_FUNCTOR(instanceOfApplication, UIWrapper)

UIWrapper::UIWrapper() {
	
	gui = NULL;
	printf("Instance of lb_I_Application created\n");
	_LOG << "Instance of lb_I_Application created" LOG_
}

UIWrapper::~UIWrapper() {
	_LOG << "Instance of lb_I_Application destroyed" LOG_
}


lbErrCodes LB_STDCALL UIWrapper::askYesNo(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev_manager)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)

	UAP(lb_I_Parameter, param)

	QI(uk, lb_I_Parameter, param)

	parameter->setData("msg");
	param->getUAPString(*&parameter, *&msg);

	COUT << msg->charrep();

	char c = ' ';

    setvbuf(stdin, &c, _IONBF, 1);
    while ( c != 'y' &&
            c != 'Y' &&
            c != 'n' &&
            c != 'N') {
        fread(&c, 1, 1, stdin);
    }


    switch (c) {
        case 'y':
        case 'Y':
            parameter->setData("result");
            result->setData("yes");
            param->setUAPString(*&parameter, *&result);
            break;
        default:
            parameter->setData("result");
            result->setData("no");
            param->setUAPString(*&parameter, *&result);
    }

    COUT << ENDL;

	return err;
}

lbErrCodes LB_STDCALL UIWrapper::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &UIWrapper::askYesNo, "askYesNo");

	return ERR_NONE;
}

lb_I_Unknown* LB_STDCALL UIWrapper::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__);
	uk++;
	return uk.getPtr();
}

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setData(lb_I_Unknown* uk) {
	_LOG << "lbApplication::setData() has not been implemented" LOG_

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager\42\ LB_STDCALL lbApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL UIWrapper::getEVManager( void ) {
	return NULL;
}
/*...e*/

lbErrCodes LB_STDCALL UIWrapper::save() {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::load() {
    return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::uninitialize() {
	return ERR_NONE;
}
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL UIWrapper::initialize(const char* user, const char* app) {

	// To be implemented in a separate application module

	int askYesNo;

	// Get the event manager

	printf("Get an event manager\n");
	REQUEST(getModuleInstance(), lb_I_EventManager, eman)


	if (user == NULL) {
	        _CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
	        REQUEST(getModuleInstance(), lb_I_String, LogonUser)
	        LogonUser->setData(user);
	}

	if (app == NULL) {
	        _CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
	} else
	if (LogonApplication == NULL) {
	        REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
	        LogonApplication->setData(app);
	}

	eman->registerEvent("askYesNo", askYesNo);

	REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());

	registerEventHandler(dispatcher.getPtr());

	return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL UIWrapper::getUserName(lb_I_String** user) {
	(*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::getApplicationName(lb_I_String** app) {
	(*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL UIWrapper::setUserName(const char* user) {
	if (LogonUser == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL UIWrapper::setApplicationName(const char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(getModuleInstance(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


lbErrCodes LB_STDCALL UIWrapper::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);
#endif
	return ERR_NONE;
}

#ifdef TEST_CONSOLE_KEYINPUT
int main(int argc, char *argv[]) {

    char c;

    setvbuf(stdin, &c, _IONBF, 1);
    while ( c != 'y' &&
            c != 'Y' &&
            c != 'n' &&
            c != 'N') {
        cout << 0x10;
        cout << "Druecke eine Taste: ";
        fread(&c, 1, 1, stdin);
    }
    cout << endl << "Taste: '" << c << "'" << endl;

    setvbuf(stdin, &c, _IONBF, 1);

    c = ' ';

    while ( c != 'y' &&
            c != 'Y' &&
            c != 'n' &&
            c != 'N') {
        cout << 0x10;
        cout << "Druecke eine Taste: ";
        fread(&c, 1, 1, stdin);
    }

    cout << endl << "Taste: '" << c << "'" << endl;

    return 0;
}
#endif
#ifndef TEST_CONSOLE_KEYINPUT
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

		UIWrapper* myUIWrapper = new UIWrapper();
		

        myUIWrapper->initialize();

		meta->load();

		meta->initialize();

		// Need to issue some events to simulate user actions

		meta->login("user", "TestUser");

		UAP(lb_I_Container, applications)

		applications = meta->getApplications();

		if (!meta->getAutoload()) meta->loadApplication("user", "lbDMF Manager");

		// Setup the configuration that is needed for this test

        UAP_REQUEST(getModuleInstance(), lb_I_String, path)
        UAP_REQUEST(getModuleInstance(), lb_I_String, File)

		*path = getenv("DEVROOT");



		#ifdef WINDOWS
		*File = path->charrep();
		*File += "\\Projects\\CPP\\AppDevelopment\\XSLT_Templates\\XMIToDMF\\";
		*File += "XMISettings.xsl";
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", File->charrep());
		*File = path->charrep();
		*File += "\\Projects\\CPP\\AppDevelopment\\XSLT_Templates\\XMIToDMF\\";
		*File += "importUML-SystemDB.xsl";
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", File->charrep());
		*File = path->charrep();
		*File += "\\Projects\\CPP\\AppDevelopment\\XSLT_Templates\\XMIToDMF\\";
		*File += "importUML-ApplicationDB.xsl";
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", File->charrep());
		*File = path->charrep();
		*File += "\\Projects\\CPP\\AppDevelopment\\DynamicApp\\ModelExchange\\PostbooksUML2.xmi";
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", File->charrep());
		#endif

		#ifdef LINUX
		meta->firePropertyChangeEvent("UML import settingsXSL file for import settings", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/XMISettings.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for system database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-SystemDB.xsl");
		meta->firePropertyChangeEvent("UML import settingsXSL file for application database", "../../../AppDevelopment/XSLT_Templates/XMIToDMF/importUML-ApplicationDB.xsl");
		meta->firePropertyChangeEvent("lbDMF Manager Import DefinitionsXMI UML input file", "../../../AppDevelopment/DynamicApp/ModelExchange/PostbooksUML2.xmi");
		#endif

		// Simulate menu click
		meta->fireEvent("importUMLXMIDocIntoApplication");

		meta->unloadApplication();

		meta->uninitialize();

		PM->unload();
	}

	unHookAll();

	return 0;
}

#endif

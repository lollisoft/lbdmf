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

#include <conio.h>

#ifdef __cplusplus
}
#endif

#endif

#include <lbConfigHook.h>

/*...sLB_APP_DLL scope:0:*/
#define LB_APP_DLL
#include <lbapp-module.h>
/*...e*/

#include <Application.h>
/*...e*/
/*...sclass lb_Application:0:*/
class lbApplication :
public lb_I_Application,
public lb_I_EventHandler
{
public:
        lbApplication();
        virtual ~lbApplication();

        DECLARE_LB_UNKNOWN()

        virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);

    lbErrCodes LB_STDCALL save();
    lbErrCodes LB_STDCALL load();

        /**
         * Let the implementation register it's symbolic events.
         * For each event, it gets an numeric identifer so it may
         * be able to dispatch that events.
         */
        virtual lbErrCodes LB_STDCALL initialize(char* user = NULL, char* app = NULL);
        virtual lbErrCodes LB_STDCALL uninitialize();
        virtual lbErrCodes LB_STDCALL run();
        virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
        virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
        virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
        virtual lbErrCodes LB_STDCALL setUserName(char* user);
        virtual lbErrCodes LB_STDCALL setApplicationName(char* app);

        virtual lb_I_EventManager* LB_STDCALL getEVManager( void );

        virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
        lb_I_Unknown* LB_STDCALL getUnknown();

        lbErrCodes LB_STDCALL getDynamicDBForm(lb_I_Unknown* uk);

        lbErrCodes LB_STDCALL getKundenDetails(lb_I_Unknown* uk);
        lbErrCodes LB_STDCALL getKundenListe(lb_I_Unknown* uk);

        lbErrCodes LB_STDCALL getLoginData(lb_I_Unknown* uk);

        lbErrCodes LB_STDCALL getCustomFormsConfig(lb_I_Unknown* uk);

protected:
        lb_I_GUI* gui;
        UAP(lb_I_EventManager, eman)
        UAP(lb_I_Dispatcher, dispatcher)
        UAP(lb_I_String, LogonUser)
        UAP(lb_I_String, LogonApplication)
};
/*...e*/
/*...slbApplication:0:*/
/*...sctors\47\dtors:0:*/
lbApplication::lbApplication() {
        ref = STARTREF;
        gui = NULL;
        printf("Instance of lb_I_Application created\n");
        _LOG << "Instance of lb_I_Application created" LOG_
}

lbApplication::~lbApplication() {
        _LOG << "Instance of lb_I_Application destroyed" LOG_
}
/*...e*/

lb_I_Unknown* LB_STDCALL lbApplication::getUnknown() {
        lb_I_Unknown* ukp;
        queryInterface("lb_I_Unknown", (void**) &ukp, __FILE__, __LINE__);
        return ukp;
}

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lbApplication::registerEventHandler(lb_I_Dispatcher* disp) {

//      disp->addEventHandlerFn(this, (lbEvHandler) &lbApplication::getLoginData, "getLoginData");

        disp->addEventHandlerFn(this, (lbEvHandler) &lbApplication::getKundenDetails, "getKundenDetails");
        disp->addEventHandlerFn(this, (lbEvHandler) &lbApplication::getKundenListe, "getKundenListe");

        // Register a dynamic formular creator

        disp->addEventHandlerFn(this, (lbEvHandler) &lbApplication::getDynamicDBForm, "getDynamicDBForm");

        return ERR_NONE;
}
/*...e*/

/*...sevent handlers\44\ that can be registered:0:*/
lbErrCodes LB_STDCALL lbApplication::getDynamicDBForm(lb_I_Unknown* uk) {
        if (gui != NULL) {
                UAP(lb_I_DatabaseForm, dbForm)

                /*
                        To get the data from the database, we do transmit only a few data by uk to this
                        function.

                        It would be only the form id it self. Additionally, we need to check the typ of the
                        formular to be really a DynamicDBForm.

                        If this is ok, we need to load the additional query from a foreign table for that
                        typ of form.

                        At best, this functionality is placed in a separate class.
                */


                char* lbDMFPasswd = getenv("lbDMFPasswd");
                char* lbDMFUser   = getenv("lbDMFUser");

                if (!lbDMFUser) lbDMFUser = "dba";
                if (!lbDMFPasswd) lbDMFPasswd = "trainres";


                dbForm = gui->createDBForm("<Load title from database>", "<Load SQL query from database>",
                "trainres", lbDMFUser, lbDMFPasswd);

                dbForm->show();
        } else {
                COUT << "KundenDetails" << ENDL;
        }

        return ERR_NONE;
}

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getLoginData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::getLoginData(lb_I_Unknown* uk) {

        if (gui != NULL) {
                UAP(lb_I_Form, loginForm)

                loginForm = gui->createLoginForm();
        } else {
                COUT << "Login form on console not supported" << ENDL;
        }

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getKundenDetails\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::getKundenDetails(lb_I_Unknown* uk) {
        _LOG << "lbApplication::getKundenDetails() called" LOG_

        if (gui != NULL) {
                UAP(lb_I_DatabaseForm, dbForm)

                dbForm = gui->createDBForm("Elemente in World", "select objecttyp, x, y, w, h from world order by id",
                "trainres", "dba", "trainres");

                dbForm->show();
        } else {
                COUT << "KundenDetails" << ENDL;
        }

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getKundenListe\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::getKundenListe(lb_I_Unknown* uk) {
        _LOG << "lbApplication::getKundenListe() called" LOG_

        if (gui != NULL) {
                UAP(lb_I_DatabaseForm, dbForm)

                dbForm = gui->createDBForm("Kunden", "select Firma, Name, Vorname, Strasse, Hausnummer, Ort, Plz, Vorwahl, Telefon from Kunden",
                "trainres", "dba", "trainres");

                dbForm->show();
        } else {
                COUT << "KundenDetails" << ENDL;
        }


        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getCustomFormsConfig\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::getCustomFormsConfig(lb_I_Unknown* uk) {

        if (gui != NULL) {
                UAP(lb_I_DatabaseForm, dbForm)

                dbForm = gui->createDBForm("Formulare", "select Name, MenuName, EventName, query from DBForms",
                "trainres", "dba", "trainres");

                dbForm->show();
        }

        return ERR_NONE;
}
/*...e*/
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplication)
        ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfApplication, lbApplication)

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::setData(lb_I_Unknown* uk) {
        _LOG << "lbApplication::setData() has not been implemented" LOG_

        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::setGUI(lb_I_GUI* _gui) {
        gui = _gui;
        return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::getGUI(lb_I_GUI** _gui) {
        *_gui = gui;
        return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager\42\ LB_STDCALL lbApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL lbApplication::getEVManager( void ) {
        return NULL;
}
/*...e*/

lbErrCodes LB_STDCALL lbApplication::save() {
    return ERR_NONE;
}

lbErrCodes LB_STDCALL lbApplication::load() {
    return ERR_NONE;
}


lbErrCodes LB_STDCALL lbApplication::uninitialize() {
        return ERR_NONE;
}
/*...slbErrCodes LB_STDCALL lbApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::initialize(char* user, char* app) {

        // To be implemented in a separate application module

        int getKundenDetails;
        int getKundenListe;
        int getLoginData;
        int unused;

        // Get the event manager

        lb_I_Module* m = *&manager;
        printf("Get an event manager\n");
        REQUEST(m, lb_I_EventManager, eman)


        if (user == NULL) {
                _CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
        } else
                if (LogonUser == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonUser)
                LogonUser->setData(user);
        }

        if (app == NULL) {
                _CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
        } else
        if (LogonApplication == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
                LogonApplication->setData(app);
        }

        // Register my handler identifers

        eman->registerEvent("getKundenDetails", getKundenDetails);
        eman->registerEvent("getKundenListe", getKundenListe);
        eman->registerEvent("getLoginData", getLoginData);

        eman->registerEvent("getDynamicDBForm", unused);

        // Attach to the dispatcher

        REQUEST(m, lb_I_Dispatcher, dispatcher)
        dispatcher->setEventManager(eman.getPtr());

        // Register my handlers to the dispatcher

        registerEventHandler(dispatcher.getPtr());

        // Step 3 (Load sub components, handling menus and else needed for an UI)

/*...ssome docs:8:*/
        /**
         * After initializion of all event handlers, we need to get up all
         * GUI accessible handlers - like menus or else.
         * This class, as an example, provides two handlers
         * getBasicApplicationInfo and getMainModuleInfo
         *
         * The handler depends on some capabilities:
         *
         *      1. A basic dialog to show text
         *              This may be a container of capabilities
         *               must:SimpleTextDialog
         *               optional:PictureElements
         *
         * It provides these capabilities:
         *
         *      1. An information about menu creation
         *              This may be a simple string - lb_I_String
         */


        /**
         * Init the application (menu, toolbar, accelerators)
         *
         * This will be done by the loaded application from the
         * environment variable (TARGET_APPLICATION)
         */
/*...e*/

        UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)

        metaapp->addMenuBar("Kunden", "Edit");
        metaapp->addMenuBar("Reservierungen", "Kunden");
        metaapp->addMenuBar("Bahnhoefe", "Reservierungen");


        //addMenuEntry("File", "Anmelden", "getLoginData", "");
        metaapp->addMenuEntry("Kunden", "Elemente in World", "getKundenDetails", "");
        metaapp->addMenuEntry("Kunden", "Kunden", "getKundenListe", "");


        return ERR_NONE;
}
/*...e*/
lbErrCodes LB_STDCALL lbApplication::getUserName(lb_I_String** user) {
        (*user)->setData(LogonUser->charrep());
        return ERR_NONE;
}

lbErrCodes LB_STDCALL lbApplication::getApplicationName(lb_I_String** app) {
        (*app)->setData(LogonApplication->charrep());
        return ERR_NONE;
}
lbErrCodes LB_STDCALL lbApplication::setUserName(char* user) {
        if (LogonUser == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonUser)
        }

        LogonUser->setData(user);
        return ERR_NONE;
}

lbErrCodes LB_STDCALL lbApplication::setApplicationName(char* app) {
        if (LogonApplication == NULL) {
                REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
        }

        LogonApplication->setData(app);
        return ERR_NONE;
}


// This starts the main application

/*...slbErrCodes LB_STDCALL lbApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lbApplication::run() {
#ifdef bla
        lb_I_Unknown* result;

        dispatcher->dispatch("AddMenu", NULL, &result);
#endif
        return ERR_NONE;
}
/*...e*/

/*...e*/


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                        TRMemOpen();
                        TRMemSetModuleName(__FILE__);

                        if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);

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
                        _CL_VERBOSE << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
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



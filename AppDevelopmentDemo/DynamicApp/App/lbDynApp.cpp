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

/*...sLB_DYNAPP_DLL scope:0:*/
#define LB_DYNAPP_DLL
#include <lbdynapp-module.h>
/*...e*/

#include <lbDynApp.h>
/*...e*/
/*...sclass lb_DynamicApplication:0:*/
class lbDynamicApplication : 
public lb_I_MetaApplication,
public lb_I_EventHandler
{
public:
	lbDynamicApplication();
	virtual ~lbDynamicApplication();

	DECLARE_LB_UNKNOWN()

	virtual lbErrCodes LB_STDCALL setGUI(lb_I_GUI* _gui);
	
	/**
	 * Let the implementation register it's symbolic events.
	 * For each event, it gets an numeric identifer so it may
	 * be able to dispatch that events.
	 */
	virtual lbErrCodes LB_STDCALL Initialize(char* user = NULL, char* app = NULL);
	virtual lbErrCodes LB_STDCALL run();
	virtual lbErrCodes LB_STDCALL getGUI(lb_I_GUI** _gui);
	virtual lbErrCodes LB_STDCALL getUserName(lb_I_String** user);
	virtual lbErrCodes LB_STDCALL getApplicationName(lb_I_String** app);
	virtual lbErrCodes LB_STDCALL setUserName(char* user);
	virtual lbErrCodes LB_STDCALL setApplicationName(char* app);
	
	virtual lb_I_EventManager * getEVManager( void );

	virtual lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);	

	/**
	 * \brief Unused here
	 */
	virtual lbErrCodes LB_STDCALL loadApplication(char* user, char* app);


	/**
	 * \brief The main handler to create dynamic forms
	 */
	lbErrCodes LB_STDCALL getDynamicDBForm(lb_I_Unknown* uk);

/*...sWrapper for some usual GUI functions:8:*/

	/* The menubar is still present in the demo. At the
	   first time, a new menubar should not be used.
	*/
	virtual lbErrCodes LB_STDCALL addMenuBar(char* name, char* after = NULL);

	/**
	 * Add a menu behind the last.
	 */
	virtual lbErrCodes LB_STDCALL addMenu(char* name);
	
	/**
	 * Add a menu entry in the named menu after given entry,
	 * if provided. The handler must be registered.
	 * 
	 * Input:
	 *	char* in_menu:		Which menu to add to (File/Edit/Help/...)
	 *	char* entry:		The text for that entry
	 *	char* evHandler:	The name of a registered event handler, that handle this
	 *	char* afterentry:	Insert the entry after an exsisting entry
	 */
	virtual lbErrCodes LB_STDCALL addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry = NULL);
	virtual lbErrCodes LB_STDCALL addButton(char* buttonText, char* evHandler, int x, int y, int w, int h);
	virtual lbErrCodes LB_STDCALL addLabel(char* text, int x, int y, int w, int h);
	virtual lbErrCodes LB_STDCALL addTextField(char* name, int x, int y, int w, int h);
/*...e*/

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman, __FILE__, __LINE__)
	UAP(lb_I_Dispatcher, dispatcher, __FILE__, __LINE__)
	UAP(lb_I_Database, database, __FILE__, __LINE__)
	
	UAP(lb_I_String, LogonUser, __FILE__, __LINE__)
	UAP(lb_I_String, LogonApplication, __FILE__, __LINE__)
		
	char hdsihd[100];
};
/*...e*/
/*...slbDynamicApplication:0:*/
/*...sctors\47\dtors:0:*/
lbDynamicApplication::lbDynamicApplication() {
	ref = STARTREF;
	gui = NULL;
}

lbDynamicApplication::~lbDynamicApplication() {
	_CL_LOG << "lbDynamicApplication::~lbDynamicApplication() called." LOG_
}
/*...e*/

/*...sregister event handlers:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::registerEventHandler(lb_I_Dispatcher* disp) {

	// Register a dynamic formular creator

// Done while initialiation
//	disp->addEventHandlerFn(this, (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, "getDynamicDBForm");

	return ERR_NONE;
}
/*...e*/

/*...sevent handlers\44\ that can be registered:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::getDynamicDBForm(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	if (gui != NULL) {
	        UAP(lb_I_DatabaseForm, dbForm, __FILE__, __LINE__)

/*...sDoc:16:*/
		/*
			To get the data from the database, we do transmit only a few data by uk to this
			function.
			
			It would be only the form id it self. Additionally, we need to check the typ of the
			formular to be really a DynamicDBForm.
			
			If this is ok, we need to load the additional query from a foreign table for that
			typ of form.
			
			At best, this functionality is placed in a separate class.
		*/
/*...e*/

		UAP(lb_I_Integer, eventID, __FILE__, __LINE__)
		UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)

		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		UAP_REQUEST(manager.getPtr(), lb_I_String, query)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formID)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formName)
		
		QI(uk, lb_I_Integer, eventID, __FILE__, __LINE__)

		// Retrieve the event name from their ID

		char* eventName = eman->reverseEvent(eventID->getData());

		if(database == NULL) {
			REQUEST(manager.getPtr(), lb_I_Database, database)
			database->init();

			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
		}
	
		sampleQuery = database->getQuery(0);	

		char* b =
		        "select Formulare.id, Formulare.name from Formulare inner join Anwendungen_Formulare on "
		        "Formulare.id = Anwendungen_Formulare.formularid "
		        "inner join Anwendungen on Anwendungen_Formulare.anwendungid = Anwendungen.id inner join "
		        "User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		        " User_Anwendungen.userid = Users.id where "
		        "Users.userid = '%s' and Anwendungen.name = '%s' and "
		        "Formulare.eventname = '%s'";

		char* buffer = (char*) malloc(strlen(b)+strlen(LogonUser->charrep())+strlen(LogonApplication->charrep())+strlen(eventName)+1);

		buffer[0] = 0;

		sprintf(buffer, b, LogonUser->charrep(), LogonApplication->charrep(), eventName);

		// Get the ID and Name of the intented formular

		_CL_LOG << "Logon user is: " << LogonUser->charrep() LOG_
		_CL_LOG << "Logon app is: " << LogonApplication->charrep() LOG_

		sampleQuery->query(buffer);
		
		err = sampleQuery->first();
		
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			formID = sampleQuery->getAsString(1);
			formName = sampleQuery->getAsString(2);
		}


		//- Internal formular implementation ------------------------------------------------

		b =
		"select Formular_Parameters.parametervalue from Formular_Parameters "
		"where Formular_Parameters.parametername = 'query' and "
		"Formular_Parameters.formularid = %s";
		
		free(buffer);
		
		buffer = (char*) malloc(strlen(b)+strlen(formID->charrep())+1);

		buffer[0] = 0;

		sprintf(buffer, b, formID->charrep());

		UAP(lb_I_Query, formularQuery, __FILE__, __LINE__)

		formularQuery = database->getQuery(0);
		
		// It is an internal formular and I don't distinguish between 
		// different formular implementations yet
		
		formularQuery->query(buffer);
		
		err = formularQuery->first();
		
		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
		        query = formularQuery->getAsString(1);
		}
		
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)
		
		b = 
			"select parametername, parametervalue from Anwendungs_Parameter inner join "
			"Anwendungen on Anwendungs_Parameter.anwendungid = Anwendungen.id where "
			"Anwendungen.name = '%s'";

		free(buffer);

		buffer = (char*) malloc(strlen(b)+strlen(LogonApplication->charrep())+1);

		buffer[0] = 0;
		
		sprintf(buffer, b, LogonApplication->charrep());

		UAP(lb_I_Query, DBConnQuery, __FILE__, __LINE__)

		DBConnQuery = database->getQuery(0);
		
		DBConnQuery->query(buffer);

		err = DBConnQuery->first();

		UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

		if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			parameter = DBConnQuery->getAsString(1);
		
			if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
			if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
			if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
			
			err = DBConnQuery->next();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				parameter = DBConnQuery->getAsString(1);
				if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
				if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
				if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
			} else {
				_LOG << "Fehler: Konnte DBUser nicht auslesen" LOG_
			}
			
			err = DBConnQuery->next();
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				parameter = DBConnQuery->getAsString(1);
				if (strcmp(parameter->charrep(), "DBName") == 0) DBName = DBConnQuery->getAsString(2);
				if (strcmp(parameter->charrep(), "DBUser") == 0) DBUser = DBConnQuery->getAsString(2);
				if (strcmp(parameter->charrep(), "DBPass") == 0) DBPass = DBConnQuery->getAsString(2);
			} else {
				_LOG << "Fehler: Konnte DBPass nicht auslesen" LOG_
			}
		
		}		

	        dbForm = gui->createDBForm(formName->charrep(), query->charrep(), 
	        				DBName->charrep(), DBUser->charrep(), DBPass->charrep());

		dbForm->show();

		//- External formular implementation ---------------------------------------------------
	        //- Would load an external module and optionally use other parameters from configuratoin
	        //--------------------------------------------------------------------------------------
	        
	        free(buffer);
	} else {
	        COUT << "KundenDetails" << ENDL;
	}

        return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicApplication)
	ADD_INTERFACE(lb_I_MetaApplication)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfApplication, lbDynamicApplication)

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::setData(lb_I_Unknown* uk) {
	_LOG << "lbDynamicApplication::setData() has not been implemented" LOG_
	
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\setGUI\40\lb_I_GUI\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::setGUI(lb_I_GUI* _gui) {
	gui = _gui;
	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\getGUI\40\lb_I_GUI\42\\42\ _gui\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::getGUI(lb_I_GUI** _gui) {
	*_gui = gui;
	return ERR_NONE;
}
/*...e*/
/*...slb_I_EventManager \42\ lbDynamicApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager * lbDynamicApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\Initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::Initialize(char* user, char* app) {

	// To be implemented in a separate application module

	int unused;

	// Get the event manager

	lb_I_Module* m = *&manager;

	REQUEST(m, lb_I_EventManager, eman)


	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());


	/*
		Select all events, that are configured and register it.
	 */


	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery, __FILE__, __LINE__)
	
	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
	
	sampleQuery = database->getQuery(0);	

	char* b =
	        "select Formulare.eventname, Formulare.menuname from Formulare inner join Anwendungen_Formulare on "
	        "Formulare.id = Anwendungen_Formulare.formularid "
	        "inner join Anwendungen on Anwendungen_Formulare.anwendungid = Anwendungen.id inner join "
	        "User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
	        " User_Anwendungen.userid = Users.id where "
	        "Users.userid = '%s' and Anwendungen.name = '%s'";

	char* buffer = (char*) malloc(strlen(b)+strlen(user)+strlen(app)+1);

	sprintf(buffer, b, user, app);

	// Save user and app internally
	
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

	if (sampleQuery == NULL) printf("NULL pointer !\n");

	sampleQuery->skipFKCollecting();
	sampleQuery->query(buffer);
	sampleQuery->enableFKCollecting();
	
	free(buffer);
	
	char* ed = strdup(_trans("&Edit"));

	char* menu = strdup(_trans(app));

	addMenuBar(menu, ed);

	free(ed);
	free(menu);

	lbErrCodes DBerr = sampleQuery->first();
	if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
		UAP(lb_I_String, EventName, __FILE__, __LINE__)
		UAP(lb_I_String, MenuName, __FILE__, __LINE__)
		
	        EventName = sampleQuery->getAsString(1);
		MenuName = sampleQuery->getAsString(2);

		if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {

			eman->registerEvent(EventName->charrep(), unused);
		
			dispatcher->addEventHandlerFn(this, 
					(lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());

			addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");

		} else {
			_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
		}
		
		if (DBerr == WARN_DB_NODATA) return ERR_NONE;
#define TRUE 1
		while (TRUE) {
/*...sget rest of menu entries:24:*/
			UAP(lb_I_String, EventName, __FILE__, __LINE__)
			UAP(lb_I_String, MenuName, __FILE__, __LINE__)
			
			DBerr = sampleQuery->next();
		
			if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
		        	EventName = sampleQuery->getAsString(1);
				MenuName = sampleQuery->getAsString(2);
				
				if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent(EventName->charrep(), unused);
				
					dispatcher->addEventHandlerFn(this,
							(lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());
				
					addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");
				} else {
					_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
				}
		        	if (DBerr == WARN_DB_NODATA) break;
		        }
/*...e*/
		}

	}

	return ERR_NONE;
}

/*...e*/
lbErrCodes LB_STDCALL lbDynamicApplication::getUserName(lb_I_String** user) {
	(*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getApplicationName(lb_I_String** app) {
	(*app)->setData(LogonApplication->charrep());
	return ERR_NONE;
}
lbErrCodes LB_STDCALL lbDynamicApplication::setUserName(char* user) {
	if (LogonUser == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonUser)
	}

       	LogonUser->setData(user);
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::setApplicationName(char* app) {
	if (LogonApplication == NULL) {
        	REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
	}

       	LogonApplication->setData(app);
	return ERR_NONE;
}


// This starts the main application

/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\run\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::run() {
#ifdef bla
	lb_I_Unknown* result;

	dispatcher->dispatch("AddMenu", NULL, &result);	
#endif
	return ERR_NONE;
}
/*...e*/

/*...sBasic functions to be used for a UI application:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::loadApplication(char* user, char* app) {
        lbErrCodes err = ERR_NONE;

        UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, MetaApp)
        MetaApp->loadApplication(user, app);

        return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addMenuBar(char* name, char* after) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)

	app->addMenuBar(name, after);

	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addMenu(char* name) {
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addButton(char* buttonText, char* evHandler, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;
		
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
	app->addButton(buttonText, evHandler, x, y, w, h);

	return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addMenuEntry(char* in_menu, char* entry, char* evHandler, char* afterentry) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
	app->addMenuEntry(in_menu, entry, evHandler, afterentry);

	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addTextField(char* name, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
	app->addTextField(name, x, y, w, h);

        return err;
}

lbErrCodes LB_STDCALL lbDynamicApplication::addLabel(char* text, int x, int y, int w, int h) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, app)
	app->addLabel(text, x, y, w, h);

	return err;
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

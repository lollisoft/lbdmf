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

//#define USE_RDCD_MODEL

#ifdef USE_RDCD_MODEL
/// \todo Move interfaces to public place, where needed.
#include <lbInterfaces-sub-Project.h>
#endif

/*...sLB_DYNAPP_DLL scope:0:*/
#define LB_DYNAPP_DLL
#include <lbdynapp-module.h>
/*...e*/

#include <lbDynApp.h>
/*...e*/
/*...sclass lb_DynamicApplication:0:*/
class lbDynamicApplication : 
public lb_I_Application,
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

	void test() {}

	/**
	 * \brief The main handler to create dynamic forms
	 */
	lbErrCodes LB_STDCALL getDynamicDBForm(lb_I_Unknown* uk);

protected:
	lb_I_GUI* gui;
	UAP(lb_I_EventManager, eman)
	UAP(lb_I_Dispatcher, dispatcher)
	UAP(lb_I_Database, database)
	
	UAP(lb_I_String, LogonUser)
	UAP(lb_I_String, LogonApplication)
	UAP(lb_I_MetaApplication, metaapp)

#ifdef USE_RDCD_MODEL
	// Model of the dynamic form configuration 
	UAP(lb_I_RDCDModel, model)
#endif
	
	// Preloaded data from database, if plugins are available.
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)


	char hdsihd[100];
};
/*...e*/
/*...slbDynamicApplication:0:*/
/*...sctors\47\dtors:0:*/
lbDynamicApplication::lbDynamicApplication() {
	ref = STARTREF;
	gui = NULL;
	_CL_LOG << "lbDynamicApplication::lbDynamicApplication() called." LOG_
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
	        UAP(lb_I_DatabaseForm, dbForm)

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

		UAP(lb_I_Integer, eventID)
		UAP(lb_I_Query, sampleQuery)

		UAP_REQUEST(manager.getPtr(), lb_I_EventManager, eman)
		UAP_REQUEST(manager.getPtr(), lb_I_String, query)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formID)
		UAP_REQUEST(manager.getPtr(), lb_I_String, formName)

		UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
		UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

		QI(uk, lb_I_Integer, eventID)

		// Retrieve the event name from their ID

		char* eventName = eman->reverseEvent(eventID->getData());

#ifdef USE_RDCD_MODEL
		if (model != NULL) {
			model->selectFormByEventName(eventName);
			
			dbForm = gui->createDBForm(	model->getFormularName(), 
										model->getFormularQuery(),
										model->getDBName(), 
										model->getDBUser(), 
										model->getDBPass());
			
			if (dbForm != NULL) dbForm->show();
			
		} else {
#endif

		if ((forms != NULL) && (forms->getFormularCount() > 0)) {
			forms->finishFormularIteration();
			while (forms->hasMoreFormulars()) {
				forms->setNextFormular();
				
				if (strcmp(forms->getEventName(), eventName) == 0) {
					forms->finishFormularIteration();
					break;
				}
			}
			
			// appParams->getParameter() changes results to prior issued calls. Do temporaly make copies.
			
			long id = metaapp->getApplicationID();			

_CL_LOG << "Create formular with new data model (application id = " << id << ")" LOG_		
			
			*DBName = appParams->getParameter("DBName", id);
			*DBUser = appParams->getParameter("DBUser", id);
			*DBPass = appParams->getParameter("DBPass", id);
		
			dbForm = gui->createDBForm(	forms->getName(),
							formParams->getParameter("query", forms->getFormularID()), 
							DBName->charrep(), 
							DBUser->charrep(), 
							DBPass->charrep());
										
			if (dbForm != NULL) dbForm->show();
		} else {
			// Use old version with direct database queries. This could happen, if no plugin was found, no file was found and couldn't created.
			
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
				"select Formulare.id, Formulare.name from Formulare "
				"inner join Anwendungen on Formulare.anwendungid = Anwendungen.id inner join "
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
				"select parametervalue from formular_parameters "
				"where parametername = 'query' and "
				"formularid = %s";
			
			free(buffer);
			
			buffer = (char*) malloc(strlen(b)+strlen(formID->charrep())+1);
			
			buffer[0] = 0;
			
			sprintf(buffer, b, formID->charrep());
			
			UAP(lb_I_Query, formularQuery)
				
			formularQuery = database->getQuery(0);
			
			// It is an internal formular and I don't distinguish between 
			// different formular implementations yet
			
			formularQuery->skipFKCollecting();
			formularQuery->query(buffer);
			formularQuery->enableFKCollecting();
			
			err = formularQuery->first();
			
			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				query = formularQuery->getAsString(1);
				
				if ((query != NULL) && (query->charrep() == NULL)) {
					_LOG << "Error: Getting SQL query for the formular '" << formID->charrep() << "' failed." LOG_
				} else {
					_LOG << "Have got this query for the form: " << query->charrep() LOG_
				}
			} else {
				_CL_LOG << "Error: Something happens while getting the formular SQL query!" LOG_
			}
			
			b = 
				"select parametername, parametervalue from anwendungs_parameter inner join "
				"anwendungen on anwendungs_parameter.anwendungid = anwendungen.id where "
				"anwendungen.name = '%s'";
			
			free(buffer);
			
			buffer = (char*) malloc(strlen(b)+strlen(LogonApplication->charrep())+1);
			
			buffer[0] = 0;
			
			sprintf(buffer, b, LogonApplication->charrep());
			
			UAP(lb_I_Query, DBConnQuery)
				
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
			
			_CL_LOG << "Create a database form for " << formName->charrep() << " with " << query->charrep() LOG_
				
				dbForm = gui->createDBForm(formName->charrep(), query->charrep(), 
										   DBName->charrep(), DBUser->charrep(), DBPass->charrep());
			
			if (dbForm != NULL) dbForm->show();
			
			//- External formular implementation ---------------------------------------------------
			//- Would load an external module and optionally use other parameters from configuratoin
			//--------------------------------------------------------------------------------------
			
			free(buffer);
#ifdef USE_RDCD_MODEL
		}
#endif
}
	} else {
	        COUT << "KundenDetails" << ENDL;
	}

        return ERR_NONE;
}
/*...e*/


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicApplication)
	ADD_INTERFACE(lb_I_Application)
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
/*...slb_I_EventManager\42\ LB_STDCALL lbDynamicApplication\58\\58\getEVManager\40\ void \41\:0:*/
lb_I_EventManager* LB_STDCALL lbDynamicApplication::getEVManager( void ) {
	return NULL;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\uninitialize\40\\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::uninitialize() {
		lbErrCodes err = ERR_NONE;
		
		UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)

		// Need to derive filename from given application name
		UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
		*filename = LogonApplication->charrep();
		*filename += ".daf"; // Dynamic application forms 
			
		pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "OutputStreamVisitor");
		
		if (pl == NULL) {
			_LOG << "Error: Could not save dynamic application data. No plugin found." LOG_
			return ERR_FILE_WRITE;
		}
		
		if (pl != NULL) {
			ukPl = pl->getImplementation();
				
			UAP(lb_I_FileOperation, fOp)

			QI(ukPl, lb_I_FileOperation, fOp)
			
			if (fOp != NULL) {
				bool success = false;
				
				success = fOp->begin(filename->charrep()); 
			
				if (success) {
					if (forms != NULL) {
						_CL_LOG << "Save a forms model object..." LOG_
						forms->accept(*&fOp);
					}

					if (formParams != NULL) {
						_CL_LOG << "Save a formParams model object..." LOG_
						formParams->accept(*&fOp);
					}

					if (appParams != NULL) {
						_CL_LOG << "Save a appParams model object..." LOG_
						appParams->accept(*&fOp);
					}
					
					if (appActions != NULL) {
						_CL_LOG << "Save a appActions model object..." LOG_
						appActions->accept(*&fOp);
					}
					
					if (appActionTypes != NULL) {
						_CL_LOG << "Save a appActionTypes model object..." LOG_
						appActionTypes->accept(*&fOp);
					}
					
					if (appActionSteps != NULL) {
						_CL_LOG << "Save a appActionSteps model object..." LOG_
						appActionSteps->accept(*&fOp);
					}
					
					fOp->end();
				} else {
				// No file found. Create one from database...
				}
			}
		}

	return ERR_NONE;
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbDynamicApplication\58\\58\initialize\40\char\42\ user \61\ NULL\44\ char\42\ app \61\ NULL\41\:0:*/
lbErrCodes LB_STDCALL lbDynamicApplication::initialize(char* user, char* app) {
	_CL_LOG << "lbDynamicApplication::initialize(...) called." LOG_	
	// To be implemented in a separate application module
	lbErrCodes err = ERR_NONE;
	int unused;

	// Get the event manager
	
	lb_I_Module* m = *&manager;
	
	REQUEST(m, lb_I_EventManager, eman)
		
	REQUEST(m, lb_I_Dispatcher, dispatcher)
	dispatcher->setEventManager(eman.getPtr());
	
	if (metaapp == NULL) {
		REQUEST(manager.getPtr(), lb_I_MetaApplication, metaapp)
	}
	
	// Save user and app internally
	
	if (user == NULL) {
        _CL_LOG << "lb_MetaApplication::Initialize() user is NULL" LOG_
	} else
		if (LogonUser == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonUser)
		}
	LogonUser->setData(user);
	
	if (app == NULL) {
        _CL_LOG << "lb_MetaApplication::Initialize() app is NULL" LOG_
	} else
		if (LogonApplication == NULL) {
			REQUEST(manager.getPtr(), lb_I_String, LogonApplication)
		}
	LogonApplication->setData(app);
	
/*...sifdef USE_RDCD_MODEL:0:*/
#ifdef USE_RDCD_MODEL
	// -------------------------------------------------------------------------
	// I plan to use an object model to be used instead. The object model should
	// fasten up the application setup.
	//
	// In a next step, the RDCD model should be loaded after the user has been
	// logged in. Thus, the login and user data must be separated from the app
	// configuration data. To ensure authenticated usage, the model may ask the
	// login 'service' for the password before enabling the interface completely.
	// -------------------------------------------------------------------------
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
	
	pl = PM->getFirstMatchingPlugin("lb_I_RDCDModel", "RDCDModel");
	
	if (pl != NULL) {
		ukPl = pl->getImplementation();
		if (ukPl != NULL) {
			QI(ukPl, lb_I_RDCDModel, model)
			
			if (model != NULL) {
				// Have a valid model instance
				_CL_LOG << "Suceeded loading a lbRDCDModel instance as plugin." LOG_
				
				// Need to derive filename from given application name
				UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
				*filename = LogonApplication->charrep();
				*filename += ".daf"; // Dynamic application forms 
				
				pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");
				
				if (pl != NULL) {
					ukPl = pl->getImplementation();
					
					UAP(lb_I_FileOperation, fOp)
					QI(ukPl, lb_I_FileOperation, fOp)
						
					if (fOp != NULL) {
						if (fOp->begin(filename->charrep())) {
							UAP(lb_I_Unknown, ukAcceptor)
							QI(model, lb_I_Unknown, ukAcceptor)
							ukAcceptor->accept(*&fOp);
								
							fOp->end();
								
						} else {
							// No file found. Create one from database...
						}
					} else {
						_LOG << "Error: Could not get a valid file operation instance." LOG_
					}
				}
			}
		}
	}
	
#endif		
/*...e*/
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
		
	// Need to derive filename from given application name
	UAP_REQUEST(manager.getPtr(), lb_I_String, filename)
	*filename = LogonApplication->charrep();
	*filename += ".daf"; // Dynamic application forms 
	
	bool isFileAvailable = false;
	bool isDBAvailable = false;
	bool DBOperation = false;
	
	UAP(lb_I_FileOperation, fOp)
	UAP(lb_I_DatabaseOperation, fOpDB)

	_CL_LOG << "Try to find a lb_I_FileOperation plugin ..." LOG_
	pl = PM->getFirstMatchingPlugin("lb_I_FileOperation", "InputStreamVisitor");
	
	if (pl != NULL)	{
		_CL_LOG << "Found one ..." LOG_
		ukPl = pl->getImplementation();
	} else {
		_LOG << "No lb_I_FileOperation plugin available." LOG_	
	}
	
	if (ukPl != NULL) QI(ukPl, lb_I_FileOperation, fOp)
	if (fOp == NULL) {
		_LOG << "Error: Found a lb_I_FileOperation plugin via PM->getFirstMatchingPlugin(...), but QI failed." LOG_
	} else {
		isFileAvailable = fOp->begin(filename->charrep()); 
	}
			
	UAP_REQUEST(manager.getPtr(), lb_I_Database, database)
	UAP(lb_I_Query, sampleQuery)
		
	database->init();
	
	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");
	
	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";
	
	if (!isFileAvailable) {
		if ((database != NULL) && (database->connect("lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
			_LOG << "Fatal: No file and no database configuration available. Cannot proceed!" LOG_
		} else {
			pl = PM->getFirstMatchingPlugin("lb_I_DatabaseOperation", "DatabaseInputStreamVisitor");
			if (pl != NULL)	ukPl = pl->getImplementation();
			if (ukPl != NULL) QI(ukPl, lb_I_DatabaseOperation, fOpDB)
			isDBAvailable = fOpDB->begin(database.getPtr());
			DBOperation = true;
		}
		
	}
	
	_CL_LOG << "Load application settings from file or database ..." LOG_
	
	if (isFileAvailable || isDBAvailable) {
/*...sLoad from file or database:16:*/
/*...sInitialize plugin based document models:32:*/
		UAP(lb_I_Plugin, plFormulars)
		UAP(lb_I_Unknown, ukPlFormulars)
		UAP(lb_I_Plugin, plFormParams)
		UAP(lb_I_Unknown, ukPlFormParams)
		UAP(lb_I_Plugin, plAppParams)
		UAP(lb_I_Unknown, ukPlAppParams)
		UAP(lb_I_Plugin, plAppActions)
		UAP(lb_I_Unknown, ukPlAppActions)
		UAP(lb_I_Plugin, plAppActionTypes)
		UAP(lb_I_Unknown, ukPlAppActionTypes)
		UAP(lb_I_Plugin, plAppActionSteps)
		UAP(lb_I_Unknown, ukPlAppActionSteps)
		
		plAppActions = PM->getFirstMatchingPlugin("lb_I_Actions", "Model");
		if (plAppActions != NULL) {
			ukPlAppActions = plAppActions->getImplementation();
		} else {
			_LOG << "Warning: No actions datamodel plugin found." LOG_
		}
		
		if (ukPlAppActions != NULL) { 
			QI(ukPlAppActions, lb_I_Actions, appActions)
		} else {
			_LOG << "Warning: No actions datamodel plugin implementation found." LOG_
		}

		plAppActionTypes = PM->getFirstMatchingPlugin("lb_I_Action_Types", "Model");
		if (plAppActionTypes != NULL) {
			ukPlAppActionTypes = plAppActionTypes->getImplementation();
		} else {
			_LOG << "Warning: No action_types datamodel plugin found." LOG_
		}
		
		if (ukPlAppActionTypes != NULL) { 
			QI(ukPlAppActionTypes, lb_I_Action_Types, appActionTypes)
		} else {
			_LOG << "Warning: No action_types datamodel plugin implementation found." LOG_
		}

		plAppActionSteps = PM->getFirstMatchingPlugin("lb_I_Action_Steps", "Model");
		if (plAppActionSteps != NULL) {
			ukPlAppActionSteps = plAppActionSteps->getImplementation();
		} else {
			_LOG << "Warning: No action_steps datamodel plugin found." LOG_
		}
		
		if (ukPlAppActionSteps != NULL) { 
			QI(ukPlAppActionSteps, lb_I_Action_Steps, appActionSteps)
		} else {
			_LOG << "Warning: No action_steps datamodel plugin implementation found." LOG_
		}

		plFormulars = PM->getFirstMatchingPlugin("lb_I_Formulars", "Model");
		if (plFormulars != NULL) {
			ukPlFormulars = plFormulars->getImplementation();
		} else {
			_LOG << "Warning: No formular datamodel plugin found." LOG_
		}
		
		if (ukPlFormulars != NULL) { 
			QI(ukPlFormulars, lb_I_Formulars, forms)
		} else {
			_LOG << "Warning: No formular datamodel plugin implementation found." LOG_
		}
		
		plFormParams = PM->getFirstMatchingPlugin("lb_I_FormularParameter", "Model");
		if (plFormParams != NULL) {
			ukPlFormParams = plFormParams->getImplementation();
		} else {
			_LOG << "Warning: No formular parameter datamodel plugin found." LOG_
		}
		
		if (ukPlFormParams != NULL) { 
			QI(ukPlFormParams, lb_I_FormularParameter, formParams)
		} else {
			_LOG << "Warning: No formular parameter datamodel plugin implementation found." LOG_
		}
		
		plAppParams = PM->getFirstMatchingPlugin("lb_I_ApplicationParameter", "Model");
		if (plAppParams != NULL) {
			ukPlAppParams = plAppParams->getImplementation();
		} else {
			_LOG << "Warning: No application parameter datamodel plugin found." LOG_
		}
		
		if (ukPlAppParams != NULL) {
			QI(ukPlAppParams, lb_I_ApplicationParameter, appParams)
		} else {
			_LOG << "Warning: No application parameter datamodel plugin implementation found." LOG_
		}
/*...e*/
		
		
		// Only this part is how to load the data. So here I have to set the correct handler for the load delegation routine.
		
		// Loading the application related data succeeded. Put these into a parameter object for reference.
		
		UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
		UAP_REQUEST(manager.getPtr(), lb_I_Container, document)
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP_REQUEST(manager.getPtr(), lb_I_String, value)
		UAP(lb_I_KeyBase, key)
		QI(name, lb_I_KeyBase, key)
		
		param->setCloning(false);
		document->setCloning(false);

		if ((forms != NULL) && 
			(formParams != NULL) && 
			(appActions != NULL) && 
			(appActionSteps != NULL) && 
			(appActionTypes != NULL) && 
			(appParams != NULL)) {
			
			UAP(lb_I_Unknown, uk)
			
			*name = "Formulars";
			QI(forms, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "FormParams";
			QI(formParams, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "AppParams";
			QI(appParams, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "AppActions";
			QI(appActions, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "AppActionSteps";
			QI(appActionSteps, lb_I_Unknown, uk)
			document->insert(&uk, &key);
			
			*name = "AppActionTypes";
			QI(appActionTypes, lb_I_Unknown, uk)
			document->insert(&uk, &key);
		}		
		*name = "ApplicationData";
		param->setUAPContainer(*&name, *&document);

		*name = "StorageDelegateInterface";
		*value = "lb_I_Streamable";
		param->setUAPString(*&name, *&value);

		*name = "StorageDelegateNamespace";
		*value = "DynamicAppXMLStorage";
		param->setUAPString(*&name, *&value);
		
		param++;
		metaapp->setActiveDocument(*&param);
		
		
		if (!DBOperation && 
			(forms != NULL) && 
			(formParams != NULL) && 
			(appActions != NULL) && 
			(appActionSteps != NULL) && 
			(appActionTypes != NULL) && 
			(appParams != NULL)) {
			_LOG << "Load application data from file ..." LOG_
			
			
			
			
			forms->accept(*&fOp);
			formParams->accept(*&fOp);
			appParams->accept(*&fOp);
			appActions->accept(*&fOp);
			appActionTypes->accept(*&fOp);
			appActionSteps->accept(*&fOp);
		}
		
		if (DBOperation && 
			(forms != NULL) && 
			(formParams != NULL) && 
			(appActions != NULL) && 
			(appActionSteps != NULL) && 
			(appActionTypes != NULL) && 
			(appParams != NULL)) {
			_LOG << "Load application data from database ..." LOG_
			
			
			forms->accept(*&fOpDB);
			formParams->accept(*&fOpDB);
			appParams->accept(*&fOpDB);
			appActions->accept(*&fOpDB);
			appActionTypes->accept(*&fOpDB);
			appActionSteps->accept(*&fOpDB);
		}
		
		if (!DBOperation) fOp->end();
		if (DBOperation) fOpDB->end();


		int id = metaapp->getApplicationID();
		
		_LOG << "Test for application ID: " << id LOG_
/*...e*/
	} else {
		// No file found. Create one from database...
	}
	
	_CL_LOG << "Begin setup menu ..." LOG_
		
	/*
	 Select all events, that are configured and register it.
	 */
	
	database->connect("lbDMF", lbDMFUser, lbDMFPasswd);
	
	sampleQuery = database->getQuery(0);	
	
	char* b =
		"select Formulare.eventname, Formulare.menuname, Formulare.toolbarimage from Formulare inner join "
		"anwendungen_formulare on anwendungen_formulare.formularid = formulare.id inner join "
		"Anwendungen on anwendungen_formulare.anwendungid = Anwendungen.id inner join "
		"User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		"User_Anwendungen.userid = Users.id where "
		"Users.userid = '%s' and Anwendungen.name = '%s' order by Formulare.menuorder";
	
	char* buffer = (char*) malloc(strlen(b)+strlen(user)+strlen(app)+1);
	
	sprintf(buffer, b, user, app);
	
	if (sampleQuery == NULL) printf("NULL pointer !\n");
	
	_CL_LOG << "lbDynamicApplication::Initialize('" << user << "', '" << app << "');" LOG_
	_CL_LOG << "Query: " << buffer LOG_
		
	sampleQuery->skipFKCollecting();
	sampleQuery->query(buffer);
	sampleQuery->enableFKCollecting();
	
	char* ed = strdup(_trans("&Edit"));
	
	char* menu = strdup(_trans(app));
	
	metaapp->addMenuBar(menu, ed);
	
	free(ed);
	free(menu);
	free(buffer);
	
	bool toolbaradded = false;
	
	lbErrCodes DBerr = sampleQuery->first();
	if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
		UAP(lb_I_String, EventName)
		UAP(lb_I_String, MenuName)
		UAP(lb_I_String, ToolBarImage)
		
		EventName = sampleQuery->getAsString(1);
		MenuName = sampleQuery->getAsString(2);
		ToolBarImage = sampleQuery->getAsString(3);
		
		if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {
			
			eman->registerEvent(EventName->charrep(), unused);
			
			dispatcher->addEventHandlerFn(this, 
				  (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());
			
			metaapp->addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");
			
			if (strcmp(ToolBarImage->charrep(), "") != 0) {
				if (toolbaradded == false) {
					metaapp->addToolBar(app);
					toolbaradded = true;
				}
				
				ToolBarImage->trim();
				
				metaapp->addToolBarButton(app, MenuName->charrep(), EventName->charrep(), ToolBarImage->charrep());
			}
			
		} else {
			_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
		}
		
		if (DBerr == WARN_DB_NODATA) return ERR_NONE;
		if (DBerr == ERR_DB_NODATA) return ERR_NONE;
#define TRUE 1
		while (TRUE) {
			/*...sget rest of menu entries:24:*/
			UAP(lb_I_String, EventName)
			UAP(lb_I_String, MenuName)
			UAP(lb_I_String, ToolBarImage)

			DBerr = sampleQuery->next();
			
			if ((DBerr == ERR_NONE) || (DBerr == WARN_DB_NODATA)) {
				EventName = sampleQuery->getAsString(1);
				MenuName = sampleQuery->getAsString(2);
				ToolBarImage = sampleQuery->getAsString(3);
				
				if (eman->resolveEvent(EventName->charrep(), unused) == ERR_EVENT_NOTREGISTERED) {
					eman->registerEvent(EventName->charrep(), unused);
					
					dispatcher->addEventHandlerFn(this,
												  (lbEvHandler) &lbDynamicApplication::getDynamicDBForm, EventName->charrep());
					
					metaapp->addMenuEntry(_trans(app), MenuName->charrep(), EventName->charrep(), "");
					
					if (strcmp(ToolBarImage->charrep(), "") != 0) {
						if (toolbaradded == false) {
							metaapp->addToolBar(app);
							toolbaradded = true;
						}
						
						ToolBarImage->trim();
						
						metaapp->addToolBarButton(app, MenuName->charrep(), EventName->charrep(), ToolBarImage->charrep());
					}
					
				} else {
					_CL_VERBOSE << "WARNING: Event name already reserved. Ignore it for menucreation." LOG_
				}
				if (DBerr == WARN_DB_NODATA) break;
			}
			if (DBerr == ERR_DB_NODATA) break;
			/*...e*/
		}
		
	} else {
		_CL_LOG << "Error: No forms are defined for application." LOG_
	}
	
	return ERR_NONE;
}

/*...e*/
lbErrCodes LB_STDCALL lbDynamicApplication::getUserName(lb_I_String** user) {
	if (LogonUser == NULL) (*user)->setData("");
	else (*user)->setData(LogonUser->charrep());
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbDynamicApplication::getApplicationName(lb_I_String** app) {
	if (LogonApplication == NULL) (*app)->setData("");
	else (*app)->setData(LogonApplication->charrep());
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

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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#include <unistd.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#ifdef __WATCOMC__
#include <direct.h>
#endif

#ifdef __MINGW32__
#include <direct.h>
#endif

#include <lbDMFXslt.h>

// Includes for the libxml / libxslt libraries

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxslt/security.h>

#include <libexslt/exslt.h>

#ifndef __WATCOMC_
extern int xmlLoadExtDtdDefaultValue;
#endif
#ifdef __WATCOMC__
#define xsltSaveResultToString lb_xsltSaveResultToString
#define xsltParseStylesheetDoc lb_xsltParseStylesheetDoc
#define xsltApplyStylesheet lb_xsltApplyStylesheet
#define xsltFreeStylesheet lb_xsltFreeStylesheet
#define xmlSubstituteEntitiesDefault lb_xmlSubstituteEntitiesDefault
#define xmlFreeDoc lb_xmlFreeDoc
#define xsltCleanupGlobals lb_xsltCleanupGlobals
#define xmlCleanupParser lb_xmlCleanupParser
#define xmlReadMemory lb_xmlReadMemory
#define xmlInitMemory lb_xmlInitMemory
#define xsltNewSecurityPrefs lb_xsltNewSecurityPrefs
#define xsltSetDefaultSecurityPrefs lb_xsltSetDefaultSecurityPrefs
#define xsltSaveResultToFile lb_xsltSaveResultToFile
#define exsltRegisterAll lb_exsltRegisterAll
#endif


IMPLEMENT_FUNCTOR(instanceOflbDMFXslt, lbDMFXslt)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDMFXslt)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()


lbDMFXslt::lbDMFXslt() {
	
	myActionID = -1;

	_CL_LOG << "lbDMFXslt::lbDMFXslt() called." LOG_
}

lbDMFXslt::~lbDMFXslt() {
	_CL_LOG << "lbDMFXslt::~lbDMFXslt() called." LOG_
}

lbErrCodes LB_STDCALL lbDMFXslt::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDMFXslt::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbDMFXslt::setActionID(long id) {
    myActionID = id;
}

void LB_STDCALL lbDMFXslt::setDatabase(lb_I_Database* _db) {
    db = _db;
}

void LB_STDCALL lbDMFXslt::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
	
}

void LB_STDCALL lbDMFXslt::setParameter(lb_I_ActionStep_Parameters* myParams) {
	
}

bool LB_STDCALL lbDMFXslt::fileFromAction(lb_I_InputStream* stream) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)

	if (stream == NULL) {
		_LOG << "Error: Stream object is a NULL pointer." LOG_
		return false;
	}
	
	if (database == NULL) {
		char* dbbackend = metaapp->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}

		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
	}
	UAP(lb_I_Query, query)

	database->init();

	const char* lbDMFPasswd = getenv("lbDMFPasswd");
	const char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);

	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {
		UAP(lb_I_String, what)
		lbErrCodes cursorErr = ERR_NONE;
		cursorErr = query->first();
		
		if ((cursorErr == ERR_NONE) || (cursorErr == WARN_DB_NODATA)) {
			what = query->getAsString(1);
			if (what == NULL) {
				return false;
			}
			if (what->charrep() == NULL) {
				return false;
			}
			if (strcmp(what->charrep(), "") == 0) {
				return false;
			}
			stream->setFileName(what->charrep());
			return true;
		}
	}

	return false;
}


/**
 * \brief Perform XSLT transformation as action step.
 *
 * This function enables XSLT transformations on application document (in XML format) when added as action step
 * in a databse form. Only when the plugin exists, the type for this action is added to the table action_types.
 * Thus only then, a designer could define such an action in a form.
 *
 * The function expects the following parameters stored in the properties for this step:
 *
 * transformation filename: The name of the XSLT transformation file. If not stored, the user would be asked.
 *
 * target directory: The directory where the transformation will be performed. If not stored, the current directory will be used.
 */
long LB_STDCALL lbDMFXslt::execute(lb_I_Parameter* execution_params) {
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;
	// Linear action
	long next_action = -1;

	long id = 0;
	const char *p[16 + 1];

	p[0] = NULL;
	
	UAP(lb_I_ApplicationParameter, appParams)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ApplicationName)

	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramValue)

	
	*name = "source value";
	execution_params->getUAPString(*&name, *&ApplicationName);


	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, activeDocument)
	ukDoc = metaapp->getActiveDocument();
	if (ukDoc == NULL) {
		_LOG << "Error: MetaApplication does not have an active document. See log entry, why this happens." LOG_
		*paramName = "result";
		*paramValue = "0";
		
		execution_params->setUAPString(*&paramName, *&paramValue);

		// The active document contains parameters that are required as input parameters for the action.
		///\todo Are the parameters always mandatory or can sometimes these parameters provided by user input.
		return 0;
	}
	QI(ukDoc, lb_I_Parameter, activeDocument)


#ifndef __WATCOMC__
// Quick hack
#define MAX_PATH 512
#endif

	bool do_chdir = false;
    char oldcwd[MAX_PATH+1] = "";
    getcwd(oldcwd, sizeof(oldcwd));

    _CL_LOG << "Storing old CWD: " << oldcwd LOG_

	if (activeDocument != NULL) {
		*name = "UMLImportDBName";
		activeDocument->getUAPString(*&name, *&DBName);
		*name = "UMLImportDBUser";
		activeDocument->getUAPString(*&name, *&DBUser);
		*name = "UMLImportDBPass";
		activeDocument->getUAPString(*&name, *&DBPass);
	} else {
		_LOG << "lbDMFXslt::execute(): Error, did not have parameters" LOG_
		chdir(oldcwd);
		
		*paramName = "result";
		*paramValue = "0";
		
		execution_params->setUAPString(*&paramName, *&paramValue);
		
		return next_action;
	}

	// Be sure to have the actual data, but save the last changes in settings before.
    bool b = metaapp->getLoadFromDatabase();
	metaapp->save();
	metaapp->setLoadFromDatabase(true);
	metaapp->load();
	metaapp->setLoadFromDatabase(b);

	UAP(lb_I_Applications, applications)
	applications = metaapp->getApplicationModel();
	applications->selectApplication(ApplicationName->charrep());
	
	if (activeDocument != NULL) {
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)
		// Get the parameters of the application to be translated.
		document->setCloning(false);
		*name = "ApplicationData";
		activeDocument->getUAPContainer(*&name, *&document);
		*name = "AppParams";
		QI(name, lb_I_KeyBase, key)
		uk = document->getElement(&key);
		QI(uk, lb_I_ApplicationParameter, appParams)
		AppID->setData(applications->getApplicationID());
		
		id = (long) AppID->getData();
		
        _CL_LOG << "Change to new output directory: " << appParams->getParameter("codegenbasedir", id) LOG_
		
		if (strcmp(appParams->getParameter("codegenbasedir", id), "") == 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_DirLocation, dirloc)
			if (metaapp->askForDirectory(*&dirloc)) {
				appParams->addParameter("codegenbasedir", dirloc->charrep(), id);
				
				UAP(lb_I_Database, database)
				
				if (database == NULL) {
					char* dbbackend = metaapp->getSystemDatabaseBackend();
					if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, database)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
					
					if (database == NULL) {
						_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
						chdir(oldcwd);

						*paramName = "result";
						*paramValue = "0";
						
						execution_params->setUAPString(*&paramName, *&paramValue);

						return next_action;
					}
				}
				
				database->init();
				
				if (database->connect("lbDMF", "lbDMF", "dba", "trainres") != ERR_NONE) {
					_LOG << "Error: Could not connect to given database: '" << "lbDMF" << "'" LOG_
					
					chdir(oldcwd);
					
					*paramName = "result";
					*paramValue = "0";
					
					execution_params->setUAPString(*&paramName, *&paramValue);
					
					return next_action;
				}
				
				UAP(lb_I_Query, q)
				UAP_REQUEST(getModuleInstance(), lb_I_String, sql)
				q = database->getQuery("lbDMF", 0);
				
				q->skipFKCollecting();
				*sql = "insert into anwendungs_parameter (parametername, parametervalue, anwendungid) values ('codegenbasedir', '";
				*sql += dirloc->charrep();
				*sql += "', ";
				*sql += AppID->charrep();
				*sql += ")";
				
				if (q->query(sql->charrep()) != ERR_NONE) {
					_LOG << "Failed to store given application parameter." LOG_
				}
				do_chdir = true;
			} else {
				// Default should be used. (On Mac there else is nothing generated)
			}
		} else {
			do_chdir = true;
		}
	}
	
	// The unique application ID should be retrieved from database
	// This is a bit too much. A better way would be providing the integer value in the 2. parameter as an entry (lb_I_Parameter instance)
	*name = "SaveApplicationID";
	activeDocument->setUAPInteger(*&name, *&AppID);
	_LOG << "lbDMFXslt::execute(): Save application ID = " << AppID->charrep() << " with name = " << ApplicationName->charrep() << "." LOG_

	// Dispatch the function call, or better let the meta application provide a direct call
	// for saving XML application data.

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename)

	UAP(lb_I_Unknown, uk)
	QI(param, lb_I_Unknown, uk)

	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result)

	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)

	if (dispatcher->dispatch("exportApplicationToXMLBuffer", uk.getPtr(), &uk_result) == ERR_DISPATCH_FAILS) {
		_LOG << "lbDMFXslt::execute(): Error: Failed to dispatch a call to 'exportApplicationToXMLBuffer'!" LOG_
		chdir(oldcwd);
		
		*paramName = "result";
		*paramValue = "0";
		
		execution_params->setUAPString(*&paramName, *&paramValue);

		return next_action;
	}

	parameter->setData("memorybuffer");
	param->getUAPString(*&parameter, *&value);
	parameter->setData("filename");
	param->getUAPString(*&parameter, *&filename);


	metaapp->setStatusText("Info", "Read XML data ...");
	// *********************************************************

	if (do_chdir) chdir(appParams->getParameter("codegenbasedir", id));

	exsltRegisterAll();
	xsltSecurityPrefsPtr sec = NULL;
	xmlInitMemory();
	sec = xsltNewSecurityPrefs();
	xsltSetDefaultSecurityPrefs(sec);

	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif

	xmlChar* URL = (xmlChar*) filename->charrep();

	if (value->charrep() == NULL) {
		_CL_LOG << "Translate XML data failed." LOG_
		metaapp->setStatusText("Info", "Translate XML data failed!");
		chdir(oldcwd);
		
		*paramName = "result";
		*paramValue = "0";
		
		execution_params->setUAPString(*&paramName, *&paramValue);
		
		return next_action;
	}

	doc = xmlReadMemory((char const*) value->charrep(), strlen(value->charrep()), (char const*) URL, NULL, 0);
	if (doc == NULL) {
		_LOG << "lbDMFXslt::execute(): Error: Failed to load in-memory XMI document as an XML document." LOG_
		_LOG << "Document content: " << value->charrep() LOG_
		metaapp->setStatusText("Info", "Translate XML data failed.");
		chdir(oldcwd);
		
		*paramName = "result";
		*paramValue = "0";
		
		execution_params->setUAPString(*&paramName, *&paramValue);

		return next_action;
	}

	// Read the stylesheet document to get SQL script for database creation
	metaapp->setStatusText("Info", "Translate XML data ...");

	// Get the question from action parameters for this action step

	bool doGenerate = true;

	doGenerate = metaapp->askYesNo("You prepare to generate other output format from XML data model.\n\nNext step ist to select the XSLT template to be used.\n\nDo you want to proceed ?");
	
	if (doGenerate) {
		UAP(lb_I_String, styledoc)
		UAP(lb_I_InputStream, input)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, input_action_configuration)

		if (!fileFromAction(*&input_action_configuration)) {
			// Get this file name later from action parameters for this action step
			input = metaapp->askOpenFileReadStream("xsl|*.xsl");
		} else {
			input = input_action_configuration.getPtr();
			input++;
		}

		if ((input != NULL) && (input->open())) {
			_LOG << "lbDMFXslt::execute(): Try to get the file as a string..." LOG_
			styledoc = input->getAsString();
			_LOG << "lbDMFXslt::execute(): Got the file as s string." LOG_

			xmlChar* URL = (xmlChar*) input->getFileName();
			_LOG << "lbDMFXslt::execute(): Read the string as an in memory XML document." LOG_
			stylesheetdoc = xmlReadMemory((char const*) styledoc->charrep(), strlen(styledoc->charrep()), (char const*) URL, NULL, 0);
			if (stylesheetdoc == NULL) {
				_LOG << "Error: Failed to load in-memory XMI stylesheet document as an XML document." LOG_
				chdir(oldcwd);

				*paramName = "result";
				*paramValue = "0";
				
				execution_params->setUAPString(*&paramName, *&paramValue);

				return next_action;
			}
			_LOG << "lbDMFXslt::execute(): Parse xml document as stylesheet." LOG_
			cur = xsltParseStylesheetDoc(stylesheetdoc);

			xmlChar* result = NULL;
			int len = 0;

			_LOG << "lbDMFXslt::execute(): Apply the stylesheet document." LOG_

			res = xsltApplyStylesheet(cur, doc, p);

			_LOG << "lbDMFXslt::execute(): Save resulting document as a string." LOG_

			//xsltSaveResultToString(&result, &len, res, cur);
			xsltSaveResultToFile(stdout, res, cur);

			xsltFreeStylesheet(cur);
			xmlFreeDoc(res);

			/* May show the result messages, but this may also output to be in a file.
			 * Document it anyway in the action parameters.
			 */

			free(result);
		} else {
			metaapp->setStatusText("Info", "Aborded Translating XML data ...");
			chdir(oldcwd);

			*paramName = "result";
			*paramValue = "0";
			
			execution_params->setUAPString(*&paramName, *&paramValue);

			return next_action;
		}
	}

	xmlFreeDoc(doc);

	xsltCleanupGlobals();
	xmlCleanupParser();

    chdir(oldcwd);

	metaapp->setStatusText("Info", "Finished Translating XML data.");
		
	*paramName = "result";
	*paramValue = "1";
	
	execution_params->setUAPString(*&paramName, *&paramValue);
	
	return next_action;
}

/*...sclass lbPluginDMFXslt implementation:0:*/
/*...slbPluginDMFXslt:0:*/
class lbPluginDMFXslt : public lb_I_PluginImpl {
public:
	lbPluginDMFXslt();

	virtual ~lbPluginDMFXslt();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();

	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDMFXslt)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDMFXslt, lbPluginDMFXslt)

/*...slbErrCodes LB_STDCALL lbPluginDMFXslt\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDMFXslt::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDMFXslt::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDMFXslt::lbPluginDMFXslt() {
	_CL_VERBOSE << "lbPluginDMFXslt::lbPluginDMFXslt() called.\n" LOG_
	
}

lbPluginDMFXslt::~lbPluginDMFXslt() {
	_CL_VERBOSE << "lbPluginDMFXslt::~lbPluginDMFXslt() called.\n" LOG_
}

bool LB_STDCALL lbPluginDMFXslt::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDMFXslt::autorun() {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Database, database)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)

	if (database == NULL) {
		char* dbbackend = metaapp->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, database)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}

		if (database == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return ERR_DYNAMIC_APP_LOAD_DBSCHEMA;
		}
	}


	if (database->init() == ERR_NONE) {
		if (database->connect("lbDMF", "lbDMF", "dba", "trainres") == ERR_NONE) {
			UAP(lb_I_Query, q)

			q = database->getQuery("lbDMF", 0);

			if (q != NULL) {

				if (q->query("select id from action_types where action_handler = 'instanceOflbDMFXslt' and module = 'lbDMFXslt'") == ERR_NONE) {
					if (q->first() == ERR_NONE) {
						// Propably installed
					} else {
						// Propably not installed
					}
				} else {
					_LOG << "Error: Could not execute query to check for XSLT action type availability." LOG_
				}
			} else {
				_LOG << "Error: Could not get query object to create XSLT action type." LOG_
			}
		} else {
			_LOG << "Error: Could not log into database to create XSLT action type." LOG_
		}
	} else {
		_LOG << "Error: Could not initialize database to create XSLT action type." LOG_
	}

	return err;
}

void LB_STDCALL lbPluginDMFXslt::initialize() {
}

bool LB_STDCALL lbPluginDMFXslt::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFXslt\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFXslt::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDMFXslt* DMFXslt = new lbDMFXslt();
		
		QI(DMFXslt, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFXslt\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFXslt::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbDMFXslt* xslt = new lbDMFXslt();
		

		QI(xslt, lb_I_Unknown, ukActions)
	}

	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDMFXslt::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/


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

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <lbDMFActionStepIdForFormValue.h>

IMPLEMENT_FUNCTOR(instanceOflbDMFIdForFormValue, lbDMFIdForFormValue)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDMFIdForFormValue)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()


lbDMFIdForFormValue::lbDMFIdForFormValue() {
	myActionID = -1;
	_CL_LOG << "lbDMFIdForFormValue::lbDMFIdForFormValue() called." LOG_
}

lbDMFIdForFormValue::~lbDMFIdForFormValue() {
	_CL_LOG << "lbDMFIdForFormValue::~lbDMFIdForFormValue() called." LOG_
}

lbErrCodes LB_STDCALL lbDMFIdForFormValue::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDMFIdForFormValue::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL lbDMFIdForFormValue::setActionID(long id) {
    myActionID = id;
}

void LB_STDCALL lbDMFIdForFormValue::setDatabase(lb_I_Database* _db) {
    db = _db;
}

void LB_STDCALL lbDMFIdForFormValue::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
	
}

void LB_STDCALL lbDMFIdForFormValue::setParameter(lb_I_ActionStep_Parameters* myParams) {
	
}

lbErrCodes LB_STDCALL lookupApplication(lb_I_Applications* applications, const char* name) {
	applications->finishApplicationsIteration();
	
	while (applications->hasMoreApplications()) {
		applications->setNextApplications();
		if (strcmp(applications->get_name(), name) == 0)
			return ERR_NONE;
	}
	
	return ERR_ENTITY_NOT_FOUND;
}

char* LB_STDCALL lookupParameter(lb_I_ApplicationParameter* from, const char* name, long ApplicationID) {
	from->finishApplicationParameterIteration();
	
	while (from->hasMoreApplicationParameter()) {
		from->setNextApplicationParameter();
		if (from->get_anwendungid() == ApplicationID && strcmp(from->get_parametername(), name) == 0)
			return from->get_parametervalue();
	}

	return NULL;
}

char* LB_STDCALL lookupParameter(lb_I_FormularParameter* from, const char* name, long FormID) {
	from->finishFormularParameterIteration();
	
	while (from->hasMoreFormularParameter()) {
		from->setNextFormularParameter();
		if (from->get_formularid() == FormID && strcmp(from->get_parametername(), name) == 0)
			return from->get_parametervalue();
	}

	return NULL;
}

long LB_STDCALL lbDMFIdForFormValue::execute(lb_I_Parameter* execution_params) {
	lbErrCodes err = ERR_NONE;
	// Linear action
	long next_action = -1;

	const char *p[16 + 1];

	p[0] = NULL;
	
	UAP(lb_I_ApplicationParameter, appParams)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceValue)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceColumn)

	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, currentFormular)

	UAP_REQUEST(getModuleInstance(), lb_I_String, paramName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramValue)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ApplicationName)
	
	*name = "application";
	execution_params->getUAPString(*&name, *&ApplicationName);
	
	*name = "source field";
	execution_params->getUAPString(*&name, *&SourceColumn);
	
	*name = "source value";
	execution_params->getUAPString(*&name, *&SourceValue);
	
	*name = "source Form";
	execution_params->getUAPString(*&name, *&currentFormular);
	
	
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

	// Be sure to have the actual data, but save the last changes in settings before.
    bool b = metaapp->getLoadFromDatabase();
	metaapp->save();
	metaapp->setLoadFromDatabase(true);
	metaapp->load();
	metaapp->setLoadFromDatabase(b);

	UAP(lb_I_SecurityProvider, securityManager)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
	UAP(lb_I_Applications, applications)
	UAP(lb_I_Unknown, apps)
	apps = securityManager->getApplicationModel();
	QI(apps, lb_I_Applications, applications)

	lookupApplication(*&applications, ApplicationName->charrep());
	
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
		AppID->setData(applications->get_id());
		
		// The database I get the current row Id.
		UAP_REQUEST(getModuleInstance(), lb_I_String, AppDBName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, AppDBPass)
		UAP_REQUEST(getModuleInstance(), lb_I_String, AppDBUser)
		
		*AppDBName = lookupParameter(*&appParams, "DBName", (long) AppID->getData());
		*AppDBUser = lookupParameter(*&appParams, "DBUser", (long) AppID->getData());
		*AppDBPass = lookupParameter(*&appParams, "DBPass", (long) AppID->getData());

		*name = "Formulars";
		
		uk = document->getElement(&key);
		
		if (uk != NULL) {
			UAP(lb_I_Formulars, formulars)
			QI(uk, lb_I_Formulars, formulars)
			
			if (formulars != NULL) {
				formulars->finishFormularsIteration();
				
				while (formulars->hasMoreFormulars()) {
					formulars->setNextFormulars();
					
					if (strcmp(formulars->get_name(), currentFormular->charrep()) == 0) {
						if (formulars->get_anwendungid() == (long) AppID->getData()) {
							long formId = formulars->get_id();
							
							// Get the query of it
							*name = "FormParams";
							uk = document->getElement(&key);
							
							if (uk != NULL) {
								UAP(lb_I_FormularParameter, formParams)
								QI(uk, lb_I_FormularParameter, formParams)
								
								UAP_REQUEST(getModuleInstance(), lb_I_String, query)
								*query = lookupParameter(*&formParams, "query", formId);
								
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
										
										*paramName = "result";
										*paramValue = "0";
										
										execution_params->setUAPString(*&paramName, *&paramValue);
										
										return next_action;
									}
								}
								
								database->init();
								
								if (database->connect(AppDBName->charrep(), AppDBName->charrep(), AppDBUser->charrep(), AppDBPass->charrep()) != ERR_NONE) {
									_LOG << "Error: Could not connect to given database: '" << AppDBName->charrep() << "'" LOG_
									
									*paramName = "result";
									*paramValue = "0";
									
									execution_params->setUAPString(*&paramName, *&paramValue);
									
									return next_action;
								}
								
								UAP(lb_I_Query, q)
								q = database->getQuery(AppDBName->charrep(), 0);
								
								if (q->query(query->charrep()) == ERR_NONE) {
									UAP_REQUEST(getModuleInstance(), lb_I_String, where)
									bool isChar = q->getColumnType(SourceColumn->charrep()) == lb_I_Query::lbDBColumnChar;
									
									*where = " WHERE ";
									*where += SourceColumn->charrep(); 
									*where += " = ";
									if (isChar) *where += "'";
									*where += SourceValue->charrep(); 
									if (isChar) *where += "'";
									
									*query = q->setWhereClause(query->charrep(), where->charrep());
									
									if (q->query(query->charrep()) == ERR_NONE) {
										// Found some data
										if (q->dataFetched()) {
											int first = 0;
											int last = 0;
											
											if (q->first() == ERR_NONE) first = q->getPosition();
											if (q->last() == ERR_NONE) last = q->getPosition();
											
											if (first+1 == last) {
												// One row
												*paramName = "id";
												UAP(lb_I_Long, l)
												l = q->getAsLong(SourceColumn->charrep());
												*paramValue = l->charrep();
												execution_params->setUAPString(*&paramName, *&paramValue);
											} else {
												// More than one row
												*paramName = "result";
												*paramValue = "0";
												
												execution_params->setUAPString(*&paramName, *&paramValue);
												
												return next_action;
											}
										} else {
											*paramName = "result";
											*paramValue = "0";

											execution_params->setUAPString(*&paramName, *&paramValue);
											
											return next_action;
										}
									}
								}
								
								
							}
						}
					}
				}
			}
		}
			
			
	}
	
	*paramName = "result";
	*paramValue = "1";
	
	execution_params->setUAPString(*&paramName, *&paramValue);
	
	return next_action;
}

/*...sclass lbPluginDMFIdForFormValue implementation:0:*/
/*...slbPluginDMFIdForFormValue:0:*/
class lbPluginDMFIdForFormValue : public lb_I_PluginImpl {
public:
	lbPluginDMFIdForFormValue();

	virtual ~lbPluginDMFIdForFormValue();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();

	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }
/*...e*/

	DECLARE_LB_UNKNOWN()

	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDMFIdForFormValue)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDMFIdForFormValue, lbPluginDMFIdForFormValue)

/*...slbErrCodes LB_STDCALL lbPluginDMFIdForFormValue\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDMFIdForFormValue::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDMFIdForFormValue::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDMFIdForFormValue::lbPluginDMFIdForFormValue() {
	_CL_VERBOSE << "lbPluginDMFIdForFormValue::lbPluginDMFIdForFormValue() called.\n" LOG_
}

lbPluginDMFIdForFormValue::~lbPluginDMFIdForFormValue() {
	_CL_VERBOSE << "lbPluginDMFIdForFormValue::~lbPluginDMFIdForFormValue() called.\n" LOG_
}

bool LB_STDCALL lbPluginDMFIdForFormValue::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDMFIdForFormValue::autorun() {
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

				if (q->query("select id from action_types where action_handler = 'instanceOflbDMFIdForFormValue' and module = 'lbDMFIdForFormValue'") == ERR_NONE) {
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

void LB_STDCALL lbPluginDMFIdForFormValue::initialize() {
}

bool LB_STDCALL lbPluginDMFIdForFormValue::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFIdForFormValue\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFIdForFormValue::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDMFIdForFormValue* DMFXslt = new lbDMFIdForFormValue();
		
		QI(DMFXslt, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}

	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDMFIdForFormValue\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDMFIdForFormValue::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_

		lbDMFIdForFormValue* xslt = new lbDMFIdForFormValue();
		

		QI(xslt, lb_I_Unknown, ukActions)
	}

	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDMFIdForFormValue::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/


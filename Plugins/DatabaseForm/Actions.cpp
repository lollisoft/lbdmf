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

// To review an imported workflow, the following query can be used:
/*
 select actionid, srcid, bezeichnung, name, value, expression, dst_actionid, src_actionid from (
 select actions.id as actionid, action_steps.id as srcid, action_steps.bezeichnung, action_step_parameter.name, action_step_parameter.value from actions
 inner join action_steps on action_steps.actionid = actions.id
 inner join action_step_parameter on action_step_parameter.action_step_id = action_steps.id
 -- where actions.id = 20
 ) as temp inner join action_step_transitions on action_step_transitions.dst_actionid = srcid
order by src_actionid
*/

class lb_I_Action;

/*...sincludes:0:*/
#include <lbDMF_wxPrec.h>

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#ifndef USE_MPATROL
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif


/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
/*...e*/

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <lbDatabaseForm.h>

/*...slbAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbAction)
	ADD_INTERFACE(lb_I_Action)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbAction, lbAction)

lbErrCodes LB_STDCALL lbAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbAction::lbAction() {
	lbErrCodes err = ERR_NONE;
	
	myActionID = -1;
	initialized = false;
	
	;
}

lbAction::~lbAction() {

	_CL_LOG << "lbAction::~lbAction() called." LOG_
	if (actions != NULL) {
		_CL_LOG << "Have " << actions->Count() << " elements in action list." LOG_
		actions->deleteAll();
	}
	_CL_LOG << "Deleted all delegation actions." LOG_
}

/*...svoid LB_STDCALL lbAction\58\\58\setActionID\40\char\42\ id\41\:0:*/
void LB_STDCALL lbAction::setActionID(long id) {
	myActionID = id;
}
/*...e*/

void makePluginName(char* path, char* module, char*& result) {
		char* pluginDir = NULL;

		#ifndef WINDOWS
		pluginDir = (char*) malloc(strlen(path)+1);
		pluginDir[0] = 0;
		strcat(pluginDir, path);
		#endif

		#ifdef WINDOWS
		// Overwrites hardcoded path
		pluginDir = getenv("PLUGIN_DIR");
		if (pluginDir == NULL) {
			pluginDir = (char*) malloc(strlen(path)+1);
			pluginDir[0] = 0;
			strcat(pluginDir, path);
		} else {
			pluginDir = strdup(pluginDir);
		}
		#endif

		/*...sBuild up pluginModule:64:*/
		char* pluginModule = (char*) malloc(strlen(pluginDir)+strlen(module)+2);
		pluginModule[0] = 0;
		strcat(pluginModule, pluginDir);
#ifdef WINDOWS
		strcat(pluginModule, "\\");
#endif
#ifdef LINUX
		strcat(pluginModule, "/");
#endif
#ifndef LINUX
#ifdef OSX
		strcat(pluginModule, "/");
#endif
#endif
		strcat(pluginModule, module);
		/*...e*/
		result = pluginModule;
		free(pluginDir);
}

lb_I_Action_Step_Transitions* LB_STDCALL lbAction::loadTransitionsForActionStep(lb_I_Long* step, lb_I_Action_Step_Transitions* allTransitions) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Action_Step_Transitions, stepTransitions)
	AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, stepTransitions, "'action step transitions'")

	bool found = false;
	if (allTransitions == NULL) {
		UAP(lb_I_String, expression)
		UAP(lb_I_String, description)
		UAP(lb_I_Long, src_actionid)
		UAP(lb_I_Long, dst_actionid)
		UAP(lb_I_Query, query)

		if (db == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, db)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (db == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return NULL;
			}
			UAP(lb_I_Query, query)

			_LOG << "Read actionsteps sequentially from the database." LOG_

			db->init();

			const char* lbDMFPasswd = getenv("lbDMFPasswd");
			const char* lbDMFUser   = getenv("lbDMFUser");

			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			db->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		}

		query = db->getQuery("lbDMF", 0);

		char buf[] = "select expression, description, src_actionid, dst_actionid from action_step_transitions where src_actionid = %d or dst_actionid = %d";

		char* q = (char*) malloc(strlen(buf)+strlen(step->charrep())*2+1);
		q[0] = 0;
		sprintf(q, buf, (long) step->getData(), (long) step->getData());

		if (query->query(q) == ERR_NONE) {
			err = query->first();

			while (err == ERR_NONE) {
				description = query->getAsString(1);
				expression = query->getAsString(2);
				src_actionid = query->getAsLong(3);
				dst_actionid = query->getAsLong(4);
				stepTransitions->add(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				description = query->getAsString(1);
				expression = query->getAsString(2);
				src_actionid = query->getAsLong(3);
				dst_actionid = query->getAsLong(4);
				stepTransitions->add(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
			}
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, expression)
		UAP_REQUEST(getModuleInstance(), lb_I_String, description)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, src_actionid)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, dst_actionid)

		allTransitions->finishIteration();
		while (allTransitions->hasMoreElements()) {
			allTransitions->setNextElement();

			if (step->getData() == allTransitions->get_src_actionid() || step->getData() == allTransitions->get_dst_actionid()) {
				*description = allTransitions->get_description();
				*expression = allTransitions->get_expression();
				src_actionid->setData(allTransitions->get_src_actionid());
				dst_actionid->setData(allTransitions->get_dst_actionid());
				stepTransitions->add(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
			}
		}
	}

	if (stepTransitions->Count() == 0) {
		_LOG << "Warning: Do not have any transitions in stepTransitions object (step id = " << step->getData() << ")!" LOG_
	}


	if (found == true) {
		_LOG << "Info: Have " << stepTransitions->Count() << " transitions in stepTransitions object (step id = " << step->getData() << ")!" LOG_
		stepTransitions++;
		return stepTransitions.getPtr();
	}

	return NULL;
}

lb_I_ActionStep_Parameters* LB_STDCALL lbAction::loadParametersForActionStep(lb_I_Long* step, lb_I_ActionStep_Parameters* allActionStepParameters, lb_I_Parameter* allParameters) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_ActionStep_Parameters, stepParameters)
	AQUIRE_PLUGIN(lb_I_ActionStep_Parameters, Model, stepParameters, "'action step parameters'")
	bool found = false;
	if (allActionStepParameters == NULL) {
		UAP(lb_I_String, name)
		UAP(lb_I_String, value)
		UAP(lb_I_String, _interface)
		UAP(lb_I_String, description)
		UAP(lb_I_Query, query)

		if (db == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
			char* dbbackend = meta->getSystemDatabaseBackend();
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, db)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (db == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return NULL;
			}
			UAP(lb_I_Query, query)

			_LOG << "Read actionsteps sequentially from the database." LOG_

			db->init();

			const char* lbDMFPasswd = getenv("lbDMFPasswd");
			const char* lbDMFUser   = getenv("lbDMFUser");

			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";

			db->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);
		}

		query = db->getQuery("lbDMF", 0);

		char buf[] = "select name, value, interface, description from action_step_parameter where action_step_id = %d ";

		char* q = (char*) malloc(strlen(buf)+strlen(step->charrep())+1);
		q[0] = 0;
		sprintf(q, buf, (long) step->getData());

		_LOG << "Execute Query: " << q LOG_

		if (query->query(q) == ERR_NONE) {
			err = query->first();

			while (err == ERR_NONE) {
				name = query->getAsString(1);
				value = query->getAsString(2);
				_interface = query->getAsString(3);
				description = query->getAsString(4);
				
				if (allParameters != NULL) value->substitutePlaceholder(allParameters);
				
				stepParameters->add(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
				found = true;
				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				name = query->getAsString(1);
				value = query->getAsString(2);
				_interface = query->getAsString(3);
				description = query->getAsString(4);

				if (allParameters != NULL) value->substitutePlaceholder(allParameters);
				
				stepParameters->add(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
				found = true;
			}
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_String, _interface)
		UAP_REQUEST(getModuleInstance(), lb_I_String, description)

		allActionStepParameters->finishIteration();
		while (allActionStepParameters->hasMoreElements()) {
			allActionStepParameters->setNextElement();

			if (step->getData() == allActionStepParameters->get_action_step_id()) {
				*name = allActionStepParameters->get_name();
				*value = allActionStepParameters->get_value();
				*_interface = allActionStepParameters->get_interface();
				*description = allActionStepParameters->get_description();
				
				if (allParameters != NULL) value->substitutePlaceholder(allParameters);		
				
				stepParameters->add(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
				found = true;
			}
		}
	}

	if (found == true) {
		stepParameters++;
		return stepParameters.getPtr();
	}

	return NULL;
}


void LB_STDCALL lbAction::loadDataModel() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL && !initialized) {
		initialized = true;
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "Formulars";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formulars, forms)

		*name = "FormularFields";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formular_Fields, formularfields)

		*name = "FormActions";
		uk = document->getElement(&key);
		QI(uk, lb_I_Formular_Actions, formActions)

		*name = "FormParams";
		uk = document->getElement(&key);
		QI(uk, lb_I_FormularParameter, formParams)

		*name = "AppParams";
		uk = document->getElement(&key);
		QI(uk, lb_I_ApplicationParameter, appParams)

		*name = "AppActions";
		uk = document->getElement(&key);
		QI(uk, lb_I_Actions, appActions)

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)

		*name = "AppActionTypes";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Types, appActionTypes)

		*name = "appActionStepTransitions";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Step_Transitions, appActionStepTransitions)


		if ((forms == NULL) ||
		(formParams == NULL) ||
		(appActions == NULL) ||
		(appActionSteps == NULL) ||
		(appActionTypes == NULL) ||
		(appActionStepTransitions == NULL) ||
		(appParams == NULL)) {
			_LOG << "Error: Could not recieve one of the required document elements of application!" LOG_
		} else {
			// Preload more data.
		}
	}
}

long LB_STDCALL lbAction::getNextStepId(lb_I_Action_Step_Transitions* trans, lb_I_Parameter* params, long id) {
	long first_dst_actionid = -1;
	long first_dst_actionid_unmatched = -1;
	int transitions_matched = 0;
	int transitions_unmatched = 0;

	_LOG << "lbAction::getNextStepId() called with id = " << id LOG_

	if (trans == NULL) {
		_LOG << "Error: Need a transition object to calculate next action step!" LOG_
		return 0;
	}

	if (trans->Count() == 0) {
		_LOG << "Warning: Do not have any transitions in trans object!" LOG_
	}

	trans->finishIteration();
	while (trans->hasMoreElements()) {
		trans->setNextElement();

		if (trans->get_src_actionid() == id) {
			// First use a simple expression without any Lex & Yacc parser
			long dst_actionid;
			long src_actionid;
			wxString expression;
///\todo Choose new or old?
			expression = trans->get_expression();
			dst_actionid = trans->get_dst_actionid();
			src_actionid = trans->get_src_actionid();
			//expression = trans->getActionStepTransitionDecision();
			//dst_actionid = trans->getActionStepTransitionDstActionID();
			//src_actionid = trans->getActionStepTransitionSrcActionID();

			_LOG << "Evaluate expression '" << expression.c_str() << "' for transition = " << trans->get_id() <<
			", src_action = " << src_actionid << ", dst_action = " << dst_actionid LOG_

			if (expression.find("==") != -1) {
				// equal operator
				_LOG << "Error: Boolean expression not allowed!" LOG_
			} else {
				if (expression.find("!=") != -1) {
					// equal operator
					_LOG << "Error: Boolean expression not allowed!" LOG_
				} else {
					if (expression.find("=") != -1) {
						// assignment (typically adding a parameter to params)
						UAP_REQUEST(getModuleInstance(), lb_I_String, left)
						UAP_REQUEST(getModuleInstance(), lb_I_String, right)

						*left = expression.substr(0, expression.find("=")-1).c_str();
						*right = expression.substr(expression.find("=")+1).c_str();

						right->trim();
						right->trim(false);
						right->substitutePlaceholder(*&params);
						left->trim();
						left->trim(false);

						_LOG << "Have build left = '" << left->charrep() << "' and right = '" << right->charrep() << "' from expression = '" << expression.c_str() << "'" LOG_

						params->setUAPString(*&left, *&right);
						first_dst_actionid = dst_actionid;
						transitions_matched++;
					} else {
						if (expression.find("+=") != -1) {
							// append value to an existing string
							UAP_REQUEST(getModuleInstance(), lb_I_String, left)
							UAP_REQUEST(getModuleInstance(), lb_I_String, right)
							UAP_REQUEST(getModuleInstance(), lb_I_String, append)

							*left = expression.substr(0, expression.find("+=")-1).c_str();
							*right = expression.substr(expression.find("+=")+1).c_str();

							right->trim();
							right->trim(false);
							right->substitutePlaceholder(*&params);
							left->trim();
							left->trim(false);

							_LOG << "Have build left = '" << left->charrep() << "' and right = '" << right->charrep() << "' from expression = '" << expression.c_str() << "'" LOG_

							
							params->getUAPString(*&left, *&append);
							
							*append += right->charrep();
							
							params->setUAPString(*&left, *&append);
							first_dst_actionid = dst_actionid;
							transitions_matched++;
						} else {
							// Unmatched
							if (transitions_unmatched == 0) {
								first_dst_actionid_unmatched = dst_actionid;
							}
							transitions_unmatched++;
						}
					}
				}
			}
		}
	}

	if (transitions_unmatched > 1) {
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->msgBox("Error", "Expected one default transition, but have more. This is not correct.");
		return 0;
	}

	if (transitions_matched == 0) return first_dst_actionid_unmatched;

	return first_dst_actionid;
}

/*...svoid LB_STDCALL lbAction\58\\58\delegate\40\lb_I_Parameter\42\ params\41\:0:*/
long LB_STDCALL lbAction::delegate(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	long nextStep = -1; // A linear action per default

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	loadDataModel();

	/*
	 Resolve the parameters that we need here.
	 Currently only the id of the action step.
	 */
	/*...sbuild PREFIX:64:*/
#ifndef LINUX
#ifdef __WATCOMC__
#define PREFIX "_"
#endif
#ifdef _MSC_VER
#define PREFIX ""
#endif
#ifdef __MINGW32__
#define PREFIX ""
#endif
#endif
#ifdef LINUX
#define PREFIX ""
#endif
	/*...e*/

	char* pluginModule = NULL;


	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)

	if (actions == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, actions)
	}

	parameter->setData("id");
	params->getUAPLong(*&parameter, *&id);

	UAP(lb_I_Action_Step_Transitions, trans)
	trans = loadTransitionsForActionStep(*&id, *&appActionStepTransitions);

	if ((appActionTypes != NULL) && (appActionSteps != NULL)) {
		_LOG << "Execute actions based on lbDMFDataModel classes." LOG_
		UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
		UAP_REQUEST(getModuleInstance(), lb_I_String, module)
		UAP_REQUEST(getModuleInstance(), lb_I_String, key)
		UAP(lb_I_KeyBase, keybase)
		QI(key, lb_I_KeyBase, keybase)

		appActionSteps->selectById(id->getData());
		appActionTypes->selectById(appActionSteps->get_type());

		*action_handler = appActionTypes->get_action_handler();
		*module = appActionTypes->get_module();

		module->trim();
		action_handler->trim();

		*key = *&module;
		*key += *&action_handler;

		if (*key == "") {
			if (strcmp(appActionTypes->get_bezeichnung(), "InitialNode") == 0) {
				_LOG << appActionTypes->get_bezeichnung() << " for action '" << appActionSteps->get_bezeichnung() << "' ignored yet." LOG_
				// If the delegated action doesn't support transitions, do it here.

				return getNextStepId(*&trans, *&params, id->getData());
			}
			if (strcmp(appActionTypes->get_bezeichnung(), "FinalNode") == 0) {
				_LOG << appActionTypes->get_bezeichnung() << " for action '" << appActionSteps->get_bezeichnung() << "' ignored yet." LOG_
				return 0; // Stop processing
			}
		}

		_LOG << "Got action handler '" << action_handler->charrep() << "' from '" << module->charrep() <<
		"' for action ID = " << id->charrep() << ", type = " << appActionTypes->get_bezeichnung() <<
		" and name = " << appActionSteps->get_bezeichnung() LOG_

		if (actions->exists(&keybase) == 0) {
			/*...sInstanciate one and insert into actions:32:*/
			UAP(lb_I_Unknown, result)
			UAP(lb_I_String, pluginPath)
			char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
			ah[0] = 0;
			strcat(ah, PREFIX);
			strcat(ah, action_handler->charrep());

			pluginPath = PM->getPluginDirectory();

			makePluginName(pluginPath->charrep(), module->charrep(), pluginModule);
			_LOG << "Try to load a plugin at: " << pluginModule LOG_
			if (getModuleInstance()->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
				_LOG << "Error: Plugin not found. (" << pluginModule << ")" LOG_
			}
			free(pluginModule);
			pluginModule = NULL;
			if (result == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)
				*errmsg = "Failed to load module for configured action!\n\n";
				*errmsg += "Module: ";
				*errmsg += module->charrep();
				*errmsg += "\nAction handler: ";
				*errmsg += action_handler->charrep();
				meta->msgBox("Error", errmsg->charrep());
				return 0;
			}
			
			actions->insert(&result, &keybase);
/*...e*/
		}
		UAP(lb_I_DelegatedAction, action)
		UAP(lb_I_Unknown, uk)
		uk = actions->getElement(&keybase);
		QI(uk, lb_I_DelegatedAction, action)
		action->setActionID(id->getData());
		wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
		meta->setStatusText("Info", msg.c_str());
		_LOG << "Execute delegated action by document model..." LOG_



		action->setTransitions(*&trans);
		action->setParameter(loadParametersForActionStep(*&id, NULL, *&params));

		nextStep = action->execute(*&params);

		// If the delegated action doesn't support transitions, do it here.
		if (nextStep == -1) nextStep = getNextStepId(*&trans, *&params, id->getData());
		_LOG << "Next actionstep is " << nextStep << "." LOG_
	} else {
		UAP(lb_I_Query, query)

		query = db->getQuery("lbDMF", 0);

		char buf[] = "select action_handler, module from action_types inner join "
			"action_steps on action_types.id = action_steps.type where action_steps.id = %s";

		char* q = (char*) malloc(strlen(buf)+strlen(id->charrep())+1);
		q[0] = 0;
		sprintf(q, buf, id->charrep());

		if (query->query(q) == ERR_NONE) {
			lbErrCodes err = ERR_NONE;
			UAP_REQUEST(getModuleInstance(), lb_I_String, key)
			UAP(lb_I_KeyBase, ukey)

			err = query->first();

			while (err == ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
				UAP_REQUEST(getModuleInstance(), lb_I_String, module)
				UAP(lb_I_DelegatedAction, action)

				_LOG << "lbAction::delegate() executes action step ID: " << id->charrep() << " in while block." LOG_

				action_handler = query->getAsString(1);
				module = query->getAsString(2);
				action_handler->trim();
				module->trim();

				key->setData(module->charrep());
				*key += *&action_handler;

				QI(key, lb_I_KeyBase, ukey)

				if (actions->exists(&ukey) == 0) {
						/*...sInstanciate one and insert into actions:32:*/

						UAP(lb_I_Unknown, result)
						UAP(lb_I_String, pluginPath)

						char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
						ah[0] = 0;

						strcat(ah, PREFIX);
						strcat(ah, action_handler->charrep());

						pluginPath = PM->getPluginDirectory();

						makePluginName(pluginPath->charrep(), module->charrep(), pluginModule);

						_LOG << "Try to load a plugin at: " << pluginModule LOG_
						if (getModuleInstance()->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
							_LOG << "Error: Plugin not found. (" << pluginModule << ")" LOG_
						}

						if (result == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)

							*errmsg = "Failed to load module for configured action!\n\n";
							*errmsg += "Module: ";
							*errmsg += module->charrep();
							*errmsg += "\nAction handler: ";
							*errmsg += action_handler->charrep();


							meta->msgBox("Error", errmsg->charrep());
							return 0;
						}


						
						actions->insert(&result, &ukey);
						/*...e*/
					}

				UAP(lb_I_Unknown, uk)

				uk = actions->getElement(&ukey);

				QI(uk, lb_I_DelegatedAction, action)

				action->setActionID(id->getData());

				wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
				meta->setStatusText("Info", msg.c_str());
				UAP(lb_I_Action_Step_Transitions, trans)
				trans = loadTransitionsForActionStep(*&id, *&appActionStepTransitions);
				action->setTransitions(*&trans);
				action->setParameter(loadParametersForActionStep(*&id, NULL, *&params));
				nextStep = action->execute(*&params);

				// If the delegated action doesn't support transitions, do it here.
				if (nextStep == -1) nextStep = getNextStepId(*&trans, *&params, id->getData());

				_LOG << "Next actionstep is " << nextStep << "." LOG_

				_CL_LOG << "References for delegated action are " << action->getRefCount() << "." LOG_

				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, action_handler)
				UAP_REQUEST(getModuleInstance(), lb_I_String, module)
				UAP(lb_I_DelegatedAction, action)

				_LOG << "lbAction::delegate() executes action step ID: " << id->charrep() << " in if block." LOG_

				action_handler = query->getAsString(1);
				module = query->getAsString(2);
				action_handler->trim();
				module->trim();

				key->setData(module->charrep());
				*key += *&action_handler;

				QI(key, lb_I_KeyBase, ukey)

				if (actions->exists(&ukey) == 0) {

						UAP(lb_I_Unknown, result)
						UAP(lb_I_String, pluginPath)

						char* ah = (char*) malloc(strlen(PREFIX)+strlen(action_handler->charrep())+1);
						ah[0] = 0;

						strcat(ah, PREFIX);
						strcat(ah, action_handler->charrep());

						pluginPath = PM->getPluginDirectory();

						makePluginName(pluginPath->charrep(), module->charrep(), pluginModule);
						_LOG << "Try to load a plugin at: " << pluginModule LOG_
						if (getModuleInstance()->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
							_LOG << "Error: Plugin not found. (" << pluginModule << ")" LOG_
						}

						if (result == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, errmsg)

							*errmsg = "Failed to load module for configured action!\n\n";
							*errmsg += "Module: ";
							*errmsg += module->charrep();
							*errmsg += "\nAction handler: ";
							*errmsg += action_handler->charrep();


							meta->msgBox("Error", errmsg->charrep());
							return 0;
						}

						
						actions->insert(&result, &ukey);
						/*...e*/
					}

				UAP(lb_I_Unknown, uk)

				uk = actions->getElement(&ukey);

				QI(uk, lb_I_DelegatedAction, action)
				action->setActionID(id->getData());

				wxString msg = wxString("Execute delegated action '") + wxString(action->getClassName()) + wxString("'");
				meta->setStatusText("Info", msg.c_str());
				UAP(lb_I_Action_Step_Transitions, trans)
				trans = loadTransitionsForActionStep(*&id, *&appActionStepTransitions);
				action->setTransitions(*&trans);
				action->setParameter(loadParametersForActionStep(*&id, NULL));
				nextStep = action->execute(*&params);

				// If the delegated action doesn't support transitions, do it here.
				if (nextStep == -1) nextStep = getNextStepId(*&trans, *&params, id->getData());
				_LOG << "Next actionstep is " << nextStep << "." LOG_
			}
		} else {
			wxString errmsg = wxString("Error: Query for action handlers didn't found any handlers.");
			meta->setStatusText("Info", errmsg.c_str());
		}
	}
	return nextStep;
}
/*...e*/

/*...svoid LB_STDCALL lbAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
void LB_STDCALL lbAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;

	bool isNonLinearActivity = false;
	UAP_REQUEST(getModuleInstance(), lb_I_KeyBase, initialNodeKey)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, initialNode)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)

	loadDataModel();

		
	UAP_REQUEST(getModuleInstance(), lb_I_String, OSTypeVarName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, OSType)
	*OSTypeVarName = "OSType";
	*OSType = getOsType();
	params->setUAPString(*&OSTypeVarName, *&OSType);
	
	if (appActionSteps != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_Container, sortedActionSteps)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, order)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, stepid)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		_LOG << "Execute action steps based on actionsteps model." LOG_

		QI(order, lb_I_KeyBase, key)
		QI(stepid, lb_I_Unknown, uk)

		UAP_REQUEST(getModuleInstance(), lb_I_Long, actionid)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, actionidcmp)

		actionidcmp->setData(myActionID);

		appActionSteps->finishIteration();
		while (appActionSteps->hasMoreElements()) {
			appActionSteps->setNextElement();
			_LOG << "Sort entry ..." LOG_
			actionid->setData(appActionSteps->get_actionid());

			if (actionidcmp->equals(*&actionid)) {
			    _LOG << "Sort action steps by ordering column: " << appActionSteps->get_a_order_nr() << "." LOG_
				order->setData(appActionSteps->get_a_order_nr());
				stepid->setData(appActionSteps->get_id());
				sortedActionSteps->insert(&uk, &key);

				appActionTypes->finishIteration();
				appActionTypes->selectById(appActionSteps->get_type());

				_LOG << "Compare type to determine nonlinear action: '" << appActionTypes->get_bezeichnung() << "' == 'InitialNode'. Actionstep type is " << appActionSteps->get_type() LOG_

				if (strcmp(appActionTypes->get_bezeichnung(), "InitialNode") == 0) {
					_LOG << "Found initial node. " << appActionSteps->get_id() << " with order number " << key->charrep() LOG_
					isNonLinearActivity = true;
					initialNode->setData(order->getData());
				}
			}
		}
		appActionSteps->finishIteration();

		sortedActionSteps->finishIteration();

		if (isNonLinearActivity) {
			QI(initialNode, lb_I_KeyBase, initialNodeKey)
			if (sortedActionSteps->position(&initialNodeKey) != 1) {
				_LOG << "Error: Could not set initial node. Not found." LOG_
			}
		}

		while (sortedActionSteps->hasMoreElements() == 1) {
			uk = sortedActionSteps->nextElement();

			stepid->setData(*&uk);

			parameter->setData("id");
			params->setUAPLong(*&parameter, *&stepid);

			_LOG << "Delegate action (" << stepid->charrep() << ") ..." LOG_
			long nextStep = delegate(*&params);
			if (nextStep > 0) {
				// The sortedActionSteps key is based on order number (not on step number)
				appActionSteps->selectById(nextStep);
				order->setData(appActionSteps->get_a_order_nr());
				sortedActionSteps->position(&key); // Set the iterator position to the next step to be executed.
			} else {
				if (nextStep == 0) {
					// Cleanup and return
					_LOG << "Action exited with 0." LOG_
					return;
				}
			}
		}
		return;
	} else {
		char* dbbackend = meta->getSystemDatabaseBackend();
		if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
			AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, db, "'database plugin'")
			_LOG << "Using plugin database backend for UML import operation..." LOG_
		} else {
			// Use built in
			REQUEST(getModuleInstance(), lb_I_Database, db)
			_LOG << "Using built in database backend for UML import operation..." LOG_
		}

		if (db == NULL) {
			_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
			return;
		}
		UAP(lb_I_Query, query)

		_LOG << "Read actionsteps sequentially from the database." LOG_

		db->init();

		const char* lbDMFPasswd = getenv("lbDMFPasswd");
		const char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		db->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		query = db->getQuery("lbDMF", 0);

		char buf[] = "select id, a_order_no from action_steps where actionid = %d order by a_order_no";
		char* q = (char*) malloc(strlen(buf)+10);
		q[0] = 0;
		sprintf(q, buf, myActionID);

		_LOG << "Get action steps from id = " << myActionID << ". Query is " << q LOG_

			if (query->query(q) == ERR_NONE) {
				lbErrCodes err = query->first();

				while(err == ERR_NONE) {
					UAP_REQUEST(getModuleInstance(), lb_I_Long, id)

					id = query->getAsLong(1);

					parameter->setData("id");
					params->setUAPLong(*&parameter, *&id);

					long nextStep = delegate(*&params);

					if (nextStep > 0) {
						if (query->first() == ERR_NONE) {
							id = query->getAsLong(2); // The next possible order number to jump to

							while ((err != ERR_DB_NODATA) && (id->getData() != nextStep)) {
								err = query->next();
								id = query->getAsLong(2); // The next possible order number to jump to
							}
						}
					} else {
						if (nextStep == 0) {
							// Cleanup and return
							_LOG << "lbAction::execute() Action has been canceled at step " << id->charrep() << "." LOG_
							return;
						}
						err = query->next();
					}
				}

				if (err == WARN_DB_NODATA) {
					UAP_REQUEST(getModuleInstance(), lb_I_Long, id)

					id = query->getAsLong(1);

					parameter->setData("id");
					params->setUAPLong(*&parameter, *&id);

					long nextStep = delegate(*&params);

					if (nextStep > 0) {
						if (query->first() == ERR_NONE) {
							id = query->getAsLong(2); // The next possible order number to jump to

							while ((err != ERR_DB_NODATA) && (id->getData() != nextStep)) {
								err = query->next();
								id = query->getAsLong(2); // The next possible order number to jump to
							}
						}
					} else {
						if (nextStep == 0) {
							// Cleanup and return
							_LOG << "lbAction::execute() Action has been canceled at step " << id->charrep() << "." LOG_
							return;
						}
						err = query->next();
					}
				}
			} else {
				wxString errmsg = wxString("Fehler: Abfrage '") + wxString(buf) + wxString("' hat keine Daten geliefert.!");
				meta->setStatusText("Info", errmsg.c_str());
			}
	}
}
/*...e*/

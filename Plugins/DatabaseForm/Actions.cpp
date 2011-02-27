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
	ref = STARTREF;
	myActionID = -1;
	initialized = false;
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

			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");

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
				stepTransitions->addTransition(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				description = query->getAsString(1);
				expression = query->getAsString(2);
				src_actionid = query->getAsLong(3);
				dst_actionid = query->getAsLong(4);
				stepTransitions->addTransition(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
			}
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, expression)
		UAP_REQUEST(getModuleInstance(), lb_I_String, description)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, src_actionid)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, dst_actionid)

		allTransitions->finishActionStepTransitionIteration();
		while (allTransitions->hasMoreActionStepTransitions()) {
			allTransitions->setNextActionStepTransition();

			if (step->getData() == allTransitions->getActionStepTransitionSrcActionID() || step->getData() == allTransitions->getActionStepTransitionDstActionID()) {
				*description = allTransitions->getActionStepTransitionDescription();
				*expression = allTransitions->getActionStepTransitionDecision();
				src_actionid->setData(allTransitions->getActionStepTransitionSrcActionID());
				dst_actionid->setData(allTransitions->getActionStepTransitionDstActionID());
				stepTransitions->addTransition(expression->charrep(), src_actionid->getData(), dst_actionid->getData(), description->charrep());
				found = true;
			}
		}
	}

	if (stepTransitions->getActionStepTransitionsCount() == 0) {
		_LOG << "Warning: Do not have any transitions in stepTransitions object (step id = " << step->getData() << ")!" LOG_
	}


	if (found == true) {
		_LOG << "Info: Have " << stepTransitions->getActionStepTransitionsCount() << " transitions in stepTransitions object (step id = " << step->getData() << ")!" LOG_
		stepTransitions++;
		return stepTransitions.getPtr();
	}

	return NULL;
}

lb_I_ActionStep_Parameters* LB_STDCALL lbAction::loadParametersForActionStep(lb_I_Long* step, lb_I_ActionStep_Parameters* allActionStepParameters) {
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

			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");

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
				stepParameters->addActionStepParameter(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
				found = true;
				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				name = query->getAsString(1);
				value = query->getAsString(2);
				_interface = query->getAsString(3);
				description = query->getAsString(4);
				stepParameters->addActionStepParameter(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
				found = true;
			}
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_String, _interface)
		UAP_REQUEST(getModuleInstance(), lb_I_String, description)

		allActionStepParameters->finishActionStepParameterIteration();
		while (allActionStepParameters->hasMoreActionStepParameters()) {
			allActionStepParameters->setNextActionStepParameter();

			if (step->getData() == allActionStepParameters->getActionStepParameterActionID()) {
				*name = allActionStepParameters->getActionStepParameterName();
				*value = allActionStepParameters->getActionStepParameterValue();
				*_interface = allActionStepParameters->getActionStepParameterInterface();
				*description = allActionStepParameters->getActionStepParameterDescription();
				stepParameters->addActionStepParameter(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), step->getData());
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

	_LOG << "lbAction::getNextStepId() called with id = " << id LOG_

	if (trans == NULL) {
		_LOG << "Error: Need a transition object to calculate next action step!" LOG_
		return 0;
	}

	if (trans->getActionStepTransitionsCount() == 0) {
		_LOG << "Warning: Do not have any transitions in trans object!" LOG_
	}

	trans->finishActionStepTransitionIteration();
	while (trans->hasMoreActionStepTransitions()) {
		trans->setNextActionStepTransition();

		if (trans->getActionStepTransitionSrcActionID() == id) {
			// First use a simple expression without any Lex & Yacc parser
			long dst_actionid;
			long src_actionid;
			wxString expression;
			expression = trans->getActionStepTransitionDecision();
			dst_actionid = trans->getActionStepTransitionDstActionID();
			src_actionid = trans->getActionStepTransitionSrcActionID();

			first_dst_actionid_unmatched = dst_actionid;

			_LOG << "Evaluate expression '" << expression.c_str() << "' for transition = " << trans->getActionStepTransitionID() <<
			", src_action = " << src_actionid << ", dst_action = " << dst_actionid LOG_

			if (expression.find("==") != -1) {
				// equal operator
				_LOG << "Error: Boolean expression not allowed!" LOG_
			} else
				if (expression.find("!=") != -1) {
					// equal operator
					_LOG << "Error: Boolean expression not allowed!" LOG_
				} else
					if (expression.find("=") != -1) {
						// assignment (typically adding a parameter to params
						UAP_REQUEST(getModuleInstance(), lb_I_String, left)
						UAP_REQUEST(getModuleInstance(), lb_I_String, right)

						*left = expression.substr(0, expression.find("=")-1).c_str();
						*right = expression.substr(expression.find("=")+1).c_str();

						right->trim();
						right->replace(" ", "");
						left->trim();

						_LOG << "Have build left = '" << left->charrep() << "' and right = '" << right->charrep() << "' from expression = '" << expression.c_str() << "'" LOG_

						params->setUAPString(*&left, *&right);
						first_dst_actionid = dst_actionid;
						transitions_matched++;
					}
		}
	}

	if (transitions_matched > 1) {
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->msgBox("Error", "Expected one transition, but have more. This is not correct.");
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
		REQUEST(manager.getPtr(), lb_I_Container, actions)
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

		appActionSteps->selectActionStep(id->getData());
		appActionTypes->selectActionType(appActionSteps->getActionStepType());

		*action_handler = appActionTypes->getActionTypeHandler();
		*module = appActionTypes->getActionTypeModule();

		module->trim();
		action_handler->trim();

		*key = *&module;
		*key += *&action_handler;

		if (*key == "") {
			if (strcmp(appActionTypes->getActionTypeBezeichnung(), "InitialNode") == 0) {
				_LOG << appActionTypes->getActionTypeBezeichnung() << " for action '" << appActionSteps->getActionStepBezeichnung() << "' ignored yet." LOG_
				// If the delegated action doesn't support transitions, do it here.

				return getNextStepId(*&trans, *&params, id->getData());
			}
			if (strcmp(appActionTypes->getActionTypeBezeichnung(), "FinalNode") == 0) {
				_LOG << appActionTypes->getActionTypeBezeichnung() << " for action '" << appActionSteps->getActionStepBezeichnung() << "' ignored yet." LOG_
				return 0; // Stop processing
			}
		}

		_LOG << "Got action handler '" << action_handler->charrep() << "' from '" << module->charrep() <<
		"' for action ID = " << id->charrep() << ", type = " << appActionTypes->getActionTypeBezeichnung() <<
		" and name = " << appActionSteps->getActionStepBezeichnung() LOG_

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
			if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
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
			result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
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
		action->setParameter(loadParametersForActionStep(*&id, NULL));

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
			UAP_REQUEST(manager.getPtr(), lb_I_String, key)
			UAP(lb_I_KeyBase, ukey)

			err = query->first();

			while (err == ERR_NONE) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
				UAP_REQUEST(manager.getPtr(), lb_I_String, module)
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
						if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
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


						result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
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

				_CL_LOG << "References for delegated action are " << action->getRefCount() << "." LOG_

				err = query->next();
			}

			if (err == WARN_DB_NODATA) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, action_handler)
				UAP_REQUEST(manager.getPtr(), lb_I_String, module)
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
						if (manager->makeInstance(ah, pluginModule,  &result) != ERR_NONE) {
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

						result->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
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
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	loadDataModel();

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

		appActionSteps->finishActionStepIteration();
		while (appActionSteps->hasMoreActionSteps()) {
			appActionSteps->setNextActionStep();
			_LOG << "Sort entry ..." LOG_
			actionid->setData(appActionSteps->getActionStepActionID());

			if (actionidcmp->equals(*&actionid)) {
			    _LOG << "Sort action steps by ordering column: " << appActionSteps->getActionStepOrderNo() << "." LOG_
				order->setData(appActionSteps->getActionStepOrderNo());
				stepid->setData(appActionSteps->getActionStepID());
				sortedActionSteps->insert(&uk, &key);

				appActionTypes->finishActionTypeIteration();
				appActionTypes->selectActionType(appActionSteps->getActionStepType());

				_LOG << "Compare type to determine nonlinear action: '" << appActionTypes->getActionTypeBezeichnung() << "' == 'InitialNode'. Actionstep type is " << appActionSteps->getActionStepType() LOG_

				if (strcmp(appActionTypes->getActionTypeBezeichnung(), "InitialNode") == 0) {
					_LOG << "Found initial node. " << appActionSteps->getActionStepID() << " with order number " << key->charrep() LOG_
					isNonLinearActivity = true;
					initialNode->setData(order->getData());
				}
			}
		}
		appActionSteps->finishActionStepIteration();

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
				appActionSteps->selectActionStep(nextStep);
				order->setData(appActionSteps->getActionStepOrderNo());
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

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

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
					UAP_REQUEST(manager.getPtr(), lb_I_Long, id)

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
					UAP_REQUEST(manager.getPtr(), lb_I_Long, id)

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

/*...slbDetailFormAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDetailFormAction)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDetailFormAction, lbDetailFormAction)

lbErrCodes LB_STDCALL lbDetailFormAction::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbDetailFormAction::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbDetailFormAction::lbDetailFormAction() {
	ref = STARTREF;
	myActionID = -1;
	detailForm = NULL;
}

lbDetailFormAction::~lbDetailFormAction() {
}

void LB_STDCALL lbDetailFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDetailFormAction::setActionID(long id) {
	myActionID = id;
}

/*...svoid LB_STDCALL lbDetailFormAction\58\\58\openDetailForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
bool LB_STDCALL lbDetailFormAction::openDetailForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbDetailFormAction::openDetailForm() called." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)
	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&masterForm);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("actionID");
	actionID->setData(myActionID);
	params->setUAPLong(*&parameter, *&actionID);
	parameter->setData("application");
	params->getUAPString(*&parameter, *&app);

	UAP(lb_I_GUI, gui)
	meta->getGUI(&gui);

	UAP(lb_I_DatabaseForm, df)
	df = gui->findDBForm(formularname->charrep());

	if (df == NULL) {
		_LOG << "Detailform '" << formularname->charrep() << "' nicht gefunden. Setze variable zur√ºck." LOG_
		detailForm = NULL;
	}

	if (df != detailForm) {
		// The form may physically another instance.
		detailForm = df.getPtr();
	}

	if (detailForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_

		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();

		detailForm->setName(formularname->charrep(), parameter->charrep());

		_LOG << "Search the masterform '" << masterForm->charrep() << "'." LOG_

		lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		if (f == NULL) {
			_LOG << "Error: Bail out, no master form found." LOG_
			return false;
		}

		detailForm->setMasterForm(f, *&params);

		detailForm->updateFromMaster();
		gui->showForm(formularname->charrep());
	} else {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, docparams)

		uk = meta->getActiveDocument();
		QI(uk, lb_I_Parameter, docparams)

		if (docparams != NULL) {
			// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
			UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_Action_Steps, appActionSteps)
			UAP(lb_I_KeyBase, key)

			UAP(lb_I_Unknown, uk)
			UAP(lb_I_Formulars, forms)
			UAP(lb_I_FormularParameter, formParams)

			docparams->setCloning(false);
			document->setCloning(false);

			QI(name, lb_I_KeyBase, key)
			*name = "ApplicationData";
			docparams->getUAPContainer(*&name, *&document);

			*name = "Formulars";
			uk = document->getElement(&key);
			QI(uk, lb_I_Formulars, forms)

			*name = "FormParams";
			uk = document->getElement(&key);
			QI(uk, lb_I_FormularParameter, formParams)


			if ((formParams != NULL) && (forms != NULL)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
				long AppID = meta->getApplicationID();

				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();

					if ((forms->getApplicationID() == AppID) && (strcmp(forms->getName(), formularname->charrep()) == 0)) {
						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, master)
						UAP(lb_I_DatabaseForm, form)
						long FormularID = forms->getFormularID();
						*SQL = formParams->getParameter("query", FormularID);
						forms->finishFormularIteration();
						form = gui->createDBForm(formularname->charrep(),
												 SQL->charrep(),
												 DBName->charrep(),
												 DBUser->charrep(),
												 DBPass->charrep());
						if (form == NULL) {
							_CL_LOG << "Error: Bail out, detail form could not be created." LOG_
							return false;
						}
						detailForm = form.getPtr();
						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						form->setName(formularname->charrep(), parameter->charrep());
						_LOG << "Search the masterform '" << masterForm->charrep() << "'." LOG_
						f = gui->findDBForm(masterForm->charrep());
						if (f == NULL) {
							_LOG << "Error: Bail out, no master form found." LOG_

							if (detailForm != NULL) {
								// Cleanup
								detailForm->destroy();
							}

							return false;
						}
						QI(f, lb_I_DatabaseForm, master)
						UAP_REQUEST(manager.getPtr(), lb_I_String, table)
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)
						// The connection may be closed.
						master->reopen();
						master->getPrimaryColumns();
						*column = master->getColumnName(1);
						*table = master->getTableName(column->charrep());
						form->ignoreForeignKeys(table->charrep());
						form->setMasterForm(*&master, *&params);
						gui->showForm(formularname->charrep());
						form++;
						return true;
					}
				}
				meta->setStatusText("Info", "Did not found detailform.");
				return false;
			}
		}

		// - old database variant -

		_LOG << "Open detail form the old database way." LOG_

		//lb_I_DatabaseForm* f = gui->findDBForm(masterForm->charrep());

		/*...sGet the SQL query based on formular name\44\ application name\46\:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_String, user)
		meta->getUserName(&user);

		char* b =
		"select Formulare.id from Formulare "
		"inner join Anwendungen on Formulare.anwendungid = Anwendungen.id inner join "
		"User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		" User_Anwendungen.userid = Users.id where "
		"Users.userid = '%s' and Anwendungen.name = '%s' and "
		"Formulare.name = '%s'";

		char* buffer = (char*) malloc(strlen(b)+
									  strlen(user->charrep())+
									  strlen(app->charrep())+
									  strlen(formularname->charrep())+1);

		buffer[0] = 0;

		sprintf(buffer, b, user->charrep(), app->charrep(), formularname->charrep());

		UAP(lb_I_Database, database)
		char* dbbackend = meta->getSystemDatabaseBackend();
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
			return false;
		}

		UAP(lb_I_Query, query)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		query = database->getQuery("lbDMF", 0);
		/*...e*/

		if (query->query(buffer) == ERR_NONE) {
			lbErrCodes err = query->first();

			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, id)

				/*...sPrepare query to get parameter value based on given ID:32:*/
				id = query->getAsString(1);

				char* b = "select parametervalue from Formular_Parameters where formularid = %s";

				char* buffer = (char*) malloc(strlen(b)+strlen(id->charrep())+1);
				buffer[0] = 0;
				sprintf(buffer, b, id->charrep());

				UAP(lb_I_Query, query)

				query = database->getQuery("lbDMF", 0);

				err = query->query(buffer);
				/*...e*/

				if (err == ERR_NONE) {
					/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();

					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk)

						sql = query->getAsString(1);

						UAP(lb_I_DatabaseForm, form)

						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui)
						meta->getGUI(&gui);

						form = gui->createDBForm(formularname->charrep(),
												 sql->charrep(),
												 DBName->charrep(),
												 DBUser->charrep(),
												 DBPass->charrep());

						if (form == NULL) {
							_CL_LOG << "Error: Bail out, detail form could not be created." LOG_
							return false;
						}

						detailForm = form.getPtr();

						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();

						form->setName(formularname->charrep(), parameter->charrep());

						/*...sDocs:136:*/
						/* Set the other information of master / detail form here

						 There is a problem for forms, if the foreign key is not
						 shown in it. In that case the relation could not full filled
						 by the add action.

						 The only way may be any kind of temporal default value.
						 */
						/*...e*/

						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, master)

						f = gui->findDBForm(masterForm->charrep());

						if (f == NULL) {
							_CL_LOG << "Error: Bail out, no master form found." LOG_

							if (detailForm != NULL) {
								// Cleanup
								detailForm->destroy();
							}

							return false;
						}

						QI(f, lb_I_DatabaseForm, master)

						UAP_REQUEST(manager.getPtr(), lb_I_String, table)
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)

						master->getPrimaryColumns();

						*column = master->getColumnName(1);
						*table = master->getTableName(column->charrep());

						form->ignoreForeignKeys(table->charrep());

						//form->init(sql->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());

						form->setMasterForm(*&master, *&params);

						/*...e*/

						/*...sSome docs:88:*/
						/*
						 * What should I do to 'interconnect' the forms over the
						 * relation 'customer number' ?
						 *
						 * lbDetailFormAction could manage these information and
						 * control the form class over the existing interface.
						 *
						 * These are the setFilter and setMasterForm functions.
						 *
						 * With these functions, it is possible to only show data,
						 * that is related to both, the master form and detail form
						 * data.
						 *
						 * setFilter could set the following value:
						 *
						 * " where customerid =
						 *     (select id from <table of masterForm> where <SourceFieldName> = '<SourceFieldValue>')"
						 */
						/*...e*/

						// Get the related table for the source field

						gui->showForm(formularname->charrep());
						form++;
						return true;
					}
					/*...e*/
				} else {
					_CL_LOG << "ERROR: Expected query for the formular ID failed:\n" << buffer LOG_
					free(buffer);
				}
			} else {
				_CL_LOG << "ERROR: No data found for query to get detailform:\n\n" << buffer LOG_
				free(buffer);
			}
		}
	}
	return false;
}
/*...e*/

void LB_STDCALL lbDetailFormAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {

}

void LB_STDCALL lbDetailFormAction::setParameter(lb_I_ActionStep_Parameters* myParams) {

}


/*...svoid LB_STDCALL lbDetailFormAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
long LB_STDCALL lbDetailFormAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbDetailFormAction::execute() called" LOG_
	/*...sInit variables for params:8:*/
	if (masterForm == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, masterForm)
	}
	if (SourceFieldName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	}
	if (SourceFieldValue == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	}
	if (app == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, app)
	}
	if (DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBName)
	}
	if (DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBUser)
	}
	if (DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBPass)
	}
	/*...e*/

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)


	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)


		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();

			*msg = "Open detail form (";
			*msg += What->charrep();
			*msg += ")";

			meta->setStatusText("Info", msg->charrep());
			openDetailForm(*&What, *&params);
			return -1;
		}
	}

	// - Old database variant -

	UAP(lb_I_Database, database)
	char* dbbackend = meta->getSystemDatabaseBackend();
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
		return 0;
	}
	UAP(lb_I_Query, query)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);

	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {

		lbErrCodes err = query->first();

		while(err == ERR_NONE) {
			/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)

			what = query->getAsString(1);
			what->trim();

			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

			*msg = "Open detail form (";
			*msg += what->charrep();
			*msg += ")";

			meta->setStatusText("Info", msg->charrep());

			openDetailForm(*&what, *&params);

			err = query->next();
			/*...e*/
		}

		if (err == WARN_DB_NODATA) {
			/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)

			what = query->getAsString(1);
			what->trim();

			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

			*msg = "Open detail form (";
			*msg += what->charrep();
			*msg += ")";

			meta->setStatusText("Info", msg->charrep());

			openDetailForm(*&what, *&params);
			/*...e*/
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)

		ID->setData(myActionID);

		*msg = "lbDetailFormAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
	}
	return -1;
}
/*...e*/
/*...e*/
/*...slbMasterFormAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbMasterFormAction)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbMasterFormAction, lbMasterFormAction)

lbErrCodes LB_STDCALL lbMasterFormAction::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbMasterFormAction::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbMasterFormAction::lbMasterFormAction() {
	ref = STARTREF;
	myActionID = -1;
	masterForm = NULL;
}

lbMasterFormAction::~lbMasterFormAction() {
}

void LB_STDCALL lbMasterFormAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbMasterFormAction::setActionID(long id) {
	myActionID = id;
}

/*...svoid LB_STDCALL lbMasterFormAction\58\\58\openMasterForm\40\lb_I_String\42\ formularname\44\ lb_I_Parameter\42\ params\41\:0:*/
bool LB_STDCALL lbMasterFormAction::openMasterForm(lb_I_String* formularname, lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbMasterFormAction::openMasterForm() called." LOG_
	UAP_REQUEST(manager.getPtr(), lb_I_Long, actionID)
	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&detailForm);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("actionID");
	actionID->setData(myActionID);
	params->setUAPLong(*&parameter, *&actionID);
	parameter->setData("application");
	params->getUAPString(*&parameter, *&app);

	UAP(lb_I_GUI, gui)
	meta->getGUI(&gui);

	UAP(lb_I_DatabaseForm, df)
	df = gui->findDBForm(formularname->charrep());

	if (df == NULL) {
		_LOG << "Masterform '" << formularname->charrep() << "' nicht gefunden. Setze variable zur√ºck." LOG_
		masterForm = NULL;
	}

	/// \todo This is a possible bug if there are more than one such form.
	if (masterForm != NULL) {
		_CL_VERBOSE << "Show previously created form." LOG_

		*parameter = " - ";
		*parameter += SourceFieldValue->charrep();

		masterForm->setName(formularname->charrep(), parameter->charrep());

		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

		if (f == NULL) {
			_CL_LOG << "ERROR: Could not find detail form. Bail out." LOG_
			return 0;
		}

		masterForm->setDetailForm(f, *&params);

		masterForm->updateFromDetail();
		gui->showForm(formularname->charrep());
	} else {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, docparams)

		uk = meta->getActiveDocument();
		QI(uk, lb_I_Parameter, docparams)

		if (docparams != NULL) {
			// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
			UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
			UAP_REQUEST(getModuleInstance(), lb_I_String, name)
			UAP(lb_I_Action_Steps, appActionSteps)
			UAP(lb_I_KeyBase, key)
			UAP(lb_I_Unknown, uk)

			UAP(lb_I_Formulars, forms)
			UAP(lb_I_FormularParameter, formParams)

			docparams->setCloning(false);
			document->setCloning(false);

			QI(name, lb_I_KeyBase, key)
			*name = "ApplicationData";
			docparams->getUAPContainer(*&name, *&document);

			*name = "Formulars";
			uk = document->getElement(&key);
			QI(uk, lb_I_Formulars, forms)

			*name = "FormParams";
			uk = document->getElement(&key);
			QI(uk, lb_I_FormularParameter, formParams)


			if ((formParams != NULL) && (forms != NULL)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, SQL)
				long AppID = meta->getApplicationID();

				while (forms->hasMoreFormulars()) {
					forms->setNextFormular();

					if ((forms->getApplicationID() == AppID) && (strcmp(forms->getName(), formularname->charrep()) == 0)) {
						UAP_REQUEST(getModuleInstance(), lb_I_String, table)
						UAP_REQUEST(getModuleInstance(), lb_I_String, column)
						UAP(lb_I_DatabaseForm, form)
						UAP(lb_I_DatabaseForm, f)
						UAP(lb_I_DatabaseForm, detail)

						long FormularID = forms->getFormularID();
						*SQL = formParams->getParameter("query", FormularID);
						form = gui->createDBForm(formularname->charrep(),
												 SQL->charrep(),
												 DBName->charrep(),
												 DBUser->charrep(),
												 DBPass->charrep());
						masterForm = form.getPtr();
						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();
						form->setName(formularname->charrep(), parameter->charrep());
						f = gui->findDBForm(detailForm->charrep());
						QI(f, lb_I_DatabaseForm, detail)
						detail->getPrimaryColumns();
						*column = detail->getColumnName(1);
						*table = detail->getTableName(column->charrep());
						form->ignoreForeignKeys(table->charrep());
						form->setDetailForm(*&detail, *&params);
						gui->showForm(formularname->charrep());
						form++;
						return -1;
					}
				}
				meta->setStatusText("Info", "Did not found masterform.");
				return 0;
			}
		}

		// - old database variant -


		lb_I_DatabaseForm* f = gui->findDBForm(detailForm->charrep());

		if (f == NULL) {
			_CL_LOG << "ERROR: Could not find detail form. Bail out." LOG_
			return 0;
		}

		/*...sGet the SQL query based on formular name\44\ application name\46\:16:*/
		UAP_REQUEST(manager.getPtr(), lb_I_String, user)
		meta->getUserName(&user);

		char* b =
		"select Formulare.id from Formulare inner join Anwendungen_Formulare on "
		"Formulare.id = Anwendungen_Formulare.formularid "
		"inner join Anwendungen on Anwendungen_Formulare.anwendungid = Anwendungen.id inner join "
		"User_Anwendungen on Anwendungen.id = User_Anwendungen.anwendungenid inner join Users on "
		" User_Anwendungen.userid = Users.id where "
		"Users.userid = '%s' and Anwendungen.name = '%s' and "
		"Formulare.name = '%s'";

		char* buffer = (char*) malloc(strlen(b)+
									  strlen(user->charrep())+
									  strlen(app->charrep())+
									  strlen(formularname->charrep())+1);

		buffer[0] = 0;

		sprintf(buffer, b, user->charrep(), app->charrep(), formularname->charrep());

		UAP(lb_I_Database, database)
		char* dbbackend = meta->getSystemDatabaseBackend();
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
			return 0;
		}
		UAP(lb_I_Query, query)

		database->init();

		char* lbDMFPasswd = getenv("lbDMFPasswd");
		char* lbDMFUser   = getenv("lbDMFUser");

		if (!lbDMFUser) lbDMFUser = "dba";
		if (!lbDMFPasswd) lbDMFPasswd = "trainres";

		database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

		query = database->getQuery("lbDMF", 0);
		/*...e*/

		if (query->query(buffer) == ERR_NONE) {
			lbErrCodes err = query->first();

			if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				UAP_REQUEST(manager.getPtr(), lb_I_String, id)

				/*...sPrepare query to get parameter value based on given ID:32:*/
				id = query->getAsString(1);

				char* b = "select parametervalue from formular_parameters where formularid = %s";

				char* buffer = (char*) malloc(strlen(b)+strlen(id->charrep())+1);
				buffer[0] = 0;
				sprintf(buffer, b, id->charrep());

				UAP(lb_I_Query, query)

				query = database->getQuery("lbDMF", 0);

				err = query->query(buffer);
				/*...e*/

				if (err == ERR_NONE) {
					/*...sTake result as the SQL query parameter for the detail form:40:*/
					UAP_REQUEST(manager.getPtr(), lb_I_PluginManager, PM)
					UAP(lb_I_Plugin, pl)
					UAP_REQUEST(manager.getPtr(), lb_I_String, sql)

					err = query->first();

					if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
						/*...sTry load the detail form and make basic setup:88:*/
						UAP(lb_I_Unknown, uk)

						sql = query->getAsString(1);

						UAP(lb_I_DatabaseForm, form)
						UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
						UAP(lb_I_GUI, gui)

						meta->getGUI(&gui);

						form = gui->createDBForm(formularname->charrep(),
												 sql->charrep(),
												 DBName->charrep(),
												 DBUser->charrep(),
												 DBPass->charrep());

						masterForm = form.getPtr();

						*parameter = " - ";
						*parameter += SourceFieldValue->charrep();

						form->setName(formularname->charrep(), parameter->charrep());

						/* Set the other information of master / detail form here

						 There is a problem for forms, if the foreign key is not
						 shown in it. In that case the relation could not full filled
						 by the add action.

						 The only way may be any kind of temporal default value.
						 */

						UAP(lb_I_DatabaseForm, f)

						UAP(lb_I_DatabaseForm, detail)

						f = gui->findDBForm(detailForm->charrep());

						QI(f, lb_I_DatabaseForm, detail)

						UAP_REQUEST(manager.getPtr(), lb_I_String, table)
						UAP_REQUEST(manager.getPtr(), lb_I_String, column)

						detail->getPrimaryColumns();

						*column = detail->getColumnName(1);
						*table = detail->getTableName(column->charrep());

						form->ignoreForeignKeys(table->charrep());

						//form->init(sql->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep());

						form->setDetailForm(*&detail, *&params);
						/*...e*/

						/*...sSome docs:88:*/
						/*
						 * What should I do to 'interconnect' the forms over the
						 * relation 'customer number' ?
						 *
						 * lbMasterFormAction could manage these information and
						 * control the form class over the existing interface.
						 *
						 * These are the setFilter and setMasterForm functions.
						 *
						 * With these functions, it is possible to only show data,
						 * that is related to both, the master form and detail form
						 * data.
						 *
						 * setFilter could set the following value:
						 *
						 * " where customerid =
						 *     (select id from <table of masterForm> where <SourceFieldName> = '<SourceFieldValue>')"
						 */
						/*...e*/

						// Get the related table for the source field

						gui->showForm(formularname->charrep());
						form++;
					}
					/*...e*/
				} else {
					_CL_LOG << "ERROR: Expected query for the formular ID failed:\n" << buffer LOG_
				}
			}
		}
	}
	return -1;
}
/*...e*/

void LB_STDCALL lbMasterFormAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {

}

void LB_STDCALL lbMasterFormAction::setParameter(lb_I_ActionStep_Parameters* myParams) {

}

/*...svoid LB_STDCALL lbMasterFormAction\58\\58\execute\40\lb_I_Parameter\42\ params\41\:0:*/
long LB_STDCALL lbMasterFormAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_LOG "lbMasterFormAction::execute() called" LOG_
	/*...sInit variables for params:8:*/
	if (masterForm == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, detailForm)
	}
	if (SourceFieldName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	}
	if (SourceFieldValue == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	}
	if (app == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, app)
	}
	if (DBName == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBName)
	}
	if (DBUser == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBUser)
	}
	if (DBPass == NULL) {
		REQUEST(manager.getPtr(), lb_I_String, DBPass)
	}
	/*...e*/

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)


		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();

			*msg = "Open master form (";
			*msg += What->charrep();
			*msg += ")";

			meta->setStatusText("Info", msg->charrep());
			openMasterForm(*&What, *&params);
			return -1;
		}
	}

	// - Old database variant -

	UAP(lb_I_Database, database)
	char* dbbackend = meta->getSystemDatabaseBackend();
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
		return 0;
	}
	UAP(lb_I_Query, query)

	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);

	char buf[] = "select what from action_steps where id = %d";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	if (query->query(q) == ERR_NONE) {

		lbErrCodes err = query->first();

		while(err == ERR_NONE) {
			/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)

			what = query->getAsString(1);
			what->trim();

			openMasterForm(*&what, *&params);

			err = query->next();
			/*...e*/
		}

		if (err == WARN_DB_NODATA) {
			/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)

			what = query->getAsString(1);
			what->trim();

			openMasterForm(*&what, *&params);
			/*...e*/
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)

		ID->setData(myActionID);

		*msg = "lbMasterFormAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
		return 0;
	}

	return -1;
}
/*...e*/
/*...e*/
/*...slbSQLQueryAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbSQLQueryAction)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbSQLQueryAction, lbSQLQueryAction)

lbErrCodes LB_STDCALL lbSQLQueryAction::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbSQLQueryAction::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbSQLQueryAction::lbSQLQueryAction() {
	ref = STARTREF;
	myActionID = -1;
}

lbSQLQueryAction::~lbSQLQueryAction() {
}

void LB_STDCALL lbSQLQueryAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbSQLQueryAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbSQLQueryAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
}

void LB_STDCALL lbSQLQueryAction::setParameter(lb_I_ActionStep_Parameters* myParams) {

}

long LB_STDCALL lbSQLQueryAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbSQLQueryAction::execute()" LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("source field");
	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&SourceFormName);

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)


		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();

			*msg = "Execute query (";
			*msg += What->charrep();
			*msg += ")";

			meta->setStatusText("Info", msg->charrep());

			UAP(lb_I_Database, db)
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
				return 0;
			}
			db->init();
			if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
				meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
				return 0;
			}

			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";

			wxString s = wxString(What->charrep());

			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*What = s.c_str();

			if ((err = q->query(What->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
			}
			q->enableFKCollecting();

			return -1;
		}
	}

	// - Old database variant -

	UAP(lb_I_Database, database)
	char* dbbackend = meta->getSystemDatabaseBackend();
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
		return 0;
	}
	UAP(lb_I_Query, query)



	database->init();

	char* lbDMFPasswd = getenv("lbDMFPasswd");
	char* lbDMFUser   = getenv("lbDMFUser");

	if (!lbDMFUser) lbDMFUser = "dba";
	if (!lbDMFPasswd) lbDMFPasswd = "trainres";

	database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd);

	query = database->getQuery("lbDMF", 0);

	char buf[] = "select what from action_steps where id = %d order by a_order_nr";
	char* q = (char*) malloc(strlen(buf)+20);
	q[0] = 0;
	sprintf(q, buf, myActionID);

	UAP(lb_I_Database, db)
	dbbackend = meta->getSystemDatabaseBackend();

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
		return 0;
	}
	db->init();
	if (db->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE) {
		meta->msgBox("Error", "Failed to execute SQL query. Connection failed.");
		return 0;
	}

	if (query->query(q) == ERR_NONE) {

		lbErrCodes err = query->first();

		while(err == ERR_NONE) {
			/*...sFor each row open the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";

			wxString s = wxString(what->charrep());

			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s.c_str();
			if ((err = q->query(what->charrep(), false)) != ERR_NONE && err != ERR_DB_NODATA) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
			}
			q->enableFKCollecting();

			err = query->next();
			/*...e*/
		}

		if (err == WARN_DB_NODATA) {
			/*...sOpen the detail form with given params:24:*/
			UAP_REQUEST(manager.getPtr(), lb_I_String, what)
			UAP_REQUEST(getModuleInstance(), lb_I_String, rep)
			what = query->getAsString(1);
			what->trim();

			*rep = "{";
			*rep +=  SourceFieldName->charrep();
			*rep += "}";

			wxString s = wxString(what->charrep());

			s.Replace(rep->charrep(), SourceFieldValue->charrep());

			UAP(lb_I_Query, q)
			q = db->getQuery(DBName->charrep(), 0);
			q->skipFKCollecting();
			*what = s.c_str();
			if (q->query(what->charrep(), false) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				q->enableFKCollecting();
				*msg = "Failed to execute SQL query. Propably missing a parameter (SQL: ";
				*msg += s.c_str();
				*msg += ")";
				meta->msgBox("Error", msg->charrep());
				return 0;
			}
			q->enableFKCollecting();
			/*...e*/
		}
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)

		ID->setData(myActionID);

		*msg = "lbSQLQueryAction::execute(";
		*msg += ID->charrep();
		*msg += ") failed.";

		meta->setStatusText("Info", msg->charrep());
	}

	lb_I_GUI* gui;

	meta->getGUI(&gui);

	if (gui != NULL) {
		UAP(lb_I_DatabaseForm, f)

		f = gui->findDBForm(SourceFormName->charrep());

		if (f != NULL) f->reopen();
	}
	return -1;
}
/*...e*/

/*...lbDecisionAction:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbDecisionAction)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDecisionAction, lbDecisionAction)

lbErrCodes LB_STDCALL lbDecisionAction::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbDecisionAction::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbDecisionAction::lbDecisionAction() {
	ref = STARTREF;
	myActionID = -1;
}

lbDecisionAction::~lbDecisionAction() {
}

void LB_STDCALL lbDecisionAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbDecisionAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbDecisionAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
	transitions = myTransitions;
	transitions++;
}

void LB_STDCALL lbDecisionAction::setParameter(lb_I_ActionStep_Parameters* myParams) {
}

long LB_STDCALL lbDecisionAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	bool expressionTrue = false;
	bool defaultexpressionTrue = false;
	long first_dst_actionid = -1;
	long defaultfirst_dst_actionid = -1;
	_CL_LOG << "lbDecisionAction::execute()" LOG_

	if (transitions == NULL) {
		_LOG << "Error: lbDecisionAction::execute() Can't execute without transitions instance!" LOG_
		return 0;
	}

	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("source field");
	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&SourceFormName);

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)


		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();

			// The desicion here does not contain how to make desicion, but may contain a general text about what the desicion is for.
			// A desicion should not have more than two outgoing connectors to other action steps. This simplifies the logic.

			transitions->finishActionStepTransitionIteration();
			while (transitions->hasMoreActionStepTransitions()) {
				transitions->setNextActionStepTransition();
				// First use a simple expression without any Lex & Yacc parser
				UAP_REQUEST(getModuleInstance(), lb_I_String, paramValue)
				UAP_REQUEST(getModuleInstance(), lb_I_String, paramName)
				long dst_actionid;
				wxString expression;
				expression = transitions->getActionStepTransitionDecision();
				dst_actionid = transitions->getActionStepTransitionDstActionID();

				if (transitions->getActionStepTransitionSrcActionID() == myActionID) {
					_LOG << "Evaluate expression '" << expression.c_str() << "' of actionid = " << myActionID LOG_
					if (expression.find("==") != -1) {
						// equal operator
						wxString left = expression.substr(0, expression.find("==")-1);
						wxString right = expression.substr(expression.find("==")+2);
						right.Trim();
						left.Trim();

						*paramName = left.c_str();
						params->getUAPString(*&paramName, *&paramValue); /// \todo Evaluate not containing parameter.

						right.Replace("\"", " ", true);
						right.Trim();
						right.Trim(false);

						if (paramValue->charrep() == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

							*msg = "Parameter to compare is not passed (";
							*msg += paramName->charrep();
							*msg += ").";

							meta->msgBox("Error", _trans(msg->charrep()));
							return 0;
						}
						paramValue->trim();

						_LOG << "Evaluate == expression ('" << paramValue->charrep() << "' == '" << right.c_str() << "')" LOG_

						if (*paramValue == right.c_str()) {
							if (expressionTrue == true) {
								_LOG << "Error: Multible expressions are true. This is wrong for a decision!" LOG_
							} else {
								expressionTrue = true;
								first_dst_actionid = dst_actionid; // Only the first expression is used
							}
						}
					} else if (expression.find("!=") != -1) {
						// equal operator
						wxString left = expression.substr(0, expression.find("!=")-1);
						wxString right = expression.substr(expression.find("!=")+2);
						right.Trim();
						left.Trim();

						*paramName = left.c_str();
						params->getUAPString(*&paramName, *&paramValue); /// \todo Evaluate not containing parameter.

						right.Replace("\"", " ", true);
						right.Trim();
						right.Trim(false);

						if (paramValue->charrep() == NULL) {
							meta->msgBox("Error", "Parameter to compare is not passed.");
							return 0;
						}

						if (!(*paramValue == right.c_str())) {
							if (expressionTrue == true) {
								_LOG << "Error: Multible expressions are true. This is wrong for a decision!" LOG_
							} else {
								expressionTrue = true;
								first_dst_actionid = dst_actionid; // Only the first expression is used
							}
						}
					} else if (expression.find("=") != -1) {
						// assignment (typically adding a parameter to params
						wxString left = expression.substr(0, expression.find("=")-1);
						wxString right = expression.substr(expression.find("=")+2);
						right.Trim();
						left.Trim();

						*paramValue = right.c_str();
						*paramName = left.c_str();
						params->setUAPString(*&paramName, *&paramValue);
					} else if (expression.Trim() == "") {
						if (expressionTrue == true) {
							_LOG << "Info: Default is not choosen due to a prior matching expression!" LOG_
						} else {
							defaultexpressionTrue = true;
							defaultfirst_dst_actionid = dst_actionid; // Only the first expression is used
						}
					}
				}
			}

			if ((!expressionTrue) && (defaultexpressionTrue)) first_dst_actionid = defaultfirst_dst_actionid;
			return first_dst_actionid;
		} else {
            _LOG << "Error: appActionSteps is NULL, but required." LOG_
		}
	} else {
		_LOG << "Error: lbDecisionAction::execute() can't work directly at database. The object model must be loaded prior!" LOG_
	}
	return 0;
}

/****************



 /*...lbOpAqueOperation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbOpAqueOperation)
ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbOpAqueOperation, lbOpAqueOperation)

lbErrCodes LB_STDCALL lbOpAqueOperation::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbOpAqueOperation::setData(lb_I_Unknown* uk) not implemented." LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbOpAqueOperation::lbOpAqueOperation() {
	ref = STARTREF;
	myActionID = -1;
}

lbOpAqueOperation::~lbOpAqueOperation() {
}

void LB_STDCALL lbOpAqueOperation::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbOpAqueOperation::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbOpAqueOperation::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
}

void LB_STDCALL lbOpAqueOperation::setParameter(lb_I_ActionStep_Parameters* myParams) {

}

long LB_STDCALL lbOpAqueOperation::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	bool expressionTrue = false;
	long first_dst_actionid = 0;
	_CL_LOG << "lbDecisionAction::execute()" LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFormName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(manager.getPtr(), lb_I_String, app)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBUser)
	UAP_REQUEST(manager.getPtr(), lb_I_String, DBPass)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)

	UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("source field");
	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&SourceFormName);

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_Parameter, docparams)

	uk = meta->getActiveDocument();
	QI(uk, lb_I_Parameter, docparams)

	if (docparams != NULL) {
		// Try to retrieve current document's data. Later on this will be preffered before plain SQL queries.
		UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Action_Steps, appActionSteps)
		UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
		UAP(lb_I_KeyBase, key)
		UAP(lb_I_Unknown, uk)

		docparams->setCloning(false);
		document->setCloning(false);

		QI(name, lb_I_KeyBase, key)
		*name = "ApplicationData";
		docparams->getUAPContainer(*&name, *&document);

		*name = "AppAction_Steps";
		uk = document->getElement(&key);
		QI(uk, lb_I_Action_Steps, appActionSteps)


		if (appActionSteps != NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			UAP_REQUEST(getModuleInstance(), lb_I_String, What)

			appActionSteps->selectActionStep(myActionID);
			*What = appActionSteps->getActionStepWhat();

			// The desicion here does not contain how to make desicion, but may contain a general text about what the desicion is for.
			// A desicion should not have more than two outgoing connectors to other action steps. This simplifies the logic.

			return -1;
		}
	} else {
		_LOG << "Error: lbDecisionAction::execute() can't work directly at database. The object model must be loaded prior!" LOG_
	}
	return 0;
}


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
/*...e*/

#include <SendSignalAction.h>


BEGIN_IMPLEMENT_LB_UNKNOWN(lbSendSignalAction)
	ADD_INTERFACE(lb_I_DelegatedAction)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbSendSignalAction, lbSendSignalAction)

lbErrCodes LB_STDCALL lbSendSignalAction::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbSendSignalAction::setData(lb_I_Unknown* uk) not implemented." LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbSendSignalAction::lbSendSignalAction() {
	ref = STARTREF;
	myActionID = -1;
}

lbSendSignalAction::~lbSendSignalAction() {
}

void LB_STDCALL lbSendSignalAction::setDatabase(lb_I_Database* _db) {
	db = _db;
	db++;
}

void LB_STDCALL lbSendSignalAction::setActionID(long id) {
	myActionID = id;
}

void LB_STDCALL lbSendSignalAction::setTransitions(lb_I_Action_Step_Transitions* myTransitions) {
}

void LB_STDCALL lbSendSignalAction::setParameter(lb_I_ActionStep_Parameters* myParams) {
	SignalParams = myParams;
}

lb_I_String* LB_STDCALL lbSendSignalAction::substitutePlaceholder(lb_I_String* value, lb_I_Parameter* params) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, substituted)

	*substituted = value->charrep();

	while (substituted->strpos("{") > -1) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, replacer)
		UAP(lb_I_String, value)
		UAP(lb_I_String, right)
		UAP(lb_I_String, left)
		left = substituted->left(substituted->strpos("}"));
		right = left->right(substituted->strpos("{"));
		*replacer = "{";
		*replacer += right->charrep();
		*replacer = "}";

		params->getUAPString(*&right, *&value);

		substituted->replace(replacer->charrep(), value->charrep());
	}
	substituted++;
	return substituted.getPtr();
}

long LB_STDCALL lbSendSignalAction::execute(lb_I_Parameter* params) {
	lbErrCodes err = ERR_NONE;
	_CL_LOG << "lbSendSignalAction::execute()" LOG_

	if(SignalParams == NULL) {
		_LOG << "Error: SignalParams is NULL. lbSendSignalAction can't be used without this." LOG_
		return 0;
	}

	//UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFormName)
	//UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldName)
	//UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldValue)
	UAP_REQUEST(getModuleInstance(), lb_I_String, app)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)

	UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)

	parameter->setData("DBName");
	params->getUAPString(*&parameter, *&DBName);
	parameter->setData("DBUser");
	params->getUAPString(*&parameter, *&DBUser);
	parameter->setData("DBPass");
	params->getUAPString(*&parameter, *&DBPass);

// They are not used, thus commented out.	
/*
	parameter->setData("source value");
	params->getUAPString(*&parameter, *&SourceFieldValue);
	parameter->setData("source field");
	params->getUAPString(*&parameter, *&SourceFieldName);
	parameter->setData("source Form");
	params->getUAPString(*&parameter, *&SourceFormName);
*/
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

			*msg = "Send signal to dispatcher (";

			/**********************************************************/
			/* Start dispatching given parameters from the what field */
			/**********************************************************/

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
			UAP_REQUEST(getModuleInstance(), lb_I_String, inputname)
			UAP_REQUEST(getModuleInstance(), lb_I_String, inputvalue)
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)

			// Build up the required parameters (with substituted placeholders) for the configured signal
			int I = 0;
			while (SignalParams->hasMoreActionStepParameters()) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, value)
				UAP_REQUEST(getModuleInstance(), lb_I_String, name)

				UAP(lb_I_String, valueSubstituted)

				SignalParams->setNextActionStepParameter();

				*name = SignalParams->getActionStepParameterName();
				*value = SignalParams->getActionStepParameterValue();

				_LOG << "Prepare parameter " << name->charrep() << " with value " << value->charrep() << " for dispatcher." LOG_

				if (I++ == 0) *msg += ", ";
				*msg += value->charrep();

				valueSubstituted = substitutePlaceholder(*&value, *&params);
				param->setUAPString(*&name, *&valueSubstituted);
			}

			*msg += ")";
			meta->setStatusText("Info", msg->charrep());

			UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
			UAP(lb_I_Unknown, uk)
			QI(param, lb_I_Unknown, uk)

			UAP_REQUEST(getModuleInstance(), lb_I_String, result)
			UAP(lb_I_Unknown, uk_result)
			QI(result, lb_I_Unknown, uk_result)

			dispatcher->dispatch(appActionSteps->getActionStepBezeichnung(), uk.getPtr(), &uk_result);

///\todo Check if there is a need to evaluate the result or pass it back (askYesNo).

/*
 * At least in a case of askYesNo there may be a change in a flow in a non linear action. Thus a value must be passed back.
 * To distinguish each result of such an action the name could be used from getActionStepBezeichnung().
 */
#define PASS_BACK_RESULT
#ifdef PASS_BACK_RESULT
			UAP_REQUEST(getModuleInstance(), lb_I_String, passback)
			*passback = appActionSteps->getActionStepBezeichnung();

			params->setUAPString(*&passback, *&result);
#endif

// I think it will also be usefull to pass back the list of parameters generated by the signal handler. (In my actual need the memorybuffer value). 
			
			params->copyFrom(*&param);
			
			return -1;
		}
	}
	return -1;
}

/** \brief Event handler that calls another activity.
 * This event handler calls another activity. You can use a send signal action step to call sub activities for the sake of
 * keeping acivities managale. An action usually needs parameters. These parameters must be passed as additional parameters
 * in the call of send signal action and thus mapped as parameters here.
 */
class lbCallActivityHandler :
public lb_I_Unknown,
public lb_I_LogonHandler,
public lb_I_EventHandler {
public:
	lbCallActivityHandler();
	virtual ~lbCallActivityHandler();
	
	DECLARE_LB_UNKNOWN()
	
	lbErrCodes LB_STDCALL registerEventHandler(lb_I_Dispatcher* disp);
	lb_I_Unknown* LB_STDCALL getUnknown();
	lbErrCodes LB_STDCALL CallActivity(lb_I_Unknown* uk);
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbCallActivityHandler)
ADD_INTERFACE(lb_I_EventHandler)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbCallActivityHandler::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbCallActivityHandler::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lb_I_Unknown* LB_STDCALL lbCallActivityHandler::getUnknown() {
	UAP(lb_I_Unknown, uk)
	queryInterface("lb_I_Unknown", (void**) &uk, __FILE__, __LINE__); 
	uk++;
	return uk.getPtr();
}

lbErrCodes LB_STDCALL lbCallActivityHandler::registerEventHandler(lb_I_Dispatcher* disp) {
	disp->addEventHandlerFn(this, (lbEvHandler) &lbCallActivityHandler::CallActivity, "CallActivity");
	
	return ERR_NONE;
}

lbErrCodes LB_STDCALL lbCallActivityHandler::CallActivity(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	
	// This only is probably ambiguous
	UAP_REQUEST(getModuleInstance(), lb_I_String, ActionName)
	
	/* So use an instance name (this may be used).
	 * If this is used, the action name must be declared as a method and linked to the activity implementing the method.
	 *
	 * This can then be used in forms (optionally designable from within the prototype, or lazy design)
	 *
	 * This can also be at application level. Then the method must be declared in a main 'application' class, but then the
	 * class used for this must be stereotyped and the only class in the model.
	 */
	UAP_REQUEST(getModuleInstance(), lb_I_String, ActionInstanceName)

	QI(uk, lb_I_Parameter, param)
	
	if (param == NULL) {
		// Handle setup on demand.
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
		meta->setStatusText("Info", "CallActivity action ...");
		
		// The send signal action must pass the action name to be called.
		// It must also pass the parameters for that action. What is about
		// overwriting existing parameters by those needed by the target activity.
		// I need a 'callstack'.
		
		
	}
	
	return ERR_NONE;
}

lbCallActivityHandler::lbCallActivityHandler() {
	ref = STARTREF;
}

lbCallActivityHandler::~lbCallActivityHandler() {
	_CL_VERBOSE << "lbCallActivityHandler::~lbCallActivityHandler() called." LOG_
}


/** \brief Implements a wizard based login plugin.
 *
 */
class lbPluginCallActivityHandler :
public lb_I_PluginImpl
{
public:
	
	lbPluginCallActivityHandler();
	virtual ~lbPluginCallActivityHandler();
	
	DECLARE_LB_UNKNOWN()
	
	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
	/** \brief Init the menu emtries.
	 *
	 * This connects the login feature to a menu.
	 */
	virtual void LB_STDCALL initialize();
	
	/** \brief Run the login manually.
	 *
	 * This let the login wizard appear manually without invoking it from
	 * the menu entry. You could use this to start the login wizard automatically.
	 */
	virtual bool LB_STDCALL run();
	
	/** \brief Get the underlying implementation.
	 *
	 * Not needed in this implementation. This implementation has no separate
	 * class with the implementation. This is due to the not existing problem
	 * of multible base class inheritation of lb_I_Unknown.
	 *
	 * If multible intarfaces could be queried, then each
	 */
	virtual lb_I_Unknown* LB_STDCALL getImplementation();
	
	virtual lb_I_Unknown* LB_STDCALL peekImplementation();
	void LB_STDCALL releaseImplementation();
	
	UAP(lb_I_Unknown, ukCallActivity)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginCallActivityHandler)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginCallActivityHandler, lbPluginCallActivityHandler)

lbErrCodes LB_STDCALL lbPluginCallActivityHandler::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbPluginCallActivityHandler::setData(...) not implemented yet" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}

lbPluginCallActivityHandler::lbPluginCallActivityHandler() {
	ref = STARTREF;
}

lbPluginCallActivityHandler::~lbPluginCallActivityHandler() {
	_CL_VERBOSE << "lbPluginCallActivityHandler::~lbPluginCallActivityHandler() called." LOG_
}

bool LB_STDCALL lbPluginCallActivityHandler::canAutorun() {
	return true;
}

lbErrCodes LB_STDCALL lbPluginCallActivityHandler::autorun() {
	lbErrCodes err = ERR_NONE;
	int lEvent;
	UAP_REQUEST(getModuleInstance(), lb_I_EventManager, ev)
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
	
	ev->registerEvent("CallActivity", lEvent);
	
	
	lbCallActivityHandler* hdl = new lbCallActivityHandler();
	hdl->setModuleManager(getModuleInstance(), __FILE__, __LINE__);
	
	QI(hdl, lb_I_Unknown, ukCallActivity)
	
	hdl->registerEventHandler(*&disp);
	
	return err;
}

/*...svoid LB_STDCALL lbPluginCallActivityHandler\58\\58\initialize\40\\41\:0:*/
void LB_STDCALL lbPluginCallActivityHandler::initialize() {
}
/*...e*/

/*...sbool LB_STDCALL lbPluginCallActivityHandler\58\\58\run\40\\41\:0:*/
bool LB_STDCALL lbPluginCallActivityHandler::run() {
	return true;
}
/*...e*/

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginCallActivityHandler\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginCallActivityHandler::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	return this;
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginCallActivityHandler\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginCallActivityHandler::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	return this;
}
/*...e*/
void LB_STDCALL lbPluginCallActivityHandler::releaseImplementation() {
	_CL_VERBOSE << "lbPluginCallActivityHandler::releaseImplementation() called." LOG_
}

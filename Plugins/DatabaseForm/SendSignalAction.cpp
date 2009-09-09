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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/

/*...sincludes:0:*/
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

#include <lbConfigHook.h>
#include <lbInterfaces.h>



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

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

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

			*msg = "Send signal to dispatcher (";

			/**********************************************************/
			/* Start dispatching given parameters from the what field */
			/**********************************************************/
			
			UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
			UAP_REQUEST(manager.getPtr(), lb_I_String, inputname)
			UAP_REQUEST(manager.getPtr(), lb_I_String, inputvalue)
			UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
			
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
			
			UAP_REQUEST(manager.getPtr(), lb_I_String, result)
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
			
			return -1;
		}
	}
	return -1;
}
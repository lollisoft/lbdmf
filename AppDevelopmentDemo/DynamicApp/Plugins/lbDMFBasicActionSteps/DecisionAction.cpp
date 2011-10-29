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

#include <lbInterfaces-lbDMFManager.h>
#include <DecisionAction.h>

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
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFormName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, SourceFieldValue)
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
				UAP_REQUEST(getModuleInstance(), lb_I_String, expression)
				//wxString expression;
				*expression = transitions->getActionStepTransitionDecision();
				dst_actionid = transitions->getActionStepTransitionDstActionID();
				
				if (transitions->getActionStepTransitionSrcActionID() == myActionID) {
					_LOG << "Evaluate expression '" << expression->charrep() << "' of actionid = " << myActionID LOG_
					if (expression->strpos("==") != -1) {
						// equal operator
						//wxString left = expression.substr(0, expression.find("==")-1);
						//wxString right = expression.substr(expression.find("==")+2);
						
						UAP_REQUEST(getModuleInstance(), lb_I_String, left)
						UAP_REQUEST(getModuleInstance(), lb_I_String, right)
						
						*left = expression->left(expression->strpos("=="))->charrep();
						*right = expression->right(expression->strpos("==")+2)->charrep(); 
						
						right->trim();
						right->trim(false);
						left->trim();
						left->trim(false);
						
						*paramName = left->charrep();
						params->getUAPString(*&paramName, *&paramValue); /// \todo Evaluate not containing parameter.
						
						right->replace("\"", " ");
						right->trim();
						right->trim(false);
						
						if (paramValue->charrep() == NULL) {
							UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
							
							*msg = "Parameter to compare is not passed (";
							*msg += paramName->charrep();
							*msg += ").";
							
							meta->msgBox("Error", _trans(msg->charrep()));
							return 0;
						}
						paramValue->trim();
						paramValue->trim(false);
						
						_LOG << "Evaluate == expression ('" << paramValue->charrep() << "' == '" << right->charrep() << "')" LOG_
						
						if (*paramValue == right->charrep()) {
							if (expressionTrue == true) {
								_LOG << "Error: Multible expressions are true. This is wrong for a decision!" LOG_
							} else {
								expressionTrue = true;
								first_dst_actionid = dst_actionid; // Only the first expression is used
							}
						}
					} else if (expression->strpos("!=") != -1) {
						// equal operator
						//wxString left = expression.substr(0, expression.find("!=")-1);
						//wxString right = expression.substr(expression.find("!=")+2);

						UAP_REQUEST(getModuleInstance(), lb_I_String, left)
						UAP_REQUEST(getModuleInstance(), lb_I_String, right)
						
						*left = expression->left(expression->strpos("!="))->charrep();
						*right = expression->right(expression->strpos("!=")+2)->charrep(); 

						right->trim();
						right->trim(false);
						left->trim();
						left->trim(false);
						
						*paramName = left->charrep();
						params->getUAPString(*&paramName, *&paramValue); /// \todo Evaluate not containing parameter.
						
						right->replace("\"", " ", true);
						right->trim();
						right->trim(false);
						
						if (paramValue->charrep() == NULL) {
							meta->msgBox("Error", "Parameter to compare is not passed.");
							return 0;
						}
						
						paramValue->trim();
						paramValue->trim(false);

						if (!(*paramValue == right->charrep())) {
							if (expressionTrue == true) {
								_LOG << "Error: Multible expressions are true. This is wrong for a decision!" LOG_
							} else {
								expressionTrue = true;
								first_dst_actionid = dst_actionid; // Only the first expression is used
							}
						}
					} else if (expression->strpos("=") != -1) {
						// assignment (typically adding a parameter to params
						//wxString left = expression.substr(0, expression.find("=")-1);
						//wxString right = expression.substr(expression.find("=")+2);
						
						UAP_REQUEST(getModuleInstance(), lb_I_String, left)
						UAP_REQUEST(getModuleInstance(), lb_I_String, right)
						
						*left = expression->left(expression->strpos("="))->charrep();
						*right = expression->right(expression->strpos("=")+1)->charrep(); 
						
						right->trim();
						right->trim(false);
						left->trim();
						left->trim(false);
						
						*paramValue = right->charrep();
						*paramName = left->charrep();
						params->setUAPString(*&paramName, *&paramValue);
					} else {
						expression->trim();
						if (*expression == "") {
							if (expressionTrue == true) {
								_LOG << "Info: Default is not choosen due to a prior matching expression!" LOG_
							} else {
								defaultexpressionTrue = true;
								defaultfirst_dst_actionid = dst_actionid; // Only the first expression is used
							}
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


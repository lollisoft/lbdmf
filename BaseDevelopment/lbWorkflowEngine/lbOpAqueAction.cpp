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

#include <lbOpAqueAction.h>

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
	
	myActionID = -1;
	
	;
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

			return -1;
		}
	} else {
		_LOG << "Error: lbDecisionAction::execute() can't work directly at database. The object model must be loaded prior!" LOG_
	}
	return 0;
}


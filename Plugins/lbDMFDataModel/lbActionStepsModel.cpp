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
#define LB_DMFDATAMODEL_DLL

#ifdef _MSC_VER

//#pragma warning( disable: 4101 )

#endif

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbInterfaces-lbDMFManager.h>
#include <lbActionStepsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbActionStepsModel, lbActionStepsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionStepsModel)
	ADD_INTERFACE(lb_I_Action_Steps)
END_IMPLEMENT_LB_UNKNOWN()

void		LB_STDCALL lbActionStepsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionStepsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbActionStepsModel::lbActionStepsModel() {
	
	_CL_VERBOSE << "lbActionStepsModel::lbActionStepsModel() called." LOG_

	REQUEST(getModuleInstance(), lb_I_Container, Actions)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepActionID)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepType)
	REQUEST(getModuleInstance(), lb_I_String, currentActionStepWhat)
	REQUEST(getModuleInstance(), lb_I_String, currentActionStepBezeichnung)
	REQUEST(getModuleInstance(), lb_I_Long, currentActionStepOrderNo)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
}

lbActionStepsModel::~lbActionStepsModel() {
	_CL_VERBOSE << "lbActionStepsModel::~lbActionStepsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionStepsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionStepsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void		LB_STDCALL lbActionStepsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActionSteps()) {
		setNextActionStep();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionStepsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActionSteps()) {
		setNextActionStep();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}


long  LB_STDCALL lbActionStepsModel::addActionStep(const char* bezeichnung, long actionid, long orderNo, long type, const char* what, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)

	UAP_REQUEST(getModuleInstance(), lb_I_String, Bezeichnung)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ActionId)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, OrderNo)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Typ)
	UAP_REQUEST(getModuleInstance(), lb_I_String, What)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "Add a parameter to lbActionStepsModel: Bezeichnung: " << bezeichnung << ", ActionID = " << actionid LOG_

	*Bezeichnung = bezeichnung;
	ActionId->setData(actionid);
	Typ->setData(type);
	*What = what;
	ID->setData(_id);
	OrderNo->setData(orderNo);
	
	*paramname = "Bezeichnung";
	param->setUAPString(*&paramname, *&Bezeichnung);
	*paramname = "ActionId";
	param->setUAPLong(*&paramname, *&ActionId);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "OrderNo";
	param->setUAPLong(*&paramname, *&OrderNo);
	*paramname = "What";
	param->setUAPString(*&paramname, *&What);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

bool LB_STDCALL lbActionStepsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionStepsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionStepsModel::unmark() {
	marked->setData((long) 0);
}

bool  LB_STDCALL lbActionStepsModel::selectActionStep(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Actions->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Bezeichnung";
		param->getUAPString(*&name, *&currentActionStepBezeichnung);
		*name = "ActionId";
		param->getUAPLong(*&name, *&currentActionStepActionID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentActionStepID);
		*name = "OrderNo";
		param->getUAPLong(*&name, *&currentActionStepOrderNo);
		*name = "Typ";
		param->getUAPLong(*&name, *&currentActionStepType);
		*name = "What";
		param->getUAPString(*&name, *&currentActionStepWhat);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbActionStepsModel::getActionStepCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionStepsModel::hasMoreActionSteps() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionStepsModel::setNextActionStep() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Actions->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Bezeichnung";
	param->getUAPString(*&name, *&currentActionStepBezeichnung);
	*name = "ActionId";
	param->getUAPLong(*&name, *&currentActionStepActionID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentActionStepID);
	*name = "OrderNo";
	param->getUAPLong(*&name, *&currentActionStepOrderNo);
	*name = "Typ";
	param->getUAPLong(*&name, *&currentActionStepType);
	*name = "What";
	param->getUAPString(*&name, *&currentActionStepWhat);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionStepsModel::finishActionStepIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionStepsModel::getID() {
	return currentActionStepID->getData();
}

long LB_STDCALL lbActionStepsModel::getActionStepOrderNo() {
	return currentActionStepOrderNo->getData();
}

long LB_STDCALL lbActionStepsModel::getActionStepActionID() {
	return currentActionStepActionID->getData();
}

char*  LB_STDCALL lbActionStepsModel::getActionStepBezeichnung() {
	return currentActionStepBezeichnung->charrep();
}

char*  LB_STDCALL lbActionStepsModel::getActionStepWhat() {
	return currentActionStepWhat->charrep();
}

long LB_STDCALL lbActionStepsModel::getActionStepType() {
	return currentActionStepType->getData();
}

/*...sclass lbPluginActionStepsModel implementation:0:*/
/*...slbPluginActionStepsModel:0:*/
class lbPluginActionStepsModel : public lb_I_PluginImpl {
public:
	lbPluginActionStepsModel();
	
	virtual ~lbPluginActionStepsModel();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStepsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStepsModel, lbPluginActionStepsModel)

/*...slbErrCodes LB_STDCALL lbPluginActionStepsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionStepsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStepsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionStepsModel::lbPluginActionStepsModel() {
	_CL_VERBOSE << "lbPluginActionStepsModel::lbPluginActionStepsModel() called.\n" LOG_
	
	
	;
}

lbPluginActionStepsModel::~lbPluginActionStepsModel() {
	_CL_VERBOSE << "lbPluginActionStepsModel::~lbPluginActionStepsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStepsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStepsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStepsModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionStepsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbActionStepsModel* ActionsModel = new lbActionStepsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionStepsModel* ActionsModel = new lbActionStepsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionStepsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionStepTransitionsModel)
	ADD_INTERFACE(lb_I_Action_Step_Transitions)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbActionStepTransitionsModel, lbActionStepTransitionsModel)

void		LB_STDCALL lbActionStepTransitionsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionStepTransitionsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbActionStepTransitionsModel::lbActionStepTransitionsModel() {
	
	_CL_VERBOSE << "lbActionStepTransitionsModel::lbActionStepTransitionsModel() called." LOG_

	REQUEST(getModuleInstance(), lb_I_Container, Actions)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentSrcActionId)
	REQUEST(getModuleInstance(), lb_I_Long, currentDstActionId)
	REQUEST(getModuleInstance(), lb_I_String, currentDescription)
	REQUEST(getModuleInstance(), lb_I_String, currentDecision)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
}

lbActionStepTransitionsModel::~lbActionStepTransitionsModel() {
	_CL_VERBOSE << "lbActionStepTransitionsModel::~lbActionStepTransitionsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionStepTransitionsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionStepTransitionsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void		LB_STDCALL lbActionStepTransitionsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActionStepTransitions()) {
		setNextActionStepTransition();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionStepTransitionsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActionStepTransitions()) {
		setNextActionStepTransition();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}


long  LB_STDCALL lbActionStepTransitionsModel::addTransition(const char* expression, long src_actionid, long dst_actionid, const char* description, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, Description)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, SrcActionId)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, DstActionId)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Decision)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	_CL_VERBOSE << "long  LB_STDCALL lbActionStepTransitionsModel::addTransition(...) called." LOG_

	*Description = description;
	SrcActionId->setData(src_actionid);
	DstActionId->setData(dst_actionid);
/// \todo Rename remaining occurences.
	*Decision = expression;
	ID->setData(_id);
	
	*paramname = "Description";
	param->setUAPString(*&paramname, *&Description);
	*paramname = "Decision";
	param->setUAPString(*&paramname, *&Decision);
	*paramname = "SrcActionId";
	param->setUAPLong(*&paramname, *&SrcActionId);
	*paramname = "DstActionId";
	param->setUAPLong(*&paramname, *&DstActionId);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

bool LB_STDCALL lbActionStepTransitionsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionStepTransitionsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionStepTransitionsModel::unmark() {
	marked->setData((long) 0);
}

bool  LB_STDCALL lbActionStepTransitionsModel::selectTransition(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Actions->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(getModuleInstance(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "Description";
		param->getUAPString(*&name, *&currentDescription);
		*name = "SrcActionId";
		param->getUAPLong(*&name, *&currentSrcActionId);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "DstActionId";
		param->getUAPLong(*&name, *&currentDstActionId);
		*name = "Decision";
		param->getUAPString(*&name, *&currentDecision);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}

int  LB_STDCALL lbActionStepTransitionsModel::getActionStepTransitionsCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionStepTransitionsModel::hasMoreActionStepTransitions() {
	return Actions->hasMoreElements();
}

void  LB_STDCALL lbActionStepTransitionsModel::setNextActionStepTransition() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Actions->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "Description";
	param->getUAPString(*&name, *&currentDescription);
	*name = "SrcActionId";
	param->getUAPLong(*&name, *&currentSrcActionId);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "DstActionId";
	param->getUAPLong(*&name, *&currentDstActionId);
	*name = "Decision";
	param->getUAPString(*&name, *&currentDecision);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbActionStepTransitionsModel::finishActionStepTransitionIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionStepTransitionsModel::getID() {
	return currentID->getData();
}

long LB_STDCALL lbActionStepTransitionsModel::getActionStepTransitionSrcActionID() {
	return currentSrcActionId->getData();
}

long LB_STDCALL lbActionStepTransitionsModel::getActionStepTransitionDstActionID() {
	return currentDstActionId->getData();
}

char*  LB_STDCALL lbActionStepTransitionsModel::getActionStepTransitionDecision() {
	return currentDecision->charrep();
}

char*  LB_STDCALL lbActionStepTransitionsModel::getActionStepTransitionDescription() {
	return currentDescription->charrep();
}

/*...sclass lbPluginActionStepsModel implementation:0:*/
/*...slbPluginActionStepsModel:0:*/
class lbPluginActionStepTransitionsModel : public lb_I_PluginImpl {
public:
	lbPluginActionStepTransitionsModel();
	
	virtual ~lbPluginActionStepTransitionsModel();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStepTransitionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStepTransitionsModel, lbPluginActionStepTransitionsModel)

/*...slbErrCodes LB_STDCALL lbPluginActionStepsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginActionStepTransitionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStepTransitionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginActionStepTransitionsModel::lbPluginActionStepTransitionsModel() {
	_LOG << "lbPluginActionStepTransitionsModel::lbPluginActionStepTransitionsModel() called." LOG_
	
	
	;
}

lbPluginActionStepTransitionsModel::~lbPluginActionStepTransitionsModel() {
	_LOG << "lbPluginActionStepTransitionsModel::~lbPluginActionStepTransitionsModel() called." LOG_
}

bool LB_STDCALL lbPluginActionStepTransitionsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStepTransitionsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStepTransitionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionStepTransitionsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepTransitionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbActionStepTransitionsModel* ActionsModel = new lbActionStepTransitionsModel();
		

		QI(ActionsModel, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginActionStepTransitionsModel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginActionStepsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginActionStepTransitionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionStepTransitionsModel* ActionsModel = new lbActionStepTransitionsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginActionStepTransitionsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




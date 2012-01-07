
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
#include <lbInterfaces-lbDMFManager.h>
#include <Generated_EntityModelActions.h>

IMPLEMENT_FUNCTOR(instanceOflbActionsModel, lbActionsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbActionsModel)
	ADD_INTERFACE(lb_I_Actions)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbActionsModel)

void		LB_STDCALL lbActionsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbActionsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbActionsModel::lbActionsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, Actions)

    REQUEST(getModuleInstance(), lb_I_String, currenttarget)
    REQUEST(getModuleInstance(), lb_I_String, currentsource)
    REQUEST(getModuleInstance(), lb_I_String, currentname)
    REQUEST(getModuleInstance(), lb_I_Long, currenttyp)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentActionsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbActionsModel::lbActionsModel() called." LOG_
}

lbActionsModel::~lbActionsModel() {
	_CL_VERBOSE << "lbActionsModel::~lbActionsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbActionsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbActionsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbActionsModel::addActions(const char* _target, const char* _source, const char* _name, long _typ,  long _ActionsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __target)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __source)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __typ)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __ActionsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__target = _target;
    *__source = _source;
    *__name = _name;
    __typ->setData(_typ);

	
	__ActionsID->setData(_ActionsID);

    *paramname = "target";
    param->setUAPString(*&paramname, *&__target);
    *paramname = "source";
    param->setUAPString(*&paramname, *&__source);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);
    *paramname = "typ";
    param->setUAPLong(*&paramname, *&__typ);


	*paramname = "ActionsID";
	param->setUAPLong(*&paramname, *&__ActionsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__ActionsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Actions->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbActionsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActions()) {
		setNextActions();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}

void		LB_STDCALL lbActionsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Actions->finishIteration();
	while (hasMoreActions()) {
		setNextActions();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Actions->remove(&key);
			Actions->finishIteration();
		}
	}
}

bool LB_STDCALL lbActionsModel::selectActions(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Actions->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "target";
    param->getUAPString(*&paramname, *&currenttarget);
    *paramname = "source";
    param->getUAPString(*&paramname, *&currentsource);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);


		*paramname = "ActionsID";
		param->getUAPLong(*&paramname, *&currentActionsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbActionsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbActionsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbActionsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbActionsModel::getActionsCount() {
	return Actions->Count();
}

bool  LB_STDCALL lbActionsModel::hasMoreActions() {
	return (Actions->hasMoreElements() == 1);
}

void  LB_STDCALL lbActionsModel::setNextActions() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Actions->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "target";
    param->getUAPString(*&paramname, *&currenttarget);
    *paramname = "source";
    param->getUAPString(*&paramname, *&currentsource);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);
    *paramname = "typ";
    param->getUAPLong(*&paramname, *&currenttyp);

	*paramname = "ActionsID";
	param->getUAPLong(*&paramname, *&currentActionsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbActionsModel::finishActionsIteration() {
	Actions->finishIteration();
}

long LB_STDCALL lbActionsModel::get_id() {
	return currentActionsID->getData();
}


char* LB_STDCALL lbActionsModel::get_target() {
	return currenttarget->charrep();
}

char* LB_STDCALL lbActionsModel::get_source() {
	return currentsource->charrep();
}

char* LB_STDCALL lbActionsModel::get_name() {
	return currentname->charrep();
}

long LB_STDCALL lbActionsModel::get_typ() {
	return currenttyp->getData();
}


class lbPluginActionsModel : public lb_I_PluginImpl {
public:
	lbPluginActionsModel();
	
	virtual ~lbPluginActionsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionsModel, lbPluginActionsModel)

lbErrCodes LB_STDCALL lbPluginActionsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionsModel::lbPluginActionsModel() {
	_CL_VERBOSE << "lbPluginActionsModel::lbPluginActionsModel() called.\n" LOG_
}

lbPluginActionsModel::~lbPluginActionsModel() {
	_CL_VERBOSE << "lbPluginActionsModel::~lbPluginActionsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionsModel::initialize() {
}
	
bool LB_STDCALL lbPluginActionsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModel == NULL) {
		lbActionsModel* ActionsModel = new lbActionsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActionsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbActionsModel* ActionsModel = new lbActionsModel();
		
	
		QI(ActionsModel, lb_I_Unknown, ukActionsModel)
	}
	
	lb_I_Unknown* r = ukActionsModel.getPtr();
	ukActionsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionsModel != NULL) {
                ukActionsModel--;
                ukActionsModel.resetPtr();
        }
}

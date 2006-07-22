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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
*/
/*...e*/
#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#include <lbConfigHook.h>
/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbRelations.h>

IMPLEMENT_FUNCTOR(instanceOflbUserApplicationRelationModel, lbUserApplicationRelationModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUserApplicationRelationModel)
	ADD_INTERFACE(lb_I_User_Applications)
END_IMPLEMENT_LB_UNKNOWN()


lbUserApplicationRelationModel::lbUserApplicationRelationModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Relations)
	REQUEST(getModuleInstance(), lb_I_Long, currentUserID)
	REQUEST(getModuleInstance(), lb_I_Long, currentAppID)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
}

lbUserApplicationRelationModel::~lbUserApplicationRelationModel() {

}

lbErrCodes LB_STDCALL lbUserApplicationRelationModel::setData(lb_I_Unknown*) {
		_LOG << "Error: lbUserApplicationRelationModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbUserApplicationRelationModel::addRelation(long app_id, long user_id, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, UserID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, AppID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	UserID->setData(user_id);
	AppID->setData(app_id);
	ID->setData(_id);
	
	*paramname = "UserID";
	param->setUAPLong(*&paramname, *&UserID);
	*paramname = "AppID";
	param->setUAPLong(*&paramname, *&AppID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Relations->insert(&ukParam, &key);

	return -1;
}

bool  LB_STDCALL lbUserApplicationRelationModel::selectRelation(long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, id)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	id->setData(_id);

	QI(id, lb_I_KeyBase, key)
	uk = Relations->getElement(&key);
	
	if (uk != NULL) {
		UAP_REQUEST(manager.getPtr(), lb_I_String, name)
		UAP(lb_I_Parameter, param)
		QI(uk, lb_I_Parameter, param)
		
		*name = "UserID";
		param->getUAPLong(*&name, *&currentUserID);
		*name = "AppID";
		param->getUAPLong(*&name, *&currentAppID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		
		return true;
	}
	
	return false;
}

bool LB_STDCALL lbUserApplicationRelationModel::addFilter(const char* filter, const char* value) {
	return false;
}

bool LB_STDCALL lbUserApplicationRelationModel::resetFilter(const char* filter) {
	return true;
}


int  LB_STDCALL lbUserApplicationRelationModel::getRelationCount() {
	return Relations->Count();
}

bool  LB_STDCALL lbUserApplicationRelationModel::hasMoreRelations() {
	return Relations->hasMoreElements();
}

void  LB_STDCALL lbUserApplicationRelationModel::setNextRelation() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Relations->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "UserID";
	param->getUAPLong(*&name, *&currentUserID);
	*name = "AppID";
	param->getUAPLong(*&name, *&currentAppID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
}

void  LB_STDCALL lbUserApplicationRelationModel::finishRelationIteration() {
	Relations->finishIteration();
}

long LB_STDCALL lbUserApplicationRelationModel::getApplicationID() {
	return currentAppID->getData();
}

long  LB_STDCALL lbUserApplicationRelationModel::getUserID() {
	return currentUserID->getData();
}

long LB_STDCALL lbUserApplicationRelationModel::getID() {
	return currentID->getData();
}

/*...sclass lbPluginUsersModel implementation:0:*/
/*...slbPluginUsersModel:0:*/
class lbPluginUserApplicationRelationModel : public lb_I_PluginImpl {
public:
	lbPluginUserApplicationRelationModel();
	
	virtual ~lbPluginUserApplicationRelationModel();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUserApplicationRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUserApplicationRelationModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUserApplicationRelationModel, lbPluginUserApplicationRelationModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginUserApplicationRelationModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginUserApplicationRelationModel::lbPluginUserApplicationRelationModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginUserApplicationRelationModel::~lbPluginUserApplicationRelationModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
}

void LB_STDCALL lbPluginUserApplicationRelationModel::initialize() {
}
	
bool LB_STDCALL lbPluginUserApplicationRelationModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUserApplicationRelationModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {
		lbUserApplicationRelationModel* Users_ApplicationModel = new lbUserApplicationRelationModel();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserApplicationRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUserApplicationRelationModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserApplicationRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbUserApplicationRelationModel* Users_ApplicationModel = new lbUserApplicationRelationModel();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukUserApplicationRelationModel)
	}
	
	lb_I_Unknown* r = ukUserApplicationRelationModel.getPtr();
	ukUserApplicationRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginUserApplicationRelationModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserApplicationRelationModel != NULL) {
                ukUserApplicationRelationModel->release(__FILE__, __LINE__);
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/



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

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbUsersModel.h>

IMPLEMENT_FUNCTOR(instanceOflbUsersModel, lbUsersModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUsersModel)
	ADD_INTERFACE(lb_I_UserAccounts)
END_IMPLEMENT_LB_UNKNOWN()


lbUsersModel::lbUsersModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Users)
	REQUEST(getModuleInstance(), lb_I_String, currentUserName)
	REQUEST(getModuleInstance(), lb_I_String, currentUserPassword)
	REQUEST(getModuleInstance(), lb_I_Long, currentUserID)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
}

lbUsersModel::~lbUsersModel() {
	_CL_LOG << "lbUsersModel::~lbUsersModel() called." LOG_
}

lbErrCodes LB_STDCALL lbUsersModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbUsersModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbUsersModel::addAccount(const char* _user, const char* _pass, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, User)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Pass)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)

	*User = _user;
	*Pass = _pass;
	ID->setData(_id);
	
	*paramname = "User";
	param->setUAPString(*&paramname, *&User);
	*paramname = "Pass";
	param->setUAPString(*&paramname, *&Pass);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Users->insert(&ukParam, &key);

	return -1;
}

bool LB_STDCALL lbUsersModel::selectAccount(const char* _user) {
	while (hasMoreUsers()) {
		setNextUser();
		
		if (strcmp(getUserName(), _user) == 0) {
			finishUserIteration();			
			return true;
		}
	}

	return false;
}


bool LB_STDCALL lbUsersModel::selectAccount(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Users->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*name = "User";
		param->getUAPString(*&name, *&currentUserName);
		*name = "Pass";
		param->getUAPString(*&name, *&currentUserPassword);
		*name = "ID";
		param->getUAPLong(*&name, *&currentUserID);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}

	return false;
}

void LB_STDCALL lbUsersModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbUsersModel::unmark() {
	marked->setData((long) 0);
}

bool LB_STDCALL lbUsersModel::ismarked() {
	if (marked->getData() == 1) return true;
	return false;
}

long  LB_STDCALL lbUsersModel::getUserCount() {
	return Users->Count();
}

bool  LB_STDCALL lbUsersModel::hasMoreUsers() {
	return (Users->hasMoreElements() == 1);
}

void  LB_STDCALL lbUsersModel::setNextUser() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Users->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "User";
	param->getUAPString(*&name, *&currentUserName);
	*name = "Pass";
	param->getUAPString(*&name, *&currentUserPassword);
	*name = "ID";
	param->getUAPLong(*&name, *&currentUserID);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}

void  LB_STDCALL lbUsersModel::finishUserIteration() {
	Users->finishIteration();
}

char* LB_STDCALL lbUsersModel::getUserName() {
	return currentUserName->charrep();
}

long  LB_STDCALL lbUsersModel::getUserID() {
	return currentUserID->getData();
}

char* LB_STDCALL lbUsersModel::getUserPassword() {
	return currentUserPassword->charrep();
}

/*...sclass lbPluginUsersModel implementation:0:*/
/*...slbPluginUsersModel:0:*/
class lbPluginUsersModel : public lb_I_PluginImpl {
public:
	lbPluginUsersModel();
	
	virtual ~lbPluginUsersModel();

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
	
	UAP(lb_I_Unknown, ukUsersModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUsersModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUsersModel, lbPluginUsersModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginUsersModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginUsersModel::lbPluginUsersModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginUsersModel::~lbPluginUsersModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginUsersModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUsersModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUsersModel::initialize() {
}
	
bool LB_STDCALL lbPluginUsersModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUsersModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUsersModel == NULL) {
		lbUsersModel* UsersModel = new lbUsersModel();
		UsersModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(UsersModel, lb_I_Unknown, ukUsersModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUsersModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginUsersModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUsersModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbUsersModel* UsersModel = new lbUsersModel();
		UsersModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(UsersModel, lb_I_Unknown, ukUsersModel)
	}
	
	lb_I_Unknown* r = ukUsersModel.getPtr();
	ukUsersModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginUsersModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUsersModel != NULL) {
                ukUsersModel--;
                ukUsersModel.resetPtr();
        }
}
/*...e*/
/*...e*/



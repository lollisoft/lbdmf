
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
#include <Generated_EntityModelUserAccounts.h>

IMPLEMENT_FUNCTOR(instanceOflbUserAccountsModel, lbUserAccountsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUserAccountsModel)
	ADD_INTERFACE(lb_I_UserAccounts)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbUserAccountsModel)

void		LB_STDCALL lbUserAccountsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbUserAccountsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbUserAccountsModel::lbUserAccountsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, UserAccounts)

    REQUEST(getModuleInstance(), lb_I_String, currentpasswort)
    REQUEST(getModuleInstance(), lb_I_String, currentuserid)
    REQUEST(getModuleInstance(), lb_I_String, currentvorname)
    REQUEST(getModuleInstance(), lb_I_String, currentname)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentUserAccountsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbUserAccountsModel::lbUserAccountsModel() called." LOG_
}

lbUserAccountsModel::~lbUserAccountsModel() {
	_CL_VERBOSE << "lbUserAccountsModel::~lbUserAccountsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbUserAccountsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbUserAccountsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbUserAccountsModel::addUserAccounts(const char* _passwort, const char* _userid, const char* _vorname, const char* _name,  long _UserAccountsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_String, __passwort)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __userid)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __vorname)
    UAP_REQUEST(getModuleInstance(), lb_I_String, __name)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __UserAccountsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    *__passwort = _passwort;
    *__userid = _userid;
    *__vorname = _vorname;
    *__name = _name;

	
	__UserAccountsID->setData(_UserAccountsID);

    *paramname = "passwort";
    param->setUAPString(*&paramname, *&__passwort);
    *paramname = "userid";
    param->setUAPString(*&paramname, *&__userid);
    *paramname = "vorname";
    param->setUAPString(*&paramname, *&__vorname);
    *paramname = "name";
    param->setUAPString(*&paramname, *&__name);


	*paramname = "UserAccountsID";
	param->setUAPLong(*&paramname, *&__UserAccountsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__UserAccountsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	UserAccounts->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbUserAccountsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	UserAccounts->finishIteration();
	while (hasMoreUserAccounts()) {
		setNextUserAccounts();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			UserAccounts->remove(&key);
			UserAccounts->finishIteration();
		}
	}
}

void		LB_STDCALL lbUserAccountsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	UserAccounts->finishIteration();
	while (hasMoreUserAccounts()) {
		setNextUserAccounts();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			UserAccounts->remove(&key);
			UserAccounts->finishIteration();
		}
	}
}

bool LB_STDCALL lbUserAccountsModel::selectUserAccounts(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = UserAccounts->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "passwort";
    param->getUAPString(*&paramname, *&currentpasswort);
    *paramname = "userid";
    param->getUAPString(*&paramname, *&currentuserid);
    *paramname = "vorname";
    param->getUAPString(*&paramname, *&currentvorname);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);


		*paramname = "UserAccountsID";
		param->getUAPLong(*&paramname, *&currentUserAccountsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbUserAccountsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbUserAccountsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbUserAccountsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbUserAccountsModel::getUserAccountsCount() {
	return UserAccounts->Count();
}

bool  LB_STDCALL lbUserAccountsModel::hasMoreUserAccounts() {
	return (UserAccounts->hasMoreElements() == 1);
}

void  LB_STDCALL lbUserAccountsModel::setNextUserAccounts() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = UserAccounts->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "passwort";
    param->getUAPString(*&paramname, *&currentpasswort);
    *paramname = "userid";
    param->getUAPString(*&paramname, *&currentuserid);
    *paramname = "vorname";
    param->getUAPString(*&paramname, *&currentvorname);
    *paramname = "name";
    param->getUAPString(*&paramname, *&currentname);

	*paramname = "UserAccountsID";
	param->getUAPLong(*&paramname, *&currentUserAccountsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbUserAccountsModel::finishUserAccountsIteration() {
	UserAccounts->finishIteration();
}

long LB_STDCALL lbUserAccountsModel::get_id() {
	return currentUserAccountsID->getData();
}


char* LB_STDCALL lbUserAccountsModel::get_passwort() {
	return currentpasswort->charrep();
}

char* LB_STDCALL lbUserAccountsModel::get_userid() {
	return currentuserid->charrep();
}

char* LB_STDCALL lbUserAccountsModel::get_vorname() {
	return currentvorname->charrep();
}

char* LB_STDCALL lbUserAccountsModel::get_name() {
	return currentname->charrep();
}


class lbPluginUserAccountsModel : public lb_I_PluginImpl {
public:
	lbPluginUserAccountsModel();
	
	virtual ~lbPluginUserAccountsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUserAccountsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUserAccountsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUserAccountsModel, lbPluginUserAccountsModel)

lbErrCodes LB_STDCALL lbPluginUserAccountsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUserAccountsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUserAccountsModel::lbPluginUserAccountsModel() {
	_CL_VERBOSE << "lbPluginUserAccountsModel::lbPluginUserAccountsModel() called.\n" LOG_
}

lbPluginUserAccountsModel::~lbPluginUserAccountsModel() {
	_CL_VERBOSE << "lbPluginUserAccountsModel::~lbPluginUserAccountsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginUserAccountsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUserAccountsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUserAccountsModel::initialize() {
}
	
bool LB_STDCALL lbPluginUserAccountsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUserAccountsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserAccountsModel == NULL) {
		lbUserAccountsModel* UserAccountsModel = new lbUserAccountsModel();
		
	
		QI(UserAccountsModel, lb_I_Unknown, ukUserAccountsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserAccountsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUserAccountsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserAccountsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbUserAccountsModel* UserAccountsModel = new lbUserAccountsModel();
		
	
		QI(UserAccountsModel, lb_I_Unknown, ukUserAccountsModel)
	}
	
	lb_I_Unknown* r = ukUserAccountsModel.getPtr();
	ukUserAccountsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUserAccountsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserAccountsModel != NULL) {
                ukUserAccountsModel--;
                ukUserAccountsModel.resetPtr();
        }
}

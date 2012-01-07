
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
#include <Generated_EntityModelUser_Applications.h>

IMPLEMENT_FUNCTOR(instanceOflbUser_ApplicationsModel, lbUser_ApplicationsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUser_ApplicationsModel)
	ADD_INTERFACE(lb_I_User_Applications)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_EXTENSIBLEOBJECT(lbUser_ApplicationsModel)

void		LB_STDCALL lbUser_ApplicationsModel::setOperator(lb_I_Unknown* db) {

}

lbErrCodes	LB_STDCALL lbUser_ApplicationsModel::ExecuteOperation(const char* operationName) {
	return ERR_NONE;
}

lbUser_ApplicationsModel::lbUser_ApplicationsModel() {
	
	REQUEST(getModuleInstance(), lb_I_Container, User_Applications)

    REQUEST(getModuleInstance(), lb_I_Long, currentuserid)
    REQUEST(getModuleInstance(), lb_I_Long, currentanwendungenid)

	
	REQUEST(getModuleInstance(), lb_I_Long, currentUser_ApplicationsID)

	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbUser_ApplicationsModel::lbUser_ApplicationsModel() called." LOG_
}

lbUser_ApplicationsModel::~lbUser_ApplicationsModel() {
	_CL_VERBOSE << "lbUser_ApplicationsModel::~lbUser_ApplicationsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbUser_ApplicationsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbUser_ApplicationsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbUser_ApplicationsModel::addUser_Applications(long _userid, long _anwendungenid,  long _User_ApplicationsID) {
	lbErrCodes err = ERR_NONE;

    UAP_REQUEST(getModuleInstance(), lb_I_Long, __userid)
    UAP_REQUEST(getModuleInstance(), lb_I_Long, __anwendungenid)


	UAP_REQUEST(getModuleInstance(), lb_I_Long, __User_ApplicationsID)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)

	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

    __userid->setData(_userid);
    __anwendungenid->setData(_anwendungenid);

	
	__User_ApplicationsID->setData(_User_ApplicationsID);

    *paramname = "userid";
    param->setUAPLong(*&paramname, *&__userid);
    *paramname = "anwendungenid";
    param->setUAPLong(*&paramname, *&__anwendungenid);


	*paramname = "User_ApplicationsID";
	param->setUAPLong(*&paramname, *&__User_ApplicationsID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(__User_ApplicationsID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	User_Applications->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbUser_ApplicationsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	User_Applications->finishIteration();
	while (hasMoreUser_Applications()) {
		setNextUser_Applications();
		if (!ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			User_Applications->remove(&key);
			User_Applications->finishIteration();
		}
	}
}

void		LB_STDCALL lbUser_ApplicationsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	User_Applications->finishIteration();
	while (hasMoreUser_Applications()) {
		setNextUser_Applications();
		if (ismarked()) {
			UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
			ID->setData(get_id());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			User_Applications->remove(&key);
			User_Applications->finishIteration();
		}
	}
}

bool LB_STDCALL lbUser_ApplicationsModel::selectUser_Applications(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = User_Applications->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
    *paramname = "userid";
    param->getUAPLong(*&paramname, *&currentuserid);
    *paramname = "anwendungenid";
    param->getUAPLong(*&paramname, *&currentanwendungenid);


		*paramname = "User_ApplicationsID";
		param->getUAPLong(*&paramname, *&currentUser_ApplicationsID);

		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbUser_ApplicationsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbUser_ApplicationsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbUser_ApplicationsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbUser_ApplicationsModel::getUser_ApplicationsCount() {
	return User_Applications->Count();
}

bool  LB_STDCALL lbUser_ApplicationsModel::hasMoreUser_Applications() {
	return (User_Applications->hasMoreElements() == 1);
}

void  LB_STDCALL lbUser_ApplicationsModel::setNextUser_Applications() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = User_Applications->nextElement();
	QI(uk, lb_I_Parameter, param)

    *paramname = "userid";
    param->getUAPLong(*&paramname, *&currentuserid);
    *paramname = "anwendungenid";
    param->getUAPLong(*&paramname, *&currentanwendungenid);

	*paramname = "User_ApplicationsID";
	param->getUAPLong(*&paramname, *&currentUser_ApplicationsID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbUser_ApplicationsModel::finishUser_ApplicationsIteration() {
	User_Applications->finishIteration();
}

long LB_STDCALL lbUser_ApplicationsModel::get_id() {
	return currentUser_ApplicationsID->getData();
}


long LB_STDCALL lbUser_ApplicationsModel::get_userid() {
	return currentuserid->getData();
}

long LB_STDCALL lbUser_ApplicationsModel::get_anwendungenid() {
	return currentanwendungenid->getData();
}


class lbPluginUser_ApplicationsModel : public lb_I_PluginImpl {
public:
	lbPluginUser_ApplicationsModel();
	
	virtual ~lbPluginUser_ApplicationsModel();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUser_ApplicationsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUser_ApplicationsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUser_ApplicationsModel, lbPluginUser_ApplicationsModel)

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUser_ApplicationsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUser_ApplicationsModel::lbPluginUser_ApplicationsModel() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsModel::lbPluginUser_ApplicationsModel() called.\n" LOG_
}

lbPluginUser_ApplicationsModel::~lbPluginUser_ApplicationsModel() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsModel::~lbPluginUser_ApplicationsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginUser_ApplicationsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUser_ApplicationsModel::initialize() {
}
	
bool LB_STDCALL lbPluginUser_ApplicationsModel::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModel == NULL) {
		lbUser_ApplicationsModel* User_ApplicationsModel = new lbUser_ApplicationsModel();
		
	
		QI(User_ApplicationsModel, lb_I_Unknown, ukUser_ApplicationsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUser_ApplicationsModel.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbUser_ApplicationsModel* User_ApplicationsModel = new lbUser_ApplicationsModel();
		
	
		QI(User_ApplicationsModel, lb_I_Unknown, ukUser_ApplicationsModel)
	}
	
	lb_I_Unknown* r = ukUser_ApplicationsModel.getPtr();
	ukUser_ApplicationsModel.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUser_ApplicationsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUser_ApplicationsModel != NULL) {
                ukUser_ApplicationsModel--;
                ukUser_ApplicationsModel.resetPtr();
        }
}

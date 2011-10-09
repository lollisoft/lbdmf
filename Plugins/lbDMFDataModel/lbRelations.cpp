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
/*...sIncludes:0:*/
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
/*...e*/

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbRelations.h>

IMPLEMENT_FUNCTOR(instanceOflbUserApplicationRelationModel, lbUserApplicationRelationModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbUserApplicationRelationModel)
	ADD_INTERFACE(lb_I_User_Applications)
END_IMPLEMENT_LB_UNKNOWN()


/*...slbUserApplicationRelationModel\58\\58\lbUserApplicationRelationModel\40\\41\:0:*/
lbUserApplicationRelationModel::lbUserApplicationRelationModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Relations)
	REQUEST(getModuleInstance(), lb_I_Long, currentUserID)
	REQUEST(getModuleInstance(), lb_I_Long, currentAppID)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbUserApplicationRelationModel::lbUserApplicationRelationModel() called." LOG_
}
/*...e*/
/*...slbUserApplicationRelationModel\58\\58\\126\lbUserApplicationRelationModel\40\\41\:0:*/
lbUserApplicationRelationModel::~lbUserApplicationRelationModel() {
	_CL_VERBOSE << "lbUserApplicationRelationModel::~lbUserApplicationRelationModel() called." LOG_
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbUserApplicationRelationModel\58\\58\setData\40\lb_I_Unknown\42\\41\:0:*/
lbErrCodes LB_STDCALL lbUserApplicationRelationModel::setData(lb_I_Unknown*) {
		_LOG << "Error: lbUserApplicationRelationModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slong  LB_STDCALL lbUserApplicationRelationModel\58\\58\addRelation\40\long app_id\44\ long user_id\44\ long _id\41\:0:*/
long  LB_STDCALL lbUserApplicationRelationModel::addRelation(long app_id, long user_id, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, UserID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, AppID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)

	UserID->setData(user_id);
	AppID->setData(app_id);
	ID->setData(_id);
	
	*paramname = "UserID";
	param->setUAPLong(*&paramname, *&UserID);
	*paramname = "AppID";
	param->setUAPLong(*&paramname, *&AppID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Relations->insert(&ukParam, &key);

	return -1;
}
/*...e*/
/*...sbool  LB_STDCALL lbUserApplicationRelationModel\58\\58\selectRelation\40\long _id\41\:0:*/
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
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}
/*...e*/

void LB_STDCALL lbUserApplicationRelationModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbUserApplicationRelationModel::unmark() {
	marked->setData((long) 0);
}

bool LB_STDCALL lbUserApplicationRelationModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}
/*...sbool LB_STDCALL lbUserApplicationRelationModel\58\\58\addFilter\40\const char\42\ filter\44\ const char\42\ value\41\:0:*/
bool LB_STDCALL lbUserApplicationRelationModel::addFilter(const char* filter, const char* value) {
	return false;
}
/*...e*/
/*...sbool LB_STDCALL lbUserApplicationRelationModel\58\\58\resetFilter\40\const char\42\ filter\41\:0:*/
bool LB_STDCALL lbUserApplicationRelationModel::resetFilter(const char* filter) {
	return true;
}
/*...e*/
/*...sint  LB_STDCALL lbUserApplicationRelationModel\58\\58\getRelationCount\40\\41\:0:*/
int  LB_STDCALL lbUserApplicationRelationModel::getRelationCount() {
	return Relations->Count();
}
/*...e*/

void		LB_STDCALL lbUserApplicationRelationModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Relations->finishIteration();
	while (hasMoreRelations()) {
		setNextRelation();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Relations->remove(&key);
			Relations->finishIteration();
		}
	}
}

void		LB_STDCALL lbUserApplicationRelationModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Relations->finishIteration();
	while (hasMoreRelations()) {
		setNextRelation();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Relations->remove(&key);
			Relations->finishIteration();
		}
	}
}


/*...sbool  LB_STDCALL lbUserApplicationRelationModel\58\\58\hasMoreRelations\40\\41\:0:*/
bool  LB_STDCALL lbUserApplicationRelationModel::hasMoreRelations() {
	return Relations->hasMoreElements();
}
/*...e*/
/*...svoid  LB_STDCALL lbUserApplicationRelationModel\58\\58\setNextRelation\40\\41\:0:*/
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
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}
/*...e*/
/*...svoid  LB_STDCALL lbUserApplicationRelationModel\58\\58\finishRelationIteration\40\\41\:0:*/
void  LB_STDCALL lbUserApplicationRelationModel::finishRelationIteration() {
	Relations->finishIteration();
}
/*...e*/
/*...slong LB_STDCALL lbUserApplicationRelationModel\58\\58\getApplicationID\40\\41\:0:*/
long LB_STDCALL lbUserApplicationRelationModel::getApplicationID() {
	return currentAppID->getData();
}
/*...e*/
/*...slong  LB_STDCALL lbUserApplicationRelationModel\58\\58\getUserID\40\\41\:0:*/
long  LB_STDCALL lbUserApplicationRelationModel::getUserID() {
	return currentUserID->getData();
}
/*...e*/
/*...slong LB_STDCALL lbUserApplicationRelationModel\58\\58\getID\40\\41\:0:*/
long LB_STDCALL lbUserApplicationRelationModel::getID() {
	return currentID->getData();
}
/*...e*/

/*...sclass lbPluginUsersModel implementation:0:*/
/*...slbPluginUsersModel:0:*/
class lbPluginUserApplicationRelationModel : public lb_I_PluginImpl {
public:
	lbPluginUserApplicationRelationModel();
	
	virtual ~lbPluginUserApplicationRelationModel();

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
	data = NULL;
	further_lock = 1;
}

lbPluginUserApplicationRelationModel::~lbPluginUserApplicationRelationModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginUserApplicationRelationModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUserApplicationRelationModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
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
                ukUserApplicationRelationModel--;
                ukUserApplicationRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/







IMPLEMENT_FUNCTOR(instanceOflbApplicationFormularsRelationModel, lbApplicationFormularsRelationModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbApplicationFormularsRelationModel)
	ADD_INTERFACE(lb_I_Applications_Formulars)
END_IMPLEMENT_LB_UNKNOWN()


/*...slbApplicationFormularsRelationModel\58\\58\lbApplicationFormularsRelationModel\40\\41\:0:*/
lbApplicationFormularsRelationModel::lbApplicationFormularsRelationModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Relations)
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularID)
	REQUEST(getModuleInstance(), lb_I_Long, currentAppID)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbApplicationFormularsRelationModel::lbApplicationFormularsRelationModel() called." LOG_
}
/*...e*/
/*...slbApplicationFormularsRelationModel\58\\58\\126\lbApplicationFormularsRelationModel\40\\41\:0:*/
lbApplicationFormularsRelationModel::~lbApplicationFormularsRelationModel() {
	_CL_VERBOSE << "lbApplicationFormularsRelationModel::~lbApplicationFormularsRelationModel() called." LOG_
}
/*...e*/
/*...slbErrCodes LB_STDCALL lbApplicationFormularsRelationModel\58\\58\setData\40\lb_I_Unknown\42\\41\:0:*/
lbErrCodes LB_STDCALL lbApplicationFormularsRelationModel::setData(lb_I_Unknown*) {
		_LOG << "Error: lbApplicationFormularsRelationModel::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}
/*...e*/
/*...slong  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\addRelation\40\long app_id\44\ long user_id\44\ long _id\41\:0:*/
long  LB_STDCALL lbApplicationFormularsRelationModel::addRelation(long app_id, long user_id, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_Long, FormularID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, AppID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)

	_LOG << "lbApplicationFormularsRelationModel::addRelation(" << app_id << ", " << user_id << ", " << _id << ")." LOG_
	
	FormularID->setData(user_id);
	AppID->setData(app_id);
	ID->setData(_id);
	
	*paramname = "FormularID";
	param->setUAPLong(*&paramname, *&FormularID);
	*paramname = "AppID";
	param->setUAPLong(*&paramname, *&AppID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	
	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Relations->insert(&ukParam, &key);

	return -1;
}
/*...e*/
/*...sbool  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\selectRelation\40\long _id\41\:0:*/
bool  LB_STDCALL lbApplicationFormularsRelationModel::selectRelation(long _id) {
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
		
		*name = "FormularID";
		param->getUAPLong(*&name, *&currentFormularID);
		*name = "AppID";
		param->getUAPLong(*&name, *&currentAppID);
		*name = "ID";
		param->getUAPLong(*&name, *&currentID);
		*name = "marked";
		param->getUAPLong(*&name, *&marked);
		
		return true;
	}
	
	return false;
}
/*...e*/

void LB_STDCALL lbApplicationFormularsRelationModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbApplicationFormularsRelationModel::unmark() {
	marked->setData((long) 0);
}

bool LB_STDCALL lbApplicationFormularsRelationModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}
/*...sbool LB_STDCALL lbApplicationFormularsRelationModel\58\\58\addFilter\40\const char\42\ filter\44\ const char\42\ value\41\:0:*/
bool LB_STDCALL lbApplicationFormularsRelationModel::addFilter(const char* filter, const char* value) {
	return false;
}
/*...e*/
/*...sbool LB_STDCALL lbApplicationFormularsRelationModel\58\\58\resetFilter\40\const char\42\ filter\41\:0:*/
bool LB_STDCALL lbApplicationFormularsRelationModel::resetFilter(const char* filter) {
	return true;
}
/*...e*/
/*...sint  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\getRelationCount\40\\41\:0:*/
int  LB_STDCALL lbApplicationFormularsRelationModel::getRelationCount() {
	return Relations->Count();
}
/*...e*/

void		LB_STDCALL lbApplicationFormularsRelationModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Relations->finishIteration();
	while (hasMoreRelations()) {
		setNextRelation();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Relations->remove(&key);
			Relations->finishIteration();
		}
	}
}

void		LB_STDCALL lbApplicationFormularsRelationModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Relations->finishIteration();
	while (hasMoreRelations()) {
		setNextRelation();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Relations->remove(&key);
			Relations->finishIteration();
		}
	}
}


/*...sbool  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\hasMoreRelations\40\\41\:0:*/
bool  LB_STDCALL lbApplicationFormularsRelationModel::hasMoreRelations() {
	return Relations->hasMoreElements();
}
/*...e*/
/*...svoid  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\setNextRelation\40\\41\:0:*/
void  LB_STDCALL lbApplicationFormularsRelationModel::setNextRelation() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, name)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	
	uk = Relations->nextElement();
	QI(uk, lb_I_Parameter, param)
	
	*name = "FormularID";
	param->getUAPLong(*&name, *&currentFormularID);
	*name = "AppID";
	param->getUAPLong(*&name, *&currentAppID);
	*name = "ID";
	param->getUAPLong(*&name, *&currentID);
	*name = "marked";
	param->getUAPLong(*&name, *&marked);
}
/*...e*/
/*...svoid  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\finishRelationIteration\40\\41\:0:*/
void  LB_STDCALL lbApplicationFormularsRelationModel::finishRelationIteration() {
	Relations->finishIteration();
}
/*...e*/
/*...slong LB_STDCALL lbApplicationFormularsRelationModel\58\\58\getApplicationID\40\\41\:0:*/
long LB_STDCALL lbApplicationFormularsRelationModel::getApplicationID() {
	return currentAppID->getData();
}
/*...e*/
/*...slong  LB_STDCALL lbApplicationFormularsRelationModel\58\\58\getFormularID\40\\41\:0:*/
long  LB_STDCALL lbApplicationFormularsRelationModel::getFormularID() {
	return currentFormularID->getData();
}
/*...e*/
/*...slong LB_STDCALL lbApplicationFormularsRelationModel\58\\58\getID\40\\41\:0:*/
long LB_STDCALL lbApplicationFormularsRelationModel::getID() {
	return currentID->getData();
}
/*...e*/

/*...sclass lbPluginUsersModel implementation:0:*/
/*...slbPluginUsersModel:0:*/
class lbPluginApplicationFormularsRelationModel : public lb_I_PluginImpl {
public:
	lbPluginApplicationFormularsRelationModel();
	
	virtual ~lbPluginApplicationFormularsRelationModel();

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
	
	UAP(lb_I_Unknown, ukApplicationFormularsRelationModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationFormularsRelationModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationFormularsRelationModel, lbPluginApplicationFormularsRelationModel)

/*...slbErrCodes LB_STDCALL lbPluginUsersModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginApplicationFormularsRelationModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUsersModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginApplicationFormularsRelationModel::lbPluginApplicationFormularsRelationModel() {
	_CL_VERBOSE << "lbPluginUsersModel::lbPluginUsersModel() called.\n" LOG_
	ref = STARTREF;
	data = NULL;
	further_lock = 1;
}

lbPluginApplicationFormularsRelationModel::~lbPluginApplicationFormularsRelationModel() {
	_CL_VERBOSE << "lbPluginUsersModel::~lbPluginUsersModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationFormularsRelationModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationFormularsRelationModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationFormularsRelationModel::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationFormularsRelationModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationFormularsRelationModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationFormularsRelationModel == NULL) {
		lbApplicationFormularsRelationModel* Users_ApplicationModel = new lbApplicationFormularsRelationModel();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukApplicationFormularsRelationModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationFormularsRelationModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginUsersModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationFormularsRelationModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationFormularsRelationModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbApplicationFormularsRelationModel* Users_ApplicationModel = new lbApplicationFormularsRelationModel();
		Users_ApplicationModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(Users_ApplicationModel, lb_I_Unknown, ukApplicationFormularsRelationModel)
	}
	
	lb_I_Unknown* r = ukApplicationFormularsRelationModel.getPtr();
	ukApplicationFormularsRelationModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginApplicationFormularsRelationModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationFormularsRelationModel != NULL) {
                ukApplicationFormularsRelationModel--;
                ukApplicationFormularsRelationModel.resetPtr();
        }
}
/*...e*/
/*...e*/




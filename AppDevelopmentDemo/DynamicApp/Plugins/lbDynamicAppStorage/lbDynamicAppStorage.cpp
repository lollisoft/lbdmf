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

#include <lbDynamicAppStorage.h>

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppXMLStorage, lbDynamicAppXMLStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppXMLStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppXMLStorage::lbDynamicAppXMLStorage() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppStorage::lbDynamicAppStorage() called." LOG_
}

lbDynamicAppXMLStorage::~lbDynamicAppXMLStorage() {
	_CL_LOG << "lbDynamicAppStorage::~lbDynamicAppStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;


	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Unknown, uk)

	UAP(lb_I_Applications, applications)

	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP(lb_I_Unknown, ukParams)
	
	UAP(lb_I_Parameter, params)

	ukParams = meta->getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	*param = "ApplicationData";
	document->setCloning(false);
	params->getUAPContainer(*&param, *&document);	

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)
			
	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, forms)
			
	*name = "DBPrimaryKeys";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBPrimaryKeys, dbPrimaryKeys)
			
	*name = "DBForeignKeys";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBForeignKeys, dbForeignKeys)
			
	*name = "DBTables";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBTables, dbTables)
			
	*name = "DBColumns";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBColumns, dbColumns)
			
	*name = "FormularFields";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Fields, formularfields)
			
	*name = "ColumnTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_Column_Types, columntypes)
			
	*name = "FormActions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Actions, formActions)
			
	*name = "FormParams";
	uk = document->getElement(&key);
	QI(uk, lb_I_FormularParameter, formParams)
			
	*name = "AppParams";
	uk = document->getElement(&key);
	QI(uk, lb_I_ApplicationParameter, appParams)
	
	*name = "AppActions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Actions, appActions)
			
	*name = "AppAction_Steps";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Steps, appActionSteps)
			
	*name = "AppActionTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Types, appActionTypes)


	// Mark that data sets, that are related to this application
	applications = meta->getApplicationModel();
	
	meta->setStatusText("Info", "Mark application to be exported ...");
	
	applications->selectApplication(meta->getApplicationID());
	applications->mark();

	if ((forms != NULL) &&
	    (formularfields != NULL) &&
	    (dbColumns != NULL) &&
	    (dbPrimaryKeys != NULL) &&
	    (dbForeignKeys != NULL) &&
	    (dbTables != NULL) &&
	    (columntypes != NULL) &&
	    (formParams != NULL) &&
	    (formActions != NULL) &&
		(appParams != NULL) &&
		(appActions != NULL) &&
		(appActionTypes != NULL) &&
		(appActionSteps != NULL)) {

		*oStream << "<lbDMF applicationid=\"";
		*oStream << meta->getApplicationID() << "\">\n";
		
		applications->accept(*&aspect);
		forms->accept(*&aspect);
		dbPrimaryKeys->accept(*&aspect);
		dbForeignKeys->accept(*&aspect);
		dbTables->accept(*&aspect);
		dbColumns->accept(*&aspect);
		formularfields->accept(*&aspect);
		columntypes->accept(*&aspect);
		formActions->accept(*&aspect);
		formParams->accept(*&aspect);
		appParams->accept(*&aspect);
		appActions->accept(*&aspect);
		appActionTypes->accept(*&aspect);
		appActionSteps->accept(*&aspect);

		*oStream << "</lbDMF>\n";
	}
	_LOG << "lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) returns" LOG_
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppXMLStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppInternalStorage, lbDynamicAppInternalStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppInternalStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppInternalStorage::lbDynamicAppInternalStorage() called." LOG_
}

lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() {
	_CL_LOG << "lbDynamicAppInternalStorage::~lbDynamicAppInternalStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppInternalStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	_LOG << "lbDynamicAppInternalStorage::save() called." LOG_

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Unknown, uk)

	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	
	meta->setStatusText("Info", "Store internal file format ...");
	
	_LOG << "Get active document" LOG_
	
	UAP(lb_I_Unknown, ukDoc)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)

	UAP(lb_I_Unknown, ukParams)
	UAP(lb_I_Parameter, params)

	ukParams = meta->getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	_LOG << "Retrieve document container with name 'ApplicationData'" LOG_

	*param = "ApplicationData";
	document->setCloning(false);
	params->getUAPContainer(*&param, *&document);	

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)
			
	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, forms)
			
	*name = "DBPrimaryKeys";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBPrimaryKeys, dbPrimaryKeys)
			
	*name = "DBForeignKeys";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBForeignKeys, dbForeignKeys)
			
	*name = "DBTables";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBTables, dbTables)
			
	*name = "DBColumns";
	uk = document->getElement(&key);
	QI(uk, lb_I_DBColumns, dbColumns)
			
	*name = "FormularFields";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Fields, formularfields)
			
	*name = "ColumnTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_Column_Types, columntypes)
			
	*name = "FormActions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Actions, formActions)
			
	*name = "FormParams";
	uk = document->getElement(&key);
	QI(uk, lb_I_FormularParameter, formParams)
			
	*name = "AppParams";
	uk = document->getElement(&key);
	QI(uk, lb_I_ApplicationParameter, appParams)
	
	*name = "AppActions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Actions, appActions)
			
	*name = "AppAction_Steps";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Steps, appActionSteps)
			
	*name = "AppActionTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Types, appActionTypes)

	_LOG << "Start storing the data" LOG_

	if ((forms != NULL) &&
	    (dbPrimaryKeys != NULL) &&
	    (dbForeignKeys != NULL) &&
	    (dbColumns != NULL) &&
	    (dbTables != NULL) &&
	    (formularfields != NULL) &&
	    (formParams != NULL) &&
	    (columntypes != NULL) &&
	    (formActions != NULL) &&
		(appParams != NULL) &&
		(appActions != NULL) &&
		(appActionTypes != NULL) &&
		(appActionSteps != NULL)) {

		forms->accept(*&aspect);
		dbPrimaryKeys->accept(*&aspect);
		dbForeignKeys->accept(*&aspect);
		dbTables->accept(*&aspect);
		dbColumns->accept(*&aspect);
		formularfields->accept(*&aspect);
		columntypes->accept(*&aspect);
		formActions->accept(*&aspect);
		formParams->accept(*&aspect);
		appParams->accept(*&aspect);
		appActions->accept(*&aspect);
		appActionTypes->accept(*&aspect);
		appActionSteps->accept(*&aspect);
	}

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}


/*...sclass lbPluginDynamicAppXMLStorage implementation:0:*/
/*...slbPluginDynamicAppXMLStorage:0:*/
class lbPluginDynamicAppXMLStorage : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppXMLStorage();
	
	virtual ~lbPluginDynamicAppXMLStorage();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppXMLStorage)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppXMLStorage, lbPluginDynamicAppXMLStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppXMLStorage::lbPluginDynamicAppXMLStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDynamicAppXMLStorage::~lbPluginDynamicAppXMLStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppXMLStorage::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppXMLStorage::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppXMLStorage::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppXMLStorage::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppXMLStorage::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppXMLStorage* DynamicAppStorage = new lbDynamicAppXMLStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppXMLStorage::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/

//==================================

/*...sclass lbPluginDynamicAppInternalStorage implementation:0:*/
/*...slbPluginDynamicAppInternalStorage:0:*/
class lbPluginDynamicAppInternalStorage : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppInternalStorage();
	
	virtual ~lbPluginDynamicAppInternalStorage();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppInternalStorage)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppInternalStorage, lbPluginDynamicAppInternalStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppInternalStorage::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppInternalStorage::lbPluginDynamicAppInternalStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDynamicAppInternalStorage::~lbPluginDynamicAppInternalStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppInternalStorage::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppInternalStorage::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppInternalStorage::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppInternalStorage::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppInternalStorage::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppInternalStorage* DynamicAppStorage = new lbDynamicAppInternalStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppInternalStorage::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppInternalStorage* DynamicAppStorage = new lbDynamicAppInternalStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppInternalStorage::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/



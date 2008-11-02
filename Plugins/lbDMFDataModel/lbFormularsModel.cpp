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
#include <lbFormularsModel.h>

IMPLEMENT_FUNCTOR(instanceOflbFormularsModel, lbFormularsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormularsModel)
	ADD_INTERFACE(lb_I_Formulars)
END_IMPLEMENT_LB_UNKNOWN()


lbFormularsModel::lbFormularsModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Formulars)
	REQUEST(getModuleInstance(), lb_I_String, currentFormularName)
	REQUEST(getModuleInstance(), lb_I_String, currentMenuName)
	REQUEST(getModuleInstance(), lb_I_String, currentToolbarImage)
	REQUEST(getModuleInstance(), lb_I_String, currentEventName)
	REQUEST(getModuleInstance(), lb_I_String, currentMenuHilfe)
	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularID)
	REQUEST(getModuleInstance(), lb_I_Long, currentApplicationID)
	REQUEST(getModuleInstance(), lb_I_Long, currentTyp)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_VERBOSE << "lbFormularsModel::lbFormularsModel() called." LOG_
}

lbFormularsModel::~lbFormularsModel() {
	_CL_VERBOSE << "lbFormularsModel::~lbFormularsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbFormularsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbFormularsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormularsModel::addFormular(const char* name, const char* toolbarimage, const char* menuname, const char* eventname, const char* menuhilfe, long anwendung_id, long typ, long formular_id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, FormularName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, MenuName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, ToolbarImage)
	UAP_REQUEST(manager.getPtr(), lb_I_String, EventName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, MenuHilfe)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, AnwendungID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, FormularID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, Typ)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*FormularName = name;
	*ToolbarImage = toolbarimage;
	*MenuName = menuname;
	*EventName = eventname;
	*MenuHilfe = menuhilfe;
	
	AnwendungID->setData(anwendung_id);
	Typ->setData(typ);
	FormularID->setData(formular_id);

	_LOG << "lbFormularsModel::addFormular('" << name << "', '" << menuname << "'...) called." LOG_
	
	*paramname = "FormularName";
	param->setUAPString(*&paramname, *&FormularName);
	*paramname = "ToolbarImage";
	param->setUAPString(*&paramname, *&ToolbarImage);
	*paramname = "MenuName";
	param->setUAPString(*&paramname, *&MenuName);
	*paramname = "EventName";
	param->setUAPString(*&paramname, *&EventName);
	*paramname = "MenuHilfe";
	param->setUAPString(*&paramname, *&MenuHilfe);
	*paramname = "FormularID";
	param->setUAPLong(*&paramname, *&FormularID);
	*paramname = "AnwendungID";
	param->setUAPLong(*&paramname, *&AnwendungID);
	*paramname = "Typ";
	param->setUAPLong(*&paramname, *&Typ);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(FormularID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Formulars->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbFormularsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Formulars->finishIteration();
	while (hasMoreFormulars()) {
		setNextFormular();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getFormularID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulars->remove(&key);
			Formulars->finishIteration();
		}
	}
}

void		LB_STDCALL lbFormularsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Formulars->finishIteration();
	while (hasMoreFormulars()) {
		setNextFormular();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getFormularID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Formulars->remove(&key);
			Formulars->finishIteration();
		}
	}
}

bool LB_STDCALL lbFormularsModel::selectFormular(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Formulars->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*paramname = "FormularName";
		param->getUAPString(*&paramname, *&currentFormularName);
		*paramname = "ToolbarImage";
		param->getUAPString(*&paramname, *&currentToolbarImage);
		*paramname = "MenuName";
		param->getUAPString(*&paramname, *&currentMenuName);
		*paramname = "EventName";
		param->getUAPString(*&paramname, *&currentEventName);
		*paramname = "MenuHilfe";
		param->getUAPString(*&paramname, *&currentMenuHilfe);
		*paramname = "FormularID";
		param->getUAPLong(*&paramname, *&currentFormularID);
		*paramname = "AnwendungID";
		param->getUAPLong(*&paramname, *&currentApplicationID);
		*paramname = "Typ";
		param->getUAPLong(*&paramname, *&currentTyp);
		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbFormularsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbFormularsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbFormularsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbFormularsModel::getFormularCount() {
	return Formulars->Count();
}

bool  LB_STDCALL lbFormularsModel::hasMoreFormulars() {
	return (Formulars->hasMoreElements() == 1);
}

void  LB_STDCALL lbFormularsModel::setNextFormular() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Formulars->nextElement();
	QI(uk, lb_I_Parameter, param)

	*paramname = "FormularName";
	param->getUAPString(*&paramname, *&currentFormularName);
	*paramname = "ToolbarImage";
	param->getUAPString(*&paramname, *&currentToolbarImage);
	*paramname = "MenuName";
	param->getUAPString(*&paramname, *&currentMenuName);
	*paramname = "EventName";
	param->getUAPString(*&paramname, *&currentEventName);
	*paramname = "MenuHilfe";
	param->getUAPString(*&paramname, *&currentMenuHilfe);
	*paramname = "FormularID";
	param->getUAPLong(*&paramname, *&currentFormularID);
	*paramname = "AnwendungID";
	param->getUAPLong(*&paramname, *&currentApplicationID);
	*paramname = "Typ";
	param->getUAPLong(*&paramname, *&currentTyp);
	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbFormularsModel::finishFormularIteration() {
	Formulars->finishIteration();
}

char* LB_STDCALL lbFormularsModel::getName() {
	return currentFormularName->charrep();
}

char* LB_STDCALL lbFormularsModel::getToolbarImage() {
	return currentToolbarImage->charrep();
}

char* LB_STDCALL lbFormularsModel::getMenuName() {
	return currentMenuName->charrep();
}

char* LB_STDCALL lbFormularsModel::getMenuHelp() {
	return currentMenuHilfe->charrep();
}

char* LB_STDCALL lbFormularsModel::getEventName() {
	return currentEventName->charrep();
}

long  LB_STDCALL lbFormularsModel::getFormularID() {
	return currentFormularID->getData();
}

long  LB_STDCALL lbFormularsModel::getApplicationID() {
	return currentApplicationID->getData();
}

long  LB_STDCALL lbFormularsModel::getTyp() {
	return currentTyp->getData();
}

/*...sclass lbPluginFormularsModel implementation:0:*/
/*...slbPluginFormularsModel:0:*/
class lbPluginFormularsModel : public lb_I_PluginImpl {
public:
	lbPluginFormularsModel();
	
	virtual ~lbPluginFormularsModel();

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
	
	UAP(lb_I_Unknown, ukFormularsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularsModel, lbPluginFormularsModel)

/*...slbErrCodes LB_STDCALL lbPluginFormularsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginFormularsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFormularsModel::lbPluginFormularsModel() {
	_CL_VERBOSE << "lbPluginFormularsModel::lbPluginFormularsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginFormularsModel::~lbPluginFormularsModel() {
	_CL_VERBOSE << "lbPluginFormularsModel::~lbPluginFormularsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {
		lbFormularsModel* FormularsModel = new lbFormularsModel();
		FormularsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(FormularsModel, lb_I_Unknown, ukFormularsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularsModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormularsModel* FormularsModel = new lbFormularsModel();
		FormularsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(FormularsModel, lb_I_Unknown, ukFormularsModel)
	}
	
	lb_I_Unknown* r = ukFormularsModel.getPtr();
	ukFormularsModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFormularsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularsModel != NULL) {
                ukFormularsModel--;
                ukFormularsModel.resetPtr();
        }
}
/*...e*/
/*...e*/

IMPLEMENT_FUNCTOR(instanceOflbFormularFieldsModel, lbFormularFieldsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbFormularFieldsModel)
	ADD_INTERFACE(lb_I_Formular_Fields)
END_IMPLEMENT_LB_UNKNOWN()


lbFormularFieldsModel::lbFormularFieldsModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, FormularFields)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentTableName)
	REQUEST(getModuleInstance(), lb_I_String, currentDBType)
	REQUEST(getModuleInstance(), lb_I_Long, currentisFK)
	REQUEST(getModuleInstance(), lb_I_String, currentFKName)
	REQUEST(getModuleInstance(), lb_I_String, currentFKTable)
	
	REQUEST(getModuleInstance(), lb_I_Long, currentFormularID)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	uniqueID = 0;
	_CL_VERBOSE << "lbFormularFieldsModel::lbFormularFieldsModel() called." LOG_
}

lbFormularFieldsModel::~lbFormularFieldsModel() {
	_CL_VERBOSE << "lbFormularFieldsModel::~lbFormularFieldsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbFormularFieldsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbFormularFieldsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbFormularFieldsModel::addField(const char* name, const char* tablename, const char* dbtype, bool isFK, const char* FKName, const char* FKTable, long formular_id, long fieldid) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, TableName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, dbType)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, IsFK)
	UAP_REQUEST(manager.getPtr(), lb_I_String, fkName)
	UAP_REQUEST(manager.getPtr(), lb_I_String, fkTable)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, FormularID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*Name = name;
	*TableName = tablename;
	*dbType = dbtype;
	if (isFK)
		IsFK->setData((long) 1);
	else
		IsFK->setData((long) 0);
	*fkName = FKName;
	*fkTable = FKTable;
	

	if (fieldid == -2) {
		finishFieldsIteration();
		while (hasMoreFields()) {
			setNextField();
			
			if ((strcmp(currentName->charrep(), Name->charrep()) == 0) && (FormularID->equals(*&currentFormularID))) {
				UAP(lb_I_KeyBase, key)
				QI(currentID, lb_I_KeyBase, key)
				FormularFields->remove(&key);
			}
		}
		uniqueID++;
		ID->setData(uniqueID);
	} else {
		if (fieldid == -1) {
			uniqueID++;
			ID->setData(uniqueID);
		} else {
			ID->setData(fieldid);
		}
	}
	
	FormularID->setData(formular_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "TableName";
	param->setUAPString(*&paramname, *&TableName);
	*paramname = "DBType";
	param->setUAPString(*&paramname, *&dbType);
	*paramname = "IsFK";
	param->setUAPLong(*&paramname, *&IsFK);
	*paramname = "FKName";
	param->setUAPString(*&paramname, *&fkName);
	*paramname = "FKTable";
	param->setUAPString(*&paramname, *&fkTable);
	*paramname = "FormularID";
	param->setUAPLong(*&paramname, *&FormularID);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(FormularID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	FormularFields->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbFormularFieldsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	FormularFields->finishIteration();
	while (hasMoreFields()) {
		setNextField();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getFormularID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularFields->remove(&key);
			FormularFields->finishIteration();
		}
	}
}

void		LB_STDCALL lbFormularFieldsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	FormularFields->finishIteration();
	while (hasMoreFields()) {
		setNextField();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getFormularID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			FormularFields->remove(&key);
			FormularFields->finishIteration();
		}
	}
}

bool LB_STDCALL lbFormularFieldsModel::selectField(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = FormularFields->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*paramname = "Name";
		param->getUAPString(*&paramname, *&currentName);
		*paramname = "TableName";
		param->getUAPString(*&paramname, *&currentTableName);
		*paramname = "DBType";
		param->getUAPString(*&paramname, *&currentDBType);
		*paramname = "IsFK";
		param->getUAPLong(*&paramname, *&currentisFK);
		*paramname = "FKName";
		param->getUAPString(*&paramname, *&currentFKName);
		*paramname = "FKTable";
		param->getUAPString(*&paramname, *&currentFKTable);
		*paramname = "FormularID";
		param->getUAPLong(*&paramname, *&currentFormularID);
		*paramname = "ID";
		param->getUAPLong(*&paramname, *&currentID);
		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbFormularFieldsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbFormularFieldsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbFormularFieldsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbFormularFieldsModel::getFieldCount() {
	return FormularFields->Count();
}

bool  LB_STDCALL lbFormularFieldsModel::hasMoreFields() {
	return (FormularFields->hasMoreElements() == 1);
}

void  LB_STDCALL lbFormularFieldsModel::setNextField() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = FormularFields->nextElement();
	QI(uk, lb_I_Parameter, param)
		
	*paramname = "Name";
	param->getUAPString(*&paramname, *&currentName);
	*paramname = "TableName";
	param->getUAPString(*&paramname, *&currentTableName);
	*paramname = "DBType";
	param->getUAPString(*&paramname, *&currentDBType);
	*paramname = "IsFK";
	param->getUAPLong(*&paramname, *&currentisFK);
	*paramname = "FKName";
	param->getUAPString(*&paramname, *&currentFKName);
	*paramname = "FKTable";
	param->getUAPString(*&paramname, *&currentFKTable);
	*paramname = "FormularID";
	param->getUAPLong(*&paramname, *&currentFormularID);
	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);
	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbFormularFieldsModel::finishFieldsIteration() {
	FormularFields->finishIteration();
}

char* LB_STDCALL lbFormularFieldsModel::getName() {
	return currentName->charrep();
}

char* LB_STDCALL lbFormularFieldsModel::getTableName() {
	return currentTableName->charrep();
}

char* LB_STDCALL lbFormularFieldsModel::getDBType() {
	return currentDBType->charrep();
}

char* LB_STDCALL lbFormularFieldsModel::getFKName() {
	return currentFKName->charrep();
}

char* LB_STDCALL lbFormularFieldsModel::getFKTable() {
	return currentFKTable->charrep();
}

long  LB_STDCALL lbFormularFieldsModel::getFormularID() {
	return currentFormularID->getData();
}

long  LB_STDCALL lbFormularFieldsModel::getID() {
	return currentID->getData();
}

bool  LB_STDCALL lbFormularFieldsModel::isFK() {
	if (currentisFK->getData() == (long) 1)
		return true;
	else
		return false;
}

/*...sclass lbPluginFormularFieldsModel implementation:0:*/
/*...slbPluginFormularFieldsModel:0:*/
class lbPluginFormularFieldsModel : public lb_I_PluginImpl {
public:
	lbPluginFormularFieldsModel();
	
	virtual ~lbPluginFormularFieldsModel();

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
	
	UAP(lb_I_Unknown, ukFormularsModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularFieldsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularFieldsModel, lbPluginFormularFieldsModel)

/*...slbErrCodes LB_STDCALL lbPluginFormularFieldsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginFormularFieldsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularFieldsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginFormularFieldsModel::lbPluginFormularFieldsModel() {
	_CL_VERBOSE << "lbPluginFormularFieldsModel::lbPluginFormularFieldsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginFormularFieldsModel::~lbPluginFormularFieldsModel() {
	_CL_VERBOSE << "lbPluginFormularFieldsModel::~lbPluginFormularFieldsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularFieldsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularFieldsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularFieldsModel::initialize() {
}
	
bool LB_STDCALL lbPluginFormularFieldsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularFieldsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularFieldsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {
		lbFormularFieldsModel* FormularsModel = new lbFormularFieldsModel();
		FormularsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(FormularsModel, lb_I_Unknown, ukFormularsModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularsModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginFormularFieldsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginFormularFieldsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbFormularFieldsModel* FormularsModel = new lbFormularFieldsModel();
		FormularsModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(FormularsModel, lb_I_Unknown, ukFormularsModel)
	}
	
	lb_I_Unknown* r = ukFormularsModel.getPtr();
	ukFormularsModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginFormularFieldsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularsModel != NULL) {
                ukFormularsModel--;
                ukFormularsModel.resetPtr();
        }
}
/*...e*/
/*...e*/



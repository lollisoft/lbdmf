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
#include <lbDatabaseModel.h>

IMPLEMENT_FUNCTOR(instanceOflbDBTableModel, lbDBTableModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBTableModel)
	ADD_INTERFACE(lb_I_DBTables)
END_IMPLEMENT_LB_UNKNOWN()


lbDBTableModel::lbDBTableModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Tables)
	REQUEST(getModuleInstance(), lb_I_String, currentCatalog)
	REQUEST(getModuleInstance(), lb_I_String, currentSchema)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentType)
	REQUEST(getModuleInstance(), lb_I_String, currentRemarks)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_LOG << "lbDBTableModel::lbDBTableModel() called." LOG_
}

lbDBTableModel::~lbDBTableModel() {
	_CL_LOG << "lbDBTableModel::~lbDBTableModel() called." LOG_
}

lbErrCodes LB_STDCALL lbDBTableModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbDBTableModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbDBTableModel::addTable(const char* catalog, const char* schema, const char* name, const char* type, const char* remarks, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, Catalog)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Schema)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Name)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Type)
	UAP_REQUEST(manager.getPtr(), lb_I_String, Remarks)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*Catalog = catalog;
	*Schema = schema;
	*Name = name;
	*Type = type;
	*Remarks = remarks;
	ID->setData(_id);
	
	*paramname = "Catalog";
	param->setUAPString(*&paramname, *&Catalog);
	*paramname = "Schema";
	param->setUAPString(*&paramname, *&Schema);
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "Type";
	param->setUAPString(*&paramname, *&Type);
	*paramname = "Remarks";
	param->setUAPString(*&paramname, *&Remarks);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Tables->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbDBTableModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Tables->finishIteration();
	while (hasMoreTables()) {
		setNextTable();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getTableID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Tables->remove(&key);
			Tables->finishIteration();
		}
	}
}

void		LB_STDCALL lbDBTableModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Tables->finishIteration();
	while (hasMoreTables()) {
		setNextTable();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getTableID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Tables->remove(&key);
			Tables->finishIteration();
		}
	}
}

bool LB_STDCALL lbDBTableModel::selectTable(long id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(id);
	QI(ID, lb_I_KeyBase, key)

	uk = Tables->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)
		
		*paramname = "Catalog";
		param->getUAPString(*&paramname, *&currentCatalog);
		*paramname = "Schema";
		param->getUAPString(*&paramname, *&currentSchema);
		*paramname = "Name";
		param->getUAPString(*&paramname, *&currentName);
		*paramname = "Type";
		param->getUAPString(*&paramname, *&currentType);
		*paramname = "Remarks";
		param->getUAPString(*&paramname, *&currentRemarks);
		*paramname = "ID";
		param->getUAPLong(*&paramname, *&currentID);
		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbDBTableModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbDBTableModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbDBTableModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbDBTableModel::getTableCount() {
	return Tables->Count();
}

bool  LB_STDCALL lbDBTableModel::hasMoreTables() {
	return (Tables->hasMoreElements() == 1);
}

void  LB_STDCALL lbDBTableModel::setNextTable() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Tables->nextElement();
	QI(uk, lb_I_Parameter, param)
		
	*paramname = "Catalog";
	param->getUAPString(*&paramname, *&currentCatalog);
	*paramname = "Schema";
	param->getUAPString(*&paramname, *&currentSchema);
	*paramname = "Name";
	param->getUAPString(*&paramname, *&currentName);
	*paramname = "Type";
	param->getUAPString(*&paramname, *&currentType);
	*paramname = "Remarks";
	param->getUAPString(*&paramname, *&currentRemarks);
	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);
	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbDBTableModel::finishTableIteration() {
	Tables->finishIteration();
}

char* LB_STDCALL lbDBTableModel::getTableCatalog() {
	return currentName->charrep();
}

char* LB_STDCALL lbDBTableModel::getTableSchema() {
	return currentSchema->charrep();
}

char* LB_STDCALL lbDBTableModel::getTableName() {
	return currentName->charrep();
}

char* LB_STDCALL lbDBTableModel::getTableType() {
	return currentType->charrep();
}

char* LB_STDCALL lbDBTableModel::getTableRemarks() {
	return currentRemarks->charrep();
}

long  LB_STDCALL lbDBTableModel::getTableID() {
	return currentID->getData();
}

/*...sclass lbPluginDBTableModel implementation:0:*/
/*...slbPluginDBTableModel:0:*/
class lbPluginDBTableModel : public lb_I_PluginImpl {
public:
	lbPluginDBTableModel();
	
	virtual ~lbPluginDBTableModel();

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
	
	UAP(lb_I_Unknown, ukDBTableModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBTableModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBTableModel, lbPluginDBTableModel)

/*...slbErrCodes LB_STDCALL lbPluginDBTableModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDBTableModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBTableModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDBTableModel::lbPluginDBTableModel() {
	_CL_VERBOSE << "lbPluginDBTableModel::lbPluginDBTableModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDBTableModel::~lbPluginDBTableModel() {
	_CL_VERBOSE << "lbPluginDBTableModel::~lbPluginDBTableModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBTableModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBTableModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBTableModel::initialize() {
}
	
bool LB_STDCALL lbPluginDBTableModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBTableModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBTableModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {
		lbDBTableModel* DBTableModel = new lbDBTableModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTableModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBTableModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBTableModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDBTableModel* DBTableModel = new lbDBTableModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	}
	
	lb_I_Unknown* r = ukDBTableModel.getPtr();
	ukDBTableModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDBTableModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTableModel != NULL) {
                ukDBTableModel--;
                ukDBTableModel.resetPtr();
        }
}
/*...e*/
/*...e*/

IMPLEMENT_FUNCTOR(instanceOflbDBColumnsModel, lbDBColumnsModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBColumnsModel)
	ADD_INTERFACE(lb_I_DBColumns)
END_IMPLEMENT_LB_UNKNOWN()


lbDBColumnsModel::lbDBColumnsModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, Columns)
	REQUEST(getModuleInstance(), lb_I_String, currentName)
	REQUEST(getModuleInstance(), lb_I_String, currentTableName)
	REQUEST(getModuleInstance(), lb_I_String, currentTyp)
	REQUEST(getModuleInstance(), lb_I_String, currentPKField)
	REQUEST(getModuleInstance(), lb_I_String, currentPKTable)
	REQUEST(getModuleInstance(), lb_I_Long, currentisFK)
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentLen)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_LOG << "lbDBColumnsModel::lbDBColumnsModel() called." LOG_
}

lbDBColumnsModel::~lbDBColumnsModel() {
	_CL_LOG << "lbDBColumnsModel::~lbDBColumnsModel() called." LOG_
}

lbErrCodes LB_STDCALL lbDBColumnsModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbDBColumnsModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbDBColumnsModel::addColumn(const char* name, const char* typ, long len, bool isfk, const char* PKTable, const char* PKField, const char* tablename, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, TableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Typ)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pkField)
	UAP_REQUEST(getModuleInstance(), lb_I_String, pkTable)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, IsFK)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, Len)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*Name = name;
	*TableName = tablename;
	*Typ = typ;
	Len->setData(len);
	if (isfk)
		IsFK->setData((long) 1);
	else
		IsFK->setData((long) 0);
	*pkField = PKField;
	*pkTable = PKTable;
	
	ID->setData(_id);
	
	*paramname = "Name";
	param->setUAPString(*&paramname, *&Name);
	*paramname = "TableName";
	param->setUAPString(*&paramname, *&TableName);
	*paramname = "Typ";
	param->setUAPString(*&paramname, *&Typ);
	*paramname = "Len";
	param->setUAPLong(*&paramname, *&Len);
	*paramname = "IsFK";
	param->setUAPLong(*&paramname, *&IsFK);
	*paramname = "PKField";
	param->setUAPString(*&paramname, *&pkField);
	*paramname = "PKTable";
	param->setUAPString(*&paramname, *&pkTable);
	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);
	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	Columns->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbDBColumnsModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	Columns->finishIteration();
	while (hasMoreColumns()) {
		setNextColumn();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getColumnID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Columns->remove(&key);
			Columns->finishIteration();
		}
	}
}

void		LB_STDCALL lbDBColumnsModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	Columns->finishIteration();
	while (hasMoreColumns()) {
		setNextColumn();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getColumnID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			Columns->remove(&key);
			Columns->finishIteration();
		}
	}
}

bool LB_STDCALL lbDBColumnsModel::selectColumn(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = Columns->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)

		*paramname = "Name";
		param->getUAPString(*&paramname, *&currentName);
		*paramname = "TableName";
		param->getUAPString(*&paramname, *&currentTableName);
		*paramname = "Typ";
		param->getUAPString(*&paramname, *&currentTyp);
		*paramname = "IsFK";
		param->getUAPLong(*&paramname, *&currentisFK);
		*paramname = "PKField";
		param->getUAPString(*&paramname, *&currentPKField);
		*paramname = "PKTable";
		param->getUAPString(*&paramname, *&currentPKTable);
		*paramname = "ID";
		param->getUAPLong(*&paramname, *&currentID);
		*paramname = "marked";
		param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbDBColumnsModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbDBColumnsModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbDBColumnsModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbDBColumnsModel::getColumnCount() {
	return Columns->Count();
}

bool  LB_STDCALL lbDBColumnsModel::hasMoreColumns() {
	return (Columns->hasMoreElements() == 1);
}

void  LB_STDCALL lbDBColumnsModel::setNextColumn() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = Columns->nextElement();
	QI(uk, lb_I_Parameter, param)
		
	*paramname = "Name";
	param->getUAPString(*&paramname, *&currentName);
	*paramname = "TableName";
	param->getUAPString(*&paramname, *&currentTableName);
	*paramname = "Typ";
	param->getUAPString(*&paramname, *&currentTyp);
	*paramname = "IsFK";
	param->getUAPLong(*&paramname, *&currentisFK);
	*paramname = "PKField";
	param->getUAPString(*&paramname, *&currentPKField);
	*paramname = "PKTable";
	param->getUAPString(*&paramname, *&currentPKTable);
	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);
	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbDBColumnsModel::finishColumnIteration() {
	Columns->finishIteration();
}

char* LB_STDCALL lbDBColumnsModel::getColumnName() {
	return currentName->charrep();
}

char* LB_STDCALL lbDBColumnsModel::getColumnTableName() {
	return currentTableName->charrep();
}

char* LB_STDCALL lbDBColumnsModel::getColumnTyp() {
	return currentTyp->charrep();
}

char* LB_STDCALL lbDBColumnsModel::getColumnPKField() {
	return currentPKField->charrep();
}

char* LB_STDCALL lbDBColumnsModel::getColumnPKTable() {
	return currentPKTable->charrep();
}

long  LB_STDCALL lbDBColumnsModel::getColumnID() {
	return currentID->getData();
}

long  LB_STDCALL lbDBColumnsModel::getColumnLen() {
	return currentLen->getData();
}

bool  LB_STDCALL lbDBColumnsModel::isFK() {
	if (currentisFK->getData() == (long) 1)
		return true;
	else
		return false;
}

/*...sclass lbPluginDBColumnsModel implementation:0:*/
/*...slbPluginDBColumnsModel:0:*/
class lbPluginDBColumnsModel : public lb_I_PluginImpl {
public:
	lbPluginDBColumnsModel();
	
	virtual ~lbPluginDBColumnsModel();

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
	
	UAP(lb_I_Unknown, ukDBTableModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBColumnsModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBColumnsModel, lbPluginDBColumnsModel)

/*...slbErrCodes LB_STDCALL lbPluginDBColumnsModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDBColumnsModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBColumnsModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDBColumnsModel::lbPluginDBColumnsModel() {
	_CL_VERBOSE << "lbPluginDBColumnsModel::lbPluginDBColumnsModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDBColumnsModel::~lbPluginDBColumnsModel() {
	_CL_VERBOSE << "lbPluginDBColumnsModel::~lbPluginDBColumnsModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBColumnsModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBColumnsModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBColumnsModel::initialize() {
}
	
bool LB_STDCALL lbPluginDBColumnsModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBColumnsModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBColumnsModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {
		lbDBColumnsModel* DBTableModel = new lbDBColumnsModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTableModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBColumnsModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBColumnsModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDBColumnsModel* DBTableModel = new lbDBColumnsModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	}
	
	lb_I_Unknown* r = ukDBTableModel.getPtr();
	ukDBTableModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDBColumnsModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTableModel != NULL) {
                ukDBTableModel--;
                ukDBTableModel.resetPtr();
        }
}
/*...e*/
/*...e*/

IMPLEMENT_FUNCTOR(instanceOflbDBForeignKeysModel, lbDBForeignKeysModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBForeignKeysModel)
	ADD_INTERFACE(lb_I_DBForeignKeys)
END_IMPLEMENT_LB_UNKNOWN()


lbDBForeignKeysModel::lbDBForeignKeysModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, ForeignKeys)
	REQUEST(getModuleInstance(), lb_I_String, currentPKTableCatalog)
	REQUEST(getModuleInstance(), lb_I_String, currentPKTableSchema)
	REQUEST(getModuleInstance(), lb_I_String, currentPKTableName)
	REQUEST(getModuleInstance(), lb_I_String, currentPKTableColumnName)

	REQUEST(getModuleInstance(), lb_I_String, currentFKTableCatalog)
	REQUEST(getModuleInstance(), lb_I_String, currentFKTableSchema)
	REQUEST(getModuleInstance(), lb_I_String, currentFKTableName)
	REQUEST(getModuleInstance(), lb_I_String, currentFKTableColumnName)

	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentKeySequence)
	REQUEST(getModuleInstance(), lb_I_Long, currentUpdateRule)
	REQUEST(getModuleInstance(), lb_I_Long, currentDeleteRule)
	REQUEST(getModuleInstance(), lb_I_Long, marked)
	_CL_LOG << "lbDBForeignKeysModel::lbDBForeignKeysModel() called." LOG_
}

lbDBForeignKeysModel::~lbDBForeignKeysModel() {
	_CL_LOG << "lbDBForeignKeysModel::~lbDBForeignKeysModel() called." LOG_
}

lbErrCodes LB_STDCALL lbDBForeignKeysModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbDBForeignKeysModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbDBForeignKeysModel::addForeignKey(	const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name, 
													const char* fktable_cat, const char* fktable_schem, const char* fktable_name, const char* fkcolumn_name, 
													long key_seq, long update_rule, long delete_rule, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, PKTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, PKTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, PKTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, PKTableColumnName)

	UAP_REQUEST(getModuleInstance(), lb_I_String, FKTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, FKTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, FKTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, FKTableColumnName)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, KeySequence)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, UpdateRule)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, DeleteRule)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)


	*PKTableCatalog = pktable_cat;
	*PKTableSchema = pktable_schem;
	*PKTableName = pktable_name;
	*PKTableColumnName = pkcolumn_name;

	*FKTableCatalog = fktable_cat;
	*FKTableSchema = fktable_schem;
	*FKTableName = fktable_name;
	*FKTableColumnName = fkcolumn_name;

	KeySequence->setData(key_seq);
	UpdateRule->setData(update_rule);
	DeleteRule->setData(delete_rule);

	ID->setData(_id);
	
	
	*paramname = "PKTableCatalog";
	param->setUAPString(*&paramname, *&PKTableCatalog);
	*paramname = "PKTableSchema";
	param->setUAPString(*&paramname, *&PKTableSchema);
	*paramname = "PKTableName";
	param->setUAPString(*&paramname, *&PKTableName);
	*paramname = "PKTableColumnName";
	param->setUAPString(*&paramname, *&PKTableColumnName);

	*paramname = "FKTableCatalog";
	param->setUAPString(*&paramname, *&FKTableCatalog);
	*paramname = "FKTableSchema";
	param->setUAPString(*&paramname, *&FKTableSchema);
	*paramname = "FKTableName";
	param->setUAPString(*&paramname, *&FKTableName);
	*paramname = "FKTableColumnName";
	param->setUAPString(*&paramname, *&FKTableColumnName);

	*paramname = "KeySequence";
	param->setUAPLong(*&paramname, *&KeySequence);
	*paramname = "UpdateRule";
	param->setUAPLong(*&paramname, *&UpdateRule);
	*paramname = "DeleteRule";
	param->setUAPLong(*&paramname, *&DeleteRule);

	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	ForeignKeys->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbDBForeignKeysModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	ForeignKeys->finishIteration();
	while (hasMoreForeignKeys()) {
		setNextForeignKey();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getForeignKeyID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ForeignKeys->remove(&key);
			ForeignKeys->finishIteration();
		}
	}
}

void		LB_STDCALL lbDBForeignKeysModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	ForeignKeys->finishIteration();
	while (hasMoreForeignKeys()) {
		setNextForeignKey();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getForeignKeyID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			ForeignKeys->remove(&key);
			ForeignKeys->finishIteration();
		}
	}
}

bool LB_STDCALL lbDBForeignKeysModel::selectForeignKey(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = ForeignKeys->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)

	*paramname = "PKTableCatalog";
	param->getUAPString(*&paramname, *&currentPKTableCatalog);
	*paramname = "PKTableSchema";
	param->getUAPString(*&paramname, *&currentPKTableSchema);
	*paramname = "PKTableName";
	param->getUAPString(*&paramname, *&currentPKTableName);
	*paramname = "PKTableColumnName";
	param->getUAPString(*&paramname, *&currentPKTableColumnName);

	*paramname = "FKTableCatalog";
	param->getUAPString(*&paramname, *&currentFKTableCatalog);
	*paramname = "FKTableSchema";
	param->getUAPString(*&paramname, *&currentFKTableSchema);
	*paramname = "FKTableName";
	param->getUAPString(*&paramname, *&currentFKTableName);
	*paramname = "FKTableColumnName";
	param->getUAPString(*&paramname, *&currentFKTableColumnName);

	*paramname = "KeySequence";
	param->getUAPLong(*&paramname, *&currentKeySequence);
	*paramname = "UpdateRule";
	param->getUAPLong(*&paramname, *&currentUpdateRule);
	*paramname = "DeleteRule";
	param->getUAPLong(*&paramname, *&currentDeleteRule);

	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbDBForeignKeysModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbDBForeignKeysModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbDBForeignKeysModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbDBForeignKeysModel::getForeignKeyCount() {
	return ForeignKeys->Count();
}

bool  LB_STDCALL lbDBForeignKeysModel::hasMoreForeignKeys() {
	return (ForeignKeys->hasMoreElements() == 1);
}

void  LB_STDCALL lbDBForeignKeysModel::setNextForeignKey() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = ForeignKeys->nextElement();
	QI(uk, lb_I_Parameter, param)
		
	*paramname = "PKTableCatalog";
	param->getUAPString(*&paramname, *&currentPKTableCatalog);
	*paramname = "PKTableSchema";
	param->getUAPString(*&paramname, *&currentPKTableSchema);
	*paramname = "PKTableName";
	param->getUAPString(*&paramname, *&currentPKTableName);
	*paramname = "PKTableColumnName";
	param->getUAPString(*&paramname, *&currentPKTableColumnName);

	*paramname = "FKTableCatalog";
	param->getUAPString(*&paramname, *&currentFKTableCatalog);
	*paramname = "FKTableSchema";
	param->getUAPString(*&paramname, *&currentFKTableSchema);
	*paramname = "FKTableName";
	param->getUAPString(*&paramname, *&currentFKTableName);
	*paramname = "FKTableColumnName";
	param->getUAPString(*&paramname, *&currentFKTableColumnName);

	*paramname = "KeySequence";
	param->getUAPLong(*&paramname, *&currentKeySequence);
	*paramname = "UpdateRule";
	param->getUAPLong(*&paramname, *&currentUpdateRule);
	*paramname = "DeleteRule";
	param->getUAPLong(*&paramname, *&currentDeleteRule);

	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbDBForeignKeysModel::finishForeignKeyIteration() {
	ForeignKeys->finishIteration();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyPKTableCatalog() {
	return currentPKTableCatalog->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyPKTableSchema() {
	return currentPKTableSchema->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyPKTableName() {
	return currentPKTableName->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyPKTableColumnName() {
	return currentPKTableColumnName->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyFKTableCatalog() {
	return currentFKTableCatalog->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyFKTableSchema() {
	return currentFKTableSchema->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyFKTableName() {
	return currentFKTableName->charrep();
}

char* LB_STDCALL lbDBForeignKeysModel::getForeignKeyFKTableColumnName() {
	return currentFKTableColumnName->charrep();
}

long  LB_STDCALL lbDBForeignKeysModel::getForeignKeyID() {
	return currentID->getData();
}

long  LB_STDCALL lbDBForeignKeysModel::getForeignKeyKeySequence() {
	return currentKeySequence->getData();
}

long  LB_STDCALL lbDBForeignKeysModel::getForeignKeyUpdateRule() {
	return currentUpdateRule->getData();
}

long  LB_STDCALL lbDBForeignKeysModel::getForeignKeyDeleteRule() {
	return currentDeleteRule->getData();
}

/*...sclass lbPluginDBForeignKeysModel implementation:0:*/
/*...slbPluginDBForeignKeysModel:0:*/
class lbPluginDBForeignKeysModel : public lb_I_PluginImpl {
public:
	lbPluginDBForeignKeysModel();
	
	virtual ~lbPluginDBForeignKeysModel();

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
	
	UAP(lb_I_Unknown, ukDBTableModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBForeignKeysModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBForeignKeysModel, lbPluginDBForeignKeysModel)

/*...slbErrCodes LB_STDCALL lbPluginDBForeignKeysModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDBForeignKeysModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBForeignKeysModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDBForeignKeysModel::lbPluginDBForeignKeysModel() {
	_CL_VERBOSE << "lbPluginDBForeignKeysModel::lbPluginDBForeignKeysModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDBForeignKeysModel::~lbPluginDBForeignKeysModel() {
	_CL_VERBOSE << "lbPluginDBForeignKeysModel::~lbPluginDBForeignKeysModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBForeignKeysModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBForeignKeysModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBForeignKeysModel::initialize() {
}
	
bool LB_STDCALL lbPluginDBForeignKeysModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBForeignKeysModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {
		lbDBForeignKeysModel* DBTableModel = new lbDBForeignKeysModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTableModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBForeignKeysModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDBForeignKeysModel* DBTableModel = new lbDBForeignKeysModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	}
	
	lb_I_Unknown* r = ukDBTableModel.getPtr();
	ukDBTableModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDBForeignKeysModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTableModel != NULL) {
                ukDBTableModel--;
                ukDBTableModel.resetPtr();
        }
}
/*...e*/
/*...e*/

















IMPLEMENT_FUNCTOR(instanceOflbDBPrimaryKeysModel, lbDBPrimaryKeysModel)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDBPrimaryKeysModel)
	ADD_INTERFACE(lb_I_DBPrimaryKeys)
END_IMPLEMENT_LB_UNKNOWN()


lbDBPrimaryKeysModel::lbDBPrimaryKeysModel() {
	ref = STARTREF;
	REQUEST(getModuleInstance(), lb_I_Container, PrimaryKeys)
	REQUEST(getModuleInstance(), lb_I_String, currentTableCatalog)
	REQUEST(getModuleInstance(), lb_I_String, currentTableSchema)
	REQUEST(getModuleInstance(), lb_I_String, currentTableName)
	REQUEST(getModuleInstance(), lb_I_String, currentColumnName)
	REQUEST(getModuleInstance(), lb_I_String, currentColumnName_V2)
	
	REQUEST(getModuleInstance(), lb_I_Long, currentID)
	REQUEST(getModuleInstance(), lb_I_Long, currentKeySequence)
	REQUEST(getModuleInstance(), lb_I_Long, marked)

	_CL_LOG << "lbDBPrimaryKeysModel::lbDBPrimaryKeysModel() called." LOG_
}

lbDBPrimaryKeysModel::~lbDBPrimaryKeysModel() {
	_CL_LOG << "lbDBPrimaryKeysModel::~lbDBPrimaryKeysModel() called." LOG_
}

lbErrCodes LB_STDCALL lbDBPrimaryKeysModel::setData(lb_I_Unknown*) {
	_LOG << "Error: lbDBPrimaryKeysModel::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

long  LB_STDCALL lbDBPrimaryKeysModel::addPrimaryKey(const char* pktable_cat, const char* pktable_schem, const char* pktable_name, const char* pkcolumn_name, 
													long key_seq, const char* column_name, long _id) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, TableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, TableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, TableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ColumnName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, ColumnName_V2)
	
	UAP_REQUEST(getModuleInstance(), lb_I_Long, ID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, KeySequence)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, marked)
	UAP_REQUEST(manager.getPtr(), lb_I_Parameter, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)

	*TableCatalog = pktable_cat;
	*TableSchema = pktable_schem;
	*TableName = pktable_name;
	*ColumnName = pkcolumn_name;
	*ColumnName_V2 = column_name;

	KeySequence->setData(key_seq);

	ID->setData(_id);
	
	*paramname = "TableCatalog";
	param->setUAPString(*&paramname, *&TableCatalog);
	*paramname = "TableSchema";
	param->setUAPString(*&paramname, *&TableSchema);
	*paramname = "TableName";
	param->setUAPString(*&paramname, *&TableName);
	*paramname = "ColumnName";
	param->setUAPString(*&paramname, *&ColumnName);
	*paramname = "ColumnName_V2";
	param->setUAPString(*&paramname, *&ColumnName_V2);

	*paramname = "KeySequence";
	param->setUAPLong(*&paramname, *&KeySequence);

	*paramname = "ID";
	param->setUAPLong(*&paramname, *&ID);

	*paramname = "marked";
	param->setUAPLong(*&paramname, *&marked);

	UAP(lb_I_KeyBase, key)
	UAP(lb_I_Unknown, ukParam)
	QI(ID, lb_I_KeyBase, key)
	QI(param, lb_I_Unknown, ukParam)
	
	PrimaryKeys->insert(&ukParam, &key);

	return -1;
}

void		LB_STDCALL lbDBPrimaryKeysModel::deleteUnmarked() {
	lbErrCodes err = ERR_NONE;
	PrimaryKeys->finishIteration();
	while (hasMorePrimaryKeys()) {
		setNextPrimaryKey();
		if (!ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getPrimaryKeyID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			PrimaryKeys->remove(&key);
			PrimaryKeys->finishIteration();
		}
	}
}

void		LB_STDCALL lbDBPrimaryKeysModel::deleteMarked() {
	lbErrCodes err = ERR_NONE;
	PrimaryKeys->finishIteration();
	while (hasMorePrimaryKeys()) {
		setNextPrimaryKey();
		if (ismarked()) {
			UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
			ID->setData(getPrimaryKeyID());
			
			UAP(lb_I_KeyBase, key)
			QI(ID, lb_I_KeyBase, key)
			
			PrimaryKeys->remove(&key);
			PrimaryKeys->finishIteration();
		}
	}
}

bool LB_STDCALL lbDBPrimaryKeysModel::selectPrimaryKey(long user_id) {
	lbErrCodes err = ERR_NONE;
	
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP_REQUEST(manager.getPtr(), lb_I_Long, ID)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	
	ID->setData(user_id);
	QI(ID, lb_I_KeyBase, key)

	uk = PrimaryKeys->getElement(&key);

	if (uk != NULL) {
		QI(uk, lb_I_Parameter, param)

	*paramname = "TableCatalog";
	param->getUAPString(*&paramname, *&currentTableCatalog);
	*paramname = "TableSchema";
	param->getUAPString(*&paramname, *&currentTableSchema);
	*paramname = "TableName";
	param->getUAPString(*&paramname, *&currentTableName);
	*paramname = "ColumnName";
	param->getUAPString(*&paramname, *&currentColumnName);
	*paramname = "ColumnName_V2";
	param->getUAPString(*&paramname, *&currentColumnName_V2);

	*paramname = "KeySequence";
	param->getUAPLong(*&paramname, *&currentKeySequence);

	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);

	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
		
		return true;
	}

	return false;
}

bool LB_STDCALL lbDBPrimaryKeysModel::ismarked() {
	if (marked->getData() == (long) 1) return true;
	return false;
}

void LB_STDCALL lbDBPrimaryKeysModel::mark() {
	marked->setData((long) 1);
}

void LB_STDCALL lbDBPrimaryKeysModel::unmark() {
	marked->setData((long) 0);
}

int  LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyCount() {
	return PrimaryKeys->Count();
}

bool  LB_STDCALL lbDBPrimaryKeysModel::hasMorePrimaryKeys() {
	return (PrimaryKeys->hasMoreElements() == 1);
}

void  LB_STDCALL lbDBPrimaryKeysModel::setNextPrimaryKey() {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(manager.getPtr(), lb_I_String, paramname)
	UAP(lb_I_Parameter, param)
	UAP(lb_I_Unknown, uk)
		
	uk = PrimaryKeys->nextElement();
	QI(uk, lb_I_Parameter, param)
		
	*paramname = "TableCatalog";
	param->getUAPString(*&paramname, *&currentTableCatalog);
	*paramname = "TableSchema";
	param->getUAPString(*&paramname, *&currentTableSchema);
	*paramname = "TableName";
	param->getUAPString(*&paramname, *&currentTableName);
	*paramname = "ColumnName";
	param->getUAPString(*&paramname, *&currentColumnName);
	*paramname = "ColumnName_V2";
	param->getUAPString(*&paramname, *&currentColumnName_V2);
	
	*paramname = "KeySequence";
	param->getUAPLong(*&paramname, *&currentKeySequence);
	
	*paramname = "ID";
	param->getUAPLong(*&paramname, *&currentID);
	
	*paramname = "marked";
	param->getUAPLong(*&paramname, *&marked);
	
}

void  LB_STDCALL lbDBPrimaryKeysModel::finishPrimaryKeyIteration() {
	PrimaryKeys->finishIteration();
}

char* LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyTableCatalog() {
	return currentTableCatalog->charrep();
}

char* LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyTableSchema() {
	return currentTableSchema->charrep();
}

char* LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyTableName() {
	return currentTableName->charrep();
}

char* LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyColumnName() {
	return currentColumnName->charrep();
}

char* LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyColumnName_ODBC_V_2() {
	return currentColumnName_V2->charrep();
}

long  LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeyID() {
	return currentID->getData();
}

long  LB_STDCALL lbDBPrimaryKeysModel::getPrimaryKeySequence() {
	return currentKeySequence->getData();
}

/*...sclass lbPluginDBPrimaryKeysModel implementation:0:*/
/*...slbPluginDBPrimaryKeysModel:0:*/
class lbPluginDBPrimaryKeysModel : public lb_I_PluginImpl {
public:
	lbPluginDBPrimaryKeysModel();
	
	virtual ~lbPluginDBPrimaryKeysModel();

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
	
	UAP(lb_I_Unknown, ukDBTableModel)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBPrimaryKeysModel)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBPrimaryKeysModel, lbPluginDBPrimaryKeysModel)

/*...slbErrCodes LB_STDCALL lbPluginDBPrimaryKeysModel\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysModel::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBPrimaryKeysModel::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDBPrimaryKeysModel::lbPluginDBPrimaryKeysModel() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysModel::lbPluginDBPrimaryKeysModel() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDBPrimaryKeysModel::~lbPluginDBPrimaryKeysModel() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysModel::~lbPluginDBPrimaryKeysModel() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBPrimaryKeysModel::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysModel::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBPrimaryKeysModel::initialize() {
}
	
bool LB_STDCALL lbPluginDBPrimaryKeysModel::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBPrimaryKeysModel\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysModel::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {
		lbDBPrimaryKeysModel* DBTableModel = new lbDBPrimaryKeysModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTableModel.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDBPrimaryKeysModel\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysModel::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTableModel == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDBPrimaryKeysModel* DBTableModel = new lbDBPrimaryKeysModel();
		DBTableModel->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DBTableModel, lb_I_Unknown, ukDBTableModel)
	}
	
	lb_I_Unknown* r = ukDBTableModel.getPtr();
	ukDBTableModel.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDBPrimaryKeysModel::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTableModel != NULL) {
                ukDBTableModel--;
                ukDBTableModel.resetPtr();
        }
}
/*...e*/
/*...e*/






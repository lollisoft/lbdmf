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
/*...sincludes:0:*/
#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#include <conio.h>

#ifdef __WATCOMC__
#include <ctype.h>
#endif
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#ifndef OSX
#include <malloc.h>
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>

/*...sLB_PLUGINMANAGER_DLL scope:0:*/
#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>
/*...e*/

/*...e*/

/*...slbDatabaseInputStream:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbDatabaseInputStream : 
	public lb_I_DatabaseOperation {
public:
	lbDatabaseInputStream();
	virtual ~lbDatabaseInputStream();
	
	DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_VERBOSE << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_VERBOSE << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_VERBOSE << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_VERBOSE << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_VERBOSE << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_VERBOSE << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_VERBOSE << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*) { _CL_VERBOSE << "visit(lb_I_String*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Integer*) { _CL_VERBOSE << "visit(lb_I_Integer*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Long*) { _CL_VERBOSE << "visit(lb_I_Long*)" LOG_ }
	void LB_STDCALL visit(lb_I_Container*) { _CL_VERBOSE << "visit(lb_I_Container*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Database*) { _CL_VERBOSE << "visit(lb_I_Database*)" LOG_ } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { _CL_VERBOSE << "visit(lb_I_ColumnBinding*)" LOG_ } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { _CL_VERBOSE << "visit(lb_I_BoundColumn*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Query*) { _CL_VERBOSE << "visit(lb_I_Query*)" LOG_ } 
	void LB_STDCALL visit(lb_I_MVC_View*) { _CL_VERBOSE << "visit(lb_I_MVC_View*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Connection*) { _CL_VERBOSE << "visit(lb_I_Connection*)" LOG_ } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { _CL_VERBOSE << "visit(lb_I_InterfaceRepository*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Element*) { _CL_VERBOSE << "visit(lb_I_Element*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Module*) { _CL_VERBOSE << "visit(lb_I_Module*)" LOG_ } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { _CL_VERBOSE << "visit(lb_I_FunctorEntity*)" LOG_ }
	void LB_STDCALL visit(lb_I_InstanceReference*) { _CL_VERBOSE << "visit(lb_I_InstanceReference*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventHandler*) { _CL_VERBOSE << "visit(lb_I_EventHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventManager*) { _CL_VERBOSE << "visit(lb_I_EventManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventMapper*) { _CL_VERBOSE << "visit(lb_I_EventMapper*)" LOG_ }
	void LB_STDCALL visit(lb_I_EvHandler*) { _CL_VERBOSE << "visit(lb_I_EvHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_Dispatcher*) { _CL_VERBOSE << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_VERBOSE << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_VERBOSE << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_VERBOSE << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_VERBOSE << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*) { _CL_VERBOSE << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_VERBOSE << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_VERBOSE << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_VERBOSE << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_VERBOSE << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_VERBOSE << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_VERBOSE << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_VERBOSE << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_VERBOSE << "visit(lb_I_Window*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action*) { _CL_VERBOSE << "visit(lb_I_Action*)" LOG_ }
	void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_VERBOSE << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_VERBOSE << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_VERBOSE << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_VERBOSE << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_VERBOSE << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*) { _CL_VERBOSE << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation*) { _CL_VERBOSE << "visit(lb_I_DatabaseOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_VERBOSE << "visit(lb_I_ParameterTable*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileLocation*)  { _CL_VERBOSE << "visit(lb_I_FileLocation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DirLocation*)  { _CL_VERBOSE << "visit(lb_I_DirLocation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Socket*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer*) { _CL_LOG << "visit(lb_I_Transfer*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_DataObject*) { _CL_LOG << "visit(lb_I_Transfer_DataObject*)" LOG_ }
	void LB_STDCALL visit(lb_I_Thread*) { _CL_LOG << "visit(lb_I_Thread*)" LOG_ }
	
	void LB_STDCALL visit(lb_I_ThreadImplementation*) { _CL_LOG << "visit(lb_I_ThreadImplementation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchProtocol*) { _CL_LOG << "visit(lb_I_DispatchProtocol*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolTarget*) { _CL_LOG << "visit(lb_I_ProtocolTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_CallbackTarget*) { _CL_LOG << "visit(lb_I_CallbackTarget*)" LOG_ }
	void LB_STDCALL visit(lb_I_ProtocolManager*) { _CL_LOG << "visit(lb_I_ProtocolManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServer*) { _CL_LOG << "visit(lb_I_ApplicationServer*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationServerThread*) { _CL_LOG << "visit(lb_I_ApplicationServerThread*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchFunction*) { _CL_LOG << "visit(lb_I_DispatchFunction*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationClient*) { _CL_LOG << "visit(lb_I_ApplicationClient*)" LOG_ }
	void LB_STDCALL visit(lb_I_Proxy*) { _CL_LOG << "visit(lb_I_Proxy*)" LOG_ }
	
/*...e*/

	void LB_STDCALL visit(lb_I_Streamable*);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);
	void LB_STDCALL visit(lb_I_UserAccounts*);
	void LB_STDCALL visit(lb_I_Applications*);
	void LB_STDCALL visit(lb_I_User_Applications*);
	void LB_STDCALL visit(lb_I_Formulars*);
	void LB_STDCALL visit(lb_I_Formular_Fields*);
	void LB_STDCALL visit(lb_I_Column_Types*);
	void LB_STDCALL visit(lb_I_Formular_Actions*);
	void LB_STDCALL visit(lb_I_Action_Types*);
	void LB_STDCALL visit(lb_I_Action_Steps*);
	
	void LB_STDCALL visit(lb_I_ApplicationParameter*);
	void LB_STDCALL visit(lb_I_FormularParameter*);
	void LB_STDCALL visit(lb_I_Actions*);
	void LB_STDCALL visit(lb_I_Translations*);
	void LB_STDCALL visit(lb_I_DBColumns*);
	void LB_STDCALL visit(lb_I_DBTables*);

	bool LB_STDCALL begin(const char* DBName, const char* DBUser, const char* DBPass);
	bool LB_STDCALL begin(lb_I_Database* _db);
	void LB_STDCALL end();

//	lb_I_Stream* LB_STDCALL getStream();

	UAP(lb_I_Database, db)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseInputStream)
	ADD_INTERFACE(lb_I_DatabaseOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbDatabaseInputStream, lbDatabaseInputStream)


/*...slbErrCodes LB_STDCALL lbDatabaseInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbDatabaseInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_VERBOSE << "lbDatabaseInputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbDatabaseInputStream\58\\58\lbDatabaseInputStream\40\\41\:0:*/
lbDatabaseInputStream::lbDatabaseInputStream() 
{
	_CL_VERBOSE << "lbDatabaseInputStream::lbDatabaseInputStream() called." LOG_
	ref = STARTREF;
}
/*...e*/
/*...slbDatabaseInputStream\58\\58\\126\lbDatabaseInputStream\40\\41\:0:*/
lbDatabaseInputStream::~lbDatabaseInputStream() {
	_CL_VERBOSE << "lbDatabaseInputStream::~lbDatabaseInputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbDatabaseInputStream::begin(const char* DBName, const char* DBUser, const char* DBPass) {
	REQUEST(manager.getPtr(), lb_I_Database, db)
	
	bool ret = false;
	
	
	
	return ret;
}

bool LB_STDCALL lbDatabaseInputStream::begin(lb_I_Database* _db) {
	lbErrCodes err = ERR_NONE;
	if (_db != NULL) {
		QI(_db, lb_I_Database, db)
		bool ret = _db->isConnected();

		if (!ret) {
			_CL_VERBOSE << "lbDatabaseInputStream::begin(lb_I_Database* _db) Error: Must have a database connection." LOG_
		}
		
		return ret;
	} else {
		_CL_VERBOSE << "lbDatabaseInputStream::begin(lb_I_Database* _db) Error: Uninitialized database onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Streamable* pm) {
	if (db != NULL) {
		/*
		   How to implement private database 'streams' ?

		   Theoretically, the database must inherid from a lb_I_Streamable interface.
		   Additionally, the function called here, must distinguish between file operations
		   and database operations.
		*/
		pm->load(db.getPtr());
	} else {
		_CL_VERBOSE << "lbDatabaseInputStream::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_UserAccounts* users) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, userid, passwort from Users") != ERR_NONE) {
		_LOG << "Error: Access to user table failed. Read user accounts would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No user accounts found. All accounts may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qUID)
		UAP(lb_I_String, qPWD)
		
		qID = q->getAsLong(1);
		qUID = q->getAsString(2);
		qPWD = q->getAsString(3);
		
		users->addAccount(qUID->charrep(), qPWD->charrep(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qUID = q->getAsString(2);
			qPWD = q->getAsString(3);
		
			users->addAccount(qUID->charrep(), qPWD->charrep(), qID->getData());
		}
	}
}



void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBTables* tables) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	UAP(lb_I_Container, Tables)
	
	Tables = db->getTables();
	
	long i = 0;
	
	while (Tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)
		
		uk = Tables->nextElement();
		QI(uk, lb_I_Parameter, param)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableCatalog)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableSchema)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableType)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableRemarks)

		*name = "TableCatalog";
		param->getUAPString(*&name, *&szTableCatalog);
		*name = "TableSchema";
		param->getUAPString(*&name, *&szTableSchema);
		*name = "TableName";
		param->getUAPString(*&name, *&szTableName);
		*name = "TableTyp";
		param->getUAPString(*&name, *&szTableType);
		*name = "TableRemarks";
		param->getUAPString(*&name, *&szTableRemarks);
		
		tables->addTable(szTableCatalog->charrep(), szTableSchema->charrep(), szTableName->charrep(), szTableType->charrep(), szTableRemarks->charrep(), ++i);
	}	
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBColumns* columns) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	UAP(lb_I_Container, Columns)
	
	Columns = db->getColumns();
	
	long i = 0;
	
	while (Columns->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)
		
		uk = Columns->nextElement();
		QI(uk, lb_I_Parameter, param)
			
		UAP_REQUEST(getModuleInstance(), lb_I_String, szCatalog)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szSchema)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTableName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szColumnName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szTypeName)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szRemarks)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szIsNullable)
		UAP_REQUEST(getModuleInstance(), lb_I_String, szColumnDefault)

		UAP_REQUEST(getModuleInstance(), lb_I_Long, DataType)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, ColumnSize)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, BufferLength)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, DecimalDigits)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, NumPrecRadix)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, Nullable)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, SQLDataType)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, DatetimeSubtypeCode)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, CharOctetLength)
		UAP_REQUEST(getModuleInstance(), lb_I_Long, OrdinalPosition)

		*name = "TableCatalog";
		param->getUAPString(*&name, *&szCatalog);
		*name = "TableSchema";
		param->getUAPString(*&name, *&szSchema);
		*name = "TableName";
		param->getUAPString(*&name, *&szTableName);
		*name = "ColumnName";
		param->getUAPString(*&name, *&szColumnName);
		
		*name = "DataType";
		param->getUAPLong(*&name, *&DataType);
		*name = "TypeName";
		param->getUAPString(*&name, *&szTypeName);
		*name = "ColumnSize";
		param->getUAPLong(*&name, *&ColumnSize);
		*name = "BufferLength";
		param->getUAPLong(*&name, *&BufferLength);
		*name = "DecimalDigits";
		param->getUAPLong(*&name, *&DecimalDigits);
		*name = "NumPrecRadix";
		param->getUAPLong(*&name, *&NumPrecRadix);
		*name = "Nullable";
		param->getUAPLong(*&name, *&Nullable);
		*name = "Remarks";
		param->getUAPString(*&name, *&szRemarks);
		*name = "ColumnDefault";
		param->getUAPString(*&name, *&szColumnDefault);
		*name = "SQLDataType";
		param->getUAPLong(*&name, *&SQLDataType);
		*name = "DatetimeSubtypeCode";
		param->getUAPLong(*&name, *&DatetimeSubtypeCode);
		*name = "CharOctetLength";
		param->getUAPLong(*&name, *&CharOctetLength);
		*name = "OrdinalPosition";
		param->getUAPLong(*&name, *&OrdinalPosition);
		*name = "IsNullable";
		param->getUAPString(*&name, *&szIsNullable);
		
		columns->addColumn(szColumnName->charrep(), szTypeName->charrep(), ColumnSize->getData(), false, "", "", szTableName->charrep(), ++i);
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Translations* trans) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, text, translated, language from translations") != ERR_NONE) {
		_LOG << "Error: Access to translations table failed. Read translations would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No translations found. All accounts may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qText)
		UAP(lb_I_String, qTranslated)
		UAP(lb_I_String, qLanguage)
		
		qID = q->getAsLong(1);
		qText = q->getAsString(2);
		qTranslated = q->getAsString(3);
		qLanguage = q->getAsString(4);
		
		trans->addTranslation(qText->charrep(), qTranslated->charrep(), qLanguage->charrep(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			UAP(lb_I_Long, qID)
			UAP(lb_I_String, qText)
			UAP(lb_I_String, qTranslated)
			UAP(lb_I_String, qLanguage)
		
			qID = q->getAsLong(1);
			qText = q->getAsString(2);
			qTranslated = q->getAsString(3);
			qLanguage = q->getAsString(4);
		
			trans->addTranslation(qText->charrep(), qTranslated->charrep(), qLanguage->charrep(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_FormularParameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, parametername, parametervalue, formularid from Formular_Parameters") != ERR_NONE) {
		_LOG << "Error: Access to Formular_Parameters table failed. Read Formular_Parameters would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qFID)
		UAP(lb_I_String, qV)
		UAP(lb_I_String, qN)
		
		qID = q->getAsLong(1);
		qN = q->getAsString(2);
		qV = q->getAsString(3);
		qFID = q->getAsLong(4);
		
		params->addParameter(qN->charrep(), qV->charrep(), qFID->getData(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qN = q->getAsString(2);
			qV = q->getAsString(3);
			qFID = q->getAsLong(4);
			
			params->addParameter(qN->charrep(), qV->charrep(), qFID->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Actions* actions) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	char *_actionquery = "select id, name, typ, source, target from actions";

	
	if (q->query(_actionquery) != ERR_NONE) {
		_LOG << "Error: Access to action table failed. Read actions would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qTyp)
		UAP(lb_I_Long, qTarget)
		UAP(lb_I_String, qName)
		UAP(lb_I_String, qSource)
		
		qID = q->getAsLong(1);
		qName = q->getAsString(2);
		qTyp = q->getAsLong(3);
		qSource = q->getAsString(4);
		qTarget = q->getAsLong(5);
		
		actions->addAction(qName->charrep(), qTyp->getData(), qSource->charrep(), qTarget->getData(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qName = q->getAsString(2);
			qTyp = q->getAsLong(3);
			qSource = q->getAsString(4);
			qTarget = q->getAsLong(5);
		
			actions->addAction(qName->charrep(), qTyp->getData(), qSource->charrep(), qTarget->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Action_Steps* action_steps) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	char *_actionquery = "select id, bezeichnung, actionid, a_order_nr, \"type\", what from action_steps";
	
	if (q->query(_actionquery) != ERR_NONE) {
		_LOG << "Error: Access to action_steps table failed. Read action_steps would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No action_steps found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qBezeichnung)
		UAP(lb_I_Long, qActionID)
		UAP(lb_I_Long, qOrderNo)
		UAP(lb_I_Long, qType)
		UAP(lb_I_String, qWhat)
		
		qID = q->getAsLong(1);
		qBezeichnung = q->getAsString(2);
		qActionID = q->getAsLong(3);
		qOrderNo = q->getAsLong(4);
		qType = q->getAsLong(5);
		qWhat = q->getAsString(6);

		action_steps->addActionStep(qBezeichnung->charrep(), qActionID->getData(), qOrderNo->getData(), qType->getData(), qWhat->charrep(), qID->getData());
		
		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qBezeichnung = q->getAsString(2);
			qActionID = q->getAsLong(3);
			qOrderNo = q->getAsLong(4);
			qType = q->getAsLong(5);
			qWhat = q->getAsString(6);

			action_steps->addActionStep(qBezeichnung->charrep(), qActionID->getData(), qOrderNo->getData(), qType->getData(), qWhat->charrep(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Action_Types* action_types) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	char *_actionquery = "select id, bezeichnung, action_handler, module from action_types";

	
	if (q->query(_actionquery) != ERR_NONE) {
		_LOG << "Error: Access to action_types table failed. Read action_types would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No action_types found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qBezeichnung)
		UAP(lb_I_String, qActionHandler)
		UAP(lb_I_String, qModule)
		
		qID = q->getAsLong(1);
		qBezeichnung = q->getAsString(2);
		qActionHandler = q->getAsString(3);
		qModule = q->getAsString(4);
		
		action_types->addActionTypes(qBezeichnung->charrep(), qActionHandler->charrep(), qModule->charrep(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qBezeichnung = q->getAsString(2);
			qActionHandler = q->getAsString(3);
			qModule = q->getAsString(4);
		
			action_types->addActionTypes(qBezeichnung->charrep(), qActionHandler->charrep() , qModule->charrep(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Formular_Actions* formular_actions) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	char *_actionquery = "select id, formular, \"action\", event from formular_actions";

	
	if (q->query(_actionquery) != ERR_NONE) {
		_LOG << "Error: Access to formular_actions table failed. Read formular_actions would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qFormular)
		UAP(lb_I_Long, qAction)
		UAP(lb_I_String, qEvent)
		
		qID = q->getAsLong(1);
		qFormular = q->getAsLong(2);
		qAction = q->getAsLong(3);
		qEvent = q->getAsString(4);
		
		formular_actions->addFormularAction(qFormular->getData() , qAction->getData(), qEvent->charrep(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qFormular = q->getAsLong(2);
			qAction = q->getAsLong(3);
			qEvent = q->getAsString(4);
		
			formular_actions->addFormularAction(qFormular->getData() , qAction->getData(), qEvent->charrep(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ApplicationParameter* params) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, parametername, parametervalue, anwendungid from Anwendungs_Parameter") != ERR_NONE) {
		_LOG << "Error: Access to Anwendungs_Parameters table failed. Read Anwendungs_Parameters would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Anwendungs_Parameters found. All data may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qAID)
		UAP(lb_I_String, qV)
		UAP(lb_I_String, qN)
		
		qID = q->getAsLong(1);
		qN = q->getAsString(2);
		qV = q->getAsString(3);
		qAID = q->getAsLong(4);
		
		params->addParameter(qN->charrep(), qV->charrep(), qAID->getData(), qID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qN = q->getAsString(2);
			qV = q->getAsString(3);
			qAID = q->getAsLong(4);
			
			params->addParameter(qN->charrep(), qV->charrep(), qAID->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Formular_Fields* formularfields) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
		
		if (db == NULL) {
			_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
			return;
		}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	// 1 = Dynamisch aufgebautes Datenbankformular
	if (q->query("select id from formulare where typ = 1") != ERR_NONE) {
		_LOG << "Error: Access to formular table failed. Read formulars would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	while (err == ERR_NONE) {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Query, query_query)
		UAP_REQUEST(getModuleInstance(), lb_I_String, query)
		
		query_query = db->getQuery(0);
		
		FormularID = q->getAsLong(1);
		
		*query = "select parametervalue from formular_parameters where formularid = ";
		*query += FormularID->charrep();
		
		if (query_query->query(query->charrep()) == ERR_NONE) {
			// Query succeeded
			UAP(lb_I_String, formularquery)
			UAP(lb_I_Query, form_query)
			
			lbErrCodes qqerr = query_query->first();
			
			if ((qqerr == ERR_NONE) || (qqerr == WARN_DB_NODATA)) {
				// Get the stored query for the formular with id = FormularID
				formularquery = query_query->getAsString(1);
				form_query = db->getQuery(0);
				
				form_query->enableFKCollecting();
				if (form_query->query(formularquery->charrep()) == ERR_NONE) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						char* name = NULL;
						char* tablename = NULL;
						name = strdup(form_query->getColumnName(i));
						tablename = strdup(form_query->getTableName(name));
						
						
						if (form_query->hasFKColumn(name) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery(0);
							
							t = form_query->getPKTable(name);
							c = form_query->getPKColumn(name);
							
							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;
							
							sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
									"where FKName = '%s' and FKTable = '%s'", name, form_query->getTableName(name));
							
							if (fkpkmapping_query->query(buffer) == ERR_NONE) {
								UAP(lb_I_String, PKName)
								UAP(lb_I_String, PKTable)
								lbErrCodes err = fkpkmapping_query->first();
								
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									PKName = fkpkmapping_query->getAsString(1);
									PKTable = fkpkmapping_query->getAsString(2);
									
									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
									
									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											formularfields->addField(name, tablename, "Bit", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											formularfields->addField(name, tablename,  "Float", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											formularfields->addField(name, tablename,  "String", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											formularfields->addField(name, tablename,  "Binary", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
											
										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											formularfields->addField(name, tablename,  "Integer", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							
							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									formularfields->addField(name, tablename,  "Bit", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									formularfields->addField(name, tablename,  "Float", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									formularfields->addField(name, tablename,  "String", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									formularfields->addField(name, tablename,  "Binary", false, "", "", FormularID->getData());
									break;
									
								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									formularfields->addField(name, tablename,  "Integer", true, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
						free(name);
						free(tablename);
					}
				} else {
					_LOG << "Error: Query '" << formularquery->charrep() << "' failed!" LOG_
				}
			}
		} else {
			_LOG << "Error: Query '" << query->charrep() << "' failed!" LOG_
		}
		err = q->next();
	}

	
	if (err == WARN_DB_NODATA) {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Query, query_query)
		UAP_REQUEST(getModuleInstance(), lb_I_String, query)
		
		query_query = db->getQuery(0);
		
		FormularID = q->getAsLong(1);
		
		*query = "select parametervalue from formular_parameters where formularid = ";
		*query += FormularID->charrep();
		
		if (query_query->query(query->charrep()) == ERR_NONE) {
			// Query succeeded
			UAP(lb_I_String, formularquery)
			UAP(lb_I_Query, form_query)
			
			lbErrCodes qqerr = query_query->first();
			
			if ((qqerr == ERR_NONE) || (qqerr == WARN_DB_NODATA)) {
				// Get the stored query for the formular with id = FormularID
				formularquery = query_query->getAsString(1);
				form_query = db->getQuery(0);
				
				form_query->enableFKCollecting();
				if (form_query->query(formularquery->charrep()) == ERR_NONE) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						char* name = NULL;
						char* tablename = NULL;
						name = strdup(form_query->getColumnName(i));
						tablename = strdup(form_query->getTableName(name));
						if (form_query->hasFKColumn(name) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery(0);
							
							t = form_query->getPKTable(name);
							c = form_query->getPKColumn(name);
							
							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;
							
							sprintf(buffer, "select PKName, PKTable	from ForeignKey_VisibleData_Mapping "
									"where FKName = '%s' and FKTable = '%s'", name, form_query->getTableName(name));
							
							if (fkpkmapping_query->query(buffer) == ERR_NONE) {
								UAP(lb_I_String, PKName)
								UAP(lb_I_String, PKTable)
								lbErrCodes err = fkpkmapping_query->first();
								
								if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
									PKName = fkpkmapping_query->getAsString(1);
									PKTable = fkpkmapping_query->getAsString(2);
									
									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
									
									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											formularfields->addField(name, tablename, "Bit", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											formularfields->addField(name, tablename, "Float", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											formularfields->addField(name, tablename, "String", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											formularfields->addField(name, tablename, "Binary", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
											
										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											formularfields->addField(name, tablename, "Integer", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							
							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									formularfields->addField(name, tablename, "Bit", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									formularfields->addField(name, tablename, "Float", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									formularfields->addField(name, tablename, "String", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									formularfields->addField(name, tablename, "Binary", false, "", "", FormularID->getData());
									break;
									
								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									formularfields->addField(name, tablename, "Integer", true, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
						free(name);
						free(tablename);
					}
				} else {
					_LOG << "Error: Query '" << formularquery->charrep() << "' failed!" LOG_
				}
			}
		} else {
			_LOG << "Error: Query '" << query->charrep() << "' failed!" LOG_
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Formulars* forms) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select id, name, menuname, eventname, menuhilfe, anwendungid, typ from formulare") != ERR_NONE) {
		_LOG << "Error: Access to formular table failed. Read formulars would be skipped." LOG_
		return;
	}
	
	err = q->first(); 

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No formulars found. All formulars may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Long, AnwendungID)
		UAP(lb_I_Long, Typ)
		UAP(lb_I_String, FormularName)
		UAP(lb_I_String, MenuName)
		UAP(lb_I_String, MenuHilfe)
		UAP(lb_I_String, EventName)

		FormularID = q->getAsLong(1);
		FormularName = q->getAsString(2);
		MenuName = q->getAsString(3);
		EventName = q->getAsString(4);		
		MenuHilfe = q->getAsString(5);
		AnwendungID = q->getAsLong(6);
		Typ = q->getAsLong(7);
		
		forms->addFormular(FormularName->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			FormularID = q->getAsLong(1);
			FormularName = q->getAsString(2);
			MenuName = q->getAsString(3);
			EventName = q->getAsString(4);		
			MenuHilfe = q->getAsString(5);
			AnwendungID = q->getAsLong(6);
			Typ = q->getAsLong(7);
			
			forms->addFormular(FormularName->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Column_Types* columntypes) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();
	
	if (q->query("select tablename, name, specialcolumn, controltype, ro from column_types") != ERR_NONE) {
		_LOG << "Error: Access to column types table failed. Read column types would be skipped." LOG_
		return;
	}
	
	err = q->first(); 

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No column types found. All column types may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, Readonly)
		UAP(lb_I_String, TableName)
		UAP(lb_I_String, Name)
		UAP(lb_I_String, SpecialColumn)
		UAP(lb_I_String, ControlType)

		TableName = q->getAsString(1);
		Name = q->getAsString(2);
		SpecialColumn = q->getAsString(3);
		ControlType = q->getAsString(4);		
		Readonly = q->getAsLong(5);
		
		columntypes->addType(TableName->charrep(), Name->charrep(), SpecialColumn->charrep(), ControlType->charrep(), (Readonly->getData() == (long) 1) ? true : false);

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			TableName = q->getAsString(1);
			Name = q->getAsString(2);
			SpecialColumn = q->getAsString(3);
			ControlType = q->getAsString(4);		
			Readonly = q->getAsLong(5);
		
			columntypes->addType(TableName->charrep(), Name->charrep(), SpecialColumn->charrep(), ControlType->charrep(), (Readonly->getData() == (long) 1) ? true : false);
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Applications* applications) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();

	if (q->query("select id, Name, Titel, ModuleName, Functor, Interface from Anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read applications would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No applications found. All applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_String, qName)
		UAP(lb_I_String, qTitel)
		UAP(lb_I_String, qModuleName)
		UAP(lb_I_String, qFunctor)
		UAP(lb_I_String, qInterface)
		
		qID = q->getAsLong(1);
		qName = q->getAsString(2);
		qTitel = q->getAsString(3);
		qModuleName = q->getAsString(4);
		qFunctor = q->getAsString(5);
		qInterface = q->getAsString(6);
		
		applications->addApplication(qName->charrep(), qTitel->charrep(), qModuleName->charrep(), qFunctor->charrep(), qInterface->charrep(), qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qName = q->getAsString(2);
			qTitel = q->getAsString(3);
			qModuleName = q->getAsString(4);
			qFunctor = q->getAsString(5);
			qInterface = q->getAsString(6);
		
			applications->addApplication(qName->charrep(), qTitel->charrep(), qModuleName->charrep(), qFunctor->charrep(), qInterface->charrep(), qID->getData());
		}

	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_User_Applications* user_applications) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)
	
	q = db->getQuery(0);
	
	q->skipFKCollecting();

	if (q->query("select id, userid, anwendungenid from user_anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read applications would be skipped." LOG_
		return;
	}
	
	err = q->first(); 
	
	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No applications found. All applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)
		UAP(lb_I_Long, qUserID)
		UAP(lb_I_Long, qAppID)
		
		qID = q->getAsLong(1);
		qUserID = q->getAsLong(2);
		qAppID = q->getAsLong(3);
		
		user_applications->addRelation(qAppID->getData(), qUserID->getData(), qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {
			qID = q->getAsLong(1);
			qUserID = q->getAsLong(2);
			qAppID = q->getAsLong(3);
		
			user_applications->addRelation(qAppID->getData(), qUserID->getData(), qID->getData());
		}

	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_MetaApplication* app) {
	_CL_VERBOSE << "lbDatabaseInputStream::visit(): Read data of meta application." LOG_

	char* temp = NULL;
	bool  b;
	int   count = 0;
	lbErrCodes err = ERR_NONE;
	
/* // No local settings in the database...	
	*iStream >> b;
	app->setAutorefreshData(b);
	
	*iStream >> temp;
	app->setApplicationName(temp);
	
	*iStream >> temp;
	app->setUserName(temp);

	*iStream >> b;
	app->setAutoload(b);
	
	*iStream >> b;
	app->setAutoselect(b);

	*iStream >> b;
	app->setGUIMaximized(b);
*/

	// Number of users
	//*iStream >> count;
	
	
	// Number of applications
	//*iStream >> count;
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Application*) {
	_CL_VERBOSE << "lbDatabaseInputStream::visit(): Read data of application." LOG_
}

void LB_STDCALL lbDatabaseInputStream::end() {

}
/*
lb_I_Stream* LB_STDCALL lbDatabaseInputStream::getStream() {
	lbErrCodes err = ERR_NONE;
	
        UAP(lb_I_Stream, s)
        QI(iStream, lb_I_Stream, s)
        s++;

        return s.getPtr();
}
*/
/*...e*/

/*...sclass lbPluginDatabaseInputStream implementation:0:*/
/*...slbPluginDatabaseInputStream:0:*/
class lbPluginDatabaseInputStream : public lb_I_PluginImpl {
public:
	lbPluginDatabaseInputStream();
	
	virtual ~lbPluginDatabaseInputStream();

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

private:
	UAP(lb_I_Unknown, impl)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabaseInputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabaseInputStream, lbPluginDatabaseInputStream)

/*...slbErrCodes LB_STDCALL lbPluginDatabaseInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDatabaseInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDatabaseInputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDatabaseInputStream::lbPluginDatabaseInputStream() {
	_CL_VERBOSE << "lbPluginDatabaseInputStream::lbPluginDatabaseInputStream() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDatabaseInputStream::~lbPluginDatabaseInputStream() {
	_CL_VERBOSE << "lbPluginDatabaseInputStream::~lbPluginDatabaseInputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginDatabaseInputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabaseInputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDatabaseInputStream::initialize() {
}
	
bool LB_STDCALL lbPluginDatabaseInputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseInputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseInputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbDatabaseInputStream* InputStream = new lbDatabaseInputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDatabaseInputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDatabaseInputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbDatabaseInputStream* InputStream = new lbDatabaseInputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDatabaseInputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/

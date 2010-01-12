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
#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

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
	void LB_STDCALL visit(lb_I_BinaryData*) { _CL_LOG << "visit(lb_I_BinaryData*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestMethod*) { _CL_LOG << "visit(lb_I_TestMethod*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestFixture*) { _CL_LOG << "visit(lb_I_TestFixture*)" LOG_ }
	void LB_STDCALL visit(lb_I_CryptoStream*) { _CL_LOG << "visit(lb_I_CryptoStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchInterceptor*) { _CL_LOG << "visit(lb_I_DispatchInterceptor*)" LOG_ }

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
	void LB_STDCALL visit(lb_I_DBPrimaryKeys*);
	void LB_STDCALL visit(lb_I_DBForeignKeys*);

	void LB_STDCALL visit(lb_I_DBReportTextblock*);
	void LB_STDCALL visit(lb_I_DBReportProperties*);
	void LB_STDCALL visit(lb_I_Reports*);
	void LB_STDCALL visit(lb_I_ReportParameters*);
	void LB_STDCALL visit(lb_I_ReportElements*);
	void LB_STDCALL visit(lb_I_ReportElementTypes*);
	void LB_STDCALL visit(lb_I_ReportTexts*);
	void LB_STDCALL visit(lb_I_Applications_Formulars*);
	void LB_STDCALL visit(lb_I_Action_Step_Transitions*);
	void LB_STDCALL visit(lb_I_ActionStep_Parameters*);
	void LB_STDCALL visit(lb_I_Action_Parameters*);

	bool LB_STDCALL begin(const char* connectionname, const char* DBName, const char* DBUser, const char* DBPass);
	bool LB_STDCALL begin(const char* connectionname, lb_I_Database* _db);
	void LB_STDCALL end();

//	lb_I_Stream* LB_STDCALL getStream();

	UAP(lb_I_Database, db)
	UAP(lb_I_String, ConnectionName)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbDatabaseInputStream)
	ADD_INTERFACE(lb_I_Aspect)
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

bool LB_STDCALL lbDatabaseInputStream::begin(const char* connectionname, const char* DBName, const char* DBUser, const char* DBPass) {
	REQUEST(manager.getPtr(), lb_I_Database, db)

	bool ret = true;

	if (ConnectionName == NULL) {
		REQUEST(getModuleInstance(), lb_I_String, ConnectionName)
	}

	*ConnectionName = connectionname;

	return ret;
}

bool LB_STDCALL lbDatabaseInputStream::begin(const char* connectionname, lb_I_Database* _db) {
	lbErrCodes err = ERR_NONE;
	if (_db != NULL) {
		QI(_db, lb_I_Database, db)
		bool ret = _db->isConnected();

		if (!ret) {
			_LOG << "lbDatabaseInputStream::begin(lb_I_Database* _db) Error: Must have a database connection." LOG_
		}

		if (ConnectionName == NULL) {
			REQUEST(getModuleInstance(), lb_I_String, ConnectionName)
		}

		*ConnectionName = connectionname;

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

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ActionStep_Parameters* actionstepparameters) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_ActionStep_Parameters* actionstepparameters) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);
	*query = "select id, action_step_id, name, value, interface, description from action_step_parameter";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
		UAP(lb_I_Long, ID)
		UAP(lb_I_Long, actionid)
		UAP(lb_I_String, name)
		UAP(lb_I_String, value)
		UAP(lb_I_String, _interface)
		UAP(lb_I_String, description)
		err = q->first();

		while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

			ID = q->getAsLong(1);
			actionid = q->getAsLong(2);
			name = q->getAsString(3);
			value = q->getAsString(4);
			_interface = q->getAsString(5);
			description = q->getAsString(6);

			actionstepparameters->addActionStepParameter(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), actionid->getData(), ID->getData());

			err = q->next();
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Action_Parameters* actionparameters) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_Action_Parameters* actionparameters) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, actionid, name, value, interface, description from action_parameters";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
		UAP(lb_I_Long, ID)
		UAP(lb_I_Long, actionid)
		UAP(lb_I_String, name)
		UAP(lb_I_String, value)
		UAP(lb_I_String, _interface)
		UAP(lb_I_String, description)
		err = q->first();

		while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

			ID = q->getAsLong(1);
			actionid = q->getAsLong(2);
			name = q->getAsString(3);
			value = q->getAsString(4);
			_interface = q->getAsString(5);
			description = q->getAsString(6);

			actionparameters->addActionParameter(description->charrep(), name->charrep(), value->charrep(), _interface->charrep(), actionid->getData(), ID->getData());

			err = q->next();
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Action_Step_Transitions* transitions) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_Action_Step_Transitions* transitions) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, src_actionid, dst_actionid, expression, description from action_step_transitions";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_Long, SrcActionID)
			UAP(lb_I_Long, DstActionID)
			UAP(lb_I_String, Decision)
			UAP(lb_I_String, Description)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

				ID = q->getAsLong(1);
				SrcActionID = q->getAsLong(2);
				DstActionID = q->getAsLong(3);
				Decision = q->getAsString(4);
				Description = q->getAsString(5);

				transitions->addTransition(Decision->charrep(), SrcActionID->getData(), DstActionID->getData(), Description->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Applications_Formulars* applicationformulars) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_Applications_Formulars* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, anwendungid, formularid from anwendungen_formulare";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_Long, ApplicationID)
			UAP(lb_I_Long, FormularID)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

				ID = q->getAsLong(1);
				ApplicationID = q->getAsLong(2);
				FormularID = q->getAsLong(3);

				applicationformulars->addRelation(ApplicationID->getData(), FormularID->getData(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Reports* reports) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_Reports* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, name, description from reports";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_String, Name)
			UAP(lb_I_String, Description)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {

				ID = q->getAsLong(1);
				Name = q->getAsString(2);
				Description = q->getAsString(3);

				reports->addReport(Name->charrep(), Description->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ReportParameters* reportparameters) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_ReportParameters* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, reportid, name, value from report_parameters";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_Long, ReportID)
			UAP(lb_I_String, Name)
			UAP(lb_I_String, Value)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				ID = q->getAsLong(1);
				ReportID = q->getAsLong(2);
				Name = q->getAsString(3);
				Value = q->getAsString(4);

				reportparameters->addParameter(ReportID->getData(), Name->charrep(), Value->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ReportElements* reportelements) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_ReportElements* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, reportid, typ, name, x, y, w, h, description from report_elements";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_Long, ReportID)
			UAP(lb_I_Long, Typ)
			UAP(lb_I_Long, X)
			UAP(lb_I_Long, Y)
			UAP(lb_I_Long, W)
			UAP(lb_I_Long, H)
			UAP(lb_I_String, Name)
			UAP(lb_I_String, Description)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				ID = q->getAsLong(1);
				ReportID = q->getAsLong(2);
				Typ = q->getAsLong(3);
				Name = q->getAsString(4);
				X = q->getAsLong(5);
				Y = q->getAsLong(6);
				W = q->getAsLong(7);
				H = q->getAsLong(8);
				Description = q->getAsString(9);

				reportelements->addElement(ReportID->getData(), Name->charrep(), Typ->getData(), X->getData(), Y->getData(), W->getData(), H->getData(), Description->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ReportElementTypes* reportelementtypes) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_ReportElementTypes* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, name, description from report_element_types";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_String, Name)
			UAP(lb_I_String, Description)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				ID = q->getAsLong(1);
				Name = q->getAsString(2);
				Description = q->getAsString(3);

				reportelementtypes->addElementType(Name->charrep(), Description->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_ReportTexts* textlines) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbDatabaseInputStream::visit(lb_I_ReportTexts* reports) called" LOG_
	UAP(lb_I_Query, q)
	UAP_REQUEST(getModuleInstance(), lb_I_String, query)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	*query = "select id, elementid, line, text from report_texts";

	err = q->query(query->charrep());

	if ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
			UAP(lb_I_Long, ID)
			UAP(lb_I_Long, ElementID)
			UAP(lb_I_Long, Line)
			UAP(lb_I_String, Text)
			err = q->first();

			while ((err == ERR_NONE) || (err == WARN_DB_NODATA)) {
				ID = q->getAsLong(1);
				ElementID = q->getAsLong(2);
				Line = q->getAsLong(3);
				Text = q->getAsString(4);

				textlines->addText(ElementID->getData(), Line->getData(), Text->charrep(), ID->getData());

				err = q->next();
			}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBReportTextblock*) {

}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBReportProperties*) {

}


void LB_STDCALL lbDatabaseInputStream::visit(lb_I_UserAccounts* users) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

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

/// \todo Improve speed by directly passing the container into the lbDMFDataModel classes.
void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBForeignKeys* fkeys) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	UAP(lb_I_Container, Tables)

	Tables = db->getForeignKeys(ConnectionName->charrep());

	long i = 0;

	UAP_REQUEST(getModuleInstance(), lb_I_String, currentPKTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentPKTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentPKTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentPKTableColumnName)

	UAP_REQUEST(getModuleInstance(), lb_I_String, currentFKTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentFKTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentFKTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentFKTableColumnName)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentKeySequence)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentUpdateRule)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentDeleteRule)

	while (Tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)

		uk = Tables->nextElement();
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

		fkeys->addForeignKey(	currentPKTableCatalog->charrep(), currentPKTableSchema->charrep(), currentPKTableName->charrep(), currentPKTableColumnName->charrep(),
								currentFKTableCatalog->charrep(), currentFKTableSchema->charrep(), currentFKTableName->charrep(), currentFKTableColumnName->charrep(),
								currentKeySequence->getData(), currentUpdateRule->getData(), currentDeleteRule->getData(), ++i);
	}
}

/// \todo Improve speed by directly passing the container into the lbDMFDataModel classes.
void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBPrimaryKeys* pkeys) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	UAP(lb_I_Container, Tables)

	Tables = db->getPrimaryKeys(ConnectionName->charrep());

	long i = 0;

	UAP_REQUEST(getModuleInstance(), lb_I_String, currentTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentColumnName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, currentColumnName_V2)

	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentID)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, currentKeySequence)

	while (Tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)

		uk = Tables->nextElement();
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

		pkeys->addPrimaryKey(	currentTableCatalog->charrep(), currentTableSchema->charrep(), currentTableName->charrep(), currentColumnName->charrep(),
								currentKeySequence->getData(), currentColumnName_V2->charrep(), ++i);
	}
}

/// \todo Improve speed by directly passing the container into the lbDMFDataModel classes.
void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBTables* tables) {
	lbErrCodes err = ERR_NONE;
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	UAP(lb_I_Container, Tables)

	// When using the optional parameter to let db fill the data directly into the model
	Tables = db->getTables(ConnectionName->charrep());

	long i = 0;

	UAP_REQUEST(getModuleInstance(), lb_I_String, szTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, szTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, szTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, szTableType)
	UAP_REQUEST(getModuleInstance(), lb_I_String, szTableRemarks)

	while (Tables->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Parameter, param)

		uk = Tables->nextElement();
		QI(uk, lb_I_Parameter, param)

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

/// \todo Improve speed by directly passing the container into the lbDMFDataModel classes.
void LB_STDCALL lbDatabaseInputStream::visit(lb_I_DBColumns* columns) {
	lbErrCodes err = ERR_NONE;

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)


	UAP_REQUEST(getModuleInstance(), lb_I_String, nameDatetimeSubtypeCode)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameTableCatalog)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameTableSchema)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameTableName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameColumnName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameDataType)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameBufferLength)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameDecimalDigits)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameNumPrecRadix)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameNullable)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameRemarks)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameColumnDefault)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameSQLDataType)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameCharOctetLength)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameOrdinalPosition)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameIsNullable)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameTypeName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, nameColumnSize)



	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}
	UAP(lb_I_Container, Pages)

	Pages = db->getColumns(ConnectionName->charrep());

	columns->addPagedConainer(*&Pages);

	return;
#ifdef bla
	long i = 0;

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
/*
	*nameDatetimeSubtypeCode = "DatetimeSubtypeCode";
	*nameTableCatalog = "TableCatalog";
	*nameTableSchema = "TableSchema";
	*nameTableName = "TableName";
	*nameColumnName = "ColumnName";
	*nameDataType = "DataType";
	*nameTypeName = "TypeName";
	*nameBufferLength = "BufferLength";
	*nameDecimalDigits = "DecimalDigits";
	*nameNumPrecRadix = "NumPrecRadix";
	*nameNullable = "Nullable";
	*nameRemarks = "Remarks";
	*nameColumnDefault = "ColumnDefault";
	*nameSQLDataType = "SQLDataType";
	*nameCharOctetLength = "CharOctetLength";
	*nameOrdinalPosition = "OrdinalPosition";
	*nameIsNullable = "IsNullable";
	*nameColumnSize = "ColumnSize";
*/

	*nameDatetimeSubtypeCode = "1";
	*nameTableCatalog = "2";
	*nameTableSchema = "3";
	*nameTableName = "4";
	*nameColumnName = "5";
	*nameDataType = "6";
	*nameTypeName = "7";
	*nameBufferLength = "8";
	*nameDecimalDigits = "9";
	*nameNumPrecRadix = "10";
	*nameNullable = "11";
	*nameRemarks = "12";
	*nameColumnDefault = "13";
	*nameSQLDataType = "14";
	*nameCharOctetLength = "15";
	*nameOrdinalPosition = "16";
	*nameIsNullable = "17";
	*nameColumnSize = "18";

	long columnsPortion = 0;
	long columnsImported = 0;

	// Outer loop over the pages.
	while (Pages->hasMoreElements() == 1) {
		UAP(lb_I_Unknown, uk)
			UAP(lb_I_Container, Columns)

			uk = Pages->nextElement();
		QI(uk, lb_I_Container, Columns)

			while (Columns->hasMoreElements() == 1) {
				UAP(lb_I_Unknown, uk)
					UAP(lb_I_Parameter, param)

					uk = Columns->nextElement();
				QI(uk, lb_I_Parameter, param)

					//		param->getUAPString(*&nameTableCatalog, *&szCatalog);
					//		param->getUAPString(*&nameTableSchema, *&szSchema);
					param->getUAPString(*&nameTableName, *&szTableName);
				param->getUAPString(*&nameColumnName, *&szColumnName);

				//		param->getUAPLong(*&nameDataType, *&DataType);
				param->getUAPString(*&nameTypeName, *&szTypeName);
				param->getUAPLong(*&nameColumnSize, *&ColumnSize);
				//		param->getUAPLong(*&nameBufferLength, *&BufferLength);
				//		param->getUAPLong(*&nameDecimalDigits, *&DecimalDigits);
				//		param->getUAPLong(*&nameNumPrecRadix, *&NumPrecRadix);
				//		param->getUAPLong(*&nameNullable, *&Nullable);
						param->getUAPString(*&nameRemarks, *&szRemarks);
				//		param->getUAPString(*&nameColumnDefault, *&szColumnDefault);
				//		param->getUAPLong(*&nameSQLDataType, *&SQLDataType);
				//		param->getUAPLong(*&nameDatetimeSubtypeCode, *&DatetimeSubtypeCode);
				//		param->getUAPLong(*&nameCharOctetLength, *&CharOctetLength);
				//		param->getUAPLong(*&nameOrdinalPosition, *&OrdinalPosition);
				//		param->getUAPString(*&nameIsNullable, *&szIsNullable);

				columnsPortion++;

				if (columnsPortion == 100) {
					UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
						UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
						columnsImported += columnsPortion;
					columnsPortion = 0;
					l->setData(columnsImported);

					*msg = "Copied ";
					*msg += l->charrep();
					*msg += " of columns into datamodel ...";

					meta->setStatusText("Info", msg->charrep());

				}


				columns->addColumn(szColumnName->charrep(), szColumnRemarks->charrep(), szTypeName->charrep(), ColumnSize->getData(), false, "", "", szTableName->charrep(), ++i);
			}
	}
#endif
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Translations* trans) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	char *_actionquery = "select \"id\", \"bezeichnung\", \"actionid\", \"a_order_nr\", \"type\", \"what\" from \"action_steps\"";

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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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
			_LOG << "Add application parameter: " << qN->charrep() << ", " << qV->charrep() << ", " <<  qAID->getData() << ", " <<  qID->getData() LOG_
			params->addParameter(qN->charrep(), qV->charrep(), qAID->getData(), qID->getData());
		}
	}
}

void LB_STDCALL lbDatabaseInputStream::visit(lb_I_Formular_Fields* formularfields) {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	UAP(lb_I_ApplicationParameter, appParams)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
    UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Parameter, document)
	UAP(lb_I_Unknown, uk)

	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")

	visit(*&appParams); // Do an additional load of application parameters. This avoids much code changes.

	uk = metaapp->getActiveDocument();

	if (uk == NULL) {
		_LOG << "Error: Expected an 'active document' here!" LOG_
		return;
	}

    QI(uk, lb_I_Parameter, document)


	/// \todo There is a problem when using Sqlite database wrapper and the cursor emulation.

	/*
	 * The where clause would propably replaced wrongly by the ID = 1 where clause.
	 */

	if (db == NULL) {
		_LOG << "FATAL: Database imput stream could not work without a database!" LOG_
		return;
	}

	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();
	// Get all formulars, even one is custom
	if (q->query("select id, anwendungid from formulare") != ERR_NONE) {
		_LOG << "Error: Access to formular table failed. Read formulars would be skipped." LOG_
		return;
	}

	err = q->first();

	while (err == ERR_NONE) {
		UAP(lb_I_Long, FormularID)
		UAP(lb_I_Long, AnwendungID)
		UAP(lb_I_Query, query_query)

		UAP_REQUEST(getModuleInstance(), lb_I_String, query)

		FormularID = q->getAsLong(1);
		AnwendungID = q->getAsLong(2);

		query_query = db->getQuery("lbDMF", 0);

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
				_LOG << "lbDatabaseInputStream::visit(lb_I_Formular_Fields* formularfields) Have query object for " << ConnectionName->charrep() << ": '" << formularquery->charrep() << "'" LOG_
/*
        UAP_REQUEST(getModuleInstance(), lb_I_String, tempformularquery)
        *tempformularquery = formularquery->charrep();
        char* t = tempformularquery->stristr(formularquery->charrep(), "WHERE");
        t[0] = 0;
        *formularquery = tempformularquery;
        *formularquery += " LIMIT 1";
*/

				UAP(lb_I_Database, customDB)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbname)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbuser)
				UAP_REQUEST(getModuleInstance(), lb_I_String, dbpass)

				*dbname = "";
				*dbuser = "";
				*dbpass = "";

				char* dbbackend = metaapp->getApplicationDatabaseBackend();
				char* sysdbbackend = metaapp->getSystemDatabaseBackend();
				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					_LOG << "Info: Have got any AppParams from document used for plugin database backend." LOG_
				} else {
					_LOG << "Info: Have got any AppParams from document used for built in database backend." LOG_
				}

				*dbname = appParams->getParameter("DBName", AnwendungID->getData());
				*dbuser = appParams->getParameter("DBUser", AnwendungID->getData());
				*dbpass = appParams->getParameter("DBPass", AnwendungID->getData());

				metaapp->setStatusText("Info", "Target database is application database ...");

				/************/

				if (strcmp(dbname->charrep(), "lbDMF") == 0) {
					// It is the system database
					if (sysdbbackend != NULL && strcmp(sysdbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, sysdbbackend, customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				} else {
					if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
						UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
						AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, customDB, "'database plugin'")
						_LOG << "Using plugin database backend for UML import operation..." LOG_
					} else {
						// Use built in
						REQUEST(getModuleInstance(), lb_I_Database, customDB)
						_LOG << "Using built in database backend for UML import operation..." LOG_
					}
				}



				if (customDB == NULL) {
					_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
					return;
				}

				customDB->init();
				/************/

				if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
					// It is the plugin that currently only supports local Sqlite
					if ((strcmp(dbname->charrep(), "") == 0) || (customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						metaapp->msgBox("Fatal", "No custom database available. Cannot read database model for custom application!");

						// A fallback to the old code, that may not produce a result.
						form_query = db->getQuery(ConnectionName->charrep(), 0);
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0); // Use retrieved database name
					}
				} else {
					if ((customDB != NULL) && (customDB->connect(dbname->charrep(), dbname->charrep(), dbuser->charrep(), dbpass->charrep()) != ERR_NONE)) {
						_LOG << "Fatal: No custom database available. Cannot read database model for custom application!" LOG_
						/// \todo Implement fallback to Sqlite3.
						metaapp->msgBox("Fatal", "No custom database available. Cannot read database model for custom application!");

						// A fallback to the old code, that may not produce a result.
						form_query = db->getQuery(ConnectionName->charrep(), 0);
					} else {
						form_query = customDB->getQuery(dbname->charrep(), 0);
					}
				}


				form_query->enableFKCollecting();
				_LOG << "Execute query '" << formularquery->charrep() << "'" LOG_
				lbErrCodes errQuery = form_query->query(formularquery->charrep());
				_LOG << "Done executing query '" << formularquery->charrep() << "'" LOG_

				if ((errQuery == ERR_NONE) || (errQuery == ERR_DB_NODATA)) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						UAP(lb_I_String, name)
						UAP(lb_I_String, tablename)

						name = form_query->getColumnName(i);
						tablename = form_query->getTableName(name->charrep());

						_LOG << "Check if column " << name->charrep() << " from " << tablename->charrep() << " is a foreign column..." LOG_

						if (form_query->hasFKColumn(name->charrep()) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery("lbDMF", 0);

							_LOG << "Yes, is foreign column." LOG_

							t = form_query->getPKTable(name->charrep());
							c = form_query->getPKColumn(name->charrep());

							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;

							UAP(lb_I_String, T)

							T = form_query->getTableName(name->charrep());

							sprintf(buffer, "select pkname, pktable	from foreignkey_visibledata_mapping "
									"where fkname = '%s' and fktable = '%s'", name->charrep(), T->charrep());

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
											formularfields->addField(name->charrep(), tablename->charrep(), "Bit", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Float", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											formularfields->addField(name->charrep(), tablename->charrep(),  "String", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Binary", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Integer", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								} else {
									_LOG << "Yes, is foreign column, but no mapping defined." LOG_

									lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);

									switch (coltype) {
										case lb_I_Query::lbDBColumnBit:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Bit", false, "", "", FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Float", false, "", "", FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											formularfields->addField(name->charrep(), tablename->charrep(),  "String", false, "", "", FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Binary", false, "", "", FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											formularfields->addField(name->charrep(), tablename->charrep(),  "Integer", false, "", "", FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							_LOG << "No, is not foreign column." LOG_

							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									formularfields->addField(name->charrep(), tablename->charrep(),  "Bit", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									formularfields->addField(name->charrep(), tablename->charrep(),  "Float", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									formularfields->addField(name->charrep(), tablename->charrep(),  "String", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									formularfields->addField(name->charrep(), tablename->charrep(),  "Binary", false, "", "", FormularID->getData());
									break;

								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									formularfields->addField(name->charrep(), tablename->charrep(),  "Integer", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
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

		query_query = db->getQuery("lbDMF", 0);

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
				_LOG << "lbDatabaseInputStream::visit(lb_I_Formular_Fields* formularfields) Have query object for " << ConnectionName->charrep() << ": '" << formularquery->charrep() << "'" LOG_
				form_query = db->getQuery(ConnectionName->charrep(), 0);

				form_query->enableFKCollecting();

				lbErrCodes errQuery = form_query->query(formularquery->charrep());

				// The second case will never happen unless the query implementation will return WARN_DB_NODATA and query_query results into no data.
				// There is always a case of no data in the application tables, but there should always meta data available except the SQL of that query is wrong.
				if ((errQuery == ERR_NONE) || (errQuery == ERR_DB_NODATA)) {
					// formular query is valid
					int columns = form_query->getColumns();
					for (int i = 1; i <= columns; i++) {
						UAP(lb_I_String, name)
						UAP(lb_I_String, tablename)

						name = form_query->getColumnName(i);
						tablename = form_query->getTableName(name->charrep());

						_LOG << "Check if column " << name->charrep() << " from " << tablename->charrep() << " is a foreign column..." LOG_

						if (form_query->hasFKColumn(name->charrep()) == 1) {
							UAP(lb_I_String, t)
							UAP(lb_I_String, c)
							UAP(lb_I_Query, fkpkmapping_query)
							fkpkmapping_query = db->getQuery("lbDMF", 0);

							_LOG << "Yes, is foreign column." LOG_

							t = form_query->getPKTable(name->charrep());
							c = form_query->getPKColumn(name->charrep());

							char* buffer = (char*) malloc(1000);
							buffer[0] = 0;

							sprintf(buffer, "select pkname, pktable	from foreignkey_visibledata_mapping "
									"where fkname = '%s' and fktable = '%s'", name->charrep(), form_query->getTableName(name->charrep()));

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
											formularfields->addField(name->charrep(), tablename->charrep(), "Bit", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnFloat:
											formularfields->addField(name->charrep(), tablename->charrep(), "Float", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnChar:
											formularfields->addField(name->charrep(), tablename->charrep(), "String", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnBinary:
											formularfields->addField(name->charrep(), tablename->charrep(), "Binary", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;

										case lb_I_Query::lbDBColumnBigInteger:
										case lb_I_Query::lbDBColumnInteger:
											formularfields->addField(name->charrep(), tablename->charrep(), "Integer", true, PKName->charrep(), PKTable->charrep(), FormularID->getData());
											break;
										case lb_I_Query::lbDBColumnUnknown:
											_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
											break;
									}
								}
							}
						} else {
							lb_I_Query::lbDBColumnTypes coltype = form_query->getColumnType(i);
							_LOG << "No, is not foreign column." LOG_

							switch (coltype) {
								case lb_I_Query::lbDBColumnBit:
									formularfields->addField(name->charrep(), tablename->charrep(), "Bit", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnFloat:
									formularfields->addField(name->charrep(), tablename->charrep(), "Float", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnChar:
									formularfields->addField(name->charrep(), tablename->charrep(), "String", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnBinary:
									formularfields->addField(name->charrep(), tablename->charrep(), "Binary", false, "", "", FormularID->getData());
									break;

								case lb_I_Query::lbDBColumnBigInteger:
								case lb_I_Query::lbDBColumnInteger:
									formularfields->addField(name->charrep(), tablename->charrep(), "Integer", false, "", "", FormularID->getData());
									break;
								case lb_I_Query::lbDBColumnUnknown:
									_CL_LOG << "lbDatabasePanel::init(...) Creating control failed due to unknown column type" LOG_
									break;
							}
						}
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

	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select id, name, menuname, eventname, menuhilfe, anwendungid, typ, toolbarimage from formulare") != ERR_NONE) {
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
		UAP(lb_I_String, ToolbarImage)

		FormularID = q->getAsLong(1);
		FormularName = q->getAsString(2);
		MenuName = q->getAsString(3);
		EventName = q->getAsString(4);
		MenuHilfe = q->getAsString(5);
		AnwendungID = q->getAsLong(6);
		Typ = q->getAsLong(7);
		ToolbarImage = q->getAsString(8);

		forms->addFormular(FormularName->charrep(), ToolbarImage->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());

		while ((err = q->next()) == ERR_NONE || err == WARN_DB_NODATA) {
			FormularID = q->getAsLong(1);
			FormularName = q->getAsString(2);
			MenuName = q->getAsString(3);
			EventName = q->getAsString(4);
			MenuHilfe = q->getAsString(5);
			AnwendungID = q->getAsLong(6);
			Typ = q->getAsLong(7);
			ToolbarImage = q->getAsString(8);

			forms->addFormular(FormularName->charrep(), ToolbarImage->charrep(), MenuName->charrep(), EventName->charrep(), MenuHilfe->charrep(), AnwendungID->getData(), Typ->getData(), FormularID->getData());
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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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

	q = db->getQuery("lbDMF", 0);

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
	_LOG << "lbDatabaseInputStream::visit(): Read data of application." LOG_
	lbErrCodes err = ERR_NONE;

	// Get the document via the active document from meta application.
	// This way no extra interface is needed (container with named elements)

	UAP_REQUEST(manager.getPtr(), lb_I_MetaApplication, meta)
	UAP_REQUEST(manager.getPtr(), lb_I_String, param)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageInterface)
	UAP_REQUEST(manager.getPtr(), lb_I_String, StorageNamespace)

	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)

	ukDoc = meta->getActiveDocument();

	QI(ukDoc, lb_I_Parameter, document)

	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);

		// Get the plugin that is responsible to save the data.
		pl = PM->getFirstMatchingPlugin("lb_I_StandaloneStreamable", StorageNamespace->charrep());

		if (pl != NULL)	{
			ukPl = pl->getImplementation();
		} else {
			_LOG << "No 'lb_I_StandaloneStreamable' plugin with namespace '" << StorageNamespace->charrep() << "' available." LOG_
		}

		UAP(lb_I_StandaloneStreamable, mystream)

		if (ukPl != NULL) QI(ukPl, lb_I_StandaloneStreamable, mystream)

		if (mystream == NULL) {
			_LOG << "Error: Found a lb_I_StandaloneStreamable plugin via PM->getFirstMatchingPlugin(...), but QI failed." LOG_
		} else {
			//isFileAvailable = fOp->begin(filename->charrep());

			mystream->setOperator(this);
			mystream->load(*&db);
		}
	}
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

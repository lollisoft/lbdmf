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

/*...slbXMLOutputStream:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbXMLOutputStream : 
	public lb_I_FileOperation {
public:
	lbXMLOutputStream();
	virtual ~lbXMLOutputStream();
	
	DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*) { _CL_LOG << "visit(lb_I_String*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Integer*) { _CL_LOG << "visit(lb_I_Integer*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Long*) { _CL_LOG << "visit(lb_I_Long*)" LOG_ }
	void LB_STDCALL visit(lb_I_Container*) { _CL_LOG << "visit(lb_I_Container*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Database*) { _CL_LOG << "visit(lb_I_Database*)" LOG_ } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { _CL_LOG << "visit(lb_I_ColumnBinding*)" LOG_ } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { _CL_LOG << "visit(lb_I_BoundColumn*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Query*) { _CL_LOG << "visit(lb_I_Query*)" LOG_ } 
	void LB_STDCALL visit(lb_I_MVC_View*) { _CL_LOG << "visit(lb_I_MVC_View*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Connection*) { _CL_LOG << "visit(lb_I_Connection*)" LOG_ } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { _CL_LOG << "visit(lb_I_InterfaceRepository*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Element*) { _CL_LOG << "visit(lb_I_Element*)" LOG_ } 
	void LB_STDCALL visit(lb_I_Module*) { _CL_LOG << "visit(lb_I_Module*)" LOG_ } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { _CL_LOG << "visit(lb_I_FunctorEntity*)" LOG_ }
	void LB_STDCALL visit(lb_I_InstanceReference*) { _CL_LOG << "visit(lb_I_InstanceReference*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventHandler*) { _CL_LOG << "visit(lb_I_EventHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventManager*) { _CL_LOG << "visit(lb_I_EventManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_EventMapper*) { _CL_LOG << "visit(lb_I_EventMapper*)" LOG_ }
	void LB_STDCALL visit(lb_I_EvHandler*) { _CL_LOG << "visit(lb_I_EvHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_Dispatcher*) { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_LOG << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_LOG << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_LOG << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_LOG << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*) { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_LOG << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_LOG << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_LOG << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_LOG << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_LOG << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_LOG << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_LOG << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_LOG << "visit(lb_I_Window*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action*) { _CL_LOG << "visit(lb_I_Action*)" LOG_ }
	void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_LOG << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_LOG << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_LOG << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_LOG << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_LOG << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*) { _CL_LOG << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation* pm) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }
	void LB_STDCALL visit(lb_I_Socket*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer*) { _CL_LOG << "visit(lb_I_Transfer*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Transfer_Data*)" LOG_ }
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
	
	void LB_STDCALL visit(lb_I_Streamable* pm);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);
	void LB_STDCALL visit(lb_I_UserAccounts*);
	void LB_STDCALL visit(lb_I_Applications*);
	void LB_STDCALL visit(lb_I_User_Applications*);
	void LB_STDCALL visit(lb_I_Formulars*);
	void LB_STDCALL visit(lb_I_Formular_Fields*);
	void LB_STDCALL visit(lb_I_Column_Types*);
	void LB_STDCALL visit(lb_I_ApplicationParameter*);
	void LB_STDCALL visit(lb_I_FormularParameter*);
	void LB_STDCALL visit(lb_I_Actions*);
	void LB_STDCALL visit(lb_I_Formular_Actions*);
	void LB_STDCALL visit(lb_I_Action_Types*);
	void LB_STDCALL visit(lb_I_Action_Steps*);
	void LB_STDCALL visit(lb_I_Translations*);
	void LB_STDCALL visit(lb_I_FileLocation*);
	void LB_STDCALL visit(lb_I_DirLocation*);
	void LB_STDCALL visit(lb_I_DBColumns*);
	void LB_STDCALL visit(lb_I_DBTables*);
	void LB_STDCALL visit(lb_I_DBPrimaryKeys*);
	void LB_STDCALL visit(lb_I_DBForeignKeys*);
	
	/** \brief Start save operation.
	 *
	 * This initializes an input file stream with a given name.
	 * For each object, you will save, call their accept() member function.
	 */
	bool LB_STDCALL begin(char* file);

	bool LB_STDCALL begin(lb_I_Stream* stream);

	
	/** \brief End save operation.
	 *
	 * This closes the file and thus disables visit members.
	 */
	void LB_STDCALL end();
		
	lb_I_Stream* LB_STDCALL getStream();
	
	UAP(lb_I_OutputStream, oStream)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbXMLOutputStream)
	ADD_INTERFACE(lb_I_Aspect)
	ADD_INTERFACE(lb_I_FileOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbXMLOutputStream, lbXMLOutputStream)

/*...slbErrCodes LB_STDCALL lbXMLOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbXMLOutputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbXMLOutputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbXMLOutputStream\58\\58\lbXMLOutputStream\40\\41\:0:*/
lbXMLOutputStream::lbXMLOutputStream() 
{
	_CL_LOG << "lbXMLOutputStream::lbXMLOutputStream() called." LOG_
	ref = STARTREF;
}
/*...e*/
/*...slbXMLOutputStream\58\\58\\126\lbXMLOutputStream\40\\41\:0:*/
lbXMLOutputStream::~lbXMLOutputStream() {
	_CL_LOG << "lbXMLOutputStream::~lbXMLOutputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbXMLOutputStream::begin(char* file) {
	if (oStream == NULL) { 
		REQUEST(manager.getPtr(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(file);
		bool ret = oStream->open();

		oStream->setBinary();		

		if (!ret) {
			_CL_LOG << "lbXMLOutputStream::begin(" << file << ") Error: Open file failed." LOG_
		}

		return ret;
	} else {
		_CL_LOG << "Error: lbXMLOutputStream::begin(...) called prior!" LOG_
	}
	
	return false;
}

bool LB_STDCALL lbXMLOutputStream::begin(lb_I_Stream* stream) {
	lbErrCodes err = ERR_NONE;
	if (stream != NULL) {
		_CL_LOG << "lbXMLOutputStream::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
		QI(stream, lb_I_OutputStream, oStream)
		bool ret = oStream->open();

		if (!ret) {
			_CL_LOG << "lbXMLOutputStream::begin(lb_I_Stream* stream) Error: Open file failed." LOG_
		}
		
		return ret;
	} else {
		_CL_LOG << "lbXMLOutputStream::begin(lb_I_Stream* stream) Error: Uninitialized stream onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Streamable* pm) {
		_CL_LOG << "lbXMLOutputStream::visit(lb_I_Streamable* pm) Error: Private format. Could not generate XML for it !" LOG_
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_UserAccounts* users) {
	*oStream << "<users>" << "\n";
	
	users->finishUserIteration();
	
	while (users->hasMoreUsers()) {
		users->setNextUser();
		*oStream << "<user ID=\"" << users->getUserID() << "\" name=\"" << users->getUserName() << "\" password=\"" << users->getUserPassword() << "\"/>" << "\n";
	}

	*oStream << "</users>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Translations* trans) {
	*oStream << "<translations>" << "\n";

	trans->finishTranslationIteration();
	
	while (trans->hasMoreTranslations()) {
		trans->setNextTranslation();
		*oStream << 
		"<translation ID=\"" << trans->getTranslationID() << 
		"\" text=\"" << trans->getTranslationText() << 
		"\" translated=\"" << trans->getTranslationTranslated() << 
		"\" language=\"" << trans->getTranslationLanguage() << "\"/>" << "\n";
	}
	
	*oStream << "</translations>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_FormularParameter* forms) {
	*oStream << "<formularparameter>" << "\n";
	
	forms->finishParameterIteration();
	
	while (forms->hasMoreParameters()) {
		forms->setNextParameter();
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, Value)
		
		*Value = forms->getParameterValue();
		*Value = Value->replace("\"", "&quot;");
		
		*oStream << 
		"<parameter ID=\"" << forms->getParameterID() << 
		"\" name=\"" << forms->getParameterName() << 
		"\" value=\"" << Value->charrep() << 
		"\" formularid=\"" << forms->getFormularID() << "\"/>" << "\n";
	}

	*oStream << "</formularparameter>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_DBForeignKeys* fkeys) {
	*oStream << "<foreignkeys>" << "\n";
	
	fkeys->finishForeignKeyIteration();
	
	while (fkeys->hasMoreForeignKeys()) {
		fkeys->setNextForeignKey();
		
		*oStream << 
		"<foreignkey ID=\"" << fkeys->getForeignKeyID() << 
		"\" pkcatalog=\"" << fkeys->getForeignKeyPKTableCatalog() << 
		"\" pkschema=\"" << fkeys->getForeignKeyPKTableSchema() << 
		"\" pktable=\"" << fkeys->getForeignKeyPKTableName() << 
		"\" pkcolumn=\"" << fkeys->getForeignKeyPKTableColumnName() << 
		"\" fkcatalog=\"" << fkeys->getForeignKeyFKTableCatalog() << 
		"\" fkschema=\"" << fkeys->getForeignKeyFKTableSchema() << 
		"\" fktable=\"" << fkeys->getForeignKeyFKTableName() << 
		"\" fkcolumn=\"" << fkeys->getForeignKeyFKTableColumnName() << 
		"\" keysequence=\"" << fkeys->getForeignKeyKeySequence() << 
		"\" updaterule=\"" << fkeys->getForeignKeyUpdateRule() << 
		"\" deleterule=\"" << fkeys->getForeignKeyDeleteRule() << "\"/>" << "\n";
	}

	*oStream << "</foreignkeys>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_DBPrimaryKeys* pkeys) {
	*oStream << "<primarykeys>" << "\n";
	
	pkeys->finishPrimaryKeyIteration();
	
	while (pkeys->hasMorePrimaryKeys()) {
		pkeys->setNextPrimaryKey();
		
//		"\" pkcolumn_v2=\"" << pkeys->getPrimaryKeyColumnName_ODBC_V_2() << 

		*oStream << 
		"<primarykey ID=\"" << pkeys->getPrimaryKeyID() << 
		"\" pkcatalog=\"" << pkeys->getPrimaryKeyTableCatalog() << 
		"\" pkschema=\"" << pkeys->getPrimaryKeyTableSchema() << 
		"\" pktable=\"" << pkeys->getPrimaryKeyTableName() << 
		"\" pkcolumn=\"" << pkeys->getPrimaryKeyColumnName() << 
		"\" keysequence=\"" << pkeys->getPrimaryKeySequence() << 
		"\"/>\n";
	}

	*oStream << "</primarykeys>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_DBColumns* dbcolumns) {
	_LOG << "lbXMLOutputStream::visit(lb_I_DBColumns* dbcolumns) called" LOG_
	*oStream << "<dbcolumns>" << "\n";
	
	dbcolumns->finishColumnIteration();
	
	while (dbcolumns->hasMoreColumns()) {
		dbcolumns->setNextColumn();
		
		*oStream << 
		"<column tablename=\"" << dbcolumns->getColumnTableName() << 
		"\" name=\"" << dbcolumns->getColumnName() <<
		"\" typ=\"" << dbcolumns->getColumnTyp() <<
		"\" len=\"" << dbcolumns->getColumnLen() <<
		"\"/>" << "\n";
	}

	*oStream << "</dbcolumns>" << "\n";
	_LOG << "lbXMLOutputStream::visit(lb_I_DBColumns* dbcolumns) leaving" LOG_
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_DBTables* dbtable) {
	*oStream << "<dbtables" << " count=\"" << dbtable->getTableCount() << "\">" << "\n";
	
	dbtable->finishTableIteration();
	
	while (dbtable->hasMoreTables()) {
		dbtable->setNextTable();
		*oStream << 
		"<table ID=\"" << dbtable->getTableID() << 
		"\" name=\"" << dbtable->getTableName() << "\"/>" << "\n";
	}

	*oStream << "</dbtables>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Actions* actions) {
	*oStream << "<actions>" << "\n";
	
	actions->finishActionIteration();

	UAP_REQUEST(getModuleInstance(), lb_I_String, Name)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Source)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Typ)
	UAP_REQUEST(getModuleInstance(), lb_I_String, Target)
	
	while (actions->hasMoreActions()) {
		actions->setNextAction();
		
		*Name = actions->getActionName();
		
		*Name = Name->replace("\"", "&quot;");
		
		*oStream << 
		"<action ID=\"" << actions->getActionID() << 
		"\" name=\"" << Name->charrep() << 
		"\" source=\"" << actions->getActionSource() << 
		"\" typ=\"" << actions->getActionTyp() << 
		"\" target=\"" << actions->getActionTarget() << "\"/>" << "\n";
	}

	*oStream << "</actions>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Action_Steps* action_steps) {
	*oStream << "<actionsteps>" << "\n";
	
	action_steps->finishActionStepIteration();
	
	while (action_steps->hasMoreActionSteps()) {
		action_steps->setNextActionStep();
		*oStream << 
		"<action ID=\"" << action_steps->getActionStepID() << 
		"\" actionid=\"" << action_steps->getActionStepActionID() << 
		"\" substep=\"" << action_steps->getActionStepOrderNo() << 
		"\" steptyp=\"" << action_steps->getActionStepType() << 
		"\" stepname=\"" << action_steps->getActionStepBezeichnung() << 
		"\" what=\"" << action_steps->getActionStepWhat() << "\"/>" << "\n";
	}
	*oStream << "</actionsteps>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Action_Types* action_types) {
	*oStream << "<actiontypes>" << "\n";
	
	action_types->finishActionTypeIteration();
	
	while (action_types->hasMoreActionTypes()) {
		action_types->setNextActionType();
		*oStream << 
		"<type ID=\"" << action_types->getActionTypeID() << 
		"\" typename=\"" << action_types->getActionTypeBezeichnung() << 
		"\" handler=\"" << action_types->getActionTypeHandler() << 
		"\" module=\"" << action_types->getActionTypeModule() << "\"/>" << "\n";
	}
	*oStream << "</actiontypes>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Formular_Actions* formular_actions) {
	*oStream << "<formularactions>" << "\n";

	formular_actions->finishFormularActionIteration();
	
	while (formular_actions->hasMoreFormularActions()) {
		formular_actions->setNextFormularAction();
		*oStream << 
		"<action ID=\"" << formular_actions->getFormularActionID() << 
		"\" formularid=\"" << formular_actions->getFormularActionFormularID() << 
		"\" actionid=\"" << formular_actions->getFormularActionActionID() << 
		"\" event=\"" << formular_actions->getFormularActionEvent() << "\"/>" << "\n";
	}
	*oStream << "</formularactions>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_FileLocation* fileloc) {
	*oStream << "<filelocation loc=\"" << fileloc->charrep() << "\"/>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_DirLocation* fileloc) {
	*oStream << "<directorylocation loc=\"" << fileloc->charrep() << "\"/>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_ApplicationParameter* apps) {
	*oStream << "<applicationparameter>" << "\n";
	
	apps->finishParameterIteration();
	
	while (apps->hasMoreParameters()) {
		apps->setNextParameter();
		*oStream << 
		"<parameter ID=\"" << apps->getParameterID() << 
		"\" name=\"" << apps->getParameterName() << 
		"\" value=\"" << apps->getParameterValue() << 
		"\" applicationid=\"" << apps->getApplicationID() << "\"/>" << "\n";
	}
	*oStream << "</applicationparameter>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Formulars* forms) {
	*oStream << "<formulare>" << "\n";
	
	forms->finishFormularIteration();
	
	while (forms->hasMoreFormulars()) {
		forms->setNextFormular();
		*oStream << 
		"<formular ID=\"" << forms->getFormularID() << 
		"\" name=\"" << forms->getName() << 
		"\" menuname=\"" << forms->getMenuName() << 
		"\" eventname=\"" << forms->getEventName() << 
		"\" menuhelp=\"" << forms->getMenuHelp() << 
		"\" applicationid=\"" << forms->getApplicationID() <<
		"\" typid=\"" << forms->getTyp() << "\"/>" << "\n";
	}
	*oStream << "</formulare>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Formular_Fields* formularfields) {
	*oStream << "<formularfields>" << "\n";
	
	formularfields->finishFieldsIteration();
	
	while (formularfields->hasMoreFields()) {
		formularfields->setNextField();
		*oStream << 
		"<formular ID=\"" << formularfields->getID() << 
		"\" name=\"" << formularfields->getName() << 
		"\" tablename=\"" << formularfields->getTableName() << 
		"\" dbtype=\"" << formularfields->getDBType();
		
		if (formularfields->isFK())
			*oStream << "\" isfk=\"" << "1"; 
		else
			*oStream << "\" isfk=\"" << "0";
			 
		*oStream << "\" fkname=\"" << formularfields->getFKName() << 
		"\" fktable=\"" << formularfields->getFKTable() << 
		"\" formularid=\"" << formularfields->getFormularID() << "\"/>" << "\n";
	}
	*oStream << "</formularfields>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Column_Types* columntypes) {
	*oStream << "<columntypes>" << "\n";
	
	columntypes->finishTypeIteration();
	
	while (columntypes->hasMoreTypes()) {
		columntypes->setNextType();
		*oStream << 
		"<columntype tablename=\"" << columntypes->getTableName() << 
		"\" name=\"" << columntypes->getName() << 
		"\" specialcolumn=\"" << columntypes->getSpecialColumn() << 
		"\" controltype=\"" << columntypes->getControlType();
		if (columntypes->getReadonly() == true)
			*oStream << "\" readonly=\"" << "1" << "\"/>" << "\n";
		else
			*oStream << "\" readonly=\"" << "0" << "\"/>" << "\n";
	}
	*oStream << "</columntypes>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Applications* app) {
	*oStream << "<applications>" << "\n";
	
	app->finishApplicationIteration();
	
	while (app->hasMoreApplications()) {
		app->setNextApplication();
		*oStream << 
		"<application ID=\"" << app->getApplicationID() << 
		"\" name=\"" << app->getApplicationName() << 
		"\" title=\"" << app->getApplicationTitle() << 
		"\" module=\"" << app->getApplicationModule() << 
		"\" functor=\"" << app->getApplicationFunctor() << 
		"\" interface=\"" << app->getApplicationInterface() << "\"/>" << "\n";
	}
	*oStream << "</applications>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_User_Applications* app) {
	*oStream << "<usersapplications>" << "\n";
	
	app->finishRelationIteration();
	
	while (app->hasMoreRelations()) {
		app->setNextRelation();
		*oStream << 
		"<assignment ID=\"" << app->getID() << 
		"\" userid=\"" << app->getUserID() << 
		"\" applicationid=\"" << app->getApplicationID() << "\"/>" << "\n";
	}
	*oStream << "</usersapplications>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_MetaApplication* app) {
	*oStream << "<metaapplication>" << "\n";

	UAP_REQUEST(manager.getPtr(), lb_I_String, temp)
	bool  b;
	int count;

	*oStream << "<autorefreshdata setting=\"" << app->getAutorefreshData() << "\"/>" << "\n";

	app->getApplicationName(&temp);
	*oStream << "<applicationname name=\"" << temp->charrep() << "\"/>" << "\n";

	app->getUserName(&temp);
	*oStream << "<username name=\"" << temp->charrep() << "\"/>" << "\n";

	*oStream << "<autoload value=\"" << app->getAutoload() << "\"/>" << "\n";

	*oStream << "<autoselect value=\"" << app->getAutoselect() << "\"/>" << "\n";

	*oStream << "<guimaximized value=\"" << app->getGUIMaximized() << "\"/>" << "\n";
	
	*oStream << "<dirlocation value=\"" << app->getDirLocation() << "\"/>" << "\n";

	*oStream << "</metaapplication>" << "\n";
}

void LB_STDCALL lbXMLOutputStream::visit(lb_I_Application*) {
	_LOG << "Save a lb_I_Application object." LOG_
	
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
			mystream->save(*&oStream);
		}
	}
	_LOG << "Saved a lb_I_Application object." LOG_
}

void LB_STDCALL lbXMLOutputStream::end() {
	if (oStream == NULL) {
		_CL_LOG << "lbXMLOutputStream::end() Error: Not opened." LOG_
	}
	
	oStream->close();
}

lb_I_Stream* LB_STDCALL lbXMLOutputStream::getStream() {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Stream, s)
	QI(oStream, lb_I_Stream, s)
	s++;
	
	return s.getPtr();
}
/*...e*/

/*...sclass lbPluginXMLOutputStream implementation:0:*/
/*...slbPluginXMLOutputStream:0:*/
class lbPluginXMLOutputStream : public lb_I_PluginImpl {
public:
	lbPluginXMLOutputStream();
	
	virtual ~lbPluginXMLOutputStream();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginXMLOutputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginXMLOutputStream, lbPluginXMLOutputStream)

/*...slbErrCodes LB_STDCALL lbPluginXMLOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginXMLOutputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginXMLOutputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginXMLOutputStream::lbPluginXMLOutputStream() {
	_CL_VERBOSE << "lbPluginXMLOutputStream::lbPluginXMLOutputStream() called.\n" LOG_
	ref = STARTREF;
}

lbPluginXMLOutputStream::~lbPluginXMLOutputStream() {
	_CL_VERBOSE << "lbPluginXMLOutputStream::~lbPluginXMLOutputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginXMLOutputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginXMLOutputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginXMLOutputStream::initialize() {
}
	
bool LB_STDCALL lbPluginXMLOutputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginXMLOutputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginXMLOutputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbXMLOutputStream* InputStream = new lbXMLOutputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginXMLOutputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginXMLOutputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbXMLOutputStream* InputStream = new lbXMLOutputStream();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginXMLOutputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/

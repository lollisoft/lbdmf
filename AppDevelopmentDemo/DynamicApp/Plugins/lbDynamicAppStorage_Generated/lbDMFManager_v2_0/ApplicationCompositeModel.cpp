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

#include <lbInterfaces-sub-security.h>
#include <lbInterfaces-lbDMFManager.h>
#include <ApplicationCompositeModel.h>

// Includes for the libxml / libxslt libraries

#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#ifndef __WATCOMC_ 
extern int xmlLoadExtDtdDefaultValue;
#endif
#ifdef __WATCOMC__

// Map the orginal API functions to my versions as exported under Windows

#define xsltSaveResultToString lb_xsltSaveResultToString
#define xsltParseStylesheetDoc lb_xsltParseStylesheetDoc
#define xsltApplyStylesheet lb_xsltApplyStylesheet
#define xsltFreeStylesheet lb_xsltFreeStylesheet
#define xmlSubstituteEntitiesDefault lb_xmlSubstituteEntitiesDefault
#define xmlFreeDoc lb_xmlFreeDoc
#define xsltCleanupGlobals lb_xsltCleanupGlobals
#define xmlCleanupParser lb_xmlCleanupParser
#define xmlReadMemory lb_xmlReadMemory
#endif


IMPLEMENT_FUNCTOR(instanceOflbDynamicAppXMLStorage, lbDynamicAppXMLStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppXMLStorage)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppXMLStorage::lbDynamicAppXMLStorage() {
	

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


	UAP(lb_I_Actions, Actions)

	UAP(lb_I_Action_Steps, Action_Steps)

	UAP(lb_I_UserAccounts, UserAccounts)

	UAP(lb_I_Formulars, Formulars)

	UAP(lb_I_FormularParameter, FormularParameter)

	UAP(lb_I_User_Applications, User_Applications)

	UAP(lb_I_Applications_Formulars, Applications_Formulars)

	UAP(lb_I_Applications, Applications)

	UAP(lb_I_Translations, Translations)

	UAP(lb_I_Formular_Actions, Formular_Actions)

	UAP(lb_I_ApplicationParameter, ApplicationParameter)

	UAP(lb_I_Reports, Reports)

	UAP(lb_I_ReportParameters, ReportParameters)

	UAP(lb_I_ReportElements, ReportElements)

	UAP(lb_I_ReportElementTypes, ReportElementTypes)

	UAP(lb_I_ReportTexts, ReportTexts)

	UAP(lb_I_Formular_Fields, Formular_Fields)

	UAP(lb_I_Action_Step_Transitions, Action_Step_Transitions)

	UAP(lb_I_Column_Types, Column_Types)

	UAP(lb_I_FKPK_Mapping, FKPK_Mapping)

	UAP(lb_I_Action_Types, Action_Types)

	UAP(lb_I_Action_Parameters, Action_Parameters)

	UAP(lb_I_ActionStep_Parameters, ActionStep_Parameters)


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

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, activedocument)
	ukDoc = meta->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, activedocument)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)
	UAP_REQUEST(getModuleInstance(), lb_I_String, writeXMISettings)

	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)

	if (activedocument != NULL) {
		*param = "XSLFileExportSettings";
		activedocument->getUAPFileLocation(*&param, *&XSLFileExportSettings);
/*
		*param = "XSLFileSystemDatabase";
		activedocument->getUAPFileLocation(*&param, *&XSLFileSystemDatabase);
		*param = "XSLFileApplicationDatabase";
		activedocument->getUAPFileLocation(*&param, *&XSLFileApplicationDatabase);
 
		_LOG << "Have got the following files: " << XSLFileSystemDatabase->charrep() << " and " << XSLFileApplicationDatabase->charrep() LOG_		
 */
		*param = "UMLImportDBName";
		activedocument->getUAPString(*&param, *&DBName);
		*param = "UMLImportDBUser";
		activedocument->getUAPString(*&param, *&DBUser);
		*param = "UMLImportDBPass";
		activedocument->getUAPString(*&param, *&DBPass);

		*param = "overwriteDatabase";
		activedocument->getUAPString(*&param, *&overwrite);
		if (overwrite->charrep() == NULL) {
			_LOG << "Warning: The overwriteDatabase parameter was not passed. Set it to no." LOG_
			*overwrite = "no";
		}
		
		*param = "writeXMISettings";
		activedocument->getUAPString(*&param, *&writeXMISettings);
		if (writeXMISettings->charrep() == NULL) {
			_LOG << "Warning: The writeXMISettings parameter was not passed. Set it to no." LOG_
			*writeXMISettings = "no";
		}
	}
	
	// Write the settings file for the application database here ...
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileExportSettings->charrep() != NULL) {
			if (strcmp(XSLFileExportSettings->charrep(), "<settings>") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream->setFileName(XSLFileExportSettings->charrep());
				if (oStream->open()) {
					oStream->setBinary();
					*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"' '\"/>--><!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/>--><!-- Mapped to Sqlite (in XSLT document) -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/>-->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/>-->\n";
					*oStream << "<xsl:variable name=\"targetdatabase\" select=\"'" << meta->getApplicationDatabaseBackend() << "'\"/><!-- Mapped from Application Database backend in the properties window group General -->\n";
					*oStream << "<xsl:variable name=\"execute_droprules\" select=\"'" << overwrite->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"stream_output\" select=\"'no'\"/>\n"; // Writing out to uml would overwrite this here, because first this output must be created.
					
					DBName->replace(">", "&gt;");
					DBName->replace("<", "&lt;");
					DBUser->replace(">", "&gt;");
					DBUser->replace("<", "&lt;");
					DBPass->replace(">", "&gt;");
					DBPass->replace("<", "&lt;");
					
					*oStream << "<xsl:variable name=\"database_name\" select=\"'" << DBName->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_user\" select=\"'" << DBUser->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_pass\" select=\"'" << DBPass->charrep() << "'\"/>\n";
					
					/// \todo Write additional XMI settings here.				
					
					
					*oStream << "</xsl:stylesheet>\n";
					oStream->close();
				}
			}
		}
	}
	
	*param = "ApplicationData";
	document->setCloning(false);
	params->getUAPContainer(*&param, *&document);	

	// Get the application ID, that would be stored inside the XML document
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	*param = "SaveApplicationID";
	params->getUAPInteger(*&param, *&AppID);
	
	_LOG << "Application ID, that would be stored inside the XML document: " << AppID->charrep() LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)


	*name = "Actions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Actions, Actions)

	*name = "Action_Steps";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Steps, Action_Steps)

	*name = "UserAccounts";
	uk = document->getElement(&key);
	QI(uk, lb_I_UserAccounts, UserAccounts)

	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, Formulars)

	*name = "FormularParameter";
	uk = document->getElement(&key);
	QI(uk, lb_I_FormularParameter, FormularParameter)

	*name = "User_Applications";
	uk = document->getElement(&key);
	QI(uk, lb_I_User_Applications, User_Applications)

	*name = "Applications_Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications_Formulars, Applications_Formulars)

	*name = "Applications";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications, Applications)

	*name = "Translations";
	uk = document->getElement(&key);
	QI(uk, lb_I_Translations, Translations)

	*name = "Formular_Actions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Actions, Formular_Actions)

	*name = "ApplicationParameter";
	uk = document->getElement(&key);
	QI(uk, lb_I_ApplicationParameter, ApplicationParameter)

	*name = "Reports";
	uk = document->getElement(&key);
	QI(uk, lb_I_Reports, Reports)

	*name = "ReportParameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportParameters, ReportParameters)

	*name = "ReportElements";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElements, ReportElements)

	*name = "ReportElementTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElementTypes, ReportElementTypes)

	*name = "ReportTexts";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportTexts, ReportTexts)

	*name = "Formular_Fields";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Fields, Formular_Fields)

	*name = "Action_Step_Transitions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Step_Transitions, Action_Step_Transitions)

	*name = "Column_Types";
	uk = document->getElement(&key);
	QI(uk, lb_I_Column_Types, Column_Types)

	*name = "FKPK_Mapping";
	uk = document->getElement(&key);
	QI(uk, lb_I_FKPK_Mapping, FKPK_Mapping)

	*name = "Action_Types";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Types, Action_Types)

	*name = "Action_Parameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Parameters, Action_Parameters)

	*name = "ActionStep_Parameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_ActionStep_Parameters, ActionStep_Parameters)


	*name = "DBPrimaryKeys";
	uk = document->getElement(&key);
	if (uk == NULL) {
		_LOG << "Error: Document element " << name->charrep() << " is missing." LOG_
		//return ERR_DOCUMENTELEMENT_MISSING;
	}
	QI(uk, lb_I_DBPrimaryKeys, dbPrimaryKeys)
			
	*name = "DBForeignKeys";
	uk = document->getElement(&key);
	if (uk == NULL) {
		_LOG << "Error: Document element " << name->charrep() << " is missing." LOG_
		//return ERR_DOCUMENTELEMENT_MISSING;
	}
	QI(uk, lb_I_DBForeignKeys, dbForeignKeys)
			
	*name = "DBTables";
	uk = document->getElement(&key);
	if (uk == NULL) {
		_LOG << "Error: Document element " << name->charrep() << " is missing." LOG_
		//return ERR_DOCUMENTELEMENT_MISSING;
	}
	QI(uk, lb_I_DBTables, dbTables)
			
	*name = "DBColumns";
	uk = document->getElement(&key);
	if (uk == NULL) {
		_LOG << "Error: Document element " << name->charrep() << " is missing." LOG_
		//return ERR_DOCUMENTELEMENT_MISSING;
	}
	QI(uk, lb_I_DBColumns, dbColumns)

	// Mark that data sets, that are related to this application
	UAP(lb_I_SecurityProvider, securityManager)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	AQUIRE_PLUGIN(lb_I_SecurityProvider, Default, securityManager, "No security provider found.")
	UAP(lb_I_Unknown, apps)
	apps = securityManager->getApplicationModel();
	QI(apps, lb_I_Applications, Applications)
	
	meta->setStatusText("Info", "Write XML document ...");
	
	Applications->selectApplications(AppID->getData());
	Applications->mark();

	if (

		(Actions != NULL) &&

		(Action_Steps != NULL) &&

		(UserAccounts != NULL) &&

		(Formulars != NULL) &&

		(FormularParameter != NULL) &&

		(User_Applications != NULL) &&

		(Applications_Formulars != NULL) &&

		(Applications != NULL) &&

		(Translations != NULL) &&

		(Formular_Actions != NULL) &&

		(ApplicationParameter != NULL) &&

		(Reports != NULL) &&

		(ReportParameters != NULL) &&

		(ReportElements != NULL) &&

		(ReportElementTypes != NULL) &&

		(ReportTexts != NULL) &&

		(Formular_Fields != NULL) &&

		(Action_Step_Transitions != NULL) &&

		(Column_Types != NULL) &&

		(FKPK_Mapping != NULL) &&

		(Action_Types != NULL) &&

		(Action_Parameters != NULL) &&

		(ActionStep_Parameters != NULL) &&

	    (dbColumns != NULL) &&
	    (dbPrimaryKeys != NULL) &&
	    (dbForeignKeys != NULL) &&
	    (dbTables != NULL)
		) {

	
		*oStream << "<lbDMF applicationid=\"";

		// Save currently used database backend information. It could be used to determine what to to in the XSLT templates.
		// If exported, the information may be changed.
		
		char* dbbackend = meta->getSystemDatabaseBackend();

		*oStream << AppID->charrep() << "\" backend=\"" << dbbackend << 
#ifdef OSX		
		"\" platform=\"osx\">\n";
#else
#ifdef LINUX		
		"\" platform=\"linux\">\n";
#else		
#ifdef WINDOWS		
		"\" platform=\"windows\">\n";
#else		
#ifdef SOLARIS		
		"\" platform=\"solaris\">\n";
#endif		
#endif		
#endif		
#endif


		meta->setStatusText("Info", "Write XML document (Actions) ...");
		Actions->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Action_Steps) ...");
		Action_Steps->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (UserAccounts) ...");
		UserAccounts->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Formulars) ...");
		Formulars->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (FormularParameter) ...");
		FormularParameter->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (User_Applications) ...");
		User_Applications->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Applications_Formulars) ...");
		Applications_Formulars->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Applications) ...");
		Applications->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Translations) ...");
		Translations->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Formular_Actions) ...");
		Formular_Actions->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ApplicationParameter) ...");
		ApplicationParameter->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Reports) ...");
		Reports->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ReportParameters) ...");
		ReportParameters->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ReportElements) ...");
		ReportElements->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ReportElementTypes) ...");
		ReportElementTypes->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ReportTexts) ...");
		ReportTexts->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Formular_Fields) ...");
		Formular_Fields->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Action_Step_Transitions) ...");
		Action_Step_Transitions->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Column_Types) ...");
		Column_Types->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (FKPK_Mapping) ...");
		FKPK_Mapping->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Action_Types) ...");
		Action_Types->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (Action_Parameters) ...");
		Action_Parameters->accept(*&aspect);

		meta->setStatusText("Info", "Write XML document (ActionStep_Parameters) ...");
		ActionStep_Parameters->accept(*&aspect);


		meta->setStatusText("Info", "Write XML document (dbPrimaryKeys) ...");
		dbPrimaryKeys->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbForeignKeys) ...");
		dbForeignKeys->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbTables) ...");
		dbTables->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbColumns) ...");
		dbColumns->accept(*&aspect);

		*oStream << "</lbDMF>\n";
	}
	_LOG << "lbDynamicAppXMLStorage::save(lb_I_OutputStream* oStream) returns" LOG_

	meta->setStatusText("Info", "Done writing XML document ...");
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
	_LOG << "lbDynamicAppInternalStorage::load(lb_I_InputStream*) called." LOG_
	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	if (aspect == NULL) {
	    _LOG << "Error: aspect instance not available." LOG_
	}


	UAP(lb_I_Actions, Actions)

	UAP(lb_I_Action_Steps, Action_Steps)

	UAP(lb_I_UserAccounts, UserAccounts)

	UAP(lb_I_Formulars, Formulars)

	UAP(lb_I_FormularParameter, FormularParameter)

	UAP(lb_I_User_Applications, User_Applications)

	UAP(lb_I_Applications_Formulars, Applications_Formulars)

	UAP(lb_I_Applications, Applications)

	UAP(lb_I_Translations, Translations)

	UAP(lb_I_Formular_Actions, Formular_Actions)

	UAP(lb_I_ApplicationParameter, ApplicationParameter)

	UAP(lb_I_Reports, Reports)

	UAP(lb_I_ReportParameters, ReportParameters)

	UAP(lb_I_ReportElements, ReportElements)

	UAP(lb_I_ReportElementTypes, ReportElementTypes)

	UAP(lb_I_ReportTexts, ReportTexts)

	UAP(lb_I_Formular_Fields, Formular_Fields)

	UAP(lb_I_Action_Step_Transitions, Action_Step_Transitions)

	UAP(lb_I_Column_Types, Column_Types)

	UAP(lb_I_FKPK_Mapping, FKPK_Mapping)

	UAP(lb_I_Action_Types, Action_Types)

	UAP(lb_I_Action_Parameters, Action_Parameters)

	UAP(lb_I_ActionStep_Parameters, ActionStep_Parameters)

	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)



	AQUIRE_PLUGIN(lb_I_Actions, Model, Actions, "'Actions'")

	AQUIRE_PLUGIN(lb_I_Action_Steps, Model, Action_Steps, "'Action_Steps'")

	AQUIRE_PLUGIN(lb_I_UserAccounts, Model, UserAccounts, "'UserAccounts'")

	AQUIRE_PLUGIN(lb_I_Formulars, Model, Formulars, "'Formulars'")

	AQUIRE_PLUGIN(lb_I_FormularParameter, Model, FormularParameter, "'FormularParameter'")

	AQUIRE_PLUGIN(lb_I_User_Applications, Model, User_Applications, "'User_Applications'")

	AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, Applications_Formulars, "'Applications_Formulars'")

	AQUIRE_PLUGIN(lb_I_Applications, Model, Applications, "'Applications'")

	AQUIRE_PLUGIN(lb_I_Translations, Model, Translations, "'Translations'")

	AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, Formular_Actions, "'Formular_Actions'")

	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, ApplicationParameter, "'ApplicationParameter'")

	AQUIRE_PLUGIN(lb_I_Reports, Model, Reports, "'Reports'")

	AQUIRE_PLUGIN(lb_I_ReportParameters, Model, ReportParameters, "'ReportParameters'")

	AQUIRE_PLUGIN(lb_I_ReportElements, Model, ReportElements, "'ReportElements'")

	AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, ReportElementTypes, "'ReportElementTypes'")

	AQUIRE_PLUGIN(lb_I_ReportTexts, Model, ReportTexts, "'ReportTexts'")

	AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, Formular_Fields, "'Formular_Fields'")

	AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, Action_Step_Transitions, "'Action_Step_Transitions'")

	AQUIRE_PLUGIN(lb_I_Column_Types, Model, Column_Types, "'Column_Types'")

	AQUIRE_PLUGIN(lb_I_FKPK_Mapping, Model, FKPK_Mapping, "'FKPK_Mapping'")

	AQUIRE_PLUGIN(lb_I_Action_Types, Model, Action_Types, "'Action_Types'")

	AQUIRE_PLUGIN(lb_I_Action_Parameters, Model, Action_Parameters, "'Action_Parameters'")

	AQUIRE_PLUGIN(lb_I_ActionStep_Parameters, Model, ActionStep_Parameters, "'ActionStep_Parameters'")
Actions->accept(*&aspect);
Action_Steps->accept(*&aspect);
UserAccounts->accept(*&aspect);
Formulars->accept(*&aspect);
FormularParameter->accept(*&aspect);
User_Applications->accept(*&aspect);
Applications_Formulars->accept(*&aspect);
Applications->accept(*&aspect);
Translations->accept(*&aspect);
Formular_Actions->accept(*&aspect);
ApplicationParameter->accept(*&aspect);
Reports->accept(*&aspect);
ReportParameters->accept(*&aspect);
ReportElements->accept(*&aspect);
ReportElementTypes->accept(*&aspect);
ReportTexts->accept(*&aspect);
Formular_Fields->accept(*&aspect);
Action_Step_Transitions->accept(*&aspect);
Column_Types->accept(*&aspect);
FKPK_Mapping->accept(*&aspect);
Action_Types->accept(*&aspect);
Action_Parameters->accept(*&aspect);
ActionStep_Parameters->accept(*&aspect);


	// Read out application settings
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProjectExport)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	//UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

	UMLImportTargetDBName->accept(*&aspect);
	UMLImportTargetDBUser->accept(*&aspect);
	UMLImportTargetDBPass->accept(*&aspect);

	DatabaseSettingNamespace->accept(*&aspect);
	UsePlugin->accept(*&aspect);	
	XSLFileSystemDatabase->accept(*&aspect);
	XSLFileApplicationDatabase->accept(*&aspect);
	//UseOtherXSLFile->accept(*&aspect);
	XMIFileUMLProject->accept(*&aspect);
	XMIFileUMLProjectExport->accept(*&aspect);

	GeneralDBSchemaname->accept(*&aspect);
	XSLFileUMLExport->accept(*&aspect);
	XSLFileImportSettings->accept(*&aspect);
	XSLFileExportSettings->accept(*&aspect);
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	QI(name, lb_I_KeyBase, key)

	param->setCloning(false);
	document->setCloning(false);

	if (

		(Actions != NULL) && 

		(Action_Steps != NULL) && 

		(UserAccounts != NULL) && 

		(Formulars != NULL) && 

		(FormularParameter != NULL) && 

		(User_Applications != NULL) && 

		(Applications_Formulars != NULL) && 

		(Applications != NULL) && 

		(Translations != NULL) && 

		(Formular_Actions != NULL) && 

		(ApplicationParameter != NULL) && 

		(Reports != NULL) && 

		(ReportParameters != NULL) && 

		(ReportElements != NULL) && 

		(ReportElementTypes != NULL) && 

		(ReportTexts != NULL) && 

		(Formular_Fields != NULL) && 

		(Action_Step_Transitions != NULL) && 

		(Column_Types != NULL) && 

		(FKPK_Mapping != NULL) && 

		(Action_Types != NULL) && 

		(Action_Parameters != NULL) && 

		(ActionStep_Parameters != NULL) && 

		true) {
		
		UAP(lb_I_Unknown, uk)
		
		metaapp->setStatusText("Info", "Load internal file format ...");
		
		_LOG << "Get active document" LOG_
		

		UAP(lb_I_Unknown, ukParams)
		UAP(lb_I_Parameter, params)

		ukParams = metaapp->getActiveDocument();
		QI(ukParams, lb_I_Parameter, params)
		

		*name = "Actions";
		QI(Actions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Steps";
		QI(Action_Steps, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "UserAccounts";
		QI(UserAccounts, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formulars";
		QI(Formulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "FormularParameter";
		QI(FormularParameter, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "User_Applications";
		QI(User_Applications, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Applications_Formulars";
		QI(Applications_Formulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Applications";
		QI(Applications, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Translations";
		QI(Translations, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formular_Actions";
		QI(Formular_Actions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ApplicationParameter";
		QI(ApplicationParameter, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Reports";
		QI(Reports, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportParameters";
		QI(ReportParameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportElements";
		QI(ReportElements, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportElementTypes";
		QI(ReportElementTypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportTexts";
		QI(ReportTexts, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formular_Fields";
		QI(Formular_Fields, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Step_Transitions";
		QI(Action_Step_Transitions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Column_Types";
		QI(Column_Types, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "FKPK_Mapping";
		QI(FKPK_Mapping, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Types";
		QI(Action_Types, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Parameters";
		QI(Action_Parameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ActionStep_Parameters";
		QI(ActionStep_Parameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);


		*name = "UMLImportTargetDBName";
		QI(UMLImportTargetDBName, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "UMLImportTargetDBUser";
		QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "UMLImportTargetDBPass";
		QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "DatabaseSettingNamespace";
		QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "UsePlugin";
		QI(UsePlugin, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XSLFileSystemDatabase";
		QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XSLFileApplicationDatabase";
		QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XMIFileUMLProject";
		QI(XMIFileUMLProject, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XMIFileUMLProjectExport";
		QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		/*
		*name = "UseOtherXSLFile";
		QI(UseOtherXSLFile, lb_I_Unknown, uk)
		document->insert(&uk, &key);
*/		
		*name = "GeneralDBSchemaname";
		QI(GeneralDBSchemaname, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XSLFileUMLExport";
		QI(XSLFileUMLExport, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XSLFileImportSettings";
		QI(XSLFileImportSettings, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "XSLFileExportSettings";
		QI(XSLFileExportSettings, lb_I_Unknown, uk)
		document->insert(&uk, &key);
	}		
	
	*name = "ApplicationData";
	param->setUAPContainer(*&name, *&document);
	
	param++;
	metaapp->setActiveDocument(*&param);
	
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	_LOG << "lbDynamicAppInternalStorage::save(lb_I_OutputStream*) called." LOG_

	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	UAP(lb_I_Unknown, uk)


	UAP(lb_I_Actions, Actions)

	UAP(lb_I_Action_Steps, Action_Steps)

	UAP(lb_I_UserAccounts, UserAccounts)

	UAP(lb_I_Formulars, Formulars)

	UAP(lb_I_FormularParameter, FormularParameter)

	UAP(lb_I_User_Applications, User_Applications)

	UAP(lb_I_Applications_Formulars, Applications_Formulars)

	UAP(lb_I_Applications, Applications)

	UAP(lb_I_Translations, Translations)

	UAP(lb_I_Formular_Actions, Formular_Actions)

	UAP(lb_I_ApplicationParameter, ApplicationParameter)

	UAP(lb_I_Reports, Reports)

	UAP(lb_I_ReportParameters, ReportParameters)

	UAP(lb_I_ReportElements, ReportElements)

	UAP(lb_I_ReportElementTypes, ReportElementTypes)

	UAP(lb_I_ReportTexts, ReportTexts)

	UAP(lb_I_Formular_Fields, Formular_Fields)

	UAP(lb_I_Action_Step_Transitions, Action_Step_Transitions)

	UAP(lb_I_Column_Types, Column_Types)

	UAP(lb_I_FKPK_Mapping, FKPK_Mapping)

	UAP(lb_I_Action_Types, Action_Types)

	UAP(lb_I_Action_Parameters, Action_Parameters)

	UAP(lb_I_ActionStep_Parameters, ActionStep_Parameters)


	// Save application settings
	UAP(lb_I_String, UMLImportTargetDBName)
	UAP(lb_I_String, UMLImportTargetDBUser)
	UAP(lb_I_String, UMLImportTargetDBPass)
	UAP(lb_I_String, GeneralDBSchemaname)

	UAP(lb_I_FileLocation, XMIFileUMLProject)
	UAP(lb_I_FileLocation, XMIFileUMLProjectExport)
	UAP(lb_I_FileLocation, XSLFileImportSettings)
	UAP(lb_I_FileLocation, XSLFileExportSettings)
	UAP(lb_I_FileLocation, XSLFileUMLExport)
	UAP(lb_I_FileLocation, XSLFileSystemDatabase)
	UAP(lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP(lb_I_String, DatabaseSettingNamespace)

	UAP(lb_I_Boolean, UsePlugin)
	//UAP(lb_I_Boolean, UseOtherXSLFile)


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
			
			

	*name = "Actions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Actions, Actions)

	*name = "Action_Steps";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Steps, Action_Steps)

	*name = "UserAccounts";
	uk = document->getElement(&key);
	QI(uk, lb_I_UserAccounts, UserAccounts)

	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, Formulars)

	*name = "FormularParameter";
	uk = document->getElement(&key);
	QI(uk, lb_I_FormularParameter, FormularParameter)

	*name = "User_Applications";
	uk = document->getElement(&key);
	QI(uk, lb_I_User_Applications, User_Applications)

	*name = "Applications_Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications_Formulars, Applications_Formulars)

	*name = "Applications";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications, Applications)

	*name = "Translations";
	uk = document->getElement(&key);
	QI(uk, lb_I_Translations, Translations)

	*name = "Formular_Actions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Actions, Formular_Actions)

	*name = "ApplicationParameter";
	uk = document->getElement(&key);
	QI(uk, lb_I_ApplicationParameter, ApplicationParameter)

	*name = "Reports";
	uk = document->getElement(&key);
	QI(uk, lb_I_Reports, Reports)

	*name = "ReportParameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportParameters, ReportParameters)

	*name = "ReportElements";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElements, ReportElements)

	*name = "ReportElementTypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElementTypes, ReportElementTypes)

	*name = "ReportTexts";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportTexts, ReportTexts)

	*name = "Formular_Fields";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formular_Fields, Formular_Fields)

	*name = "Action_Step_Transitions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Step_Transitions, Action_Step_Transitions)

	*name = "Column_Types";
	uk = document->getElement(&key);
	QI(uk, lb_I_Column_Types, Column_Types)

	*name = "FKPK_Mapping";
	uk = document->getElement(&key);
	QI(uk, lb_I_FKPK_Mapping, FKPK_Mapping)

	*name = "Action_Types";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Types, Action_Types)

	*name = "Action_Parameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Parameters, Action_Parameters)

	*name = "ActionStep_Parameters";
	uk = document->getElement(&key);
	QI(uk, lb_I_ActionStep_Parameters, ActionStep_Parameters)


	// Store the settings from dynamic application
	*name = "UMLImportTargetDBName";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, UMLImportTargetDBName)
			
	*name = "UMLImportTargetDBUser";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, UMLImportTargetDBUser)
			
	*name = "UMLImportTargetDBPass";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, UMLImportTargetDBPass)
			
	*name = "XSLFileSystemDatabase";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XSLFileSystemDatabase)
			
	*name = "XSLFileApplicationDatabase";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XSLFileApplicationDatabase)
			
	*name = "DatabaseSettingNamespace";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, DatabaseSettingNamespace)

	*name = "UsePlugin";
	uk = document->getElement(&key);
	QI(uk, lb_I_Boolean, UsePlugin)
/*	
	*name = "UseOtherXSLFile";
	uk = document->getElement(&key);
	QI(uk, lb_I_Boolean, UseOtherXSLFile)
*/			
	*name = "XMIFileUMLProject";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XMIFileUMLProject)
	
	*name = "XMIFileUMLProjectExport";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XMIFileUMLProjectExport)
	
	*name = "GeneralDBSchemaname";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, GeneralDBSchemaname)
	
	*name = "XSLFileUMLExport";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XSLFileUMLExport)
	
	*name = "XSLFileImportSettings";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XSLFileImportSettings)
	
	*name = "XSLFileExportSettings";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XSLFileExportSettings)
	
				

	if (

		(Actions != NULL) &&

		(Action_Steps != NULL) &&

		(UserAccounts != NULL) &&

		(Formulars != NULL) &&

		(FormularParameter != NULL) &&

		(User_Applications != NULL) &&

		(Applications_Formulars != NULL) &&

		(Applications != NULL) &&

		(Translations != NULL) &&

		(Formular_Actions != NULL) &&

		(ApplicationParameter != NULL) &&

		(Reports != NULL) &&

		(ReportParameters != NULL) &&

		(ReportElements != NULL) &&

		(ReportElementTypes != NULL) &&

		(ReportTexts != NULL) &&

		(Formular_Fields != NULL) &&

		(Action_Step_Transitions != NULL) &&

		(Column_Types != NULL) &&

		(FKPK_Mapping != NULL) &&

		(Action_Types != NULL) &&

		(Action_Parameters != NULL) &&

		(ActionStep_Parameters != NULL) &&


		true) {

		_LOG << "Start storing the data" LOG_

Actions->accept(*&aspect);
Action_Steps->accept(*&aspect);
UserAccounts->accept(*&aspect);
Formulars->accept(*&aspect);
FormularParameter->accept(*&aspect);
User_Applications->accept(*&aspect);
Applications_Formulars->accept(*&aspect);
Applications->accept(*&aspect);
Translations->accept(*&aspect);
Formular_Actions->accept(*&aspect);
ApplicationParameter->accept(*&aspect);
Reports->accept(*&aspect);
ReportParameters->accept(*&aspect);
ReportElements->accept(*&aspect);
ReportElementTypes->accept(*&aspect);
ReportTexts->accept(*&aspect);
Formular_Fields->accept(*&aspect);
Action_Step_Transitions->accept(*&aspect);
Column_Types->accept(*&aspect);
FKPK_Mapping->accept(*&aspect);
Action_Types->accept(*&aspect);
Action_Parameters->accept(*&aspect);
ActionStep_Parameters->accept(*&aspect);


		UMLImportTargetDBName->accept(*&aspect);
		UMLImportTargetDBUser->accept(*&aspect);
		UMLImportTargetDBPass->accept(*&aspect);

		DatabaseSettingNamespace->accept(*&aspect);
		UsePlugin->accept(*&aspect);
		XSLFileSystemDatabase->accept(*&aspect);
		XSLFileApplicationDatabase->accept(*&aspect);
		//UseOtherXSLFile->accept(*&aspect);
		XMIFileUMLProject->accept(*&aspect);
		XMIFileUMLProjectExport->accept(*&aspect);
		GeneralDBSchemaname->accept(*&aspect);
		XSLFileUMLExport->accept(*&aspect);
		XSLFileImportSettings->accept(*&aspect);
		XSLFileExportSettings->accept(*&aspect);
		
		_LOG << "End storing the data" LOG_
	}

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::load(lb_I_Database* iDB) {
	_LOG << "lbDynamicAppInternalStorage::load(lb_I_Database*) called." LOG_
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)

	if (aspect == NULL) {
	    _LOG << "Error: aspect instance not available." LOG_
	}


	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)



	UAP(lb_I_Actions, Actions)

	UAP(lb_I_Action_Steps, Action_Steps)

	UAP(lb_I_UserAccounts, UserAccounts)

	UAP(lb_I_Formulars, Formulars)

	UAP(lb_I_FormularParameter, FormularParameter)

	UAP(lb_I_User_Applications, User_Applications)

	UAP(lb_I_Applications_Formulars, Applications_Formulars)

	UAP(lb_I_Applications, Applications)

	UAP(lb_I_Translations, Translations)

	UAP(lb_I_Formular_Actions, Formular_Actions)

	UAP(lb_I_ApplicationParameter, ApplicationParameter)

	UAP(lb_I_Reports, Reports)

	UAP(lb_I_ReportParameters, ReportParameters)

	UAP(lb_I_ReportElements, ReportElements)

	UAP(lb_I_ReportElementTypes, ReportElementTypes)

	UAP(lb_I_ReportTexts, ReportTexts)

	UAP(lb_I_Formular_Fields, Formular_Fields)

	UAP(lb_I_Action_Step_Transitions, Action_Step_Transitions)

	UAP(lb_I_Column_Types, Column_Types)

	UAP(lb_I_FKPK_Mapping, FKPK_Mapping)

	UAP(lb_I_Action_Types, Action_Types)

	UAP(lb_I_Action_Parameters, Action_Parameters)

	UAP(lb_I_ActionStep_Parameters, ActionStep_Parameters)


	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)

	AQUIRE_PLUGIN(lb_I_DBTables, Model, dbTables, "'database report'")
	AQUIRE_PLUGIN(lb_I_DBColumns, Model, dbColumns, "'database report'")
	AQUIRE_PLUGIN(lb_I_DBPrimaryKeys, Model, dbPrimaryKeys, "'database report'")
	AQUIRE_PLUGIN(lb_I_DBForeignKeys, Model, dbForeignKeys, "'database report'")


	AQUIRE_PLUGIN(lb_I_Actions, Model, Actions, "'Actions'")

	AQUIRE_PLUGIN(lb_I_Action_Steps, Model, Action_Steps, "'Action_Steps'")

	AQUIRE_PLUGIN(lb_I_UserAccounts, Model, UserAccounts, "'UserAccounts'")

	AQUIRE_PLUGIN(lb_I_Formulars, Model, Formulars, "'Formulars'")

	AQUIRE_PLUGIN(lb_I_FormularParameter, Model, FormularParameter, "'FormularParameter'")

	AQUIRE_PLUGIN(lb_I_User_Applications, Model, User_Applications, "'User_Applications'")

	AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, Applications_Formulars, "'Applications_Formulars'")

	AQUIRE_PLUGIN(lb_I_Applications, Model, Applications, "'Applications'")

	AQUIRE_PLUGIN(lb_I_Translations, Model, Translations, "'Translations'")

	AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, Formular_Actions, "'Formular_Actions'")

	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, ApplicationParameter, "'ApplicationParameter'")

	AQUIRE_PLUGIN(lb_I_Reports, Model, Reports, "'Reports'")

	AQUIRE_PLUGIN(lb_I_ReportParameters, Model, ReportParameters, "'ReportParameters'")

	AQUIRE_PLUGIN(lb_I_ReportElements, Model, ReportElements, "'ReportElements'")

	AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, ReportElementTypes, "'ReportElementTypes'")

	AQUIRE_PLUGIN(lb_I_ReportTexts, Model, ReportTexts, "'ReportTexts'")

	AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, Formular_Fields, "'Formular_Fields'")

	AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, Action_Step_Transitions, "'Action_Step_Transitions'")

	AQUIRE_PLUGIN(lb_I_Column_Types, Model, Column_Types, "'Column_Types'")

	AQUIRE_PLUGIN(lb_I_FKPK_Mapping, Model, FKPK_Mapping, "'FKPK_Mapping'")

	AQUIRE_PLUGIN(lb_I_Action_Types, Model, Action_Types, "'Action_Types'")

	AQUIRE_PLUGIN(lb_I_Action_Parameters, Model, Action_Parameters, "'Action_Parameters'")

	AQUIRE_PLUGIN(lb_I_ActionStep_Parameters, Model, ActionStep_Parameters, "'ActionStep_Parameters'")

	if (Actions == NULL)  {
		_LOG << "lb_I_Actions instance is NULL." LOG_
	}

	if (Action_Steps == NULL)  {
		_LOG << "lb_I_Action_Steps instance is NULL." LOG_
	}

	if (UserAccounts == NULL)  {
		_LOG << "lb_I_UserAccounts instance is NULL." LOG_
	}

	if (Formulars == NULL)  {
		_LOG << "lb_I_Formulars instance is NULL." LOG_
	}

	if (FormularParameter == NULL)  {
		_LOG << "lb_I_FormularParameter instance is NULL." LOG_
	}

	if (User_Applications == NULL)  {
		_LOG << "lb_I_User_Applications instance is NULL." LOG_
	}

	if (Applications_Formulars == NULL)  {
		_LOG << "lb_I_Applications_Formulars instance is NULL." LOG_
	}

	if (Applications == NULL)  {
		_LOG << "lb_I_Applications instance is NULL." LOG_
	}

	if (Translations == NULL)  {
		_LOG << "lb_I_Translations instance is NULL." LOG_
	}

	if (Formular_Actions == NULL)  {
		_LOG << "lb_I_Formular_Actions instance is NULL." LOG_
	}

	if (ApplicationParameter == NULL)  {
		_LOG << "lb_I_ApplicationParameter instance is NULL." LOG_
	}

	if (Reports == NULL)  {
		_LOG << "lb_I_Reports instance is NULL." LOG_
	}

	if (ReportParameters == NULL)  {
		_LOG << "lb_I_ReportParameters instance is NULL." LOG_
	}

	if (ReportElements == NULL)  {
		_LOG << "lb_I_ReportElements instance is NULL." LOG_
	}

	if (ReportElementTypes == NULL)  {
		_LOG << "lb_I_ReportElementTypes instance is NULL." LOG_
	}

	if (ReportTexts == NULL)  {
		_LOG << "lb_I_ReportTexts instance is NULL." LOG_
	}

	if (Formular_Fields == NULL)  {
		_LOG << "lb_I_Formular_Fields instance is NULL." LOG_
	}

	if (Action_Step_Transitions == NULL)  {
		_LOG << "lb_I_Action_Step_Transitions instance is NULL." LOG_
	}

	if (Column_Types == NULL)  {
		_LOG << "lb_I_Column_Types instance is NULL." LOG_
	}

	if (FKPK_Mapping == NULL)  {
		_LOG << "lb_I_FKPK_Mapping instance is NULL." LOG_
	}

	if (Action_Types == NULL)  {
		_LOG << "lb_I_Action_Types instance is NULL." LOG_
	}

	if (Action_Parameters == NULL)  {
		_LOG << "lb_I_Action_Parameters instance is NULL." LOG_
	}

	if (ActionStep_Parameters == NULL)  {
		_LOG << "lb_I_ActionStep_Parameters instance is NULL." LOG_
	}


	if (dbTables == NULL)  {
		_LOG << "lb_I_DBTables instance is NULL." LOG_
	}
	if (dbColumns == NULL)  {
		_LOG << "lb_I_DBColumns instance is NULL." LOG_
	}
	if (dbPrimaryKeys == NULL)  {
		_LOG << "lb_I_DBPrimaryKeys instance is NULL." LOG_
	}
	if (dbForeignKeys == NULL)  {
		_LOG << "lb_I_DBForeignKeys instance is NULL." LOG_
	}

	
	meta->setStatusText("Info", "Load database configuration (dbTables) ...");
	dbTables->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (dbColumns) ...");
	dbColumns->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (dbPrimaryKeys) ...");
	dbPrimaryKeys->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (dbForeignKeys) ...");
	dbForeignKeys->accept(*&aspect);


	meta->setStatusText("Info", "Load database configuration (Actions) ...");
	Actions->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Action_Steps) ...");
	Action_Steps->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (UserAccounts) ...");
	UserAccounts->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Formulars) ...");
	Formulars->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (FormularParameter) ...");
	FormularParameter->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (User_Applications) ...");
	User_Applications->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Applications_Formulars) ...");
	Applications_Formulars->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Applications) ...");
	Applications->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Translations) ...");
	Translations->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Formular_Actions) ...");
	Formular_Actions->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ApplicationParameter) ...");
	ApplicationParameter->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Reports) ...");
	Reports->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ReportParameters) ...");
	ReportParameters->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ReportElements) ...");
	ReportElements->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ReportElementTypes) ...");
	ReportElementTypes->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ReportTexts) ...");
	ReportTexts->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Formular_Fields) ...");
	Formular_Fields->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Action_Step_Transitions) ...");
	Action_Step_Transitions->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Column_Types) ...");
	Column_Types->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (FKPK_Mapping) ...");
	FKPK_Mapping->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Action_Types) ...");
	Action_Types->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (Action_Parameters) ...");
	Action_Parameters->accept(*&aspect);

	meta->setStatusText("Info", "Load database configuration (ActionStep_Parameters) ...");
	ActionStep_Parameters->accept(*&aspect);


	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP(lb_I_Unknown, ukDoc)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP(lb_I_Unknown, ukParams)
	UAP(lb_I_Parameter, params)

	ukParams = meta->getActiveDocument();
	QI(ukParams, lb_I_Parameter, params)

	_LOG << "Retrieve document container with name 'ApplicationData'" LOG_

	*name = "ApplicationData";
	params->setCloning(false);
	document->setCloning(false);


	// Need to read the new application settings from a good place
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProjectExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	//UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

	UAP(lb_I_Unknown, uk)
	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)

	UAP(lb_I_Parameter, SomeBaseSettings)
	
	SomeBaseSettings = meta->getPropertySet("DynamicAppDefaultSettings");

	if (SomeBaseSettings == NULL || SomeBaseSettings->Count() == 0) {
		// Firstly let them empty
		_LOG << "Initialize the dynamic app import settings..." LOG_
		*UMLImportTargetDBName = "CRM";
		*UMLImportTargetDBUser = "<dbuser>";
		*UMLImportTargetDBPass = "<dbpass>";
		*GeneralDBSchemaname = "public";

		*DatabaseSettingNamespace = "DatabaseLayerGateway"; // When used, I can support this one yet. But not fully tested.
		XMIFileUMLProject->setData("");

		UsePlugin->setData(false);
		//UseOtherXSLFile->setData(true);

#ifdef WINDOWS
		///\todo Change the used files to refer the HOME versions.
		//installXMIFilesToHome();
		//installXSLFilesToHome();
        XMIFileUMLProject->setData("c:\\lbDMF\\UMLSamples\\SecondStageModels\\lbDMF Manager.xmi");
        XMIFileUMLProjectExport->setData("c:\\lbDMF\\UMLSamples\\SecondStageModels\\Export.xmi");
		XSLFileUMLExport->setData("c:\\lbDMF\\XSLT\\DMFToXMI\\gen_DMFToXMI.xsl");
        XSLFileImportSettings->setData("c:\\lbDMF\\XSLT\\XMIToDMF\\XMISettings.xsl");
        XSLFileExportSettings->setData("c:\\lbDMF\\XSLT\\DMFToXMI\\XMISettings.xsl");
        XSLFileSystemDatabase->setData("c:\\lbDMF\\XSLT\\XMIToDMF\\ImportUML-SystemDB.xsl");
        XSLFileApplicationDatabase->setData("c:\\lbDMF\\XSLT\\XMIToDMF\\ImportUML-ApplicationDB.xsl");
#endif
#ifdef LINUX
#ifndef OSX
		///\todo Change the used files to refer the HOME versions.
		//installXMIFilesToHome();
		//installXSLFilesToHome();
        XMIFileUMLProject->setData("/usr/share/lbdmf/UMLSamples/SecondStageModels/lbDMFManager.xmi");
        XMIFileUMLProjectExport->setData("/usr/share/lbdmf/UMLSamples/SecondStageModels/Export.xmi");
	XSLFileUMLExport->setData("/usr/share/lbdmf/DMFToXMI/gen_DMFToXMI.xsl");
        XSLFileImportSettings->setData("/usr/share/lbdmf/XMIToDMF/XMISettings.xsl");
        XSLFileExportSettings->setData("/usr/share/lbdmf/DMFToXMI/XMISettings.xsl");
        XSLFileSystemDatabase->setData("/usr/share/lbdmf/XMIToDMF/importUML-SystemDB.xsl");
        XSLFileApplicationDatabase->setData("/usr/share/lbdmf/XMIToDMF/importUML-ApplicationDB.xsl");
#endif
#endif
#ifdef OSX
        XMIFileUMLProject->setData("./wxWrapper.app/Contents/Resources/UMLSamples/SecondStageModels/lbDMF Manager.xmi");
        XMIFileUMLProjectExport->setData("./wxWrapper.app/Contents/Resources/UMLSamples/SecondStageModels/Export.xmi");
		XSLFileUMLExport->setData("./wxWrapper.app/Contents/Resources/XSLT/DMFToXMI/gen_DMFToXMI.xsl");
        XSLFileImportSettings->setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/XMISettings.xsl");
        XSLFileExportSettings->setData("./wxWrapper.app/Contents/Resources/XSLT/DMFToXMI/XMISettings.xsl");
        XSLFileSystemDatabase->setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/ImportUML-SystemDB.xsl");
        XSLFileApplicationDatabase->setData("./wxWrapper.app/Contents/Resources/XSLT/XMIToDMF/ImportUML-ApplicationDB.xsl");
#endif
	 } else {
		_LOG << "Load the dynamic app import settings from parameter set..." LOG_
		*name = "UMLImportDBName";
		SomeBaseSettings->getUAPString(*&name, *&UMLImportTargetDBName);
		*name = "UMLImportDBUser";
		SomeBaseSettings->getUAPString(*&name, *&UMLImportTargetDBUser);
		*name = "UMLImportDBPass";
		SomeBaseSettings->getUAPString(*&name, *&UMLImportTargetDBPass);
		*name = "DatabaseSettingNamespace";
		SomeBaseSettings->getUAPString(*&name, *&DatabaseSettingNamespace);
		*name = "UsePlugin";
		SomeBaseSettings->getUAPBoolean(*&name, *&UsePlugin);
/*
		*name = "UseOtherXSLFile";
		SomeBaseSettings->getUAPBoolean(*&name, *&UseOtherXSLFile);
*/
		*name = "XSLFileSystemDatabase";
		SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileSystemDatabase);
		*name = "XSLFileApplicationDatabase";
		SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileApplicationDatabase);
		 *name = "XMIFileUMLProject";
		 SomeBaseSettings->getUAPFileLocation(*&name, *&XMIFileUMLProject);
		 *name = "XMIFileUMLProjectExport";
		 SomeBaseSettings->getUAPFileLocation(*&name, *&XMIFileUMLProjectExport);
		 *name = "GeneralDBSchemaname";
		 SomeBaseSettings->getUAPString(*&name, *&GeneralDBSchemaname);
		 *name = "XSLFileUMLExport";
		 SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileUMLExport);
		 *name = "XSLFileImportSettings";
		 SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileImportSettings);
		 *name = "XSLFileExportSettings";
		 SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileExportSettings);
	} 

	*name = "DBTables";
	QI(dbTables, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "DBColumns";
	QI(dbColumns, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "DBPrimaryKeys";
	QI(dbPrimaryKeys, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "DBForeignKeys";
	QI(dbForeignKeys, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	

	*name = "UMLImportTargetDBName";
	QI(UMLImportTargetDBName, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "UMLImportTargetDBUser";
	QI(UMLImportTargetDBUser, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "UMLImportTargetDBPass";
	QI(UMLImportTargetDBPass, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "DatabaseSettingNamespace";
	QI(DatabaseSettingNamespace, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "UsePlugin";
	QI(UsePlugin, lb_I_Unknown, uk)
	document->insert(&uk, &key);

	_LOG << "Loaded Use Plugin switch from database: " << UsePlugin->charrep() LOG_

	*name = "XSLFileUMLExport";
	QI(XSLFileUMLExport, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XSLFileImportSettings";
	QI(XSLFileImportSettings, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XSLFileExportSettings";
	QI(XSLFileExportSettings, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XSLFileSystemDatabase";
	QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XSLFileApplicationDatabase";
	QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
	document->insert(&uk, &key);
/*	
	*name = "UseOtherXSLFile";
	QI(UseOtherXSLFile, lb_I_Unknown, uk)
	document->insert(&uk, &key);
*/
	*name = "XMIFileUMLProject";
	QI(XMIFileUMLProject, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XMIFileUMLProjectExport";
	QI(XMIFileUMLProjectExport, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "GeneralDBSchemaname";
	QI(GeneralDBSchemaname, lb_I_Unknown, uk)
	document->insert(&uk, &key);

	if (

		(Actions != NULL) && 

		(Action_Steps != NULL) && 

		(UserAccounts != NULL) && 

		(Formulars != NULL) && 

		(FormularParameter != NULL) && 

		(User_Applications != NULL) && 

		(Applications_Formulars != NULL) && 

		(Applications != NULL) && 

		(Translations != NULL) && 

		(Formular_Actions != NULL) && 

		(ApplicationParameter != NULL) && 

		(Reports != NULL) && 

		(ReportParameters != NULL) && 

		(ReportElements != NULL) && 

		(ReportElementTypes != NULL) && 

		(ReportTexts != NULL) && 

		(Formular_Fields != NULL) && 

		(Action_Step_Transitions != NULL) && 

		(Column_Types != NULL) && 

		(FKPK_Mapping != NULL) && 

		(Action_Types != NULL) && 

		(Action_Parameters != NULL) && 

		(ActionStep_Parameters != NULL) && 

		true) {


		*name = "Actions";
		QI(Actions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Steps";
		QI(Action_Steps, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "UserAccounts";
		QI(UserAccounts, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formulars";
		QI(Formulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "FormularParameter";
		QI(FormularParameter, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "User_Applications";
		QI(User_Applications, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Applications_Formulars";
		QI(Applications_Formulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Applications";
		QI(Applications, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Translations";
		QI(Translations, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formular_Actions";
		QI(Formular_Actions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ApplicationParameter";
		QI(ApplicationParameter, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Reports";
		QI(Reports, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportParameters";
		QI(ReportParameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportElements";
		QI(ReportElements, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportElementTypes";
		QI(ReportElementTypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ReportTexts";
		QI(ReportTexts, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Formular_Fields";
		QI(Formular_Fields, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Step_Transitions";
		QI(Action_Step_Transitions, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Column_Types";
		QI(Column_Types, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "FKPK_Mapping";
		QI(FKPK_Mapping, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Types";
		QI(Action_Types, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "Action_Parameters";
		QI(Action_Parameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "ActionStep_Parameters";
		QI(ActionStep_Parameters, lb_I_Unknown, uk)
		document->insert(&uk, &key);

	}		
	
	*name = "ApplicationData";
	params->setUAPContainer(*&name, *&document);
	
	params++;
	meta->setActiveDocument(*&params);
	meta->setStatusText("Info", "Load database configuration done.");
	
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppInternalStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppBoUMLImportExport, lbDynamicAppBoUMLImportExport)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppBoUMLImportExport)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppBoUMLImportExport::lbDynamicAppBoUMLImportExport() {
	

	_CL_LOG << "lbDynamicAppBoUMLImportExport::lbDynamicAppBoUMLImportExport() called." LOG_
}

lbDynamicAppBoUMLImportExport::~lbDynamicAppBoUMLImportExport() {
	_CL_LOG << "lbDynamicAppBoUMLImportExport::~lbDynamicAppBoUMLImportExport() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppBoUMLImportExport::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;
	
	const char *params[16 + 1];
	
	params[0] = NULL;

	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)

	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_String, overwrite)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileImportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, writeXMISettings)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
								
	if (document != NULL) {
		*param = "XSLFileImportSettings";
		document->getUAPFileLocation(*&param, *&XSLFileImportSettings);
		*param = "XSLFileSystemDatabase";
		document->getUAPFileLocation(*&param, *&XSLFileSystemDatabase);
		*param = "XSLFileApplicationDatabase";
		document->getUAPFileLocation(*&param, *&XSLFileApplicationDatabase);

		_LOG << "Have got the following files: " << XSLFileSystemDatabase->charrep() << " and " << XSLFileApplicationDatabase->charrep() LOG_		

		*param = "UMLImportDBName";
		document->getUAPString(*&param, *&DBName);
		*param = "UMLImportDBUser";
		document->getUAPString(*&param, *&DBUser);
		*param = "UMLImportDBPass";
		document->getUAPString(*&param, *&DBPass);

		*param = "overwriteDatabase";
		document->getUAPString(*&param, *&overwrite);
		
		*param = "writeXMISettings";
		document->getUAPString(*&param, *&writeXMISettings);
		if (writeXMISettings->charrep() == NULL) {
			_LOG << "Warning: The writeXMISettings parameter was not passed. Set it to no." LOG_
			*writeXMISettings = "no";
		}
    }

	// Write the settings file for the application database here ...
	
	
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileImportSettings->charrep() != NULL) {
			if (strcmp(XSLFileImportSettings->charrep(), "<settings>") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream->setFileName(XSLFileImportSettings->charrep());
				if (oStream->open()) {
					oStream->setBinary();
					*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"' '\"/>--><!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/>--><!-- Mapped to Sqlite (in XSLT document) -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/>-->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/>-->\n";
					*oStream << "<xsl:variable name=\"targetdatabase\" select=\"'" << metaapp->getApplicationDatabaseBackend() << "'\"/><!-- Mapped from Application Database backend in the properties window group General -->\n";
					*oStream << "<xsl:variable name=\"execute_droprules\" select=\"'" << overwrite->charrep() << "'\"/>\n";
					
					DBName->replace(">", "&gt;");
					DBName->replace("<", "&lt;");
					DBUser->replace(">", "&gt;");
					DBUser->replace("<", "&lt;");
					DBPass->replace(">", "&gt;");
					DBPass->replace("<", "&lt;");
					
					*oStream << "<xsl:variable name=\"database_name\" select=\"'" << DBName->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_user\" select=\"'" << DBUser->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_pass\" select=\"'" << DBPass->charrep() << "'\"/>\n";
					
					/// \todo Write additional XMI settings here.				
					
					
					*oStream << "</xsl:stylesheet>\n";
					oStream->close();
				}
			}
		}
	}
	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__	
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif
		
	// Read the provided stream as the XMI document to be translated.
		
	UAP(lb_I_String, xmidoc)
	xmidoc = iStream->getAsString();
	xmlChar* XMIURL = (xmlChar*) iStream->getFileName();
	doc = xmlReadMemory((char const*) xmidoc->charrep(), strlen(xmidoc->charrep()), (char const*) XMIURL, NULL, 0);
	if (doc == NULL) {
		_LOG << "Error: Failed to load in-memory XMI document as an XML document." LOG_
		return err; 
	}
	
	// Read the stylesheet document to get SQL script for database creation
	metaapp->setStatusText("Info", "Importing application database model ...");

	if (metaapp->askYesNo("Would you create the database for the application to be imported ?")) {
		UAP(lb_I_String, styledoc)
		UAP(lb_I_InputStream, input)
		
		// May not initialized
		if (XSLFileApplicationDatabase->charrep() == NULL) {
			XSLFileApplicationDatabase->setData("");
		}
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
		*ts = XSLFileApplicationDatabase->charrep();
		ts->trim();
		XSLFileApplicationDatabase->setData(ts->charrep());
		
		if (strcmp(XSLFileApplicationDatabase->charrep(), "") == 0) {
			input = metaapp->askOpenFileReadStream("xsl|*.xsl");
			
			if (input == NULL) {
				return err;	
			}

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileApplicationDatabase->setData((char*) input->getFileName());
			
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
			UAP_REQUEST(getModuleInstance(), lb_I_String, value)
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
			
			parameter->setData("UML import settings");
			//--------------------------------------------
			
			parameterXSL->setData("XSL file for application database");
			fileXSL->setData(XSLFileApplicationDatabase->getData());
			paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);
			
			params->setUAPParameter(*&parameter, *&paramXSL);
			metaapp->showPropertyPanel(*&params, true);
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			REQUEST(getModuleInstance(), lb_I_InputStream, input)
			input->setFileName(XSLFileApplicationDatabase->charrep());
		}
		
		if (input->open()) {
			_LOG << "Try to get the file as a string..." LOG_
			styledoc = input->getAsString();
			_LOG << "Got the file as s string." LOG_
			
			xmlChar* URL = (xmlChar*) input->getFileName();
			_LOG << "Read the string as an in memory XML document." LOG_
			stylesheetdoc = xmlReadMemory((char const*) styledoc->charrep(), strlen(styledoc->charrep()), (char const*) URL, NULL, 0);
			if (stylesheetdoc == NULL) {
				_LOG << "Error: Failed to load in-memory XMI stylesheet document as an XML document (" << input->getFileName() << ")" LOG_
				return err; 
			}

			_LOG << "Parse xml document as stylesheet." LOG_
			cur = xsltParseStylesheetDoc(stylesheetdoc);
			
			if (cur == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				
				*msg = _trans("Failed to parse XSL file.");
				
				metaapp->msgBox(_trans("Error"), msg->charrep());
				return err;
			}
			
			xmlChar* result = NULL;
			int len = 0;

			_LOG << "Apply the stylesheet document." LOG_

			xsltTransformContextPtr ctxt;

			res = xsltApplyStylesheet(cur, doc, params);

			_LOG << "Save resulting document as a string." LOG_

			if (res == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)

				*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
				*msg += (const char*) XMIURL;
				*msg += "\n\nStylesheet: ";
				*msg += (const char*) URL;
				metaapp->msgBox(_trans("Error"), msg->charrep());
				return err;
			}

			xsltSaveResultToString(&result, &len, res, cur);
			
			xsltFreeStylesheet(cur);
			xmlFreeDoc(res);
			
			// Apply the resulting SQL script to the database
			
			_LOG << "Prepare database creation..." LOG_

			char* dbbackend = metaapp->getApplicationDatabaseBackend();
			
			UAP(lb_I_Database, database)
			UAP(lb_I_Query, sampleQuery)
			
			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_UML_IMPORT_LOADDATABASE_MODUL;
			}
				
			database->init();
			
			if ((database != NULL) && (database->connect(DBName->charrep(), DBName->charrep(), DBUser->charrep(), DBPass->charrep()) != ERR_NONE)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = "Could not login to given database.\n";
				*msg += "Please check the following:\n\n";
				*msg += "1. ODBC setup is correct.\n";
				*msg += "2. No spaces are in the database name.\n";
				*msg += "3. Database is created.\n";
				*msg += "4. Login credentials are correct.\n\n";
				*msg += "(Is the following setup correct:\nDatabase: ";
				*msg += DBName->charrep();
				*msg += "\nUser: ";
				*msg += DBUser->charrep();
				*msg += " ?";
				metaapp->msgBox("Error", msg->charrep());
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database->getQuery(DBName->charrep(), 0);
			
			if (result == NULL) {
				_LOG << "Error: Did not got the translation from XSLT file." LOG_
				return err;
			}
			
			_LOG << "Create database... (script is " << (const char*) result << ")" LOG_
			sampleQuery->skipFKCollecting();
			
			if ((metaapp->getApplicationDatabaseBackend() != NULL) && (strcmp(metaapp->getApplicationDatabaseBackend(), "") == 0)) {
				// Do an additional SQL command to create the PostgreSQL plsql handler, but ignore any failures
				sampleQuery->query("CREATE OR REPLACE FUNCTION plpgsql_call_handler()"
								   "RETURNS language_handler AS"
								   "'$libdir/plpgsql', 'plpgsql_call_handler'"
								   "LANGUAGE 'c' VOLATILE;\n"
								   "CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;");
			}
			
			if (sampleQuery->query((char*) result) != ERR_NONE) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = _trans("Failed to apply SQL Script imported from UML definition (XMI)!\n\nYou may have a permission problem when you manually have created\ntables with another user prior.\nPlease see into the logfile for more information.");
				metaapp->msgBox(_trans("Error"), msg->charrep());
				sampleQuery->enableFKCollecting();

				xmlFreeDoc(doc);
				
				xsltCleanupGlobals();
				xmlCleanupParser();	
				free(result);
				return err;
			} else {
				sampleQuery->close();
				database->close();
				_LOG << "Database schema has been created." LOG_
				free(result);
			}
		}	
	}
	
	// Read the stylesheet document to import application definition into system database
	
	metaapp->setStatusText("Info", "Importing lbDMF application definition ...");

	// Write the settings file for the application database here ...
	
	// If I import to a MS SQL server, then I need other settings. Always writing the 'wrong' default settings is not correct.
	if (*writeXMISettings == "yes") {
		if (XSLFileImportSettings->charrep() != NULL) {
			if (strcmp(XSLFileImportSettings->charrep(), "<settings>") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
				
				oStream->setFileName(XSLFileImportSettings->charrep());
				if (oStream->open()) {
					oStream->setBinary();
					*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"' '\"/>--><!-- Mapped to DefaultDatabaseSystem as in XSLT document defined. -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'DatabaseLayerGateway'\"/>--><!-- Mapped to Sqlite (in XSLT document) -->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'MSSQL'\"/>-->\n";
					*oStream << "<!--<xsl:variable name=\"targetdatabase\" select=\"'PostgreSQL'\"/>-->\n";
					*oStream << "<xsl:variable name=\"targetdatabase\" select=\"'" << metaapp->getSystemDatabaseBackend() << "'\"/><!-- Mapped from Application Database backend in the properties window group General -->\n";
					*oStream << "<xsl:variable name=\"execute_droprules\" select=\"'" << overwrite->charrep() << "'\"/>\n";

					DBName->replace(">", "&gt;");
					DBName->replace("<", "&lt;");
					DBUser->replace(">", "&gt;");
					DBUser->replace("<", "&lt;");
					DBPass->replace(">", "&gt;");
					DBPass->replace("<", "&lt;");

					*oStream << "<xsl:variable name=\"database_name\" select=\"'" << DBName->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_user\" select=\"'" << DBUser->charrep() << "'\"/>\n";
					*oStream << "<xsl:variable name=\"database_pass\" select=\"'" << DBPass->charrep() << "'\"/>\n";
					*oStream << "</xsl:stylesheet>\n";
					oStream->close();
				}
			}
		}
	}

	if (metaapp->askYesNo("Would you create the application definition for the application to be imported into the system database ?")) {
		UAP(lb_I_String, styledoc)
		UAP_REQUEST(getModuleInstance(), lb_I_InputStream, input)
		
		// May not initialized
		if (XSLFileSystemDatabase->charrep() == NULL) {
			XSLFileSystemDatabase->setData("");
		}
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
		*ts = XSLFileSystemDatabase->charrep();
		ts->trim();
		XSLFileSystemDatabase->setData(ts->charrep());
		
		if (strcmp(XSLFileSystemDatabase->charrep(), "") == 0) {
			input = metaapp->askOpenFileReadStream("xsl|*.xsl");
			
			if (input == NULL) {
				return err;	
			}

			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileSystemDatabase->setData((char*) input->getFileName());
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
			UAP_REQUEST(getModuleInstance(), lb_I_String, value)
			UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
			
			parameter->setData("UML import settings");
			//--------------------------------------------
			
			parameterXSL->setData("XSL file for system database");
			fileXSL->setData(XSLFileSystemDatabase->getData());
			paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);
			
			params->setUAPParameter(*&parameter, *&paramXSL);
			metaapp->showPropertyPanel(*&params, true);
		} else {
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			REQUEST(getModuleInstance(), lb_I_InputStream, input)
			input->setFileName(XSLFileSystemDatabase->charrep());
		}

		if (input->open()) {
			_LOG << "Try to get the file as a string..." LOG_
			styledoc = input->getAsString();
			_LOG << "Got the file as s string." LOG_
			
			xmlChar* URL = (xmlChar*) input->getFileName();
			_LOG << "Read the string as an in memory XML document." LOG_
			stylesheetdoc = xmlReadMemory((char const*) styledoc->charrep(), strlen(styledoc->charrep()), (char const*) URL, NULL, 0);
			if (stylesheetdoc == NULL) {
				_LOG << "Error: Failed to load in-memory XMI stylesheet document as an XML document." LOG_
				return err; 
			}

			_LOG << "Parse xml document as stylesheet." LOG_
			cur = xsltParseStylesheetDoc(stylesheetdoc);
			
			xmlChar* result = NULL;
			int len = 0;

			_LOG << "Apply the stylesheet document." LOG_

			res = xsltApplyStylesheet(cur, doc, params);

			if (res == NULL) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				
				*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
				*msg += (const char*) XMIURL;
				*msg += "\n\nStylesheet: ";
				*msg += (const char*) URL;
				metaapp->msgBox(_trans("Error"), msg->charrep());
				return err;
			}
			
			_LOG << "Save resulting document as a string." LOG_

			xsltSaveResultToString(&result, &len, res, cur);
			
			xsltFreeStylesheet(cur);
			xmlFreeDoc(res);
			
			// Apply the resulting SQL script to the database
			
			_LOG << "Prepare database creation..." LOG_

			char* dbbackend = metaapp->getSystemDatabaseBackend();
			
			UAP(lb_I_Database, database)
			UAP(lb_I_Query, sampleQuery)

			if (dbbackend != NULL && strcmp(dbbackend, "") != 0) {
				UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
				AQUIRE_PLUGIN_NAMESPACE_BYSTRING(lb_I_Database, dbbackend, database, "'database plugin'")
				_LOG << "Using plugin database backend for UML import operation..." LOG_
			} else {
				// Use built in
				REQUEST(getModuleInstance(), lb_I_Database, database)
				_LOG << "Using built in database backend for UML import operation..." LOG_
			}

			if (database == NULL) {
				_LOG << "Error: Could not load database backend, either plugin or built in version." LOG_
				return ERR_UML_IMPORT_LOADDATABASE_MODUL;
			}
				
			database->init();
			
			const char* lbDMFPasswd = getenv("lbDMFPasswd");
			const char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";
			
			if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
				UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
				*msg = "Could not login to given database.\n";
				*msg += "Please check the following:\n\n";
				*msg += "1. ODBC setup is correct.\n";
				*msg += "2. No spaces are in the database name.\n";
				*msg += "3. Database is created.\n";
				*msg += "4. Login credentials are correct.\n\n";
				*msg += "(Is the following setup correct:\nDatabase: ";
				*msg += DBName->charrep();
				*msg += "\nUser: ";
				*msg += DBUser->charrep();
				*msg += " ?";
				metaapp->msgBox("Error", msg->charrep());
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database->getQuery("lbDMF", 0);
			
			_LOG << "Create system database... (script is " << (const char*) result << ")" LOG_
			sampleQuery->skipFKCollecting();
			
			if ((metaapp->getSystemDatabaseBackend() != NULL) && (strcmp(metaapp->getSystemDatabaseBackend(), "") == 0)) {
				// Do an additional SQL command to create the PostgreSQL plsql handler, but ignore any failures
				sampleQuery->query("CREATE OR REPLACE FUNCTION plpgsql_call_handler()"
								   "RETURNS language_handler AS"
								   "'$libdir/plpgsql', 'plpgsql_call_handler'"
								   "LANGUAGE 'c' VOLATILE;\n"
								   "CREATE LANGUAGE plpgsql HANDLER plpgsql_call_handler;");
			}
			
			if (sampleQuery->query((char*) result) != ERR_NONE) {
				metaapp->msgBox("Error", "Failed to apply SQL Script imported from UML definition (XMI)!");
				sampleQuery->enableFKCollecting();

				xmlFreeDoc(doc);
				
				xsltCleanupGlobals();
				xmlCleanupParser();	
				free(result);
				
				return err;
			} else {
				sampleQuery->close();
				database->close();
				_LOG << "Database has been filled." LOG_
				sampleQuery->enableFKCollecting();
				free(result);
			}
		}	
	}

	xmlFreeDoc(doc);
				
	xsltCleanupGlobals();
	xmlCleanupParser();	

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;
	xsltStylesheetPtr cur = NULL;
	xmlDocPtr doc, res;
	xmlDocPtr stylesheetdoc;
	
	const char *params[16 + 1];
	
	_LOG << "lbDynamicAppBoUMLImportExport::save(lb_I_OutputStream* oStream) called." LOG_
	
	params[0] = NULL;
	
	UAP(lb_I_Parameter, appparams)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	appparams = metaapp->getPropertySet("DynamicAppDefaultSettings");

	/* To save the output of generated content, I need to deactivate the generation into a file inside
	 * the XSL template. Therefore the template needs to support it and the settings here should be used.
	 */
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DBPass)
	
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileExportSettings)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileUMLExport)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
	
	if (document != NULL) {
		*param = "XSLFileExportSettings";
		document->getUAPFileLocation(*&param, *&XSLFileExportSettings);
		
		*param = "XSLFileUMLExport";
		document->getUAPFileLocation(*&param, *&XSLFileUMLExport);
		
		_LOG << "Export definition for settings file is: " << XSLFileExportSettings->charrep() LOG_
		_LOG << "Export definition for UML XMI file is: " << XSLFileUMLExport->charrep() LOG_
	}
	
	xmlSubstituteEntitiesDefault(1);
#ifndef __WATCOMC__	
    xmlLoadExtDtdDefaultValue = 1;
#endif
#ifdef __WATCOMC__
    setxmlLoadExtDtdDefaultValue(1);
#endif
	
	// Read the lbDMF XML formatted stream into a memory block to be translated.
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, exportparams)
	UAP(lb_I_Unknown, uk)
	QI(exportparams, lb_I_Unknown, uk)
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, result)
	UAP(lb_I_Unknown, uk_result)
	QI(result, lb_I_Unknown, uk_result) // Result is not filled (inconsistent). The function exportApplicationToXMLBuffer returns it in the parameter given.
	
	UAP_REQUEST(getModuleInstance(), lb_I_Dispatcher, dispatcher)
	
	if (dispatcher->dispatch("exportApplicationToXMLBuffer", uk.getPtr(), &uk_result) == ERR_DISPATCH_FAILS) {
		_LOG << "Error: Failed to dispatch a call to 'exportApplicationToXMLBuffer'!" LOG_
		return err;
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, value)
	UAP_REQUEST(getModuleInstance(), lb_I_String, filename)
	param->setData("memorybuffer");
	exportparams->getUAPString(*&param, *&value);
	param->setData("filename");
	exportparams->getUAPString(*&param, *&filename);
	
	
	// Write the settings file for the application database here ...

	metaapp->setStatusText("Info", "Writing XMISettings ...");
	
	if (XSLFileExportSettings->charrep() != NULL) {
		if (strcmp(XSLFileExportSettings->charrep(), "<settings>") != 0) {
			UAP_REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
			
			oStream->setFileName(XSLFileExportSettings->charrep());
			if (oStream->open()) {
				oStream->setBinary();
				*oStream << "<xsl:stylesheet version=\"1.1\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\" xmlns:exsl=\"http://exslt.org/common\" extension-element-prefixes=\"exsl\">\n";
				*oStream << "<xsl:variable name=\"targetdatabase\" select=\"'" << metaapp->getApplicationDatabaseBackend() << "'\"/>\n";
				*oStream << "<xsl:variable name=\"stream_output\" select=\"'yes'\"/>\n";
				
				/// \todo Write additional XMI settings here.				
				
				
				*oStream << "</xsl:stylesheet>\n";
				oStream->close();
			} else {
				metaapp->msgBox("Error", "Failed to write to XMISettings file. Please check file permissions.");
				return err;
			}
		}
	}

	if (value->charrep() == NULL) {
		metaapp->msgBox("Error", "Step 1 of exporting application definition has been failed. (This is the plain XML format, not the XMI).");
		return err;
	} else {
		_LOG << "Generated XML file to transform: '" << value->charrep() << "'" LOG_
	}
	
	xmlChar* XMLURL = (xmlChar*) filename->charrep();
	doc = xmlReadMemory((char const*) value->charrep(), strlen(value->charrep()), (char const*) XMLURL, NULL, 0);
	if (doc == NULL) {
		_LOG << "Error: Failed to load in-memory XML document." LOG_
		metaapp->setStatusText("Info", "Failed to translate application definition to XMI.");
		return err; 
	}
	
	UAP(lb_I_String, styledoc)
	UAP(lb_I_InputStream, input)
	
	// May not initialized
	if (XSLFileUMLExport->charrep() == NULL) {
		XSLFileUMLExport->setData("");
	}
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, ts)
	*ts = XSLFileUMLExport->charrep();
	ts->trim();
	XSLFileUMLExport->setData(ts->charrep());
		
	if (strcmp(XSLFileUMLExport->charrep(), "") == 0) {
		input = metaapp->askOpenFileReadStream("xsl|*.xsl");
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		XSLFileUMLExport->setData((char*) input->getFileName());
		
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, paramXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameterXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_String, valueXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, fileXSL)
		UAP_REQUEST(getModuleInstance(), lb_I_Boolean, boolXSL)
		
		UAP_REQUEST(getModuleInstance(), lb_I_String, parameter)
		UAP_REQUEST(getModuleInstance(), lb_I_String, value)
		UAP_REQUEST(getModuleInstance(), lb_I_Integer, i)
		
		parameter->setData("UML export settings");
		//--------------------------------------------
		
		parameterXSL->setData("XSL file for application database");
		fileXSL->setData(XSLFileUMLExport->getData());
		paramXSL->setUAPFileLocation(*&parameterXSL, *&fileXSL);
		
		params->setUAPParameter(*&parameter, *&paramXSL);
		metaapp->showPropertyPanel(*&params, true);
	} else {
		UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
		REQUEST(getModuleInstance(), lb_I_InputStream, input)
		input->setFileName(XSLFileUMLExport->charrep());
	}

	metaapp->setStatusText("Info", "Start translating application definition to XMI ...");
	
	if (input->open()) {
		_LOG << "Try to get the file as a string..." LOG_
		styledoc = input->getAsString();
		_LOG << "Got the file as s string." LOG_
			
		xmlChar* URL = (xmlChar*) input->getFileName();
		_LOG << "Read the string as an in memory XML document." LOG_
		stylesheetdoc = xmlReadMemory((char const*) styledoc->charrep(), strlen(styledoc->charrep()), (char const*) URL, NULL, 0);
		if (stylesheetdoc == NULL) {
			_LOG << "Error: Failed to load in-memory XSL stylesheet document as an XML document (" << input->getFileName() << ")" LOG_
			metaapp->setStatusText("Info", "Failed to translate application definition to XMI.");
			return err; 
		}
			
		_LOG << "Parse xml document as stylesheet." LOG_
		cur = xsltParseStylesheetDoc(stylesheetdoc);
			
		if (cur == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = _trans("Failed to parse XSL file.");
				
			metaapp->msgBox(_trans("Error"), msg->charrep());
			metaapp->setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
			
		xmlChar* result = NULL;
		int len = 0;
			
		_LOG << "Apply the stylesheet document." LOG_
			
		xsltTransformContextPtr ctxt;
		
		res = xsltApplyStylesheet(cur, doc, params);
			
		_LOG << "Save resulting document as a string." LOG_
			
		if (res == NULL) {
			UAP_REQUEST(getModuleInstance(), lb_I_String, msg)
			
			*msg = _trans("Failed to translate XMI file.\n\nXMI document: ");
			*msg += (const char*) XMLURL;
			*msg += "\n\nStylesheet: ";
			*msg += (const char*) URL;
			metaapp->msgBox(_trans("Error"), msg->charrep());
			metaapp->setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
			
		xsltSaveResultToString(&result, &len, res, cur);
			
		xsltFreeStylesheet(cur);
		xmlFreeDoc(res);
			
		if (result == NULL) {
			_LOG << "Error: Did not got the translation from XSLT file." LOG_
			xmlFreeDoc(doc);
			
			xsltCleanupGlobals();
			xmlCleanupParser();	
			metaapp->setStatusText("Info", "Failed to translate application definition to XMI.");
			return err;
		}
		
		oStream->setBinary();
		*oStream << (char*) result;
		oStream->close();
		xmlFreeDoc(doc);
			
		xsltCleanupGlobals();
		xmlCleanupParser();	
		free(result);
		metaapp->setStatusText("Info", "");
		return err;
}	

return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::load(lb_I_Database* iDB) {
lbErrCodes err = ERR_NONE;
return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImportExport::save(lb_I_Database* oDB) {
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

	void LB_STDCALL setNamespace(const char* _namespace) { }
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

	void LB_STDCALL setNamespace(const char* _namespace) { }
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


/*...sclass lbPluginDynamicAppBoUMLImport implementation:0:*/
/*...slbPluginDynamicAppBoUMLImport:0:*/
class lbPluginDynamicAppBoUMLImport : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppBoUMLImport();
	
	virtual ~lbPluginDynamicAppBoUMLImport();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }
/*...e*/

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppBoUMLImport)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppBoUMLImport, lbPluginDynamicAppBoUMLImport)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppBoUMLImport::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppBoUMLImport::lbPluginDynamicAppBoUMLImport() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	
}

lbPluginDynamicAppBoUMLImport::~lbPluginDynamicAppBoUMLImport() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppBoUMLImport::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppBoUMLImport::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppBoUMLImport::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppBoUMLImport::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppBoUMLImport::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppBoUMLImportExport* DynamicAppStorage = new lbDynamicAppBoUMLImportExport();
		
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppBoUMLImport::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppBoUMLImportExport* DynamicAppStorage = new lbDynamicAppBoUMLImportExport();
		
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppBoUMLImport::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/

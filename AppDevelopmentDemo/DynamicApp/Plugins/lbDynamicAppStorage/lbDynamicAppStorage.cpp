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

	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)

	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)

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

	// Get the application ID, that would be stored inside the XML document
	UAP_REQUEST(getModuleInstance(), lb_I_Integer, AppID)
	*param = "SaveApplicationID";
	params->getUAPInteger(*&param, *&AppID);	

	UAP_REQUEST(getModuleInstance(), lb_I_String, name)

	UAP(lb_I_KeyBase, key)
	QI(name, lb_I_KeyBase, key)


	*name = "Reports";
	uk = document->getElement(&key);
	QI(uk, lb_I_Reports, reports)
			
	*name = "Reportparams";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportParameters, reportparams)
			
	*name = "Reportelements";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElements, reportelements)
			
	*name = "Reportelementtypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElementTypes, reportelementtypes)
			
	*name = "Reporttextblocks";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportTexts, reporttextblocks)
			

			
	*name = "FormularApplications";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications_Formulars, ApplicationFormulars)
			
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
			
	*name = "appActionStepTransitions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Step_Transitions, appActionStepTransitions)
	
	

	// Mark that data sets, that are related to this application
	applications = meta->getApplicationModel();
	
	meta->setStatusText("Info", "Write XML document ...");
	
	applications->selectApplication(AppID->getData());
	applications->mark();

	if ((forms != NULL) &&
	    (ApplicationFormulars != NULL) &&
	    (reports != NULL) &&
	    (reportparams != NULL) &&
	    (reportelements != NULL) &&
	    (reportelementtypes != NULL) &&
	    (reporttextblocks != NULL) &&
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
		(appActionStepTransitions != NULL) &&
		(appActionSteps != NULL)) {

	
		*oStream << "<lbDMF applicationid=\"";

		// Save currently used database backend information. It could be used to determine what to to in the XSLT templates.
		// If exported, the information may be changed.
		
		char* dbbackend = meta->getSystemDatabaseBackend();
		*oStream << "\" backend=\"" << dbbackend;

#ifdef OSX		
		*oStream << AppID->charrep() << "\" platform=\"osx\">\n";
#else
#ifdef LINUX		
		*oStream << AppID->charrep() << "\" platform=\"linux\">\n";
#else		
#ifdef WINDOWS		
		*oStream << AppID->charrep() << "\" platform=\"windows\">\n";
#else		
#ifdef SOLARIS		
		*oStream << AppID->charrep() << "\" platform=\"solaris\">\n";
#endif		
#endif		
#endif		
#endif		
		meta->setStatusText("Info", "Write XML document (reports) ...");
		reports->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (reportparams) ...");
		reportparams->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (reportelements) ...");
		reportelements->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (reportelementtypes) ...");
		reportelementtypes->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (reporttextblocks) ...");
		reporttextblocks->accept(*&aspect);
	
		meta->setStatusText("Info", "Write XML document (applications) ...");
		applications->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (ApplicationFormulars) ...");
		ApplicationFormulars->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (forms) ...");
		forms->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbPrimaryKeys) ...");
		dbPrimaryKeys->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbForeignKeys) ...");
		dbForeignKeys->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbTables) ...");
		dbTables->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (dbColumns) ...");
		dbColumns->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (formularfields) ...");
		formularfields->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (columntypes) ...");
		columntypes->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (formActions) ...");
		formActions->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (formParams) ...");
		formParams->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (appParams) ...");
		appParams->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (appActions) ...");
		appActions->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (appActionTypes) ...");
		appActionTypes->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (appActionSteps) ...");
		appActionSteps->accept(*&aspect);
		meta->setStatusText("Info", "Write XML document (appActionStepTransitions) ...");
		appActionStepTransitions->accept(*&aspect);

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
	_LOG << "lbDynamicAppInternalStorage::load(lb_I_InputStream*) called." LOG_
	UAP(lb_I_Aspect, aspect)
	QI(op, lb_I_Aspect, aspect)
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)

	if (aspect == NULL) {
	    _LOG << "Error: aspect instance not available." LOG_
	}

	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
	UAP(lb_I_Action_Types, appActionTypes)
	UAP(lb_I_DBTables, dbTables)
	UAP(lb_I_DBColumns, dbColumns)
	UAP(lb_I_DBPrimaryKeys, dbPrimaryKeys)
	UAP(lb_I_DBForeignKeys, dbForeignKeys)


	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)

	AQUIRE_PLUGIN(lb_I_Reports, Model, reports, "'database report'")
	AQUIRE_PLUGIN(lb_I_ReportParameters, Model, reportparams, "'database report parameter'")
	AQUIRE_PLUGIN(lb_I_ReportElements, Model, reportelements, "'database report elements'")
	AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, reportelementtypes, "'database report element types'")
	AQUIRE_PLUGIN(lb_I_ReportTexts, Model, reporttextblocks, "'database report text blocks'")
	AQUIRE_PLUGIN(lb_I_Column_Types, Model, columntypes, "'column types'")
	AQUIRE_PLUGIN(lb_I_Actions, Model, appActions, "'actions'")
	AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, formActions, "'formular actions'")
	AQUIRE_PLUGIN(lb_I_Action_Types, Model, appActionTypes, "'action types'")
	AQUIRE_PLUGIN(lb_I_Action_Steps, Model, appActionSteps, "'action steps'")
	AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, appActionStepTransitions, "'application formular assoc'")
	AQUIRE_PLUGIN(lb_I_Formulars, Model, forms, "'formulars'")
	AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, formularfields, "'formular fields'")
	AQUIRE_PLUGIN(lb_I_FormularParameter, Model, formParams, "'formular parameters'")
	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")
	AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, ApplicationFormulars, "'application formular assoc'")
	reports->accept(*&aspect);
	reportparams->accept(*&aspect);
	reportelements->accept(*&aspect);
	reportelementtypes->accept(*&aspect);
	reporttextblocks->accept(*&aspect);
	
	ApplicationFormulars->accept(*&aspect);
	forms->accept(*&aspect);
	formularfields->accept(*&aspect);
	columntypes->accept(*&aspect);
	formActions->accept(*&aspect);
	formParams->accept(*&aspect);
	appParams->accept(*&aspect);
	appActions->accept(*&aspect);
	appActionTypes->accept(*&aspect);
	appActionSteps->accept(*&aspect);
	appActionStepTransitions->accept(*&aspect);

	// Read out application settings
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBName)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBUser)
	UAP_REQUEST(getModuleInstance(), lb_I_String, UMLImportTargetDBPass)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XMIFileUMLProject)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

	UMLImportTargetDBName->accept(*&aspect);
	UMLImportTargetDBUser->accept(*&aspect);
	UMLImportTargetDBPass->accept(*&aspect);

	DatabaseSettingNamespace->accept(*&aspect);
	UsePlugin->accept(*&aspect);	
	XSLFileSystemDatabase->accept(*&aspect);
	XSLFileApplicationDatabase->accept(*&aspect);
	UseOtherXSLFile->accept(*&aspect);
	XMIFileUMLProject->accept(*&aspect);
	GeneralDBSchemaname->accept(*&aspect);

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_KeyBase, key)
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, metaapp)
	UAP_REQUEST(getModuleInstance(), lb_I_Container, document)
	UAP_REQUEST(getModuleInstance(), lb_I_String, name)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, param)
	QI(name, lb_I_KeyBase, key)

	param->setCloning(false);
	document->setCloning(false);

	if ((forms != NULL) && 
		(ApplicationFormulars != NULL) && 
		(reports != NULL) && 
		(reportparams != NULL) && 
		(reportelements != NULL) && 
		(reportelementtypes != NULL) && 
		(reporttextblocks != NULL) && 
		(formularfields != NULL) && 
		(formParams != NULL) && 
		(appActions != NULL) && 
		(appActionSteps != NULL) && 
		(appActionStepTransitions != NULL) && 
		(appActionTypes != NULL) && 
		(appParams != NULL)) {
		
		UAP(lb_I_Unknown, uk)
		
		metaapp->setStatusText("Info", "Load internal file format ...");
		
		_LOG << "Get active document" LOG_
		

		UAP(lb_I_Unknown, ukParams)
		UAP(lb_I_Parameter, params)

		ukParams = metaapp->getActiveDocument();
		QI(ukParams, lb_I_Parameter, params)
		
		*name = "Reports";
		QI(reports, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportparams";
		QI(reportparams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportelements";
		QI(reportelements, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportelementtypes";
		QI(reportelementtypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reporttextblocks";
		QI(reporttextblocks, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		
		
		*name = "FormularApplications";
		QI(ApplicationFormulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Formulars";
		QI(forms, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormularFields";
		QI(formularfields, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "ColumnTypes";
		QI(columntypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormActions";
		QI(formActions, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormParams";
		QI(formParams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppParams";
		QI(appParams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppActions";
		QI(appActions, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppAction_Steps";
		QI(appActionSteps, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppActionTypes";
		QI(appActionTypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "appActionStepTransitions";
		QI(appActionStepTransitions, lb_I_Unknown, uk)
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

		*name = "UseOtherXSLFile";
		QI(UseOtherXSLFile, lb_I_Unknown, uk)
		document->insert(&uk, &key);

		*name = "GeneralDBSchemaname";
		QI(GeneralDBSchemaname, lb_I_Unknown, uk)
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

	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
	UAP(lb_I_Formulars, forms)
	UAP(lb_I_Formular_Fields, formularfields)
	UAP(lb_I_Column_Types, columntypes)
	UAP(lb_I_FormularParameter, formParams)
	UAP(lb_I_Formular_Actions, formActions)
	UAP(lb_I_ApplicationParameter, appParams)
	UAP(lb_I_Actions, appActions)
	UAP(lb_I_Action_Steps, appActionSteps)
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)
	UAP(lb_I_Action_Types, appActionTypes)

	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)

	// Save application settings
	UAP(lb_I_String, UMLImportTargetDBName)
	UAP(lb_I_String, UMLImportTargetDBUser)
	UAP(lb_I_String, UMLImportTargetDBPass)
	UAP(lb_I_String, GeneralDBSchemaname)

	UAP(lb_I_FileLocation, XMIFileUMLProject)
	UAP(lb_I_FileLocation, XSLFileSystemDatabase)
	UAP(lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP(lb_I_String, DatabaseSettingNamespace)

	UAP(lb_I_Boolean, UsePlugin)
	UAP(lb_I_Boolean, UseOtherXSLFile)


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
			
			
	*name = "Reports";
	uk = document->getElement(&key);
	QI(uk, lb_I_Reports, reports)
			
	*name = "Reportparams";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportParameters, reportparams)
			
	*name = "Reportelements";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElements, reportelements)
			
	*name = "Reportelementtypes";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportElementTypes, reportelementtypes)
			
	*name = "Reporttextblocks";
	uk = document->getElement(&key);
	QI(uk, lb_I_ReportTexts, reporttextblocks)


			
	*name = "FormularApplications";
	uk = document->getElement(&key);
	QI(uk, lb_I_Applications_Formulars, ApplicationFormulars)
			
	*name = "Formulars";
	uk = document->getElement(&key);
	QI(uk, lb_I_Formulars, forms)
			
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
			
	*name = "appActionStepTransitions";
	uk = document->getElement(&key);
	QI(uk, lb_I_Action_Step_Transitions, appActionStepTransitions)



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
	
	*name = "UseOtherXSLFile";
	uk = document->getElement(&key);
	QI(uk, lb_I_Boolean, UseOtherXSLFile)
			
	*name = "XMIFileUMLProject";
	uk = document->getElement(&key);
	QI(uk, lb_I_FileLocation, XMIFileUMLProject)

	*name = "GeneralDBSchemaname";
	uk = document->getElement(&key);
	QI(uk, lb_I_String, GeneralDBSchemaname)
			

	if ((forms != NULL) &&
	    (ApplicationFormulars != NULL) &&
	    (reports != NULL) &&
	    (reportparams != NULL) &&
	    (reportelements != NULL) &&
	    (reportelementtypes != NULL) &&
	    (reporttextblocks != NULL) &&
	    (formularfields != NULL) &&
	    (formParams != NULL) &&
	    (columntypes != NULL) &&
	    (formActions != NULL) &&
		(appParams != NULL) &&
		(appActions != NULL) &&
		(appActionTypes != NULL) &&
		(appActionStepTransitions != NULL) &&
		(appActionSteps != NULL)) {

		_LOG << "Start storing the data" LOG_

		reports->accept(*&aspect);
		reportparams->accept(*&aspect);
		reportelements->accept(*&aspect);
		reportelementtypes->accept(*&aspect);
		reporttextblocks->accept(*&aspect);

		ApplicationFormulars->accept(*&aspect);
		forms->accept(*&aspect);
		formularfields->accept(*&aspect);
		columntypes->accept(*&aspect);
		formActions->accept(*&aspect);
		formParams->accept(*&aspect);
		appParams->accept(*&aspect);
		appActions->accept(*&aspect);
		appActionTypes->accept(*&aspect);
		appActionSteps->accept(*&aspect);
		appActionStepTransitions->accept(*&aspect);

		UMLImportTargetDBName->accept(*&aspect);
		UMLImportTargetDBUser->accept(*&aspect);
		UMLImportTargetDBPass->accept(*&aspect);

		DatabaseSettingNamespace->accept(*&aspect);
		UsePlugin->accept(*&aspect);
		XSLFileSystemDatabase->accept(*&aspect);
		XSLFileApplicationDatabase->accept(*&aspect);
		UseOtherXSLFile->accept(*&aspect);
		XMIFileUMLProject->accept(*&aspect);
		GeneralDBSchemaname->accept(*&aspect);

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


	UAP(lb_I_Applications_Formulars, ApplicationFormulars)
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
	UAP(lb_I_Action_Step_Transitions, appActionStepTransitions)

	UAP(lb_I_Reports, reports)
	UAP(lb_I_ReportParameters, reportparams)
	UAP(lb_I_ReportElements, reportelements)
	UAP(lb_I_ReportElementTypes, reportelementtypes)
	UAP(lb_I_ReportTexts, reporttextblocks)

	AQUIRE_PLUGIN(lb_I_Reports, Model, reports, "'database report'")
	AQUIRE_PLUGIN(lb_I_ReportParameters, Model, reportparams, "'database report parameter'")
	AQUIRE_PLUGIN(lb_I_ReportElements, Model, reportelements, "'database report elements'")
	AQUIRE_PLUGIN(lb_I_ReportElementTypes, Model, reportelementtypes, "'database report element types'")
	AQUIRE_PLUGIN(lb_I_ReportTexts, Model, reporttextblocks, "'database report text blocks'")
	AQUIRE_PLUGIN(lb_I_Column_Types, Model, columntypes, "'column types'")
	AQUIRE_PLUGIN(lb_I_Actions, Model, appActions, "'actions'")
	AQUIRE_PLUGIN(lb_I_Formular_Actions, Model, formActions, "'formular actions'")
	AQUIRE_PLUGIN(lb_I_Action_Types, Model, appActionTypes, "'action types'")
	AQUIRE_PLUGIN(lb_I_Action_Steps, Model, appActionSteps, "'action steps'")
	AQUIRE_PLUGIN(lb_I_Formulars, Model, forms, "'formulars'")
	AQUIRE_PLUGIN(lb_I_Formular_Fields, Model, formularfields, "'formular fields'")
	AQUIRE_PLUGIN(lb_I_FormularParameter, Model, formParams, "'formular parameters'")
	AQUIRE_PLUGIN(lb_I_ApplicationParameter, Model, appParams, "'application parameters'")
	AQUIRE_PLUGIN(lb_I_Applications_Formulars, Model, ApplicationFormulars, "'application formular assoc'")
	AQUIRE_PLUGIN(lb_I_Action_Step_Transitions, Model, appActionStepTransitions, "'application formular assoc'")

	if (reports == NULL)  {
		_LOG << "lb_I_Reports instance is NULL." LOG_
	}
	if (reportparams == NULL)  {
		_LOG << "lb_I_ReportParameters instance is NULL." LOG_
	}
	if (reportelements == NULL)  {
		_LOG << "lb_I_ReportElements instance is NULL." LOG_
	}
	if (reportelementtypes == NULL)  {
		_LOG << "lb_I_ReportElementTypes instance is NULL." LOG_
	}
	if (reporttextblocks == NULL)  {
		_LOG << "lb_I_ReportTexts instance is NULL." LOG_
	}
	if (ApplicationFormulars == NULL)  {
		_LOG << "lb_I_Applications_Formulars instance is NULL." LOG_
	}
	if (forms == NULL)  {
		_LOG << "lb_I_Formulars instance is NULL." LOG_
	}
	if (formularfields == NULL)  {
		_LOG << "lb_I_Formular_Fields instance is NULL." LOG_
	}
	if (columntypes == NULL)  {
		_LOG << "lb_I_Column_Types instance is NULL." LOG_
	}
	if (formParams == NULL)  {
		_LOG << "lb_I_FormularParameter instance is NULL." LOG_
	}
	if (formActions == NULL)  {
		_LOG << "lb_I_Formular_Actions instance is NULL." LOG_
	}
	if (appParams == NULL)  {
		_LOG << "lb_I_ApplicationParameter instance is NULL." LOG_
	}
	if (appActions == NULL)  {
		_LOG << "lb_I_Actions instance is NULL." LOG_
	}
	if (appActionTypes == NULL)  {
		_LOG << "lb_I_Action_Types instance is NULL." LOG_
	}
	if (appActionSteps == NULL)  {
		_LOG << "lb_I_Action_Steps instance is NULL." LOG_
	}
	if (appActionStepTransitions == NULL)  {
		_LOG << "lb_I_Action_Step_Transitions instance is NULL." LOG_
	}
	
	meta->setStatusText("Info", "Load database configuration (reports) ...");
	reports->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (reportparams) ...");
	reportparams->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (reportelements) ...");
	reportelements->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (reportelementtypes) ...");
	reportelementtypes->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (reporttextblocks) ...");
	reporttextblocks->accept(*&aspect);
	
	meta->setStatusText("Info", "Load database configuration (ApplicationFormulars) ...");
	ApplicationFormulars->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (forms) ...");
	forms->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (formularfields) ...");
	formularfields->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (columntypes) ...");
	columntypes->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (formActions) ...");
	formActions->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (formParams) ...");
	formParams->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (appParams) ...");
	appParams->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (appActions) ...");
	appActions->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (appActionTypes) ...");
	appActionTypes->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (appActionSteps) ...");
	appActionSteps->accept(*&aspect);
	meta->setStatusText("Info", "Load database configuration (appActionStepTransitions) ...");
	appActionStepTransitions->accept(*&aspect);

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
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_String, DatabaseSettingNamespace)
	UAP_REQUEST(getModuleInstance(), lb_I_String, GeneralDBSchemaname)

	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UsePlugin)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, UseOtherXSLFile)

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
		UseOtherXSLFile->setData(true);

		XSLFileSystemDatabase->setData("<system>");
		XSLFileApplicationDatabase->setData("<application>");
		XMIFileUMLProject->setData("<UML XMI file>");
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
		*name = "UseOtherXSLFile";
		SomeBaseSettings->getUAPBoolean(*&name, *&UseOtherXSLFile);
		*name = "XSLFileSystemDatabase";
		SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileSystemDatabase);
		*name = "XSLFileApplicationDatabase";
		SomeBaseSettings->getUAPFileLocation(*&name, *&XSLFileApplicationDatabase);
		*name = "XMIFileUMLProject";
		SomeBaseSettings->getUAPFileLocation(*&name, *&XMIFileUMLProject);
		*name = "GeneralDBSchemaname";
		SomeBaseSettings->getUAPString(*&name, *&GeneralDBSchemaname);
	} 

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

	*name = "XSLFileSystemDatabase";
	QI(XSLFileSystemDatabase, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "XSLFileApplicationDatabase";
	QI(XSLFileApplicationDatabase, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	*name = "UseOtherXSLFile";
	QI(UseOtherXSLFile, lb_I_Unknown, uk)
	document->insert(&uk, &key);

	*name = "XMIFileUMLProject";
	QI(XMIFileUMLProject, lb_I_Unknown, uk)
	document->insert(&uk, &key);

	*name = "GeneralDBSchemaname";
	QI(GeneralDBSchemaname, lb_I_Unknown, uk)
	document->insert(&uk, &key);

	*name = "appActionStepTransitions";
	QI(appActionStepTransitions, lb_I_Unknown, uk)
	document->insert(&uk, &key);
	
	if ((forms != NULL) && 
		(ApplicationFormulars != NULL) && 
		(reports != NULL) && 
		(reportparams != NULL) && 
		(reportelements != NULL) && 
		(reportelementtypes != NULL) && 
		(reporttextblocks != NULL) && 
		(formularfields != NULL) && 
		(formParams != NULL) && 
		(appActions != NULL) && 
		(appActionSteps != NULL) && 
		(appActionStepTransitions != NULL) && 
		(appActionTypes != NULL) && 
		(appParams != NULL)) {

		*name = "Reports";
		QI(reports, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportparams";
		QI(reportparams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportelements";
		QI(reportelements, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reportelementtypes";
		QI(reportelementtypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Reporttextblocks";
		QI(reporttextblocks, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		
		
		*name = "FormularApplications";
		QI(ApplicationFormulars, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "Formulars";
		QI(forms, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormularFields";
		QI(formularfields, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "ColumnTypes";
		QI(columntypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormActions";
		QI(formActions, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "FormParams";
		QI(formParams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppParams";
		QI(appParams, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppActions";
		QI(appActions, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppAction_Steps";
		QI(appActionSteps, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "AppActionTypes";
		QI(appActionTypes, lb_I_Unknown, uk)
		document->insert(&uk, &key);
		
		*name = "appActionStepTransitions";
		QI(appActionStepTransitions, lb_I_Unknown, uk)
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

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppBoUMLImport, lbDynamicAppBoUMLImport)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppBoUMLImport)
	ADD_INTERFACE(lb_I_StandaloneStreamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppBoUMLImport::lbDynamicAppBoUMLImport() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppBoUMLImport::lbDynamicAppBoUMLImport() called." LOG_
}

lbDynamicAppBoUMLImport::~lbDynamicAppBoUMLImport() {
	_CL_LOG << "lbDynamicAppBoUMLImport::~lbDynamicAppBoUMLImport() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImport::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppBoUMLImport::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppBoUMLImport::load(lb_I_InputStream* iStream) {
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

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileSystemDatabase)
	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, XSLFileApplicationDatabase)

	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	ukDoc = metaapp->getActiveDocument();
	QI(ukDoc, lb_I_Parameter, document)
								
	if (document != NULL) {
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
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileApplicationDatabase->setData((char*) input->getFileName());
			
			UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_String, valueXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
			UAP_REQUEST(manager.getPtr(), lb_I_String, value)
			UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
			
			parameter->setData("Transformation settings");
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
				metaapp->msgBox("Error", "Could not login to given database.\nPlease check the following:\n\n1. ODBC setup is correct.\n2. No spaces are in the database name.\n3. Database is created.\n4. Login credentials are correct.");
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database->getQuery(DBName->charrep(), 0);
			
			if (result == NULL) {
				_LOG << "Error: Did not got the translation from XSLT file." LOG_
				return err;
			}
			
			_LOG << "Create database... (script is " << (const char*) result << ")" LOG_
			sampleQuery->skipFKCollecting();
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
				database->close();
				_LOG << "Database schema has been created." LOG_
				free(result);
			}
		}	
	}
	
	// Read the stylesheet document to import application definition into system database
	
	metaapp->setStatusText("Info", "Importing lbDMF application definition ...");

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
			UAP_REQUEST(getModuleInstance(), lb_I_Parameter, params)
			XSLFileSystemDatabase->setData((char*) input->getFileName());
			UAP_REQUEST(manager.getPtr(), lb_I_Parameter, paramXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_String, parameterXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_String, valueXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_FileLocation, fileXSL)
			UAP_REQUEST(manager.getPtr(), lb_I_Boolean, boolXSL)

			UAP_REQUEST(manager.getPtr(), lb_I_String, parameter)
			UAP_REQUEST(manager.getPtr(), lb_I_String, value)
			UAP_REQUEST(manager.getPtr(), lb_I_Integer, i)
			
			parameter->setData("Transformation settings");
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
			
			char* lbDMFPasswd = getenv("lbDMFPasswd");
			char* lbDMFUser   = getenv("lbDMFUser");
			
			if (!lbDMFUser) lbDMFUser = "dba";
			if (!lbDMFPasswd) lbDMFPasswd = "trainres";
			
			if ((database != NULL) && (database->connect("lbDMF", "lbDMF", lbDMFUser, lbDMFPasswd) != ERR_NONE)) {
				metaapp->msgBox("Error", "Could not login to given database.\nPlease check the following:\n\n1. ODBC setup is correct.\n2. Database is created.\n3. Login credentials are correct.");
				return ERR_DB_CONNECT;
			}
			
			sampleQuery = database->getQuery("lbDMF", 0);
			
			_LOG << "Create system database... (script is " << (const char*) result << ")" LOG_
			sampleQuery->skipFKCollecting();
			if (sampleQuery->query((char*) result) != ERR_NONE) {
				metaapp->msgBox("Error", "Failed to apply SQL Script imported from UML definition (XMI)!");
				sampleQuery->enableFKCollecting();

				xmlFreeDoc(doc);
				
				xsltCleanupGlobals();
				xmlCleanupParser();	
				free(result);
				
				return err;
			} else {
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

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImport::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImport::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;
	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppBoUMLImport::save(lb_I_Database* oDB) {
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
	ref = STARTREF;
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
		lbDynamicAppBoUMLImport* DynamicAppStorage = new lbDynamicAppBoUMLImport();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
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
	
		lbDynamicAppBoUMLImport* DynamicAppStorage = new lbDynamicAppBoUMLImport();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
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



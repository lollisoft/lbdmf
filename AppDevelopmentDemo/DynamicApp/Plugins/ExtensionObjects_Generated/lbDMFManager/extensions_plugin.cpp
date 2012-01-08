
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

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

/*...e*/

/*...sclass lbPluginModulelbDMFDataModelExtensions:0:*/
class lbPluginModulelbDMFDataModelExtensions : public lb_I_PluginModule {
public:

	lbPluginModulelbDMFDataModelExtensions();
	virtual ~lbPluginModulelbDMFDataModelExtensions();

	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};
/*...e*/

/*...sclass lbPluginModulelbDMFDataModelExtensions implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModulelbDMFDataModelExtensions)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModulelbDMFDataModelExtensions)

BEGIN_PLUGINS(lbPluginModulelbDMFDataModelExtensions)
// Generated plugin definitions
	ADD_PLUGIN(lbPluginActionsInternalFileReaderExtension, InputStreamVisitor_ActionsModel)
	ADD_PLUGIN(lbPluginActionsDBReaderExtension, DatabaseInputStreamVisitor_ActionsModel)
	ADD_PLUGIN(lbPluginActionsInternalFileWriterExtension, OutputStreamVisitor_ActionsModel)
	ADD_PLUGIN(lbPluginActionsXMLWriterExtension, XMLOutputStreamVisitor_ActionsModel)

	ADD_PLUGIN(lbPluginAction_StepsInternalFileReaderExtension, InputStreamVisitor_Action_StepsModel)
	ADD_PLUGIN(lbPluginAction_StepsDBReaderExtension, DatabaseInputStreamVisitor_Action_StepsModel)
	ADD_PLUGIN(lbPluginAction_StepsInternalFileWriterExtension, OutputStreamVisitor_Action_StepsModel)
	ADD_PLUGIN(lbPluginAction_StepsXMLWriterExtension, XMLOutputStreamVisitor_Action_StepsModel)

	ADD_PLUGIN(lbPluginUserAccountsInternalFileReaderExtension, InputStreamVisitor_UserAccountsModel)
	ADD_PLUGIN(lbPluginUserAccountsDBReaderExtension, DatabaseInputStreamVisitor_UserAccountsModel)
	ADD_PLUGIN(lbPluginUserAccountsInternalFileWriterExtension, OutputStreamVisitor_UserAccountsModel)
	ADD_PLUGIN(lbPluginUserAccountsXMLWriterExtension, XMLOutputStreamVisitor_UserAccountsModel)

	ADD_PLUGIN(lbPluginFormularsInternalFileReaderExtension, InputStreamVisitor_FormularsModel)
	ADD_PLUGIN(lbPluginFormularsDBReaderExtension, DatabaseInputStreamVisitor_FormularsModel)
	ADD_PLUGIN(lbPluginFormularsInternalFileWriterExtension, OutputStreamVisitor_FormularsModel)
	ADD_PLUGIN(lbPluginFormularsXMLWriterExtension, XMLOutputStreamVisitor_FormularsModel)

	ADD_PLUGIN(lbPluginFormularParameterInternalFileReaderExtension, InputStreamVisitor_FormularParameterModel)
	ADD_PLUGIN(lbPluginFormularParameterDBReaderExtension, DatabaseInputStreamVisitor_FormularParameterModel)
	ADD_PLUGIN(lbPluginFormularParameterInternalFileWriterExtension, OutputStreamVisitor_FormularParameterModel)
	ADD_PLUGIN(lbPluginFormularParameterXMLWriterExtension, XMLOutputStreamVisitor_FormularParameterModel)

	ADD_PLUGIN(lbPluginUser_ApplicationsInternalFileReaderExtension, InputStreamVisitor_User_ApplicationsModel)
	ADD_PLUGIN(lbPluginUser_ApplicationsDBReaderExtension, DatabaseInputStreamVisitor_User_ApplicationsModel)
	ADD_PLUGIN(lbPluginUser_ApplicationsInternalFileWriterExtension, OutputStreamVisitor_User_ApplicationsModel)
	ADD_PLUGIN(lbPluginUser_ApplicationsXMLWriterExtension, XMLOutputStreamVisitor_User_ApplicationsModel)

	ADD_PLUGIN(lbPluginApplications_FormularsInternalFileReaderExtension, InputStreamVisitor_Applications_FormularsModel)
	ADD_PLUGIN(lbPluginApplications_FormularsDBReaderExtension, DatabaseInputStreamVisitor_Applications_FormularsModel)
	ADD_PLUGIN(lbPluginApplications_FormularsInternalFileWriterExtension, OutputStreamVisitor_Applications_FormularsModel)
	ADD_PLUGIN(lbPluginApplications_FormularsXMLWriterExtension, XMLOutputStreamVisitor_Applications_FormularsModel)

	ADD_PLUGIN(lbPluginApplicationsInternalFileReaderExtension, InputStreamVisitor_ApplicationsModel)
	ADD_PLUGIN(lbPluginApplicationsDBReaderExtension, DatabaseInputStreamVisitor_ApplicationsModel)
	ADD_PLUGIN(lbPluginApplicationsInternalFileWriterExtension, OutputStreamVisitor_ApplicationsModel)
	ADD_PLUGIN(lbPluginApplicationsXMLWriterExtension, XMLOutputStreamVisitor_ApplicationsModel)

	ADD_PLUGIN(lbPluginTranslationsInternalFileReaderExtension, InputStreamVisitor_TranslationsModel)
	ADD_PLUGIN(lbPluginTranslationsDBReaderExtension, DatabaseInputStreamVisitor_TranslationsModel)
	ADD_PLUGIN(lbPluginTranslationsInternalFileWriterExtension, OutputStreamVisitor_TranslationsModel)
	ADD_PLUGIN(lbPluginTranslationsXMLWriterExtension, XMLOutputStreamVisitor_TranslationsModel)

	ADD_PLUGIN(lbPluginFormular_ActionsInternalFileReaderExtension, InputStreamVisitor_Formular_ActionsModel)
	ADD_PLUGIN(lbPluginFormular_ActionsDBReaderExtension, DatabaseInputStreamVisitor_Formular_ActionsModel)
	ADD_PLUGIN(lbPluginFormular_ActionsInternalFileWriterExtension, OutputStreamVisitor_Formular_ActionsModel)
	ADD_PLUGIN(lbPluginFormular_ActionsXMLWriterExtension, XMLOutputStreamVisitor_Formular_ActionsModel)

	ADD_PLUGIN(lbPluginApplicationParameterInternalFileReaderExtension, InputStreamVisitor_ApplicationParameterModel)
	ADD_PLUGIN(lbPluginApplicationParameterDBReaderExtension, DatabaseInputStreamVisitor_ApplicationParameterModel)
	ADD_PLUGIN(lbPluginApplicationParameterInternalFileWriterExtension, OutputStreamVisitor_ApplicationParameterModel)
	ADD_PLUGIN(lbPluginApplicationParameterXMLWriterExtension, XMLOutputStreamVisitor_ApplicationParameterModel)

	ADD_PLUGIN(lbPluginReportsInternalFileReaderExtension, InputStreamVisitor_ReportsModel)
	ADD_PLUGIN(lbPluginReportsDBReaderExtension, DatabaseInputStreamVisitor_ReportsModel)
	ADD_PLUGIN(lbPluginReportsInternalFileWriterExtension, OutputStreamVisitor_ReportsModel)
	ADD_PLUGIN(lbPluginReportsXMLWriterExtension, XMLOutputStreamVisitor_ReportsModel)

	ADD_PLUGIN(lbPluginReportParametersInternalFileReaderExtension, InputStreamVisitor_ReportParametersModel)
	ADD_PLUGIN(lbPluginReportParametersDBReaderExtension, DatabaseInputStreamVisitor_ReportParametersModel)
	ADD_PLUGIN(lbPluginReportParametersInternalFileWriterExtension, OutputStreamVisitor_ReportParametersModel)
	ADD_PLUGIN(lbPluginReportParametersXMLWriterExtension, XMLOutputStreamVisitor_ReportParametersModel)

	ADD_PLUGIN(lbPluginReportElementsInternalFileReaderExtension, InputStreamVisitor_ReportElementsModel)
	ADD_PLUGIN(lbPluginReportElementsDBReaderExtension, DatabaseInputStreamVisitor_ReportElementsModel)
	ADD_PLUGIN(lbPluginReportElementsInternalFileWriterExtension, OutputStreamVisitor_ReportElementsModel)
	ADD_PLUGIN(lbPluginReportElementsXMLWriterExtension, XMLOutputStreamVisitor_ReportElementsModel)

	ADD_PLUGIN(lbPluginReportElementTypesInternalFileReaderExtension, InputStreamVisitor_ReportElementTypesModel)
	ADD_PLUGIN(lbPluginReportElementTypesDBReaderExtension, DatabaseInputStreamVisitor_ReportElementTypesModel)
	ADD_PLUGIN(lbPluginReportElementTypesInternalFileWriterExtension, OutputStreamVisitor_ReportElementTypesModel)
	ADD_PLUGIN(lbPluginReportElementTypesXMLWriterExtension, XMLOutputStreamVisitor_ReportElementTypesModel)

	ADD_PLUGIN(lbPluginReportTextsInternalFileReaderExtension, InputStreamVisitor_ReportTextsModel)
	ADD_PLUGIN(lbPluginReportTextsDBReaderExtension, DatabaseInputStreamVisitor_ReportTextsModel)
	ADD_PLUGIN(lbPluginReportTextsInternalFileWriterExtension, OutputStreamVisitor_ReportTextsModel)
	ADD_PLUGIN(lbPluginReportTextsXMLWriterExtension, XMLOutputStreamVisitor_ReportTextsModel)

	ADD_PLUGIN(lbPluginFormular_FieldsInternalFileReaderExtension, InputStreamVisitor_Formular_FieldsModel)
	ADD_PLUGIN(lbPluginFormular_FieldsDBReaderExtension, DatabaseInputStreamVisitor_Formular_FieldsModel)
	ADD_PLUGIN(lbPluginFormular_FieldsInternalFileWriterExtension, OutputStreamVisitor_Formular_FieldsModel)
	ADD_PLUGIN(lbPluginFormular_FieldsXMLWriterExtension, XMLOutputStreamVisitor_Formular_FieldsModel)

	ADD_PLUGIN(lbPluginAction_Step_TransitionsInternalFileReaderExtension, InputStreamVisitor_Action_Step_TransitionsModel)
	ADD_PLUGIN(lbPluginAction_Step_TransitionsDBReaderExtension, DatabaseInputStreamVisitor_Action_Step_TransitionsModel)
	ADD_PLUGIN(lbPluginAction_Step_TransitionsInternalFileWriterExtension, OutputStreamVisitor_Action_Step_TransitionsModel)
	ADD_PLUGIN(lbPluginAction_Step_TransitionsXMLWriterExtension, XMLOutputStreamVisitor_Action_Step_TransitionsModel)

	ADD_PLUGIN(lbPluginColumn_TypesInternalFileReaderExtension, InputStreamVisitor_Column_TypesModel)
	ADD_PLUGIN(lbPluginColumn_TypesDBReaderExtension, DatabaseInputStreamVisitor_Column_TypesModel)
	ADD_PLUGIN(lbPluginColumn_TypesInternalFileWriterExtension, OutputStreamVisitor_Column_TypesModel)
	ADD_PLUGIN(lbPluginColumn_TypesXMLWriterExtension, XMLOutputStreamVisitor_Column_TypesModel)

	ADD_PLUGIN(lbPluginFKPK_MappingInternalFileReaderExtension, InputStreamVisitor_FKPK_MappingModel)
	ADD_PLUGIN(lbPluginFKPK_MappingDBReaderExtension, DatabaseInputStreamVisitor_FKPK_MappingModel)
	ADD_PLUGIN(lbPluginFKPK_MappingInternalFileWriterExtension, OutputStreamVisitor_FKPK_MappingModel)
	ADD_PLUGIN(lbPluginFKPK_MappingXMLWriterExtension, XMLOutputStreamVisitor_FKPK_MappingModel)

	ADD_PLUGIN(lbPluginAction_TypesInternalFileReaderExtension, InputStreamVisitor_Action_TypesModel)
	ADD_PLUGIN(lbPluginAction_TypesDBReaderExtension, DatabaseInputStreamVisitor_Action_TypesModel)
	ADD_PLUGIN(lbPluginAction_TypesInternalFileWriterExtension, OutputStreamVisitor_Action_TypesModel)
	ADD_PLUGIN(lbPluginAction_TypesXMLWriterExtension, XMLOutputStreamVisitor_Action_TypesModel)

	ADD_PLUGIN(lbPluginAction_ParametersInternalFileReaderExtension, InputStreamVisitor_Action_ParametersModel)
	ADD_PLUGIN(lbPluginAction_ParametersDBReaderExtension, DatabaseInputStreamVisitor_Action_ParametersModel)
	ADD_PLUGIN(lbPluginAction_ParametersInternalFileWriterExtension, OutputStreamVisitor_Action_ParametersModel)
	ADD_PLUGIN(lbPluginAction_ParametersXMLWriterExtension, XMLOutputStreamVisitor_Action_ParametersModel)

	ADD_PLUGIN(lbPluginActionStep_ParametersInternalFileReaderExtension, InputStreamVisitor_ActionStep_ParametersModel)
	ADD_PLUGIN(lbPluginActionStep_ParametersDBReaderExtension, DatabaseInputStreamVisitor_ActionStep_ParametersModel)
	ADD_PLUGIN(lbPluginActionStep_ParametersInternalFileWriterExtension, OutputStreamVisitor_ActionStep_ParametersModel)
	ADD_PLUGIN(lbPluginActionStep_ParametersXMLWriterExtension, XMLOutputStreamVisitor_ActionStep_ParametersModel)
	
// Nongenerated plugin definitions	
END_PLUGINS()

lbPluginModulelbDMFDataModelExtensions::lbPluginModulelbDMFDataModelExtensions() {
	_CL_VERBOSE << "lbPluginModulelbDMFDataModelExtensions::lbPluginModulelbDMFDataModelExtensions() called." LOG_
}

lbPluginModulelbDMFDataModelExtensions::~lbPluginModulelbDMFDataModelExtensions() {
	_CL_VERBOSE << "lbPluginModulelbDMFDataModelExtensions::~lbPluginModulelbDMFDataModelExtensions() called." LOG_
}

void LB_STDCALL lbPluginModulelbDMFDataModelExtensions::initialize() {
	char ptr[20] = "";
	sprintf(ptr, "%p", this);
	
	enumPlugins();
}

void LB_STDCALL lbPluginModulelbDMFDataModelExtensions::install() {

}

lbErrCodes LB_STDCALL lbPluginModulelbDMFDataModelExtensions::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModulelbDMFDataModelExtensions::setData(...) not implemented yet" LOG_

	if (uk != NULL) {
		_CL_VERBOSE << "Cloning object with " << uk->getRefCount() << " references." LOG_
	}
        
        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

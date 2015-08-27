/*...sLicense:0:*/
/*
 DMF Distributed Multiplatform Framework (the initial goal of this library)
 This file is part of lbDMF.
 Copyright (C) 2015  Lothar Behrens (lothar.behrens@lollisoft.de)
 
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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
 */
/*...e*/
/*...sHistory:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.1.2.2 $
 * $Name:  $
 * $Id: lbControlFactory.h,v 1.1.2.2 2015/08/27 14:15:20 lollisoft Exp $
 *
 * $Log: lbControlFactory.h,v $
 * Revision 1.1.2.2  2015/08/27 14:15:20  lollisoft
 * First basic implementation of a property dialog using a visitor factory.
 *
 * Revision 1.1.2.1  2015/07/12 10:05:50  lollisoft
 * Added new property dialog and panel implementations. A first step toward workflow enabled dialogs.
 *
 **************************************************************/
/*...e*/

#ifndef __LB_ControlFactory__
#define __LB_ControlFactory__

#include <iostream>


/** \brief First control factory trial.
 * This interface is an attempt to stop copy&paste code for creating controls used in a panel or form.
 * The base types are always the same and thus I start repeating code without a factory mechanism.
 */
class lb_I_ControlFactory : 
public lb_I_VisitableHelper,
public lb_I_EventHandler {
public:
	virtual void			LB_STDCALL setParent(lb_I_Window* parent) = 0;
	
	
	/** \brief Creates a specific control and returns a lb_I_Window instance.
	 * The instance represents the control within an encapsulation for my interfaces to
	 * hide internals. The window can return it's id for accessing purposes.
	 */
	virtual lb_I_Window*	LB_STDCALL createControl(const char* typeName, const char* name, const char* title) = 0;
};


/** \brief Provides a visitor to map built in types to factories for UI controls.
 * A concrete type may be a lbString class that implements a lb_I_String interface.
 * Using a visitor pattern helps to implement the mapping to a corresponding UI
 * control, that can be used to interact with the user.
 */
class lb_I_UIElementFactoryAspect :
public lb_I_Aspect
{
protected:
	lb_I_UIElementFactoryAspect() {}
	virtual ~lb_I_UIElementFactoryAspect() {}
	
public:
	/** \brief Start the operation.
	 *
	 * Start mapping concrete instances to corresponding controls using the given factory class. The parent
	 * window will contain the newly created controls.
	 */
	virtual bool LB_STDCALL begin(lb_I_ControlFactory* factory, lb_I_Form* parent) = 0;
	
	/** \brief End the operation.
	 *
	 * This closes the file and disables the operation.
	 */
	virtual void LB_STDCALL end() = 0;
};


class lbUIElementFactoryAspect : 
public lb_I_UIElementFactoryAspect {
public:
	lbUIElementFactoryAspect();
	virtual ~lbUIElementFactoryAspect();
	
	DECLARE_LB_UNKNOWN()
	
	/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
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
	void LB_STDCALL visit(lb_I_DatabaseOperation* pm) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_UIElementFactoryAspect*) { _CL_LOG << "visit(lb_I_UIElementFactoryAspect*)" LOG_ }
	void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }
	void LB_STDCALL visit(lb_I_Socket*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer*) { _CL_LOG << "visit(lb_I_Transfer*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Socket*)" LOG_ }
	void LB_STDCALL visit(lb_I_Transfer_DataObject*) { _CL_LOG << "visit(lb_I_Transfer_DataObject*)" LOG_ }
	void LB_STDCALL visit(lb_I_Thread*) { _CL_LOG << "visit(lb_I_Thread*)" LOG_ }
	void LB_STDCALL visit(lb_I_Mutex*) { _CL_LOG << "visit(lb_I_Mutex*)" LOG_ }
	void LB_STDCALL visit(lb_I_CriticalSection*) { _CL_LOG << "visit(lb_I_CriticalSection*)" LOG_ }
	void LB_STDCALL visit(lb_I_Lock*) { _CL_LOG << "visit(lb_I_Lock*)" LOG_ }
	
	
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
	void LB_STDCALL visit(lb_I_TestMethod*) { _CL_LOG << "visit(lb_I_TestMethod*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestFixture*) { _CL_LOG << "visit(lb_I_TestFixture*)" LOG_ }
	void LB_STDCALL visit(lb_I_CryptoStream*) { _CL_LOG << "visit(lb_I_CryptoStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchInterceptor*) { _CL_LOG << "visit(lb_I_DispatchInterceptor*)" LOG_ }
	void LB_STDCALL visit(lb_I_VisitableHelper*) { _CL_LOG << "visit(lb_I_VisitableHelper*)" LOG_ }
	
	/*...e*/
	
	void LB_STDCALL visit(lb_I_BinaryData*) { _CL_LOG << "visit(lb_I_BinaryData*)" LOG_ }
	
	void LB_STDCALL visit(lb_I_Streamable* pm) { _CL_LOG << "visit(lb_I_Streamable*)" LOG_ }
	void LB_STDCALL visit(lb_I_Application*) { _CL_LOG << "visit(lb_I_Application*)" LOG_ }
	void LB_STDCALL visit(lb_I_MetaApplication*) { _CL_LOG << "visit(lb_I_MetaApplication*)" LOG_ }
	void LB_STDCALL visit(lb_I_UserAccounts*) { _CL_LOG << "visit(lb_I_UserAccounts*)" LOG_ }
	void LB_STDCALL visit(lb_I_Applications*) { _CL_LOG << "visit(lb_I_Applications*)" LOG_ }
	void LB_STDCALL visit(lb_I_User_Applications*) { _CL_LOG << "visit(lb_I_User_Applications*)" LOG_ }
	void LB_STDCALL visit(lb_I_Formulars*) { _CL_LOG << "visit(lb_I_Formulars*)" LOG_ }
	void LB_STDCALL visit(lb_I_Formular_Fields*) { _CL_LOG << "visit(lb_I_Formular_Fields*)" LOG_ }
	void LB_STDCALL visit(lb_I_Column_Types*) { _CL_LOG << "visit(lb_I_Column_Types*)" LOG_ }
	void LB_STDCALL visit(lb_I_ApplicationParameter*) { _CL_LOG << "visit(lb_I_ApplicationParameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_FormularParameter*) { _CL_LOG << "visit(lb_I_FormularParameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Actions*) { _CL_LOG << "visit(lb_I_Actions*)" LOG_ }
	void LB_STDCALL visit(lb_I_Formular_Actions*) { _CL_LOG << "visit(lb_I_Formular_Actions*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action_Types*) { _CL_LOG << "visit(lb_I_Action_Types*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action_Steps*) { _CL_LOG << "visit(lb_I_Action_Steps*)" LOG_ }
	void LB_STDCALL visit(lb_I_Translations*) { _CL_LOG << "visit(lb_I_Translations*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileLocation*) { _CL_LOG << "visit(lb_I_FileLocation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DirLocation*) { _CL_LOG << "visit(lb_I_DirLocation*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBColumns*) { _CL_LOG << "visit(lb_I_DBColumns*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBTables*) { _CL_LOG << "visit(lb_I_DBTables*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBTableParameter*) { _CL_LOG << "visit(lb_I_DBTableParameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBPrimaryKeys*) { _CL_LOG << "visit(lb_I_DBPrimaryKeys*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBForeignKeys*) { _CL_LOG << "visit(lb_I_DBForeignKeys*)" LOG_ }
	
	void LB_STDCALL visit(lb_I_DBReportTextblock*) { _CL_LOG << "visit(lb_I_DBReportTextblock*)" LOG_ }
	void LB_STDCALL visit(lb_I_DBReportProperties*) { _CL_LOG << "visit(lb_I_DBReportProperties*)" LOG_ }
	
	void LB_STDCALL visit(lb_I_Reports*) { _CL_LOG << "visit(lb_I_Reports*)" LOG_ }
	void LB_STDCALL visit(lb_I_ReportParameters*) { _CL_LOG << "visit(lb_I_ReportParameters*)" LOG_ }
	void LB_STDCALL visit(lb_I_ReportElements*) { _CL_LOG << "visit(lb_I_ReportElements*)" LOG_ }
	void LB_STDCALL visit(lb_I_ReportElementTypes*) { _CL_LOG << "visit(lb_I_ReportElementTypes*)" LOG_ }
	void LB_STDCALL visit(lb_I_ReportTexts*) { _CL_LOG << "visit(lb_I_ReportTexts*)" LOG_ }
	void LB_STDCALL visit(lb_I_Applications_Formulars*) { _CL_LOG << "visit(lb_I_Applications_Formulars*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action_Step_Transitions*) { _CL_LOG << "visit(lb_I_Action_Step_Transitions*)" LOG_ }
	void LB_STDCALL visit(lb_I_ActionStep_Parameters*) { _CL_LOG << "visit(lb_I_ActionStep_Parameters*)" LOG_ }
	void LB_STDCALL visit(lb_I_Action_Parameters*) { _CL_LOG << "visit(lb_I_Action_Parameters*)" LOG_ }
	
	void LB_STDCALL visit(lb_I_Parameter*) { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }

	void LB_STDCALL visit(lb_I_Integer*);
	void LB_STDCALL visit(lb_I_Long*);
	void LB_STDCALL visit(lb_I_Boolean*);
	void LB_STDCALL visit(lb_I_String*);
	
	bool LB_STDCALL begin(lb_I_ControlFactory* factory, lb_I_Form* parent);
	void LB_STDCALL end();
	
	void LB_STDCALL setCurrentLabel(lb_I_String* label);
	void LB_STDCALL setCurrentName(lb_I_String* name);
	
	wxWindow* parentWindow;
	wxSizer* sizerMain;
	wxBoxSizer* sizerColumn;
	
	UAP(lb_I_String, currentLabel)
	UAP(lb_I_String, currentName)
};

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif


#endif // __LB_ControlFactory__



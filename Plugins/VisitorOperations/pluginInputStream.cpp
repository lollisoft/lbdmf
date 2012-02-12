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
 p-Mail: See my current address on http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=6
 
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

/*...slbInputStreamOpr:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbInputStreamOpr : 
	public lb_I_FileOperation {
public:
	lbInputStreamOpr();
	virtual ~lbInputStreamOpr();
	
	DECLARE_LB_UNKNOWN()

/*...sUnimplemented visitors:8:*/
	void LB_STDCALL visit(lb_I_SecurityProvider*) { _CL_VERBOSE << "visit(lb_I_SecurityProvider*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonHandler*) { _CL_LOG << "visit(lb_I_LogonHandler*)" LOG_ }
	void LB_STDCALL visit(lb_I_LogonPage*) { _CL_LOG << "visit(lb_I_LogonPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_AppSelectPage*) { _CL_LOG << "visit(lb_I_AppSelectPage*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUI*) { _CL_LOG << "visit(lb_I_GUI*)" LOG_ }
	void LB_STDCALL visit(lb_I_GUIApp*) { _CL_LOG << "visit(lb_I_GUIApp*)" LOG_ }
	void LB_STDCALL visit(lb_I_Frame*) { _CL_LOG << "visit(lb_I_Frame*)" LOG_ }
	void LB_STDCALL visit(lb_I_KeyBase*) { _CL_LOG << "visit(lb_I_KeyBase*)" LOG_ } 
	void LB_STDCALL visit(lb_I_String*); // { _CL_LOG << "visit(lb_I_String*)" LOG_ } 
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
		void LB_STDCALL visit(lb_I_Dispatcher*);// { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
	void LB_STDCALL visit(lb_I_InputStream*) { _CL_LOG << "visit(lb_I_InputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_OutputStream*) { _CL_LOG << "visit(lb_I_OutputStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_FileOperation*) { _CL_LOG << "visit(lb_I_FileOperation*)" LOG_ }
	void LB_STDCALL visit(lb_I_Locale*) { _CL_LOG << "visit(lb_I_Locale*)" LOG_ }
	void LB_STDCALL visit(lb_I_Parameter*); // { _CL_LOG << "visit(lb_I_Parameter*)" LOG_ }
	void LB_STDCALL visit(lb_I_Reference*) { _CL_LOG << "visit(lb_I_Reference*)" LOG_ }
	void LB_STDCALL visit(lb_I_Log*) { _CL_LOG << "visit(lb_I_Log*)" LOG_ }
	void LB_STDCALL visit(lb_I_Plugin*) { _CL_LOG << "visit(lb_I_Plugin*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginImpl*) { _CL_LOG << "visit(lb_I_PluginImpl*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginManager*) { _CL_LOG << "visit(lb_I_PluginManager*)" LOG_ }
	void LB_STDCALL visit(lb_I_PluginModule*) { _CL_LOG << "visit(lb_I_PluginModule*)" LOG_ }
	void LB_STDCALL visit(lb_I_wxFrame*) { _CL_LOG << "visit(lb_I_wxFrame*)" LOG_ }
	void LB_STDCALL visit(lb_I_Window*) { _CL_LOG << "visit(lb_I_Window*)" LOG_ }
	//void LB_STDCALL visit(lb_I_Action*) { _CL_LOG << "visit(lb_I_Action*)" LOG_ }
	//void LB_STDCALL visit(lb_I_DelegatedAction*) { _CL_LOG << "visit(lb_I_DelegatedAction*)" LOG_ }
	void LB_STDCALL visit(lb_I_Form*) { _CL_LOG << "visit(lb_I_Form*)" LOG_ }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { _CL_LOG << "visit(lb_I_MasterDetailFormDefinition*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { _CL_LOG << "visit(lb_I_DatabaseReport*)" LOG_ }
	void LB_STDCALL visit(lb_I_CodeGenerator*) { _CL_LOG << "visit(lb_I_CodeGenerator*)" LOG_ }
	void LB_STDCALL visit(lb_I_Boolean*); // { _CL_LOG << "visit(lb_I_Boolean*)" LOG_ }
	void LB_STDCALL visit(lb_I_DatabaseOperation* pm) { _CL_LOG << "visit(lb_I_DatabaseOperation*)" LOG_ }
	//void LB_STDCALL visit(lb_I_ParameterTable*) { _CL_LOG << "visit(lb_I_ParameterTable*)" LOG_ }
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
	void LB_STDCALL visit(lb_I_BinaryData*) { _CL_LOG << "visit(lb_I_BinaryData*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestMethod*) { _CL_LOG << "visit(lb_I_TestMethod*)" LOG_ }
	void LB_STDCALL visit(lb_I_TestFixture*) { _CL_LOG << "visit(lb_I_TestFixture*)" LOG_ }
	void LB_STDCALL visit(lb_I_CryptoStream*) { _CL_LOG << "visit(lb_I_CryptoStream*)" LOG_ }
	void LB_STDCALL visit(lb_I_DispatchInterceptor*) { _CL_LOG << "visit(lb_I_DispatchInterceptor*)" LOG_ }
	void LB_STDCALL visit(lb_I_VisitableHelper*) { _CL_LOG << "visit(lb_I_VisitableHelper*)" LOG_ }
	void LB_STDCALL visit(lb_I_ExtensionObject*) { _CL_LOG << "visit(lb_I_ExtensionObject*)" LOG_ }

/*...e*/

	void LB_STDCALL visit(lb_I_Streamable* pm);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);

	void LB_STDCALL visit(lb_I_ExtensibleObject* tableModule);

	void LB_STDCALL visit(lb_I_DocumentVersion*);

#ifdef UNFLEXIBLE_TOBE_REMOVED
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
#endif
	void LB_STDCALL visit(lb_I_FileLocation*);
	void LB_STDCALL visit(lb_I_DirLocation*);
	void LB_STDCALL visit(lb_I_DBColumns*);
	void LB_STDCALL visit(lb_I_DBTables*);
	void LB_STDCALL visit(lb_I_DBPrimaryKeys*);
	void LB_STDCALL visit(lb_I_DBForeignKeys*);


	bool LB_STDCALL begin(const char* file);
	bool LB_STDCALL begin(lb_I_Stream* stream);
	void LB_STDCALL end();

	void LB_STDCALL setContextNamespace(const char* _namespace);
	lb_I_Stream* LB_STDCALL getStream();

	UAP(lb_I_InputStream, iStream)
	UAP(lb_I_String, contextNamespace)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbInputStreamOpr)
	ADD_INTERFACE(lb_I_Aspect)
	ADD_INTERFACE(lb_I_FileOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbInputStreamOpr, lbInputStreamOpr)


/*...slbErrCodes LB_STDCALL lbInputStreamOpr\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbInputStreamOpr::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbInputStreamOpr::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbInputStreamOpr\58\\58\lbInputStreamOpr\40\\41\:0:*/
lbInputStreamOpr::lbInputStreamOpr() 
{
	_CL_LOG << "lbInputStreamOpr::lbInputStreamOpr() called." LOG_
	REQUEST(getModuleInstance(), lb_I_String, contextNamespace)
}
/*...e*/
/*...slbInputStreamOpr\58\\58\\126\lbInputStreamOpr\40\\41\:0:*/
lbInputStreamOpr::~lbInputStreamOpr() {
	_CL_LOG << "lbInputStreamOpr::~lbInputStreamOpr() called." LOG_
}
/*...e*/

bool LB_STDCALL lbInputStreamOpr::begin(const char* file) {
	REQUEST(getModuleInstance(), lb_I_InputStream, iStream)
	
	iStream->setFileName(file);
	bool ret = iStream->open();

	if (!ret) {
		_CL_LOG << "lbInputStreamOpr::begin(" << file << ") Error: Open file failed." LOG_
	}
	
	return ret;
}

bool LB_STDCALL lbInputStreamOpr::begin(lb_I_Stream* stream) {
	lbErrCodes err = ERR_NONE;
	if (stream != NULL) {
		_CL_LOG << "lbInputStreamOpr::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
		QI(stream, lb_I_InputStream, iStream)
		bool ret = iStream->open();

		if (!ret) {
			_CL_LOG << "lbInputStreamOpr::begin(lb_I_Stream* stream) Error: Open file failed." LOG_
		}
		
		return ret;
	} else {
		_CL_LOG << "lbInputStreamOpr::begin(lb_I_Stream* stream) Error: Uninitialized stream onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void lbInputStreamOpr::setContextNamespace(const char* _namespace) {
	_LOG << "lbInputStreamOpr::setContextNamespace('" << _namespace << "') called." LOG_
	*contextNamespace = _namespace;
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Streamable* pm) {
	if (iStream != NULL) {
		// Project manager has a private implementation. Use existing fromFile function.
		pm->load(iStream.getPtr());
	} else {
		_CL_LOG << "lbInputStreamOpr::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DocumentVersion* dver) {
	char* buffer = NULL;
	char* _Interface = NULL;
	char* _Functor = NULL;
	char* _Module = NULL;
	char* _ModuleVersion = NULL;
	char* _StoragePluginNamespace = NULL;
	char* _StoragePluginVersion = NULL;
	*iStream >> buffer;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	*s = buffer;
	free(buffer);
	
	
	if (*s == "DocumentVersion") {

		*iStream >> _Interface;
		*iStream >> _Functor;
		*iStream >> _Module;
		*iStream >> _ModuleVersion;
		*iStream >> _StoragePluginNamespace;
		*iStream >> _StoragePluginVersion;
		dver->setData(_Interface, _Functor, _Module, _ModuleVersion, _StoragePluginNamespace, _StoragePluginVersion);
	} else {
		dver->setInvalid();
		iStream->close();
		bool ret = iStream->open();
		if (!ret) {
			_LOG << "lbInputStreamOpr::visit(lb_I_DocumentVersion* dver) Failed to reopen file." LOG_
		}
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_String* s) {
	char* buffer = NULL;

	*iStream >> buffer;
		
	*s = buffer;
	free(buffer);
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Boolean* b) {
	bool _b = NULL;
	*iStream >> _b;
	b->setData(_b);
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Parameter* params) {
	int count = 0;
	*iStream >> count;
	
	UAP_REQUEST(getModuleInstance(), lb_I_String, paramname)

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, f)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)

	for (int i = 0; i < count; i++) {
		char* ParameterName = NULL;
		char* ParameterClassName = NULL;

		*iStream >> ParameterName;
		*iStream >> ParameterClassName;
		
		*paramname = ParameterName;
		
		if (strcmp(ParameterClassName, p->getClassName()) == 0) {
			visit(*&p);
			params->setUAPParameter(*&paramname, *&p);
		}
		else
		if (strcmp(ParameterClassName, f->getClassName()) == 0) {
			char* _f = NULL;
			*iStream >> _f;
			f->setData(_f);
			params->setUAPFileLocation(*&paramname, *&f);
		}
		else
		if (strcmp(ParameterClassName, s->getClassName()) == 0) {
			char* _s = NULL;
			*iStream >> _s;
			*s = _s;
			params->setUAPString(*&paramname, *&s);
		}
		else
		if (strcmp(ParameterClassName, l->getClassName()) == 0) {
			long _l;
			*iStream >> _l;
			l->setData(_l);
			params->setUAPLong(*&paramname, *&l);
		}
		else
		if (strcmp(ParameterClassName, b->getClassName()) == 0) {
			bool _b;
			*iStream >> _b;
			b->setData(_b);
			params->setUAPBoolean(*&paramname, *&b);
		} else {
			_CL_LOG << "lbInputStreamOpr::visit(lb_I_Parameter* params) Error: Not supported type '" << ParameterClassName << "'" LOG_
		}
	}
}


void LB_STDCALL lbInputStreamOpr::visit(lb_I_ExtensibleObject* tableModule) {
	UAP(lb_I_ExtensionObject, extension) 
	_LOG << "lbInputStreamOpr::visit(lb_I_ExtensibleObject* tableModule) using context namespace = " << contextNamespace->charrep() LOG_
	extension = tableModule->getExtension(*&contextNamespace);
	
	if (extension != NULL) {
		UAP(lb_I_Unknown, uk)
		QI(tableModule, lb_I_Unknown, uk)
		extension->setOwningObject(*&uk);

		UAP(lb_I_VisitorExtension, visitorExtension)
		QI(extension, lb_I_VisitorExtension, visitorExtension)
	
		if (visitorExtension != NULL) {
			_LOG << "Load an object from internal formatted file: " << tableModule->getClassName() << " with " << visitorExtension->getClassName() LOG_
			visitorExtension->setOperator(this);
			visitorExtension->execute();
		}
	}
}

#ifdef UNFLEXIBLE_TOBE_REMOVED
void LB_STDCALL lbInputStreamOpr::visit(lb_I_ActionStep_Parameters* actionstepparameters) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ActionID = NULL;
		char* Description = NULL;
		char* Name = NULL;
		char* Value = NULL;
		char* Interface = NULL;
		
		*iStream >> ID;
		*iStream >> ActionID;
		*iStream >> Description;
		*iStream >> Name;
		*iStream >> Value;
		*iStream >> Interface;
		
		actionstepparameters->addActionStepParameter(Description, Name, Value, Interface, ActionID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Action_Parameters* actionparameters) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ActionID = NULL;
		char* Description = NULL;
		char* Name = NULL;
		char* Value = NULL;
		char* Interface = NULL;
		
		*iStream >> ID;
		*iStream >> ActionID;
		*iStream >> Description;
		*iStream >> Name;
		*iStream >> Value;
		*iStream >> Interface;
		
		actionparameters->addActionParameter(Description, Name, Value, Interface, ActionID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Action_Step_Transitions* transition) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long SrcActionID = NULL;
		long DstActionID = NULL;
		char* Decision = NULL;
		char* Description = NULL;
		
		*iStream >> ID;
		*iStream >> SrcActionID;
		*iStream >> DstActionID;
		*iStream >> Decision;
		*iStream >> Description;
		
		transition->addTransition(Decision, SrcActionID, DstActionID, Description, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Applications_Formulars* applicationformulars) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ApplicationID = NULL;
		long FormularID = NULL;
		
		*iStream >> ID;
		*iStream >> ApplicationID;
		*iStream >> FormularID;
		
		applicationformulars->addRelation(ApplicationID, FormularID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Reports* reports) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		char* Name = NULL;
		char* Description = NULL;
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Description;
		
		reports->addReport(Name, Description, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_ReportParameters* reportparameters) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ReportID;
		char* Name = NULL;
		char* Value = NULL;
		
		*iStream >> ID;
		*iStream >> ReportID;
		*iStream >> Name;
		*iStream >> Value;
		
		reportparameters->addParameter(ReportID, Name, Value, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_ReportElements* reportelements) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ReportID;
		char* Name = NULL;
		long Typ;
		long x;
		long y;
		long w;
		long h;
		char* Description = NULL;
		
		*iStream >> ID;
		*iStream >> ReportID;
		*iStream >> Name;
		*iStream >> Typ;
		*iStream >> x;
		*iStream >> y;
		*iStream >> w;
		*iStream >> h;
		*iStream >> Description;
		
		reportelements->addElement(ReportID, Name, Typ, x, y, w, h, Description, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_ReportElementTypes* reportelementtypes) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		char* Name = NULL;
		char* Description = NULL;
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Description;
		
		reportelementtypes->addElementType(Name, Description, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_ReportTexts* reporttexts) {
	int count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long ID;
		long ElementID;
		long Line;
		char* Text = NULL;
		
		*iStream >> ID;
		*iStream >> ElementID;
		*iStream >> Line;
		*iStream >> Text;
		
		reporttexts->addText(ElementID, Line, Text , ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBReportTextblock*) {

}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBReportProperties*) {

}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_UserAccounts* users) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		// Load a user entry.
		int   UID;
		char* User = NULL;
		char* Pass = NULL;
		
		*iStream >> UID;
		*iStream >> User;
		*iStream >> Pass;
		
		users->addAccount(User, Pass, UID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Translations* trans) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	int   ID;
	char* Text = NULL;
	char* Translated = NULL;
	char* Language = NULL;

	for (int i = 0; i < count; i++) {
		// Load a user entry.
		
		*iStream >> ID;
		*iStream >> Text;
		*iStream >> Translated;
		*iStream >> Language;
		
		trans->addTranslation(Text, Translated, Language, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_FormularParameter* params) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Name = NULL;
		char* Value = NULL;
		long  FID;
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Value;
		*iStream >> FID;
		
		params->addParameter(Name, Value, FID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_ApplicationParameter* params) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Name = NULL;
		char* Value = NULL;
		long  AID;
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Value;
		*iStream >> AID;
		
		params->addParameter(Name, Value, AID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Actions* actions) {
	// Number of actions
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Name = NULL;
		char* Source = NULL;
		long  Typ;
		long  Target;
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Source;
		*iStream >> Typ;
		*iStream >> Target;
		
		actions->addAction(Name, Typ, Source, Target, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Action_Steps* action_steps) {
	// Number of actions
	int   count = 0;
	*iStream >> count;

	_LOG << "lbInputStreamOpr::visit(lb_I_Action_Steps* action_steps) called." LOG_

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Bezeichnung = NULL;
		char* What = NULL;
		long  ActionID;
		long  OrderNo;
		long  Type;

		*iStream >> ID;
		*iStream >> ActionID;
		*iStream >> OrderNo;
		*iStream >> Type;
		*iStream >> Bezeichnung;
		*iStream >> What;
		
		
		action_steps->addActionStep(Bezeichnung, ActionID, OrderNo, Type, What, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Action_Types* action_types) {
	// Number of actions
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Bezeichnung = NULL;
		char* Handler = NULL;
		char* Module = NULL;
		
		*iStream >> ID;
		*iStream >> Bezeichnung;
		*iStream >> Handler;
		*iStream >> Module;
		
		action_types->addActionTypes(Bezeichnung, Handler, Module, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Formular_Actions* formular_actions) {
	// Number of actions
	int   count = 0;
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		long   ID;
		char* Event = NULL;
		long  FormularID;
		long  ActionID;
		
		*iStream >> ID;
		*iStream >> FormularID;
		*iStream >> ActionID;
		*iStream >> Event;
		
		formular_actions->addFormularAction(FormularID , ActionID, Event, ID); 
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Formular_Fields* formularfields) {
	// Number of users
	int   count = 0;
	int FormularID;
	int ID;
	long isFK;
	char* Name = NULL;
	char* TableName = NULL;
	char* DBType = NULL;
	char* FKName = NULL;
	char* FKTable = NULL;
	char* EventName = NULL;
	
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> TableName;
		*iStream >> DBType;
		*iStream >> isFK;
		*iStream >> FKName;
		*iStream >> FKTable;
		*iStream >> FormularID;
		
		formularfields->addField(Name, TableName, DBType, (isFK == 1) ? 1 : 0, FKName, FKTable, FormularID, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Formulars* forms) {
	// Number of users
	int   count = 0;
	int FormularID;
	int AnwendungID;
	int Typ;
	char* FormularName = NULL;
	char* MenuName = NULL;
	char* MenuHilfe = NULL;
	char* EventName = NULL;
	char* ToolbarImage = NULL;
	
	*iStream >> count;
_LOG << "Read " << count << " formulars." LOG_
	for (int i = 0; i < count; i++) {
		
		*iStream >> FormularID;
		*iStream >> FormularName;
		*iStream >> MenuName;
		*iStream >> EventName;
		*iStream >> MenuHilfe;
		*iStream >> AnwendungID;
		*iStream >> Typ;
		*iStream >> ToolbarImage;
		
		forms->addFormular(FormularName, ToolbarImage, MenuName, EventName, MenuHilfe, AnwendungID, Typ, FormularID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Column_Types* columntypes) {
	// Number of users
	int   count = 0;
	long readonly;
	char* TableName = NULL;
	char* Name = NULL;
	char* SpecialColumn = NULL;
	char* ControlType = NULL;
	
	*iStream >> count;

	for (int i = 0; i < count; i++) {
		
		*iStream >> TableName;
		*iStream >> Name;
		*iStream >> SpecialColumn;
		*iStream >> ControlType;
		*iStream >> readonly;
		
		columntypes->addType(TableName, Name, SpecialColumn, ControlType, (readonly == 1) ? true : false);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Applications* app) {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  ID = -1;
		char* Name = NULL;
		char* Titel = NULL;
		char* ModuleName = NULL;
		char* Functor = NULL;
		char* Interface = NULL;
	
		*iStream >> ID;
		*iStream >> Name;
		*iStream >> Titel;
		*iStream >> ModuleName;
		*iStream >> Functor;
		*iStream >> Interface;
												
		app->addApplication(Name, Titel, ModuleName, Functor, Interface, ID);

		// Leaky !
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_User_Applications* user_app) {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  ID = -1;
		long  UserID = -1;
		long  AppID = -1;
	
		*iStream >> ID;
		*iStream >> UserID;
		*iStream >> AppID;
												
		user_app->addRelation(AppID, UserID, ID);
	}
}
#endif
void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBForeignKeys* fkeys) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	int   ID;
	int KeySequence;
	int UpdateRule;
	int DeleteRule;

	char* PKTableCatalog = NULL;
	char* PKTableSchema = NULL;
	char* PKTableName = NULL;
	char* PKColumnName = NULL;

	char* FKTableCatalog = NULL;
	char* FKTableSchema = NULL;
	char* FKTableName = NULL;
	char* FKColumnName = NULL;


	for (int i = 0; i < count; i++) {
		// Load a user entry.
		
		*iStream >> ID;
		*iStream >> PKTableCatalog;
		*iStream >> PKTableSchema;
		*iStream >> PKTableName;
		*iStream >> PKColumnName;

		*iStream >> FKTableCatalog;
		*iStream >> FKTableSchema;
		*iStream >> FKTableName;
		*iStream >> FKColumnName;

		*iStream >> KeySequence;
		*iStream >> UpdateRule;
		*iStream >> DeleteRule;
		
		fkeys->addForeignKey(	PKTableCatalog, PKTableSchema, PKTableName, PKColumnName,
								FKTableCatalog, FKTableSchema, FKTableName, FKColumnName,
								KeySequence, UpdateRule, DeleteRule, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBPrimaryKeys* pkeys) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	long ID;
	long KeySequence;

	char* TableCatalog = NULL;
	char* TableSchema = NULL;
	char* TableName = NULL;
	char* ColumnName = NULL;
	char* ColumnName_V2 = NULL;


	for (int i = 0; i < count; i++) {
		// Load a user entry.
		
		*iStream >> ID;
		*iStream >> TableCatalog;
		*iStream >> TableSchema;
		*iStream >> TableName;
		*iStream >> ColumnName;
		*iStream >> KeySequence;
		*iStream >> ColumnName_V2;
		
		pkeys->addPrimaryKey(TableCatalog, TableSchema, TableName, ColumnName, KeySequence, ColumnName_V2, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBColumns* columns) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	long   ID;
	char* name = NULL;
	char* comment = NULL;
	char* typ = NULL;
	int   len;
	int   isNullable;
	char* PKTable = NULL;
	char* PKField = NULL;
	char* tablename = NULL;

	for (int i = 0; i < count; i++) {
		// Load a user entry.
		
		*iStream >> ID;
		*iStream >> name;
		*iStream >> comment;
		*iStream >> typ;
		*iStream >> len;
		*iStream >> PKTable;
		*iStream >> PKField;
		*iStream >> tablename;
		*iStream >> isNullable;
		
		columns->addColumn(name, comment, typ, len, (isNullable == 1) ? true : false, PKTable, PKField, tablename, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DBTables* tables) {
	// Number of users
	int   count = 0;
	*iStream >> count;

	int   ID;
	char* catalog = NULL;
	char* schema = NULL;
	char* name = NULL;
	char* type = NULL;
	char* remarks = NULL;

	for (int i = 0; i < count; i++) {
		// Load a user entry.
		
		*iStream >> ID;
		*iStream >> catalog;
		*iStream >> schema;
		*iStream >> name;
		*iStream >> type;
		*iStream >> remarks;
		
		tables->addTable(catalog, schema, name, type, remarks, ID);
	}
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_FileLocation* fileloc) {
		char*  f = NULL;
		
		*iStream >> f;
		
		fileloc->setData(f); 
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_DirLocation* fileloc) {
		char*  f = NULL;
		
		*iStream >> f;
		
		fileloc->setData(f); 
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_MetaApplication* app) {
	_CL_LOG << "lbInputStreamOpr::visit(lb_I_MetaApplication* app): Read data of meta application." LOG_

	char* temp = NULL;
	bool  b;
	int   count = 0;
	
	*iStream >> b;
	app->setAutorefreshData(b);

	*iStream >> temp;
	app->setApplicationName(temp);
	
	*iStream >> temp;
	app->setUserName(temp);
	
	_LOG << "Metaapplication has got the username: '" << temp << "'." LOG_
	
	*iStream >> b;
	app->setAutoload(b);
	
	*iStream >> b;
	app->setAutoselect(b);

	*iStream >> b;
	app->setGUIMaximized(b);
	
	*iStream >> temp;
	app->setDirLocation(temp);
	
	*iStream >> b;
	if (b) app->setPropertyPaneLayoutFloating();
	
	*iStream >> b;
	if (b) app->setPropertyPaneLayoutLeft();
	
	*iStream >> b;
	if (b) app->setLoadFromDatabase(true);
	//else app->setLoadFromDatabase(false);

	*iStream >> temp;
	app->setApplicationDatabaseBackend(temp);

	*iStream >> temp;
	app->setSystemDatabaseBackend(temp);

	*iStream >> b;
	if (b) app->useApplicationDatabaseBackend(true);
	else app->useApplicationDatabaseBackend(false);

	*iStream >> b;
	if (b) app->useSystemDatabaseBackend(true);
	else app->useSystemDatabaseBackend(false);
	_CL_LOG << "lbInputStreamOpr::visit(lb_I_MetaApplication* app): Read data of meta application done." LOG_
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Dispatcher* disp) {
	_CL_LOG << "lbInputStreamOpr::visit(): Read data of dispatcher." LOG_
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	char* temp = NULL;
	*iStream >> temp;
	*s = temp;
	disp->setInterceptorDefinitions(*&s);	
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Application*) {
	_CL_LOG << "lbInputStreamOpr::visit(): Read data of application." LOG_
	lbErrCodes err = ERR_NONE;
	
	// Get the document via the active document from meta application.
	// This way no extra interface is needed (container with named elements)
	
	UAP_REQUEST(getModuleInstance(), lb_I_MetaApplication, meta)
	UAP_REQUEST(getModuleInstance(), lb_I_String, param)
	UAP_REQUEST(getModuleInstance(), lb_I_String, StorageInterface)
	UAP_REQUEST(getModuleInstance(), lb_I_String, StorageNamespace)
	
	UAP_REQUEST(getModuleInstance(), lb_I_PluginManager, PM)
	UAP(lb_I_Plugin, pl)
	UAP(lb_I_Unknown, ukPl)
	
	UAP(lb_I_Unknown, ukDoc)
	UAP(lb_I_Parameter, document)
	
	ukDoc = meta->getActiveDocument();
	if (ukDoc == NULL) {
		_LOG << "Error: Expected a document as 'active document' here!" LOG_
		return;
	}
	
	QI(ukDoc, lb_I_Parameter, document)
	
	if (document != NULL) {
		*param = "StorageDelegateNamespace";
		document->getUAPString(*&param, *&StorageNamespace);

		// Here would be the point to detect, if there is any version information in the document.
		// If so, the proper plugin should be selected by appending the version information to the namespace
		
		UAP_REQUEST(getModuleInstance(), lb_I_DocumentVersion, DocumentVersion)
		
		// This function should revert to begin if no document version was found.
		visit(*&DocumentVersion);
		
		if (DocumentVersion->isValidVersion()) {
			// Read out the version information and create a corresponding namespace to get the correct implementation.
			
			UAP(lb_I_String, v)
			v = DocumentVersion->getStoragePluginVersion();
			
			*StorageNamespace += "_";
			*StorageNamespace += v->charrep();
			_LOG << "lbInputStreamOpr::visit(lb_I_Application*) is setting custom version to " << StorageNamespace->charrep() LOG_
		} else {
			_LOG << "lbInputStreamOpr::visit(lb_I_Application*) is an old version of " << StorageNamespace->charrep() LOG_
		}
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
			mystream->load(*&iStream);
		}
	}
}

void LB_STDCALL lbInputStreamOpr::end() {

}

lb_I_Stream* LB_STDCALL lbInputStreamOpr::getStream() {
	lbErrCodes err = ERR_NONE;
	
        UAP(lb_I_Stream, s)
        QI(iStream, lb_I_Stream, s)
        s++;

        return s.getPtr();
}
/*...e*/

/*...sclass lbPluginInputStream implementation:0:*/
/*...slbPluginInputStream:0:*/
class lbPluginInputStream : public lb_I_PluginImpl {
public:
	lbPluginInputStream();
	
	virtual ~lbPluginInputStream();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();
/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace);
/*...e*/

	DECLARE_LB_UNKNOWN()

private:
	UAP(lb_I_Unknown, impl)
	UAP(lb_I_String, pluginNamespace)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginInputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginInputStream, lbPluginInputStream)

/*...slbErrCodes LB_STDCALL lbPluginInputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginInputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginInputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

void LB_STDCALL lbPluginInputStream::setNamespace(const char* _namespace) {
	*pluginNamespace = _namespace;
}

lbPluginInputStream::lbPluginInputStream() {
	_CL_VERBOSE << "lbPluginInputStream::lbPluginInputStream() called.\n" LOG_
	REQUEST(getModuleInstance(), lb_I_String, pluginNamespace)
	*pluginNamespace = "Plugin namespace was not set.";
}

lbPluginInputStream::~lbPluginInputStream() {
	_CL_VERBOSE << "lbPluginInputStream::~lbPluginInputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginInputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginInputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginInputStream::initialize() {
}
	
bool LB_STDCALL lbPluginInputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginInputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginInputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbInputStreamOpr* InputStream = new lbInputStreamOpr();
		
		InputStream->setContextNamespace(pluginNamespace->charrep());
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginInputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginInputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbInputStreamOpr* InputStream = new lbInputStreamOpr();
		
		InputStream->setContextNamespace(pluginNamespace->charrep());

		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginInputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/

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

/*...slbOutputStream:0:*/
/** \brief Implementation of input stream.
 *
 * Implements lb_I_Aspect to allow getting calls from objects, I support.
 * Implements lb_I_FileOperation to specify, that this operation has to do
 * with files. Here loading from file.
 */
class lbOutputStream : 
	public lb_I_FileOperation {
public:
	lbOutputStream();
	virtual ~lbOutputStream();
	
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
		void LB_STDCALL visit(lb_I_Dispatcher*); // { _CL_LOG << "visit(lb_I_Dispatcher*)" LOG_ }
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
	void LB_STDCALL visit(lb_I_Transfer_Data*) { _CL_LOG << "visit(lb_I_Transfer_Data*)" LOG_ }
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

/*...e*/
	
	void LB_STDCALL visit(lb_I_Streamable* pm);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);
	
	void LB_STDCALL visit(lb_I_TableModule* tableModule);

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

	/** \brief Start save operation.
	 *
	 * This initializes an input file stream with a given name.
	 * For each object, you will save, call their accept() member function.
	 */
	bool LB_STDCALL begin(const char* file);

	bool LB_STDCALL begin(lb_I_Stream* stream);

	
	/** \brief End save operation.
	 *
	 * This closes the file and thus disables visit members.
	 */
	void LB_STDCALL end();
		
	lb_I_Stream* LB_STDCALL getStream();
	
	UAP(lb_I_OutputStream, oStream)
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbOutputStream)
	ADD_INTERFACE(lb_I_Aspect)
	ADD_INTERFACE(lb_I_FileOperation)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbOutputStream, lbOutputStream)


/*...slbErrCodes LB_STDCALL lbOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbOutputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbOutputStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbOutputStream\58\\58\lbOutputStream\40\\41\:0:*/
lbOutputStream::lbOutputStream() 
{
	_CL_LOG << "lbOutputStream::lbOutputStream() called." LOG_
	
}
/*...e*/
/*...slbOutputStream\58\\58\\126\lbOutputStream\40\\41\:0:*/
lbOutputStream::~lbOutputStream() {
	_CL_LOG << "lbOutputStream::~lbOutputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbOutputStream::begin(const char* file) {
	if (oStream == NULL) { 
		REQUEST(getModuleInstance(), lb_I_OutputStream, oStream)
		
		oStream->setFileName(file);
		bool ret = oStream->open();

		if (!ret) {
			_CL_LOG << "lbOutputStream::begin(" << file << ") Error: Open file failed." LOG_
		}

		return ret;
	} else {
		_CL_LOG << "Error: lbOutputStream::begin(...) called prior!" LOG_
	}
	
	return false;
}

bool LB_STDCALL lbOutputStream::begin(lb_I_Stream* stream) {
	lbErrCodes err = ERR_NONE;
	if (stream != NULL) {
		_CL_LOG << "lbOutputStream::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
		QI(stream, lb_I_OutputStream, oStream)
		bool ret = oStream->open();

		if (!ret) {
			_CL_LOG << "lbOutputStream::begin(lb_I_Stream* stream) Error: Open file failed." LOG_
		}
		
		return ret;
	} else {
		_CL_LOG << "lbOutputStream::begin(lb_I_Stream* stream) Error: Uninitialized stream onject (NULL pointer)!" LOG_
	}
	
	return false;
}

void LB_STDCALL lbOutputStream::visit(lb_I_Streamable* pm) {
	if (oStream != NULL) {
		// lb_I_Streamable is generic and selfsaving.
		pm->save(oStream.getPtr());
	} else {
		_CL_LOG << "lbOutputStream::visit(lb_I_ProjectManager* pm) Error: No input stream available. Could not read from stream!" LOG_
	}

}

void LB_STDCALL lbOutputStream::visit(lb_I_Boolean* b) {
	*oStream << b->getData();
}

void LB_STDCALL lbOutputStream::visit(lb_I_String* s) {
	*oStream << s->charrep();
}

void LB_STDCALL lbOutputStream::visit(lb_I_Parameter* params) {
	int count;

	count = params->Count();
	*oStream << count;

	UAP(lb_I_Container, container)
	
	container = params->getParameterList();
	
	if (count == 0) return;
	
	container->finishIteration();

	UAP_REQUEST(getModuleInstance(), lb_I_FileLocation, f)
	UAP_REQUEST(getModuleInstance(), lb_I_String, s)
	UAP_REQUEST(getModuleInstance(), lb_I_Long, l)
	UAP_REQUEST(getModuleInstance(), lb_I_Boolean, b)
	UAP_REQUEST(getModuleInstance(), lb_I_Parameter, p)
	
	while (container->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_KeyBase, key)
		uk = container->nextElement();
		key = container->currentKey();
		
		*oStream << key->charrep();
		*oStream << uk->getClassName();

		_LOG << "Writing object name '" << key->charrep() << "' of type '" << uk->getClassName() << "'." LOG_ 

		if (strcmp(uk->getClassName(), p->getClassName()) == 0) {
			p->setData(*&uk);
			visit(*&p);
		}
		if (strcmp(uk->getClassName(), f->getClassName()) == 0) {
			f->setData(*&uk);
			visit(*&f);
		}
		if (strcmp(uk->getClassName(), s->getClassName()) == 0) {
			s->setData(*&uk);
			visit(*&s);
		}
		if (strcmp(uk->getClassName(), l->getClassName()) == 0) {
			l->setData(*&uk);
			visit(*&l);
		}
		if (strcmp(uk->getClassName(), b->getClassName()) == 0) {
			b ->setData(*&uk);
			visit(*&b);
		}
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_TableModule* tableModule) {
	tableModule->setOperator(*&oStream);
	tableModule->ExecuteOperation("WriteToFile");
}

#ifdef UNFLEXIBLE_TOBE_REMOVED
void LB_STDCALL lbOutputStream::visit(lb_I_ActionStep_Parameters* actionstepparameters) {
	int count;
	
	count = actionstepparameters->getActionStepParametersCount();
	*oStream << count;

	actionstepparameters->finishActionStepParameterIteration();
	
	while (actionstepparameters->hasMoreActionStepParameters()) {
		actionstepparameters->setNextActionStepParameter();
		
		*oStream << actionstepparameters->getActionStepParameterID();
		*oStream << actionstepparameters->getActionStepParameterActionID();
		
		*oStream << actionstepparameters->getActionStepParameterDescription();
		*oStream << actionstepparameters->getActionStepParameterName();
		*oStream << actionstepparameters->getActionStepParameterValue();
		*oStream << actionstepparameters->getActionStepParameterInterface();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Action_Parameters* actionparameters) {
	int count;
	
	count = actionparameters->getActionParametersCount();
	*oStream << count;
	
	actionparameters->finishActionParameterIteration();
	
	while (actionparameters->hasMoreActionParameters()) {
		actionparameters->setNextActionParameter();
		
		*oStream << actionparameters->getActionParameterID();
		*oStream << actionparameters->getActionParameterActionID();
		
		*oStream << actionparameters->getActionParameterDescription();
		*oStream << actionparameters->getActionParameterName();
		*oStream << actionparameters->getActionParameterValue();
		*oStream << actionparameters->getActionParameterInterface();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Applications_Formulars* applicationformulars) {
	int count;

	count = applicationformulars->getRelationCount();
	*oStream << count;
	
	applicationformulars->finishRelationIteration();
	
	while (applicationformulars->hasMoreRelations()) {
		applicationformulars->setNextRelation();
		
		*oStream << applicationformulars->getID();
		*oStream << applicationformulars->getApplicationID();
		*oStream << applicationformulars->getFormularID();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Action_Step_Transitions* transition) {
	int count;

	count = transition->getActionStepTransitionsCount();
	*oStream << count;
	
	transition->finishActionStepTransitionIteration();
	
	while (transition->hasMoreActionStepTransitions()) {
		transition->setNextActionStepTransition();
		
		*oStream << transition->getActionStepTransitionID();
		*oStream << transition->getActionStepTransitionSrcActionID();
		*oStream << transition->getActionStepTransitionDstActionID();
		*oStream << transition->getActionStepTransitionDecision();
		*oStream << transition->getActionStepTransitionDescription();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Reports* reports) {
	int count;

	count = reports->getReportCount();
	*oStream << count;
	
	reports->finishReportIteration();
	
	while (reports->hasMoreReports()) {
		reports->setNextReport();
		
		*oStream << reports->getReportID();
		*oStream << reports->getReportName();
		*oStream << reports->getReportDescription();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_ReportParameters* reportparameters) {
	int count;

	count = reportparameters->getParameterCount();
	*oStream << count;
	
	reportparameters->finishParameterIteration();
	
	while (reportparameters->hasMoreParameters()) {
		reportparameters->setNextParameter();
		
		*oStream << reportparameters->getParameterID();
		*oStream << reportparameters->getReportID();
		*oStream << reportparameters->getParameterName();
		*oStream << reportparameters->getParameterValue();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_ReportElements* reportelements) {
	int count;

	count = reportelements->getElementCount();
	*oStream << count;
	
	reportelements->finishElementIteration();
	
	while (reportelements->hasMoreElements()) {
		reportelements->setNextElement();
		
		*oStream << reportelements->getElementID();
		*oStream << reportelements->getElementReportID();
		*oStream << reportelements->getElementName();
		*oStream << reportelements->getElementTyp();
		*oStream << reportelements->getElementX();
		*oStream << reportelements->getElementY();
		*oStream << reportelements->getElementW();
		*oStream << reportelements->getElementH();
		*oStream << reportelements->getElementDescription();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_ReportElementTypes* reportelementtypes) {
	int count;

	count = reportelementtypes->getElementTypeCount();
	*oStream << count;
	
	reportelementtypes->finishElementTypeIteration();
	
	while (reportelementtypes->hasMoreElementTypes()) {
		reportelementtypes->setNextElementType();
		
		*oStream << reportelementtypes->getElementID();
		*oStream << reportelementtypes->getElementName();
		*oStream << reportelementtypes->getElementDescription();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_ReportTexts* reporttexts) {
	int count;

	count = reporttexts->getTextCount();
	*oStream << count;
	
	reporttexts->finishTextIteration();
	
	while (reporttexts->hasMoreTexts()) {
		reporttexts->setNextText();
		
		*oStream << reporttexts->getID();
		*oStream << reporttexts->getElementID();
		*oStream << reporttexts->getLine();
		*oStream << reporttexts->getText();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_DBReportTextblock*) {

}

void LB_STDCALL lbOutputStream::visit(lb_I_DBReportProperties*) {

}

void LB_STDCALL lbOutputStream::visit(lb_I_UserAccounts* users) {
	int count;

	count = users->getUserCount();
	*oStream << count;
	
	users->finishUserIteration();
	
	while (users->hasMoreUsers()) {
		users->setNextUser();
		
		*oStream << users->getUserID();
		*oStream << users->getUserName();
		*oStream << users->getUserPassword();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Translations* trans) {
	int count;

	count = trans->getTranslationsCount();
	*oStream << count;
	
	trans->finishTranslationIteration();
	
	while (trans->hasMoreTranslations()) {
		trans->setNextTranslation();
		
		*oStream << trans->getTranslationID();
		*oStream << trans->getTranslationText();
		*oStream << trans->getTranslationTranslated();
		*oStream << trans->getTranslationLanguage();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_FormularParameter* forms) {
	int count;

	count = forms->getParameterCount();
	*oStream << count;
	
	forms->finishParameterIteration();
	
	while (forms->hasMoreParameters()) {
		forms->setNextParameter();
		
		*oStream << forms->getParameterID();
		*oStream << forms->getParameterName();
		*oStream << forms->getParameterValue();
		*oStream << forms->getFormularID();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Actions* actions) {
	int count;

	count = actions->getActionCount();
	*oStream << count;
	
	actions->finishActionIteration();
	
	while (actions->hasMoreActions()) {
		actions->setNextAction();
		
		*oStream << actions->getActionID();
		*oStream << actions->getActionName();
		*oStream << actions->getActionSource();
		*oStream << actions->getActionTyp();
		*oStream << actions->getActionTarget();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Action_Steps* action_steps) {
	int count;

	count = action_steps->getActionStepCount();
	*oStream << count;

	_LOG << "lbOutputStream::visit(lb_I_Action_Steps* action_steps) called." LOG_

	action_steps->finishActionStepIteration();
	
	while (action_steps->hasMoreActionSteps()) {
		action_steps->setNextActionStep();

		_LOG << "lbOutputStream::visit(lb_I_Action_Steps* action_steps) writes an entry." LOG_
		
		*oStream << action_steps->getActionStepID();
		*oStream << action_steps->getActionStepActionID();
		*oStream << action_steps->getActionStepOrderNo();
		*oStream << action_steps->getActionStepType();
		*oStream << action_steps->getActionStepBezeichnung();
		*oStream << action_steps->getActionStepWhat();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Action_Types* action_types) {
	int count;

	count = action_types->getActionTypesCount();
	*oStream << count;
	
	action_types->finishActionTypeIteration();
	
	while (action_types->hasMoreActionTypes()) {
		action_types->setNextActionType();
		
		*oStream << action_types->getActionTypeID();
		*oStream << action_types->getActionTypeBezeichnung();
		*oStream << action_types->getActionTypeHandler();
		*oStream << action_types->getActionTypeModule();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Formular_Actions* formular_actions) {
	int count;

	count = formular_actions->getFormularActionsCount();
	*oStream << count;
	
	formular_actions->finishFormularActionIteration();
	
	while (formular_actions->hasMoreFormularActions()) {
		formular_actions->setNextFormularAction();
		
		*oStream << formular_actions->getFormularActionID();
		*oStream << formular_actions->getFormularActionFormularID();
		*oStream << formular_actions->getFormularActionActionID();
		*oStream << formular_actions->getFormularActionEvent();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_ApplicationParameter* apps) {
	int count;

	count = apps->getParameterCount();
	*oStream << count;
	
	apps->finishParameterIteration();
	
	while (apps->hasMoreParameters()) {
		apps->setNextParameter();
		
		*oStream << apps->getParameterID();
		*oStream << apps->getParameterName();
		*oStream << apps->getParameterValue();
		*oStream << apps->getApplicationID();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Formulars* forms) {
	int count;

	count = forms->getFormularCount();
	*oStream << count;
	
	forms->finishFormularIteration();
	
	while (forms->hasMoreFormulars()) {
		forms->setNextFormular();
		
		*oStream << forms->getFormularID();
		*oStream << forms->getName();
		*oStream << forms->getMenuName();
		*oStream << forms->getEventName();
		*oStream << forms->getMenuHelp();
		*oStream << forms->getApplicationID();
		*oStream << forms->getTyp();
		*oStream << forms->getToolbarImage();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Formular_Fields* formularfields) {
	int count;

	count = formularfields->getFieldCount();
	*oStream << count;
	
	formularfields->finishFieldsIteration();
	
	while (formularfields->hasMoreFields()) {
		formularfields->setNextField();
		
		*oStream << formularfields->getID();
		*oStream << formularfields->getName();
		*oStream << formularfields->getTableName();
		*oStream << formularfields->getDBType();
		if (formularfields->isFK())
			*oStream << (long) 1;
		else
			*oStream << (long) 0;
		*oStream << formularfields->getFKName();
		*oStream << formularfields->getFKTable();
		*oStream << formularfields->getFormularID();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Column_Types* columntypes) {
	int count;

	count = columntypes->getTypeCount();
	*oStream << count;
	
	columntypes->finishTypeIteration();
	
	while (columntypes->hasMoreTypes()) {
		columntypes->setNextType();
		
		*oStream << columntypes->getTableName();
		*oStream << columntypes->getName();
		*oStream << columntypes->getSpecialColumn();
		*oStream << columntypes->getControlType();
		if (columntypes->getReadonly() == true) 
			*oStream << (long) 1;
		else
			*oStream << (long) 0;
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Applications* app) {
	int count;

	count = app->getApplicationCount();
	*oStream << count;
	
	app->finishApplicationIteration();
	
	while (app->hasMoreApplications()) {
		app->setNextApplication();
		
		_CL_LOG << "Save application: '" << app->getApplicationName() << 
		"', title: '" << app->getApplicationTitle() <<
		"', module: '" << app->getApplicationModule() <<
		"', functor: '" << app->getApplicationFunctor() <<
		"', interface: '" << app->getApplicationInterface()
		  LOG_
		
		*oStream << app->getApplicationID();
		*oStream << app->getApplicationName();
		*oStream << app->getApplicationTitle();
		*oStream << app->getApplicationModule();
		*oStream << app->getApplicationFunctor();
		*oStream << app->getApplicationInterface();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_User_Applications* app) {
	int count;

	count = app->getRelationCount();
	*oStream << count;
	
	app->finishRelationIteration();
	
	while (app->hasMoreRelations()) {
		app->setNextRelation();
		
		*oStream << app->getID();
		*oStream << app->getUserID();
		*oStream << app->getApplicationID();
	}
}
#endif

void LB_STDCALL lbOutputStream::visit(lb_I_DBColumns* columns) {
	int count;

	count = columns->getColumnCount();
	*oStream << count;
	
	columns->finishColumnIteration();
	
	while (columns->hasMoreColumns()) {
		columns->setNextColumn();
		
		*oStream << columns->getColumnID();
		*oStream << columns->getColumnName();
		*oStream << columns->getColumnComment();
		*oStream << columns->getColumnTyp();
		*oStream << columns->getColumnLen();
		*oStream << columns->getColumnPKTable();
		*oStream << columns->getColumnPKField();
		*oStream << columns->getColumnTableName();
		(columns->isNullable() == true) ? *oStream << 1 : *oStream << 0;
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_DBTables* tables) {
	int count;

	count = tables->getTableCount();
	*oStream << count;
	
	tables->finishTableIteration();
	
	while (tables->hasMoreTables()) {
		tables->setNextTable();
		
		*oStream << tables->getTableID();
		*oStream << tables->getTableCatalog();
		*oStream << tables->getTableSchema();
		*oStream << tables->getTableName();
		*oStream << tables->getTableType();
		*oStream << tables->getTableRemarks();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_DBForeignKeys* fkeys) {
	int count;

	count = fkeys->getForeignKeyCount();
	*oStream << count;
	
	fkeys->finishForeignKeyIteration();
	
	while (fkeys->hasMoreForeignKeys()) {
		fkeys->setNextForeignKey();
		
		*oStream << fkeys->getForeignKeyID();
		
		*oStream << fkeys->getForeignKeyPKTableCatalog();
		*oStream << fkeys->getForeignKeyPKTableSchema();
		*oStream << fkeys->getForeignKeyPKTableName();
		*oStream << fkeys->getForeignKeyPKTableColumnName();
		
		*oStream << fkeys->getForeignKeyFKTableCatalog();
		*oStream << fkeys->getForeignKeyFKTableSchema();
		*oStream << fkeys->getForeignKeyFKTableName();
		*oStream << fkeys->getForeignKeyFKTableColumnName();
		
		*oStream << fkeys->getForeignKeyKeySequence();
		*oStream << fkeys->getForeignKeyUpdateRule();
		*oStream << fkeys->getForeignKeyDeleteRule();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_DBPrimaryKeys* pkeys) {
	int count;

	count = pkeys->getPrimaryKeyCount();
	*oStream << count;
	
	pkeys->finishPrimaryKeyIteration();
	
	while (pkeys->hasMorePrimaryKeys()) {
		pkeys->setNextPrimaryKey();
		
		*oStream << pkeys->getPrimaryKeyID();
		*oStream << pkeys->getPrimaryKeyTableCatalog();
		*oStream << pkeys->getPrimaryKeyTableSchema();
		*oStream << pkeys->getPrimaryKeyTableName();
		*oStream << pkeys->getPrimaryKeyColumnName();
		*oStream << pkeys->getPrimaryKeySequence();
		*oStream << pkeys->getPrimaryKeyColumnName_ODBC_V_2();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_FileLocation* fileloc) {
		*oStream << fileloc->charrep();
}

void LB_STDCALL lbOutputStream::visit(lb_I_DirLocation* fileloc) {
		*oStream << fileloc->charrep();
}

void LB_STDCALL lbOutputStream::visit(lb_I_MetaApplication* app) {
	_LOG << "Save a lb_I_MetaApplication object." LOG_

	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	bool  b;
	int count;

	b = app->getAutorefreshData();
	*oStream << b;

	app->getApplicationName(&temp);
	*oStream << temp->charrep();

	app->getUserName(&temp);
	*oStream << temp->charrep();

	b = app->getAutoload();
	*oStream << b;

	b = app->getAutoselect();
	*oStream << b;

	b = app->getGUIMaximized();
	*oStream << b;
	
	*oStream << app->getDirLocation();
	
	*oStream << app->isPropertyPaneLayoutFloating();
	
	*oStream << app->isPropertyPaneLayoutLeft();

	*oStream << app->getLoadFromDatabase();
	
	*oStream << app->getApplicationDatabaseBackend();

	*oStream << app->getSystemDatabaseBackend();

	*oStream << app->usingApplicationDatabaseBackend();

	*oStream << app->usingSystemDatabaseBackend();

}

void LB_STDCALL lbOutputStream::visit(lb_I_Dispatcher* disp) {
	UAP_REQUEST(getModuleInstance(), lb_I_String, temp)
	temp = disp->getInterceptorDefinitions();
	*oStream << temp->charrep();
}

void LB_STDCALL lbOutputStream::visit(lb_I_Application*) {
	_CL_LOG << "Save a lb_I_Application object." LOG_
	
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
}

void LB_STDCALL lbOutputStream::end() {
	if (oStream == NULL) {
		_CL_LOG << "lbOutputStream::end() Error: Not opened." LOG_
	}
	
	oStream->close();
}

lb_I_Stream* LB_STDCALL lbOutputStream::getStream() {
	lbErrCodes err = ERR_NONE;
	
	UAP(lb_I_Stream, s)
	QI(oStream, lb_I_Stream, s)
	s++;
	
	return s.getPtr();
}
/*...e*/

/*...sclass lbPluginOutputStream implementation:0:*/
/*...slbPluginOutputStream:0:*/
class lbPluginOutputStream : public lb_I_PluginImpl {
public:
	lbPluginOutputStream();
	
	virtual ~lbPluginOutputStream();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginOutputStream)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginOutputStream, lbPluginOutputStream)

/*...slbErrCodes LB_STDCALL lbPluginOutputStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginOutputStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginOutputStream::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginOutputStream::lbPluginOutputStream() {
	_CL_VERBOSE << "lbPluginOutputStream::lbPluginOutputStream() called.\n" LOG_
	
}

lbPluginOutputStream::~lbPluginOutputStream() {
	_CL_VERBOSE << "lbPluginOutputStream::~lbPluginOutputStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginOutputStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginOutputStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginOutputStream::initialize() {
}
	
bool LB_STDCALL lbPluginOutputStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginOutputStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginOutputStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbOutputStream* InputStream = new lbOutputStream();
		
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginOutputStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginOutputStream::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		lbOutputStream* InputStream = new lbOutputStream();
		
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginOutputStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/

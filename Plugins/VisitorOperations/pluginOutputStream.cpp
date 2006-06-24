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
            Rosmarinstr. 3
            
            40235 Duesseldorf (germany)
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
/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "dynamic.cpp"
#pragma interface "dynamic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

/*...swx ifdef\39\s:0:*/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
//#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
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

/*...e*/
	
	void LB_STDCALL visit(lb_I_Streamable* pm);
	void LB_STDCALL visit(lb_I_Application*);
	void LB_STDCALL visit(lb_I_MetaApplication*);
	void LB_STDCALL visit(lb_I_UserAccounts*);
	void LB_STDCALL visit(lb_I_Applications*);
	void LB_STDCALL visit(lb_I_User_Applications*);
	void LB_STDCALL visit(lb_I_Formulars*);
	void LB_STDCALL visit(lb_I_ApplicationParameter*);
	void LB_STDCALL visit(lb_I_FormularParameter*);

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
	ref = STARTREF;
}
/*...e*/
/*...slbOutputStream\58\\58\\126\lbOutputStream\40\\41\:0:*/
lbOutputStream::~lbOutputStream() {
	_CL_LOG << "lbOutputStream::~lbOutputStream() called." LOG_
}
/*...e*/

bool LB_STDCALL lbOutputStream::begin(char* file) {
	if (oStream == NULL) { 
		REQUEST(manager.getPtr(), lb_I_OutputStream, oStream)
		
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

void LB_STDCALL lbOutputStream::visit(lb_I_MetaApplication* app) {
	_CL_LOG << "Save a lb_I_MetaApplication object." LOG_

	UAP_REQUEST(manager.getPtr(), lb_I_String, temp)
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
}

void LB_STDCALL lbOutputStream::visit(lb_I_Application*) {
	_CL_LOG << "Save a lb_I_Application object." LOG_
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
class lbPluginOutputStream : public virtual lb_I_PluginImpl {
public:
	lbPluginOutputStream();
	
	virtual ~lbPluginOutputStream();

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
	ref = STARTREF;
}

lbPluginOutputStream::~lbPluginOutputStream() {
	_CL_VERBOSE << "lbPluginOutputStream::~lbPluginOutputStream() called.\n" LOG_
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
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
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
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
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

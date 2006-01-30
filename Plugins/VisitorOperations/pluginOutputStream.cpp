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
#include <lbInterfaces.h>



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

	void LB_STDCALL visit(lb_I_KeyBase*) { } 
	void LB_STDCALL visit(lb_I_String*) { } 
	void LB_STDCALL visit(lb_I_Integer*) { } 
	void LB_STDCALL visit(lb_I_Long*) { }
	void LB_STDCALL visit(lb_I_Container*) { } 
	void LB_STDCALL visit(lb_I_Database*) { } 
	void LB_STDCALL visit(lb_I_ColumnBinding*) { } 
	void LB_STDCALL visit(lb_I_BoundColumn*) { } 
	void LB_STDCALL visit(lb_I_Query*) { } 
	void LB_STDCALL visit(lb_I_MVC_View*) { } 
	void LB_STDCALL visit(lb_I_Connection*) { } 
	void LB_STDCALL visit(lb_I_InterfaceRepository*) { } 
	void LB_STDCALL visit(lb_I_Element*) { } 
	void LB_STDCALL visit(lb_I_Module*) { } 
	void LB_STDCALL visit(lb_I_FunctorEntity*) { }
	void LB_STDCALL visit(lb_I_InstanceReference*) { }
	void LB_STDCALL visit(lb_I_EventHandler*) { }
	void LB_STDCALL visit(lb_I_EventManager*) { }
	void LB_STDCALL visit(lb_I_EventMapper*) { }
	//void LB_STDCALL visit(lb_I_Application*) { }
	//void LB_STDCALL visit(lb_I_MetaApplication*) { }
	void LB_STDCALL visit(lb_I_EvHandler*) { }
	void LB_STDCALL visit(lb_I_Dispatcher*) { }
	void LB_STDCALL visit(lb_I_InputStream*) { }
	void LB_STDCALL visit(lb_I_OutputStream*) { }
	void LB_STDCALL visit(lb_I_FileOperation*) { }
	void LB_STDCALL visit(lb_I_Locale*) { }
	void LB_STDCALL visit(lb_I_Parameter*) { }
	void LB_STDCALL visit(lb_I_Reference*) { }
	void LB_STDCALL visit(lb_I_Log*) { }
	void LB_STDCALL visit(lb_I_Plugin*) { }
	void LB_STDCALL visit(lb_I_PluginImpl*) { }
	void LB_STDCALL visit(lb_I_PluginManager*) { }
	void LB_STDCALL visit(lb_I_PluginModule*) { }
	void LB_STDCALL visit(lb_I_wxFrame*) { }
	void LB_STDCALL visit(lb_I_Window*) { }
	void LB_STDCALL visit(lb_I_Action*) { }
	void LB_STDCALL visit(lb_I_DelegatedAction*) { }
	void LB_STDCALL visit(lb_I_Form*) { }
	void LB_STDCALL visit(lb_I_MasterDetailFormDefinition*) { }
	void LB_STDCALL visit(lb_I_DatabaseReport*) { }
	void LB_STDCALL visit(lb_I_Project*);
	void LB_STDCALL visit(lb_I_CodeGenerator*) { }
	void LB_STDCALL visit(lb_I_ProjectManager*) { }	
	
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
		return oStream->open();
	} else {
		_CL_LOG << "Error: lbOutputStream::begin(...) called prior!" LOG_
	}
	
	return false;
}

bool LB_STDCALL lbOutputStream::begin(lb_I_Stream* stream) {
	lbErrCodes err = ERR_NONE;
	QI(stream, lb_I_OutputStream, oStream)
	
	if (oStream == NULL) {
		_CL_LOG << "lbOutputStream::begin(...) Error: This is not a output stream." LOG_
		return false;
	} else {
		return oStream->open();
	}
}

void LB_STDCALL lbOutputStream::visit(lb_I_Project*) {
	_CL_LOG << "Save a lb_I_Project object. (Warning: This interface is private and could not be saved or loaded." LOG_
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

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

	bool LB_STDCALL begin(char* file);
	bool LB_STDCALL begin(lb_I_Stream* stream);
	void LB_STDCALL end();
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbInputStreamOpr)
//	ADD_INTERFACE(lb_I_Aspect)
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
	ref = STARTREF;
}
/*...e*/
/*...slbInputStreamOpr\58\\58\\126\lbInputStreamOpr\40\\41\:0:*/
lbInputStreamOpr::~lbInputStreamOpr() {
	_CL_LOG << "lbInputStreamOpr::~lbInputStreamOpr() called." LOG_
}
/*...e*/

bool LB_STDCALL lbInputStreamOpr::begin(char* file) {
	return true;
}

bool LB_STDCALL lbInputStreamOpr::begin(lb_I_Stream* stream) {
	if (stream != NULL) {
		_CL_LOG << "lbInputStreamOpr::begin(lb_I_Stream*): Got a stream (" << stream->getClassName() << ")." LOG_
	}
	
	return true;
}

void LB_STDCALL lbInputStreamOpr::visit(lb_I_Project*) {
	_CL_LOG << "lbInputStreamOpr::visit(): Read data of a project." LOG_
	
}


void LB_STDCALL lbInputStreamOpr::end() {

}

/*...e*/

/*...sclass lbPluginInputStream implementation:0:*/
/*...slbPluginInputStream:0:*/
class lbPluginInputStream : public lb_I_PluginImpl {
public:
	lbPluginInputStream();
	
	~lbPluginInputStream();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()

private:
	UAP(lb_I_Unknown, impl, __FILE__, __LINE__)
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

lbPluginInputStream::lbPluginInputStream() {
	_CL_VERBOSE << "lbPluginInputStream::lbPluginInputStream() called.\n" LOG_
	ref = STARTREF;
}

lbPluginInputStream::~lbPluginInputStream() {
	_CL_VERBOSE << "lbPluginInputStream::~lbPluginInputStream() called.\n" LOG_
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
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl, __FILE__, __LINE__)
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
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl, __FILE__, __LINE__)
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

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


#include <lbConfigHook.h>

/*...smisc and includes:0:*/
#ifdef __GNUG__
#pragma implementation "lbCryptoStream.cpp"
#pragma interface "lbCryptoStream.cpp"
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
#include "mondrian.xpm"
#endif
/*...e*/

#include "wx/wizard.h"
/*...e*/
/*...sLB_DATABASE_DLL scope:0:*/
#define LB_LOGINWIZARD_DLL
#include <lbloginwizard-module.h>
/*...e*/

#include <lbCryptoStream.h>

/** \brief This is the plugin module definition class for the login wizard.
 *
 */
class lbPluginModuleCryptoStream :
	public lb_I_PluginModule {
public:

	lbPluginModuleCryptoStream();
	virtual ~lbPluginModuleCryptoStream();

	DECLARE_LB_UNKNOWN()

	void LB_STDCALL initialize();
	void LB_STDCALL install();
	
	DECLARE_PLUGINS()
};

/*...sclass lbPluginModuleCryptoStream implementation:0:*/
BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginModuleCryptoStream)
        ADD_INTERFACE(lb_I_PluginModule)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOfPluginModule, lbPluginModuleCryptoStream)

BEGIN_PLUGINS(lbPluginModuleCryptoStream)
	ADD_PLUGIN(lbPluginCryptoStream, cryptostream)
END_PLUGINS()

lbPluginModuleCryptoStream::lbPluginModuleCryptoStream() {
	
	
	;
}

lbPluginModuleCryptoStream::~lbPluginModuleCryptoStream() {
	_CL_VERBOSE << "lbPluginModuleCryptoStream::~lbPluginModuleCryptoStream() called." LOG_
}

void LB_STDCALL lbPluginModuleCryptoStream::initialize() {
	enumPlugins();
}

void LB_STDCALL lbPluginModuleCryptoStream::install() {

}

lbErrCodes LB_STDCALL lbPluginModuleCryptoStream::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbPluginModuleCryptoStream::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

class lbCryptoStream : public lb_I_CryptoStream {
public:
	lbCryptoStream();
	virtual ~lbCryptoStream() { 
		if (algorythm) free(algorythm);
	}
		
	DECLARE_LB_UNKNOWN()
	
	bool LB_STDCALL setAlgorythm(const char* name);
	lb_I_CryptoStream& LB_STDCALL operator>> (lb_I_String* string);
	lb_I_CryptoStream& LB_STDCALL operator<< (lb_I_String* string);
		
/*...sprivate:0:*/
	private:
	char* algorythm;
	UAP(lb_I_String, cryptobuffer)
	UAP(lb_I_Dispatcher, disp)
/*...e*/
};


/// \todo A wrong name in plugin list may interfere other plugins.

IMPLEMENT_FUNCTOR(instanceOflbCryptoStream, lbCryptoStream)
	
BEGIN_IMPLEMENT_LB_UNKNOWN(lbCryptoStream)
ADD_INTERFACE(lb_I_CryptoStream)
END_IMPLEMENT_LB_UNKNOWN()

lbErrCodes LB_STDCALL lbCryptoStream::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbCryptoStream::setData(...) not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}


/*...slbInputStream\58\\58\lbInputStream\40\\41\:0:*/
lbCryptoStream::lbCryptoStream() {
	//lbLock lbLock(sect);
	
	
	algorythm = NULL;
	REQUEST(getModuleInstance(), lb_I_String, cryptobuffer)
}
/*...e*/
bool LB_STDCALL lbCryptoStream::setAlgorythm(const char* name) {
	if (algorythm) free(algorythm);
	algorythm = strdup(name);
	REQUEST(getModuleInstance(), lb_I_Dispatcher, disp)
	return true;
}

lb_I_CryptoStream& LB_STDCALL lbCryptoStream::operator>> (lb_I_String* string) {
	if (string != NULL) {
		*string = cryptobuffer->charrep();
	}
	
	return *this;
}

lb_I_CryptoStream& LB_STDCALL lbCryptoStream::operator<< (lb_I_String* string) {
	if (string != NULL) {
		*cryptobuffer += string->charrep();
	}	
	return *this;
}

/*...sclass lbPluginCryptoStream implementation:0:*/
/*...slbPluginCryptoStream:0:*/
class lbPluginCryptoStream : public lb_I_PluginImpl {
public:
	lbPluginCryptoStream();
	
	virtual ~lbPluginCryptoStream();
	
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
	
private:
	UAP(lb_I_Unknown, impl)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginCryptoStream)
ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginCryptoStream, lbPluginCryptoStream)

/*...slbErrCodes LB_STDCALL lbPluginCryptoStream\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginCryptoStream::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
	
	_CL_VERBOSE << "lbPluginCryptoStream::setData(...) called.\n" LOG_
	
	return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginCryptoStream::lbPluginCryptoStream() {
	_CL_VERBOSE << "lbPluginCryptoStream::lbPluginCryptoStream() called.\n" LOG_
	
	
	;
}

lbPluginCryptoStream::~lbPluginCryptoStream() {
	_CL_VERBOSE << "lbPluginCryptoStream::~lbPluginCryptoStream() called.\n" LOG_
}

bool LB_STDCALL lbPluginCryptoStream::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginCryptoStream::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginCryptoStream::initialize() {
}

bool LB_STDCALL lbPluginCryptoStream::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginCryptoStream\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginCryptoStream::peekImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		lbCryptoStream* CryptoStream = new lbCryptoStream();
		
		
		QI(CryptoStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginCryptoStream\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginCryptoStream::getImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl == NULL) {
		
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
		
		lbCryptoStream* CryptoStream = new lbCryptoStream();
		
		
		QI(CryptoStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginCryptoStream::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/


#ifdef WINDOWS
/*...sDllMain:0:*/
BOOL WINAPI DllMain(HINSTANCE dllHandle, DWORD reason, LPVOID situation) {
        char buf[100]="";

        switch (reason) {
                case DLL_PROCESS_ATTACH:
                	TRMemOpen();
                	TRMemSetModuleName(__FILE__);

			if (isSetTRMemTrackBreak()) TRMemSetAdrBreakPoint(getTRMemTrackBreak(), 0);

                        if (situation) {
                                _CL_VERBOSE << "DLL statically loaded." LOG_
                        }
                        else {
                                _CL_VERBOSE << "DLL dynamically loaded.\n" LOG_
                        }
                        break;
                case DLL_THREAD_ATTACH:
                        _CL_VERBOSE << "New thread starting.\n" LOG_
                        break;
                case DLL_PROCESS_DETACH:
                	_CL_LOG << "DLL_PROCESS_DETACH for " << __FILE__ LOG_
                        if (situation)
                        {
                                _CL_VERBOSE << "DLL released by system." LOG_
                        }
                        else
                        {
                                _CL_VERBOSE << "DLL released by program.\n" LOG_
                        }
                        break;
                case DLL_THREAD_DETACH:
                        _CL_VERBOSE << "Thread terminating.\n" LOG_
                default:
                        return FALSE;
        }

        return TRUE;
}
/*...e*/
#endif

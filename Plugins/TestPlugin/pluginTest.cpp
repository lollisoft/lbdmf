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
#define USE_TEST_PLUGIN

#ifdef USE_TEST_PLUGIN
/*...slbTest:0:*/
class lbTest :
	public lb_I_Streamable,
	public lb_I_Unknown {
public:
	lbTest();
	virtual ~lbTest();
	
	DECLARE_LB_UNKNOWN()
	
	void LB_STDCALL test();
	lbErrCodes LB_STDCALL save(lb_I_OutputStream* oStream) { return ERR_NONE; }
	lbErrCodes LB_STDCALL load(lb_I_InputStream* iStream) { return ERR_NONE; }
	lbErrCodes LB_STDCALL save(lb_I_Database* oDB) { return ERR_NONE; }
	lbErrCodes LB_STDCALL load(lb_I_Database* iDB) { return ERR_NONE; }
};


BEGIN_IMPLEMENT_LB_UNKNOWN(lbTest)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbTest, lbTest)


/*...slbErrCodes LB_STDCALL lbTest\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbTest::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;
		
        _CL_LOG << "lbTest::setData(...) not implemented yet" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

/*...slbTest\58\\58\lbTest\40\\41\:0:*/
lbTest::lbTest() 
{
	_CL_LOG << "lbTest::lbTest() called." LOG_
	ref = STARTREF;
}
/*...e*/
/*...slbTest\58\\58\\126\lbTest\40\\41\:0:*/
lbTest::~lbTest() {
	_CL_LOG << "lbTest::~lbTest() called." LOG_
}
/*...e*/

void LB_STDCALL lbTest::test() {

}
/*...e*/
#endif
/*...sclass lbPluginTest implementation:0:*/
/*...slbPluginTest:0:*/
class lbPluginTest : public lb_I_PluginImpl {
public:
	lbPluginTest();
	
	virtual ~lbPluginTest();

/*...sfrom plugin interface:8:*/
	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();
/*...e*/

	DECLARE_LB_UNKNOWN()
	
#ifdef USE_TEST_PLUGIN
private:
        UAP(lb_I_Unknown, impl)
#endif
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginTest)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginTest, lbPluginTest)

/*...slbErrCodes LB_STDCALL lbPluginTest\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginTest::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_LOG << "lbPluginTest::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginTest::lbPluginTest() {
	_CL_VERBOSE << "lbPluginTest::lbPluginTest() called.\n" LOG_
	ref = STARTREF;
}

lbPluginTest::~lbPluginTest() {
	_CL_LOG << "lbPluginTest::~lbPluginTest() called.\n" LOG_
}

void LB_STDCALL lbPluginTest::initialize() {
}
	
bool LB_STDCALL lbPluginTest::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginTest::peekImplementation() {
#ifdef USE_TEST_PLUGIN
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbTest* test = new lbTest();
		test->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(test, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginTest::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
#endif
#ifndef USE_TEST_PLUGIN	
	return NULL;
#endif
}
lb_I_Unknown* LB_STDCALL lbPluginTest::getImplementation() {
#ifdef USE_TEST_PLUGIN
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		lbTest* test = new lbTest();
		test->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(test, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
#endif
#ifndef USE_TEST_PLUGIN
	return NULL;
#endif
}

void LB_STDCALL lbPluginTest::releaseImplementation() {
#ifdef USE_TEST_PLUGIN
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
#endif
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

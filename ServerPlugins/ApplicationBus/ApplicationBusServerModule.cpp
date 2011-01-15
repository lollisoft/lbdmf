
/*
    DMF Distributed Multiplatform Framework (the initial goal of this library)
    This file is part of lbDMF.
    Copyright (C) 2002  Lothar Behrens (lothar.behrens at lollisoft.de)

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

#include <string.h>
#include <conio.h>
#include <lbConfigHook.h>
#include <IApplicationBus.h>

#undef DLLEXPORT

#include <appcs.h>
//#include <appbus.h>

#ifdef WINDOWS
#define DLLEXPORT LB_DLLEXPORT
#endif
#ifdef LINUX 
#define DLLEXPORT
#endif

#include <ApplicationBus.h>

/*...sclass lbPluginApplicationBus implementation:0:*/
/*...slbPluginApplicationBus:0:*/
class lbPluginApplicationBus : public lb_I_PluginImpl {
public:
	lbPluginApplicationBus();
	
	virtual ~lbPluginApplicationBus();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationBus)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationBus, lbPluginApplicationBus)

/*...slbErrCodes LB_STDCALL lbPluginApplicationBus\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginApplicationBus::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationBus::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginApplicationBus::lbPluginApplicationBus() {
	_CL_VERBOSE << "lbPluginApplicationBus::lbPluginApplicationBus() called.\n" LOG_
	ref = STARTREF;
}

lbPluginApplicationBus::~lbPluginApplicationBus() {
	_CL_VERBOSE << "lbPluginApplicationBus::~lbPluginApplicationBus() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationBus::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationBus::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationBus::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationBus::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationBus\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationBus::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		ApplicationBus* InputStream = new ApplicationBus();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationBus\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationBus::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
	
		ApplicationBus* InputStream = new ApplicationBus();
		InputStream->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(InputStream, lb_I_Unknown, impl)
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginApplicationBus::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
}
/*...e*/
/*...e*/


class lbServerModul : public lb_I_ApplicationServerModul {
public:
	lbServerModul();
	virtual ~lbServerModul();
	
	DECLARE_LB_UNKNOWN()
	
	virtual void LB_STDCALL initialize();

	DECLARE_PLUGINS()
	
	char* LB_STDCALL getServiceName();
	void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr);
};

IMPLEMENT_FUNCTOR(instanceOfPluginServerModule, lbServerModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbServerModul)
	ADD_INTERFACE(lb_I_ApplicationServerModul)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbServerModul)
	ADD_PLUGIN(lbPluginApplicationBus,			ApplicationBus)
END_PLUGINS()

lbServerModul::lbServerModul() {
	ref = STARTREF;
}

lbServerModul::~lbServerModul() {

}

void LB_STDCALL lbServerModul::initialize() {
	enumPlugins();
}

lbErrCodes LB_STDCALL lbServerModul::setData(lb_I_Unknown* uk) {
        _CL_VERBOSE << "lbServerModul::setData(...) for ApplicationBus not implemented yet" LOG_
        return ERR_NOT_IMPLEMENTED;
}

char* LB_STDCALL lbServerModul::getServiceName() {
	return "localhost/ApplicationBus";
}

void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) {
	_CL_LOG << "void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) called." LOG_
}

    
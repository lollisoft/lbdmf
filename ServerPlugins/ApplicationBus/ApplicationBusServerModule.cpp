
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
            Ginsterweg 4
            
            65760 Eschborn (germany)
*/

#include <string.h>
#include <conio.h>
#include <lbConfigHook.h>
#include <IApplicationBus.h>

#include <appcs.h>
//#include <appbus.h>

#undef DLLEXPORT

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

	void LB_STDCALL setNamespace(const char* _namespace) { }
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
	_LOG << "lbPluginApplicationBus::lbPluginApplicationBus() called." LOG_
	
}

lbPluginApplicationBus::~lbPluginApplicationBus() {
	_LOG << "lbPluginApplicationBus::~lbPluginApplicationBus() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationBus::canAutorun() {
	_LOG << "lbPluginApplicationBus::canAutorun() called.\n" LOG_
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationBus::autorun() {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbPluginApplicationBus::autorun() called.\n" LOG_
	return err;
}

void LB_STDCALL lbPluginApplicationBus::initialize() {
	_LOG << "lbPluginApplicationBus::initialize() called.\n" LOG_
}
	
bool LB_STDCALL lbPluginApplicationBus::run() {
	_LOG << "lbPluginApplicationBus::run() called.\n" LOG_
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginApplicationBus\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginApplicationBus::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		ApplicationBus* InputStream = new ApplicationBus();
	
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
		_LOG << "Warning: getImplementation() has not been used prior." LOG_
		ApplicationBus* applicationBus = new ApplicationBus();
	
		QI(applicationBus, lb_I_Unknown, impl)
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
	void LB_STDCALL registerModul(lb_I_ProtocolManager* pMgr, char* serverInstance);

	void LB_STDCALL install();
private:
	UAP(lb_I_Container, protocolHandlers)
	UAP(lb_I_Container, protocolHandlerInstances)
	
	char* LB_STDCALL getModuleName();
};

IMPLEMENT_FUNCTOR(instanceOfPluginServerModule, lbServerModul)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbServerModul)
	ADD_INTERFACE(lb_I_ApplicationServerModul)
END_IMPLEMENT_LB_UNKNOWN()

BEGIN_PLUGINS(lbServerModul)
	ADD_PLUGIN(lbPluginApplicationBus,			ApplicationBus)
END_PLUGINS()

lbServerModul::lbServerModul() {
	
}

lbServerModul::~lbServerModul() {

}

void LB_STDCALL lbServerModul::initialize() {
	enumPlugins();
}

void LB_STDCALL lbServerModul::install() {

}

lbErrCodes LB_STDCALL lbServerModul::setData(lb_I_Unknown* uk) {
	_CL_VERBOSE << "lbServerModul::setData(...) for ApplicationBus not implemented yet" LOG_
	return ERR_NOT_IMPLEMENTED;
}

char* LB_STDCALL lbServerModul::getModuleName() {
	return "ApplicationBus";
}

char* LB_STDCALL lbServerModul::getServiceName() {
	return "localhost/ApplicationBus";
}

void LB_STDCALL lbServerModul::registerModul(lb_I_ProtocolManager* pMgr, char* serverInstance) {
	lbErrCodes err = ERR_NONE;
	_LOG << "lbServerModul::registerModul(lb_I_ProtocolManager* pMgr) for ApplicationBus called." LOG_
	initialize();
	
	if (protocolHandlerInstances == NULL) {
		REQUEST(getModuleInstance(), lb_I_Container, protocolHandlerInstances)
		protocolHandlerInstances->setCloning(false);
	} else {
		protocolHandlerInstances->deleteAll();
	}
	
	protocolHandlers = getPlugins();
	protocolHandlers->finishIteration();
	
	while (protocolHandlers->hasMoreElements()) {
		UAP(lb_I_Unknown, uk)
		UAP(lb_I_Plugin, pl)
		UAP(lb_I_Unknown, ukPl)
		UAP(lb_I_ProtocolTarget, pt)
		_LOG << "Try to register a protocol handler." LOG_
		uk = protocolHandlers->nextElement();
		
		QI(uk, lb_I_Plugin, pl)
		
		if (pl == NULL) {
			_LOG << "Error: Element in plugin list has no interface of type lb_I_Plugin (" << uk->getClassName() << ")." LOG_
			continue;
		}

		pl->initialize();
		ukPl = pl->getImplementation(); 
		
		if (ukPl == NULL) {
			_LOG << "Error: Peeked plugin element is NULL" LOG_
			continue;
		}
		
		QI(ukPl, lb_I_ProtocolTarget, pt)
		
		if (pt != NULL) {
			_LOG << "Register protocols for " << pt->getClassName() LOG_
			pt->registerProtocols(*&pMgr, serverInstance);
			//Ensure lifetime hold by plugin implementation and thus by this class.
			UAP_REQUEST(getModuleInstance(), lb_I_String, pluginName)
			UAP(lb_I_KeyBase, PluginKey)
			*pluginName = ukPl->getClassName();
			QI(pluginName, lb_I_KeyBase, PluginKey)
			protocolHandlerInstances->insert(&ukPl, &PluginKey);
		} else {
			_LOG << "Have not got an interface of type lb_I_ProtocolTarget." LOG_
		}
	}
}

    

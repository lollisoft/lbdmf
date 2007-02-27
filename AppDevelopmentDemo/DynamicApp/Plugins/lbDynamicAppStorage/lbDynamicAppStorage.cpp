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
            Heinrich-Scheufelen-Platz 2
            
            73252 Lenningen (germany)
*/
/*...e*/
#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#include <lbConfigHook.h>
/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/

#include <lbDynamicAppStorage.h>

IMPLEMENT_FUNCTOR(instanceOflbDynamicAppStorage, lbDynamicAppStorage)

BEGIN_IMPLEMENT_LB_UNKNOWN(lbDynamicAppStorage)
	ADD_INTERFACE(lb_I_Streamable)
END_IMPLEMENT_LB_UNKNOWN()


lbDynamicAppStorage::lbDynamicAppStorage() {
	ref = STARTREF;

	_CL_LOG << "lbDynamicAppStorage::lbDynamicAppStorage() called." LOG_
}

lbDynamicAppStorage::~lbDynamicAppStorage() {
	_CL_LOG << "lbDynamicAppStorage::~lbDynamicAppStorage() called." LOG_
}

lbErrCodes LB_STDCALL lbDynamicAppStorage::setData(lb_I_Unknown*) {
		_CL_VERBOSE << "Error: lbDynamicAppStorage::setData(lb_I_Unknown*) not implemented." LOG_
		return ERR_NOT_IMPLEMENTED;
}


lbErrCodes LB_STDCALL lbDynamicAppStorage::load(lb_I_InputStream* iStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppStorage::save(lb_I_OutputStream* oStream) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppStorage::load(lb_I_Database* iDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}

lbErrCodes LB_STDCALL lbDynamicAppStorage::save(lb_I_Database* oDB) {
	lbErrCodes err = ERR_NONE;

	return err;
}


/*...sclass lbPluginDynamicAppStorage implementation:0:*/
/*...slbPluginDynamicAppStorage:0:*/
class lbPluginDynamicAppStorage : public lb_I_PluginImpl {
public:
	lbPluginDynamicAppStorage();
	
	virtual ~lbPluginDynamicAppStorage();

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
	
	UAP(lb_I_Unknown, ukActions)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDynamicAppStorage)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDynamicAppStorage, lbPluginDynamicAppStorage)

/*...slbErrCodes LB_STDCALL lbPluginDynamicAppStorage\58\\58\setData\40\lb_I_Unknown\42\ uk\41\:0:*/
lbErrCodes LB_STDCALL lbPluginDynamicAppStorage::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDynamicAppStorage::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}
/*...e*/

lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::lbPluginDynamicAppStorage() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() {
	_CL_VERBOSE << "lbPluginDynamicAppStorage::~lbPluginDynamicAppStorage() called.\n" LOG_
}

bool LB_STDCALL lbPluginDynamicAppStorage::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDynamicAppStorage::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDynamicAppStorage::initialize() {
}
	
bool LB_STDCALL lbPluginDynamicAppStorage::run() {
	return true;
}

/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\peekImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppStorage::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {
		lbDynamicAppStorage* DynamicAppStorage = new lbDynamicAppStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActions.getPtr();
}
/*...e*/
/*...slb_I_Unknown\42\ LB_STDCALL lbPluginDynamicAppStorage\58\\58\getImplementation\40\\41\:0:*/
lb_I_Unknown* LB_STDCALL lbPluginDynamicAppStorage::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActions == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		lbDynamicAppStorage* DynamicAppStorage = new lbDynamicAppStorage();
		DynamicAppStorage->setModuleManager(manager.getPtr(), __FILE__, __LINE__);
	
		QI(DynamicAppStorage, lb_I_Unknown, ukActions)
	}
	
	lb_I_Unknown* r = ukActions.getPtr();
	ukActions.resetPtr();
	return r;
}
/*...e*/
void LB_STDCALL lbPluginDynamicAppStorage::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActions != NULL) {
                ukActions--;
                ukActions.resetPtr();
        }
}
/*...e*/
/*...e*/




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
#ifndef DEBUG_MALLOC
#include <malloc.h>
#endif
#endif
#ifdef OSX
#include <sys/malloc.h>
#endif

#include <lbConfigHook.h>


#define LB_PLUGINMANAGER_DLL
#include <lbpluginmanager-module.h>

extern "C" {
#include <sql.h>
#include <sqlext.h>
}
#include <lbDB.h>

/** \brief Implementation of database gateway to databaselayer.
 *
 * This class wraps the databaselayer specific code to enable lb_I_Database compilant interface.
 * It is a basic gateway pattern.
 */
class lbPluginDatabase : public lb_I_PluginImpl {
public:
	lbPluginDatabase();
	
	virtual ~lbPluginDatabase();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	DECLARE_LB_UNKNOWN()

private:
	UAP(lb_I_Unknown, impl)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDatabase)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDatabase, lbPluginDatabase)

lbErrCodes LB_STDCALL lbPluginDatabase::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDatabase::setData(...) called.\n" LOG_

	return ERR_NOT_IMPLEMENTED;
}

lbPluginDatabase::lbPluginDatabase() {
	_CL_VERBOSE << "lbPluginDatabase::lbPluginDatabase() called.\n" LOG_
	ref = STARTREF;
}

lbPluginDatabase::~lbPluginDatabase() {
	_CL_VERBOSE << "lbPluginDatabase::~lbPluginDatabase() called.\n" LOG_
}

bool LB_STDCALL lbPluginDatabase::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDatabase::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDatabase::initialize() {
}
	
bool LB_STDCALL lbPluginDatabase::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDatabase::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		instanceOflbDatabaseLayerDatabase(&impl, manager.getPtr(), __FILE__, __LINE__);
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return impl.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDatabase::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (impl == NULL) {
		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior." LOG_
		instanceOflbDatabaseLayerDatabase(&impl, manager.getPtr(), __FILE__, __LINE__);
	}
	
	lb_I_Unknown* r = impl.getPtr();
	impl.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDatabase::releaseImplementation() {
	lbErrCodes err = ERR_NONE;
	
/*	if (impl != NULL) {
		impl->release(__FILE__, __LINE__);
		impl.resetPtr();
	}
*/
}


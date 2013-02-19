
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

#ifdef LBDMF_PREC
#include <lbConfigHook.h>
#endif

#include <stdio.h>
#include <string.h>
#ifndef UNIX
#include <windows.h>
#endif
#ifdef UNIX
#endif

#ifndef LBDMF_PREC
#include <lbConfigHook.h>
#endif

/*...sLB_DMFDATAMODEL_DLL scope:0:*/
#define LB_DMFDATAMODEL_DLL
#include <lbdmfdatamodel-module.h>
/*...e*/
#include <lbInterfaces-lbDMFManager.h>
#include <InternalFormatReader_User_Applications.h>

IMPLEMENT_FUNCTOR(instanceOfUser_ApplicationsInternalFormatReaderExtension, User_ApplicationsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(User_ApplicationsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

User_ApplicationsInternalFormatReaderExtension::User_ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "User_ApplicationsInternalFormatReaderExtension::User_ApplicationsInternalFormatReaderExtension() called." LOG_
}

User_ApplicationsInternalFormatReaderExtension::~User_ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "User_ApplicationsInternalFormatReaderExtension::~User_ApplicationsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL User_ApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: User_ApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL User_ApplicationsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_User_Applications, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: User_ApplicationsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_User_Applications." LOG_
		}
	} else {
		_LOG << "Error: User_ApplicationsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL User_ApplicationsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: User_ApplicationsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: User_ApplicationsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL User_ApplicationsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		long _userid = 0;
		long _anwendungenid = 0;
	
		*iStream >> _ID;

		*iStream >> _userid;
		*iStream >> _anwendungenid;
		owningObject->add(_userid, _anwendungenid,  _ID);

		// Leaky !
	}
}



class lbPluginUser_ApplicationsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginUser_ApplicationsInternalFormatReaderExtension();
	
	virtual ~lbPluginUser_ApplicationsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUser_ApplicationsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUser_ApplicationsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUser_ApplicationsInternalFormatReaderExtension, lbPluginUser_ApplicationsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUser_ApplicationsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUser_ApplicationsInternalFormatReaderExtension::lbPluginUser_ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsInternalFormatReaderExtension::lbPluginUser_ApplicationsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginUser_ApplicationsInternalFormatReaderExtension::~lbPluginUser_ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsInternalFormatReaderExtension::~lbPluginUser_ApplicationsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModelExtension == NULL) {
		User_ApplicationsInternalFormatReaderExtension* User_ApplicationsModelExtension = new User_ApplicationsInternalFormatReaderExtension();
		
	
		QI(User_ApplicationsModelExtension, lb_I_Unknown, ukUser_ApplicationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUser_ApplicationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		User_ApplicationsInternalFormatReaderExtension* User_ApplicationsModelExtension = new User_ApplicationsInternalFormatReaderExtension();
		
	
		QI(User_ApplicationsModelExtension, lb_I_Unknown, ukUser_ApplicationsModelExtension)
	}
	
	lb_I_Unknown* r = ukUser_ApplicationsModelExtension.getPtr();
	ukUser_ApplicationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUser_ApplicationsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUser_ApplicationsModelExtension != NULL) {
                ukUser_ApplicationsModelExtension--;
                ukUser_ApplicationsModelExtension.resetPtr();
        }
}

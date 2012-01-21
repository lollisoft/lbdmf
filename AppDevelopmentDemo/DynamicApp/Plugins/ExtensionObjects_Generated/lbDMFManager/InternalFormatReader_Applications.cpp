
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
#include <InternalFormatReader_Applications.h>

IMPLEMENT_FUNCTOR(instanceOfApplicationsInternalFormatReaderExtension, ApplicationsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ApplicationsInternalFormatReaderExtension::ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "ApplicationsInternalFormatReaderExtension::ApplicationsInternalFormatReaderExtension() called." LOG_
}

ApplicationsInternalFormatReaderExtension::~ApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "ApplicationsInternalFormatReaderExtension::~ApplicationsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ApplicationsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Applications, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ApplicationsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Applications." LOG_
		}
	} else {
		_LOG << "Error: ApplicationsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ApplicationsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ApplicationsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _titel = NULL;
		char* _name = NULL;
		char* _interface = NULL;
		char* _functor = NULL;
		char* _modulename = NULL;
	
		*iStream >> _ID;

		*iStream >> _titel;
		*iStream >> _name;
		*iStream >> _interface;
		*iStream >> _functor;
		*iStream >> _modulename;
		_LOG << "Read Applications entry from database: " << _titel << ", " << _name << ", " << _interface << ", " << _functor << ", " << _modulename << ", " <<  _ID LOG_
		owningObject->addApplications(_titel, _name, _interface, _functor, _modulename,  _ID);

		// Leaky !
	}
}



class lbPluginApplicationsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginApplicationsInternalFormatReaderExtension();
	
	virtual ~lbPluginApplicationsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationsInternalFormatReaderExtension, lbPluginApplicationsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationsInternalFormatReaderExtension::lbPluginApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationsInternalFormatReaderExtension::lbPluginApplicationsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginApplicationsInternalFormatReaderExtension::~lbPluginApplicationsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationsInternalFormatReaderExtension::~lbPluginApplicationsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {
		ApplicationsInternalFormatReaderExtension* ApplicationsModelExtension = new ApplicationsInternalFormatReaderExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationsInternalFormatReaderExtension* ApplicationsModelExtension = new ApplicationsInternalFormatReaderExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	}
	
	lb_I_Unknown* r = ukApplicationsModelExtension.getPtr();
	ukApplicationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationsModelExtension != NULL) {
                ukApplicationsModelExtension--;
                ukApplicationsModelExtension.resetPtr();
        }
}

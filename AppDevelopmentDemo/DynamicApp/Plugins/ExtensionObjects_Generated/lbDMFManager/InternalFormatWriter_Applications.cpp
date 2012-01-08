
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
#include <InternalFormatWriter_Applications.h>

IMPLEMENT_FUNCTOR(instanceOfApplicationsInternalFormatWriterExtension, ApplicationsInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationsInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ApplicationsInternalFormatWriterExtension::ApplicationsInternalFormatWriterExtension() {
	_CL_VERBOSE << "ApplicationsInternalFormatWriterExtension::ApplicationsInternalFormatWriterExtension() called." LOG_
}

ApplicationsInternalFormatWriterExtension::~ApplicationsInternalFormatWriterExtension() {
	_CL_VERBOSE << "ApplicationsInternalFormatWriterExtension::~ApplicationsInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ApplicationsInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ApplicationsInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ApplicationsInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Applications, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ApplicationsInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_Applications." LOG_
		}
	} else {
		_LOG << "Error: ApplicationsInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ApplicationsInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ApplicationsInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getApplicationsCount();
	*oStream << count;
	
	owningObject->finishApplicationsIteration();
	
	while (owningObject->hasMoreApplications()) {
		owningObject->setNextApplications();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_titel();
		*oStream << owningObject->get_name();
		*oStream << owningObject->get_interface();
		*oStream << owningObject->get_functor();
		*oStream << owningObject->get_modulename();
		*oStream << owningObject->get_modulename();
	}
}



class lbPluginApplicationsInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginApplicationsInternalFormatWriterExtension();
	
	virtual ~lbPluginApplicationsInternalFormatWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationsInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationsInternalFormatWriterExtension, lbPluginApplicationsInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationsInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationsInternalFormatWriterExtension::lbPluginApplicationsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginApplicationsInternalFormatWriterExtension::lbPluginApplicationsInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginApplicationsInternalFormatWriterExtension::~lbPluginApplicationsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginApplicationsInternalFormatWriterExtension::~lbPluginApplicationsInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {
		ApplicationsInternalFormatWriterExtension* ApplicationsModelExtension = new ApplicationsInternalFormatWriterExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationsInternalFormatWriterExtension* ApplicationsModelExtension = new ApplicationsInternalFormatWriterExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	}
	
	lb_I_Unknown* r = ukApplicationsModelExtension.getPtr();
	ukApplicationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationsInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationsModelExtension != NULL) {
                ukApplicationsModelExtension--;
                ukApplicationsModelExtension.resetPtr();
        }
}

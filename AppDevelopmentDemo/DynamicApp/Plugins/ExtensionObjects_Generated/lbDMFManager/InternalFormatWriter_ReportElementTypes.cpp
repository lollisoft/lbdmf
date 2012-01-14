
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
#include <InternalFormatWriter_ReportElementTypes.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementTypesInternalFormatWriterExtension, ReportElementTypesInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementTypesInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementTypesInternalFormatWriterExtension::ReportElementTypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportElementTypesInternalFormatWriterExtension::ReportElementTypesInternalFormatWriterExtension() called." LOG_
}

ReportElementTypesInternalFormatWriterExtension::~ReportElementTypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportElementTypesInternalFormatWriterExtension::~ReportElementTypesInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementTypesInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementTypesInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementTypesInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElementTypes, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementTypesInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_ReportElementTypes." LOG_
		}
	} else {
		_LOG << "Error: ReportElementTypesInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementTypesInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportElementTypesInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ReportElementTypesInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementTypesInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getReportElementTypesCount();
	*oStream << count;
	
	owningObject->finishReportElementTypesIteration();
	
	while (owningObject->hasMoreReportElementTypes()) {
		owningObject->setNextReportElementTypes();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_name();
		*oStream << owningObject->get_description();
	}
}



class lbPluginReportElementTypesInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementTypesInternalFormatWriterExtension();
	
	virtual ~lbPluginReportElementTypesInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportElementTypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementTypesInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementTypesInternalFormatWriterExtension, lbPluginReportElementTypesInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementTypesInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementTypesInternalFormatWriterExtension::lbPluginReportElementTypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementTypesInternalFormatWriterExtension::lbPluginReportElementTypesInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginReportElementTypesInternalFormatWriterExtension::~lbPluginReportElementTypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementTypesInternalFormatWriterExtension::~lbPluginReportElementTypesInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModelExtension == NULL) {
		ReportElementTypesInternalFormatWriterExtension* ReportElementTypesModelExtension = new ReportElementTypesInternalFormatWriterExtension();
		
	
		QI(ReportElementTypesModelExtension, lb_I_Unknown, ukReportElementTypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementTypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementTypesInternalFormatWriterExtension* ReportElementTypesModelExtension = new ReportElementTypesInternalFormatWriterExtension();
		
	
		QI(ReportElementTypesModelExtension, lb_I_Unknown, ukReportElementTypesModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementTypesModelExtension.getPtr();
	ukReportElementTypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementTypesInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementTypesModelExtension != NULL) {
                ukReportElementTypesModelExtension--;
                ukReportElementTypesModelExtension.resetPtr();
        }
}

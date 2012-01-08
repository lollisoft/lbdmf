
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
#include <InternalFormatWriter_ReportParameters.h>

IMPLEMENT_FUNCTOR(instanceOfReportParametersInternalFormatWriterExtension, ReportParametersInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportParametersInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ReportParametersInternalFormatWriterExtension::ReportParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportParametersInternalFormatWriterExtension::ReportParametersInternalFormatWriterExtension() called." LOG_
}

ReportParametersInternalFormatWriterExtension::~ReportParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportParametersInternalFormatWriterExtension::~ReportParametersInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportParametersInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportParametersInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportParametersInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportParameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportParametersInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_ReportParameters." LOG_
		}
	} else {
		_LOG << "Error: ReportParametersInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportParametersInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ReportParametersInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getReportParametersCount();
	*oStream << count;
	
	owningObject->finishReportParametersIteration();
	
	while (owningObject->hasMoreReportParameters()) {
		owningObject->setNextReportParameters();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_value();
		*oStream << owningObject->get_name();
		*oStream << owningObject->get_reportid();
		*oStream << owningObject->get_reportid();
	}
}



class lbPluginReportParametersInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginReportParametersInternalFormatWriterExtension();
	
	virtual ~lbPluginReportParametersInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportParametersModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportParametersInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportParametersInternalFormatWriterExtension, lbPluginReportParametersInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportParametersInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportParametersInternalFormatWriterExtension::lbPluginReportParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportParametersInternalFormatWriterExtension::lbPluginReportParametersInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginReportParametersInternalFormatWriterExtension::~lbPluginReportParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportParametersInternalFormatWriterExtension::~lbPluginReportParametersInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {
		ReportParametersInternalFormatWriterExtension* ReportParametersModelExtension = new ReportParametersInternalFormatWriterExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportParametersInternalFormatWriterExtension* ReportParametersModelExtension = new ReportParametersInternalFormatWriterExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukReportParametersModelExtension.getPtr();
	ukReportParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportParametersInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportParametersModelExtension != NULL) {
                ukReportParametersModelExtension--;
                ukReportParametersModelExtension.resetPtr();
        }
}


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
#include <InternalFormatWriter_ReportElements.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementsInternalFormatWriterExtension, ReportElementsInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementsInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementsInternalFormatWriterExtension::ReportElementsInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportElementsInternalFormatWriterExtension::ReportElementsInternalFormatWriterExtension() called." LOG_
}

ReportElementsInternalFormatWriterExtension::~ReportElementsInternalFormatWriterExtension() {
	_CL_VERBOSE << "ReportElementsInternalFormatWriterExtension::~ReportElementsInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementsInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementsInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementsInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElements, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementsInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_ReportElements." LOG_
		}
	} else {
		_LOG << "Error: ReportElementsInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportElementsInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ReportElementsInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getReportElementsCount();
	*oStream << count;
	
	owningObject->finishReportElementsIteration();
	
	while (owningObject->hasMoreReportElements()) {
		owningObject->setNextReportElements();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_name();
		*oStream << owningObject->get_description();
		*oStream << owningObject->get_x();
		*oStream << owningObject->get_y();
		*oStream << owningObject->get_w();
		*oStream << owningObject->get_h();
		*oStream << owningObject->get_reportid();
		*oStream << owningObject->get_typ();
	}
}



class lbPluginReportElementsInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementsInternalFormatWriterExtension();
	
	virtual ~lbPluginReportElementsInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportElementsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsInternalFormatWriterExtension, lbPluginReportElementsInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementsInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementsInternalFormatWriterExtension::lbPluginReportElementsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementsInternalFormatWriterExtension::lbPluginReportElementsInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginReportElementsInternalFormatWriterExtension::~lbPluginReportElementsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementsInternalFormatWriterExtension::~lbPluginReportElementsInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {
		ReportElementsInternalFormatWriterExtension* ReportElementsModelExtension = new ReportElementsInternalFormatWriterExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementsInternalFormatWriterExtension* ReportElementsModelExtension = new ReportElementsInternalFormatWriterExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementsModelExtension.getPtr();
	ukReportElementsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementsInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementsModelExtension != NULL) {
                ukReportElementsModelExtension--;
                ukReportElementsModelExtension.resetPtr();
        }
}

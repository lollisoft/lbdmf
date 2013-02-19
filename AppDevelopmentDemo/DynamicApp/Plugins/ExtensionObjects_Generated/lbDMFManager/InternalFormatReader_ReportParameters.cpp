
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
#include <InternalFormatReader_ReportParameters.h>

IMPLEMENT_FUNCTOR(instanceOfReportParametersInternalFormatReaderExtension, ReportParametersInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportParametersInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportParametersInternalFormatReaderExtension::ReportParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportParametersInternalFormatReaderExtension::ReportParametersInternalFormatReaderExtension() called." LOG_
}

ReportParametersInternalFormatReaderExtension::~ReportParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportParametersInternalFormatReaderExtension::~ReportParametersInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportParametersInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportParametersInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportParametersInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportParameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportParametersInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportParameters." LOG_
		}
	} else {
		_LOG << "Error: ReportParametersInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportParametersInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ReportParametersInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		int _value = 0;
		char* _name = NULL;
		long _reportid = 0;
	
		*iStream >> _ID;

		*iStream >> _value;
		*iStream >> _name;
		*iStream >> _reportid;
		owningObject->add(_value, _name, _reportid,  _ID);

		// Leaky !
	}
}



class lbPluginReportParametersInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportParametersInternalFormatReaderExtension();
	
	virtual ~lbPluginReportParametersInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportParametersInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportParametersInternalFormatReaderExtension, lbPluginReportParametersInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportParametersInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportParametersInternalFormatReaderExtension::lbPluginReportParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportParametersInternalFormatReaderExtension::lbPluginReportParametersInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginReportParametersInternalFormatReaderExtension::~lbPluginReportParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportParametersInternalFormatReaderExtension::~lbPluginReportParametersInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {
		ReportParametersInternalFormatReaderExtension* ReportParametersModelExtension = new ReportParametersInternalFormatReaderExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportParametersInternalFormatReaderExtension* ReportParametersModelExtension = new ReportParametersInternalFormatReaderExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukReportParametersModelExtension.getPtr();
	ukReportParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportParametersInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportParametersModelExtension != NULL) {
                ukReportParametersModelExtension--;
                ukReportParametersModelExtension.resetPtr();
        }
}

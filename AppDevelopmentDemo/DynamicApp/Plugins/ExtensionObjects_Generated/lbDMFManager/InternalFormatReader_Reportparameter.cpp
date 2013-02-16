
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
#include <InternalFormatReader_Reportparameter.h>

IMPLEMENT_FUNCTOR(instanceOfReportparameterInternalFormatReaderExtension, ReportparameterInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportparameterInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportparameterInternalFormatReaderExtension::ReportparameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportparameterInternalFormatReaderExtension::ReportparameterInternalFormatReaderExtension() called." LOG_
}

ReportparameterInternalFormatReaderExtension::~ReportparameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportparameterInternalFormatReaderExtension::~ReportparameterInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportparameterInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportparameterInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportparameterInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Reportparameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportparameterInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Reportparameter." LOG_
		}
	} else {
		_LOG << "Error: ReportparameterInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportparameterInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportparameterInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ReportparameterInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportparameterInternalFormatReaderExtension::execute() {
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
		owningObject->addReportparameter(_value, _name, _reportid,  _ID);

		// Leaky !
	}
}



class lbPluginReportparameterInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportparameterInternalFormatReaderExtension();
	
	virtual ~lbPluginReportparameterInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportparameterModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportparameterInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportparameterInternalFormatReaderExtension, lbPluginReportparameterInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportparameterInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportparameterInternalFormatReaderExtension::lbPluginReportparameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportparameterInternalFormatReaderExtension::lbPluginReportparameterInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginReportparameterInternalFormatReaderExtension::~lbPluginReportparameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportparameterInternalFormatReaderExtension::~lbPluginReportparameterInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModelExtension == NULL) {
		ReportparameterInternalFormatReaderExtension* ReportparameterModelExtension = new ReportparameterInternalFormatReaderExtension();
		
	
		QI(ReportparameterModelExtension, lb_I_Unknown, ukReportparameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportparameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportparameterInternalFormatReaderExtension* ReportparameterModelExtension = new ReportparameterInternalFormatReaderExtension();
		
	
		QI(ReportparameterModelExtension, lb_I_Unknown, ukReportparameterModelExtension)
	}
	
	lb_I_Unknown* r = ukReportparameterModelExtension.getPtr();
	ukReportparameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportparameterInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportparameterModelExtension != NULL) {
                ukReportparameterModelExtension--;
                ukReportparameterModelExtension.resetPtr();
        }
}

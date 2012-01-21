
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
#include <InternalFormatReader_ReportElements.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementsInternalFormatReaderExtension, ReportElementsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementsInternalFormatReaderExtension::ReportElementsInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportElementsInternalFormatReaderExtension::ReportElementsInternalFormatReaderExtension() called." LOG_
}

ReportElementsInternalFormatReaderExtension::~ReportElementsInternalFormatReaderExtension() {
	_CL_VERBOSE << "ReportElementsInternalFormatReaderExtension::~ReportElementsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElements, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportElements." LOG_
		}
	} else {
		_LOG << "Error: ReportElementsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportElementsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ReportElementsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _name = NULL;
		char* _description = NULL;
		int _x = 0;
		int _y = 0;
		int _w = 0;
		int _h = 0;
		long _reportid = 0;
		long _typ = 0;
	
		*iStream >> _ID;

		*iStream >> _name;
		*iStream >> _description;
		*iStream >> _x;
		*iStream >> _y;
		*iStream >> _w;
		*iStream >> _h;
		*iStream >> _reportid;
		*iStream >> _typ;
		_LOG << "Read ReportElements entry from database: " << _name << ", " << _description << ", " << _x << ", " << _y << ", " << _w << ", " << _h << ", " << _reportid << ", " << _typ << ", " <<  _ID LOG_
		owningObject->addReportElements(_name, _description, _x, _y, _w, _h, _reportid, _typ,  _ID);

		// Leaky !
	}
}



class lbPluginReportElementsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementsInternalFormatReaderExtension();
	
	virtual ~lbPluginReportElementsInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsInternalFormatReaderExtension, lbPluginReportElementsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementsInternalFormatReaderExtension::lbPluginReportElementsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementsInternalFormatReaderExtension::lbPluginReportElementsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginReportElementsInternalFormatReaderExtension::~lbPluginReportElementsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementsInternalFormatReaderExtension::~lbPluginReportElementsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {
		ReportElementsInternalFormatReaderExtension* ReportElementsModelExtension = new ReportElementsInternalFormatReaderExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementsInternalFormatReaderExtension* ReportElementsModelExtension = new ReportElementsInternalFormatReaderExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementsModelExtension.getPtr();
	ukReportElementsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementsModelExtension != NULL) {
                ukReportElementsModelExtension--;
                ukReportElementsModelExtension.resetPtr();
        }
}

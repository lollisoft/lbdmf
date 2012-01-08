
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
#include <XMLWriterExtension_ReportElements.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementsXMLWriterExtension, ReportElementsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementsXMLWriterExtension::ReportElementsXMLWriterExtension() {
	_CL_VERBOSE << "ReportElementsXMLWriterExtension::ReportElementsXMLWriterExtension() called." LOG_
}

ReportElementsXMLWriterExtension::~ReportElementsXMLWriterExtension() {
	_CL_VERBOSE << "ReportElementsXMLWriterExtension::~ReportElementsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElements, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_ReportElements." LOG_
		}
	} else {
		_LOG << "Error: ReportElementsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportElementsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ReportElementsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsXMLWriterExtension::execute() {
	*oStream << "<report_elements>" << "\n";
	
	owningObject->finishReportElementsIteration();
	
	while (owningObject->hasMoreReportElements()) {
		owningObject->setNextReportElements();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" name=\"" << owningObject->get_name() <<
		"\" description=\"" << owningObject->get_description() <<
		"\" x=\"" << owningObject->get_x() <<
		"\" y=\"" << owningObject->get_y() <<
		"\" w=\"" << owningObject->get_w() <<
		"\" h=\"" << owningObject->get_h() <<
		"\" reportid=\"" << owningObject->get_reportid() <<
		"\" typ=\"" << owningObject->get_typ() << "\"/>" << "\n";
	}
	*oStream << "</report_elements>" << "\n";
}



class lbPluginReportElementsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementsXMLWriterExtension();
	
	virtual ~lbPluginReportElementsXMLWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsXMLWriterExtension, lbPluginReportElementsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginReportElementsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementsXMLWriterExtension::lbPluginReportElementsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementsXMLWriterExtension::lbPluginReportElementsXMLWriterExtension() called.\n" LOG_
}

lbPluginReportElementsXMLWriterExtension::~lbPluginReportElementsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginReportElementsXMLWriterExtension::~lbPluginReportElementsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {
		ReportElementsXMLWriterExtension* ReportElementsModelExtension = new ReportElementsXMLWriterExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementsXMLWriterExtension* ReportElementsModelExtension = new ReportElementsXMLWriterExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementsModelExtension.getPtr();
	ukReportElementsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementsModelExtension != NULL) {
                ukReportElementsModelExtension--;
                ukReportElementsModelExtension.resetPtr();
        }
}

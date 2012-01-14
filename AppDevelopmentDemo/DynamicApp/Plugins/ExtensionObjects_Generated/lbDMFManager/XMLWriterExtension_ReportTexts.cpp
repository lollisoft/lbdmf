
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
#include <XMLWriterExtension_ReportTexts.h>

IMPLEMENT_FUNCTOR(instanceOfReportTextsXMLWriterExtension, ReportTextsXMLWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportTextsXMLWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportTextsXMLWriterExtension::ReportTextsXMLWriterExtension() {
	_CL_VERBOSE << "ReportTextsXMLWriterExtension::ReportTextsXMLWriterExtension() called." LOG_
}

ReportTextsXMLWriterExtension::~ReportTextsXMLWriterExtension() {
	_CL_VERBOSE << "ReportTextsXMLWriterExtension::~ReportTextsXMLWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportTextsXMLWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportTextsXMLWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportTextsXMLWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportTexts, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportTextsXMLWriterExtension::setOwningObject() owning parameter is not a lb_I_ReportTexts." LOG_
		}
	} else {
		_LOG << "Error: ReportTextsXMLWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportTextsXMLWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ReportTextsXMLWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ReportTextsXMLWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportTextsXMLWriterExtension::execute() {
	*oStream << "<report_texts>" << "\n";
	
	owningObject->finishReportTextsIteration();
	
	while (owningObject->hasMoreReportTexts()) {
		owningObject->setNextReportTexts();
		*oStream << 
		"<entry ID=\"" << owningObject->get_id() << 

		"\" line=\"" << owningObject->get_line() <<
		"\" text=\"" << owningObject->get_text() <<
		"\" elementid=\"" << owningObject->get_elementid() << "\"/>" << "\n";
	}
	*oStream << "</report_texts>" << "\n";
}



class lbPluginReportTextsXMLWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginReportTextsXMLWriterExtension();
	
	virtual ~lbPluginReportTextsXMLWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportTextsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportTextsXMLWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportTextsXMLWriterExtension, lbPluginReportTextsXMLWriterExtension)

lbErrCodes LB_STDCALL lbPluginReportTextsXMLWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportTextsXMLWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportTextsXMLWriterExtension::lbPluginReportTextsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginReportTextsXMLWriterExtension::lbPluginReportTextsXMLWriterExtension() called.\n" LOG_
}

lbPluginReportTextsXMLWriterExtension::~lbPluginReportTextsXMLWriterExtension() {
	_CL_VERBOSE << "lbPluginReportTextsXMLWriterExtension::~lbPluginReportTextsXMLWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportTextsXMLWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportTextsXMLWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportTextsXMLWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportTextsXMLWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsXMLWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModelExtension == NULL) {
		ReportTextsXMLWriterExtension* ReportTextsModelExtension = new ReportTextsXMLWriterExtension();
		
	
		QI(ReportTextsModelExtension, lb_I_Unknown, ukReportTextsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportTextsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsXMLWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportTextsXMLWriterExtension* ReportTextsModelExtension = new ReportTextsXMLWriterExtension();
		
	
		QI(ReportTextsModelExtension, lb_I_Unknown, ukReportTextsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportTextsModelExtension.getPtr();
	ukReportTextsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportTextsXMLWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportTextsModelExtension != NULL) {
                ukReportTextsModelExtension--;
                ukReportTextsModelExtension.resetPtr();
        }
}

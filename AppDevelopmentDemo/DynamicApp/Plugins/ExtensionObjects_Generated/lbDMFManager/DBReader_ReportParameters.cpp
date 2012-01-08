
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
#include <DBReader_ReportParameters.h>

IMPLEMENT_FUNCTOR(instanceOfReportParametersDBReaderExtension, ReportParametersDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportParametersDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ReportParametersDBReaderExtension::ReportParametersDBReaderExtension() {
	_CL_VERBOSE << "ReportParametersDBReaderExtension::ReportParametersDBReaderExtension() called." LOG_
}

ReportParametersDBReaderExtension::~ReportParametersDBReaderExtension() {
	_CL_VERBOSE << "ReportParametersDBReaderExtension::~ReportParametersDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportParametersDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportParametersDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportParametersDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportParameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportParametersDBReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportParameters." LOG_
		}
	} else {
		_LOG << "Error: ReportParametersDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportParametersDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportParametersDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportParametersDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportParametersDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select value, name, reportid,  id from report_parameters") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read ReportParameters would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No ReportParameters found. All ReportParameters may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_Long, qvalue)
		UAP(lb_I_String, qname)
		UAP(lb_I_Long, qreportid)

		// Copy values

		qvalue = q->getAsLong(1);
		qname = q->getAsString(2);
		qreportid = q->getAsLong(3);
		qID = q->getAsLong(4);

		owningObject->addReportParameters(qvalue->getData(), qname->charrep(), qreportid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qvalue = q->getAsLong(1);
			qname = q->getAsString(2);
			qreportid = q->getAsLong(3);
			qID = q->getAsLong(4);

			owningObject->addReportParameters(qvalue->getData(), qname->charrep(), qreportid->getData(),  qID->getData());
		}
	}
}



class lbPluginReportParametersDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportParametersDBReaderExtension();
	
	virtual ~lbPluginReportParametersDBReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportParametersDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportParametersDBReaderExtension, lbPluginReportParametersDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportParametersDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportParametersDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportParametersDBReaderExtension::lbPluginReportParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportParametersDBReaderExtension::lbPluginReportParametersDBReaderExtension() called.\n" LOG_
}

lbPluginReportParametersDBReaderExtension::~lbPluginReportParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportParametersDBReaderExtension::~lbPluginReportParametersDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportParametersDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportParametersDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportParametersDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportParametersDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {
		ReportParametersDBReaderExtension* ReportParametersModelExtension = new ReportParametersDBReaderExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportParametersDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportParametersDBReaderExtension* ReportParametersModelExtension = new ReportParametersDBReaderExtension();
		
	
		QI(ReportParametersModelExtension, lb_I_Unknown, ukReportParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukReportParametersModelExtension.getPtr();
	ukReportParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportParametersDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportParametersModelExtension != NULL) {
                ukReportParametersModelExtension--;
                ukReportParametersModelExtension.resetPtr();
        }
}

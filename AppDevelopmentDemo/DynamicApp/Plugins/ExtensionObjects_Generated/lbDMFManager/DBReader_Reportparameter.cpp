
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
#include <DBReader_Reportparameter.h>

IMPLEMENT_FUNCTOR(instanceOfReportparameterDBReaderExtension, ReportparameterDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportparameterDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportparameterDBReaderExtension::ReportparameterDBReaderExtension() {
	_CL_VERBOSE << "ReportparameterDBReaderExtension::ReportparameterDBReaderExtension() called." LOG_
}

ReportparameterDBReaderExtension::~ReportparameterDBReaderExtension() {
	_CL_VERBOSE << "ReportparameterDBReaderExtension::~ReportparameterDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportparameterDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportparameterDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportparameterDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Reportparameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportparameterDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Reportparameter." LOG_
		}
	} else {
		_LOG << "Error: ReportparameterDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportparameterDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportparameterDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportparameterDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportparameterDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportparameterDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select value, name, reportid,  id from report_parameters") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Reportparameter would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Reportparameter found. All Reportparameter may be deleted accidantly." LOG_
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

		owningObject->addReportparameter(qvalue->getData(), qname->charrep(), qreportid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qvalue = q->getAsLong(1);
			qname = q->getAsString(2);
			qreportid = q->getAsLong(3);
			qID = q->getAsLong(4);

			owningObject->addReportparameter(qvalue->getData(), qname->charrep(), qreportid->getData(),  qID->getData());
		}
	}
}



class lbPluginReportparameterDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportparameterDBReaderExtension();
	
	virtual ~lbPluginReportparameterDBReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportparameterDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportparameterDBReaderExtension, lbPluginReportparameterDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportparameterDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportparameterDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportparameterDBReaderExtension::lbPluginReportparameterDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportparameterDBReaderExtension::lbPluginReportparameterDBReaderExtension() called.\n" LOG_
}

lbPluginReportparameterDBReaderExtension::~lbPluginReportparameterDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportparameterDBReaderExtension::~lbPluginReportparameterDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportparameterDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportparameterDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportparameterDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportparameterDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModelExtension == NULL) {
		ReportparameterDBReaderExtension* ReportparameterModelExtension = new ReportparameterDBReaderExtension();
		
	
		QI(ReportparameterModelExtension, lb_I_Unknown, ukReportparameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportparameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportparameterDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportparameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportparameterDBReaderExtension* ReportparameterModelExtension = new ReportparameterDBReaderExtension();
		
	
		QI(ReportparameterModelExtension, lb_I_Unknown, ukReportparameterModelExtension)
	}
	
	lb_I_Unknown* r = ukReportparameterModelExtension.getPtr();
	ukReportparameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportparameterDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportparameterModelExtension != NULL) {
                ukReportparameterModelExtension--;
                ukReportparameterModelExtension.resetPtr();
        }
}

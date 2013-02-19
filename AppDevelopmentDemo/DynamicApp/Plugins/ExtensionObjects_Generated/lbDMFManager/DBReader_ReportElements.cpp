
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
#include <DBReader_ReportElements.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementsDBReaderExtension, ReportElementsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementsDBReaderExtension::ReportElementsDBReaderExtension() {
	_CL_VERBOSE << "ReportElementsDBReaderExtension::ReportElementsDBReaderExtension() called." LOG_
}

ReportElementsDBReaderExtension::~ReportElementsDBReaderExtension() {
	_CL_VERBOSE << "ReportElementsDBReaderExtension::~ReportElementsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElements, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportElements." LOG_
		}
	} else {
		_LOG << "Error: ReportElementsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportElementsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportElementsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportElementsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, description, x, y, w, h, reportid, typ,  id from report_elements") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read ReportElements would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No ReportElements found. All ReportElements may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qname)
		UAP(lb_I_String, qdescription)
		UAP(lb_I_Long, qx)
		UAP(lb_I_Long, qy)
		UAP(lb_I_Long, qw)
		UAP(lb_I_Long, qh)
		UAP(lb_I_Long, qreportid)
		UAP(lb_I_Long, qtyp)

		// Copy values

		qname = q->getAsString(1);
		qdescription = q->getAsString(2);
		qx = q->getAsLong(3);
		qy = q->getAsLong(4);
		qw = q->getAsLong(5);
		qh = q->getAsLong(6);
		qreportid = q->getAsLong(7);
		qtyp = q->getAsLong(8);
		qID = q->getAsLong(9);

		owningObject->add(qname->charrep(), qdescription->charrep(), qx->getData(), qy->getData(), qw->getData(), qh->getData(), qreportid->getData(), qtyp->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qname = q->getAsString(1);
			qdescription = q->getAsString(2);
			qx = q->getAsLong(3);
			qy = q->getAsLong(4);
			qw = q->getAsLong(5);
			qh = q->getAsLong(6);
			qreportid = q->getAsLong(7);
			qtyp = q->getAsLong(8);
			qID = q->getAsLong(9);

			owningObject->add(qname->charrep(), qdescription->charrep(), qx->getData(), qy->getData(), qw->getData(), qh->getData(), qreportid->getData(), qtyp->getData(),  qID->getData());
		}
	}
}



class lbPluginReportElementsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementsDBReaderExtension();
	
	virtual ~lbPluginReportElementsDBReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementsDBReaderExtension, lbPluginReportElementsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportElementsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementsDBReaderExtension::lbPluginReportElementsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementsDBReaderExtension::lbPluginReportElementsDBReaderExtension() called.\n" LOG_
}

lbPluginReportElementsDBReaderExtension::~lbPluginReportElementsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementsDBReaderExtension::~lbPluginReportElementsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {
		ReportElementsDBReaderExtension* ReportElementsModelExtension = new ReportElementsDBReaderExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementsDBReaderExtension* ReportElementsModelExtension = new ReportElementsDBReaderExtension();
		
	
		QI(ReportElementsModelExtension, lb_I_Unknown, ukReportElementsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementsModelExtension.getPtr();
	ukReportElementsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementsModelExtension != NULL) {
                ukReportElementsModelExtension--;
                ukReportElementsModelExtension.resetPtr();
        }
}

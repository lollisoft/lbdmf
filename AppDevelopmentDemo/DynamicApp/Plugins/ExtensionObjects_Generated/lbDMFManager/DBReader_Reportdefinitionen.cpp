
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
#include <DBReader_Reportdefinitionen.h>

IMPLEMENT_FUNCTOR(instanceOfReportdefinitionenDBReaderExtension, ReportdefinitionenDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportdefinitionenDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportdefinitionenDBReaderExtension::ReportdefinitionenDBReaderExtension() {
	_CL_VERBOSE << "ReportdefinitionenDBReaderExtension::ReportdefinitionenDBReaderExtension() called." LOG_
}

ReportdefinitionenDBReaderExtension::~ReportdefinitionenDBReaderExtension() {
	_CL_VERBOSE << "ReportdefinitionenDBReaderExtension::~ReportdefinitionenDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportdefinitionenDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportdefinitionenDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportdefinitionenDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Reportdefinitionen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportdefinitionenDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Reportdefinitionen." LOG_
		}
	} else {
		_LOG << "Error: ReportdefinitionenDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportdefinitionenDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportdefinitionenDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportdefinitionenDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportdefinitionenDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportdefinitionenDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select description, name,  id from reports") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Reportdefinitionen would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Reportdefinitionen found. All Reportdefinitionen may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qdescription)
		UAP(lb_I_String, qname)

		// Copy values

		qdescription = q->getAsString(1);
		qname = q->getAsString(2);
		qID = q->getAsLong(3);

		owningObject->addReportdefinitionen(qdescription->charrep(), qname->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qdescription = q->getAsString(1);
			qname = q->getAsString(2);
			qID = q->getAsLong(3);

			owningObject->addReportdefinitionen(qdescription->charrep(), qname->charrep(),  qID->getData());
		}
	}
}



class lbPluginReportdefinitionenDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportdefinitionenDBReaderExtension();
	
	virtual ~lbPluginReportdefinitionenDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportdefinitionenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportdefinitionenDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportdefinitionenDBReaderExtension, lbPluginReportdefinitionenDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportdefinitionenDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportdefinitionenDBReaderExtension::lbPluginReportdefinitionenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportdefinitionenDBReaderExtension::lbPluginReportdefinitionenDBReaderExtension() called.\n" LOG_
}

lbPluginReportdefinitionenDBReaderExtension::~lbPluginReportdefinitionenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportdefinitionenDBReaderExtension::~lbPluginReportdefinitionenDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportdefinitionenModelExtension == NULL) {
		ReportdefinitionenDBReaderExtension* ReportdefinitionenModelExtension = new ReportdefinitionenDBReaderExtension();
		
	
		QI(ReportdefinitionenModelExtension, lb_I_Unknown, ukReportdefinitionenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportdefinitionenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportdefinitionenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportdefinitionenDBReaderExtension* ReportdefinitionenModelExtension = new ReportdefinitionenDBReaderExtension();
		
	
		QI(ReportdefinitionenModelExtension, lb_I_Unknown, ukReportdefinitionenModelExtension)
	}
	
	lb_I_Unknown* r = ukReportdefinitionenModelExtension.getPtr();
	ukReportdefinitionenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportdefinitionenDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportdefinitionenModelExtension != NULL) {
                ukReportdefinitionenModelExtension--;
                ukReportdefinitionenModelExtension.resetPtr();
        }
}

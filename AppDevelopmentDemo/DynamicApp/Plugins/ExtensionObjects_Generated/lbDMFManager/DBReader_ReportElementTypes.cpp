
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
#include <DBReader_ReportElementTypes.h>

IMPLEMENT_FUNCTOR(instanceOfReportElementTypesDBReaderExtension, ReportElementTypesDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportElementTypesDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportElementTypesDBReaderExtension::ReportElementTypesDBReaderExtension() {
	_CL_VERBOSE << "ReportElementTypesDBReaderExtension::ReportElementTypesDBReaderExtension() called." LOG_
}

ReportElementTypesDBReaderExtension::~ReportElementTypesDBReaderExtension() {
	_CL_VERBOSE << "ReportElementTypesDBReaderExtension::~ReportElementTypesDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportElementTypesDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportElementTypesDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportElementTypesDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportElementTypes, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportElementTypesDBReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportElementTypes." LOG_
		}
	} else {
		_LOG << "Error: ReportElementTypesDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementTypesDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportElementTypesDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportElementTypesDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportElementTypesDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportElementTypesDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, description,  id from report_element_types") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read ReportElementTypes would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No ReportElementTypes found. All ReportElementTypes may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qname)
		UAP(lb_I_String, qdescription)

		// Copy values

		qname = q->getAsString(1);
		qdescription = q->getAsString(2);
		qID = q->getAsLong(3);

		owningObject->addReportElementTypes(qname->charrep(), qdescription->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qname = q->getAsString(1);
			qdescription = q->getAsString(2);
			qID = q->getAsLong(3);

			owningObject->addReportElementTypes(qname->charrep(), qdescription->charrep(),  qID->getData());
		}
	}
}



class lbPluginReportElementTypesDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportElementTypesDBReaderExtension();
	
	virtual ~lbPluginReportElementTypesDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportElementTypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportElementTypesDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportElementTypesDBReaderExtension, lbPluginReportElementTypesDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportElementTypesDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportElementTypesDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportElementTypesDBReaderExtension::lbPluginReportElementTypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementTypesDBReaderExtension::lbPluginReportElementTypesDBReaderExtension() called.\n" LOG_
}

lbPluginReportElementTypesDBReaderExtension::~lbPluginReportElementTypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportElementTypesDBReaderExtension::~lbPluginReportElementTypesDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportElementTypesDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportElementTypesDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportElementTypesDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportElementTypesDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModelExtension == NULL) {
		ReportElementTypesDBReaderExtension* ReportElementTypesModelExtension = new ReportElementTypesDBReaderExtension();
		
	
		QI(ReportElementTypesModelExtension, lb_I_Unknown, ukReportElementTypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportElementTypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportElementTypesDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportElementTypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportElementTypesDBReaderExtension* ReportElementTypesModelExtension = new ReportElementTypesDBReaderExtension();
		
	
		QI(ReportElementTypesModelExtension, lb_I_Unknown, ukReportElementTypesModelExtension)
	}
	
	lb_I_Unknown* r = ukReportElementTypesModelExtension.getPtr();
	ukReportElementTypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportElementTypesDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportElementTypesModelExtension != NULL) {
                ukReportElementTypesModelExtension--;
                ukReportElementTypesModelExtension.resetPtr();
        }
}

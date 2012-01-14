
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
#include <DBReader_Reports.h>

IMPLEMENT_FUNCTOR(instanceOfReportsDBReaderExtension, ReportsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ReportsDBReaderExtension::ReportsDBReaderExtension() {
	_CL_VERBOSE << "ReportsDBReaderExtension::ReportsDBReaderExtension() called." LOG_
}

ReportsDBReaderExtension::~ReportsDBReaderExtension() {
	_CL_VERBOSE << "ReportsDBReaderExtension::~ReportsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Reports, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Reports." LOG_
		}
	} else {
		_LOG << "Error: ReportsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select description, name,  id from reports") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Reports would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Reports found. All Reports may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qdescription)
		UAP(lb_I_String, qname)

		// Copy values

		qdescription = q->getAsString(1);
		qname = q->getAsString(2);
		qID = q->getAsLong(3);

		owningObject->addReports(qdescription->charrep(), qname->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qdescription = q->getAsString(1);
			qname = q->getAsString(2);
			qID = q->getAsLong(3);

			owningObject->addReports(qdescription->charrep(), qname->charrep(),  qID->getData());
		}
	}
}



class lbPluginReportsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportsDBReaderExtension();
	
	virtual ~lbPluginReportsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukReportsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportsDBReaderExtension, lbPluginReportsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportsDBReaderExtension::lbPluginReportsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportsDBReaderExtension::lbPluginReportsDBReaderExtension() called.\n" LOG_
}

lbPluginReportsDBReaderExtension::~lbPluginReportsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportsDBReaderExtension::~lbPluginReportsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportsModelExtension == NULL) {
		ReportsDBReaderExtension* ReportsModelExtension = new ReportsDBReaderExtension();
		
	
		QI(ReportsModelExtension, lb_I_Unknown, ukReportsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportsDBReaderExtension* ReportsModelExtension = new ReportsDBReaderExtension();
		
	
		QI(ReportsModelExtension, lb_I_Unknown, ukReportsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportsModelExtension.getPtr();
	ukReportsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportsModelExtension != NULL) {
                ukReportsModelExtension--;
                ukReportsModelExtension.resetPtr();
        }
}

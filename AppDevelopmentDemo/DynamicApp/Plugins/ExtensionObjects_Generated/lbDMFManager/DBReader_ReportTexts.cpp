
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
#include <DBReader_ReportTexts.h>

IMPLEMENT_FUNCTOR(instanceOfReportTextsDBReaderExtension, ReportTextsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ReportTextsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ReportTextsDBReaderExtension::ReportTextsDBReaderExtension() {
	_CL_VERBOSE << "ReportTextsDBReaderExtension::ReportTextsDBReaderExtension() called." LOG_
}

ReportTextsDBReaderExtension::~ReportTextsDBReaderExtension() {
	_CL_VERBOSE << "ReportTextsDBReaderExtension::~ReportTextsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ReportTextsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ReportTextsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ReportTextsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ReportTexts, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ReportTextsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_ReportTexts." LOG_
		}
	} else {
		_LOG << "Error: ReportTextsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportTextsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ReportTextsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ReportTextsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ReportTextsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ReportTextsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select line, text, elementid,  id from report_texts") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read ReportTexts would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No ReportTexts found. All ReportTexts may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_Long, qline)
		UAP(lb_I_String, qtext)
		UAP(lb_I_Long, qelementid)

		// Copy values

		qline = q->getAsLong(1);
		qtext = q->getAsString(2);
		qelementid = q->getAsLong(3);
		qID = q->getAsLong(4);

		owningObject->addReportTexts(qline->getData(), qtext->charrep(), qelementid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qline = q->getAsLong(1);
			qtext = q->getAsString(2);
			qelementid = q->getAsLong(3);
			qID = q->getAsLong(4);

			owningObject->addReportTexts(qline->getData(), qtext->charrep(), qelementid->getData(),  qID->getData());
		}
	}
}



class lbPluginReportTextsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginReportTextsDBReaderExtension();
	
	virtual ~lbPluginReportTextsDBReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginReportTextsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginReportTextsDBReaderExtension, lbPluginReportTextsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginReportTextsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginReportTextsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginReportTextsDBReaderExtension::lbPluginReportTextsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportTextsDBReaderExtension::lbPluginReportTextsDBReaderExtension() called.\n" LOG_
}

lbPluginReportTextsDBReaderExtension::~lbPluginReportTextsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginReportTextsDBReaderExtension::~lbPluginReportTextsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginReportTextsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginReportTextsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginReportTextsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginReportTextsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModelExtension == NULL) {
		ReportTextsDBReaderExtension* ReportTextsModelExtension = new ReportTextsDBReaderExtension();
		
	
		QI(ReportTextsModelExtension, lb_I_Unknown, ukReportTextsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukReportTextsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginReportTextsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukReportTextsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ReportTextsDBReaderExtension* ReportTextsModelExtension = new ReportTextsDBReaderExtension();
		
	
		QI(ReportTextsModelExtension, lb_I_Unknown, ukReportTextsModelExtension)
	}
	
	lb_I_Unknown* r = ukReportTextsModelExtension.getPtr();
	ukReportTextsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginReportTextsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukReportTextsModelExtension != NULL) {
                ukReportTextsModelExtension--;
                ukReportTextsModelExtension.resetPtr();
        }
}

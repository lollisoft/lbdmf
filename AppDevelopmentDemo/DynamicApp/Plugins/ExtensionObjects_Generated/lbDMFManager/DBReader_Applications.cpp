
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
#include <DBReader_Applications.h>

IMPLEMENT_FUNCTOR(instanceOfApplicationsDBReaderExtension, ApplicationsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ApplicationsDBReaderExtension::ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "ApplicationsDBReaderExtension::ApplicationsDBReaderExtension() called." LOG_
}

ApplicationsDBReaderExtension::~ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "ApplicationsDBReaderExtension::~ApplicationsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ApplicationsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ApplicationsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ApplicationsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Applications, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ApplicationsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Applications." LOG_
		}
	} else {
		_LOG << "Error: ApplicationsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ApplicationsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ApplicationsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ApplicationsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select titel, name, interface, functor, modulename,  id from anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Applications would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Applications found. All Applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qtitel)
		UAP(lb_I_String, qname)
		UAP(lb_I_String, qinterface)
		UAP(lb_I_String, qfunctor)
		UAP(lb_I_String, qmodulename)

		// Copy values

		qtitel = q->getAsString(1);
		qname = q->getAsString(2);
		qinterface = q->getAsString(3);
		qfunctor = q->getAsString(4);
		qmodulename = q->getAsString(5);
		qID = q->getAsLong(6);

		owningObject->addApplications(qtitel->charrep(), qname->charrep(), qinterface->charrep(), qfunctor->charrep(), qmodulename->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qtitel = q->getAsString(1);
			qname = q->getAsString(2);
			qinterface = q->getAsString(3);
			qfunctor = q->getAsString(4);
			qmodulename = q->getAsString(5);
			qID = q->getAsLong(6);

			owningObject->addApplications(qtitel->charrep(), qname->charrep(), qinterface->charrep(), qfunctor->charrep(), qmodulename->charrep(),  qID->getData());
		}
	}
}



class lbPluginApplicationsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginApplicationsDBReaderExtension();
	
	virtual ~lbPluginApplicationsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationsDBReaderExtension, lbPluginApplicationsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginApplicationsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationsDBReaderExtension::lbPluginApplicationsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationsDBReaderExtension::lbPluginApplicationsDBReaderExtension() called.\n" LOG_
}

lbPluginApplicationsDBReaderExtension::~lbPluginApplicationsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationsDBReaderExtension::~lbPluginApplicationsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {
		ApplicationsDBReaderExtension* ApplicationsModelExtension = new ApplicationsDBReaderExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationsDBReaderExtension* ApplicationsModelExtension = new ApplicationsDBReaderExtension();
		
	
		QI(ApplicationsModelExtension, lb_I_Unknown, ukApplicationsModelExtension)
	}
	
	lb_I_Unknown* r = ukApplicationsModelExtension.getPtr();
	ukApplicationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationsModelExtension != NULL) {
                ukApplicationsModelExtension--;
                ukApplicationsModelExtension.resetPtr();
        }
}

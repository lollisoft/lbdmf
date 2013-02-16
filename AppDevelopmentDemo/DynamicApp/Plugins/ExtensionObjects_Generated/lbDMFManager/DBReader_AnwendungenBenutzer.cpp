
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
#include <DBReader_AnwendungenBenutzer.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungenBenutzerDBReaderExtension, AnwendungenBenutzerDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungenBenutzerDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AnwendungenBenutzerDBReaderExtension::AnwendungenBenutzerDBReaderExtension() {
	_CL_VERBOSE << "AnwendungenBenutzerDBReaderExtension::AnwendungenBenutzerDBReaderExtension() called." LOG_
}

AnwendungenBenutzerDBReaderExtension::~AnwendungenBenutzerDBReaderExtension() {
	_CL_VERBOSE << "AnwendungenBenutzerDBReaderExtension::~AnwendungenBenutzerDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungenBenutzerDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungenBenutzerDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AnwendungenBenutzerDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_AnwendungenBenutzer, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AnwendungenBenutzerDBReaderExtension::setOwningObject() owning parameter is not a lb_I_AnwendungenBenutzer." LOG_
		}
	} else {
		_LOG << "Error: AnwendungenBenutzerDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenBenutzerDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: AnwendungenBenutzerDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: AnwendungenBenutzerDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenBenutzerDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "AnwendungenBenutzerDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select userid, anwendungenid,  id from user_anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read AnwendungenBenutzer would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No AnwendungenBenutzer found. All AnwendungenBenutzer may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_Long, quserid)
		UAP(lb_I_Long, qanwendungenid)

		// Copy values

		quserid = q->getAsLong(1);
		qanwendungenid = q->getAsLong(2);
		qID = q->getAsLong(3);

		owningObject->addAnwendungenBenutzer(quserid->getData(), qanwendungenid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			quserid = q->getAsLong(1);
			qanwendungenid = q->getAsLong(2);
			qID = q->getAsLong(3);

			owningObject->addAnwendungenBenutzer(quserid->getData(), qanwendungenid->getData(),  qID->getData());
		}
	}
}



class lbPluginAnwendungenBenutzerDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAnwendungenBenutzerDBReaderExtension();
	
	virtual ~lbPluginAnwendungenBenutzerDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungenBenutzerDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungenBenutzerDBReaderExtension, lbPluginAnwendungenBenutzerDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungenBenutzerDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungenBenutzerDBReaderExtension::lbPluginAnwendungenBenutzerDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerDBReaderExtension::lbPluginAnwendungenBenutzerDBReaderExtension() called.\n" LOG_
}

lbPluginAnwendungenBenutzerDBReaderExtension::~lbPluginAnwendungenBenutzerDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerDBReaderExtension::~lbPluginAnwendungenBenutzerDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModelExtension == NULL) {
		AnwendungenBenutzerDBReaderExtension* AnwendungenBenutzerModelExtension = new AnwendungenBenutzerDBReaderExtension();
		
	
		QI(AnwendungenBenutzerModelExtension, lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungenBenutzerModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungenBenutzerDBReaderExtension* AnwendungenBenutzerModelExtension = new AnwendungenBenutzerDBReaderExtension();
		
	
		QI(AnwendungenBenutzerModelExtension, lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
	}
	
	lb_I_Unknown* r = ukAnwendungenBenutzerModelExtension.getPtr();
	ukAnwendungenBenutzerModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungenBenutzerDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungenBenutzerModelExtension != NULL) {
                ukAnwendungenBenutzerModelExtension--;
                ukAnwendungenBenutzerModelExtension.resetPtr();
        }
}

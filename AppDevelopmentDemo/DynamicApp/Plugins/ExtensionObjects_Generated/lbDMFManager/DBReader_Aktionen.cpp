
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
#include <DBReader_Aktionen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionenDBReaderExtension, AktionenDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionenDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AktionenDBReaderExtension::AktionenDBReaderExtension() {
	_CL_VERBOSE << "AktionenDBReaderExtension::AktionenDBReaderExtension() called." LOG_
}

AktionenDBReaderExtension::~AktionenDBReaderExtension() {
	_CL_VERBOSE << "AktionenDBReaderExtension::~AktionenDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL AktionenDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionenDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AktionenDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Aktionen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AktionenDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Aktionen." LOG_
		}
	} else {
		_LOG << "Error: AktionenDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionenDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: AktionenDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: AktionenDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionenDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "AktionenDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select target, source, name, typ,  id from actions") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Aktionen would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Aktionen found. All Aktionen may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qtarget)
		UAP(lb_I_String, qsource)
		UAP(lb_I_String, qname)
		UAP(lb_I_Long, qtyp)

		// Copy values

		qtarget = q->getAsString(1);
		qsource = q->getAsString(2);
		qname = q->getAsString(3);
		qtyp = q->getAsLong(4);
		qID = q->getAsLong(5);

		owningObject->addAktionen(qtarget->charrep(), qsource->charrep(), qname->charrep(), qtyp->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qtarget = q->getAsString(1);
			qsource = q->getAsString(2);
			qname = q->getAsString(3);
			qtyp = q->getAsLong(4);
			qID = q->getAsLong(5);

			owningObject->addAktionen(qtarget->charrep(), qsource->charrep(), qname->charrep(), qtyp->getData(),  qID->getData());
		}
	}
}



class lbPluginAktionenDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAktionenDBReaderExtension();
	
	virtual ~lbPluginAktionenDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionenDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionenDBReaderExtension, lbPluginAktionenDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginAktionenDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionenDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionenDBReaderExtension::lbPluginAktionenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAktionenDBReaderExtension::lbPluginAktionenDBReaderExtension() called.\n" LOG_
}

lbPluginAktionenDBReaderExtension::~lbPluginAktionenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAktionenDBReaderExtension::~lbPluginAktionenDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionenDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionenDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionenDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAktionenDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModelExtension == NULL) {
		AktionenDBReaderExtension* AktionenModelExtension = new AktionenDBReaderExtension();
		
	
		QI(AktionenModelExtension, lb_I_Unknown, ukAktionenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionenDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionenDBReaderExtension* AktionenModelExtension = new AktionenDBReaderExtension();
		
	
		QI(AktionenModelExtension, lb_I_Unknown, ukAktionenModelExtension)
	}
	
	lb_I_Unknown* r = ukAktionenModelExtension.getPtr();
	ukAktionenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionenDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionenModelExtension != NULL) {
                ukAktionenModelExtension--;
                ukAktionenModelExtension.resetPtr();
        }
}

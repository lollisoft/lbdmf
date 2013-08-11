
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
#include <DBReader_Actions.h>

IMPLEMENT_FUNCTOR(instanceOfActionsDBReaderExtension, ActionsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ActionsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ActionsDBReaderExtension::ActionsDBReaderExtension() {
	_CL_VERBOSE << "ActionsDBReaderExtension::ActionsDBReaderExtension() called." LOG_
}

ActionsDBReaderExtension::~ActionsDBReaderExtension() {
	_CL_VERBOSE << "ActionsDBReaderExtension::~ActionsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ActionsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ActionsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ActionsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Actions, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ActionsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Actions." LOG_
		}
	} else {
		_LOG << "Error: ActionsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ActionsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ActionsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ActionsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select target, source, name, typ, anwendungenid,  id from actions") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Actions would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Actions found. All Actions may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qtarget)
		UAP(lb_I_String, qsource)
		UAP(lb_I_String, qname)
		UAP(lb_I_Long, qtyp)
		UAP(lb_I_Long, qanwendungenid)

		// Copy values

		qtarget = q->getAsString(1);
		qsource = q->getAsString(2);
		qname = q->getAsString(3);
		qtyp = q->getAsLong(4);
		qanwendungenid = q->getAsLong(5);
		qID = q->getAsLong(6);

		owningObject->add(qtarget->charrep(), qsource->charrep(), qname->charrep(), qtyp->getData(), qanwendungenid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qtarget = q->getAsString(1);
			qsource = q->getAsString(2);
			qname = q->getAsString(3);
			qtyp = q->getAsLong(4);
			qanwendungenid = q->getAsLong(5);
			qID = q->getAsLong(6);

			owningObject->add(qtarget->charrep(), qsource->charrep(), qname->charrep(), qtyp->getData(), qanwendungenid->getData(),  qID->getData());
		}
	}
}



class lbPluginActionsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginActionsDBReaderExtension();
	
	virtual ~lbPluginActionsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionsDBReaderExtension, lbPluginActionsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginActionsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionsDBReaderExtension::lbPluginActionsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginActionsDBReaderExtension::lbPluginActionsDBReaderExtension() called.\n" LOG_
}

lbPluginActionsDBReaderExtension::~lbPluginActionsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginActionsDBReaderExtension::~lbPluginActionsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginActionsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModelExtension == NULL) {
		ActionsDBReaderExtension* ActionsModelExtension = new ActionsDBReaderExtension();
		
	
		QI(ActionsModelExtension, lb_I_Unknown, ukActionsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ActionsDBReaderExtension* ActionsModelExtension = new ActionsDBReaderExtension();
		
	
		QI(ActionsModelExtension, lb_I_Unknown, ukActionsModelExtension)
	}
	
	lb_I_Unknown* r = ukActionsModelExtension.getPtr();
	ukActionsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionsModelExtension != NULL) {
                ukActionsModelExtension--;
                ukActionsModelExtension.resetPtr();
        }
}

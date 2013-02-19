
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
#include <DBReader_Action_Steps.h>

IMPLEMENT_FUNCTOR(instanceOfAction_StepsDBReaderExtension, Action_StepsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_StepsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_StepsDBReaderExtension::Action_StepsDBReaderExtension() {
	_CL_VERBOSE << "Action_StepsDBReaderExtension::Action_StepsDBReaderExtension() called." LOG_
}

Action_StepsDBReaderExtension::~Action_StepsDBReaderExtension() {
	_CL_VERBOSE << "Action_StepsDBReaderExtension::~Action_StepsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_StepsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_StepsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_StepsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Steps, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_StepsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Action_Steps." LOG_
		}
	} else {
		_LOG << "Error: Action_StepsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_StepsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Action_StepsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Action_StepsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_StepsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Action_StepsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select bezeichnung, what, a_order_nr, type, actionid,  id from action_steps") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Action_Steps would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Action_Steps found. All Action_Steps may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qbezeichnung)
		UAP(lb_I_String, qwhat)
		UAP(lb_I_Long, qa_order_nr)
		UAP(lb_I_Long, qtype)
		UAP(lb_I_Long, qactionid)

		// Copy values

		qbezeichnung = q->getAsString(1);
		qwhat = q->getAsString(2);
		qa_order_nr = q->getAsLong(3);
		qtype = q->getAsLong(4);
		qactionid = q->getAsLong(5);
		qID = q->getAsLong(6);

		owningObject->add(qbezeichnung->charrep(), qwhat->charrep(), qa_order_nr->getData(), qtype->getData(), qactionid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qbezeichnung = q->getAsString(1);
			qwhat = q->getAsString(2);
			qa_order_nr = q->getAsLong(3);
			qtype = q->getAsLong(4);
			qactionid = q->getAsLong(5);
			qID = q->getAsLong(6);

			owningObject->add(qbezeichnung->charrep(), qwhat->charrep(), qa_order_nr->getData(), qtype->getData(), qactionid->getData(),  qID->getData());
		}
	}
}



class lbPluginAction_StepsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_StepsDBReaderExtension();
	
	virtual ~lbPluginAction_StepsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_StepsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_StepsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_StepsDBReaderExtension, lbPluginAction_StepsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginAction_StepsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_StepsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_StepsDBReaderExtension::lbPluginAction_StepsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_StepsDBReaderExtension::lbPluginAction_StepsDBReaderExtension() called.\n" LOG_
}

lbPluginAction_StepsDBReaderExtension::~lbPluginAction_StepsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_StepsDBReaderExtension::~lbPluginAction_StepsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_StepsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_StepsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_StepsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_StepsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModelExtension == NULL) {
		Action_StepsDBReaderExtension* Action_StepsModelExtension = new Action_StepsDBReaderExtension();
		
	
		QI(Action_StepsModelExtension, lb_I_Unknown, ukAction_StepsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_StepsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_StepsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_StepsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_StepsDBReaderExtension* Action_StepsModelExtension = new Action_StepsDBReaderExtension();
		
	
		QI(Action_StepsModelExtension, lb_I_Unknown, ukAction_StepsModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_StepsModelExtension.getPtr();
	ukAction_StepsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_StepsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_StepsModelExtension != NULL) {
                ukAction_StepsModelExtension--;
                ukAction_StepsModelExtension.resetPtr();
        }
}

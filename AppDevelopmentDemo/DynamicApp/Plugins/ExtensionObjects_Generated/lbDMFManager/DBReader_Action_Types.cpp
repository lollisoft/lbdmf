
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
#include <DBReader_Action_Types.h>

IMPLEMENT_FUNCTOR(instanceOfAction_TypesDBReaderExtension, Action_TypesDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_TypesDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_TypesDBReaderExtension::Action_TypesDBReaderExtension() {
	_CL_VERBOSE << "Action_TypesDBReaderExtension::Action_TypesDBReaderExtension() called." LOG_
}

Action_TypesDBReaderExtension::~Action_TypesDBReaderExtension() {
	_CL_VERBOSE << "Action_TypesDBReaderExtension::~Action_TypesDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_TypesDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_TypesDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_TypesDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Types, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_TypesDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Action_Types." LOG_
		}
	} else {
		_LOG << "Error: Action_TypesDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_TypesDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Action_TypesDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Action_TypesDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_TypesDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Action_TypesDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select bezeichnung, action_handler, module,  id from action_types") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Action_Types would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Action_Types found. All Action_Types may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qbezeichnung)
		UAP(lb_I_String, qaction_handler)
		UAP(lb_I_String, qmodule)

		// Copy values

		qbezeichnung = q->getAsString(1);
		qaction_handler = q->getAsString(2);
		qmodule = q->getAsString(3);
		qID = q->getAsLong(4);

		owningObject->add(qbezeichnung->charrep(), qaction_handler->charrep(), qmodule->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qbezeichnung = q->getAsString(1);
			qaction_handler = q->getAsString(2);
			qmodule = q->getAsString(3);
			qID = q->getAsLong(4);

			owningObject->add(qbezeichnung->charrep(), qaction_handler->charrep(), qmodule->charrep(),  qID->getData());
		}
	}
}



class lbPluginAction_TypesDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_TypesDBReaderExtension();
	
	virtual ~lbPluginAction_TypesDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_TypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_TypesDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_TypesDBReaderExtension, lbPluginAction_TypesDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginAction_TypesDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_TypesDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_TypesDBReaderExtension::lbPluginAction_TypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_TypesDBReaderExtension::lbPluginAction_TypesDBReaderExtension() called.\n" LOG_
}

lbPluginAction_TypesDBReaderExtension::~lbPluginAction_TypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_TypesDBReaderExtension::~lbPluginAction_TypesDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_TypesDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_TypesDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_TypesDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_TypesDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModelExtension == NULL) {
		Action_TypesDBReaderExtension* Action_TypesModelExtension = new Action_TypesDBReaderExtension();
		
	
		QI(Action_TypesModelExtension, lb_I_Unknown, ukAction_TypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_TypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_TypesDBReaderExtension* Action_TypesModelExtension = new Action_TypesDBReaderExtension();
		
	
		QI(Action_TypesModelExtension, lb_I_Unknown, ukAction_TypesModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_TypesModelExtension.getPtr();
	ukAction_TypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_TypesDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_TypesModelExtension != NULL) {
                ukAction_TypesModelExtension--;
                ukAction_TypesModelExtension.resetPtr();
        }
}


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
#include <DBReader_Action_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOfAction_ParametersDBReaderExtension, Action_ParametersDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_ParametersDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_ParametersDBReaderExtension::Action_ParametersDBReaderExtension() {
	_CL_VERBOSE << "Action_ParametersDBReaderExtension::Action_ParametersDBReaderExtension() called." LOG_
}

Action_ParametersDBReaderExtension::~Action_ParametersDBReaderExtension() {
	_CL_VERBOSE << "Action_ParametersDBReaderExtension::~Action_ParametersDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_ParametersDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_ParametersDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_ParametersDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Parameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_ParametersDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Action_Parameters." LOG_
		}
	} else {
		_LOG << "Error: Action_ParametersDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_ParametersDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Action_ParametersDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Action_ParametersDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_ParametersDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Action_ParametersDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, value, interface, description, actionid,  id from action_parameters") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Action_Parameters would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Action_Parameters found. All Action_Parameters may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qname)
		UAP(lb_I_String, qvalue)
		UAP(lb_I_String, qinterface)
		UAP(lb_I_String, qdescription)
		UAP(lb_I_Long, qactionid)

		// Copy values

		qname = q->getAsString(1);
		qvalue = q->getAsString(2);
		qinterface = q->getAsString(3);
		qdescription = q->getAsString(4);
		qactionid = q->getAsLong(5);
		qID = q->getAsLong(6);

		owningObject->add(qname->charrep(), qvalue->charrep(), qinterface->charrep(), qdescription->charrep(), qactionid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qname = q->getAsString(1);
			qvalue = q->getAsString(2);
			qinterface = q->getAsString(3);
			qdescription = q->getAsString(4);
			qactionid = q->getAsLong(5);
			qID = q->getAsLong(6);

			owningObject->add(qname->charrep(), qvalue->charrep(), qinterface->charrep(), qdescription->charrep(), qactionid->getData(),  qID->getData());
		}
	}
}



class lbPluginAction_ParametersDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_ParametersDBReaderExtension();
	
	virtual ~lbPluginAction_ParametersDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_ParametersModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_ParametersDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_ParametersDBReaderExtension, lbPluginAction_ParametersDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginAction_ParametersDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_ParametersDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_ParametersDBReaderExtension::lbPluginAction_ParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_ParametersDBReaderExtension::lbPluginAction_ParametersDBReaderExtension() called.\n" LOG_
}

lbPluginAction_ParametersDBReaderExtension::~lbPluginAction_ParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_ParametersDBReaderExtension::~lbPluginAction_ParametersDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_ParametersDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_ParametersDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_ParametersDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_ParametersDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModelExtension == NULL) {
		Action_ParametersDBReaderExtension* Action_ParametersModelExtension = new Action_ParametersDBReaderExtension();
		
	
		QI(Action_ParametersModelExtension, lb_I_Unknown, ukAction_ParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_ParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_ParametersDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_ParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_ParametersDBReaderExtension* Action_ParametersModelExtension = new Action_ParametersDBReaderExtension();
		
	
		QI(Action_ParametersModelExtension, lb_I_Unknown, ukAction_ParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_ParametersModelExtension.getPtr();
	ukAction_ParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_ParametersDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_ParametersModelExtension != NULL) {
                ukAction_ParametersModelExtension--;
                ukAction_ParametersModelExtension.resetPtr();
        }
}

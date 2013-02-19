
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
#include <DBReader_ActionStep_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOfActionStep_ParametersDBReaderExtension, ActionStep_ParametersDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ActionStep_ParametersDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ActionStep_ParametersDBReaderExtension::ActionStep_ParametersDBReaderExtension() {
	_CL_VERBOSE << "ActionStep_ParametersDBReaderExtension::ActionStep_ParametersDBReaderExtension() called." LOG_
}

ActionStep_ParametersDBReaderExtension::~ActionStep_ParametersDBReaderExtension() {
	_CL_VERBOSE << "ActionStep_ParametersDBReaderExtension::~ActionStep_ParametersDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ActionStep_ParametersDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ActionStep_ParametersDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ActionStep_ParametersDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ActionStep_Parameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ActionStep_ParametersDBReaderExtension::setOwningObject() owning parameter is not a lb_I_ActionStep_Parameters." LOG_
		}
	} else {
		_LOG << "Error: ActionStep_ParametersDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: ActionStep_ParametersDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: ActionStep_ParametersDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "ActionStep_ParametersDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select description, name, value, interface, action_step_id,  id from action_step_parameter") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read ActionStep_Parameters would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No ActionStep_Parameters found. All ActionStep_Parameters may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qdescription)
		UAP(lb_I_String, qname)
		UAP(lb_I_String, qvalue)
		UAP(lb_I_String, qinterface)
		UAP(lb_I_Long, qaction_step_id)

		// Copy values

		qdescription = q->getAsString(1);
		qname = q->getAsString(2);
		qvalue = q->getAsString(3);
		qinterface = q->getAsString(4);
		qaction_step_id = q->getAsLong(5);
		qID = q->getAsLong(6);

		owningObject->add(qdescription->charrep(), qname->charrep(), qvalue->charrep(), qinterface->charrep(), qaction_step_id->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qdescription = q->getAsString(1);
			qname = q->getAsString(2);
			qvalue = q->getAsString(3);
			qinterface = q->getAsString(4);
			qaction_step_id = q->getAsLong(5);
			qID = q->getAsLong(6);

			owningObject->add(qdescription->charrep(), qname->charrep(), qvalue->charrep(), qinterface->charrep(), qaction_step_id->getData(),  qID->getData());
		}
	}
}



class lbPluginActionStep_ParametersDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginActionStep_ParametersDBReaderExtension();
	
	virtual ~lbPluginActionStep_ParametersDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionStep_ParametersModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStep_ParametersDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStep_ParametersDBReaderExtension, lbPluginActionStep_ParametersDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStep_ParametersDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionStep_ParametersDBReaderExtension::lbPluginActionStep_ParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersDBReaderExtension::lbPluginActionStep_ParametersDBReaderExtension() called.\n" LOG_
}

lbPluginActionStep_ParametersDBReaderExtension::~lbPluginActionStep_ParametersDBReaderExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersDBReaderExtension::~lbPluginActionStep_ParametersDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {
		ActionStep_ParametersDBReaderExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersDBReaderExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionStep_ParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ActionStep_ParametersDBReaderExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersDBReaderExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukActionStep_ParametersModelExtension.getPtr();
	ukActionStep_ParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionStep_ParametersDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionStep_ParametersModelExtension != NULL) {
                ukActionStep_ParametersModelExtension--;
                ukActionStep_ParametersModelExtension.resetPtr();
        }
}

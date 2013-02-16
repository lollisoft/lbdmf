
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
#include <DBReader_Formularaktionenzuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfFormularaktionenzuordnenDBReaderExtension, FormularaktionenzuordnenDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularaktionenzuordnenDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormularaktionenzuordnenDBReaderExtension::FormularaktionenzuordnenDBReaderExtension() {
	_CL_VERBOSE << "FormularaktionenzuordnenDBReaderExtension::FormularaktionenzuordnenDBReaderExtension() called." LOG_
}

FormularaktionenzuordnenDBReaderExtension::~FormularaktionenzuordnenDBReaderExtension() {
	_CL_VERBOSE << "FormularaktionenzuordnenDBReaderExtension::~FormularaktionenzuordnenDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormularaktionenzuordnenDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularaktionenzuordnenDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormularaktionenzuordnenDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formularaktionenzuordnen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormularaktionenzuordnenDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Formularaktionenzuordnen." LOG_
		}
	} else {
		_LOG << "Error: FormularaktionenzuordnenDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularaktionenzuordnenDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: FormularaktionenzuordnenDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: FormularaktionenzuordnenDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularaktionenzuordnenDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FormularaktionenzuordnenDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select event, action, formular,  id from formular_actions") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Formularaktionenzuordnen would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formularaktionenzuordnen found. All Formularaktionenzuordnen may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qevent)
		UAP(lb_I_Long, qaction)
		UAP(lb_I_Long, qformular)

		// Copy values

		qevent = q->getAsString(1);
		qaction = q->getAsLong(2);
		qformular = q->getAsLong(3);
		qID = q->getAsLong(4);

		owningObject->addFormularaktionenzuordnen(qevent->charrep(), qaction->getData(), qformular->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qevent = q->getAsString(1);
			qaction = q->getAsLong(2);
			qformular = q->getAsLong(3);
			qID = q->getAsLong(4);

			owningObject->addFormularaktionenzuordnen(qevent->charrep(), qaction->getData(), qformular->getData(),  qID->getData());
		}
	}
}



class lbPluginFormularaktionenzuordnenDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormularaktionenzuordnenDBReaderExtension();
	
	virtual ~lbPluginFormularaktionenzuordnenDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularaktionenzuordnenDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularaktionenzuordnenDBReaderExtension, lbPluginFormularaktionenzuordnenDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularaktionenzuordnenDBReaderExtension::lbPluginFormularaktionenzuordnenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenDBReaderExtension::lbPluginFormularaktionenzuordnenDBReaderExtension() called.\n" LOG_
}

lbPluginFormularaktionenzuordnenDBReaderExtension::~lbPluginFormularaktionenzuordnenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenDBReaderExtension::~lbPluginFormularaktionenzuordnenDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModelExtension == NULL) {
		FormularaktionenzuordnenDBReaderExtension* FormularaktionenzuordnenModelExtension = new FormularaktionenzuordnenDBReaderExtension();
		
	
		QI(FormularaktionenzuordnenModelExtension, lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularaktionenzuordnenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularaktionenzuordnenDBReaderExtension* FormularaktionenzuordnenModelExtension = new FormularaktionenzuordnenDBReaderExtension();
		
	
		QI(FormularaktionenzuordnenModelExtension, lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
	}
	
	lb_I_Unknown* r = ukFormularaktionenzuordnenModelExtension.getPtr();
	ukFormularaktionenzuordnenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularaktionenzuordnenModelExtension != NULL) {
                ukFormularaktionenzuordnenModelExtension--;
                ukFormularaktionenzuordnenModelExtension.resetPtr();
        }
}

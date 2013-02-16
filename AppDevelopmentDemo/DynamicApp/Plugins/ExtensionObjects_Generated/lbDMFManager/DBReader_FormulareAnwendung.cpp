
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
#include <DBReader_FormulareAnwendung.h>

IMPLEMENT_FUNCTOR(instanceOfFormulareAnwendungDBReaderExtension, FormulareAnwendungDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormulareAnwendungDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormulareAnwendungDBReaderExtension::FormulareAnwendungDBReaderExtension() {
	_CL_VERBOSE << "FormulareAnwendungDBReaderExtension::FormulareAnwendungDBReaderExtension() called." LOG_
}

FormulareAnwendungDBReaderExtension::~FormulareAnwendungDBReaderExtension() {
	_CL_VERBOSE << "FormulareAnwendungDBReaderExtension::~FormulareAnwendungDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormulareAnwendungDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormulareAnwendungDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormulareAnwendungDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_FormulareAnwendung, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormulareAnwendungDBReaderExtension::setOwningObject() owning parameter is not a lb_I_FormulareAnwendung." LOG_
		}
	} else {
		_LOG << "Error: FormulareAnwendungDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareAnwendungDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: FormulareAnwendungDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: FormulareAnwendungDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormulareAnwendungDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FormulareAnwendungDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select anwendungid, formularid,  id from anwendungen_formulare") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read FormulareAnwendung would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No FormulareAnwendung found. All FormulareAnwendung may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_Long, qanwendungid)
		UAP(lb_I_Long, qformularid)

		// Copy values

		qanwendungid = q->getAsLong(1);
		qformularid = q->getAsLong(2);
		qID = q->getAsLong(3);

		owningObject->addFormulareAnwendung(qanwendungid->getData(), qformularid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qanwendungid = q->getAsLong(1);
			qformularid = q->getAsLong(2);
			qID = q->getAsLong(3);

			owningObject->addFormulareAnwendung(qanwendungid->getData(), qformularid->getData(),  qID->getData());
		}
	}
}



class lbPluginFormulareAnwendungDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormulareAnwendungDBReaderExtension();
	
	virtual ~lbPluginFormulareAnwendungDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormulareAnwendungModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormulareAnwendungDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormulareAnwendungDBReaderExtension, lbPluginFormulareAnwendungDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormulareAnwendungDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormulareAnwendungDBReaderExtension::lbPluginFormulareAnwendungDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormulareAnwendungDBReaderExtension::lbPluginFormulareAnwendungDBReaderExtension() called.\n" LOG_
}

lbPluginFormulareAnwendungDBReaderExtension::~lbPluginFormulareAnwendungDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormulareAnwendungDBReaderExtension::~lbPluginFormulareAnwendungDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareAnwendungModelExtension == NULL) {
		FormulareAnwendungDBReaderExtension* FormulareAnwendungModelExtension = new FormulareAnwendungDBReaderExtension();
		
	
		QI(FormulareAnwendungModelExtension, lb_I_Unknown, ukFormulareAnwendungModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormulareAnwendungModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormulareAnwendungModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormulareAnwendungDBReaderExtension* FormulareAnwendungModelExtension = new FormulareAnwendungDBReaderExtension();
		
	
		QI(FormulareAnwendungModelExtension, lb_I_Unknown, ukFormulareAnwendungModelExtension)
	}
	
	lb_I_Unknown* r = ukFormulareAnwendungModelExtension.getPtr();
	ukFormulareAnwendungModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormulareAnwendungDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormulareAnwendungModelExtension != NULL) {
                ukFormulareAnwendungModelExtension--;
                ukFormulareAnwendungModelExtension.resetPtr();
        }
}


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
#include <DBReader_Formular_Parameter.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_ParameterDBReaderExtension, Formular_ParameterDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_ParameterDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Formular_ParameterDBReaderExtension::Formular_ParameterDBReaderExtension() {
	_CL_VERBOSE << "Formular_ParameterDBReaderExtension::Formular_ParameterDBReaderExtension() called." LOG_
}

Formular_ParameterDBReaderExtension::~Formular_ParameterDBReaderExtension() {
	_CL_VERBOSE << "Formular_ParameterDBReaderExtension::~Formular_ParameterDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Formular_ParameterDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_ParameterDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_ParameterDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Parameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_ParameterDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Formular_Parameter." LOG_
		}
	} else {
		_LOG << "Error: Formular_ParameterDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ParameterDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Formular_ParameterDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Formular_ParameterDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ParameterDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Formular_ParameterDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select parametervalue, parametername, formularid,  id from formular_parameters") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Formular_Parameter would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Parameter found. All Formular_Parameter may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qparametervalue)
		UAP(lb_I_String, qparametername)
		UAP(lb_I_Long, qformularid)

		// Copy values

		qparametervalue = q->getAsString(1);
		qparametername = q->getAsString(2);
		qformularid = q->getAsLong(3);
		qID = q->getAsLong(4);

		owningObject->addFormular_Parameter(qparametervalue->charrep(), qparametername->charrep(), qformularid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qparametervalue = q->getAsString(1);
			qparametername = q->getAsString(2);
			qformularid = q->getAsLong(3);
			qID = q->getAsLong(4);

			owningObject->addFormular_Parameter(qparametervalue->charrep(), qparametername->charrep(), qformularid->getData(),  qID->getData());
		}
	}
}



class lbPluginFormular_ParameterDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormular_ParameterDBReaderExtension();
	
	virtual ~lbPluginFormular_ParameterDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_ParameterModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_ParameterDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_ParameterDBReaderExtension, lbPluginFormular_ParameterDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_ParameterDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_ParameterDBReaderExtension::lbPluginFormular_ParameterDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_ParameterDBReaderExtension::lbPluginFormular_ParameterDBReaderExtension() called.\n" LOG_
}

lbPluginFormular_ParameterDBReaderExtension::~lbPluginFormular_ParameterDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_ParameterDBReaderExtension::~lbPluginFormular_ParameterDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ParameterModelExtension == NULL) {
		Formular_ParameterDBReaderExtension* Formular_ParameterModelExtension = new Formular_ParameterDBReaderExtension();
		
	
		QI(Formular_ParameterModelExtension, lb_I_Unknown, ukFormular_ParameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_ParameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ParameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_ParameterDBReaderExtension* Formular_ParameterModelExtension = new Formular_ParameterDBReaderExtension();
		
	
		QI(Formular_ParameterModelExtension, lb_I_Unknown, ukFormular_ParameterModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_ParameterModelExtension.getPtr();
	ukFormular_ParameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_ParameterDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_ParameterModelExtension != NULL) {
                ukFormular_ParameterModelExtension--;
                ukFormular_ParameterModelExtension.resetPtr();
        }
}

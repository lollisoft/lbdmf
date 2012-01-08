
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
#include <DBReader_Formular_Fields.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_FieldsDBReaderExtension, Formular_FieldsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_FieldsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

Formular_FieldsDBReaderExtension::Formular_FieldsDBReaderExtension() {
	_CL_VERBOSE << "Formular_FieldsDBReaderExtension::Formular_FieldsDBReaderExtension() called." LOG_
}

Formular_FieldsDBReaderExtension::~Formular_FieldsDBReaderExtension() {
	_CL_VERBOSE << "Formular_FieldsDBReaderExtension::~Formular_FieldsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Formular_FieldsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_FieldsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_FieldsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Fields, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_FieldsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Formular_Fields." LOG_
		}
	} else {
		_LOG << "Error: Formular_FieldsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_FieldsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Formular_FieldsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Formular_FieldsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_FieldsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Formular_FieldsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select fkname, fktable, dbtype, isforeignkey, name, tablename, formularid,  id from formular_fields") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Formular_Fields would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Formular_Fields found. All Formular_Fields may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qfkname)
		UAP(lb_I_String, qfktable)
		UAP(lb_I_String, qdbtype)
		UAP(lb_I_Boolean, qisforeignkey)
		UAP(lb_I_String, qname)
		UAP(lb_I_String, qtablename)
		UAP(lb_I_Long, qformularid)

		// Copy values

		qfkname = q->getAsString(1);
		qfktable = q->getAsString(2);
		qdbtype = q->getAsString(3);
		UAP(lb_I_String, bisforeignkey)
		bisforeignkey = q->getAsString(4);
		if (*bisforeignkey == "true")
			qisforeignkey->setData(true);
		else
			qisforeignkey->setData(false);
		qname = q->getAsString(5);
		qtablename = q->getAsString(6);
		qformularid = q->getAsLong(7);
		qID = q->getAsLong(8);

		owningObject->addFormular_Fields(qfkname->charrep(), qfktable->charrep(), qdbtype->charrep(), qisforeignkey->getData(), qname->charrep(), qtablename->charrep(), qformularid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qfkname = q->getAsString(1);
			qfktable = q->getAsString(2);
			qdbtype = q->getAsString(3);
			UAP(lb_I_String, bisforeignkey)
			bisforeignkey = q->getAsString(4);
			if (*bisforeignkey == "true")
				qisforeignkey->setData(true);
			else
				qisforeignkey->setData(false);
			qname = q->getAsString(5);
			qtablename = q->getAsString(6);
			qformularid = q->getAsLong(7);
			qID = q->getAsLong(8);

			owningObject->addFormular_Fields(qfkname->charrep(), qfktable->charrep(), qdbtype->charrep(), qisforeignkey->charrep(), qname->charrep(), qtablename->charrep(), qformularid->getData(),  qID->getData());
		}
	}
}



class lbPluginFormular_FieldsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormular_FieldsDBReaderExtension();
	
	virtual ~lbPluginFormular_FieldsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_FieldsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_FieldsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_FieldsDBReaderExtension, lbPluginFormular_FieldsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_FieldsDBReaderExtension::lbPluginFormular_FieldsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension::lbPluginFormular_FieldsDBReaderExtension() called.\n" LOG_
}

lbPluginFormular_FieldsDBReaderExtension::~lbPluginFormular_FieldsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_FieldsDBReaderExtension::~lbPluginFormular_FieldsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {
		Formular_FieldsDBReaderExtension* Formular_FieldsModelExtension = new Formular_FieldsDBReaderExtension();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_FieldsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_FieldsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_FieldsDBReaderExtension* Formular_FieldsModelExtension = new Formular_FieldsDBReaderExtension();
		
	
		QI(Formular_FieldsModelExtension, lb_I_Unknown, ukFormular_FieldsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_FieldsModelExtension.getPtr();
	ukFormular_FieldsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_FieldsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_FieldsModelExtension != NULL) {
                ukFormular_FieldsModelExtension--;
                ukFormular_FieldsModelExtension.resetPtr();
        }
}

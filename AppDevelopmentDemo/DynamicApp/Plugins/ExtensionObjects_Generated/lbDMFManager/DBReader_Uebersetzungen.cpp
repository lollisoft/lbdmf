
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
#include <DBReader_Uebersetzungen.h>

IMPLEMENT_FUNCTOR(instanceOfUebersetzungenDBReaderExtension, UebersetzungenDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(UebersetzungenDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

UebersetzungenDBReaderExtension::UebersetzungenDBReaderExtension() {
	_CL_VERBOSE << "UebersetzungenDBReaderExtension::UebersetzungenDBReaderExtension() called." LOG_
}

UebersetzungenDBReaderExtension::~UebersetzungenDBReaderExtension() {
	_CL_VERBOSE << "UebersetzungenDBReaderExtension::~UebersetzungenDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL UebersetzungenDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: UebersetzungenDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL UebersetzungenDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Uebersetzungen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: UebersetzungenDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Uebersetzungen." LOG_
		}
	} else {
		_LOG << "Error: UebersetzungenDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL UebersetzungenDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: UebersetzungenDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: UebersetzungenDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL UebersetzungenDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "UebersetzungenDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select translated, text,  id from translations") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Uebersetzungen would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Uebersetzungen found. All Uebersetzungen may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qtranslated)
		UAP(lb_I_String, qtext)

		// Copy values

		qtranslated = q->getAsString(1);
		qtext = q->getAsString(2);
		qID = q->getAsLong(3);

		owningObject->addUebersetzungen(qtranslated->charrep(), qtext->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qtranslated = q->getAsString(1);
			qtext = q->getAsString(2);
			qID = q->getAsLong(3);

			owningObject->addUebersetzungen(qtranslated->charrep(), qtext->charrep(),  qID->getData());
		}
	}
}



class lbPluginUebersetzungenDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginUebersetzungenDBReaderExtension();
	
	virtual ~lbPluginUebersetzungenDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUebersetzungenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUebersetzungenDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUebersetzungenDBReaderExtension, lbPluginUebersetzungenDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginUebersetzungenDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUebersetzungenDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUebersetzungenDBReaderExtension::lbPluginUebersetzungenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUebersetzungenDBReaderExtension::lbPluginUebersetzungenDBReaderExtension() called.\n" LOG_
}

lbPluginUebersetzungenDBReaderExtension::~lbPluginUebersetzungenDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUebersetzungenDBReaderExtension::~lbPluginUebersetzungenDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginUebersetzungenDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUebersetzungenDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUebersetzungenDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginUebersetzungenDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUebersetzungenDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUebersetzungenModelExtension == NULL) {
		UebersetzungenDBReaderExtension* UebersetzungenModelExtension = new UebersetzungenDBReaderExtension();
		
	
		QI(UebersetzungenModelExtension, lb_I_Unknown, ukUebersetzungenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUebersetzungenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUebersetzungenDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUebersetzungenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		UebersetzungenDBReaderExtension* UebersetzungenModelExtension = new UebersetzungenDBReaderExtension();
		
	
		QI(UebersetzungenModelExtension, lb_I_Unknown, ukUebersetzungenModelExtension)
	}
	
	lb_I_Unknown* r = ukUebersetzungenModelExtension.getPtr();
	ukUebersetzungenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUebersetzungenDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUebersetzungenModelExtension != NULL) {
                ukUebersetzungenModelExtension--;
                ukUebersetzungenModelExtension.resetPtr();
        }
}

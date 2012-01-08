
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
#include <DBReader_FKPK_Mapping.h>

IMPLEMENT_FUNCTOR(instanceOfFKPK_MappingDBReaderExtension, FKPK_MappingDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FKPK_MappingDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

FKPK_MappingDBReaderExtension::FKPK_MappingDBReaderExtension() {
	_CL_VERBOSE << "FKPK_MappingDBReaderExtension::FKPK_MappingDBReaderExtension() called." LOG_
}

FKPK_MappingDBReaderExtension::~FKPK_MappingDBReaderExtension() {
	_CL_VERBOSE << "FKPK_MappingDBReaderExtension::~FKPK_MappingDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FKPK_MappingDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FKPK_MappingDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FKPK_MappingDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_FKPK_Mapping, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FKPK_MappingDBReaderExtension::setOwningObject() owning parameter is not a lb_I_FKPK_Mapping." LOG_
		}
	} else {
		_LOG << "Error: FKPK_MappingDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: FKPK_MappingDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: FKPK_MappingDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FKPK_MappingDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "FKPK_MappingDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select pktable, pkname, fktable, fkname,  id from foreignkey_visibledata_mapping") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read FKPK_Mapping would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No FKPK_Mapping found. All FKPK_Mapping may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qpktable)
		UAP(lb_I_String, qpkname)
		UAP(lb_I_String, qfktable)
		UAP(lb_I_String, qfkname)

		// Copy values

		qpktable = q->getAsString(1);
		qpkname = q->getAsString(2);
		qfktable = q->getAsString(3);
		qfkname = q->getAsString(4);
		qID = q->getAsLong(5);

		owningObject->addFKPK_Mapping(qpktable->charrep(), qpkname->charrep(), qfktable->charrep(), qfkname->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qpktable = q->getAsString(1);
			qpkname = q->getAsString(2);
			qfktable = q->getAsString(3);
			qfkname = q->getAsString(4);
			qID = q->getAsLong(5);

			owningObject->addFKPK_Mapping(qpktable->charrep(), qpkname->charrep(), qfktable->charrep(), qfkname->charrep(),  qID->getData());
		}
	}
}



class lbPluginFKPK_MappingDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFKPK_MappingDBReaderExtension();
	
	virtual ~lbPluginFKPK_MappingDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFKPK_MappingModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFKPK_MappingDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFKPK_MappingDBReaderExtension, lbPluginFKPK_MappingDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFKPK_MappingDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFKPK_MappingDBReaderExtension::lbPluginFKPK_MappingDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingDBReaderExtension::lbPluginFKPK_MappingDBReaderExtension() called.\n" LOG_
}

lbPluginFKPK_MappingDBReaderExtension::~lbPluginFKPK_MappingDBReaderExtension() {
	_CL_VERBOSE << "lbPluginFKPK_MappingDBReaderExtension::~lbPluginFKPK_MappingDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {
		FKPK_MappingDBReaderExtension* FKPK_MappingModelExtension = new FKPK_MappingDBReaderExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFKPK_MappingModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFKPK_MappingModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FKPK_MappingDBReaderExtension* FKPK_MappingModelExtension = new FKPK_MappingDBReaderExtension();
		
	
		QI(FKPK_MappingModelExtension, lb_I_Unknown, ukFKPK_MappingModelExtension)
	}
	
	lb_I_Unknown* r = ukFKPK_MappingModelExtension.getPtr();
	ukFKPK_MappingModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFKPK_MappingDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFKPK_MappingModelExtension != NULL) {
                ukFKPK_MappingModelExtension--;
                ukFKPK_MappingModelExtension.resetPtr();
        }
}

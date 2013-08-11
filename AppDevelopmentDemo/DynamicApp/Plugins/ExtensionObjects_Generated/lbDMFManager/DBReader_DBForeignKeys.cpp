
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
#include <DBReader_DBForeignKeys.h>

IMPLEMENT_FUNCTOR(instanceOfDBForeignKeysDBReaderExtension, DBForeignKeysDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBForeignKeysDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBForeignKeysDBReaderExtension::DBForeignKeysDBReaderExtension() {
	_CL_VERBOSE << "DBForeignKeysDBReaderExtension::DBForeignKeysDBReaderExtension() called." LOG_
}

DBForeignKeysDBReaderExtension::~DBForeignKeysDBReaderExtension() {
	_CL_VERBOSE << "DBForeignKeysDBReaderExtension::~DBForeignKeysDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBForeignKeysDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBForeignKeysDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBForeignKeysDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBForeignKeys, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBForeignKeysDBReaderExtension::setOwningObject() owning parameter is not a lb_I_DBForeignKeys." LOG_
		}
	} else {
		_LOG << "Error: DBForeignKeysDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBForeignKeysDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: DBForeignKeysDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: DBForeignKeysDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBForeignKeysDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "DBForeignKeysDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select pkcatalog, pkschema, pktable, pkcolumn, fkcatalog, fkschema, fktable, fkcolumn, keysequence, updaterule, deleterule, dbtableid,  id from dbforeignkey") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read DBForeignKeys would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No DBForeignKeys found. All DBForeignKeys may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qpkcatalog)
		UAP(lb_I_String, qpkschema)
		UAP(lb_I_String, qpktable)
		UAP(lb_I_String, qpkcolumn)
		UAP(lb_I_String, qfkcatalog)
		UAP(lb_I_String, qfkschema)
		UAP(lb_I_String, qfktable)
		UAP(lb_I_String, qfkcolumn)
		UAP(lb_I_Long, qkeysequence)
		UAP(lb_I_Long, qupdaterule)
		UAP(lb_I_Long, qdeleterule)
		UAP(lb_I_Long, qdbtableid)

		// Copy values

		qpkcatalog = q->getAsString(1);
		qpkschema = q->getAsString(2);
		qpktable = q->getAsString(3);
		qpkcolumn = q->getAsString(4);
		qfkcatalog = q->getAsString(5);
		qfkschema = q->getAsString(6);
		qfktable = q->getAsString(7);
		qfkcolumn = q->getAsString(8);
		qkeysequence = q->getAsLong(9);
		qupdaterule = q->getAsLong(10);
		qdeleterule = q->getAsLong(11);
		qdbtableid = q->getAsLong(12);
		qID = q->getAsLong(13);

		owningObject->add(qpkcatalog->charrep(), qpkschema->charrep(), qpktable->charrep(), qpkcolumn->charrep(), qfkcatalog->charrep(), qfkschema->charrep(), qfktable->charrep(), qfkcolumn->charrep(), qkeysequence->getData(), qupdaterule->getData(), qdeleterule->getData(), qdbtableid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qpkcatalog = q->getAsString(1);
			qpkschema = q->getAsString(2);
			qpktable = q->getAsString(3);
			qpkcolumn = q->getAsString(4);
			qfkcatalog = q->getAsString(5);
			qfkschema = q->getAsString(6);
			qfktable = q->getAsString(7);
			qfkcolumn = q->getAsString(8);
			qkeysequence = q->getAsLong(9);
			qupdaterule = q->getAsLong(10);
			qdeleterule = q->getAsLong(11);
			qdbtableid = q->getAsLong(12);
			qID = q->getAsLong(13);

			owningObject->add(qpkcatalog->charrep(), qpkschema->charrep(), qpktable->charrep(), qpkcolumn->charrep(), qfkcatalog->charrep(), qfkschema->charrep(), qfktable->charrep(), qfkcolumn->charrep(), qkeysequence->getData(), qupdaterule->getData(), qdeleterule->getData(), qdbtableid->getData(),  qID->getData());
		}
	}
}



class lbPluginDBForeignKeysDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBForeignKeysDBReaderExtension();
	
	virtual ~lbPluginDBForeignKeysDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukDBForeignKeysModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBForeignKeysDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBForeignKeysDBReaderExtension, lbPluginDBForeignKeysDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBForeignKeysDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBForeignKeysDBReaderExtension::lbPluginDBForeignKeysDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBForeignKeysDBReaderExtension::lbPluginDBForeignKeysDBReaderExtension() called.\n" LOG_
}

lbPluginDBForeignKeysDBReaderExtension::~lbPluginDBForeignKeysDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBForeignKeysDBReaderExtension::~lbPluginDBForeignKeysDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBForeignKeysModelExtension == NULL) {
		DBForeignKeysDBReaderExtension* DBForeignKeysModelExtension = new DBForeignKeysDBReaderExtension();
		
	
		QI(DBForeignKeysModelExtension, lb_I_Unknown, ukDBForeignKeysModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBForeignKeysModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBForeignKeysModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBForeignKeysDBReaderExtension* DBForeignKeysModelExtension = new DBForeignKeysDBReaderExtension();
		
	
		QI(DBForeignKeysModelExtension, lb_I_Unknown, ukDBForeignKeysModelExtension)
	}
	
	lb_I_Unknown* r = ukDBForeignKeysModelExtension.getPtr();
	ukDBForeignKeysModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBForeignKeysDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBForeignKeysModelExtension != NULL) {
                ukDBForeignKeysModelExtension--;
                ukDBForeignKeysModelExtension.resetPtr();
        }
}

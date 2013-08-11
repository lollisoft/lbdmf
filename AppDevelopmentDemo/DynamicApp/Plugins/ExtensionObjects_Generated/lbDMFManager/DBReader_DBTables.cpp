
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
#include <DBReader_DBTables.h>

IMPLEMENT_FUNCTOR(instanceOfDBTablesDBReaderExtension, DBTablesDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBTablesDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBTablesDBReaderExtension::DBTablesDBReaderExtension() {
	_CL_VERBOSE << "DBTablesDBReaderExtension::DBTablesDBReaderExtension() called." LOG_
}

DBTablesDBReaderExtension::~DBTablesDBReaderExtension() {
	_CL_VERBOSE << "DBTablesDBReaderExtension::~DBTablesDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBTablesDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBTablesDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBTablesDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBTables, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBTablesDBReaderExtension::setOwningObject() owning parameter is not a lb_I_DBTables." LOG_
		}
	} else {
		_LOG << "Error: DBTablesDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBTablesDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: DBTablesDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: DBTablesDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBTablesDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "DBTablesDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select catalogname, schemaname, tablename, tabletype, tableremarks, anwendungenid,  id from dbtable") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read DBTables would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No DBTables found. All DBTables may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qcatalogname)
		UAP(lb_I_String, qschemaname)
		UAP(lb_I_String, qtablename)
		UAP(lb_I_String, qtabletype)
		UAP(lb_I_String, qtableremarks)
		UAP(lb_I_Long, qanwendungenid)

		// Copy values

		qcatalogname = q->getAsString(1);
		qschemaname = q->getAsString(2);
		qtablename = q->getAsString(3);
		qtabletype = q->getAsString(4);
		qtableremarks = q->getAsString(5);
		qanwendungenid = q->getAsLong(6);
		qID = q->getAsLong(7);

		owningObject->add(qcatalogname->charrep(), qschemaname->charrep(), qtablename->charrep(), qtabletype->charrep(), qtableremarks->charrep(), qanwendungenid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qcatalogname = q->getAsString(1);
			qschemaname = q->getAsString(2);
			qtablename = q->getAsString(3);
			qtabletype = q->getAsString(4);
			qtableremarks = q->getAsString(5);
			qanwendungenid = q->getAsLong(6);
			qID = q->getAsLong(7);

			owningObject->add(qcatalogname->charrep(), qschemaname->charrep(), qtablename->charrep(), qtabletype->charrep(), qtableremarks->charrep(), qanwendungenid->getData(),  qID->getData());
		}
	}
}



class lbPluginDBTablesDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBTablesDBReaderExtension();
	
	virtual ~lbPluginDBTablesDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukDBTablesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBTablesDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBTablesDBReaderExtension, lbPluginDBTablesDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBTablesDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBTablesDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBTablesDBReaderExtension::lbPluginDBTablesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBTablesDBReaderExtension::lbPluginDBTablesDBReaderExtension() called.\n" LOG_
}

lbPluginDBTablesDBReaderExtension::~lbPluginDBTablesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBTablesDBReaderExtension::~lbPluginDBTablesDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBTablesDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBTablesDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBTablesDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBTablesDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBTablesDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTablesModelExtension == NULL) {
		DBTablesDBReaderExtension* DBTablesModelExtension = new DBTablesDBReaderExtension();
		
	
		QI(DBTablesModelExtension, lb_I_Unknown, ukDBTablesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTablesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBTablesDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTablesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBTablesDBReaderExtension* DBTablesModelExtension = new DBTablesDBReaderExtension();
		
	
		QI(DBTablesModelExtension, lb_I_Unknown, ukDBTablesModelExtension)
	}
	
	lb_I_Unknown* r = ukDBTablesModelExtension.getPtr();
	ukDBTablesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBTablesDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTablesModelExtension != NULL) {
                ukDBTablesModelExtension--;
                ukDBTablesModelExtension.resetPtr();
        }
}


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
#include <DBReader_DBPrimaryKeys.h>

IMPLEMENT_FUNCTOR(instanceOfDBPrimaryKeysDBReaderExtension, DBPrimaryKeysDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBPrimaryKeysDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBPrimaryKeysDBReaderExtension::DBPrimaryKeysDBReaderExtension() {
	_CL_VERBOSE << "DBPrimaryKeysDBReaderExtension::DBPrimaryKeysDBReaderExtension() called." LOG_
}

DBPrimaryKeysDBReaderExtension::~DBPrimaryKeysDBReaderExtension() {
	_CL_VERBOSE << "DBPrimaryKeysDBReaderExtension::~DBPrimaryKeysDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBPrimaryKeysDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBPrimaryKeysDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBPrimaryKeysDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBPrimaryKeys, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBPrimaryKeysDBReaderExtension::setOwningObject() owning parameter is not a lb_I_DBPrimaryKeys." LOG_
		}
	} else {
		_LOG << "Error: DBPrimaryKeysDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: DBPrimaryKeysDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: DBPrimaryKeysDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "DBPrimaryKeysDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select tablecatalog, tableschema, tablename, columnname, columnname2, keysequence, dbtableid,  id from dbprimarykey") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read DBPrimaryKeys would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No DBPrimaryKeys found. All DBPrimaryKeys may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qtablecatalog)
		UAP(lb_I_String, qtableschema)
		UAP(lb_I_String, qtablename)
		UAP(lb_I_String, qcolumnname)
		UAP(lb_I_String, qcolumnname2)
		UAP(lb_I_Long, qkeysequence)
		UAP(lb_I_Long, qdbtableid)

		// Copy values

		qtablecatalog = q->getAsString(1);
		qtableschema = q->getAsString(2);
		qtablename = q->getAsString(3);
		qcolumnname = q->getAsString(4);
		qcolumnname2 = q->getAsString(5);
		qkeysequence = q->getAsLong(6);
		qdbtableid = q->getAsLong(7);
		qID = q->getAsLong(8);

		owningObject->add(qtablecatalog->charrep(), qtableschema->charrep(), qtablename->charrep(), qcolumnname->charrep(), qcolumnname2->charrep(), qkeysequence->getData(), qdbtableid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qtablecatalog = q->getAsString(1);
			qtableschema = q->getAsString(2);
			qtablename = q->getAsString(3);
			qcolumnname = q->getAsString(4);
			qcolumnname2 = q->getAsString(5);
			qkeysequence = q->getAsLong(6);
			qdbtableid = q->getAsLong(7);
			qID = q->getAsLong(8);

			owningObject->add(qtablecatalog->charrep(), qtableschema->charrep(), qtablename->charrep(), qcolumnname->charrep(), qcolumnname2->charrep(), qkeysequence->getData(), qdbtableid->getData(),  qID->getData());
		}
	}
}



class lbPluginDBPrimaryKeysDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBPrimaryKeysDBReaderExtension();
	
	virtual ~lbPluginDBPrimaryKeysDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukDBPrimaryKeysModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBPrimaryKeysDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBPrimaryKeysDBReaderExtension, lbPluginDBPrimaryKeysDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBPrimaryKeysDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBPrimaryKeysDBReaderExtension::lbPluginDBPrimaryKeysDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysDBReaderExtension::lbPluginDBPrimaryKeysDBReaderExtension() called.\n" LOG_
}

lbPluginDBPrimaryKeysDBReaderExtension::~lbPluginDBPrimaryKeysDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysDBReaderExtension::~lbPluginDBPrimaryKeysDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {
		DBPrimaryKeysDBReaderExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysDBReaderExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBPrimaryKeysModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBPrimaryKeysDBReaderExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysDBReaderExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	}
	
	lb_I_Unknown* r = ukDBPrimaryKeysModelExtension.getPtr();
	ukDBPrimaryKeysModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBPrimaryKeysDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBPrimaryKeysModelExtension != NULL) {
                ukDBPrimaryKeysModelExtension--;
                ukDBPrimaryKeysModelExtension.resetPtr();
        }
}


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
#include <DBReader_DBColumns.h>

IMPLEMENT_FUNCTOR(instanceOfDBColumnsDBReaderExtension, DBColumnsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBColumnsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBColumnsDBReaderExtension::DBColumnsDBReaderExtension() {
	_CL_VERBOSE << "DBColumnsDBReaderExtension::DBColumnsDBReaderExtension() called." LOG_
}

DBColumnsDBReaderExtension::~DBColumnsDBReaderExtension() {
	_CL_VERBOSE << "DBColumnsDBReaderExtension::~DBColumnsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBColumnsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBColumnsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBColumnsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBColumns, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBColumnsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_DBColumns." LOG_
		}
	} else {
		_LOG << "Error: DBColumnsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBColumnsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: DBColumnsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: DBColumnsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBColumnsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "DBColumnsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select columnname, columnremarks, typename, columnsize, nullable, tablename, dbtableid,  id from dbcolumn") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read DBColumns would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No DBColumns found. All DBColumns may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qcolumnname)
		UAP(lb_I_String, qcolumnremarks)
		UAP(lb_I_String, qtypename)
		UAP(lb_I_Long, qcolumnsize)
		UAP_REQUEST(getModuleInstance(), lb_I_Boolean, qnullable)
		UAP(lb_I_String, qtablename)
		UAP(lb_I_Long, qdbtableid)

		// Copy values

		qcolumnname = q->getAsString(1);
		qcolumnremarks = q->getAsString(2);
		qtypename = q->getAsString(3);
		qcolumnsize = q->getAsLong(4);
		UAP(lb_I_String, bnullable)
		bnullable = q->getAsString(5);
		if (*bnullable == "true")
			qnullable->setData(true);
		else
			qnullable->setData(false);
		qtablename = q->getAsString(6);
		qdbtableid = q->getAsLong(7);
		qID = q->getAsLong(8);

		owningObject->add(qcolumnname->charrep(), qcolumnremarks->charrep(), qtypename->charrep(), qcolumnsize->getData(), qnullable->getData(), qtablename->charrep(), qdbtableid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qcolumnname = q->getAsString(1);
			qcolumnremarks = q->getAsString(2);
			qtypename = q->getAsString(3);
			qcolumnsize = q->getAsLong(4);
			UAP(lb_I_String, bnullable)
			bnullable = q->getAsString(5);
			if (*bnullable == "true")
				qnullable->setData(true);
			else
				qnullable->setData(false);
			qtablename = q->getAsString(6);
			qdbtableid = q->getAsLong(7);
			qID = q->getAsLong(8);

			owningObject->add(qcolumnname->charrep(), qcolumnremarks->charrep(), qtypename->charrep(), qcolumnsize->getData(), qnullable->charrep(), qtablename->charrep(), qdbtableid->getData(),  qID->getData());
		}
	}
}



class lbPluginDBColumnsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBColumnsDBReaderExtension();
	
	virtual ~lbPluginDBColumnsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukDBColumnsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBColumnsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBColumnsDBReaderExtension, lbPluginDBColumnsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBColumnsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBColumnsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBColumnsDBReaderExtension::lbPluginDBColumnsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBColumnsDBReaderExtension::lbPluginDBColumnsDBReaderExtension() called.\n" LOG_
}

lbPluginDBColumnsDBReaderExtension::~lbPluginDBColumnsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginDBColumnsDBReaderExtension::~lbPluginDBColumnsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBColumnsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBColumnsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBColumnsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBColumnsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBColumnsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBColumnsModelExtension == NULL) {
		DBColumnsDBReaderExtension* DBColumnsModelExtension = new DBColumnsDBReaderExtension();
		
	
		QI(DBColumnsModelExtension, lb_I_Unknown, ukDBColumnsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBColumnsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBColumnsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBColumnsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBColumnsDBReaderExtension* DBColumnsModelExtension = new DBColumnsDBReaderExtension();
		
	
		QI(DBColumnsModelExtension, lb_I_Unknown, ukDBColumnsModelExtension)
	}
	
	lb_I_Unknown* r = ukDBColumnsModelExtension.getPtr();
	ukDBColumnsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBColumnsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBColumnsModelExtension != NULL) {
                ukDBColumnsModelExtension--;
                ukDBColumnsModelExtension.resetPtr();
        }
}

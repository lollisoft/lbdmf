
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
#include <DBReader_Column_Types.h>

IMPLEMENT_FUNCTOR(instanceOfColumn_TypesDBReaderExtension, Column_TypesDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Column_TypesDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

Column_TypesDBReaderExtension::Column_TypesDBReaderExtension() {
	_CL_VERBOSE << "Column_TypesDBReaderExtension::Column_TypesDBReaderExtension() called." LOG_
}

Column_TypesDBReaderExtension::~Column_TypesDBReaderExtension() {
	_CL_VERBOSE << "Column_TypesDBReaderExtension::~Column_TypesDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Column_TypesDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Column_TypesDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Column_TypesDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Column_Types, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Column_TypesDBReaderExtension::setOwningObject() owning parameter is not a lb_I_Column_Types." LOG_
		}
	} else {
		_LOG << "Error: Column_TypesDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: Column_TypesDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: Column_TypesDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "Column_TypesDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select name, tablename, ro, specialcolumn, controltype,  id from column_types") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read Column_Types would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No Column_Types found. All Column_Types may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qname)
		UAP(lb_I_String, qtablename)
		UAP(lb_I_Boolean, qro)
		UAP(lb_I_Boolean, qspecialcolumn)
		UAP(lb_I_String, qcontroltype)

		// Copy values

		qname = q->getAsString(1);
		qtablename = q->getAsString(2);
		UAP(lb_I_String, bro)
		bro = q->getAsString(3);
		if (*bro == "true")
			qro->setData(true);
		else
			qro->setData(false);
		UAP(lb_I_String, bspecialcolumn)
		bspecialcolumn = q->getAsString(4);
		if (*bspecialcolumn == "true")
			qspecialcolumn->setData(true);
		else
			qspecialcolumn->setData(false);
		qcontroltype = q->getAsString(5);
		qID = q->getAsLong(6);

		owningObject->addColumn_Types(qname->charrep(), qtablename->charrep(), qro->getData(), qspecialcolumn->getData(), qcontroltype->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qname = q->getAsString(1);
			qtablename = q->getAsString(2);
			UAP(lb_I_String, bro)
			bro = q->getAsString(3);
			if (*bro == "true")
				qro->setData(true);
			else
				qro->setData(false);
			UAP(lb_I_String, bspecialcolumn)
			bspecialcolumn = q->getAsString(4);
			if (*bspecialcolumn == "true")
				qspecialcolumn->setData(true);
			else
				qspecialcolumn->setData(false);
			qcontroltype = q->getAsString(5);
			qID = q->getAsLong(6);

			owningObject->addColumn_Types(qname->charrep(), qtablename->charrep(), qro->charrep(), qspecialcolumn->charrep(), qcontroltype->charrep(),  qID->getData());
		}
	}
}



class lbPluginColumn_TypesDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginColumn_TypesDBReaderExtension();
	
	virtual ~lbPluginColumn_TypesDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukColumn_TypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginColumn_TypesDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginColumn_TypesDBReaderExtension, lbPluginColumn_TypesDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginColumn_TypesDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginColumn_TypesDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginColumn_TypesDBReaderExtension::lbPluginColumn_TypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesDBReaderExtension::lbPluginColumn_TypesDBReaderExtension() called.\n" LOG_
}

lbPluginColumn_TypesDBReaderExtension::~lbPluginColumn_TypesDBReaderExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesDBReaderExtension::~lbPluginColumn_TypesDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginColumn_TypesDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginColumn_TypesDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginColumn_TypesDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginColumn_TypesDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {
		Column_TypesDBReaderExtension* Column_TypesModelExtension = new Column_TypesDBReaderExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukColumn_TypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Column_TypesDBReaderExtension* Column_TypesModelExtension = new Column_TypesDBReaderExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	}
	
	lb_I_Unknown* r = ukColumn_TypesModelExtension.getPtr();
	ukColumn_TypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginColumn_TypesDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukColumn_TypesModelExtension != NULL) {
                ukColumn_TypesModelExtension--;
                ukColumn_TypesModelExtension.resetPtr();
        }
}

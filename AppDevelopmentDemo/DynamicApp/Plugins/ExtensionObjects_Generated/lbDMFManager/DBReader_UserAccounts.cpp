
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
#include <DBReader_UserAccounts.h>

IMPLEMENT_FUNCTOR(instanceOfUserAccountsDBReaderExtension, UserAccountsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(UserAccountsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

UserAccountsDBReaderExtension::UserAccountsDBReaderExtension() {
	_CL_VERBOSE << "UserAccountsDBReaderExtension::UserAccountsDBReaderExtension() called." LOG_
}

UserAccountsDBReaderExtension::~UserAccountsDBReaderExtension() {
	_CL_VERBOSE << "UserAccountsDBReaderExtension::~UserAccountsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL UserAccountsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: UserAccountsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL UserAccountsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_UserAccounts, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: UserAccountsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_UserAccounts." LOG_
		}
	} else {
		_LOG << "Error: UserAccountsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL UserAccountsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: UserAccountsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: UserAccountsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL UserAccountsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "UserAccountsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select passwort, userid, vorname, name, secret,  id from users") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read UserAccounts would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No UserAccounts found. All UserAccounts may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_String, qpasswort)
		UAP(lb_I_String, quserid)
		UAP(lb_I_String, qvorname)
		UAP(lb_I_String, qname)
		UAP(lb_I_String, qsecret)

		// Copy values

		qpasswort = q->getAsString(1);
		quserid = q->getAsString(2);
		qvorname = q->getAsString(3);
		qname = q->getAsString(4);
		qsecret = q->getAsString(5);
		qID = q->getAsLong(6);

		owningObject->addUserAccounts(qpasswort->charrep(), quserid->charrep(), qvorname->charrep(), qname->charrep(), qsecret->charrep(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			qpasswort = q->getAsString(1);
			quserid = q->getAsString(2);
			qvorname = q->getAsString(3);
			qname = q->getAsString(4);
			qsecret = q->getAsString(5);
			qID = q->getAsLong(6);

			owningObject->addUserAccounts(qpasswort->charrep(), quserid->charrep(), qvorname->charrep(), qname->charrep(), qsecret->charrep(),  qID->getData());
		}
	}
}



class lbPluginUserAccountsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginUserAccountsDBReaderExtension();
	
	virtual ~lbPluginUserAccountsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUserAccountsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUserAccountsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUserAccountsDBReaderExtension, lbPluginUserAccountsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginUserAccountsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUserAccountsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUserAccountsDBReaderExtension::lbPluginUserAccountsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUserAccountsDBReaderExtension::lbPluginUserAccountsDBReaderExtension() called.\n" LOG_
}

lbPluginUserAccountsDBReaderExtension::~lbPluginUserAccountsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUserAccountsDBReaderExtension::~lbPluginUserAccountsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginUserAccountsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUserAccountsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUserAccountsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginUserAccountsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUserAccountsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserAccountsModelExtension == NULL) {
		UserAccountsDBReaderExtension* UserAccountsModelExtension = new UserAccountsDBReaderExtension();
		
	
		QI(UserAccountsModelExtension, lb_I_Unknown, ukUserAccountsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUserAccountsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUserAccountsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUserAccountsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		UserAccountsDBReaderExtension* UserAccountsModelExtension = new UserAccountsDBReaderExtension();
		
	
		QI(UserAccountsModelExtension, lb_I_Unknown, ukUserAccountsModelExtension)
	}
	
	lb_I_Unknown* r = ukUserAccountsModelExtension.getPtr();
	ukUserAccountsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUserAccountsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUserAccountsModelExtension != NULL) {
                ukUserAccountsModelExtension--;
                ukUserAccountsModelExtension.resetPtr();
        }
}

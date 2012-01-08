
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
#include <DBReader_User_Applications.h>

IMPLEMENT_FUNCTOR(instanceOfUser_ApplicationsDBReaderExtension, User_ApplicationsDBReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(User_ApplicationsDBReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

User_ApplicationsDBReaderExtension::User_ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "User_ApplicationsDBReaderExtension::User_ApplicationsDBReaderExtension() called." LOG_
}

User_ApplicationsDBReaderExtension::~User_ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "User_ApplicationsDBReaderExtension::~User_ApplicationsDBReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL User_ApplicationsDBReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: User_ApplicationsDBReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL User_ApplicationsDBReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_User_Applications, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: User_ApplicationsDBReaderExtension::setOwningObject() owning parameter is not a lb_I_User_Applications." LOG_
		}
	} else {
		_LOG << "Error: User_ApplicationsDBReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL User_ApplicationsDBReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_DatabaseOperation, dbOp)
		QI(operation, lb_I_DatabaseOperation, dbOp)
		if (dbOp == NULL) {
			_LOG << "Error: User_ApplicationsDBReaderExtension::setOperator() operation parameter is not a lb_I_DatabaseOperation." LOG_
		}
		
		db = dbOp->getDatabase();
	} else {
		_LOG << "Error: User_ApplicationsDBReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL User_ApplicationsDBReaderExtension::execute() {
	lbErrCodes err = ERR_NONE;
	UAP(lb_I_Query, q)

	if (db == NULL) {
		_LOG << "User_ApplicationsDBReaderExtension::execute() Error: Database object was not passed before this call." LOG_
		return;
	}
	
	q = db->getQuery("lbDMF", 0);

	q->skipFKCollecting();

	if (q->query("select userid, anwendungenid,  id from user_anwendungen") != ERR_NONE) {
		_LOG << "Error: Access to application table failed. Read User_Applications would be skipped." LOG_
		return;
	}

	err = q->first();

	if ((err != ERR_NONE) && (err != WARN_DB_NODATA)) {
		_LOG << "Error: No User_Applications found. All User_Applications may be deleted accidantly." LOG_
	} else {
		UAP(lb_I_Long, qID)

		UAP(lb_I_Long, quserid)
		UAP(lb_I_Long, qanwendungenid)

		// Copy values

		quserid = q->getAsLong(1);
		qanwendungenid = q->getAsLong(2);
		qID = q->getAsLong(3);

		owningObject->addUser_Applications(quserid->getData(), qanwendungenid->getData(),  qID->getData());

		while (((err = q->next()) == ERR_NONE) || err == WARN_DB_NODATA) {

			// Copy values

			quserid = q->getAsLong(1);
			qanwendungenid = q->getAsLong(2);
			qID = q->getAsLong(3);

			owningObject->addUser_Applications(quserid->getData(), qanwendungenid->getData(),  qID->getData());
		}
	}
}



class lbPluginUser_ApplicationsDBReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginUser_ApplicationsDBReaderExtension();
	
	virtual ~lbPluginUser_ApplicationsDBReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukUser_ApplicationsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginUser_ApplicationsDBReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginUser_ApplicationsDBReaderExtension, lbPluginUser_ApplicationsDBReaderExtension)

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginUser_ApplicationsDBReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginUser_ApplicationsDBReaderExtension::lbPluginUser_ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsDBReaderExtension::lbPluginUser_ApplicationsDBReaderExtension() called.\n" LOG_
}

lbPluginUser_ApplicationsDBReaderExtension::~lbPluginUser_ApplicationsDBReaderExtension() {
	_CL_VERBOSE << "lbPluginUser_ApplicationsDBReaderExtension::~lbPluginUser_ApplicationsDBReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModelExtension == NULL) {
		User_ApplicationsDBReaderExtension* User_ApplicationsModelExtension = new User_ApplicationsDBReaderExtension();
		
	
		QI(User_ApplicationsModelExtension, lb_I_Unknown, ukUser_ApplicationsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukUser_ApplicationsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukUser_ApplicationsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		User_ApplicationsDBReaderExtension* User_ApplicationsModelExtension = new User_ApplicationsDBReaderExtension();
		
	
		QI(User_ApplicationsModelExtension, lb_I_Unknown, ukUser_ApplicationsModelExtension)
	}
	
	lb_I_Unknown* r = ukUser_ApplicationsModelExtension.getPtr();
	ukUser_ApplicationsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginUser_ApplicationsDBReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukUser_ApplicationsModelExtension != NULL) {
                ukUser_ApplicationsModelExtension--;
                ukUser_ApplicationsModelExtension.resetPtr();
        }
}

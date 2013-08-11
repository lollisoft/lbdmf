
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
#include <InternalFormatReader_DBPrimaryKeys.h>

IMPLEMENT_FUNCTOR(instanceOfDBPrimaryKeysInternalFormatReaderExtension, DBPrimaryKeysInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBPrimaryKeysInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBPrimaryKeysInternalFormatReaderExtension::DBPrimaryKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBPrimaryKeysInternalFormatReaderExtension::DBPrimaryKeysInternalFormatReaderExtension() called." LOG_
}

DBPrimaryKeysInternalFormatReaderExtension::~DBPrimaryKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBPrimaryKeysInternalFormatReaderExtension::~DBPrimaryKeysInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBPrimaryKeysInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBPrimaryKeysInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBPrimaryKeysInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBPrimaryKeys, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBPrimaryKeysInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_DBPrimaryKeys." LOG_
		}
	} else {
		_LOG << "Error: DBPrimaryKeysInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: DBPrimaryKeysInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: DBPrimaryKeysInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBPrimaryKeysInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _tablecatalog = NULL;
		char* _tableschema = NULL;
		char* _tablename = NULL;
		char* _columnname = NULL;
		char* _columnname2 = NULL;
		int _keysequence = 0;
		long _dbtableid = 0;
	
		*iStream >> _ID;

		*iStream >> _tablecatalog;
		*iStream >> _tableschema;
		*iStream >> _tablename;
		*iStream >> _columnname;
		*iStream >> _columnname2;
		*iStream >> _keysequence;
		*iStream >> _dbtableid;
		owningObject->add(_tablecatalog, _tableschema, _tablename, _columnname, _columnname2, _keysequence, _dbtableid,  _ID);

		// Leaky !
	}
}



class lbPluginDBPrimaryKeysInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBPrimaryKeysInternalFormatReaderExtension();
	
	virtual ~lbPluginDBPrimaryKeysInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBPrimaryKeysInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBPrimaryKeysInternalFormatReaderExtension, lbPluginDBPrimaryKeysInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBPrimaryKeysInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBPrimaryKeysInternalFormatReaderExtension::lbPluginDBPrimaryKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysInternalFormatReaderExtension::lbPluginDBPrimaryKeysInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginDBPrimaryKeysInternalFormatReaderExtension::~lbPluginDBPrimaryKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBPrimaryKeysInternalFormatReaderExtension::~lbPluginDBPrimaryKeysInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {
		DBPrimaryKeysInternalFormatReaderExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysInternalFormatReaderExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBPrimaryKeysModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBPrimaryKeysModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBPrimaryKeysInternalFormatReaderExtension* DBPrimaryKeysModelExtension = new DBPrimaryKeysInternalFormatReaderExtension();
		
	
		QI(DBPrimaryKeysModelExtension, lb_I_Unknown, ukDBPrimaryKeysModelExtension)
	}
	
	lb_I_Unknown* r = ukDBPrimaryKeysModelExtension.getPtr();
	ukDBPrimaryKeysModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBPrimaryKeysInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBPrimaryKeysModelExtension != NULL) {
                ukDBPrimaryKeysModelExtension--;
                ukDBPrimaryKeysModelExtension.resetPtr();
        }
}

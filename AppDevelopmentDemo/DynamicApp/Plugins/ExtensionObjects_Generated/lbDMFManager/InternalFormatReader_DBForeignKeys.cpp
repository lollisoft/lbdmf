
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
#include <InternalFormatReader_DBForeignKeys.h>

IMPLEMENT_FUNCTOR(instanceOfDBForeignKeysInternalFormatReaderExtension, DBForeignKeysInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBForeignKeysInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBForeignKeysInternalFormatReaderExtension::DBForeignKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBForeignKeysInternalFormatReaderExtension::DBForeignKeysInternalFormatReaderExtension() called." LOG_
}

DBForeignKeysInternalFormatReaderExtension::~DBForeignKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBForeignKeysInternalFormatReaderExtension::~DBForeignKeysInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBForeignKeysInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBForeignKeysInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBForeignKeysInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBForeignKeys, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBForeignKeysInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_DBForeignKeys." LOG_
		}
	} else {
		_LOG << "Error: DBForeignKeysInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBForeignKeysInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: DBForeignKeysInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: DBForeignKeysInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBForeignKeysInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _pkcatalog = NULL;
		char* _pkschema = NULL;
		char* _pktable = NULL;
		char* _pkcolumn = NULL;
		char* _fkcatalog = NULL;
		char* _fkschema = NULL;
		char* _fktable = NULL;
		char* _fkcolumn = NULL;
		int _keysequence = 0;
		int _updaterule = 0;
		int _deleterule = 0;
		long _dbtableid = 0;
	
		*iStream >> _ID;

		*iStream >> _pkcatalog;
		*iStream >> _pkschema;
		*iStream >> _pktable;
		*iStream >> _pkcolumn;
		*iStream >> _fkcatalog;
		*iStream >> _fkschema;
		*iStream >> _fktable;
		*iStream >> _fkcolumn;
		*iStream >> _keysequence;
		*iStream >> _updaterule;
		*iStream >> _deleterule;
		*iStream >> _dbtableid;
		owningObject->add(_pkcatalog, _pkschema, _pktable, _pkcolumn, _fkcatalog, _fkschema, _fktable, _fkcolumn, _keysequence, _updaterule, _deleterule, _dbtableid,  _ID);

		// Leaky !
	}
}



class lbPluginDBForeignKeysInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBForeignKeysInternalFormatReaderExtension();
	
	virtual ~lbPluginDBForeignKeysInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBForeignKeysInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBForeignKeysInternalFormatReaderExtension, lbPluginDBForeignKeysInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBForeignKeysInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBForeignKeysInternalFormatReaderExtension::lbPluginDBForeignKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBForeignKeysInternalFormatReaderExtension::lbPluginDBForeignKeysInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginDBForeignKeysInternalFormatReaderExtension::~lbPluginDBForeignKeysInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBForeignKeysInternalFormatReaderExtension::~lbPluginDBForeignKeysInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBForeignKeysModelExtension == NULL) {
		DBForeignKeysInternalFormatReaderExtension* DBForeignKeysModelExtension = new DBForeignKeysInternalFormatReaderExtension();
		
	
		QI(DBForeignKeysModelExtension, lb_I_Unknown, ukDBForeignKeysModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBForeignKeysModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBForeignKeysModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBForeignKeysInternalFormatReaderExtension* DBForeignKeysModelExtension = new DBForeignKeysInternalFormatReaderExtension();
		
	
		QI(DBForeignKeysModelExtension, lb_I_Unknown, ukDBForeignKeysModelExtension)
	}
	
	lb_I_Unknown* r = ukDBForeignKeysModelExtension.getPtr();
	ukDBForeignKeysModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBForeignKeysInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBForeignKeysModelExtension != NULL) {
                ukDBForeignKeysModelExtension--;
                ukDBForeignKeysModelExtension.resetPtr();
        }
}

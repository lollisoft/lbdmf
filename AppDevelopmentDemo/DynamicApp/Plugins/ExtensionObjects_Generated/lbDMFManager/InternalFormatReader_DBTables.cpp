
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
#include <InternalFormatReader_DBTables.h>

IMPLEMENT_FUNCTOR(instanceOfDBTablesInternalFormatReaderExtension, DBTablesInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBTablesInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBTablesInternalFormatReaderExtension::DBTablesInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBTablesInternalFormatReaderExtension::DBTablesInternalFormatReaderExtension() called." LOG_
}

DBTablesInternalFormatReaderExtension::~DBTablesInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBTablesInternalFormatReaderExtension::~DBTablesInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBTablesInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBTablesInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBTablesInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBTables, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBTablesInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_DBTables." LOG_
		}
	} else {
		_LOG << "Error: DBTablesInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBTablesInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: DBTablesInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: DBTablesInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBTablesInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _catalogname = NULL;
		char* _schemaname = NULL;
		char* _tablename = NULL;
		char* _tabletype = NULL;
		char* _tableremarks = NULL;
		long _anwendungenid = 0;
	
		*iStream >> _ID;

		*iStream >> _catalogname;
		*iStream >> _schemaname;
		*iStream >> _tablename;
		*iStream >> _tabletype;
		*iStream >> _tableremarks;
		*iStream >> _anwendungenid;
		owningObject->add(_catalogname, _schemaname, _tablename, _tabletype, _tableremarks, _anwendungenid,  _ID);

		// Leaky !
	}
}



class lbPluginDBTablesInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBTablesInternalFormatReaderExtension();
	
	virtual ~lbPluginDBTablesInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBTablesInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBTablesInternalFormatReaderExtension, lbPluginDBTablesInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBTablesInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBTablesInternalFormatReaderExtension::lbPluginDBTablesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBTablesInternalFormatReaderExtension::lbPluginDBTablesInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginDBTablesInternalFormatReaderExtension::~lbPluginDBTablesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBTablesInternalFormatReaderExtension::~lbPluginDBTablesInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTablesModelExtension == NULL) {
		DBTablesInternalFormatReaderExtension* DBTablesModelExtension = new DBTablesInternalFormatReaderExtension();
		
	
		QI(DBTablesModelExtension, lb_I_Unknown, ukDBTablesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBTablesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBTablesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBTablesInternalFormatReaderExtension* DBTablesModelExtension = new DBTablesInternalFormatReaderExtension();
		
	
		QI(DBTablesModelExtension, lb_I_Unknown, ukDBTablesModelExtension)
	}
	
	lb_I_Unknown* r = ukDBTablesModelExtension.getPtr();
	ukDBTablesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBTablesInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBTablesModelExtension != NULL) {
                ukDBTablesModelExtension--;
                ukDBTablesModelExtension.resetPtr();
        }
}

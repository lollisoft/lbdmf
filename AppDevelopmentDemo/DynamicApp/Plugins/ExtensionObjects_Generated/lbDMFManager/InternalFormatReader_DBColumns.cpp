
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
#include <InternalFormatReader_DBColumns.h>

IMPLEMENT_FUNCTOR(instanceOfDBColumnsInternalFormatReaderExtension, DBColumnsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(DBColumnsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

DBColumnsInternalFormatReaderExtension::DBColumnsInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBColumnsInternalFormatReaderExtension::DBColumnsInternalFormatReaderExtension() called." LOG_
}

DBColumnsInternalFormatReaderExtension::~DBColumnsInternalFormatReaderExtension() {
	_CL_VERBOSE << "DBColumnsInternalFormatReaderExtension::~DBColumnsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL DBColumnsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: DBColumnsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL DBColumnsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_DBColumns, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: DBColumnsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_DBColumns." LOG_
		}
	} else {
		_LOG << "Error: DBColumnsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBColumnsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: DBColumnsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: DBColumnsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL DBColumnsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _columnname = NULL;
		char* _columnremarks = NULL;
		char* _typename = NULL;
		int _columnsize = 0;
		bool _nullable = false;
		char* _tablename = NULL;
		long _dbtableid = 0;
	
		*iStream >> _ID;

		*iStream >> _columnname;
		*iStream >> _columnremarks;
		*iStream >> _typename;
		*iStream >> _columnsize;
		*iStream >> _nullable;
		*iStream >> _tablename;
		*iStream >> _dbtableid;
		owningObject->add(_columnname, _columnremarks, _typename, _columnsize, _nullable, _tablename, _dbtableid,  _ID);

		// Leaky !
	}
}



class lbPluginDBColumnsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginDBColumnsInternalFormatReaderExtension();
	
	virtual ~lbPluginDBColumnsInternalFormatReaderExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginDBColumnsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginDBColumnsInternalFormatReaderExtension, lbPluginDBColumnsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginDBColumnsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginDBColumnsInternalFormatReaderExtension::lbPluginDBColumnsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBColumnsInternalFormatReaderExtension::lbPluginDBColumnsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginDBColumnsInternalFormatReaderExtension::~lbPluginDBColumnsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginDBColumnsInternalFormatReaderExtension::~lbPluginDBColumnsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBColumnsModelExtension == NULL) {
		DBColumnsInternalFormatReaderExtension* DBColumnsModelExtension = new DBColumnsInternalFormatReaderExtension();
		
	
		QI(DBColumnsModelExtension, lb_I_Unknown, ukDBColumnsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukDBColumnsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukDBColumnsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		DBColumnsInternalFormatReaderExtension* DBColumnsModelExtension = new DBColumnsInternalFormatReaderExtension();
		
	
		QI(DBColumnsModelExtension, lb_I_Unknown, ukDBColumnsModelExtension)
	}
	
	lb_I_Unknown* r = ukDBColumnsModelExtension.getPtr();
	ukDBColumnsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginDBColumnsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukDBColumnsModelExtension != NULL) {
                ukDBColumnsModelExtension--;
                ukDBColumnsModelExtension.resetPtr();
        }
}

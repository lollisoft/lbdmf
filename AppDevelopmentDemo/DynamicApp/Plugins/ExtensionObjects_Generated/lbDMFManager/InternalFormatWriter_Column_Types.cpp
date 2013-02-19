
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
#include <InternalFormatWriter_Column_Types.h>

IMPLEMENT_FUNCTOR(instanceOfColumn_TypesInternalFormatWriterExtension, Column_TypesInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Column_TypesInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Column_TypesInternalFormatWriterExtension::Column_TypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "Column_TypesInternalFormatWriterExtension::Column_TypesInternalFormatWriterExtension() called." LOG_
}

Column_TypesInternalFormatWriterExtension::~Column_TypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "Column_TypesInternalFormatWriterExtension::~Column_TypesInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Column_TypesInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Column_TypesInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Column_TypesInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Column_Types, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Column_TypesInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_Column_Types." LOG_
		}
	} else {
		_LOG << "Error: Column_TypesInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Column_TypesInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Column_TypesInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Column_TypesInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->Count();
	*oStream << count;
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_name();
		*oStream << owningObject->get_tablename();
		*oStream << owningObject->get_ro();
		*oStream << owningObject->get_specialcolumn();
		*oStream << owningObject->get_controltype();
	}
}



class lbPluginColumn_TypesInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginColumn_TypesInternalFormatWriterExtension();
	
	virtual ~lbPluginColumn_TypesInternalFormatWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginColumn_TypesInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginColumn_TypesInternalFormatWriterExtension, lbPluginColumn_TypesInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginColumn_TypesInternalFormatWriterExtension::lbPluginColumn_TypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatWriterExtension::lbPluginColumn_TypesInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginColumn_TypesInternalFormatWriterExtension::~lbPluginColumn_TypesInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginColumn_TypesInternalFormatWriterExtension::~lbPluginColumn_TypesInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {
		Column_TypesInternalFormatWriterExtension* Column_TypesModelExtension = new Column_TypesInternalFormatWriterExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukColumn_TypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukColumn_TypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Column_TypesInternalFormatWriterExtension* Column_TypesModelExtension = new Column_TypesInternalFormatWriterExtension();
		
	
		QI(Column_TypesModelExtension, lb_I_Unknown, ukColumn_TypesModelExtension)
	}
	
	lb_I_Unknown* r = ukColumn_TypesModelExtension.getPtr();
	ukColumn_TypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginColumn_TypesInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukColumn_TypesModelExtension != NULL) {
                ukColumn_TypesModelExtension--;
                ukColumn_TypesModelExtension.resetPtr();
        }
}

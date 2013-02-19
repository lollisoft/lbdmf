
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
#include <InternalFormatReader_Formular_Actions.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_ActionsInternalFormatReaderExtension, Formular_ActionsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_ActionsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Formular_ActionsInternalFormatReaderExtension::Formular_ActionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "Formular_ActionsInternalFormatReaderExtension::Formular_ActionsInternalFormatReaderExtension() called." LOG_
}

Formular_ActionsInternalFormatReaderExtension::~Formular_ActionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "Formular_ActionsInternalFormatReaderExtension::~Formular_ActionsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Formular_ActionsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_ActionsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_ActionsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Actions, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_ActionsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Formular_Actions." LOG_
		}
	} else {
		_LOG << "Error: Formular_ActionsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ActionsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Formular_ActionsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: Formular_ActionsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ActionsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _event = NULL;
		long _action = 0;
		long _formular = 0;
	
		*iStream >> _ID;

		*iStream >> _event;
		*iStream >> _action;
		*iStream >> _formular;
		owningObject->add(_event, _action, _formular,  _ID);

		// Leaky !
	}
}



class lbPluginFormular_ActionsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormular_ActionsInternalFormatReaderExtension();
	
	virtual ~lbPluginFormular_ActionsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormular_ActionsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_ActionsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_ActionsInternalFormatReaderExtension, lbPluginFormular_ActionsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_ActionsInternalFormatReaderExtension::lbPluginFormular_ActionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatReaderExtension::lbPluginFormular_ActionsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginFormular_ActionsInternalFormatReaderExtension::~lbPluginFormular_ActionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatReaderExtension::~lbPluginFormular_ActionsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModelExtension == NULL) {
		Formular_ActionsInternalFormatReaderExtension* Formular_ActionsModelExtension = new Formular_ActionsInternalFormatReaderExtension();
		
	
		QI(Formular_ActionsModelExtension, lb_I_Unknown, ukFormular_ActionsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_ActionsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_ActionsInternalFormatReaderExtension* Formular_ActionsModelExtension = new Formular_ActionsInternalFormatReaderExtension();
		
	
		QI(Formular_ActionsModelExtension, lb_I_Unknown, ukFormular_ActionsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_ActionsModelExtension.getPtr();
	ukFormular_ActionsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_ActionsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_ActionsModelExtension != NULL) {
                ukFormular_ActionsModelExtension--;
                ukFormular_ActionsModelExtension.resetPtr();
        }
}

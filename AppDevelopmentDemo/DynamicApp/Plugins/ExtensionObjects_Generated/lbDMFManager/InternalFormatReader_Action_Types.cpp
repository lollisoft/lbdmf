
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
#include <InternalFormatReader_Action_Types.h>

IMPLEMENT_FUNCTOR(instanceOfAction_TypesInternalFormatReaderExtension, Action_TypesInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_TypesInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_TypesInternalFormatReaderExtension::Action_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "Action_TypesInternalFormatReaderExtension::Action_TypesInternalFormatReaderExtension() called." LOG_
}

Action_TypesInternalFormatReaderExtension::~Action_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "Action_TypesInternalFormatReaderExtension::~Action_TypesInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_TypesInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_TypesInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_TypesInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Types, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_TypesInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Action_Types." LOG_
		}
	} else {
		_LOG << "Error: Action_TypesInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_TypesInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Action_TypesInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: Action_TypesInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_TypesInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _bezeichnung = NULL;
		char* _action_handler = NULL;
		char* _module = NULL;
	
		*iStream >> _ID;

		*iStream >> _bezeichnung;
		*iStream >> _action_handler;
		*iStream >> _module;
		_LOG << "Read Action_Types entry from database: " << _bezeichnung << ", " << _action_handler << ", " << _module << ", " <<  _ID LOG_
		owningObject->addAction_Types(_bezeichnung, _action_handler, _module,  _ID);

		// Leaky !
	}
}



class lbPluginAction_TypesInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_TypesInternalFormatReaderExtension();
	
	virtual ~lbPluginAction_TypesInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_TypesModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_TypesInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_TypesInternalFormatReaderExtension, lbPluginAction_TypesInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_TypesInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_TypesInternalFormatReaderExtension::lbPluginAction_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_TypesInternalFormatReaderExtension::lbPluginAction_TypesInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginAction_TypesInternalFormatReaderExtension::~lbPluginAction_TypesInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_TypesInternalFormatReaderExtension::~lbPluginAction_TypesInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModelExtension == NULL) {
		Action_TypesInternalFormatReaderExtension* Action_TypesModelExtension = new Action_TypesInternalFormatReaderExtension();
		
	
		QI(Action_TypesModelExtension, lb_I_Unknown, ukAction_TypesModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_TypesModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_TypesModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_TypesInternalFormatReaderExtension* Action_TypesModelExtension = new Action_TypesInternalFormatReaderExtension();
		
	
		QI(Action_TypesModelExtension, lb_I_Unknown, ukAction_TypesModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_TypesModelExtension.getPtr();
	ukAction_TypesModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_TypesInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_TypesModelExtension != NULL) {
                ukAction_TypesModelExtension--;
                ukAction_TypesModelExtension.resetPtr();
        }
}

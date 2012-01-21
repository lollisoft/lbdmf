
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
#include <InternalFormatReader_ActionStep_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOfActionStep_ParametersInternalFormatReaderExtension, ActionStep_ParametersInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ActionStep_ParametersInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ActionStep_ParametersInternalFormatReaderExtension::ActionStep_ParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "ActionStep_ParametersInternalFormatReaderExtension::ActionStep_ParametersInternalFormatReaderExtension() called." LOG_
}

ActionStep_ParametersInternalFormatReaderExtension::~ActionStep_ParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "ActionStep_ParametersInternalFormatReaderExtension::~ActionStep_ParametersInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ActionStep_ParametersInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ActionStep_ParametersInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ActionStep_ParametersInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ActionStep_Parameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ActionStep_ParametersInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_ActionStep_Parameters." LOG_
		}
	} else {
		_LOG << "Error: ActionStep_ParametersInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ActionStep_ParametersInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ActionStep_ParametersInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _description = NULL;
		char* _name = NULL;
		char* _value = NULL;
		char* _interface = NULL;
		long _action_step_id = 0;
	
		*iStream >> _ID;

		*iStream >> _description;
		*iStream >> _name;
		*iStream >> _value;
		*iStream >> _interface;
		*iStream >> _action_step_id;
		_LOG << "Read ActionStep_Parameters entry from database: " << _description << ", " << _name << ", " << _value << ", " << _interface << ", " << _action_step_id << ", " <<  _ID LOG_
		owningObject->addActionStep_Parameters(_description, _name, _value, _interface, _action_step_id,  _ID);

		// Leaky !
	}
}



class lbPluginActionStep_ParametersInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginActionStep_ParametersInternalFormatReaderExtension();
	
	virtual ~lbPluginActionStep_ParametersInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukActionStep_ParametersModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStep_ParametersInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStep_ParametersInternalFormatReaderExtension, lbPluginActionStep_ParametersInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionStep_ParametersInternalFormatReaderExtension::lbPluginActionStep_ParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatReaderExtension::lbPluginActionStep_ParametersInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginActionStep_ParametersInternalFormatReaderExtension::~lbPluginActionStep_ParametersInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatReaderExtension::~lbPluginActionStep_ParametersInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {
		ActionStep_ParametersInternalFormatReaderExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersInternalFormatReaderExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionStep_ParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ActionStep_ParametersInternalFormatReaderExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersInternalFormatReaderExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukActionStep_ParametersModelExtension.getPtr();
	ukActionStep_ParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionStep_ParametersInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionStep_ParametersModelExtension != NULL) {
                ukActionStep_ParametersModelExtension--;
                ukActionStep_ParametersModelExtension.resetPtr();
        }
}

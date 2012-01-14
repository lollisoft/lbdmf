
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
#include <InternalFormatWriter_ActionStep_Parameters.h>

IMPLEMENT_FUNCTOR(instanceOfActionStep_ParametersInternalFormatWriterExtension, ActionStep_ParametersInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ActionStep_ParametersInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

ActionStep_ParametersInternalFormatWriterExtension::ActionStep_ParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "ActionStep_ParametersInternalFormatWriterExtension::ActionStep_ParametersInternalFormatWriterExtension() called." LOG_
}

ActionStep_ParametersInternalFormatWriterExtension::~ActionStep_ParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "ActionStep_ParametersInternalFormatWriterExtension::~ActionStep_ParametersInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL ActionStep_ParametersInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ActionStep_ParametersInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ActionStep_ParametersInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ActionStep_Parameters, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ActionStep_ParametersInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_ActionStep_Parameters." LOG_
		}
	} else {
		_LOG << "Error: ActionStep_ParametersInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ActionStep_ParametersInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: ActionStep_ParametersInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ActionStep_ParametersInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getActionStep_ParametersCount();
	*oStream << count;
	
	owningObject->finishActionStep_ParametersIteration();
	
	while (owningObject->hasMoreActionStep_Parameters()) {
		owningObject->setNextActionStep_Parameters();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_description();
		*oStream << owningObject->get_name();
		*oStream << owningObject->get_value();
		*oStream << owningObject->get_interface();
		*oStream << owningObject->get_action_step_id();
	}
}



class lbPluginActionStep_ParametersInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginActionStep_ParametersInternalFormatWriterExtension();
	
	virtual ~lbPluginActionStep_ParametersInternalFormatWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginActionStep_ParametersInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginActionStep_ParametersInternalFormatWriterExtension, lbPluginActionStep_ParametersInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginActionStep_ParametersInternalFormatWriterExtension::lbPluginActionStep_ParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatWriterExtension::lbPluginActionStep_ParametersInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginActionStep_ParametersInternalFormatWriterExtension::~lbPluginActionStep_ParametersInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginActionStep_ParametersInternalFormatWriterExtension::~lbPluginActionStep_ParametersInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {
		ActionStep_ParametersInternalFormatWriterExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersInternalFormatWriterExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukActionStep_ParametersModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukActionStep_ParametersModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ActionStep_ParametersInternalFormatWriterExtension* ActionStep_ParametersModelExtension = new ActionStep_ParametersInternalFormatWriterExtension();
		
	
		QI(ActionStep_ParametersModelExtension, lb_I_Unknown, ukActionStep_ParametersModelExtension)
	}
	
	lb_I_Unknown* r = ukActionStep_ParametersModelExtension.getPtr();
	ukActionStep_ParametersModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginActionStep_ParametersInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukActionStep_ParametersModelExtension != NULL) {
                ukActionStep_ParametersModelExtension--;
                ukActionStep_ParametersModelExtension.resetPtr();
        }
}

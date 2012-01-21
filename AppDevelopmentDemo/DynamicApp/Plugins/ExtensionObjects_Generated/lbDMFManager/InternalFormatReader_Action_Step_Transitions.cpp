
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
#include <InternalFormatReader_Action_Step_Transitions.h>

IMPLEMENT_FUNCTOR(instanceOfAction_Step_TransitionsInternalFormatReaderExtension, Action_Step_TransitionsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Action_Step_TransitionsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

Action_Step_TransitionsInternalFormatReaderExtension::Action_Step_TransitionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "Action_Step_TransitionsInternalFormatReaderExtension::Action_Step_TransitionsInternalFormatReaderExtension() called." LOG_
}

Action_Step_TransitionsInternalFormatReaderExtension::~Action_Step_TransitionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "Action_Step_TransitionsInternalFormatReaderExtension::~Action_Step_TransitionsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL Action_Step_TransitionsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Action_Step_TransitionsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Action_Step_TransitionsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Action_Step_Transitions, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Action_Step_TransitionsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Action_Step_Transitions." LOG_
		}
	} else {
		_LOG << "Error: Action_Step_TransitionsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_Step_TransitionsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Action_Step_TransitionsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: Action_Step_TransitionsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Action_Step_TransitionsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _expression = NULL;
		long _src_actionid = 0;
		long _dst_actionid = 0;
		char* _description = NULL;
	
		*iStream >> _ID;

		*iStream >> _expression;
		*iStream >> _src_actionid;
		*iStream >> _dst_actionid;
		*iStream >> _description;
		_LOG << "Read Action_Step_Transitions entry from database: " << _expression << ", " << _src_actionid << ", " << _dst_actionid << ", " << _description << ", " <<  _ID LOG_
		owningObject->addAction_Step_Transitions(_expression, _src_actionid, _dst_actionid, _description,  _ID);

		// Leaky !
	}
}



class lbPluginAction_Step_TransitionsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAction_Step_TransitionsInternalFormatReaderExtension();
	
	virtual ~lbPluginAction_Step_TransitionsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAction_Step_TransitionsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAction_Step_TransitionsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAction_Step_TransitionsInternalFormatReaderExtension, lbPluginAction_Step_TransitionsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAction_Step_TransitionsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAction_Step_TransitionsInternalFormatReaderExtension::lbPluginAction_Step_TransitionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_Step_TransitionsInternalFormatReaderExtension::lbPluginAction_Step_TransitionsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginAction_Step_TransitionsInternalFormatReaderExtension::~lbPluginAction_Step_TransitionsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAction_Step_TransitionsInternalFormatReaderExtension::~lbPluginAction_Step_TransitionsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_Step_TransitionsModelExtension == NULL) {
		Action_Step_TransitionsInternalFormatReaderExtension* Action_Step_TransitionsModelExtension = new Action_Step_TransitionsInternalFormatReaderExtension();
		
	
		QI(Action_Step_TransitionsModelExtension, lb_I_Unknown, ukAction_Step_TransitionsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAction_Step_TransitionsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAction_Step_TransitionsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Action_Step_TransitionsInternalFormatReaderExtension* Action_Step_TransitionsModelExtension = new Action_Step_TransitionsInternalFormatReaderExtension();
		
	
		QI(Action_Step_TransitionsModelExtension, lb_I_Unknown, ukAction_Step_TransitionsModelExtension)
	}
	
	lb_I_Unknown* r = ukAction_Step_TransitionsModelExtension.getPtr();
	ukAction_Step_TransitionsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAction_Step_TransitionsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAction_Step_TransitionsModelExtension != NULL) {
                ukAction_Step_TransitionsModelExtension--;
                ukAction_Step_TransitionsModelExtension.resetPtr();
        }
}

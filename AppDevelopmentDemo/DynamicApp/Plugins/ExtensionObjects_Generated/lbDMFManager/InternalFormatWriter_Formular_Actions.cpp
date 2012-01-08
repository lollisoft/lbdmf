
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
#include <InternalFormatWriter_Formular_Actions.h>

IMPLEMENT_FUNCTOR(instanceOfFormular_ActionsInternalFormatWriterExtension, Formular_ActionsInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(Formular_ActionsInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

Formular_ActionsInternalFormatWriterExtension::Formular_ActionsInternalFormatWriterExtension() {
	_CL_VERBOSE << "Formular_ActionsInternalFormatWriterExtension::Formular_ActionsInternalFormatWriterExtension() called." LOG_
}

Formular_ActionsInternalFormatWriterExtension::~Formular_ActionsInternalFormatWriterExtension() {
	_CL_VERBOSE << "Formular_ActionsInternalFormatWriterExtension::~Formular_ActionsInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL Formular_ActionsInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: Formular_ActionsInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL Formular_ActionsInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formular_Actions, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: Formular_ActionsInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_Formular_Actions." LOG_
		}
	} else {
		_LOG << "Error: Formular_ActionsInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ActionsInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: Formular_ActionsInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: Formular_ActionsInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL Formular_ActionsInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getFormular_ActionsCount();
	*oStream << count;
	
	owningObject->finishFormular_ActionsIteration();
	
	while (owningObject->hasMoreFormular_Actions()) {
		owningObject->setNextFormular_Actions();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_event();
		*oStream << owningObject->get_action();
		*oStream << owningObject->get_formular();
		*oStream << owningObject->get_formular();
	}
}



class lbPluginFormular_ActionsInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFormular_ActionsInternalFormatWriterExtension();
	
	virtual ~lbPluginFormular_ActionsInternalFormatWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormular_ActionsInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormular_ActionsInternalFormatWriterExtension, lbPluginFormular_ActionsInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormular_ActionsInternalFormatWriterExtension::lbPluginFormular_ActionsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatWriterExtension::lbPluginFormular_ActionsInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginFormular_ActionsInternalFormatWriterExtension::~lbPluginFormular_ActionsInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFormular_ActionsInternalFormatWriterExtension::~lbPluginFormular_ActionsInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModelExtension == NULL) {
		Formular_ActionsInternalFormatWriterExtension* Formular_ActionsModelExtension = new Formular_ActionsInternalFormatWriterExtension();
		
	
		QI(Formular_ActionsModelExtension, lb_I_Unknown, ukFormular_ActionsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormular_ActionsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormular_ActionsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		Formular_ActionsInternalFormatWriterExtension* Formular_ActionsModelExtension = new Formular_ActionsInternalFormatWriterExtension();
		
	
		QI(Formular_ActionsModelExtension, lb_I_Unknown, ukFormular_ActionsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormular_ActionsModelExtension.getPtr();
	ukFormular_ActionsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormular_ActionsInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormular_ActionsModelExtension != NULL) {
                ukFormular_ActionsModelExtension--;
                ukFormular_ActionsModelExtension.resetPtr();
        }
}

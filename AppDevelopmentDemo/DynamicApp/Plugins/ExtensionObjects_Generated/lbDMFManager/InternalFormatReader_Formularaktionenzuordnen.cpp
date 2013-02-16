
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
#include <InternalFormatReader_Formularaktionenzuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfFormularaktionenzuordnenInternalFormatReaderExtension, FormularaktionenzuordnenInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularaktionenzuordnenInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormularaktionenzuordnenInternalFormatReaderExtension::FormularaktionenzuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "FormularaktionenzuordnenInternalFormatReaderExtension::FormularaktionenzuordnenInternalFormatReaderExtension() called." LOG_
}

FormularaktionenzuordnenInternalFormatReaderExtension::~FormularaktionenzuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "FormularaktionenzuordnenInternalFormatReaderExtension::~FormularaktionenzuordnenInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormularaktionenzuordnenInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularaktionenzuordnenInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormularaktionenzuordnenInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formularaktionenzuordnen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormularaktionenzuordnenInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Formularaktionenzuordnen." LOG_
		}
	} else {
		_LOG << "Error: FormularaktionenzuordnenInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularaktionenzuordnenInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FormularaktionenzuordnenInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: FormularaktionenzuordnenInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularaktionenzuordnenInternalFormatReaderExtension::execute() {
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
		owningObject->addFormularaktionenzuordnen(_event, _action, _formular,  _ID);

		// Leaky !
	}
}



class lbPluginFormularaktionenzuordnenInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormularaktionenzuordnenInternalFormatReaderExtension();
	
	virtual ~lbPluginFormularaktionenzuordnenInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularaktionenzuordnenInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularaktionenzuordnenInternalFormatReaderExtension, lbPluginFormularaktionenzuordnenInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::lbPluginFormularaktionenzuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::lbPluginFormularaktionenzuordnenInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::~lbPluginFormularaktionenzuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::~lbPluginFormularaktionenzuordnenInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModelExtension == NULL) {
		FormularaktionenzuordnenInternalFormatReaderExtension* FormularaktionenzuordnenModelExtension = new FormularaktionenzuordnenInternalFormatReaderExtension();
		
	
		QI(FormularaktionenzuordnenModelExtension, lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularaktionenzuordnenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularaktionenzuordnenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularaktionenzuordnenInternalFormatReaderExtension* FormularaktionenzuordnenModelExtension = new FormularaktionenzuordnenInternalFormatReaderExtension();
		
	
		QI(FormularaktionenzuordnenModelExtension, lb_I_Unknown, ukFormularaktionenzuordnenModelExtension)
	}
	
	lb_I_Unknown* r = ukFormularaktionenzuordnenModelExtension.getPtr();
	ukFormularaktionenzuordnenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularaktionenzuordnenInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularaktionenzuordnenModelExtension != NULL) {
                ukFormularaktionenzuordnenModelExtension--;
                ukFormularaktionenzuordnenModelExtension.resetPtr();
        }
}

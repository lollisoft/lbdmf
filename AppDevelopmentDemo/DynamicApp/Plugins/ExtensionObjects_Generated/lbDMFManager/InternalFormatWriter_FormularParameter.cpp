
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
#include <InternalFormatWriter_FormularParameter.h>

IMPLEMENT_FUNCTOR(instanceOfFormularParameterInternalFormatWriterExtension, FormularParameterInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularParameterInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormularParameterInternalFormatWriterExtension::FormularParameterInternalFormatWriterExtension() {
	_CL_VERBOSE << "FormularParameterInternalFormatWriterExtension::FormularParameterInternalFormatWriterExtension() called." LOG_
}

FormularParameterInternalFormatWriterExtension::~FormularParameterInternalFormatWriterExtension() {
	_CL_VERBOSE << "FormularParameterInternalFormatWriterExtension::~FormularParameterInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormularParameterInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularParameterInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormularParameterInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_FormularParameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormularParameterInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_FormularParameter." LOG_
		}
	} else {
		_LOG << "Error: FormularParameterInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularParameterInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FormularParameterInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: FormularParameterInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularParameterInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->Count();
	*oStream << count;
	
	owningObject->finishIteration();
	
	while (owningObject->hasMoreElements()) {
		owningObject->setNextElement();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_parametervalue();
		*oStream << owningObject->get_parametername();
		*oStream << owningObject->get_formularid();
	}
}



class lbPluginFormularParameterInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginFormularParameterInternalFormatWriterExtension();
	
	virtual ~lbPluginFormularParameterInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularParameterModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularParameterInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularParameterInternalFormatWriterExtension, lbPluginFormularParameterInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularParameterInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularParameterInternalFormatWriterExtension::lbPluginFormularParameterInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFormularParameterInternalFormatWriterExtension::lbPluginFormularParameterInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginFormularParameterInternalFormatWriterExtension::~lbPluginFormularParameterInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginFormularParameterInternalFormatWriterExtension::~lbPluginFormularParameterInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModelExtension == NULL) {
		FormularParameterInternalFormatWriterExtension* FormularParameterModelExtension = new FormularParameterInternalFormatWriterExtension();
		
	
		QI(FormularParameterModelExtension, lb_I_Unknown, ukFormularParameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularParameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularParameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularParameterInternalFormatWriterExtension* FormularParameterModelExtension = new FormularParameterInternalFormatWriterExtension();
		
	
		QI(FormularParameterModelExtension, lb_I_Unknown, ukFormularParameterModelExtension)
	}
	
	lb_I_Unknown* r = ukFormularParameterModelExtension.getPtr();
	ukFormularParameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularParameterInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularParameterModelExtension != NULL) {
                ukFormularParameterModelExtension--;
                ukFormularParameterModelExtension.resetPtr();
        }
}

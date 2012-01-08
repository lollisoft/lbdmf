
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
#include <InternalFormatReader_ApplicationParameter.h>

IMPLEMENT_FUNCTOR(instanceOfApplicationParameterInternalFormatReaderExtension, ApplicationParameterInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(ApplicationParameterInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
END_IMPLEMENT_LB_UNKNOWN()

ApplicationParameterInternalFormatReaderExtension::ApplicationParameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "ApplicationParameterInternalFormatReaderExtension::ApplicationParameterInternalFormatReaderExtension() called." LOG_
}

ApplicationParameterInternalFormatReaderExtension::~ApplicationParameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "ApplicationParameterInternalFormatReaderExtension::~ApplicationParameterInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL ApplicationParameterInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: ApplicationParameterInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL ApplicationParameterInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_ApplicationParameter, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: ApplicationParameterInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_ApplicationParameter." LOG_
		}
	} else {
		_LOG << "Error: ApplicationParameterInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationParameterInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: ApplicationParameterInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: ApplicationParameterInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL ApplicationParameterInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _parametername = NULL;
		char* _parametervalue = NULL;
		long _anwendungid = 0;
	
		*iStream >> _ID;

		*iStream >> _parametername;
		*iStream >> _parametervalue;
		*iStream >> _anwendungid;
												
		owningObject->addApplicationParameter(_parametername, _parametervalue, _anwendungid,  _ID);

		// Leaky !
	}
}



class lbPluginApplicationParameterInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginApplicationParameterInternalFormatReaderExtension();
	
	virtual ~lbPluginApplicationParameterInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukApplicationParameterModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginApplicationParameterInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginApplicationParameterInternalFormatReaderExtension, lbPluginApplicationParameterInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginApplicationParameterInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginApplicationParameterInternalFormatReaderExtension::lbPluginApplicationParameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationParameterInternalFormatReaderExtension::lbPluginApplicationParameterInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginApplicationParameterInternalFormatReaderExtension::~lbPluginApplicationParameterInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginApplicationParameterInternalFormatReaderExtension::~lbPluginApplicationParameterInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameterModelExtension == NULL) {
		ApplicationParameterInternalFormatReaderExtension* ApplicationParameterModelExtension = new ApplicationParameterInternalFormatReaderExtension();
		
	
		QI(ApplicationParameterModelExtension, lb_I_Unknown, ukApplicationParameterModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukApplicationParameterModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukApplicationParameterModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		ApplicationParameterInternalFormatReaderExtension* ApplicationParameterModelExtension = new ApplicationParameterInternalFormatReaderExtension();
		
	
		QI(ApplicationParameterModelExtension, lb_I_Unknown, ukApplicationParameterModelExtension)
	}
	
	lb_I_Unknown* r = ukApplicationParameterModelExtension.getPtr();
	ukApplicationParameterModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginApplicationParameterInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukApplicationParameterModelExtension != NULL) {
                ukApplicationParameterModelExtension--;
                ukApplicationParameterModelExtension.resetPtr();
        }
}

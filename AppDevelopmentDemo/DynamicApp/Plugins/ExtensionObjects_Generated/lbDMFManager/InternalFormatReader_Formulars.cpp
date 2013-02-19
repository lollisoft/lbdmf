
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
#include <InternalFormatReader_Formulars.h>

IMPLEMENT_FUNCTOR(instanceOfFormularsInternalFormatReaderExtension, FormularsInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(FormularsInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

FormularsInternalFormatReaderExtension::FormularsInternalFormatReaderExtension() {
	_CL_VERBOSE << "FormularsInternalFormatReaderExtension::FormularsInternalFormatReaderExtension() called." LOG_
}

FormularsInternalFormatReaderExtension::~FormularsInternalFormatReaderExtension() {
	_CL_VERBOSE << "FormularsInternalFormatReaderExtension::~FormularsInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL FormularsInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: FormularsInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL FormularsInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Formulars, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: FormularsInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Formulars." LOG_
		}
	} else {
		_LOG << "Error: FormularsInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularsInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: FormularsInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: FormularsInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL FormularsInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _name = NULL;
		char* _menuname = NULL;
		char* _menuhilfe = NULL;
		char* _eventname = NULL;
		char* _toolbarimage = NULL;
		long _anwendungid = 0;
		long _typ = 0;
	
		*iStream >> _ID;

		*iStream >> _name;
		*iStream >> _menuname;
		*iStream >> _menuhilfe;
		*iStream >> _eventname;
		*iStream >> _toolbarimage;
		*iStream >> _anwendungid;
		*iStream >> _typ;
		owningObject->add(_name, _menuname, _menuhilfe, _eventname, _toolbarimage, _anwendungid, _typ,  _ID);

		// Leaky !
	}
}



class lbPluginFormularsInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginFormularsInternalFormatReaderExtension();
	
	virtual ~lbPluginFormularsInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukFormularsModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginFormularsInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginFormularsInternalFormatReaderExtension, lbPluginFormularsInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginFormularsInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginFormularsInternalFormatReaderExtension::lbPluginFormularsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularsInternalFormatReaderExtension::lbPluginFormularsInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginFormularsInternalFormatReaderExtension::~lbPluginFormularsInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginFormularsInternalFormatReaderExtension::~lbPluginFormularsInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModelExtension == NULL) {
		FormularsInternalFormatReaderExtension* FormularsModelExtension = new FormularsInternalFormatReaderExtension();
		
	
		QI(FormularsModelExtension, lb_I_Unknown, ukFormularsModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukFormularsModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukFormularsModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		FormularsInternalFormatReaderExtension* FormularsModelExtension = new FormularsInternalFormatReaderExtension();
		
	
		QI(FormularsModelExtension, lb_I_Unknown, ukFormularsModelExtension)
	}
	
	lb_I_Unknown* r = ukFormularsModelExtension.getPtr();
	ukFormularsModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginFormularsInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukFormularsModelExtension != NULL) {
                ukFormularsModelExtension--;
                ukFormularsModelExtension.resetPtr();
        }
}

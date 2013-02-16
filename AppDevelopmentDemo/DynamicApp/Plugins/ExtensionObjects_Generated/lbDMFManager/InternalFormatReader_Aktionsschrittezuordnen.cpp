
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
#include <InternalFormatReader_Aktionsschrittezuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionsschrittezuordnenInternalFormatReaderExtension, AktionsschrittezuordnenInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionsschrittezuordnenInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AktionsschrittezuordnenInternalFormatReaderExtension::AktionsschrittezuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenInternalFormatReaderExtension::AktionsschrittezuordnenInternalFormatReaderExtension() called." LOG_
}

AktionsschrittezuordnenInternalFormatReaderExtension::~AktionsschrittezuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenInternalFormatReaderExtension::~AktionsschrittezuordnenInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL AktionsschrittezuordnenInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionsschrittezuordnenInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Aktionsschrittezuordnen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AktionsschrittezuordnenInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_Aktionsschrittezuordnen." LOG_
		}
	} else {
		_LOG << "Error: AktionsschrittezuordnenInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AktionsschrittezuordnenInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: AktionsschrittezuordnenInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		char* _bezeichnung = NULL;
		char* _what = NULL;
		int _a_order_nr = 0;
		long _type = 0;
		long _actionid = 0;
	
		*iStream >> _ID;

		*iStream >> _bezeichnung;
		*iStream >> _what;
		*iStream >> _a_order_nr;
		*iStream >> _type;
		*iStream >> _actionid;
		owningObject->addAktionsschrittezuordnen(_bezeichnung, _what, _a_order_nr, _type, _actionid,  _ID);

		// Leaky !
	}
}



class lbPluginAktionsschrittezuordnenInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAktionsschrittezuordnenInternalFormatReaderExtension();
	
	virtual ~lbPluginAktionsschrittezuordnenInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionsschrittezuordnenInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionsschrittezuordnenInternalFormatReaderExtension, lbPluginAktionsschrittezuordnenInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::lbPluginAktionsschrittezuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::lbPluginAktionsschrittezuordnenInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::~lbPluginAktionsschrittezuordnenInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::~lbPluginAktionsschrittezuordnenInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {
		AktionsschrittezuordnenInternalFormatReaderExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenInternalFormatReaderExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionsschrittezuordnenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionsschrittezuordnenInternalFormatReaderExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenInternalFormatReaderExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	}
	
	lb_I_Unknown* r = ukAktionsschrittezuordnenModelExtension.getPtr();
	ukAktionsschrittezuordnenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionsschrittezuordnenModelExtension != NULL) {
                ukAktionsschrittezuordnenModelExtension--;
                ukAktionsschrittezuordnenModelExtension.resetPtr();
        }
}

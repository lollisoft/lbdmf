
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
#include <InternalFormatReader_AnwendungenBenutzer.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungenBenutzerInternalFormatReaderExtension, AnwendungenBenutzerInternalFormatReaderExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungenBenutzerInternalFormatReaderExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AnwendungenBenutzerInternalFormatReaderExtension::AnwendungenBenutzerInternalFormatReaderExtension() {
	_CL_VERBOSE << "AnwendungenBenutzerInternalFormatReaderExtension::AnwendungenBenutzerInternalFormatReaderExtension() called." LOG_
}

AnwendungenBenutzerInternalFormatReaderExtension::~AnwendungenBenutzerInternalFormatReaderExtension() {
	_CL_VERBOSE << "AnwendungenBenutzerInternalFormatReaderExtension::~AnwendungenBenutzerInternalFormatReaderExtension() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungenBenutzerInternalFormatReaderExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungenBenutzerInternalFormatReaderExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AnwendungenBenutzerInternalFormatReaderExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_AnwendungenBenutzer, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AnwendungenBenutzerInternalFormatReaderExtension::setOwningObject() owning parameter is not a lb_I_AnwendungenBenutzer." LOG_
		}
	} else {
		_LOG << "Error: AnwendungenBenutzerInternalFormatReaderExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenBenutzerInternalFormatReaderExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AnwendungenBenutzerInternalFormatReaderExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_InputStream, iStream)
	} else {
		_LOG << "Error: AnwendungenBenutzerInternalFormatReaderExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenBenutzerInternalFormatReaderExtension::execute() {
	// Number of applications
	int   count = 0;
	*iStream >> count;
	
	for (int i = 0; i < count; i++) {
		long  _ID = -1;

		long _userid = 0;
		long _anwendungenid = 0;
	
		*iStream >> _ID;

		*iStream >> _userid;
		*iStream >> _anwendungenid;
		owningObject->addAnwendungenBenutzer(_userid, _anwendungenid,  _ID);

		// Leaky !
	}
}



class lbPluginAnwendungenBenutzerInternalFormatReaderExtension : public lb_I_PluginImpl {
public:
	lbPluginAnwendungenBenutzerInternalFormatReaderExtension();
	
	virtual ~lbPluginAnwendungenBenutzerInternalFormatReaderExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungenBenutzerInternalFormatReaderExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungenBenutzerInternalFormatReaderExtension, lbPluginAnwendungenBenutzerInternalFormatReaderExtension)

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungenBenutzerInternalFormatReaderExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungenBenutzerInternalFormatReaderExtension::lbPluginAnwendungenBenutzerInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerInternalFormatReaderExtension::lbPluginAnwendungenBenutzerInternalFormatReaderExtension() called.\n" LOG_
}

lbPluginAnwendungenBenutzerInternalFormatReaderExtension::~lbPluginAnwendungenBenutzerInternalFormatReaderExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenBenutzerInternalFormatReaderExtension::~lbPluginAnwendungenBenutzerInternalFormatReaderExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModelExtension == NULL) {
		AnwendungenBenutzerInternalFormatReaderExtension* AnwendungenBenutzerModelExtension = new AnwendungenBenutzerInternalFormatReaderExtension();
		
	
		QI(AnwendungenBenutzerModelExtension, lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungenBenutzerModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenBenutzerModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungenBenutzerInternalFormatReaderExtension* AnwendungenBenutzerModelExtension = new AnwendungenBenutzerInternalFormatReaderExtension();
		
	
		QI(AnwendungenBenutzerModelExtension, lb_I_Unknown, ukAnwendungenBenutzerModelExtension)
	}
	
	lb_I_Unknown* r = ukAnwendungenBenutzerModelExtension.getPtr();
	ukAnwendungenBenutzerModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungenBenutzerInternalFormatReaderExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungenBenutzerModelExtension != NULL) {
                ukAnwendungenBenutzerModelExtension--;
                ukAnwendungenBenutzerModelExtension.resetPtr();
        }
}

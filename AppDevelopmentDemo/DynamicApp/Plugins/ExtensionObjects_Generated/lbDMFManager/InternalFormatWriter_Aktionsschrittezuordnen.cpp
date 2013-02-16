
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
#include <InternalFormatWriter_Aktionsschrittezuordnen.h>

IMPLEMENT_FUNCTOR(instanceOfAktionsschrittezuordnenInternalFormatWriterExtension, AktionsschrittezuordnenInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AktionsschrittezuordnenInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AktionsschrittezuordnenInternalFormatWriterExtension::AktionsschrittezuordnenInternalFormatWriterExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenInternalFormatWriterExtension::AktionsschrittezuordnenInternalFormatWriterExtension() called." LOG_
}

AktionsschrittezuordnenInternalFormatWriterExtension::~AktionsschrittezuordnenInternalFormatWriterExtension() {
	_CL_VERBOSE << "AktionsschrittezuordnenInternalFormatWriterExtension::~AktionsschrittezuordnenInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL AktionsschrittezuordnenInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AktionsschrittezuordnenInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Aktionsschrittezuordnen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AktionsschrittezuordnenInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_Aktionsschrittezuordnen." LOG_
		}
	} else {
		_LOG << "Error: AktionsschrittezuordnenInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AktionsschrittezuordnenInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: AktionsschrittezuordnenInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AktionsschrittezuordnenInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getAktionsschrittezuordnenCount();
	*oStream << count;
	
	owningObject->finishAktionsschrittezuordnenIteration();
	
	while (owningObject->hasMoreAktionsschrittezuordnen()) {
		owningObject->setNextAktionsschrittezuordnen();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_bezeichnung();
		*oStream << owningObject->get_what();
		*oStream << owningObject->get_a_order_nr();
		*oStream << owningObject->get_type();
		*oStream << owningObject->get_actionid();
	}
}



class lbPluginAktionsschrittezuordnenInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAktionsschrittezuordnenInternalFormatWriterExtension();
	
	virtual ~lbPluginAktionsschrittezuordnenInternalFormatWriterExtension();

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

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAktionsschrittezuordnenInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAktionsschrittezuordnenInternalFormatWriterExtension, lbPluginAktionsschrittezuordnenInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::lbPluginAktionsschrittezuordnenInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::lbPluginAktionsschrittezuordnenInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::~lbPluginAktionsschrittezuordnenInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::~lbPluginAktionsschrittezuordnenInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {
		AktionsschrittezuordnenInternalFormatWriterExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenInternalFormatWriterExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAktionsschrittezuordnenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAktionsschrittezuordnenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AktionsschrittezuordnenInternalFormatWriterExtension* AktionsschrittezuordnenModelExtension = new AktionsschrittezuordnenInternalFormatWriterExtension();
		
	
		QI(AktionsschrittezuordnenModelExtension, lb_I_Unknown, ukAktionsschrittezuordnenModelExtension)
	}
	
	lb_I_Unknown* r = ukAktionsschrittezuordnenModelExtension.getPtr();
	ukAktionsschrittezuordnenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAktionsschrittezuordnenInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAktionsschrittezuordnenModelExtension != NULL) {
                ukAktionsschrittezuordnenModelExtension--;
                ukAktionsschrittezuordnenModelExtension.resetPtr();
        }
}

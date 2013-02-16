
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
#include <InternalFormatWriter_Anwendungen.h>

IMPLEMENT_FUNCTOR(instanceOfAnwendungenInternalFormatWriterExtension, AnwendungenInternalFormatWriterExtension)

BEGIN_IMPLEMENT_LB_UNKNOWN(AnwendungenInternalFormatWriterExtension)
	ADD_INTERFACE(lb_I_ExtensionObject)
	ADD_INTERFACE(lb_I_VisitorExtension)
END_IMPLEMENT_LB_UNKNOWN()

AnwendungenInternalFormatWriterExtension::AnwendungenInternalFormatWriterExtension() {
	_CL_VERBOSE << "AnwendungenInternalFormatWriterExtension::AnwendungenInternalFormatWriterExtension() called." LOG_
}

AnwendungenInternalFormatWriterExtension::~AnwendungenInternalFormatWriterExtension() {
	_CL_VERBOSE << "AnwendungenInternalFormatWriterExtension::~AnwendungenInternalFormatWriterExtension() called." LOG_
}

lbErrCodes LB_STDCALL AnwendungenInternalFormatWriterExtension::setData(lb_I_Unknown*) {
	_LOG << "Error: AnwendungenInternalFormatWriterExtension::setData(lb_I_Unknown*) not implemented." LOG_
	return ERR_NOT_IMPLEMENTED;
}

void LB_STDCALL AnwendungenInternalFormatWriterExtension::setOwningObject(lb_I_Unknown* owning) {
	// Need a lb_I_DatabaseOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (owning != NULL) 
	{
		QI(owning, lb_I_Anwendungen, owningObject)
		if (owningObject == NULL) {
			_LOG << "Error: AnwendungenInternalFormatWriterExtension::setOwningObject() owning parameter is not a lb_I_Anwendungen." LOG_
		}
	} else {
		_LOG << "Error: AnwendungenInternalFormatWriterExtension::setOwningObject() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenInternalFormatWriterExtension::setOperator(lb_I_Aspect* operation) {
	// Need a lb_I_FileOperation here from the aspect
	lbErrCodes err = ERR_NONE;
	
	if (operation != NULL) 
	{
		UAP(lb_I_FileOperation, fileOp)
		QI(operation, lb_I_FileOperation, fileOp)
		if (fileOp == NULL) {
			_LOG << "Error: AnwendungenInternalFormatWriterExtension::setOperator() operation parameter is not a lb_I_FileOperation." LOG_
		}
		UAP(lb_I_Stream, s)
		s = fileOp->getStream();
		
		QI(s, lb_I_OutputStream, oStream)
	} else {
		_LOG << "Error: AnwendungenInternalFormatWriterExtension::setOperator() called with a NULL pointer." LOG_
	}
}

void LB_STDCALL AnwendungenInternalFormatWriterExtension::execute() {
	int count;

	count = owningObject->getAnwendungenCount();
	*oStream << count;
	
	owningObject->finishAnwendungenIteration();
	
	while (owningObject->hasMoreAnwendungen()) {
		owningObject->setNextAnwendungen();
		
		*oStream << owningObject->get_id();
		// Copy values

		*oStream << owningObject->get_titel();
		*oStream << owningObject->get_name();
		*oStream << owningObject->get_interface();
		*oStream << owningObject->get_functor();
		*oStream << owningObject->get_modulename();
	}
}



class lbPluginAnwendungenInternalFormatWriterExtension : public lb_I_PluginImpl {
public:
	lbPluginAnwendungenInternalFormatWriterExtension();
	
	virtual ~lbPluginAnwendungenInternalFormatWriterExtension();

	bool LB_STDCALL canAutorun();
	lbErrCodes LB_STDCALL autorun();

	void LB_STDCALL initialize();
	
	bool LB_STDCALL run();

	lb_I_Unknown* LB_STDCALL peekImplementation();
	lb_I_Unknown* LB_STDCALL getImplementation();
	void LB_STDCALL releaseImplementation();

	void LB_STDCALL setNamespace(const char* _namespace) { }

	DECLARE_LB_UNKNOWN()
	
	UAP(lb_I_Unknown, ukAnwendungenModelExtension)
};

BEGIN_IMPLEMENT_LB_UNKNOWN(lbPluginAnwendungenInternalFormatWriterExtension)
        ADD_INTERFACE(lb_I_PluginImpl)
END_IMPLEMENT_LB_UNKNOWN()

IMPLEMENT_FUNCTOR(instanceOflbPluginAnwendungenInternalFormatWriterExtension, lbPluginAnwendungenInternalFormatWriterExtension)

lbErrCodes LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::setData(lb_I_Unknown* uk) {
	lbErrCodes err = ERR_NONE;

	_CL_VERBOSE << "lbPluginAnwendungenInternalFormatWriterExtension::setData(...) called.\n" LOG_

        return ERR_NOT_IMPLEMENTED;
}

lbPluginAnwendungenInternalFormatWriterExtension::lbPluginAnwendungenInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenInternalFormatWriterExtension::lbPluginAnwendungenInternalFormatWriterExtension() called.\n" LOG_
}

lbPluginAnwendungenInternalFormatWriterExtension::~lbPluginAnwendungenInternalFormatWriterExtension() {
	_CL_VERBOSE << "lbPluginAnwendungenInternalFormatWriterExtension::~lbPluginAnwendungenInternalFormatWriterExtension() called.\n" LOG_
}

bool LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::canAutorun() {
	return false;
}

lbErrCodes LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::autorun() {
	lbErrCodes err = ERR_NONE;
	return err;
}

void LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::initialize() {
}
	
bool LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::run() {
	return true;
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::peekImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenModelExtension == NULL) {
		AnwendungenInternalFormatWriterExtension* AnwendungenModelExtension = new AnwendungenInternalFormatWriterExtension();
		
	
		QI(AnwendungenModelExtension, lb_I_Unknown, ukAnwendungenModelExtension)
	} else {
		_CL_VERBOSE << "lbPluginDatabasePanel::peekImplementation() Implementation already peeked.\n" LOG_
	}
	
	return ukAnwendungenModelExtension.getPtr();
}

lb_I_Unknown* LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::getImplementation() {
	lbErrCodes err = ERR_NONE;

	if (ukAnwendungenModelExtension == NULL) {

		_CL_VERBOSE << "Warning: peekImplementation() has not been used prior.\n" LOG_
	
		AnwendungenInternalFormatWriterExtension* AnwendungenModelExtension = new AnwendungenInternalFormatWriterExtension();
		
	
		QI(AnwendungenModelExtension, lb_I_Unknown, ukAnwendungenModelExtension)
	}
	
	lb_I_Unknown* r = ukAnwendungenModelExtension.getPtr();
	ukAnwendungenModelExtension.resetPtr();
	return r;
}

void LB_STDCALL lbPluginAnwendungenInternalFormatWriterExtension::releaseImplementation() {
        lbErrCodes err = ERR_NONE;

        if (ukAnwendungenModelExtension != NULL) {
                ukAnwendungenModelExtension--;
                ukAnwendungenModelExtension.resetPtr();
        }
}
